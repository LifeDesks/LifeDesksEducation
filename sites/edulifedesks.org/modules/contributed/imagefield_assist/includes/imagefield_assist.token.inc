<?php
// $Id: imagefield_assist.token.inc,v 1.1.2.3 2009/12/07 18:27:40 lourenzo Exp $

/**
 * @file
 * Token API
 *
 * Provides integration with Token API
 */

/**
 * Implementation of hook_token_values().
 */
function imagefield_assist_token_values($type, $object = NULL, $options = array()) {
  $values = array();
  switch ($type) {
    case 'node':
      $node = $object;
      $values['teaser'] = imagefield_assist_sanitize($node->teaser);
      $values['body']   = imagefield_assist_sanitize($node->body);
      break;
  }
  return $values;
}

/**
 * Implementation of hook_token_list().
 */
function imagefield_assist_token_list($type = 'all') {
  if ($type == 'node' || $type == 'all') {
    $tokens['node']['teaser'] = t('Node teaser text (plain text)');
    $tokens['node']['body']   = t('Node body text (plain text)');
    return $tokens;
  }
}

