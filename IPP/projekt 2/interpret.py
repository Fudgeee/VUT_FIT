import argparse
import re
import xml.etree.ElementTree as ET
import sys
import os.path as OP

instruction_list = ['MOVE', 'CREATEFRAME', 'PUSHFRAME', 'POPFRAME', 'DEFVAR', 'CALL', 'RETURN', 'POPS', 'PUSHS', 
                'ADD', 'SUB', 'MUL', 'IDIV', 'LT', 'GT', 'EQ', 'AND', 'OR', 'NOT', 'INT2CHAR', 'STRI2INT',
                'READ', 'WRITE', 'CONCAT', 'STRLEN', 'GETCHAR', 'SETCHAR', 'TYPE',
                'LABEL', 'JUMP', 'JUMPIFEQ', 'JUMPIFNEQ', 'EXIT', 'DPRINT', 'BREAK']
typy_argumentov = ['string', 'int', 'bool', 'var', 'nil', 'type', 'label']
VarSymbArgs = ['MOVE', 'INT2CHAR', 'STRLEN', 'TYPE', 'NOT']
NoArgs = ['CREATEFRAME', 'PUSHFRAME', 'POPFRAME', 'RETURN', 'BREAK']
VarArg = ['DEFVAR', 'POPS']
LabelArg = ['CALL', 'LABEL', 'JUMP']
SymbArg = ['PUSHS', 'WRITE', 'EXIT', 'DPRINT']
VarSymbSymbArgs = ['ADD', 'SUB', 'MUL', 'IDIV', 'LT', 'GT', 'EQ', 'AND', 'OR', 'STRI2INT', 'CONCAT', 'GETCHAR', 'SETCHAR']
VarTypeArgs = ['READ']
LabelSymbSymbArgs = ['JUMPIFEQ', 'JUMPIFNEQ']
ins_dictionary = dict()
#vymena escape sekvenci za znaky
def Esc(val):
    escList = re.findall(r'\\[0123456789]{3}', val)
    while(len(escList) > 0):
        newval = escList[0]
        val = val.replace(newval, chr(int(newval.replace("\\", ""))))
        while(newval in escList):
            escList.remove(newval)
    return val
#kontrola spravnej hodnoty string-u
def checkString(value):
    if (value == None):
        value = ""
    if (re.match(r'^([^\s\\#]|(\\\d{3}))*$', value)):
        return True
    return False
#kontrola spravnej hodnoty int-u
def checkInt(value):
    if (re.match(r'^[-+]?[0-9]+$', value)):
        return True
    return False
#kontrola spravnej hodnoty bool-u
def checkBool(value):
    if (value == "true" or value == "false"):
        return True
    return False
#kontrola spravnej hodnoty var-u
def checkVar(value):
    if (re.match(r'^(GF|LF|TF)@[a-zA-Z_\-$&%*!?][\w\-$&%*!?]*$', value)):
        return True
    return False
#kontrola spravnej hodnoty nil-u    
def checkNil(value):
    if (value == "nil"):
        return True
    return False
#kontrola spravnej hodnoty type-u
def checkType(value):
    if (value == "int" or value == "string" or value == "bool"):
        return True
    return False
#kontrola spravnej hodnoty label-u
def checkLabel(value):
    if (re.match(r'^[a-zA-Z_\-$&%*!?][\w\-$&%*!?]*$', value)):
        return True
    return False
#kontrola obsahu symbolu a spravnej hodnoty daneho obsahu
def checkycheck(value):
    if (subelem.attrib['type'] == 'string'):
        if not(checkString(value)):
            exit(32)
    if (subelem.attrib['type'] == 'int'):
        if (value == None):
            exit(32)
        if not(checkInt(value)):
            exit(32)
    if (subelem.attrib['type'] == 'bool'):
        if (value == None):
            exit(32)
        if not(checkBool(value)):
            exit(32)
    if (subelem.attrib['type'] == 'var'):
        if (value == None):
            exit(32)
        if not(checkVar(value)):
            exit(32)
    if (subelem.attrib['type'] == 'nil'):
        if (value == None):
            exit(32)
        if not(checkNil(value)):
            exit(32)
    return True

class variable:
    def __init__(self, type, value):
        self.type = type
        self.value = value

class arg:
    def __init__(self, arg_type, value):
        self.type = arg_type
        self.value = value

class instruction:
    def __init__(self, opcode):
        self.opcode = opcode
        self.args = []
    def add_argument(self, arg):
        self.args.append(arg)

#argparse
ap = argparse.ArgumentParser()
ap.add_argument("--source", nargs = 1, help = "XML representations of program")
ap.add_argument("--input", nargs = 1, help = "Input file of program")
args= ap.parse_args()

issrcfile = True #kontrolna premena existencie srcfile-u
isinputfile = True #kontrolna premena existencie inputfile-u
#IF zistuje pocet zadanych argumentov,ak su oba zadane berie ich na vstupy, 
# ak jeden je zadany a druhy nie, tak nezadany berie z STDIN, 
# pokial su oba nezadane, vyhlasi error
if ((args.source != None) and (args.input != None)):
    issrcfile = OP.isfile(args.source[0])
    isinputfile = OP.isfile(args.input[0])
elif ((args.source != None) and (args.input == None)):
    issrcfile = OP.isfile(args.source[0])
    isinputfile = sys.stdin
elif ((args.source == None) and (args.input != None)):
    issrcfile = sys.stdin
    isinputfile = OP.isfile(args.input[0])
else:
	ap.exit(10,'Missing source and input, at least one of them have to be set\n')

if (issrcfile):
    srcfile = args.source[0]
else:
    exit(11)

#xml load
try:
    tree = ET.parse(srcfile)
except IOError:
	ap.exit(11,'Can not open source file')
except ET.ParseError:
    ap.exit(31,'Invalid XML format')

root = tree.getroot()

#xml check
if root.tag != 'program': #kontrola ci XML subor obsahuje koren program
    exit(32)
ra = list(root.attrib.keys())
if not('language' in ra): #kontrola ci program obsahuje atribut language a ci je v danom atribute spravny jazyk = IPPCODE21
	exit(32)
if (root.attrib['language'].upper() != "IPPCODE21"):
	exit(32)

orders = []
for child in root:
    if child.tag != 'instruction': #kontrola ci detmi rootu su prave instrukcie
        exit(32)  
    ca = list(child.attrib.keys())
    if (len(ca) != 2):
        exit(32)
    if not('order' in ca) and not ('opcode' in ca): #kontrola ci sa nachadzaju v instrukciach prave dane dva atributy: order a opcode
        exit(32)
    if not(re.match("[0123456789]+", child.attrib['order'])): #kontrola ci order pozostava len z cisel 
        exit(32)
    if (int(child.attrib['order']) == 0): 
        exit(32)
    if (int(child.attrib['order']) in orders): #kontrola ci sa v poli orderov nenachadza order s rovnakym cislom
        exit(32)
    orders.append(int(child.attrib['order']))
    control = False
    order = int(child.attrib['order'])
    opcode = child.attrib['opcode'].upper()
    for ins in instruction_list:
        if (opcode == ins): #kontrola spravne zadanych instrukcii
            control = True
    if (control == False):
        exit(32)
    if (opcode in VarSymbArgs): #kontrola instrukcii s 2 argumentami: Var a Symb, kontrola poctu argumentov a nasledne kontrola spravneho obsahu
        if (len(child) != 2):
            exit(32)
        ins_dictionary[order] = instruction(opcode)
        for subelem in child:
            if not (re.match(r"arg[12]", subelem.tag)):
                exit(32)
            if not('type' in subelem.attrib.keys()):
                exit(32)
            if (subelem.tag == 'arg1'):
                if not(subelem.attrib['type'] == 'var'):
                    exit(32)
                if not(checkVar(subelem.text)):
                    exit(32)
            if (subelem.tag == 'arg2'):
                if not(subelem.attrib['type'] in typy_argumentov):
                    exit(32)
                if not(checkycheck(subelem.text)):
                    exit(32)
            ins_dictionary[order].add_argument(arg(subelem.attrib['type'], subelem.text)) 
    if (opcode in NoArgs ): #kontrola instrukcii s 0 argumentami,  kontrola poctu argumentov
        if (len(child) != 0):
            exit(32)
        ins_dictionary[order] = instruction(opcode)
    if (opcode in VarArg): #kontrola instrukcii s 1 argumentom: Var, kontrola poctu argumentov a nasledne kontrola spravneho obsahu
        if (len(child) != 1):
            exit(32)
        ins_dictionary[order] = instruction(opcode)
        for subelem in child:
            if not (re.match(r"arg[1]", subelem.tag)):
                exit(32)
            if not('type' in subelem.attrib.keys()):
                exit(32)
            if (subelem.tag == 'arg1'):
                if not(subelem.attrib['type'] == 'var'):
                    exit(32)
                if not(checkVar(subelem.text)):
                    exit(32) 
            ins_dictionary[order].add_argument(arg(subelem.attrib['type'], subelem.text))    
    if (opcode in LabelArg): #kontrola instrukcii s 1 argumentom: Label, kontrola poctu argumentov a nasledne kontrola spravneho obsahu
        if (len(child) != 1):
            exit(32)
        ins_dictionary[order] = instruction(opcode)
        for subelem in child:
            if not (re.match(r"arg[1]", subelem.tag)):
                exit(32)
            if not('type' in subelem.attrib.keys()):
                exit(32)
            if (subelem.tag == 'arg1'):
                if not(subelem.attrib['type'] == 'label'):
                    exit(32)
                if not(checkLabel(subelem.text)):
                    exit(32)
            ins_dictionary[order].add_argument(arg(subelem.attrib['type'], subelem.text)) 
    if (opcode in SymbArg): #kontrola instrukcii s 1 argumentom: Symb, kontrola poctu argumentov a nasledne kontrola spravneho obsahu
        if (len(child) != 1):
            exit(32)
        ins_dictionary[order] = instruction(opcode)
        for subelem in child:
            if not (re.match(r"arg[1]", subelem.tag)):
                exit(32)
            if not('type' in subelem.attrib.keys()):
                exit(32)
            if (subelem.tag == 'arg1'):
                if not(subelem.attrib['type'] in typy_argumentov):
                    exit(32)
                if not(checkycheck(subelem.text)):
                    exit(32)
            ins_dictionary[order].add_argument(arg(subelem.attrib['type'], subelem.text)) 
    if (opcode in VarSymbSymbArgs): #kontrola instrukcii s 3 argumentami: Var, Symb, Symb, kontrola poctu argumentov a nasledne kontrola spravneho obsahu
        if (len(child) != 3):
            exit(32)
        ins_dictionary[order] = instruction(opcode)
        for subelem in child:
            if not (re.match(r"arg[123]", subelem.tag)):
                exit(32)
            if not('type' in subelem.attrib.keys()):
                exit(32)
            if (subelem.tag == 'arg1'):
                if not(subelem.attrib['type'] == 'var'):
                    exit(32)
                if not(checkVar(subelem.text)):
                    exit(32)
            if (subelem.tag == 'arg2'):
                if not(subelem.attrib['type'] in typy_argumentov):
                    exit(32)
                if not(checkycheck(subelem.text)):
                    exit(32)
            if (subelem.tag == 'arg3'):
                if not(subelem.attrib['type'] in typy_argumentov):
                    exit(32)
                if not(checkycheck(subelem.text)):
                    exit(32)
            ins_dictionary[order].add_argument(arg(subelem.attrib['type'], subelem.text)) 
    if (opcode in VarTypeArgs): #kontrola instrukcii s 2 argumentom: Var, Type, kontrola poctu argumentov a nasledne kontrola spravneho obsahu
        if (len(child) != 2):
            exit(32)
        ins_dictionary[order] = instruction(opcode)
        for subelem in child:
            if not (re.match(r"arg[12]", subelem.tag)):
                exit(32)
            if not('type' in subelem.attrib.keys()):
                exit(32)
            if (subelem.tag == 'arg1'):
                if not(subelem.attrib['type'] == 'var'):
                    exit(32)
                if not(checkVar(subelem.text)):
                    exit(32)
            if (subelem.tag == 'arg2'):
                if not(subelem.attrib['type'] == 'type'):
                    exit(32)
                if not(checkType(subelem.text)):
                    exit(32)
            ins_dictionary[order].add_argument(arg(subelem.attrib['type'], subelem.text)) 
    if (opcode in LabelSymbSymbArgs): #kontrola instrukcii s 3 argumentami: Label, Symb, Symb, kontrola poctu argumentov a nasledne kontrola spravneho obsahu
        if (len(child) != 3):
            exit(32)  
        ins_dictionary[order] = instruction(opcode)     
        for subelem in child:
            if not (re.match(r"arg[123]", subelem.tag)):
                exit(32)
            if not('type' in subelem.attrib.keys()):
                exit(32)
            if (subelem.tag == 'arg1'):
                if not(subelem.attrib['type'] == 'label'):
                    exit(32)
                if not(checkLabel(subelem.text)):
                    exit(32)
            if (subelem.tag == 'arg2'):
                if not(subelem.attrib['type'] in typy_argumentov):
                    exit(32)
                if not(checkycheck(subelem.text)):
                    exit(32)
            if (subelem.tag == 'arg3'):
                if not(subelem.attrib['type'] in typy_argumentov):
                    exit(32)
                if not(checkycheck(subelem.text)):
                    exit(32)
            ins_dictionary[order].add_argument(arg(subelem.attrib['type'], subelem.text)) 
orders.sort()
frames = dict()
frames["GF"] = dict()
frames["LF"] = None
frames["TF"] = None
frameStack = []
callStack = []
dataStack = []
i = 0
while (i < len(orders)): #cyklus prechadzajuci vsetkymi instrukciami doradu
    instr = ins_dictionary[orders[i]]
    if (instr.opcode == 'MOVE'): #MOVE
        var = instr.args[0].value.split('@')
        symb = instr.args[1].value.split('@')
        type1 = instr.args[1].type
        if (len(symb) == 1):
            value = symb[0]
        elif (len(symb) > 1):
            if (var[0] == 'LF'):
                if (frames["LF"] == None):
                    exit(55)
                else:
                    value = symb[1]
            elif (var[0] == 'GF'):
                if (frames["GF"] == None):
                    exit(55)
                else:
                    value = symb[1]  
        frames[var[0]][var[1]].type = type1
        frames[var[0]][var[1]].value = value     
    if (instr.opcode == 'CREATEFRAME'): #CREATEFRAME
        frames["TF"] = dict()
    if (instr.opcode == 'PUSHFRAME'): #PUSHFRAME
        if (frames["TF"] == None):
            exit(55)
        frameStack.append(frames["TF"])
        frames["LF"] = frames["TF"]
        frames["TF"]
    if (instr.opcode == 'POPFRAME'): #POPFRAME
        if (frames["LF"] == None):
            exit(55)
        frames["TF"] = frames["LF"]
        frameStack.pop()
        if(len(frameStack) == 0):
            frames["LF"] == None
        else:
            frames["LF"] = frameStack.pop()
            frameStack.append(frames["LF"])
    if (instr.opcode == 'DEFVAR'): #DEFVAR
        var = instr.args[0].value.split('@')
        if (var[0] == 'LF'):
            if (frames["LF"] == None):
                exit(55)
        if (var[0] == 'GF'):
            if (frames["GF"] == None):
                exit(55)
        if (var[0] == 'TF'):
            if (frames["TF"] == None):
                exit(55)
        frames[var[0]][var[1]] = variable(var[1], None)
    if (instr.opcode == 'CALL'): #CALL
        callStack.append(i)  
    if (instr.opcode == 'RETURN'): #RETURN
        if (len(callStack) == 0):
            exit(56)
        i = callStack.pop()
    if (instr.opcode == 'PUSHS'): #PUSHS
        var = instr.args[0].value.split('@')
        if (len(var) > 1):
            if (frames[var[0]] == None):
                exit(55)
            if (frames[var[0]][var[1]] == None):
                exit(54)
            datatype = frames[var[0]][var[1]].type
            datavalue = frames[var[0]][var[1]].value
            dataStack.append(variable(datatype, datavalue))
        else:
            datatype = instr.args[0].type
            datavalue = instr.args[0].value
            dataStack.append(variable(datatype, datavalue))
    if (instr.opcode == 'POPS'): #POPS
        if (len(dataStack) == 0):
            exit(56)
        else:
            var = instr.args[0].value.split('@')
            data = dataStack.pop()
            frames[var[0]][var[1]].type = data.type
            frames[var[0]][var[1]].value = data.value
    if (instr.opcode == 'ADD'): #ADD
        var = instr.args[0].value.split('@')
        symb1 = instr.args[1].value.split('@')
        symb2 = instr.args[2].value.split('@')
        if (len(symb1) > 1):
            value1 = int(symb1[1])
        else:
            value1 = int(symb1[0])
        if (len(symb2) > 1):
            value2 = int(symb2[1])
        else:
            value2 = int(symb2[0])
        result = value1 + value2
        frames[var[0]][var[1]].type = "int"
        frames[var[0]][var[1]].value = result
    if (instr.opcode == 'SUB'): #SUB
        var = instr.args[0].value.split('@')
        symb1 = instr.args[1].value.split('@')
        symb2 = instr.args[2].value.split('@')
        if (len(symb1) > 1):
            value1 = int(symb1[1])
        else:
            value1 = int(symb1[0])
        if (len(symb2) > 1):
            value2 = int(symb2[1])
        else:
            value2 = int(symb2[0])
        result = value1 - value2
        frames[var[0]][var[1]].type = "int"
        frames[var[0]][var[1]].value = result
    if (instr.opcode == 'MUL'): #MUL
        var = instr.args[0].value.split('@')
        symb1 = instr.args[1].value.split('@')
        symb2 = instr.args[2].value.split('@')
        if (len(symb1) > 1):
            value1 = int(symb1[1])
        else:
            value1 = int(symb1[0])
        if (len(symb2) > 1):
            value2 = int(symb2[1])
        else:
            value2 = int(symb2[0])
        result = value1 * value2
        frames[var[0]][var[1]].type = "int"
        frames[var[0]][var[1]].value = result
    if (instr.opcode == 'IDIV'):#IDIV
        var = instr.args[0].value.split('@')
        symb1 = instr.args[1].value.split('@')
        symb2 = instr.args[2].value.split('@')
        if (len(symb1) > 1):
            value1 = int(symb1[1])
        else:
            value1 = int(symb1[0])
        if (len(symb2) > 1):
            value2 = int(symb2[1])
        else:
            value2 = int(symb2[0])
        if (value2 == 0):
            exit(57)
        result = value1 // value2
        frames[var[0]][var[1]].type = "int"
        frames[var[0]][var[1]].value = result
    if (instr.opcode == 'LT'): #LT
        var = instr.args[0].value.split('@')
        symb1 = instr.args[1].value.split('@')
        symb2 = instr.args[2].value.split('@')
        type1 = instr.args[1].type
        type2 = instr.args[2].type
        if (len(symb1) > 1):
            value1 = symb1[1]
        else:
            value1 = symb1[0]
        if (len(symb2) > 1):
            value2 = symb2[1]
        else:
            value2 = symb2[0]
        if (type1 == "int" and type2 == "int"):
            value1 = int(value1)
            value2 = int(value2)
            if (value1 < value2):
                frames[var[0]][var[1]].type = "bool"
                frames[var[0]][var[1]].value = "true"
            else:
                frames[var[0]][var[1]].type = "bool"
                frames[var[0]][var[1]].value = "false"
        elif (type1 == "bool" and type2 == "bool"):
            if (value1 == "false" and value2 == "true"):
                frames[var[0]][var[1]].type = "bool"
                frames[var[0]][var[1]].value = "true"
            else:
                frames[var[0]][var[1]].type = "bool"
                frames[var[0]][var[1]].value = "false"
        elif (type1 == "string" and type2 == "string"):
            if (value1 < value2):
                frames[var[0]][var[1]].type = "bool"
                frames[var[0]][var[1]].value = "true"
            else:
                frames[var[0]][var[1]].type = "bool"
                frames[var[0]][var[1]].value = "false"
        else:
            exit(53)
    if (instr.opcode == 'GT'): #GT
        var = instr.args[0].value.split('@')
        symb1 = instr.args[1].value.split('@')
        symb2 = instr.args[2].value.split('@')
        type1 = instr.args[1].type
        type2 = instr.args[2].type
        if (len(symb1) > 1):
            value1 = symb1[1]
        else:
            value1 = symb1[0]
        if (len(symb2) > 1):
            value2 = symb2[1]
        else:
            value2 = symb2[0]
        if (type1 == "int" and type2 == "int"):
            value1 = int(value1)
            value2 = int(value2)
            if (value1 > value2):
                frames[var[0]][var[1]].type = "bool"
                frames[var[0]][var[1]].value = "true"
            else:
                frames[var[0]][var[1]].type = "bool"
                frames[var[0]][var[1]].value = "false"
        elif (type1 == "bool" and type2 == "bool"):
            if (value1 == "true" and value2 == "false"):
                frames[var[0]][var[1]].type = "bool"
                frames[var[0]][var[1]].value = "true"
            else:
                frames[var[0]][var[1]].type = "bool"
                frames[var[0]][var[1]].value = "false"
        elif (type1 == "string" and type2 == "string"):
            if (value1 > value2):
                frames[var[0]][var[1]].type = "bool"
                frames[var[0]][var[1]].value = "true"
            else:
                frames[var[0]][var[1]].type = "bool"
                frames[var[0]][var[1]].value = "false"
        else:
            exit(53)
    if (instr.opcode == 'EQ'): #EQ
        var = instr.args[0].value.split('@')
        symb1 = instr.args[1].value.split('@')
        symb2 = instr.args[2].value.split('@')
        type1 = instr.args[1].type
        type2 = instr.args[2].type
        if (len(symb1) > 1):
            value1 = symb1[1]
        else:
            value1 = symb1[0]
        if (len(symb2) > 1):
            value2 = symb2[1]
        else:
            value2 = symb2[0]
        if (type1 == "int" and type2 == "int"):
            value1 = int(value1)
            value2 = int(value2)
            if (value1 == value2):
                frames[var[0]][var[1]].type = "bool"
                frames[var[0]][var[1]].value = "true"
            else:
                frames[var[0]][var[1]].type = "bool"
                frames[var[0]][var[1]].value = "false"
        elif (type1 == "bool" and type2 == "bool"):
            if ((value1 == "false" and value2 == "false") or (value1 == "true" and value2 == "true")):
                frames[var[0]][var[1]].type = "bool"
                frames[var[0]][var[1]].value = "true"
            else:
                frames[var[0]][var[1]].type = "bool"
                frames[var[0]][var[1]].value = "false"
        elif (type1 == "string" and type2 == "string"):
            if (value1 == value2):
                frames[var[0]][var[1]].type = "bool"
                frames[var[0]][var[1]].value = "true"
            else:
                frames[var[0]][var[1]].type = "bool"
                frames[var[0]][var[1]].value = "false"
        elif (type1 == "nil" or type2 == "nil"):
            if (type1 == "nil" or type2 == "nil"):
                frames[var[0]][var[1]].type = "bool"
                frames[var[0]][var[1]].value = "true"
            else:
                frames[var[0]][var[1]].type = "bool"
                frames[var[0]][var[1]].value = "false"
        else:
            exit(53) 
    if (instr.opcode == 'AND'): #AND
        var = instr.args[0].value.split('@')
        symb1 = instr.args[1].value.split('@')
        symb2 = instr.args[2].value.split('@')
        type1 = instr.args[1].type
        type2 = instr.args[2].type
        if (len(symb1) > 1):
            value1 = symb1[1]
        else:
            value1 = symb1[0]
        if (len(symb2) > 1):
            value2 = symb2[1]
        else:
            value2 = symb2[0]
        if (type1 == "bool" and type2 == "bool"):
            if (value1 == "true" and value2 == "true"):
                frames[var[0]][var[1]].type = "bool"
                frames[var[0]][var[1]].value = "true"
            else:
                frames[var[0]][var[1]].type = "bool"
                frames[var[0]][var[1]].value = "false"
        else:
            exit(53)
    if (instr.opcode == 'OR'): #OR
        var = instr.args[0].value.split('@')
        symb1 = instr.args[1].value.split('@')
        symb2 = instr.args[2].value.split('@')
        type1 = instr.args[1].type
        type2 = instr.args[2].type
        if (len(symb1) > 1):
            value1 = symb1[1]
        else:
            value1 = symb1[0]
        if (len(symb2) > 1):
            value2 = symb2[1]
        else:
            value2 = symb2[0]
        if (type1 == "bool" and type2 == "bool"):
            if (value1 == "true" or value2 == "true"):
                frames[var[0]][var[1]].type = "bool"
                frames[var[0]][var[1]].value = "true"
            else:
                frames[var[0]][var[1]].type = "bool"
                frames[var[0]][var[1]].value = "false"
        else:
            exit(53)
    if (instr.opcode == 'NOT'): #NOT
        var = instr.args[0].value.split('@')
        symb1 = instr.args[1].value.split('@')
        type1 = instr.args[1].type
        if (len(symb1) > 1):
            value1 = symb1[1]
        else:
            value1 = symb1[0]
        if (type1 == "bool"):
            if (value1 == "true"):
                frames[var[0]][var[1]].type = "bool"
                frames[var[0]][var[1]].value = "false"
            else:
                frames[var[0]][var[1]].type = "bool"
                frames[var[0]][var[1]].value = "true"
        else:
            exit(53)
    if (instr.opcode == 'INT2CHAR'): #INT2CHAR
        var = instr.args[0].value.split('@')
        symb = instr.args[1].value.split('@')
        if (len(symb) > 1):
            type1 = frames[symb[0]][symb[1]].type
            value = frames[symb[0]][symb[1]].value
        else:
            type1 = instr.args[1].type
            value = instr.args[1].value
        if (type1 == "int"):
            val = int(value)
        else:
            exit(58)
        if (val >= 0 and val <= 11000):
            frames[var[0]][var[1]].type = "string"
            frames[var[0]][var[1]].value = chr(val)
        else:
            exit(58)
    if (instr.opcode == 'STRI2INT'): #STRI2INT
        var = instr.args[0].value.split('@')
        symb1 = instr.args[1].value.split('@')
        symb2 = instr.args[2].value.split('@')
        if (len(symb1) > 1):
            value1 = symb1[1]
        else:
            value1 = symb1[0]
        if (len(symb2) > 1):
            value2 = int(symb2[1])
        else:
            value2 = int(symb2[0])
        string = value1
        index = 0
        for i in string:
            if (value2 == index):
                valuex = i
            index += 1
        if (value2 >= 0 and value2 < len(value1)):
            frames[var[0]][var[1]].type = "int"
            frames[var[0]][var[1]].value = ord(valuex) 
        else:
            exit(58)     
    if (instr.opcode == 'READ'): #READ
        var = instr.args[0].value.split('@')
        typ = instr.args[1].value
        try:
            value = input()
        except:
            typ = "nil"
        if(typ == "int"):
            try:
                value = int(value)
            except:
                typ == "nil"
        if(typ == "nil"):
            value = "nil"
        if(typ == "bool"):
            value = value.lower()
        frames[var[0]][var[1]].type = typ
        frames[var[0]][var[1]].value = value
    if (instr.opcode == 'WRITE'): #WRITE
        if (instr.args[0].type == "var"):
            var = instr.args[0].value.split('@')
            type1 = frames[var[0]][var[1]].type
            value = frames[var[0]][var[1]].value
        else:
            type1 = instr.args[0].type
            value = instr.args[0].value
        if (type1 == "string"):
            print(Esc(value), end = '')
        if (type1 == "int"):
            print(int(value), end = '')
        if (type1 == "bool"):
            print(value, end = '')
        else:
            print("", end = '')
    if (instr.opcode == 'CONCAT'): #CONCAT
        var = instr.args[0].value.split('@')
        symb1 = instr.args[1].value.split('@')
        symb2 = instr.args[2].value.split('@')
        if (len(symb1) > 1):
            value1 = symb1[1]
        else:
            value1 = symb1[0]
        if (len(symb2) > 1):
            value2 = symb2[1]
        else:
            value2 = symb2[0]
        result = value1 + value2
        frames[var[0]][var[1]].type = "string"
        frames[var[0]][var[1]].value = result
    if (instr.opcode == 'STRLEN'): #STRLEN
        var = instr.args[0].value.split('@')    
        symb = instr.args[1].value.split('@')
        if (len(symb) > 1):
            value = str(symb[1])
        else:
            value = str(symb[0])
        result = len(Esc(value))
        frames[var[0]][var[1]].varType = "int"
        frames[var[0]][var[1]].value = result
    if (instr.opcode == 'GETCHAR'): #GETCHAR
        var = instr.args[0].value.split('@')
        symb1 = instr.args[1].value.split('@')
        symb2 = instr.args[2].value.split('@')
        if (len(symb1) > 1):
            value1 = symb1[1]
        else:
            value1 = symb1[0]
        if (len(symb2) > 1):
            value2 = int(symb2[1])
        else:
            value2 = int(symb2[0])
        if(value2 < 0 or value2 >= len(value1)):
            exit(58)
        frames[var[0]][var[1]].type = "string"
        frames[var[0]][var[1]].value = value1[value2]
    if (instr.opcode == 'SETCHAR'): #SETCHAR
        var = instr.args[0].value.split('@')
        symb1 = instr.args[1].value.split('@')
        symb2 = instr.args[2].value.split('@')
        type1 = instr.args[1].type
        type2 = instr.args[2].type
        if(type1 != "int"):
            exit(53)
        if(type2 != "string"):
            exit(53)
        if (len(symb1) > 1):
            value1 = int(symb1[1])
        else:
            value1 = int(symb1[0])
        if (len(symb2) > 1):
            valuex = symb2[1]
        else:
            valuex = symb2[0]
        value2 = valuex[0]
        if (len(value2) == 0):
            exit(58)
        tmp = frames[var[0]][var[1]].value
        if(value1 >= 0 and value1 < len(tmp)):
            tmp[value1] = value2[0]
            frames[var[0]][var[1]].value = tmp
        else:
            exit(58)
    if (instr.opcode == 'TYPE'): #TYPE
        var = instr.args[0].value.split('@')
        if(instr.args[1].type == "var"):
            var2 = instr.args[1].value.split('@')
            if(frames[var2[0]][var2[1]].type == None):
                type1 = ""
            else:
                type1 = frames[var2[0]][var2[1]].type
        else:
            type1 = instr.args[1].type
        frames[var[0]][var[1]].type = "string"
        frames[var[0]][var[1]].value = type1
    if (instr.opcode == 'LABEL'): #LABEL
        pass
    if (instr.opcode == 'JUMP'): #JUMP
        pass
    if (instr.opcode == 'JUMPIFEQ'): #JUMPIFEQ
        pass
    if (instr.opcode == 'JUMPIFNEQ'): #JUMPIFNEQ
        pass
    if (instr.opcode == 'EXIT'): #EXIT
        symb = instr.args[0].value.split('@')
        if (len(symb) > 1):
            type1 = symb[0]
            value = int(frames[var[0]][var[1]].value)
        else:
            type1 = instr.args[0].type
            value = int(instr.args[0].value)
        if not(type1 == "int"):
            exit(53)
        if (value < 0 and value > 49):
            exit(57)
        sys.exit(value)
    if (instr.opcode == 'DPRINT'): #DPRINT
        symb = instr.args[0].value.split('@')
        if (len(symb) > 1):
            value = symb[1]
        else:
            value = symb[0]
        print(value, end = '', file = sys.stderr)
    if (instr.opcode == 'BREAK'): #BREAK
        number = i + 1
        print("pocet vykonanych instrukcii: " + str(number), file = sys.stderr)
        print("pozicia v kode(order_number): " + str(orders[i]), file = sys.stderr)
    i += 1
sys.exit(0)