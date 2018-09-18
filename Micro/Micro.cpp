#include <stdio.h>

typedef enum{INICIO, FIN, LEER, ESCRIBIR, ID, CONST, ASIGNACION, PARENIZQ, PARENDER, COMA, PUNTOYCOMA, SUMA, RESTA, ERROR} TOKEN;

int transiciones[14][11] = 	{//		  l   d   +   -   :   =   ;   ,   (   )  esp
							 /*0*/	{ 1,  3,  9, 10, 11, 13,  5,  6,  7,  8,  0},
							 /*1*/	{ 1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2},
							 /*2*/	{13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13}, 
							 /*3*/	{13,  3,  4,  4,  4,  4,  4,  4,  4,  4,  4},
							 /*4*/	{13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13},
							 /*5*/	{13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13},
							 /*6*/	{13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13},
							 /*7*/	{13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13},
							 /*8*/	{13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13},
							 /*9*/	{13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13},
							 /*10*/	{13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13},
							 /*11*/	{13, 13, 13, 13, 13, 12, 13, 13, 13, 13, 13},
							 /*12*/	{13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13},
							 /*13*/	{13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13}
							};

char *simbolos[4][2] = 	{
							{"inicio", "PR"},
							{"fin", "PR"},
							{"escribir", "PR"},
							{"leer", "PR"}
						};
						
char buffer[256];

TOKEN scanner(char*);
void transicion(int&, char);
bool esLetra(char);
int obtenerColumna(char);
TOKEN esReservada(char*);
void agregarCaracter(char);
void limpiarBuffer();
void objetivo();
void programa();
void listaDeSentencias();
void sentencia();
void listaDeIdentificadores();
void listaDeExpresiones();
void expresion();
void primaria();

int main() {
	printf("buffer: %s\n\n", buffer);
	
	scanner("Program.mi");
}

void objetivo() {
	programa();
	match(EOF);
}

void programa() {
	match(INICIO);
	listaDeSentencias();
	match(FIN);
}

void listaDeSentencias() {
	/*sentencia();
	while() {
		sentencia();
	}*/
}

TOKEN scanner(char * file) {
	int estado = 0;
	FILE * f = fopen(file, "rt");
	char c = getc(f);
	
	while(!feof(f)) {
		transicion(estado, c);
		
		if(estado == 2) {
			ungetc(c, f);
			printf("<ID>");
			estado = 0;
			//return ID;
		}
		
		if(estado == 4) {
			ungetc(c, f);
			printf("<CONST>");
			estado = 0;
			//return CONST;
		}
		
		if(estado == 5) {
			printf("<PYC>");
			estado = 0;
			//return PUNTOYCOMA;
		}
		
		if(estado == 6) {
			printf("<COMA>");
			estado = 0;
			//return COMA;
		}
		
		if(estado == 7) {
			printf("<PARENIZQ>");
			estado = 0;
			//return PARENIZQ;
		}
		
		if(estado == 8) {
			printf("<PARENDER>");
			estado = 0;
			//return PARENDER;
		}
		
		if(estado == 9) {
			printf("<SUMA>");
			estado = 0;
			//return SUMA;
		}
		
		if(estado == 10) {
			printf("<RESTA>");
			estado = 0;
			//return RESTA;
		}
		
		if(estado == 12) {
			printf("<ASIGNACION>");
			estado = 0;
			//return ASIGNACION;
		}
		
		if(estado == 13) {
			printf("<ERROR>");
			estado = 0;
			return ERROR;
		}
		if(c == '\n')
			printf("\n");
		c = getc(f);
	}
	return ERROR;
}

void transicion(int &estado, char simbolo) {
	simbolo = obtenerColumna(simbolo);
	estado = transiciones[estado][simbolo];
}

bool esLetra(char simbolo) {
	return ((simbolo >= 'a' && simbolo <= 'z') || (simbolo >= 'A' && simbolo <= 'Z'));
}

bool esDigito(char simbolo) {
	return (simbolo >= '0' && simbolo <= '9');
}

int obtenerColumna(char simbolo) {
	if(esLetra(simbolo))
		return 0;
	if(esDigito(simbolo))
		return 1;
	switch(simbolo) {
		case '+': 	return 2;
					break;
		case '-': 	return 3;
					break;
		case ':': 	return 4;
					break;
		case '=': 	return 5;
					break;
		case ';': 	return 6;
					break;			
		case ',': 	return 7;
					break;
		case '(': 	return 8;
					break;
		case ')': 	return 9;
					break;
		case ' ': 	return 10;
					break;
		case '\n':	return 10;
					break;
	}
}

void agregarCaracter(char c) {
	char *p = buffer;
	while(*p != '\0') {
		p++;
	}
	
	*p = c;
	*(p+1) = '\0';
}

void limpiarBuffer() {
	buffer[0] = '\0';
}


