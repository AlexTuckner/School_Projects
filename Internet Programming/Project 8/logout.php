<?php
session_start();
unset($_SESSION);
session_destroy();
session_write_close();
header("Location: http://www-users.cselabs.umn.edu/~tuckn016/login.php");
die;
?>
