<?php
//$Id$

/**
 * @file node-submitted.tpl.php
 *
 * Theme implementation of node module's theme_node_submitted, showing author and created (?) date.
 * 
 * Available variables:
 * - $node: Full node object. Contains data that may not be safe.
 */
print t('Submitted by !username ', array('!username' => theme('username', $node)));
?>
<span class="updated"><?php print format_date($node->changed, 'custom', 'd M');?></span>