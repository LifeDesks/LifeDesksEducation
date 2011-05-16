<?php
// $Id$
/**
 * @file
 * Menu callbacks for Organic Groups Content Permissions type configuration pages.
 */
/**
 * 
 * Menu call back for content type configuration
 */
function og_content_permissions_configure_form(&$form_state = NULL, $group_node, $type_name = NULL) {
  $form = array();
  // Get enabled types
  $configurable_types = variable_get('og_content_permissions_post_types', array());
    
  if (empty($type_name) || !in_array($type_name, $configurable_types)) {
    drupal_set_title(t('Content settings'));
    $form['configurable_types'] = array(
      '#type' => 'markup',
    );
    if (empty($configurable_types)) {
      $form['configurable_types'] = array(
        '#prefix' => '<p>',
        '#value' => t('There are no configurable content types. Contact your site administrator.'),
        '#suffix' => '</p>',
      );
    }
    else {
      foreach ($configurable_types as $type => $enabled) {
        if ($enabled !== 0) {
          $form['configurable_types'] = array(
            '#prefix' => '<p>',
            '#value' => l(t('Configure !type form', array('!type' => str_replace('_', ' ', $type))), 'node/' . $group_node->nid .'/configure/' . $type),
            '#suffix' => '</p>',
          );
        }
      }
    }
  }
  else {
    // Gather field information.
    $type = content_types($type_name);
    $fieldset_details = fieldgroup_groups($type_name);
    drupal_set_title(t('!type configuration', array('!type' => $type['name'])));
    $form['og_content_permissions_introduction'] = array(
      '#type' => 'markup',
      '#value' => t("Because of the large number of content sections available on the !type editing form,"
                   ." it may be useful to limit the number that are displayed. This page allows group administrators" 
                   ." to choose which content sections to include on the !type editing form. All !types"
                   ." will be limited to the content sections that are checked here. Note that sections on existing"
                   ." !types that already have content may not be unchecked here until that content has been removed"
                   ." from the !types.", array('!type' => strtolower($type['name']))),
    );
    $fieldsets = array();
    foreach ($type['fields'] as $field_name => $field) {
      if (!empty($field['display_settings']['parent'])) {
        $fieldsets[$field['display_settings']['parent']][$field_name] = $field;
      }
      else {
        $fieldset['og_content_permissions_other_fields'][$field_name] = $field;
      }
    }
    $configurable_fields = variable_get('og_content_permissions_configurable_fields', array());
    // TODO: Invoke hook to allow other modules to programmatically modify allowed fields? Can manually set fields in admin/og/content-permissions
    $options = array();
    $starting_values = array();
    foreach ($configurable_fields[$type_name] as $field => $configurable) {
      if ($configurable !== 0) {
        foreach ($fieldsets as $fieldset => $fields) {
          if (!empty($fields[$field])) {
            $options[$fieldset][$fields[$field]['field_name']] = $fields[$field]['widget']['label'];
            $starting_values[$fieldset][$fields[$field]['field_name']] = $fields[$field]['field_name'];
            break;
          }
        }
      }
    }
    $form['post_type_fields'] = array(
      '#type' => 'hidden',
      '#value' => $type['fields'],
    );
    $form['group_node'] = array(
      '#type' => 'hidden',
      '#value' => $group_node,
    );
    $form['type_name'] = array(
      '#type' => 'hidden',
      '#value' => $type_name,
    );
    // List nodes containing content in disabled fields
    if (!empty($form_state['existing_content'])) {
      foreach ($form_state['existing_content'] as $field => $results) {
        $form['existing_content'][$field] = array(
          '#type' => 'markup',
          '#prefix' => '<div><h3>' . t('The field %field is being used in:', array('%field' => $field)) .'</h3>',
          '#value' => $results,
          '#suffix' => '</div>',
        );
      }
    }
    // Get saved field permissions, for default values
    $field_permissions = variable_get('og_content_permissions_per_group', array());
    foreach ($options as $fieldset => $fields) {
      $form[$fieldset .'_fields'] = array(
        '#type' => 'fieldset',
        '#title' => $fieldset_details[$fieldset]['label'],
        '#collapsible' => FALSE,
      );
      $enabled_fields = !empty($field_permissions[$group_node->nid][$type_name][$fieldset]) ? $field_permissions[$group_node->nid][$type_name][$fieldset] : $starting_values[$fieldset];
      $form[$fieldset .'_fields'][$fieldset .'_permissions'] = array(
        '#type' => 'checkboxes',
        '#description' => t('Check box to show item on !type edit form. Uncheck box to hide item on !type edit form.', array('!type' => str_replace('_', ' ', $type_name))),
        '#options' => $fields,
        '#default_value' => $enabled_fields,
      );
    }
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save settings'),
    );
  }
  // Restore user input if necessary
  if (is_array($form_state['values']) || count($form_state['values']) > 0 || (!empty($form_state['rebuild']) && $form_state['rebuild'] === TRUE)) _og_content_permissions_restore_user_input($form, $form_state);
  $form_state['rebuild'] = FALSE;
  return $form;
}
/**
 * Validation handler for og_content_permissions_configure_form.
 */
function og_content_permissions_configure_form_validate($form, &$form_state) {

  $rebuild = FALSE;
  foreach ($form_state['values'] as $element => $values) {
    if (preg_match('/_permissions$/', $element)) {
      foreach ($values as $field => $enabled) {
        // If field is disabled check no existing content, ignore select widgets as these will not be empty
        if ($enabled === 0 && $form_state['values']['post_type_fields'][$field]['widget']['type'] != 'optionwidgets_select') {
          if (!empty($view)) unset($view);
          $view = views_get_view('og_content_permissions', TRUE);
          if (!empty($view)) {
            $display_id = 'default';
            $view->set_display($display_id);
            $view->set_arguments(array($form_state['values']['group_node']->nid));
            $id = $view->add_item($display_id, 'filter', 'node_data_' . $field, $field .'_value');
            $item = $view->get_item($display_id, 'filter', $id);
            $item['operator'] = 'not empty';
            $view->set_item($display_id, 'filter', $id, $item);
            $view->is_cacheable = FALSE;
            $nodes = $view->preview($display_id);
            foreach ($view->result as $result) {
              if (count($result) > 0) {
                // Content exists for this field
                $rebuild = TRUE;
                $form_state['existing_content'][$form_state['values']['post_type_fields'][$field]['widget']['label']] = $nodes;
                drupal_set_message(t('The field !field is already in use and contains content, it cannot be disabled.', array('!field' => $form_state['values']['post_type_fields'][$field]['widget']['label'])), 'error', FALSE);
              }
            }
          }
        }
      }
    }
  }
  if ($rebuild === TRUE) {
    $form_state['rebuild'] = TRUE;
    drupal_set_message(t('Your settings have not been saved.'), 'error', FALSE);
  }
  
}
/**
 * Default submit handler for og_content_permissions_configure_form.
 */
function og_content_permissions_configure_form_submit($form, &$form_state) {
  $field_permissions_per_group = variable_get('og_content_permissions_per_group',array());
  foreach ($form_state['values'] as $element => $values) {
    if (preg_match('/_permissions$/', $element)) {
      $element = str_replace('_permissions', '', $element);
      $field_permissions_per_group[$form_state['values']['group_node']->nid][$form_state['values']['type_name']][$element] = $values;
    }
  }
  variable_set('og_content_permissions_per_group' , $field_permissions_per_group);
  drupal_set_message(t('Your settings have been saved.'));
}
/**
 * Helper function to restore user input of form data on form rebuild.
 */
function _og_content_permissions_restore_user_input(&$form, &$form_state) {
  // If form is not being rebuilt or form_state doesn't contain any values then don't act, otherwise copy input to rebuilt form.
  $values = $form_state['values'];
  foreach ($form as $key => &$parent) {
    if (!empty($parent['#type'])) {
      if (!empty($parent['#tree']) && $parent['#tree'] == FALSE) {
        $values = $values[$key];
      }
      _og_content_permissions_restore_user_input_recursive($key, $parent, $values);
    }
  }
}
/**
 * Helper function to recursively restore user input.
 */
function _og_content_permissions_restore_user_input_recursive($key, &$parent, &$values) {
  $value = $values[$key];
  if (!empty($value)) {
    $parent['#default_value'] = $value;
  }
  foreach ($parent as $key => &$child) {
    if (is_array($child) && !empty($child['#type'])) {
      if (!empty($child['#tree']) && $child['#tree'] == FALSE) {
        $values = $values[$key];
      }
      _og_content_permissions_restore_user_input_recursive($key, $child, $values);
    }
  }
}
/**
 * Helper function to get fieldset label, given it's field name
 */
function _og_content_permissions_get_group_label($content_type, $field_name) {
  return db_result(db_query("SELECT group_name FROM {". fieldgroup_fields_tablename() ."} WHERE type_name = '%s' AND field_name = '%s'", $content_type, $field_name));
}