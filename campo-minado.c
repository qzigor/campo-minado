#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct campo{
    int aberto;
    int bomba;
    int perigo;
} Campo;

int menuPrincipal();
void desenharCampo(Campo campo_minado[][10]);
void iniciarCampo(Campo (*campo_minado)[10]);
void adicionarBombas(Campo (*campo_minado)[10]);
void adicionarIndices(Campo (*campo_minado)[10]);


int main(void){

    Campo campo_minado[10][10];
    int opcao;
    int eixo_jogador_x, eixo_jogador_y;
    int valid;


    opcao = menuPrincipal();
    system("cls");
    switch (opcao){
    case 1:

        iniciarCampo(campo_minado);
        adicionarBombas(campo_minado);
        adicionarIndices(campo_minado);

        while(1){
            desenharCampo(campo_minado);
            printf("\n");
            printf("Informe o eixo X: ");  
            valid = 0;
            while(valid == 0){
                valid = scanf("%d",&eixo_jogador_x);
                while(getchar() != '\n');
                if(valid == 0){
                    printf("Por favor, insira um valor entre 1 e 10.\n");
                    printf("Informe o eixo X: ");
                }
            }
            printf("Informe o eixo Y: ");  
            valid = 0;
            while(valid == 0){
                valid = scanf("%d",&eixo_jogador_y);
                while(getchar() != '\n');
                if(valid == 0){
                    printf("Por favor, insira um valor entre 1 e 10.\n");
                    printf("Informe o eixo X: ");
                }
            }
            system("cls");
        } 

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
                printf(" %d ", campo_minado[i][j].perigo);
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

void iniciarCampo(Campo (*campo_minado)[10]){
    int i, j;
    for(i=0; i<10; i++){
            for(j=0; j<10; j++){
                campo_minado[i][j].aberto = 0;
                campo_minado[i][j].bomba = 0;
                campo_minado[i][j].perigo = 0;
            }
        }
}

void adicionarBombas(Campo (*campo_minado)[10]){
    int eixo_bomba_x, eixo_bomba_y;
    int i;
    srand(time(NULL));
    for(i=0; i<10; i++){
        eixo_bomba_x = rand() % 10;
        eixo_bomba_y = rand() % 10;
        campo_minado[eixo_bomba_x][eixo_bomba_y].bomba = 1;
    }
}

void adicionarIndices(Campo (*campo_minado)[10]){
    int i, j;
    for(i=0; i<10; i++){
        for(j=0; j<10; j++){
            if(campo_minado[i][j].bomba == 1){
                if(i+1 <= 9){
                    campo_minado[i+1][j].perigo++;
                }
                if(i-1 >= 0){
                    campo_minado[i-1][j].perigo++;
                }
                if(j+1 <= 9){
                    campo_minado[i][j+1].perigo++;
                }
                if(j-1 >= 0){
                    campo_minado[i][j-1].perigo++;
                }
                if(i-1 >= 0 && j-1 >= 0){
                    campo_minado[i-1][j-1].perigo++;
                }
                if(i-1 >= 0 && j+1 <= 9){
                    campo_minado[i-1][j+1].perigo++;
                }
                if(i+1 <= 9 && j-1 >= 0){
                    campo_minado[i+1][j-1].perigo++;
                }
                if(i+1 <= 9 && j+1 <= 9){
                    campo_minado[i+1][j+1].perigo++;
                }
            }
        }
    }
}


/* Função auxiliar */
void verBombas(Campo campo_minado[][10]){
    int i, j;
    for(i=0; i<20; i++){
        printf("--");
    }
    printf("\n");
    for(i=0; i<10; i++){
        for(j=0; j<10; j++){
            printf("|");
            if(campo_minado[i][j].aberto == 0){
                if(campo_minado[i][j].bomba == 1){
                    printf(" * ");
                }
                else{
                    printf(" %d ", campo_minado[i][j].perigo);
                }
            }
        }
        printf("|");
        printf("\n");
    }
    for(i=0; i<20; i++){
        printf("--");
    }
}
