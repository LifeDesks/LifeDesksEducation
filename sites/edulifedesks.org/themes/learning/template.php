<?php
// $Id$

/**
 * @file
 * Contains theme override functions and preprocess functions for the theme.
 *
 * ABOUT THE TEMPLATE.PHP FILE
 *
 *   The template.php file is one of the most useful files when creating or
 *   modifying Drupal themes. You can add new regions for block content, modify
 *   or override Drupal's theme functions, intercept or make additional
 *   variables available to your theme, and create custom PHP logic. For more
 *   information, please visit the Theme Developer's Guide on Drupal.org:
 *   http://drupal.org/theme-guide
 *
 * OVERRIDING THEME FUNCTIONS
 *
 *   The Drupal theme system uses special theme functions to generate HTML
 *   output automatically. Often we wish to customize this HTML output. To do
 *   this, we have to override the theme function. You have to first find the
 *   theme function that generates the output, and then "catch" it and modify it
 *   here. The easiest way to do it is to copy the original function in its
 *   entirety and paste it here, changing the prefix from theme_ to learning_.
 *   For example:
 *
 *     original: theme_breadcrumb()
 *     theme override: learning_breadcrumb()
 *
 *   where learning is the name of your sub-theme. For example, the
 *   zen_classic theme would define a zen_classic_breadcrumb() function.
 *
 *   If you would like to override any of the theme functions used in Zen core,
 *   you should first look at how Zen core implements those functions:
 *     theme_breadcrumbs()      in zen/template.php
 *     theme_menu_item_link()   in zen/template.php
 *     theme_menu_local_tasks() in zen/template.php
 *
 *   For more information, please visit the Theme Developer's Guide on
 *   Drupal.org: http://drupal.org/node/173880
 *
 * CREATE OR MODIFY VARIABLES FOR YOUR THEME
 *
 *   Each tpl.php template file has several variables which hold various pieces
 *   of content. You can modify those variables (or add new ones) before they
 *   are used in the template files by using preprocess functions.
 *
 *   This makes THEME_preprocess_HOOK() functions the most powerful functions
 *   available to themers.
 *
 *   It works by having one preprocess function for each template file or its
 *   derivatives (called template suggestions). For example:
 *     THEME_preprocess_page    alters the variables for page.tpl.php
 *     THEME_preprocess_node    alters the variables for node.tpl.php or
 *                              for node-forum.tpl.php
 *     THEME_preprocess_comment alters the variables for comment.tpl.php
 *     THEME_preprocess_block   alters the variables for block.tpl.php
 *
 *   For more information on preprocess functions and template suggestions,
 *   please visit the Theme Developer's Guide on Drupal.org:
 *   http://drupal.org/node/223440
 *   and http://drupal.org/node/190815#template-suggestions
 */


/*
 * Add any conditional stylesheets you will need for this sub-theme.
 *
 * To add stylesheets that ALWAYS need to be included, you should add them to
 * your .info file instead. Only use this section if you are including
 * stylesheets based on certain conditions.
 */
/* -- Delete this line if you want to use and modify this code
// Example: optionally add a fixed width CSS file.
if (theme_get_setting('learning_fixed')) {
  drupal_add_css(path_to_theme() . '/layout-fixed.css', 'theme', 'all');
}
// */


/**
 * Implementation of HOOK_theme().
 */
function learning_theme(&$existing, $type, $theme, $path) {
  
  $hooks = zen_theme($existing, $type, $theme, $path);
  // Add your theme hooks like this:
  /*
  $hooks['hook_name_here'] = array( // Details go here );
  */
  $hooks['blocks'] = array(
    'arguments' => array('region' => NULL, 'show_blocks' => NULL),
  );
  $hooks['class_node_form'] = array(
    'arguments' => array('form' => array()),
    'template' => 'class-node-form',
    'path' => drupal_get_path('theme', 'learning'),
  );
  $hooks['user_login_block'] = array(
    'arguments' => array('form' => array()),
    'template' => 'user-login-block',
    'path' => drupal_get_path('theme', 'learning'),
  );
  return $hooks;
}
/**
 * Override or insert variables into all templates.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered (name of the .tpl.php file.)
 */
function learning_preprocess(&$vars, $hook) {
  //$vars['sample_variable'] = t('Lorem ipsum.');
  //switch to use logo.gif as default logo rather than logo.png
  if(theme_get_setting('default_logo', $refresh = TRUE)) {
    $logo = theme_get_setting('logo');
    $logo = str_replace('.png', '.gif', $logo);
    $vars['logo'] = $logo;
  }
}
/**
 * Override or insert variables into the class_node_form template.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("page" in this case.)
 */
function learning_preprocess_class_node_form(&$vars, $hook) {
  // dsm($vars);
  // dsm($hook);
  // $vars['sample_variable'] = t('Lorem ipsum.');
  $form = $vars['form'];
  $optional_fields = array();
  $important_fields = array();
  $closure_fields = array();

  // Collapse fieldsets for fields that can't be modified through cck
  $collapse = array('themes','path', 'options');
  foreach ($collapse as $fieldset_name) {
    $vars['form'][$fieldset_name]['#collapsed'] = true;
  }
  
  // Get fields and cateogrize them for grouping in theme.
  foreach ($form as $name => $field) {
    if ($name == 'body_field' || $name == 'taxonomy') {
      // Add body and taxonomy to important -these don't have #required values in first level of array.
      $important_fields[$name] = $field;
      
    } elseif ($name == 'group_class_image') {
      // Add other important fields regardless of required or not. Important fields get rendered first.
      $important_fields[$name] = $field;
       
    } elseif ($name == 'themes') {
      // Unless important, put fields that are too big for side by side layout into their own section that will clear rest of fields.
      $closure_fields[$name] = $field;
      
    } elseif (is_array($field) && array_key_exists('#required', $field) && ($field['#type'] != 'value' && $field['#type'] != 'hidden' && $field['#type'] != 'token')) {
      // Add form items to important if they're required, unless radio.
      if ($field['#required'] === TRUE && $field['#type'] != 'radios') {
        // Radios will always be required, but will always have one option checked by default anyway.
        // Once user has chosen a radio option they won't always need to change it on future edits, so not important field.
        $important_fields[$name] = $field;
      } elseif ($field['#required'] === FALSE || $field['#type'] == 'radios') {
        $optional_fields[$name] = $field;
      }
    }
  }
  
  // Put optional og form fields into new array ready for grouping into fieldset, if not already a fieldset
  $og_optional_fields = array();
  foreach ($optional_fields as $name => $field) {
    if ($field['#type'] != 'fieldset' && preg_match('/^og_/i', $name)) {
      $og_optional_fields[$name] = $field;
    }
  }
  
  // Create new fieldset: not collapsed by default
  if (count($og_optional_fields) > 0) {
    $vars['form']['class_og_settings'] = array(
      '#type' => 'fieldset',
      '#title' => t('Group settings'),
      '#description' => t("Set your group's privacy level and membership options. In private groups, only members may view your group's content. Please note, regardless of your group's privacy setting, individual pages will only become viewable to all members (and non-members, if your group is public) once the page is 'published'."),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
      '#attributes' => array('class' => 'fieldset-class_og_settings'),
    );
    
    // Add fields to fieldset and get weight of fieldset's lightest field
    $lightest_weight = 1000;
    foreach ($og_optional_fields as $name => $field) {
      // check field weight
      if($field['#weight'] < $lightest_weight) $lightest_weight = $field['#weight'];
      
      // add fields to fieldset
      $vars['form']['class_og_settings'][$name] = $field;
      unset($vars['form'][$name]);
      unset($optional_fields[$name]);
    }
    
    // Add weight to fieldset
    $vars['form']['class_og_settings']['#weight'] = $lightest_weight;
    
    // Add fieldset to optional_fields
    $optional_fields['class_og_settings'] = $vars['form']['class_og_settings'];
  }
  
  // Sort array based on weight
  uasort($optional_fields, '_sort_by_weight');
  
  // Add variables to $vars to send to theme
  $vars['important_fields'] = array();
  foreach ($important_fields as $name => $field) {
    $vars['important_fields'][] = $name;
  }
  $vars['optional_fields'] = array();
  foreach ($optional_fields as $name => $field) {
    $vars['optional_fields'][] = $name;
  }
}
// */

/**
 * Helper function for sorting multi-dimensional arrays
 * Used by preprocess_class_node_form
 */
function _sort_by_weight($a, $b) {
    if ($a['#weight'] == $b['#weight']) {
        return 0;
    }
    return ($a < $b) ? -1 : 1;
}

/**
 * Override or insert variables into the page templates.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("page" in this case.)
 */

function learning_preprocess_page(&$vars, $hook) {
  global $user;
  
  // Add Log in link to secondary-links menu if user not logged in
  if ($user->uid == 0) {
    $log_in_link = array(
      'title' => 'Log in',
      'href' => 'user',
      'attributes' => array(
        'title' => t('Go to the log in form to sign in.'),
        'class' => 'log-on',
      ),
    );
    $vars['secondary_links'] = array('log-on' => $log_in_link) + $vars['secondary_links'];
    $my_groups_disabled = array(
      'title' => 'My groups',
      'attributes' => array(
        'title' => t('Sign in or join LifeDesks to access your groups.'),
        'class' => 'my-groups'
      ),
    );
    $vars['primary_links'] = array('my-groups' => $my_groups_disabled) + $vars['primary_links'];
    
  }
  // Change title of og/users/%node/roles page
  if (preg_match('@^Member roles for .+$@i', $vars['title'])) {
    $vars['title'] = 'Configure member roles';
  }
  // Remove header if class group overview or broadcast, and tabs on overview page
  if (in_array('node-type-class', $vars['body_classes_array'])) {
    unset($vars['tabs']);
    $unset_title = TRUE;
    foreach ($vars['body_classes_array'] as $class) {
      if (preg_match('#^page-node-[0-9]+-(broadcast|configure)#i', $class)) {
        $unset_title = FALSE;
        break; 
      }
    }
    if ($unset_title === TRUE) unset($vars['title']);
  }
}
// */

/**
 * Override or insert variables into the node templates.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("node" in this case.)
 */
function learning_preprocess_node(&$vars, $hook) {
  global $user;
  if ($vars['type'] == 'ifa_upload' && $vars['teaser']) {
    unset($vars['title']);
    unset($vars['submitted']);
  }
  // Produce workflow state output for unpublished nodes
  if (isset($vars['_workflow']) && $user->uid > 0) {
    $workflow_state = _learning_get_workflow_state($vars['type'], $vars['_workflow']);
    if (isset($workflow_state)) {
      // only show workflow illustration for taxon pages (return text for image nodes)
      if ($vars['type'] == 'ifa_upload') $vars['_workflow_state']['text'] = $workflow_state['text'];
      if ($vars['type'] == 'taxon_page') $vars['_workflow_state']['illustration'] = $workflow_state['illustration'];
      $vars['classes'] .= ' ' .$workflow_state['class'];
    }
  }
}
// */

/**
 * Override or insert variables into the comment templates.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("comment" in this case.)
 */
/* -- Delete this line if you want to use this function
function learning_preprocess_comment(&$vars, $hook) {
  $vars['sample_variable'] = t('Lorem ipsum.');
}
// */

/**
 * Override or insert variables into the block templates.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("block" in this case.)
 */
function learning_preprocess_block(&$vars, $hook) {
  if ($vars['block']->module == 'menu_block') {
    switch ($vars['block']->delta) {
      case 1: // Primary links level 2 (subprimary)
        $vars['block']->subject = _learning_build_page_title();
    }
  }
}
// */
/**
 * Helper function to build page title from current path
 */
function _learning_build_page_title() {
  switch (arg(0)) {
    case 'groups':
      if (arg(2)) {
        $title = ucfirst(str_replace('-', ' ', arg(2)));
      } else {
        $title = ucfirst(arg(0));
      }
      $title .= ' gallery';
      break;
  }
  return isset($title) ? t($title) : '';
}
/**
 * Fix for conflict between context and Zen.
 * See http://drupal.org/node/633778
 */
function learning_blocks($region, $show_blocks = NULL) {
  if (module_exists("context")) {
    /**
     * Since Drupal 6 doesn't pass $show_blocks to theme_blocks, we manually call
     * theme('blocks', NULL, $show_blocks) so that this function can remember the
     * value on later calls.
     */
    static $render_sidebars = TRUE;
    if (!is_null($show_blocks)) {
      $render_sidebars = $show_blocks;
    }
   
    // Bail if this region is disabled.
    $disabled_regions = context_active_values('theme_regiontoggle');
    if (!empty($disabled_regions) && in_array($region, $disabled_regions)) {
      return '';
    }
  
    /**
     * If zen_blocks was called with a NULL region, its likely we were just
     * setting the $render_sidebars static variable.
     */
    if ($region) {
      $output = '';
  
      /**
       * If $renders_sidebars is FALSE, don't render any region whose name begins
       * with "sidebar_".
       */
      if (($render_sidebars || (strpos($region, 'sidebar_') !== 0)) && ($list = context_block_list($region))) {
        foreach ($list as $key => $block) {
          // $key == module_delta
          $output .= theme('block', $block);
        }
      }
  
      // Add any content assigned to this region through drupal_set_content() calls.
      $output .= drupal_get_content($region);
  
      $elements['#children'] = $output;
      $elements['#region'] = $region;
  
      return $output ? theme('region', $elements) : '';
    }
   
  } else {
    return zen_blocks($region, $show_blocks);
  }
}
/**
 * Implements theme_menu_item_link()
 * Copied from zen_menu_item_link() and then modified
 */
function learning_menu_item_link($link) {
  if (empty($link['localized_options'])) {
    $link['localized_options'] = array();
  }

  // If an item is a LOCAL TASK, render it as a tab
  if ($link['type'] & MENU_IS_LOCAL_TASK) {
    // If menu item is node edit link and node is group node show title as 'Edit group'
    $group_node = og_set_group_context();
    if ($link['path'] == 'node/%/edit' && arg(1) == $group_node->nid) {
      $link['title'] .= ' group';
    } else if (preg_match('@^edit current$@i', $link['title'])) {
      $link['title'] = 'Edit'; 
    } else if (preg_match('@^view current$@i', $link['title'])) {
      $link['title'] = 'View'; 
    } else if ($link['path'] == 'node/%/revisions') { // hide revisions tab, access still required
      return NULL;
    } else if($link['path'] == 'og/users/%/roles') {
      $link['title'] = 'Manage members';
    }
    $link['title'] = '<span class="tab">[ ' . check_plain($link['title']) . ' ]</span>';
    $link['localized_options']['html'] = TRUE;
  }
  
  return l($link['title'], $link['href'], $link['localized_options']);
}

/**
 * Override of theme_filefield_widget_file
 * See filefield_widget.inc line 474 
 * / comment out this for now cross browser issues.
function learning_filefield_widget_file($element) {
  $output = '';

  $output .= '<div class="filefield-upload clear-block">';

  if (isset($element['#field_prefix'])) {
    $output .= $element['#field_prefix'];
  }

  _form_set_class($element, array('form-file'));
  $output .= '<div class="pseudo-filefield">';
  $output .= '<input class="pseudo-file-text" type="text" size="22" />';
  $output .= '<input class="pseudo-file-button" type="button" value="Browse..." />';
  $output .= '</div>';
  $output .= '<input type="file" name="'. $element['#name'] .'"'. ($element['#attributes'] ? ' '. drupal_attributes($element['#attributes']) : '') .' id="'. $element['#id'] .'" size="'. $element['#size'] ."\" />\n";

  if (isset($element['#field_suffix'])) {
    $output .= $element['#field_suffix'];
  }

  $output .= '</div>';

  return theme('form_element', $element, $output);
}*/
/**
 * Helper function to return workflow state for us in node template 
 * @param $type node content type
 * @param $node_sid node state id
 * @return array
 */
function _learning_get_workflow_state($type, $node_sid) {
  $wid = workflow_get_workflow_for_type($type);
  $states = workflow_get_states($wid);
  
  // To treat 'Archived' states differently we need to know which ones they are
  // This makes this dependent on either knowing workflow state id or matching state name (would name matching break with translations?)
  // Similarly want to ignore creation states, name is '(creation)' but what about multilingual? to be safe recording sids
  switch ($wid) {
    case 1:
      $archived_sid = 7;
      $creation_sid = 1;
      break;
    case 2:
      $archived_sid = 11;
      $creation_sid = 8;
      break;
    case 3:
      $archived_sid = 17;
      $creation_sid = 12;
      break;
    default:
      $archived_sid = 0;
      $creation_sid = 0;
      break;   
  }
  if (array_key_exists($archived_sid, $states)) {
    if ($node_sid == $archived_sid) {
       return array('text' => t($states[$archived_sid]), 'class' => 'archived');
    } else {
      unset($states[$archived_sid]);
    }
  }
  if (array_key_exists($creation_sid, $states)) unset($states[$creation_sid]);
  
  // With archived and creation states removed, build data for workflow state output
  $output = array();
  $i = 0;
  foreach ($states as $sid => $state) {
    // Build class names and accessible labels for each state
    $current_state_label = '';
    $i++;
    $find = array('@ @i', '@![a-z- ]@i');
    $replace = array('-', '');
    $class = strtolower(preg_replace($find, $replace, $state)) .' state';
    if ($node_sid == $sid) {
      $output['text'] = t($state);
      $output['class'] = $class;
      $class .= ' current';
      $current_state_label = '<br /><span class="state-label">' .t('(current state)') .'</span>';
    }
    // Establish % width of each state container, based on the number of states - 1 (end states are half width of middle states)
    $width = 100 / (count($states) - 0.5);
    if ($i == 1) {
      $class .= ' first';
      $width = $width * 0.5;
    } 
    if ($i == count($states)) {
      $class .= ' last';
      //$width = $width * 0.5;
    }
    $output['illustration'] .= '<span class="' .trim($class) .'" style="width: ' .$width .'%;">' .t($state) .$current_state_label .'</span>';
  }
  return $output;
}
/**
 * Theme override function for 'default' nodereference field formatter.
 * @see nodereference.module
 */
function learning_nodereference_formatter_default($element) {
  $output = '';
  if (!empty($element['#item']['safe']['nid'])) {
    $output = l($element['#item']['safe']['title'], 'node/'. $element['#item']['safe']['nid']);
  }  
  return $output;
}

/**
 * Theme override function for 'plain' nodereference field formatter.
 * @see nodereference.module
 */
function learning_nodereference_formatter_plain($element) {
  $output = '';
  if (!empty($element['#item']['safe']['nid'])) {
    $output = check_plain($element['#item']['safe']['title']);
  }
  return $output;
}


/**
* Truncate the string if it is beyond a certain $length and append with an ellipses or custom text
* $length is the number of characters allowed before truncating
* $append is appended to the truncated string
*/
function _learning_truncate($string = '', $length = 30, $append = '...') {
  return strlen($string) > $length ? trim(substr($string, 0, $length)) . $append : $string;
}