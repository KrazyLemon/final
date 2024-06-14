<?php
    $servername = "localhost";
    // Your Database name
    $dbname = "id22193181_dht22_dev_db";
    // Your Database user
    $username = "id22193181_esp32_client";
    // Your Database user password
    $password = "s]2O79jdO$61";
   
    //--------------- TABLA DHT_DATA FUNCIONES ----------------- //
    function createDHT($hum,$temp,$moist,$heat){
        global $servername, $username, $password, $dbname;
        $conn = new mysqli($servername,$username,$password, $dbname);
        if($conn->connect_error){
            die("Conexion a la DB Fallida" . $conn->connect_error);
        }
        date_default_timezone_set('america/Mexico_City');
        $posted_at = date("Y-m-d H:i:s");

        $sql = "INSERT INTO dht_data(dht_humidity,dht_temperature,dht_heat,soil_moisture,posted_at) 
        VALUES ('$hum','$temp','$heat','$moist','$posted_at')";     
    
        if($result = $conn->query($sql)){
            return $result;
        }else{
            return false;
            }
        $conn->close();
    }
    
    function getDHT($limit){
        global $servername, $username, $password, $dbname;
    
        $conn = new mysqli($servername,$username,$password, $dbname);
        if($conn->connect_error){
            die("Conexion a la DB Fallida" . $conn->connect_error);
        }
        $sql = "SELECT dht_humidity, dht_temperature, dht_heat, soil_moisture, posted_at 
        FROM dht_data ORDER BY posted_at DESC LIMIT '" . $limit . "'";
            
        if($result = $conn->query($sql)){
            return $result;
        }else{
            return false;
        }
        $conn->close();
    }
        
?>