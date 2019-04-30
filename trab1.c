#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "lib/graficos.h"
#include "lib/carta.h"

#define ESAIR -1
#define EMENU 0
#define ECONFIG 1
#define EAJUDA 2
#define EJOGO 3

//-----[Dimensões da Janela]
#define ALTURA 20
#define LARGURA 72

#define SIMBOLOPAUS "\u2663"
#define SIMBOLOOUROS "\u2666"
#define SIMBOLOESPADAS "\u2660"
#define SIMBOLOCOPAS "\u2665"

#define PAUS 1
#define OUROS 2
#define ESPADAS 3
#define COPAS 4


int main(int argc, char *argv[])
{
    tJogador *jogador1, *jogador2, *jogador3, *jogador4;
    tMesa *mesa;
    int estado = 0, jogadores;
    char opcao, chat[5][50] = { {" "}, {" "}, {" "}, {" "}, {" "} };

	srand(time(NULL));
	
    DesenhaEspaco(ALTURA + 9);
    //[O jogo ocorre dentro de um laço que alterna entre "estados"]
    while(1)
    {
        //[Menu inicial do jogo, com opcoes de iniciar jogo, ajuda ou sair]
        if(estado == EMENU)
        {
            opcao = '-';
            DesenhaLayout(LARGURA, ALTURA, 0, 0);
            DesenhaItensMenu();
            while( opcao != '1' && opcao != '2' && opcao != '3' )
            {
                printf(">");
                opcao = getchar();
                ApagaLinha(ALTURA + 1, 100);
            }

            switch(opcao)
            {
                case '1':
                    estado = ECONFIG;
                    break;
                case '2':
                    estado = EAJUDA;
                    break;
                case '3':
                    estado = ESAIR;
            }

            ApagaLinha(ALTURA + 1, 100);
        }

        //[Configuracoes iniciais antes da partida]
        if(estado == ECONFIG)
        {
            opcao = '-';
            DesenhaLayout(LARGURA, ALTURA, 0, 0);
            DesenhaItensConfig();
            while(opcao != '2' && opcao != '4')
            {
                ApagaLinha(ALTURA + 1, 100);
                printf(">Jogadores: ");
                opcao = getchar();
                if(opcao == '2')
                {
                    jogadores = 2;
                }
                if(opcao == '4')
                {
                    jogadores = 4;
                }
            }

            opcao = '-';
            while(opcao != '1' && opcao != '2')
            {
                ApagaLinha(ALTURA + 2, 100);
                printf(">Dificuldade: ");
                opcao = getchar();
                
            }
            ApagaLinha(ALTURA + 1, 100);
            ApagaLinha(ALTURA + 2, 100);
            estado = EJOGO;
        }

        //[Instrucoes sobre o jogo]
        if(estado == EAJUDA)
        {
            opcao = '-';
            DesenhaLayout(LARGURA, ALTURA, 0, 0);
            DesenhaItensAjuda();
            while( opcao != '0' )
            {
                printf(">");
                opcao = getchar();
                ApagaLinha(ALTURA + 1, 100);
            }

            estado = EMENU;
            ApagaLinha(ALTURA + 1, 100);
        }

        //[Inicio do jogo]
        if(estado == EJOGO)
        {
            DesenhaLayout(LARGURA, ALTURA, 0, 0);
            DesenhaItensJogo(jogadores);
            CursorPosicao(0, 28);
            
            mesa = InicializaMesa();
            Embaralha(mesa -> baralho);

            jogador1 = InicializaJogador(mesa -> baralho);
            jogador2 = InicializaJogador(mesa -> baralho);
            if(jogadores == 4)
            {
                jogador3 = InicializaJogador(mesa -> baralho);
                jogador4 = InicializaJogador(mesa -> baralho);
            }
              
            while(estado == EJOGO)
            {   
                ApagaLinha(28, 100);
                printf(">");
                int jogouCarta = 0;
                while(!jogouCarta)
                {
                    char tmp[50];
                    tCarta *retirada;
                    switch(getchar())
                    {
                        case '1':
                            if(TamLista(jogador1 -> mao) >= 1)
                            {
                                retirada = RetiraCarta(jogador1 -> mao, 1);
                                sprintf(tmp, "Voce jogou a carta %c%s", ConverteValor(retirada -> valor), RetornaNaipe(retirada -> naipe));
                                AtualizaChat(chat, tmp);
                                InsereCarta(mesa -> monte, retirada);
                                jogouCarta = 1;
                            }
                            else
                            {
                                sprintf(tmp, "Carta na posicao invalida");
                                AtualizaChat(chat, tmp);
                            }
                            break;
                        case '2':
                            if(TamLista(jogador1 -> mao) >= 2)
                            {
                                retirada = RetiraCarta(jogador1 -> mao, 2);
                                sprintf(tmp, "Voce jogou a carta %c%s", ConverteValor(retirada -> valor), RetornaNaipe(retirada -> naipe));
                                AtualizaChat(chat, tmp);
                                InsereCarta(mesa -> monte, retirada);
                                jogouCarta = 1;
                            }
                            else
                            {
                                sprintf(tmp, "Carta na posicao invalida");
                                AtualizaChat(chat, tmp);
                            }
                            break;
                        case '3':
                            if(TamLista(jogador1 -> mao) >= 3)
                            {
                                retirada = RetiraCarta(jogador1 -> mao, 3);
                                sprintf(tmp, "Voce jogou a carta %c%s", ConverteValor(retirada -> valor), RetornaNaipe(retirada -> naipe));
                                AtualizaChat(chat, tmp);
                                InsereCarta(mesa -> monte, retirada);
                                jogouCarta = 1;
                            }
                            else
                            {
                                sprintf(tmp, "Carta na posicao invalida");
                                AtualizaChat(chat, tmp);
                            }
                            break;
                        case 'E':
                        case 'e':
                            break;
                        case 'C':
                        case 'c':
                            break;
                        case 'M':
                        case 'm':
                            break;
                        case 'S':
                        case 's':
                            jogouCarta = 1;
                            estado = ESAIR;
                            break;
                    }

                    if(jogouCarta)
                    {
                        retirada = IACartaJogada(jogador2, 1);
                        InsereCarta(mesa -> monte, retirada);
                        sprintf(tmp, "Jogador %d jogou a carta %c%s", 2, ConverteValor(retirada -> valor), RetornaNaipe(retirada -> naipe));
                        AtualizaChat(chat, tmp);

                        if(jogadores == 4)
                        {
                            retirada = IACartaJogada(jogador3, 1);
                            InsereCarta(mesa -> monte, retirada);
                            sprintf(tmp, "Jogador %d jogou a carta %c%s", 3, ConverteValor(retirada -> valor), RetornaNaipe(retirada -> naipe));
                            AtualizaChat(chat, tmp);
                            
                            retirada = IACartaJogada(jogador4, 1);
                            InsereCarta(mesa -> monte, retirada);
                            sprintf(tmp, "Jogador %d jogou a carta %c%s", 4, ConverteValor(retirada -> valor), RetornaNaipe(retirada -> naipe));
                            AtualizaChat(chat, tmp);
                        }
                    }

                    ImprimeChat(chat);
                    if(jogadores == 2)
                    {
                        DesenhaMao(jogador1 -> mao, 28, 15, "1");
                        DesenhaMao(jogador2 -> mao, 28, 1, argv[1]);
                    }
                    else
                    {
                        DesenhaMao(jogador1 -> mao, 14, 15, "1");
                        DesenhaMao(jogador2 -> mao, 44, 15, argv[1]);
                        DesenhaMao(jogador3 -> mao, 14, 1, argv[1]);
                        DesenhaMao(jogador4 -> mao, 44, 1, argv[1]);
                    }

                    DesenhaMesa(mesa -> monte, jogadores);
                    ApagaLinha(28, 100);
                }
                
            }

            LiberaJogador(jogador1);
            LiberaJogador(jogador2);
            if(jogadores == 4)
            {
                LiberaJogador(jogador3);
                LiberaJogador(jogador4);
            }
            LiberaMesa(mesa);
        }

        //[Estado que finaliza o laço e encerra o jogo]
        if(estado == ESAIR)
        {
            break;
        }
    }

    return 0;
}



/*
♠ - 6
♣ - 5
♦ - 4
♥ - 3

┌─────┐
│3    │
│  ♥  │
│    3│
└─────┘

*/









