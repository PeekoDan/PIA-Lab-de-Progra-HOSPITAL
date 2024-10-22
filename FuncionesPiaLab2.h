#ifndef FUNCIONESPIALAB2_H_INCLUDED
#define FUNCIONESPIALAB2_H_INCLUDED

/*Variable global de cantidad total de registros*/
int n;

/*La funcion imprime el menu principal*/
void menu(){
	printf("\n\n----------------- MENU -----------------");
	printf("\n|         1. Alta de paciente          |");
	printf("\n|  2. Busqueda o edicion de paciente   |");
	printf("\n|       3. Listado de pacientes        |");
	printf("\n|         4. Baja de paciente          |");
	printf("\n|               5. Salir               |");
	printf("\n----------------------------------------");
}

/*La funcion determina la cantidad total de registros dado un archivo*/
int numPacientes(){
	int cont = 0;
	char buffer[50];

	/*Si el archivo no existe, la funcion regresa 0*/
	FILE *arch;
	if((arch = fopen("RegistroPacientes.txt","r")) == NULL){
		return 0;
	}

	/*Si el archivo existe, la cantidad total de registros sera cantidad_total_lineas/9, ya que cada registro ocupa 9 lineas*/
	while(fgets(buffer,sizeof(buffer),arch)){
		cont++;
	}

	/*Cerramos el archivo*/
	fclose(arch);

	/*Definimos la cantidad total de registros y regresamos 1*/
	n = cont/9;
	return 1;
}

/*La funcion lee un dato del paciente y lo almacena en un buffer*/
void solicitud_dato(int opc_dat, char *buffer){
	int opc,edad,cons;
	char gen;

	/*Determinamos el dato a solicitar con un switch*/
	switch(opc_dat){
		case 1:
			/*Solicitamos el tipo de servicio mediante un menu y validamos que exista la opcion*/
			printf("\nA partir del siguiente menu, indica el tipo de servicio: ");
			printf("\n1.- Consulta externa");
			printf("\n2.- Emergencia");
			do{
				printf("\nClave del servicio deseado: ");
				scanf("%d",&opc);
				if(opc!=1&&opc!=2) printf("\n*Error - Clave invalida. Ingrese de nuevo.*");
			}while(opc!=1&&opc!=2);

			/*Dependiendo de la opcion elegida, almacenamos el tipo de servicio en buffer*/
			if(opc == 1) strcpy(buffer,"Consulta externa");
			else strcpy(buffer,"Emergencia");
			break;
		case 2:
			/*Limpiamos la consola y solicitamos el nombre*/
			fflush(stdin);
			printf("\nIngrese su nombre completo: ");
			scanf("%[^\n]",buffer);
			break;
		case 3:
			/*Limpiamos la consola y solicitamos la direccion*/
			fflush(stdin);
			printf("\nIngrese su direccion: ");
			scanf("%[^\n]",buffer);
			break;
		case 4:
			/*Solicitamos la edad y la validamos*/
			do{
				printf("\nIngrese su edad: ");
				scanf("%d",&edad);
				if(edad<1) printf("\n*Error - Edad invalida. Ingrese de nuevo.*");
			}while(edad<1);
			/*Almacenamos el numero como cadena en buffer*/
			sprintf(buffer, "%d", edad);
			break;
		case 5:
			/*Solicitamos el genero y validamos que la opcion sea correcta*/
			do{
				fflush(stdin);
				printf("\nIngrese su genero (H - Hombre, M - Mujer, O - Otro): ");
				scanf("%c",&gen);
				if(gen!='H'&&gen!='M'&&gen!='O') printf("\n*Error - Caracter invalido. Ingrese de nuevo.*");
			}while(gen!='H'&&gen!='M'&&gen!='O');

			/*Dependiendo de la opcion elegida, almacenamos el genero en buffer*/
			if(gen == 'H') strcpy(buffer,"Hombre");
			else if(gen == 'M') strcpy(buffer,"Mujer");
			else strcpy(buffer,"Otro");
			break;
		case 6:
			/*Limpiamos la consola y soliticamos la descripcion de los sintomas*/
			fflush(stdin);
			printf("\nIngrese una breve descripcion de sus sintomas: ");
			scanf("%[^\n]",buffer);
			break;
		case 7:
			/*Solicitamos el numero de consultorio y validamos que exista*/
			do{
				printf("\nIngrese el numero de consultorio disponible donde sera atendido (1-30): ");
				scanf("%d",&cons);
				if(cons<1||cons>30) printf("\n*Error - Consultorio invalido. Ingrese de nuevo.*");
			}while(cons<1||cons>30);
			/*Almacenamos el numero como cadena en buffer*/
			sprintf(buffer, "%d", cons);
	}
	return;
}

/*La funcion lee los datos de un paciente y los guarda en el archivo*/
int alta(){
	/*Apartamos 50 caracteres en memoria para buffer*/
	char *buffer = (char *)malloc(50*sizeof(char));
	int i;

	/*Declaracion y validacion del archivo*/
	FILE *arch;
	if((arch = fopen("RegistroPacientes.txt","a")) == NULL){
		printf("\n*Error al abrir el archivo*");
		return 0;
	}

	/*Almacenamos el numero de registro asignado al archivo y lo aumentamos en 1*/
	fprintf(arch, "%d\n", ++n);

	/*Solicitamos todos los datos del paciente y los almacenamos con formato en el archivo*/
	for(i=1; i<=7; i++){
		solicitud_dato(i, buffer);
		fprintf(arch, "%s\n", buffer);
	}
	fprintf(arch, "%s", "\n");

	/*Liberamos la memoria de buffer y cerramos el archivo*/
	free(buffer);
	fclose(arch);

	/*Si no hubo error, retornamos 1*/
	return 1;
}

/*La funcion recibe un numero de registro e imprime la informacion (si se encuentra regresa 1, si no se encuentra regresa -1)*/
int mostrarDatos(int numR){
	int i;
	char buffer[50];

	/*Declaracion y validacion del archivo*/
	FILE *arch;
	if((arch = fopen("RegistroPacientes.txt","r")) == NULL){
		printf("\n*Error al abrir el archivo.*");
		return 0;
	}

	/*Leemos y desechamos todas las lineas que hay hasta llegar al registro que nos interesa*/
	for(i=0;i<(numR-1)*9;i++){
		fgets(buffer,sizeof(buffer),arch);
	}

	/*Leemos su numero de registro*/
	fscanf(arch,"%d\n",&numR);

	/*Si el paciente fue dado de baja, cerramos el archivo y la funcion retorna -1*/
	if(numR == -1){
		fclose(arch);
		return -1;
	}

	/*Imprimimos todo el registro del paciente*/
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

	/*Cerramos el archivo y regresamos 1*/
	fclose(arch);
	return 1;
}

/*La funcion recibe un nombre y regresa su numero de registro, o si no se encuentra, -1*/
int buscarNombre(char nom[50]){
	/*cont es el numero del registro en el que estamos (en el ciclo de mas abajo)*/
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

/*La funcion imprime todos los registros activos*/
int mostrarTodos(){
	char buffer[50];
	/*flag cuenta los registros activos*/
	int numR,i,j,flag = 0;

	/*Declaracion y validacion del archivo*/
	FILE *arch;
	if((arch = fopen("RegistroPacientes.txt","r")) == NULL){
		printf("\n*Error al abrir el archivo.*");
		return 0;
	}

	/*El ciclo itera tantas veces como registros haya*/
	for(i=0;i<n;i++){
		/*Leemos el numero de registro*/
		fscanf(arch,"%d\n",&numR);

		/*Si el paciente fue dado de baja, pasamos al siguiente registro*/
		if(numR == -1){
			for(j=1;j<=8;j++){
				fgets(buffer,sizeof(buffer),arch);
			}
			continue;
		}

		/*Imprimimos todos los datos del registro*/
		printf("\n-------------------------------------------------------");
		printf("\nNumero de registro: %d",numR);
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
		fscanf(arch,"%[^\n]",buffer);
		printf("Numero de consultorio: %s",buffer);
		printf("\n-------------------------------------------------------");

		/*Aumentamos la variable contadora de registros activos*/
		flag++;
	}

	/*Cerramos el archivo*/
	fclose(arch);

	/*Si no se imprimio ningun registro, la funcion regresa -1*/
	if(flag == 0) return -1;

	/*Si se imprimio por lo menos 1 registro, la funcion regresa 1*/
	return 1;
}

/*La funcion actualiza un dato en especifico de un registro en especifico*/
int editar(int opc_edc, int numR, char *nueva_linea){
	/*Determinamos la linea a actualizar en base al numero de registro y al dato a editar*/
	int linea_editar = ((numR-1)*9)+opc_edc;

	/*Definimos una lista de cadenas*/
	char *lineas[n*9];

    char buffer[50];
    int i = 0;

	/*Declaracion y validacion del archivo*/
	FILE *arch;
	if((arch = fopen("RegistroPacientes.txt","r")) == NULL){
		printf("\n*Error al abrir el archivo*");
		return 0;
	}

    /*Leemos el archivo completo y almacenamos todas las lineas*/
    while(i < n*9){
    	fgets(buffer, sizeof(buffer), arch);
        lineas[i] = strdup(buffer); // Duplica la línea y la almacena
        i++;
    }

    /*Cerramos el archivo*/
    fclose(arch);

	/*Si la linea a actualizar es igual a la nueva linea, liberamos la memoria de las lineas y la funcion regresa -1*/
	if(strcmp(lineas[linea_editar],nueva_linea) == 0){
		for(i=0;i<n*9;i++){
			free(lineas[i]);
		}
		free(lineas);
		return -1;
	}

	/*Liberamos la memoria de la linea a actualizar*/
    free(lineas[linea_editar]);

    /*Actualizamos la linea con la nueva linea*/
    lineas[linea_editar] = strdup(nueva_linea);

	/*Declaracion y validacion del archivo*/
    if((arch = fopen("RegistroPacientes.txt","w")) == NULL){
		printf("\n*Error al abrir el archivo*");
		return 0;
	}

	/*Sobreescribimos el archivo (actualizado) y liberamos la memoria de cada linea*/
    for (i = 0; i < n*9; i++) {
        fprintf(arch,"%s",lineas[i]);
        free(lineas[i]);
    }

	/*Liberamos la memoria de la lista de cadenas y cerramos al archivo*/
	free(lineas);
    fclose(arch);

    /*Si no hubo error, retorna 1*/
	return 1;
}

/*La funcion da de baja un registro*/
/*'Dar de baja' significa actualizar el numero de registro a -1 y borrar su nombre*/
int baja(int numR){
	int res;
	/*Si el paciente ya estaba dado de baja, la funcion regresa -1*/
	if((res = editar(0, numR, "-1\n")) == -1){
		return -1;
	}
	/*Si ambas actualizaciones se ejecutan sin error, retorna 1*/
	if(res&&(editar(2, numR, "\n"))){
		return 1;
	}
	/*Si hubo algun error, la funcion retorna 0*/
	return 0;
}

/*La funcion recibe una cadena y determina si es un numero*/
int esNum(char *buffer){
	int num;

	/*Verificamos que sea un numero*/
	if (sscanf(buffer, "%d", &num) == 1) {
		/*Si es un numero, pero no es valido, retorna -1*/
    	if(num<1||num>n) return -1;

    	/*Si es un numero valido, retorna el numero*/
    	return num;
    }
    /*Si no lo es, la funcion regresa 0*/
	else{
        return 0;
    }
}

void menuEdicion(){
	printf("\n--------- Submenu - Edicion ---------");
	printf("\n|        1. Tipo de servicio        |");
	printf("\n|             2. Nombre             |");
	printf("\n|            3. Direccion           |");
	printf("\n|              4. Edad              |");
	printf("\n|             5. Genero             |");
	printf("\n|     6. Descripcion de sintomas    |");
	printf("\n|      7. Numero de consultorio     |");
	printf("\n-------------------------------------");
}




#endif // FUNCIONESPIALAB2_H_INCLUDED
