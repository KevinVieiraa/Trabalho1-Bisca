#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "lib/graficos.h"
#include "lib/carta.h"
#include "lib/bisca.h"

#define ESAIR -1
#define EMENU 0
#define ECONFIG 1
#define EAJUDA 2
#define EJOGO 3

//-----[Dimensões da Janela]
#define ALTURA 20
#define LARGURA 72

//-----[Valores dos Simbolos(char)]
#define SIMBOLOPAUS "\u2663"
#define SIMBOLOOUROS "\u2666"
#define SIMBOLOESPADAS "\u2660"
#define SIMBOLOCOPAS "\u2665"

//-----[Valores dos Simbolos(int)]
#define PAUS 1
#define OUROS 2
#define ESPADAS 3
#define COPAS 4


int main(int argc, char *argv[])
{
    tJogador *jogador1, *jogador2, *jogador3, *jogador4;
    tMesa *mesa;
    int estado = 0;
    int jogadores;
    char opcao;
    char chat[5][50] = { {" "}, {" "}, {" "}, {" "}, {" "} };

	srand(time(NULL));
	
    DesenhaEspaco(ALTURA + 25);//Funcao necessaria para exibicao dos valores do valgrind (desnecessario se nao utilizar valgrind)

    /*
    * O jogo ocorre em um loop com condicionais que definem a sequencia 
    * de codigo a ser executada baseado no estado atual:
    * 
    * Menu:
    *  Possui opcoes de iniciar jogo, instrucoes e sair
    * 
    * Instrucoes:
    *  Fornece informacoes sobre como jogar o jogo, comandos, etc...
    * 
    * Configuracoes:
    *  Estado pre-jogo, nele sao definidas informacoes como quantidade
    *  de jogadores e dificuldade
    * 
    * Jogo:
    *  Onde ocorre a real logica do jogo, como a inicializacao das
    *  estruturas utilizadas, a distribuicao de cartas para cada jogador, etc...
    *  Logo em seguida, se inicia o loop que ira se manter ate o fim da partida.
    *  Este contem toda a logica de decisao de ganhador da rodada, qual carta o
    *  computador ira jogar, etc...
    */
    while(estado != ESAIR)
    {
        //[Menu inicial do jogo, com opcoes de iniciar jogo, ajuda ou sair]
        if(estado == EMENU)
        {
            opcao = '-'; //Zera a opcao com um valor conhecido
            DesenhaBordaDupla(LARGURA, ALTURA, 0, 0);
            DesenhaItensMenu();
            while( opcao != '1' && opcao != '2' && opcao != '3' )
            {
                printf(">");
                opcao = getchar();
                ApagaLinha(ALTURA + 1, 100); //Apaga o valor escrito anteriormente
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
            opcao = '-'; //Zera a opcao com um valor conhecido
            DesenhaBordaDupla(LARGURA, ALTURA, 0, 0);
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

            opcao = '-'; //Zera a opcao com um valor conhecido
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
            opcao = '-'; //Zera a opcao com um valor conhecido
            DesenhaBordaDupla(LARGURA, ALTURA, 0, 0);
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
            DesenhaItensJogo(jogadores);
            CursorPosicao(0, 28);
            
            mesa = InicializaMesa();
            Embaralha(mesa -> baralho);

            jogador1 = InicializaJogador(mesa -> baralho, 1);
            jogador2 = InicializaJogador(mesa -> baralho, 2);
            if(jogadores == 4)
            {
                jogador3 = InicializaJogador(mesa -> baralho, 3);
                jogador4 = InicializaJogador(mesa -> baralho, 4);
            }
              
            while(estado == EJOGO)
            {   
                printf(">");
                int jogouCarta = 0; //Sinaliza quando o jogo deve prosseguir a logica, necessario para opcoes diferentes de 1, 2 ou 3
                while(!jogouCarta && estado == EJOGO)
                {
                    char tmp[50]; //Guarda o valor temporario da mensagem a ser exibida no chat
                    tCarta *retirada; //Ponteiro temporario para salvar a carta retirada pelo jogador ou IA
                    switch(getchar())
                    {
                        case '1':
                            if(TamLista(jogador1 -> mao) >= 1)
                            {
                                retirada = RetiraCarta(jogador1 -> mao, 1);
                                InsereCarta(mesa -> monte, retirada);
                                jogouCarta = 1;

                                sprintf(tmp, "Voce jogou a carta %c%s", ConverteValor(retirada -> valor), RetornaNaipe(retirada -> naipe));
                                AtualizaChat(chat, tmp);
                            }
                            else
                            {
                                //Nao existe carta na posicao 1
                                sprintf(tmp, "Carta na posicao invalida");
                                AtualizaChat(chat, tmp);
                            }
                            break;
                        case '2':
                            if(TamLista(jogador1 -> mao) >= 2)
                            {
                                retirada = RetiraCarta(jogador1 -> mao, 2);
                                InsereCarta(mesa -> monte, retirada);
                                jogouCarta = 1;

                                sprintf(tmp, "Voce jogou a carta %c%s", ConverteValor(retirada -> valor), RetornaNaipe(retirada -> naipe));
                                AtualizaChat(chat, tmp);
                            }
                            else
                            {
                                //Nao existe carta na posicao 2
                                sprintf(tmp, "Carta na posicao invalida");
                                AtualizaChat(chat, tmp);
                            }
                            break;
                        case '3':
                            if(TamLista(jogador1 -> mao) >= 3)
                            {
                                retirada = RetiraCarta(jogador1 -> mao, 3);
                                InsereCarta(mesa -> monte, retirada);
                                jogouCarta = 1;

                                AtualizaChat(chat, tmp);
                                sprintf(tmp, "Voce jogou a carta %c%s", ConverteValor(retirada -> valor), RetornaNaipe(retirada -> naipe));
                            }
                            else
                            {
                                //Nao existe carta na posicao 3
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
                            sprintf(tmp, "Encerrando partida... Abrindo menu...");
                            AtualizaChat(chat, tmp);
                            estado = EMENU;
                            break;
                        case 'S':
                        case 's':
                            sprintf(tmp, "Encerrando programa...");
                            AtualizaChat(chat, tmp);
                            estado = ESAIR;
                            break;
                    }
                    
                    if(jogouCarta)
                    {
                        retirada = IACartaJogada(jogador2, 1);
                        InsereCarta(mesa -> monte, retirada);
                        sprintf(tmp, "Jogador %d jogou a carta %c%s", jogador2 -> id, ConverteValor(retirada -> valor), RetornaNaipe(retirada -> naipe));
                        AtualizaChat(chat, tmp);

                        if(jogadores == 4)
                        {
                            retirada = IACartaJogada(jogador3, 1);
                            InsereCarta(mesa -> monte, retirada);
                            sprintf(tmp, "Jogador %d jogou a carta %c%s", jogador3 -> id, ConverteValor(retirada -> valor), RetornaNaipe(retirada -> naipe));
                            AtualizaChat(chat, tmp);
                            
                            retirada = IACartaJogada(jogador4, 1);
                            InsereCarta(mesa -> monte, retirada);
                            sprintf(tmp, "Jogador %d jogou a carta %c%s", jogador3 -> id, ConverteValor(retirada -> valor), RetornaNaipe(retirada -> naipe));
                            AtualizaChat(chat, tmp);
                        }
                    }

                    ImprimeChat(chat);

                    DesenhaMao(jogador1 -> mao, 19, 15, "1");
                    DesenhaMao(jogador2 -> mao, 19, 1, argv[1]);
                    if(jogadores == 4)
                    {
                        DesenhaMao(jogador3 -> mao, 49, 15, argv[1]);
                        DesenhaMao(jogador4 -> mao, 49, 1, argv[1]);
                    }

                    DesenhaMesa(mesa -> monte);
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
            sleep(1);
        }
    }

    return 0;
}