<?php
function imagefield_assist_views_default_views() {
 
  // Find all fields and their content types
  // that use imagefields.
  $types = content_types();
  $fields = array();
  $node_types = array();
  foreach ($types as $type_name => $type) {
    foreach ($type['fields'] as $field_name => $field) {
      if (substr($field['widget']['module'], 0, 10) == 'imagefield') {
        $node_types[] = $field['type_name'];
        $fields[$field_name] = $field;
      }
    }
  }
  
  $views = array();
  
$view = new view;
$view->name = 'imagefield_assist_browser';
$view->description = 'The browser screen for images in imagefield assist module.';
$view->tag = '';
$view->view_php = '';
$view->base_table = 'node';
$view->is_cacheable = FALSE;
$view->api_version = 2;
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
$handler = $view->new_display('default', 'Defaults', 'default');

$relationships = array();
foreach ($fields as $field_name => $field) {
  $relationships[$field_name .'_fid'] = array(
    'label' => 'Image',
    'required' => 0,
    'delta' => -1,
    'id' => $field_name .'_fid',
    'table' => 'node_data_'. $field_name,
    'field' => $field_name .'_fid',
    'relationship' => 'none',
  );
}
$handler->override_option('relationships', $relationships);

$count = 0;
$viewfields = array();
foreach ($fields as $field_name => $field) {
  $append = $count > 0 ? '_'. $count : '';
  $viewfields['fid'. $append] = array(
    'label' => '',
    'alter' => array(
      'alter_text' => 0,
      'text' => '',
      'make_link' => 0,
      'path' => '',
      'link_class' => '',
      'alt' => '',
      'prefix' => '',
      'suffix' => '',
      'help' => '',
      'trim' => 0,
      'max_length' => '',
      'word_boundary' => 1,
      'ellipsis' => 1,
      'strip_tags' => 0,
      'html' => 0,
    ),
    'link_to_file' => 0,
    'exclude' => 1,
    'id' => 'fid'. $append,
    'table' => 'files',
    'field' => 'fid',
    'relationship' => $field_name .'_fid',  
  );
  $viewfields[$field_name .'_fid'] = array(
    'label' => '',
    'alter' => array(
      'alter_text' => 0,
      'text' => '',
      'make_link' => 1,
      'path' => 'imagefield_assist/properties/[fid]',
      'link_class' => '',
      'alt' => '',
      'prefix' => '',
      'suffix' => '',
      'help' => '',
      'trim' => 0,
      'max_length' => '',
      'word_boundary' => 1,
      'ellipsis' => 1,
      'strip_tags' => 0,
      'html' => 0,
    ),
    'link_to_node' => 0,
    'label_type' => 'none',
    'format' => 'ifa_thumbnail_default',
    'multiple' => array(
      'group' => TRUE,
      'multiple_number' => '',
      'multiple_from' => '',
      'multiple_reversed' => FALSE,
    ),
    'exclude' => 0,
    'id' => $field_name .'_fid',
    'table' => 'node_data_'. $field_name,
    'field' => $field_name .'_fid',
    'relationship' => 'none',  
  );
  $count;
}
$handler->override_option('fields', $viewfields);

$handler->override_option('filters', array(
  'type' => array(
    'operator' => 'in',
    'value' => drupal_map_assoc($node_types),
    'group' => '0',
    'exposed' => FALSE,
    'expose' => array(
      'operator' => FALSE,
      'label' => '',
    ),
    'id' => 'type',
    'table' => 'node',
    'field' => 'type',
    'relationship' => 'none',
  ),
));

$handler->override_option('sorts', array(
  'created' => array(
    'order' => 'DESC',
    'granularity' => 'second',
    'id' => 'created',
    'table' => 'node',
    'field' => 'created',
    'relationship' => 'none',
  ),
));
$handler->override_option('access', array(
  'type' => 'none',
));
$handler->override_option('cache', array(
  'type' => 'none',
));
$handler->override_option('use_ajax', TRUE);
$handler->override_option('items_per_page', 8);
$handler->override_option('use_pager', '1');
$handler->override_option('style_plugin', 'grid');
$handler->override_option('style_options', array(
  'grouping' => '',
  'columns' => '4',
  'alignment' => 'horizontal',
));

$views[$view->name] = $view;
return $views;
}
