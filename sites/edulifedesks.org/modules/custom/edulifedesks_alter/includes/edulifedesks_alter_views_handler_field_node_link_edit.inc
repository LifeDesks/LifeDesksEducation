<?php
// $Id$

/**
 * @file
 * Provide views field handler override for node edit link.
 */

/**
 * Field handler to restrict access to views node edit link.
 */
class edulifedesks_alter_views_handler_field_node_link_edit extends views_handler_field_node_link {
  function construct() {
    parent::construct();
    $this->additional_fields['uid'] = 'uid';
    $this->additional_fields['type'] = 'type';
    $this->additional_fields['format'] = array('table' => 'node_revisions', 'field' => 'format');
  }
  
  function render($values) {
    // ensure user has access to edit this node.
    $node = new stdClass();
    $node->nid = $values->{$this->aliases['nid']};
    $node->uid = $values->{$this->aliases['uid']};
    $node->type = $values->{$this->aliases['type']};
    $node->format = $values->{$this->aliases['format']};
    // $node->status = 1; // unpublished nodes ignore access control (only without module grants so don't actually need this)
    if (!module_grants_node_access('update', $node)) {
     return;
    }
    
    $text = !empty($this->options['text']) ? $this->options['text'] : t('edit');
    return l($text, "node/$node->nid/edit", array('query' => drupal_get_destination()));
  }  
}