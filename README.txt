# PIA-Lab-de-Progra


EN CASO DE QUE NO EXISTA EL ARCHIVO .EXE EN ESTA CARPETA
Favor de compilar por el Proyecto de CodeBlocks ("Recursos\RegistroHospital.cbp")
Alternativamente, se puede compilar en cualquier compilador el archivo "Recursos\BaseDeDatos_HOSPITAL.c"
Se recomienda más compilar desde el proyecto de CodeBlocks.



A continuación hay una breve descripción de los elementos del código:


/* Variable global para la cantidad total de registros */
int n;

/* Función para validar valores enteros ingresados por usuario, manejando errores de ingresar letras */
int validar_num();

/* Función para imprimir el menú principal de opciones */
void menu();

/* Función para obtener el total de registros de pacientes desde un archivo */
int numPacientes();

/* Función para solicitar un dato específico de un paciente */
void solicitud_dato(int opc_dat, char *buffer);

/* Función para registrar los datos de un paciente en el archivo */
int alta();

/* Función para mostrar la información de un paciente dado su número de registro */
int mostrarDatos(int numR);

/* Función para buscar el número de registro de un paciente por su nombre */
int buscarNombre(char nom[50]);

/* Función para mostrar todos los registros activos de pacientes */
int mostrarTodos();

/* Función para actualizar un dato específico de un registro */
int editar(int opc_edc, int numR, char *nueva_linea);

/* Función para dar de baja un registro de paciente */
int baja(int numR);

/* Función para verificar si una cadena representa un número válido */
int esNum(char *buffer);

/* Función para imprimir el menú de opciones de edición */
void menuEdicion();

/* Función que verifica si el directorio actual es "Recursos" y, de ser así, sube un nivel */
void checarEnRecursos();
