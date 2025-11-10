
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

void banco_init(Banco *b, const char *arq_cli, const char * arq_mov);
int banco_salvar(Banco *b);
int banco_carregar(Banco *b);
int banco_add_cliente(Banco *b, Cliente c);
void banco_free(Banco *b);
int banco_registrar_mov(const Banco *b, const char* conta, const char* tipo, double valor, double saldo_novo);
int buscar_por_conta (const Banco *b, const char *conta);
int buscar_por_cpf (const Banco *b, const char *conta);
int banco_criar_conta(Banco *b);





#endif //BANCO_MALVADER_BANCO_H