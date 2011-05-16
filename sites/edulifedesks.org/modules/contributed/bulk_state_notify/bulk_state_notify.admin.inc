<?php
// $Id: bulk_state_notify.admin.inc,v 1.1 2009/09/09 19:36:44 jcfiala Exp $

/**
 * @file
 * Contains admin setting items.
 */

/**
 * This form allows the admin to set up the frequency of the notifications, along with the body and subject
 * of the notification.
 */
function bulk_state_notify_settings() {
  $form = array();

  $form['bulk_state_notify_freqency'] = array(
    '#type' => 'select',
    '#title' => t('Frequency of Reminders'),
    '#multiple' => FALSE,
    '#required' => TRUE,
    '#options' => array(
      '48' => t('Once every two days'),
      '24' => t('Once a day'),
      '12' => t('Twice a day'),
      '8' => t('Three times a day'),
    ),
    '#default_value' => variable_get('bulk_state_notify_frequency', 24),
  );

  $form['bulk_state_notify'] = array(
    '#type' => 'fieldset',
    '#title' => t('Notifications'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['bulk_state_notify']['bulk_state_notify_markup'] = array(
    '#type' => 'markup',
    '#value' => "In the following three items, there are three variables that can be set (currently) for each item:
    <dl><dt>@project</dt><dd>The title of the organic group/project.</dd>
    <dt>!link</dt><dd>The link to the organic group/project.</dd>
    <dt>!list</dt><dd>The list of tickets as links.</dd></dl>",
  );

  $form['bulk_state_notify']['bulk_state_notify_subject_single'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject field for notification emails when one ticket is found'),
    '#required' => TRUE,
    '#default_value' => variable_get('bulk_state_notify_subject_single', 'notification for @project: 1 ticket'),
  );

  $form['bulk_state_notify']['bulk_state_notify_subject_plural'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject field for notification emails with more than one ticket'),
    '#required' => TRUE,
    '#default_value' => variable_get('bulk_state_notify_subject_plural', 'notification for @project: @count tickets'),
  );

  $message_base = <<<MESSAGE_BASE
<p>These are the tickets on the site which are waiting for your attention.  Although they may not need
your immediate feedback, we've found that it's a good idea to keep an eye on these items, as we don't want to lose track of
anything that's unresolved.  In addition to this list, you can visit the site !link</p>

<p>For the project @title, the following items are awaiting your feedback or response: !list</p>
MESSAGE_BASE;

  $form['bulk_state_notify']['bulk_state_notify_body'] = array(
    '#type' => 'textarea',
    '#title' => t('Body field for notification emails.'),
    '#required' => TRUE,
    '#default_value' => variable_get('bulk_state_notify_body', $message_base),
  );

  $form['bulk_state_notify_send'] = array(
    '#type' => 'submit',
    '#value' => 'Send Notifications Now',
    '#submit' => array('bulk_state_notify_settings_send_submit'),
  );

  return system_settings_form($form);
}

/**
 * This submit handler triggers a notification, but saves no other data - best used for testing.
 */
function bulk_state_notify_settings_send_submit($form, &$form_state) {
  $number_sent = _bulk_state_notify_send_emails();
  drupal_set_message(t("Sent out @number emails.", array('@number' => $number_sent)));
}

/**
 * This page displays the list of groups that have been established for bulk notify.
 */
function bulk_state_notify_display_groups() {

  $header = array(
    t('Name'),
    t('Project'),
    t('Group Size'),
    t('Status'),
    array('data' => t('Actions'), 'colspan' => 3),
  );
  if (module_exists('og')) {
    $group_query = "SELECT cng.gid, name, cng.status, og_nid, IFNULL(n.title, '') as group_name, COUNT(ug.uid) AS size FROM {bulk_state_notify_groups} cng LEFT JOIN {bulk_state_notify_user_group} ug ON (cng.gid = ug.gid) LEFT JOIN {node} n ON (cng.og_nid = n.nid) GROUP BY cng.gid, name, cng.status ORDER BY cng.gid";
  }
  else {
    $group_query = "SELECT cng.gid, name, cng.status, 0 as og_nid, '' AS group_name, COUNT(ug.uid) AS size FROM {bulk_state_notify_groups} cng LEFT JOIN {bulk_state_notify_user_group} ug ON (cng.gid = ug.gid) GROUP BY cng.gid, name, cng.status ORDER BY cng.gid";
  }
  $result = db_query($group_query);

  $rows = array();
  while ($group = db_fetch_object($result)) {
    //dpm($group);
    $row = array(l($group->name, 'admin/settings/bulk_state_notify/group/'. $group->gid),
                 $group->og_nid == 0 ? t('All Groups') : check_plain($group->group_name),
                 $group->size,
                 $group->status ? t('Active') : t('Disabled'),
                 l(t('Edit'), 'admin/settings/bulk_state_notify/group/'. $group->gid .'/edit'),
                 l(t('Clone'), 'admin/settings/bulk_state_notify/group/'. $group->gid .'/clone'),
                 l(t('Delete'), 'admin/settings/bulk_state_notify/group/'. $group->gid .'/delete'));
    $rows[] = $row;
  }

  return theme('table', $header, $rows);
}

/**
 * Form API function to allow for creating or updating a group.
 */
function bulk_state_notify_group_add(&$form_state, $group = NULL) {
  $form = array();

  if ($group == NULL) {
    $group = new stdClass();
    $group->name = '';
    $group->og_nid = '';
    $group->status = 1;
  }

  $form['group'] = array(
    '#type' => 'value',
    '#value' => $group,
  );

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Group Name'),
    '#maxlength' => 128,
    '#required' => TRUE,
    '#default_value' => $group->name,
  );

  $options = array(
    '' => t('Pick One'),
    '0' => t('All Groups'),
  );
  if (module_exists('og')) {
    $options = $options + og_all_groups_options();

    $form['og_nid'] = array(
      '#type' => 'select',
      '#title' => t('Organic Group'),
      '#required' => TRUE,
      '#options' => $options,
      '#default_value' => $group->og_nid,
    );
  }
  else {
    $form['og_nid'] = array(
      '#type' => 'hidden',
      '#value' => 0,
    );
  }

  $form['status'] = array(
    '#type' => 'checkbox',
    '#title' => t('Active'),
    '#default_value' => $group->status,
  );

  if ($group->gid) {
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Update'),
    );
  }
  elseif (empty($group->clone_gid)) {
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Create'),
    );
  }
  else {
    // We're cloning an existing item, so we want to run an extra submit function.
    $form['#submit'] = array('bulk_state_notify_group_add_submit', 'bulk_state_notify_group_clone_submit');
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Create'),
    );
  }

  return $form;
}

/**
 * Form API function to handle the submit of the add/edit form.
 *
 * Given how simple our interface is, there's no need right now for validation.
 */
function bulk_state_notify_group_add_submit($form, &$form_state) {
  if ($form_state['values']['group']->gid) {
    db_query("UPDATE {bulk_state_notify_groups} SET name = '%s', og_nid = %d, status = %d WHERE gid = %d",
             $form_state['values']['name'], $form_state['values']['og_nid'], $form_state['values']['status'], $form_state['values']['group']->gid);
    drupal_set_message(t("Updated group %name.", array('%name' => $form_state['values']['name'])));
  }
  else {
    db_query("INSERT INTO {bulk_state_notify_groups} (name, og_nid, status) VALUES ('%s', %d, %d)",
             $form_state['values']['name'], $form_state['values']['og_nid'], $form_state['values']['status']);
    $form_state['values']['gid'] = db_last_insert_id('bulk_state_notify_groups', 'gid');
    drupal_set_message(t("Created new notification group %name.", array("%name" => $form_state['values']['name'])));
  }
  $form_state['redirect'] = 'admin/settings/bulk_state_notify/group';
}

/**
 * Page to display the current information about the viewed group.
 */
function bulk_state_notify_group_view($group) {
  return theme('bulk_state_notify_group', $group) . drupal_get_form('bulk_state_notify_group_add_user', $group);
}

/**
 * This form allows a user to be added to the current group.
 */
function bulk_state_notify_group_add_user($form_state, $group) {
  $form = array();

  $form['user'] = array(
    '#type' => 'textfield',
    '#title' => t('User to Add'),
    '#maxlength' => 60,
    '#autocomplete_path' => 'user/autocomplete',
    '#default_value' => '',
    '#weight' => -1,
    '#required' => TRUE,
  );

  $form['gid'] = array(
    '#type' => 'value',
    '#value' => $group->gid,
  );

  $form['name'] = array(
    '#type' => 'value',
    '#value' => $group->name,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add User'),
  );

  return $form;
}

/**
 * This validation function makes sure that the user being added is not already in the group, and that they exist.
 */
function bulk_state_notify_group_add_user_validate($form, &$form_state) {
  $uid = db_result(db_query("SELECT uid FROM {users} WHERE name = '%s'", $form_state['values']['user']));
  if ($uid) {
    if (db_result(db_query("SELECT COUNT(*) FROM {bulk_state_notify_user_group} WHERE uid = %d AND gid = %d", $uid, $form_state['values']['gid']))) {
      form_set_error('user', t('Cannot add %user to group %name because that person is already in that group.', array('%user' => $form_state['values']['user'], '%name' => $form_state['values']['name'])));
    }
    else {
      $form_state['values']['uid'] = $uid;
    }
  }
  else {
    form_set_error('user', t('The user %name does not exist.', array('%name' => $form_state['values']['user'])));
  }
}

/**
 * This submit function adds the validated user to the group.
 */
function bulk_state_notify_group_add_user_submit($form, &$form_state) {
  if ($form_state['values']['uid'] && db_query("INSERT INTO {bulk_state_notify_user_group} (uid, gid) VALUES (%d, %d)",
           $form_state['values']['uid'], $form_state['values']['gid'])) {
    drupal_set_message(t("Successfully added %user to the group %name.", array('%user' => $form_state['values']['user'], '%name' => $form_state['values']['name'])));
  }
  else {
    drupal_set_message(t("There was an error, and the user was not added to that group."));
  }
}

/**
 * Menu callback -- ask for confirmation of group deletion
 */
function bulk_state_notify_group_delete(&$form_state, $group) {
  $form['gid'] = array(
    '#type' => 'value',
    '#value' => $group->gid,
  );
  $form['name'] = array(
    '#type' => 'value',
    '#value' => $group->name,
  );

  return confirm_form($form,
    t('Are you sure you want to delete %title?', array('%title' => $group->name)),
    isset($_GET['destination']) ? $_GET['destination'] : 'admin/settings/bulk_state_notify/group/'. $group->gid,
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Execute group deletion
 */
function bulk_state_notify_group_delete_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    db_query("DELETE FROM {bulk_state_notify_groups} WHERE gid = %d", $form_state['values']['gid']);
    drupal_set_message(t("Group %name has been deleted.", array('%name' => $form_state['values']['name'])));
  }

  $form_state['redirect'] = 'admin/settings/bulk_state_notify/group';
}

/**
 * Menu callback - this form confirms that a user should be removed from the group.
 */
function bulk_state_notify_group_remove_user(&$form_state, $group, $user) {
  $form['gid'] = array(
    '#type' => 'value',
    '#value' => $group->gid,
  );
  $form['name'] = array(
    '#type' => 'value',
    '#value' => $group->name,
  );
  $form['uid'] = array(
    '#type' => 'value',
    '#value' => $user->uid,
  );
  $form['user_name'] = array(
    '#type' => 'value',
    '#value' => $user->name,
  );

  return confirm_form($form,
    t('Are you sure you want to remove %user_name from %group_name?', array('%user_name' => $user->name, '%group_name' => $group->name)),
    isset($_GET['destination']) ? $_GET['destination'] : 'admin/settings/bulk_state_notify/group/'. $group->gid,
    t('This action cannot be undone.'),
    t('Remove'),
    t('Cancel')
  );
}

/**
 * Execute group deletion
 */
function bulk_state_notify_group_remove_user_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    db_query("DELETE FROM {bulk_state_notify_user_group} WHERE uid = %d AND gid = %d",
             $form_state['values']['uid'], $form_state['values']['gid']);
    drupal_set_message(t("%user_name has been removed from group %name.",
                         array('%user_name' => $form_state['values']['user_name'], '%name' => $form_state['values']['name'])));
  }

  $form_state['redirect'] = 'admin/settings/bulk_state_notify/group/'. $form_state['values']['gid'];
}

/**
 * Find and set up the various states each group is notified for.
 */
function bulk_state_notify_group_states($form_state, $group) {
  $form = array();
  drupal_set_title(t("Notification states for the group @name", array("@name" => $group->name)));

  $form['group'] = array(
    '#type' => 'value',
    '#value' => $group,
  );

  $casetracker_states = array();
  if (module_exists('casetracker')) {
    // Get casetracker states!
    $casetracker_states = _bulk_state_notify_get_casetracker_states();

    // Get current states for this group!
    $default_value = array();
    $result = db_query("SELECT state_id, gid FROM {bulk_state_notify_states} WHERE module = '%s' AND set_id = 1 AND gid = %d",
                       'casetracker', $group->gid);
    while ($case_row = db_fetch_array($result)) {
      $default_value[] = $case_row['state_id'];
    }

    $form['casetracker_states'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Case Tracker States this group should be notified of.'),
      '#options' => $casetracker_states,
      '#default_value' => $default_value,
    );
  }

  $workflows = array();
  $workflow_states = array();
  if (module_exists('workflow')) {
    $form['workflow'] = array(
      '#type' => 'fieldset',
      '#title' => t('Workflows'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    // Get workflow states!
    list($workflows, $workflow_states) = _bulk_state_notify_get_workflow_states();

    $form['workflow']['workflows'] = array(
      '#type' => 'value',
      '#value' => $workflows,
    );

    foreach ($workflows as $wid => $name) {
      $default_value = array();
      $workflow_results = db_query("SELECT state_id FROM {bulk_state_notify_states} WHERE module = '%s' AND set_id = %d AND gid = %d",
                                   'workflow', $wid, $group->gid);
      while ($workflow_row = db_fetch_array($workflow_results)) {
        $default_value[] = $workflow_row['state_id'];
      }
      $form['workflow']['workflow_'. $wid] = array(
        '#type' => 'checkboxes',
        '#title' => t('Workflow %workflow states this group should be notified of', array('%workflow' => $name)),
        '#options' => $workflow_states[$wid],
        '#default_value' => $default_value,
      );
    }
  }

  if (!module_exists('casetracker') && !module_exists('workflow')) {
    $form['message'] = array(
      '#value' => '<p>'. t('If neither Casetracker or Workflow is enabled, this module won\'t actually do anything.') .
      '</p><p>'. t('Please install either !casetracker or !workflow or both to use this module.',
                    array('!casetracker' => l(t('Casetracker'), 'http://drupal.org/project/casetracker'),
                          '!workflow' => l(t('Workflow'), 'http://drupal.org/project/workflow'))) .'</p>',
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  //dpm($form);

  return $form;
}

/**
 * Submit handler for updating the group states.
 */
function bulk_state_notify_group_states_submit($form, &$form_state) {
  //dpm($form_state['values']);
  $group = $form_state['values']['group']; // for ease of use.

  if (module_exists('casetracker')) {
    _bulk_state_notify_group_states_submit_casetracker($group, $form, $form_state);
  }
  if (module_exists('workflow')) {
    _bulk_state_notify_group_states_submit_workflow($group, $form, $form_state);
  }

  //$form_state['redirect'] = 'admin/settings/bulk_state_notify/group/'. $group->gid;
  drupal_set_message(t("The states for %name group have been updated.", array('%name' => $group->name)));
}

/**
 * Submit helper for the states submit - checks to see if a row exists, and then based on that and the need,
 * either writes a new row or deletes the existing one.
 */
function _bulk_state_notify_group_states_submit_helper($module, $gid, $index, $value, $set_id = 1) {
  $row_exists = db_result(db_query("SELECT cnid FROM {bulk_state_notify_states} WHERE module = '%s' AND set_id = %d AND gid = %d AND state_id = %d",
                          $module, $set_id, $gid, $index));
  if ($value && !$row_exists) {
    db_query("INSERT INTO {bulk_state_notify_states} (module, set_id, state_id, gid) VALUES ('%s', %d, %d, %d)",
             $module, $set_id, $value, $gid);
  }
  elseif ($value == 0 && $row_exists) {
    db_query("DELETE FROM {bulk_state_notify_states} WHERE cnid = %d",
             $row_exists);
  }
}

/**
 * Submit handler for the states submit that updates for casetracker states.
 */
function _bulk_state_notify_group_states_submit_casetracker($group, $form, &$form_state) {
  foreach ($form_state['values']['casetracker_states'] as $index => $value) {
    _bulk_state_notify_group_states_submit_helper('casetracker', $group->gid, $index, $value);
  }
}

/**
 * Submit handler for the states submit that updates for workflow states.
 */
function _bulk_state_notify_group_states_submit_workflow($group, $form, &$form_state) {
  $workflows = $form_state['values']['workflows'];

  foreach ($workflows as $wid => $name) {
    foreach ($form_state['values']['workflow_'. $wid] as $index => $value) {
      _bulk_state_notify_group_states_submit_helper('workflow', $group->gid, $index, $value, $wid);
    }
  }
}

/**
 * Function that clones an existing group and presents it to the user.
 */
function bulk_state_notify_group_clone($group) {
  // Take the group, and scrub out the gid.
  if ($group->gid) {
    $group->clone_gid = $group->gid;
    $group->gid = 0;
  }

  return drupal_get_form('bulk_state_notify_group_add', $group);
}

/**
 * This function is called when cloning an existing group.
 */
function bulk_state_notify_group_clone_submit($form, &$form_state) {
  //dpm($form_state);
  if ($form_state['values']['gid']) {
    $insert_query = "INSERT INTO {bulk_state_notify_states} (module, set_id, state_id, gid, status)
    SELECT module, set_id, state_id, %d, status FROM {bulk_state_notify_states} WHERE gid = %d";
    $result = db_query($insert_query, $form_state['values']['gid'], $form_state['values']['group']->clone_gid);
    if ($result) {
      drupal_set_message(t("Successfully cloned state information into %new_group", array("%new_group" => $form_state['values']['name'])));
    }
    else {
      drupal_set_message(t("There was a problem cloning the state information into this group, you will need to set states by hand."));
    }
    $form_state['redirect'] = 'admin/settings/bulk_state_notify/group/'. $form_state['values']['gid'];
  }
}