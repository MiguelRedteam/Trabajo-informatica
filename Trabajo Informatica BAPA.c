//Grupo 5 V9 17/05/2026 por adolfo

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h> //Librería para los acentos

#define N 5005
#define MAX_FESTIVOS 30

// Aqui declaramos el prototipo de las estructuras

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

struct festivo {
    int anio;
    int mes;               //estructura del fichero de festivos (Belen)
    int dia;
    char dia_semana[40];
    char festividad[100];
    char tipo[50];
};

struct login{
	char usuario [40];
	int contrasenia;
	char tipo_usuario[50];
};

int leer_archivo(const char *nombre_archivo, int tipo_archivo, struct info usuario[], struct festivo lista_festivos[]);

void analizarOcupacionActividades(struct info usuario[], int total_registros); //emetealo

void analizarComparacionCentros(struct info usuario[], int total_registros);//emetealo

void analizarDemanda(struct info usuario[], int total_registros, struct festivo lista_festivos[], int total_festivos);//Pau

void analizarTiposActividades(struct info usuario[], int total_registros);//Pau

void sustituirespacios(char texto[]); //De clase, añadido por Adolfo                                //Tenemos 15 funciones en total

void ponerespacios(char texto[]); //De clase, añadido por Adolfo.

int comprobar_festivo(int d, int m, struct festivo lista_festivo[], int total_festivos); //Añadido por Belen

void menuUsuario(struct info usuario[],int total_registros);//Pau funcion del menu Usuario

void AnalizarDemandaCentro(struct info usuario[],int total_registros,char centro_elegido[]);//Usuario demanda del centro elegido

void AnalizarActividadesCentro(struct info usuario[], int total_registros,char centro_elegido[]);//Usuario activdad por centro

void AnalizarHorariosCentro( struct info usuario[], int total_registros,char centro_elegido[] );

int cargarUsuarios(struct login lista[]);

void Lista_centros(struct info usuario[], int total_registros);

void actualizarbasedatos(struct info usuario[],struct festivo lista_festivos[], int *ptr_registros, int *ptr_festivos); //actualizar base de datos, añadido por adolfo

void Lista_actividades(struct info usuario[], int total_registros);

int main () {

	setlocale(LC_ALL, ""); // Para leer las ñ y acentos

    static struct info usuario[N];
    static struct festivo lista_festivos[MAX_FESTIVOS];



    int opcion;  //Opcion elegida en el menú
    int total_registros = 0;
    int total_festivos = 0;

    int anio_buscado, mes_buscado, dia_buscado;
    char dia_sem_buscado[40];

    int contrasenia_intro;
	char usuario_intro[50];
	struct login usuarios[100];
	int total = cargarUsuarios(usuarios);
	int i=0;
	int login_correcto=0;
	int indice_login= -1;		//se pone -1 para que coja una opcion negativa (nadie registrado), si pusieramos 0 cogeria la primera linea

    total_registros = leer_archivo("deportes_ayuntamiento.txt", 1, usuario, lista_festivos);

    // Leemos archivo  tipor 2 (Festivos)

    total_festivos = leer_archivo("festivos_madrid_2026_v2.txt", 2, usuario, lista_festivos);

    printf("Bienvenido a nuestro programa para facilitar ver las estadisticas de las actividades deportivas en Madrid.\n");
    system("pause");
    system("cls");
	printf("Elige una opción:\n");
	printf("[1] Ya tengo una cuenta. Iniciar sesión\n");
	printf("[2] No tengo una cuenta. Registrarme\n");
	scanf("%d",&opcion);

	switch (opcion){
		case 1:
			do {
                printf("Usuario: ");
                scanf("%s", usuario_intro);
                printf("Contraseña: ");
                scanf("%d", &contrasenia_intro);

                // ¿ existe ? 67
                for ( i = 0; i < total; i++) {
                    if (strcmp(usuario_intro, usuarios[i].usuario) == 0 && 		//Comparar caracter por caracter
                        contrasenia_intro == usuarios[i].contrasenia) {

                        login_correcto = 1;
                        indice_login = i;
                        printf("\nAcceso concedido. Bienvenido %s [%s]\n",
                                usuarios[i].usuario, usuarios[i].tipo_usuario);
                        break;
                    }
                }

                if (login_correcto == 0)
                    printf("Usuario o contraseña incorrectos. Intentalo de nuevo.\n");
            } while (login_correcto == 0);
            break;

		case 2:
			printf("Usuario:\n");
			scanf("%s",usuarios[total].usuario);
			printf("Contraseña:\n");
			scanf("%d",&usuarios[total].contrasenia);
			printf("Eres cliente o administrador?\n");
			scanf("%s",usuarios[total].tipo_usuario);

			//Editar archivo de usuarios y añadir el nuevo
			FILE *archivo = fopen("Usuario_Contrasenia.txt", "a");

            if (archivo == NULL) {
                printf("Error: No se pudo abrir el archivo.\n");
            } else {
                fprintf(archivo, "\n%s %d %s",
                        usuarios[total].usuario,
                        usuarios[total].contrasenia,
                        usuarios[total].tipo_usuario);

                fclose(archivo);
                printf("Usuario guardado correctamente.\n");
                total++; // Aumentamos el contador de usuarios en memoria
            }
            break;
	}

//Cliente

if (strcmp(usuarios[indice_login].tipo_usuario, "Cliente") == 0){
    do {
       system("cls");
       printf("\n ** PORTAL DE DEPORTES DE LA COMUNIDAD DE MADRID  ** \n");
       printf("Introduce una opción:\n");
       printf("1. Informacion Centros Deportivos \n");
       printf("2. Reservas\n");
       printf("3. Eventos especiales\n");
       printf("0. Salir del programa\n");
       printf("Opción: ");
       scanf("%d", &opcion);


       switch(opcion) {
          case 1:
             system("cls");
             menuUsuario(usuario,total_registros);
             system("pause");
             break;

          case 2:
             system("cls");
             printf("\n--- Reservas ---\n");
             //Funcion de reservvas
             system("pause");
             break;

          case 3:
             system("cls");
             printf("\n--- Eventos especiales ---\n");
             //funcion de eventos especiales
             system("pause");
             break;

          case 0:
             system("cls");
             printf("\nSaliendo del programa, gracias por confiar en nosotros.\n");
             system("pause");
             break;

          default:
             printf("\nOpción incorrecta, teclee otra opción o escriba '0' para salir del programa.\n");
             system("pause");
       }
    } while (opcion != 0);


//Administrador
} else if (strcmp(usuarios[indice_login].tipo_usuario, "Administrador") == 0) {
    do {
        system("cls");
        printf("\n--- MENU ADMINISTRADOR ---\n");
        printf("1. Comparar uso de polideportivos\n");
        printf("2. Ver ocupación de actividades\n");
        printf("3. Balance uso libre vs dirigido\n");
        printf("4. Analizar demanda por fecha\n");
        printf("5. Actualizar base de datos\n");
        printf("0. Salir del programa\n");
        printf("Opción: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                system("cls");
                analizarComparacionCentros(usuario, total_registros);
                system("pause");
                break;

            case 2:
                system("cls");

                analizarOcupacionActividades(usuario, total_registros);
                system("pause");
                break;

            case 3:
                system("cls");
                analizarTiposActividades(usuario, total_registros);
                system("pause");
                break;

            case 4:
                system("cls");
                analizarDemanda(usuario, total_registros, lista_festivos, total_festivos);
                system("pause");
                break;

            case 5:
            system("cls");
                actualizarbasedatos(usuario,lista_festivos,&total_registros,&total_festivos);
                system("pause");
                break;

            case 0:
                printf("\nSaliendo del menu de administrador...\n");
                break;

            default:
                printf("\nOpción incorrecta. Intentalo de nuevo.\n");
                system("pause");
        }
    } while (opcion != 0);
}

    return 0;
}

void menuUsuario(struct info usuario[], int total_registros) {
    char centro_elegido[100];
    int opcion_centro;
    int opcion_actividades;
    int i, j;

    do {
        printf("\nEscriba el nombre del Centro Deportivo a consultar.\n");
        printf("(Escriba 'LISTA' para ver los centros disponibles o 'SALIR' para volver al inicio): ");
        scanf(" %[^\n]", centro_elegido);

        if (strcmp(centro_elegido, "Salir") == 0 || strcmp(centro_elegido, "SALIR") == 0) {
            printf("\nVolviendo al menu principal...\n");
            break; // Rompe el bucle y termina la función
        }

       if (strcmp(centro_elegido, "LISTA") == 0) {
	            Lista_centros( usuario, total_registros);
	            continue;
	        }
	    system("pause");

        // El usuario escribe el centro (entramos al submenú)
        system("cls");
        do {
            printf("\n--- GESTIONANDO CENTRO: %s ---\n", centro_elegido);
            printf("1. Ver demanda general del centro\n");
            printf("2. Ver información de horarios\n");
            printf("3. Ver actividades ofertadas\n");
            printf("0. Volver a la selección de centro\n");
            printf("Elige una opción: ");
            scanf("%d", &opcion_centro);

            switch(opcion_centro) {
                case 1:
                	system("cls");
                    printf("\nCalculando demanda del centro %s...\n", centro_elegido);
                        AnalizarDemandaCentro(usuario,total_registros,centro_elegido);;
                    break;

                case 2:
                	system("cls");
                    printf("\nBuscando horarios del centro %s...\n", centro_elegido);
                        AnalizarHorariosCentro(usuario,total_registros,centro_elegido);
                    break;

                case 3:
                	system("cls");
                        printf("\n--- ACTIVIDADES EN %s ---\n", centro_elegido);
                        AnalizarActividadesCentro(usuario,total_registros,centro_elegido);
                    break;

                case 0:
                	system("cls");
                    printf("\nSaliendo del centro %s...\n", centro_elegido);
                    break;

                default:
                    printf("Opción no valida.\n");
            }
        } while (opcion_centro != 0);

    } while (1); // Bucle infinito que solo se rompe si escribe "SALIR"
}


//Case 1 Analizar Demanda centros
void AnalizarDemandaCentro(struct info usuario[],int total_registros,char centro_elegido[]){
    int i = 0;
    int suma_ocupadas = 0;
    int suma_libres = 0;
    int centro_encontrado = 0;
    printf("\n La demanda del centro %s  ---\n", centro_elegido);

    for (i=0; i<total_registros; i++){

       if (strcmp(usuario[i].centro,centro_elegido)==0){
            suma_ocupadas = suma_ocupadas + usuario[i].ocupadas;
            suma_libres = suma_libres + usuario[i].libres;
            centro_encontrado=1;
       }
    }
    if (centro_encontrado == 1) {
        printf("Total de plazas OCUPADAS en el centro: %d\n", suma_ocupadas);
        printf("Total de plazas LIBRES en el centro: %d\n", suma_libres);
        printf("Porcentaje de ocupación %d %% \n", (suma_ocupadas*100)/(suma_libres+suma_ocupadas) );
    } else {
        printf("No se han encontrado registros de actividades para el centro '%s'.\n", centro_elegido);
    }
}
//Case 2: Info horarios actividad por centro
void AnalizarHorariosCentro(struct info usuario[], int total_registros, char centro_elegido[]) {
    char actividad_buscada[100];
    int i, j;
    int horario_encontrado;


    char actividades_vistas[500][100];
    int total_vistas = 0;
    int repetida;
    int centro_encontrado = 0;

    printf("\n--- CONSULTA DE HORARIOS: %s ---\n", centro_elegido);
    printf("Actividades disponibles en este centro:\n");
    printf("--------------------------------------------------\n");


    for (i = 0; i < total_registros; i++) {

        if (strcmp(usuario[i].centro, centro_elegido) == 0) {
            centro_encontrado = 1;
            repetida = 0;

            // Comprobamos si ya la hemos impreso
            for (j = 0; j < total_vistas; j++) {
                if (strcmp(usuario[i].actividad_base, actividades_vistas[j]) == 0) {
                    repetida = 1;
                    break;
                }
            }

            // Si es nueva, la imprimimos y la apuntamos
            if (repetida == 0) {
                printf("- %s\n", usuario[i].actividad_base);
                strcpy(actividades_vistas[total_vistas], usuario[i].actividad_base);
                total_vistas++;
            }
        }
    }

    // Si el polideportivo no tiene actividades registradas, salimos directamente
    if (centro_encontrado == 0) {
        printf("No hay actividades registradas en este centro.\n");
        return;
    }

    //EL BUSCADOR DE HORARIOS ---
    do {
        printf("\n¿De qué actividad quieres consultar el horario?\n");
        printf("(Escribe el nombre tal como aparece arriba o 'SALIR' para volver): ");
        scanf(" %[^\n]", actividad_buscada);

        if (strcmp(actividad_buscada, "SALIR") == 0 || strcmp(actividad_buscada, "Salir") == 0) {
            printf("\nVolviendo al menu del centro...\n");
            break;
        }

        horario_encontrado = 0;

        printf("\n>> HORARIOS DE %s EN %s <<\n", actividad_buscada, centro_elegido);

        for (i = 0; i < total_registros; i++) {
            // Doble filtro: Centro correcto y actividad correcta
            if (strcmp(usuario[i].centro, centro_elegido) == 0 && strcmp(usuario[i].actividad_base, actividad_buscada) == 0) {
                // Imprimimos 6 huecos: 2 números (%d) y 4 textos (%s)
printf("* Fecha %02d/%02d - %s: de %s a %s (%s)\n",
       usuario[i].dia,
       usuario[i].mes,
       usuario[i].dia_semana,
       usuario[i].hora_inicio,
       usuario[i].hora_fin,
       usuario[i].tipo_actividad);
                horario_encontrado = 1;
            }
        }

        if (horario_encontrado == 0) {
            printf("Error: No se han encontrado horarios para '%s'. Asegurate de escribirlo igual que en la lista.\n", actividad_buscada);
        }

    } while (1);
}


//Case 3 Analizar Actividades por centro
void AnalizarActividadesCentro(struct info usuario[], int total_registros, char centro_elegido[]) {
    int i, j;
    int centro_encontrado = 0;

    // Nuestra "libreta" ahora tiene 3 columnas: Nombre, Tipo y Plazas Acumuladas
    char actividades_vistas[500][100];
    char tipos_vistos[500][100];
    int plazas_acumuladas[500] = {0}; // Inicializamos a 0
    int total_vistas = 0;

    //RECOPILAR Y SUMAR DATOS
    for (i = 0; i < total_registros; i++) {
        // Solo miramos las fichas de este centro
        if (strcmp(usuario[i].centro, centro_elegido) == 0) {
            centro_encontrado = 1;
            int posicion_en_libreta = -1; // Chivato para saber en qué renglón está

            // Buscamos si ya habíamos apuntado esta actividad
            for (j = 0; j < total_vistas; j++) {
                if (strcmp(usuario[i].actividad_base, actividades_vistas[j]) == 0) {
                    posicion_en_libreta = j; // ¡La encontramos en el renglón 'j'!
                    break;
                }
            }

            if (posicion_en_libreta != -1) {
                // YA EXISTE: Le sumamos las plazas de esta nueva sesión al total
                plazas_acumuladas[posicion_en_libreta] = plazas_acumuladas[posicion_en_libreta] + usuario[i].plazas;
            } else {
                // ES NUEVA: La apuntamos en un renglón nuevo
                strcpy(actividades_vistas[total_vistas], usuario[i].actividad_base);
                strcpy(tipos_vistos[total_vistas], usuario[i].tipo_actividad);
                plazas_acumuladas[total_vistas] = usuario[i].plazas;
                total_vistas++; // Pasamos al siguiente renglón en blanco
            }
        }
    }

    if (centro_encontrado == 0) {
        printf("No hay actividades registradas en este centro.\n");
        return;
    }

    //PRIMIR LA TABLA LIMPIA
    printf("\n--- CATALOGO RESUMIDO DE ACTIVIDADES: %s ---\n", centro_elegido);
    printf("%-30s | %-20s | %-15s\n", "ACTIVIDAD", "TIPO DE USO", "PLAZAS TOTALES");
    printf("-----------------------------------------------------------------------\n");

    // Ahora solo imprimimos nuestra libreta, que ya tiene todo sumado y sin repetir
    for (j = 0; j < total_vistas; j++) {
        printf("%-30s | %-20s | %-15d\n", actividades_vistas[j], tipos_vistos[j], plazas_acumuladas[j]);
    }

    // --- PARTE 3: EL BUSCADOR INTEGRADO ---
    char actividad_buscada[100];
    do {
        printf("\n¿Deseas ver la demanda detallada de alguna actividad?\n");
        printf("(Escriba 'LISTA' para ver las actividades disponibles o 'SALIR' para volver al inicio): ");
		scanf(" %[^\n]", actividad_buscada);

	    if (strcmp(actividad_buscada, "LISTA") == 0) {
		    Lista_actividades( usuario, total_registros);
		}

        if (strcmp(actividad_buscada, "SALIR") == 0 || strcmp(actividad_buscada, "Salir") == 0) {
            printf("\nCerrando catalogo...\n");
            break;
        }

        int act_encontrada = 0;
        int suma_ocupadas = 0;
        int suma_libres = 0;

        // Buscamos todas las sesiones de esa actividad en ese centro y las sumamos
        for (i = 0; i < total_registros; i++) {
            if (strcmp(usuario[i].centro, centro_elegido) == 0 && strcmp(usuario[i].actividad_base, actividad_buscada) == 0) {
                suma_ocupadas = suma_ocupadas + usuario[i].ocupadas;
                suma_libres = suma_libres + usuario[i].libres;
                act_encontrada = 1;
            }
        }

        if (act_encontrada == 1) {
            printf("\n>> BALANCE TOTAL SEMANAL PARA: %s <<\n", actividad_buscada);
            printf("Plazas Ocupadas: %d\n", suma_ocupadas);
            printf("Plazas Libres:   %d\n", suma_libres);
        } else {
            printf("Error: La actividad '%s' no se oferta en este centro.\n", actividad_buscada);
        }

    } while (1);
}

// Lector de Archivos Universal

int leer_archivo(const char *nombre_archivo, int tipo_archivo, struct info usuario[], struct festivo lista_festivos[]) {
    FILE *archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo %s\n", nombre_archivo);

        return 0;
    }

    char cabecera[N];
    fgets(cabecera, N, archivo); // Saltar la primera línea

    int i = 0;

    //Un if para cada tipo de archivo, esto lo hacemos asi porque cada archivo tiene una serie de datos que se tiene que leer y almacenar de manera distinta
    if (tipo_archivo == 1) {
        while (i < N && fscanf(archivo, "%d %d %d %s %s %s %s %s %s %d %d %d %s",
           &usuario[i].anio,
           &usuario[i].mes,
           &usuario[i].dia,
           usuario[i].dia_semana,
           usuario[i].hora_inicio,
           usuario[i].hora_fin,             //Lo pongo asi porque es mas facil copiar los datos que necesitemos en algun otro lado
           usuario[i].actividad_base,
           usuario[i].modalidad,
           usuario[i].centro,
           &usuario[i].plazas,
           &usuario[i].ocupadas,
           &usuario[i].libres,
           usuario[i].tipo_actividad)

           != EOF) {
            i++;
        }
    }

    else if (tipo_archivo == 2) {
        while (i < MAX_FESTIVOS && fscanf(archivo, "%d %d %d %s %s %s",
           &lista_festivos[i].anio,
           &lista_festivos[i].mes,
           &lista_festivos[i].dia,
           lista_festivos[i].dia_semana,
           lista_festivos[i].festividad,
           lista_festivos[i].tipo)

           != EOF) {
            i++;
        }
    }

    fclose(archivo);
    return i;
}

// Pau: Analizar actividades dirigidas y libres

void analizarTiposActividades(struct info usuario[], int total_registros){
    int i=0;
    int contador_libre=0;
    int contador_dirigida=0;
    char actividad_base[100];
    char actividad_elegida[100];
    for (i=0; i<total_registros; i++){
       if (strcmp(usuario[i].tipo_actividad,"uso_libre")==0){
          contador_libre=contador_libre+1;
       }else{
          contador_dirigida=contador_dirigida+1;
       }
    }
    printf("Sesiones de Uso Libre: %d\n", contador_libre);
    printf("Sesiones de Actividad Dirigida: %d\n", contador_dirigida);

    printf("¿Que actividad quiere consultar? ");
    printf("(Escriba 'LISTA' para ver las actividades disponibles o 'SALIR' para volver al inicio): ");
	scanf(" %[^\n]", actividad_elegida);

    if (strcmp(actividad_elegida, "Salir") == 0 || strcmp(actividad_elegida, "SALIR") == 0) {
		printf("\nVolviendo al menu principal...\n");
    }

    if (strcmp(actividad_elegida, "LISTA") == 0) {
	    Lista_actividades( usuario, total_registros);
	}
    for (i=0; i<total_registros; i++){
       if(strcmp(usuario[i].actividad_base,actividad_base)==0){
          printf("La actividad %s es del tipo %s\n",actividad_elegida,usuario[i].tipo_actividad);
          break;
       }
    }
}

// Pau y Belen: Analizar demanda
// Actualizada para recibir los festivos
void analizarDemanda(struct info usuario[], int total_registros, struct festivo lista_festivos[], int total_festivos){
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
    int anio_buscado, mes_buscado, dia_buscado;
    char dia_sem_buscado[40];
    int festivo = 0;
    int j;
    int encontrada = 0;

    printf("Seleccione día que quiera realizar una actividad (Anio Mes Día Día_Semana):\n");
    scanf("%d %d %d %s", &anio_buscado, &mes_buscado, &dia_buscado, dia_sem_buscado);

    // ¡ARREGLADO!: Le quitamos los corchetes vacíos a lista_festivos
    festivo = comprobar_festivo(dia_buscado, mes_buscado, lista_festivos, total_festivos);

    if(festivo != 1){
        do {
            printf("\n%s %d/%d/%d\n", dia_sem_buscado, dia_buscado, mes_buscado, anio_buscado);
            printf("--- ANALISIS DE DEMANDA DE ACTIVIDADES ---\n");
            printf("1. Actividades con mas demanda\n");
            printf("2. Buscador de plazas por actividad\n");
            printf("3. Ver catalogo completo de actividades y sus plazas\n");
            printf("0. Volver al menú principal\n");
            printf("Elige una opción: ");
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
                    printf("\n¿Qué actividad quiere consultar?: ");
                    printf("(Escriba 'LISTA' para ver las actividades disponibles o 'SALIR' para volver al inicio): ");
					scanf(" %[^\n]", actividad_base);

				    if (strcmp(actividad_base, "Salir") == 0 || strcmp(actividad_base, "SALIR") == 0) {
						printf("\nVolviendo al menu principal...\n");
				    }

				    if (strcmp(actividad_base, "LISTA") == 0) {
					    Lista_actividades( usuario, total_registros);
					}

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
                        printf("La actividad '%s' no se encuentra en la base de datos para ese dia.\n", actividad_base);
                    }
                    break;

                case 3:
                    printf("\n--- CATALOGO DE ACTIVIDADES POR DEMANDA ---\n");
                    printf("%-35s | %-20s\n", "ACTIVIDAD", "PLAZAS LIBRES");
                    printf("--------------------------------------------------------\n");
                    total_vistas = 0;
                    for (i = 0; i < total_registros; i++) {
                        repetida = 0;
                        for ( j = 0; j < total_vistas; j++) {
                           if (usuario[i].dia == dia_buscado && usuario[i].mes == mes_buscado && usuario[i].anio == anio_buscado) {
                               if (strcmp(usuario[i].actividad_base, actividades_vistas[j]) == 0) {
                                   repetida = 1;
                                   break;
                               }
                           }
                        }
                        if (repetida == 0 && usuario[i].dia == dia_buscado && usuario[i].mes == mes_buscado && usuario[i].anio == anio_buscado) {
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
                    printf("Opción no valida. Intentalo de nuevo.\n");
            }
        } while (sub_opcion != 0);
    }
}

int comprobar_festivo(int d, int m, struct festivo lista[], int dim) {
    int encontrado = 0;
    int j;
    for ( j = 0; j < dim; j++) {
        if (lista[j].dia == d && lista[j].mes == m) {
            printf("\nAVISO: El día seleccionado es FESTIVO: %s (%s). NO SE REALIZAN ACTIVIDADES.\n",
                    lista[j].festividad, lista[j].tipo);
            encontrado = 1;
            break;
        }
    }
    if (encontrado != 1) {
        printf("\nEl día seleccionado es un día laborable.\n");
    }
    return encontrado;
}

// emtealo comparacion de ocupacion de centros
void analizarComparacionCentros(struct info usuario[], int total_registros){
    struct resumen {
        char nombre[100];
        int suma_plazas;
        int suma_ocupadas;
    };

    struct resumen listado[100];
    int n_centros = 0;
    int i, j;
    float max_porcentaje = -1.0f;
    char centro_ganador[100] = "";

    for (i = 0; i < total_registros; i++) {
        int encontrado = -1;
        for (j = 0; j < n_centros; j++) {
            if (strcmp(usuario[i].centro, listado[j].nombre) == 0) {
                encontrado = j;
                break;
            }
        }
        if (encontrado != -1) {
            listado[encontrado].suma_plazas += usuario[i].plazas;
            listado[encontrado].suma_ocupadas += usuario[i].ocupadas;
        } else {
            strcpy(listado[n_centros].nombre, usuario[i].centro);
            listado[n_centros].suma_plazas = usuario[i].plazas;
            listado[n_centros].suma_ocupadas = usuario[i].ocupadas;
            n_centros++;
        }
    }

    printf("\n======================================================\n");
    printf("   COMPARATIVA DE USO POR CENTRO DEPORTIVO\n");
    printf("======================================================\n");
    printf("%-35s | %-12s\n", "NOMBRE DEL CENTRO", "OCUPACIÓN %");
    printf("------------------------------------------------------\n");

    for (i = 0; i < n_centros; i++) {
        if (listado[i].suma_plazas > 0) {
            float porcentaje = (listado[i].suma_ocupadas * 100.0f) / listado[i].suma_plazas;
            printf("%-35s | %10.2f%%\n", listado[i].nombre, porcentaje);

            if (porcentaje > max_porcentaje) {
                max_porcentaje = porcentaje;
                strcpy(centro_ganador, listado[i].nombre);
            }
        }
    }

    printf("------------------------------------------------------\n");
    if (n_centros > 0) {
        printf("CENTRO CON MAYOR DEMANDA:\n");
        printf(">> %s (%.2f%% de ocupación).\n", centro_ganador, max_porcentaje);
    }
    printf("======================================================\n");
}

//EMETEALO Ocupacion de actividades
void analizarOcupacionActividades(struct info usuario[], int total_registros){
    struct resumen_actividad {
        char nombre[100];
        int suma_plazas;
        int suma_ocupadas;
    };

    struct resumen_actividad lista_deportes[150];
    int n_deportes = 0;
    int i, j;

    for (i = 0; i < total_registros; i++) {
        int encontrado = -1;
        for (j = 0; j < n_deportes; j++) {
            if (strcmp(usuario[i].actividad_base, lista_deportes[j].nombre) == 0) {
                encontrado = j;
                break;
            }
        }

        if (encontrado != -1) {
            lista_deportes[encontrado].suma_plazas += usuario[i].plazas;
            lista_deportes[encontrado].suma_ocupadas += usuario[i].ocupadas;
        } else {
            strcpy(lista_deportes[n_deportes].nombre, usuario[i].actividad_base);
            lista_deportes[n_deportes].suma_plazas = usuario[i].plazas;
            lista_deportes[n_deportes].suma_ocupadas = usuario[i].ocupadas;
            n_deportes++;
        }
    }

    printf("\n======================================================\n");
    printf("     ANALISIS DE OCUPACIÓN POR ACTIVIDAD BASE\n");
    printf("======================================================\n");
    printf("%-35s | %-12s\n", "ACTIVIDAD DEPORTIVA", "OCUPACIÓN %");
    printf("------------------------------------------------------\n");

    for (i = 0; i < n_deportes; i++) {
        if (lista_deportes[i].suma_plazas > 0) {
            float porcentaje = (lista_deportes[i].suma_ocupadas * 100.0f) / lista_deportes[i].suma_plazas;
            printf("%-35s | %10.2f%%\n", lista_deportes[i].nombre, porcentaje);
        }
    }
    printf("======================================================\n");
}

void sustituirespacios(char texto[]) {
    int i = 0;
    while (texto[i]!='\0') {
       if (texto[i] == '_') {
          texto[i] = ' ';
       }
       i++;
    }
}

void ponerespacios(char texto[]) {
    int i = 0;
    while (texto[i]!='\0') {
       if (texto[i] == ' ') {
          texto[i] = '_';
       }
       i++;
    }
}

int cargarUsuarios(struct login lista[]) {
    FILE *archivo = fopen("Usuario_Contrasenia.txt", "r");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo.\n");
        return 0;
    }

    char cabecera[100];
    // Saltamos la línea primera linea
    fgets(cabecera, sizeof(cabecera), archivo);

    int i = 0;
    while (fscanf(archivo, "%s %d %s", lista[i].usuario, &lista[i].contrasenia, lista[i].tipo_usuario) == 3) {
    	i++;
	}

    fclose(archivo);
    return i;
}

void Lista_actividades(struct info usuario[], int total_registros){
		char actividades_vistas[500][100];
        int total_actividades = 0;
        int repetido;
		int i=0, j=0;
      	 printf("\n--- ACTIVIDADES DISPONIBLES ---\n");

        for (i = 0; i < total_registros; i++) {
            repetido = 0;
            for (j = 0; j < total_registros; j++) {
                if (strcmp(usuario[i].actividad_base, actividades_vistas[j]) == 0) {
                    repetido = 1;
                    break;
                }
            }
        	if (repetido == 0) {
                printf("- %s\n", usuario[i].actividad_base);
                if (total_actividades < 500) {		//Por si hay mas de 500 actividades
                	strcpy(actividades_vistas[total_actividades], usuario[i].actividad_base);
                	total_actividades++;
            	}

            }
        }
        system("pause");
}

void Lista_centros(struct info usuario[], int total_registros){
		char centros_vistos[500][100];
        int total_centros = 0;
        int repetido;
		int i=0, j=0;
      	 printf("\n--- CENTROS DEPORTIVOS DISPONIBLES ---\n");

        for (i = 0; i < total_registros; i++) {
            repetido = 0;
            for (j = 0; j < total_centros; j++) {
                if (strcmp(usuario[i].centro, centros_vistos[j]) == 0) {
                    repetido = 1;
                    break;
                }
            }
        	if (repetido == 0) {
        	    // creo una cadena nueva para poner en limpio los nombres temporalmente y asi no tener que modificar el archivo original

        	    char nombrelimpio[400];

        	    //copio la cadena con los guiones en la cadena limpia

        	    strcpy(nombrelimpio, usuario[i].centro);

        	    //aplicamos la funcion en la cadena temporal limpia para no modificar el archivo original

        	    sustituirespacios(nombrelimpio);

                printf("- %s\n", nombrelimpio); //Cambio aqui el usuario[i].centro por el nombre limpio sin guiones
                if (total_centros < 500) {		//Por si hay mas de 500 centros
                	strcpy(centros_vistos[total_centros], usuario[i].centro);
                	total_centros++;
            	}

            }
        }
        system("pause");
}

void actualizarbasedatos(struct info usuario[],struct festivo lista_festivos[], int *ptr_registros, int *ptr_festivos) {


    char nombre_archivo_datos[100];
    char nombre_archivo_festivos[100];


    printf("Para que nuestro programa funcione, por favor indicanos el archivo donde leer los datos.\n");
    system("pause");
    system("cls");

    printf("Escribe el nombre del archivo de DATOS (ej. deportes.txt): ");

    scanf(" %[^\n]", nombre_archivo_datos);
    system("pause");
    system("cls");

    printf("\nEscribe el nombre del archivo de FESTIVOS (ej. festivos.txt): \n");
    scanf(" %[^\n]", nombre_archivo_festivos);

    *ptr_registros = leer_archivo(nombre_archivo_datos, 1, usuario, lista_festivos);
    *ptr_festivos = leer_archivo(nombre_archivo_festivos, 2, usuario, lista_festivos);

    // Leemos archivo  tipor 1 (Actividades)

    if (*ptr_registros == 0 && *ptr_festivos == 0) {
        printf("\nADVERTENCIA: No se pudieron cargar datos o los archivos estan vacios.\n");
        system("pause");
    } else {
        printf("\nExito: Se cargaron %d actividades y %d dias festivos.\n", *ptr_registros, *ptr_festivos);
        system("pause");
    }

}