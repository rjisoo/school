<?php ini_set('display_errors', 'On'); ?>
<!DOCTYPE html>
<html><body>
<?php

# connects to the DB
include('dbcon.php');

#includes some check functions for data validation
include('functions.php');

$state = check_input($_POST['state'], "Please go back and select a state!");
$tier = check_input($_POST['tier'], "Please go back and select a state!");
$size = $_POST['space'];
$assigned = "n";
$id;

$query = "INSERT INTO storage(space_avail, storage_assigned) VALUES(?,?)";
# Begins prepared statements
if(!($stmt = $db->prepare($query))){
     echo "Prepare failed: (" . $mysqli->errno . ") " . $mysqli->error;
}
if(!$stmt->bind_param('ss', $size, $assigned)){
    echo "Binding parameters failed: (" . $stmt->errno . ") " . $stmt->error;
}

if (!$stmt->execute()) { #adds to storage table
    echo "Execute failed: (" . $stmt->errno . ") " . $stmt->error;
} else {
    echo "You selected: ".$state."<br>";
    echo "You selected: ".$tier."<br>";
    echo "You selected: ".$size."<br>";
    echo "Added to database!";
    $id = $db->insert_id;
    echo $id."<br>";
    $stmt->close();
}


$query2 = "INSERT INTO stor_belongs_tier(stor_id, tier_name) VALUES(?,?)";
$stmt = $db->prepare($query2);
$stmt->bind_param('is', $id, $tier);
$stmt->execute();
$stmt->close();

$query3 = "INSERT INTO stor_has_location(stor_id, state_name) values(?,?)";
$stmt = $db->prepare($query3);
$stmt->bind_param("is", $id, $state);
$stmt->execute();
$stmt->close();
?>
<br>
<br>
Go back to
<a href="http://web.engr.oregonstate.edu/~coreyg/add_storage.php">Add Storage</a>
or
<a href="http://web.engr.oregonstate.edu/~coreyg/main.html">Home</a>
<br>
<?php $db->close(); ?>
</body></html>
