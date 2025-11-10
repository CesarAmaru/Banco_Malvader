#include "cliente_data.h"
#include <stdio.h>
#include <string.h>

// Criar cliente vazio -> Inicializar todos os campos com zero/string vazia
Cliente cliente_criar_vazio(void) {
    Cliente c = {0};
    strcpy(c.estado, "DF");
    c.saldo = 0.0;
    c.ativo = 1;
    return c;
}

// Implementação: Imprime dados do cliente
void cliente_impr(const Cliente *c) {
    printf("\n=====DADOS DO CLIENTE=====\n");
    printf("CONTA: %s\n", c->conta);
    printf("AGENCIA: %s\n", c->agencia);
    printf("NOME: %s", c->nome);
    printf("CPF: %s\n", c->cpf);
    printf("SALDO: %.2f\n", c->saldo);
    printf("STATUS: %s\n", c->ativo ? "ATIVO" : "INATIVO");
}