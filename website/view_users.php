<?php ini_set('display_errors', 'On'); ?>
<!DOCTYPE html>
<html><body>
<?php
include('dbcon.php');

$select = $_POST['views'];
?>

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
switch ($select){
  
    default:
        $sql1 = <<<SQL
        SELECT u.user_id, u.first_name, u.last_name, u.start_subscription, u.acct_standing, s.tier_name
        FROM users u, user_subs_to s
        WHERE u.user_id = s.user_id
SQL;
        if(!$result = $db->query($sql1)){
            die('There was an error running the query [' . $db->error . ']');
        }
        while($row = $result->fetch_assoc()){
            echo "<tr><td>".$row['user_id']."</td><td>".$row['first_name']."</td><td>".$row['last_name']."</td><td>".$row['start_subscription']."</td><td>".$row['acct_standing']."</td><td>".$row['tier_name']."</td></tr>";
        }
        break;
        
    case 2:
        $sql2 = <<<SQL
        SELECT u.user_id, u.first_name, u.last_name, u.start_subscription, u.acct_standing, s.tier_name
        FROM users u, user_subs_to s
        WHERE u.user_id = s.user_id AND acct_standing='y'
SQL;
        if(!$result = $db->query($sql2)){
            die('There was an error running the query [' . $db->error . ']');
        }
        while($row = $result->fetch_assoc()){
            echo "<tr><td>".$row['user_id']."</td><td>".$row['first_name']."</td><td>".$row['last_name']."</td><td>".$row['start_subscription']."</td><td>".$row['acct_standing']."</td><td>".$row['tier_name']."</td></tr>";
        }
        break;
        
        case 3:
        $sql3 = <<<SQL
        SELECT u.user_id, u.first_name, u.last_name, u.start_subscription, u.acct_standing, s.tier_name
        FROM users u, user_subs_to s
        WHERE u.user_id = s.user_id AND acct_standing='n'
SQL;
        if(!$result = $db->query($sql3)){
            die('There was an error running the query [' . $db->error . ']');
        }
        while($row = $result->fetch_assoc()){
            echo "<tr><td>".$row['user_id']."</td><td>".$row['first_name']."</td><td>".$row['last_name']."</td><td>".$row['start_subscription']."</td><td>".$row['acct_standing']."</td><td>".$row['tier_name']."</td></tr>";
        }
        break;
        
        case 4:
        $sql4 = <<<SQL
        SELECT u.user_id, u.first_name, u.last_name, u.start_subscription, u.acct_standing, s.tier_name
        FROM users u, user_subs_to s
        WHERE u.user_id = s.user_id
        GROUP BY s.tier_name, u.user_id
SQL;
        if(!$result = $db->query($sql4)){
            die('There was an error running the query [' . $db->error . ']');
        }
        while($row = $result->fetch_assoc()){
            echo "<tr><td>".$row['user_id']."</td><td>".$row['first_name']."</td><td>".$row['last_name']."</td><td>".$row['start_subscription']."</td><td>".$row['acct_standing']."</td><td>".$row['tier_name']."</td></tr>";
        }
        break;

}
?>
</table>

<?php $db->close(); ?>
<br>
Go back to 
<a href="http://web.engr.oregonstate.edu/~coreyg/users.php">View Users</a>
or 
<a href="http://web.engr.oregonstate.edu/~coreyg/main.html">Home</a>
<br>

</body></html>