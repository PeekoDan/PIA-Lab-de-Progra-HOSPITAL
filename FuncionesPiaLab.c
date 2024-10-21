#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Variable global de cantidad total de registros*/
int n = 0;

void menu(){
	printf("\n\n----------------- MENU -----------------");
	printf("\n|         1. Alta de paciente          |");
	printf("\n|  2. Busqueda o edicion de paciente   |");
	printf("\n|       3. Listado de pacientes        |");
	printf("\n|         4. Baja de paciente          |");
	printf("\n|               5. Salir               |");
	printf("\n----------------------------------------");
}

/*Estructura tipo paciente*/
typedef struct{
	int numR, edad, cons;
	char tipoS[18], nom[50], dir[50], desc[50], gen[7];
}PACIENTE;

char* num_a_Cadena(int n){
	char *str = (char *) malloc(3*sizeof(char));
	snprintf(str,3,"%d",n);
	return str;
}

void solicitud_dato(int opc_dat, PACIENTE *p){
	int opc;
	char gen;
	switch(opc_dat){
		case 1:
			printf("\nA partir del siguiente menu, indica el tipo de servicio: ");
			printf("\n1.- Consulta externa");
			printf("\n2.- Emergencia");
			do{
				printf("\nClave del servicio deseado: ");
				scanf("%d",&opc);
				if(opc!=1&&opc!=2) printf("\n*Error - Clave invalida. Ingrese de nuevo.*");
			}while(opc!=1&&opc!=2);
			if(opc == 1) strcpy(p->tipoS,"Consulta externa");
			else strcpy(p->tipoS,"Emergencia");
			break;
		case 2:
			fflush(stdin);
			printf("\nIngrese su nombre completo: ");
			scanf("%[^\n]",p->nom);
			break;
		case 3:
			fflush(stdin);
			printf("\nIngrese su direccion: ");
			scanf("%[^\n]",p->dir);
			break;
		case 4:
			do{
				printf("\nIngrese su edad: ");
				scanf("%d",&p->edad);
				if(p->edad<1) printf("\n*Error - Edad invalida. Ingrese de nuevo.*");
			}while(p->edad<1);
			break;
		case 5:
			do{
				fflush(stdin);
				printf("\nIngrese su genero (H - Hombre, M - Mujer, O - Otro): ");
				scanf("%c",&gen);
				if(gen!='H'&&gen!='M'&&gen!='O') printf("\n*Error - Caracter invalido. Ingrese de nuevo.*");
			}while(gen!='H'&&gen!='M'&&gen!='O');
			if(gen == 'H') strcpy(p->gen,"Hombre");
			else if(gen == 'M') strcpy(p->gen,"Mujer");
			else strcpy(p->gen,"Otro");
			break;
		case 6:
			fflush(stdin);
			printf("\nIngrese una breve descripcion de sus sintomas: ");
			scanf("%[^\n]",p->desc);
			break;
		case 7:
			do{
				printf("\nIngrese el numero de consultorio disponible donde sera atendido (1-30): ");
				scanf("%d",&p->cons);
				if(p->cons<1||p->cons>30) printf("\n*Error - Consultorio invalido. Ingrese de nuevo.*");
			}while(p->cons<1||p->cons>30);
	}
	return;
}

/*La funcion lee los datos de un paciente y los guarda en el archivo*/
int alta(){
	PACIENTE p;
	int i;

	for(i=1; i<=7; i++){
		solicitud_dato(i, &p);
	}
	
	FILE *arch;
	if((arch = fopen("RegistroPacientes.txt","a")) == NULL){
		printf("\n*Error al abrir el archivo*");
		return 0;
	}
	
	/*if(n) fprintf(arch,"%s","\n\n");*/
	fprintf(arch,"%d\n", n++);
	fprintf(arch, "%s\n", p.tipoS);
	fprintf(arch, "%s\n", p.nom);
	fprintf(arch, "%s\n", p.dir);
	fprintf(arch, "%d\n", p.edad);
	fprintf(arch, "%s\n", p.gen);
	fprintf(arch, "%s\n", p.desc);
	fprintf(arch, "%d\n\n", p.cons);
	fclose(arch);
	
	printf("\n*Los datos del paciente fueron guardados con exito*");
	return 1;
}

/*La funcion recibe un numero de registro e imprime la informacion (si se encuentra regresa 1, si no se encuentra regresa -1)*/
int mostrarDatos(int numR){
	PACIENTE p;
	int i;
	char buffer[50];
	
	/*Declaracion y validacion del archivo*/
	FILE *arch;
	if((arch = fopen("RegistroPacientes.txt","r")) == NULL){
		printf("\n*Error al abrir el archivo.*");
		return 0;
	}
	
	/*Leemos y desechamos todas las lineas que hay hasta llegar al registro que nos interesa*/
	for(i=1;i<=(numR-1)*9;i++){
		fgets(buffer,sizeof(buffer),arch);
	}
	
	/*Leemos toda la informacion del registro y la almacenamos en la estructura*/
	fscanf(arch, "%d\n%[^\n]\n%[^\n]\n%[^\n]\n%d\n%[^\n]\n%[^\n]\n%d", &p.numR, p.tipoS, p.nom, p.dir, &p.edad, p.gen, p.desc, &p.cons);
	
	/*Si el numero de registro es -1, la funcion devuelve -1 (como si no lo hubiera encontrado)
	***es q mi idea es q cuando se dé de baja un paciente, su numero de registro se actualice a -1
	y su nombre se vuelva \n y asi ya no se tome en cuenta, otra opcion seria borrar todo el registro
	dejandolo en blanco***/
	if(p.numR == -1) return -1;
	
	/*Imprime toda la informacion del registro, cierra el archivo y regresa 1*/
	printf("\nNumero de registro: %d",p.numR);
	printf("\nTipo de servicio: %s",p.tipoS);
	printf("\nNombre: %s",p.nom);
	printf("\nDireccion: %s",p.dir);
	printf("\nEdad: %d",p.edad);
	printf("\nGenero: %s",p.gen);
	printf("\nDescripcion de sintomas: %s",p.desc);
	printf("\nNumero de consultorio: %d",p.cons);
	fclose(arch);
	return 1;
}

/*La funcion recibe un nombre y regresa su numero de registro, o si no se encuentra, -1*/
int buscarNombre(char nom[50]){
	/*Cont es el numero del registro en el que estamos (en el ciclo de mas abajo)*/
	int i,cont = 1;
	char buffer[50];
	
	/*Declaracion y validacion del archivo*/
	FILE *arch;
	if((arch = fopen("RegistroPacientes.txt","r")) == NULL){
		printf("\n*Error al abrir el archivo.*");
		return 0;
	}
	
	/*Leemos y desechamos las primeras dos lineas (nunca habra un nombre a comparar aqui)*/
	fgets(buffer,sizeof(buffer),arch);
	fgets(buffer,sizeof(buffer),arch);
	
	while(1){
		/*Leemos un nombre y lo comparamos con el buscado, si es igual devolvemos el numero de registro*/
		fscanf(arch,"%[^\n]",buffer);
		if(strcmp(buffer,nom) == 0){
			fclose(arch);
			return cont;
		}
		
		/*Si no era igual, pasamos al siguiente numero de registro*/
		cont++;
		
		/*Si se alcanza el ultimo registro sin haberse encontrado el nombre, el ciclo para*/
		if(cont == n+1) break;
		
		/*Saltamos hasta la linea del siguiente nombre*/
		for(i=1;i<=9;i++){
			fgets(buffer,sizeof(buffer),arch);
		}
	}
	/*Si no se encontro el nombre, cerramos el archivo y regresamos -1*/
	fclose(arch);
	return -1;
}

int mostrarTodos(){
	char buffer[50];
	int numR,i;
	
	/*Declaracion y validacion del archivo*/
	FILE *arch;
	if((arch = fopen("RegistroPacientes.txt","r")) == NULL){
		printf("\n*Error al abrir el archivo.*");
		return 0;
	}
	while(1){
		fscanf(arch,"%d\n",&numR);
		if(numR == -1){
			for(i=1;i<=8;i++){
				fgets(buffer,sizeof(buffer),arch);
			}
			fscanf(arch,"%d\n",&numR);
		}
		printf("\n\nNumero de registro: %d",numR);
		fgets(buffer,sizeof(buffer),arch);
		printf("\nTipo de servicio: %s",buffer);
		fgets(buffer,sizeof(buffer),arch);
		printf("Nombre: %s",buffer);
		fgets(buffer,sizeof(buffer),arch);
		printf("Direccion: %s",buffer);
		fgets(buffer,sizeof(buffer),arch);
		printf("Edad: %s",buffer);
		fgets(buffer,sizeof(buffer),arch);
		printf("Genero: %s",buffer);
		fgets(buffer,sizeof(buffer),arch);
		printf("Descripcion de sintomas: %s",buffer);
		fgets(buffer,sizeof(buffer),arch);
		printf("Numero de consultorio: %s",buffer);
		if(numR == n) break;
	}
	return 1;
}

int editar(int opc_edc, int numR){
	int i;
	PACIENTE p;
	char *buffer = (char *)malloc(50*sizeof(char));
	char *str;
	FILE *arch;
	if((arch = fopen("RegistroPacientes.txt","r+")) == NULL){
		printf("\n*Error al abrir el archivo*");
		return 0;
	}
	for(i=1;i<=((numR-1)*9)+opc_edc;i++){
		fgets(buffer,sizeof(buffer),arch);
	}
	free(buffer);
	solicitud_dato(opc_edc, &p);
	printf("\n*La informacion del paciente fue actualizada con exito.*");
	return 1;
}

int main(){
	int opc;
	while(1){
		menu();
		do{
			printf("\nOpcion deseada: ");
			scanf("%d",&opc);
			if(opc<1||opc>5) printf("*Error - Opcion invalida.*");
		}while(opc<1||opc>5);
		
		if(opc == 5) break;
		
		switch(opc){
			case 1:
				alta();
				break;
			case 2:
				break;
		}
	}
	/*editar(2, 3); La funcion esta bien, solo hay que investigar como sobreescribir solo una parte del archivo 
	(sospecho que literalmente habra que reescribirlo todo en un archivo nuevo y renombrarlo)*/ 
	printf("\nPrograma terminado.");
	return 0;
}
