<?php

/**
 * Implementation of hook_content_default_fields().
 */
function assignments_content_default_fields() {
  module_load_include('inc', 'assignments', 'assignments.defaults');
  $args = func_get_args();
  return call_user_func_array('_assignments_content_default_fields', $args);
}

/**
 * Implementation of hook_node_info().
 */
function assignments_node_info() {
  module_load_include('inc', 'assignments', 'assignments.features.node');
  $args = func_get_args();
  return call_user_func_array('_assignments_node_info', $args);
}

/**
 * Implementation of hook_views_default_views().
 */
function assignments_views_default_views() {
  module_load_include('inc', 'assignments', 'assignments.features.views');
  $args = func_get_args();
  return call_user_func_array('_assignments_views_default_views', $args);
}
