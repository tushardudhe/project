<?php

if(!empty($_GET))
{
    require_once('config.php');
    $sql = mysqli_query($al,"INSERT INTO data(veganhash,current,voltage,time,date) VALUES('".uniqid()."','".$_GET['c']."','".$_GET['v']."','".date('h:i a')."','".date('d-m-Y')."')");
    if($sql)
    {
        echo "Success";
    }
    else
    {
        echo "Error";
    }
}
?>