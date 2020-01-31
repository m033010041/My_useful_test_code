<?php
header('Content-Type: application/json');

$dir          = "./"; //path

$list = array(); //main array

if(is_dir($dir)){
    if($dh = opendir($dir)){
        while(($content = readdir($dh)) != false){

            if($content == "." or $content == ".."){
                //...
	    } else { //create object with two fields
		    if(is_file($content))
		    {
		    }
		    else if(is_dir($content))
		    {
		    }
                $list3 = array(
                'file' => $content,
		'size' => filesize($content),
	        'modified_time' => filemtime($content));
                array_push($list, $list3);
            }
        }
    }

    $return_array = array('files'=> $list);

    echo json_encode($return_array);
}

?>
