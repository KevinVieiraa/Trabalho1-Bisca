#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "lib/graficos.h"

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


typedef struct carta
{
 	int valor;
 	int naipe;
 	struct carta* proximo;
}tCarta;

typedef tCarta Endereco;

typedef struct listaCartas
{
    tCarta* lista;
    Endereco* ultimo;
    int tamanho;
}tListaCartas;

typedef struct jogador
{
    tListaCartas *mao;
    tListaCartas *pontosCartas;
    int pontos;
}tJogador;

typedef struct mesa
{
    tListaCartas *baralho;
    tListaCartas *monte;
    tCarta *corte;
}tMesa;


tCarta* NovaCarta(int valor, int naipe);
tListaCartas* NovaListaCartas();
void InsereCarta(tListaCartas  *cartas, tCarta *carta);
void InicializaBaralho(tListaCartas *baralho);
void ImprimeLista(tListaCartas *lista);
int TamLista(tListaCartas *cartas);
void ImprimeCarta(tCarta carta);
tCarta* RetiraCarta(tListaCartas *cartas, int pos);
void Embaralha(tListaCartas *cartas);

tCarta* NovaCarta(int valor, int naipe)
{
	tCarta *nova = (tCarta*)malloc(sizeof(tCarta));
	nova -> valor = valor;
	nova -> naipe = naipe;
	nova -> proximo = NULL;
	
	return nova;
}

tListaCartas* NovaListaCartas()
{
	tListaCartas *nova = (tListaCartas*)malloc(sizeof(tListaCartas));
	
	nova -> lista = NULL;
	nova -> ultimo = NULL;
    nova -> tamanho = 0;
	return nova;
}

void ModificaTamanho(tListaCartas *cartas, int valor)
{
    cartas -> tamanho += valor;
}

void InsereCarta(tListaCartas *cartas, tCarta *carta)
{
	if(cartas -> lista == NULL)
	{
		cartas -> lista = carta;
		cartas -> ultimo = carta;
        ModificaTamanho(cartas, 1);
	}
	else
	{
		cartas -> ultimo -> proximo = (tCarta*)carta;
		cartas -> ultimo = carta;
        ModificaTamanho(cartas, 1);
	}
}

void InicializaBaralho(tListaCartas *baralho)
{
    for(int i = 1;i <= 4;i++)
	{
		for(int j = 1;j <= 10;j++)
		{
			InsereCarta(baralho, NovaCarta(j + 1, i));
		}
	}
}

void ImprimeLista(tListaCartas *lista)
{
	if(lista != NULL && lista -> lista != NULL)
	{
		tCarta *aux = lista -> lista;
		while(aux != NULL)
		{
			ImprimeCarta(*aux);
			aux = aux -> proximo;
		}
	}
}

int TamLista(tListaCartas *cartas)
{
	return cartas -> tamanho;
}

char* RetornaNaipe(int naipe)
{
    switch(naipe)
    {
        case OUROS:
            return SIMBOLOOUROS;
            break;
        case PAUS:
            return SIMBOLOPAUS;
            break;
        case COPAS:
            return SIMBOLOCOPAS;
            break;
        case ESPADAS:
            return SIMBOLOESPADAS;
            break;
    }

    return "E";
}
void ImprimeCarta(tCarta carta)
{
    char naipe[4];

    switch(carta.naipe)
    {
        case OUROS:
            strcpy(naipe, SIMBOLOOUROS);
            break;
        case PAUS:
            strcpy(naipe, SIMBOLOPAUS);
            break;
        case COPAS:
            strcpy(naipe, SIMBOLOCOPAS);
            break;
        case ESPADAS:
            strcpy(naipe, SIMBOLOESPADAS);
            break;
    }
    printf("%s%c\n", naipe, ConverteValor(carta.valor));
}

void ApagaArea(int xInic, int yInic, int tamX, int tamY)
{
    for(int i = xInic; i < xInic + tamX; i++)
    {
        for(int j = yInic; j < yInic + tamY; j++)
        {
            CursorPosicao(i, j);
            printf(" ");
        }
    }
}


tCarta* RetiraCarta(tListaCartas *cartas, int pos)
{
	tCarta *carta;
	
    int tamanho = TamLista(cartas);
    if(tamanho != 0 && pos > 0 && pos <= tamanho)
    {
        if(pos == 1)
        {
            carta = cartas -> lista;
            cartas -> lista = carta -> proximo;
            carta -> proximo = NULL;
            if(tamanho == 1)
            {
                cartas -> ultimo = NULL;
            }
            ModificaTamanho(cartas, -1);
        }
        else
        {
            int i = 1;
            tCarta *aux = cartas -> lista;
            while(i < pos - 1)
            {
                aux = aux -> proximo;
                i++;
            }

            carta = aux -> proximo;
            aux -> proximo = carta -> proximo;
            carta -> proximo = NULL;
            if(cartas -> ultimo == carta && aux -> proximo == NULL)
            {
                cartas -> ultimo = aux;
            }
            ModificaTamanho(cartas, -1);
        }
    }
    else
    {
        carta = NULL;
    }
	
	return carta;
}

void Embaralha(tListaCartas *cartas)
{
	int tamanhoLista = TamLista(cartas);
	for(int i = 1; i < tamanhoLista*25 ; i++)
	{   
        InsereCarta(cartas, RetiraCarta(cartas, 1 + rand() % tamanhoLista));
	}
}

void LiberaLista(tListaCartas *cartas)
{
    tListaCartas *tmp = cartas;
    while(tmp -> lista != NULL)
    {
        tCarta *aux = tmp -> lista -> proximo;
        free(tmp -> lista);
        tmp -> lista = aux;
    }
    free(cartas);
}

void ImprimeChat(char chat[5][50])
{
    ApagaArea(1, ALTURA + 2, 50, 1);
    ApagaArea(1, ALTURA + 3, 50, 1);
    ApagaArea(1, ALTURA + 4, 50, 1);
    ApagaArea(1, ALTURA + 5, 50, 1);
    ApagaArea(1, ALTURA + 6, 50, 1);

    CursorPosicao(1, ALTURA + 2);
    printf("%s", chat[0]);
    CursorPosicao(1, ALTURA + 3);
    printf("%s", chat[1]);
    CursorPosicao(1, ALTURA + 4);
    printf("%s", chat[2]);
    CursorPosicao(1, ALTURA + 5);
    printf("%s", chat[3]);
    CursorPosicao(1, ALTURA + 6);
    printf("%s", chat[4]);
}

void AtualizaChat(char chat[5][50], char string[50])
{
    for(int i = 0; i < 4; i++ )
    {
        strcpy(chat[i], chat[i+1]);
    }
    strcpy(chat[4], string);
}

void Saca(tListaCartas *baralho, tListaCartas *maoDestino)
{
    InsereCarta(maoDestino, RetiraCarta(baralho, 1));
}

tJogador* InicializaJogador(tListaCartas *baralho)
{
    tJogador *novoJogador = (tJogador*)malloc(sizeof(tJogador));
    novoJogador -> mao = NovaListaCartas();
    novoJogador -> pontosCartas = NovaListaCartas();
    novoJogador -> pontos = 0;

    Saca(baralho, novoJogador -> mao);
    Saca(baralho, novoJogador -> mao);
    Saca(baralho, novoJogador -> mao);

    return novoJogador;
}

void LiberaJogador(tJogador *jogador)
{
    LiberaLista(jogador -> mao);
    LiberaLista(jogador -> pontosCartas);
    free(jogador);
}

tMesa* InicializaMesa()
{
    tMesa *novaMesa = (tMesa*)malloc(sizeof(tMesa));
    novaMesa -> baralho = NovaListaCartas();
    novaMesa -> monte = NovaListaCartas();
    novaMesa -> corte = NovaCarta(4, 4);

    InicializaBaralho(novaMesa -> baralho);

    return novaMesa;
}

void LiberaMesa(tMesa *mesa)
{
    LiberaLista(mesa -> baralho);
    LiberaLista(mesa -> monte);
    free(mesa -> corte);
    free(mesa);
}

void DesenhaMao(tListaCartas *mao, int posX, int posY, char* param)
{
    tCarta *carta1, *carta2, *carta3;
    int tam = TamLista(mao);
    int parametro = strcmp(param, "1") == 0;

    ApagaArea(posX, posY, 21, 5);

    switch(tam)
    {
        case 1:
            if(parametro)
            {
                carta1 = mao -> lista;
                DesenhaCarta(carta1 -> naipe, carta1 -> valor, posX + 7, posY);
            }
            else
            {
                DesenhaCaixa(posX + 7, posY, 7, 5);
            }
            break;
        case 2:
            if(parametro)
            {
                carta1 = mao -> lista;
                carta2 = carta1 -> proximo;
                carta3 = carta2 -> proximo;
                DesenhaCarta(carta1 -> naipe, carta1 -> valor, posX + 3, posY);
                DesenhaCarta(carta2 -> naipe, carta2 -> valor, posX + 10, posY);
            }
            else
            {
                DesenhaCaixa(posX + 3, posY, 7, 5);
                DesenhaCaixa(posX + 10, posY, 7, 5);
            }
            break;
        case 3:
            if(parametro)
            {
                carta1 = mao -> lista;
                carta2 = carta1 -> proximo;
                carta3 = carta2 -> proximo;
                DesenhaCarta(carta1 -> naipe, carta1 -> valor, posX, posY);
                DesenhaCarta(carta2 -> naipe, carta2 -> valor, posX + 7, posY);
                DesenhaCarta(carta3 -> naipe, carta3 -> valor, posX + 14, posY);
            }
            else
            {
                DesenhaCaixa(posX, posY, 7, 5);
                DesenhaCaixa(posX + 7, posY, 7, 5);
                DesenhaCaixa(posX + 14, posY, 7, 5);
            }
            break;
    }
}
/*
void DesenhaMao(tListaCartas *mao)
{
    tCarta *carta1, *carta2, *carta3;
    int tam = TamLista(mao);
    
    
    switch(tam)
    {
        case 1:
            carta1 = mao -> lista;
            DesenhaCarta(carta1 -> naipe, carta1 -> valor, 32, 15);
            CursorPosicao(35, 14);
            printf("1");
            break;
        case 2:
            carta1 = mao -> lista;
            carta2 = carta1 -> proximo;
            DesenhaCarta(carta1 -> naipe, carta1 -> valor, 28, 15);
            DesenhaCarta(carta2 -> naipe, carta2 -> valor, 35, 15);
            CursorPosicao(31, 14);
            printf("1");
            CursorPosicao(38, 14);
            printf("2");
            break;
        case 3:
            carta1 = mao -> lista;
            carta2 = carta1 -> proximo;
            carta3 = carta2 -> proximo;
            DesenhaCarta(carta1 -> naipe, carta1 -> valor, 25, 15);
            DesenhaCarta(carta2 -> naipe, carta2 -> valor, 32, 15);
            DesenhaCarta(carta3 -> naipe, carta3 -> valor, 39, 15);
            CursorPosicao(28, 14);
            printf("1");
            CursorPosicao(35, 14);
            printf("2");
            CursorPosicao(42, 14);
            printf("3");
            break;
    }
}*/

void DesenhaMesa(tListaCartas *monte, int jogadores)
{
    tCarta *carta1, *carta2, *carta3, *carta4;
    int tam = TamLista(monte);

    ApagaArea(24, 8, 28, 5);

    switch(tam)
        {
            case 1:
                carta1 = monte -> lista;
                DesenhaCarta(carta1 -> naipe, carta1 -> valor, 33, 8);
                break;
            case 2:
                carta1 = monte -> lista;
                carta2 = carta1 -> proximo;
                DesenhaCarta(carta1 -> naipe, carta1 -> valor, 31, 8);
                DesenhaCarta(carta2 -> naipe, carta2 -> valor, 38, 8);
                break;
            case 3:
                carta1 = monte -> lista;
                carta2 = carta1 -> proximo;
                carta3 = carta2 -> proximo;
                DesenhaCarta(carta1 -> naipe, carta1 -> valor, 28, 8);
                DesenhaCarta(carta2 -> naipe, carta2 -> valor, 35, 8);
                DesenhaCarta(carta3 -> naipe, carta3 -> valor, 42, 8);
                break;
            case 4: 
                carta1 = monte -> lista;
                carta2 = carta1 -> proximo;
                carta3 = carta2 -> proximo;
                carta4 = carta3 -> proximo;
                DesenhaCarta(carta1 -> naipe, carta1 -> valor, 24, 8);
                DesenhaCarta(carta2 -> naipe, carta2 -> valor, 31, 8);
                DesenhaCarta(carta3 -> naipe, carta3 -> valor, 38, 8);
                DesenhaCarta(carta4 -> naipe, carta4 -> valor, 45, 8);
                break;
        }
}

tCarta* IACartaJogada(tJogador *jogador, int dificuldade)
{
    tCarta *retirada = RetiraCarta(jogador -> mao, 1 + rand() % TamLista(jogador -> mao));

    
    return retirada;
    
}

int main(int argc, char *argv[])
{
    tJogador *jogador1, *jogador2, *jogador3, *jogador4;
    tMesa *mesa;
    int estado = 0, jogadores;
    char opcao, chat[5][50] = { {" "}, {" "}, {" "}, {" "}, {" "} };

	srand(time(NULL));
	
    Espaco(ALTURA + 9);
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
                                ImprimeChat(chat);
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
                    sleep(1);

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









