<?php
require_once("../config.php");
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}
$query = "SELECT * FROM data ORDER BY id DESC LIMIT 0,40";
$result = $conn->query($query);
$jsonArray = array();
if ($result->num_rows > 0) {
  while($row = $result->fetch_assoc()) {
    $jsonArrayItem = array();
    $jsonArrayItem['label'] = $row['date'];
    $jsonArrayItem['value'] = $row['voltage'];
    array_push($jsonArray, $jsonArrayItem);
  }
}
$conn->close();
header('Content-type: application/json');
echo json_encode($jsonArray);
?>
