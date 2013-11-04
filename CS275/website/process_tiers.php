<?php ini_set('display_errors', 'On'); ?>
<!DOCTYPE html>
<html><body>

<?php
include('dbcon.php');
#$db = new mysqli('oniddb.cws.oregonstate.edu', 'coreyg-db', '89zkgigYFzMJyfqn', 'coreyg-db');

#if($db->connect_errno > 0){
#    die('Unable to connect to database [' . $db->connect_error . ']');
#}
# Verbose code checking.
#echo "success!<br>";
include('functions.php');

$tier = check_input($_POST['tier'], "Please go back and enter a tier name!");
$dollars = $_POST['dollars'];
$cents = $_POST['cents'];
$cost = $dollars.".".$cents;

$space = $_POST['space'];
$years = $_POST['years'];

#Begin interting into databse operations
$query = "INSERT INTO tiers(tier_name, cost, sub_length, space_alloted) VAlUES (?, ?, ?, ?)";

if(!($stmt = $db->prepare($query))){
     echo "Prepare failed: (" . $mysqli->errno . ") " . $mysqli->error;
}

if(!$stmt->bind_param('ssii', $tier, $cost, $years, $space)){
    echo "Binding parameters failed: (" . $stmt->errno . ") " . $stmt->error;
}

if (!$stmt->execute()) {
    echo "Execute failed: (" . $stmt->errno . ") " . $stmt->error;
} else { #if it gets to this part, it has been successfully added to the databse
    print "Added: <br>".$tier."<br>".
    "$".$cost."<br>".
    $space." Gigabytes<br>".
    $years." years<br>
    To tiers table.";
} 
?>

<br>
<br>
Go back to
<a href="http://web.engr.oregonstate.edu/~coreyg/add_tiers.php">Add Tiers</a>
or
<a href="http://web.engr.oregonstate.edu/~coreyg/main.html">Home</a>
<br>
<?php $db->close(); ?>
</body></html>
