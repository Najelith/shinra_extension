<?php 

class db {

  var $id;

  function db() { }
  
  function getq() { return $this->queries; }
  
  function open($database, $host, $user, $password, $pconnect = 0) {
  
    if ($pconnect) {
       $this->id=mysql_pconnect($host, $user, $password); 
    } else {
       $this->id=mysql_connect($host, $user, $password); 
    }

    if ($this->id) {
       if (!mysql_select_db($database)) { $this->error('<b>Fatal Error</b>: Could not find database on the server'); }
    }
    return $this->id;
  }

  function error($error = 0) {
    global $lastquery;
    print '<font face="verdana" size="5">yoursite SQL</font><br><br><font face="verdana" size="2">An Error has occured, please contact the system administrator.</font><br><br><br><hr><font face="verdana" size="1">';
    if (!$error) { print mysql_error($this->id); } else { print $error; }
	print '<br>Query:<br>'.$lastquery;
	print '</font>';
	exit();
  }
      function errorcheck() {
    global $lastquery;        if (mysql_error($this->id)) {
		print '<font face="verdana" size="5">yoursite SQL</font><br><br><font face="verdana" size="2">An Error has occured, please contact the system administrator.</font><br><br><br><hr><font face="verdana" size="1">';
		$em = mysql_error($this->id);
		print $em;
		$errbd = explode("'",$em);
		if ($errbd[3] == '. (errno: 145)'){
			$badtable = explode(".",$errbd[2]);
			mysql_query("REPAIR TABLE ".$badtable[0]);
		}
		print '<br>Query:<br>'.$lastquery;
		print '</font>';
		exit();	}
  }
	 
  function error2() {
    return mysql_error($this->id);
  } 
  
  function close() {
    $result=@mysql_close($this->id);
    return $result;
  } 
};

class query {

  var $result;
  var $row;

  function query(&$db, $query="") {
      global $lastquery;
	  $lastquery = $query;
      $this->result=mysql_query($query, $db->id);      $db->errorcheck();
	  $db->queries .= '<br>'.$query;
  }
  
  function getrow() {
    if ($this->result) {
      $this->row=mysql_fetch_array($this->result);
    } else {
      $this->row=0;
    }
    return $this->row;
  }
   
   
  function fetch() {
    if ($this->result) {
      $this->row=mysql_fetch_array($this->result);
    } else {
      $this->row=0;
    }
    return $this->row;
  }    function seek($row) {    return mysql_data_seek($this->result, $row);  }
   
  function field($field) {
	return $this->row[$field];
  }

  function free() {
    return @mysql_free_result($this->result);
  }

		
  function affected() {
		return @mysql_affected_rows();
	}

}


?>