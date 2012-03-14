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
      '#default_value' => isset($default_values['admin_menu_source_role_menu_' . $rid]) ? $default_values['admin_menu_source_role_menu_' . $rid] : '',
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