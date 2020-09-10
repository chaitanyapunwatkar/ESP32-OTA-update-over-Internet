<?php
// To take value from esp32 & store value in check file that update has been done 
$Received=$_POST["Text1"];
echo $Recieved;
file_put_contents('check.txt', $Received);
?>