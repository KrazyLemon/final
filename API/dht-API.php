<?php
    include_once('dht-database.php');
    if($_SERVER["$_REQUEST_METHOD"]== "POST"){
        $temp = test_input($_POST["temp"]);
        $hum = test_input($_POST["hum"]);
        $heat = test_input($_POST["heat"]);
        $spm_a = test_input($_POST["spm_a"]);
        $spm_b = test_input($_POST["spm_b"]);
        $spm_c = test_input($_POST["spm_c"]);
        $spm_d = test_input($_POST["spm_d"]);
        $spm_e = test_input($_POST["spm_e"]);
        $result = postDatos($hum,$temp,$heat,$spm_a,$spm_b,$spm_c,$spm_d,$spm_e);
        echo $result;
    }else{
        echo "No data posted with HTTP POST.";
    }
    if($_SERVER["$_REQUEST_METHOD"]=="GET"){
        $limit = test_input($_GET["limit"]);
        $result = getDatos($limit);
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
