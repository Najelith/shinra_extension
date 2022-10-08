<?php 


class db {

  var $id;
  var $queries;

  function db() { }
  
  function getq() { return $this->queries; }
  
  function open($database, $host, $user, $password, $pconnect = 0) {
  //$connectionInfo = array( "Database"=>$database, "UID"=>$user, "PWD"=>$password);
    if ($pconnect) {
       $this->id=odbc_connect("Driver={SQL Server};Server=$host;Database=$database;", $user, $password);
	   //sqlsrv_connect( $serverName, $connectionInfo); 
    } else { // change later to pconnect
       $this->id=odbc_connect($database,$user,$password);
	   }

    if (!$this->id) {
        $this->error('<b>Fatal Error</b>: Could not connect to server'); 
    }
    return $this->id;
  }

  function error($error = 0) {
    global $lastquery;
    print '<font face="verdana" size="5"> Classic Soma SQL</font><br><br><font face="verdana" size="2">An Error has occured, please contact the system administrator.</font><br><br><br><hr><font face="verdana" size="1">';
    if (!$error) { print $this->id; } else { print $error; }
	print '<br>Query:<br>'.$lastquery;
	print '</font>';
	die( print_r( odbc_errormsg($this->id), true));
	exit();
  }

	 
  function error2() {
    return $this->id;
  } 
  
  function close() {
    $result=odbc_close($this->id);
    return $result;
  } 
};

class query {

  var $result;
  var $row;
  var $numrows;

  function __construct(&$db, $query="") {
      global $lastquery;
	  $lastquery = $query;
	   $this->result = odbc_prepare($db->id, $query );
		$success = odbc_execute($this->result);
      //$this->result=@odbc_exec($db->id,$query );     # $db->errorcheck();

	  $db->queries .= '<br>'.$query;
	  $this->numrows=odbc_num_rows($this->result);

  }
  
  
  function getrow() {
    if ($this->result) {
      $this->row=odbc_fetch_array($this->result);
    } else {
      $this->row=0;
    }
    return $this->row;
  }
   
   
  function fetch() {
	  
    if ($this->result && $this->numrows) { // pop first result
	  $this->row=odbc_fetch_row($this->result); 
	  $this->numrows--;

    } else {
      $this->row=0;
    }
	
    return $this->row;
  }    function seek($row) {    return odbc_fetch_array($this->result, $row);  }
   
  function field($field) {
	return odbc_result($this->result,$field);
  }

  function free() {
    return @odbc_free_result($this->result);
  }

		
  function affected() {
		return $this->numrows;
	}
 
}

?>