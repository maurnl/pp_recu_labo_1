/*
 * Menu.c
 *
 *  Created on: 17 jun. 2022
 *      Author: Mauro
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Controller.h"
#include "utn.h"

/**
 * Add eVivienda
 * @param list pointers to arrays of eVivienda, eCensista, eCatastro
 * @param int arrays len
 * @return -3 if NULL pointer(s) or -2 if no free space avaliable or -1 if addVivienda was canceled or 0 if addVivienda was successful
 */
int Controller_addVivienda(eVivienda* viviendaList,eCensista* censistaList,eCatastro* catastroList,int lenVivienda,int lenCensista,int lenCatastro, int *viviendasActivas, int *idVivienda){
	int retorno=-3;
	char tipoDescTmp[13];
	char calleTmp[25];
	int cantidadPersonasTmp;
	int cantidadHabitacionesTmp;
	int tipoViviendaTmp;
	int legajoCensistaTmp;
	int idCatastroTmp;
	if(viviendaList!=NULL&&censistaList!=NULL&&catastroList!=NULL&&viviendasActivas!=NULL&&idVivienda!=NULL&&lenVivienda>0&&lenCensista>0&&lenCatastro>0){
		retorno=-2;
		if(Vivienda_getEmptyIndex(viviendaList, lenVivienda)!=-1){
			retorno=-1;
			printf("\t\t**REGISTRAR NUEVA VIVIENDA**\n");
			if(!Censista_printCensistas(censistaList,lenCensista)
			   &&!getPositiveInt("- INGRESE CENSISTA POR LEGAJO: ", &legajoCensistaTmp, 0, 200)
			   &&Censista_getIndexById(censistaList, lenCensista, legajoCensistaTmp)!=-1
			   &&!Catastro_printCatastros(catastroList,lenCatastro)
			   &&!getPositiveInt("- INGRESE CATASTRO POR ID: ", &idCatastroTmp, 1000, 2000)
			   &&Catastro_getIndexById(catastroList,lenCatastro,idCatastroTmp)!=-1
			   &&!getAlphabeticText("- INGRESE CALLE DE LA VIVIENDA: ", calleTmp, 25)
			   &&!getPositiveInt("- INGRESE LA CANTIDAD DE PERSONAS QUE VIVEN EN EL HOGAR (1-20): ", &cantidadPersonasTmp, 1, 20)
			   &&!getPositiveInt("- INGRESE LA CANTIDAD DE HABITACIONES QUE POSEE EL HOGAR (1-20): ", &cantidadHabitacionesTmp, 1, 20)
			   &&!getAlphabeticText("- INGRESE TIPO VIVIENDA(CASA - DEPARTAMENTO - CASILLA - RANCHO): ", tipoDescTmp, 14)
			   && Vivienda_TipoViviendaStrToInt(tipoDescTmp) )
			{
				retorno=1;
				tipoViviendaTmp=Vivienda_TipoViviendaStrToInt(tipoDescTmp);
				printf("- DATOS INGRESADOS:\n");
				printf("CALLE                   PERSONAS        HABITACIONES   TIPO DE VIVIENDA    LEGAJO CENSISTA   ID CATASTRO\n");
				printf("---------------------------------------------------------------------------------------------------------\n");
				printf("%-17s \t%-4d\t%-4d\t%-8s\t%-8d\t%-5d\n",calleTmp,cantidadPersonasTmp,cantidadHabitacionesTmp,tipoDescTmp,legajoCensistaTmp,idCatastroTmp);
				printf("---------------------------------------------------------------------------------------------------------\n");
				if(confirm("DESEA DAR DE ALTA ESTA VIVIENDA(S/N)?")){
					retorno=0;
					Vivienda_addVivienda(viviendaList,lenVivienda,*idVivienda,calleTmp,cantidadPersonasTmp,cantidadHabitacionesTmp,tipoViviendaTmp,legajoCensistaTmp,idCatastroTmp);
					(*idVivienda)++;
					(*viviendasActivas)++;
				}
			}
		}
	}
	return retorno;
}

/**
 * Edit viviendas
 * @param viviendaList pointer to an eVivienda array
 * @param lenVivienda int eVivienda array len
 * @return -2 if NULL pointer(s) or -1 if no eVivienda found or 0 if eVivienda was found
 */
int Controller_editVivienda(eVivienda* viviendaList,int lenVivienda){
	int retorno=-2;
	int opcion, indice, idVivienda;
	char calleBuff[25], tipoDesc[25];
	int cantPersonasBuff, cantHabitacionesBuff, tipoViviendaBuff;
	if((viviendaList!=NULL&&lenVivienda>0)){
		retorno=-1;
		Vivienda_printViviendas(viviendaList, lenVivienda);
		getPositiveInt("- INGRESE ID DE VIVIENDA A MODIFICAR: ",&idVivienda,0,100000);
		indice=Vivienda_getIndexById(viviendaList,lenVivienda,idVivienda);
		if(indice!=-1&&(*(viviendaList+indice)).isEmpty==0){
			retorno=0;
			printf("ID      CALLE                   PERSONAS         HABITACIONES   TIPO VIVIENDA   LEGAJO CENSISTA   ID CATASTRO\n");
			printf("-----------------------------------------------------------------------------------------------------------------\n");
			Vivienda_printVivienda((*(viviendaList+indice)));
			printf("-----------------------------------------------------------------------------------------------------------------\n");
			do{
				getPositiveInt("- INGRESE DATO A MODIFICAR:\n\t1. CALLE\n\t2. CANT. PERSONAS\n\t3. CANT. HABITACIONES\n\t4. TIPO DE VIVIENDA.\n\t5. VOLVER AL MENU",&opcion,1,5);
				switch(opcion){
					case 1:
						getAlphanumericText("- INGRESE NUEVA CALLE: ", calleBuff,25);
						printf("- CALLE NUEVA: '%s'.\n", calleBuff);
						if(confirm("- CONFIRME MODIFICACION DE CALLE(S/N)"))
							strcpy((*(viviendaList+indice)).calle, calleBuff);
						break;
					case 2:
						getPositiveInt("- INGRESE CANTIDAD DE PERSONAS NUEVA: ",&cantPersonasBuff,1,20);
						printf("- CANT. PERSONAS NUEVA: %d.\n", cantPersonasBuff);
						if(confirm("- CONFIRME MODIFICACION DE CANT. PERSONAS(S/N)"))
							(*(viviendaList+indice)).cantidadPersonas=cantPersonasBuff;
						break;
					case 3:
						getPositiveInt("- INGRESE CANTIDAD DE HABITACIONES NUEVA: ",&cantHabitacionesBuff,1,20);
						printf("- CANT. HABITACIONES NUEVA: %d.\n", cantHabitacionesBuff);
						if(confirm("- CONFIRME MODIFICACION DE CANT. HABITACIONES(S/N)"))
							(*(viviendaList+indice)).cantidadHabitaciones=cantHabitacionesBuff;
						break;
					case 4:
						getAlphabeticText("- INGRESE TIPO VIVIENDA(CASA - DEPARTAMENTO - CASILLA - RANCHO): ", tipoDesc, 14);
						while(!Vivienda_TipoViviendaStrToInt(tipoDesc)){
							getAlphabeticText("- INGRESE TIPO VIVIENDA(1.CASA - 2.DEPARTAMENTO - 3.CASILLA - 4.RANCHO): ", tipoDesc, 14);
						}
						tipoViviendaBuff=Vivienda_TipoViviendaStrToInt(tipoDesc);
						Vivienda_TipoViviendaIntToStr(tipoViviendaBuff,tipoDesc);
						printf("- TIPO DE VIVIENDA NUEVO: %s.\n", tipoDesc);
						if(confirm("- CONFIRME MODIFICACION DE TIPO DE VIVIENDA(S/N)")){
							(*(viviendaList+indice)).tipoVivienda.id=tipoViviendaBuff;
							strcpy((*(viviendaList+indice)).tipoVivienda.descripcion,tipoDesc);
						}
						break;
				}
				printf("ID      CALLE                   PERSONAS         HABITACIONES   TIPO VIVIENDA   LEGAJO CENSISTA   ID CATASTRO\n");
				printf("-----------------------------------------------------------------------------------------------------------------\n");
				Vivienda_printVivienda((*(viviendaList+indice)));
				printf("-----------------------------------------------------------------------------------------------------------------\n");
				while(confirm("- << PRESIONE ENTER PARA CONTINUAR... >>"));
			}while(opcion!=5);
		}
	}
	return retorno;
}

/**
 * Remove viviendas
 * @param viviendaList pointer to an eVivienda array
 * @param lenVivienda int eVivienda array len
 * @param viviendasActivas int currently active Viviendas(isEmpty==0)
 * @return -1 if NULL pointer(s) or -1 if remove fails(id not found or canceled) or 0 if remove was successful
 */
int Controller_removeVivienda(eVivienda* list, int len, int* viviendasActivas){
	int retorno=-2;
	int id;
	if(list!=NULL&&len>0){
		Vivienda_printViviendas(list, len);
		getPositiveInt("- INGRESE ID DE VIVIENDA A DAR DE BAJA: ",&id,0,10000);
		retorno=Vivienda_removeVivienda(list, len, id);
		if(!retorno)
			(*viviendasActivas)--;
	}
	return retorno;
}

/**
 * Lists viviendas with censista and catastro information
 * @param viviendaList pointer to an eVivienda array
 * @param censistaList pointer to an eCensista array
 * @param catastroList pointer to an eCatastro array
 * @param lenVivienda int vivienda array len
 * @param lenCensista int censista array len
 * @param lenCatastro int catastro array len
 * @return if NULL pointer or 0 if ok
 */
int Controller_listVivienda(eVivienda* viviendaList,eCensista* censistaList,eCatastro* catastroList,int lenVivienda,int lenCensista,int lenCatastro){
	int retorno=-1;
	if(viviendaList!=NULL&&censistaList!=NULL&&catastroList!=NULL&&lenVivienda>0&&lenCensista>0&&lenCatastro>0){
		Vivienda_sortViviendasByCalle(viviendaList, lenVivienda);
		retorno=Listado_listViviendas(viviendaList,censistaList,catastroList,lenVivienda,lenCensista,lenCatastro);
		while(confirm("- << PRESIONE ENTER PARA CONTINUAR... >>"));
	}
	return retorno;
}

/**
 * List censistas
 * @param list pointer tu an eCensista array
 * @param len int censista array len
 * @return -1 if NULL pointer or 0 if ok
 */
int Controller_listCensista(eCensista* list,int len){
	int retorno=-1;
	if(list!=NULL&&len>0){
		retorno=Censista_printCensistas(list, len);
		while(confirm("- << PRESIONE ENTER PARA CONTINUAR... >>"));
	}
	return retorno;
}

/**
 * List catastro
 * @param list pointer tu an eCatastro array
 * @param len int catastro array len
 * @return -1 if NULL pointer or 0 if ok
 */
int Controller_listCatastro(eCatastro* list,int len){
	int retorno=-1;
	if(list!=NULL&&len>0){
		Catastro_sortCatastrosByLocalidad(list, len);
		retorno=Catastro_printCatastros(list, len);
		while(confirm("- << PRESIONE ENTER PARA CONTINUAR... >>"));
	}
	return retorno;
}

/**
 * Lists viviendas filtered by some criteria
 * @param viviendaList pointer to an eVivienda array
 * @param censistaList pointer to an eCensista array
 * @param catastroList pointer to an eCatastro array
 * @param lenVivienda int vivienda array len
 * @param lenCensista int censista array len
 * @param lenCatastro int catastro array len
 * @return -1 if NULL pointer or 0 if ok
 */
int Controller_filterVivienda(eVivienda* viviendaList,eCensista* censistaList,eCatastro* catastroList,int lenVivienda,int lenCensista,int lenCatastro){
	char localidad[25];
	int opcion;
	char opcionStr[25];
	int tipoVivienda, idCatastro, legajoCensista;
	char descTipo[25];
	int retorno=-1;
	if(viviendaList!=NULL&&censistaList!=NULL&&catastroList!=NULL&&lenVivienda>0&&lenCensista>0&&lenCatastro>0){
		retorno=0;
		do{
			getPositiveInt("\t\t** INFORMES RECUPERATORIO **\n\t1. ELEGIR TIPO DE VIVIENDA Y MOSTRAR.\n\t2. ELEGIR LOCALIDAD Y MOSTRAR.\n\t3. CANTIDAD DE VIVIENDAS CENSADAS EN AVELLANEDA.\n\t4. ELEGIR CENSISTA Y MOSTRAR CENSADAS.\n\t5. CANTIDAD DE VIVIENDAS TIPO 'CASA'.\n\t6. CANTIDAD DE VIVIENDAS TIPO 'DEPARTAMENTO' EN 'LANUS'.\n\t7. VOLVER.",&opcion,1,7);
			switch(opcion){
				case 1:
					getAlphabeticText("- INGRESE TIPO DE VIVIENDA(CASA,DEPARTAMENTO,CASILLA O RANCHO): ",opcionStr,25);
					tipoVivienda=Vivienda_TipoViviendaStrToInt(opcionStr);
					if(tipoVivienda!=-1)
						Listado_listViviendasPorTipo(viviendaList, censistaList, catastroList, lenVivienda, lenCensista, lenCatastro, tipoVivienda);
					break;
				case 2:
					Catastro_printCatastros(catastroList, lenCatastro);
					getAlphabeticText("- INGRESE LOCALIDAD A LISTAR: ",opcionStr,25);
					idCatastro=Catastro_getIdByLocalidad(catastroList, lenCatastro, opcionStr);
					if(idCatastro!=-1){
						Catastro_printCatastro(*(catastroList+Catastro_getIndexById(catastroList, lenCatastro, idCatastro)));
						Listado_listViviendasPorLocalidad(viviendaList, censistaList, lenVivienda, lenCensista, idCatastro);
					}
					break;
				case 3:
					printf("CANTIDAD DE VIVIENDAS CENSADAS EN AVELLANEDA: %d.\n",Listado_contarViviendasPorLocalidad(viviendaList, lenVivienda, 1000));
					break;
				case 4:
					Censista_printCensistas(censistaList, lenCensista);
					getPositiveInt("- INGRESE LEGAJO CENSISTA: ",&legajoCensista,0,1000);
					if(Censista_getIndexById(censistaList, lenCensista, legajoCensista)!=-1){
						Censista_printCensista(*(censistaList+Censista_getIndexById(censistaList, lenCatastro, legajoCensista)));
						Listado_listViviendasPorCensista(viviendaList, catastroList, lenVivienda, lenCatastro, legajoCensista);
					}
					break;
				case 5:
					Vivienda_TipoViviendaIntToStr(1, descTipo);
					printf("CANTIDAD DE VIVIENDAS CENSADAS DE TIPO '%s': %d.\n", descTipo,Listado_contarViviendasPorTipo(viviendaList, lenVivienda, 1));
					break;
				case 6:
					Vivienda_TipoViviendaIntToStr(2, descTipo);
					Catastro_getLocalidadById(catastroList, lenCatastro, 1001, localidad);
					printf("CANTIDAD DE VIVIENDAS CENSADAS DE TIPO '%s' EN '%s': %d.\n", descTipo,localidad,Listado_contarViviendasPorLocalidadYTipo(viviendaList, lenVivienda, 1001, 2));
					break;
			}
		}while(opcion!=7);
	}
	return retorno;
}

/*
int Controller_filterVivienda(eVivienda* viviendaList,eCensista* censistaList,eCatastro* catastroList,int lenVivienda,int lenCensista,int lenCatastro){
	char localidad[25];
	int opcion;
	char opcionStr[25];
	int tipoVivienda, idCatastro, legajoCensista;
	char descTipo[25];
	int (*pFuncionFiltro)(eVivienda, int)=NULL;
	do{
		getPositiveInt("\t\t** INFORMES RECUPERATORIO **\n\t1. ELEGIR TIPO DE VIVIENDA Y MOSTRAR.\n\t2. ELEGIR LOCALIDAD Y MOSTRAR.\n\t3. CANTIDAD DE VIVIENDAS CENSADAS EN AVELLANEDA.\n\t4. ELEGIR CENSISTA Y MOSTRAR CENSADAS.\n\t5. CANTIDAD DE VIVIENDAS TIPO 'CASA'.\n\t6. CANTIDAD DE VIVIENDAS TIPO 'DEPARTAMENTO'.\n\t7. VOLVER.",&opcion,1,7);
		switch(opcion){
			case 1:
				getAlphabeticText("- INGRESE TIPO DE VIVIENDA(CASA,DEPARTAMENTO,CASILLA O RANCHO): ",opcionStr,25);
				tipoVivienda=Vivienda_TipoViviendaStrToInt(opcionStr);
				if(tipoVivienda!=-1){
						pFuncionFiltro=Vivienda_filtrarPorTipo;
						Listado_listFiltrado(viviendaList, censistaList, catastroList, lenVivienda, lenCensista, lenCatastro, pFuncionFiltro,tipoVivienda);
				} else {
						printf("- TIPO DE VIVIENDA NO ENCONTRADO.\n");
				}
				break;
			case 2:
				Catastro_printCatastros(catastroList, lenCatastro);
				getAlphabeticText("- INGRESE LOCALIDAD A LISTAR: ",opcionStr,25);
				idCatastro=Catastro_getIdByLocalidad(catastroList, lenCatastro, opcionStr);
				if(idCatastro!=-1){
						pFuncionFiltro=Vivienda_filtrarPorLocalidad;
						Listado_listFiltrado(viviendaList, censistaList, catastroList, lenVivienda, lenCensista, lenCatastro, pFuncionFiltro,idCatastro);
				} else {
						printf("- LOCALIDAD NO ENCONTRADA.\n");
				}
				break;
			case 3:
				pFuncionFiltro=Vivienda_filtrarPorLocalidad;
				printf("CANTIDAD DE VIVIENDAS CENSADAS EN AVELLANEDA: %d.\n",Listado_contarFiltrado(viviendaList, lenVivienda, pFuncionFiltro,1000));
				break;
			case 4:
				Censista_printCensistas(censistaList, lenCensista);
				getPositiveInt("- INGRESE LEGAJO CENSISTA: ",&legajoCensista,0,1000);
				if(Censista_getIndexById(censistaList, lenCensista, legajoCensista)!=-1){
					pFuncionFiltro=Vivienda_filtrarPorLegajoCensista;
					Listado_listFiltrado(viviendaList, censistaList, catastroList, lenVivienda, lenCensista, lenCatastro, pFuncionFiltro, legajoCensista);
				} else {
					printf("- CENSISTA NO ENCONTRADO.\n");
				}
				break;
			case 5:
				Vivienda_TipoViviendaIntToStr(1, descTipo);
				pFuncionFiltro=Vivienda_filtrarPorTipo;
				printf("CANTIDAD DE VIVIENDAS CENSADAS DE TIPO '%s': %d.\n", descTipo,Listado_contarFiltrado(viviendaList, lenVivienda, pFuncionFiltro, 1));
				break;
			case 6:
				Vivienda_TipoViviendaIntToStr(2, descTipo);
				Catastro_getLocalidadById(catastroList, lenCatastro, 1001, localidad);
				printf("CANTIDAD DE VIVIENDAS CENSADAS DE TIPO '%s' EN '%s': %d.\n", descTipo,localidad,Listado_contarViviendasPorLocalidadYTipo(viviendaList, lenVivienda, 1001, 2));
				break;
		}
	}while(opcion!=7);
	return 0;
}
*/
