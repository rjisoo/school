<?php
ini_set('display_errors', 'On');
?>
<!DOCTYPE html>
<html><body>
<?php include('dbcon.php'); ?>

<h2>Storage Information</h2>

<?php
$select = $_POST['views'];
?>

<?php

switch ($select){
    default:
        $sql1 = <<<SQL
        SELECT storage.stor_id, storage.space_avail, b.tier_name, l.state_name
        FROM  `storage` , stor_belongs_tier b, stor_has_location l
        WHERE storage.stor_id = b.stor_id AND storage.stor_id = l.stor_id
SQL;
        if(!$result = $db->query($sql1)){
            die('There was an error running the query [' . $db->error . ']');
        }
        echo'
            <table border="1" cellspacing="0" cellpadding="7">
                <tr>
                    <td>Sotrage ID</td>
                    <td>Space Allotment (GB)</td>
                    <td>Tier</td>
                    <td>Location</td>
                </tr>';
        while($row = $result->fetch_assoc()){
            echo "<tr><td>".$row['stor_id']."</td><td>".$row['space_avail']."</td><td>".$row['tier_name']."</td><td>".$row['state_name']."</td></tr>";
        }
        break;
        
    case 2:
        $sql2 = <<<SQL
        SELECT storage.stor_id, storage.space_avail, b.tier_name, l.state_name
        FROM  `storage` , stor_belongs_tier b, stor_has_location l
        WHERE storage.stor_id = b.stor_id AND storage.stor_id = l.stor_id
        GROUP BY storage.space_avail, storage.stor_id
SQL;
        if(!$result = $db->query($sql2)){
            die('There was an error running the query [' . $db->error . ']');
        }
        echo'
            <table border="1" cellspacing="0" cellpadding="7">
                <tr>
                    <td>Space Allotment (GB)</td>
                    <td>Sotrage ID</td>
                    <td>Tier</td>
                    <td>Location</td>
                </tr>';
        while($row = $result->fetch_assoc()){
            echo "<tr><td>".$row['space_avail']."</td><td>".$row['stor_id']."</td><td>".$row['tier_name']."</td><td>".$row['state_name']."</td></tr>";
        }
        break;
        
    case 3:
        $sql3 = <<<SQL
        SELECT storage.stor_id, storage.space_avail, b.tier_name, l.state_name
        FROM  `storage` , stor_belongs_tier b, stor_has_location l
        WHERE storage.stor_id = b.stor_id AND storage.stor_id = l.stor_id
        GROUP BY l.state_name, storage.stor_id
SQL;
        if(!$result = $db->query($sql3)){
            die('There was an error running the query [' . $db->error . ']');
        }
        
        echo'
            <table border="1" cellspacing="0" cellpadding="7">
                <tr>
                    <td>Location</td>
                    <td>Sotrage ID</td>
                    <td>Space Allotment (GB)</td>
                    <td>Tier</td>
                </tr>';
        while($row = $result->fetch_assoc()){
            echo "<tr><td>".$row['state_name']."</td><td>".$row['stor_id']."</td><td>".$row['space_avail']."</td><td>".$row['tier_name']."</td></tr>";
        }
        break;
        
    case 4:
        $sql4 = <<<SQL
        SELECT storage.stor_id, storage.space_avail, b.tier_name, l.state_name
        FROM  `storage` , stor_belongs_tier b, stor_has_location l
        WHERE storage.stor_id = b.stor_id AND storage.stor_id = l.stor_id
        GROUP BY b.tier_name, storage.stor_id
SQL;
        if(!$result = $db->query($sql4)){
            die('There was an error running the query [' . $db->error . ']');
        }
        echo'
            <table border="1" cellspacing="0" cellpadding="7">
                <tr>
                    <td>Tier</td>
                    <td>Sotrage ID</td>
                    <td>Space Allotment (GB)</td>
                    <td>Location</td>
                </tr>';
        while($row = $result->fetch_assoc()){
            echo "<tr><td>".$row['tier_name']."</td><td>".$row['stor_id']."</td><td>".$row['space_avail']."</td><td>".$row['state_name']."</td></tr>";
        }
        break; 
}
?>



<?php $db->close(); ?>
</table>
<br>
Go back to 
<a href="http://web.engr.oregonstate.edu/~coreyg/main.html">Home</a>
<br>
</body></hmtl>