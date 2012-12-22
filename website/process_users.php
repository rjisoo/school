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

$fname = check_input($_POST['first'], "Please go back and enter first name!");
$lname = check_input($_POST['last'], "Please go back and enter last name!");
$tier = check_input($_POST['tier'], "Please go back and select a tier!");
$date = date("Y-m-d");
$standing = "n";
$id;

$query = "INSERT INTO users(first_name, last_name, start_subscription, acct_standing) VAlUES (?, ?, ?, ?)";

if(!($stmt = $db->prepare($query))){
     echo "Prepare failed: (" . $mysqli->errno . ") " . $mysqli->error;
}

if(!$stmt->bind_param('ssss', $fname, $lname, $date, $standing)){
    echo "Binding parameters failed: (" . $stmt->errno . ") " . $stmt->error;
}

if (!$stmt->execute()) {
    echo "Execute failed: (" . $stmt->errno . ") " . $stmt->error;
} else { #if it gets to this part, it has been successfully added to the databse
    echo "Added: <br>";
    echo $fname."<br>";
    echo $lname."<br>";
    echo $tier."<br>";
    echo "On ".$date."<br>";
    echo "To database!";
    $id = $db->insert_id;
    echo $id."<br>";
    $stmt->close();
}

$stmt = $db->prepare("insert into user_subs_to(user_id, tier_name) values (?,?)");
$stmt->bind_param('is', $id, $tier);
$stmt->execute();
$stmt->close();

?>
<br>
<br>
Go back to 
<a href="http://web.engr.oregonstate.edu/~coreyg/add_users.php">Add Users</a>
or 
<a href="http://web.engr.oregonstate.edu/~coreyg/main.html">Home</a>
<br>
<?php $db->close(); ?>
</body></html>
