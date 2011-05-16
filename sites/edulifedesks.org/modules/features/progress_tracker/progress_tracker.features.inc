<?php

/**
 * Implementation of hook_views_default_views().
 */
function progress_tracker_views_default_views() {
  module_load_include('inc', 'progress_tracker', 'progress_tracker.features.views');
  $args = func_get_args();
  return call_user_func_array('_progress_tracker_views_default_views', $args);
}
