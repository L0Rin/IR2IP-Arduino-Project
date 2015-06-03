<?php
 
/**
 * A class file to connect to database
 */
 

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
 
    /**
     * Function to connect with database
     */
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
 
    /**
     * Function to close db connection
     */
    function close() {
        // closing db connection
        mysql_close();
    }
 
}
 
?>