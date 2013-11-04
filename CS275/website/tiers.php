<?php
ini_set('display_errors', 'On');
?>
<!DOCTYPE html>
<html>
<body>

<h1>Information About Subscriptions</h1><br>

<h2>Subscriptions Information</h2>
<table border="1" cellspacing="0" cellpadding="7">
<tr>
  <td>Subscription Name</td>
  <td>Cost (per year)</td>
  <td>Subscription Length (Years)</td>
  <td>Space Aolloted (GB)</td>
</tr>
<?php
include('dbcon.php');

$sql = <<<SQL
    SELECT tier_name, cost, sub_length, space_alloted
    FROM `tiers`
SQL;
if(!$result = $db->query($sql)){
    die('There was an error running the query [' . $db->error . ']');
}

while($row = $result->fetch_assoc()){
      echo "<tr><td>".$row['tier_name']."</td><td>$".$row['cost']."</td><td>".$row['sub_length']."</td><td>".$row['space_alloted']."</td></tr>";
}
?>
</table>

<?php $db->close(); ?>
<br>
Go back to 
<a href="http://web.engr.oregonstate.edu/~coreyg/main.html">Home</a>
<br>
</body></html>
