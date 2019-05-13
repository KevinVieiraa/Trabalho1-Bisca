/*
*   Trabalho - Estrutura de Dados I
*             Turma: 01
*        Kevin Vieira Izabel
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lib/graficos.h"
#include "lib/carta.h"
#include "lib/bisca.h"

//-----[Estados do jogo]
#define ESAIR -1
#define EMENU 0
#define ECONFIG 1
#define EAJUDA 2
#define EJOGO 3
//-----[Dimensões da janela]
#define ALTURA 20
#define LARGURA 72
//-----[Parametros das cartas]
#define NADA 1
#define PONTO 2
#define TRUNFO 3
#define BISCA 4


void Espera()
{
    while(1)
    {
        ApagaLinha(28, 100);
        printf(">");
        if (getchar() == '0')
        {
            break;
        }
    }
}

void PrintaTeste(char* string, int x, int y)
{
    CursorPosicao(x, y);
    ApagaLinha(y, 100);
    printf("%s", string);
    Espera();
}

void ModificaPontosJogador(tJogador* jogador, int valor)
{
    jogador -> pontos += valor;
}

void CalculaPontos(tJogador* jogador)
{
    tCarta *aux = jogador -> pontosCartas -> lista;
    ModificaPontosJogador(jogador, -jogador -> pontos);
    while(aux != NULL)
    {
        switch(ValorCarta(aux))
        {
            case 7:
                ModificaPontosJogador(jogador, 2);
                break;
            case 8:
                ModificaPontosJogador(jogador, 3);
                break;
            case 9:
                ModificaPontosJogador(jogador, 4);
                break;
            case 10:
                ModificaPontosJogador(jogador, 10);
                break;
            case 11:
                ModificaPontosJogador(jogador, 11);
                break;
        }
        aux = aux -> proximo;
    }
}

tJogador* DecideVencedor(tListaJogadores* jogadores)
{
    tJogador *aux = jogadores -> lista;
    tJogador *vencedor = jogadores -> primeiro;
    int tamanhoJogadores = TamJogadores(jogadores);

    for(int i = 1; i <= tamanhoJogadores; i++)
    {
        if(PontosJogador(aux) > PontosJogador(vencedor))
        {
            vencedor = aux;
        }
        aux = aux -> prox;
    }

    return vencedor;
}

int CartaTrunfo(tCarta* carta, tCarta* trunfo)
{
    if(NaipeCarta(carta) == NaipeCarta(trunfo))
    {
        return 1;
    }
    return 0;
}

int CartaPonto(tCarta* carta, tCarta* trunfo)
{
    if(!CartaTrunfo(carta, trunfo) && ValorCarta(carta) >= 7 && ValorCarta(carta) <= 9)
    {
        return 1;
    }
    return 0;
}

int CartaBisca(tCarta* carta, tCarta* trunfo)
{
    if(!CartaTrunfo(carta, trunfo) && ValorCarta(carta) >= 10)
    {
        return 1;
    }
    return 0;
}

int CartaSemValor(tCarta* carta, tCarta* trunfo)
{
    if(!CartaBisca(carta, trunfo) && !CartaPonto(carta, trunfo) && !CartaTrunfo(carta, trunfo))
    {
        return 1;
    }
    return 0;
}

int TemNadaLista(tListaCartas* cartas, tCarta* trunfo)
{
    if(TamListaCartas(cartas) != 0)
    {
        tCarta* aux = cartas -> lista;
        while(aux != NULL)
        {
            if(CartaSemValor(aux, trunfo))
            {
                return 1;
            }   
            aux = aux -> proximo;
        }
    }
    else
    {
        return 1;
    }
    return 0;
}

int TemPontoLista(tListaCartas* cartas, tCarta* trunfo)
{
    if(TamListaCartas(cartas) != 0)
    {
        tCarta* aux = cartas -> lista;
        while(aux != NULL)
        {
            if(CartaPonto(aux, trunfo))
            {
                return 1;
            }   
            aux = aux -> proximo;
        }
    }
    return 0;
}

int TemTrunfoLista(tListaCartas* cartas, tCarta* trunfo)
{
    if(TamListaCartas(cartas) != 0)
    {
        tCarta* aux = cartas -> lista;
        while(aux != NULL)
        {
            if(CartaTrunfo(aux, trunfo))
            {
                return 1;
            }   
            aux = aux -> proximo;
        }
    }
    return 0;
}

int TemBiscaLista(tListaCartas* cartas, tCarta* trunfo)
{
    if(TamListaCartas(cartas) != 0)
    {
        tCarta* aux = cartas -> lista;
        while(aux != NULL)
        {
            if(CartaBisca(aux, trunfo))
            {
                return 1;
            }   
            aux = aux -> proximo;
        }
    }
    return 0;
}


tCarta* RetiraCartaEscolhida(tListaCartas* cartas, tCarta* trunfo, int param)
{
    tCarta *aux = cartas -> lista;
    while(aux != NULL)
    {
        switch(param)
        {
            case NADA:
                if(CartaSemValor(aux, trunfo))
                {
                    return RetiraCarta(cartas, PosicaoDaCarta(aux, cartas));
                }
                break;
            case PONTO:
                if(CartaPonto(aux, trunfo))
                {
                    return RetiraCarta(cartas, PosicaoDaCarta(aux, cartas));
                }
                break;
            case TRUNFO:
                if(CartaTrunfo(aux, trunfo))
                {
                    return RetiraCarta(cartas, PosicaoDaCarta(aux, cartas));
                }
                break;
            case BISCA:
                if(CartaBisca(aux, trunfo))
                {
                    return RetiraCarta(cartas, PosicaoDaCarta(aux, cartas));
                }
                break;
        }
        aux = aux -> proximo;
    }

    return RetiraCarta(cartas, 1);
}

tCarta* IACartaJogada(tJogador* jogador, tMesa* mesa, int dificuldade)
{
    tCarta *retirada;
    switch(dificuldade)
    {
        case 1:
            retirada = RetiraCarta(jogador -> mao, 1 + rand() % TamListaCartas(jogador -> mao));
            break;
        case 2:
            if(TemBiscaLista(mesa -> monte, mesa -> trunfo))
            {
                if(TemTrunfoLista(jogador -> mao, mesa -> trunfo))
                {
                    retirada = RetiraCartaEscolhida(jogador -> mao, mesa -> trunfo, TRUNFO);
                }
                else if(TemNadaLista(jogador -> mao, mesa -> trunfo))
                {
                    retirada = RetiraCartaEscolhida(jogador -> mao, mesa -> trunfo, NADA);
                }
                else if(TemPontoLista(jogador -> mao, mesa -> trunfo))
                {
                    retirada = RetiraCartaEscolhida(jogador -> mao, mesa -> trunfo, PONTO);
                }
                else if(TemBiscaLista(jogador -> mao, mesa -> trunfo))
                {
                    retirada = RetiraCartaEscolhida(jogador -> mao, mesa -> trunfo, BISCA);
                }
                else
                {
                    retirada = RetiraCarta(jogador -> mao, 1 + rand() % TamListaCartas(jogador -> mao));
                }
            }
            else if(TemTrunfoLista(mesa -> monte, mesa -> trunfo))
            {
                if(TemTrunfoLista(jogador -> mao, mesa -> trunfo))
                {
                    retirada = RetiraCartaEscolhida(jogador -> mao, mesa -> trunfo, TRUNFO);
                }
                else if(TemNadaLista(jogador -> mao, mesa -> trunfo))
                {   
                    retirada = RetiraCartaEscolhida(jogador -> mao, mesa -> trunfo, NADA);
                }
                else if(TemPontoLista(jogador -> mao, mesa -> trunfo))
                {
                    retirada = RetiraCartaEscolhida(jogador -> mao, mesa -> trunfo, PONTO);
                }
                else if(TemBiscaLista(jogador -> mao, mesa -> trunfo))
                {
                    retirada = RetiraCartaEscolhida(jogador -> mao, mesa -> trunfo, BISCA);
                }
                else
                {
                    retirada = RetiraCarta(jogador -> mao, 1 + rand() % TamListaCartas(jogador -> mao));
                }
            }
            else if(TemPontoLista(mesa -> monte, mesa -> trunfo))
            {
                if(TemTrunfoLista(jogador -> mao, mesa -> trunfo))
                {
                    retirada = RetiraCartaEscolhida(jogador -> mao, mesa -> trunfo, TRUNFO);
                }
                else if(TemNadaLista(jogador -> mao, mesa -> trunfo))
                {   
                    retirada = RetiraCartaEscolhida(jogador -> mao, mesa -> trunfo, NADA);
                }
                else if(TemPontoLista(jogador -> mao, mesa -> trunfo))
                {
                    retirada = RetiraCartaEscolhida(jogador -> mao, mesa -> trunfo, PONTO);
                }
                else if(TemBiscaLista(jogador -> mao, mesa -> trunfo))
                {
                    retirada = RetiraCartaEscolhida(jogador -> mao, mesa -> trunfo, BISCA);
                }
                else
                {
                    retirada = RetiraCarta(jogador -> mao, 1 + rand() % TamListaCartas(jogador -> mao));
                }
            }
            else if(TemNadaLista(mesa -> monte, mesa -> trunfo))
            {
                if(TemNadaLista(jogador -> mao, mesa -> trunfo))
                {
                    retirada = RetiraCartaEscolhida(jogador -> mao, mesa -> trunfo, NADA);
                }
                else if(TemPontoLista(jogador -> mao, mesa -> trunfo))
                {
                    retirada = RetiraCartaEscolhida(jogador -> mao, mesa -> trunfo, PONTO);
                }
                else if(TemTrunfoLista(jogador -> mao, mesa -> trunfo))
                {
                    retirada = RetiraCartaEscolhida(jogador -> mao, mesa -> trunfo, TRUNFO);
                }
                else if(TemBiscaLista(jogador -> mao, mesa -> trunfo))
                {
                    retirada = RetiraCartaEscolhida(jogador -> mao, mesa -> trunfo, BISCA);
                }
                else 
                {
                    retirada = RetiraCarta(jogador -> mao, 1 + rand() % TamListaCartas(jogador -> mao));
                }
            }
            break;
    }

    return retirada;
}


int main(int argc, char *argv[])
{
    tListaJogadores *lJogadores;
    tMesa *mesa;
    int estado = 0;
    int dificuldade;
    int nJogadores;
    char opcao;

	srand(time(NULL));
	
    DesenhaEspaco(ALTURA + 25);//Funcao necessaria para exibicao dos valores do valgrind (desnecessario se nao usar o valgrind)

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
                    nJogadores = 2;
                }
                if(opcao == '4')
                {
                    nJogadores = 4;
                }
            }

            opcao = '-'; //Zera a opcao com um valor conhecido
            while(opcao != '1' && opcao != '2')
            {
                ApagaLinha(ALTURA + 2, 100);
                printf(">Dificuldade: ");
                opcao = getchar();
                if(opcao == '1')
                {
                    dificuldade = 1;
                }
                if(opcao == '2')
                {
                    dificuldade = 2;
                }
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
            tJogador *jogadorAtual;//Aponta para o jogador da vez
            tJogador *jogadorVencedor;
            tCarta *retirada; //Ponteiro temporario para salvar a carta retirada pelo jogador
            char chat[5][50] = { {" "}, {" "}, {" "}, {" "}, {" "} };
            char tmp[50]; //Guarda o valor temporario da mensagem a ser exibida no chat
            char comando;
            
            mesa = InicializaMesa();
            Embaralha(mesa -> baralho);
            sprintf(tmp, "Embaralhando...");
            AtualizaChat(chat, tmp);
            ImprimeChat(chat);

            lJogadores = NovaListaJogadores();
            AdicionaJogadores(lJogadores, mesa -> baralho, nJogadores);
            sprintf(tmp, "Distribuindo cartas...");
            AtualizaChat(chat, tmp);
            ImprimeChat(chat);

            jogadorAtual = DecidePrimeiroJogador(lJogadores);
            CortaBaralho(mesa);

            sprintf(tmp, "O Jogador %d cortou o baralho", IdentificadorJogador(jogadorAtual));
            AtualizaChat(chat, tmp);
            sprintf(tmp, "O trunfo da partida eh \"%s\"", RetornaNaipe(mesa -> trunfo -> naipe));
            AtualizaChat(chat, tmp);
            ImprimeChat(chat);
            
            DesenhaItensJogo(lJogadores);
            DesenhaBaralho(mesa -> baralho, argv[1]);
            DesenhaTrunfo(mesa -> trunfo);
            CursorPosicao(0, 28);
            
            DesenhaMaos(lJogadores, nJogadores, argv[1]);

            sprintf(tmp, "Iniciando partida... (0)");
            AtualizaChat(chat, tmp);
            ImprimeChat(chat);
            Espera();

            while(estado == EJOGO)
            {
                if(TamListaCartas(jogadorAtual -> mao) == 0)
                {
                    sprintf(tmp, "Fim de jogo!");
                    AtualizaChat(chat, tmp);
                    jogadorVencedor = DecideVencedor(lJogadores);
                    sprintf(tmp, "O jogador %d foi o vencedor!", IdJogador(jogadorVencedor));
                    AtualizaChat(chat, tmp);
                    ImprimeChat(chat);
                    break;
                }

                if(IdJogador(jogadorAtual) == 1)//Vez do jogador
                {
                    ApagaLinha(28, 100);
                    printf(">");
                    comando = getchar();
                    switch(comando)
                    {
                        case '1':
                            if(TamListaCartas(jogadorAtual -> mao) >= 1)
                            {
                                retirada = RetiraCarta(jogadorAtual -> mao, 1);
                                InsereCarta(mesa -> monte, retirada);

                                sprintf(tmp, "Voce jogou a carta %c%s", ConverteValor(ValorCarta(retirada)), RetornaNaipe(NaipeCarta(retirada)));
                                AtualizaChat(chat, tmp);
                            }
                            else
                            {
                                //Nao existe carta na posicao 1
                                sprintf(tmp, "Carta na posicao invalida");
                                AtualizaChat(chat, tmp);
                                comando = '-';
                            }
                            break;
                        case '2':

                            if(TamListaCartas(jogadorAtual -> mao) >= 2)
                            {
                                retirada = RetiraCarta(jogadorAtual -> mao, 2);
                                InsereCarta(mesa -> monte, retirada);

                                sprintf(tmp, "Voce jogou a carta %c%s", ConverteValor(ValorCarta(retirada)), RetornaNaipe(NaipeCarta(retirada)));
                                AtualizaChat(chat, tmp);
                            }
                            else
                            {
                                //Nao existe carta na posicao 2
                                sprintf(tmp, "Carta na posicao invalida");
                                AtualizaChat(chat, tmp);
                                comando = '-';
                            }
                            break;

                        case '3':
                            if(TamListaCartas(jogadorAtual -> mao) >= 3)
                            {
                                retirada = RetiraCarta(jogadorAtual -> mao, 3);
                                InsereCarta(mesa -> monte, retirada);

                                sprintf(tmp, "Voce jogou a carta %c%s", ConverteValor(ValorCarta(retirada)), RetornaNaipe(NaipeCarta(retirada)));
                                AtualizaChat(chat, tmp);
                            }
                            else
                            {
                                //Nao existe carta na posicao 3
                                sprintf(tmp, "Carta na posicao invalida");
                                AtualizaChat(chat, tmp);
                                comando = '-';
                            }
                            break;
                        //Embaralha as cartas novamente
                        case 'E':
                        case 'e':
                            if(strcmp(argv[1], "1") == 0)
                            {
                                Embaralha(mesa -> baralho);
                                DesenhaBaralho(mesa -> baralho, argv[1]);
                            }
                            break;

                        case 'C':
                        case 'c':
                            break;
                        //Mostra o baralho na ordem
                        case 'B':
                        case 'b':
                            if(strcmp(argv[1], "1") == 0)
                            {
                                MostraBaralho(mesa -> baralho);
                                getchar();
                                getchar();
                            }
                            break;
                        //Encerra a partida e volta ao menu
                        case 'M':
                        case 'm':
                            sprintf(tmp, "Encerrando partida... Abrindo menu...");
                            AtualizaChat(chat, tmp);
                            estado = EMENU;
                            break;
                        //Sai do programa
                        case 'S':
                        case 's':
                            sprintf(tmp, "Encerrando programa...");
                            AtualizaChat(chat, tmp);
                            estado = ESAIR;
                            break;
                    }
                }
                else
                {
                    //IA Joga
                    retirada = IACartaJogada(jogadorAtual, mesa, dificuldade);
                    InsereCarta(mesa -> monte, retirada);
                    sprintf(tmp, "Jogador %d jogou a carta %c%s", IdJogador(jogadorAtual), ConverteValor(ValorCarta(retirada)), RetornaNaipe(NaipeCarta(retirada)));
                    AtualizaChat(chat, tmp);
                    comando = '1';
                }

                ImprimeChat(chat);
                DesenhaMesa(mesa -> monte);

                switch(IdJogador(jogadorAtual))
                {
                    case 1:
                        DesenhaMao(jogadorAtual -> mao, 19, 15, "1");
                        break;
                    case 2:
                        DesenhaMao(jogadorAtual -> mao, 19, 1, argv[1]);
                        break;
                    case 3:
                        DesenhaMao(jogadorAtual -> mao, 49, 1, argv[1]);
                        break;
                    case 4:
                        DesenhaMao(jogadorAtual -> mao, 49, 15, argv[1]);
                        break;
                }
                
                if(comando == '1' || comando == '2' || comando == '3') //Verifica se o jogador jogou uma carta para prosseguir o jogo
                {
                    AvancaListaJogadores(lJogadores, 1);
                    jogadorAtual = lJogadores -> lista;
                }

                if(TamListaCartas(mesa -> monte) == nJogadores)
                {
                    DecideRodada(mesa, lJogadores);
                    jogadorAtual = lJogadores -> lista;
                    CalculaPontos(jogadorAtual);
                    DesenhaPontuacao(lJogadores);

                    sprintf(tmp, "O jogador %d venceu a rodada (0)", IdJogador(jogadorAtual));
                    AtualizaChat(chat, tmp);
                    ImprimeChat(chat);
                    Espera();
                    
                    if(TamListaCartas(mesa -> baralho) != 0)
                    {
                        sprintf(tmp, "Distribuindo cartas...");
                        AtualizaChat(chat, tmp);
                        ImprimeChat(chat);
                        DistribuiCartas(lJogadores, mesa -> baralho);
                        DesenhaMaos(lJogadores, nJogadores, argv[1]);
                        DesenhaBaralho(mesa -> baralho, argv[1]);
                    }
                    
                    DesenhaMesa(mesa -> monte);
                }
            }

            if(estado == EJOGO)
            {
                sprintf(tmp, "Voltar ao menu (0)");
                AtualizaChat(chat, tmp);
                ImprimeChat(chat);
                Espera();
                estado = EMENU;
            }

            LiberaListaJogadores(lJogadores);
            LiberaMesa(mesa);
            ApagaArea(0, 22, 73, 7);
        }
    }
    return 0;
}