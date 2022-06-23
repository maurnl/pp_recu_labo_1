/*
 * Censista.h
 *
 *  Created on: 17 jun. 2022
 *      Author: Mauro
 */

#ifndef CENSISTA_H_
#define CENSISTA_H_

typedef struct {
	int legajoCensista;
	char nombre[25];
	int edad;
	char telefono[25];
}eCensista;

#endif /* CENSISTA_H_ */

/**
 * Finds by legajo an eCensista struct in an eCensista array and returns its index
 * @param *list pointer to eCensista array
 * @param len eCensista array len
 * @param legajo eCensista.legajo
 * @return -1 if error (NULL pointer or no match found) - index found if ok
 */
int Censista_getIndexById(eCensista* list, int len, int legajo);
/**
 * Prints a single line containing information about an eCensista entity
 * @param eCensista censista struct
 */
void Censista_printCensista(eCensista censista);
/**
 * Prints an eVivienda array in table format
 * @param *list pointer to eCensista array
 * @param len eCensista array len
 * @return -1 if error(NULL pointer) - 0 if ok
 */
int Censista_printCensistas(eCensista* list,  int len);

void Censista_hardcodearCensistas(eCensista* list, int len);
