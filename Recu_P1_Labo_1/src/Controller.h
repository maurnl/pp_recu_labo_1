/*
 * Menu.h
 *
 *  Created on: 17 jun. 2022
 *      Author: Mauro
 */
#include "Listado.h"

int Controller_addVivienda(eVivienda* viviendaList,eCensista* censistaList,eCatastro* catastroList,int lenVivienda,int lenCensista,int lenCatastro, int *viviendasActivas, int *idVivienda);
int Controller_editVivienda(eVivienda* viviendaList,int lenVivienda);
int Controller_removeVivienda(eVivienda* list, int len,int* viviendasActivas);
int Controller_listVivienda(eVivienda* viviendaList,eCensista* censistaList,eCatastro* catastroList,int lenVivienda,int lenCensista,int lenCatastro);
int Controller_listCensista(eCensista* list,int len);
int Controller_listCatastro(eCatastro* list,int len);
int Controller_filterVivienda(eVivienda* viviendaList,eCensista* censistaList,eCatastro* catastroList,int lenVivienda,int lenCensista,int lenCatastro);
