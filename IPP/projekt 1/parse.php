<?php
    ini_set('display_errors', 'stderr');
    if ($argc == 1){
        Load();
        echo("</program>\n");
        exit(0); //OK
    }
    elseif ($argc == 2){
        if ($argv[1] == "--help"){
            echo("Usage: parser.php [options] <inputFile>\n");
            exit (0); //OK
        }
        else{
            exit (10); // missing parameter or forbidden combination of parameters
        }
    }
    else{
        exit(10); // missing parameter or forbidden combination of parameters
    }
    function Load(){
        $header = false;
        $counter = 0;
        while ($line = fgets(STDIN)){
            $line = preg_replace('/\s+/', ' ', $line); // remove white spaces
            RemoveComments($line);
            if(strlen($line) > 0){
                if ($header == false){
                    if ($line == ".IPPcode21"){
                        $header = true;
                        echo("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
                        echo("<program language=\"IPPcode21\">\n");
                    }
                    else{
                    exit(21); // missing header
                    }
                }
                else{
                    $item = explode(' ', $line); 
                    if (strlen($item[0]) > 0){
                        $counter++;
                        switch(strtoupper($item[0])){
                            case 'MOVE':
                            case 'INT2CHAR':
                            case 'STRLEN':
                            case 'TYPE':
                                if (count($item) == 3){
                                    echo("\t<instruction order=\"".$counter."\" opcode=\"".strtoupper($item[0])."\">\n");
                                    if (preg_match("/\b(LF|GF|TF)@[a-zA-Z-_$&%*!?][a-zA-Z-_$&%*!?0-9]*\b/", $item[1])){
                                        $split = explode("@",$item[2]);
                                        $load = $split;
                                        array_splice($load,0,1);
                                        $load = implode("@",$load);
                                        $split = $split[0];
                                        if (preg_match("/\b(LF|GF|TF)@[a-zA-Z-_$&%*!?][a-zA-Z-_$&%*!?0-9]*\b/", $item[2])){
                                            echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                            echo("\t\t<arg2 type=\"var\">$item[2]</arg2>\n");
                                            echo("\t</instruction>\n");
                                        }
                                        elseif (preg_match("/\b(nil)@(nil)\b/", $item[2])){
                                            echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                            echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                            echo("\t</instruction>\n");
                                        }
                                        elseif (preg_match("/\b(bool)@(true|false)\b/", $item[2])){
                                            echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                            echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                            echo("\t</instruction>\n");
                                        }
                                        elseif (preg_match("/\b(int)\b/", $split)){
                                            echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                            echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                            echo("\t</instruction>\n");
                                        }
                                        elseif (preg_match("/\bstring@((LF|TF|GF)@[a-zA-Z-_$&%*!?][a-zA-Z0-9-_$&%*!?])*|([a-zA-Z0-9-_$<>&%*!?]|\\\[0-9]{3})*\b/", $item[2])){
                                            echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                            echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                            echo("\t</instruction>\n");
                                        }
                                        else{echo($item[1]."\n");
                                            exit(23); //wrong parameter
                                        }
                                    }
                                    else{
                                        exit(23); //wrong parameter
                                    }
                                }
                                else{
                                    exit(23); //wrong count of parameters
                                }
                                break;
                            case 'CREATEFRAME':                           
                            case 'PUSHFRAME':
                            case 'POPFRAME':
                            case 'RETURN':
                            case 'BREAK':
                                if (count($item) == 1){
                                    echo("\t<instruction order=\"".$counter."\" opcode=\"".strtoupper($item[0])."\">\n");
                                    echo("\t</instruction>\n");
                                }
                                else{
                                    exit(23); //wrong count of parameters
                                }
                                break;
                            case 'DEFVAR':
                            case 'POPS':
                                if (count($item) == 2){
                                    echo("\t<instruction order=\"".$counter."\" opcode=\"".strtoupper($item[0])."\">\n");
                                    if (preg_match("/\b(LF|GF|TF)@[a-zA-Z-_$&%*!?][a-zA-Z-_$&%*!?0-9]*\b/", $item[1])){
                                        echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                        echo("\t</instruction>\n");
                                    }
                                    else{
                                        exit(23); //wrong parameter
                                    }
                                }
                                else{
                                    exit(23); //wrong count of parameters
                                }
                                break;
                            case 'CALL':
                            case 'LABEL':
                            case 'JUMP':
                                if (count($item) == 2){
                                    echo("\t<instruction order=\"".$counter."\" opcode=\"".strtoupper($item[0])."\">\n");
                                    if (preg_match("/\b[a-zA-Z-_$&%*!?][a-zA-Z-_$&%*!?0-9]*\b/", $item[1])){
                                        echo("\t\t<arg1 type=\"label\">$item[1]</arg1>\n");
                                        echo("\t</instruction>\n");
                                    }
                                    else{
                                        exit(23); //wrong parameter
                                    }
                                }
                                else{
                                    exit(23); //wrong count of parameters
                                }
                                break;
                            case 'PUSHS':
                            case 'WRITE':
                            case 'EXIT':
                            case 'DPRINT':
                                if (count($item) == 2){
                                    echo("\t<instruction order=\"".$counter."\" opcode=\"".strtoupper($item[0])."\">\n");
                                    $split = explode("@",$item[1]);
                                    $load = $split;
                                    array_splice($load,0,1);
                                    $load = implode("@",$load);
                                    $split = $split[0];
                                    if (preg_match("/\b(LF|GF|TF)@[a-zA-Z-_$&%*!?][a-zA-Z-_$&%*!?0-9]*\b/", $item[1])){                                       
                                        echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                        echo("\t</instruction>\n");
                                    }
                                    elseif (preg_match("/\b(nil)@(nil)\b/", $item[1])){             
                                        echo("\t\t<arg1 type=\"".$split."\">$load</arg1>\n");
                                        echo("\t</instruction>\n");
                                    }
                                    elseif (preg_match("/\b(bool)@(true|false)\b/", $item[1])){             
                                        echo("\t\t<arg1 type=\"".$split."\">$load</arg1>\n");
                                        echo("\t</instruction>\n");
                                    }
                                    elseif (preg_match("/\b(int)\b/", $split)){             
                                        echo("\t\t<arg1 type=\"".$split."\">$load</arg1>\n");
                                        echo("\t</instruction>\n");
                                    }
                                    elseif (preg_match("/\b(string)@((LF|TF|GF)@[a-zA-Z-_$&%*!?][a-zA-Z0-9-_$&%*!?])*|([a-zA-Z0-9-_$<>&%*!?]|\\\[0-9]{3})*\b/", $item[1])){             
                                        echo("\t\t<arg1 type=\"".$split."\">$load</arg1>\n");
                                        echo("\t</instruction>\n");
                                    }
                                    else{ 
                                        exit(23); //wrong parameter
                                    }
                                }
                                else{
                                    exit(23); //wrong count of parameters
                                }
                                break;
                            case 'ADD':
                            case 'SUB':
                            case 'MUL':                           
                            case 'IDIV':
                            case 'LT':
                            case 'GT':
                            case 'EQ':              
                            case 'AND':
                            case 'OR':
                            case 'NOT':
                            case 'STRI2INT':
                            case 'CONCAT':
                            case 'GETCHAR':
                            case 'SETCHAR':
                                if (count($item) == 4){
                                    echo("\t<instruction order=\"".$counter."\" opcode=\"".strtoupper($item[0])."\">\n");
                                    if (preg_match("/\b(LF|GF|TF)@[a-zA-Z-_$&%*!?][a-zA-Z-_$&%*!?0-9]*\b/", $item[1])){
                                        $split = explode("@",$item[2]);
                                        $load = $split;
                                        array_splice($load,0,1);
                                        $load = implode("@",$load);
                                        $split = $split[0];
                                        if (preg_match("/\b(LF|GF|TF)@[a-zA-Z-_$&%*!?][a-zA-Z-_$&%*!?0-9]*\b/", $item[2])){
                                            $split1 = explode("@",$item[3]);
                                            $load1 = $split1;
                                            array_splice($load1,0,1);
                                            $load1 = implode("@",$load1);
                                            $split1 = $split1[0];
                                            if (preg_match("/\b(LF|GF|TF)@[a-zA-Z-_$&%*!?][a-zA-Z-_$&%*!?0-9]*\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"var\">$item[2]</arg2>\n");
                                                echo("\t\t<arg3 type=\"var\">$item[3]</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\b(nil)@(nil)\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"var\">$item[2]</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\b(bool)@(true|false)\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"var\">$item[2]</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\b(int)\b/", $split1)){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"var\">$item[2]</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\bstring@((LF|TF|GF)@[a-zA-Z-_$&%*!?][a-zA-Z0-9-_$&%*!?])*|([a-zA-Z0-9-_$<>&%*!?]|\\\[0-9]{3})*\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"var\">$item[2]</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            else{
                                            exit(23); //wrong parameter
                                            }
                                        }
                                        elseif(preg_match("/\b(nil)@(nil)\b/", $item[2])){
                                            $split1 = explode("@",$item[3]);
                                            $load1 = $split1;
                                            array_splice($load1,0,1);
                                            $load1 = implode("@",$load1);
                                            $split1 = $split1[0];
                                            if (preg_match("/\b(LF|GF|TF)@[a-zA-Z-_$&%*!?][a-zA-Z-_$&%*!?0-9]*\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"var\">$item[3]</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\b(nil)@(nil)\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\b(bool)@(true|false)\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\b(int)\b/", $split1)){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\bstring@((LF|TF|GF)@[a-zA-Z-_$&%*!?][a-zA-Z0-9-_$&%*!?])*|([a-zA-Z0-9-_$<>&%*!?]|\\\[0-9]{3})*\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            else{
                                            exit(23); //wrong parameter
                                            }
                                        }
                                        elseif(preg_match("/\b(bool)@(true|false)\b/", $item[2])){
                                            $split1 = explode("@",$item[3]);
                                            $load1 = $split1;
                                            array_splice($load1,0,1);
                                            $load1 = implode("@",$load1);
                                            $split1 = $split1[0];
                                            if (preg_match("/\b(LF|GF|TF)@[a-zA-Z-_$&%*!?][a-zA-Z-_$&%*!?0-9]*\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"var\">$item[3]</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\b(nil)@(nil)\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\b(bool)@(true|false)\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\b(int)\b/", $split1)){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\bstring@((LF|TF|GF)@[a-zA-Z-_$&%*!?][a-zA-Z0-9-_$&%*!?])*|([a-zA-Z0-9-_$<>&%*!?]|\\\[0-9]{3})*\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            else{
                                            exit(23); //wrong parameter
                                            }
                                        }
                                        elseif(preg_match("/\b(int)\b/", $split)){
                                            $split1 = explode("@",$item[3]);
                                            $load1 = $split1;
                                            array_splice($load1,0,1);
                                            $load1 = implode("@",$load1);
                                            $split1 = $split1[0];
                                            if (preg_match("/\b(LF|GF|TF)@[a-zA-Z-_$&%*!?][a-zA-Z-_$&%*!?0-9]*\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"var\">$item[3]</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\b(nil)@(nil)\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\b(bool)@(true|false)\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\b(int)\b/", $split1)){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\bstring@((LF|TF|GF)@[a-zA-Z-_$&%*!?][a-zA-Z0-9-_$&%*!?])*|([a-zA-Z0-9-_$<>&%*!?]|\\\[0-9]{3})*\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            else{
                                            exit(23); //wrong parameter
                                            }
                                        }
                                        elseif(preg_match("/\bstring@((LF|TF|GF)@[a-zA-Z-_$&%*!?][a-zA-Z0-9-_$&%*!?])*|([a-zA-Z0-9-_$<>&%*!?]|\\\[0-9]{3})*\b/", $item[2])){
                                            $split1 = explode("@",$item[3]);
                                            $load1 = $split1;
                                            array_splice($load1,0,1);
                                            $load1 = implode("@",$load1);
                                            $split1 = $split1[0];
                                            if (preg_match("/\b(LF|GF|TF)@[a-zA-Z-_$&%*!?][a-zA-Z-_$&%*!?0-9]*\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"var\">$item[3]</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\b(nil)@(nil)\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\b(bool)@(true|false)\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\b(int)\b/", $split1)){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\bstring@((LF|TF|GF)@[a-zA-Z-_$&%*!?][a-zA-Z0-9-_$&%*!?])*|([a-zA-Z0-9-_$<>&%*!?]|\\\[0-9]{3})*\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            else{
                                            exit(23); //wrong parameter
                                            }
                                        }
                                        else{
                                            exit(23); //wrong parameter
                                        }
                                    }
                                    else{
                                        exit(23); //wrong parameter
                                    }
                                }
                                else{
                                    exit(23); //wrong count of parameters
                                }
                                break;
                            case 'READ':
                                if (count($item) == 3){
                                    echo("\t<instruction order=\"".$counter."\" opcode=\"".strtoupper($item[0])."\">\n");
                                    if (preg_match("/\b(LF|GF|TF)@[a-zA-Z-_$&%*!?][a-zA-Z-_$&%*!?0-9]*\b/", $item[1])){
                                        if (preg_match("/\b(int|bool|string)\b/", $item[2])){
                                            echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                            echo("\t\t<arg2 type=\"type\">$item[2]</arg2>\n");
                                            echo("\t</instruction>\n");
                                        }
                                        else{
                                        exit(23); //wrong parameter
                                        }
                                    }
                                    else{
                                        exit(23); //wrong parameter
                                    }
                                }
                                else{
                                    exit(23); //wrong count of parameters
                                }
                                break;
                            case 'JUMPIFEQ':
                            case 'JUMPIFNEQ':
                                if (count($item) == 4){
                                    echo("\t<instruction order=\"".$counter."\" opcode=\"".strtoupper($item[0])."\">\n");
                                    if (preg_match("/\b[a-zA-Z-_$&%*!?][a-zA-Z-_$&%*!?0-9]*\b/", $item[1])){
                                        $split = explode("@",$item[2]);
                                        $load = $split;
                                        array_splice($load,0,1);
                                        $load = implode("@",$load);
                                        $split = $split[0];
                                        if (preg_match("/\b(LF|GF|TF)@[a-zA-Z-_$&%*!?][a-zA-Z-_$&%*!?0-9]*\b/", $item[2])){
                                            $split1 = explode("@",$item[3]);
                                            $load1 = $split1;
                                            array_splice($load1,0,1);
                                            $load1 = implode("@",$load1);
                                            $split1 = $split1[0];
                                            if (preg_match("/\b(LF|GF|TF)@[a-zA-Z-_$&%*!?][a-zA-Z-_$&%*!?0-9]*\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"var\">$item[2]</arg2>\n");
                                                echo("\t\t<arg3 type=\"var\">$item[3]</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\b(nil)@(nil)\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"var\">$item[2]</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\b(bool)@(true|false)\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"var\">$item[2]</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\b(int)\b/", $split1)){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"var\">$item[2]</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\bstring@((LF|TF|GF)@[a-zA-Z-_$&%*!?][a-zA-Z0-9-_$&%*!?])*|([a-zA-Z0-9-_$<>&%*!?]|\\\[0-9]{3})*\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"var\">$item[2]</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            else{
                                            exit(23); //wrong parameter
                                            }
                                        }
                                        elseif(preg_match("/\b(nil)@(nil)\b/", $item[2])){
                                            $split1 = explode("@",$item[3]);
                                            $load1 = $split1;
                                            array_splice($load1,0,1);
                                            $load1 = implode("@",$load1);
                                            $split1 = $split1[0];
                                            if (preg_match("/\b(LF|GF|TF)@[a-zA-Z-_$&%*!?][a-zA-Z-_$&%*!?0-9]*\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"var\">$item[3]</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\b(nil)@(nil)\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\b(bool)@(true|false)\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\b(int)@\b/", $split1)){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\bstring@((LF|TF|GF)@[a-zA-Z-_$&%*!?][a-zA-Z0-9-_$&%*!?])*|([a-zA-Z0-9-_$<>&%*!?]|\\\[0-9]{3})*\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            else{
                                            exit(23); //wrong parameter
                                            }
                                        }
                                        elseif(preg_match("/\b(bool)@(true|false)\b/", $item[2])){
                                            $split1 = explode("@",$item[3]);
                                            $load1 = $split1;
                                            array_splice($load1,0,1);
                                            $load1 = implode("@",$load1);
                                            $split1 = $split1[0];
                                            if (preg_match("/\b(LF|GF|TF)@[a-zA-Z-_$&%*!?][a-zA-Z-_$&%*!?0-9]*\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"var\">$item[3]</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\b(nil)@(nil)\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\b(bool)@(true|false)\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\b(int)\b/", $split1)){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\bstring@((LF|TF|GF)@[a-zA-Z-_$&%*!?][a-zA-Z0-9-_$&%*!?])*|([a-zA-Z0-9-_$<>&%*!?]|\\\[0-9]{3})*\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            else{
                                            exit(23); //wrong parameter
                                            }
                                        }
                                        elseif(preg_match("/\b(int)\b/", $split)){
                                            $split1 = explode("@",$item[3]);
                                            $load1 = $split1;
                                            array_splice($load1,0,1);
                                            $load1 = implode("@",$load1);
                                            $split1 = $split1[0];
                                            if (preg_match("/\b(LF|GF|TF)@[a-zA-Z-_$&%*!?][a-zA-Z-_$&%*!?0-9]*\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"var\">$item[3]</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\b(nil)@(nil)\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\b(bool)@(true|false)\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\b(int)\b/", $split1)){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\bstring@((LF|TF|GF)@[a-zA-Z-_$&%*!?][a-zA-Z0-9-_$&%*!?])*|([a-zA-Z0-9-_$<>&%*!?]|\\\[0-9]{3})*\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            else{
                                            exit(23); //wrong parameter
                                            }
                                        }
                                        elseif(preg_match("/\bstring@((LF|TF|GF)@[a-zA-Z-_$&%*!?][a-zA-Z0-9-_$&%*!?])*|([a-zA-Z0-9-_$<>&%*!?]|\\\[0-9]{3})*\b/", $item[2])){
                                            $split1 = explode("@",$item[3]);
                                            $load1 = $split1;
                                            array_splice($load1,0,1);
                                            $load1 = implode("@",$load1);
                                            $split1 = $split1[0];
                                            if (preg_match("/\b(LF|GF|TF)@[a-zA-Z-_$&%*!?][a-zA-Z-_$&%*!?0-9]*\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"var\">$item[3]</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\b(nil)@(nil)\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\b(bool)@(true|false)\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\b(int)\b/", $split1)){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            elseif(preg_match("/\bstring@((LF|TF|GF)@[a-zA-Z-_$&%*!?][a-zA-Z0-9-_$&%*!?])*|([a-zA-Z0-9-_$<>&%*!?]|\\\[0-9]{3})*\b/", $item[3])){
                                                echo("\t\t<arg1 type=\"var\">$item[1]</arg1>\n");
                                                echo("\t\t<arg2 type=\"".$split."\">$load</arg2>\n");
                                                echo("\t\t<arg3 type=\"".$split1."\">$load1</arg3>\n");
                                                echo("\t</instruction>\n");
                                            }
                                            else{
                                            exit(23); //wrong parameter
                                            }
                                        }
                                        else{
                                            exit(23); //wrong parameter
                                        }
                                    }
                                    else{
                                        exit(23); //wrong parameter
                                    }
                                }
                                else{
                                    exit(23); //wrong count of parameters
                                }
                                break;
                            default:
                                exit(22); //unknown or wrong opcode 
                        }
                    }
                }
            }
        }  
    }   
    function RemoveComments(&$line){
        $line = explode('#', $line);
        $line = $line[0];
        $line = trim($line);
    }
?>