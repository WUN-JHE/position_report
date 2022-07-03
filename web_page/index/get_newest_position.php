<?php
    require_once('../mysql.php');
    if($_SERVER['REQUEST_METHOD']=='POST' && $_POST) 
    {
        $call_name=$_POST["call_name"];
        $sql="SELECT * FROM ".$call_name." ORDER BY id DESC";
        $result=$conn->query($sql);
        $js = array();
        if($result->num_rows > 0) {
            while($row = $result->fetch_assoc()) 
            {
                array_push($js,$row);
            }
        }

        print(json_encode($js,JSON_UNESCAPED_UNICODE));
    }
?>