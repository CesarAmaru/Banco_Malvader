
#ifndef BANCO_MALVADER_CLIENTE_DATA_H
#define BANCO_MALVADER_CLIENTE_DATA_H
#include <string.h>
#include <stdio.h>
// strcut para o tipo Cliente
typedef struct {
    char agencia[8];
    char conta[16];
    char nome[100];
    char cpf[18];
    char data_nasc[15];
    char telefone[20];
    char endereco[120];
    char cep[12];
    char numero_casa[10];
    char bairro[60];
    char cidade[60];
    char estado[5];
    char senha[20];
    double saldo;
    int ativo;
}Cliente;


//---------------------------------------

void cliente_impr(const Cliente *c);
Cliente cliente_criar_vazio(void);



#endif //BANCO_MALVADER_CLIENTE_DATA_H