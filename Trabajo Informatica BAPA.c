#include <stdio.h>
#include <math.h>
#define N 5005

// Variables del trabajo conjuntas

struct info {
	int anio;
	int mes;
	int dia;
	char dia_semana;
	char hora_inicio;
	char hora_fin;
	char actividad_base;
	char modalidad;
	char centro;
	int plazas;
	int ocupadas;
	int libres;
	char tipo_actividad;
}



// Variables de Belen





//Variables de Alonso




//Variables de Pau





//Variables de Adolfo




int main() {
	int opcion;
	struct TEstudiante info[N];
	struct TEstudiante aux;
	struct TEstudiante e100[N] = {{50001, "5000000A", "Mario", "Lopez", 10.93}, {50002, "5000300A", "Maria", "Lopez", 11.93}, {50003, "5030000A", "Marta", "Lopez", 12.03}};
	int nestudiantes = 0;
	int i,j, matricula_buscada, encontrado = 0;
	float nota_max; // Mayor nota
	int pos_m; // Posicion del estudiante con la mayor nota
	float nota_corte;

	// Primer paso, leer los datos desde el fichero y volcarlo a la memoria (vector de estructuras de TEstudiante)


	FILE * fentrada;
	fentrada = fopen("deportes_ayuntamiento.txt","r");
	if (fentrada == NULL) {
		printf("Error abriendo el fichero \n");
		return 0;
	}
// Se puede hacer con la funcion feof (esta en el libro)

	while (fscanf(fentrada,"%d %s %s %s %f",&e100[i].nmatricula,e100[i].dni,e100[i].nombre,e100[i].apellidos,&e100[i].nota_acceso)!= EOF) {
		i++;
		nestudiantes++;
	}
	fclose(fentrada);
	do {
		printf(" ****** SECRETARIA ETSIDI ****** ");
		printf("Introduce una opcion:\n");
		printf("1. Imprimir lista de estudiantes\n");
		printf("2. Imprimir mejor expediente\n");
		printf("3. Imprimir ordenados de mayor a menor nota\n");
		printf("4. Buscar estudiante por numero de matricula\n");
		printf("5. Distribuir estudiantes por nota de corte\n");
		printf("9. Salir del programa\n");
		scanf("%d", &opcion);
		switch(opcion) {
			case 1:
				printf("Imprimiendo lista de estudiantes\n");
				for (i=0; i< nestudiantes; i++) {
					printf("%s %s %s %d %.2f\n", e100[i].nombre, e100[i].apellidos, e100[i].dni, e100[i].nmatricula, e100[i].nota_acceso);
				}
				break;
			case 2:
				printf("Imprimiendo mejor estudiante\n");

				nota_max = e100[0].nota_acceso;
				pos_m = 0;
				for (i=1; i<nestudiantes; i++) {
					if (e100[i].nota_acceso > nota_max) {
						nota_max = e100[i].nota_acceso;
						pos_m = i;
					}
				}
				printf("%s %s tiene la nota maxima = %.2f\n", e100[pos_m].nombre, e100[pos_m].apellidos, e100[pos_m].nota_acceso);
				break;
			case 3: //esta opcion trata de ordenar los alumnos de mayor a menor nota
				for (i=0; i<nestudiantes; i++) { //copio los estudiantes en un nuevo vector para no modificar el original, y ordeno el nuevo vector
					e100ordenados[i] = e100[i];
				}
				for (i=0; i<nestudiantes-1; i++) { //menos 1 porque el ultimo se da por hecho que tiene la menor nota de corte

					pos_m=i; //cada vez asumo que el primero que veo es el que mayor nota de corte q tiene porque es el primero que vuelvo a buscar

					for (j=i+1; j<nestudiantes; j++) { //aqui miro de toda la clase cual es el que mayor nota tiene

						if (e100ordenados[j].nota_acceso > e100ordenados[pos_m].nota_acceso){ //un bucle para ir comparando con el que mayor nota tiene hasta el momento
							pos_m = j;
						}
					}
					if (pos_m!= i) { // voy ordenando a los muchachos, pero me pregunto si el que tiene la nota mas alta ya esta en la posicion que quiero
						aux = e100ordenados[i];
						e100ordenados[i] = e100ordenados[pos_m];
						e100ordenados[pos_m] = aux;
					}
				}
				printf("----Lista de estudiantes por orden de nota de acceso creciente----\n \n ");

				for (i=0; i<nestudiantes; i++) {
					printf(" %.2f | %s %s %s \n",e100ordenados[i].nota_acceso,e100ordenados[i].nombre,e100ordenados[i].apellidos,e100ordenados[i].dni); //%.2f para mostrar los dos primeros decimales de la nota de corte que son los interesantes
				}
				break;
			case 4:
				printf("Introduce el numero de matricula\n");
				scanf("%d", &matricula_buscada);
				for (i=0; i<nestudiantes; i++) {
					if (matricula_buscada == e100[i].nmatricula) {
						printf("%s %s %s %d %.2f\n", e100[i].nombre, e100[i].apellidos, e100[i].dni, e100[i].nmatricula, e100[i].nota_acceso);
						encontrado = 1;
						break; // Es opcional, pero mas eficiente
					}
				}
				if (encontrado == 0) {
					printf("Estudiante no encontrado\n");
				}
				break;
			case 5:
				printf("Nota de corte:\n");
				scanf("%f", &nota_corte);
				printf("\n\nESTUDIANTES QUE ENTRAN AL GRADO:\n");
				for (i=0; i<nestudiantes; i++) {
					if (e100[i].nota_acceso >= nota_corte) {
						printf("%s %s %s %d %.2f\n", e100[i].nombre, e100[i].apellidos, e100[i].dni, e100[i].nmatricula, e100[i].nota_acceso);
					}
				}
				printf("\n\nESTUDIANTES EXCLUIDOS DEL GRADO:\n");
				for (i=0; i<nestudiantes; i++) {
					if (e100[i].nota_acceso < nota_corte) {
						printf("%s %s %s %d %.2f\n", e100[i].nombre, e100[i].apellidos, e100[i].dni, e100[i].nmatricula, e100[i].nota_acceso);
					}
				}
				break;
			case 9:
				printf("Calabaza calabaza cada quien a su casa.");
				break;
			default:
				printf("Opcion incorrecta, teclee otra opcion.");
		}
	}while (opcion!=9);
}