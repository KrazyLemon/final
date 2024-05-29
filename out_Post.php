<?php
    $host = "localhost";
    $db = "id22193181_dht22_dev_db";
    $user = "id22193181_esp32_client";
    $pass = "s]2O79jdO$61";
  
    $con = mysqli_connect($host,$user,$pass,$db);

    if($con){
        if(isset($_POST[id]) && isset($_POST[state])){
            $id = $_POST[id];
            $state = $_POST[state];
            $consulta = "UPDATE Outputs SET state='" . $state . "' WHERE id='". $id .  "'";
            $resultado = mysqli_query($con, $consulta);
            if ($resultado){
                echo "Estado de salida actualizado correctamente!";
            } else {
                echo "Error: " . $sql . "<br>" . $conn->error;
            }
        }
    }
      
    function getAllOutputs() {
        global $servername, $username, $password, $dbname;

        // Create connection
        $conn = new mysqli($servername, $username, $password, $dbname);
        // Check connection
        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        }

        $sql = "SELECT id, name, board, gpio, state FROM Outputs ORDER BY board";
        if ($result = $conn->query($sql)) {
            return $result;
        }
        else {
            return false;
        }
        $conn->close();
    }
    
?>