<?php
    include_once('dht-database.php');

    if($_SERVER["REQUEST_METHOD"] == "POST"){
        $hum = test_input($_POST["hum"]);
        $temp = test_input($_POST["temp"]);
        $heat = test_input($_POST["heat"]);
        $smp_a = test_input($_POST["smp_a"]);
        $smp_b = test_input($_POST["smp_b"]);
        $smp_c = test_input($_POST["smp_c"]);
        $smp_d = test_input($_POST["smp_d"]);
        $smp_e = test_input($_POST["smp_e"]);
        $result = postDatos($hum,$temp,$heat,$smp_a,$smp_b,$smp_c,$smp_d,$smp_e);
        echo $result;
    }else{
        echo "No data posted with HTTP POST.";
    }
    if($_SERVER["REQUEST_METHOD"] == "GET"){
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
