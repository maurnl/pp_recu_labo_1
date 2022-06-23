/*
 * Vivienda.h
 *
 *  Created on: 17 jun. 2022
 *      Author: Mauro
 */

#ifndef VIVIENDA_H_
#define VIVIENDA_H_

typedef struct {
	int id;
	char descripcion[25];
}TipoVivienda;

typedef struct {
	int idVivienda;
	char calle[25];
	int cantidadPersonas;
	int cantidadHabitaciones;
	TipoVivienda tipoVivienda;
	int legajoCensista; //FK Censista
	int idCatastro; //FK Catastro
	int isEmpty;
}eVivienda;

#endif /* VIVIENDA_H_ */

void Vivienda_hardcodearViviendas(eVivienda* list, int len, int* id,int* viviendasActivas);
int Vivienda_getEmptyIndex(eVivienda* list, int len);
int Vivienda_initViviendas(eVivienda* list, int len);
int Vivienda_addVivienda(eVivienda* list,int len, int id, char calle[], int personas, int habitaciones, int tipo, int legajoCensista,int idCatastro);
int Vivienda_getIndexById(eVivienda* list, int len, int id);
int Vivienda_removeVivienda(eVivienda* list,int len,int id);
int Vivienda_sortViviendasByCalle(eVivienda* list, int len);
int Vivienda_sortViviendasByTipo(eVivienda* list, int len);
int Vivienda_TipoViviendaStrToInt(char* tipo);
int Vivienda_TipoViviendaIntToStr(int id, char tipo[]);
void Vivienda_printVivienda(eVivienda vivienda);
int Vivienda_printViviendas(eVivienda* list, int len);

//int Vivienda_filtrarPorTipo(eVivienda vivienda,int tipo);
//int Vivienda_filtrarPorLocalidad(eVivienda vivienda,int idCatastro);
//int Vivienda_filtrarPorLegajoCensista(eVivienda vivienda,int legajoCensista);

