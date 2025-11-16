
#ifndef BANCO_MALVADER_IO_H
#define BANCO_MALVADER_IO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ler_linha(char *buffer, size_t tamanho);
double ler_double(void);
int ler_int(void);
void limpar_buffer(void);
void ler_conta_e_valor(char *conta, size_t tam_conta, double *valor);

//--------------------------




#endif //BANCO_MALVADER_IO_H