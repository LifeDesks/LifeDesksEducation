<?php
// $Id$
/**
 * @file
 * Override template to render "eol_partnership" view's "feed" display results into Encyclopedia of Life XML schema.
 *
 * - $taxa : An associative array of taxa.
 * - $eol_error : a string containing error message if template_preprocess_views_bonus_export_xml__eol_partnership__feed has determined an error.
 * @ingroup views_templates
 * 
 */

// Short tags act bad below in the html so we print it here.
  print '<?xml version="1.0" encoding="UTF-8" ?>';
?>

<response
    xmlns="http://www.eol.org/transfer/content/0.2"
    xmlns:xsd="http://www.w3.org/2001/XMLSchema"
    xmlns:dc="http://purl.org/dc/elements/1.1/"
    xmlns:dcterms="http://purl.org/dc/terms/"
    xmlns:geo="http://www.w3.org/2003/01/geo/wgs84_pos#"
    xmlns:dwc="http://rs.tdwg.org/dwc/dwcore/"
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xsi:schemaLocation="http://www.eol.org/transfer/content/0.2 http://services.eol.org/schema/content_0_2.xsd">
<?php foreach ($taxa as $nid => $taxon): ?>
  <taxon>
    <?php foreach ($taxon as $label => $content): if ($label != 'data_objects'): if (!is_array($content)): print $content; ?>

    <?php else: foreach ($content as $i => $v): print $v; ?>

<?php endforeach; endif; endif; endforeach; if (!empty($taxon['data_objects'])): foreach ($taxon['data_objects'] as $object): ?>
    <dataObject>
      <?php foreach ($object as $label => $content): if (!is_array($content)): print $content; ?>

      <?php else: foreach ($content as $i => $v): print $v; ?>

<?php endforeach; endif; endforeach; ?>
    </dataObject>
  
    <?php endforeach; endif; ?>
  </taxon>
<?php endforeach; ?>
</response>