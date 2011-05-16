<?php
// $Id$

/**
 * @file
 * Provides user interfaces for custom elements in edulifedesks.
 */

/**
 * Menu callback.
 * Display evaluation teaser of a node, with links to add / edit if applicable.
 * Note: access to evaluation node is determined primarily by coherent_access module.
 */
function _evaluation_tab_page($node = NULL) {
  
  drupal_set_title($title = t('Evaluations of %nodetitle', array('%nodetitle' => $node->title)));
  
  // get current group id if exists
  $current_group_id = 0;
  if (module_exists(og)) {
    $group_node = og_get_group_context();
    $group_nid = $group_node->nid;
    if ($group_nid != NULL) {
      $current_group_id = (int)$group_nid;
    }
  }
  
  $view_name = 'edulifedesks_linked_evaluations';
  $display_id = 'default';
  $args = $node->nid;
  
  $output = views_embed_view($view_name, $display_id, $args);
  if ($output == NULL) {
    $output = t('There are no evaluations of %nodetitle.', array('%nodetitle' => $node->title)) .' ';
    if (user_access('create evaluation content')) {
      $output .= l(t('Add an evaluation.'), 'node/add/evaluation', array('query' => array('gids[]' => $current_group_id)));
    }
  }
  
  return trim($output);
}
 