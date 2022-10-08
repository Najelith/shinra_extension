<?php

include 'header.php';

    $query_getdata = new query($SQL, "SELECT * FROM Guild");
    
//    headers
$mess = 'Downloads';
$title = 'Downloads';
$subtitle = 'Client & Patches';
$descript = 'List of mirrors';

mheader($title,$subtitle,$descript);
?>
Client:<br><br>
:::<a href='http://<?=$database_server['hostname']?>/download/soma.zip'>Myth of Soma 220 </a>:::<br>
<br><br>

Patches( only for this server ):<br><br>

::<a href='./patch/updater.rar'>Client patch nw1.0</a>::<br>
IMPORTANT: place in a clean soma main install folder (i.e C:/soma/). Always run updater.exe to launch soma.<br>

<?php

// footers
mfooter($mess,$intuser,$database_server['hostname']);


?>


