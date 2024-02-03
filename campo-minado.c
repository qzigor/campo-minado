#include<stdio.h>
#include<stdlib.h>

int menu_principal();

int main(void){
    int opcao;
    opcao = menu_principal();
    switch (opcao){
    case 1:
        printf("Vamos jogar");
        break;
    case 2:
        printf("Saindo...");
        break;
    }
}

int menu_principal(){
    int valid = 0;
    int opcao;

    printf("\nBem-vindo ao jogo campo minado.\n");
    printf("Selecione uma opcao: \n");
    printf("[1] - Novo jogo.\n");
    printf("[2] - Sair do jogo.\n");
    while(valid == 0){
        valid = scanf("%d", &opcao);
        while(getchar() != '\n');
        if(valid == 0){
            printf("Por favor, digite um numero de uma opcao valida.\n");
        }
    }
    

    return opcao;
}
