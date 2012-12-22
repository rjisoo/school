<?php ini_set('display_errors', 'On'); ?>
<!DOCTYPE html>
<html><body>
<?php
include('dbcon.php');
include('checktiers.php');
?>

<h1>Storage Assignment</h1>

<?php
$query = "select stor_id from stor_is_assigned where assigned=?";
$assigned='n';
$stmt= $db->prepare($query);
$stmt->bind_param('s', $assigned);
$stmt->execute();
$stmt->bind_result($col1);
?>
Storage ID:
<select>
<?php
while ($stmt->fetch()){
        echo "<option>".$col1."</option>";
}
echo "</select>";
$stmt->close();


?>




</body></html>