<?php 

function execute(string $sql, array $args) : PDOStatement
{
	static $pdo;
	$pdo ??= new PDO('odbc:dsn=soma');

	$statement = $pdo->prepare($sql);
	$statement->execute($args);

	return $statement;
}

function find(string $sql, array $args) : array 
{
  return execute($sql, $args)->fetchAll(PDO::FETCH_ASSOC);	
}
