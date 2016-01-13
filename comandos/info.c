#include <stdio.h>
#include "comandos.h"

void comando_info_caracteres(estado_t *estado, FILE *out) {
  char c;
  int vocales = 0, consonantes = 0, digitos = 0, otros = 0;

  fseek(estado->fd_origen, 0, SEEK_SET);
  while ((c = fgetc(estado->fd_origen)) != EOF) {
    if (es_vocal(c)) {
      vocales++;
    } else if (es_consonante(c)) {
      consonantes++;
    } else if (es_digito(c)) {
      digitos++;
    } else {
      otros++;
    }
  }

  fprintf(out, "Vocales     : %i\n", vocales);
  fprintf(out, "Consonantes : %i\n", consonantes);
  fprintf(out, "Digitos     : %i\n", digitos);
  fprintf(out, "Otros       : %i\n", otros);
}

void comando_info_palabras(estado_t *estado, FILE *out) {
  TNodo *nodo;
  int fechas = 0, numeros = 0;
  int neutras = 0, diccionario = 0, otras = 0;

  for (nodo = estado->origen.primero; nodo; nodo = nodo->siguiente) {
    if (es_fecha(nodo->palabra)) {
      fechas++;
    } else if (es_numero(nodo->palabra)) {
      numeros++;
    } else if (obtener_palabra(&estado->neutros, nodo->palabra)) {
      neutras++;
    } else if (obtener_palabra(&estado->diccionario, nodo->palabra)) {
      diccionario++;
    } else {
      otras++;
    }
  }

  fprintf(out, "Fechas      : %i\n", fechas);
  fprintf(out, "Numeros     : %i\n", numeros);
  fprintf(out, "Neutras     : %i\n", neutras);
  fprintf(out, "Diccionario : %i\n", diccionario);
  fprintf(out, "Otras       : %i\n", otras);
}
