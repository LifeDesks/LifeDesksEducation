// $Id$

ABOUT
-----

This module provides access to summary data about content produced by Organic Groups groups, including node counts 
for each content type and Workflow status.

INSTALLATION
------------

1. Place the "edulifedesks_statistics" folder in your modules directory e.g. "sites/all/modules".
2. Enable the module under Administer >> Site building >> Modules (admin/build/modules).
3. Go to Administer >> User Management >> Permissions (admin/user/permissions) and give roles the 'access content statistics' permission
3. Go to Administer >> Content Management >> Content Statistics (admin/content/statistics) to view stats.
4. (optional) Go to Administer >> Site Building >> Blocks and enable the EduLifeDesks Statistics blocks.
   To only display blocks on group home page use PHP code e.g.:
   <?php
   $group = og_get_group_context();
   $alias = $_SERVER['REQUEST_URI'];
   if (preg_match('@^/class/[0-9]+/?(view)?/?(\?.*)?$@i', $alias) && (isset($group) && user_access('access content statistics'))) {
   return TRUE;
   } else {
   return FALSE; 
   }
   ?>

AUTHOR
------
lwalley@eol.org