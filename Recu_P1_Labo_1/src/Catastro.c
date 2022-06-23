/*
 * Catastro.c
 *
 *  Created on: 17 jun. 2022
 *      Author: Mauro
 */
#include "Catastro.h"
#include "utn.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void Catastro_hardcodearCatastros(eCatastro* list, int len){
	// {{1000,"Avellaneda",28,1540},{1001,"Lanus",43,1789},{1002,"Quilmes",32,1624},{1003,"La Plata",67,1677},{1004,"Lomas de Zamora",32,1923}};
	int ids[5]={1000,1001,1002,1003,1004};
	char localidades[5][25]={"Avellaneda","Lanus","Quilmes","La Plata","Lomas de Zamora"};
	int manzanas[5]={28,43,32,67,32};
	int parcelas[5]={1540,1789,1624,1677,1923};
	for(int i=0;i<len;i++){
		(*(list+i)).idCatastro=ids[i];
		strcpy((*(list+i)).localidad,localidades[i]);
		(*(list+i)).manzana=manzanas[i];
		(*(list+i)).parcela=parcelas[i];
	}
}
/**
 * Finds by id an eCatastro struct in an eCatastro array and returns its index
 * @param *list pointer to an eCatastro array
 * @param len eCatastro array len
 * @param id eCatastro id to find
 * @return -1 if error (NULL pointer or no match found) - index found if ok
 */
int Catastro_getIndexById(eCatastro* list, int len, int id){
	int retorno=-1;
	if(list!=NULL&&id>-1) {
	    for(int i=0;i<len;i++){
	        if((*(list + i)).idCatastro==id) {
	        	retorno=i;
	            break;
	        }
	    }
	}
	return retorno;
}

/**
 * Finds by localidad the corresponding id and returns the id
 * @param list eCatastro array pointer
 * @param len int len
 * @param localidad char* localidad to find
 * @return int -1 if NULL pointer or localidad not valid or localidad corresponding ID
 */
int Catastro_getIdByLocalidad(eCatastro* list, int len, char* localidad){
	int retorno=-1;
	char localidadAux[30];
	if(list!=NULL&&localidad!=NULL) {
		stringToUpper(localidad,strlen(localidad));
	    for(int i=0;i<len;i++){
	    	strcpy(localidadAux,(*(list + i)).localidad);
	    	stringToUpper(localidadAux,strlen(localidadAux));
	        if(!strcmp(localidadAux,localidad)) {
	        	retorno=(*(list + i)).idCatastro;
	            break;
	        }
	    }
	}
	return retorno;
}

/**
 * Finds by id the corresponding localidad and returns the localidad
 * @param list eCatastro array pointer
 * @param len int len
 * @param idCatastro int id to find
 * @param localidad char* localidad to store the result
 * @return int -1 if NULL pointer or localidad not valid or 0 if ok
 */
int Catastro_getLocalidadById(eCatastro* list, int len, int idCatastro, char* localidad){
	int retorno=-1;
	if(list!=NULL&&localidad!=NULL) {
	    for(int i=0;i<len;i++){
	        if((*(list+i)).idCatastro==idCatastro) {
	        	retorno=0;
	        	strcpy(localidad,(*(list+i)).localidad);
	            break;
	        }
	    }
	}
	return retorno;
}

/**
 * Prints a single eCatastro entity information in line format
 * @param catastro eCatastro
 */
void Catastro_printCatastro(eCatastro catastro){
	printf("%-5d \t%-15s \t%-4d \t%-4d\n",catastro.idCatastro, catastro.localidad, catastro.manzana, catastro.parcela);
}

/**
 * Prints an eCatastro array information in table format
 * @param list eCatastro array pointer
 * @param len int len
 * @return -1 if NULL pointer or 0 if ok
 */
int Catastro_printCatastros(eCatastro* list,  int len){
    int retorno=-1;
    if(list!=NULL) {
    	retorno=0;
    	printf("ID      LOCALIDAD               MANZANA PARCELA\n");
        printf("--------------------------------------------------------\n");
        for(int i=0;i<len;i++){
        	Catastro_printCatastro(*(list+i));
        }
        printf("--------------------------------------------------------\n");
    }
    return retorno;
}
/**
 * Sorts eCatastro array by localidad alphabetically
 * @param list pointer to eCatastro array
 * @param len int len
 * @return -1 if null pointer or 0 if ok
 */
int Catastro_sortCatastrosByLocalidad(eCatastro* list, int len){
	int retorno=-1;
	int flagSwapeo;
	eCatastro aux;
	if(list!=NULL&&len>0){
		do {
			flagSwapeo = 0;
			for(int i=1; i<len; i++) {
				if(strcmp((*(list+i)).localidad, (*(list+i-1)).localidad)<0) {
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
