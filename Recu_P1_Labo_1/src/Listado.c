/*
 * eRelacion.c
 *
 *  Created on: 17 jun. 2022
 *      Author: Mauro
 */
#include <stdlib.h>
#include <stdio.h>
#include "Listado.h"

/**
 *  Esta biblioteca cumple la funcion de relacionar las tres estructuras a la hora de imprimir en pantalla
 *  un listado general con todos los datos. Esto para mantener cada entidad y sus funcionalidades separadas
 *  de las demas.
 */
/**
 * Prints a single vivienda information with censista and catastro information
 * @param vivienda eVivienda entity
 * @param censista eCensista entity
 * @param catastro eCatastro entity
 */
void Listado_listVivienda(eVivienda vivienda, eCensista censista, eCatastro catastro){
	char tipoDesc[25];
	Vivienda_TipoViviendaIntToStr(vivienda.tipoVivienda, tipoDesc);
	printf("%-5d\t%-15s\t%-3d\t  %-3d\t\t%-13s\t  %-3d\t\t\t%-10s%-2d\t%-10s\t%-4d\t\t%-16s%-2d\t%-4d\n",vivienda.idVivienda, vivienda.calle, vivienda.cantidadPersonas,vivienda.cantidadHabitaciones,tipoDesc,vivienda.legajoCensista,censista.nombre,
			censista.edad,censista.telefono,vivienda.idCatastro,catastro.localidad,catastro.manzana,catastro.parcela);
}

/**
 * Prints a vivienda array information with censista and catastro information
 * @param viviendaList pointer to an eVivienda array
 * @param censistaList pointer to an eCensista array
 * @param catastroList pointer to an eCatastro array
 * @param lenVivienda int
 * @param lenCensista int
 * @param lenCatastro int
 * @return -1 if null pointer(s) or 0 if ok
 */
int Listado_listViviendas(eVivienda* viviendaList,eCensista* censistaList,eCatastro* catastroList,int lenVivienda,int lenCensista,int lenCatastro){
	int retorno=-1;
	int indiceCensista, indiceCatastro;
	if(viviendaList!=NULL&&censistaList!=NULL&&catastroList!=NULL&&lenVivienda>0&&lenCensista>0&&lenCatastro>0){
		retorno=0;
		printf("ID      CALLE           PERSONAS  HABITACIONES  TIPO DE VIVIENDA  LEGAJO CENSISTA       NOMBRE    EDAD  TELEFONO        ID CATASTRO     LOCALIDAD       MANZANA PARCELA\n");
		printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		for(int i=0;i<lenVivienda;i++){
			if((*(viviendaList+i)).isEmpty==0){
				indiceCensista=Censista_getIndexById(censistaList,lenCensista,(*(viviendaList+i)).legajoCensista);
				indiceCatastro=Catastro_getIndexById(catastroList,lenCatastro,(*(viviendaList+i)).idCatastro);
				Listado_listVivienda(*(viviendaList+i),*(censistaList+indiceCensista),*(catastroList+indiceCatastro));
			}
		}
		printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	}
	return retorno;
}

/**
 * Filters by tipoVivienda and prints a vivienda array information with vivienda, censista and catastro information if tipoVivienda is matched
 * @param viviendaList pointer to an eVivienda array
 * @param censistaList pointer to an eCensista array
 * @param catastroList pointer to an eCatastro array
 * @param lenVivienda int
 * @param lenCensista int
 * @param lenCatastro int
 * @param tipoVivienda int tipoVivienda to filter
 * @return -1 if null pointer(s) or 0 if ok
 */
int Listado_listViviendasPorTipo(eVivienda* viviendaList,eCensista* censistaList,eCatastro* catastroList,int lenVivienda,int lenCensista,int lenCatastro,int tipoVivienda){
	int retorno=-1;
	int indiceCensista, indiceCatastro;
	if(viviendaList!=NULL&&censistaList!=NULL&&catastroList!=NULL&&lenVivienda>0&&lenCensista>0&&lenCatastro>0){
		retorno=0;
		printf("ID      CALLE           PERSONAS  HABITACIONES  TIPO DE VIVIENDA  LEGAJO CENSISTA       NOMBRE    EDAD  TELEFONO        ID CATASTRO     LOCALIDAD       MANZANA PARCELA\n");
		printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		for(int i=0;i<lenVivienda;i++){
			if((*(viviendaList+i)).isEmpty==0&&(*(viviendaList+i)).tipoVivienda==tipoVivienda){
				indiceCensista=Censista_getIndexById(censistaList,lenCensista,(*(viviendaList+i)).legajoCensista);
				indiceCatastro=Catastro_getIndexById(catastroList,lenCatastro,(*(viviendaList+i)).idCatastro);
				Listado_listVivienda(*(viviendaList+i),*(censistaList+indiceCensista),*(catastroList+indiceCatastro));
			}
		}
		printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	}
	return retorno;
}
/**
 * Filters by tipoVivienda and returns the matches qty
 * @param viviendaList pointer to eVivienda array
 * @param lenVivienda int
 * @param tipoVivienda int tipoVivienda to filter
 * @return -1 if null pointer or qty matches
 */
int Listado_contarViviendasPorTipo(eVivienda* viviendaList,int lenVivienda,int tipoVivienda){
	int retorno=-1;
	if(viviendaList!=NULL&&lenVivienda>0){
		retorno=0;
		for(int i=0;i<lenVivienda;i++){
			if(!(*(viviendaList+i)).isEmpty&&(*(viviendaList+i)).tipoVivienda==tipoVivienda){
				retorno++;
			}
		}
	}
	return retorno;
}
/**
 * Filters by idCatastro and prints a vivienda array information with vivienda and censista information if idCatastro is matched
 * @param viviendaList pointer to an eVivienda array
 * @param censistaList pointer to an eCensista array
 * @param lenVivienda int
 * @param lenCensista int
 * @param idCatastro int idCatastro to filter
 * @return -1 if nullpointer or 0 if ok
 */
int Listado_listViviendasPorLocalidad(eVivienda* viviendaList,eCensista* censistaList,int lenVivienda,int lenCensista,int idCatastro){
	int retorno=-1;
	int indiceCensista;
	char tipoDesc[25];
	eVivienda vivienda;
	eCensista censista;
	if(viviendaList!=NULL&&censistaList!=NULL&&lenVivienda>0&&lenCensista>0){
		retorno=0;
		printf("ID      CALLE           PERSONAS  HABITACIONES  TIPO DE VIVIENDA        NOMBRE DEL CENSISTA \n");
		printf("----------------------------------------------------------------------------------------------\n");
		for(int i=0;i<lenVivienda;i++){
			vivienda=(*(viviendaList+i));
			indiceCensista=Censista_getIndexById(censistaList,lenCensista,vivienda.legajoCensista);
			censista=*(censistaList+indiceCensista);
			if(vivienda.isEmpty==0&&vivienda.idCatastro==idCatastro){
				Vivienda_TipoViviendaIntToStr(vivienda.tipoVivienda, tipoDesc);
				printf("%-5d\t%-15s\t%-3d\t  %-3d\t\t%-13s\t\t%-10s\n",vivienda.idVivienda, vivienda.calle, vivienda.cantidadPersonas,vivienda.cantidadHabitaciones,tipoDesc,censista.nombre);
			}
		}
		printf("----------------------------------------------------------------------------------------------\n");
	}
	return retorno;
}
/**
 * Filters by idCatastro and returns the matches qty
 * @param viviendaList pointer to eVivienda array
 * @param lenVivienda int
 * @param idCatastro int idCatastro to filter
 * @return -1 if null pointer or qty matches
 */
int Listado_contarViviendasPorLocalidad(eVivienda* viviendaList,int lenVivienda,int idCatastro){
	int retorno=-1;
	if(viviendaList!=NULL&&lenVivienda>0){
		retorno=0;
		for(int i=0;i<lenVivienda;i++){
			if(!(*(viviendaList+i)).isEmpty&&(*(viviendaList+i)).idCatastro==idCatastro){
				retorno++;
			}
		}
	}
	return retorno;
}
/**
 * Filters by idCatastro and tipoVivienda and returns the matches qty
 * @param viviendaList pointer to eVivienda array
 * @param lenVivienda int
 * @param idCatastro int idCatastro to filter
 * @param tipoVivienda int tipoVivienda to filter
 * @return -1 if null pointer or qty matches
 */
int Listado_contarViviendasPorLocalidadYTipo(eVivienda* viviendaList,int lenVivienda,int idCatastro,int tipoVivienda){
	int retorno=-1;
	if(viviendaList!=NULL&&lenVivienda>0){
		retorno=0;
		for(int i=0;i<lenVivienda;i++){
			if(!(*(viviendaList+i)).isEmpty&&(*(viviendaList+i)).idCatastro==idCatastro&&(*(viviendaList+i)).tipoVivienda==tipoVivienda){
				retorno++;
			}
		}
	}
	return retorno;
}

/**
 * Filters by legajoCensista and prints a vivienda array information with vivienda and catastro information if legajoCensista is matched
 * @param viviendaList pointer to an eVivienda array
 * @param catastroList pointer to an eCensista array
 * @param lenVivienda int
 * @param lenCatastro int
 * @param legajoCensista int legajoCensista to filter
 * @return -1 if nullpointer or 0 if ok
 */
int Listado_listViviendasPorCensista(eVivienda* viviendaList, eCatastro* catastroList,int lenVivienda, int lenCatastro,int legajoCensista){
	int retorno=-1;
	int indiceCatastro;
	char tipoDesc[25];
	eVivienda vivienda;
	eCatastro catastro;
	if(viviendaList!=NULL&&catastroList!=NULL&&lenVivienda>0&&lenCatastro>0){
		retorno=0;
		printf("ID      CALLE           PERSONAS  HABITACIONES  TIPO DE VIVIENDA  ID CATASTRO     LOCALIDAD       MANZANA PARCELA \n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		for(int i=0;i<lenVivienda;i++){
			vivienda=(*(viviendaList+i));
			indiceCatastro=Catastro_getIndexById(catastroList,lenCatastro,vivienda.idCatastro);
			catastro=*(catastroList+indiceCatastro);
			if(vivienda.isEmpty==0&&vivienda.legajoCensista==legajoCensista){
				Vivienda_TipoViviendaIntToStr(vivienda.tipoVivienda, tipoDesc);
				printf("%-5d\t%-15s\t%-3d\t  %-3d\t\t%-13s\t\t%-4d\t\t%-16s%-2d\t%-4d\n",vivienda.idVivienda, vivienda.calle, vivienda.cantidadPersonas,vivienda.cantidadHabitaciones,tipoDesc,vivienda.idCatastro,catastro.localidad,catastro.manzana,catastro.parcela);
			}
		}
		printf("------------------------------------------------------------------------------------------------------------------\n");
	}
	return retorno;
}



/*
 * **
 * Calls a filter function and prints a vivienda array information with censista and catastro information if 1 is returned
 * @param viviendaList pointer to an eVivienda array
 * @param censistaList pointer to an eCensista array
 * @param catastroList pointer to an eCensista array
 * @param lenVivienda int
 * @param lenCensista int
 * @param lenCatastro int
 * @param int (*pFunc)(eVivienda,int) filter function
 * @param criteria (filter function argument)
 * @return -1 if null pointers or 0 if ok
int Listado_listFiltrado(eVivienda* viviendaList,eCensista* censistaList,eCatastro* catastroList,int lenVivienda,int lenCensista,int lenCatastro,int (*pFunc)(eVivienda,int),int filtroFk){
	int retorno=-1;
	int indiceCensista, indiceCatastro;
	if(viviendaList!=NULL&&censistaList!=NULL&&catastroList!=NULL&&lenVivienda>0&&lenCensista>0&&lenCatastro>0){
		retorno=0;
		printf("ID      CALLE           PERSONAS  HABITACIONES  TIPO DE VIVIENDA  LEGAJO CENSISTA       NOMBRE    EDAD  TELEFONO        ID CATASTRO     LOCALIDAD       MANZANA PARCELA\n");
		printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		for(int i=0;i<lenVivienda;i++){
			if(!(*(viviendaList+i)).isEmpty&&pFunc(*(viviendaList+i),filtroFk)){
				indiceCensista=Censista_getIndexById(censistaList,lenCensista,(*(viviendaList+i)).legajoCensista);
				indiceCatastro=Catastro_getIndexById(catastroList,lenCatastro,(*(viviendaList+i)).idCatastro);
				Listado_listVivienda(*(viviendaList+i),*(censistaList+indiceCensista),*(catastroList+indiceCatastro));
			}
		}
		printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	}
	return retorno;
}
 * **
 * Calls a filter function and counts matching eVivienda entities
 * @param viviendaList pointer to an eVivienda array
 * @param lenVivienda int
 * @param int (*pFunc)(eVivienda,int) filter function
 * @param criteria (filter function argument)
 * @return -1 if null pointers or 0 if ok
int Listado_contarFiltrado(eVivienda* viviendaList,int lenVivienda,int (*pFunc)(eVivienda,int),int filtroFk){
	int retorno=-1;
	if(viviendaList!=NULL&&pFunc!=NULL&&lenVivienda>0){
		retorno=0;
		for(int i=0;i<lenVivienda;i++){
			if(!(*(viviendaList+i)).isEmpty&&pFunc(*(viviendaList+i),filtroFk))
				retorno++;
		}
	}
	return retorno;
}
*/
