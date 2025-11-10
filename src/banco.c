#include "banco.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "io.h"
// inicializar o Banco Malvader
void banco_init(Banco *b, const char *arq_cli, const char *arq_mov) {
    b->clientes = NULL;
    b->tam = 0;
    b->cap = 0;

    strncpy(b->arq_clientes, arq_cli, sizeof(b->arq_clientes) - 1);
    strncpy(b->arq_movs, arq_mov, sizeof(b->arq_movs) - 1);

    b->arq_clientes[sizeof(b->arq_clientes) - 1] = '\0';
    b->arq_movs[sizeof(b->arq_movs) - 1 ] = '\0';
}
// limpar memoria alocada para o banco
void banco_free(Banco *b) {
    if (b->clientes) {
        free(b->clientes);
        b->clientes = NULL;
    }
    b->tam = 0;
    b->cap = 0;
}

// adicionar cliente ao banco
int banco_add_cliente(Banco *b, Cliente c) {
    if (b->tam == b->cap) {
        size_t new_cap = (b->cap == 0) ? 4 : b->cap*2;

        Cliente *temporario = realloc(b->clientes, new_cap*sizeof(Cliente));

        if (!temporario) {fprintf(stderr,"MEMORIA INSUFICIENTE!"); exit(1);}
    }
    b->clientes[b->tam] = c;
    b->tam++;
}

// salvar os clientes no arquivo clientes.txt
int banco_salvar(Banco *b) {
    int i;
    FILE *a = fopen(b->arq_clientes, "w");
    if (a == NULL) {
        printf("Erro ao abrir o arquivo!");
        return 0;
    }

    for (i = 0; i < b->tam; i++) {
        Cliente c = b->clientes[i];

        fprintf(a, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%.2f;%d\n",
                c.agencia, c.conta, c.nome, c.cpf, c.data_nasc,
                c.telefone, c.endereco, c.cep, c.numero_casa,
                c.bairro, c.cidade, c.estado, c.senha, c.saldo, c.ativo);
    }

    fclose(a);
    printf("Dados salvos com sucesso!");
}

// carregar clientes salvos no arquivo clientes.txt
int banco_carregar(Banco* b) {
    FILE* arquivo = fopen(b->arq_clientes, "r");

    if (!arquivo) {
        printf("Arquivo não encontrado. Iniciando banco vazio.\n");
        return 1;
    }

    char linha[1024];
    int carregados = 0;

    // Lê linha por linha
    while (fgets(linha, sizeof(linha), arquivo)) {
        Cliente c = {0};
        int ativo_temp;


        linha[strcspn(linha, "\n")] = '\0';

        int campos = sscanf(linha,
            "%7[^;];%15[^;];%99[^;];%14[^;];%10[^;];%19[^;];"
            "%119[^;];%9[^;];%9[^;];%59[^;];%59[^;];"
            "%2[^;];%19[^;];%lf;%d",
            c.agencia, c.conta, c.nome, c.cpf, c.data_nasc, c.telefone,
            c.endereco, c.cep, c.numero_casa, c.bairro,
            c.cidade, c.estado, c.senha, &c.saldo, &ativo_temp);

        if (campos == 15) {
            c.ativo = ativo_temp;
            if (banco_add_cliente(b, c)) {
                carregados++;
            } else {
                fprintf(stderr, "Erro ao adicionar cliente durante carregamento\n");
                fclose(arquivo);
                return 0;
            }
        }
    }

    fclose(arquivo);
    printf("Carregados %d clientes com sucesso!\n", carregados);
    return 1;
}
// registrar movimentações
int banco_registrar_mov(const Banco* b, const char* conta, const char* tipo, double valor, double saldo_novo) {
    FILE *a = fopen(b->arq_movs, "a");
    if (a == NULL) {
        printf("Erro ao abrir o arquivo!");
        return 0;
    }

    time_t aogra = time(NULL);
    struct  tm *tempo = localtime(&aogra);

    // Formato: DD-MM-AAAA;CONTA;TIPO;VALOR;SALDO
    fprintf(a, "%02d-%02d-%04d; %s; %s; %.2f; %.2f\n", tempo->tm_mday, tempo->tm_mon + 1, tempo->tm_year + 1900,
        conta, tipo, valor, saldo_novo);

}

int buscar_por_conta (const Banco *b, const char *conta) {
    int i;
    for (i = 0; i < b->tam; i++) {
        if (strcmp(b->clientes[i].conta, conta) == 0) {
            return i;
        }
    }
    return -1;
}

int buscar_por_cpf (const Banco *b, const char *cpf) {
    int i;
    for (i = 0; i < b->tam; i++) {
        if (strcmp(b->clientes[i].cpf, cpf) == 0) {
            return i;
        }
    }
    return -1;
}

int banco_criar_conta(Banco *b) {
    Cliente novo = cliente_criar_vazio();

    printf(" =======================================\n");
    printf("|      ABERTURA DE NOVA CONTA           |\n");
    printf(" =======================================\n");
    // Informaçoes da nova conta
    printf("AGENCIA (formato -> 0001): "); ler_linha(novo.agencia, sizeof(novo.agencia));
    printf("CONTA (formato -> 123456-7): "); ler_linha(novo.conta, sizeof(novo.conta));
    if (buscar_por_conta(b, novo.conta) != -1) {
        printf("Essa conta já eaxiste!!");
        return 0;
    }

    printf("NOME COMPLETO: "); ler_linha(novo.nome, sizeof(novo.nome));
    // Pegar CPF
    printf("CPF (formato -> 123.456.789-00): "); ler_linha(novo.cpf, sizeof(novo.cpf));
    if (buscar_por_conta(b, novo.cpf) != -1) {
        printf("Esse CPF ja foi cadastrado!");
        return 0;
    }
    // Data de nascimento do cliente
    printf("DATA DE NASCIMENTO (formato -> DD-MM-AAAA): "); ler_linha(novo.data_nasc, sizeof(novo.data_nasc));
    // número de telefone
    printf("TELEFONE (formato -> 6134567890"); ler_linha(novo.telefone, sizeof(novo.telefone));

    // Pegar endereço
    printf("ESTADO (formato -> sigla): "); ler_linha(novo.estado, sizeof(novo.estado));
    printf("ENDERECO COMPLETO: "); ler_linha(novo.endereco, sizeof(novo.endereco));
    printf("CEP (formato -> 00000-001"); ler_linha(novo.cep, sizeof(novo.cep));
    printf("NUMERO DA CASA: "); ler_linha(novo.numero_casa, sizeof(novo.numero_casa));
    printf("CIDADE: "); ler_linha(novo.cidade, sizeof(novo.cidade));
    printf("BAIRRO: "); ler_linha(novo.bairro, sizeof(novo.bairro));

    // Criar senha para conta
    printf("\n CRIE UMA SENHA (minimo 4 caracteres)\n");
    printf("SENHA: "); ler_linha(novo.senha, sizeof(novo.senha));
    if (strlen(novo.senha) < 4) {
        printf("ERRO! Senha muito curta\n");
        return 0;
    }

    novo.saldo = 0;
    novo.ativo = 1;

    // Adiciona o cliente (vai executar a função e só depois fazer a verificação)
    if (!banco_add_cliente(b, novo)) {
        printf("\nERRO AO TENTAR ADICIONAR CLIENTE!\n");
        return 0;
    }

    if (!banco_salvar(b)) {
        printf("\nERRO AO SALVAR OS DADOS!");
        return 0;
    }

    printf("Conta criada com sucesso");
    printf("Agencia: %s | Conta: %s", novo.agencia, novo.conta);
}
