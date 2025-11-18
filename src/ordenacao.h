#ifndef BANCO_MALVADER_ORDENACAO_H
#define BANCO_MALVADER_ORDENACAO_H
#include "cliente_data.h"

int comparar_por_nome(const Cliente *a, const Cliente *b);
int comparar_por_conta(const Cliente *a, const Cliente *b);

void quicksort_clientes(Cliente *v, int left, int right, int (*cmp)(const Cliente*, const Cliente*));

void ordenar_por_nome(Cliente *v, int n);
void ordenar_por_conta(Cliente *v, int n);

#endif //BANCO_MALVADER_ORDENACAO_H
