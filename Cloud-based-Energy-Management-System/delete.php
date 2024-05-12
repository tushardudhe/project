<?php
if (!isset($_COOKIE['username'])) {
    header("location:index.php");
}
require_once("config.php");
if(!empty($_GET))
{
    mysqli_query($al,"DELETE FROM data WHERE veganhash = '".$_GET['key']."'");
    setcookie("status",1,time() + 5);
    header("location:home.php");
}