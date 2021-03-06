"use strict";


(function() {
	// the API end point
	var url = "/getListOfUsers";
	var xmlhttp = new XMLHttpRequest();
	xmlhttp.open("GET", url, true);
	xmlhttp.send();
	xmlhttp.onreadystatechange = function() {
    	if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
	   	var myArr = JSON.parse(xmlhttp.responseText);
	      fillTable(myArr);
		}
	};

	function fillTable(response) {
		console.log('filling Table');
		var output = "";
		for (var i in response) {
			output +='<tr class="urow"><td class="userid">' +
			response[i].acc_id + '</td><td class="username">' +
			response[i].acc_name + '</td><td class="userlogin">' +
			response[i].acc_login + "</td><td>" + "</td><td>" +
			'<input type="submit" value="Edit" form="userform" onclick="getEditInfo()">' +
			'<input type="submit" value="Remove" form="userform" onclick="getUserInformation()">' + "</td></tr>";
		}
		document.getElementsByTagName("tbody")[0].innerHTML= output;
	}

}) ();
