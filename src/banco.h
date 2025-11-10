

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

void banco_init(Banco *b, const char *arq_cli, const char * arq_mov);
void banco_salvar(Banco *b);
void banco_carregar(Banco *b);
void banco_add_cliente(Banco *b, Cliente c);
void banco_free(Banco *b);



// ----------------



#endif //BANCO_MALVADER_BANCO_H