#include<stdio.h>
#include<stdbool.h>

#define MAXLINE 300

const char MENSAJE_RESPUESTA_INVALIDA[MAXLINE] ="respuesta invalida, inserta una respuesta valida en el formato que se encuentran en el menu\n";

const int PUNTOS_CORRECTA_1 = 100;
const int PUNTOS_PERDIDOS_POR_INTENTO = 20;
const int INTENTOS_MAX = 3;
const int NUMERO_OPCIONES_1 = 4;
const char CHARS_OP_1[] = {'J', 'A', 'S', 'B'};
const char OPCIONES_1[][MAXLINE] = {"Jebediah Springfield", "Los aliens", "Los Magios", "Sr. Burns"};
const char OPCION_CORRECTA_1 = CHARS_OP_1[0];

const int PUNTOS_2_CORRECTA = 50;
const int PUNTOS_2_INCORRECTA = -300;
const int NUMERO_OPCIONES_2 = 2;
const int OPCIONES_2[] = {'S', 'N'};

//1.preguntar
//2.escanear input
//3.verificar input. si es valido, pasar a siguiente pregunta, si es falso (y le quedan intentos) o es invalido seguir preguntando
//	3.1 si es valido: se debe sumar la cantidad de puntos segun la pregunta, y aumentar un coounter que mantenga cuenta de la pregunta en la que nos encontramos
//	3.2 si es falso: sumar uno al counter de intentos. si el counter = 3, imprimir -RECHAZADO- y salir del programa. si le quedan intentos, imprimir sus intentos restantes y seguir preguntando
//	3.3 si es invalido, no se suman intentos, solo tomar chars mayusculas

//ideas:
//	tener un diccionario por pregunta en el cual tenes el caracter asociado a cada respuesta como key y como valor tiene la respuesta en si. con eso podriamos imprimir los menus de manera que se puedan cambiar mas facilmente las preguntas si asi se desea


void imprimir_menu(int pregunta);
int puntos_ganados(int pregunta, int intentos, bool respuesta_2);
bool es_respuesta_valida(char respuesta, int pregunta);

int main(void){

	int pregunta = 1;
	int puntos_total = 0;

	bool respuesta_1_correcta = false;
	int intentos = 0;
	char respuesta_1;

	bool respuesta_2;
	char chartmp;
	bool respuesta_2_es_valida = false;

//	bool respuesta_3_correcta = false;
//	bool respuesta_4_correcta = false;

//pregunta 1
	do{
		imprimir_menu(pregunta);
		scanf(" %c",&respuesta_1);

		if(respuesta_1 == OPCION_CORRECTA_1){
			int puntos_1 = puntos_ganados(pregunta, intentos, false);
			printf("Respuesta correcta!\t +%d puntos\n", puntos_1);
			puntos_total += puntos_1;
			printf("Puntos totales: %d\n",puntos_total);
			respuesta_1_correcta = true;
		}
		else if( es_respuesta_valida(respuesta_1, pregunta) ){ 
			intentos++;
			if(intentos == INTENTOS_MAX){
				printf("-RECHAZADO-\n");
				return 1;
			}
			else{
				printf("respuesta incorrecta, te quedan %d intentos\n", INTENTOS_MAX - intentos);
			}
		}
		else{
			printf("%s",MENSAJE_RESPUESTA_INVALIDA);
		}
	}while( !respuesta_1_correcta ); 
	pregunta++;
	

//pregunta 2

	
	do{
		imprimir_menu(pregunta);
		scanf(" %c",&chartmp);
	       	if(chartmp == 'S'){
			respuesta_2 = true;
			respuesta_2_es_valida = true;
		}else if(chartmp == 'N'){
			respuesta_2 = false;
			respuesta_2_es_valida = true;
		}else{
			printf("%s",MENSAJE_RESPUESTA_INVALIDA);
		}
	}while( !respuesta_2_es_valida);

	int puntos_2 = puntos_ganados(pregunta, 0, respuesta_2);
	printf("Puntos: %d\n", puntos_2);
	puntos_total += puntos_2;
	printf("Puntos totales: %d\n",puntos_total);
	

//pregunta 3

	





	return 0;
}


void imprimir_menu(int pregunta){
	switch(pregunta){
		case 1:
			printf("1. ¿Quién fundó realmente Springfield?\n");
			for(int i = 0; i < NUMERO_OPCIONES_1; i++){
				printf("\t[%c] %s\n", CHARS_OP_1[i], OPCIONES_1[i]);
			}
			break;
		case 2:
			printf("2. ¿Promete mantener en secreto la existencia de los Magios?\n\t[S] si\n\t[N] no\n"); // hacer que funcione con un forlup
			break;
		case 3:
			printf("3. ¿Cuál es su fecha de nacimiento? (formato: yyyy/mm)\n");
			break;
		case 4:
			printf("4. ¿Cuántas donas estaría dispuesto a sacrificar para el Número Uno?\n");
			break;
		default:
			printf("DEBUG: NO DEBERIA LLEGAR A ESTE PUNTO, CHEQUEAR NUMERO DE PREGUNTA QUE SE PASA COMO ARGUMENTO\n");
			break;	
	}
}

int puntos_ganados(int pregunta, int intentos, bool respuesta_2){
	switch(pregunta){
		case 1:
			return PUNTOS_CORRECTA_1 - (intentos*PUNTOS_PERDIDOS_POR_INTENTO);
			break;
		case 2:
			if(respuesta_2 == true){
				return PUNTOS_2_CORRECTA;
			}else{
				return PUNTOS_2_INCORRECTA;
			}
			break;
	}
	return 666;
}

bool es_respuesta_valida(char respuesta, int pregunta){
	switch(pregunta){
		case 1:
			for(int i = 0; i < NUMERO_OPCIONES_1; i++){
				if(CHARS_OP_1[i] == respuesta){
					return true;
				}
			}
			return false;
			break;
		case 2:
			for(int i = 0; i < NUMERO_OPCIONES_2; i++){
				if(OPCIONES_2[i] == respuesta){
					return true;
				}
			}
			return false;
			break;
	}
	return false;
}


