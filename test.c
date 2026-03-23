#include<stdio.h>

#define MAXLINE 255

const int MIN_SACRIFICIO = 0;
const int MAX_SACRIFICIO = 12;
const int STEP = 3;
const int INDEX_PUNTOS_MAXIMO = 4;
const int PUNTOS[5] = {-100, 10, 40, 70, 120};

void imprimir_puntos(int respuesta);

int main(void){
	imprimir_puntos(0);
	imprimir_puntos(1);
	imprimir_puntos(2);
	imprimir_puntos(3);
	imprimir_puntos(4);
	imprimir_puntos(5);
	imprimir_puntos(6);
	imprimir_puntos(7);
	imprimir_puntos(8);
	imprimir_puntos(9);
	imprimir_puntos(10);
	imprimir_puntos(11);
	imprimir_puntos(12);

	return 0;
}

void imprimir_puntos(int respuesta){

	int upper_range = 0;
	for(int i = 0; upper_range <= MAX_SACRIFICIO; i++){
		int lower_range = (MIN_SACRIFICIO+(STEP*i))+1;
		upper_range = MIN_SACRIFICIO+(STEP*(i+1));
		
		if(respuesta == MIN_SACRIFICIO){
			printf("%d\n", PUNTOS[0]);
			return;
		}else if(respuesta >= lower_range && respuesta <= upper_range){
			printf("%d\n", PUNTOS[i+1]); 
			return;
		}
	}
	return;
}
