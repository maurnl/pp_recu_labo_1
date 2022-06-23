/*
 *  Listado.h
 *
 *  Created on: 17 jun. 2022
 *      Author: Mauro
 */
#include "Vivienda.h"
#include "Censista.h"
#include "Catastro.h"

void Listado_listVivienda(eVivienda vivienda, eCensista censista, eCatastro catastro);
int Listado_listViviendas(eVivienda* viviendaList,eCensista* censistaList,eCatastro* catastroList,int lenVivienda,int lenCensista,int lenCatastro);
int Listado_listViviendasPorTipo(eVivienda* viviendaList,eCensista* censistaList,eCatastro* catastroList,int lenVivienda,int lenCensista,int lenCatastro,int tipoVivienda);
int Listado_listViviendasPorTipos(eVivienda* viviendaList,eCensista* censistaList,eCatastro* catastroList,int lenVivienda,int lenCensista,int lenCatastro);
int Listado_contarViviendasPorTipo(eVivienda* viviendaList,int lenVivienda,int tipoVivienda);
int Listado_listViviendasPorLocalidad(eVivienda* viviendaList,eCensista* censistaList,int lenVivienda,int lenCensista,int idCatastro);
int Listado_contarViviendasPorLocalidad(eVivienda* viviendaList,int lenVivienda,int idCatastro);
int Listado_listViviendasPorCensista(eVivienda* viviendaList, eCatastro* catastroList,int lenVivienda, int lenCatastro,int legajoCensista);
int Listado_contarViviendasPorLocalidadYTipo(eVivienda* viviendaList,int lenVivienda,int idCatastro,int tipoVivienda);

//int Listado_listFiltrado(eVivienda* viviendaList,eCensista* censistaList,eCatastro* catastroList,int lenVivienda,int lenCensista,int lenCatastro,int (*pFunc)(eVivienda,int),int filtroFk);
//int Listado_contarFiltrado(eVivienda* viviendaList,int lenVivienda,int (*pFunc)(eVivienda,int),int filtroFk);
