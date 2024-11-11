/*Incluimos las librerias*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Nuestras funciones creadas para usar aqui*/
#include "FuncionesPiaLab.h"

/* SE INCLUYE UNA VARIABLE GLOBAL DE ESTA PREVIA LIBRERIA*/
/* INT n;
    Va a guardar la cantidad total de registros.
    Es una variable GLOBAL.
    OJO AL USARLA*/

int main(){
    checarEnRecursos();
     /*Establecemos el idioma a español con las librerías locale.h y windows.h
    setLocale es para linux y SetConsole es para Windows. */
    setlocale(LC_ALL, "spanish");
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);
	
	mkdir("Datos");
	/*Se crea la carpeta donde se guarda la información*/
	int opc, i, numR, res;
	char dec;
	/*Apartamos 50 caracteres en memoria para buffer*/
	char *buffer = (char *)malloc(50 * sizeof(char));

	/*Si el archivo no existe, lo creamos y definimos la cantidad total de registros como 0*/
	if (!numPacientes()) {
		FILE *arch;
		if ((arch = fopen("Datos/RegistroPacientes.txt", "a")) == NULL) {
			printf("\n*Error al abrir el archivo*");
			return 0;
		}
		n = 0;
		fclose(arch);
	}

	while (1) {
		/*Limpiamos la consola e imprimimos el menu*/
		system("cls");
		menu();

		/*Solicitamos y validamos la opcion*/
		opc = minmaxInt("\nOpcion deseada: ", 1, 5);

		/*Si se elige la opcion 5, el programa termina*/
		if (opc == 5) break;

		/*Determinamos la accion a realizar mediante un switch*/
		switch (opc) {
			case 1:
				/*Damos de alta un paciente, si no hubo error se notifica el numero de registro asignado*/
				if (alta()) {
					printf("\n*Los datos del paciente fueron mostrados con exito.*");
					printf("\n*Al paciente se le asigno el numero de registro %d.*", n);
				}
				break;
			case 2:
				/*Solicitamos el nombre o numero de registro del paciente*/
				do {
					fgetc(stdin);
					printf("\nIngrese el nombre/numero de registro del paciente a buscar/editar: ");
					scanf("%[^\n]", buffer);
					/*Determinamos si se leyo un numero o un nombre*/
					numR = esNum(buffer);

					/*Si se dio un numero invalido, lo notificamos y lo solicitamos de nuevo*/
					if (numR == -1) {
						printf("\n*Error - Numero de registro invalido. Ingrese de nuevo.*");
					}
				} while (numR == -1);

				/*Si se leyo un nombre, buscamos el numero de registro asociado al nombre*/
				if (numR == 0) {
					/*Si no se encontro al paciente, se notifica*/
					if ((numR = buscarNombre(buffer)) == -1) {
						printf("\n*No se encontro al paciente %s.*", buffer);
						break;
					};
				}

				/*Si el registro esta activo se imprimen sus datos, si no, se notifica*/
				if (mostrarDatos(numR) == -1) {
					printf("\n*No se encontro al paciente %d.*", numR);
					break;
				}

				/*Preguntamos si el usuario desea editar algun dato del registro*/
				do {
					fgetc(stdin);
					printf("\nDesea editar algun dato? (S/N): ");
					scanf("%c", &dec);
					if (dec != 'S' && dec != 'N') printf("\n*Error - Caracter invalido. Ingrese de nuevo.*");
				} while (dec != 'S' && dec != 'N');

				/*Si no se desea editar nada, volvemos al menu principal*/
				if (dec == 'N') break;

				/*Imprimimos un menu con las opciones de edicion de datos*/
				printf("\nEn base al siguiente menu, elige la opcion a editar: ");
				menuEdicion();

				/*Solicitamos la opcion a editar y validamos que este en el menu*/
				opc = minmaxInt("\nOpcion deseada: ", 1, 7);

				/*Pedimos el nuevo dato y lo almacenamos en buffer*/
				solicitud_dato(opc, buffer);

				/*Le añadimos el caracter de fin de cadena*/
				strcat(buffer, "\n");

				/*Si el nuevo dato es exactamente igual al antiguo, se notifica*/
				if ((res = editar(opc, numR, buffer)) == -1) {
					printf("\n*No se realizo ningun cambio.*");
					break;
				}

				/*Si la edicion fue exitosa, se notifica*/
				if (res) printf("\n*La informacion del paciente fue actualizada con exito.*");
				break;
			case 3:
				/*Se muestran todos los registros activos, en caso de no haber ninguno activo se notifica*/
				if (mostrarTodos() == -1) printf("\n*No hay pacientes para mostrar.*");
				break;
			case 4:
				/*Solicitamos el nombre o numero de registro del paciente*/
				do {
					fgetc(stdin);
					printf("\nIngrese el nombre/numero de registro del paciente a dar de baja: ");
					scanf("%[^\n]", buffer);
					/*Determinamos si se leyo un numero o un nombre*/
					numR = esNum(buffer);

					/*Si se dio un numero invalido, lo notificamos y lo solicitamos de nuevo*/
					if (numR == -1) {
						printf("\n*Error - Numero de registro invalido. Ingrese de nuevo.*");
					}
				} while (numR == -1);

				/*Si se leyo un nombre, buscamos el numero de registro asociado al nombre*/
				if (numR == 0) {
					/*Si no se encontro al paciente, se notifica*/
					if ((numR = buscarNombre(buffer)) == -1) {
						printf("\n*No se encontro al paciente %s.*", buffer);
						break;
					};
				}

				/*Solicitamos una confirmacion para dar de baja al paciente*/
				do {
					fgetc(stdin);
					printf("\nEsta seguro que desea dar de baja al paciente %s? (S/N): ", buffer);
					scanf("%c", &dec);
					if (dec != 'S' && dec != 'N') printf("\n*Error - Caracter invalido. Ingrese de nuevo.*");
				} while (dec != 'S' && dec != 'N');

				/*Si no se desea dar de baja al paciente, regresamos al menu principal*/
				if (dec == 'N') break;

				/*Si el registro ya estaba dado de baja, lo notificamos*/
				if ((res = baja(numR)) == -1) {
					printf("\n*El paciente %s ya fue dado de baja anteriormente.*", buffer);
					break;
				}

				/*Si se dio de baja exitosamente, se notifica*/
				if (res) printf("\n*El paciente %s fue dado de baja con exito.*", buffer);
				break;
		}
		/*Pausamos el programa y solicitamos cualquier tecla para continuar*/
		printf("\n\n");
		system("PAUSE");
	}
	/*Liberamos la memoria de buffer*/
	free(buffer);

	/*Se notifica el fin del programa*/
	printf("\nPrograma terminado.\n\n");
	return 0;
}
