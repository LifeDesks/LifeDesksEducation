<?php

/**
 * Helper to implementation of hook_content_default_fields().
 */
function _assignments_content_default_fields() {
  $fields = array();

  // Exported field: field_due_date
  $fields[] = array(
    'field_name' => 'field_due_date',
    'type_name' => 'assignment',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'datetime',
    'required' => '1',
    'multiple' => '0',
    'module' => 'date',
    'active' => '1',
    'granularity' => array(
      'year' => 'year',
      'month' => 'month',
      'day' => 'day',
      'hour' => 'hour',
      'minute' => 'minute',
    ),
    'timezone_db' => '',
    'tz_handling' => 'none',
    'todate' => '',
    'repeat' => 0,
    'repeat_collapsed' => '',
    'default_format' => 'long',
    'widget' => array(
      'default_value' => 'now',
      'default_value_code' => '',
      'default_value2' => 'same',
      'default_value_code2' => '',
      'input_format' => 'l, F j, Y - g:ia e',
      'input_format_custom' => '',
      'increment' => '1',
      'text_parts' => array(),
      'year_range' => '-0:+3',
      'label_position' => 'above',
      'label' => 'Due Date',
      'weight' => '-4',
      'description' => 'Enter the date and time the assignment is due.',
      'type' => 'date_popup',
      'module' => 'date',
    ),
  );

  // Exported field: field_reviewed_content
  $fields[] = array(
    'field_name' => 'field_reviewed_content',
    'type_name' => 'review',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereference',
    'required' => '1',
    'multiple' => '0',
    'module' => 'nodereference',
    'active' => '1',
    'referenceable_types' => array(
      'assignment' => 0,
      'audio' => 0,
      'blog_post' => 0,
      'bookmark' => 0,
      'class' => 0,
      'page' => 0,
      'image' => 0,
      'notes' => 0,
      'profile' => 0,
      'review' => 0,
      'story' => 0,
      'taxon_account' => 0,
      'video' => 0,
    ),
    'advanced_view' => 'taxon_accounts',
    'advanced_view_args' => '',
    'widget' => array(
      'autocomplete_match' => 'starts_with',
      'size' => '100',
      'default_value' => array(
        '0' => array(
          'nid' => NULL,
          '_error_element' => 'default_value_widget][field_reviewed_content][0][nid][nid',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Content under review',
      'weight' => '-4',
      'description' => 'Choose the content you are reviewing by entering the start of it\'s title.',
      'type' => 'nodereference_autocomplete',
      'module' => 'nodereference',
    ),
  );

  // Translatables
  array(
    t('Content under review'),
    t('Due Date'),
  );

  return $fields;
}
