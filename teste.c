#include <stdio.h>
#include <stdbool.h>

// =========================================================================
// DECLARAÇÃO DAS FUNÇÕES (PROTÓTIPOS)
// =========================================================================
void exibirMenu();
void encerrarAplicacao();
void inicializarVetor(int vetor[]);
void exibirVetor(int vetor[]);
void exibirVetorInverso(int vetor[]);
void exibirElementoPosicao(int vetor[], int pos);
void substituirElemento(int vetor[], int pos, int valor);
void exibirMaior(int vetor[]);
void exibirMenor(int vetor[]);
float calcularMedia(int vetor[]);
int contarIntervalo(int vetor[], int ki, int kj);
int posicaoMaiorAPartir(int vetor[], int n);
int posicaoMenorAPartir(int vetor[], int n);
void permutar(int vetor[], int pos1, int pos2);
void copiarVetor(int vetor[], int aux[]);
void restaurarVetor(int vetor[], int aux[]);
void ordenarVetor(int vetor[]);
void sobre();

// =========================================================================
// MAIN
// =========================================================================
int main() {
    int vetorPrincipal[10];
    int vetorBackup[10];
    int opcao = -1;
    int acoesExecutadas = 0;
    bool inicializado = false;
    bool backupCriado = false;

    while (opcao != 0) {
        exibirMenu();
        scanf("%d", &opcao);

        // Validação se o vetor foi inicializado para as opções que dependem dele
        if (opcao > 1 && opcao <= 15 && !inicializado) {
            printf("\n[ERRO] O vetor ainda nao foi inicializado! Execute a opcao 1 primeiro.\n\n");
            continue;
        }

        switch (opcao) {
            case 0:
                encerrarAplicacao();
                printf("Total de acoes executadas na sessao: %d\n", acoesExecutadas);
                break;

            case 1:
                inicializarVetor(vetorPrincipal);
                inicializado = true;
                acoesExecutadas++;
                break;

            case 2:
                exibirVetor(vetorPrincipal);
                acoesExecutadas++;
                break;

            case 3:
                exibirVetorInverso(vetorPrincipal);
                acoesExecutadas++;
                break;

            case 4: {
                int pos;
                do {
                    printf("Informe uma posicao do vetor (0 a 9): ");
                    scanf("%d", &pos);
                } while (pos < 0 || pos > 9);
                exibirElementoPosicao(vetorPrincipal, pos);
                acoesExecutadas++;
                break;
            }

            case 5: {
                int pos, valor;
                printf("Informe o novo valor: ");
                scanf("%d", &valor);
                do {
                    printf("Informe a posicao do vetor (0 a 9) para substituicao: ");
                    scanf("%d", &pos);
                } while (pos < 0 || pos > 9);
                substituirElemento(vetorPrincipal, pos, valor);
                acoesExecutadas++;
                break;
            }

            case 6:
                exibirMaior(vetorPrincipal);
                acoesExecutadas++;
                break;

            case 7:
                exibirMenor(vetorPrincipal);
                acoesExecutadas++;
                break;

            case 8: {
                float media = calcularMedia(vetorPrincipal);
                printf("\nA media dos numeros do vetor e: %.2f\n", media);
                acoesExecutadas++;
                break;
            }

            case 9: {
                int ki, kj;
                printf("Informe o valor limite inferior (Ki): ");
                scanf("%d", &ki);
                printf("Informe o valor limite superior (Kj): ");
                scanf("%d", &kj);
                int qtd = contarIntervalo(vetorPrincipal, ki, kj);
                printf("\nQuantidade de numeros entre %d e %d: %d\n", ki, kj, qtd);
                acoesExecutadas++;
                break;
            }

            case 10: {
                int n;
                do {
                    printf("Informe a posicao N inicial (0 a 9): ");
                    scanf("%d", &n);
                } while (n < 0 || n > 9);
                int posMaior = posicaoMaiorAPartir(vetorPrincipal, n);
                printf("\nA posicao do maior numero a partir do indice %d e: %d\n", n, posMaior);
                acoesExecutadas++;
                break;
            }

            case 11: {
                int n;
                do {
                    printf("Informe a posicao N inicial (0 a 9): ");
                    scanf("%d", &n);
                } while (n < 0 || n > 9);
                int posMenor = posicaoMenorAPartir(vetorPrincipal, n);
                printf("\nA posicao do menor numero a partir do indice %d e: %d\n", n, posMenor);
                acoesExecutadas++;
                break;
            }

            case 12: {
                int p1, p2;
                do {
                    printf("Informe a primeira posicao (0 a 9): ");
                    scanf("%d", &p1);
                    printf("Informe a segunda posicao (0 a 9): ");
                    scanf("%d", &p2);
                } while (p1 < 0 || p1 > 9 || p2 < 0 || p2 > 9);
                permutar(vetorPrincipal, p1, p2);
                acoesExecutadas++;
                break;
            }

            case 13:
                copiarVetor(vetorPrincipal, vetorBackup);
                backupCriado = true;
                acoesExecutadas++;
                break;

            case 14:
                if (backupCriado) {
                    restaurarVetor(vetorPrincipal, vetorBackup);
                    acoesExecutadas++;
                } else {
                    printf("\n[ERRO] Nenhum backup foi criado ainda. Execute a opcao 13 primeiro.\n");
                }
                break;

            case 15:
                ordenarVetor(vetorPrincipal);
                acoesExecutadas++;
                break;

            case 16:
                sobre();
                acoesExecutadas++;
                break;

            default:
                printf("\n[ERRO] Opcao invalida! Tente novamente.\n");
        }
    }

    return 0;
}

// =========================================================================
// IMPLEMENTAÇÃO DAS FUNÇÕES
// =========================================================================

void exibirMenu() {
    printf("\n***********************************************************************************************\n");
    printf("0 - SAIR DA APLICACAO\n");
    printf("1 - INICIALIZAR O VETOR DE 10 POSICOES\n");
    printf("2 - EXIBIR O VETOR COMPLETO\n");
    printf("3 - EXIBIR O VETOR EM ORDEM INVERSA\n");
    printf("4 - EXIBIR O ELEMENTO DE UMA POSICAO DO VETOR\n");
    printf("5 - SUBSTITUIR O ELEMENTO DE UMA POSICAO DO VETOR\n");
    printf("6 - EXIBIR O MAIOR NUMERO DO VETOR E SUA POSICAO\n");
    printf("7 - EXIBIR O MENOR NUMERO DO VETOR E SUA POSICAO\n");
    printf("8 - RETORNAR A MEDIA DOS NUMEROS DO VETOR\n");
    printf("9 - RETORNAR A QUANTIDADE DE NUMEROS DENTRO DE UM INTERVALO KI E KJ\n");
    printf("10 - RETORNAR A POSICAO DO MAIOR NUMERO A PARTIR DE UMA POSICAO N INFORMADA\n");
    printf("11 - RETORNAR A POSICAO DO MENOR NUMERO A PARTIR DE UMA POSICAO N INFORMADA\n");
    printf("12 - PERMUTAR DUAS POSICOES DO VETOR\n");
    printf("13 - CRIAR UMA COPIA DO VETOR\n");
    printf("14 - RESTAURAR A COPIA DO VETOR\n");
    printf("15 - ORDENAR O VETOR\n");
    printf("16 - SOBRE\n");
    printf("DIGITE A OPCAO DESEJADA: ");
}

// OPÇÃO 0
void encerrarAplicacao() {
    printf("\nEncerrando a aplicacao...\n");
}

// OPÇÃO 1
void inicializarVetor(int vetor[]) {
    printf("\n--- Inicializando Vetor ---\n");
    for (int i = 0; i < 10; i++) {
        printf("Informe o valor para a posicao [%d]: ", i);
        scanf("%d", &vetor[i]);
    }
    printf("Vetor inicializado com sucesso!\n");
}

// OPÇÃO 2
void exibirVetor(int vetor[]) {
    printf("\n--- Vetor Completo ---\n[ ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", vetor[i]);
    }
    printf("]\n");
}

// OPÇÃO 3
void exibirVetorInverso(int vetor[]) {
    printf("\n--- Vetor em Ordem Inversa ---\n[ ");
    for (int i = 9; i >= 0; i--) {
        printf("%d ", vetor[i]);
    }
    printf("]\n");
}

// OPÇÃO 4
void exibirElementoPosicao(int vetor[], int pos) {
    printf("\nO elemento na posicao [%d] e: %d\n", pos, vetor[pos]);
}

// OPÇÃO 5
void substituirElemento(int vetor[], int pos, int valor) {
    vetor[pos] = valor;
    printf("\nElemento substituido com sucesso!\n");
}

// OPÇÃO 6
void exibirMaior(int vetor[]) {
    int maior = vetor[0];
    int posicao = 0;
    for (int i = 1; i < 10; i++) {
        if (vetor[i] > maior) {
            maior = vetor[i];
            posicao = i;
        }
    }
    printf("\nO maior numero do vetor e %d, localizado na posicao [%d].\n", maior, posicao);
}

// OPÇÃO 7
void exibirMenor(int vetor[]) {
    int menor = vetor[0];
    int posicao = 0;
    for (int i = 1; i < 10; i++) {
        if (vetor[i] < menor) {
            menor = vetor[i];
            posicao = i;
        }
    }
    printf("\nO menor numero do vetor e %d, localizado na posicao [%d].\n", menor, posicao);
}

// OPÇÃO 8
float calcularMedia(int vetor[]) {
    int soma = 0;
    for (int i = 0; i < 10; i++) {
        soma += vetor[i];
    }
    return (float)soma / 10.0f;
}

// OPÇÃO 9
int contarIntervalo(int vetor[], int ki, int kj) {
    int contador = 0;
    for (int i = 0; i < 10; i++) {
        if (vetor[i] > ki && vetor[i] < kj) {
            contador++;
        }
    }
    return contador;
}

// OPÇÃO 10
int posicaoMaiorAPartir(int vetor[], int n) {
    int maior = vetor[n];
    int posicao = n;
    for (int i = n + 1; i < 10; i++) {
        if (vetor[i] > maior) {
            maior = vetor[i];
            posicao = i;
        }
    }
    return posicao;
}

// OPÇÃO 11
int posicaoMenorAPartir(int vetor[], int n) {
    int menor = vetor[n];
    int posicao = n;
    for (int i = n + 1; i < 10; i++) {
        if (vetor[i] < menor) {
            menor = vetor[i];
            posicao = i;
        }
    }
    return posicao;
}

// OPÇÃO 12
void permutar(int vetor[], int pos1, int pos2) {
    int temp = vetor[pos1];
    vetor[pos1] = vetor[pos2];
    vetor[pos2] = temp;
    printf("\nValores das posicoes %d e %d permutados com sucesso!\n", pos1, pos2);
}

// OPÇÃO 13
void copiarVetor(int vetor[], int aux[]) {
    for (int i = 0; i < 10; i++) {
        aux[i] = vetor[i];
    }
    printf("\nVetor copiado para o backup com sucesso!\n");
}

// OPÇÃO 14
void restaurarVetor(int vetor[], int aux[]) {
    for (int i = 0; i < 10; i++) {
        vetor[i] = aux[i];
    }
    printf("\nVetor restaurado a partir do backup com sucesso!\n");
}

// OPÇÃO 15 (Utilizando as opções 11 e 12 conforme o algoritmo exigido)
void ordenarVetor(int vetor[]) {
    for (int i = 0; i < 10; i++) {
        int posMenor = posicaoMenorAPartir(vetor, i);
        if (posMenor != i) {
            permutar(vetor, i, posMenor);
        }
    }
    printf("\nVetor ordenado em ordem crescente com sucesso!\n");
}

// OPÇÃO 16
void sobre() {
    printf("\n========================================\n");
    printf("               SOBRE\n");
    printf("========================================\n");
    printf("Autores(a): Arthur Candido Maria\n Lucas \n Natã Oliveira");
    printf("Data de Lancamento: Outubro de 2026\n");
    printf("Instituicao: IFES\n");
    printf("========================================\n");
}