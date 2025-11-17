#include "banco.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "cliente_data.h"
#include "io.h"

// inicializar o Banco Malvader
void banco_init(Banco *b, const char *arq_cli, const char *arq_mov) {
    b->clientes = NULL; // Começa a funçao com 0 dados de clientes
    b->tam = 0; // zera o tamanho (numero de clientes) do banco
    b->cap = 0; // zera a capacidade de armazenamento de clientes

    // Faz a copia dos dados em arq_cli (endereço do arquivo clientes.txt) para b->arq_clientes
    strncpy(b->arq_clientes, arq_cli, sizeof(b->arq_clientes) - 1); // -1 deixa um bite livre
    // Copia os dados do arquivo movimentos.txt para b->arq_mov
    strncpy(b->arq_movs, arq_mov, sizeof(b->arq_movs) - 1);

    b->arq_clientes[sizeof(b->arq_clientes) - 1] = '\0'; // usa o bite livre para adicionar o caractere nulo \0
    b->arq_movs[sizeof(b->arq_movs) - 1 ] = '\0';
}

// limpar memoria alocada para o banco
void banco_free(Banco *b) {
    if (b->clientes) {
        free(b->clientes); // Libera a memoria alocada
        b->clientes = NULL; // Apaga o endereço de memoria que estava apontando para um endereço vazio
    }
    b->tam = 0;
    b->cap = 0;
}

// adicionar cliente ao banco
int banco_add_cliente(Banco *b, Cliente c) {
    if (b->tam == b->cap) { // verifica se o tamanho da quantidade de clientes ja atingiu o limite
        size_t new_cap = (b->cap == 0) ? 4 : b->cap*2; // se sim, realoca mais 4 "espaços" ou dobra o tamanho

        Cliente *temporario = realloc(b->clientes, new_cap*sizeof(Cliente)); // realoca mais memoria para b->clientes

        if (!temporario) {fprintf(stderr,"MEMORIA INSUFICIENTE!"); return 0;}
        b->clientes = temporario;
        b->cap = new_cap;
    }
    b->clientes[b->tam] = c; // Poe o cliente cadastrado na ultima posiçao disponivel de b->clientes
    b->tam++;
    return 1;
}

// salvar os clientes no arquivo clientes.txt
int banco_salvar(Banco *b) {
    size_t i;
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

    fclose(a); // fecha o arquivo para evitar problemas ao decorrer do codigo
    printf("Dados salvos com sucesso!");
    return 1;
}

// carregar clientes salvos no arquivo clientes.txt
int banco_carregar(Banco* b) {
    FILE *a = fopen(b->arq_clientes, "r"); // abre o arquivo clientes
    char linha[1024]; // cria um vetor para a quantidade de linhas do arquivo
    int carregados = 0; // Quantos

    if (a == NULL) { // Verifica se o arquivo foi aberto com sucesso
        printf("Arquivo nao encontrado. Iniciando banco vazio.\n");
        return 1;
    }



    // Le linha por linha
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

        if (campos == 15) { // Verifica se a quantidade de dados dos clientes corresponde com a da Struct
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

// registrar movimentaçoes
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
        conta, tipo, valor, saldo_novo); // escreve no arquivo movimebntos.txt a data, conta, tipo de movimentaçao
    //valor e saldo atualizado
    fclose(a);
    return 1;
}

// buscar cliente por conta
int buscar_por_conta (const Banco *b, const char *conta) {
    size_t i;
    for (i = 0; i < b->tam; i++) {
        if (strcmp(b->clientes[i].conta, conta) == 0) { // strcmp retorna 0 caso os numeros sejam iguais
            // compara se o numero da conta fornecido bate com a conta salva no arquivo .txt
            return i; // retorna a posiçao em que a conta se encontra em b->clientes
        }
    }
    return -1; // caso nao seja encontrado, o valor retornado eh -1
}

// buscar cliente por CPF
int buscar_por_cpf (const Banco *b, const char *cpf) {
    size_t i;
    for (i = 0; i < b->tam; i++) {
        if (strcmp(b->clientes[i].cpf, cpf) == 0) { // verifica se o CPF digitado coincide com o CPF do arquivo .txt
            return i; // retorna o posiçao da conta em b->clientes
        }
    }
    return -1;
}

// criar conta no Banco Malvader
int banco_criar_conta(Banco *b) {
    Cliente novo = cliente_criar_vazio(); // inicializa um cliente com os campos vazios (funçao de cliente_data.h)

    // Informaçoes da nova conta
    printf("AGENCIA (formato -> 0001): "); ler_linha(novo.agencia, sizeof(novo.agencia)); // ler agencia
    printf("CONTA (formato -> 123456-7): "); ler_linha(novo.conta, sizeof(novo.conta)); // ler conta
    if (buscar_por_conta(b, novo.conta) != -1) { // verifica se a conta ja existe
        // -1 eh retornado caso nenhuma conta com mesmos digitos for encontrada em clientes.txt
        printf("Essa conta ja eaxiste!!");
        return 0;
    }

    printf("NOME COMPLETO: "); ler_linha(novo.nome, sizeof(novo.nome)); // le nome

    printf("CPF (formato -> 123.456.789-00): "); ler_linha(novo.cpf, sizeof(novo.cpf)); // Pegar CPF
    if (buscar_por_conta(b, novo.cpf) != -1) {// verifica se o CPF ja existe
        printf("Esse CPF ja foi cadastrado!");
        return 0;
    }
    // Data de nascimento do cliente
    printf("DATA DE NASCIMENTO (formato -> DD-MM-AAAA): "); ler_linha(novo.data_nasc, sizeof(novo.data_nasc));
    // numero de telefone
    printf("TELEFONE (formato -> 6134567890): "); ler_linha(novo.telefone, sizeof(novo.telefone));

    // Pegar endereço do cliente
    printf("ESTADO (formato -> sigla): "); ler_linha(novo.estado, sizeof(novo.estado));
    printf("ENDERECO COMPLETO: "); ler_linha(novo.endereco, sizeof(novo.endereco));
    printf("CEP (formato -> 00000-001): "); ler_linha(novo.cep, sizeof(novo.cep));
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

    // Adiciona o cliente (vai executar a funçao e so depois fazer a verificaçao)
    if (!banco_add_cliente(b, novo)) {
        printf("\nERRO AO TENTAR ADICIONAR CLIENTE!\n");
        return 0;
    }

    if (!banco_salvar(b)) { // salva a conta no arquivo clientes.txt
        printf("\nErro ao salvar dados!\n");
        return 0;
    }

    printf("\nConta criada com sucesso!\n");
    printf("Agencia: %s | Conta: %s\n", novo.agencia, novo.conta);

    return 1;
}

// consultar dados da conta do cliente
int banco_consultar(const Banco *b) {
    int pos; //posicao da conta no b->clientes
    char conta[16];
    printf(" =======================================\n");
    printf("|             CONSULTAR CONTA            |\n");
    printf(" =======================================\n");

    printf("Digite sua conta: "); ler_linha(conta, sizeof(conta)); //pegar conta

    pos = buscar_por_conta(b, conta); //buscar conta. Retorna a posicao da conta
    if (pos == -1) { // verifica se a conta esta correta
        printf("CONTA INVALIDA!\n");
        return 0;
    }

    printf(" =======================================\n");
    cliente_impr(&b->clientes[pos]);// imprimir os dados do cliente

    return 1;
}

// encerrar conta
int banco_encerrar_conta(Banco *b) {
    char conta[16], senha[20]; // receber a conta e a senha
    int pos;
    Cliente *temporario;
    printf(" =======================================\n");
    printf("|             ENCERRAR CONTA            |\n");
    printf(" =======================================\n");
    printf("\nDigite sua conta: "); ler_linha(conta, sizeof(conta));

    pos = buscar_por_conta(b, conta);// recebe a posiçao da conta no arquivo clientes.txt
    if (pos == -1) {
        printf("CONTA INEXISTENTE!\n");
        return 0;
    }

    temporario = &b->clientes[pos];
    if (!temporario->ativo) {
        printf("CONTA ENCERRADA\n"); //verifica se a conta ja esta encerrada
        return 0;
    }

    printf("Digite sua senha: "); ler_linha(senha, sizeof(senha)); // autenticacao
    if (strcmp(temporario->senha, senha) != 0) {
        printf("SENHA INCORRETA!\n");
        return 0;
    }

        //verifica o saldo antes de encerrar. O saldo deve ser 0
    if (temporario->saldo != 0) {
        printf("NAO EH POSSIVEL ENCERRAR A CONTA!\n");
        printf("Para encerrar a conta eh necessario que o saldo da contra seja R$0,00\nSaldo atual: %.2f\n", temporario->saldo);
        if (temporario->saldo > 0)
            printf("Tente fazer um saque!\n");
        else
            printf("Tente fazer um deposito um deposito!\n");

        return 0;
    }

    temporario->ativo = 0;

    if (!banco_salvar(b)) { //salva a alteracao
        printf("ERRO AO SALVAR OS DADOS!\n");
        return 0;
    }

    printf("CONTA ENCERRADA COM SUCESSO!\n");

    return 1;
}

// Realizar Depoisito em conta existente (emite um aviso caso a conta nao seja encontrada).
int banco_depositar(Banco *b, const char *conta, double valor) {
    char senha[20];

    if (valor <= 0) { // verifica se o valor eh um valor valido para a operacao
        printf("Valor invalido!\n");
        return 0;
    }

    // validacao da conta
    int idx = buscar_por_conta(b, conta);
    if (idx == -1) {
        printf("Conta nao encontrada!\n");
        return 0;
    }

    if (!b->clientes[idx].ativo) {
        printf("Conta esta encerrada!\n");
        return 0;
    }

    printf("\nDigite sua senha: "); ler_linha(senha, sizeof(senha));
    if (strcmp(b->clientes[idx].senha, senha) != 0) {
        printf("SENHA INCORRETA!\n");
        return 0;
    }

    //realizar transacao
    b->clientes[idx].saldo += valor;
    if (!banco_registrar_mov(b, conta, "DEPOSITO", valor, b->clientes[idx].saldo)) {
        printf("NAO FOI POSSIVEL REGISTRAR A TRANSACAO");
        return 0;
    }


    if (!banco_salvar(b)) {
        printf("NAO FOI POSSIVEL SALVAR");
        return 0;
    }


    printf("Deposito de R$ %.2f realizado com sucesso!\n", valor);
    return 1;
}

// Realizar Saque em conta existente.
int banco_sacar(Banco *b, const char *conta, double valor) {
    char senha[20];

    if (valor <= 0) { // confere se o valor eh valido
        printf("Valor invalido!\n");
        return 0;
    }
    //validar conta
    int idx = buscar_por_conta(b, conta);
    if (idx == -1) {
        printf("Conta nao encontrada!\n");
        return 0;
    }

    if (!b->clientes[idx].ativo) {
        printf("Conta esta encerrada!\n");
        return 0;
    }

    printf("\nDigite sua senha: "); ler_linha(senha, sizeof(senha));
    if (strcmp(b->clientes[idx].senha, senha) != 0) {
        printf("SENHA INCORRETA!\n");
        return 0;
    }
    //confere se o cliente possui o valor para ser sacado
    if (b->clientes[idx].saldo < valor) {
        printf("Saldo insuficiente!\n");
        return 0;
    }

    b->clientes[idx].saldo -= valor;

    if (!banco_registrar_mov(b, conta, "SAQUE", valor, b->clientes[idx].saldo))
        return 0;

    if (!banco_salvar(b))
        return 0;

    printf("Saque de R$ %.2f realizado com sucesso!\n", valor);
    return 1;
}

// Transferir saldo disponivel em uma conta existente para outra conta existente.
int banco_transferir(Banco *b, const char *origem, const char *destino, double valor) {
    char senha[20];
    if (valor <= 0) {
        printf("Valor invalido!\n");
        return 0;
    }
    // verificacao das contas origem e destino
    int idxOrigem = buscar_por_conta(b, origem);
    int idxDestino = buscar_por_conta(b, destino);

    if (idxOrigem == -1 || idxDestino == -1) {
        printf("Conta de origem ou destino nao encontrada!\n");
        return 0;
    }
    // verificar se nao esta transferindo para si mesmo
    if (idxOrigem == idxDestino) {
        printf("Transferencia para mesma contas invalida!");
        return 0;
    }

    printf("Digite sua senha: ");
    ler_linha(senha, sizeof(senha));
    if (strcmp(b->clientes[idxOrigem].senha, senha) != 0) {
        printf("SENHA INCORRETA\n");
        return 0;
    }
    //confere se o o cliente possui saldo para fazer a operacao
    if (b->clientes[idxOrigem].saldo < valor) {
        printf("Saldo insuficiente!\n");
        return 0;
    }

    // Atualizar os saldos das contas envolvidas na transaçao.
    b->clientes[idxOrigem].saldo -= valor;
    b->clientes[idxDestino].saldo += valor;

    // Registrar ambas as movimentacoes das contas.
    banco_registrar_mov(b, origem, "TRANSFERENCIA SAiDA", valor, b->clientes[idxOrigem].saldo);
    banco_registrar_mov(b, destino, "TRANSFERENCIA ENTRADA", valor, b->clientes[idxDestino].saldo);

    if (!banco_salvar(b)) { //salva a alteracao
        printf("ERRO AO SALVAR OS DADOS!\n");
        return 0;
    }

    printf("Transferencia de R$ %.2f realizada com sucesso!\n", valor);
    return 1;
}

// Realizar a Listagem dos Clientes cadastrados.
void banco_listar_clientes(const Banco *b) {
    if (b->tam == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    printf("=============================================\n");
    printf("| %-20s | %-10s | %-10s |\n", "Nome", "Conta", "Saldo");
    printf("=============================================\n");

    for (size_t i = 0; i < b->tam; i++) {
        if (b->clientes[i].ativo)
            printf("| %-20s | %-10s | R$ %-8.2f |\n",
                   b->clientes[i].nome, b->clientes[i].conta, b->clientes[i].saldo);
    }
    printf("=============================================\n");
}

// alterar dados de cliente
int banco_alterar_dados(Banco *b) {
    char conta[16], senha[20], buffer[250]; //buffer temporario para pegar as novas informacoes
    int pos;
    Cliente *temporario;

    printf(" =======================================\n");
    printf("|             ALTERAR DADOS             |\n");
    printf(" =======================================\n");

    printf("\nDigite sua conta: ");
    ler_linha(conta, sizeof(conta));

    pos = buscar_por_conta(b, conta);
    if (pos == -1) {
        printf("CONTA INEXISTENTE!\n");
        return 0;
    }

    temporario = &b->clientes[pos];

    if (temporario->ativo == 0) {
        printf("CONTA ENCERRADA\n");
        return 0;
    }

    printf("Digite sua senha: ");
    ler_linha(senha, sizeof(senha));
    if (strcmp(temporario->senha, senha) != 0) {
        printf("SENHA INCORRETA\n");
        return 0;
    }

    printf("\n--- DADOS ATUAIS ---\n");
    cliente_impr(temporario);

    printf("\n--- ALTERAR DADOS ---\n");
    printf("-> Pressione enter para manter a informacao <-\n\n");

    // Nome
    printf("NOME {%s}: ", temporario->nome);
    ler_linha(buffer, sizeof(buffer));
    if (strlen(buffer) > 0)
        strncpy(temporario->nome, buffer, sizeof(temporario->nome) - 1);

    // Telefone
    printf("TELEFONE {%s}: ", temporario->telefone);
    ler_linha(buffer, sizeof(buffer));
    if (strlen(buffer) > 0)
        strncpy(temporario->telefone, buffer, sizeof(temporario->telefone) - 1);

    // Endereço
    printf("ENDERECO {%s}: ", temporario->endereco);
    ler_linha(buffer, sizeof(buffer));
    if (strlen(buffer) > 0)
        strncpy(temporario->endereco, buffer, sizeof(temporario->endereco) - 1);

    // Numero da casa
    printf("NUMERO {%s}: ", temporario->numero_casa);
    ler_linha(buffer, sizeof(buffer));
    if (strlen(buffer) > 0)
        strncpy(temporario->numero_casa, buffer, sizeof(temporario->numero_casa) - 1);

    // Bairro
    printf("BAIRRO {%s}: ", temporario->bairro);
    ler_linha(buffer, sizeof(buffer));
    if (strlen(buffer) > 0)
        strncpy(temporario->bairro, buffer, sizeof(temporario->bairro) - 1);

    // Cidade
    printf("CIDADE {%s}: ", temporario->cidade);
    ler_linha(buffer, sizeof(buffer));
    if (strlen(buffer) > 0)
        strncpy(temporario->cidade, buffer, sizeof(temporario->cidade) - 1);

    // CEP
    printf("CEP {%s}: ", temporario->cep);
    ler_linha(buffer, sizeof(buffer));
    if (strlen(buffer) > 0)
        strncpy(temporario->cep, buffer, sizeof(temporario->cep) - 1);

    // Senha
    printf("\nAlterar senha? (s/n): ");
    ler_linha(buffer, sizeof(buffer));
    if (buffer[0] == 's' || buffer[0] == 'S') {
        printf("Nova senha: ");
        ler_linha(buffer, sizeof(buffer));
        if (strlen(buffer) >= 4) {
            strncpy(temporario->senha, buffer, sizeof(temporario->senha) - 1);
            printf("Senha alterada!\n");
        } else {
            printf("Senha muito curta. Mantendo senha atual.\n");
        }
    }

    // Salvar alteraçooes
    if (!banco_salvar(b)) {
        printf("Erro ao salvar alteracoes!\n");
        return 0;
    }

    printf("\nDados alterados com sucesso!\n");
    return 1;
}