
          <td width="458" valign="top" bgcolor="#2B333A" style="border-left-style: none; border-left-width: 0px">
		    <table width="100%" border="0" cellspacing="0" cellpadding="2" summary="Main Content Table">
			  <tr>
			    <td rowspan="2" width="120" align="center" valign="middle" style="border-top:0px;border-left:0px;border-right:0px"> <img src="img/mon/<?=$monmesh ?>.png" alt="Monster Image" onError="this.src=('img/shots.jpg');"></td>
			    <td align="left" valign="top" class="thing" style="border-top:0px;border-bottom:0px;border-right:0px"><b>.::
                  Quest Information &amp; Monster History ::.</b></td>
			  </tr>
			  <tr>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-right:0px"><p style="font-size:10px"><b><?=$monname ?>:</b>
                  &quot;NPC's Speach <?=$monchat1 ?>&quot;<br>
                  <b>Quests:</b> Quests this AI is in.<br>
                  <b>Monster History:</b><br>
                  &quot;history of monster<br>
                  or tactucs to fight it with.<br>
                  etc.&quot;<br><img src="img/spacer_2.gif" width="1" height="2" alt="Spacer"></p></td>
			  </tr>
			</table>
			<table width="458" border="0" cellspacing="0" cellpadding="2" summary="Site News Table">
			  <tr>
			    <td align="left" valign="top" class="thing" style="border-left-style: none; border-left-width: 0px; border-right-style: none; border-right-width: 0px; border-top-style: none; border-top-width: 0px" width="454" colspan="7"><b>.::<?=$monname ?> 
                  :: Detail Information</b></td>
		      </tr>
			  <tr>
			  <!-- detail here -->
			        			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="454" colspan="7"><p style="font-size:10px;font-weight:bold;color:#FFFFFF">�&nbsp;Statistics<br><img src="img/line_spacer.gif" width="400" height="1" alt="Spacer"></p></td>
			  </tr>
			  <tr>
			    <th align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="132" colspan="2">
                       Name </hd>
			    <th align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="69">World</th>
			    <th align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="60">Type</th>
			    <th align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="38">AI</th>
			    <th align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="45">Level</th>
			    <th align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="90">Exp</th>
			  </tr>
              <tr>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="132" colspan="2"><?=$monname ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="69"><?=$monclass ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="60"><?=$montype ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="38">
<?=$monAI ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="45"><?=$monlvl ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="90"><?=$monexp ?></td>
              </tr>
              <tr>
			    <th align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="132" colspan="2">Min
                  Damage</th>
			    <th align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="69">Moral</th>
			    <th align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="60">HP</th>
			    <th align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="38">MP</th>
			    <th align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="45">Range</th>
			    <th align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="90">&nbsp;</th>
              </tr>
              <tr>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="132" colspan="2"><?=$monmindam ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="69"><?=$monmoral ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="60"><?=$monhp ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="38"><?=$monmp ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="45"><?=$monrange ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="90">&nbsp;</td>
              </tr>
              <tr>
			    <th align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="132" colspan="2">STR</th>
			    <th align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="69">DEX
                  ATK</th>
			    <th align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="60">DEX
                  DEF</th>
			    <th align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="38">INT</th>
			    <th align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="45">WIS</th>
			    <th align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="90">CON</th>
              </tr>
              <tr>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="132" colspan="2"><?=$monstr ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="69"><?=$monadex ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="60"><?=$monddex ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="38"><?=$monint ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="45"><?=$monwis ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="90"><?=$moncon ?></td>
              </tr>
			  <tr>			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="454" colspan="7"><p style="font-size:10px;font-weight:bold;color:#FFFFFF">�&nbsp;Magic<br><img src="img/line_spacer.gif" width="400" height="1" alt="Spacer"></p></td>
			  </tr>
			  <tr>
			    <th align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="65">
                       Spell </th>
			    <th align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="63">Rate</th>
			    <th align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="69">Spell</th>
			    <th align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="60">Rate</th>
			    <th align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="38">Spell</th>
			    <th align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="45">Rate</th>
			    <th align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="90">&nbsp;</th>
			  </tr>
              <tr>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="65"><?=$monmag1 ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="63"><?=$monmrate1 ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="69"><?=$monmag2 ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="60"><?=$monmrate2 ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="38"><?=$monmag3 ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="45"><?=$monmrate3 ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="90">&nbsp;</td>
              </tr>
			  <tr>			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="454" colspan="7"><p style="font-size:10px;font-weight:bold;color:#FFFFFF">�&nbsp;Drops<br><img src="img/line_spacer.gif" width="400" height="1" alt="Spacer"></p></td>
			  </tr>
			  <tr>
			    <th align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="65">
                       Barr: 
</th>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="63"><?=$monminbarr ?>~<?=$monmaxbarr ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="318" colspan="5">&nbsp;</td>
			  </tr>
              <tr>
			    <th align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="132" colspan="2">Item</th>
			    <th align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="318" colspan="5">Rate</th>
              </tr>
              <tr>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="132" colspan="2"><?=$monitem1 ?><?=$monitem1gen ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="318" colspan="5"><?=$monirand1 ?></td>
              </tr>
              <tr>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="132" colspan="2"><?=$monitem2 ?><?=$monitem2gen ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="318" colspan="5"><?=$monirand2 ?></td>
              </tr>
              <tr>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="132" colspan="2"><?=$monitem3 ?><?=$monitem3gen ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="318" colspan="5"><?=$monirand3 ?></td>
              </tr>
              <tr>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="132" colspan="2"><?=$monitem4 ?><?=$monitem4gen ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="318" colspan="5"><?=$monirand4 ?></td>
              </tr>
              <tr>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="132" colspan="2"><?=$monitem5 ?><?=$monitem5gen ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="318" colspan="5"><?=$monirand5 ?></td>
              </tr>
              <tr>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="132" colspan="2"><?=$monitem6 ?><?=$monitem6gen ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="318" colspan="5"><?=$monirand6 ?></td>
              </tr>
              <tr>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="132" colspan="2"><?=$monitem7 ?><?=$monitem7gen ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="318" colspan="5"><?=$monirand7 ?></td>
              </tr>
              <tr>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="132" colspan="2"><?=$monitem8 ?><?=$monitem8gen ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="318" colspan="5"><?=$monirand8 ?></td>
              </tr>
              <tr>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="132" colspan="2"><?=$monitem9 ?><?=$monitem9gen ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="318" colspan="5"><?=$monirand9 ?></td>
              </tr>
              <tr>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="132" colspan="2"><?=$monitem10 ?><?=$monitem10gen ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="318" colspan="5"><?=$monirand10 ?></td>
              </tr>
              <tr>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="132" colspan="2"><?=$monitem11 ?><?=$monitem11gen ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="318" colspan="5"><?=$monirand11 ?></td>
              </tr>
              <tr>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="132" colspan="2"><?=$monitem12 ?><?=$monitem12gen ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="318" colspan="5"><?=$monirand12 ?></td>
              </tr>
              <tr>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="132" colspan="2"><?=$monitem13 ?><?=$monitem13gen ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="318" colspan="5"><?=$monirand13 ?></td>
              </tr>
              <tr>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="132" colspan="2"><?=$monitem14 ?><?=$monitem14gen ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="318" colspan="5"><?=$monirand14 ?></td>
              </tr>
              <tr>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="132" colspan="2"><?=$monitem15 ?><?=$monitem15gen ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="318" colspan="5"><?=$monirand15 ?></td>
              </tr>
              <tr>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="454" colspan="7"><p style="font-size:10px;font-weight:bold;color:#FFFFFF">�&nbsp;Locations<br><img src="img/line_spacer.gif" width="400" height="1" alt="Spacer"></p></td>
              </tr>
              <tr>
			    <th align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="132" colspan="2">
			        Map</th>
			    <th align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="69">Min
                  X</th>
			    <th align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="60">Min
                  Y</th>
			    <th align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="38">Max
                  X</th>
			    <th align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="45">Max
                  Y</th>
			    <th align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="90">Respawn</th>
              </tr>
              <tr>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="132" colspan="2"><?=$monzone ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="69"><?=$monminx ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="60"><?=$monminy ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="38"><?=$monmaxx ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="45"><?=$monmaxy ?></td>
			    <td align="left" valign="top" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="90"><?=$monspawn ?></td>
              </tr>
              <tr>
			    <td align="center" valign="middle" bgcolor="#2B333A" style="border-style: none; border-width: 0px" width="434" colspan="7"><i>view
                  spawn range on map</i><br />
				  <img src="img.jsp?zone=<?=$monzonenum?>&minx=<?=$monminx ?>&maxx=<?=$monmaxx ?>&miny=<?=$monminy ?>&maxy=<?=$monmaxy ?>&name=<?=$monname ?>" alt="map" onError="this.src=('/img/nomap.png');">