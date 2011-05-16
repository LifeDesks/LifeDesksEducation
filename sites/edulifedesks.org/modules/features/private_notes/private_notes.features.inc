<?php

/**
 * Implementation of hook_node_info().
 */
function private_notes_node_info() {
  module_load_include('inc', 'private_notes', 'private_notes.features.node');
  $args = func_get_args();
  return call_user_func_array('_private_notes_node_info', $args);
}
