<?php

/**
 * Helper to implementation of hook_node_info().
 */
function _private_notes_node_info() {
  $items = array(
    'notes' => array(
      'name' => t('Notes'),
      'module' => 'features',
      'description' => t('Add personal or shared notes.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}
