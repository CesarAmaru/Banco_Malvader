#include "ordenacao.h"      // < Arquivo com os protótipos das funções.
#include <string.h>

// Compara dois clientes pelo nome.
int comparar_por_nome(const Cliente *a, const Cliente *b) {
    return strcasecmp(a->nome, b->nome);
}

// Compara dois clientes utilizando o numero da conta.
int comparar_por_conta(const Cliente *a, const Cliente *b) {
    return strcmp(a->conta, b->conta);
}

// Ordena vetor de clientes pelo nome.
void ordenar_por_nome(Cliente *v, int n) {
    quicksort_clientes(v, 0, n - 1, comparar_por_nome);     // Chama função de comparaçao por nome.
}

// Ordena vetor de clientes pelo numero da conta.
void ordenar_por_conta(Cliente *v, int n) {
    quicksort_clientes(v, 0, n - 1, comparar_por_conta);        // Chama funçao de comparaçao por conta.
}


// Funçao de ordenaçao generica usando QuickSort.
void quicksort_clientes(Cliente *v, int left, int right, int (*cmp)(const Cliente*, const Cliente*)) {

    int i = left, j = right;
    Cliente pivot = v[left + (right - left) / 2];

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
        quicksort_clientes(v, left, j, cmp);    // Chama a propria funçao de ordenaçao recursivamente.
    if (i < right)
        quicksort_clientes(v, i, right, cmp);   // Chama a propria funçao de ordenaçao recursivamente.
}
