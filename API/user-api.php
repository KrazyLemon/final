<?php
    include_once('user-database.php');

    if($_SERVER["REQUEST_METHOD"] == "POST"){
        $name = test_input($_POST["name"]);
        $email = test_input($_POST["email"]);
        $password = test_input($_POST["password"]);
        $model = test_input($_POST["model"]);
        $result = createUser($name,$email,$password,$model);
        if ($result) {
            $response = array(
                "message" => "User created successfully",
                "response" => "200"
            );
            echo json_encode($response, JSON_PRETTY_PRINT);
        } else {
            echo json_encode(array("message" => "No data found", "response" => "404"));
        }
    }

    // if($_SERVER["REQUEST_METHOD"] == "DELETE"){
    //     $id = test_input($_DELETE["id"]);
    //     $result = deleteUser($id);
    //     if ($result) {
    //         $response = array(
    //             "message" => "User deleted successfully",
    //             "response" => "200"
    //         );
    
    //         echo json_encode($response, JSON_PRETTY_PRINT);
    //     } else {
    //         echo json_encode(array("message" => "No data found", "response" => "404"));
    //     }
    // }

    // if($_SERVER["REQUEST_METHOD"] == "PUT"){
    //     $id = test_input($_PUT["id"]);
    //     $name = test_input($_PUT["name"]);
    //     $email = test_input($_PUT["email"]);
    //     $password = test_input($_PUT["password"]);
    //     $model = test_input($_PUT["model"]);
    //     $result = updateUser($id,$name,$email,$password,$model);
    //     if ($result) {
    //         $response = array(
    //             "message" => "User updated successfully",
    //             "response" => "200"
    //         );
    
    //         echo json_encode($response, JSON_PRETTY_PRINT);
    //     } else {
    //         echo json_encode(array("message" => "No data found", "response" => "404"));
    //     }
    // }

    function test_input($data) {
        $data = trim($data);
        $data = stripslashes($data);
        $data = htmlspecialchars($data);
        return $data;
    }
?>