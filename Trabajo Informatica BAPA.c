#include <stdio.h>

#include <stdlib.h>

#define N 5005


//Aquí fuera no inicialicemos variables que nos la cargamos


//Aqui declaramos el prototipo de las funciones




struct info {
	int anio;
	int mes;
	int dia;
	char dia_semana[40];			// Los 3 primeros int, los 6 siguientes char, luego 3 int y luego 1 char final.
	char hora_inicio[40];
	char hora_fin[40];
	char actividad_base[100];
	char modalidad[100];
	char centro[100];
	int plazas;
	int ocupadas;
	int libres;
	char tipo_actividad[40];
};

int main (){

	struct info usuario[N];

	//Aquí vamos poniendo las variables que necesitemos, id poniendo un comentario para saber cual es cual y todas las que declareis juntas.

	//Variables Miguel

	int nusuarios = 0; //numero de usuarios, empezamos en cero weon
	int i = 0; //Contador para los vectores con los datos weon

	int opcion; //Opcion elegida en el menú

	//Variables Belén



	//Variables Pau




	//Variables Alonso






	//Primero leemos el fichero y cargamos los datos en la memoria

	FILE * fentrada;
	fentrada = fopen("deportes_ayuntamiento.txt","r");
	if (fentrada == NULL) {
		printf("Error abriendo el fichero, vuelva a intentarlo. \n \n");
		return 0;
	}


// Se puede hacer con la funcion feof (esta en el libro)

	while (fscanf(fentrada,"%d %d %d %s %s %s %s %s %s %d %d %d %s ",
	&usuario[i].anio,
	&usuario[i].mes,
	&usuario[i].dia,
	usuario[i].dia_semana,
	usuario[i].hora_inicio,
	usuario[i].hora_fin,					//Lo pongo en vertical porque asi podemos copiar y pegar si necesitamos usar varias de golpe.
	usuario[i].actividad_base,
	usuario[i].modalidad,
	usuario[i].centro,
	&usuario[i].plazas,
	&usuario[i].ocupadas,
	&usuario[i].libres,
	usuario[i].tipo_actividad
	)!= EOF){
		i++;
		nusuarios++;
	}
	fclose(fentrada);
	printf("Fichero leido correctamente");

	do {
		printf(" ** PORTAL DE DEPORTES DE LA COMUNIDAD DE MADRID  ** ");
		printf("Introduce una opcion:\n");
		printf("1. Ocupacion media por centro \n");
		printf("2. Ocupacion por actividad\n");
		printf("3. Ocupacion por franja de horario\n");
		printf("4. Comparación de uso entre centros\n");
		printf("5. Actividades de alta y baja demanda\n");
		printf("6. Ocupacion por franja de horario\n");
		printf("7. Comparación de uso entre centros\n");
		printf("8. Actividades de alta y baja demanda\n");
		printf("9. Análisis tipos de actividades\n");
		printf("'S' Para salir del programa.\n \n");
		scanf("%d", &opcion);
		switch(opcion) {
			case 1:
				printf("Ocupacion media por centro\n");
				break;

			case 2:
				printf("Ocupacion por actividad\n");
				break;

			case 3: //esta opcion trata de ordenar los alumnos de mayor a menor nota
				printf("Ocupacion por franja horaria");
				break;

			case 4:
				printf("Comparacion de uso entre centros\n");
				break;

			case 5:
				printf("Actividades de alta y baja demanda\n");
				break;


			case 6:
				printf("Ocupacion por franja de horario\n");
				break;

			case 7:
				printf("Comparacion de uso entre centros\n");
				break;

			case 8:
				printf("Actividades de alta y baja demanda\n");
				break;

			case 9:
				printf("Analisis tipos de actividades");
				break;

			case 'S':
				printf("Saliendo del programa, gracias por confiar en nosotros");
				break;

			default:
				printf("Opcion incorrecta, teclee otra opcion o escriba 'S' para salir del programa.");
		}
	}while (opcion!='S');



return 0;
}


//Ahora aqui abajo desarrollamos las funciones, yo propongo hacer por cada case una funcion, y asi tenemos el programa mas ordenado y limpio, en cada case simplemente inicializamos la funcion y listo.
//Al poner la funcion poned un comentario con vuestro nombre y lo que hace.
