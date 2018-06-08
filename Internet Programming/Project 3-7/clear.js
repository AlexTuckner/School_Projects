
var mysql = require("mysql");

var con = mysql.createConnection({
  host: "cse-curly.cse.umn.edu",
  user: "C4131S18U129", // replace with the database user provided to you
  password: "134", // replace with the database password provided to you
  database: "C4131S18U129", // replace with the database user provided to you
  port: 3306
});

con.connect(function(err) {
  if(err) throw err;
  con.query("DROP TABLE tbl_accounts", function(err,result){
    console.log("table dropped");
  });
});
