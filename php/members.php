<?php

	function update_authorized_users($dbConn, $username, $newPassword)
	{

	    $query = 'UPDATE authorized_users SET password = :password WHERE username = :username';

	    $statement = $dbConn->prepare($query);

	    $params = [
				'password' => $newPassword,
				'username' => $username
	    ];

	    $result = $statement->execute($params);

	    if(!$result)
	    {
	        echo "Error executing statement";
	    }
	}

	function delete_authorized_users($dbConn, $username, $password)
	{
	    $query = 'DELETE FROM authorized_users WHERE username = :username AND password = :password';

	    $statement = $dbConn->prepare($query);

	    $params = [
	    	'username' => $username,
	    	'password' => $password
	    ];

	    $result = $statement->execute($params);

	    if(!$result)
	    {
	        echo "Error executing statement";
	    }
	}

	function connect_to_database()
	{
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

		return $db;
	}

	$deleteMember = $_POST['delete'] ?? '';
	$modifyMember = $_POST['modify'] ?? '';
	$username = $_POST['username'] ?? '';
	$password = $_POST['password'] ?? '';

	$db = connect_to_database();

	if($modifyMember == true)
	{
		update_authorized_users($db, $username, $password);	
	}
	else
	{
		delete_authorized_users($db, $username, $password);
	}

?>