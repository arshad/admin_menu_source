<?php

/**
 * @file
 * Menu callbacks for admin_menu_source module
 */

function admin_menu_source_settings() {
  $roles = user_roles();
  $menus = menu_get_menus();
  $default_values = _admin_menu_source_get_settings();
  
  $form['admin_menu_source_settings'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => t('Menu source per role'),
  );
  
  foreach ($roles as $rid => $role) {
    $form['admin_menu_source_settings']['admin_menu_source_role_' . $rid] = array(
      '#markup' => $role
    );
    $form['admin_menu_source_settings']['admin_menu_source_role_menu_' . $rid] = array(
      '#type' => 'select',
      '#options' => array('' => t('Default')) + $menus,
      '#default_value' => $default_values['admin_menu_source_role_menu_' . $rid],
    );
  }
  
  //add a custom submit handler
  $form['#submit'][] = 'admin_menu_source_settings_submit';
  
  return system_settings_form($form);
}

function admin_menu_source_settings_submit() {
  //flush admin_menu's cache
  admin_menu_flush_caches();
}

/**
 * Helper function to get settings for admin_menu_source
 */
function _admin_menu_source_get_settings() {
  return variable_get('admin_menu_source_settings', array());
}

/**
 * Helper function to get source menu per role
 *
 * @param $rid
 *  the user role id
 */
function _admin_menu_source_get_role_menu($rid) {
  //load the settings
  $settings = _admin_menu_source_get_settings();
  
  return $settings['admin_menu_source_role_menu_' . $rid];
}