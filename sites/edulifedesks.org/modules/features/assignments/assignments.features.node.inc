<?php

/**
 * Helper to implementation of hook_node_info().
 */
function _assignments_node_info() {
  $items = array(
    'assignment' => array(
      'name' => t('Assignment'),
      'module' => 'features',
      'description' => t('Add task details and due dates of assignments for students.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Description'),
      'min_word_count' => '0',
      'help' => t('Create an assignment. Remember to set a due date.'),
    ),
    'review' => array(
      'name' => t('Review'),
      'module' => 'features',
      'description' => t('Write a confidential evaluation of a piece of content.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Review'),
      'min_word_count' => '0',
      'help' => t('Write a review of a piece of content.'),
    ),
  );
  return $items;
}
