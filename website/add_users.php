<?php ini_set('display_errors', 'On'); ?>
<!DOCTYPE html>
<html><body>
<?php
include('dbcon.php');
include('checktiers.php');
?>
<form action="process_users.php" method="post">

<h1>New User Addittion</h1>
First Name: 
<input name="first" type="text">
<br>
Last Name: 
<input name="last" type="text">
<br>

<br>
Select Tier Type: 

<select name="tier">
<?php
while($row = $tresult->fetch_assoc()){
    echo "<option>" . $row['tier_name'] . '</option>';
}
?>
</select>

<br>
<br>
<input type="submit" value="Submit">
</form>

<?php $db->close(); ?>
</body></html>