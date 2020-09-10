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
        $value = "1";
        echo "Firmware will get updated within few minutes";
        file_put_contents("check.txt", $value);
    } 
    
    else {
        echo "Sorry, there was an error uploading your file.";
    }
}

?>


