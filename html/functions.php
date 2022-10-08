<?php

function dec2hex($number, $length) { 
  $hexval=""; 
  while ($number>0) { 
   $remainder=$number%16; 
   if ($remainder<10) 
     $hexval=$remainder.$hexval; 
   elseif ($remainder==10) 
     $hexval="a".$hexval; 
   elseif ($remainder==11) 
     $hexval="b".$hexval; 
   elseif ($remainder==12) 
     $hexval="c".$hexval; 
   elseif ($remainder==13) 
     $hexval="d".$hexval; 
   elseif ($remainder==14) 
     $hexval="e".$hexval; 
   elseif ($remainder==15) 
     $hexval="f".$hexval; 
   $number=floor($number/16); 
  } 
  while (strlen($hexval)<$length) $hexval="0".$hexval; 
//this is just to add zero's at the beginning to make hexval a certain length 
  return $hexval; 
} 

function genwithdraw($mess){ 
include 'templates/withdraw.php';
}


function gendeposit($mess){ 
include 'templates/deposit.php';
}


function genlogin($mess){ 
include 'templates/login.php';
}

function genmain($mess){ 
include 'templates/main.php';
}

function gennormal($accnum,$balance,$money,$nn1,$nn2,$nn3,$cc,$nnm){ 
include 'templates/normal.php';
}

function buildrow($action,$amount,$usrip,$stadate,$name){ 
include 'templates/staterow.php';
}

function stateheader(){
include 'templates/stateheader.php';
}


function statefooter(){
include 'templates/statefooter.php';                          
}

function outheader(){ 
include 'templates/outheader.php';
}

function outfooter(){
include 'templates/outfooter.php';                          
}

function buildoutrow($action,$amount,$usrip,$stadate,$fname,$tname,$orderof){ 
include 'templates/outrow.php';
}

function inheader(){ 
include 'templates/inheader.php';
}

function infooter(){
include 'templates/infooter.php';
}                         

function buildinrow($action,$amount,$usrip,$stadate,$fname,$tname,$orderof){ 
include 'templates/inrow.php';
}

function gennout($mess){ 
include 'templates/nout.php';
}
function buildguildrow($guildname,$guildclass,$strinfo,$leader,$win,$draw,$lose,$intpos){
include 'templates/guildrow.php';
}
function buildmonrow($guildname,$guildclass,$strinfo,$leader,$win,$draw,$lose,$MID){
include 'templates/monrow.php';
}
function guildheader(){ 
include 'templates/gheader.php';
}

function mlistheader(){ 
include 'templates/mlheader.php';
}

function guildfooter(){
include 'templates/gfooter.php';
}                         

function mheader($title,$subtitle,$descript){ 
include 'templates/header.php';
}
function mfooter($mess,$intuser,$hostname){ 
include 'templates/footer.php';
}
function monheader($title,$subtitle,$descript){ 
include 'templates/dhead.php';
}
function mondetail($monzonenum,$monname,$monclass,$montype,$monAI,$monmesh,$monmindam,$monlvl,$monexp,$monstr,$monadex,$monddex,$monint2,$monwis,$moncon,$monhp,$monmp,$monmoral,$monint,$monrange,$monmag1,$monmrate1,$monmag2,$monmrate2,$monmag3,$monmrate3,$monzone,$monminx,$monminy,$monmaxx,$monmaxy,$monspawn,$monminbarr,$monmaxbarr,$monchat1,$monchat2,$monchat3,$monirand1,$monirand2,$monirand3,$monirand4,$monirand5,$monirand6,$monirand7,$monirand8,$monirand9,$monirand10,$monirand11,$monirand12,$monirand13,$monirand14,$monirand15,$monitem1,$monitem2,$monitem3,$monitem4,$monitem5,$monitem6,$monitem7,$monitem8,$monitem9,$monitem10,$monitem11,$monitem12,$monitem13,$monitem14,$monitem15){
include 'templates/detail.php';
}

function buildncraftrow($iname,$ipic,$slottype,$needexp,$maxab,$metal,$wood,$leather,$bone,$cloth,$plant,$meat,$powder,$spice,$gem){
include 'templates/crow.php';
}

function buildscraftrow($iname,$ipic,$slottype,$needexp,$item1,$item2,$item3,$item4,$item5,$inum1,$inum2,$inum3,$inum4,$inum5){
include 'templates/scrow.php';
}

?>