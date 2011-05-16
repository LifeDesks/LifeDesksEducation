<?php
// $Id$
/**
 * @file
 * Default theme implementation to for EOL Partnership administration overview.
 *
 * @see template_preprocess_eol_partnership_admin_overview.tpl.php
 * Available variables:
 * - $data: Array of available data.
 * - $content: Array of html strings 
 * - $content['view_status']['description']
 * - $content['content_types']['description']
 * - $content['content_types']['included_description']
 * - $content['content_types']['included_list']
 * - $content['content_types']['excluded_description']
 * - $content['content_types']['excluded_list']
 * - $content['content_types']['compatible_description']
 * - $content['content_types']['compatible_list'] 
 * - $content['xml']['partnership']
 * - $content['xml']['download']
 * - $content['rebuild_xml_form']
 */
?>
<div id="eol-partnership-overview">
<?php
  if ($content) {
    foreach ($content as $section => $content) {
      if (is_array($content)) {
        foreach ($content as $subsection => $output) {
          print $output;
        }
      } else {
        print $content;
      }
    }
  }
?>
</div>