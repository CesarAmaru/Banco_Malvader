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


void banco_salvar(Banco *b) {
    int i;
    FILE *a = fopen(b->arq_clientes, "w");
    if (a == NULL) {
        printf("Erro ao abrir o arquivo!");
        exit(1);
    }

    for (i = 0; i < b->tam; i++) {
        Cliente c = b->clientes[i];

        fprintf(a, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%.2f;%d\n",
                c.agencia, c.conta, c.nome, c.cpf, c.data_nasc,
                c.telefone, c.endereco, c.cep, c.local, c.numero_casa,
                c.bairro, c.cidade, c.estado, c.senha, c.saldo, c.ativo);
    }

    fclose(a);
    printf("Dados salvos com sucesso!");
}

void banco_buscar(Banco *b) {

}