#ifndef _COMANDOS_H
#define _COMANDOS_H

#include "../lista.h"
#include "../util.h"

#define off 0
#define on  1

typedef struct {
  char nombre_origen[50];
  FILE *fd_origen;

  int estado_neutros;

  TLista diccionario;
  TLista neutros;
  TLista origen;
} estado_t;

void comando_origen(estado_t *, char *);

void comando_diccionario(estado_t *, char *);

void comando_neutro_on(TLista *);
void comando_neutro_off(TLista *);
void comando_neutro_agregar(TLista *, char *);
void comando_neutro_eliminar(TLista *, char *);
void comando_neutro_actualizar(TLista *);

void comando_info_caracteres(estado_t *, FILE *);
void comando_info_palabras(estado_t *, FILE *);

void comando_ranking_caracteres(estado_t *, int);
void comando_ranking_palabras(estado_t *, int);

void comando_buscar(estado_t *, char *);

#endif
