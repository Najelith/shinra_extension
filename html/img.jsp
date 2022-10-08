<?php

// validate inputs
$zone = intval($_GET['zone']);
$maxx = intval($_GET['maxx']);
$minx = intval($_GET['minx']);
$maxy = intval($_GET['maxy']);
$miny = intval($_GET['miny']);
$name = str_replace('"', '', str_replace("'", "", str_replace(',', '', str_replace(';', '', $_GET['name']))));

$ratiox = 0.88967971530249110320284697508897;
$ratioy = 0.4439655172413793103448275862069;

$imgp = "./img/".$zone.".png";

//$imgp = './img/1.png';
// Load the stamp and the photo to apply the watermark to
$im = imagecreatefrompng($imgp);

// First we create our stamp image manually from GD
$stamp = imagecreatetruecolor(100, 70);
imagefilledrectangle($stamp, 0, 0, (($maxx*$ratiox)-($minx*$ratiox)),(($maxy*$ratioy)-($miny*$ratioy)), 0x0000FF);
//imagefilledrectangle($stamp, 9, 9, 90, 60, 0xFFFFFF);
$im = imagecreatefrompng($imgp);
imagestring($stamp, 5, 20, 20, $name, 0xFFFFFF);
//imagestring($im, 3, 20, 40, 'zone'.$zone, 0x0000FF);


// Set the margins for the stamp and get the height/width of the stamp image
$marge_right = 10;
$marge_bottom = 10;
$sx = imagesx($stamp);
$sy = imagesy($stamp);

// Merge the stamp onto our photo with an opacity (transparency) of 50%
//imagecopymerge($im, $stamp, imagesx($im) - $sx - $marge_right, imagesy($im) - $sy - $marge_bottom, 0, 0, imagesx($stamp), imagesy($stamp), 50);
imagecopymerge($im, $stamp, $minx*$ratiox, $miny*$ratioy, 0, 0, $sx ,$sy, 50);

// Save the image to file and free memory
//imagepng($im, 'photo_stamp.png');
header('Content-Type: image/png');


// Make the background transparent
//imagealphablending( $im, false );
imagesavealpha( $im, true );

imagepng($im);
imagedestroy($im);


// tiger helm island
?>