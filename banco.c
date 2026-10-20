#include <stdio.h>
#include <string.h>
#include "banco.h"

// Função auxiliar para limpar o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Retorna o índice da agência ou -1 se não encontrar
int buscarAgencia(Agencia agencias[], int qtdAgencias, int numero) {
    for (int i = 0; i < qtdAgencias; i++) {
        if (agencias[i].numero == numero) return i;
    }
    return -1;
}

// Retorna o índice da conta ou -1 se não encontrar
int buscarConta(ContaCorrente contas[], int qtdContas, int numAgencia, int numConta) {
    for (int i = 0; i < qtdContas; i++) {
        if (contas[i].numeroAgencia == numAgencia && contas[i].numeroConta == numConta) return i;
    }
    return -1;
}

// OPERAÇÃO 1
void inserirAgencia(Agencia agencias[], int *qtdAgencias) {
    if (*qtdAgencias >= 10) {
        printf("ERRO: Limite maximo de 10 agencias atingido!\n");
        return;
    }
    
    int numero;
    printf("Digite o numero da agencia: ");
    scanf("%d", &numero);
    
    if (buscarAgencia(agencias, *qtdAgencias, numero) != -1) {
        printf("ERRO: Agencia com numero %d ja existe!\n", numero);
        return;
    }
    
    agencias[*qtdAgencias].numero = numero;
    limparBuffer();
    printf("Digite o nome da agencia: ");
    fgets(agencias[*qtdAgencias].nome, 50, stdin);
    agencias[*qtdAgencias].nome[strcspn(agencias[*qtdAgencias].nome, "\n")] = 0; // Remove \n
    
    (*qtdAgencias)++;
    printf("SUCESSO: Agencia cadastrada!\n");
}

// OPERAÇÃO 2
void inserirVariasAgencias(Agencia agencias[], int *qtdAgencias) {
    int continuar = 1;
    while (continuar && *qtdAgencias < 10) {
        inserirAgencia(agencias, qtdAgencias);
        if (*qtdAgencias < 10) {
            printf("Deseja inserir outra agencia? (1 - Sim, 0 - Nao): ");
            scanf("%d", &continuar);
        } else {
            printf("Limite de agencias atingido!\n");
        }
    }
}

// OPERAÇÃO 3
void exibirAgencias(Agencia agencias[], int qtdAgencias, ContaCorrente contas[], int qtdContas) {
    if (qtdAgencias == 0) {
        printf("Nenhuma agencia cadastrada.\n");
        return;
    }
    printf("\n--- RELAÇÃO DE AGÊNCIAS ---\n");
    for (int i = 0; i < qtdAgencias; i++) {
        int qtdContasAgencia = 0;
        for (int j = 0; j < qtdContas; j++) {
            if (contas[j].numeroAgencia == agencias[i].numero) qtdContasAgencia++;
        }
        printf("Agencia: %d | Nome: %s | Contas cadastradas: %d\n", agencias[i].numero, agencias[i].nome, qtdContasAgencia);
    }
}

// OPERAÇÃO 4
void inserirContaCorrente(ContaCorrente contas[], int *qtdContas, Agencia agencias[], int qtdAgencias) {
    if (*qtdContas >= 1000) {
        printf("ERRO: Limite maximo de 1000 contas atingido!\n");
        return;
    }
    
    int numAgencia;
    printf("Digite o numero da agencia: ");
    scanf("%d", &numAgencia);
    
    int idxAgencia = buscarAgencia(agencias, qtdAgencias, numAgencia);
    if (idxAgencia == -1) {
        printf("ERRO: Agencia nao encontrada!\n");
        return;
    }
    
    printf("Agencia selecionada: %d - %s\n", agencias[idxAgencia].numero, agencias[idxAgencia].nome);
    
    ContaCorrente novaConta;
    novaConta.numeroAgencia = numAgencia;
    
    limparBuffer();
    printf("Digite o nome do correntista: ");
    fgets(novaConta.nomeCorrentista, 100, stdin);
    novaConta.nomeCorrentista[strcspn(novaConta.nomeCorrentista, "\n")] = 0;
    
    printf("Digite a data de cadastro (DD MM YYYY): ");
    scanf("%d %d %d", &novaConta.dataCadastro.dd, &novaConta.dataCadastro.mm, &novaConta.dataCadastro.yyyy);
    
    printf("Digite o saldo inicial: R$ ");
    scanf("%f", &novaConta.saldo);
    
    // Gerar numero da conta incremental para esta agencia
    int maiorConta = 0;
    for (int i = 0; i < *qtdContas; i++) {
        if (contas[i].numeroAgencia == numAgencia && contas[i].numeroConta > maiorConta) {
            maiorConta = contas[i].numeroConta;
        }
    }
    novaConta.numeroConta = maiorConta + 1;
    
    contas[*qtdContas] = novaConta;
    (*qtdContas)++;
    
    printf("SUCESSO: Conta gerada automaticamente com o numero %d\n", novaConta.numeroConta);
}

// OPERAÇÃO 5
void imprimirCorrentistasAgencia(ContaCorrente contas[], int qtdContas, Agencia agencias[], int qtdAgencias) {
    int numAgencia;
    printf("Digite o numero da agencia: ");
    scanf("%d", &numAgencia);
    
    int idxAgencia = buscarAgencia(agencias, qtdAgencias, numAgencia);
    if (idxAgencia == -1) {
        printf("ERRO: Agencia nao encontrada!\n");
        return;
    }
    
    printf("\n--- CONTAS DA AGÊNCIA %d - %s ---\n", agencias[idxAgencia].numero, agencias[idxAgencia].nome);
    int encontrou = 0;
    for (int i = 0; i < qtdContas; i++) {
        if (contas[i].numeroAgencia == numAgencia) {
            printf("Conta: %d | Correntista: %s | Saldo: R$ %.2f\n", 
                   contas[i].numeroConta, contas[i].nomeCorrentista, contas[i].saldo);
            encontrou = 1;
        }
    }
    if (!encontrou) printf("Nenhuma conta registrada nesta agencia.\n");
}

// OPERAÇÃO 6
void realizarDeposito(ContaCorrente contas[], int qtdContas, Agencia agencias[], int qtdAgencias) {
    int numAgencia, numConta;
    printf("Digite o numero da agencia: ");
    scanf("%d", &numAgencia);
    printf("Digite o numero da conta: ");
    scanf("%d", &numConta);
    
    int idxAgencia = buscarAgencia(agencias, qtdAgencias, numAgencia);
    if (idxAgencia == -1) {
        printf("ERRO: Agencia nao encontrada!\n");
        return;
    }
    
    int idxConta = buscarConta(contas, qtdContas, numAgencia, numConta);
    if (idxConta == -1) {
        printf("ERRO: Conta nao encontrada!\n");
        return;
    }
    
    printf("Agencia: %s\n", agencias[idxAgencia].nome);
    float valor;
    printf("Digite o valor do deposito: R$ ");
    scanf("%f", &valor);
    if (valor <= 0) {
        printf("ERRO: Valor de deposito deve ser maior que zero!\n");
        return;
    }
    
    contas[idxConta].saldo += valor;
    printf("SUCESSO: Deposito realizado. Saldo atualizado: R$ %.2f\n", contas[idxConta].saldo);
}

// OPERAÇÃO 7
void realizarSaque(ContaCorrente contas[], int qtdContas, Agencia agencias[], int qtdAgencias) {
    int numAgencia, numConta;
    printf("Digite o numero da agencia: ");
    scanf("%d", &numAgencia);
    printf("Digite o numero da conta: ");
    scanf("%d", &numConta);
    
    int idxAgencia = buscarAgencia(agencias, qtdAgencias, numAgencia);
    if (idxAgencia == -1) {
        printf("ERRO: Agencia nao encontrada!\n");
        return;
    }
    
    int idxConta = buscarConta(contas, qtdContas, numAgencia, numConta);
    if (idxConta == -1) {
        printf("ERRO: Conta nao encontrada!\n");
        return;
    }
    
    printf("Agencia: %s\n", agencias[idxAgencia].nome);
    float valor;
    printf("Digite o valor do saque: R$ ");
    scanf("%f", &valor);
    if (valor <= 0) {
        printf("ERRO: Valor do saque deve ser maior que zero!\n");
        return;
    }
    
    contas[idxConta].saldo -= valor;
    printf("SUCESSO: Saque realizado. Saldo atualizado: R$ %.2f\n", contas[idxConta].saldo);
    
    if (contas[idxConta].saldo < 0) {
        printf("ALERTA: A conta %d entrou em debito (saldo negativo).\n", contas[idxConta].numeroConta);
    }
}

// OPERAÇÃO 8
void cobrarTaxaAgencia(ContaCorrente contas[], int qtdContas, Agencia agencias[], int qtdAgencias) {
    int numAgencia;
    printf("Digite o numero da agencia: ");
    scanf("%d", &numAgencia);
    
    int idxAgencia = buscarAgencia(agencias, qtdAgencias, numAgencia);
    if (idxAgencia == -1) {
        printf("ERRO: Agencia nao encontrada!\n");
        return;
    }
    
    printf("Agencia selecionada: %s\n", agencias[idxAgencia].nome);
    float valor;
    printf("Digite o valor da taxa: R$ ");
    scanf("%f", &valor);
    if (valor <= 0) {
        printf("ERRO: O valor da taxa deve ser maior que zero!\n");
        return;
    }
    
    int cobradas = 0;
    for (int i = 0; i < qtdContas; i++) {
        if (contas[i].numeroAgencia == numAgencia) {
            contas[i].saldo -= valor;
            cobradas++;
        }
    }
    printf("SUCESSO: Taxa cobrada de %d contas da agencia %d.\n", cobradas, numAgencia);
}

// OPERAÇÃO 9
void imprimirDevedores(ContaCorrente contas[], int qtdContas, Agencia agencias[], int qtdAgencias) {
    printf("\n--- CORRENTISTAS EM DÉBITO ---\n");
    int encontrou = 0;
    for (int i = 0; i < qtdContas; i++) {
        if (contas[i].saldo < 0) {
            int idxAgencia = buscarAgencia(agencias, qtdAgencias, contas[i].numeroAgencia);
            printf("Agencia: %d - %s | Conta: %d | Correntista: %s | Saldo: R$ %.2f\n", 
                   agencias[idxAgencia].numero, agencias[idxAgencia].nome, 
                   contas[i].numeroConta, contas[i].nomeCorrentista, contas[i].saldo);
            encontrou = 1;
        }
    }
    if (!encontrou) {
        printf("Nenhum correntista em debito.\n");
    }
}