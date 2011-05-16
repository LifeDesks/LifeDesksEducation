<?php
// $Id$
/**
 * @file
 * Menu callbacks for EduLifeDesks Statistics.
 */

/**
 * Overview of EduLifeDesks Statistics.
 */
function edulifedesks_statistics_overview() {
  $items = array();
  $items[] = l(t('All groups'), 'admin/content/statistics/all');
  return theme('item_list', $items, 'Data', 'ul');
}