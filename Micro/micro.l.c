%{
#include <string.h>
#include "y.tab.h"
%}

%option noyywrap

digito	[0-9]
letra	[a-zA-Z]

%%

inicio										return INICIO;
fin											return FIN;
leer										return LEER;
escribir									return ESCRIBIR;
{letra}({letra}|{digito})*					yylval.str=strdup(yytext); return ID;
{digito}+									yylval.num=atoi(yytext); return CONSTANTE;
"("											return PARENIZQ;
")"											return PARENDER;
";"											return PUNTOYCOMA;
","											return COMA;
":="										return ASIGNACION;
"+"											return SUMA;
"-"											return RESTA;
<<EOF>>										return FDT;
\n											/*ignora el fin de linea*/
[ \t]+										/*ignora los espacios en blanco*/
.											return ERRORLEXICO;
