
#ifndef BANCO_MALVADER_BANCO_H
#define BANCO_MALVADER_BANCO_H
#include "cliente_data.h"
#include <stdlib.h>
#include <time.h>

/**
 * @brief Estrutura principal do sistema bancario.
 *
 * Armazena todos os clientes carregados em memoria, capacidade interna de
 *  armazenamento e os nomes dos arquivos fisicos usados para persistencia.
 */
typedef struct {
    Cliente *clientes;              /** < Vetor dinâmico de clientes cadastrados. */
    size_t tam;                     /** < Quantidade atual de clientes. */
    size_t cap;                     /** < Capacidade maxima atual do vetor. */
    char arq_clientes[100];         /** < Caminho do arquivo de clientes. */
    char arq_movs[100];             /** < Caminho do arquivo de movimentacoes. */
} Banco;                            /** < Nome da struct. */

// -----------------------------------------------


// ======================================================================
// FUNÇoES PRINCIPAIS DO BANCO

/**
 * @brief Inicializa a estrutura do banco.
 *
 * Configura os nomes dos arquivos que serao utilizados e
 * zera os dados internos.
 *
 * @param b Ponteiro para a estrutura Banco.
 * @param arq_cli Caminho do arquivo de clientes.
 * @param arq_mov Caminho do arquivo de movimentaçoes.
 */
void banco_init(Banco *b, const char *arq_cli, const char * arq_mov);

/**
 * @brief Salva todos os clientes do banco no arquivo.
 *
 * Escreve todos os dados cadastrados no arquivo definido em banco_init().
 *
 * @param b Ponteiro para a estrutura Banco.
 * @return 1 caso salvo com sucesso, 0 caso contrario.
 */
int banco_salvar(Banco *b);

/**
 * @brief Carrega os clientes salvos no arquivo para a memoria.
 *
 * Deve ser chamada logo apos banco_init().
 *
 * @param b Ponteiro para a estrutura Banco.
 * @return 1 se carregou com sucesso, 0 se falhou.
 */
int banco_carregar(Banco *b);

/**
 * @brief Adiciona um cliente à lista interna do banco.
 *
 * Se necessario, realoca memoria para aumentar a capacidade.
 *
 * @param b Ponteiro para o banco.
 * @param c Estrutura Cliente ja preenchida.
 * @return 1 se adicionou, 0 se houve erro de memoria.
 */
int banco_add_cliente(Banco *b, Cliente c);

/**
 * @brief Libera toda a memoria interna do banco.
 *
 * Deve ser chamada ao finalizar a aplicaçao.
 *
 * @param b Ponteiro para a estrutura Banco.
 */
void banco_free(Banco *b);

/**
 * @brief Registra uma movimentaçao no arquivo de historico.
 *
 * Inclui entrada no formato:
 * DD-MM-AAAA;CONTA;TIPO;VALOR;SALDO
 *
 * @param b Ponteiro para a estrutura Banco.
 * @param conta Numero da conta envolvida.
 * @param tipo Tipo da transaçao (ex.: "SAQUE", "DEPOSITO").
 * @param valor Valor movimentado.
 * @param saldo_novo Saldo resultante apos a operaçao.
 * @return 1 registrou, 0 falhou.
 */
int banco_registrar_mov(const Banco *b, const char* conta, const char* tipo, double valor, double saldo_novo);

/**
 * @brief Busca o indice de um cliente pelo numero da conta.
 *
 * @param b Ponteiro para o banco.
 * @param conta Conta a ser buscada.
 * @return indice do cliente no vetor ou -1 se nao encontrado.
 */
int buscar_por_conta (const Banco *b, const char *conta);

/**
 * @brief Busca o indice de um cliente pelo cpf.
 *
 * @param b Ponteiro para o banco.
 * @param cpf Conta a ser buscada.
 * @return indice do cliente no vetor ou -1 se nao encontrado.
 */
int buscar_por_cpf (const Banco *b, const char *cpf);

/**
 * @brief Cria uma nova conta no banco.
 *
 * Solicita dados ao usuario, valida entrada e persiste no arquivo.
 *
 * @param b Ponteiro para o banco.
 * @return 1 se criada com sucesso, 0 se falhou.
 */
int banco_criar_conta(Banco *b);

/**
 * @brief Consulta e exibe os dados de um cliente.
 *
 * @param b Ponteiro para o banco.
 * @return 1 se a conta existe, 0 caso contrario.
 */
int banco_consultar(const Banco *b);

/**
 * @brief Encerra uma conta bancaria.
 *
 * So eh possivel encerrar se o saldo for 0.
 *
 * @param b Ponteiro para o banco.
 * @return 1 se encerrada, 0 se falhou.
 */
int banco_encerrar_conta(Banco *b);

/**
 * @brief Reativa uma conta que estava inativa.
 *
 * @param b Ponteiro para o banco.
 * @return 1 se reativada, 0 se falhou.
 */
int banco_reativar_conta(Banco *b);

/**
 * @brief Realiza um deposito em uma conta existente.
 *
 * @param b Ponteiro para o banco.
 * @param conta Numero da conta.
 * @param valor Valor a ser depositado.
 * @return 1 se sucesso, 0 caso erro.
 */
int banco_depositar(Banco *b, const char *conta, double valor);

/**
 * @brief Realiza um saque em uma conta existente.
 *
 * @param b Ponteiro para o banco.
 * @param conta Numero da conta.
 * @param valor Valor a ser sacado.
 * @return 1 se sucesso, 0 caso erro.
 */
int banco_sacar(Banco *b, const char *conta, double valor);

/**
 * @brief Transfere saldo de uma conta para outra.
 *
 * @param b Ponteiro para o banco.
 * @param origem Conta de origem.
 * @param destino Conta de destino.
 * @param valor Valor a transferir.
 * @return 1 se sucesso, 0 caso erro.
 */
int banco_transferir(Banco *b, const char *origem, const char *destino, double valor);

/**
 * @brief Lista todos os clientes registrados.
 *
 * Chama menu do tipo de listagem.
 * Apenas clientes ativos sao exibidos.
 *
 * @param b Ponteiro para o banco.
 */
void banco_listar_clientes(const Banco *b);

/**
 * @brief Permite alterar dados de um cliente ja cadastrado.
 *
 * @param b Ponteiro para o banco.
 * @return 1 se alterou, 0 caso erro.
 */
int banco_alterar_dados(Banco *b);

/**
 * @brief Menu de seleçao de tipo de listagem.
 *
 * @param banco Ponteiro para o banco.
 */
void banco_menu_listagem(Banco *banco);

/**
 * @brief Interface de deposito via terminal.
 *
 * Solicita ao usuario conta e valor e repassa para banco_depositar().
 *
 * @param b Ponteiro para o banco.
 */
void banco_ui_depositar(Banco *b);

/**
 * @brief Interface de saque via terminal.
 *
 * Solicita ao usuario conta e valor e repassa para banco_sacar().
 *
 * @param b Ponteiro para o banco.
 */
void banco_ui_sacar(Banco *b);

/**
 * @brief Interface de transferência via terminal.
 *
 * Solicita contas de origem, destino e valor e repassa para banco_transferir().
 *
 * @param b Ponteiro para o banco.
 */
void banco_ui_transferir(Banco *b);

#endif //BANCO_MALVADER_BANCO_H