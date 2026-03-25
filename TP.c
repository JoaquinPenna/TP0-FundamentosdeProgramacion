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

const int MIN_SACRIFICIO = 0;
const int MAX_SACRIFICIO = 12;
const int STEP = 3;
const int PUNTOS[5] = {-100, 10, 40, 70, 120};

void imprimir_menu(int pregunta);
int puntos_ganados(int pregunta, int intentos, int respuesta);
bool es_respuesta_valida(char respuesta, int pregunta);
int suma_total_actual(int puntos_inicio, int puntos_pregunta);

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
			puntos_total = suma_total_actual(puntos_total, puntos_ganados(pregunta, intentos, false));
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
	
	puntos_total = suma_total_actual(puntos_total, puntos_ganados(pregunta, 0, respuesta_2));
	
	pregunta++;

//pregunta 3
	pregunta++;


//pregunta 4
	int respuesta_4 = 0;
	do{
		imprimir_menu(pregunta);
		scanf("%d", &respuesta_4);
	}while( !(respuesta_4 >= MIN_SACRIFICIO && respuesta_4 <= MAX_SACRIFICIO) );
	
	puntos_total = suma_total_actual(puntos_total, puntos_ganados(pregunta,0,respuesta_4));
	
	pregunta++;


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
			printf("4. ¿Cuántas donas estaría dispuesto a sacrificar para el Número Uno? [%d-%d]\n", MIN_SACRIFICIO, MAX_SACRIFICIO);
			break;
		default:
			printf("DEBUG: NO DEBERIA LLEGAR A ESTE PUNTO, CHEQUEAR NUMERO DE PREGUNTA QUE SE PASA COMO ARGUMENTO\n");
			break;	
	}
}

int puntos_ganados(int pregunta, int intentos, int respuesta){
	switch(pregunta){
		case 1:
			return PUNTOS_CORRECTA_1 - (intentos*PUNTOS_PERDIDOS_POR_INTENTO);
			break;

		case 2:
			if(respuesta == true){
				return PUNTOS_2_CORRECTA;
			}else{
				return PUNTOS_2_INCORRECTA;
			}
			break;

		case 4:
			int upper_range = 0;
			for(int i = 0; upper_range <= MAX_SACRIFICIO; i++){
				int lower_range = (MIN_SACRIFICIO+(STEP*i))+1;
				upper_range = MIN_SACRIFICIO+(STEP*(i+1));
				
				if(respuesta == MIN_SACRIFICIO){
					return PUNTOS[0];
				}else if(respuesta >= lower_range && respuesta <= upper_range){
					return PUNTOS[i+1];
				}
			}

	}
	return 0;
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

int suma_total_actual(int puntos_inicio, int puntos_pregunta){
	   int puntos_fin = puntos_inicio + puntos_pregunta;
	   printf("puntos obtenidos: %d\n",puntos_pregunta);
	   printf("puntaje total: %d\n",puntos_fin);
	   return puntos_fin;
}
