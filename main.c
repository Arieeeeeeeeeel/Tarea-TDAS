#include "tdas/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef enum {
  LOW_PRIORITY=3,
  MEDIUM_PRIORITY=2,
  HIGH_PRIORITY=1
} Prioridad;

typedef struct Paciente {
  char nombre[100];
  int edad;
  char sintoma[100];
  Prioridad prioridad;
  time_t horaRegistro;
} Paciente;

int paciente_lowerThan(void *data1, void *data2) {
  Paciente *paciente1 = (Paciente *)data1;
  Paciente *paciente2 = (Paciente *)data2;
  if (paciente1->prioridad == paciente2->prioridad) {
    return paciente1->horaRegistro < paciente2->horaRegistro;
  }
  return paciente1->prioridad < paciente2->prioridad;
}

void paciente_obtenerPrioridad(Prioridad prioridad, char *inputString) {
  if (prioridad == LOW_PRIORITY) {
    strcpy(inputString, "baja");
  } else if (prioridad == MEDIUM_PRIORITY) {
    strcpy(inputString, "media");
  } else if (prioridad == HIGH_PRIORITY) {
    strcpy(inputString, "alta");
  } else {
    strcpy(inputString, "desconocida");
  }
}

void paciente_print(Paciente *paciente) {
  char prioridadL[100];
  paciente_obtenerPrioridad(paciente->prioridad, prioridadL);
  printf("%s (edad: %d, sintoma: %s, prioridad: %s, registro: %s)",
    paciente->nombre,
    paciente->edad,
    paciente->sintoma,
    prioridadL,
    ctime(&paciente->horaRegistro)
  );
}

// Función para limpiar la  pantalla
void limpiarPantalla() { system("clear"); }

void presioneTeclaParaContinuar() {
  puts("Presione una tecla para continuar...");
  getchar(); // Consume el '\n' del buffer de entrada
  getchar(); // Espera a que el usuario presione una tecla
}

// Menú principal
void mostrarMenuPrincipal() {
  //limpiarPantalla();
  puts("========================================");
  puts("     Sistema de Gestión Hospitalaria");
  puts("========================================");

  puts("1) Registrar paciente");
  puts("2) Asignar prioridad a paciente");
  puts("3) Mostrar lista de espera");
  puts("4) Atender al siguiente paciente");
  puts("5) Mostrar pacientes por prioridad");
  puts("6) Salir");
}

void registrar_paciente(List *pacientes) {
  printf("Registrar nuevo paciente\n");
  // Aquí implementarías la lógica para registrar un nuevo paciente
  Paciente * nuevoPaciente = (Paciente *)malloc(sizeof(Paciente));
  printf("Nombre del paciente: ");
  scanf("%s", nuevoPaciente->nombre);
  printf("Edad del paciente: ");
  scanf("%d", &(nuevoPaciente->edad));
  printf("Sintoma del paciente: ");
  scanf("%s", nuevoPaciente->sintoma);
  nuevoPaciente->prioridad = LOW_PRIORITY;
  nuevoPaciente->horaRegistro = time(NULL);
  list_sortedInsert(pacientes, nuevoPaciente, paciente_lowerThan);
  printf("Paciente registrado con éxito.\n");
}

void asignar_prioridad(List *pacientes) {
  printf("Asignar prioridad a paciente\n");
  char nombrePaciente[100];
  printf("Nombre del paciente: ");
  scanf("%s", nombrePaciente);

  Paciente *paciente = (Paciente *) list_first(pacientes);
  while (paciente != NULL && strcmp(paciente->nombre, nombrePaciente) != 0) {
    paciente = (Paciente *) list_next(pacientes);
  }

  if (paciente == NULL) {
    printf("Paciente no encontrado.\n");
    return;
  }

  list_popCurrent(pacientes);
  printf("Ingrese nueva prioridad para el paciente\n");
  printf("1) Baja\n");
  printf("2) Media\n");
  printf("3) Alta\n");
  printf(">> ");
  char opcion;
  scanf(" %c", &opcion);
  if (opcion == '1') {
    paciente->prioridad = LOW_PRIORITY;
  } else if (opcion == '2') {
    paciente->prioridad = MEDIUM_PRIORITY;
  } else if (opcion == '3') {
    paciente->prioridad = HIGH_PRIORITY;
  } else {
    printf("Opcion invalida.\n");
    list_sortedInsert(pacientes, paciente, paciente_lowerThan);
    return;
  }
  list_sortedInsert(pacientes, paciente, paciente_lowerThan);
  printf("Prioridad actualizada con exito.\n");
}


void mostrar_lista_pacientes(List *pacientes) {
  // Mostrar pacientes en la cola de espera
  printf("Pacientes en espera: \n");
  Paciente * paciente = (Paciente *) list_first(pacientes);
  if (paciente == NULL) {
    printf("No hay pacientes en espera.\n");
  } else {
    while (paciente != NULL) {
      paciente_print(paciente);
      printf("\n");
      paciente = (Paciente *) list_next(pacientes);
    }
 }
}

void atender_siguiente_paciente(List *pacientes) {
  printf("Atender paciente\n");
  Paciente * paciente = (Paciente *) list_first(pacientes);
  if (paciente == NULL) {
    printf("No existen pacientes en espera.\n");
  } else {
    list_popFront(pacientes);
    printf("Paciente atendido: ");
    paciente_print(paciente);
    printf("\n");
  }
}

void mostrar_pacientes_por_prioridad(List *pacientes) {
  Prioridad prioridad;
  printf("Mostrar pacientes por prioridad\n");
  printf("Ingrese una prioridad\n");
  printf("1) Baja\n");
  printf("2) Media\n");
  printf("3) Alta\n");
  printf(">> ");
  char opcion;
  scanf(" %c", &opcion);
  if (opcion == '1') {
    prioridad = LOW_PRIORITY;
  } else if (opcion == '2') {
    prioridad = MEDIUM_PRIORITY;
  } else if (opcion == '3') {
    prioridad = HIGH_PRIORITY;
  } else {
    printf("Opcion invalida.\n");
    return;
  }

  char prioridadLabel[100];
  paciente_obtenerPrioridad(prioridad, prioridadLabel);
  printf("Pacientes con prioridad %s: \n", prioridadLabel);

  Paciente * paciente = (Paciente *) list_first(pacientes);
  int pacientesEncontrados = 0;
  while (paciente != NULL) {
    if (paciente->prioridad == prioridad) {
      paciente_print(paciente);
      printf("\n");
      pacientesEncontrados++;
    }
    paciente = (Paciente *) list_next(pacientes);
  }
  if (pacientesEncontrados > 0) {
    printf("Pacientes encontrados: %d\n", pacientesEncontrados);
  } else {
    printf("No se encontraron pacientes con la prioridad especificada.\n");
  }
}

int main() {
  char opcion;
  List *pacientes = list_create(); // puedes usar una lista para gestionar los pacientes

  do {
  mostrarMenuPrincipal();
  printf("Ingrese su opción: ");
  scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el
         // newline anterior

  switch (opcion) {
  case '1':
    registrar_paciente(pacientes);
    break;
  case '2':
    asignar_prioridad(pacientes);
    break;
  case '3':
    mostrar_lista_pacientes(pacientes);
    break;
  case '4':
    atender_siguiente_paciente(pacientes);
    break;
  case '5':
    mostrar_pacientes_por_prioridad(pacientes);
    break;
  case '6':
    puts("Saliendo del sistema de gestión hospitalaria...");
    break;
  default:
    puts("Opción no válida. Por favor, intente de nuevo.");
  }
  presioneTeclaParaContinuar();

  } while (opcion != '6');

  // Liberar recursos, si es necesario
  list_clean(pacientes);

  return 0;
}
