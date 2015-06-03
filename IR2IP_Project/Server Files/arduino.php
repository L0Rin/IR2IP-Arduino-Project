<?php
 
 
 $response = array();
 echo "Welcome";
if ( 

$_REQUEST['code']

) {

  echo "Welcome ". $_REQUEST['code']. "<br />";
  
  $data = $_REQUEST['code'];
   // include db connect class
    require_once __DIR__ . '/db_connect.php';
   // connecting to db
    $db = new DB_CONNECT();
 
 $result = mysql_query("INSERT INTO mytable1(data1) VALUES('$data')");
 
 
 
	if ($result)
	 {
	 	 $response["status"] = "success";
      		  $response["message"] = "Success";
 		  // echoing JSON response
       		 echo json_encode($response);
	 }
	 else
	 {
	 	 $response["status"] = "fail";
      		  $response["message"] = $result;
 		  // echoing JSON response
       		 echo json_encode($response);
	 }
 }
?>