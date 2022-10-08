</td>
              </tr>
			  <tr>			    <td align="center" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="454" colspan="7"><img src="img/line_spacer_2.gif" width="400" height="1" alt="Spacer"></td>
			  </tr>
			  <tr>
			    <td align="right" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="454" colspan="7"><img src="img/message.gif" width="11" height="15" alt="Archive">&nbsp;<i>Help
                  about this section can be viewed here <a href="#help" class="thing">Help</a>.</i></td>
			  </tr>
			</table>

		  </td>
          <td bgcolor="#101F21" style="border-style: none; border-width: 0px" width="12">&nbsp;</td>
          <td width="141" align="center" valign="top" bgcolor="#101F21" style="border-style: none; border-width: 0px">
		    <table width="93%" border="0" cellspacing="0" cellpadding="2" summary="Site Information Table">
		      <tr>
		        <td class="thing"><img src="img/support.jpg" width="125" height="15" alt="Game Support"></td>
		      </tr>
		      <tr>
		        <td bgcolor="#2B333A" onmouseover="bgColor='#101F21'" onmouseout="bgColor='#2B333A'" style="border-top:0px"><p>		      
		        <b>&raquo;</b><a href="tech.jsp">Tech. Support</a><br>
              </p></td>
		      </tr>
		      
			 <tr>
		        <td bgcolor="#2B333A" onmouseover="bgColor='#101F21'" onmouseout="bgColor='#2B333A'" style="border-top:0px"><p>		      
		        <b>&raquo;</b><a href="olgmsup.jsp">GM Support</a><br>
              </p></td>
		      </tr>
		      <tr>
		        <td bgcolor="#2B333A" onmouseover="bgColor='#101F21'" onmouseout="bgColor='#2B333A'" style="border-top:0px"><p>		      
		        <b>&raquo;</b><a href="staff.jsp">Staff Schedules</a><br>
              </p></td>
		      </tr>
		         
            </table>
		    <table width="93%" border="0" cellspacing="0" cellpadding="2" summary="Site Information Table">
			  <tr>
		        <td style="border:0px"><img src="img/spacer_3.gif" width="1" height="1" alt="Spacer"></td>
			  </tr>
		      <tr>
		        <td class="thing"><img src="img/s_info.jpg" width="125" height="15" alt="Site Info"></td>
		      </tr>
		      <tr>
		        <td bgcolor="#2B333A" style="border-top:0px"><p><b>&raquo;</b> 
                  Users Online:&nbsp;
<?php
                 
    //$query_getdata = new query($SQL, "SELECT * FROM CURRENTUSER");
    
//$intuser = 0;

      //while($query_getdata->fetch()) {

	//	$nnm = $query_getdata->field('nAccounID');
	//	$intuser++;
	//} 
echo $intuser;	
?>

                  <br><img src="img/spacer_2.gif" width="1" height="4" alt="Spacer"><br>                 <!-- server status -->
				<?PHP 

$IP = array( 
"Login Server" => $database_server['hostname'].":4111",
"Session Server" => $database_server['hostname'].":4110",
"1p1 Server" => $database_server['hostname'].":22010", 
"Game Server" => $database_server['hostname'].":4120"); 
foreach ($IP as $ServerName => $Host){

list($IPAddress,$Port)=explode(":",$Host); 
echo("<DIV>".$ServerName.":</DIV>"); 
if($fp=fsockopen($IPAddress,$Port,$ERROR_NO, $ERROR_STR ,(float)1.5)) { 
echo("<b>&raquo;</b><Font style=\"color:#008000\">Running</Font><br>"); 
fclose($fp); 
} 
else { 
echo ("<b>&raquo;</b><Font style=\"color:#BF0000\">DOWN</Font><br>"); 
}  
}
?>
&nbsp;<br><b>&raquo;</b>  Site layout by: Zander<br>

<img src="img/spacer_2.gif" width="1" height="2" alt="Spacer"></td>
		      </tr>
            </table>
          </td>
	    </tr>
      </table>
    </td>
  </tr>
  <tr> 
    <td colspan="2" align="left" bgcolor="#101F21" style="border-top:0px"><p>&nbsp;Copyright &copy; 2005 &ndash;
      <a href="http://<?=$hostname ?>">The Myth of Soma</a>&nbsp;&nbsp;&gt&nbsp;&nbsp;<?= $mess ?>&nbsp;&nbsp;&gt&nbsp;&nbsp;[ <a href="disclaimer.htm">Disclaimer</a> ]</p></td>
  </tr>
</table>


</body>
</html>
	      </td>                     