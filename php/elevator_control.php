<?php 
    session_start();
    if(!isset($_SESSION['username']))
    {
        echo "<p>You are not authorized users. Click <a href=../request_access.html> here to sign up.</p>"; 
        die();
    }
 ?>
<!DOCTYPE html>
<html lang="en">
<head>
    <title>Elevator Control</title>
    <meta charset="utf-8">
    <meta content="" name="decription">
    <meta content="Group DAM" http-equiv="author">
    <meta content="no-cache" http-equiv="pragma">
    <meta content="width=device-width, initial-scale=1" name="viewport">
    <!-- Latest compiled and minified CSS -->
    <link href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" rel=
    "stylesheet"><!-- jQuery library -->
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js">
    </script><!-- Latest compiled JavaScript -->
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js">
    </script>
    <link rel="stylesheet" type="text/css" href="../css/navbar.css">
    <link rel="stylesheet" type="text/css" href="../css/elevator_control.css">
</head>
<body>
    <header>
        <nav class="navbar navbar-inverse navbar-fixed-top">
            <div class="container-fluid">
                <div class="navbar-header">
                    <button class="navbar-toggle" data-target="#myNavbar" data-toggle="collapse" type=
                    "button"><span class="icon-bar"></span> <span class="icon-bar"></span> <span class=
                    "icon-bar"></span></button> <a class="navbar-brand" href="../index.html">DAM Elevator</a>
                </div>
                <div id="myNavbar" class="collapse navbar-collapse">
                    <ul class="nav navbar-nav">
                        <li><a href="../about.html">About</a></li>
                        <li><a href="../project_details.html">Project Details</a></li>
                        <li><a href="../project_plan.html">Project Plan</a></li>
                        <li class="dropdown">
                            <a class="dropdown-toggle" data-toggle="dropdown" href="#">LogBooks<span class="caret"></span></a>
                            <ul class="dropdown-menu">
                                <li><a href="../logbook/dinkar-logbook.html">Dinkar</a></li>
                                <li class="divider"></li>
                                <li><a href="../logbook/anas-logbook.html">Anas</a></li>
                                <li class="divider"></li>
                                <li><a href="../logbook/mike-logbook.html">Mike</a></li>
                            </ul>
                        </li>
                        <li><a id="displayTime"></a></li>
                    </ul>
                    <ul class="nav navbar-nav navbar-right">
                        <li>
                            <a><span id="welcome" class="glyphicon glyphicon-user"></span> <?php echo $_SESSION['username']; ?></a>
                        </li>
                        <li>
                            <a href="logout.php"> <span class="glyphicon glyphicon-log-out"></span> Log out</a>
                        </li>
                    </ul>
                </div>
            </div>
        </nav>
    </header>
    <div id="elevator-controller" class="col-sm-4 bg-grey-light text-center">
        <h2>Elevator Controller</h2>
        <div id="controller-btn" class="btn-group-vertical">
            <button class="btn btn-primary btn-lg" type="button" onclick="send_elevator_request('car-3-req')">3</button>
            <button class="btn btn-primary btn-lg" type="button" onclick="send_elevator_request('car-2-req')">2</button>
            <button class="btn btn-primary btn-lg" type="button" onclick="send_elevator_request('car-1-req')">1</button>
            <div id="door-state-btn" class="btn-group btn-group-justified">
                <div class="btn-group">
                    <button value="door-open" class="btn btn-primary" type="button" onclick="send_elevator_request('open')">Open</button>
                </div>
                <div class="btn-group">
                    <button value="door-close" class="btn btn-primary" type="button" onclick="send_elevator_request('close')">Close</button>
                </div>
            </div>
        </div>
<!--             <div class="floor-req-light">
            <span id="floor-3-light" class="floor-light"></span>
            <span id="floor-2-light" class="floor-light"></span>
            <span id="floor-1-light" class="floor-light"></span>
            <span id="door-open-light" class="floor-light"></span>
            <span id="door-close-light" class="floor-light"></span>
        </div>   -->
    </div>
    <div id="car-controller" class="col-sm-4 bg-grey-light text-center">
        <h2>Floor Controller</h2>
        <div id="controller-btn" class="btn-group-vertical">
            <button name="floor-3-req" class="btn btn-primary btn-lg" onclick="send_elevator_request('floor-3-req')">3</button>
            <button name="floor-2-req" class="btn btn-primary btn-lg" onclick="send_elevator_request('floor-2-req')">2</button>
            <button name="floor-1-req" class="btn btn-primary btn-lg" onclick="send_elevator_request('floor-1-req')">1</button>
        </div>
<!--             <div class="floor-req-light">
            <span id="floor-3-light" class="floor-light"></span>
            <span id="floor-2-light" class="floor-light"></span>
            <span id="floor-1-light" class="floor-light"></span>
            <span id="floor-1-light" class="floor-light"></span>
            <span id="floor-1-light" class="floor-light"></span>
        </div> -->
    </div>
    <div id="car-controller" class="col-sm-4 bg-grey-light text-center">
        <h2>Modify Member</h2>
        <form method="POST" action="members.php">
            <div class="input-group">
                <span class="input-group-addon"><i class="glyphicon glyphicon-user"></i></span>
                <input class="form-control" name="username" placeholder="Enter Username"
                type="text" required="">
            </div>
            <div class="input-group">
                <span class="input-group-addon"><i class="glyphicon glyphicon-lock"></i></span>
                <input class="form-control" name="password" placeholder="Enter New Password"
                type="password" required="">
            </div>
            <div class="input-group">
                <button name="modify" value="true" class="btn btn-default login-btn" type="submit">
                    <span class="glyphicon glyphicon-log-in"></span> Modify
                </button>
            </div>
            <div class="input-group">
                <button name="delete" value="true" class="btn btn-default login-btn" type="submit">
                    <span class="glyphicon glyphicon-log-in"></span> Delete
                </button>
            </div>
        </form>
    </div>
    <section class="bg-grey-dark">
        <div class="col-sm-12 bg-grey-dark text-center" id="debug-content">
            <!--   <h2>Debug-Panel</h2> -->
            <div class="table-responsive">
                <h2>Debug-Panel</h2>
                <table id="elevator-network-table" class="table">
                    <thead>
                        <tr>
                            <th>Node ID</th>
                            <th>Floor Request</th>
                            <th>Controller Type</th>
                            <th>Door State</th>
                            <th>Current Floor</th>
                            <th>Date</th>
                            <th>Time</th>
                        </tr>
                    </thead>
                    <tbody id="elevator-network-content"></tbody>
                </table>
				</div>
                <div class="table-responsive">
                    <table class="table" id="members-table">
                        <thead>
                            <!-- <h2>Members</h2> -->
                            <tr>
                                <th>User ID</th>
                                <th>Username</th>
                                <th>Password</th>
                            </tr>
                        </thead>
                        <tbody id="member-content"></tbody>
                    </table>
					</div>
					<div class="table-responsive">
						<table id="can-network-table" class="table">
						<thead>
							<tr>
								<th>CAN ID</th>
								<th>Floor Request</th>
								<th>Door State</th>
								<th>Current Floor</th>
								<th>Date</th>
								<th>Time</th>
							</tr>
						</thead>
						<tbody id="can-network-content"></tbody>
						</table>
                </div>
                <ul class="pagination">
                    <li>
                        <a href="#" id="elevator-network" onclick="display_database(this.id)">1</a>
                    </li>
                    <li>
                        <a href="#" id="authorized-users" onclick="display_database(this.id)">2</a>
                    </li>
					<li>
                        <a href="#" id="can-network" onclick="display_database(this.id)">3</a>
                    </li>
                </ul>
            </div>
        </div>
       <script src="../js/elevator_control.js"></script>
    </section>
    <footer id="foot" class="col-sm-12 text-center">
        <script src="../js/common.js"></script>
    </footer>
</body>
</html>