<?php

/**
 * Helper to implementation of hook_content_default_fields().
 */
function _taxon_accounts_content_default_fields() {
  $fields = array();

  // Exported field: field_scientific_name
  $fields[] = array(
    'field_name' => 'field_scientific_name',
    'type_name' => 'taxon_account',
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
    'type' => 'text',
    'required' => '1',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '1',
    'max_length' => '500',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => '1',
      'size' => 60,
      'default_value' => array(
        '0' => array(
          'value' => '',
          'format' => '1',
          '_error_element' => 'default_value_widget][field_scientific_name][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Scientific name',
      'weight' => '-4',
      'description' => 'Enter a scientific name for the organism.',
      'type' => 'text_textarea',
      'module' => 'text',
    ),
  );

  // Translatables
  array(
    t('Scientific name'),
  );

  return $fields;
}
