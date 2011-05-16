<?php
// $Id: views_crosstab_table.inc,v 1.1 2009/11/02 07:19:40 grugnog Exp $

/**
 * Style plugin to transform a linear query into a crosstab table.
 *
 * @ingroup views_style_plugins
 */
class views_crosstab_table extends views_plugin_style_table {

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    
    $handlers = $this->display->handler->get_handlers('field');
    $columns = $this->sanitize_columns($this->options['columns']);
    
    $defaults_select = array_keys($columns);
    if (count($defaults_select) < 3) {
      drupal_set_message(t('At least 3 fields need to be added to your view to create a crosstab.'), 'error');
      return;
    }
    
    $crosstab_rows_default = array_shift($defaults_select);
    $crosstab_columns_default = array_shift($defaults_select);
    $crosstab_data_default = array_shift($defaults_select);

    $form['#theme'] = 'views_crosstab_ui_table';
    foreach ($columns as $field => $column) {
      $safe = str_replace(array('][', '_', ' '), '-', $field);
      $id = 'edit-style-options-columns-' . $safe;
      // Collect the row, column and data fields.
      // TODO: JS helper.
      $radio_id = form_clean_id('edit-crosstab-rows-' . $field);
      $form['crosstab_rows'][$field] = array(
        '#type' => 'radio',
        '#return_value' => $field,
        '#parents' => array('style_options', 'crosstab_rows'),
        '#id' => $radio_id,
        '#attributes' => array('id' => $radio_id),
        '#default_value' => isset($this->options['crosstab_rows']) ? $this->options['crosstab_rows'] : $crosstab_rows_default,
        '#process' => array('views_process_dependency'),
        '#dependency' => array($id => array($field)),
      );
      $radio_id = form_clean_id('edit-crosstab-columns-' . $field);
      $form['crosstab_columns'][$field] = array(
        '#type' => 'radio',
        '#return_value' => $field,
        '#parents' => array('style_options', 'crosstab_columns'),
        '#id' => $radio_id,
        '#attributes' => array('id' => $radio_id),
        '#default_value' => isset($this->options['crosstab_columns']) ? $this->options['crosstab_columns'] : $crosstab_columns_default,
        '#process' => array('views_process_dependency'),
        '#dependency' => array($id => array($field)),
      );
      $radio_id = form_clean_id('edit-crosstab-data-' . $field);
      $form['crosstab_data'][$field] = array(
        '#type' => 'radio',
        '#return_value' => $field,
        '#parents' => array('style_options', 'crosstab_data'),
        '#id' => $radio_id,
        '#attributes' => array('id' => $radio_id),
        '#default_value' => isset($this->options['crosstab_data']) ? $this->options['crosstab_data'] : $crosstab_data_default,
        '#process' => array('views_process_dependency'),
        '#dependency' => array($id => array($field)),
      );
    }
    
    // Collect the operation to use on the data.
    $form['crosstab_operation'] = array(
      '#type' => 'select',
      '#title' => 'Crosstab operation',
      '#options' => array('COUNT' => 'Count', 'SUM' => 'Sum', 'AVG' => 'Average', 'MIN' => 'Minimum', 'MAX' => 'Maximum'),
      '#default_value' => isset($this->options['crosstab_operation']) ? $this->options['crosstab_operation'] : 'COUNT',
      '#weight' => -1,
    );
  }

  function options_validate(&$form, &$form_state) {
    parent::options_validate($form, $form_state);

     
    foreach ($options as $option => $option_name) {
      foreach ($options as $optiontest => $optiontest_name) {
        if ($option == $optiontest) {
          break;
        }
        if ($form_state['values']['style_options'][$option] == $form_state['values']['style_options'][$optiontest]) {
          $field = $form_state['values']['style_options'][$option];
          $error_items = array(
            '%field' => $form['info'][$field]['name']['#value'],
            '%option' => $option_name,
            '%optiontest' => $optiontest_name,
          );
          form_error($form[$option][$field], t('You cannot set the same field (%field) to be a source for <strong>both</strong> %option and %optiontest.', $error_items));
        }
      }
    }
  }

  function query() {
    parent::query();

    $options = $this->view->style_plugin->options;
    $columns = $this->sanitize_columns($this->options['columns']);

    // Clone the query, and modify the clone to determine the crosstab columns.
    $crosstab_columns_query = drupal_clone($this->view->query);
    foreach ($crosstab_columns_query->fields as $key => $field) {
      // We set aggregate to TRUE for each field, to ensure ours is the only
      // groupby.
      // http://drupal.org/node/385158
      $crosstab_columns_query->fields[$key]['aggregate'] = TRUE;
      $this->view->query->fields[$key]['aggregate'] = TRUE;
      // Locate the crosstab rows, column and data fields.
      if ($field['field'] == $options['crosstab_rows']) {
        $crosstab_rows = $field;
      }
      // Patch for using crosstab with Organic Groups as rows -lwalley
      elseif ($options['crosstab_rows'] == 'group_nid' && $key == 'og_ancestry_nid') {
        $crosstab_rows = $field;
      }
      // End patch
      if ($field['field'] == $options['crosstab_columns']) {
        $crosstab_columns = $field;
      }
      if ($field['field'] == $options['crosstab_data']) {
        $crosstab_data = $field;
      }
      
    }

    // Basic sanity checking.
    $defaults_select = array_keys($columns);
    if (count($defaults_select) < 3) {
      // This is only a warning at this stage (unlike on the options screen,
      // where we set an error, to further ensure we have the users attention.
      drupal_set_message(t('At least 3 fields need to be added to your view to create a crosstab.'), 'warning');
      $error = TRUE;
    }
    // The options do not appear to be set, or we haven't located each field
    // in the query. This can happen on fresh views, or on views where a field
    // used for a previously configured crosstab has been removed.
    if (empty($options['crosstab_rows']) || empty($options['crosstab_columns']) || empty($options['crosstab_data']) || empty($options['crosstab_operation'])
        || !isset($crosstab_rows['field']) || !isset($crosstab_columns['field']) || !isset($crosstab_data['field'])) {
      drupal_set_message(t('The Crosstab Table views style does not appear to be configured.'), 'warning');
      $error = TRUE;
    }
    if (isset($error)) {
      // This falls back to the parent table handler.
      drupal_set_message(t('The crosstab could not be displayed, showing a linear table instead.'), 'message');
      return;
    }
    
    // Group by the header, and remove any existing orders.
    $crosstab_columns_query->add_groupby($crosstab_columns['alias']);
    $crosstab_columns_query->orderby = array();
    $query = $crosstab_columns_query->query();

    // Run the query and collate the results.
    // Patch to add args to query for filters -lwalley
    $args = $crosstab_columns_query->get_where_args();
    $results = db_query($query, $args);
    // End patch
    
    // Crosstab COUNT is really a SUM of 1s.
    if ($options['crosstab_operation'] == 'COUNT') {
      $data = 1;
      $options['crosstab_operation'] = 'SUM';
    }
    else {
      $data = $crosstab_data['table'] . '.' . $crosstab_data['field'];
    }

    // Loop through the columns, adding to the query and the view.
    while ($result = db_fetch_object($results)) {
      $crosstab_column = $result->$crosstab_columns['alias'];
      $alias = $crosstab_columns['alias'] . '_' . strtolower(preg_replace('/[^A-Za-z_-]+/', '_', $crosstab_column));
      // Add the new field to the query, basing it on the original data query field.
      $this->view->query->add_field(NULL, $options['crosstab_operation'] . '(IF(' . $crosstab_columns['table'] . '.' . $crosstab_columns['field'] . ' = "' . $crosstab_column . '", ' . $data . ', 0))', $alias);
      $this->view->query->fields[$alias]['aggregate'] = TRUE;
      
      // Add the field to the view, basing it on the data view field.
      $this->view->field[$alias] = drupal_clone($this->view->field[$crosstab_data['field']]);
      // Set the alias, label and remove the table association (since it is aggregate).
      $this->view->field[$alias]->field_alias = $alias;
      $this->view->field[$alias]->options['label'] = $crosstab_column;
      unset($this->view->field[$alias]->table_alias);
      
      // Add the field to the current style_plugin, so we can sort with it.
      $this->view->style_plugin->options['info'][$alias] = $this->view->style_options['info'][$crosstab_data['field']];
      $this->view->style_plugin->options['columns'][$alias] = $alias;
    }

    // Add a "Total" column.
    // TODO: Add an option for this.
    $alias = $crosstab_columns['alias'] . '_total';
    // Patch to switch total operation from SUM to COUNT -lwalley
    $total_operation = ($options['crosstab_operation'] == 'SUM') ? 'COUNT' : $options['crosstab_operation'];
    $this->view->query->add_field(NULL, $total_operation . '(' . $crosstab_data['table'] . '.' . $crosstab_data['field'] . ')', $alias);
    // End patch
    $this->view->query->fields[$alias]['aggregate'] = TRUE;
    $this->view->field[$alias] = drupal_clone($this->view->field[$crosstab_data['field']]);
    $this->view->field[$alias]->field_alias = $alias;
    $this->view->field[$alias]->options['label'] = t('Total');
    $this->view->style_plugin->options['info'][$alias] = $this->view->style_options['info'][$crosstab_data['field']];
    $this->view->style_plugin->options['columns'][$alias] = $alias;

    // Remove the source header and data source fields, since they have now
    // been replaced by the crosstab.
    unset($this->view->field[$crosstab_data['field']]);
    unset($this->view->field[$crosstab_columns['field']]);
    unset($this->view->style_plugin->options['info'][$crosstab_data['field']]);
    unset($this->view->style_plugin->options['info'][$crosstab_columns['field']]);
    unset($this->view->style_plugin->options['columns'][$crosstab_data['field']]);
    unset($this->view->style_plugin->options['columns'][$crosstab_columns['field']]);
    
    // Rebuild the sort, so that column sorts will be added by the new fields.
    $this->view->style_plugin->build_sort();

    // Add a group by for the crosstab row grouping field.
    // This has to come after the build_sort, or it tries to add groups.
    $this->view->query->add_groupby($crosstab_rows['field']);
  }
}