/*Inserts copyright with the current year*/
var today = new Date();
var year = today.getFullYear();
msg = "<p>Copyright &copy DAM Group " + year + "</p>";
var element = document.getElementById('foot');
element.innerHTML = msg;

/*Closes login window when curser is clicked out of login window*/
var modal = document.getElementById('id01');

// When the user clicks anywhere outside of the modal, close it
window.onclick = function(event) 
{
    if (event.target == modal) 
    {
        modal.style.display = "none";
    }
}