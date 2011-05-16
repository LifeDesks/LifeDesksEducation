<?php 
  // Admin form fields and submit buttons must be rendered first, because
  // they need to go to the bottom of the form, and so should not be part of
  // the catch-all call to drupal_render().
  $admin = '';
  if (isset($form['author'])) {
    $admin .= "    <div class=\"authored\">\n";
    $admin .= drupal_render($form['author']);
    $admin .= "    </div>\n";
  }
  if (isset($form['options'])) {
    $admin .= "    <div class=\"options\">\n";
    $admin .= drupal_render($form['options']);
    $admin .= "    </div>\n";
  }
  $buttons = drupal_render($form['buttons']);
?>
<div class="node-form">
  <div class="standard">
    
    <?php if ($important_fields): ?>
    <div class="important-fields">
      <?php 
        foreach ($important_fields as $name) {
          print drupal_render($form[$name]);
        }
      ?>
    </div>
    <?php endif; ?>
    
    <?php if ($optional_fields): ?>
    <div class="optional-fields">
      <?php 
        foreach ($optional_fields as $name) {
          print drupal_render($form[$name]);
        }
        print $admin;
      ?>
    </div>
    <?php endif; ?>
    
    <div class="closure-fields">
      <?php print $closure_fields; ?>
      <?php print drupal_render($form); // catch all adds any remaining fields to bottom of form ?>
    </div>
    
    <div class="buttons">
      <?php print $buttons; ?>
    </div>
  </div>
</div>