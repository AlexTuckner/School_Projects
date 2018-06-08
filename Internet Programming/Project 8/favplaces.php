<?php
  session_start();
  // ini_set('display_errors', '1');
  // ini_set('allow_url_include','1');
  // error_reporting(E_ALL);
  // Get data from the login
  $user = $_POST['username'];
  $pass = $_POST['password'];
  $fid = $_POST['filterId'];
  $fplacename = $_POST['filterPlaceName'];


  // echo "fid: ".$fid." fPlace: ".$fplacename;
  //include the database
  include("database.php");
  $conn = new mysqli($db_host, $db_username, $db_password, $db_name);

  if(isset($user) && isset($pass)){

    $_SESSION["username"] = $user;
    $_SESSION["password"] = $pass;

    if ($conn->connect_error) {
      echo die("Could not connect to database");
    } else {
      $stringquery = 'SELECT * FROM tbl_accounts WHERE acc_login="'.$user.'" AND acc_password="'.sha1($pass).'"';
      // echo $stringquery." Password=$pass   -- ";
      $result = $conn->query($stringquery);
      if($result->num_rows == 0){
        header("Location: http://www-users.cselabs.umn.edu/~tuckn016/login.php");
      }
    }
  } else if(isset($_SESSION['username']) && isset($_SESSION['password'])){
  } else {
    header("Location: http://www-users.cselabs.umn.edu/~tuckn016/login.php");
  }

?>

<!doctype html>
<html lang="en">
  <head>
      <meta charset="utf-8">
      <meta name="viewport" content="width=device-width, initial-scale=1">
      <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
      <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js"></script>
      <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
      <link rel="stylesheet" href="style.css">
      <title>My favourite places</title>
  </head>

  <body>
      <nav class="navbar navbar-default">
        <div class="container-fluid">
          <ul class="nav navbar-nav">
              <li><a href="/~tuckn016/favplaces.php"><b>Favourite places</b></a></li>
              <li><a href="/~tuckn016/logout.php"><b>Logout</b></a></li>
              <?php print('<li><a href="/~tuckn016/favplaces.php"><b> Welcome: '.$_SESSION['username']."</b></a></li>")?>
          </ul>
        </div>
      </nav>
      <div>
        <h1><b> Favorite Places </b></h1>
      </div>
      <div class="container">
        <table class="table" id="myFavTable">
          <thead>
            <tr>
              <th scope="col">ID</th>
              <th scope="col">Name</th>
              <th scope="col">Address</th>
              <th scope="col">Open / Close</th>
              <th scope="col">Information</th>
              <th scope="col">URL</th>
            </tr>
          </thead>
          <tbody id="myFavTableBody">
            <?php
            if ($conn->connect_error) {
              echo die("Could not connect to database");
            } else {
              if (isset($fid) && $fid != '') {
                $stringquery = 'SELECT * FROM tbl_places WHERE place_id="'.$fid.'"';
              } else if (isset($fplacename) && $fplacename != ''){
                $stringquery = 'SELECT * FROM tbl_places WHERE place_name="'.$fplacename.'"';
              } else {
                $stringquery = 'SELECT * FROM tbl_places';
              }

              $result = $conn->query($stringquery);
              $i = 0;
              print("<tr> </tr>");
              while($row = mysqli_fetch_row($result)) {
                $i = 0;
                print("<tr>");
                foreach ($row as $value) {
                  if($i == 0 || $i == 1 || $i == 6 || $i == 7 )
                    print("<td>$value</td>");
                  if ($i == 2 || $i == 4) {
                    print("<td>$value <br>");
                  }
                  if ($i == 3 || $i == 5) {
                    print("$value </td>");
                  }
                  $i += 1;
                } // end Foreach
                print("</tr>");
              } // end while
            }
            ?>
          </tbody>
        </table>
      </div>

      <div>
        <form name = "validate" method = "post" action="http://www-users.cselabs.umn.edu/~tuckn016/favplaces.php">
          <h1> <b> Filter Criteria </b> </h1>
          <tr>
              <td class="col-md-6">Place ID:</td>
              <td class="col-md-6">
                <div class="form-group">
                  <input type="text" class="form-control" name="filterId" maxlength="30">
                </div>
              </td>
          </tr>

          <tr>
              <td class="col-md-6">Place Name: </td>
              <td class="col-md-6">
                <div class="form-group">
                  <input type="text" class="form-control" name="filterPlaceName" maxlength="30">
                </div>
              </td>
          </tr>
          <tr>
            <div class="col-md-1"></div>
            <div class="col-md-10">

              <input type="submit" value="Submit" class="btn btn-primary btn-block">
            </form>
            </div>
            <div class="col-md-1"></div>
          </tr>
      </div>
  </body>
</html>
