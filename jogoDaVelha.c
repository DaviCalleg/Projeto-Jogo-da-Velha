#include <stdio.h>
#include <stdlib.h>

//Funções Utilizadas
int selecao_modo();
void tabuleiro();
void prog_rodada();
void contraJogador();
void contraComputador();
int verificacao();


//Variáveis Globais
int mat_tut[3][3] = {1,2,3,4,5,6,7,8,9};
int sim_jog;
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
    int i, j;
    for (i=0; i<3; i++){
       for (int j=0; j<3; j++){
            if (j == 2) {
                printf(" %d", mat_tut[i][j]);
            } else{
                printf(" %d |", mat_tut[i][j]);
            }
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
                    if(mat_tut[i][j] == escolha){
                        mat_tut[i][j] = sim_jog;
                        if(rodada > 4){
                            verificacao();
                            if(verificacao() == 1){
                                return;
                            }
                        }
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
void contraJogador (){
    tabuleiro(); //Apresentando o tutorial para o jogador
    for (rodada = 0; rodada<= 9; rodada++){
        if(rodada % 2 == 0){
            printf(" Vez do Jogador 1: ");
            sim_jog = 77;
            prog_rodada();
        }
        else{
            printf(" Vez do Jogador 2: ");
            sim_jog = 88;
            prog_rodada();
        } 
    }
    

}

//Opcao contra computador
void contraComputador(){
    printf("\ncontra Computador");
    tabuleiro(); //Apresentando o tutorial para o jogador
}

int verificacao(){
    int verificador = 0;

    //Ganhando na linha
    for (int i=0; i<3; i++){
        verificador = 0;
        for (int j=0; j<3; j++){
            if (mat_tut[i][j] == sim_jog){
                verificador += 1;

            }
        }
        if(verificador == 3){
            verificador_parada = 1;
            return verificador_parada;
        }
    }
      
    //Ganhando na coluna
    for (int i=0; i<3; i++){
        verificador = 0;
        for (int j=0; j<3; j++){
            if (mat_tut[j][i] == sim_jog){
                verificador += 1;
            }
        }
        if(verificador == 3){
            verificador_parada = 1;
            break;
        }
    }
    
    //Ganhando na diagonal
    for (int i = 0; i<3; i++){
        verificador = 0;
        for (int j = 0; j < 3; j++){
            if ( i == j){
                if (mat_tut[i][j] == sim_jog){
                    verificador += 1;
                }
            }
        }
        if(verificador == 3){
            verificador_parada = 1;
            break;
        }
    }
}