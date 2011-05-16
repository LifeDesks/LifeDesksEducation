<?php

/**
 * Implementation of hook_content_default_fields().
 */
function taxon_accounts_content_default_fields() {
  module_load_include('inc', 'taxon_accounts', 'taxon_accounts.defaults');
  $args = func_get_args();
  return call_user_func_array('_taxon_accounts_content_default_fields', $args);
}

/**
 * Implementation of hook_node_info().
 */
function taxon_accounts_node_info() {
  module_load_include('inc', 'taxon_accounts', 'taxon_accounts.features.node');
  $args = func_get_args();
  return call_user_func_array('_taxon_accounts_node_info', $args);
}

/**
 * Implementation of hook_views_default_views().
 */
function taxon_accounts_views_default_views() {
  module_load_include('inc', 'taxon_accounts', 'taxon_accounts.features.views');
  $args = func_get_args();
  return call_user_func_array('_taxon_accounts_views_default_views', $args);
}