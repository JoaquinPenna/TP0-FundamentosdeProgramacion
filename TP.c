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

const int AÑO_ACTUAL = 2026;
const int AÑO_MINIMO = 1926;
const int MES_ACTUAL = 3;
const int PUNTOS_POR_EDAD = 2;

const int LIMITES_FINALES[] = {0, 151, 251, 350};
const char RANGOS_FINALES[][MAXLINE] = {"-ASPIRANTE-", "-MAGIO NOVATO-", "-MAGIO-", "-LIDER SUPREMO"};
const int NRO_RANGOS = 4;

void imprimir_menu(int pregunta);
int puntos_ganados(int pregunta, int intentos, int respuesta);
bool es_respuesta_valida(int respuesta, int pregunta);
int suma_total_actual(int puntos_inicio, int puntos_pregunta);
bool fecha_valida( int año, int mes, char separador);
int calcular_edad(int año, int mes);
int resultado_final(int puntos_totales);


int main(void){

	int pregunta = 1;
	int puntos_total = 0;

	bool respuesta_1_correcta = false;
	int intentos = 0;
	char respuesta_1 = '\0';
	int puntos_1 = 0;

	bool respuesta_2;
	char chartmp;
	int puntos_2 = 0;

	int puntos_3 = 0;
	int año = 0;
	int mes = 0;
	int edad = 0;

	int respuesta_4 = 0;
	int puntos_4 = 0;


//pregunta 1
	do{
		imprimir_menu(pregunta);
		scanf(" %c",&respuesta_1);

		if(respuesta_1 == OPCION_CORRECTA_1){
			puntos_1 = puntos_ganados(pregunta, intentos, false);
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
		}else if(chartmp == 'N'){
			respuesta_2 = false;
		}else{
			printf("%s",MENSAJE_RESPUESTA_INVALIDA);
		}
	}while( !es_respuesta_valida(chartmp, pregunta));
	
	puntos_2 = puntos_ganados(pregunta, 0, respuesta_2);
	
	pregunta++;


//pregunta 3
	char separador = '\0';
	do{
		printf("Fecha de nacimiento[yyyy/mm]: ");
		scanf("%d%c%d", &año, &separador, &mes);
	}while( !fecha_valida(año, mes, separador) );

	edad = calcular_edad(año, mes);
	if (edad < 18){
		printf("-RECHAZADO-\n");
		return 1;
	}else{
		puntos_3 = puntos_ganados(pregunta, 0, edad);
	}
	pregunta++;


//pregunta 4
	do{
		imprimir_menu(pregunta);
		scanf("%d", &respuesta_4);
	}while( !(es_respuesta_valida(respuesta_4, pregunta)) );
	
	puntos_4 = puntos_ganados(pregunta,0,respuesta_4);
	
	pregunta++;


//fin de las preguntas
	puntos_total = puntos_1 + puntos_2 + puntos_3 + puntos_4;
	printf("puntaje total = %d\nPregunta 1: %d\nPregunta 2: %d\nPregunta 3: %d\nPregunta 4: %d\n", puntos_total, puntos_1, puntos_2, puntos_3, puntos_4);

	if(resultado_final(puntos_total) == 666){
		printf("-RECHAZADO-\n");
		return 1;
	}

	printf("%s\n", RANGOS_FINALES[resultado_final(puntos_total)]);

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

		case 3:
			return respuesta * PUNTOS_POR_EDAD;
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

bool es_respuesta_valida(int respuesta, int pregunta){
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
			return respuesta == 'S' || respuesta == 'N';
			break;

		case 4:
			return respuesta >= MIN_SACRIFICIO && respuesta <= MAX_SACRIFICIO;
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

bool fecha_valida( int año, int mes, char separador){
	if( año < 0 || mes < 0 || separador != '/' ){
		printf("%s",  MENSAJE_RESPUESTA_INVALIDA);
		return false;
	}else if( año < 1000 || año > 9999 ){
		printf("%s",  MENSAJE_RESPUESTA_INVALIDA);
		return false;
	}else if( mes < 1 || mes > 12 ){
		printf("%s",  MENSAJE_RESPUESTA_INVALIDA);
		return false;
	}else if( (año == AÑO_ACTUAL && mes > MES_ACTUAL) || año > AÑO_ACTUAL ){
		printf("%s",  MENSAJE_RESPUESTA_INVALIDA);
		return false;
	}else if( (año == AÑO_MINIMO && mes < MES_ACTUAL) || año < AÑO_MINIMO ){
		printf("%s",  MENSAJE_RESPUESTA_INVALIDA);
		return false;
	}
	return true;
}

int calcular_edad(int año, int mes){
	int edad = AÑO_ACTUAL - año;
	if( mes < MES_ACTUAL ){
		return edad;
	}else{
		return edad-1;
	}
}

//return index to the thingamajig
int resultado_final(int puntos_totales){
	for(int i = NRO_RANGOS; i >= 0; i--){
		if( puntos_totales >= LIMITES_FINALES[i] ){
			return i;
		}
	}
	return 666;
}

