<?php

include 'lib/sqldata.php';
include 'lib/db/odbc.php';
include 'functions.php';
$SQL = new db;
$result = $SQL->open($database_server['database'], $database_server['hostname'], $database_server['username'], $database_server['password']);

if (!$result) {
        show_dberror('Could Not Connect To Database');
}

// get users online
$query_getusercount = new query($SQL, "SELECT count(*) as icount  FROM CURRENTUSER");
$query_getusercount->fetch() ;
$intuser = $query_getusercount->field('icount');



$imgp = "./img/img.PNG";  // your background image
$im = imagecreatefrompng($imgp);
$stamp = imagecreatetruecolor(140, 70); //size of your infobox
$im = imagecreatefrompng($imgp);

error_reporting(0); 

$icount = 0;
$IP = array( 
"Login Server" => $database_server['hostname'].":4111",
"Session Server" => $database_server['hostname'].":4110",
"1p1 Server" => $database_server['hostname'].":22010", 
"Game Server" => $database_server['hostname'].":4120"); 
foreach ($IP as $ServerName => $Host){
 
list($IPAddress,$Port)=explode(":",$Host); 
 imagestring($stamp, 2, 1, $icount , $ServerName.": ", 0xFFFFFF);
if($fp=fsockopen($IPAddress,$Port,$ERROR_NO, $ERROR_STR ,(float)1.5)) { 

imagestring($stamp, 2 , 100,  $icount, "Online", 0x008000);
fclose($fp); 
} 
else { 
imagestring($stamp, 2, 100, $icount, "Maintainance", 0xBF0000 );
}  
$icount+=13;
}
imagestring($stamp, 2, 1, $icount , "Users online: ".$intuser, 0xFFFFFF);
$marge_right = 10;
$marge_bottom = 10;
$sx = imagesx($stamp);
$sy = imagesy($stamp);
imagecopymerge($im, $stamp, imagesx($im) - $sx - $marge_right, imagesy($im) - $sy - $marge_bottom, 0, 0, imagesx($stamp), imagesy($stamp), 50);
header('Content-Type: image/png');
imagesavealpha( $im, true );

imagepng($im);
imagedestroy($im);


?>