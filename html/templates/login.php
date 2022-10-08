
 <Center>   
<form method="POST" action="login.jsp">
<table>
<input type="hidden" Name="send" Value="1" >
<td><tr>Nickname:</tr><tr><input type="text" Value="" Name="nnm" onblur="style.backgroundColor=''; style.color=''" onfocus="style.backgroundColor='Silver'; style.color='Navy'" onmouseover="style.backgroundColor=''; style.color='gold'" onmouseout="style.backgroundColor=''; style.color=''"></tr></td>
<td><tr>Password:</tr><tr><input type="Password" Value="" Name="pwd" onblur="style.backgroundColor=''; style.color=''" onfocus="style.backgroundColor='Silver'; style.color='Navy'" onmouseover="style.backgroundColor=''; style.color='gold'" onmouseout="style.backgroundColor=''; style.color=''"></tr></tr><tr><?= $mess ?></tr>
<td><Center>
<input type="submit" value="     Enter     "  onblur="style.backgroundColor=''; style.color=''" onfocus="style.backgroundColor='Silver'; style.color='Navy'" onmouseover="style.backgroundColor=''; style.color='gold'" onmouseout="style.backgroundColor=''; style.color=''">

<input type="reset" value="     Clear     " name="clear" onblur="style.backgroundColor=''; style.color=''" onfocus="style.backgroundColor='Silver'; style.color='Navy'" onmouseover="style.backgroundColor=''; style.color='gold'" onmouseout="style.backgroundColor=''; style.color=''"></center></td>
</table>

</form>
</Center>

