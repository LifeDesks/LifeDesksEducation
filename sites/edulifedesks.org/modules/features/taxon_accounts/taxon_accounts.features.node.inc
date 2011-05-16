<?php

/**
 * Helper to implementation of hook_node_info().
 */
function _taxon_accounts_node_info() {
  $items = array(
    'taxon_account' => array(
      'name' => t('Taxon account'),
      'module' => 'features',
      'description' => t('An organism profile.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Organism profile'),
      'min_word_count' => '0',
      'help' => t('Enter information about an organism. To allow exchange of your data with the Encyclopedia of Life (EOL), provide metadata about the information you enter by selecting the meaning of each header and paragraph in your account, e.g. for your header and paragraphs that together make up a section containing information about the biology of the organism select meaning \'biology\'.'),
    ),
  );
  return $items;
}
