/*
 ============================================================================
 Name        : main.c
 Author      : 
 Version     : la ke anda
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include "Controller.h"
#include "menu.h"
#include <stdio.h>
#define VIVIENDA_LEN 300
#define CENSISTA_LEN 3
#define CATASTRO_LEN 5
int main(void) {
	setbuf(stdout,NULL);
	int opcion, salida;
	int viviendasActivas=0;
	int idVivienda=20000;
	eVivienda viviendaList[VIVIENDA_LEN];
	eCensista censistaList[CENSISTA_LEN];
	eCatastro catastroList[CATASTRO_LEN];
	Vivienda_initViviendas(viviendaList,VIVIENDA_LEN);
	Vivienda_hardcodearViviendas(viviendaList, VIVIENDA_LEN, &idVivienda,&viviendasActivas);
	Censista_hardcodearCensistas(censistaList, CENSISTA_LEN);
	Catastro_hardcodearCatastros(catastroList, CATASTRO_LEN);
	do{
		opcion=menu(viviendasActivas);
		switch(opcion){
			case 1:
				salida=Controller_addVivienda(viviendaList,censistaList,catastroList,VIVIENDA_LEN,CENSISTA_LEN,CATASTRO_LEN,&viviendasActivas,&idVivienda);
				switch(salida){
				case -1:
					printf("- EL DATO INGRESADO NO ES VALIDO. REINTENTE.\n");
					break;
				case 0:
					printf("- VIVIENDA DADA DE ALTA CORRECTAMENTE.\n");
					break;
				case 1:
					printf("- ALTA CANCELADA CORRECTAMENTE.\n");
				}
				break;
			case 2:
				salida=Controller_editVivienda(viviendaList,VIVIENDA_LEN);
				if(salida==-1){
					printf("- ID DE VIVIENDA NO ENCONTRADO.\n");
				}
				break;
			case 3:
				salida=Controller_removeVivienda(viviendaList,VIVIENDA_LEN,&viviendasActivas);
				switch(salida){
					case -1:
						printf("- ID DE VIVIENDA NO ENCONTRADO.\n");
						break;
					case 0:
						printf("- VIVIENDA DADA DE BAJA CON EXITO.\n");
						break;
				}
				break;
			case 4:
				Controller_listVivienda(viviendaList,censistaList,catastroList,VIVIENDA_LEN,CENSISTA_LEN,CATASTRO_LEN);
				break;
			case 5:
				Controller_listCensista(censistaList,CENSISTA_LEN);
				break;
			case 6:
				Controller_listCatastro(catastroList,CATASTRO_LEN);
				break;
			case 7:
				Controller_filterVivienda(viviendaList,censistaList,catastroList,VIVIENDA_LEN,CENSISTA_LEN,CATASTRO_LEN);
				break;
			case 8:
				break;
		}
	}while(opcion!=8);
	return 0;
}
