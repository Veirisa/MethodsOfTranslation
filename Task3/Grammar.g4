grammar Grammar;


@header {
	import java.util.*;
}

@parser::members {

    final Random random = new Random();

    Map<String, String> newNames = new HashMap<String, String>();
    Set<String> allNames = new HashSet<String>();
    Set<String> fakeNames = new TreeSet<String>();
    final String[] types = {"short", "int", "long"};
    final String[] op = {"+", "-", "*"};
    final String[] appr = {"=", "+=", "-=", "*="};
    int nameSize = 10;

    String generateName() {
        if (allNames.size() >= (1 << (nameSize - 4))) {
            ++nameSize;
        }
        String name = "I00O1IO0I1O1";
        while (!allNames.add(name)) {
            name = "I0";
            for (int i = 2; i < nameSize - 2; ++i) {
                boolean isRound = random.nextBoolean(), isLetter = random.nextBoolean();
                if (isLetter) {
                    if (isRound) {
                        name += "O";
                    } else {
                        name += "I";
                    }
                } else {
                    if (isRound) {
                        name += "0";
                    } else {
                        name += "1";
                    }
                }
            }
            name += "O1";
        }
        return name;
    }

    String getNewName(String var) {
        if (newNames.containsKey(var)) {
            return newNames.get(var);
        }
        String name = generateName();
        newNames.put(var, name);
        return name;
    }

    String getRandomFakeName() {
        String name = "";
        int ind = random.nextInt(fakeNames.size());
        Iterator<String> iter = fakeNames.iterator();
        while (ind >= 0 && iter.hasNext()) {
            name = iter.next();
            --ind;
        }
        return name;
    }

    String getRandomRvalue() {
        if (random.nextBoolean()) {
            return getRandomFakeName();
        }
        return String.valueOf(random.nextInt(256));
    }

    String generateAd() {
        boolean isEmpty = random.nextBoolean();
        if (isEmpty) {
            return "";
        }
        String result = types[random.nextInt(3)] + " ";
        int count = random.nextInt(4) + 1;
        for (int i = 0; i < count; ++i) {
            if (i > 0) {
                result += ", ";
            }
            String name = generateName();
            fakeNames.add(name);
            result += name;
            boolean isAppr = random.nextBoolean();
            if (isAppr) {
                result += " = " + String.valueOf(random.nextInt(256));
            }
        }
        return result + ";\n";
    }

    String generateOp() {
        boolean isEmpty = random.nextBoolean();
        if (isEmpty || fakeNames.size() == 0) {
            return "";
        }
        String result = "";
        result += getRandomFakeName() + " " + appr[random.nextInt(4)] + " " + getRandomRvalue();
        boolean withOp = random.nextBoolean();
        if (withOp) {
            result += " " + op[random.nextInt(3)] + " " + getRandomRvalue();
        }
        return result + ";\n";
    }

}

code returns [String res] @init{$res = "";}:
                    (include_part {$res += $include_part.res + generateAd() + generateAd();} | var_part {$res += generateAd() + $var_part.res + "\n" + generateAd();} | function_part {$res += generateAd() + generateAd() + $function_part.res;})*;

include_part returns [String res]:
                    INCLUDE {$res = "#include ";} (STRING {$res += $STRING.text;} | INCLUDE_STRING {$res += $INCLUDE_STRING.text;}) {$res += "\n";};

var_part returns [String res]:
                    t=NAME v=NAME {$res = $t.text + " " + getNewName($v.text);} (APPROPRIATION val=value {$res += " = " + $val.res;})? (COMMA vnext=NAME {$res += ", " + getNewName($vnext.text);} (APPROPRIATION valnext=value {$res += " = " + $valnext.res;})?)* SEMICOLON {$res += ";";};

value returns [String res]:
                    el=element {$res = $el.res;} (ARITH elnext=element {$res += " " + $ARITH.text + " " + $elnext.res;})?;

element returns [String res] @init{$res = "";}:
                    BOOL {$res += $BOOL.text;} | NUMBER {$res += $NUMBER.text;} | STRING {$res += $STRING.text;} | CHAR {$res += $CHAR.text;} | ((AMPERSAND {$res += "&";})? NAME {$res += getNewName($NAME.text);});

function_part returns [String res]:
                    t=NAME f=NAME arguments body {$res = $t.text + " " + $f.text + $arguments.res + $body.res;};

arguments returns [String res]:
                    LBRACKET {$res = "(";} (t=NAME arg=NAME {$res += $t.text + " " + getNewName($arg.text);} (COMMA tnext=NAME argnext=NAME {$res += ", " + $tnext.text + " " + getNewName($argnext.text);})*)? RBRACKET {$res += ")";};

body returns [String res]:
                    LFIGBRACKET {$res = " {\n" + generateOp();} (for_part {$res += $for_part.res;} | while_part {$res += $while_part.res;} | if_else_part {$res += $if_else_part.res;} | appr_part {$res += $appr_part.res;} | var_part {$res += $var_part.res + "\n";} | call_part {$res += $call_part.res;} | return_part {$res += $return_part.res;})* RFIGBRACKET {$res += generateOp() + "}\n";};

for_part returns [String res]:
                    FOR LBRACKET {$res = "for (";} (var_part {$res += $var_part.res;} | SEMICOLON {$res += "; ";}) (comparing {$res += $comparing.res;})? SEMICOLON {$res += ";";} (appr_part_for {$res += $appr_part_for.res;} | RBRACKET {$res += ")";}) body {$res += $body.res;};

while_part returns [String res]:
                    WHILE condition body {$res = "while " + $condition.res + $body.res;};

if_else_part returns [String res]:
                    IF condition b=body {$res = "if " + $condition.res + $b.res;} (ELSE interb=body {$res += "else" + $interb.res;})?;

appr_part_for returns [String res]:
                    NAME {$res = getNewName($NAME.text) + " ";} (APPROPRIATION {$res += "= ";} | ARITH_CHANGE {$res += $ARITH_CHANGE.text + " ";}) value RBRACKET {$res += $value.res + ")";};

appr_part returns [String res]:
                    NAME {$res = getNewName($NAME.text) + " ";} (APPROPRIATION {$res += "= ";} | ARITH_CHANGE {$res += $ARITH_CHANGE.text + " ";}) value SEMICOLON {$res += $value.res + ";\n";};

call_part returns [String res]:
                    NAME LBRACKET {$res = $NAME.text + "(";} (v=value {$res += $v.res;} (COMMA vnext=value {$res += ", " + $vnext.res;})*)? RBRACKET SEMICOLON {$res += ");\n";};

return_part returns [String res]:
                    RETURN {$res = "return";} (value {$res += " " + $value.res;})? SEMICOLON {$res += ";\n";};

condition returns [String res]:
                    LBRACKET lv=logic_value {$res = "(" + $lv.res;} (LOGIC lvnext=logic_value {$res += " " + $LOGIC.text + " " + $lvnext.res;})* RBRACKET {$res += ")";};

logic_value returns [String res] @init{$res = "";}:
                    comparing {$res += $comparing.res;} | BOOL {$res += $BOOL.text;} | NAME {$res += getNewName($NAME.text);};

comparing returns [String res]:
                    v1=value COMPARE v2=value {$res = $v1.res + " " + $COMPARE.text + " " + $v2.res;};

WS: [ \n\t]+ -> skip;

RETURN: 'return';
INCLUDE: '#include';
INCLUDE_STRING: '<'.*?'>';

BOOL: 'true' | 'false';
NUMBER: [0-9]+('.'[0-9]+)?;
STRING: '"'.*?'"';
CHAR: '\''.'\'';

APPROPRIATION: '=';
ARITH_CHANGE: '+=' | '-=' | '/=' | '*=' | '%=';
ARITH: '+' | '-' | '/' | '*' | '%';
LOGIC: '||' | '&&';
COMPARE: '>=' | '<=' | '>' | '<' | '!=' | '==';

IF: 'if';
ELSE: 'else';
FOR: 'for';
WHILE: 'while';

NAME: [a-zA-Z][a-zA-Z0-9]*;

COMMA: ',';
SEMICOLON: ';';
LBRACKET: '(';
RBRACKET: ')';
LFIGBRACKET: '{';
RFIGBRACKET: '}';
AMPERSAND: '&';
