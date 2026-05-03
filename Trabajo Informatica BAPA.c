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

struct festivo {		//estructura del fichero de festivos (Belen)
	int anio;
	int mes;
	int dia;
	char dia_semana[40];
	char festividad[100];
	char tipo[50];
};

int leer_archivo(const char *nombre_archivo, struct info usuario[]);

//Funciones nombradas
//1

//2
void analizarOcupacionActividades(struct info usuario[], int total_registros); //emetealo
//3

//4
void analizarComparacionCentros(struct info usuario[], int total_registros);//emetealo
//5
void analizarDemanda(struct info usuario[], int total_registros);//Pau
//6
void analizarTiposActividades(struct info usuario[], int total_registros);//Pau




void sustituirespacios(char texto[]); //De clase, añadido por Adolfo
void ponerespacios(char texto[]); //De clase, añadido por Adolfo. Lo contrario al programa anterior por si queremos modificar datos en el fichero.

void comprobar_festivo(int d, int m, struct festivo lista[], int total); //Añadido por Belen






int main (){

	 static struct info usuario[N];

	//Aquí vamos poniendo las variables que necesitemos, id poniendo un comentario para saber cual es cual y todas las que declareis juntas.

	//Variables Miguel
	int i = 0; //Contador para los vectores con los datos weon
	int opcion; //Opcion elegida en el menú (AHORA TODO NÚMEROS)
	int total_registros=0;

	//Variables Belén

	//Variables Pau

	//Primero leemos el fichero y cargamos los datos en la memoria
	total_registros = leer_archivo("deportes_ayuntamiento.txt", usuario);

    if (total_registros == 0) {
        printf("No se pudieron cargar datos o el archivo esta vacio.\n");
    }

	do {
		system("cls");
		printf("\n ** PORTAL DE DEPORTES DE LA COMUNIDAD DE MADRID  ** \n");
		printf("Introduce una opcion:\n");
		printf("1. Ocupacion media por centro \n");
		printf("2. Ocupacion por actividad\n");
		printf("3. Ocupacion por franja de horario\n");
		printf("4. Comparacion de uso entre centros\n");
		printf("5. Actividades de alta y baja demanda\n");
		printf("6. Analisis tipos de actividades (Uso libre vs Dirigida)\n");
		printf("7. Comprobar disponibilidad\n");
		printf("0. Salir del programa.\n");
		printf("Opcion: ");
		scanf("%d", &opcion);


		switch(opcion) {
			case 1:
				system("cls");
				printf("\n--- Ocupacion media por centro ---\n");
				system("pause");
				break;

			case 2:
				system("cls");
				printf("\n--- Ocupacion por actividad ---\n");
				system("pause");
				break;

			case 3:
				system("cls");
				printf("\n--- Ocupacion por franja horaria ---\n");
				system("pause");
				break;

			case 4:
				system("cls");
				printf("\n--- Comparacion de uso entre centros ---\n");
				analizarComparacionCentros(usuario, total_registros);
				system("pause");
				break;

			case 5:
				system("cls");
				printf("\n--- Actividades de alta y baja demanda ---\n");
				analizarDemanda(usuario,total_registros);
				system("pause");
				break;

			case 6:
				system("cls");
				printf("\n--- Analisis tipos de actividades ---\n");
				// AQUÍ ES DONDE LLAMARÁS A TU FUNCIÓN ASÍ:
			    analizarTiposActividades(usuario, total_registros);
			    system("pause");
				break;

			case 7:
				printf("Seleccione dia que quiera realizar una actividad (Anio Mes Dia Dia_Semana):\n");
				// Leemos los datos del usuario[cite: 3]
				scanf("%d %d %d %s", &anio_buscado, &mes_buscado, &dia_buscado, dia_sem_buscado);

				// LLAMADA A LA FUNCIÓN
				comprobar_festivo(dia_buscado, mes_buscado, lista_festivos, total_festivos);

			case 0:
				system("cls");
				printf("\nSaliendo del programa, gracias por confiar en nosotros.\n");
				system("pause");
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
	char actividad_base[100];
	for (i;i<total_registros;i++){
		if (strcmp(usuario[i].tipo_actividad,"uso_libre")==0){
			contador_libre=contador_libre+1;
		}else{
			contador_dirigida=contador_dirigida+1;
		}
	}
	printf("Sesiones de Uso Libre: %d\n", contador_libre);
	printf("Sesiones de Actividad Dirigida: %d\n", contador_dirigida);

	printf("¿Que actividad quiere consultar?");
	scanf("%s",actividad_base);
	for (i=0;i<total_registros;i++){
		if(strcmp(usuario[i].actividad_base,actividad_base)==0){
			printf("La actividad %s es del tipo %s",actividad_base,usuario[i].tipo_actividad);
			break;
		}
	}

}

//Pau y Belen analizar demanda

void analizarDemanda(struct info usuario[], int total_registros){
    int i = 0;
    int max_ocupadas = usuario[0].ocupadas;
    int min_ocupadas = usuario[0].ocupadas;
    int pos_max = 0;
    int pos_min = 0;
    int sub_opcion;
    int repetida;
    char actividades_vistas[500][100];
    char actividad_base[100];
    int total_vistas = 0;
    festivo=0;

    printf("Seleccione dia que quiera realizar una actividad (Anio Mes Dia Dia_Semana):\n");
    scanf("%d %d %d %s", &anio_buscado, &mes_buscado, &dia_buscado, dia_sem_buscado);
    festivo=comprobar_festivo(dia_buscado, mes_buscado, lista_festivos, total_festivos);


    if(festivo!=1){
	    do {
	    	printf("%s %d %d %d",dia__sem_buscado, dia_buscado, mes_buscado, anio_buscado);
	        printf("\n--- ANALISIS DE DEMANDA DE ACTIVIDADES ---\n");
	        printf("1. Actividades con mas demanda\n");
	        printf("2. Buscador de plazas por actividad\n");
	        printf("3. Ver catalogo completo de actividades y sus plazas\n");
	        printf("0. Volver al menu principal\n");
	        printf("Elige una opcion: ");
	        scanf("%d", &sub_opcion);

	        switch(sub_opcion) {
	            case 1:
	                for (i = 0; i < total_registros; i++){
	                	if (usuario[i].dia == dia_buscado && usuario[i].mes == mes_buscado && usuario[i].anio == anio_buscado) {
		                    if(max_ocupadas < usuario[i].ocupadas){
		                        max_ocupadas = usuario[i].ocupadas;
		                        pos_max = i;
		                    }
		                    if(min_ocupadas > usuario[i].ocupadas){
		                        min_ocupadas = usuario[i].ocupadas;
		                        pos_min = i;
		                    }
		                }
	                }
	                printf("\nLa actividad mas popular es %s con %d plazas ocupadas.\n", usuario[pos_max].actividad_base, max_ocupadas);
	                printf("La actividad menos popular es %s con %d plazas ocupadas.\n", usuario[pos_min].actividad_base, min_ocupadas);
	                break;

	            case 2:
	                printf("\n¿Que actividad quiere consultar?: ");
	                scanf("%s", actividad_base);

	                int encontrada = 0;

	                for (i = 0; i < total_registros; i++) {
	                	if (usuario[i].dia == dia_buscado && usuario[i].mes == mes_buscado && usuario[i].anio == anio_buscado) {
		                    if (strcmp(usuario[i].actividad_base, actividad_base) == 0) {
		                        printf("La actividad %s tiene un total de %d plazas de las cuales, %d estan libres y %d estan ocupadas\n", actividad_base, usuario[i].plazas, usuario[i].libres, usuario[i].ocupadas);
		                        encontrada = 1;
		                        break;
		                    }
		                }
	                }

	                if (encontrada == 0) {
	                    printf("La actividad '%s' no se encuentra en la base de datos.\n", actividad_base);
	                }
	                break;

	            case 3:
	                printf("\n--- CATALOGO DE ACTIVIDADES POR DEMANDA ---\n");
	                printf("%-35s | %-20s\n", "ACTIVIDAD", "PLAZAS LIBRES");
	                printf("--------------------------------------------------------\n");

	                total_vistas = 0;

	                for (i = 0; i < total_registros; i++) {
	                    repetida = 0;

	                    for (int j = 0; j < total_vistas; j++) {
	                    	if (usuario[i].dia == dia_buscado && usuario[i].mes == mes_buscado && usuario[i].anio == anio_buscado) {
		                        if (strcmp(usuario[i].actividad_base, actividades_vistas[j]) == 0) {
		                            repetida = 1;
		                            break;
		                        }
		                    }
	                    }

	                    if (repetida == 0) {
	                        printf("%-35s | %-20d\n", usuario[i].actividad_base, usuario[i].libres);
	                        strcpy(actividades_vistas[total_vistas], usuario[i].actividad_base);
	                        total_vistas++;
	                    }
	                }
	                break;

	            case 0:
	                printf("\n----- Saliendo de la herramienta de analisis... -----\n");
	                break;

	            default:
	                printf("Opcion no valida. Intentalo de nuevo.\n");
	        } // Fin del switch

	    } while (sub_opcion != 0);
	}
}
int comprobar_festivo(int d, int m, struct festivo lista[], int dim) {
    int encontrado = 0;
	int j;
    for ( j = 0; j < dim; j++) {
        // Comparamos el día y el mes introducidos con la lista
        if (lista[j].dia == d && lista[j].mes == m) {
            printf("\nAVISO: El dia seleccionado es FESTIVO: %s (%s). NO SE REALIZAN ACTIVIDADES.\n",
                    lista[j].festividad, lista[j].tipo);
            encontrado = 1;
            break; // Si lo encuentra, deja de buscar
        }
    }

    if (encontrado!=1) {
        printf("\nEl dia seleccionado es un dia laborable.\n");

    }
    return encontrado;
}
// emtealo comparacion de ocupacion de centros

void analizarComparacionCentros(struct info usuario[], int total_registros)
{
    /* 1. Definicion de estructura local segun el Libro (Cap 4.4) */
    struct resumen
    {
        char nombre[100];
        int suma_plazas;
        int suma_ocupadas;
    };

    struct resumen listado[100]; /* Soporta hasta 100 centros distintos */
    int n_centros = 0;
    int i, j;
    float max_porcentaje = -1.0f;
    char centro_ganador[100] = "";

    /* --- FASE 1: AGREGACION (Procesamiento del archivo) --- */
    for (i = 0; i < total_registros; i++)
    {
        int encontrado = -1; /* Indica si el centro ya esta en el listado */

        /* Busqueda del centro actual en nuestro array de resumen (Cap 4.3.4.5) */
        for (j = 0; j < n_centros; j++)
        {
            if (strcmp(usuario[i].centro, listado[j].nombre) == 0)
            {
                encontrado = j;
                break;
            }
        }

        if (encontrado != -1)
        {
            /* Si ya existe, acumulamos los datos (Cap 2.5.6) */
            listado[encontrado].suma_plazas += usuario[i].plazas;
            listado[encontrado].suma_ocupadas += usuario[i].ocupadas;
        }
        else
        {
            /* Si es nuevo, lo registramos en la siguiente posicion libre */
            strcpy(listado[n_centros].nombre, usuario[i].centro);
            listado[n_centros].suma_plazas = usuario[i].plazas;
            listado[n_centros].suma_ocupadas = usuario[i].ocupadas;
            n_centros++;
        }
    }

    /* --- FASE 2: CALCULO Y SALIDA (Cap 7.2.1.1) --- */
    printf("\n======================================================\n");
    printf("   COMPARATIVA DE USO POR CENTRO DEPORTIVO\n");
    printf("======================================================\n");
    printf("%-35s | %-12s\n", "NOMBRE DEL CENTRO", "OCUPACION %");
    printf("------------------------------------------------------\n");

    for (i = 0; i < n_centros; i++)
    {
        if (listado[i].suma_plazas > 0)
        {
            /* Promocion automatica a float para precision (Cap 2.5.7) */
            float porcentaje = (listado[i].suma_ocupadas * 100.0f) / listado[i].suma_plazas;

            printf("%-35s | %10.2f%%\n", listado[i].nombre, porcentaje);

            /* Hallar el maximo (Logica de problemas resueltos Cap 8) */
            if (porcentaje > max_porcentaje)
            {
                max_porcentaje = porcentaje;
                strcpy(centro_ganador, listado[i].nombre);
            }
        }
    }

    /* --- FASE 3: RESULTADO FINAL --- */
    printf("------------------------------------------------------\n");
    if (n_centros > 0)
    {
        printf("CENTRO CON MAYOR DEMANDA:\n");
        printf(">> %s (%.2f%% de ocupacion).\n", centro_ganador, max_porcentaje);
    }
    printf("======================================================\n");
}


//EMETEALO Ocupacion de actividades
void analizarOcupacionActividades(struct info usuario[], int total_registros)
{
    /* 1. Estructura local para agrupar por deporte (Cap 4.4.1) */
    struct resumen_actividad
    {
        char nombre[100];
        int suma_plazas;
        int suma_ocupadas;
    };

    struct resumen_actividad lista_deportes[150]; /* Registramos deportes unicos */
    int n_deportes = 0;
    int i, j;

    /* --- FASE 1: AGREGACION POR ACTIVIDAD (Cap 3.3.2) --- */
    for (i = 0; i < total_registros; i++)
    {
        int encontrado = -1;

        /* Buscamos la actividad actual en nuestra lista auxiliar (Cap 4.3.4.5) */
        for (j = 0; j < n_deportes; j++)
        {
            /* IMPORTANTE: Ahora comparamos usuario[i].actividad_base */
            if (strcmp(usuario[i].actividad_base, lista_deportes[j].nombre) == 0)
            {
                encontrado = j;
                break;
            }
        }

        if (encontrado != -1)
        {
            /* Si ya la conocemos, sumamos plazas y ocupadas (Cap 2.5.6) */
            lista_deportes[encontrado].suma_plazas += usuario[i].plazas;
            lista_deportes[encontrado].suma_ocupadas += usuario[i].ocupadas;
        }
        else
        {
            /* Si es un deporte nuevo, lo registramos (Cap 4.3.4.3) */
            strcpy(lista_deportes[n_deportes].nombre, usuario[i].actividad_base);
            lista_deportes[n_deportes].suma_plazas = usuario[i].plazas;
            lista_deportes[n_deportes].suma_ocupadas = usuario[i].ocupadas;
            n_deportes++;
        }
    }

    /* --- FASE 2: CALCULO Y PRESENTACION (Cap 7.2.1.1) --- */
    printf("\n======================================================\n");
    printf("     ANALISIS DE OCUPACION POR ACTIVIDAD BASE\n");
    printf("======================================================\n");
    printf("%-35s | %-12s\n", "ACTIVIDAD DEPORTIVA", "OCUPACION %");
    printf("------------------------------------------------------\n");

    for (i = 0; i < n_deportes; i++)
    {
        if (lista_deportes[i].suma_plazas > 0)
        {
            /* Calculo con promocion a float para precision (Cap 2.5.7) */
            float porcentaje = (lista_deportes[i].suma_ocupadas * 100.0f) / lista_deportes[i].suma_plazas;

            /* Impresion con formato de tabla alineada */
            printf("%-35s | %10.2f%%\n", lista_deportes[i].nombre, porcentaje);
        }
    }
    printf("======================================================\n");
}



void sustituirespacios(char texto[]) {
	//De clase, añadido por Adolfo, para eliminar los guiones en los apellidos o en los nombres de los centros.
	int i = 0;

	while (texto[i]!='\0') {
		if (texto[i] == '_') {
			texto[i] = ' ';
		}
		i++;
	}
}

void ponerespacios(char texto[]) {
	//De clase, añadido por Adolfo, para poner espacios en los nombres para guardar datos en los ficheros por ejemplo, lo meto por si acaso
	int i = 0;

	while (texto[i]!='\0') {
		if (texto[i] == ' ') {
			texto[i] = '_';
		}
		i++;
	}
}


void comprobar_festivo(int d, int m, struct festivo lista[], int dim) {
	int encontrado = 0;
	int j;
	for ( j = 0; j < dim; j++) {
		// Comparamos el día y el mes introducidos con la lista
		if (lista[j].dia == d && lista[j].mes == m) {
			printf("\nAVISO: El dia seleccionado es FESTIVO: %s (%s)\n",
					lista[j].festividad, lista[j].tipo);
			encontrado = 1;
			break; // Si lo encuentra, deja de buscar
		}
	}

	if (encontrado!=1) {
		printf("\nEl dia seleccionado es un dia laborable.\n");

	}
}

