<?php

include 'header.php';

    $query_getdata = new query($SQL, "SELECT * FROM [dbo].[moninf]");
    //WHERE name LIKE '".$s."%' for later searches and display by zone/letters.
//    headers
$mess = 'Monster List';
$title = 'Monster List';
$subtitle = 'Monster List';
$descript = 'Detail and sorting order options coming soon..';

mheader($title,$subtitle,$descript);
mlistheader();
getdata($query_getdata);

function getdata($q){
      if($q->fetch()) {


          // get data monsterset
		    $zone = $q->field('zone');
		    $xcords = $q->field('minx') ." ~ ".$q->field('maxx');
		    $ycords = $q->field('miny') ." ~ ".$q->field('maxy');
                    $MID = $q->field('mid');
                    $MonID= $q->field('id');

		//get name and such 
                $name = $q->field('name');
		$sclass = $q->field('class');
		if($sclass == '0' ){
		$sclass = "Human";
		}
		else{
		$sclass = "Devil";
		}
		$mlvl = $q->field('lvl');
		$micon = $q->field('pic');  
               
		buildmonrow($name,$sclass,$mlvl,$micon,$zone,$xcords,$ycords,$MonID);
     // recursive call 
     getdata($q);

	}
//else do nothing

}



// footers
guildfooter();
mfooter($mess,$intuser,$database_server['hostname']);


?>


