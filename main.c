#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "comandos/comandos.h"

#define PROMPT_ALIAS "jesus.burgos"

#define T_LINEA    300
#define T_PALABRA  50
#define N_PALABRAS 20

/*
 * Muestra los datos del alumno
 */
void mostrar_datos_alumno() {
  printf("Alumno: Jesus Burgos Macia\n");
  printf("   DNI: 12345678X\n\n");
}

/*
 * Muestra el prompt tal y como se pide en el enunciado, ejemplo:
 *
 *     jesus.burgos[*]:>
 *
 */
void mostrar_prompt(char *fichero_origen) {
  if (strlen(fichero_origen) == 0) {
    printf("%s[*]:> ", PROMPT_ALIAS);
  } else {
    printf("%s[%s]:> ", PROMPT_ALIAS, fichero_origen);
  }
}

typedef struct {
  char id_comando;
  /* Estableceremos los siguientes identificadores para cada comando:
   *
   * salir       : 's'
   * origen      : 'o'
   * diccionario : 'd'
   * neutro      : 'n'
   * info        : 'i'
   * ranking     : 'r'
   */
  char linea[T_LINEA];
  char palabras[N_PALABRAS][T_PALABRA];
  int n_palabras;
} comando_t;

/*
 * Analiza la linea obtenida y separa todas sus palabras.
 *
 * Introduce cada palabra que se identifica en el array `palabras` del
 * registro `comando_t` que se obtiene como parametro (variable `comando`).
 */
void identificar_palabras(comando_t *comando) {
  int i, j;
  int lon_linea = strlen(comando->linea);
  char caracter, siguiente_caracter;

  comando->n_palabras = 0;
  for (i = 0, j = 0; i < lon_linea; i++) {
    caracter = comando->linea[i];

    if (caracter != ' ' && caracter != '\n') {
      comando->palabras[comando->n_palabras][j] = caracter;
      j++;

      siguiente_caracter = comando->linea[i + 1];
      if (siguiente_caracter == ' ' || siguiente_caracter == '\n') {
        comando->palabras[comando->n_palabras][j] = '\0';
        comando->n_palabras++;
        j = 0;
      }
    }
  }
}

/*
 * Analiza la primera palabra del comando introducido.
 *
 * Escribe el identificador asociado a ese comando en el campo `id_comando` del
 * registro `comando_t` que se obtiene como parametro (variable `comando`).
 */
void identificar_comando(comando_t *comando) {
  if (strcmp(comando->palabras[0], "salir") == 0) {
    comando->id_comando = 's';
  } else if (strcmp(comando->palabras[0], "origen") == 0) {
    comando->id_comando = 'o';
  } else if (strcmp(comando->palabras[0], "diccionario") == 0) {
    comando->id_comando = 'd';
  } else if (strcmp(comando->palabras[0], "neutro") == 0) {
    comando->id_comando = 'n';
  } else if (strcmp(comando->palabras[0], "info") == 0) {
    comando->id_comando = 'i';
  } else if (strcmp(comando->palabras[0], "ranking") == 0) {
    comando->id_comando = 'r';
  } else if (strcmp(comando->palabras[0], "buscar") == 0) {
    comando->id_comando = 'b';
  } else if (strcmp(comando->palabras[0], "suma") == 0) {
    comando->id_comando = '+';
  } else {
    comando->id_comando = '\0';
  }
}

/*
 * Obtiene un comando y lo analiza. Devuelve un objeto `comando_t` que ya
 * incluye el identificador del comando introducido, un array de todas las
 * palabras que componen la linea introducida por el usuario.
 */
comando_t obtener_comando() {
  comando_t comando;

  if (fgets(comando.linea, T_LINEA, stdin)) {
    identificar_palabras(&comando);
    identificar_comando(&comando);
  } else {
    // Hubo un error de lectura leyendo el comando (Ctrl + D), salimos
    comando.id_comando = 's';
  }

  return comando;
}

void argumentos_invalidos(char *comando) {
  fprintf(stderr, "Argumentos invalidos para el comando '%s'\n", comando);
}

void comando_invalido(char *comando) {
  fprintf(stderr, "El comando '%s' no es valido\n", comando);
}

void ejecutar_comando_neutro(estado_t *estado, comando_t comando) {
  if (comando.n_palabras == 2) {
      if (strcmp(comando.palabras[1], "on") == 0) {
        comando_neutro_on(&estado->neutros);
        estado->estado_neutros = on;
      } else if (strcmp(comando.palabras[1], "off") == 0) {
        comando_neutro_off(&estado->neutros);
        estado->estado_neutros = off;
      } else if (strcmp(comando.palabras[1], "actualizar") == 0) {
        comando_neutro_actualizar(&estado->neutros);
      } else {
        argumentos_invalidos("neutro");
      }
  } else if (comando.n_palabras > 2) {
    if (strcmp(comando.palabras[1], "agregar") == 0
        || strcmp(comando.palabras[1], "eliminar") == 0) {
      if (estado->estado_neutros == on) {
        for (int i = 2; i < comando.n_palabras; i++) {
          if (comando.palabras[1][0] == 'a') // 'a' de agregar
            comando_neutro_agregar(&estado->neutros, comando.palabras[i]);
          else if (comando.palabras[1][0] == 'e') // 'e' de eliminar
            comando_neutro_eliminar(&estado->neutros, comando.palabras[i]);
        }
      } else {
        fprintf(stderr, "Primero debes activar la lista de palabras neutras\n");
      }
    } else {
      argumentos_invalidos("neutro");
    }
  } else {
    argumentos_invalidos("neutro");
  }
}

void ejecutar_comando_info(estado_t *estado, comando_t comando) {
  FILE *salida = NULL;

  if (estado->fd_origen == NULL) {
    fprintf(stderr, "No hay un fichero de origen\n");
    return;
  }

  if (comando.n_palabras == 2) {
    salida = stdout;
  } else if (comando.n_palabras == 3) {
    salida = fopen(comando.palabras[2], "w");

    if (salida == NULL) {
      fprintf(stderr, "No se puede abrir '%s' para escritura\n",
              comando.palabras[2]);
    }
  } else {
    argumentos_invalidos("info");
  }

  if (strcmp(comando.palabras[1], "caracteres") == 0) {
    comando_info_caracteres(estado, salida);
  } else if (strcmp(comando.palabras[1], "palabras") == 0) {
    comando_info_palabras(estado, salida);
  } else {
    argumentos_invalidos("info");
  }

  if (salida != stdout && salida != NULL) {
    fclose(salida);
  }
}

void ejecutar_comando_ranking(estado_t *estado, comando_t comando) {
  int n;
  char *opcion;

  if (estado->fd_origen == NULL) {
    fprintf(stderr, "No hay un fichero de origen\n");
    return;
  }

  if (comando.n_palabras == 2) {
    n = 10;
    opcion = comando.palabras[1];
  } else if (comando.n_palabras == 3) {
    if (strcmp(comando.palabras[1], "total") == 0) {
      n = 0;
    } else {
      n = atoi(comando.palabras[1]);
      if (n <= 0) {
        argumentos_invalidos("ranking");
        return;
      }
    }
    opcion = comando.palabras[2];
  } else {
    argumentos_invalidos("ranking");
    return;
  }

  if (strcmp(opcion, "caracteres") == 0) {
    comando_ranking_caracteres(estado, n);
  } else if (strcmp(opcion, "palabras") == 0) {
    comando_ranking_palabras(estado, n);
  } else {
    argumentos_invalidos("ranking");
  }
}

/*
 * Nota: Seria recomendable obtener la variable comando por referencia. Es
 * decir, en forma de puntero: `void ejecutar_comando(comando_t *comando)`.
 */
void ejecutar_comando(estado_t *estado, comando_t comando) {
  if (comando.n_palabras == 0) return;

  switch (comando.id_comando) {
    case 'o':
      comando_origen(estado, comando.palabras[1]);
      break;
    case 'd':
      comando_diccionario(estado, comando.palabras[1]);
      break;
    case 'n':
      ejecutar_comando_neutro(estado, comando);
      break;
    case 'i':
      ejecutar_comando_info(estado, comando);
      break;
    case 'r':
      ejecutar_comando_ranking(estado, comando);
      break;
    case 'b':
      comando_buscar(estado, comando.palabras[1]);
      break;
    case '+':
      comando_suma(&estado->origen);
      break;
    case 's':
      break;
    default:
      comando_invalido(comando.palabras[0]);
  }
}

/* Pone a cero todos los campos del registro de estado. */
void inicializar_estado(estado_t *estado) {
  // Fichero de origen
  estado->nombre_origen[0] = '\0';
  estado->fd_origen = NULL;

  estado->estado_neutros = off;

  inicializar_lista(&estado->diccionario);
  inicializar_lista(&estado->neutros);
  inicializar_lista(&estado->origen);
}

/* Libera todos los recursos que esten siendo empleados por el registro de
 * estado recibido como parametro.
 */
void terminar_estado(estado_t *estado) {
  // Si habia algun fichero abierto, lo cerramos
  if (estado->fd_origen != NULL) {
    fclose(estado->fd_origen);
  }

  // Liberamos todas las listas
  terminar_lista(&estado->diccionario);
  terminar_lista(&estado->neutros);
  terminar_lista(&estado->origen);
}

int main() {
  estado_t estado;
  comando_t comando;

  inicializar_estado(&estado);

  mostrar_datos_alumno();
  do {
    mostrar_prompt(estado.nombre_origen);
    comando = obtener_comando();
    ejecutar_comando(&estado, comando);
  } while (comando.id_comando != 's');

  terminar_estado(&estado);
  return 0;
}
