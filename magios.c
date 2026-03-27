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
const int EDAD_MINIMA = 18;

const int LIMITES_FINALES[] = {0,151,251,350};
const char RESULTADOS_FINALES[][MAXLINE] = { "-ASPIRANTE-", "-MAGIO NOVATO-", "-MAGIO-", "-LIDER SUPREMO-"};
const int TOPE_RESULTADOS = 4;

void imprimir_menu(int pregunta); //
bool es_respuesta_valida(int respuesta, int pregunta);
bool fecha_valida( int año, int mes);
int puntos_ganados(int pregunta, int respuesta);
int calcular_edad(int año, int mes);
void resultado_final(int puntos_totales);


int main(void){

	int pregunta = 0;
	int puntos_total = 0;

	bool respuesta_1_correcta = false;
	int intentos = 0;
	int puntos_1 = 0;
	char respuesta_1 = '\0';

	bool respuesta_2;
	char chartmp;
	int puntos_2 = 0;

	int puntos_3 = 0;
	int año = 0;
	int mes = 0;
	int edad = 0;

	int respuesta_4 = 0;
	int puntos_4 = 0;


	pregunta++;
//pregunta 1
	do{
		imprimir_menu(pregunta);
		scanf(" %c",&respuesta_1);

		if(respuesta_1 == OPCION_CORRECTA_1){
			puntos_1 = puntos_ganados(pregunta, false) - intentos * PUNTOS_PERDIDOS_POR_INTENTO;
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
	printf("%d puntos\n", puntos_1);
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
	
	puntos_2 = puntos_ganados(pregunta, respuesta_2);
	printf("%d puntos\n", puntos_2);
	
	pregunta++;


//pregunta 3
	do{
		imprimir_menu(pregunta);
		scanf("%d/%d", &año, &mes);
	}while( !fecha_valida(año, mes) );

	edad = calcular_edad(año, mes);
	if (edad < EDAD_MINIMA){
		printf("-RECHAZADO-\n");
		return 1;
	}else{
		puntos_3 = puntos_ganados(pregunta, edad);
		printf("%d puntos\n", puntos_3);
	}
	pregunta++;


//pregunta 4
	do{
		imprimir_menu(pregunta);
		scanf("%d", &respuesta_4);
	}while( !(es_respuesta_valida(respuesta_4, pregunta)) );
	
	puntos_4 = puntos_ganados(pregunta, respuesta_4);
	printf("%d puntos\n", puntos_4);
	
	pregunta++;


//fin de las preguntas, calculo del resultado final
	//posible hacer que la funcion de puntos ganados reciba un pointer a un int donde luego de calcular los puntos ganados se sume a los puntos totales
	puntos_total = puntos_1 + puntos_2 + puntos_3 + puntos_4;
	printf("puntaje total = %d\nPregunta 1: %d\nPregunta 2: %d\nPregunta 3: %d\nPregunta 4: %d\n", puntos_total, puntos_1, puntos_2, puntos_3, puntos_4);

	resultado_final(puntos_total);

	return 0;

}

//PRE: se asume que la variable de "pregunta" se fue incrementando al ejecutarse el programa, y que esta estara entre 1 y 4,*/
//POST: se imprime un mensaje de la pregunta con la informacion sobre el formato y las opciones que tiene el usuario
void imprimir_menu(int pregunta){
	switch(pregunta){
		case 1:
			printf("1. ¿Quién fundó realmente Springfield?\n");
			for(int i = 0; i < NUMERO_OPCIONES_1; i++){
				printf("\t[%c] %s\n", CHARS_OP_1[i], OPCIONES_1[i]);
			}
			break;
		case 2:
			printf("2. ¿Promete mantener en secreto la existencia de los Magios?\n\t[S] si\n\t[N] no\n");
			break;
		case 3:
			printf("3.  ¿Cuál es su fecha de nacimiento? (formato: yyyy/mm)\n");
			break;
		case 4:
			printf("4. ¿Cuántas donas estaría dispuesto a sacrificar para el Número Uno? [%d-%d]\n", MIN_SACRIFICIO, MAX_SACRIFICIO);
			break;
	}
}


/*PRE: se asume que
 * 	la variable pregunta es igual al numero de la pregunta la cual fue respondida por el usuario
 * 	la respuesta del usuario fue validada y es la respuesta correcta si es que hay una
 * el parametro de intentos es para poder calcular los puntos de la pregunta 1, como las demas preguntas no los utilizan, lo pasamos con 0*/
//POST: se devuelve como un int la cantidad de puntos en base a la respuesta que se dio
int puntos_ganados(int pregunta, int respuesta){
	switch(pregunta){
		case 1:
			return PUNTOS_CORRECTA_1;
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


/*PRE: se asume que la variable pregunta es el numero de pregunta para el cual es la respuesta, y que la respuesta es del tipo solicitado en la prgunta
 * excepto para la pregunta 3 la cual tiene su propia funcion */
//POST: se devuelve true si el formato de la respuesta es valido y la respuesta esta en las opciones indicadas, y false si no
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


//PRE: se esperan 2 ints, y un character de la forma %d%c%d
//POST: se devuelve false si no se cumple con alguna de las condiciones para que la fecha de nacimiento sea valida, y true si no rompe ninguna regla
bool fecha_valida( int año, int mes){
	//hola profe, yo se que se ve feo pero podia hacerlo mucho mas feo
	if( año < 0 || mes < 0 ){
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


//PRE: recibe 2 ints validos
//POST: devuelve un int el cual indica la edad de la persona nacida en esa fecha
int calcular_edad(int año, int mes){
	int edad = AÑO_ACTUAL - año;
	if( mes < MES_ACTUAL ){
		return edad;
	}else{
		return edad-1;
	}
}


//PRE: se recibe la suma de todos los puntos como un entero
//POST: se imprime el estado segun el arreglo RESILTADOS_FINALES 
void resultado_final(int puntos){
	printf("Tu estado es: ");
	
	int i = 0;
	if ( puntos < LIMITES_FINALES[i] ){
		printf("-RECHAZADO-");
	}else if ( puntos >= LIMITES_FINALES[TOPE_RESULTADOS-1] ){
		printf("%s",RESULTADOS_FINALES[TOPE_RESULTADOS-1]);
	}
	while( i <= TOPE_RESULTADOS-1 ){
		if( puntos >= LIMITES_FINALES[i] && puntos < LIMITES_FINALES[i+1] ){
			printf("%s",RESULTADOS_FINALES[i]);
		}
		i++;
	}
}
