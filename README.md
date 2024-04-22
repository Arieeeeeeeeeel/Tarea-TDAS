# Sistema de Gestión de Pacientes en Hospital

Este pequeño programa sirve para ingresar pacientes a la base de datos, pudiendo asímismo asignarle una prioridad al paciente (baja, media, alta) y mostrar cómo quedaría la lista de espera. Luego, atender a un paciente de manera directa, eliminando al anterior, también pudiendo mostrar a los pacientes en orden de prioridad.

## Cómo compilar y ejecutar

1. Visita [Repl.it](https://repl.it/).
2. Crea una nueva cuenta o inicia sesión si ya tienes una.
3. Una vez en tu dashboard, selecciona "New Repl" y elige "Import from GitHub".
4. Pega la URL del repositorio: `https://github.com/Arieeeeeeeeeel/Tarea-TDAS`.
5. [Repl.it](http://repl.it/) clonará el repositorio y preparará un entorno de ejecución.
6. Presiona el botón "Run" para compilar y ejecutar la aplicación.

## Funcionalidades

- Registrar pacientes con su nombre, edad y sintoma. 
- Asignar o modificar la prioridad de los pacientes.
- Ver la lista de espera de pacientes, ordenada por prioridad y hora de registro.
- Atender al siguiente paciente, respetando el orden de prioridad.

### A mejorar:

- Que la interfaz sea más rápida y llamativa
- Edición de datos de paciente en caso de ser mal registrados
- Restringir palabras erróneas, solo aceptar nombres, edad y sintomas correctos

## Ejemplo de uso
# Función Registro paciente
Se registra el paciente rellenando los datos en el siguiente orden: Nombre, Edad y Sintoma.
# Función Asignar prioridad
Como se sabe, todos los pacientes al ser registrados, se les asigna una prioridad baja automáticamente. Esta función de asignar prioridad, nos ayuda a asignarle una prioridad nueva al paciente, solamente ingresando su nombre y la prioridad a actualizar.
# Función Mostrar Lista de Espera
Como dice la función, esta nos muestra la lista de espera que tenemos en el orden de prioridad y hora de llegada.
# Función Atender al siguiente paciente
En base a la función de lista de espera, atendemos al siguiente paciente, respetando la prioridad y el orden de llegada.
# Función Mostrar Pacientes por prioridad
Nos muestra las prioridades a escoger (baja, media, alta) y al seleccionar una se nos muestra en pantalla todos los pacientes que tienen esa prioridad.


