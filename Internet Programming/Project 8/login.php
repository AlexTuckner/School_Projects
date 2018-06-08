
<!doctype html>
<html lang="en">
  <head>
      <meta charset="utf-8">
      <meta name="viewport" content="width=device-width, initial-scale=1">
      <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
      <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js"></script>
      <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
      <link rel="stylesheet" type="text/css" href="style.css">
      <title>Welcome to Node.js</title>
  </head>

  <body>
      <div class="jumbotron">
        <h1>Login Page</h1>
        <p>Please enter your user name and password. Both are case sensitive.</p>
      </div>

      <div>
        <form name = "validate" method = "post" action="http://www-users.cselabs.umn.edu/~tuckn016/favplaces.php">
          <tr>
              <td class="col-md-6">User:</td>
              <td class="col-md-6">
                <div class="form-group">
                  <input type="text" class="form-control" name="username" required maxlength="30">
                </div>
              </td>
          </tr>

          <tr>
              <td class="col-md-6">Password: </td>
              <td class="col-md-6">
                <div class="form-group">
                  <input type="text" class="form-control" name="password" required maxlength="30">
                </div>
              </td>
          </tr>
      </div>

      <div class="row">
        <div class="col-md-1"></div>
        <div class="col-md-10">

          <input type="submit" value="Submit" class="btn btn-primary btn-block">
        </form>
        </div>
        <div class="col-md-1"></div>
      </div>
  </body>
</html>
