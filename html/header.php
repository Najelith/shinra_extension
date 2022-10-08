<?php
/*
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);
*/
include 'lib/sqldata.php';
include 'lib/db/odbc.php';
include 'functions.php';

$SQL = new db;
$result = $SQL->open($database_server['database'], $database_server['hostname'], $database_server['username'], $database_server['password']);

if (!$result) {
        show_dberror('Could Not Connect To Database');
}

// get users online

    $query_getusercount = new query($SQL, "SELECT * FROM CURRENTUSER");
    
$intuser = $query_getusercount->affected();

    //  while($query_getusercount->fetch()) {

		//$nnm = $query_getusercount->field('nAccounID');
	//	$intuser++;
	//}
if(!isset($_POST))
{
 extract($HTTP_POST_VARS);
 extract($HTTP_GET_VARS);
 extract($HTTP_COOKIE_VARS);
 extract($HTTP_ENV_VARS);
 extract($HTTP_SERVER_VARS);
}
else{
 extract($_POST);
 extract($_GET);
 extract($_COOKIE);
 extract($_ENV);
 extract($_SERVER);
}

error_reporting(7); 
?>