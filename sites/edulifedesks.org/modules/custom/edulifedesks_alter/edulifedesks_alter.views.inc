<?php
// $Id$
/**
 * @file
 * Provides views data and handler overrides information for edulifedesks_alter
 */
/**
 * Implementation of hook_views_default_views_alter().
 *
 * Alters default view but will not update a view that has been customised in UI.
 * To programmatically edit a custom view, use views_get_view, $view->add_item and $view->save() 
 */
function edulifedesks_alter_views_default_views_alter(&$views) {
  // Get content types and add filter to exclude all from default EOL Partnership view
  if (isset($views[EOL_PARTNERSHIP_VIEW_NAME])) {
    // Configure types filter
    $types = array('ifa_upload' => 'ifa_upload', 'taxon_page' => 'taxon_page');
    $views[EOL_PARTNERSHIP_VIEW_NAME]->display['default']->display_options['filters']['type']['operator'] = 'in';
    $views[EOL_PARTNERSHIP_VIEW_NAME]->display['default']->display_options['filters']['type']['value'] = $types;
    // Add content profile relationship to get given and family name of author
    $views[EOL_PARTNERSHIP_VIEW_NAME]->display['default']->display_options['relationships']['content_profile_rel'] = array(
      'label' => 'Content Profile',
      'required' => 0,
      'type' => 'profile',
      'id' => 'content_profile_rel',
      'table' => 'users',
      'field' => 'content_profile_rel',
      'relationship' => 'none',
    );
    // Add fields for author name, relationship with content profile
    $views[EOL_PARTNERSHIP_VIEW_NAME]->display['default']->display_options['fields']['uid'] = array(
      'label' => 'uid',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_user' => 1,
      'exclude' => 0,
      'id' => 'uid',
      'table' => 'users',
      'field' => 'uid',
      'relationship' => 'none',
    );
    $views[EOL_PARTNERSHIP_VIEW_NAME]->display['default']->display_options['fields']['field_vcard_family_value'] = array(
      'label' => 'family',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'custom',
      'format' => 'plain',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_vcard_family_value',
      'table' => 'node_data_field_vcard_family',
      'field' => 'field_vcard_family_value',
      'relationship' => 'content_profile_rel',
    );
    $views[EOL_PARTNERSHIP_VIEW_NAME]->display['default']->display_options['fields']['field_vcard_given_value'] = array(
      'label' => 'given',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'custom',
      'format' => 'plain',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_vcard_given_value',
      'table' => 'node_data_field_vcard_given',
      'field' => 'field_vcard_given_value',
      'relationship' => 'content_profile_rel',
    );
    // To get right order delete existing name field and add new one
    unset($views[EOL_PARTNERSHIP_VIEW_NAME]->display['default']->display_options['fields']['name']);
    $views[EOL_PARTNERSHIP_VIEW_NAME]->display['default']->display_options['fields']['name'] = array(
      'label' => 'agent role="author"',
      'alter' => array(
        'alter_text' => 1,
        'text' => '[name]|[field_vcard_given_value] [field_vcard_family_value]',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_user' => 0,
      'overwrite_anonymous' => 0,
      'anonymous_text' => '',
      'exclude' => 0,
      'id' => 'name',
      'table' => 'users',
      'field' => 'name',
      'relationship' => 'none',
    );
    
    // Add relationship with parent node (for images)
    $views[EOL_PARTNERSHIP_VIEW_NAME]->display['default']->display_options['relationships']['field_attached_to_nodes_nid'] = array(
      'label' => 'Associated with',
      'required' => 0,
      'delta' => '-1',
      'id' => 'field_attached_to_nodes_nid',
      'table' => 'node_data_field_attached_to_nodes',
      'field' => 'field_attached_to_nodes_nid',
      'relationship' => 'none',
    );
    // Add 'parent' nid
    $views[EOL_PARTNERSHIP_VIEW_NAME]->display['default']->display_options['fields']['nid_1'] = array(
      'label' => 'taxon_nid',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'nid_1',
      'table' => 'node',
      'field' => 'nid',
      'relationship' => 'field_attached_to_nodes_nid',
    );
    $views[EOL_PARTNERSHIP_VIEW_NAME]->display['default']->display_options['fields']['field_dwc_scientificname_value_1'] = array(
      'label' => 'dwc:ScientificName[secondary]',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'custom',
      'format' => 'plain',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_dwc_scientificname_value_1',
      'table' => 'node_data_field_dwc_scientificname',
      'field' => 'field_dwc_scientificname_value',
      'relationship' => 'field_attached_to_nodes_nid',
    );
    // Add geolocation fields
    $views[EOL_PARTNERSHIP_VIEW_NAME]->display['default']->display_options['fields']['field_geo_map_openlayers_wkt'] = array(
      'label' => 'geo:Point',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'custom',
      'format' => 'openlayers_wkt',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_geo_map_openlayers_wkt',
      'table' => 'node_data_field_geo_map',
      'field' => 'field_geo_map_openlayers_wkt',
      'relationship' => 'none',
    );
  }
}
/**
 * Implementation of hook_views_handlers().
 */
function edulifedesks_alter_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'edulifedesks_alter') .'/includes',
    ),
    'handlers' => array(
      'edulifedesks_alter_views_handler_field_node_link_edit' => array(
        'parent' => 'views_handler_field_node_link',
      ),
      'edulifedesks_alter_views_handler_field_node_link_delete' => array(
        'parent' => 'views_handler_field_node_link',
      ),
    ),
  );
}
/**
 * Implementation of hook_views_data_alter().
 */
function edulifedesks_alter_views_data_alter(&$data) {
  $data['node']['edit_node']['field']['handler'] = 'edulifedesks_alter_views_handler_field_node_link_edit';
  $data['node']['delete_node']['field']['handler'] = 'edulifedesks_alter_views_handler_field_node_link_delete';
}
/**
 * Implementation of hook_views_query_alter().
 */
function edulifedesks_alter_views_query_alter(&$view, &$query) {
  global $user;
  // Don't show groups that current use is a member of in 'Groups you can join' view
  if ($view->name == 'edulifedesks_join_groups' && $query->where[0]['clauses'][0] == 'node.nid = %d') {
    $query->where[0]['clauses'][0] = 'node.nid NOT IN (%s)';
    $query->where[0]['args'][0] = 'select nid from og_uid where uid = ' . $user->uid;
  }
  if ($view->name == 'og_mytracker_edulifedesks') {
    // TODO: find a way to make og_user_roles apply to listing in this view
  }
}
/**
 * Implementation of hook_views_plugins().
 * /
function edulifedesks_alter_views_plugins() {
  return array(
    'display' => array(
    // ... list of display plugins,
    ),
    'style' => array(
    // ... list of style plugins,
    ),
    'row' => array(
    // ... list of row style plugins,
    ),
    'argument default' => array(
    // ... list of argument default plugins,
    ),
    'argument validator' => array(
    // ... list of argument validator plugins,
    ),
    'access' => array(
    // ... list of access plugins,
    ),
  );
}*/