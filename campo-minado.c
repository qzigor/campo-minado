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
int temBomba(Campo (*campo_minado)[10], int eixo_x, int eixo_y);
void abrirCampos(Campo (*campo_minado)[10], int eixo_x, int eixo_y);

void verCampoMinado(Campo campo_minado[][10]);


int main(void){

    Campo campo_minado[10][10];
    int opcao;
    int eixo_jogador_x = -1, eixo_jogador_y = -1;
    int valid;
    int tem_bomba;

    opcao = menuPrincipal();
    system("cls");
    switch (opcao){
    case 1:

        iniciarCampo(campo_minado);
        adicionarBombas(campo_minado);
        adicionarIndices(campo_minado);

        while(1){
            desenharCampo(campo_minado);
            verCampoMinado(campo_minado);
            printf("\n");
            printf("Informe o eixo X: ");  
            valid = 0;
            while(valid == 0 || eixo_jogador_x <= 0 || eixo_jogador_x > 10){
                valid = scanf("%d", &eixo_jogador_x);
                while(getchar() != '\n');
                if(valid == 0 || eixo_jogador_x <= 0 || eixo_jogador_x > 10){
                    printf("Por favor, insira um valor entre 1 e 10.\n");
                    printf("Informe o eixo X: ");
                }
            }
            eixo_jogador_x--;
            printf("Informe o eixo Y: ");  
            valid = 0;
            while(valid == 0 || eixo_jogador_y<= 0 || eixo_jogador_y > 10){
                valid = scanf("%d", &eixo_jogador_y);
                while(getchar() != '\n');
                if(valid == 0 || eixo_jogador_y <= 0 || eixo_jogador_y > 10){
                    printf("Por favor, insira um valor entre 1 e 10.\n");
                    printf("Informe o eixo Y: ");
                }
            }
            eixo_jogador_y--;
            tem_bomba = temBomba(campo_minado,eixo_jogador_x,eixo_jogador_y);
            if(tem_bomba == 0){
                abrirCampos(campo_minado, eixo_jogador_x, eixo_jogador_y);
                system("cls");
            }
            else{
                printf("Fim do jogo!!");
                break;
            }
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
            if(campo_minado[i][j].aberto == 0){
                printf("   ");
            }
            if(campo_minado[i][j].aberto == 1){
                printf(" %d ", campo_minado[i][j].perigo);
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
    for(i=0; i<12; i++){
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

int temBomba(Campo (*campo_minado)[10], int eixo_x, int eixo_y){
    if(campo_minado[eixo_x][eixo_y].bomba == 1){
        return 1;
    }
    else{
        return 0;
    }
}

void abrirCampos(Campo (*campo_minado)[10], int eixo_x, int eixo_y){
    campo_minado[eixo_x][eixo_y].aberto = 1;
    if(campo_minado[eixo_x][eixo_y].perigo != 0){
        return;
    }
    else{
        if(eixo_x+1 <= 9 && campo_minado[eixo_x+1][eixo_y].aberto == 0){
            abrirCampos(campo_minado, eixo_x+1, eixo_y);
        }
        if(eixo_x-1 >= 0 && campo_minado[eixo_x-1][eixo_y].aberto == 0){
            abrirCampos(campo_minado, eixo_x-1, eixo_y);
        }
        if(eixo_y+1 <= 9 && campo_minado[eixo_x][eixo_y+1].aberto == 0){
            abrirCampos(campo_minado, eixo_x, eixo_y+1);
        }
        if(eixo_y-1 >= 0 && campo_minado[eixo_x][eixo_y-1].aberto == 0){
            abrirCampos(campo_minado, eixo_x, eixo_y-1);
        }
        if(eixo_x-1 >= 0 && eixo_y-1 >= 0 && campo_minado[eixo_x-1][eixo_y-1].aberto == 0){
            abrirCampos(campo_minado, eixo_x-1, eixo_y-1);
        }
        if(eixo_x-1 >= 0 && eixo_y+1 <= 9 && campo_minado[eixo_x-1][eixo_y+1].aberto == 0){
            abrirCampos(campo_minado, eixo_x-1, eixo_y+1);
        }
        if(eixo_x+1 <= 9 && eixo_y-1 >= 0 && campo_minado[eixo_x+1][eixo_y-1].aberto == 0){
            abrirCampos(campo_minado, eixo_x+1, eixo_y-1);
        }
        if(eixo_x+1 <= 9 && eixo_y+1 <= 9 && campo_minado[eixo_x+1][eixo_y+1].aberto == 0){
            abrirCampos(campo_minado, eixo_x+1, eixo_y+1);
        }
    }

}


/* Função auxiliar */
void verCampoMinado(Campo campo_minado[][10]){
    int i, j;
    for(i=0; i<20; i++){
        printf("--");
    }
    printf("\n");
    for(i=0; i<10; i++){
        for(j=0; j<10; j++){
            printf("|");
                if(campo_minado[i][j].bomba == 1){
                    printf(" \033[1;31m*\033[0m ");
                }
                else{
                    printf(" %d ", campo_minado[i][j].perigo);
                }
        }
        printf("|");
        printf("\n");
    }
    for(i=0; i<20; i++){
        printf("--");
    }
}
