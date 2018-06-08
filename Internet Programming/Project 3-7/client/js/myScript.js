function addEmptyTableRow(){
	var output = "<tr><td>" + "</td><td>" +
	'<input type="text" class="form-control" name="newUserName" required maxlength="15">' + "</td><td>" +
	'<input type="text" class="form-control" name="newLogin" required maxlength="15">' + "</td><td>" +
	'<input type="text" class="form-control" name="newPassword" required maxlength="15">' + "</td><td>" +
	'<input type="submit" value="Submit" form="formEdit">' +
	'<input type="submit" value="Exit" form="formEdit" formaction="/resetAdmin" formnovalidate>' + "</td></tr>";
	document.getElementsByTagName("tbody")[0].innerHTML += output;
}


function getUserInformation(){
	var userid = $(event.target).closest('.urow').find('.userid');
	//alert("UID: " + userid[0].innerHTML);
	var username = $(event.target).closest('.urow').find('.username');
	//alert("Name: " + username[0].innerHTML);
	var userLogin = $(event.target).closest('.urow').find('.userlogin');
	//alert("Login: " + userLogin[0].innerHTML);

	var url = "/deleteUser";
	var xmlhttp = new XMLHttpRequest();
	var params="userid=" + userid[0].innerHTML;
	xmlhttp.open("POST", url, true);
	xmlhttp.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
	xmlhttp.onreadystatechange = function() {
			if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
		}
	}
	xmlhttp.send(params);
	location.reload(true);
	//alert("Inside Function");
}


function getEditInfo(){
	var userid = $(event.target).closest('.urow').find('.userid');
	//alert("UID: " + userid[0].innerHTML);
	var uid = parseInt(userid[0].innerHTML);
	var username = $(event.target).closest('.urow').find('.username');
	//alert("Name: " + username[0].innerHTML);
	var userLogin = $(event.target).closest('.urow').find('.userlogin');
	//alert("Login: " + userLogin[0].innerHTML);


	var output = "<tr><td>" + uid + "</td><td>" +
	'<input type="text" class="form-control" name="newUserName" required maxlength="15">' + "</td><td>" +
	'<input type="text" class="form-control" name="newLogin" required maxlength="15">' + "</td><td>" +
	'<input type="text" class="form-control" name="newPassword" required maxlength="15">' + "</td><td>" +
	'<input type="submit" value="Submit" form="formEdit" formaction="/editUser">' +
	'<input type="submit" value="Exit" form="formEdit" formaction="/resetAdmin" formnovalidate>' + "</td></tr>";
	document.getElementsByClassName("urow")[1].innerHTML = output;
	// var url = "/editUser";
	// var xmlhttp = new XMLHttpRequest();
	// var params="userid=" + userid[0].innerHTML + "&username=" + username[0].innerHTML + "&userLogin=" + userLogin[0].innerHTML;
	// xmlhttp.open("POST", url, true);
	// xmlhttp.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
	// xmlhttp.onreadystatechange = function() {
	// 		if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
	// 	}
	// }
	// xmlhttp.send(params);
	//alert("Inside Function");
}
