<?php
$db = new mysqli('oniddb.cws.oregonstate.edu', 'coreyg-db', '8b1wf4rFITezPd3q', 'coreyg-db');

if($db->connect_errno > 0){
    die('Unable to connect to database [' . $db->connect_error . ']');
}
# Verbose code checking.
#echo "success!<br>";
?>
