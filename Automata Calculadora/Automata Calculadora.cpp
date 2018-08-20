#include <stdio.h>
#include <string.h>
#include <windows.h>

int transiciones[7][7] = 	{  //n  +  -  /  *  \0 otro
						/*0-*/	{2, 1, 1, 6, 6, 6, 6},
						/*1*/	{2, 6, 6, 6, 6, 6, 6},
						/*2*/	{2, 3, 3, 4, 4, 5, 6},
						/*3*/	{2, 6, 6, 6, 6, 6, 6},
						/*4*/	{2, 6, 6, 6, 6, 6, 6},
						/*5+*/	{6, 6, 6, 6, 6, 6, 6},
						/*6*/	{6, 6, 6, 6, 6, 6, 6}
							};

int calcular(char*);
void transicion(int&, char);
int obtenerColumna(char);
int sig(char);
int operar(int, char, int);

int main() {
	char operacion[128];
	int resultado;
	
	do{
		system("cls");
		printf("Ingrese operacion: ");
		fflush(stdin);
		scanf("%s", operacion);
		
		if(strcmp(operacion, "salir") != 0) {
			resultado = calcular(operacion);
			printf("Resultado: %d\n", resultado);
		}
		
		system("pause");
	} while(strcmp(operacion, "salir") != 0);
}

int calcular(char *operacion) {
	int estado = 0;	
	int parcial = 0;
	int total = 0;
	char operador = '+';
	int valor = 0;
	int signo = 1;
	
	for(int i = 0; i <= strlen(operacion); i++) {
		char simbolo = operacion[i];
		
		printf("%d-->(%c)-->", estado, simbolo);
		transicion(estado, operacion[i]);
		printf("%d\n", estado);
		
		if(estado == 1) {
			signo = sig(simbolo);
		}
		
		if(estado == 2) {
			valor = (valor * 10) + (simbolo - '0');
		}
		
		if(estado == 3) {
			parcial = operar(parcial, operador, valor);
			operador = simbolo;
			valor = 0;
			total += signo * parcial;
			parcial = 0;
			signo = sig(simbolo);
		}
		
		if(estado == 4) {
			parcial = operar(parcial, operador, valor);
			operador = simbolo;
			valor = 0;
		}
		
		if(estado == 5) {
			parcial = operar(parcial, operador, valor);
			total += signo * parcial;
			return total;
		}
		
		if(estado == 6) {
			printf("Expresion invalida.\n");
			break;
		}
	}
}

void transicion(int &estado, char simbolo) {
	simbolo = obtenerColumna(simbolo);
	estado = transiciones[estado][simbolo];
}

int obtenerColumna(char simbolo) {
	if(simbolo >= '0' && simbolo <='9')
		return 0;
	if(simbolo == '+')
		return 1;
	if(simbolo == '-')
		return 2;
	if(simbolo == '/')
		return 3;
	if(simbolo == '*')
		return 4;
	if(simbolo == '\0')
		return 5;
	return 6;
}

int sig(char simbolo) {
	if(simbolo == '+')
		return 1;
	return -1;
}

int operar(int n1, char operador, int n2) {
	switch(operador) {
		case '+':	return n1 + n2;
					break;
		case '-':	return n1 + n2;
					break;
		case '/':	return n1 / n2;
					break;
		case '*':	return n1 * n2;
					break;
	}
}
