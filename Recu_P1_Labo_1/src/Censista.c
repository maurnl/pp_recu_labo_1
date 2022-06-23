/*
 * Censista.c
 *
 *  Created on: 17 jun. 2022
 *      Author: Mauro
 */

#include "Censista.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void Censista_hardcodearCensistas(eCensista* list, int len){
	int legajos[3]={100,101,102};
	char nombres[3][25]={"Ana","Juan","Sol"};
	int edades[3]={34,24,47};
	char telefonos[3][25]={"1203-2345","4301-54678","5902-37487"};
     // {{100,"Ana",34,"1203-2345"},{101,"Juan",24,"4301-54678"},{102,"Sol",47,"5902-37487"}};
	for(int i=0;i<len;i++){
		(*(list+i)).legajoCensista=legajos[i];
		strcpy((*(list+i)).nombre,nombres[i]);
		(*(list+i)).edad=edades[i];
		strcpy((*(list+i)).telefono, telefonos[i]);
	}
}
/**
 * Finds by id an eVivienda struct in an eCensista array and returns its index
 * @param *list pointer to an eCensista array
 * @param len eVivienda array len
 * @param id eCensista id to find
 * @return -1 if error (NULL pointer or no match found) - index found if ok
 */
int Censista_getIndexById(eCensista* list, int len, int legajo){
	int retorno=-1;
	if(list!=NULL&&legajo>-1) {
	    for(int i=0;i<len;i++){
	        if((*(list + i)).legajoCensista==legajo) {
	        	retorno=i;
	            break;
	        }
	    }
	}
	return retorno;
}
/**
 * Prints a single eCensista entity information in line format
 * @param censista eCensista
 */
void Censista_printCensista(eCensista censista){
	printf("%-5d \t%-7s \t%-4d \t%-4s\n",censista.legajoCensista, censista.nombre, censista.edad, censista.telefono);
}
/**
 * Prints an eCensista array information in table format
 * @param list eCensista array pointer
 * @param len int len
 * @return -1 if NULL pointer or 0 if ok
 */
int Censista_printCensistas(eCensista* list,  int len){
    int retorno=-1;
    if(list!=NULL) {
    	retorno=0;
    	printf("LEGAJO  NOMBRE          EDAD    TELEFONO\n");
        printf("--------------------------------------------------------\n");
        for(int i=0;i<len;i++){
			Censista_printCensista(*(list+i));
        }
        printf("--------------------------------------------------------\n");
    }
    return retorno;
}
