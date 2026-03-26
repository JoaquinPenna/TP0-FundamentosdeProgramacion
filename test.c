#include<stdio.h>
#include<stdbool.h>
#include<string.h>
bool fecha_valida( int año, int mes, int separador );
bool mayor_de_edad(int año, int mes);
int main(void){
	char fecha[7];
	int año = 0;
	int mes = 0;
	char separador = '\0';
	do{
		printf("ingresar fecha (yyyy/mm): ");
		scanf("%d%c%d",&año , &separador, &mes);
	}while( !fecha_valida(año, mes, separador) );
	if (mayor_de_edad(año,mes)){
		printf("mayor de edad\n");
	}
	else{
		printf("-rechazado-\n");
	}
	return 0;
}

bool fecha_valida( int año, int mes, int separador ){
	if( año < 0 || mes < 0 || separador != '/' ){
		return false;
	}else if( año < 1000 || año > 9999 ){
		return false;
	}else if( mes < 1 || mes > 12 ){
		return false;
	}else if( (año == 2026 && mes > 3) || año > 2026 ){
		return false;
	}else if( (año == 1926 && mes < 3) || año < 1926 ){
		return false;
	}
	return true;
}

int calcular_edad(int año, int mes){:
	int edad = AÑ
	año actual - año, if mes < mes actual +1
}
