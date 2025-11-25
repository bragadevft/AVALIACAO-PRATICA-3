#include <stdio.h>

struct Conta {
        int numero;
        float saldo;
        char nome[50];
    };

int main() {
    
    struct Conta c1;
    int opcao = 0;
    int contas = 0;

    while(opcao != 4){
        printf("\n====== MENU ======");
        printf("\n1. CRIAR CONTA");
        printf("\n2. VER EXTRATO");
        printf("\n3. DEPOSITAR");
        printf("\n4. SAIR");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                printf("\n====== CRIAR CONTA ======\n");
                printf("Digite o numero da conta: ");
                scanf("%d", &c1.numero);
                printf("Digite o nome da conta: ");
                scanf("%s", &c1.nome);
                printf("Digite o saldo inicial: ");
                scanf("%f", &c1.saldo);
                contas = 1;
            break;
            case 2:
                printf("\n====== VER EXTRATO ======\n");
                if(contas){
                    printf("Numero: %d\n", c1.numero);
                    printf("Nome: %s\n", c1.nome);
                    printf("Saldo: %2.f\n", c1.saldo);
                } else {
                    printf("Nenhuma conta cadastrada ainda.");
                }
            break;
            case 3: {
                printf("\n====== DEPOSITO ======\n");
                if(!contas){
                    printf("Nao ha contas. Crie uma.");
                    break;
                }
                int numC;
                float valor;
                printf("Digite o numero da conta: ");
                scanf("%d", &numC);
                if(numC != c1.numero){
                    printf("Conta nao encontrada. Tente novamente.");
                } else {
                    printf("Digite o valor que deseja depositar: ");
                    scanf("%f", &valor);
                } if(valor <= 0){
                    printf("Valor invalido. Tente novamente.");
                } else{
                    c1.saldo += valor;
                    printf("Saldo atual: %2.f", c1.saldo);
                }
                break;
            }
            case 4:
                printf("\nVoce escolheu sair.\n");
            break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }
    }

    return 0;
}