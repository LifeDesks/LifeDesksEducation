<?php
// $Id$
/**
 * @file
 * Menu callbacks for Organic Groups Content Permissions administration settings.
 */
/**
 * Menu call back for og content permissions settings form.
 * Specify which content types group owners should be able to control.
 */
function og_content_permissions_settings($form_state) {
  $form = array();
  $group_post_types = og_get_types('group_post');
  if ($group_post_types) {
    if (!isset($form_state['storage']['configure_fields'])) {
      $options = array();
      foreach ($group_post_types as $type) {
        $options[$type] = str_replace('_', ' ', $type);
      }
      $form['group_configure_post_types'] = array(
        '#type' => 'fieldset',
        '#title' => t('Group post content types'),
        '#description' => t('Check box next to post type to allow group administrators to configure which fields to show in add and edit forms of that post type.'),
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
      );
      $form['group_configure_post_types']['og_content_permissions_post_types'] = array(
        '#type' => 'checkboxes',
        '#title' => t('Select content types group owners can control'),
        '#default_value' => variable_get('og_content_permissions_post_types', array()),
        '#options' => $options,
      );
      $form['next'] = array(
        '#type' => 'submit',
        '#value' => 'Save and continue',
      );
    }
    else {
      $content_types = $form_state['values']['og_content_permissions_post_types'];
      foreach ($content_types as $content_type => $enabled) {
        if ($enabled !== 0) {
          $type = content_types($content_type);
          $fields = $type['fields'];
          $form['group_' .$content_type] = array(
            '#type' => 'fieldset',
            '#title' => t('!type fields', array('!type' => $type['name'])),
            '#description' => t('Check box next to field to allow group administrators the ability to configure field in their !type settings.', array('!type' => strtolower($type['name']))),
            '#collapsible' => TRUE,
            '#collapsed' => FALSE,
          );
          $default_values = variable_get('og_content_permissions_configurable_fields', array());
          $options = array();
          foreach ($fields as $field_name => $field) {
            $options[$field['field_name']] = $field['widget']['label'];
          }
          $form['group_' .$content_type][$content_type .'_configurable_fields'] = array(
            '#type' => 'checkboxes',
            '#options' => $options,
            '#default_value' => $default_values[$content_type],
          );
        }
      }
      $form['back'] = array(
        '#type' => 'submit',
        '#value' => 'Back',
      );
      $form['submit'] = array(
        '#type' => 'submit',
        '#value' => 'Submit',
      );
    }
  }
  
  return $form;
}
/**
 * Validate og_content_permissions_settings form
 */
function og_content_permissions_settings_validate($form, &$form_state) {
  if ($form_state['clicked_button']['#id'] == 'edit-next') {
    $content_types = $form_state['values']['og_content_permissions_post_types'];
    foreach ($content_types as $content_type => $enabled) {
      // Valid if a post type has been enabled
      if ($enabled !== 0) return; 
    }
    // Invalid if no post type selected
    variable_set('og_content_permissions_post_types', $content_types);
    form_set_error('og_content_permissions_post_types', 'Your settings have been saved. If you wish to configure fields, please select a post type to continue.');
  }
}
/**
 * Default submit handler for og_content_permissions_settings form
 */
function og_content_permissions_settings_submit($form, &$form_state) {
  $form_state['storage']['post_type_values'] = $form_state['values'];
  if ($form_state['clicked_button']['#id'] == 'edit-next') {
    // Process first page - select post type
    variable_set('og_content_permissions_post_types', $form_state['values']['og_content_permissions_post_types']);
    $form_state['storage']['configure_fields'] = TRUE;
  }
  elseif ($form_state['clicked_button']['#id'] == 'edit-back') {
    unset($form_state['storage']);
  }
  else {
    // Process second page - configure fields
    $configurable_fields = variable_get('og_content_permissions_configurable_fields', array());
    foreach ($form_state['values'] as $element => $values) {
      if (preg_match('/_configurable_fields$/', $element)) {
        $element = str_replace('_configurable_fields', '', $element);
        $configurable_fields[$element] = $values;
      }
    }
    variable_set('og_content_permissions_configurable_fields', $configurable_fields);
    // TODO: If not allow users to change fields then assume those fields should be enabled and therefore need to change all content settings across group
    $field_permissions = variable_get('og_content_permissions_per_group',array());
    foreach ($field_permissions as $group_nid => $fields) {
      
    }
    unset($form_state['storage']);
    drupal_set_message('Your settings have been saved.');
  }
}