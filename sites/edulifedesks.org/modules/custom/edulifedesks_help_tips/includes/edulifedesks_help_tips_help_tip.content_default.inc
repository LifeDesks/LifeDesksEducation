$content['type']  = array (
  'name' => 'Help tip',
  'type' => 'help_tip',
  'description' => 'Add help tips for users. Add a tip and decide on which page it should appear and for which user role.',
  'title_label' => 'Title',
  'body_label' => 'Tip',
  'min_word_count' => '0',
  'help' => '',
  'node_options' => 
  array (
    'status' => false,
    'promote' => false,
    'sticky' => false,
    'revision' => false,
    'revision_moderation' => false,
  ),
  'new_revisions' => 1,
  'revisioning_auto_publish' => 0,
  'language_content_type' => '1',
  'upload' => '1',
  'old_type' => 'help_tip',
  'orig_type' => '',
  'module' => 'node',
  'custom' => '1',
  'modified' => '1',
  'locked' => '0',
  'og_content_type_usage' => 'omitted',
  'og_max_groups' => '',
  'content_profile_use' => 0,
  'comment' => '0',
  'comment_default_mode' => '4',
  'comment_default_order' => '1',
  'comment_default_per_page' => '50',
  'comment_controls' => '3',
  'comment_anonymous' => 0,
  'comment_subject_field' => '1',
  'comment_preview' => '0',
  'comment_form_location' => '0',
  'comment_upload' => '0',
  'comment_upload_images' => 'none',
  'notifications_node_ui' => 
  array (
    'form' => false,
    'comment' => false,
    'links' => false,
    'teaserlinks' => false,
    'subform' => false,
    'block' => false,
  ),
  'notifications_content_type' => 
  array (
    'grouptype' => false,
    'thread' => false,
    'nodetype' => false,
    'author' => false,
    'typeauthor' => false,
  ),
  'ant' => '0',
  'ant_pattern' => '',
  'ant_php' => 0,
  'i18n_newnode_current' => 0,
  'i18n_required_node' => 0,
  'i18n_lock_node' => 0,
  'i18n_node' => 1,
  'better_formats_allowed' => 
  array (
    9 => true,
    1 => false,
    2 => false,
    4 => false,
    5 => false,
    14 => false,
    7 => false,
    10 => false,
    11 => false,
    12 => false,
    13 => false,
    15 => false,
  ),
  'better_formats_defaults' => 
  array (
    'node-3' => 
    array (
      'format' => '0',
      'weight' => '-25',
    ),
    'node-4' => 
    array (
      'format' => '0',
      'weight' => '-24',
    ),
    'node-5' => 
    array (
      'format' => '0',
      'weight' => '-23',
    ),
    'node-2' => 
    array (
      'format' => '0',
      'weight' => '-22',
    ),
    'node-1' => 
    array (
      'format' => '0',
      'weight' => '-21',
    ),
    'node-6' => 
    array (
      'format' => '0',
      'weight' => '25',
    ),
    'node-7' => 
    array (
      'format' => '0',
      'weight' => '25',
    ),
    'node-11' => 
    array (
      'format' => '0',
      'weight' => '25',
    ),
    'comment-3' => 
    array (
      'format' => '0',
      'weight' => '-25',
    ),
    'comment-4' => 
    array (
      'format' => '0',
      'weight' => '-24',
    ),
    'comment-5' => 
    array (
      'format' => '0',
      'weight' => '-23',
    ),
    'comment-2' => 
    array (
      'format' => '0',
      'weight' => '-22',
    ),
    'comment-1' => 
    array (
      'format' => '0',
      'weight' => '-21',
    ),
    'comment-6' => 
    array (
      'format' => '0',
      'weight' => '25',
    ),
    'comment-7' => 
    array (
      'format' => '0',
      'weight' => '25',
    ),
    'comment-11' => 
    array (
      'format' => '0',
      'weight' => '25',
    ),
  ),
);
$content['fields']  = array (
  0 => 
  array (
    'label' => 'Override heading',
    'field_name' => 'field_override_heading',
    'type' => 'number_integer',
    'widget_type' => 'optionwidgets_onoff',
    'change' => 'Change basic information',
    'weight' => '-4',
    'description' => 'Check override title to use the title of this help tip as the block header instead of the default "Need Help?" heading.',
    'default_value' => 
    array (
      0 => 
      array (
        'value' => 'default',
      ),
    ),
    'default_value_php' => '',
    'default_value_widget' => NULL,
    'group' => false,
    'required' => 0,
    'multiple' => '0',
    'min' => '',
    'max' => '',
    'prefix' => '',
    'suffix' => '',
    'allowed_values' => '0|Use default
1|Override heading',
    'allowed_values_php' => '',
    'op' => 'Save field settings',
    'module' => 'number',
    'widget_module' => 'optionwidgets',
    'columns' => 
    array (
      'value' => 
      array (
        'type' => 'int',
        'not null' => false,
        'sortable' => true,
      ),
    ),
    'display_settings' => 
    array (
      'weight' => '-4',
      'parent' => '',
      'label' => 
      array (
        'format' => 'above',
      ),
      'teaser' => 
      array (
        'format' => 'default',
        'exclude' => 1,
      ),
      'full' => 
      array (
        'format' => 'default',
        'exclude' => 1,
      ),
      5 => 
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
      4 => 
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
      2 => 
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
      3 => 
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => 
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
  ),
  1 => 
  array (
    'label' => 'Appears on',
    'field_name' => 'field_internal_path',
    'type' => 'text',
    'widget_type' => 'optionwidgets_select',
    'change' => 'Change basic information',
    'weight' => '-2',
    'description' => 'Select the site section on which you would like the help tip to appear.',
    'default_value' => 
    array (
      0 => 
      array (
        'value' => '',
      ),
    ),
    'default_value_php' => '',
    'default_value_widget' => 
    array (
      'field_internal_path' => 
      array (
        'value' => '',
      ),
    ),
    'group' => false,
    'required' => 1,
    'multiple' => '0',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => 'return array(
  \'<front>\' => \'Site home page\',
  \'groups|my|activity\' => \'Site section: My groups\',
  \'class|%nid\' => \'Class section: Overview\',
  \'class|%nid|taxon-pages\' => \'Class section: Taxon pages > List\',
  \'class|%nid|taxon-page|%nid\' => \'Class section: Taxon pages > Taxon page > view\',
  \'class|%nid|assignments\' => \'Class section: Assignments > List\',
  \'og|users|%nid\' => \'Class section: Members > List\',
  \'og|users|%nid|add_user\' => \'Class section: Members > Add members\',
  \'og|users|%nid|roles\' => \'Class section: Members > Configure roles\',
  \'class|%nid|broadcast\' => \'Class section: Send email\',
);',
    'op' => 'Save field settings',
    'module' => 'text',
    'widget_module' => 'optionwidgets',
    'columns' => 
    array (
      'value' => 
      array (
        'type' => 'text',
        'size' => 'big',
        'not null' => false,
        'sortable' => true,
        'views' => true,
      ),
    ),
    'display_settings' => 
    array (
      'weight' => '-2',
      'parent' => '',
      'label' => 
      array (
        'format' => 'above',
      ),
      'teaser' => 
      array (
        'format' => 'default',
        'exclude' => 1,
      ),
      'full' => 
      array (
        'format' => 'default',
        'exclude' => 1,
      ),
      2 => 
      array (
        'format' => 'default',
        'exclude' => 1,
      ),
      3 => 
      array (
        'format' => 'default',
        'exclude' => 1,
      ),
      4 => 
      array (
        'format' => 'default',
        'exclude' => 1,
      ),
      'token' => 
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
  ),
  2 => 
  array (
    'label' => 'More on help page',
    'field_name' => 'field_help_page',
    'type' => 'nodereference',
    'widget_type' => 'nodereference_select',
    'change' => 'Change basic information',
    'weight' => '-1',
    'autocomplete_match' => 'contains',
    'size' => 60,
    'description' => 'Link this help tip with a help page.',
    'default_value' => 
    array (
      0 => 
      array (
        'nid' => '',
      ),
    ),
    'default_value_php' => '',
    'default_value_widget' => 
    array (
      'field_help_page' => 
      array (
        0 => 
        array (
          'nid' => '',
        ),
        'nid' => 
        array (
          'nid' => '',
        ),
      ),
    ),
    'group' => false,
    'required' => 0,
    'multiple' => '0',
    'referenceable_types' => 
    array (
      'help' => 'help',
      'assignment' => 0,
      'book' => 0,
      'class' => 0,
      'error' => 0,
      'evaluation' => 0,
      'feature' => 0,
      'feed' => 0,
      'page' => 0,
      'help_tip' => 0,
      'home' => 0,
      'ifa_upload' => 0,
      'profile' => 0,
      'slide' => 0,
      'story' => 0,
      'taxon_page' => 0,
      'notice' => false,
    ),
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'op' => 'Save field settings',
    'module' => 'nodereference',
    'widget_module' => 'nodereference',
    'columns' => 
    array (
      'nid' => 
      array (
        'type' => 'int',
        'unsigned' => true,
        'not null' => false,
        'index' => true,
      ),
    ),
    'display_settings' => 
    array (
      'weight' => '-1',
      'parent' => '',
      'label' => 
      array (
        'format' => 'hidden',
      ),
      'teaser' => 
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => 
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
      5 => 
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
      4 => 
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
      2 => 
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
      3 => 
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => 
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
  ),
  3 => 
  array (
    'label' => 'Lightbox',
    'field_name' => 'field_use_lightbox',
    'type' => 'number_integer',
    'widget_type' => 'optionwidgets_onoff',
    'change' => 'Change basic information',
    'weight' => 0,
    'description' => 'Check to use lightbox for the \'more on help page\' link. A lightbox link is where the linked page is shown in an overlay window on top of current page. If you uncheck then the link will behave as a normal hyperlink.',
    'default_value' => 
    array (
      0 => 
      array (
        'value' => 1,
      ),
    ),
    'default_value_php' => '',
    'default_value_widget' => 
    array (
      'field_use_lightbox' => 
      array (
        'value' => true,
      ),
    ),
    'group' => false,
    'required' => 0,
    'multiple' => '0',
    'min' => '',
    'max' => '',
    'prefix' => '',
    'suffix' => '',
    'allowed_values' => '0|Do not use lightbox
1|Use lightbox',
    'allowed_values_php' => '',
    'op' => 'Save field settings',
    'module' => 'number',
    'widget_module' => 'optionwidgets',
    'columns' => 
    array (
      'value' => 
      array (
        'type' => 'int',
        'not null' => false,
        'sortable' => true,
      ),
    ),
    'display_settings' => 
    array (
      'weight' => 0,
      'parent' => '',
      'label' => 
      array (
        'format' => 'above',
      ),
      'teaser' => 
      array (
        'format' => 'default',
        'exclude' => 1,
      ),
      'full' => 
      array (
        'format' => 'default',
        'exclude' => 1,
      ),
      5 => 
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
      4 => 
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
      2 => 
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
      3 => 
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => 
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
  ),
  4 => 
  array (
    'label' => 'Target roles',
    'field_name' => 'field_user_roles',
    'type' => 'text',
    'widget_type' => 'optionwidgets_buttons',
    'change' => 'Change basic information',
    'weight' => '3',
    'description' => 'Display this help tip for selected roles. You must specify at least one role.',
    'default_value' => 
    array (
      0 => 
      array (
        'value' => NULL,
      ),
    ),
    'default_value_php' => '',
    'default_value_widget' => 
    array (
      'field_user_roles' => 
      array (
        'value' => 
        array (
          '' => 1,
          2 => false,
          4 => false,
          3 => false,
          6 => false,
          7 => false,
          5 => false,
          11 => false,
        ),
      ),
    ),
    'group' => false,
    'required' => 1,
    'multiple' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '$roles = user_roles(TRUE);
foreach ($roles as $rid => $role) {
  $allowed[$rid] = $role;
}
return (isset($allowed)) ? $allowed : array(t(\'An error occurred selecting the available roles, please contact your site administrator\'));',
    'op' => 'Save field settings',
    'module' => 'text',
    'widget_module' => 'optionwidgets',
    'columns' => 
    array (
      'value' => 
      array (
        'type' => 'text',
        'size' => 'big',
        'not null' => false,
        'sortable' => true,
        'views' => true,
      ),
    ),
    'display_settings' => 
    array (
      'weight' => '3',
      'parent' => '',
      'label' => 
      array (
        'format' => 'above',
      ),
      'teaser' => 
      array (
        'format' => 'default',
        'exclude' => 1,
      ),
      'full' => 
      array (
        'format' => 'default',
        'exclude' => 1,
      ),
      4 => 
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
      2 => 
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
      3 => 
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => 
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
  ),
);
$content['extra']  = array (
  'title' => '-5',
  'body_field' => '-3',
  'revision_information' => '5',
  'author' => '11',
  'options' => '12',
  'comment_settings' => '8',
  'language' => '2',
  'menu' => '4',
  'book' => '9',
  'path' => '6',
  'attachments' => '7',
  'workflow' => '10',
);