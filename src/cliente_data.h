
#ifndef BANCO_MALVADER_CLIENTE_DATA_H
#define BANCO_MALVADER_CLIENTE_DATA_H
#include <string.h>
#include <stdio.h>

/**
 * @brief Estrutura que representa um cliente cadastrado no sistema bancario.
 *
 * Armazena todos os dados pessoais e bancarios do cliente,
 * incluindo saldo e status da conta (ativa ou encerrada).
 */
typedef struct {
    char agencia[8];                    /** < Numero da agência (ex.: 0001). */
    char conta[16];                     /** < Numero da conta (ex.: 123456-7). */
    char nome[100];                     /** < Nome completo do cliente. */
    char cpf[18];                       /** < CPF com mascara (ex.: 123.456.789-00). */
    char data_nasc[15];                 /** < Data de nascimento (ex.: 01-01-2000). */
    char telefone[20];                  /** < Telefone para contato. */
    char endereco[120];                 /** < Endereço completo. */
    char cep[12];                       /** < CEP do endereço. */
    char numero_casa[10];               /** < Numero do endereço. */
    char bairro[60];                    /** < Bairro. */
    char cidade[60];                    /** < Cidade. */
    char estado[5];                     /** < Estado (UF). */
    char senha[20];                     /** < Senha para acesso à conta. */
    double saldo;                       /** < Saldo disponivel na conta. */
    int ativo;                          /** < 1 = conta ativa, 0 = conta encerrada. */
}Cliente;

/**
 * @brief Estrutura generica para armazenar uma lista dinâmica de clientes.
 *
 * Usada internamente para gerenciar vetores que crescem em runtime.
 */
typedef struct {
    Cliente *dados;                 /** < Vetor de clientes. */
    size_t tamanho;                 /** < Quantidade atual de elementos. */
    size_t capacidade;              /** < Capacidade maxima atual do vetor. */
} ListaClientes;

//-------------------------------------------------------------------------------

// ======================================================================
//  FUNÇOES RELACIONADAS AO CLIENTE
// ======================================================================

/**
 * @brief Inicializa uma estrutura Cliente zerando todos os campos.
 *
 * @param c Ponteiro para a estrutura Cliente a ser inicializada.
 */
void cliente_ini(Cliente *c);   // Inicializa uma estrutura Cliente zerando todos os campos.

/**
 * @brief Imprime todos os dados de um cliente na tela.
 *
 * Exibe dados cadastrais completos, incluindo saldo e status.
 *
 * @param c Ponteiro para o cliente a ser exibido.
 */
void cliente_impr(const Cliente *c);    // Imprime todos os dados de um cliente na tela.

/**
 * @brief Cria e retorna um cliente vazio ja inicializado.
 *
 * Todos os campos vem zerados ou preenchidos com strings vazias.
 *
 * @return Cliente inicializado vazio.
 */
Cliente cliente_criar_vazio(void);  // Cria e retorna um cliente vazio ja inicializado.

#endif // BANCO_MALVADER_CLIENTE_DATA_H