function checkTime(i) 
{
  if (i < 10) 
  {
    i = "0" + i;
  }
  return i;
}

function displayTime() 
{
  var today = new Date();
  var h = today.getHours();
  var m = today.getMinutes();
  var s = today.getSeconds();
  // add a zero in front of numbers<10
  m = checkTime(m);
  s = checkTime(s);
  document.getElementById('displayTime').innerHTML = h + ":" + m + ":" + s;
  t = setTimeout(function() 
  {
    displayTime()
  }, 500);
}

function send_elevator_request(elevatorRequest)
{
    $.ajax({
        url: 'elevator_control_ajax.php',
        type: 'POST',
        data: {request: elevatorRequest},
        success: function(data)
        {
          display_database('elevator-network');
        }
    });
}

function display_database(databaseName)
{
    var xhttp;

    xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function()
    {
        if (this.readyState == 4 && this.status == 200) 
        {
            if(databaseName == 'elevator-network')
            {
              document.getElementById('elevator-network-content').innerHTML = this.responseText;
              document.getElementById('elevator-network-table').style.display = 'inline-table';
              document.getElementById('members-table').style.display = 'none';
			  document.getElementById('can-network-table').style.display = 'none';
            }
            else if(databaseName == 'authorized-users')
            {
                document.getElementById('member-content').innerHTML = this.responseText;
                document.getElementById('members-table').style.display = 'inline-table';
                document.getElementById('elevator-network-table').style.display = 'none';
				document.getElementById('can-network-table').style.display = 'none';
            }
			else if (databaseName == 'can-network')
            {
                document.getElementById('can-network-content').innerHTML = this.responseText;
                document.getElementById('can-network-table').style.display = 'inline-table';
                document.getElementById('elevator-network-table').style.display = 'none';
				document.getElementById('members-table').style.display = 'none';
            }
            
        }
    };
    xhttp.open("GET", "display_database.php?q="+databaseName, true);
    xhttp.send();
}


display_database('elevator-network');
displayTime();
