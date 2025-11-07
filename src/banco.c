#include "banco.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void banco_init(Banco *b, const char *arq_cli, const char * arq_mov) {
    b->clientes = NULL;
    b->tam = 0;
    b->cap = 0;

    strncpy(b->arq_clientes, arq_cli, sizeof(b->arq_clientes) - 1);
    strncpy(b->arq_movs, arq_mov, sizeof(b->arq_movs) - 1);

    b->arq_clientes[sizeof(b->arq_clientes) - 1] = '\0';
    b->arq_movs[sizeof(b->arq_movs) - 1 ] = '\0';
}

void banco_free(Banco *b) {
    if (b->clientes) {
        free(b->clientes);
        b->clientes = NULL;
    }
    b->tam = 0;
    b->cap = 0;
}

void banco_add_cliente(Banco *b, Cliente c) {
    if (b->tam == b->cap) {
        size_t new_cap = (b->cap == 0) ? 4 : b->cap*2;

        Cliente *temporario = realloc(b->clientes, new_cap*sizeof(Cliente));

        if (!temporario) {fprintf(stderr,"MEMORIA INSUFICIENTE!"); exit(1);}
    }
    b->clientes[b->tam] = c;
    b->tam++;
}