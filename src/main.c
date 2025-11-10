#include <stdio.h>
#include "banco.h"
#include "cliente_data.h"
int main(void) {
    Banco banco;
    banco_init(&banco, "data/clientes.txt", "data/movimentos.txt");
    banco_carregar(&banco);
    banco_free(&banco);

}