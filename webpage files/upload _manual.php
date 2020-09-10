
<!DOCTYPE html>
<html>
<body>

<h3>For Updating the firmware click on button below</h3>

<form name="input" method="post" action="upload.php">
<input type="submit" name="submit" value="Update"/>
<input type="submit" name="submit" value="No Update"/>
</form>

</body>
</html>

<?php
$target_dir = "public_html";
$target_file = "firm.bin";

$imageFileType = strtolower(pathinfo($target_file,PATHINFO_EXTENSION));
echo "</br>";
// Check if image file is a actual image or fake image
if($_POST["submit"] === "Upload") {
    
    if (move_uploaded_file($_FILES["fileToUpload"]["tmp_name"], $target_file)) {
        $uploadOk = 1;
        echo "The file ". basename( $_FILES["fileToUpload"]["name"]). " has been uploaded.";
    } 
    
    else {
        echo "Sorry, there was an error uploading your file.";
    }
}


    
if($_POST["submit"] === "Update"){
    $value = "1";
    echo "Firmware will get updated within few minutes";
    file_put_contents("check.txt", $value);
}

if($_POST["submit"] === "No Update"){
   $value = "10";
   file_put_contents("check.txt", $value);
   echo "Stop Update";
}

?>


