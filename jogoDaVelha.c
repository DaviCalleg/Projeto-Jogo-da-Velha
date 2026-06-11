//Alunos: Arthur Rocha Saldanha, Davi Callegario Caetano e Felipe Silva Mantuani.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // biblioteca para adicionar tempo (Somente para fins visuais)

// Funções Utilizadas
void limpar_buffer();
int menu(char matriz_jogo[3][3], int placar[3]);
void selecao_modo(char matriz_jogo[3][3], int placar[3]);
void tabuleiro(char matriz_jogo[3][3]);
void jogadaJogador(char matriz_jogo[3][3], char simbolo_jogador, int *escolha, int *jogada_valida);
int jogadaComputador(char matriz_jogo[3][3], char simb_alvo);
void prog_rodada(char matriz_jogo[3][3], int modo_jogo, int dificuldade, int rodada, char simbolo_jogador);
void iniciar_partida(int modo_jogo, char matriz_jogo[3][3], int placar[3]); 
int verificacao(char matriz_jogo[3][3], char simbolo_jogador);
void reset_tabuleiro(char matriz_jogo[3][3]);
void pontuacao(int placar[3]);
void troca_de_tela();

//Variáveis Globais
int mod_visual = 1;

// Main
int main(){
    srand(time(NULL));
    

    char matriz_jogo[3][3] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    int placar[3] = {0}; // placar[0] = Jogador X | placar[1] = Jogador O | placar[2] = Computador
    
    menu(matriz_jogo, placar); 
    return 0;
}

// Menu de escolha
int menu(char matriz_jogo[3][3], int placar[3]){
    int opcao_menu = 0;
    do{
        do{
            printf("\n[1] Jogar\n[2] Pontuacao\n[3] Visual do tabuleiro\n[4] Sair\n\n->");
            if(scanf("%d", &opcao_menu) != 1) { // Se não ler um número
                limpar_buffer();
                opcao_menu = 0; // Força a repetição do loop
            }
            troca_de_tela();
        }while (opcao_menu != 1 && opcao_menu != 2 && opcao_menu != 3 && opcao_menu != 4);
        
        if(opcao_menu == 1) selecao_modo(matriz_jogo, placar);
        if(opcao_menu == 2) pontuacao(placar);
        if(opcao_menu == 3){
           do{
            printf("\nEscolha o visual do tabuleiro\n\n[1] Com números\n[2] Sem números\n\n->");
            if(scanf("%d", &mod_visual) != 1) { // Se não ler um número
                limpar_buffer();
            }
            troca_de_tela();
        }while (mod_visual != 1 && mod_visual != 2);

        }
    }while(opcao_menu != 4);
    
    printf("\nFim de jogo!\n\n");
    return 0;
}

// Escolha do modo de jogo
void selecao_modo(char matriz_jogo[3][3], int placar[3]){
    int opcao_modo;
    printf("\nSelecione o modo de jogo:\n\n [1] Jogador x Jogador\n [2] Jogador x Computador\n\n->");
    scanf("%d", &opcao_modo);
    limpar_buffer();
    troca_de_tela();
    while (opcao_modo != 1 && opcao_modo != 2){
        printf("\nEscolha um modo de jogo existente!\n");
        printf("\nSelecione o modo de jogo:\n 1 -> Jogador x Jogador\n 2 -> Jogador x Computador\n\n->");
        scanf("%d", &opcao_modo);
        limpar_buffer();
    }
    iniciar_partida(opcao_modo, matriz_jogo, placar);
}

// Tabuleiro do Jogo
void tabuleiro(char matriz_jogo[3][3]){
    int i, contador = 1;
    printf("\n\n");

    if(mod_visual == 1){
        for (i=0; i<3; i++){
            for (int j=0; j<3; j++){
                    if (matriz_jogo[i][j] == ' '){
                        if (j == 2) printf(" %d", contador);
                        else printf(" %d |", contador);
                    }
                    else {
                        if (j == 2) printf(" %c", matriz_jogo[i][j]);
                        else printf(" %c |", matriz_jogo[i][j]);
                    }
                    contador ++;
            }
            printf("\n");
        }
    }
    else{
      for (i=0; i<3; i++){
            for (int j=0; j<3; j++){
                   
                if (j == 2) printf(" %c", matriz_jogo[i][j]);
                else printf(" %c |", matriz_jogo[i][j]);
            }
            printf("\n");
        }

    }
}

// Pergunta se quer jogar novamente e retorna 1 (sim) ou 0 (não)
int jogar_novamente(){
    int jogar_nov = 0;
    do {
        printf("\nJogar Novamente:\n\n[1] Sim\n[2] Nao\n\n->");
        scanf("%d", &jogar_nov);
    } while (jogar_nov != 1 && jogar_nov != 2);
    troca_de_tela();
    return jogar_nov == 1;
}

//Inicia a partida
void iniciar_partida(int modo_jogo, char matriz_jogo[3][3], int placar[3]) {
    int dificuldade = 0;
    if (modo_jogo == 2) {
        do {
            printf("\nDificuldades:\n\n[1] Facil\n[2] Medio\n[3] Dificil\n\n->");
            scanf("%d", &dificuldade);
            troca_de_tela();
            limpar_buffer();
        } while (dificuldade != 1 && dificuldade != 2 && dificuldade != 3);
    }
    // Loop de partidas
    do {
        char simbolo_jogador;
        int partida_encerrada = 0;
        for (int rodada = 0; rodada < 9; rodada++) {
            if (rodada % 2 == 0) {
                printf("\nVez do Jogador 1 (x): ");
                simbolo_jogador = 'x';
                tabuleiro(matriz_jogo);
            } else {
                if (modo_jogo == 1) {
                    printf("\nVez do Jogador 2 (o): ");
                    tabuleiro(matriz_jogo);
                }
                simbolo_jogador = 'o';
            }
            prog_rodada(matriz_jogo, modo_jogo, dificuldade, rodada, simbolo_jogador);
            if (verificacao(matriz_jogo, simbolo_jogador)) {
                if (modo_jogo == 2 && rodada % 2 != 0)
                    printf("\nO Computador venceu!");
                else
                    printf("\nJogador %c venceu!", simbolo_jogador);

                tabuleiro(matriz_jogo);
                troca_de_tela();
                if (rodada % 2 == 0) placar[0]++;
                else if (modo_jogo == 1) placar[1]++;
                else placar[2]++;
                partida_encerrada = 1;
                break;
            }
        }

        if (!partida_encerrada) {
            printf("\nEmpate!");
            tabuleiro(matriz_jogo);
            troca_de_tela();
        }
        reset_tabuleiro(matriz_jogo);

    } while (jogar_novamente());
}

// Progressão da Rodada
void prog_rodada(char matriz_jogo[3][3], int modo_jogo, int dificuldade, int rodada, char simbolo_jogador){
    int escolha, jogada_valida = 0;
    if (modo_jogo == 1) jogadaJogador(matriz_jogo, simbolo_jogador, &escolha, &jogada_valida);
    else if (modo_jogo == 2){
        if (rodada % 2 == 0) jogadaJogador(matriz_jogo, simbolo_jogador, &escolha, &jogada_valida);
        else{
            int chance = rand()%100, jogarCerto = 0;
            if (dificuldade == 3) jogarCerto = 1; 
            else if (dificuldade == 2){
                if (chance < 75) jogarCerto = 1;
            }
            else if (dificuldade == 1){
                if (chance < 50) jogarCerto = 1;
            }
            
            if(jogarCerto){
                // 1° Passo: Tentar Atacar (Completar sequência de 'o')
                if (jogadaComputador(matriz_jogo, 'o')) return;
                // 2° Passo: Tentar Defender (Bloquear sequência de 'x')
                if (jogadaComputador(matriz_jogo, 'x')) return;
            }
            if (matriz_jogo[1][1] == ' '){
                if (dificuldade > 1 ){
                    matriz_jogo[1][1] = 'o';
                    return;
                }
            }
            // 3° Passo: Jogada Aleatória (Se não tiver o que atacar ou defender)
            do {
                escolha = (rand() % 9) + 1;
                int linha  = (escolha - 1) / 3;
                int coluna = (escolha - 1) % 3;
                if (matriz_jogo[linha][coluna] != 'x' && matriz_jogo[linha][coluna] != 'o') {
                    matriz_jogo[linha][coluna] = 'o';
                    jogada_valida = 1;
                }
            } while (!jogada_valida);
        }
    }
}

//Jogadas feitos pelos jogadores
void jogadaJogador(char matriz_jogo[3][3], char simbolo_jogador, int *escolha, int *jogada_valida){
    while (1){
        printf("\nEscolha a posicao -> ");
        if(scanf("%d", escolha) != 1) {
            limpar_buffer();
            *escolha = 0;
        }
        troca_de_tela();
        if(*escolha <= 9 && *escolha > 0){
                int linha = (*escolha - 1) / 3;
                int coluna = (*escolha - 1) % 3;
                if (matriz_jogo[linha][coluna] == ' ') {
                    matriz_jogo[linha][coluna] = simbolo_jogador;
                    *jogada_valida = 1;
                }
            if (*jogada_valida) break;  
            else {
                printf("\nSelecione um espaco valido");
                tabuleiro(matriz_jogo);
            }
        } 
        else{
            printf("\nSelecione um espaco valido");
            tabuleiro(matriz_jogo);
        } 
    }
}

//Jogadas feitas pelo Computador
int jogadaComputador(char matriz_jogo[3][3], char simb_alvo){
    int casas_iguais, escolhaLinha, escolhaColuna;
    
    // Verificando linhas
    for (int i = 0; i<3; i++){
        casas_iguais = 0;
        for(int j = 0; j<3; j++){
            if(matriz_jogo[i][j] == simb_alvo) casas_iguais++;
            else{
                escolhaColuna = j;
                escolhaLinha = i;
            }
        }
        if (casas_iguais == 2 && matriz_jogo[escolhaLinha][escolhaColuna] == ' '){
            matriz_jogo[escolhaLinha][escolhaColuna] = 'o';
            return 1;
        }
    }
    // Verificando colunas
    for (int i = 0; i<3; i++){
        casas_iguais = 0;
        for(int j = 0; j<3; j++){
            if(matriz_jogo[j][i] == simb_alvo) casas_iguais++;
            else{
                escolhaColuna = i;
                escolhaLinha = j;
            }
        }
        if (casas_iguais == 2 && matriz_jogo[escolhaLinha][escolhaColuna] == ' '){
            matriz_jogo[escolhaLinha][escolhaColuna] = 'o';
            return 1;
        }
    }
    // Verificando diagonal principal
    casas_iguais = 0;
    for (int i = 0; i<3; i++){
        if (matriz_jogo[i][i] == simb_alvo) casas_iguais++;
        else{
            escolhaLinha = i;
            escolhaColuna = i;
        }
    }
    if (casas_iguais == 2 && matriz_jogo[escolhaLinha][escolhaColuna] == ' '){
        matriz_jogo[escolhaLinha][escolhaColuna] = 'o';
        return 1;
    }
    // Verificando diagonal secundária
    casas_iguais = 0;
    for (int i = 0; i < 3; i++) {
        if (matriz_jogo[i][2 - i] == simb_alvo) {
            casas_iguais++;
        } else {
            escolhaLinha = i;
            escolhaColuna = 2 - i;
        }
    }
    if (casas_iguais == 2 && matriz_jogo[escolhaLinha][escolhaColuna] == ' ') {
        matriz_jogo[escolhaLinha][escolhaColuna] = 'o';
        return 1;
    }
    return 0; // Nenhuma jogada foi feita
}

// Verificacao do vencedor (Retorna 1 se venceu, ou 0 se não)
int verificacao(char matriz_jogo[3][3], char simbolo_jogador){
    int casas_iguais = 0;
    
    // Ganhando na linha
    for (int i=0; i<3; i++){
        casas_iguais = 0;
        for (int j=0; j<3; j++){
            if (matriz_jogo[i][j] == simbolo_jogador){
                casas_iguais++;
            }
        }
        if(casas_iguais == 3) return 1;
    }
    
    // Ganhando na coluna
    for (int i=0; i<3; i++){
        casas_iguais = 0;
        for (int j=0; j<3; j++){
            if (matriz_jogo[j][i] == simbolo_jogador){
                casas_iguais++;
            }
        }
        if(casas_iguais == 3) return 1;
    }
    
    // Ganhando na diagonal principal
    casas_iguais = 0;
    for (int i = 0; i<3; i++){
        if (matriz_jogo[i][i] == simbolo_jogador){
            casas_iguais++;
        }
    }
    if(casas_iguais == 3) return 1;

    // Ganhando na diagonal secundária
    casas_iguais = 0;
    for (int i = 0; i < 3; i++) {
        if (matriz_jogo[i][2 - i] == simbolo_jogador) {
            casas_iguais++;
        }
    }
    if (casas_iguais == 3) return 1;
    
    return 0; // Ninguém ganhou ainda
}

// Mostra a pontuação acumulada até o usuário sair do jogo
void pontuacao(int placar[3]){
    printf("\nPontuacao: \n\nJogador x: %d \nJogador o: %d \nComputador: %d\n", placar[0], placar[1], placar[2]);
    troca_de_tela();
    sleep(2);
}

// Resetar o tabuleiro para próxima partida
void reset_tabuleiro(char matriz_jogo[3][3]){
    for(int i=0; i < 3; i++){
        for(int j=0; j < 3; j++){       
            matriz_jogo[i][j] = ' ';
        }
    }
}

// Estética na troca de "Telas"
void troca_de_tela(){
    printf("_________________________________\n");
}

// Função para evitar loop infinito caso o usuário digite uma letra
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
