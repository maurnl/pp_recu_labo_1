/*
 * Catastro.h
 *
 *  Created on: 17 jun. 2022
 *      Author: Mauro
 */

#ifndef CATASTRO_H_
#define CATASTRO_H_

typedef struct {
	int idCatastro;
	char localidad[25];
	int manzana;
	int parcela;
}eCatastro;

#endif /* CATASTRO_H_ */

int Catastro_getIndexById(eCatastro* list, int len, int id);
int Catastro_getIdByLocalidad(eCatastro* list, int len, char* localidad);
int Catastro_getLocalidadById(eCatastro* list, int len, int idCatastro, char* localidad);
void Catastro_printCatastro(eCatastro catastro);
int Catastro_printCatastros(eCatastro* list,  int len);
int Catastro_sortCatastrosByLocalidad(eCatastro* list, int len);
void Catastro_hardcodearCatastros(eCatastro* list, int len);
