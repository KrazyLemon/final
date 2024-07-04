<?php
    include_once('esp-database.php');

    $action = $id = $name = $gpio = $state = "";
    
    if ($_SERVER["REQUEST_METHOD"] == "GET") {
        $action = test_input($_GET["action"]);
        if ($action == "outputs_state") {
            $board = test_input($_GET["board"]);
            $result = getAllOutputStates($board);
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
        else if ($action == "output_update") {
            $id = test_input($_GET["id"]);
            $state = test_input($_GET["state"]);
            $result = updateOutput($id, $state);
            if($result){
                $response = array(
                    "message" => "Output state updated successfully",
                    "response" => "200"
                );
                echo json_encode($response, JSON_PRETTY_PRINT);
            }
            else {
                echo json_encode(array("message" => "Error: " , "response" => "404"));
            }
        }
        else {
            echo "Invalid HTTP request.";
        }
    }

    function test_input($data) {
        $data = trim($data);
        $data = stripslashes($data);
        $data = htmlspecialchars($data);
        return $data;
    }
?>