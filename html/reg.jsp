<?php

include 'header.php';
$fmess = 'Registration';
$title = 'Registration';
$subtitle = 'Registration';
$descript = 'New Account';



if (!intval($send)) {
       mheader($title,$subtitle,$descript);
       buildform($mess);
       mfooter($fmess,$intuser,$database_server['hostname']);
     }
/*
fields
strUserId,
strPasswd,
wSerial,
strName,
strSocNo,
strEmail,
strPostalCode,
strAddr1,
strAddr2,
strPhoneNo,
strHandNo,
strQuery1,
strReply1,
strQuery2,
strReply2,
*/

        // ### Set User to logged in
        elseif (intval($send)) {
// strip inputs
$annm = str_replace('"', '', str_replace("'", "", str_replace(',', '', str_replace(';', '', $annm))));
$pwd = str_replace('"', '', str_replace("'", "", str_replace(',', '', str_replace(';', '', $pwd))));
$wser = intval($wser);
$nnm = str_replace('"', '', str_replace("'", "", str_replace(',', '', str_replace(';', '', $nnm))));
$socno = intval($socno);
$mail = str_replace('"', '', str_replace("'", "", str_replace(',', '', str_replace(';', '', $mail))));
$pscode = intval($pscode);
$addr1 = str_replace('"', '', str_replace("'", "", str_replace(',', '', str_replace(';', '', $addr1))));
$addr2 = str_replace('"', '', str_replace("'", "", str_replace(',', '', str_replace(';', '', $addr2))));
$phone = intval($phone);
$cell = intval($cell);
$qry1 = str_replace('"', '', str_replace("'", "", str_replace(',', '', str_replace(';', '', $qry1))));
$rpl1 = str_replace('"', '', str_replace("'", "", str_replace(',', '', str_replace(';', '', $rpl1))));
$qry2 = str_replace('"', '', str_replace("'", "", str_replace(',', '', str_replace(';', '', $qry2))));
$rpl2 = str_replace('"', '', str_replace("'", "", str_replace(',', '', str_replace(';', '', $rpl2))));

                if ($annm == '' || $nnm == '' ||  $mail == '' || $pwd == '' || $addr1 == '' || $rpl2 == '' ){
//|| $activ == '') { 
                       mheader($title,$subtitle,$descript);
                       buildform('Please Fill in ALL Fields!');
                       mfooter($fmess,$intuser,$database_server['hostname']);
                      
                     exit; 
                }

else{
                // query to check  activation code
               // $query_checkcode = new query($SQL, "SELECT * FROM regcodes WHERE regcode='".$activ."' AND intusage='0'");

			   
                $query_checkacc = new query($SQL, "SELECT * FROM NGSCUSER WHERE strUserId = '".$annm."'");  
                if (!$query_checkacc->getrow()) { 
          new query($SQL, "INSERT into NGSCUSER ( strUserId,strPasswd,wSerial,strName,strSocNo,strEmail,strPostalCode,strAddr1,strAddr2,strPhoneNo,strHandNo,strQuery1,strReply1,strQuery2,strReply2) VALUES ('".$annm."','".$pwd."','".$wser."','".$nnm."','".$socno."','".$mail."','".$pscode."','".$addr1."','".$addr2."','".$phone."','".$cell."','".$qry1."','".$rpl1."','".$qry2."','".$rpl2."')");
          //new query($SQL, "UPDATE regcodes SET intusage = '1' WHERE regcode = '".$activ."'");
		mheader($title,$subtitle,$descript);
                 echo "Registration compelete!";
		mfooter($fmess,$intuser,$database_server['hostname']);

                 exit;
                 }
                 
else{

                 $mess ="Login already exists! or Registration code Invalid or in use!";
				 
                mheader($title,$subtitle,$descript);
                buildform($mess);
                mfooter($fmess,$intuser,$database_server['hostname']); 
                exit;
                }
}
        }
                                   
 
function buildform($mess){ ?>
 <Center>   
 <?= $mess ?><br>
 :: note: feilds with * are required ::
<form method="POST" action="reg.jsp">

<input type="hidden" Name="send" Value="1" >
<table>
<tr><td style="border:0px solid blue;">User ID:*</td><td style="border:0px solid blue;"><input type="text" Value="" Name="annm" onblur="style.backgroundColor=''; style.color=''" onfocus="style.backgroundColor='Silver'; style.color='Navy'" onmouseover="style.backgroundColor=''; style.color='gold'" onmouseout="style.backgroundColor=''; style.color=''"></td></tr>
<tr><td style="border:0px solid blue;">Password:*</td><td style="border:0px solid blue;"><input type="Password" Value="" Name="pwd" onblur="style.backgroundColor=''; style.color=''" onfocus="style.backgroundColor='Silver'; style.color='Navy'" onmouseover="style.backgroundColor=''; style.color='gold'" onmouseout="style.backgroundColor=''; style.color=''"></td></tr>

<tr><td style="border:0px solid blue;">Serial:</td><td style="border:0px solid blue;"><input type="text" Value="" Name="wser" onblur="style.backgroundColor=''; style.color=''" onfocus="style.backgroundColor='Silver'; style.color='Navy'" onmouseover="style.backgroundColor=''; style.color='gold'" onmouseout="style.backgroundColor=''; style.color=''"></td></tr>
<tr><td style="border:0px solid blue;">Name:*</td><td style="border:0px solid blue;"><input type="text" Value="" Name="nnm" onblur="style.backgroundColor=''; style.color=''" onfocus="style.backgroundColor='Silver'; style.color='Navy'" onmouseover="style.backgroundColor=''; style.color='gold'" onmouseout="style.backgroundColor=''; style.color=''"></td></tr>
<tr><td style="border:0px solid blue;">Social Security:</td><td style="border:0px solid blue;"><input type="text" Value="" Name="socno" onblur="style.backgroundColor=''; style.color=''" onfocus="style.backgroundColor='Silver'; style.color='Navy'" onmouseover="style.backgroundColor=''; style.color='gold'" onmouseout="style.backgroundColor=''; style.color=''"></td></tr>
<tr><td style="border:0px solid blue;">E-mail:*</td><td style="border:0px solid blue;"><input type="text" Value="" Name="mail" onblur="style.backgroundColor=''; style.color=''" onfocus="style.backgroundColor='Silver'; style.color='Navy'" onmouseover="style.backgroundColor=''; style.color='gold'" onmouseout="style.backgroundColor=''; style.color=''"></td></tr>
<tr><td style="border:0px solid blue;">Postal Code:</td><td style="border:0px solid blue;"><input type="text" Value="" Name="pscode" onblur="style.backgroundColor=''; style.color=''" onfocus="style.backgroundColor='Silver'; style.color='Navy'" onmouseover="style.backgroundColor=''; style.color='gold'" onmouseout="style.backgroundColor=''; style.color=''"></td></tr>
<tr><td style="border:0px solid blue;">Address 1:*</td><td style="border:0px solid blue;"><input type="text" Value="" Name="addr1" onblur="style.backgroundColor=''; style.color=''" onfocus="style.backgroundColor='Silver'; style.color='Navy'" onmouseover="style.backgroundColor=''; style.color='gold'" onmouseout="style.backgroundColor=''; style.color=''"></td></tr>
<tr><td style="border:0px solid blue;">Address 2:</td><td style="border:0px solid blue;"><input type="text" Value="" Name="addr2" onblur="style.backgroundColor=''; style.color=''" onfocus="style.backgroundColor='Silver'; style.color='Navy'" onmouseover="style.backgroundColor=''; style.color='gold'" onmouseout="style.backgroundColor=''; style.color=''"></td></tr>
<tr><td style="border:0px solid blue;">Phone Number:</td><td style="border:0px solid blue;"><input type="text" Value="" Name="phone" onblur="style.backgroundColor=''; style.color=''" onfocus="style.backgroundColor='Silver'; style.color='Navy'" onmouseover="style.backgroundColor=''; style.color='gold'" onmouseout="style.backgroundColor=''; style.color=''"></td></tr>
<tr><td style="border:0px solid blue;">Phone Number Cell:</td><td style="border:0px solid blue;"><input type="text" Value="" Name="cell" onblur="style.backgroundColor=''; style.color=''" onfocus="style.backgroundColor='Silver'; style.color='Navy'" onmouseover="style.backgroundColor=''; style.color='gold'" onmouseout="style.backgroundColor=''; style.color=''"></td></tr>
<tr><td style="border:0px solid blue;">Question 1:</td><td style="border:0px solid blue;"><input type="text" Value="" Name="qry1" onblur="style.backgroundColor=''; style.color=''" onfocus="style.backgroundColor='Silver'; style.color='Navy'" onmouseover="style.backgroundColor=''; style.color='gold'" onmouseout="style.backgroundColor=''; style.color=''"></td></tr>
<tr><td style="border:0px solid blue;">Reply 1:</td><td style="border:0px solid blue;"><input type="text" Value="" Name="rpl1" onblur="style.backgroundColor=''; style.color=''" onfocus="style.backgroundColor='Silver'; style.color='Navy'" onmouseover="style.backgroundColor=''; style.color='gold'" onmouseout="style.backgroundColor=''; style.color=''"></td></tr>
<tr><td style="border:0px solid blue;">Question 2:</td><td style="border:0px solid blue;"><input type="text" Value="" Name="qry2" onblur="style.backgroundColor=''; style.color=''" onfocus="style.backgroundColor='Silver'; style.color='Navy'" onmouseover="style.backgroundColor=''; style.color='gold'" onmouseout="style.backgroundColor=''; style.color=''"></td></tr>
<tr><td style="border:0px solid blue;">Reply 2:*</td><td style="border:0px solid blue;"><input type="text" Value="" Name="rpl2" onblur="style.backgroundColor=''; style.color=''" onfocus="style.backgroundColor='Silver'; style.color='Navy'" onmouseover="style.backgroundColor=''; style.color='gold'" onmouseout="style.backgroundColor=''; style.color=''"></td></tr>
</table>
<Center>
<input type="submit" value="     Creat     "  onblur="style.backgroundColor=''; style.color=''" onfocus="style.backgroundColor='Silver'; style.color='Navy'" onmouseover="style.backgroundColor=''; style.color='gold'" onmouseout="style.backgroundColor=''; style.color=''">

<input type="reset" value="     Clear     " name="clear" onblur="style.backgroundColor=''; style.color=''" onfocus="style.backgroundColor='Silver'; style.color='Navy'" onmouseover="style.backgroundColor=''; style.color='gold'" onmouseout="style.backgroundColor=''; style.color=''"></center>



</form>

<?php
}

#	$query_users = new query($SQL, 'SELECT * FROM Member ORDER BY Nickname');
#while($query_users->fetch()) {

#		$NNM = $query_users->field('Nickname');
 #echo "$NNM<br>\n";

#	}

?>


