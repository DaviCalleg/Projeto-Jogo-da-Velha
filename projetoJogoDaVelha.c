#include <stdio.h>
#define L 3
#define C 3
int matriz[L][C] = {1,2,3,4,5,6,7,8,9};  //oi

void ilustracaoJogoDaVelha(){
    for (int i = 0; i < L; i++){
        for (int j = 0; j<C; j++){
            if (j!= C-1){
                printf(" %d |", matriz[i][j]);
            } 
            else{
                printf(" %d", matriz[i][j]);
            }
        }
        printf("\n");
    }
}

void jogoContraAmigo(){
    int escolha, rodada = 1, vitoria=0;
    while(rodada <= L*C && vitoria == 0 ){
        if (rodada % 2 != 0){
            ilustracaoJogoDaVelha();
            printf("Jogdaor 1, digite a cedula escolhida: ");
            scanf("%d", &escolha);
        }
        else {
            ilustracaoJogoDaVelha();
            printf("Jogdaor 2, digite a cedula escolhida: ");
            scanf("%d", &escolha);   
        }
        rodada += 1;
    }    
}

void tutorialJogoDaVelha (int matriz[L][C]){
    int contador = 0;
    printf("Para jogar, o usuario deve digitar algum numero disponivel no jogo, e a cedula sera marcada: \n\n");
    ilustracaoJogoDaVelha();
    printf("\nO jogador que completar uma linha, coluna ou diagonal, vence! \nPorem, caso ninguem complete e todas cedulas sao marcadas, o jogo da empate\n");
}

int main(){
    int opcao;
    printf("Menu (Digite o numero da opcao escolhida):\n1- Comecar jogo contra um amigo\n2- Comecar jogo contra o computador\n3- Tutorial de como jogar:\n");
    scanf("%d", &opcao);
    switch(opcao){
        case 1:
            jogoContraAmigo();
            break;
        case 2:
            printf("comecando jogo contra computador...");
            break;
        case 3:
            tutorialJogoDaVelha(matriz);
            break;
        }
    return 0;
}