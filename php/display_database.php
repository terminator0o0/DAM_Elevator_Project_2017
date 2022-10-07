<?php 
	function authorized_users_display($dbConn)
	{
	    $query = 'SELECT * FROM authorized_users ORDER BY userID LIMIT 10';
	    $rows = $dbConn->query($query);
	    foreach ($rows as $row) 
	    {
	        echo "<tr>";
	        for ($i=0; $i < sizeof($row)/2 ; $i++) 
	        { 
	            echo "<td>".$row[$i]."</td>";
	        }
	        echo "</tr>";
	    }
	}

	function elevator_network_display($dbConn)
	{
	    $query = 'SELECT nodeID, requestedFloor, controllerType, doorState, currentFloor, dateID, timeID FROM (SELECT * FROM elevator_network ORDER BY ID DESC LIMIT 10) sub ORDER BY ID ASC';
	    $rows = $dbConn->query($query);
	    foreach ($rows as $row) 
	    {
	        echo "<tr>";
	        for ($i=0; $i < sizeof($row)/2 ; $i++) 
	        { 
	            echo "<td>".$row[$i]."</td>";
	        }
	        echo "</tr>";
	    }
	}
	
	function can_network_display($dbConn)
	{
	    $query = 'SELECT CAN_ID, requestedFloor, doorState, currentFloor, dateID, timeID FROM (SELECT * FROM CAN_network ORDER BY ID DESC LIMIT 10) sub ORDER BY ID ASC';
	    $rows = $dbConn->query($query);
	    foreach ($rows as $row) 
	    {
	        echo "<tr>";
	        for ($i=0; $i < sizeof($row)/2 ; $i++) 
	        { 
	            echo "<td>".$row[$i]."</td>";
	        }
	        echo "</tr>";
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

	$tableName = $_GET['q'];

	$dbConn = connect_to_database();

	switch ($tableName) 
	{
		case 'can-network':
			can_network_display($dbConn);
			break;
		case 'authorized-users':
			authorized_users_display($dbConn);
			break;
		default:
			elevator_network_display($dbConn);
			break;
	}

 ?>