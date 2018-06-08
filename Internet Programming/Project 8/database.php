<?php
  $data=simplexml_load_file('dbconfig.xml') or die("Error: Cannot create object!");
  $db_host = $data->host;
  $db_username = $data->user;
  $db_password = $data->password;
  $db_name = $data->database;
  $db_port = $data->port;
?>
