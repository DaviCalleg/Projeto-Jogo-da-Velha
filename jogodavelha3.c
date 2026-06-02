#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> //biblioteca para adicionar tempo (Somente para fins visuais)

//Funções Utilizadas
int menu();
void selecao_modo();
void tabuleiro();
void prog_rodada();
void contraJogador();
void contraComputador();
void verificacao();
void reset_tabuleiro();
void pontuacao();
void troca_de_tela();


//Variáveis Globais
char mat_tut[3][3] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
char sim_jog;
int rodada = 0;
int verificador_parada = 0;
int jogadorXcomputador = 0;
int jogadorXjogador=0;
int plc[3] = {0};

//Main
int main(){
   
    srand(time(NULL));

    menu(); 

    return 0;
}

//Menu de escolha
int menu(){
    int sel_men = 0;

    do{
        do{
            printf("\n[1] Jogar\n[2] Pontuação\n[3] Sair\n\n->");

            scanf("%d", &sel_men); 

            troca_de_tela();

        }while (sel_men != 1 && sel_men!=2 && sel_men != 3);
            
        if(sel_men == 1)
            selecao_modo();
        if(sel_men == 2)
            pontuacao();
       
    }while(sel_men != 3);

    printf("\nFim de jogo!\n\n");
}

//Tabuleiro do Jogo
void tabuleiro(){
    int i, j, contador = 1;

    printf("\n\n");

    for (i=0; i<3; i++){
       for (int j=0; j<3; j++){
            if (mat_tut[i][j] == ' '){
                if (j == 2) {
                    printf(" %d", contador);
                } else{
                    printf(" %d |", contador);
                }
            }
            else {
                if (j == 2) {
                    printf(" %c", mat_tut[i][j]);
                } else{
                    printf(" %c |", mat_tut[i][j]);
                }  
            }

            contador ++;
       }
       printf("\n");
    }
    
    
}

//Progressão da Rodada
void prog_rodada(){
    int escolha, escolhalinha, escolhacoluna, ok = 0;
    int verificador = 0,verificadorcomp = 0;

    if (jogadorXjogador){
        while (1){
            printf("\nEscolha a posicao -> ");
            scanf("%d", &escolha);

            troca_de_tela();

                if(escolha <= 9 && escolha > 0){
    
                    int linha = (escolha - 1) / 3;
                    int coluna = (escolha - 1) % 3;
                    if (mat_tut[linha][coluna] == ' ') {
                        mat_tut[linha][coluna] = sim_jog;
                        verificador = 1;
                        
                }
                if (verificador){
                    break;
                } else {
                    printf("\nSelecione um espaco valido");
                    tabuleiro();
                }
            } 
            else{
                printf("\nSelecione um espaco valido");
                tabuleiro();
            } 
        }
    }
    else if (jogadorXcomputador){
        if (rodada % 2 == 0){
            while (1){
                printf("\nEscolha a posicao ->");
                scanf("%d", &escolha);

                troca_de_tela();

                if(escolha <= 9 && escolha > 0){
                    for (int i=0; i<3; i++){
                        for (int j=0; j<3; j++){
                            int linha = (escolha - 1) / 3;
                            int coluna = (escolha - 1) % 3;
                            if (mat_tut[linha][coluna] == ' ') {
                                mat_tut[linha][coluna] = sim_jog;
                                verificador = 1;
                            }
                        }
                    }
                    if (verificador){
                        break;
                    } else {
                        printf("\nSelecione um espaco valido");
                        tabuleiro();
                    }
                } 
                else{
                    printf("\nSelecione um espaco valido");
                    tabuleiro();
                } 
            }
        }
        else {
           
               //Atacando na linha
                for (int i=0; i<3; i++){
                    verificadorcomp = 0;
                    for (int j=0; j<3; j++){
                        if (mat_tut[i][j] == 'o'){
                            verificadorcomp ++;
                        }
                        else{
                            escolhalinha = i;
                            escolhacoluna = j;
                        }
                    }
                    if(verificadorcomp == 2){
                        if(mat_tut[escolhalinha][escolhacoluna] != 'x' && mat_tut[escolhalinha][escolhacoluna] != 'o'){
                             mat_tut[escolhalinha][escolhacoluna] = 'o';
                            return;
                        }
                    }
                }
                
                //Atacando na coluna
                for (int j=0; j<3; j++){
                    verificadorcomp = 0;
                    for (int i=0; i<3; i++){
                        if (mat_tut[i][j] == 'o'){
                            verificadorcomp ++;
                        }
                        else{
                            escolhalinha = i;
                            escolhacoluna = j;
                        }
                    }
                    if(verificadorcomp == 2){
                        if(mat_tut[escolhalinha][escolhacoluna] != 'x' && mat_tut[escolhalinha][escolhacoluna] != 'o'){
                            mat_tut[escolhalinha][escolhacoluna] = 'o';
                            return;
                        }
                    }
                }
                
                //Atacando na diagonal principal
                verificadorcomp = 0;
                for (int i = 0; i<3; i++){
                    if (mat_tut[i][i] == 'o'){
                        verificadorcomp ++;
                    }
                    else{
                        escolhalinha = i;
                        escolhacoluna = i;
                    }
                }
                if(verificadorcomp == 2){
                    if(mat_tut[escolhalinha][escolhacoluna] != 'x' && mat_tut[escolhalinha][escolhacoluna] != 'o'){
                        mat_tut[escolhalinha][escolhacoluna] = 'o';
                        return;
                    }    
                }

                //Atacando na diagonal secundária
                verificadorcomp = 0;
                for (int i = 0; i < 3; i++) {
                    if (mat_tut[i][2 - i] == 'o') {
                        verificadorcomp++;
                    }
                    else{
                        escolhalinha = i;
                        escolhacoluna = 2 - i;

                    }
                }
                if (verificadorcomp == 2) {
                   if(mat_tut[escolhalinha][escolhacoluna] != 'x' && mat_tut[escolhalinha][escolhacoluna] != 'o'){
                        mat_tut[escolhalinha][escolhacoluna] = 'o';
                        return;
                   }    
                }


                //Defendendo na linha
                for (int i=0; i<3; i++){
                    verificadorcomp = 0;
                    for (int j=0; j<3; j++){
                        if (mat_tut[i][j] == 'x'){
                            verificadorcomp ++;
                        }
                        else{
                            escolhalinha = i;
                            escolhacoluna = j;
                        }
                    }
                    if(verificadorcomp == 2){
                        if(mat_tut[escolhalinha][escolhacoluna] != 'x' && mat_tut[escolhalinha][escolhacoluna] != 'o'){
                             mat_tut[escolhalinha][escolhacoluna] = 'o';
                             return;
                        }
                    }
                }
                
                //Defendendo na coluna
                for (int j=0; j<3; j++){
                    verificadorcomp = 0;
                    for (int i=0; i<3; i++){
                        if (mat_tut[i][j] == 'x'){
                            verificadorcomp ++;
                        }
                        else{
                            escolhalinha = i;
                            escolhacoluna = j;
                        }
                    }
                    if(verificadorcomp == 2){
                        if(mat_tut[escolhalinha][escolhacoluna] != 'x' && mat_tut[escolhalinha][escolhacoluna] != 'o'){
                            mat_tut[escolhalinha][escolhacoluna] = 'o';
                            return;
                        }    
                    }
                }
                
                //Defendendo na diagonal principal
                verificadorcomp = 0;
                for (int i = 0; i<3; i++){
                    if (mat_tut[i][i] == 'x'){
                        verificadorcomp ++;
                    }
                    else{
                        escolhalinha = i;
                        escolhacoluna = i;
                    }
                }
                if(verificadorcomp == 2){
                    if(mat_tut[escolhalinha][escolhacoluna] != 'x' && mat_tut[escolhalinha][escolhacoluna] != 'o'){
                        mat_tut[escolhalinha][escolhacoluna] = 'o';
                        return;
                    }    
                }

                //Defendendo na diagonal secundária
                verificadorcomp = 0;
                for (int i = 0; i < 3; i++) {
                    if (mat_tut[i][2 - i] == 'x') {
                        verificadorcomp++;
                    }
                    else{
                        escolhalinha = i;
                        escolhacoluna = 2 - i;

                    }
                }
                if (verificadorcomp == 2) {
                   if(mat_tut[escolhalinha][escolhacoluna] != 'x' && mat_tut[escolhalinha][escolhacoluna] != 'o'){
                        mat_tut[escolhalinha][escolhacoluna] = 'o';
                        return;
                   }    
                }
             
                while(1){
                    escolha = (rand() % 9) + 1;
                    for (int i=0; i<3; i++){
                        for (int j=0; j<3; j++){
                            int linha = (escolha - 1) / 3;
                            int coluna = (escolha - 1) % 3;
                            if (mat_tut[linha][coluna] != 'x' && mat_tut[linha][coluna] != 'o') {
                                mat_tut[linha][coluna] = 'o';
                                verificador = 1;
                            }
                        }
                    }
                    if(verificador) break;
                    else escolha = (rand() % 9) + 1;
                }

        }
    }
}

//Opcao contra jogador
void contraJogador() {
    jogadorXjogador = 1;
    rodada = 0;
    
    for (rodada = 0; rodada < 9; rodada++) {
        if (rodada % 2 == 0) {
            printf("\nVez do Jogador 1: ");
            sim_jog = 'x';
        } else {
            printf("\nVez do Jogador 2: ");
            sim_jog = 'o';
        }
        tabuleiro();
        prog_rodada();
        verificacao();

        if (verificador_parada) {
            printf("\nJogador %c venceu!", sim_jog);

            tabuleiro();

            troca_de_tela();

            sleep(2);

                if(rodada % 2 == 0){
                    plc[0]++;
                }
                else{
                    plc[1]++;
                }

                    reset_tabuleiro();
            return;
        }
    }
    printf("\nEmpate!");

    tabuleiro();

    reset_tabuleiro();

    troca_de_tela();

    sleep(2);
}

//Opcao contra computador
void contraComputador(){
    jogadorXcomputador = 1;
    jogadorXjogador = 0;
    verificador_parada = 0;
    rodada = 0;
    
    for(rodada=0; rodada<9; rodada++){
        if (rodada % 2 == 0){
            printf("\nVez do jogador 1: ");
            sim_jog = 'x';
            tabuleiro();
        } else {
            sim_jog = 'o';
        }
        prog_rodada();
        verificacao();
        //Se alguem venceu, a funcao mostra quem foi o vencedor e sai da funcao
        if (verificador_parada) {
            printf("\nJogador %c venceu!", sim_jog);

            tabuleiro();

            troca_de_tela();

            sleep(2);

                if(rodada % 2 == 0){
                    plc[0]++;
                }
                else{
                    plc[2]++;
                }
                    
                    reset_tabuleiro();

            return;
        }
    }
    printf("\nEmpate!");

    tabuleiro();

    reset_tabuleiro();

    troca_de_tela();

    sleep(2);
}

//Verificacao do vencedor
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

    //Ganhando na diagonal secundária
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

//Esolha do modo de jogo
void selecao_modo(){
  int sel_mod;

    printf("\nSelecione o modo de jogo:\n\n [1] Jogador x Jogador\n [2] Jogador x Computador\n\n->");
    scanf("%d", &sel_mod);

    troca_de_tela();
    
    while (sel_mod != 1 && sel_mod!=2){
        printf("\nEscolha um modo de jogo existente!\n"); 
        printf("\nSelecione o modo de jogo:\n 1 -> Jogador x Jogador\n 2 -> Jogador x Computador\n\n->");
        scanf("%d", &sel_mod);
    }
    
    if (sel_mod == 1)
        contraJogador();
    if (sel_mod == 2)
        contraComputador();
}

//Motra a pontuação acumulada até o usuário sair do jogo
void pontuacao(){

    printf("\nPontuação: \n\nJogador x: %d \nJogador o: %d \nComputador: %d\n", plc[0], plc[1], plc[2]);
    
    troca_de_tela();
    sleep(2);
}

//Resetar o tabuleiro para próxima partida
void reset_tabuleiro(){
  
    for(int i=0; i < 3; i++){
        for(int j=0; j < 3; j++){
             
            mat_tut[i][j] = ' ';

        }

    }

    verificador_parada = 0;
}

//Estética na troca de "Telas"
void troca_de_tela(){

    printf("_________________________________\n");
}
