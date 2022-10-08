<?php

include 'header.php';


//    headers
$fmess = 'Monster Detail';
$title = 'Monster Detail';
$subtitle = 'Monster Detail';
$descript = 'Information';
//strip any none int chars
$id = intval($id);

 if (!$id) {
                 monheader($title,$subtitle,$descript);
        
        mfooter($fmess,$intuser,$database_server['hostname']);
     }

        // ### get the monster's info
        elseif ($id) {
        
        $query_getdata = new query($SQL, "SELECT * FROM [dbo].[mondetail] WHERE id ='".$id."'");
                        if($query_getdata->fetch()) {

		$monname = $query_getdata->field('name');
$fmess = "Monster Detail->".$monname;
$title = "Monster Detail->".$monname;
$subtitle = "Monster Detail->".$monname;	
monheader($title,$subtitle,$descript);

      

		$monclass = $query_getdata->field('class');
		$montype = $query_getdata->field('type');
		$monAI = $query_getdata->field('sTypeAI');
		$monmesh = $query_getdata->field('pic');
		$monmindam = $query_getdata->field('sMinDamage');
		$monlvl = $query_getdata->field('lvl');
		$monexp = $query_getdata->field('iMaxExp');
		$monstr = $query_getdata->field('sStr');
		$monadex = $query_getdata->field('sDex_at');
		$monddex = $query_getdata->field('sDex_df');
		$monwis = $query_getdata->field('sWis');
		$moncon = $query_getdata->field('sCon');
		$monhp = $query_getdata->field('sMaxHp');
		$monmp = $query_getdata->field('sMaxMp');
		$monmoral = $query_getdata->field('iMoral');
		$monint = $query_getdata->field('sIntel');
		$monrange = $query_getdata->field('sDistance');
		$monmag1 = $query_getdata->field('Magic1');
		$monmrate1 = $query_getdata->field('sMagicRate01');
		
		if ($monmag1 == '-1'){
		$monmag1 = "None";
		}

		$monmag2 = $query_getdata->field('Magic2');
		$monmrate2 = $query_getdata->field('sMagicRate02');

		if ($monmag2 == '-1'){		
		$monmag2 = "None";
		}

		$monmag3 = $query_getdata->field('Magic3');
		$monmrate3 = $query_getdata->field('sMagicRate03');

		if ($monmag3 == '-1'){
		$monmag3 = "None";
		}
		
		if($monclass == '0' ){
		$monclass = "Human";
		}
		else{
		$monclass = "Devil";
		}

                // Get drop info and rates, location spawns, 
                //$query_getdata = new query($SQL, "SELECT * FROM monsterset WHERE sTableNum ='".$id."'");
               // while($query_getdata->fetch()) {
                $monzonenum = $query_getdata->field('zone');
                $query_getzone = new query($SQL, "SELECT * FROM Zones WHERE ZoneID ='".$monzonenum."'");
                while($query_getzone->fetch()) {
                $monzone = $query_getzone->field('name');
                }
                $monminx = $query_getdata->field('minx');
                $monminy = $query_getdata->field('miny');
                $monmaxx = $query_getdata->field('maxx');
                $monmaxy = $query_getdata->field('maxy');
                $monspawn = $query_getdata->field('sRegenTime');
                $monminbarr = $query_getdata->field('sMoneyMin');
                $monmaxbarr = $query_getdata->field('sMoneyMax');
                $monchat1 = $query_getdata->field('sChat01');
                $monchat2 = $query_getdata->field('sChat02');
                $monchat3 = $query_getdata->field('sChat03');
                $monirand1 = $query_getdata->field('sItem01Rand');
                $monirand2 = $query_getdata->field('sItem02Rand');
                $monirand3 = $query_getdata->field('sItem03Rand');
                $monirand4 = $query_getdata->field('sItem04Rand');
                $monirand5 = $query_getdata->field('sItem05Rand');
                $monirand6 = $query_getdata->field('sItem06Rand');
                $monirand7 = $query_getdata->field('sItem07Rand');
                $monirand8 = $query_getdata->field('sItem08Rand');
                $monirand9 = $query_getdata->field('sItem09Rand');
                $monirand10 = $query_getdata->field('sItem10Rand');
                $monirand11 = $query_getdata->field('sItem11Rand');
                $monirand12 = $query_getdata->field('sItem12Rand');
                $monirand13 = $query_getdata->field('sItem13Rand');
                $monirand14 = $query_getdata->field('sItem14Rand');
                $monirand15 = $query_getdata->field('sItem15Rand');
                
                $monitem[1] = $query_getdata->field('sItem01'); 
                $monitem1gen = $query_getdata->field('Gender01');
                
                if($monitem1gen == '1'){
                $monitem1gen = "(M)";
                }
                if($monitem1gen == '2'){
                $monitem1gen = "(F)";
                }
                if($monitem1gen == '0'){
                $monitem1gen = "";
                }    

                $monitem[2] = $query_getdata->field('sItem02');
                $monitem2gen = $query_getdata->field('Gender02');


                if($monitem2gen == '1'){
                $monitem2gen = "(M)";
                }
                if($monitem2gen == '2'){
                $monitem2gen = "(F)";
                }
                if($monitem2gen == '0'){
                $monitem2gen = "";
                }  

                $monitem[3] = $query_getdata->field('sItem03');
                $monitem3gen = $query_getdata->field('Gender03');
                
                if($monitem3gen == '1'){
                $monitem3gen = "(M)";
                }
                if($monitem3gen == '2'){
                $monitem3gen = "(F)";
                }
                if($monitem3gen == '0'){
                $monitem3gen = "";
                }  

                $monitem[4] = $query_getdata->field('sItem04');
                $monitem4gen = $query_getdata->field('Gender04');
                
                if($monitem4gen == '1'){
                $monitem4gen = "(M)";
                }
                if($monitem4gen == '2'){
                $monitem4gen = "(F)";
                }
                if($monitem4gen == '0'){
                $monitem4gen = "";
                }  

                $monitem[5] = $query_getdata->field('sItem05'); 
                $monitem5gen = $query_getdata->field('Gender05');
                
                if($monitem5gen == '1'){
                $monitem5gen = "(M)";
                }
                if($monitem5gen == '2'){
                $monitem5gen = "(F)";
                }
                if($monitem5gen == '0'){
                $monitem5gen = "";
                }  

                $monitem[6] = $query_getdata->field('sItem06');
                $monitem6gen = $query_getdata->field('Gender06');
                
                if($monitem6gen == '1'){
                $monitem6gen = "(M)";
                }
                if($monitem6gen == '2'){
                $monitem6gen = "(F)";
                }
                if($monitem6gen == '0'){
                $monitem6gen = "";
                }  

                $monitem[7] = $query_getdata->field('sItem07');
                $monitem7gen = $query_getdata->field('Gender07');
                
                if($monitem7gen == '1'){
                $monitem7gen = "(M)";
                }
                if($monitem7gen == '2'){
                $monitem7gen = "(F)";
                }
                if($monitem7gen == '0'){
                $monitem7gen = "";
                }  

                $monitem[8] = $query_getdata->field('sItem08');
                $monitem8gen = $query_getdata->field('Gender08');
                
                if($monitem8gen == '1'){
                $monitem8gen = "(M)";
                }
                if($monitem8gen == '2'){
                $monitem8gen = "(F)";
                }
                if($monitem8gen == '0'){
                $monitem8gen = "";
                } 
 
                $monitem[9] = $query_getdata->field('sItem09');
                $monitem9gen = $query_getdata->field('Gender09');
                

                if($monitem9gen == '1'){
                $monitem9gen = "(M)";
                }
                if($monitem9gen == '2'){
                $monitem9gen = "(F)";
                }
                if($monitem9gen == '0'){
                $monitem9gen = "";
                }  

                $monitem[10] = $query_getdata->field('sItem10');
                
                $monitem10gen = $query_getdata->field('Gender10');
                
                if($monitem10gen == '1'){
                $monitem10gen = "(M)";
                }
                if($monitem10gen == '2'){
                $monitem10gen = "(F)";
                }
                if($monitem10gen == '0'){
                $monitem10gen = "";
                }
  
                $monitem[11] = $query_getdata->field('sItem11');
                $monitem11gen = $query_getdata->field('Gender11');
                

                if($monitem11gen == '1'){
                $monitem11gen = "(M)";
                }
                if($monitem11gen == '2'){
                $monitem11gen = "(F)";
                }
                if($monitem11gen == '0'){
                $monitem11gen = "";
                }  

                $monitem[12] = $query_getdata->field('sItem12');
                $monitem12gen = $query_getdata->field('Gender12');
                
                if($monitem12gen == '1'){
                $monitem12gen = "(M)";
                }
                if($monitem12gen == '2'){
                $monitem12gen = "(F)";
                }
                if($monitem12gen == '0'){
                $monitem12gen = "";
                }  

                $monitem[13] = $query_getdata->field('sItem13');
                $monitem13gen = $query_getdata->field('Gender13');
                 
                if($monitem13gen == '1'){
                $monitem13gen = "(M)";
                }
                if($monitem13gen == '2'){
                $monitem13gen = "(F)";
                }
                if($monitem13gen == '0'){
                $monitem13gen = "";
                }  

                $monitem[14] = $query_getdata->field('sItem14');
                $monitem14gen = $query_getdata->field('Gender14');
                
                if($monitem14gen == '1'){
                $monitem14gen = "(M)";
                }
                if($monitem14gen == '2'){
                $monitem14gen = "(F)";
                }
                if($monitem14gen == '0'){
                $monitem14gen = "";
                }  

                $monitem[15] = $query_getdata->field('sItem15');
                $monitem15gen = $query_getdata->field('Gender15');
                

                if($monitem15gen == '1'){
                $monitem15gen = "(M)";
                }
                else if($monitem15gen == '2'){
                $monitem15gen = "(F)";
                }
                else {
                $monitem15gen = "";
                }  
				for ($i = 1; $i <= 16; $i++) {
				// normal item
				if( $monitem[$i] < 10000){
				  $query_getidata[$i] = new query($SQL, "SELECT * FROM BASICITEM WHERE sNum ='".$monitem[$i]."'");
			if($query_getidata[$i]->fetch()){
                $monitem[$i] = $query_getidata[$i]->field('strName');
                
                }
				}
				//special item
				else{
					if( $monitem[$i] > 10000){
					$monitem[$i] = $monitem[$i] - 10000;
				  $query_getidata[$i] = new query($SQL, "SELECT * FROM BASICITEM WHERE sNum ='".$monitem[$i]."'");
			if($query_getidata[$i]->fetch()){
                $monitem[$i] = $query_getidata[$i]->field('strName');
				$monitem[$i] = "<font style='color:#FFCC33'>[S]</font>".$monitem[$i];
                
                }
				}
				}
				
				}
}
	
mondetail($monzonenum,$monname,$monclass,$montype,$monAI,$monmesh,$monmindam,$monlvl,$monexp,$monstr,$monadex,$monddex,$monint2,$monwis,$moncon,$monhp,$monmp,$monmoral,$monint,$monrange,$monmag1,$monmrate1,$monmag2,$monmrate2,$monmag3,$monmrate3,$monzone,$monminx,$monminy,$monmaxx,$monmaxy,$monspawn,$monminbarr,$monmaxbarr,$monchat1,$monchat2,$monchat3,$monirand1,$monirand2,$monirand3,$monirand4,$monirand5,$monirand6,$monirand7,$monirand8,$monirand9,$monirand10,$monirand11,$monirand12,$monirand13,$monirand14,$monirand15,$monitem[1],$monitem[2],$monitem[3],$monitem[4],$monitem[5],$monitem[6],$monitem[7],$monitem[8],$monitem[9],$monitem[10],$monitem[11],$monitem[12],$monitem[13],$monitem[14],$monitem[15]);

// footers
mfooter($fmess,$intuser,$database_server['hostname']); 

   }


?>


