

#ifndef BANCO_MALVADER_BANCO_H
#define BANCO_MALVADER_BANCO_H
#include "cliente_data.h"
#include <stdlib.h>
typedef struct {
    Cliente *clientes;
    size_t tam;
    size_t cap;
    char arq_clientes[100];
    char arq_movs[100];
} Banco;

void baco_init();
void banco_carregar();
void banco_add_cliente();
void banco_salvar();
void banco_free();

// ----------------



#endif //BANCO_MALVADER_BANCO_H