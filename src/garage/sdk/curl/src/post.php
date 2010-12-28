<?php
   header('Content-type: text/plain');
   echo "<!-- You said -->\n";
   if(get_magic_quotes_gpc())
      echo stripslashes($_REQUEST['xmldata']);
   else
      echo $_REQUEST['xmldata'];

?>
