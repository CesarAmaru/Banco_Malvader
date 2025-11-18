
#ifndef BANCO_MALVADER_IO_H
#define BANCO_MALVADER_IO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "banco.h"
#include "ordenacao.h"

void ler_linha(char *buffer, size_t tamanho);
double ler_double(void);
int ler_int(void);
void limpar_buffer(void);
void ler_conta_e_valor(char *conta, size_t tam_conta, double *valor);
void limpar_tela(void);
void menu_listagem(Banco *banco);

//--------------------------




#endif //BANCO_MALVADER_IO_H