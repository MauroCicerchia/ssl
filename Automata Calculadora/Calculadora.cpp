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

void transicion(int&, char);
int obtenerColumna(char);
int sig(char);
int operar(int, char, int);

int main() {
	int estadoActual;
	char operacion[100];
	
	do{
		estadoActual = 0;
		
		int parcial = 0;
		int total = 0;
		char operador = '+';
		int valor = 0;
		int signo = 1;
		
		system("cls");
		printf("Ingrese operacion: ");
		fflush(stdin);
		scanf("%s", operacion);
		
		for(int i = 0; i <= strlen(operacion); i++) {
			char simbolo = operacion[i];
			
			printf("%d-->(%c)-->", estadoActual, simbolo);
			transicion(estadoActual, operacion[i]);
			printf("%d\n", estadoActual);
			
			if(estadoActual == 1) {
				signo = sig(simbolo);
			}
			
			if(estadoActual == 2) {
				valor = (valor * 10) + (simbolo - '0');
			}
			
			if(estadoActual == 3) {
				parcial = operar(parcial, operador, valor);
				operador = simbolo;
				valor = 0;
				total += signo * parcial;
				parcial = 0;
				signo = sig(simbolo);
			}
			
			if(estadoActual == 4) {
				parcial = operar(parcial, operador, valor);
				operador = simbolo;
				valor = 0;
			}
			
			if(estadoActual == 5) {
				parcial = operar(parcial, operador, valor);
				total += signo * parcial;
				printf("Resultado = %d\n", total);
				break;
			}
			
			if(estadoActual == 6) {
				printf("Expresion invalida.\n");
				break;
			}
			
			/*printf("signo = %d\n", signo);
			printf("valor = %d\n", valor);
			printf("parcial = %d\n", parcial);
			printf("total = %d\n", total);*/
			
			
		}
		system("pause");
	} while(strcmp(operacion, "salir") != 0);
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
