/*Incluimos las librerias*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

/*Nuestras funciones creadas para usar aqui*/
#include "FuncionesPiaLab.c"

/* SE INCLUYE UNA VARIABLE GLOBAL DE ESTA PREVIA LIBRERIA*/
/* INT n;
    Va a guardar la cantidad total de registros.
    Es una variable GLOBAL.
    OJO AL USARLA*/

int main(){
    /*Ayuda a que se guarden los datos donde deben
    si se está ejecutando desde el código en C por CodeBlocks.*/
    checarEnRecursos();
    /*Establecemos el idioma a español con las librerías y windows.h
    SetConsole es para Windows. Locale funciona para todos los ordenadores */
    setlocale(LC_ALL, "es_ES.UTF-8");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

	mkdir("Datos");
	/*Se crea la carpeta donde se guarda la información*/

	int opc, numR, res;
	char dec;
	/*Apartamos 50 caracteres en memoria para buffer*/
	char *buffer = (char *)malloc(50 * sizeof(char));

	/*Si el archivo no existe, lo creamos y definimos la cantidad total de registros como 0*/
	if (!numPacientes()) {
		FILE *arch;
		if ((arch = fopen("Datos/RegistroPacientes.txt", "a")) == NULL) {
			printf("\n*Error al abrir el archivo*\n");
			/*LIBERANDO LA MEMORIA PORQUE SE VA A CERRAR EL PROGRAMA*/
			free(buffer);
			system("PAUSE");
			return 0;
		}
		n = 0;
		fclose(arch);
	}

	while(1){
		/*Limpiamos la consola e imprimimos el menu*/
		system("cls");
		menu();

		/*Solicitamos y validamos la opcion*/
		do{
			printf("\nOpción deseada: ");
			opc=validar_num();
			if(opc<1||opc>5) printf("*Error - Opción inválida.*");
		}while(opc<1||opc>5);

		/*Si se elige la opcion 5, el programa termina*/
		if(opc == 5) break;

		if(!n&&(opc == 2||opc == 4)){
			printf("\n*No hay pacientes registrados en este momento.*");
			printf("\n\n");
			system("PAUSE");
			continue;
		}

		/*Determinamos la accion a realizar mediante u switch*/
		switch(opc){
			case 1:
				/*Damos de alta un paciente, si no hubo error se notifica el numero de registro asignado*/
				if(alta()) {
					printf("\n*Los datos del paciente fueron guardados con éxito.*");
					printf("\n*Al paciente se le asignó el número de registro %d.*",n);
				}
				break;
			case 2:
				/*Solicitamos el nombre o numero de registro del paciente*/
				do{
					fflush(stdin);
					printf("\nIngrese el nombre/número de registro del paciente a buscar/editar: ");
					scanf("%49[^\n]",buffer);
					/*Determinamos si se leyo un numero o un nombre*/
					numR = esNum(buffer);

					/*Si se dio un numero invalido, lo notificamos y lo solicitamos de nuevo*/
					if(numR == -1) {
						printf("\n*Error - Número de registro inválido. Ingrese de nuevo.*");
					}
				}while(numR == -1);

				/*Si se leyo un nombre, buscamos el numero de registro asociado al nombre*/
				if(numR == 0){
					/*Si no se encontro al paciente, se notifica*/
					if((numR = buscarNombre(buffer)) == -1){
						printf("\n*No se encontró al paciente '%s'.*",buffer);
						break;
					};
				}

				/*Si el registro esta activo se imprimen sus datos, si no, se notifica*/
				if(mostrarDatos(numR) == -1){
					printf("\n*No se encontró al paciente %d.*",numR);
					break;
				}

				/*Preguntamos si el usuario desea editar algun dato del registro*/
				do{
					fflush(stdin);
					printf("\nDesea editar algún dato? (S/N): ");
					scanf("%c",&dec);
					if(dec != 'S' && dec != 'N' && dec!= 's' && dec!= 'n') printf("\n*Error - Caracter inválido. Ingrese de nuevo.*");
				}while(dec != 'S' && dec != 'N' && dec!= 's' && dec!= 'n');

				/*Si no se desea editar nada, volvemos al menu principal*/
				if(dec == 'N' || dec=='n') break;

				/*Imprimimos un menu con las opciones de edicion de datos*/
				printf("\nEn base al siguiente menú, elige la opción a editar: ");
				menuEdicion();

				/*Solicitamos la opcion a editar y validamos que este en el menu*/
				do{
					printf("\nOpción deseada: ");
					opc=validar_num();
					if(opc<1||opc>7) printf("\n*Error - Opción inválida. Ingrese de nuevo.*");
				}while(opc<1||opc>7);

				/*Pedimos el nuevo dato y lo almacenamos en buffer*/
				solicitud_dato(opc,buffer);

				/*Le añadimos el caracter de fin de cadena*/
				strcat(buffer,"\n");

				/*Si el nuevo dato es exactamente igual al antiguo, se notifica*/
				if((res = editar(opc,numR,buffer)) == -1){
					printf("\n*No se realizó ningún cambio.*");
					break;
				}

				/*Si la edicion fue exitosa, se notifica*/
				if(res) printf("\n*La información del paciente fue actualizada con éxito.*");
				break;
			case 3:
				/*Se muestran todos los registros activos, en caso de no haber ninguno activo se notifica*/
				if(mostrarTodos() == -1) printf("\n*No hay pacientes para mostrar.*");
				break;
			case 4:
				/*Solicitamos el nombre o numero de registro del paciente*/
				do{
					printf("\nIngrese el nombre/número de registro del paciente a dar de baja: ");
					scanf("%49[^\n]",buffer);
					/*Determinamos si se leyo un numero o un nombre*/
					numR = esNum(buffer);

					/*Si se dio un numero invalido, lo notificamos y lo solicitamos de nuevo*/
					if(numR == -1) {
						printf("\n*Error - Número de registro inválido. Ingrese de nuevo.*");
					}
				}while(numR == -1);

				/*Si se leyo un nombre, buscamos el numero de registro asociado al nombre*/
				if(numR == 0){
					/*Si no se encontro al paciente, se notifica*/
					if((numR = buscarNombre(buffer)) == -1){
						printf("\n*No se encontró al paciente '%s'.*",buffer);
						break;
					};
				}

				/*Solicitamos una confirmacion para dar de baja al paciente*/
				do{
					fflush(stdin);
					printf("\nEstá seguro que desea dar de baja al paciente? (S/N): ",buffer);
					scanf("%c",&dec);
					if(dec != 'S' && dec != 'N' && dec!= 's' && dec!= 'n') printf("\n*Error - Caracter inválido. Ingrese de nuevo.*");
				}while(dec != 'S' && dec != 'N' && dec!= 's' && dec!= 'n');

				/*Si no se desea dar de baja al paciente, regresamos al menu principal*/
				if(dec == 'N' || dec == 'n') break;

				/*Si el registro ya estaba dado de baja, lo notificamos*/
				if((res = baja(numR)) == -1) {
					printf("\n*El paciente ya fue dado de baja anteriormente.*",buffer);
					break;
				}

				/*Si se dio de baja exitosamente, se notifica*/
				if(res) printf("\n*El paciente fue dado de baja con éxito.*",buffer);
				break;
		}
		/*Pausamos el programa y solicitamos cualquier tecla para continuar*/
		printf("\n\n");
		system("PAUSE");
	}
	/*Liberamos la memoria de buffer*/
	free(buffer);

	/*Se notifica el fin del programa*/
	printf("\nPrograma terminado.\n");
	system("PAUSE");
	return 0;
}
