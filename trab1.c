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


tListaJogadores* NovaListaJogadores()
{
    tListaJogadores *nova = (tListaJogadores*)malloc(sizeof(tListaJogadores));

    nova -> lista = NULL;
    nova -> primeiro = NULL;
    nova -> ultimo = NULL;
    nova -> tamanho = 0;

    return nova;
}

void ModificaTamanhoJogadores(tListaJogadores* lista, int valor)
{
    lista -> tamanho += valor;
}

void InsereJogador(tListaJogadores* jogadores, tJogador* jogador)
{
    if(jogadores != NULL && jogador != NULL)
    {
        if(jogadores -> lista == NULL)
        {
            jogadores -> lista = jogador;
            jogadores -> primeiro = jogador;
            jogadores -> ultimo = jogadores -> lista;
            jogador -> prox = jogador;
            ModificaTamanhoJogadores(jogadores, 1);
        }
        else
        {
            jogador -> prox = jogadores -> lista;
            jogadores -> ultimo -> prox = jogador;
            jogadores -> ultimo = jogador;
            ModificaTamanhoJogadores(jogadores, 1);
        }
    }
}

void LiberaListaJogadores(tListaJogadores* jogadores)
{
    jogadores -> lista = jogadores -> primeiro;
    tListaJogadores *tmp = jogadores;
    jogadores -> ultimo -> prox = NULL;
    while(tmp -> lista != NULL)
    {
        tJogador *aux = tmp -> lista -> prox;
        LiberaJogador(tmp->lista);
        tmp -> lista = aux;
    }
    free(jogadores);
}

void AdicionaJogadores(tListaJogadores* jogadores, tListaCartas* listaOrigem, int qtd)
{
    for(int i = 1; i <= qtd; i++)
    {
        tJogador *tmp = CriaJogador(listaOrigem, i);
        InsereJogador(jogadores, tmp);
    }
}

int TamJogadores(tListaJogadores* jogadores)
{
    return jogadores -> tamanho;
}

void ResetaListaJogadores(tListaJogadores* jogadores)
{
    jogadores -> lista = jogadores -> primeiro;
}

void AvancaListaJogadores(tListaJogadores* jogadores, int qtd)
{
    for(int i = 1; i <= qtd; i++)
    {
        jogadores -> lista = jogadores -> lista -> prox;
    }
}


tJogador* DecidePrimeiroJogador(tListaJogadores* jogadores)
{
    int idSelecionado = 1 /*+ rand() % TamJogadores(jogadores)*/;
    while(jogadores -> lista -> id != idSelecionado)
    {
        AvancaListaJogadores(jogadores, 1);
    }
    return jogadores -> lista;
}

void CortaBaralho(tMesa* mesa)
{
    InsereCarta(mesa -> baralho, RetiraCarta(mesa -> baralho, 1 + rand() % TamListaCartas(mesa -> baralho)));
    mesa -> trunfo = mesa -> baralho -> ultimo;
}

int IdJogador(tJogador* jogador)
{
    return jogador -> id;
}

int PontosJogador(tJogador* jogador)
{
    return jogador -> pontos;
}

int ValorCarta(tCarta* carta)
{
    return carta -> valor;
}

int NaipeCarta(tCarta* carta)
{
    return carta -> naipe;
}

int BuscaPorNaipe(tListaCartas* cartas, int naipe)
{
    tCarta* aux = cartas -> lista;
    while(aux != NULL)
    {
        if(NaipeCarta(aux) == naipe)
        {
            return 1;
        }
        aux = aux -> proximo;
    }
    return 0;
}

void BuscaPorValor()
{

}

void PrintaTeste(char* string, int x, int y)
{
    CursorPosicao(x, y);
    printf("%s", string);
}

void DecideRodada(tMesa* mesa, tListaJogadores* jogadores)
{   
    tCarta* cartaGanhadora;
    tListaCartas* aux = mesa -> monte;

    if(BuscaPorNaipe(mesa -> monte, NaipeCarta(mesa -> trunfo)))
    {
        while(aux -> lista != NULL)
        {
            if(NaipeCarta(aux -> lista) == NaipeCarta(mesa -> trunfo))
            {
                if(NULL == cartaGanhadora)
                {
                    cartaGanhadora = aux -> lista;
                }
                else if(ValorCarta(cartaGanhadora) < ValorCarta(aux -> lista))
                {
                    cartaGanhadora = aux -> lista;
                }
            }
            aux -> lista = aux -> lista -> proximo;
        }
    }
    else
    {
        
    }
}

void DesenhaBaralho(tListaCartas* baralho, char* param)
{
    tCarta *tmp = baralho -> lista;
    int parametro = strcmp(param, "1") == 0;
    if(parametro)
    {
        CursorPosicao(1, 5);
        printf("Restantes:");
        CursorPosicao(1, 6);
        printf("%d Cartas", TamListaCartas(baralho));
        DesenhaCarta(tmp -> naipe, tmp -> valor, 1, 7);
    }
    else
    {
        DesenhaCaixa(1, 7, 7, 5);
        CursorPosicao(3, 9);
        printf("%d", TamListaCartas(baralho));
    }
}


void DesenhaTrunfo(tCarta* trunfo)
{
    CursorPosicao(1, 12);
    printf("Trunfo:");
    DesenhaCarta(trunfo -> naipe, trunfo -> valor, 1, 13);
}

void MostraBaralho(tListaCartas* baralho)
{
    tCarta *aux = baralho -> lista;

    ApagaArea(1, 22, 50, 5);
    CursorPosicao(5, 22);
    printf("Cartas no baralho:");
    for(int i = 1; i <= 4; i++)
    {
        CursorPosicao(5, 22 + i);
        for(int j = 1; j <= TamListaCartas(baralho)/4; j++)
        {
            ImprimeCarta(aux);
            printf(" ");
            aux = aux -> proximo;
        }
    }
}

int IdentificadorJogador(tJogador* jogador)
{
    return jogador -> id;
}

int main(int argc, char *argv[])
{
    tListaJogadores *lJogadores;
    tMesa *mesa;
    int estado = 0;
    int nJogadores;
    char opcao;

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

            DesenhaItensJogo(nJogadores);
            DesenhaBaralho(mesa -> baralho, argv[1]);
            DesenhaTrunfo(mesa -> trunfo);
            CursorPosicao(0, 28);
            
            for(int i = 1; i < nJogadores + 1; i++)
            {
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
                AvancaListaJogadores(lJogadores, 1);
                jogadorAtual = lJogadores -> lista;
            }

            while(estado == EJOGO)
            {
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
                    retirada = IACartaJogada(jogadorAtual, 1);
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
                
                if(comando == '1' || comando == '2' || comando == '3')
                {
                    AvancaListaJogadores(lJogadores, 1);
                    jogadorAtual = lJogadores -> lista;
                }

                if(TamListaCartas(mesa -> monte) == nJogadores)
                {
                    DecideRodada(mesa, lJogadores);
                }
            }

            LiberaListaJogadores(lJogadores);
            LiberaMesa(mesa);
            estado = EMENU;
            ApagaArea(0, 22, 73, 7);
        }
    }
    return 0;
}