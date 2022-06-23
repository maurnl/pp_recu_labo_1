/*
 * menu.c
 *
 *  Created on: 17 jun. 2022
 *      Author: Mauro
 */
#include "utn.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * options control for the program
 * @param viviendasActivas int
 * @return a valid option based on viviendasActivas
 */
int menu(int viviendasActivas){
	int retorno=-1;
	getPositiveInt("----------------------------------------------------------\n\n\t\t** MENU PRINCIPAL **\n\n\t\t1. ALTA VIVIENDA.\n\t\t2. MODIFICAR UNA VIVIENDA.\n\t\t3. BAJA VIVIENDA.\n\t\t4. LISTAR VIVIENDAS.\n\t\t5. LISTAR CENSISTAS.\n\t\t6. LISTAR CATASTROS ORDENADOS(A-Z).\n\t\t7. LISTADOS FRILTRADOS...\n\t\t8. SALIR\n\n----------------------------------------------------------\n\n- INGRESE OPCION: ",&retorno, 1, 8);
	if(((retorno>1 && retorno<5)||retorno==7) && viviendasActivas==0) {
		printf("- DEBE DAR DE ALTA AL MENOS UNA VIVIENDA ANTES DE CONTINUAR.\n");
		while(confirm("- << PRESIONE ENTER PARA CONTINUAR... >>"));
		retorno=1;
	}
	return retorno;
}
