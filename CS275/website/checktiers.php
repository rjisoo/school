<?php

$tname = <<<SQL
    SELECT tier_name
    FROM `tiers`
    WHERE 1 
SQL;

if(!$tresult = $db->query($tname)){ # get list of tier names
    die('There was an error running the query [' . $db->error . ']');
}

if (mysqli_num_rows($tresult) == 0){
        echo '<br />There are no tiers in the data base.
                  <br />Loading Tier Input page...
                  <META http-equiv="REFRESH" content="3; url=http://web.engr.oregonstate.edu/~coreyg/add_tiers.php">';
}
?>