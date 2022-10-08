</p></td>
			  </tr>
			  <tr>			    <td align="center" valign="top" bgcolor="#2B333A" style="border:0px"><img src="img/line_spacer_2.gif" width="400" height="1" alt="Spacer"></td>
			  </tr>
			  <tr>
			    <td align="right" valign="top" bgcolor="#2B333A" style="border:0px"><img src="img/message.gif" width="11" height="15" alt="Archive">&nbsp;<i>Help
                  about this section can be viewed here <a href="#help" class="thing">Help</a>.</i></td>
			  </tr>
			</table>
		  </td>
          <td bgcolor="#101F21" style="border-top:0px;border-bottom:0px;border-left:0px;border-right:0px">&nbsp;</td>
          <td width="145" align="center" valign="top" bgcolor="#101F21" style="border:0px">
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


	
echo $intuser;	
?>

                  <br><img src="img/spacer_2.gif" width="1" height="4" alt="Spacer"><br>                 <!-- server status -->
				<?PHP 
/* 

rights of aegis and others 
*/ 
error_reporting(0); 

$IP = array( 
"Login Server" => "66.149.252.8:4111",
"Session Server" => "66.149.252.8:4110",
"1p1 Server" => "66.149.252.8:12000", 
"Game Server" => "66.149.252.8:4120"); 
while(list($ServerName,$Host)=each($IP)) { 
list($IPAddress,$Port)=explode(":",$Host); 
echo("<DIV>".$ServerName.":</DIV>"); 
if($fp=fsockopen($IPAddress,$Port,$ERROR_NO, $ERROR_STR ,(float)1.5)) { 
echo("<b>&raquo;</b><Font style=\"color:'green'\">Running</Font><br>"); 
fclose($fp); 
} 
else { 
echo ("<b>&raquo;</b><Font style=\"color:'red'\">DOWN</Font><br>"); 
}  
}
?>
                  &nbsp;<br><b>&raquo;</b>  Site layout by: Zander<br><img src="img/spacer_2.gif" width="1" height="2" alt="Spacer"></p></td>
		      </tr>
            </table>
          </td>
	    </tr>
      </table>
    </td>
  </tr>
  <tr> 
    <td colspan="2" align="left" bgcolor="#101F21" style="border-top:0px"><p>&nbsp;Copyright &copy; 2005 &ndash;
      <a href="http://soma.neoworldvr.net">The Myth of Soma</a>&nbsp;&nbsp;&gt&nbsp;&nbsp;<?= $mess ?>&nbsp;&nbsp;&gt&nbsp;&nbsp;[ <a href="disclaimer.htm">Disclaimer</a> ]</p></td>
  </tr>
</table>


</body>
</html>