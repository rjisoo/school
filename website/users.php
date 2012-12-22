<?php
ini_set('display_errors', 'On');
?>
<!DOCTYPE html>
<html>
<body>
<?php include('dbcon.php');
?>

<h1>Information About Subscribers</h1>
<form action="view_users.php" method="post">
View By:
<select name="views">
<option value="1">Default</option>
<option value="2">Accounts: Enabled</option>
<option value="3">Accounts: Disabled</option>
<option value="4">Group by: Tiers</option>
</select><br>
<br><input type="submit" value="Show"><br><br>
</form>

<h2>Users Information</h2>

<table border="1" cellspacing="0" cellpadding="7">
<tr>
  <td>User ID</td>
  <td>First Name</td>
  <td>Last Name</td>
  <td>Date Started</td>
  <td>Sub. Standing</td>
  <td>Tier</td>
</tr>
<?php
$sql = <<<SQL
    SELECT u.user_id, u.first_name, u.last_name, u.start_subscription, u.acct_standing, s.tier_name
    FROM users u, user_subs_to s
    WHERE u.user_id = s.user_id
SQL;
if(!$result = $db->query($sql)){
    die('There was an error running the query [' . $db->error . ']');
}

while($row = $result->fetch_assoc()){
      echo "<tr><td>".$row['user_id']."</td><td>".$row['first_name']."</td><td>".$row['last_name']."</td><td>".$row['start_subscription']."</td><td>".$row['acct_standing']."</td><td>".$row['tier_name']."</td></tr>";
}
?>

</table>

<?php $db->close(); ?>

<br>
Go back to 
<a href="http://web.engr.oregonstate.edu/~coreyg/main.html">Home</a>
<br>
</body>
</html>
