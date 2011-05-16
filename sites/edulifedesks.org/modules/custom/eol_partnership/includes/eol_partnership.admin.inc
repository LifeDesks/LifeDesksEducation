<?php
// $Id$
/**
 * @file
 * Menu callbacks for EOL Partnership administration settings.
 */

/**
 * Overview of EOL Partnership administration
 */
function eol_partnership_admin_overview() {
  
  /**
   * TODO: Use EOL API to get information about content partner registration
   * See helper function _eol_partnership_api_ping() 
   */

  // Create data array to pass for themers
  $data = array();
  // Create array of content for output to theme
  $content = array();
  
  // Get details of EOL partnership view used to generate data for XML
  $view = views_get_view(EOL_PARTNERSHIP_VIEW_NAME);
  $display = variable_get('eol_partnership_view_display', EOL_PARTNERSHIP_DISPLAY_NAME);
  $data['view'] = $view;
  $view_name = (user_access('administer views')) ? l($view->name, 'admin/build/views/edit/' .$view->name) : $view->name;
  $feed_path = $view->display[$display]->display_options['path'];
  $view_filters = isset($view->display[$display]->display_options['filters']) ? $view->display[$display]->display_options['filters'] : $view->display['default']->display_options['filters'];
  $view_fields = isset($view->display[$display]->display_options['fields']) ? $view->display[$display]->display_options['fields'] : $view->display['default']->display_options['fields'];
  
  // Get name of any fields that have view label 'dwc:ScientificName'
  $scientific_name_field_names = array();
  foreach ($view_fields as $field_details) {
    if ($field_details['label'] == 'dwc:ScientificName') $scientific_name_field_names[] = preg_replace('#^node_data_#i', '', $field_details['table'], 1);
  }
  
  // Get content types that have the EOL compatible scientific name field
  $content_types = content_types();
  $eol_content_types = array();
  foreach ($scientific_name_field_names as $field_name) {
    foreach ($content_types as $type) {
      if (isset($type['fields'][$field_name])) {
        $eol_content_types[$field_name][$type['type']] = $type['name'];
      }
    }
  }
  $data['eol_compatible_content_types'] = $eol_content_types;

  // Build string of themed content
  $replace = array('!add_fields_url' => url('admin/content/eol-partnership/add/fields'), '!view_name' => $view_name);
  $content['view_status']['description'] = ($view->disabled) ? '<p>' .t('The <em>!view_name</em> view is currently disabled. <a href="!add_fields_url">Add fields</a> or customise the <em>!view_name</em> view to continue.', $replace) .'</p>' : '<p>' .t('The <em>!view_name</em> view is currently enabled', $replace) .'</p>';
  if (count($scientific_name_field_names) < 1) {
    $content['content_types']['description'] = '<p>' .t('The required dwc:ScientificName label is missing from the <em>!view_name</em> view.'
                      . ' This suggests that the EOL Partnership view has not been loaded properly or that you or a site administrator has modified the view.'
                      . ' To make use of the EOL Partnership view it must include a field with the label dwc:ScientificName.'
                      , $replace) .'</p>';
                      
  } elseif (count($eol_content_types) < 1) {
    $content['content_types']['description'] = '<p>' .t('You do not currently appear to have any EOL compatible content types.'
                      . ' This suggests that either EOL fields have not yet been <a href="!add_fields_url">added</a> to any new or existing content types, or'
                      . ' the required dwc:ScientificName label is not correctly matched to a custom scientific name field in the <em>!view_name</em> view.'
                      , $replace) .'</p>';
  } else {
    $compatible_content_types = array();
    foreach ($eol_content_types as $field => $types) {
      foreach ($types as $type => $name) {
        $converted_type = str_replace('_', '-', $type);
        if (user_access('administer content types')) {
          $item = l(t('!name (!type)', array('!name' => $name, '!type' => $type)), 'admin/content/node-type/' .$converted_type, array('attributes' => array('class' => $converted_type))); 
        } else {
          $item = t('!name', array('!name' => $name));
        }
        $compatible_content_types[] = array(
          'data' => $item,
          'class' => $converted_type,
        );
      }
    }

    // Get list of content types used in filter
    $included_types = array();
    $excluded_types = array(); 
    if (isset($view_filters['type'])) {
      if ($view_filters['type']['operator'] == 'in') {
        $included_types = $view_filters['type']['value'];
      } elseif ($view_filters['type']['operator'] == 'not in') {
        $excluded_types = $view_filters['type']['value'];
      }
    }
    if (count($included_types) > 0) {
      foreach ($content_types as $type_name => $type) {
        if (!array_key_exists($type_name, $included_types)) $excluded_types[$type_name] = t('!type', array('!type' => $type_name));   
      }
    } elseif (count($excluded_types) > 0) {
      foreach ($content_types as $type_name => $type) {
        if (!array_key_exists($type_name, $excluded_types)) $included_types[$type_name] = t('!type', array('!type' => $type_name));
      }
    }
    
    if (count($included_types) > 0) {
      $content['content_types']['included_description'] = '<p>' .t('Content types currently included in the EOL Partnership view (<em>!view_name</em>):', array('!view_name' => $view_name)) .'</p>';
      $content['content_types']['included_list'] = theme('item_list', $included_types);
    } 
    if (count($excluded_types) > 0) {
      $content['content_types']['excluded_description'] = '<p>' .t('Content types currently excluded from the EOL Partnership view (<em>!view_name</em>):', array('!view_name' => $view_name)) .'</p>';
      $content['content_types']['excluded_list'] = theme('item_list', $excluded_types);
    }
    $content['content_types']['compatible_description'] = '<p>' .t('Content types which appear to have scientific name fields compatible with EOL:') .'</p>';
    $content['content_types']['compatible_list'] = theme('item_list', $compatible_content_types);
    
    if (!$view->disabled) {
      // Get file path or feed url
      if (variable_get('eol_partnership_static', EOL_PARTNERSHIP_DYNAMIC_XML) == EOL_PARTNERSHIP_STATIC_XML) {
        $dir = variable_get('eol_partnership_directory', '');
        $files = file_scan_directory($dir, '.*');
        $file_list = array();
        foreach ($files as $file_path => $file_name) {
          $file_list[] = array(
            'data' => '<a class="xml-file" href="' .url($file_path) .'">' .url($file_path, array('absolute' => TRUE)) .'</a>',
            'class' => $file_name->name,
          );
          $content['xml']['description'] = '<p>' .t('Add file path to your EOL Content Partner account:') .'</p>';
          $content['xml']['download'] = theme('item_list', $file_list); 
          //TODO: Add an XML validation checker and inform user of errors in file generation, see eol_partnership.module error handling 
        }
      } else {
        $xml_url = $feed_path;
        $content['xml']['description'] = '<p>' .t('Add the URL <em>!xml_url</em> to your EOL Content Partner account.', array('!xml_url' => url($xml_url, array('absolute' => TRUE)))) .'</p>';
        $content['xml']['download']  .= '<p>' .t('<a class="xml-file" href="!xml_url">Download the XML file</a> produced by the default EOL Partnership view.', array('!xml_url' => url($feed_path))) .'</p>';
      }
    }
  }
  if (variable_get('eol_partnership_static', EOL_PARTNERSHIP_DYNAMIC_XML) == EOL_PARTNERSHIP_STATIC_XML) {
    $content['xml']['rebuild_xml_form'] = drupal_get_form('eol_partnership_form_rebuild_xml_files');
  }
  return theme('eol_partnership_admin_overview', $data, $content);
}
/**
 * Process variables for eol-partnership-admin-overview.tpl.php.
 *
 * @see eol-partnership-admin-overview.tpl.php
 */
function eol_partnership_preprocess_eol_partnership_admin_overview(&$vars) {
  
}
/**
 * Import CCK fields into existing content type or create new content type
 * Menu call back for admin add fields form
 */
function eol_partnership_form_add_fields(&$form_state) {
  $form = array();
  // User creates new content type or selects existing content type into which fields can be imported
  $types = node_get_types('names');
  if ($types) {
    $create = '<Create new EOL Taxon Page content type>';
    array_unshift($types, $create);
    $form['content_type'] = array(
      '#type' => 'select',
      '#title' => t('Select content type to add fields to'),
      '#default_value' => (isset($form_state['values']['content_type'])) ? $form_state['values']['content_type'] : '0',
      '#options' => $types,
      '#description' => t('Add EOL compatible fields into an existing content type, or create a new EOL Taxon Page content type.'),
    );
  }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add fields'),
  );
  return $form;
}
/**
 * Validate eol_partnership_form_add_fields form submissions.
 */
function eol_partnership_form_add_fields_validate($form, &$form_state) {

}
/**
 * Process eol_partnership_form_add_fields form submissions.
 *
 */
function eol_partnership_form_add_fields_submit($form, &$form_state) {
  // Get content type
  if ($form_state['values']['content_type'] == '0') {
    $type = '<create>';
  } else {
     $type = $form_state['values']['content_type']; 
  }
  $macro = '';
  $file = realpath('.') .'/' .drupal_get_path('module', 'eol_partnership') .'/includes/eol_partnership_eol_taxon_page.content_default.inc';
  // Add fields to content type
  _eol_partnership_create_content($type, $macro, $file);
  
  // Append content type to variable array of content types to which EOL fields have been added, to be used by views filter
  if ($type == '<create>') $type = 'eol_taxon_page';
  
  // Add content type to default type filter to default view
  $view = views_get_view(EOL_PARTNERSHIP_VIEW_NAME, FALSE);
  $display = variable_get('eol_partnership_view_display', EOL_PARTNERSHIP_DISPLAY_NAME);
  // Check to see if filters that should be in views 'default' display are being overridden by the feed display
  $display_filters = isset($view->display[$display]->display_options['filters']) ? $display : 'default';
  
  $filter_id = 'type'; // Filter should have been added in default view, with id 'type', if its been removed recreate it
  if (!isset($view->display[$display_filters]->display_options['filters'][$filter_id])) {
    $filter_id = $view->add_item($display_filters, 'filter', 'node', $filter_id); 
  }
  // Add new type depending on operator
  if ($view->display[$display_filters]->display_options['filters'][$filter_id]['operator'] == 'not in' && isset($view->display[$display_filters]->display_options['filters'][$filter_id]['value'][$type])) {
    unset($view->display[$display_filters]->display_options['filters'][$filter_id]['value'][$type]);
  } elseif ($view->display[$display_filters]->display_options['filters'][$filter_id]['operator'] == 'in') {
    $view->display[$display_filters]->display_options['filters'][$filter_id]['value'][$type] = $type;
  }
  $view->disabled = FALSE;
  $view->save();

  drupal_set_message(t('Node type !type as been added to eol_partnership view', array( '!type' => $type)));
}
/**
 * Menu call back for eol partnership settings form
 * Specify XML file generation on cron or harvested on the fly, etc
 */
function eol_partnership_settings() {
  $form = array();

  $form['eol_partnership_settings_xml_output'] = array(
    '#type' => 'fieldset',
    '#title' => t('Select how you would like the XML output to be stored.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
    $form['eol_partnership_settings_xml_output']['eol_partnership_static'] = array(
      '#type' => 'radios',
      '#title' => t('Specify whether to save XML to static files (recommended) or generate XML dynamically during harvest'),
      '#default_value' => variable_get('eol_partnership_static', EOL_PARTNERSHIP_DYNAMIC_XML),
      '#options' => array('dynamic' => t('Dynamic'), 'static' => t('Static file')),
    );
  $form['eol_partnership_settings_schedule'] = array(
    '#type' => 'fieldset',
    '#title' => t('Specify whether you want to rebuild static files automatically.'),
    '#description' => t('You can also <a href="!overview_url">manually rebuild your files</a>', array('!overview_url' => url('admin/content/eol-partnership'))),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
    $form['eol_partnership_settings_schedule']['eol_partnership_cron'] = array(
      '#type' => 'checkbox',
      '#title' => t('Rebuild static XML files (if selected) on cron.'),
      '#description' => t('This option requires cron jobs to be set up on your site, or run manually by an administrator.'),
      '#default_value' => variable_get('eol_partnership_cron', 0),
    );
  $form['eol_partnership_settings_view'] = array(
    '#type' => 'fieldset',
    '#title' => t("Specify view settings"),
    '#description' => t('These settings should only be modified if you have customised the view.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
    $view = views_get_view(EOL_PARTNERSHIP_VIEW_NAME);
    $displays = $view->display;
    $options = array();
    foreach($displays as $name => $display) {
      if ($name != 'default') $options[$name] = $name;
    }
    $form['eol_partnership_settings_view']['eol_partnership_view_display'] = array(
      '#type' => 'select',
      '#title' => t('Select which display to use to generate the view'),
      '#description' => t('The EOL Partnership default display is !default_display', array('!default_display' => EOL_PARTNERSHIP_DISPLAY_NAME)),
      '#options' => $options,
      '#default_value' => variable_get('eol_partnership_view_display', NULL),
    );
  // $form['#submit'][] = '_eol_partnership_settings_custom_submit';
  return system_settings_form($form);
}
/**
 * Validate eol_partnership_settings form.
 */
function eol_partnership_settings_validate($form, &$form_state) {
  if ($form_state['values']['eol_partnership_cron'] == 1) {
    $eol_directory_path = variable_get('eol_partnership_directory', '');
    if (empty($eol_directory_path) || !file_check_directory($eol_directory_path)) {
      form_set_error('eol_partnership_cron', t('EOL Partnership cron job cannot be enabled, the EOL Partnership directory <em>!eol_directory_path</em> is missing. Check <a href="!status">status report</a> to ensure the default directory has been created successfully.', array('!status' => url('admin/reports/status'), '!eol_directory_path' => $eol_directory_path))); 
    }
  }
}
/**
 * Form to rebuild XML file, only applicable if using static files
 */
function eol_partnership_form_rebuild_xml_files() {
  $form = array();
  $form['eol_partnership_rebuild_xml_file'] = array(
    '#type' => 'submit',
    '#access' => user_access('administer eol partnership'),
    '#title' => t('Manually build/re-build static XML files'),
    '#value' => 'Rebuild XML',
    '#suffix' => '',
    /*'#ahah' => array(
      'event' => 'click',
      'path' => 'admin/content/eol-partnership/rebuild-xml',
      'wrapper' => 'ahah-response',
      'method' => 'replace',
      'effect' => 'fade',
      'progress' => array(
        'type' => 'bar',
        'message' => t('Rebuilding...')
      ) 
    ),*/
    //'#submit' => 'eol_partnership_form_rebuild_xml_files_submit',
  );
  /*$form['ahah_response'] = array(
    '#type' => 'markup',
    '#prefix' => '<div id="ahah-response">',
    '#value' => ' ',
    '#suffix' => '</div>',
  );*/
  return $form;
}
/**
 * Custom submit handler for ... to rebuild XML file form
 */
function eol_partnership_form_rebuild_xml_files_submit($form, &$form_state) {
  $batch = array(
    'title' => t('Re-building files'),
    'init_message' => t('Preparing to rebuild...'),
    'error_message' => t('File rebuild has encountered an error.'),
    'progess_message' => t('Rebuilding files...'),
    'progressive' => TRUE,
  );
  $response = _eol_partnership_rebuild_xml_files($batch);
}

/**
 * Helper function to programmatically create content types using the content copy module (see http://groups.drupal.org/node/5272)
 *
 * @param $type string
 * Content type to create, defaults to new type, if type exists, only fields will be added.
 *
 * @param $macro array
 * Exported array from content types -> export. If file is not specified, macro will be used.
 * 
 * @param $file string
 * Path to file containing content copy exported macro data structure. Escaping not required.
 */
function _eol_partnership_create_content($type = '<create>', $macro = '', $file = '') {
  if (!module_exists('content_copy')) {
    drupal_set_message(t('The Content Copy module is required in order to import content types and fields. Enable the Content Copy module before proceeding.'), 'error');
    return;
  }
  $values = array();
  $values['type_name'] = $type;
  // Get macro data for Content import, if file exists get data from file otherwise use macro variable.
  if ($file){
    if (file_exists($file)) {
      $values['macro'] = file_get_contents($file);
    } else {
      drupal_set_message(t('Error: Unable to read input file for import. Please check file exists and path is correct.'), 'error');
      return;
    }
  } elseif ($macro){
    $values['macro'] = $macro;
  } else {
    drupal_set_message(t('Error: Missing import data. File path or macro is required.'), 'error');
    return;
  }
  $content['values'] = $values;
  // Include required files from node and content
  include_once('./'. drupal_get_path('module', 'content') .'/includes/content.admin.inc');
  include_once('./'. drupal_get_path('module', 'node') .'/content_types.inc');
  // Import content by executing content copy import form and passing macro
  drupal_execute('content_copy_import_form', $content);
}