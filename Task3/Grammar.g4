grammar Grammar;


@header {
	import java.util.*;
}

@parser::members {}

code: (include_part | var_part | function_part)*;

include_part: INCLUDE (STRING | INCLUDE_STRING);

var_part: NAME NAME (APPROPRIATION value)? (COMMA NAME (APPROPRIATION value)?)* SEMICOLON;
value: element (ARITH element)?;
element: BOOL | NUMBER | STRING | CHAR | (AMPERSAND|)NAME;

function_part: NAME NAME arguments body;
arguments: LBRACKET ((NAME NAME (COMMA NAME NAME)*) |) RBRACKET;

body: LFIGBRACKET (for_part | while_part | if_else_part | appr_part | var_part | call_part | return_part)* RFIGBRACKET;

for_part: FOR LBRACKET (var_part | SEMICOLON) (comparing)? SEMICOLON (appr_part_for | RBRACKET) body;
while_part: WHILE condition body;
if_else_part: IF condition body (ELSE body)?;
appr_part_for: NAME (APPROPRIATION | ARITH_CHANGE) value RBRACKET;
appr_part: NAME (APPROPRIATION | ARITH_CHANGE) value SEMICOLON;
call_part: NAME LBRACKET (value (COMMA value)* |) RBRACKET SEMICOLON;
return_part: RETURN (value)? SEMICOLON;

condition: LBRACKET logic_value (LOGIC logic_value)? RBRACKET;
logic_value: comparing | BOOL | NAME;
comparing: value COMPARE value;

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
