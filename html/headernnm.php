<?php 
/*
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);
*/
if (session_status() == PHP_SESSION_NONE) {
    session_start();
	
}

/*session is started if you don't write this line can't use $_Session  global variable*/

include 'lib/db/pdo.php';
include 'lib/sqldata.php';
include 'lib/db/odbc.php';
include 'functions.php';
/*
if(!isset($_SESSION))
{
 extract($HTTP_POST_VARS);
 extract($HTTP_GET_VARS);
 extract($HTTP_COOKIE_VARS);
 extract($HTTP_ENV_VARS);
 extract($HTTP_SERVER_VARS);
 extract($HTTP_SESSION_VARS);
}
else{
 extract($_POST);
 extract($_GET);
 extract($_COOKIE);
 extract($_ENV);
 extract($_SERVER);
 extract($_SESSION); 
} 
*/
$SQL = new db;
$result = $SQL->open($database_server['database'], $database_server['hostname'], $database_server['username'], $database_server['password']);

if (!$result) {
        show_dberror('Could Not Connect To Database');
}





// check to see if session exists
// assumes $_SESSION[nnm] was previously defined login
switch (!($_SESSION["nnm"] == '')) {
     case TRUE:
        // do nothing
           break;
     case FALSE:
		 //  $_SESSION[nnm] = test;
         //  echo $_SESSION[nnm];
		   header("Location: http://".$database_server['hostname']."/login.jsp");
           exit;
           break;
}



?>