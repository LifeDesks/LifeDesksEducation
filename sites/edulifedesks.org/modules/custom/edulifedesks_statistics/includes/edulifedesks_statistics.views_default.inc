<?php
// $Id$
/**
 * @file
 * Default view for generating content statistics for Education LifeDesks Statistics module.
 */
/**
 * Implementation of hook_views_default_views().
 */
function edulifedesks_statistics_views_default_views() {
  $view = new view;
  $view->name = 'edulifedesks_statistics';
  $view->description = 'Provides statistics for Education LifeDesks content';
  $view->tag = '';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'type' => array(
      'label' => 'Type',
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
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'relationship' => 'none',
    ),
    'nid' => array(
      'label' => 'Count',
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
      'empty' => '0',
      'hide_empty' => 0,
      'empty_zero' => 1,
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'nid',
      'table' => 'node',
      'field' => 'nid',
      'relationship' => 'none',
    ),
    'views_sql_groupedfields' => array(
      'label' => 'Group By Fields',
      'alter' => array(
        'alter_text' => FALSE,
        'text' => '',
        'make_link' => FALSE,
        'path' => '',
        'alt' => '',
        'link_class' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'trim' => FALSE,
        'max_length' => '',
        'word_boundary' => TRUE,
        'ellipsis' => TRUE,
        'strip_tags' => FALSE,
        'html' => FALSE,
      ),
      'empty' => '0',
      'hide_empty' => 0,
      'empty_zero' => 1,
      'exclude' => '1',
      'id' => 'views_sql_groupedfields',
      'table' => 'views_groupby',
      'field' => 'views_sql_groupedfields',
      'relationship' => 'none',
      'views_groupby_fields_to_group' => array(
        'type' => 'type',
      ),
      'views_groupby_sql_function' => 'count',
      'views_groupby_fields_to_aggregate' => array(
        'nid' => 'nid',
      ),
      'views_groupby_field_sortby' => 'nid',
      'views_groupby_sortby_direction' => 'desc',
    ),
  ));
  $handler->override_option('arguments', array(
    'group_nid' => array(
      'default_action' => 'default',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '',
      'breadcrumb' => '',
      'default_argument_type' => 'php',
      'default_argument' => '',
      'validate_type' => 'og_group_types',
      'validate_fail' => 'empty',
      'break_phrase' => 1,
      'not' => 0,
      'id' => 'group_nid',
      'table' => 'og_ancestry',
      'field' => 'group_nid',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        '2' => 0,
        '4' => 0,
        '3' => 0,
        '6' => 0,
        '7' => 0,
        '5' => 0,
        '11' => 0,
      ),
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '$group = og_get_group_context();
  if (isset($group->nid)) return $group->nid;',
      'validate_argument_node_type' => array(
        'assignment' => 0,
        'book' => 0,
        'class' => 0,
        'error' => 0,
        'evaluation' => 0,
        'feature' => 0,
        'feed' => 0,
        'help' => 0,
        'help_tip' => 0,
        'home' => 0,
        'ifa_upload' => 0,
        'page' => 0,
        'profile' => 0,
        'slide' => 0,
        'story' => 0,
        'taxon_page' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(
        '4' => 0,
        '35' => 0,
        '28' => 0,
        '21' => 0,
        '22' => 0,
        '26' => 0,
        '34' => 0,
        '15' => 0,
        '29' => 0,
        '30' => 0,
        '20' => 0,
        '19' => 0,
        '23' => 0,
        '5' => 0,
        '27' => 0,
        '24' => 0,
      ),
      'validate_argument_type' => 'tid',
      'validate_argument_transform' => 0,
      'validate_user_restrict_roles' => 0,
      'validate_argument_is_member' => 0,
      'validate_argument_php' => '',
      'override' => array(
        'button' => 'Override',
      ),
    ),
  ));
  $handler->override_option('filters', array(
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'assignment' => 'assignment',
        'evaluation' => 'evaluation',
        'ifa_upload' => 'ifa_upload',
        'taxon_page' => 'taxon_page',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => 'type_op',
        'label' => 'Content type',
        'use_operator' => 0,
        'identifier' => 'type',
        'optional' => 0,
        'single' => 1,
        'remember' => 0,
        'reduce' => 1,
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'perm',
    'perm' => 'access content statistics',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('header', '<h2 class="title">Statistics</h2>');
  $handler->override_option('header_format', '2');
  $handler->override_option('header_empty', 1);
  $handler->override_option('items_per_page', 0);
  $handler->override_option('style_plugin', 'table');
  $handler = $view->new_display('block', 'Block (all content)', 'block_1');
  $handler->override_option('block_description', 'EduLifedesks Statistics content type totals');
  $handler->override_option('block_caching', -1);
  $handler = $view->new_display('block', 'Block (published taxon pages)', 'block_2');
  $handler->override_option('fields', array(
    'state' => array(
      'label' => 'State',
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
      'exclude' => 0,
      'id' => 'state',
      'table' => 'workflow_states',
      'field' => 'state',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'nid' => array(
      'label' => 'Count',
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
      'empty' => '0',
      'hide_empty' => 0,
      'empty_zero' => 1,
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'nid',
      'table' => 'node',
      'field' => 'nid',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'views_sql_groupedfields' => array(
      'label' => 'Group By Fields',
      'alter' => array(
        'alter_text' => FALSE,
        'text' => '',
        'make_link' => FALSE,
        'path' => '',
        'alt' => '',
        'link_class' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'trim' => FALSE,
        'max_length' => '',
        'word_boundary' => TRUE,
        'ellipsis' => TRUE,
        'strip_tags' => FALSE,
        'html' => FALSE,
      ),
      'empty' => '0',
      'hide_empty' => 0,
      'empty_zero' => 1,
      'exclude' => '1',
      'id' => 'views_sql_groupedfields',
      'table' => 'views_groupby',
      'field' => 'views_sql_groupedfields',
      'relationship' => 'none',
      'views_groupby_fields_to_group' => array(
        'state' => 'state',
      ),
      'views_groupby_sql_function' => 'count',
      'views_groupby_fields_to_aggregate' => array(
        'nid' => 'nid',
      ),
      'views_groupby_field_sortby' => 'nid',
      'views_groupby_sortby_direction' => 'desc',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
  ));
  $handler->override_option('filters', array(
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'taxon_page' => 'taxon_page',
      ),
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
      'override' => array(
        'button' => 'Use default',
      ),
    ),
  ));
  $handler->override_option('header', '<h2 class="inner">Taxon pages</h2>');
  $handler->override_option('footer', '<p>View <a href="/admin/content/statistics/all">more statistics</p>');
  $handler->override_option('footer_format', '2');
  $handler->override_option('footer_empty', 1);
  $handler->override_option('block_description', 'EduLifedesks Statistics taxon page states');
  $handler->override_option('block_caching', -1);
  $handler = $view->new_display('page', 'Groups, content types and states', 'page_1');
  $handler->override_option('fields', array(
    'nid' => array(
      'label' => 'Count',
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
      'empty' => '0',
      'hide_empty' => 0,
      'empty_zero' => 1,
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'nid',
      'table' => 'node',
      'field' => 'nid',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'group_nid' => array(
      'label' => 'Groups',
      'alter' => array(
        'alter_text' => FALSE,
        'text' => '',
        'make_link' => FALSE,
        'path' => '',
        'alt' => '',
        'link_class' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'trim' => FALSE,
        'max_length' => '',
        'word_boundary' => TRUE,
        'ellipsis' => TRUE,
        'strip_tags' => FALSE,
        'html' => FALSE,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'type' => 'separator',
      'separator' => ', ',
      'exclude' => 0,
      'id' => 'group_nid',
      'table' => 'og_ancestry',
      'field' => 'group_nid',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'state' => array(
      'label' => 'Status',
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
      'exclude' => 0,
      'id' => 'state',
      'table' => 'workflow_states',
      'field' => 'state',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('filters', array(
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'assignment' => 'assignment',
        'evaluation' => 'evaluation',
        'ifa_upload' => 'ifa_upload',
        'taxon_page' => 'taxon_page',
      ),
      'group' => '0',
      'exposed' => TRUE,
      'expose' => array(
        'use_operator' => 0,
        'operator' => 'type_op',
        'identifier' => 'type',
        'label' => 'Content type',
        'optional' => 0,
        'single' => 1,
        'remember' => 0,
        'reduce' => 1,
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
  ));
  $handler->override_option('style_plugin', 'views_crosstab_table');
  $handler->override_option('style_options', array(
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'columns' => array(
      'nid' => 'nid',
      'group_nid' => 'group_nid',
      'state' => 'state',
    ),
    'info' => array(
      'nid' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'group_nid' => array(
        'separator' => '',
      ),
      'state' => array(
        'sortable' => 0,
        'separator' => '',
      ),
    ),
    'default' => '-1',
    'crosstab_rows' => 'group_nid',
    'crosstab_columns' => 'state',
    'crosstab_data' => 'nid',
    'crosstab_operation' => 'COUNT',
  ));
  $handler->override_option('path', 'admin/content/statistics/%');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => 'Content statistics',
    'description' => 'View reports on the number of nodes in each group post type and their workflow status',
    'weight' => '0',
    'name' => 'primary-links',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
  ));
  
  $views[$view->name] = $view;
  return $views;
}