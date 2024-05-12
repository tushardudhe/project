<?php
  setcookie("username","", time() - 300);
  header("location:index.php");
  ?>