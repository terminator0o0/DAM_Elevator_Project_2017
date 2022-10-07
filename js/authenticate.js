var usernameSubmit = document.getElementById('username');
var passwordSubmit = document.getElementById('password');
var msgPassword = document.getElementById('passwordMsg');
var msgUsername = document.getElementById('usernameMsg');
var form = document.getElementById('form-validate');


function checkUsername(event) 
{
	if (usernameSubmit.value.length < 7)
	{
		msgUsername.innerHTML = "<i>Username must be 7 characters minimum<i>";
		event.preventDefault();
	} 
	else
	{
		msgUsername.innerHTML = "";
	}
}

function checkPassword(event) 
{
	if (passwordSubmit.value.length < 7)
	{
		msgPassword.innerHTML = "<i>Password must be 7 characters minimum<i>";
		event.preventDefault();
	} 
	else
	{
		msgPassword.innerHTML = '';	
	}
}

form.addEventListener('submit', function(event) {checkUsername(event); checkPassword(event);}, false);