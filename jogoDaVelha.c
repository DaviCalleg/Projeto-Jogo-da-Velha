#include <stdio.h>
#include <stdlib.h>

//Funções Utilizadas
int selecao_modo();
void tabuleiro();
void prog_rodada();
void contraJogador();
void contraComputador();
void verificacao();


//Variáveis Globais
char mat_tut[3][3] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
char sim_jog;
int rodada = 0;
int verificador_parada = 0;

//Main
int main(){
    int res_mod;

    res_mod = selecao_modo(); //Escolhendo o modo de Jogo


    if (res_mod == 1){
        contraJogador();
    } 
    else if (res_mod == 2){
        contraComputador();
    }

    return 0;
}



//Função para escolher modo de jogo
int selecao_modo (){
    int sel_mod;
    
    printf("Selecione o modo de jogo:\n 1 -> Jogador x Jogador\n 2 -> Jogador x Computador\n");
    scanf("%d", &sel_mod);
    
    while (sel_mod != 1 && sel_mod!=2){
        printf("\nEscolha um modo de jogo existente"); 
        printf("\nSelecione o modo de jogo:\n 1 -> Jogador x Jogador\n 2 -> Jogador x Computador\n");
        scanf("%d", &sel_mod);
    }
    
    return sel_mod;
    
}

//Tabuleiro do Jogo
void tabuleiro(){
    int i, j, contador = 1;
    for (i=0; i<3; i++){
       for (int j=0; j<3; j++){
            if (mat_tut[i][j] == ' '){
                if (j == 2) {
                    printf(" %d", contador );
                } else{
                    printf(" %d |", contador);
                }
            }
            else {
                if (j == 2) {
                    printf(" %c", mat_tut[i][j] );
                } else{
                    printf(" %c |", mat_tut[i][j]);
                }  
            }

            contador ++;
       }
       printf("\n");
    }
    
    
}

 void prog_rodada(){
    int escolha;

    while (1){
        printf("\nEscolha a posicao: ");
        scanf("%d", &escolha);
        if(escolha <= 9 && escolha > 0){
            for (int i=0; i<3; i++){
                for (int j=0; j<3; j++){
                    int linha = (escolha - 1) / 3;
                    int coluna = (escolha - 1) % 3;
                    if (mat_tut[linha][coluna] == ' ') {
                        mat_tut[linha][coluna] = sim_jog;
                    }
                }
            }
            break;
        } 
        else{
            printf("Selecione um espaco valido\n");
            tabuleiro();
        } 
    }

    tabuleiro();
    
 }

//Opcao contra jogador
void contraJogador() {
    tabuleiro();
    for (rodada = 0; rodada < 9; rodada++) {
        if (rodada % 2 == 0) {
            printf("Vez do Jogador 1: ");
            sim_jog = 'X';
        } else {
            printf("Vez do Jogador 2: ");
            sim_jog = 'O';
        }
        prog_rodada();
        verificacao();

        if (verificador_parada) {
            printf("\nJogador %c venceu!\n", sim_jog);
            return;
        }
    }
    printf("\nEmpate!\n");
}
//Opcao contra computador
void contraComputador(){
    printf("\ncontra Computador");
    tabuleiro(); //Apresentando o tutorial para o jogador
}

void verificacao(){
    int verificador = 0;

    //Ganhando na linha
    for (int i=0; i<3; i++){
        verificador = 0;
        for (int j=0; j<3; j++){
            if (mat_tut[i][j] == sim_jog){
                verificador ++;
            }
        }
        if(verificador == 3){
            verificador_parada = 1;
            break;
        }
    }
      
    //Ganhando na coluna
    for (int i=0; i<3; i++){
        verificador = 0;
        for (int j=0; j<3; j++){
            if (mat_tut[j][i] == sim_jog){
                verificador ++;
            }
        }
        if(verificador == 3){
            verificador_parada = 1;
            break;
        }
    }
    
    //Ganhando na diagonal principal
    verificador = 0;
    for (int i = 0; i<3; i++){
        if (mat_tut[i][i] == sim_jog){
            verificador ++;
        }
    }
    if(verificador == 3){
        verificador_parada = 1;
    }

    verificador = 0;
    for (int i = 0; i < 3; i++) {
        if (mat_tut[i][2 - i] == sim_jog) {
            verificador++;
        }
    }
    if (verificador == 3) {
        verificador_parada = 1;
    }
}