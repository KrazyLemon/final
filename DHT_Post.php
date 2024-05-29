<?php
$DB_HOST = "localhost";
$DB = "id22193181_dht22_dev_db";
$DB_USER = "id22193181_esp32_client";
$DB_PASS = "s]2O79jdO$61";

$CON = mysqli_connect($DB_HOST,$DB_USER,$DB_PASS,$DB);

if ($CON) {
    echo "Conexion con base de datos exitosa! ";
    
    if(isset($_POST['dht_humidity']) && isset($_POST['dht_temperature']) && isset($_POST['dht_heat']) && isset($_POST['soil_moisture']) ) { 
        $dht_humidity = $_POST['dht_humidity'];
        $dht_temperature = $_POST['dht_temperature'];
        $dht_heat = $_POST['dht_heat'];
        $soil_moisture = $_POST['soil_moisture'];
        
        date_default_timezone_set('america/Mexico_City');
        $posted_at = date("Y-m-d H:i:s");
        $consulta = "INSERT INTO dht_data(dht_humidity,dht_temperature,dht_heat,soil_moisture,posted_at) VALUES ('$dht_humidity','$dht_temperature','$dht_heat','$soil_moisture','$posted_at')";     
        $resultado = mysqli_query($CON, $consulta);
        if ($resultado){
            echo " Registo en base de datos OK! ";
        } else {
            echo " Falla! Registro BD";
        }
    }
} else {
    echo "Falla! conexion con Base de datos ";   
}
?>