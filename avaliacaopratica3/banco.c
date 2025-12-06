#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int numero;
    char nome[50];
    float saldo;
} Conta;

void salvarConta(Conta c) {
    FILE *f = fopen("contas.dat", "ab");
    fwrite(&c, sizeof(Conta), 1, f);
    fclose(f);
}

int carregarContas(Conta **contas) {
    FILE *f = fopen("contas.dat", "rb");
    if (!f) return 0;
    fseek(f, 0, SEEK_END);
    long tamanho = ftell(f) / sizeof(Conta);
    rewind(f);
    *contas = malloc(tamanho * sizeof(Conta));
    fread(*contas, sizeof(Conta), tamanho, f);
    fclose(f);
    return tamanho;
}

void atualizarArquivo(Conta *contas, int qtd) {
    FILE *f = fopen("contas.dat", "wb");
    fwrite(contas, sizeof(Conta), qtd, f);
    fclose(f);
}

int buscarConta(Conta *contas, int qtd, int num) {
    for (int i = 0; i < qtd; i++)
        if (contas[i].numero == num)
            return i;
    return -1;
}

int main() {
    Conta *contas = NULL;
    int qtdContas = carregarContas(&contas);

    int opcao;
    while (1) {
        printf("\n===== MENU =====\n");
        printf("1 Criar conta\n");
        printf("2 Ver extrato\n");
        printf("3 Depositar\n");
        printf("4 Sacar\n");
        printf("5 Transferir\n");
        printf("6 Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            contas = realloc(contas, (qtdContas + 1) * sizeof(Conta));
            Conta c;
            printf("Numero da conta: ");
            scanf("%d", &c.numero);
            printf("Nome: ");
            scanf(" %[^\n]", c.nome);
            c.saldo = 0;
            contas[qtdContas] = c;
            qtdContas++;
            salvarConta(c);
            printf("Conta criada.\n");
        }

        else if (opcao == 2) {
            int n;
            printf("Numero da conta: ");
            scanf("%d", &n);
            int idx = buscarConta(contas, qtdContas, n);
            if (idx == -1) printf("Conta inexistente.\n");
            else {
                printf("Numero: %d\n", contas[idx].numero);
                printf("Nome: %s\n", contas[idx].nome);
                printf("Saldo: %.2f\n", contas[idx].saldo);
            }
        }

        else if (opcao == 3) {
            int n;
            float v;
            printf("Numero da conta: ");
            scanf("%d", &n);
            int idx = buscarConta(contas, qtdContas, n);
            if (idx == -1) printf("Conta inexistente.\n");
            else {
                printf("Valor: ");
                scanf("%f", &v);
                contas[idx].saldo += v;
                atualizarArquivo(contas, qtdContas);
                printf("Deposito concluido.\n");
            }
        }

        else if (opcao == 4) {
            int n;
            float v;
            printf("Numero da conta: ");
            scanf("%d", &n);
            int idx = buscarConta(contas, qtdContas, n);
            if (idx == -1) printf("Conta inexistente.\n");
            else {
                printf("Valor: ");
                scanf("%f", &v);
                if (contas[idx].saldo < v) {
                    printf("Saldo insuficiente.\n");
                } else {
                    contas[idx].saldo -= v;
                    atualizarArquivo(contas, qtdContas);
                    printf("Saque concluido.\n");
                }
            }
        }

        else if (opcao == 5) {
            int o, d;
            float v;
            printf("Conta origem: ");
            scanf("%d", &o);
            printf("Conta destino: ");
            scanf("%d", &d);
            printf("Valor: ");
            scanf("%f", &v);

            int idxO = buscarConta(contas, qtdContas, o);
            int idxD = buscarConta(contas, qtdContas, d);

            if (idxO == -1 || idxD == -1) printf("Conta invalida.\n");
            else if (contas[idxO].saldo < v) printf("Saldo insuficiente.\n");
            else {
                contas[idxO].saldo -= v;
                contas[idxD].saldo += v;
                atualizarArquivo(contas, qtdContas);
                printf("Transferencia concluida.\n");
            }
        }

        else if (opcao == 6) break;
    }

    free(contas);
    return 0;
}
