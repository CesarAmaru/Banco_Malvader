
#ifndef BANCO_MALVADER_BANCO_H
#define BANCO_MALVADER_BANCO_H
#include "cliente_data.h"
#include <stdlib.h>
#include <time.h>

typedef struct {
    Cliente *clientes;
    size_t tam;
    size_t cap;
    char arq_clientes[100];
    char arq_movs[100];
} Banco;

// ----------------

void banco_init(Banco *b, const char *arq_cli, const char * arq_mov); // inicializar o Banco Malvader
int banco_salvar(Banco *b); // salvar os clientes no arquivo clientes.txt
int banco_carregar(Banco *b); // carregar clientes salvos no arquivo clientes.txt
int banco_add_cliente(Banco *b, Cliente c);
void banco_free(Banco *b); // limpar memoria alocada para o banco
int banco_registrar_mov(const Banco *b, const char* conta, const char* tipo, double valor, double saldo_novo);
int buscar_por_conta (const Banco *b, const char *conta);
int buscar_por_cpf (const Banco *b, const char *conta);
int banco_criar_conta(Banco *b);
int banco_consultar(const Banco *b);
int banco_encerrar_conta(Banco *b);
int banco_depositar(Banco *b, const char *conta, double valor);
int banco_sacar(Banco *b, const char *conta, double valor);
int banco_transferir(Banco *b, const char *origem, const char *destino, double valor);
void banco_listar_clientes(const Banco *b);
int banco_alterar_dados(Banco *b);




#endif //BANCO_MALVADER_BANCO_H