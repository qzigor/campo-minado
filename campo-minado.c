#include<stdio.h>
#include<stdlib.h>

typedef struct campo{
    int aberto;
    int bomba;
    int perigo;
} Campo;

int menuPrincipal();
void desenharCampo(Campo campo_minado[][10]);

int main(void){

    Campo campo_minado[10][10];
    int opcao;
    int i, j;
    opcao = menuPrincipal();

    switch (opcao){
    case 1:
        for(i=0; i<10; i++){
            for(j=0; j<10; j++){
                campo_minado[i][j].aberto = 0;
                campo_minado[i][j].bomba = 0;
                campo_minado[i][j].perigo = 0;
            }
        }
        desenharCampo(campo_minado);
        break;
    case 2:
        exit(0);
        break;
    }
}

int menuPrincipal(){
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

void desenharCampo(Campo campo_minado[][10]){
    int i, j;
    for(i=0; i<20; i++){
        printf("--");
    }
    printf("\n");
    for(i=0; i<10; i++){
        for(j=0; j<10; j++){
            printf("|");
            if(campo_minado[i][j].aberto == 1){
                printf("%d", campo_minado[i][j].perigo);
            }
            else{
                printf(" * ");
            }
        }
        printf("|");
        printf("\n");
    }
    for(i=0; i<20; i++){
        printf("--");
    }
}

