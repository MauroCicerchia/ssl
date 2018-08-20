#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <iostream>
using namespace std;

int transiciones[7][7] = 	{  //0  x  nD nO nH \0 otro
						/*0-*/	{1, 6, 4, 6, 6, 6, 6},
						/*1*/	{3, 2, 6, 3, 6, 6, 6},
						/*2*/	{2, 6, 6, 6, 2, 5, 6},
						/*3*/	{3, 6, 6, 3, 6, 5, 6},
						/*4*/	{4, 6, 4, 6, 6, 5, 6},
						/*5+*/	{6, 6, 6, 6, 6, 6, 6},
						/*6*/	{6, 6, 6, 6, 6, 6, 6}
							};
							
void escribirNumero(char*, FILE*);
int automata(char*);
void transicion(int&, char);
int obtenerColumna(int, char);
int estadoSegunNumero(int, char);
bool esDecimal(char);
bool esOctal(char);
bool esHexa(char);
bool esLetraHexa(char);
int toDec(char);
int toOct(char);
int toHexa(char);

int main() {
	FILE * fin = fopen("input.txt", "rt");
	FILE * fout = fopen("output.bin", "wb");
	
	char s[128];
	char *num;
	
	while(fgets(s, sizeof(s), fin)) {		
		num = strtok(s, "#\n");
		escribirNumero(num, fout);
		
		while(num = strtok(NULL, "#\n")) {
			escribirNumero(num, fout);
		}
	}
	printf("\nArchivo escrito satisfactoriamente.");
	fclose(fin);
	fclose(fout);
}

void escribirNumero(char *num, FILE *f) {	
	int numFinal = automata(num);
	if(numFinal) {
		printf("%s	--> %d\n", num, numFinal);
		fwrite(&numFinal, sizeof(numFinal), 1, f);
	}
}

int automata(char *s) {
	int estado = 0, num = 0;
	
	for(int i = 0; i < strlen(s) + 1; i++) {
		transicion(estado, s[i]);
		
		if(estado == 2 && s[i] != 'x') {
			num = num * 16 + toHexa(s[i]);
		}
		
		if(estado == 3) {
			num = num * 8 + toOct(s[i]);
		}
		
		if(estado == 4) {
			num = num * 10 + toDec(s[i]);
		}
		
		if(estado == 5) {
			return num;
		}
		
		if(estado == 6) {
			return 0;
		}
	}
}

void transicion(int &estado, char simbolo) {
	simbolo = obtenerColumna(estado, simbolo);
	estado = transiciones[estado][simbolo];
}

int obtenerColumna(int estado, char simbolo) {
	if(simbolo == '0')
		return 0;
	if(simbolo == 'x')
		return 1;
	if(simbolo == '\0')
		return 5;
	return estadoSegunNumero(estado, simbolo);
}

int estadoSegunNumero(int estado, char simbolo) {
	if((estado == 0 || estado == 4) && esDecimal(simbolo))
		return 2;
	if((estado == 1 || estado == 3) && esOctal(simbolo))
		return 3;
	if(estado == 2 && esHexa(simbolo))
		return 4;
	return 6;
}

bool esDecimal(char simbolo) {
	return simbolo >= '1' && simbolo <= '9';
}

bool esOctal(char simbolo) {
	return simbolo >= '1' && simbolo <= '7';
}

bool esHexa(char simbolo) {
	return esDecimal(simbolo) || esLetraHexa(simbolo);
}

bool esLetraHexa(char simbolo) {
	simbolo = tolower(simbolo);
	return simbolo >= 'a' && simbolo <= 'f';
}

int toDec(char c) {
	return c - '0';
}

int toOct(char c) {
	return toDec(c);
}

int toHexa(char c) {
	if(esDecimal(c))
		return toDec(c);
	else
		return tolower(c) - 'a' + 10;
}
