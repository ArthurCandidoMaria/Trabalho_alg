/*
 * TRABALHO DE ALGORITMOS E ESTRUTURAS DE DADOS
 * NOME DO SISTEMA DESENVOLVIDO: Sistema de Agência Bancária (Sistema 3)
 * COMPONENTES: [NOME DO ALUNO 1], [NOME DO ALUNO 2], [NOME DO ALUNO 3]
 * DATA: 20/10/2026
 */

#include <stdio.h>
#include <stdlib.h>
#include "banco.h"

int main() {
    Agencia agencias[10];
    int qtdAgencias = 0;
    
    ContaCorrente contas[1000];
    int qtdContas = 0;
    
    int opcao = -1;
    int acoesExecutadas = 0;
    
    while (opcao != 0) {
        printf("\n---------------- SISTEMA DE AGENCIA BANCARIA ----------------\n");
        printf("0  - SAIR DA APLICACAO\n");
        printf("1  - INSERIR AGENCIA\n");
        printf("2  - INSERIR VARIAS AGENCIAS\n");
        printf("3  - EXIBIR RELACAO DE AGENCIAS\n");
        printf("4  - INSERIR CONTA CORRENTE\n");
        printf("5  - IMPRIMIR RELACAO DE CORRENTISTAS DE UMA AGENCIA\n");
        printf("6  - REALIZAR DEPOSITO\n");
        printf("7  - REALIZAR SAQUE\n");
        printf("8  - COBRAR TAXA DE UMA AGENCIA\n");
        printf("9  - IMPRIMIR TODOS OS CORRENTISTAS COM DEBITO\n");
        printf("10 - SOBRE\n");
        printf("\nDIGITE A OPCAO DESEJADA: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 0:
                printf("\nEncerrando o programa...\n");
                break;
            case 1:
                inserirAgencia(agencias, &qtdAgencias);
                acoesExecutadas++;
                break;
            case 2:
                inserirVariasAgencias(agencias, &qtdAgencias);
                acoesExecutadas++;
                break;
            case 3:
                exibirAgencias(agencias, qtdAgencias, contas, qtdContas);
                acoesExecutadas++;
                break;
            case 4:
                inserirContaCorrente(contas, &qtdContas, agencias, qtdAgencias);
                acoesExecutadas++;
                break;
            case 5:
                imprimirCorrentistasAgencia(contas, qtdContas, agencias, qtdAgencias);
                acoesExecutadas++;
                break;
            case 6:
                realizarDeposito(contas, qtdContas, agencias, qtdAgencias);
                acoesExecutadas++;
                break;
            case 7:
                realizarSaque(contas, qtdContas, agencias, qtdAgencias);
                acoesExecutadas++;
                break;
            case 8:
                cobrarTaxaAgencia(contas, qtdContas, agencias, qtdAgencias);
                acoesExecutadas++;
                break;
            case 9:
                imprimirDevedores(contas, qtdContas, agencias, qtdAgencias);
                acoesExecutadas++;
                break;
            case 10:
                printf("\n--- SOBRE O SISTEMA ---\n");
                printf("Sistema de Agencia Bancaria (Sistema 3) - Trabalho de Algoritmos e Estruturas de Dados\n");
                acoesExecutadas++;
                break;
            default:
                printf("\nERRO: Opcao invalida! Tente novamente.\n");
                break;
        }
    }
    
    printf("\nQuantidade de acoes executadas pelo usuario: %d\n", acoesExecutadas);
    return 0;
}