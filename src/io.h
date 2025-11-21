
#ifndef BANCO_MALVADER_IO_H
#define BANCO_MALVADER_IO_H

#include <stdlib.h>

/**
 * @brief Le uma string da entrada padrao removendo o '\n' final.
 *
 * Essa funçao eh usada para capturar textos como nome,
 * CPF, endereço e outros campos de entrada.
 *
 * @param buffer Ponteiro onde a string lida sera armazenada.
 * @param tamanho Tamanho maximo do buffer.
 */
void ler_linha(char *buffer, size_t tamanho);

/**
 * @brief Le um valor do tipo double da entrada padrao.
 *
 * Deve ser usada sempre que o usuario precisa digitar
 * valores monetarios (depositos, saques, transferencias).
 *
 * @return O valor lido como double.
 */
double ler_double(void);

/**
 * @brief Le um valor inteiro da entrada padrao.
 *
 * Funçao usada para ler opçoes de menus e valores inteiros simples.
 *
 * @return Numero inteiro informado pelo usuario.
 */
int ler_int(void);

/**
 * @brief Limpa caracteres pendentes no buffer de entrada.
 *
 * Usado para evitar problemas com leituras consecutivas,
 * especialmente apos `scanf` ou leituras parciais.
 */
void limpar_buffer(void);

/**
 * @brief Le numero da conta e valor de forma conjunta.
 *
 * Usada em operaçoes como deposito, saque e transferencia.
 *
 * @param conta Buffer onde o numero da conta sera salvo.
 * @param tam_conta Tamanho maximo do buffer da conta.
 * @param valor Ponteiro onde o valor lido sera armazenado.
 */
void ler_conta_e_valor(char *conta, size_t tam_conta, double *valor);

/**
 * @brief Limpa a tela do usuario.
 *
 * Pode usar system("cls") no Windows ou system("clear") no Linux,
 * dependendo da implementaçao no arquivo correspondente.
 */
void limpar_tela(void);

//------------------------------------------------------

#endif // BANCO_MALVADER_IO_H