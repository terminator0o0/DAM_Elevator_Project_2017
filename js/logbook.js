var today = new Date();
var	hourNow = today.getFullYear();

var dinkarBirthdate = new Date("Aug 4, 1996 12:00:00");
var anasBirthdate = new Date("Feb 21, 1994 12:00:00");
var mikeBirthdate = new Date("July 7, 1989 12:00:00");

var nameEle = document.getElementById('name');


function bDayFunc(bDay){

	var age = today.getTime() - bDay.getTime();

	age = Math.floor(age/31556900000);

	msg = "<p>I am " + age + " years old! </p>";
	
	return msg; 
}


if ( nameEle.innerHTML == 'dinkar'){
	bDayFunc(dinkarBirthdate);
	nameEle.innerHTML = msg;
} else if ( nameEle.innerHTML == 'anas') {
	bDayFunc(anasBirthdate);
	nameEle.innerHTML = msg;
} else if( nameEle.innerHTML == 'mike'){
	bDayFunc(mikeBirthdate);
	nameEle.innerHTML = msg;
} else {
	nameEle.innerHTML = 'fail';
}

$(document).ready(function(){
  $("#week1").on("hide.bs.collapse", function(){
    $(".test").html('<span class="glyphicon glyphicon-collapse-down"></span> Week 1');
  });
  $("#week1").on("show.bs.collapse", function(){
    $(".test").html('<span class="glyphicon glyphicon-collapse-up"></span> Week 1');
  });
});







