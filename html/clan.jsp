<?php

include 'header.php';

    $query_getdata = new query($SQL, "SELECT * FROM Guild");


//    headers
$mess = 'Guilds';
$title = 'Guilds';
$subtitle = 'Guilds';
$descript = 'Information and History Of Guilds';

mheader($title,$subtitle,$descript);
guildheader();



      while($query_getdata->fetch()) {

		$guildname = $query_getdata->field('strGuildName');
		$guildclass = $query_getdata->field('sGuildClass');
		if($guildclass == '0' ){
		$guildclass = "Human";
		}
		else{
		$guildclass = "Devil";
		}
		$strinfo = $query_getdata->field('strInfo');
		$gID = $query_getdata->field('GuildNum');
                $intpos = "0";

		//get guild pos
		    $query_getgpos = new query($SQL, "SELECT * FROM Guildrank WHERE Guildid ='".$gID."'");
		   
                while($query_getgpos->fetch()) {
		     $intpos = $query_getgpos->field('pos');
                }



		//get guild leader
		    $query_getleader = new query($SQL, "SELECT * FROM Guild_USER WHERE sGuild ='".$gID."' AND sRank ='1'");
		   
                while($query_getleader->fetch()) {
		     $leader = $query_getleader->field('strUserId');
                }
                // Get guild's wins and losses
                $query_getscore = new query($SQL, "SELECT * FROM Guild_War_Score WHERE strGuildName ='".$guildname."'");
                     while($query_getscore->fetch()) {
		                $win = $query_getscore->field('sWin');
		                $draw = $query_getscore->field('sDraw');
		                $lose = $query_getscore->field('sLose');
    	                }
		buildguildrow($guildname,$guildclass,$strinfo,$leader,$win,$draw,$lose,$intpos);
		         // reinit
		      	    $win = 0;
		                $draw = 0;
		                $lose = 0;
     

	}
// footers
guildfooter();
mfooter($mess,$intuser,$database_server['hostname']);


?>


