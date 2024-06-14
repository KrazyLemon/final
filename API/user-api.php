<?php
    include_once('user-database');
    IF($_SERVER[$_REQUEST_METHOD]== "POST"){
        $name = test_input($_POST["name"]);
        $email = test_input($_POST["email"]);
        $password = test_input($_POST["password"]);
        $result = createUser($name,$email,$password);
        echo $result;
    }else{
        echo "No se Creo el Usuario";
    }
    IF($_SERVER[$_REQUEST_METHOD=="DELETE"]){
        $id = test_input($_DELETE["id"]);
        $result = deleteUser($id);
        echo $result;
    }else{
        echo "No se eleimino el usuario";
    }
    IF($_SERVER[$_REQUEST_METHOD=="PUT"]){
        $id = test_input($_PUT["id"]);
        $name = test_input($_PUT["name"]);
        $email = test_input($_PUT["email"]);
        $password = test_input($_PUT["password"]);
        $result = updateUser($id,$name,$email,$password);
        echo $result;
    }else{
        echo "No se actualizo el usuario";
    }

?>