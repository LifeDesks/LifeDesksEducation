<?php

/**
 * Implementation of hook_content_default_fields().
 */
function multimedia_blogging_content_default_fields() {
  module_load_include('inc', 'multimedia_blogging', 'multimedia_blogging.defaults');
  $args = func_get_args();
  return call_user_func_array('_multimedia_blogging_content_default_fields', $args);
}

/**
 * Implementation of hook_imagecache_default_presets().
 */
function multimedia_blogging_imagecache_default_presets() {
  module_load_include('inc', 'multimedia_blogging', 'multimedia_blogging.defaults');
  $args = func_get_args();
  return call_user_func_array('_multimedia_blogging_imagecache_default_presets', $args);
}

/**
 * Implementation of hook_node_info().
 */
function multimedia_blogging_node_info() {
  module_load_include('inc', 'multimedia_blogging', 'multimedia_blogging.features.node');
  $args = func_get_args();
  return call_user_func_array('_multimedia_blogging_node_info', $args);
}

/**
 * Implementation of hook_views_default_views().
 */
function multimedia_blogging_views_default_views() {
  module_load_include('inc', 'multimedia_blogging', 'multimedia_blogging.features.views');
  $args = func_get_args();
  return call_user_func_array('_multimedia_blogging_views_default_views', $args);
}
