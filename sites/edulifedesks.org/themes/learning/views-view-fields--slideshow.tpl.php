<?php
// $Id$
/**
 * @file views-view-fields.tpl.php
 * Default simple view template to all the fields as a row.
 *
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->separator: an optional separator that may appear before a field.
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * @ingroup views_templates
 */
?>
<div style="position:relative;width:960px;height:284px;padding-left:120px;background:url(/<?php print $fields['field_slide_image_fid']->content ?>) no-repeat;overflow:hidden;">
	<div style="width:250px;height:284px;background:#FFFFFF;filter:alpha(opacity=<?php print $fields['field_bg_transparency_value']->content ?>0);-moz-opacity:0.<?php print $fields['field_bg_transparency_value']->content ?>;-khtml-opacity:0.<?php print $fields['field_bg_transparency_value']->content ?>;opacity:0.<?php print $fields['field_bg_transparency_value']->content ?>;"></div>
    <div style="position:relative;top:-180px;left:10px;width:235px;z-index:10;" class="slidetext">
    	<h2><?php print $fields['title']->content ?></h2>
    	<?php print $fields['body']->content ?>
    </div>
</div>
