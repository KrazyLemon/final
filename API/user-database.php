<?php
     $servername = "localhost";
     // Your Database name
     $dbname = "id22193181_dht22_dev_db";
     // Your Database user
     $username = "id22193181_esp32_client";
     // Your Database user password
     $password = "s]2O79jdO$61";

    function createUser($name, $email, $password) {
        global $servername, $username, $password, $dbname;
    
            // Create connection
        $conn = new mysqli($servername, $username, $password, $dbname);
            // Check connection
            if ($conn->connect_error) {
                die("Connection failed: " . $conn->connect_error);
            }
    
            $sql = "INSERT INTO Users (name, email, password)
            VALUES ('" . $name . "', '" . $email . "', '" . $password . "')";
    
            if ($conn->query($sql) === TRUE) {
                return "New user created successfully";
            }
            else {
                return "Error: " . $sql . "<br>" . $conn->error;
            }
            $conn->close();
    }
    function deleteUser($id) {
        global $servername, $username, $password, $dbname;
    
            // Create connection
        $conn = new mysqli($servername, $username, $password, $dbname);
            // Check connection
            if ($conn->connect_error) {
                die("Connection failed: " . $conn->connect_error);
            }
    
            $sql = "DELETE FROM Users WHERE id='". $id .  "'";
    
            if ($conn->query($sql) === TRUE) {
                return "User deleted successfully";
            }
            else {
                return "Error: " . $sql . "<br>" . $conn->error;
            }
            $conn->close();
    }
    function updateUser($id, $name, $email, $password) {
        global $servername, $username, $password, $dbname;
    
            // Create connection
        $conn = new mysqli($servername, $username, $password, $dbname);
            // Check connection
            if ($conn->connect_error) {
                die("Connection failed: " . $conn->connect_error);
            }
    
            $sql = "UPDATE Users SET name='" . $name . "', email='" . $email . "', password='" . $password . "' WHERE id='". $id .  "'";
    
            if ($conn->query($sql) === TRUE) {
                return "User updated successfully";
            }
            else {
                return "Error: " . $sql . "<br>" . $conn->error;
            }
            $conn->close();
    }
    
?>