#!/usr/bin/php
<?php
include_once dirname(__FILE__).'/' .'class.csv_update_module.inc';
ini_set('display_errors', "On");
CSV_UPDATE_MODULE::set_csv_filename('create');
CSV_UPDATE_MODULE::force_load_csv();
//CSV_UPDATE_MODULE::set_template_html(dirname(__FILE__).'/' .'template.html');
CSV_UPDATE_MODULE::set_template_html(dirname(__FILE__).'/' .'replace.html');
//CSV_UPDATE_MODULE::force_create_html();
CSV_UPDATE_MODULE::replace_html();
?>
