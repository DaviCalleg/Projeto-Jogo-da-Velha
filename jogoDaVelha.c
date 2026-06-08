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

// Main
int main(){
    srand(time(NULL));
    
    char matriz_jogo[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    int placar[3] = {0}; // placar[0] = Jogador X | placar[1] = Jogador O | placar[2] = Computador
    
    menu(matriz_jogo, placar); 
    return 0;
}

// Função para evitar loop infinito caso o usuário digite uma letra
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Menu de escolha
int menu(char matriz_jogo[3][3], int placar[3]){
    int opcao_menu = 0;
    do{
        do{
            printf("\n[1] Jogar\n[2] Pontuacao\n[3] Sair\n\n->");
            if(scanf("%d", &opcao_menu) != 1) { // Se não ler um número
                limpar_buffer();
                opcao_menu = 0; // Força a repetição do loop
            }
            troca_de_tela();
        }while (opcao_menu != 1 && opcao_menu != 2 && opcao_menu != 3);
        
        if(opcao_menu == 1) selecao_modo(matriz_jogo, placar);
        if(opcao_menu == 2) pontuacao(placar);
    }while(opcao_menu != 3);
    
    printf("\nFim de jogo!\n\n");
    return 0;
}

// Tabuleiro do Jogo
void tabuleiro(char matriz_jogo[3][3]){
    int i, contador = 1;
    printf("\n\n");

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
            // 3° Passo: Jogada Aleatória (Se não tiver o que atacar ou defender)
            while(1){
                escolha = (rand() % 9) + 1;
                for (int i=0; i<3; i++){
                    for (int j=0; j<3; j++){
                        int linha = (escolha - 1) / 3;
                        int coluna = (escolha - 1) % 3;
                        if (matriz_jogo[linha][coluna] != 'x' && matriz_jogo[linha][coluna] != 'o') {
                            matriz_jogo[linha][coluna] = 'o';
                            jogada_valida = 1;
                        }
                    }
                }
                if(jogada_valida) break;
                else escolha = (rand() % 9) + 1;
            }
        }
    }
}

void iniciar_partida(int modo_jogo, char matriz_jogo[3][3], int placar[3]) {
    int dificuldade = 0;
    char simbolo_jogador;
    
    if (modo_jogo == 2) {
        do{
            printf("Dificuldades:\n[1] facil\n[2] medio\n[3] dificil\n->");
            if(scanf("%d", &dificuldade) != 1) {
                limpar_buffer();
                dificuldade = 0;
            }
        } while(dificuldade < 1 || dificuldade > 3);
    }
    
    for (int rodada = 0; rodada < 9; rodada++) {
        if (rodada % 2 == 0) {
            printf("\nVez do Jogador 1 (x): ");
            simbolo_jogador = 'x';
            tabuleiro(matriz_jogo); // Mostra o tabuleiro para o jogador 1
        } else {
            if (modo_jogo == 1) {
                printf("\nVez do Jogador 2 (o): ");
                tabuleiro(matriz_jogo); // Mostra o tabuleiro para o jogador 2
            } else {
                printf("\nVez do Computador (o): ");
            }
            simbolo_jogador = 'o';
        }

        // Executa a jogada
        prog_rodada(matriz_jogo, modo_jogo, dificuldade, rodada, simbolo_jogador);

        // 3. Verificação de Vitória
        if (verificacao(matriz_jogo, simbolo_jogador)) { // Se a função retornar 1 (Verdadeiro)
            if (modo_jogo == 2 && rodada % 2 != 0) {
                printf("\nO Computador venceu!");
            } else {
                printf("\nJogador %c venceu!", simbolo_jogador);
            }
            tabuleiro(matriz_jogo);
            troca_de_tela();
            sleep(2);

            // Atualiza o placar corretamente dependendo de quem ganhou
            if (rodada % 2 == 0) {
                placar[0]++; // Vitória do Jogador 1
            } else if (modo_jogo == 1) {
                placar[1]++; // Vitória do Jogador 2
            } else {
                placar[2]++; // Vitória do Computador
            }

            reset_tabuleiro(matriz_jogo);
            return; // Sai da função, encerrando a partida
        }
    }

    // 4. Se o loop de 9 rodadas acabar sem vencedores, é empate
    printf("\nEmpate!");
    tabuleiro(matriz_jogo);
    reset_tabuleiro(matriz_jogo);
    troca_de_tela();
    sleep(2);
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

// Escolha do modo de jogo
void selecao_modo(char matriz_jogo[3][3], int placar[3]){
    int opcao_modo;
    printf("\nSelecione o modo de jogo:\n\n [1] Jogador x Jogador\n [2] Jogador x Computador\n\n->");
    if(scanf("%d", &opcao_modo) != 1) { limpar_buffer(); opcao_modo = 0;}
    troca_de_tela();
    
    while (opcao_modo != 1 && opcao_modo != 2){
        printf("\nEscolha um modo de jogo existente!\n"); 
        printf("\nSelecione o modo de jogo:\n 1 -> Jogador x Jogador\n 2 -> Jogador x Computador\n\n->");
        if(scanf("%d", &opcao_modo) != 1) { limpar_buffer(); opcao_modo = 0;}
    }
    iniciar_partida(opcao_modo, matriz_jogo, placar);
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
