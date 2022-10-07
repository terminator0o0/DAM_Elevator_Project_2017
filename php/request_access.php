<?php

	$usernameSubmit = $_POST['username'] ?? '';
	$passwordSubmit = $_POST['password'];

	try 
	{
		$db = new PDO(
		'mysql:host=127.0.0.1;dbname=elevator_project_2017',
		'root',
		'');
	} 
	catch (Exception $e) 
	{
		echo "Error connecting to database: " .$e->getMessage();
	}

	$query = 'INSERT INTO authorized_users (username, password)
			  VALUES (:username, :password) ';
	$statement = $db->prepare($query);
	$params = [
			'username' => $usernameSubmit,
			'password' => $passwordSubmit
			];

	if(!$statement->execute($params))
	{
		echo "Error executing statement";
	}
	else
	{
		header("Location: ../index.html");
	}
?>