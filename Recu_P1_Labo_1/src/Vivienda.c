/*
 * Vivienda.c
 *
 *  Created on: 17 jun. 2022
 *      Author: Mauro
 */

#include "Vivienda.h"
#include "utn.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void Vivienda_hardcodearViviendas(eVivienda* list, int len, int* id,int* viviendasActivas){
	char calles[5][25]={"Avenida Algo","Calle uno","Zan Martin","Boulevard coso","Holasdas"};
	int cantPersonas[5]={1,5,7,1,5};
	int cantHabitaciones[5]={4,3,1,6,4};
	int tipos[5]={1,2,3,4,2};
	int legajos[5]={100,102,100,102,101};
	int catastros[5]={1000,1001,1004,1003,1001};
	for(int i=0;i<5;i++){
		Vivienda_addVivienda(list,len,*id,calles[i],cantPersonas[i],cantHabitaciones[i],tipos[i],legajos[i],catastros[i]);
		(*id)++;
		(*viviendasActivas)++;
	}
}
/**
 * Gets the first empty index in eVivienda* list and returns it
 * @param *list pointer to an eVivienda array
 * @param len array len
 * @return -1 if error (NULL pointer or no empty index) - 0 if ok
 */
int Vivienda_getEmptyIndex(eVivienda* list, int len) {
	int retornoAux=-1;
	if(list!=NULL&&len>0) {
		for(int i=0;i<len;i++){
			if((*(list + i)).isEmpty){
				retornoAux=i;
				break;
			}
		}
	}
	return retornoAux;
}
/**
 * Initializes an eVivienda array by setting isEmpty flag to 1
 * @param *list pointer to an eVivienda array
 * @param len array len
 * @return -1 if error (NULL pointer) - 0 if ok
 */
int Vivienda_initViviendas(eVivienda* list, int len)	{
	int retorno=-1;
	if(list!=NULL&&len>0) {
		for(int i=0;i<len;i++){
			(*(list + i)).isEmpty=1;
		}
		retorno=0;
	}
	return retorno;
}
/**
 * Adds a new eVivienda struct to an existing eVivienda array
 * @param *list pointer to an eVivienda array
 * @param len eVivienda array len
 * @param id new eVivienda data
 * @param calle new eVivienda data
 * @param personas new eVivienda data
 * @param habitaciones new eVivienda data
 * @param tipo new eVivienda data
 * @param legajoCensista int eCensista FK
 * @param idCatrasto int eCatastro FK
 * @return -1 if error (NULL pointer(s)) - 0 if ok
 */
int Vivienda_addVivienda(eVivienda* list,int len, int id, char* calle, int personas, int habitaciones, int tipo, int legajoCensista, int idCatastro){
	int retorno=-1;
	int emptyIndex;
	emptyIndex = Vivienda_getEmptyIndex(list, len);
	if(list!=NULL&&len>0&&id>-1&&calle!=NULL&&emptyIndex!=-1){
		stringToUpper(calle, 1);
		(*(list + emptyIndex)).idVivienda=id;
		strcpy((*(list + emptyIndex)).calle,calle);
		(*(list + emptyIndex)).cantidadPersonas =personas;
		(*(list + emptyIndex)).cantidadHabitaciones=habitaciones;
		(*(list + emptyIndex)).tipoVivienda=tipo;
		(*(list + emptyIndex)).legajoCensista=legajoCensista;
		(*(list + emptyIndex)).idCatastro=idCatastro;
		(*(list + emptyIndex)).isEmpty=0;
		retorno=0;
	}
	return retorno;
}
/**
 * Finds by id an eVivienda struct in an eVivienda array and returns its index
 * @param *list pointer to an eVivienda array
 * @param len eVivienda array len
 * @param id eVivienda id to find
 * @return -1 if error (NULL pointer or no match found) - index found if ok
 */
int Vivienda_getIndexById(eVivienda* list, int len, int id)	{
	int retorno=-1;
	if(list!=NULL&&len>0&&id>-1) {
		for(int i=0;i<len;i++){
			if((*(list + i)).idVivienda==id){
				retorno=i;
				break;
			}
		}
	}
	return retorno;
}
/**
 * Finds by id an eVivienda struct in an eVivienda array and sets its isEmpty flag to 1
 * @param *list pointer to an eVivienda array
 * @param len eVivienda array len
 * @param id eVivienda id to find
 * @return -1 if error(NULL pointer or no match found) - 0 if ok
 */
int Vivienda_removeVivienda(eVivienda* list,int len,int id){
	int retorno=-1;
	int indice;
	if(list!=NULL&&id>-1&&len>0){
		indice=Vivienda_getIndexById(list,len,id);
		if(indice!=-1){
			(*(list + indice)).isEmpty=1;
			retorno=0;
		}
	}
	return retorno;
}
/**
 * Ascending sorts an eVivienda array by calle and cantidadPersonas
 * @param *list pointer to an eVivienda array
 * @param len eVivienda array len
 * @return -1 if error(NULL pointer(s)) - 0 if ok
 */
int Vivienda_sortViviendasByCalle(eVivienda* list, int len){
	int retorno=-1;
	int flagSwapeo;
	eVivienda aux;
	if(list!=NULL&&len>0){
		do {
			flagSwapeo = 0;
			for(int i=1; i<len; i++) {
				if(strcmp((*(list+i)).calle, (*(list+i-1)).calle)<0||(!strcmp((*(list+i)).calle, (*(list+i-1)).calle)&&(*(list+i)).cantidadPersonas<(*(list+i-1)).cantidadPersonas)) {
					aux = *(list+i);
					*(list+i) = *(list+i-1);
					*(list+i-1) = aux;
					flagSwapeo = 1;
				}
			}
		} while(flagSwapeo);
		retorno = 1;
	}
	return retorno;
}
/**
 * Ascending sorts an eVivienda array by tipoVivienda
 * @param *list pointer to an eVivienda array
 * @param len eVivienda array len
 * @return -1 if error(NULL pointer(s)) - 0 if ok
 */
int Vivienda_sortViviendasByTipo(eVivienda* list, int len){
	int retorno=-1;
	int flagSwapeo;
	eVivienda aux;
	if(list!=NULL&&len>0){
		do {
			flagSwapeo = 0;
			for(int i=1; i<len; i++) {
				if((*(list+i)).tipoVivienda<(*(list+i-1)).tipoVivienda) {
					aux = *(list+i);
					*(list+i) = *(list+i-1);
					*(list+i-1) = aux;
					flagSwapeo = 1;
				}
			}
		} while(flagSwapeo);
		retorno = 1;
	}
	return retorno;
}
/**
 * Get tipoVivienda id by description
 * @param tipo char*
 * @return -1 if not valid tipoVivienda description or tipoVivienda id
 */
int Vivienda_TipoViviendaStrToInt(char* tipo){
	int retorno=-1;
	if(tipo!=NULL){
		stringToUpper(tipo,strlen(tipo));
		if(!strcmp("CASA",tipo)){
			retorno=1;
		}else if(!strcmp("DEPARTAMENTO",tipo)){
			retorno=2;
		}else if(!strcmp("CASILLA",tipo)){
			retorno=3;
		}else if(!strcmp("RANCHO",tipo)){
			retorno=4;
		}
	}
	return retorno;
}
/**
 * Get tipoVivienda description by description id
 * @param id int
 * @param tipo char* to store description
 * @return -1 if not valid id description or 0 if ok
 */
int Vivienda_TipoViviendaIntToStr(int id, char* tipo){
	int retorno=-1;
	if(id>0&&tipo!=NULL){
		switch(id){
		case 1:
			strncpy(tipo, "CASA",13);
			break;
		case 2:
			strncpy(tipo, "DEPARTAMENTO",13);
			break;
		case 3:
			strncpy(tipo, "CASILLA",13);
			break;
		case 4:
			strncpy(tipo, "RANCHO",13);
			break;
		}
		retorno=0;
	}
	return retorno;
}

/**
 * Prints a single eVivienda entity information in line format
 * @param vivienda eVivienda
 */
void Vivienda_printVivienda(eVivienda vivienda){
	char tipo[25];
	Vivienda_TipoViviendaIntToStr(vivienda.tipoVivienda, tipo);
	printf("%-4d \t%-17s \t%-8d \t %-8d \t%-8s \t%-8d \t%-5d\n",vivienda.idVivienda, vivienda.calle, vivienda.cantidadPersonas, vivienda.cantidadHabitaciones, tipo, vivienda.legajoCensista, vivienda.idCatastro);
}

/**
 * Prints an eVivienda array information in table format
 * @param list eVivienda array pointer
 * @param len int len
 * @return -1 if NULL pointer or 0 if ok
 */
int Vivienda_printViviendas(eVivienda* list, int len){
	int retorno=-1;
	if(list!=NULL&&len>0){
		retorno=0;
		printf("ID      CALLE                   PERSONAS         HABITACIONES   TIPO VIVIENDA   LEGAJO CENSISTA   ID CATASTRO\n");
		printf("-----------------------------------------------------------------------------------------------------------------\n");
		for(int i=0;i<len;i++){
			if((*(list+i)).isEmpty==0)
				Vivienda_printVivienda((*(list+i)));
		}
		printf("-----------------------------------------------------------------------------------------------------------------\n");
	}
	return retorno;
}

/* Funcion modificarVivienda
void Vivienda_modificarVivienda(eVivienda vivienda){
	int opcion,tipoViviendaBuff,cantHabitacionesBuff,cantPersonasBuff;
	char calleBuff[25], tipoDesc[25];
	printf("ID      CALLE                   PERSONAS         HABITACIONES   TIPO DE VIVIENDA    LEGAJO CENSISTA   ID CATASTRO\n");
	Vivienda_printVivienda(vivienda);
	do{
		getPositiveInt("- INGRESE DATO A MODIFICAR:\n\t1. CALLE\n\t2. CANT. PERSONAS\n\t3. CANT. HABITACIONES\n\t4. TIPO DE VIVIENDA.\n\t5. VOLVER AL MENU",&opcion,1,5);
		switch(opcion){
			case 1:
				getAlphanumericText("- INGRESE NUEVA CALLE: ", calleBuff,25);
				printf("- CALLE NUEVA: '%s'.\n", calleBuff);
				if(confirm("- CONFIRME MODIFICACION DE CALLE(S/N)"))
					strcpy(vivienda.calle, calleBuff);
				break;
			case 2:
				getPositiveInt("- INGRESE CANTIDAD DE PERSONAS NUEVA: ",&cantPersonasBuff,1,20);
				printf("- CANT. PERSONAS NUEVA: %d.\n", cantPersonasBuff);
				if(confirm("- CONFIRME MODIFICACION DE CANT. PERSONAS(S/N)"))
					vivienda.cantidadPersonas=cantPersonasBuff;
				break;
			case 3:
				getPositiveInt("- INGRESE CANTIDAD DE HABITACIONES NUEVA: ",&cantHabitacionesBuff,1,20);
				printf("- CANT. HABITACIONES NUEVA: %d.\n", cantHabitacionesBuff);
				if(confirm("- CONFIRME MODIFICACION DE CANT. HABITACIONES(S/N)"))
					vivienda.cantidadHabitaciones=cantHabitacionesBuff;
				break;
			case 4:
				printf("- TIPOS DE VIVIENDA: 1.CASA - 2.DEPARTAMENTO - 3.CASILLA - 4.RANCHO.\n");
				getAlphabeticText("- INGRESE TIPO VIVIENDA(CASA - DEPARTAMENTO - CASILLA - RANCHO): ", tipoDesc, 14);
				while(!Vivienda_TipoViviendaStrToInt(tipoDesc)){
					getAlphabeticText("- INGRESE TIPO VIVIENDA(1.CASA - 2.DEPARTAMENTO - 3.CASILLA - 4.RANCHO): ", tipoDesc, 14);
				}
				tipoViviendaBuff=Vivienda_TipoViviendaStrToInt(tipoDesc);
				Vivienda_TipoViviendaIntToStr(tipoViviendaBuff,tipoDesc);
				printf("- TIPO DE VIVIENDA NUEVO: %s.\n", tipoDesc);
				if(confirm("- CONFIRME MODIFICACION DE TIPO DE VIVIENDA(S/N)"))
					vivienda.tipoVivienda=tipoViviendaBuff;
				break;
		}
		printf("ID      CALLE                   PERSONAS         HABITACIONES   TIPO DE VIVIENDA    LEGAJO CENSISTA   ID CATASTRO\n");
		Vivienda_printVivienda(vivienda);
		while(confirm("- << PRESIONE ENTER PARA CONTINUAR... >>"));
	}while(opcion!=5);
}


int Vivienda_filtrarPorTipo(eVivienda vivienda,int tipo){
	int retorno=0;
	if(vivienda.tipoVivienda==tipo)
		retorno=1;
	return retorno;
}

int Vivienda_filtrarPorLocalidad(eVivienda vivienda,int idCatastro){
	int retorno=0;
	if(vivienda.idCatastro==idCatastro)
		retorno=1;
	return retorno;
}

int Vivienda_filtrarPorLegajoCensista(eVivienda vivienda,int legajoCensista){
	int retorno=0;
	if(vivienda.legajoCensista==legajoCensista)
		retorno=1;
	return retorno;
}
*/
