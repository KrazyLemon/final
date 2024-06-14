<?php
    include_once('dht-database.php');
    if($_SERVER[$_REQUEST_METHOD]== "POST"){
        $temperature = test_input($_POST["temperature"]);
        $humidity = test_input($_POST["humidity"]);
        $heat = test_input($_POST["heat"]);
        $moist = test_input($_POST["moist"]);
        $result = createDHT($humidity,$temperature,$moist,$heat);
        echo $result;
    }else{
        echo "No data posted with HTTP POST.";
    }
    if($_SERVER[$_REQUEST_METHOD]=="GET"){
        $limit = test_input($_GET["limit"]);
        $result = getDHT($limit);
        echo json_encode($result);
    }else{
        echo "No data posted with HTTP GET.";
    }
    function test_input($data) {
        $data = trim($data);
        $data = stripslashes($data);
        $data = htmlspecialchars($data);
        return $data;
    }
?>
