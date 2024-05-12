<?php
if (!isset($_COOKIE['username'])) {
    header("location:index.php");
} else {
    $name = "Administrator";
}
require_once("config.php");
mysqli_query($al,"TRUNCATE data");
header("location:home.php");
?>