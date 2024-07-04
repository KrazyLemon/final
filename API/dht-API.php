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
    }
    if($_SERVER["REQUEST_METHOD"] == "GET"){
        $action = test_input($_GET["action"]);
        if($action == "output_date"){
            $first_date = test_input($_GET["first_date"]);
            $second_date = test_input($_GET["second_date"]);
            $result = getDatosbyDate($first_date,$second_date);
            if ($result) {
                $rows = array();
                while ($row = $result->fetch_assoc()) {
                    $rows[] = $row;
                }
                $response = array(
                    "message" => $rows,
                    "response" => "200"
                );
        
                echo json_encode($response, JSON_PRETTY_PRINT);
            } else {
                echo json_encode(array("message" => "No data found", "response" => "404"));
            }
        }
        elseif($action == "output_limit"){
            $limit = test_input($_GET["limit"]);
            $result = getDatos($limit);
            if ($result) {
                $rows = array();
                while ($row = $result->fetch_assoc()) {
                    $rows[] = $row;
                }
                $response = array(
                    "message" => $rows,
                    "response" => "200"
                );
        
                echo json_encode($response, JSON_PRETTY_PRINT);
            } else {
                echo json_encode(array("message" => "No data found", "response" => "404"));
            }
        }
    }

    function test_input($data) {
        $data = trim($data);
        $data = stripslashes($data);
        $data = htmlspecialchars($data);
        return $data;
    }
?>
