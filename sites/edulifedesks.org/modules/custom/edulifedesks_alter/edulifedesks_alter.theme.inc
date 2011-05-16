<?php
// $Id$
/**
 * @file
 * Theme related functions for edulifedesks_alter.
 */
/*
 * Theme group settings block
 */
function theme_edulifedesks_alter_group_settings_block($group) {
  if (!empty($group)) {
    $content .= '<dl>';
    $content .= '<dt>' . t('Group name:') .'</dt>';
    $content .= '<dd>' . $group['name'] .'</dd>';
    $content .= '<dt>' . t('Group privacy:') .'</dt>';
    $content .= '<dd>';
    $content .= ($group['node']->og_private) ? t('Private') : t('Public');
    $content .= '</dd>';
    $content .= '</dl>';
  }
  return $content;
}