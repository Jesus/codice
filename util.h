#ifndef _UTIL_H
#define _UTIL_H

typedef struct {
  int dia, mes, anyo;
} fecha_t;

char minuscula(char);

int es_letra(char);
int es_vocal(char);
int es_consonante(char);
int es_digito(char);
int es_delimitador(char);

int es_fecha(char *);
int es_numero(char *);

void cargar_palabras(TLista *, FILE *);

#endif
