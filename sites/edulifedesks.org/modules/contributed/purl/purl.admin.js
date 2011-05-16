// $Id: purl.admin.js,v 1.1.2.1 2009/11/04 21:21:47 yhahn Exp $

if (typeof(Drupal) == "undefined" || !Drupal.purl_admin) {
  Drupal.purl_admin = {};
}

Drupal.purl_admin.attach = function() {
  $('select[id^="edit-purl-"]:not(.purl-processed)').change(function(i) {
    Drupal.purl_admin.alter(this);
  }).each(function(i){
    Drupal.purl_admin.alter(this);
  }).addClass('purl-processed');
}

Drupal.purl_admin.alter = function(elem){
  if (elem.value == 'pair' || elem.value == 'querystring') {
    $(elem).parents('tr').find('input[id^="edit-purl-"]').show();
  }
  else {
    $(elem).parents('tr').find('input[id^="edit-purl-"]').hide();
  }
}

Drupal.behaviors.purl = function() {
  if ($('form#purl-settings-form').size() > 0) {
    Drupal.purl_admin.attach();
  }
}