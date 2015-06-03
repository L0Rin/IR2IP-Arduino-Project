**Server Part**  
Server part contains the receiving codes from Arduino. For posting the data here we are using the get request.
Code is written in such a way that both Get and Post request can be used for posting data to server.
GET - Requests data from a specified resource
POST - Submits data to be processed to a specified resource
Also it receives the data on server and insert the IR codes in database.
Php code which recives the IR codes is in the project with the name arduino.php.
Also you can create own php file and copy the code. Below is the recieving php arduino code
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
This code also give server response about success and fails, Server response is int jSon format.  
For insersion in database mysql is used. There are two other files which are used to configure and connect to databases.  
 
**Code for database connection**  
 <?php  
class DB_CONNECT {  
    // constructor  
    function __construct() {  
        // connecting to database  
        $this->connect();  
    }  
    // destructor  
    function __destruct() {  
        // closing db connection   
        $this->close();  
    }  
 
    function connect() {  
        // import database connection variables  
        require_once __DIR__ . '/db_config.php';  
       
        // Connecting to mysql database  
        $con = mysql_connect(DB_SERVERR, DB_USERR, DB_PASSWORDD) or die(mysql_error());  
 
        // Selecing database  
        $db = mysql_select_db(DB_DATABASEE) or die(mysql_error()) or die(mysql_error());  
 
        // returing connection cursor
        return $con;  
    }  
    function close() {  
        // closing db connection  
        mysql_close();  
    }  
 
}  
?>  
 
 **Code for Configure Database**  
 <?php  
 
 // All database connection variables  
 
 error_reporting(-1);  
 
define('DB_USERR', "sajjad_appuser"); // db user  
define('DB_PASSWORDD', ",d(MTvFTTm^V"); // db password (mention your db password here)  
define('DB_DATABASEE', "sajjad_iosapp"); // database name  
define('DB_SERVERR', "localhost"); // db server  
?>  
These files are also avialable in project.  
