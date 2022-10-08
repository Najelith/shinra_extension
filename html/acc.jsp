<?php

include 'headernnm.php';

$nnm = $_SESSION["nnm"];
//$banker = $_SESSION[disa];

//strip inputs
$nnm = str_replace('"', '', str_replace("'", "", str_replace(',', '', str_replace(';', '', $nnm))));
$nn1 =  str_replace('"', '', str_replace("'", "", str_replace(',', '', str_replace(';', '', $_POST["nn1"]))));
$acmail =  str_replace('"', '', str_replace("'", "", str_replace(',', '', str_replace(';', '', $_POST["acmail"]))));
$acpc =  str_replace('"', '', str_replace("'", "", str_replace(',', '', str_replace(';', '', $_POST["acpc"]))));
$addr1 =  str_replace('"', '', str_replace("'", "", str_replace(',', '', str_replace(';', '', $_POST["addr1"]))));
$acpw =  str_replace('"', '', str_replace("'", "", str_replace(',', '', str_replace(';', '', $_POST["acpw"]))));
//$hidden = $_POST[hidden]; # to be implemented later.
$send = $_POST["send"];
$fmess = 'Account';
$title = 'Account';
$subtitle = 'Account Management';
$descript = 'Edit Personal Info..';


if (!$send) {
            
                
                $query_getacc = new query($SQL, "SELECT strName , strEmail , strPostalCode , strAddr1, timeReg, timeLog FROM NGSCUSER WHERE strUserId = '".$nnm."'"); 
                
                 $query_getacc->fetch();
                 $oaccnm = $query_getacc->field('strName');
                 $oaccmail = $query_getacc->field('strEmail');
                 $oacpc = $query_getacc->field('strPostalCode');
                 $oaddr1 = $query_getacc->field('strAddr1');
                 $regtime = $query_getacc->field('timeReg');
                 $lastlog = $query_getacc->field('timeLog');
                        $_SESSION["regtime"] =$regtime;
						$_SESSION["lastlog"] =$lastlog;
       mheader($title,$subtitle,$descript);
       buildform($mess,$oaccnm,$oaccmail,$oacpc,$oaddr1,$regtime,$lastlog);
       // get users online

    $query_getusercount = new query($SQL, "SELECT * FROM CURRENTUSER");
    
$intuser = 0;

      while($query_getusercount->fetch()) {

		//$nnm2 = $query_getusercount->field('nAccounID');
		$intuser++;
	}
       mfooter($fmess,$intuser,$database_server['hostname']);
     }

        // ### Set User to logged in
        elseif ($send) {
trim($pin);

                if ($nn1 == '' || $acmail == '' ||  $addr1 == '' || $acpw == '') { 
                
                   mheader($title,$subtitle,$descript);
                   buildform('Please Fill in required Fields!',$nn1,$acmail,$acpc,$addr1,$_SESSION["regtime"],$_SESSION["lastlog"]);
                          // get users online
       
    $query_getusercount = new query($SQL, "SELECT * FROM CURRENTUSER");
    
$intuser = 0;

      while($query_getusercount->fetch()) {

		//$nnm2 = $query_getusercount->field('nAccounID');
		$intuser++;
	}
                   mfooter($fmess,$intuser,$database_server['hostname']); 
                     exit; 
                }
               // $query_checkdata = new query($SQL, "SELECT * FROM Member WHERE Nickname_To_Lower='".$nnm."' AND Pin='".$pin."'");
                
       //         $query_checkbanker = new query($SQL, "SELECT * FROM Member WHERE Nickname_To_Lower='".$nnm."' AND Pin='".$pin."' AND Banker='1'");

           //     $query_checkacc = new query($SQL, "SELECT * FROM Bank WHERE  Accnumb != '".$accnumb."'");  
           //     if ($query_checkbanker->getrow() && $query_checkacc->getrow()) { 
           //      $pin = $query_checkbanker->field('Pin');
           //      $accnum = $query_checkacc->field('Accnumb');
           //      $banker = $query_checkbanker->field('Banker');
          new query($SQL, "UPDATE NGSCUSER SET strPasswd = '".$acpw."', strName = '".$nn1."', strEmail = '".$acmail."', strPostalCode = '".$acpc."', strAddr1 = '".$addr1."' WHERE strUserId = '".$nnm."'");
mheader($title,$subtitle,$descript);
                 echo "Account updated!";
mfooter($fmess,$intuser,$database_server['hostname']);
        
                 exit;
              //   }
              //   elseif(!$query_checkdata->getrow() || !$query_checkacc->getrow()){
              //   $mess ="Access Denied!";
               // buildform($mess); 
               // exit;
               // }

        }
                                   


function buildform($mess,$name,$mail,$pc,$addr1,$regtime,$lastlog){ ?>
 <Center>   
 <?= $mess ?>
<form method="POST" action="acc.jsp">
<table>
<input type="hidden" Name="send" Value="1" >
<tr><td style="border:0px solid blue;">Name:*</td><td style="border:0px solid blue;"><input type="text" Value="<?= $name ?>" Name="nn1" onblur="style.backgroundColor=''; style.color=''" onfocus="style.backgroundColor='Silver'; style.color='Navy'" onmouseover="style.backgroundColor=''; style.color='gold'" onmouseout="style.backgroundColor=''; style.color=''"></td></tr>
<tr><td style="border:0px solid blue;">New Password:*</td><td style="border:0px solid blue;"><input type="Password" Value="" Name="acpw" onblur="style.backgroundColor=''; style.color=''" onfocus="style.backgroundColor='Silver'; style.color='Navy'" onmouseover="style.backgroundColor=''; style.color='gold'" onmouseout="style.backgroundColor=''; style.color=''"></td></tr>
<tr><td style="border:0px solid blue;">E-Mail:*</td><td style="border:0px solid blue;"><input type="text" Value="<?= $mail ?>" Name="acmail" onblur="style.backgroundColor=''; style.color=''" onfocus="style.backgroundColor='Silver'; style.color='Navy'" onmouseover="style.backgroundColor=''; style.color='gold'" onmouseout="style.backgroundColor=''; style.color=''"></td></tr>
<tr><td style="border:0px solid blue;">Postal Code:</td><td style="border:0px solid blue;"><input type="text" Value="<?= $pc ?>" Name="acpc" onblur="style.backgroundColor=''; style.color=''" onfocus="style.backgroundColor='Silver'; style.color='Navy'" onmouseover="style.backgroundColor=''; style.color='gold'" onmouseout="style.backgroundColor=''; style.color=''"></td></tr>
<tr><td style="border:0px solid blue;">Address 1:*</td><td style="border:0px solid blue;"><input type="text" Value="<?= $addr1 ?>" Name="addr1" onblur="style.backgroundColor=''; style.color=''" onfocus="style.backgroundColor='Silver'; style.color='Navy'" onmouseover="style.backgroundColor=''; style.color='gold'" onmouseout="style.backgroundColor=''; style.color=''"></td></tr>
<tr><td style="border:0px solid blue;">Registration Date:</td><td style="border:0px solid blue;"><?= $regtime ?></td></tr>
<tr><td style="border:0px solid blue;">Last Login Date:</td><td style="border:0px solid blue;"><?= $lastlog ?></td></tr>
</table>
<Center>
<input type="submit" value="     Update     "  onblur="style.backgroundColor=''; style.color=''" onfocus="style.backgroundColor='Silver'; style.color='Navy'" onmouseover="style.backgroundColor=''; style.color='gold'" onmouseout="style.backgroundColor=''; style.color=''">

<input type="reset" value="     Clear     " name="clear" onblur="style.backgroundColor=''; style.color=''" onfocus="style.backgroundColor='Silver'; style.color='Navy'" onmouseover="style.backgroundColor=''; style.color='gold'" onmouseout="style.backgroundColor=''; style.color=''"></center>


</form>
</Center>

<?php
}

#	$query_users = new query($SQL, 'SELECT * FROM Member ORDER BY Nickname');
#while($query_users->fetch()) {

#		$NNM = $query_users->field('Nickname');
 #echo "$NNM<br>\n";

#	}

?>


