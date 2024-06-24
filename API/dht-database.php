<?php
    $servername = "localhost";
    // Your Database name
    $dbname = "id22193181_dht22_dev_db";
    // Your Database user
    $username = "id22193181_esp32_client";
    // Your Database user password
    $password = "s]2O79jdO$61";
   
    //--------------- TABLA DHT_DATA FUNCIONES ----------------- //
    function postDatos($hum,$temp,$heat,$smp_a,$smp_b,$smp_c,$smp_d,$smp_e){
        global $servername, $username, $password, $dbname;
        
        
        $conn = new mysqli($servername,$username,$password, $dbname);

        if($conn->connect_error){
            die("Conexion a la DB Fallida" . $conn->connect_error);
        }

        date_default_timezone_set('america/Mexico_City');
        $posted_at = date("Y-m-d H:i:s");

        $sql = "INSERT INTO Datos(temp,hum,heat,smp_a,smp_b,smp_c,smp_d,smp_e,posted_at) 
        VALUES('" . $temp . "','" . $hum . "','" . $heat . "','" . $smp_a . "','". $smp_b . "','" . $smp_c . "','" . $smp_d . "','" . $smp_e . "','" . $posted_at . "')";
                
        if($conn->query($sql) === TRUE){
            return "Datos Insertados Correctamente";
        }else{
            return "Error: " . $sql . "<br>" . $conn->error;
            }
        $conn->close();
    }
    
    function getDatos($limit){
        global $servername, $username, $password, $dbname;
    
        $conn = new mysqli($servername,$username,$password, $dbname);
        if($conn->connect_error){
            die("Conexion a la DB Fallida" . $conn->connect_error);
        }
        $sql = "SELECT * FROM Datos ORDER BY posted_at DESC LIMIT '" . $limit . "'";
            
        if($result = $conn->query($sql)){
            return $result;
        }else{
            return false;
        }
        $conn->close();
    }
        
?>