#include "ordenacao.h"
#include <string.h>

int comparar_por_nome(const Cliente *a, const Cliente *b) {
    return strcasecmp(a->nome, b->nome);
}

int comparar_por_conta(const Cliente *a, const Cliente *b) {
    return strcmp(a->conta, b->conta);
}

void ordenar_por_nome(Cliente *v, int n) {
    quicksort_clientes(v, 0, n - 1, comparar_por_nome);
}

void ordenar_por_conta(Cliente *v, int n) {
    quicksort_clientes(v, 0, n - 1, comparar_por_conta);
}

void quicksort_clientes(Cliente *v, int left, int right, int (*cmp)(const Cliente*, const Cliente*)) {

    int i = left, j = right;
    Cliente pivot = v[(left + right) / 2];

    while (i <= j) {
        while (cmp(&v[i], &pivot) < 0) i++;
        while (cmp(&v[j], &pivot) > 0) j--;


        if (i <= j) {
            Cliente temp = v[i];
            v[i] = v[j];
            v[j] = temp;
            i++;
            j--;
        }
    }

    if (left < j)
        quicksort_clientes(v, left, j, cmp);
    if (i < right)
        quicksort_clientes(v, i, right, cmp);
}