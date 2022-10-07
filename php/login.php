<?php

	session_start();
	$authenticated = FALSE;
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

	$rows = $db->query('SELECT * FROM authorized_users');
	foreach ($rows as $row)
	{
		if ($usernameSubmit == $row[1] && $passwordSubmit == $row[2])
		{
			$authenticated = TRUE;
			break;
		}
	}
	if ($authenticated == TRUE)
	{
		$_SESSION['username']=$usernameSubmit;
		header("Location: elevator_control.php");
	}
	else
	{
		echo"<p>Invalid username or password</p>";
	}
	
?>