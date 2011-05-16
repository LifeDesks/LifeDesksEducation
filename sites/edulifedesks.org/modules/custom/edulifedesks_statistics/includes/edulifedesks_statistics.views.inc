<?php
// $Id$
/**
 * @file
 * Provides views data and handler overrides information for edulifedesks_statistics
 */
/**
 * Implementation of hook_views_query_alter().
 */
function edulifedesks_statistics_views_query_alter(&$view, &$query) {
  if ($view->name == 'edulifedesks_statistics' && $view->current_display == 'page_1') { //
    $query->groupby[0] = 'group_nid';
    $query->add_field('og_ancestry', 'group_nid');
  }
}
/**
 * Implementation of hook_views_pre_execute().
 */
/*
function edulifedesks_statistics_views_pre_execute(&$view) {

}*/
/**
 * Implementation of hook_views_pre_render().
 */
function edulifedesks_statistics_views_pre_render(&$view) {
  $display = 'page_1';
  if ($view->name == 'edulifedesks_statistics' && $view->current_display == $display) {
    if ($view->args[0] == 'all') {
      $results = db_query("SELECT node.title, og_ancestry.nid AS nid, og.nid AS og_ancestry_group_nid FROM og LEFT JOIN og_ancestry ON og.nid = og_ancestry.group_nid LEFT JOIN node ON og.nid = node.nid GROUP BY og_ancestry_group_nid");
      while ($class = db_fetch_object($results)) {
        $class->og_ancestry_nid = $class->nid;
        $classes[$class->og_ancestry_group_nid] = $class;
        foreach ($view->result as $i => $result) {
          if ($result->og_ancestry_group_nid == $class->og_ancestry_group_nid) unset($classes[$class->og_ancestry_group_nid]); 
        }
      }
      foreach ($classes as $gid => $class) {
        if (!is_null($class->nid)) {
          $view->result[] = $class;
          unset($classes[$gid]);
        } 
      }
    }
    // If any classes remain then this means they have no nodes associated with them of any content type.
    // Add a list of these remaining classes to the footer of the view
    if (count($classes) > 0) {
      $items = array();
      foreach ($classes as $gid => $class) {
        $items[] = l($class->title, 'node/' .$gid);       
      }
      $footer_content = '<p>' . t('The following groups are not included in the results, they do not have any content of any kind:') .'</p>'
                      . theme('item_list', $items, '', 'ul', array('class' => 'groups-without-content'));
      // Check for an existing footer, and provided its not PHP format prepend the list to the existing footer
      $footer = $view->display[$display]->handler->get_option('footer');
      if (empty($footer)) $footer = $view->display['default']->handler->get_option('footer');
      if (!empty($footer) && !stripos($footer, '?php') > 0) $footer_content .= $footer;
      $view->display[$display]->handler->set_option('footer', $footer_content);    
    }
  }
}
/**
 * Implementation of hook_views_post_render().
 */
/*
function edulifedesks_statistics_views_post_render(&$view) {

}*/