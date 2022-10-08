<?php

include 'header.php';

   // $query_getdata = new query($SQL, "SELECT * FROM [dbo].[moninf]");
    //WHERE name LIKE '".$s."%' for later searches and display by zone/letters.
//    headers
$mess = 'Monster List';
$title = 'Monster List';
$subtitle = 'Monster List';
$descript = 'Detail and sorting order options coming soon..';

mheader($title,$subtitle,$descript);
mlistheader();
getdata(5544,1);

function getdata($q,$count){
      if($count < 1222 ){

          // get data monsterset
		    
		    $xcords = "Devil";
		    $ycords = "Devil";
                    $MID = "Devil";
                    $MonID= "Devil";
                
                $q = $q + 1972;
		//get name and such 
                $name1 = dechex($q);
                $namelen = strlen($name1);
                if($namelen == 4){
                $name2 = substr($name1, -2); 
                $name3 = substr($name1,-4, 2);
                $name = $name2.$name3."0000";
                }
		//len = 5
		else if($namelen == 5){
                $name2 = substr($name1, -2); 
                $name3 = substr($name1,-4, 2);
                $name4 = substr($name1,-5, 1);
                $name = $name2.$name3."0".$name4."00";
                }
		//len = 6
		else if($namelen == 6){
                $name2 = substr($name1, -2); 
                $name3 = substr($name1,-4, 2);
                $name4 = substr($name1,-6, 2);
                $name = $name2.$name3.$name4."00";
                }
                else{
		$name= "null";
                }
	
		$sclass = "devil";
		$count++;
		$zone = $count;
		$mlvl = "";
		$micon =""; 
               
		echo $name;
     // recursive call 
     getdata($q,$count);

	}
//else do nothing

}



// footers
guildfooter();
mfooter($mess,$intuser);


?>


