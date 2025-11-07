
#ifndef BANCO_MALVADER_CLIENTE_DATA_H
#define BANCO_MALVADER_CLIENTE_DATA_H
#include <string.h>

typedef struct {
    char agencia[8];
    char conta[16];
    char nome[100];
    char cpf[15];
    char data_nasc[11];
    char telefone[20];
    char endereco[120];
    char cep[10];
    char local[60];
    char numero_casa[10];
    char bairro[60];
    char cidade[60];
    char estado[3];
    char senha[20];
    double saldo;
    int ativo;
}Cliente;

typedef struct {
    Cliente *dados;
    size_t tamanho;
    size_t capacidade;
} ListaClientes;

void cliente_ini(Cliente *c);
void cliente_impr(const Cliente *c);
//---------------------------------------

void cliente_ini(Cliente *c) {
    memset(c ,0, sizeof(Cliente));
    c->ativo = 1;
    strcpy(c->estado, "DF");
}

void cliente_impr(const Cliente *c) {
    printf("\n=====DADOS DO CLIENTE=====\n");
    printf("CONTA: %s\n", c->conta);
    printf("AGENCIA: %s\n", c->agencia);
    printf("NOME: %s", c->nome);
    printf("CPF: %s\n", c->cpf);
    printf("SALDO: %.2f\n", c->saldo);
    printf("STATUS: %s\n", c->ativo ? "ATIVO" : "INATIVO");
}




#endif //BANCO_MALVADER_CLIENTE_DATA_H