#ifndef BANCO_H
#define BANCO_H

// Estruturas
typedef struct {
    int dd;
    int mm;
    int yyyy;
} Data;

typedef struct {
    int numero;
    char nome[50];
} Agencia;

typedef struct {
    int numeroAgencia;
    int numeroConta;
    Data dataCadastro;
    char nomeCorrentista[100];
    float saldo;
} ContaCorrente;

// Protótipos das funções
int buscarAgencia(Agencia agencias[], int qtdAgencias, int numero);
int buscarConta(ContaCorrente contas[], int qtdContas, int numAgencia, int numConta);

// Operações Agências
void inserirAgencia(Agencia agencias[], int *qtdAgencias);
void inserirVariasAgencias(Agencia agencias[], int *qtdAgencias);
void exibirAgencias(Agencia agencias[], int qtdAgencias, ContaCorrente contas[], int qtdContas);

// Operações Contas
void inserirContaCorrente(ContaCorrente contas[], int *qtdContas, Agencia agencias[], int qtdAgencias);
void imprimirCorrentistasAgencia(ContaCorrente contas[], int qtdContas, Agencia agencias[], int qtdAgencias);

// Operações Financeiras
void realizarDeposito(ContaCorrente contas[], int qtdContas, Agencia agencias[], int qtdAgencias);
void realizarSaque(ContaCorrente contas[], int qtdContas, Agencia agencias[], int qtdAgencias);
void cobrarTaxaAgencia(ContaCorrente contas[], int qtdContas, Agencia agencias[], int qtdAgencias);

// Relatórios
void imprimirDevedores(ContaCorrente contas[], int qtdContas, Agencia agencias[], int qtdAgencias);

#endif