#ifndef BANCO_MALVADER_CLIENTE_DATA_C
#define BANCO_MALVADER_CLIENTE_DATA_C

#include "cliente_data.h"       // < Arquivo com os protótipos das funções.
#include <stdio.h>
#include <string.h>

// Criar cliente vazio -> Inicializar todos os campos com zero/string vazia.
Cliente cliente_criar_vazio(void) {
    Cliente c = {0};
    strcpy(c.estado, "DF");
    c.saldo = 0.0;
    c.ativo = 1;
    return c;
}

// Imprime dados do cliente.
void cliente_impr(const Cliente *c) {
    printf("\n=====DADOS DO CLIENTE=====\n");
    printf("CONTA: %s\n", c->conta);            // < Imprimir conta.
    printf("AGENCIA: %s\n", c->agencia);        // < Imprimir agencia.
    printf("NOME: %s\n", c->nome);                // < Imprimir nome.
    printf("CPF: %s\n", c->cpf);                // < Imprimir CPF.
    printf("SALDO: %.2f\n", c->saldo);          // < Imprimir saldo.
    printf("STATUS: %s\n", c->ativo ? "ATIVO" : "INATIVO");     // < Imprimir status.
}

#endif //BANCO_MALVADER_CLIENTE_DATA_C