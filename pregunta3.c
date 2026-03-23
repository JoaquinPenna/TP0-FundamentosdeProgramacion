/*
* en el main: 
* 	separar string en str_año y str_mes
* 		mandar al validar_formato ambas strings que devuelve un bool sobre la validez del formato
*	transformar ambas strings en int_año e int_mes
*		enviar al validar_edades que devuelve un int sobre la validez de la edad
*/

#include<stdio.h>
#include<string.h>
#include<stdbool.h>

bool formato_valido(char* fecha);

int main(void){

	char usuario_fecha[10];
	scanf("%s", usuario_fecha);
	printf("%s\t%d\n", usuario_fecha, formato_valido(usuario_fecha));

	return 0;
}
	
bool formato_valido(char* fecha){
	int año_count = 0;
	int mes_count = 0;
	int slash_count = 0;

	for(int i = 0; i < strlen(fecha); i++){
		if( (fecha[i] >= '0' && fecha[i] <= '9') && slash_count == 0){
			año_count++;
		}else if( (fecha[i] >='0' && fecha[i] <= '9') && slash_count == 1 ){
			mes_count++;
		}else if( fecha[i] == '/' ){
			slash_count++;
			if( slash_count == 2 ){
				printf("FORMATO INVALIDO\n");
				return false;
			}
		}else{
			printf("FORMATO INVALIDO\n");
			return false;
		}
	}
	char* str_year = strtok(fecha, "/");
	char* str_month = str_year + año_count + 1; 

	if( año_count != 4 || !(mes_count == 2 || mes_count == 1) ){
		printf("FORMATO INVALIDO");
		return false;
	}
	return true;
}


