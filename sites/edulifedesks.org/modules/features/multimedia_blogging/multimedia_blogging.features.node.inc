<?php

/**
 * Helper to implementation of hook_node_info().
 */
function _multimedia_blogging_node_info() {
  $items = array(
    'blog_post' => array(
      'name' => t('Blog post'),
      'module' => 'features',
      'description' => t('Create a blog post.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => t('Create your blog post.'),
    ),
    'bookmark' => array(
      'name' => t('Bookmark'),
      'module' => 'features',
      'description' => t('Add a link that points to an external Web site.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
    'image' => array(
      'name' => t('Image'),
      'module' => 'features',
      'description' => t('Upload an image.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
    'video' => array(
      'name' => t('Video'),
      'module' => 'features',
      'description' => t('Embed video into your site.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => t('<p>If you are embedding video from an external site (like Google Video or Blip.tv) add the URL of the video into the <em>Video location</em> field.</p> 
<p>If you are uploading video to this site, upload the video as an attachment, and then paste the url of the file into the <em>Video location</em> field.</p> '),
    ),
  );
  return $items;
}
