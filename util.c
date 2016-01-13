#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "util.h"

/* Cuando el argumento es una letra en mayusculas, devuelve su equivalente en
 * minsuculas. Si el argumento no es una letra en mayusculas, lo devuelve
 * sin modificar.
 */
char minuscula(char c) {
  if (c >= 'A' && c <= 'Z')
    c += 32;

  return c;
}

/*
 * Devuelve 1 cuando el argumento es una letra de la 'a' a la 'z', sin
 * distinguir mayusculas o minusculas. En caso contrario devuelve 0.
 */
int es_letra(char c) {
  c = minuscula(c);

  return c >= 'a' && c <= 'z';
}

/* Devuelve 1 cuando el argumento es una vocal, sin distinguir mayusculas o
 * minusculas.
 */
int es_vocal(char c) {
  c = minuscula(c);

  return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

/* Devuelve 1 cuando el argumento es una consonante, sin distinguir mayusculas
 * o minusculas.
 */
int es_consonante(char c) {
  return es_letra(c) && !es_vocal(c);
}

/* Devuelve 1 cuando el argumento es un digito numerico. Devuelve 0 en caso
 * contrario.
 */
int es_digito(char c) {
  return c >= '0' && c <= '9';
}

/*
 * Devuelve 1 cuando el caracter obtenido es un delimitador de palabra. Los
 * caracteres considerados como delimitadores son:
 *   - ' ' (espacio)
 *   - '\t' (tabulador)
 *   - '\n' (salto de linea)
 *   - '"' (comilla doble)
 *   - ',', '.', ';', ':' (signos de puntuacion)
 *   - '(', ')' (parentesis)
 *   - '\0' (caracter nulo)
 *
 * Total: 11
 */
int es_delimitador(char c) {
  int i;
  char delimitadores[11] = {
    ' ',
    ',', '.', ';', ':',
    '\n',
    '\t',
    '"',
    '(', ')',
    '\0'
  };

  for (i = 0; i < 11; i++) {
    if (c == delimitadores[i]) {
      return 1;
    }
  }

  return 0;
}

int es_bisiesto(int anyo) {
  return ((anyo % 4 == 0 && anyo % 100 != 0) || anyo % 400 == 0);
}

int es_fecha_valida(fecha_t f) {
  int dias[] = {
    0,
    31, // enero
    28, // febrero
    31, // marzo
    30, // abril
    31, // mayo
    31, // junio
    31, // julio
    31, // agosto
    30, // septiembre
    31, // octubre
    30, // noviembre
    31  // diciembre
  };

  if (es_bisiesto(f.anyo)) dias[2]++;

  if (f.mes <= 0 || f.mes > 12)
    return 0;

  if (f.dia <= 0 || f.dia > dias[f.mes])
    return 0;

  return 1;
}

int es_fecha(char *cadena) {
  char dia[3], mes[3], anyo[5];
  char formato[] = "ii/ii/iiii#";
  int i;
  fecha_t fecha;

  for (i = 0; cadena[i]; i++) {
    if (formato[i] == 'i') {
      if (!es_digito(cadena[i])) return 0;
    }
    if (formato[i] == '/') {
      if (cadena[i] != '/') return 0;
    }
    if (formato[i] == '#') {
      if (cadena[i] != '\0') return 0;
    }
  }

  dia[0] = cadena[0];
  dia[1] = cadena[1];
  dia[2] = '\0';
  fecha.dia = atoi(dia);

  mes[0] = cadena[3];
  mes[1] = cadena[4];
  mes[2] = '\0';
  fecha.mes = atoi(mes);

  anyo[0] = cadena[6];
  anyo[1] = cadena[7];
  anyo[2] = cadena[8];
  anyo[3] = cadena[9];
  anyo[4] = '\0';
  fecha.anyo = atoi(anyo);

  return es_fecha_valida(fecha);
}

int es_numero(char *cadena) {
  int i = 0;
  int cuenta_puntos = 0;

  for (i = 0; cadena[i]; i++) {
    if (!es_digito(cadena[i])) {
      if (i == 0) {
        if (cadena[i] != '+' && cadena[i] != '-') {
          return 0;
        }
      } else {
        if (cadena[i] == '.' && cuenta_puntos == 0) {
          cuenta_puntos++;
        } else {
          return 0;
        }
      }
    }
  }

  return 1;
}

void cargar_palabras(TLista *lista, FILE *f) {
  char palabra[100];
  char c;
  int i = 0;

  // Si hay una lista ya cargada, hay que borrarla
  if (lista->longitud > 0) {
    terminar_lista(lista);
    inicializar_lista(lista);
  }

  // Extraer cada palabra del fichero
  while ((c = fgetc(f)) != EOF) {
    if (!es_delimitador(c)) {
      palabra[i] = c;
      i++;
    } else {
      palabra[i] = '\0';
      i = 0;

      if (strlen(palabra) > 0) {
        insertar_palabra(lista, palabra);
      }
    }
  }
}
