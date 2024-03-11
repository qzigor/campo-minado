#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct field{
    int open;
    int bomb;
    int danger;
    int flag;
} Field;

int mainMenu();
void drawField(Field mine_field[][10]);
void startField(Field (*mine_field)[10]);
void addBombs(Field (*mine_field)[10]);
void addIndices(Field (*mine_field)[10]);
int axis();
int isBombs(Field (*mine_field)[10], int eixo_x, int eixo_y);
void openFields(Field (*mine_field)[10], int eixo_x, int eixo_y, int *vitoria);
void addFlag(Field (*mine_field)[10], int eixo_x, int eixo_y);
void removeFlag(Field (*mine_field)[10], int eixo_x, int eixo_y);
void viewBombs(Field mine_field[][10]);


int main(void){

    Field mine_field[10][10];
    int option;
    int axis_player_x = -1, axis_player_y = -1;
    int validator;
    int quantity_for_victory = 0;
    int game = 1;
    int play = 0;

    printf("\nBem-vindo ao jogo Campo Minado.\n");
    option = mainMenu();
    if(option == 2){
        exit('0');
    }

    system("cls");
    while(game == 1){
        startField(mine_field);
        addBombs(mine_field);
        addIndices(mine_field);

        while(1){
            drawField(mine_field);
            printf("\n");
            validator = 0;
            while(validator == 0 || play < 1 || play > 3){
                printf("Qual opcao deseja:\n");
                printf("[1] - abrir um campo.\n");
                printf("[2] - colocar bandeira\n");
                printf("[3] - remover bandeira\n");
                validator = scanf("%d", &play);
                while(getchar() != '\n');
                if(validator == 0 || play < 1 || play > 3){
                    printf("Por favor, selecione uma das 3 opcoes.\n");
                }
            }
            if(play == 1){
                printf("Informe o eixo X: ");  
                axis_player_x = axis();
                printf("Informe o eixo Y: ");  
                axis_player_y = axis();
                if(isBombs(mine_field,axis_player_x,axis_player_y) == 1){
                    system("cls");
                    viewBombs(mine_field);
                    printf("\n");
                    printf("Voce perdeu!!\n");
                    break;
                    
                }
                if(isBombs(mine_field,axis_player_x,axis_player_y) == 0){
                    openFields(mine_field, axis_player_x, axis_player_y, &quantity_for_victory);
                    system("cls");
                }
                if(quantity_for_victory == 88){
                    system("cls");
                    printf("Parabens!!! Voce venceu o jogo.");
                    break;
                }
            }
            if(play == 2){
                printf("Informe o eixo X: ");  
                axis_player_x = axis();
                printf("Informe o eixo Y: ");  
                axis_player_y = axis();
                addFlag(mine_field, axis_player_x, axis_player_y);
                system("cls");
            }
            if(play == 3){
                printf("Informe o eixo X: ");  
                axis_player_x = axis();
                printf("Informe o eixo Y: ");  
                axis_player_y = axis();
                removeFlag(mine_field, axis_player_x, axis_player_y);
                system("cls");
            }         
        } 
        game = mainMenu();
        system("cls");
    }

}

int mainMenu(){
    int validator = 0;
    int option;

    printf("Selecione uma opcao: \n");
    printf("[1] - Novo jogo.\n");
    printf("[2] - Sair do jogo.\n");
    while(validator == 0 || option < 1 || option > 2){
        validator = scanf("%d", &option);
        while(getchar() != '\n');
        if(validator == 0 || option < 1 || option > 2){
            printf("Por favor, digite um numero de uma opcao valida.\n");
        }
    }
    
    return option;
}

void drawField(Field mine_field[][10]){
    int i, j;
    printf("   ");
    for(i=0; i<10; i++){
        printf("  %d ", i+1);
    }
    printf("\n");
    printf("    ");
    for(i=0; i<20; i++){
        printf("--");
    }
    printf("\n");
    for(i=0; i<10; i++){
        if(i+1 == 10){
            printf(" %d ", i+1);
        }
        else{
            printf(" %d  ", i+1);
        }
        for(j=0; j<10; j++){
            printf("|");
            if(mine_field[i][j].open == 0 && mine_field[i][j].flag == 1){
                printf(" ! ");
            }
            if(mine_field[i][j].open == 0 && mine_field[i][j].flag == 0){
                printf("   ");
            }
            if(mine_field[i][j].open == 1){
                printf(" %d ", mine_field[i][j].danger);
            }
        }
        printf("|");
        printf("\n");
    }
    printf("    ");
    for(i=0; i<20; i++){
        printf("--");
    }
}

void startField(Field (*mine_field)[10]){
    int i, j;
    for(i=0; i<10; i++){
            for(j=0; j<10; j++){
                mine_field[i][j].open = 0;
                mine_field[i][j].bomb = 0;
                mine_field[i][j].danger = 0;
                mine_field[i][j].flag = 0;
            }
        }
}

void addBombs(Field (*mine_field)[10]){
    int axis_bomb_x, axis_bomb_y;
    int quantity_bomb = 0;
    srand(time(NULL));
    while(quantity_bomb < 12){
        axis_bomb_x = rand() % 10;
        axis_bomb_y = rand() % 10;
        if(mine_field[axis_bomb_x][axis_bomb_y].bomb == 0){
            mine_field[axis_bomb_x][axis_bomb_y].bomb = 1;
            quantity_bomb++;
        }
    }
}

void addIndices(Field (*mine_field)[10]){
    int i, j;
    for(i=0; i<10; i++){
        for(j=0; j<10; j++){
            if(mine_field[i][j].bomb == 1){
                if(i+1 <= 9){
                    mine_field[i+1][j].danger++;
                }
                if(i-1 >= 0){
                    mine_field[i-1][j].danger++;
                }
                if(j+1 <= 9){
                    mine_field[i][j+1].danger++;
                }
                if(j-1 >= 0){
                    mine_field[i][j-1].danger++;
                }
                if(i-1 >= 0 && j-1 >= 0){
                    mine_field[i-1][j-1].danger++;
                }
                if(i-1 >= 0 && j+1 <= 9){
                    mine_field[i-1][j+1].danger++;
                }
                if(i+1 <= 9 && j-1 >= 0){
                    mine_field[i+1][j-1].danger++;
                }
                if(i+1 <= 9 && j+1 <= 9){
                    mine_field[i+1][j+1].danger++;
                }
            }
        }
    }
}

int axis(){
    int validator = 0;
    int axis_player = 0;
    while(validator == 0 || axis_player <= 0 || axis_player > 10){
        validator = scanf("%d", &axis_player);
        while(getchar() != '\n');
        if(validator == 0 || axis_player <= 0 || axis_player > 10){
            printf("Por favor, insira um valor entre 1 e 10.\n");
        }
    }
    axis_player--;
    return axis_player;
}

int isBombs(Field (*mine_field)[10], int eixo_x, int eixo_y){
    if(mine_field[eixo_x][eixo_y].bomb == 1){
        return 1;
    }
    else{
        return 0;
    }
}

void openFields(Field (*mine_field)[10], int eixo_x, int eixo_y, int *vitoria){
    *vitoria = *vitoria + 1;
    mine_field[eixo_x][eixo_y].open = 1;
    if(mine_field[eixo_x][eixo_y].danger != 0){
        return;
    }
    else{
        if(eixo_x+1 <= 9 && mine_field[eixo_x+1][eixo_y].open == 0){
            openFields(mine_field, eixo_x+1, eixo_y, vitoria);
        }
        if(eixo_x-1 >= 0 && mine_field[eixo_x-1][eixo_y].open == 0){
            openFields(mine_field, eixo_x-1, eixo_y, vitoria);
        }
        if(eixo_y+1 <= 9 && mine_field[eixo_x][eixo_y+1].open == 0){
            openFields(mine_field, eixo_x, eixo_y+1, vitoria);
        }
        if(eixo_y-1 >= 0 && mine_field[eixo_x][eixo_y-1].open == 0){
            openFields(mine_field, eixo_x, eixo_y-1, vitoria);
        }
        if(eixo_x-1 >= 0 && eixo_y-1 >= 0 && mine_field[eixo_x-1][eixo_y-1].open == 0){
            openFields(mine_field, eixo_x-1, eixo_y-1, vitoria);
        }
        if(eixo_x-1 >= 0 && eixo_y+1 <= 9 && mine_field[eixo_x-1][eixo_y+1].open == 0){
            openFields(mine_field, eixo_x-1, eixo_y+1, vitoria);
        }
        if(eixo_x+1 <= 9 && eixo_y-1 >= 0 && mine_field[eixo_x+1][eixo_y-1].open == 0){
            openFields(mine_field, eixo_x+1, eixo_y-1, vitoria);
        }
        if(eixo_x+1 <= 9 && eixo_y+1 <= 9 && mine_field[eixo_x+1][eixo_y+1].open == 0){
            openFields(mine_field, eixo_x+1, eixo_y+1, vitoria);
        }
    }

}

void addFlag(Field (*mine_field)[10], int eixo_x, int eixo_y){
    mine_field[eixo_x][eixo_y].flag = 1;
}

void removeFlag(Field (*mine_field)[10], int eixo_x, int eixo_y){
    mine_field[eixo_x][eixo_y].flag = 0;
}

void viewBombs(Field mine_field[][10]){
    int i, j;
    printf("   ");
    for(i=0; i<10; i++){
        printf("  %d ", i+1);
    }
    printf("\n");
    printf("    ");
    for(i=0; i<20; i++){
        printf("--");
    }
    printf("\n");
    for(i=0; i<10; i++){
        if(i+1 == 10){
            printf(" %d ", i+1);
        }
        else{
            printf(" %d  ", i+1);
        }
        for(j=0; j<10; j++){
            printf("|");
                if(mine_field[i][j].bomb == 1){
                    printf(" \033[1;31m*\033[0m ");
                }
                else{
                    printf("   ");
                }
        }
        printf("|");
        printf("\n");
    }
    printf("    ");
    for(i=0; i<20; i++){
        printf("--");
    }
}
