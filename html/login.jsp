<?php
session_start();

include 'header.php';

$nnm = strtolower($_POST["nnm"]);
$pwd = $_POST["pwd"];
$send = $_POST["send"];
$fmess = 'Login';
$title = 'Login';
$subtitle = 'Login';
$descript = 'Please Login..';

 if (!$send) {
        mheader($title,$subtitle,$descript);
        genlogin($mess);
        mfooter($fmess,$intuser,$database_server['hostname']);
       
     }

        // ### Set User to logged in
        elseif ($send) {
trim($nnm);
trim($pwd);

                if ($nnm == '' ||  $pwd == '') { 
                       

                     mheader($title,$subtitle,$descript);
                     genlogin('Fill in all fields please!<br>Required information is missing.'); 
                     mfooter($fmess,$intuser,$database_server['hostname']);
                     exit; 
                }
                $query_checkdata = new query($SQL, "SELECT * FROM NGSCUSER WHERE strUserId='".$nnm."' AND strPasswd='".$pwd."'");
                
                if ($query_checkdata->getrow()) { 
               
                 $nnm = $query_checkdata->field('strUserId');
                 $_SESSION["nnm"]=$nnm;

                 header("Location: http://".$database_server['hostname']."/acc.jsp");
                 exit;
                 }
                 elseif(!$query_checkdata->getrow()){
                 $mess ="Login Failed!<br>Please check for typing mistakes. To register click <a href='reg.jsp'>here</a>.";
                        

                mheader($title,$subtitle,$descript);
                genlogin($mess);
                mfooter($fmess,$intuser,$database_server['hostname']); 
                exit;
                }

        }
                                   



?>