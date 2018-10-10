%{
#include <stdio.h>
#include <windows.h>

int yylex();
int yyparse();
void asignar(char*, int);
int valor(char*);
int buscar(char*);
int declarar(char*);

FILE *yyin;
int VARCOUNT = 0;

typedef struct{
	char* nombre;
	int valor;
} VAR;

VAR TV[128];

void yyerror(const char *str)
{
        fprintf(stderr,"error: %s\n",str);
}

int main(int argc, char *argv[])
{
		FILE *in = fopen(argv[1], "r");
		if(in)
		{
			yyin = in;
		}
        yyparse();
        return 0;
} 

//Asigna valor a una variable
void asignar(char* var, int val)
{
	int pos = buscar(var);
	
	if(pos == -1)
		pos = declarar(var);
	TV[pos].valor = val;
}

//Devuelve el valor de la varible buscada
int valor(char* var)
{
	int pos = buscar(var);
	if(pos == -1)
		return 0;
	return TV[pos].valor;
}

//Devuelve la posicion de la variable en la TV
int buscar(char* var)
{
	for(int i = 0; i < VARCOUNT; i++)
	{
		if(strcmp(TV[i].nombre, var) == 0)
		{
			return i;
		}
	}
	return -1;
}

//Agrega la nueva variable a la tabla y devuelve su posicion
int declarar(char* var)
{
	if(VARCOUNT < 128)
	{
		VAR aux;
		aux.nombre = var;
		TV[VARCOUNT] = aux;
		VARCOUNT++;
		return VARCOUNT-1;
	}
	yyerror("max variables");
	return -1;
}

%}

%start objetivo

%token INICIO FIN LEER ESCRIBIR ID CONSTANTE PARENIZQ PARENDER PUNTOYCOMA COMA ASIGNACION SUMA RESTA FDT ERRORLEXICO

%union
{
    int num;
    char *str;
}

%type <char*> ID
%type <int> CONSTANTE
%type <int> expresion
%type <int> primaria
%type <int> operador

%%

objetivo: 
		programa FDT {return 0;}
		;

programa:
		INICIO listaSentencias FIN {printf("Fin de Programa\n\n");}
		;

listaSentencias:
		sentencia
		|
        sentencia listaSentencias
		;

sentencia:
		ID ASIGNACION expresion PUNTOYCOMA {printf("Asigna %d a %s\n", $<num>3, $<str>1); asignar($<str>1, $<num>3);}
		|
		LEER PARENIZQ listaIdentificadores PARENDER PUNTOYCOMA {printf("Lee %s\n", $<str>3);}
		|
		ESCRIBIR PARENIZQ listaExpresiones PARENDER PUNTOYCOMA {printf("Escribe %s\n", $<str>3);}
		;
		
listaIdentificadores:
		ID {$<str>$ = $<str>1;}
		|
		ID COMA listaIdentificadores {char aux[100]; strcpy(aux, $<str>1); strcat(aux, ", "); strcat(aux, $<str>3); $<str>$ = strdup(aux);}
		;

listaExpresiones:
		expresion {char aux[100]; $<str>$ = strdup(itoa($<num>1, aux, 10));}
		|
		expresion COMA listaExpresiones {char aux[100]; itoa($<num>1, aux, 10); strcat(aux, ", "); strcat(aux, $<str>3); $<str>$ = strdup(aux);}
		;

expresion:
		primaria {$<num>$ = $<num>1;}
		|
		primaria operador expresion {$<num>$ = $<num>1 + $<num>2 * $<num>3;}
		;
		
primaria:
		ID {$<num>$ = valor($<str>1);}
		|
		CONSTANTE {$<num>$ = $<num>1;}
		|
		PARENIZQ expresion PARENDER {$<num>$ = $<num>2;}
		;
		
operador:
		SUMA {$<num>$ = 1;}
		|
		RESTA {$<num>$ = -1;}
		;
