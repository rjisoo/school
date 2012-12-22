<?php ini_set('display_errors', 'On'); ?>

<!DOCTYPE html>
<html><body>
<?php
include('dbcon.php');
include('checktiers.php');

$stname = <<<SQL
    SELECT state_name
    FROM `states`
    WHERE 1
SQL;

if(!$stresult = $db->query($stname)){ # Get list of state names
    die('There was an error running the query [' . $db->error . ']');
}
?>

<form action="process_storage.php" method="post">

<h1>New Storage Addittion</h1>
Storage Location: 
<select name="state">
<?php
while($row = $stresult->fetch_assoc()){
    echo "<option>".$row['state_name'] . '</option>';
}
?>
</select>

<br />

Select Tier Type: 

<select name="tier">
<?php
    while($row = $tresult->fetch_assoc()){ #print out tier names for options
        echo "<option>" . $row['tier_name'] . '</option>';
    }
?>
</select>

<br>
Space to Allot (Gigabytes):
<select name="space">
<?php
    $i = 1;
    while ($i <= 10){ #print out values for space_allotted values
        printf("<option>%01s</option>", $i);
        $i++;
    }
?>
</select>

<br /><input type="submit" value="Submit" >
</form>


<?php $db->close(); ?>
</body></html>