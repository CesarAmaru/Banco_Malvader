#ifndef BANCO_MALVADER_ORDENACAO_H
#define BANCO_MALVADER_ORDENACAO_H

#include "cliente_data.h"       // < Arquivo com funçoes e dados relacionados ao cliente.

/**
 * @brief Compara dois clientes pelo nome.
 *
 * Funçao auxiliar usada como callback para algoritmos de ordenaçao.
 * Deve retornar:
 *  - Valor negativo se `a` < `b`
 *  - Valor positivo se `a` > `b`
 *  - Zero se forem iguais
 *
 * @param a Ponteiro para o primeiro cliente.
 * @param b Ponteiro para o segundo cliente.
 * @return Resultado da comparaçao.
 */
int comparar_por_nome(const Cliente *a, const Cliente *b);

/**
 * @brief Compara dois clientes pelo numero da conta.
 *
 * Mesma logica de comparar_por_nome(), mas usando a string da conta.
 *
 * @param a Ponteiro para o primeiro cliente.
 * @param b Ponteiro para o segundo cliente.
 * @return Resultado da comparaçao.
 */
int comparar_por_conta(const Cliente *a, const Cliente *b);

/**
 * @brief Funçao de ordenaçao usando QuickSort.
 *
 * Recebe um vetor de clientes e uma funçao de comparaçao,
 * permitindo ordenar por qualquer criterio (nome, conta, etc).
 *
 * @param v Vetor de clientes.
 * @param left Indice inicial do intervalo da ordenaçao.
 * @param right Indice final do intervalo da ordenaçao.
 * @param cmp Funçao de comparaçao que define o criterio de ordenaçao.
*/
void quicksort_clientes(Cliente *v, int left, int right, int (*cmp)(const Cliente*, const Cliente*));

/**
 * @brief Ordena um vetor de clientes pelo nome.
 *
 * Internamente chama quicksort_clientes usando comparar_por_nome().
 *
 * @param v Vetor de clientes.
 * @param n Quantidade de clientes.
 */
void ordenar_por_nome(Cliente *v, int n);

/**
 * @brief Ordena um vetor de clientes pelo numero da conta.
 *
 * Internamente chama quicksort_clientes usando comparar_por_conta().
 *
 * @param v Vetor de clientes.
 * @param n Quantidade de clientes.
 */
void ordenar_por_conta(Cliente *v, int n);

#endif // BANCO_MALVADER_ORDENACAO_H
