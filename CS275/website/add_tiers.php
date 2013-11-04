<?php ini_set('display_errors', 'On'); ?>
<!DOCTYPE html>
<html><body>

<?php
include('functions.php');

?>

<h1>New Subscription Addition</h1>
<form action="process_tiers.php" method="post">
    Tier Name: 
<input type="text" name="tier">
<br>
	
    Tier Cost (per year): $
<select name="dollars">
<?php
    dollars();
?>
</select>
<select name="cents">
<?php
    cents();
?>
</select>

<br>
    Space Alloted (Gigabytes): 
<select name="space">
<?php
    $i = 1;
    while ($i <= 10){
        printf("<option>%01s</option>", $i);
    $i++;
    }
?>
</select>

<br>
    Subscription Length (Years): 
<select name="years">
<?php
    $i = 1;
    while ($i <= 10){
        printf("<option>%01s</option>", $i);
    $i++;
    }
?>

</select>
<br>
<br>
<input type="submit" value="Submit">
</form>

</body></html>