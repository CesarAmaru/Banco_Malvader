#include "banco.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "cliente_data.h"
#include "io.h"

// inicializar o Banco Malvader
void banco_init(Banco *b, const char *arq_cli, const char *arq_mov) {
    b->clientes = NULL; // Começa a função com 0 dados de clientes
    b->tam = 0; // zera o tamanho (numero de clientes) do banco
    b->cap = 0; // zera a capacidade de armazenamento de clientes

    // Faz a cópia dos dados em arq_cli (endereço do arquivo clientes.txt) para b->arq_clientes
    strncpy(b->arq_clientes, arq_cli, sizeof(b->arq_clientes) - 1); // -1 deixa um bite livre
    // Copia os dados do arquivo movimentos.txt para b->arq_mov
    strncpy(b->arq_movs, arq_mov, sizeof(b->arq_movs) - 1);

    b->arq_clientes[sizeof(b->arq_clientes) - 1] = '\0'; // usa o bite livre para adicionar o caractere nulo \0
    b->arq_movs[sizeof(b->arq_movs) - 1 ] = '\0';
}

// limpar memoria alocada para o banco
void banco_free(Banco *b) {
    if (b->clientes) {
        free(b->clientes); // Libera a memória alocada
        b->clientes = NULL; // Apaga o endereço de memória que estava apontando para um endereço vazio
    }
    b->tam = 0;
    b->cap = 0;
}

// adicionar cliente ao banco
int banco_add_cliente(Banco *b, Cliente c) {
    if (b->tam == b->cap) { // verifica se o tamanho da quantidade de clientes já atingiu o limite
        size_t new_cap = (b->cap == 0) ? 4 : b->cap*2; // se sim, realoca mais 4 "espaços" ou dobra o tamanho

        Cliente *temporario = realloc(b->clientes, new_cap*sizeof(Cliente)); // realoca mais memoria para b->clientes

        if (!temporario) {fprintf(stderr,"MEMORIA INSUFICIENTE!"); return 0;}
    }
    b->clientes[b->tam] = c; // Põe o cliente cadastrado na ultima posição disponivel de b->clientes
    b->tam++;
    return 1;
}

// salvar os clientes no arquivo clientes.txt
int banco_salvar(Banco *b) {
    int i;
    FILE *a = fopen(b->arq_clientes, "w"); // abre o arquivo de clientes
    if (a == NULL) { // verifica se o arquivo foi aberto com sucesso
        printf("Erro ao abrir o arquivo!");
        return 0;
    }

    for (i = 0; i < b->tam; i++) {
        Cliente c = b->clientes[i];

        fprintf(a, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%.2f;%d\n",
                c.agencia, c.conta, c.nome, c.cpf, c.data_nasc,
                c.telefone, c.endereco, c.cep, c.numero_casa,
                c.bairro, c.cidade, c.estado, c.senha, c.saldo, c.ativo);
    } // salva os dados no arquivo clientes.txt

    fclose(a); // fecha o arquivo para evitar problemas ao decorrer do código
    printf("Dados salvos com sucesso!");
    return 1;
}

// carregar clientes salvos no arquivo clientes.txt
int banco_carregar(Banco* b) {
    FILE *a = fopen(b->arq_clientes, "r"); // abre o arquivo clientes
    char linha[1024]; // cria um vetor para a quantidade de linhas do arquivo
    int carregados = 0; // Quantos

    if (a == NULL) { // Verifica se o arquivo foi aberto com sucesso
        printf("Arquivo não encontrado. Iniciando banco vazio.\n");
        return 1;
    }



    // Lê linha por linha
    while (fgets(linha, sizeof(linha), a)) {
        Cliente c = {0};
        int ativo_temp;
        linha[strcspn(linha, "\n")] = '\0';

        int campos = sscanf(linha,
            "%7[^;];%15[^;];%99[^;];%14[^;];%10[^;];%19[^;];"
            "%119[^;];%9[^;];%9[^;];%59[^;];%59[^;];"
            "%2[^;];%19[^;];%lf;%d",
            c.agencia, c.conta, c.nome, c.cpf, c.data_nasc, c.telefone,
            c.endereco, c.cep, c.numero_casa, c.bairro,
            c.cidade, c.estado, c.senha, &c.saldo, &ativo_temp); // Percorre cada linha para pegar os dados dos clientes

        if (campos == 15) { // Verifica se a quantidade de dados dos cleintes corresponde com a da Struct
            c.ativo = ativo_temp;
            if (banco_add_cliente(b, c)) { // Carrega os clientes para Banco b
                carregados++;
            } else {
                fprintf(stderr, "Erro ao adicionar cliente durante carregamento\n"); // se houver algum erro
                fclose(a);
                return 0;
            }
        }
    }

    fclose(a); // fecha o arquivo
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

    time_t agora = time(NULL); // cria uma variavel do tipo time_t (da biblioteca time)
    struct  tm *tempo = localtime(&agora); // pega a data com base no sistema

    // Formato: DD-MM-AAAA;CONTA;TIPO;VALOR;SALDO
    fprintf(a, "%02d-%02d-%04d; %s; %s; %.2f; %.2f\n", tempo->tm_mday, tempo->tm_mon + 1, tempo->tm_year + 1900,
        conta, tipo, valor, saldo_novo); // escreve no arquivo movimebntos.txt a data, conta, tipo de movimentação
    //valor e saldo atualizado
}

// buscar cliente por conta
int buscar_por_conta (const Banco *b, const char *conta) {
    int i;
    for (i = 0; i < b->tam; i++) {
        if (strcmp(b->clientes[i].conta, conta) == 0) { // strcmp retorna 0 caso os numeros sejam iguais
            // compara se o número da conta fornecido bate com a conta salva no arquivo .txt
            return i; // retorna a posição em que a conta se encontra em b->clientes
        }
    }
    return -1; // caso não seja encontrado, o valor retornado é -1
}

// buscar cliente por CPF
int buscar_por_cpf (const Banco *b, const char *cpf) {
    int i;
    for (i = 0; i < b->tam; i++) {
        if (strcmp(b->clientes[i].cpf, cpf) == 0) { // verifica se o CPF digitado coincide com o CPF do arquivo .txt
            return i; // retorna o posição da conta em b->clientes
        }
    }
    return -1;
}

// criar conta no Banco Malvader
int banco_criar_conta(Banco *b) {
    Cliente novo = cliente_criar_vazio(); // inicializa um cliente com os campos vazios (função de cliente_data.h)

    printf(" =======================================\n");
    printf("|      ABERTURA DE NOVA CONTA           |\n");
    printf(" =======================================\n");

    // Informaçoes da nova conta
    printf("AGENCIA (formato -> 0001): "); ler_linha(novo.agencia, sizeof(novo.agencia)); // ler agência
    printf("CONTA (formato -> 123456-7): "); ler_linha(novo.conta, sizeof(novo.conta)); // ler conta
    if (buscar_por_conta(b, novo.conta) != -1) { // verifica se a conta já existe
        // -1 é retornado caso nenhuma conta com mesmos digitos for encontrada em clientes.txt
        printf("Essa conta já eaxiste!!");
        return 0;
    }

    printf("NOME COMPLETO: "); ler_linha(novo.nome, sizeof(novo.nome)); // le nome

    printf("CPF (formato -> 123.456.789-00): "); ler_linha(novo.cpf, sizeof(novo.cpf)); // Pegar CPF
    if (buscar_por_conta(b, novo.cpf) != -1) {// verifica se o CPF já existe
        printf("Esse CPF ja foi cadastrado!");
        return 0;
    }
    // Data de nascimento do cliente
    printf("DATA DE NASCIMENTO (formato -> DD-MM-AAAA): "); ler_linha(novo.data_nasc, sizeof(novo.data_nasc));
    // número de telefone
    printf("TELEFONE (formato -> 6134567890"); ler_linha(novo.telefone, sizeof(novo.telefone));

    // Pegar endereço do cliente
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

    novo.saldo = 0; // conta criada com zerado
    novo.ativo = 1; // marca a conta como ativa

    // Adiciona o cliente (vai executar a função e só depois fazer a verificação)
    if (!banco_add_cliente(b, novo)) {
        printf("\nERRO AO TENTAR ADICIONAR CLIENTE!\n");
        return 0;
    }

    if (!banco_salvar(b)) { // salva a conta no arquivo clientes.txt
        printf("\nErro ao salvar dados!\n");
        return 0;
    }

    printf("\nConta criada com sucesso!\n");
    printf("Agência: %s | Conta: %s\n", novo.agencia, novo.conta);

    return 1;
}

// consultar dados da conta do cliente
int banco_consultar(const Banco *b) {
    int pos;
    char conta[16];
    printf(" =======================================\n");
    printf("|             CONSULTAR CONTA            |\n");
    printf(" =======================================\n");

    printf("Digite sua conta: "); ler_linha(conta, sizeof(conta));

    pos = buscar_por_conta(b, conta);
    if (pos == -1) {
        printf("CONTA INVALIDA!\n");
        return 0;
    }

    printf(" =======================================\n");
    cliente_impr(&b->clientes[pos]);

    return 1;
}

// encerrar conta
int banco_encerrar_conta(Banco *b) {
    char conta[16], senha[20]; // receber a conta e a senha
    int pos;
    Cliente *c;
    printf(" =======================================\n");
    printf("|             ENCERRAR CONTA            |\n");
    printf(" =======================================\n");
    printf("Digite sua conta: "); ler_linha(conta, sizeof(conta));

    pos = buscar_por_conta(b, conta);// recebe a posição da conta no arquivo clientes.txt
    if (pos == -1) {
        printf("CONTA INEXISTENTE!\n");
        return 0;
    }

    c = &b->clientes[pos];
    if (!c->ativo) {
        printf("Conta ja encerrada!\n");
        return 0;
    }

    printf("Digite sua senha: "); ler_linha(senha, sizeof(senha));
    if (strcmp(c->senha, senha) != 0) {
        printf("SENHA INCORRETA!\n");
        return 0;
    }

    if (c->saldo != 0) {
        printf("NAO EH POSSIVEL ENCERRAR A CONTA!\n");
        printf("Para encerrar a conta eh necessario que o saldo da contra seja R$0,00\nSaldo atual: %.2f\n", c->saldo);
        if (c->saldo > 0)
            printf("Tente fazer um saque!\n");
        else
            printf("Tente fazer um deposito um deposito!\n");

        return 0;
    }

    c->ativo = 0;

    if (!banco_salvar(b)) {
        printf("ERRO AO SALVAR OS DADOS!\n");
        return 0;
    }

    printf("CONTA ENCERRADA COM SUCESSO!\n");

    return 1;
}