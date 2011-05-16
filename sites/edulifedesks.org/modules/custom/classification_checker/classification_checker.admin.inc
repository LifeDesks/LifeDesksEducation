<?php

/*
 * Implementation of hook_settings()
 *
 * NOTE: this is merely a start to a more flexible solution. The URL parameters are STILL hard-coded to some extent
 */
function classification_checker_admin_settings() {
  $form['webservice'] = array(
    '#type' => 'fieldset',
    '#title' => t('EOL Web Service settings'),
    '#description' => t('Configure the EOL search web service'),
  );

  $form['webservice']['classification_checker_service_baseurl'] = array(
    '#type' => 'textfield',
    '#title' => t('EOL web service URL'),
    '#default_value' => variable_get('classification_checker_service_baseurl', 'http://services.eol.org/lifedesk/'),
    '#description' => t('Set the URL for the EOL search web service'),
    '#required' => true,
  );
  
  $form['webservice']['classification_checker_service_params'] = array(
    '#type' => 'textfield',
    '#title' => t('Additional parameters'),
    '#description' => t('Note: Catalogue of Life 2009 has hierarchy_id 147'),
    '#default_value' => variable_get('classification_checker_service_params', 'service.php?function=search&hierarchy_id=147&search='),
    '#required' => true,
  );
  
  return system_settings_form($form);
}
