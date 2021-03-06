// YOU CAN USE THIS FILE AS REFERENCE FOR SERVER DEVELOPMENT

// include the express module
var express = require("express");

// create an express application
var app = express();

// helps in extracting the body portion of an incoming request stream
var bodyparser = require('body-parser');
// apply the body-parser middleware to all incoming requests
app.use(bodyparser());

// fs module - provides an API for interacting with the file system
var fs = require("fs");

// helps in managing user sessions
var session = require('express-session');

// native js function for hashing messages with the SHA-1 algorithm
var sha1 = require('sha1');

// include the mysql module
var mysql = require("mysql");

var xml2js = require('xml2js');
var parser = new xml2js.Parser();
var theinfo;

fs.readFile(__dirname + '/sample_dbconfig.xml', function(err, data) {
	if (err) throw err;
    parser.parseString(data, function (err, result) {
		if (err) throw err;
    theinfo = result;

  var con = mysql.createConnection({
    host: theinfo.dbconfig.host[0],
    user: theinfo.dbconfig.user[0], // replace with the database user provided to you
    password: theinfo.dbconfig.password[0], // replace with the database password provided to you
    database: theinfo.dbconfig.database[0], // replace with the database user provided to you
    port: theinfo.dbconfig.port[0]
  });

con.connect(function(err) {
  if (err) {
    throw err;
  };
  console.log("Connected!");
});


// use express-session
// in memory session is sufficient for this assignment
app.use(session({
  secret: "csci4131secretkey",
  saveUninitialized: true,
  resave: false}
));

// server listens on port 9007 for incoming connections
app.listen(9007, () => console.log('Listening on port 9007!'));

// // GET method route for the favourites page.
// It serves favourites.html present in client folder
app.get('/favourites',function(req, res) {
   console.log("Request for Favourites");
   if(!req.session.value){
     res.redirect('/login');
   } else {
     res.sendFile( __dirname + "/client/" + "favourites.html");
   }
});

// GET method route for the addPlace page.
// It serves addPlace.html present in client folder
app.get('/addPlace',function(req, res) {
   console.log("Request for AddPlace");

   if(!req.session.value){
     res.redirect("/login");
   } else {
     res.sendFile( __dirname + "/client/" + "addPlace.html");
   }
});

// GET method route for the Admin page.
// It serves addPlace.html present in client folder
app.get('/admin',function(req, res) {
   console.log("Request for Admin");

   if(!req.session.value){
     res.redirect("/login");
   } else {
     res.sendFile( __dirname + "/client/" + "admin.html");
   }
});

// GET method route for the login page.
// It serves login.html present in client folder
app.get('/login',function(req, res) {
  // ADD DETAILS...
  console.log("Request for Login");
  res.sendFile( __dirname + "/client/" + "login.html");
});

// GET method to return the list of favourite places
// The function queries the table tbl_places for the list of places and sends the response back to client
app.get('/getListOfFavPlaces', function(req, res) {
  console.log("Getting list of favorite places");

  con.query('SELECT * FROM tbl_places', function(err, results){
    res.send(results);
  });
    console.log("Query Successful");
  });

app.get('/getListOfUsers', function(req, res) {
  //console.log("Getting list of users");
  con.query('SELECT * FROM tbl_accounts', function(err, results){
    //console.log(results);
    if(err) throw err;
    res.send(results);
  });
  //console.log("Query Successful");
});

// POST method to insert details of a new place to tbl_places table
app.post('/postPlace', function(req, res) {
  // ADD DETAILS...
  var rowToBeInsert = {
    place_name: req.body.placename,
    addr_line1: req.body.addressline1,
    addr_line2: req.body.addressline2,
    open_time: req.body.opentime,
    close_time: req.body.closetime,
    add_info: req.body.additionalinfo,
    add_info_url: req.body.additionalinfourl,
  }

  con.query('INSERT tbl_places SET ?', rowToBeInsert, function(err, result) {
    if(err) throw err;
    console.log("values inserted");
    res.redirect('/favourites');
  });
});

// POST method to insert details of a new user to tbl_places table
app.post('/postUser', function(req, res) {
  // ADD DETAILS...
  console.log("in postUser")
  var rowToBeInsert = {
    acc_name: req.body.newUserName,
    acc_login: req.body.newLogin,
    acc_password: sha1(req.body.newPassword),
  }
  con.query('INSERT tbl_accounts SET ?', rowToBeInsert, function(err, result) {
    if(err) throw err;
    console.log("values inserted");
    res.redirect('/admin');
  });
});

app.post('/resetAdmin', function(req, res) {
  // ADD DETAILS...
  console.log("Resetting");
  res.redirect('/admin');
});

app.post('/deleteUser', function(req, res) {
  // ADD DETAILS...
  console.log("Request for DeleteUser");
  //console.log(req.body);
  var uid = req.body.userid;
  console.log("Uid: " + uid);
  con.query('DELETE FROM tbl_accounts WHERE acc_id=' + '"' + uid + '"', function(err, results){
    if(err) throw err;
    //res.send(results);
  });
  console.log("Query Successful");
  res.redirect('/admin');
});

app.post('/editUser', function(req, res) {
  // ADD DETAILS...
  console.log("Request for EditUser");
  console.log(req.body);
  // Finish
  res.redirect('/admin');
});

// POST method to validate user login
// upon successful login, user session is created
app.post('/validateLoginDetails', function(req, res) {
  // ADD DETAILS...
  console.log("In validate Login details");
  var flag = false;
  var index = -1;

  var username = req.body.user;
  var password = req.body.password;

    console.log("Connected!");
    console.log("User: " + username + " Pass: " + password);
    con.query('SELECT acc_password FROM tbl_accounts WHERE acc_login=' + '"' + username + '"', function(err, result) {
      if(err) { throw err; };
      if (result.length == 0){
        console.log("No entries in database");
        res.redirect('/login?login=failed');
      } else if(result[0].acc_password != sha1(password)){
        console.log("Wrong password");
        res.redirect('/login?login=failed');
      } else {
        req.session.value = 1;
        res.redirect('/favourites');
      }
  });
});

// log out of the application
// destroy user session
app.get('/logout', function(req, res) {
  // ADD DETAILS...
  console.log("Request for Logout");
  if(!req.session.value){
    res.send("Session not started, cannot logout.");
  } else {
    req.session.destroy();
    res.redirect("/login");
  }
});

// middle ware to server static files
app.use('/client', express.static(__dirname + '/client'));


// function to return the 404 message and error to client
app.get('*', function(req, res) {
  console.log("Invalid Request");
  res.send("Not Found", 404);
  // add details
});

});
});
