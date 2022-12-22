<?php

include 'headernnm.php';

$nnm = $_SESSION["nnm"];
$nn1 = $_POST["nn1"];
$acmail = $_POST["acmail"];
$acpc = $_POST["acpc"];
$addr1 = $_POST["addr1"];
$acpw = $_POST["acpw"];
$send = $_POST["send"];

$fmess = 'Account';
$title = 'Account';
$subtitle = 'Account Management';
$descript = 'Edit Personal Info..';


if (!$send) {
            
    $query_getacc = find('SELECT strName , strEmail , strPostalCode , strAddr1, timeReg, timeLog FROM NGSCUSER WHERE strUserId = ?', [$nnm]);

    [[
       $oaccnm,
       $oaccmail,
       $oacpc,
       $oaddr1,
       $regtime,
       $lastlog
    ]] = $query_getacc;
                
    $_SESSION["regtime"] = $regtime;
    $_SESSION["lastlog"] = $lastlog;

    mheader($title, $subtitle, $descript);
    buildform($mess, $oaccnm, $oaccmail, $oacpc, $oaddr1, $regtime, $lastlog);
    mfooter($fmess, null, $database_server['hostname']);
}
// ### Set User to logged in
elseif ($send) {

    if ($nn1 == '' || $acmail == '' ||  $addr1 == '' || $acpw == '') { 
                
        mheader($title, $subtitle, $descript);
        buildform('Please Fill in required Fields!', $nn1, $acmail, $acpc, $addr1, $_SESSION["regtime"], $_SESSION["lastlog"]);
        mfooter($fmess, null, $database_server['hostname']); 
        exit; 
    }
   
    execute('UPDATE NGSCUSER SET strPasswd = ?, strName = ?, strEmail = ?, strPostalCode = ?, strAddr1 = ? WHERE strUserId = ?', [$acpw, $nn1, $acmail, $acpc, $addr1, $nnm]);
    mheader($title, $subtitle, $descript);
    echo "Account updated!";
    mfooter($fmess, null, $database_server['hostname']);
        
    exit;
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
?>
