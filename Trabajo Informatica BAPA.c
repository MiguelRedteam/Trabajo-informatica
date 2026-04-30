#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 5005

//Aquí fuera no inicialicemos variables que nos la cargamos

//Aqui declaramos el prototipo de las funciones
struct info {
    int anio;
    int mes;
    int dia;
    char dia_semana[40];
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

int leer_archivo(const char *nombre_archivo, struct info usuario[]);

//Funciones nombradas
void analizarTiposActividades(struct info usuario[], int total_registros);//Pau
void analizarDemanda(struct info usuario[], int total_registros);//Pau
int leer_archivo(const char *nombre_archivo, struct info usuario[]); //De clase
void sustituirespacios(char texto[], int p);

int main (){

	 static struct info usuario[N];

	//Aquí vamos poniendo las variables que necesitemos, id poniendo un comentario para saber cual es cual y todas las que declareis juntas.

	//Variables Miguel
	int i = 0; //Contador para los vectores con los datos weon
	int opcion; //Opcion elegida en el menú (AHORA TODO NÚMEROS)
	int total_registros=0;

	//Variables Belén

	//Variables Pau

	//Variables Alonso

	//Primero leemos el fichero y cargamos los datos en la memoria
	total_registros = leer_archivo("deportes_ayuntamiento.txt", usuario);

    if (total_registros == 0) {
        printf("No se pudieron cargar datos o el archivo esta vacio.\n");
    }

	do {
		printf("\n ** PORTAL DE DEPORTES DE LA COMUNIDAD DE MADRID  ** \n");
		printf("Introduce una opcion:\n");
		printf("1. Ocupacion media por centro \n");
		printf("2. Ocupacion por actividad\n");
		printf("3. Ocupacion por franja de horario\n");
		printf("4. Comparacion de uso entre centros\n");
		printf("5. Actividades de alta y baja demanda\n");
		printf("6. Analisis tipos de actividades (Uso libre vs Dirigida)\n");
		printf("0. Salir del programa.\n");
		printf("Opcion: ");
		scanf("%d", &opcion);

		switch(opcion) {
			case 1:
				printf("\n--- Ocupacion media por centro ---\n");
				break;

			case 2:
				printf("\n--- Ocupacion por actividad ---\n");
				break;

			case 3:
				printf("\n--- Ocupacion por franja horaria ---\n");
				break;

			case 4:
				printf("\n--- Comparacion de uso entre centros ---\n");
				break;

			case 5:
				printf("\n--- Actividades de alta y baja demanda ---\n");
				break;

			case 6:
				printf("\n--- Analisis tipos de actividades ---\n");
				// AQUÍ ES DONDE LLAMARÁS A TU FUNCIÓN ASÍ:
			    analizarTiposActividades(usuario, total_registros);
				break;

			case 0:
				printf("\nSaliendo del programa, gracias por confiar en nosotros.\n");
				break;

			default:
				printf("\nOpcion incorrecta, teclee otra opcion o escriba '0' para salir del programa.\n");
		}
	} while (opcion != 0);

    return 0;
}

//Ahora aqui abajo desarrollamos las funciones.

//DESARROLLO DE FUNCIONES

//Leer archivo - Belén
int leer_archivo(const char *nombre_archivo, struct info usuario[]) {
    FILE *archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo %s\n", nombre_archivo);
        return 0;
    }

    char cabecera[N];
    fgets(cabecera, N, archivo); // Saltar la primera línea

   	int nusuarios = 0; //numero de usuarios, empezamos en cero
    int i = 0;

    // Mientras no lleguemos al máximo y el fscanf lea todos los campos que queremos
    while (i < N &&
           fscanf(archivo, "%d %d %d %s %s %s %s %s %s %d %d %d %s",
		&usuario[i].anio,
		&usuario[i].mes,
		&usuario[i].dia,
		usuario[i].dia_semana,
		usuario[i].hora_inicio,
		usuario[i].hora_fin,
		usuario[i].actividad_base,
		usuario[i].modalidad,
		usuario[i].centro,
		&usuario[i].plazas,
		&usuario[i].ocupadas,
		&usuario[i].libres,
		usuario[i].tipo_actividad
		) != EOF) {

        i++;
       	nusuarios++; //para saber el n total de usuarios
    }

    fclose(archivo);
    return i; // Devolvemos el total de lineas leídas para guardarlo en total_registros
}
//funciones :----D
//Pau analizar actividades dirigidas y libres:
void analizarTiposActividades(struct info usuario[], int total_registros){
int i=0;
int contador_libre=0;
int contador_dirigida=0;
for (i;i<total_registros;i++){
    if (strcmp(usuario[i].tipo_actividad,"uso_libre")==0){
        contador_libre=contador_libre+1;
    }else{
        contador_dirigida=contador_dirigida+1;
    }
}
printf("Sesiones de Uso Libre: %d\n", contador_libre);
printf("Sesiones de Actividad Dirigida: %d\n", contador_dirigida);
}

//Pau analizar demanda
void analizarDemanda(struct info usuario[], int total_registros){
    int i=0;
    int max_ocupadas = usuario[0].ocupadas;
    int min_ocupadas = usuario[0].ocupadas;
    int pos_max=0;
    int pos_min=0; //posiciones
    for (i=0;i< total_registros;i++){
        if(max_ocupadas<usuario[i].ocupadas){
            max_ocupadas=usuario[i].ocupadas;
            pos_max=i;
        }if(min_ocupadas>usuario[i].ocupadas){
            min_ocupadas=usuario[i].ocupadas;
            pos_min=i;
        }
    }
    printf("El juego MAS popular es %s con %d jugadores.\n", usuario[pos_max].ocupadas, max_ocupadas);
    printf("El juego MENOS popular es %s con %d jugadores.\n", usuario[pos_min].ocupadas, min_ocupadas);

}

void sustiuirespacios(char texto[]) {
	int i = 0;

	while (texto[i]!='\0') {
		if (texto[i] == '_') {
			texto[i] = ' ';
		}
		i++;
	}
}