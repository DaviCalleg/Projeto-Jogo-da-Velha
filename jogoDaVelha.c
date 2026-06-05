#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> //biblioteca para adicionar tempo (Somente para fins visuais)

//Funções Utilizadas
int menu();
void selecao_modo();
void tabuleiro();
void prog_rodada();
void iniciar_partida(int modo_jogo); 
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
int jogadorXjogador = 0;
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
    int i, contador = 1;
    printf("\n\n");

    for (i=0; i<3; i++){
       for (int j=0; j<3; j++){
            if (mat_tut[i][j] == ' '){
                if (j == 2) printf(" %d", contador);
                else printf(" %d |", contador);
            }
            else {
                if (j == 2) printf(" %c", mat_tut[i][j]);
                else printf(" %c |", mat_tut[i][j]);
            }
            contador ++;
       }
       printf("\n");
    }
}

void jogadaJogador(int *escolha, int *verificador){
    while (1){
        printf("\nEscolha a posicao -> ");
        scanf("%d", escolha);
        troca_de_tela();
            if(*escolha <= 9 && *escolha > 0){
                int linha = (*escolha - 1) / 3;
                int coluna = (*escolha - 1) % 3;
                if (mat_tut[linha][coluna] == ' ') {
                    mat_tut[linha][coluna] = sim_jog;
                    *verificador = 1;
                }
            if (*verificador) break;  
            else {
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

int jogadaComputador(char simb_alvo){
    int verificadorComp, escolhaLinha, escolhaColuna;
    //verificando linhas
    for (int i = 0; i<3; i++){
        verificadorComp = 0;
        for(int j = 0; j<3; j++){
            if(mat_tut[i][j]== simb_alvo) verificadorComp++;
            else{
                escolhaColuna = j;
                escolhaLinha = i;
            }
        }
        if (verificadorComp == 2 && mat_tut[escolhaLinha][escolhaColuna] == ' '){
            mat_tut[escolhaLinha][escolhaColuna] = 'o';
            return 1;
        }
    }
    //Verificando colunas
    for (int i = 0; i<3; i++){
        verificadorComp = 0;
        for(int j = 0; j<3; j++){
            if(mat_tut[j][i]== simb_alvo) verificadorComp++;
            else{
                escolhaColuna = i;
                escolhaLinha = j;
            }
        }
        if (verificadorComp == 2 && mat_tut[escolhaLinha][escolhaColuna] == ' '){
            mat_tut[escolhaLinha][escolhaColuna] = 'o';
            return 1;
        }
    }
    //Verificando diagonal principal
    verificadorComp = 0;
    for (int i = 0; i<3; i++){
        if (mat_tut[i][i] == simb_alvo) verificadorComp ++;
        else{
            escolhaLinha = i;
            escolhaColuna = i;
        }
    }
    if (verificadorComp == 2 && mat_tut[escolhaLinha][escolhaColuna] == ' '){
        mat_tut[escolhaLinha][escolhaColuna] = 'o';
        return 1;
    }
    // Verificando Diagonal Secundária
    verificadorComp = 0;
    for (int i = 0; i < 3; i++) {
        if (mat_tut[i][2 - i] == simb_alvo) {
            verificadorComp++;
        } else {
            escolhaLinha = i;
            escolhaColuna = 2 - i;
        }
    }
    if (verificadorComp == 2 && mat_tut[escolhaLinha][escolhaColuna] == ' ') {
        mat_tut[escolhaLinha][escolhaColuna] = 'o';
        return 1;
    }
    return 0; // Nenhuma jogada foi feita
}

//Progressão da Rodada
void prog_rodada(){
    int escolha, verificador = 0; 
    if (jogadorXjogador) jogadaJogador(&escolha, &verificador);
    else if (jogadorXcomputador){
        if (rodada % 2 == 0) jogadaJogador(&escolha, &verificador);
        else{
            // 1° Passo: Tentar Atacar (Completar sequência de 'o')
            if (jogadaComputador('o')) return;
            // 2° Passo: Tentar Defender (Bloquear sequência de 'x')
            if (jogadaComputador('x')) return;
            // 3° Passo: Jogada Aleatória (Se não tiver o que atacar ou defender)
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

void iniciar_partida(int modo_jogo) {
    if (modo_jogo == 1) {
        jogadorXjogador = 1;
        jogadorXcomputador = 0;
    } else {
        jogadorXjogador = 0;
        jogadorXcomputador = 1;
    }
    verificador_parada = 0;
    for (rodada = 0; rodada < 9; rodada++) {
        if (rodada % 2 == 0) {
            printf("\nVez do Jogador 1 (x): ");
            sim_jog = 'x';
            tabuleiro(); // Mostra o tabuleiro para o jogador 1
        } else {
            if (modo_jogo == 1) {
                printf("\nVez do Jogador 2 (o): ");
                tabuleiro(); // Mostra o tabuleiro para o jogador 2
            } else {
                printf("\nVez do Computador (o): ");
            }
            sim_jog = 'o';
        }

        // Executa a jogada e verifica vitória
        prog_rodada();
        verificacao();

        // 3. verificação de Vitória
        if (verificador_parada) {
            if (modo_jogo == 2 && rodada % 2 != 0) {
                printf("\nO Computador venceu!");
            } else {
                printf("\nJogador %c venceu!", sim_jog);
            }
            tabuleiro();
            troca_de_tela();
            sleep(2);

            // Atualiza o placar corretamente dependendo de quem ganhou
            if (rodada % 2 == 0) {
                plc[0]++; // Vitória do Jogador 1
            } else if (modo_jogo == 1) {
                plc[1]++; // Vitória do Jogador 2
            } else {
                plc[2]++; // Vitória do Computador
            }

            reset_tabuleiro();
            return; // Sai da função, encerrando a partida
        }
    }

    // 4. Se o loop de 9 rodadas acabar sem vencedores, é empate
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

//Escolha do modo de jogo
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
    iniciar_partida(sel_mod);
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
