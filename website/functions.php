<?php
function cents(){
    $i = 0;
    while ($i < 100){
        if ($i < 10)
            printf("<option>%02s</option>", $i);
        else 
            printf("<option>%01s</option>", $i); 
    $i++;
    }
}

function dollars(){
    $i = 3;
    while ($i <= 100){
        printf("<option>%01s</option>", $i);
        $i++;
    }
}

function check_input($data, $problem=''){
    # Checks if the input has any data in it
    if ($problem && strlen($data) == 0){
        die($problem);
    }
    return $data;
}
?>