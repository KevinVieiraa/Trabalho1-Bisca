/*
*   Biblioteca - "Bisca"
* Contem funcoes especificas referentes ao jogo de bisca,
* como decisão de jogada pela "cpu", distribuiçao de cartas, etc...
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "carta.h"
#include "bisca.h"
#include "graficos.h"

//-----[Parametros das cartas]
#define NADA 1
#define PONTO 2
#define TRUNFO 3
#define BISCA 4

tJogador* CriaJogador(tListaCartas* lista, int identificador)
{
    tJogador *novoJogador = (tJogador*)malloc(sizeof(tJogador));
    novoJogador -> mao = NovaListaCartas();
    novoJogador -> pontosCartas = NovaListaCartas();
    novoJogador -> pontos = 0;
    novoJogador -> id = identificador;
    novoJogador -> prox = NULL;

    int i = 0;
    while(i < 3)
    {
        Saca(lista, novoJogador -> mao);
        i++;
    }

    return novoJogador;
}

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

int IdJogador(tJogador* jogador)
{
    return jogador -> id;
}

int PontosJogador(tJogador* jogador)
{
    return jogador -> pontos;
}

int TamJogadores(tListaJogadores* jogadores)
{
    return jogadores -> tamanho;
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

void AdicionaJogadores(tListaJogadores* jogadores, tListaCartas* listaOrigem, int qtd)
{
    for(int i = 1; i <= qtd; i++)
    {
        tJogador *tmp = CriaJogador(listaOrigem, i);
        InsereJogador(jogadores, tmp);
    }
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
    int idSelecionado = 1 + rand() % TamJogadores(jogadores);
    while(jogadores -> lista -> id != idSelecionado)
    {
        AvancaListaJogadores(jogadores, 1);
    }
    return jogadores -> lista;
}

void InicializaBaralho(tListaCartas* baralho)
{
    for(int i = 1;i <= 4;i++)
	{
		for(int j = 1;j <= 10;j++)
		{
			InsereCarta(baralho, NovaCarta(j + 1, i));
		}
	}
}

void CortaBaralho(tMesa* mesa)
{
    InsereCarta(mesa -> baralho, RetiraCarta(mesa -> baralho, 1 + rand() % TamListaCartas(mesa -> baralho)));
    mesa -> trunfo = mesa -> baralho -> ultimo;
}

void Saca(tListaCartas* origem, tListaCartas* destino)
{
    InsereCarta(destino, RetiraCarta(origem, 1));
}

void DistribuiCartas(tListaJogadores* jogadores, tListaCartas* origem)
{
    int qtd = TamJogadores(jogadores);
    tJogador *aux = jogadores -> lista;
    for(int i = 1; i <= qtd; i++)
    {
        InsereCarta(aux -> mao, RetiraCarta(origem, 1));
        aux = aux -> prox;
    }
    aux = aux -> prox;
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

void DecideRodada(tMesa* mesa, tListaJogadores* jogadores)
{   
    tCarta* cartaGanhadora = NULL;
    tCarta* aux = mesa -> monte -> lista;
    int posicaoCarta;

    if(BuscaPorNaipe(mesa -> monte, NaipeCarta(mesa -> trunfo)))
    {
        while(aux != NULL)
        {
            if(NaipeCarta(aux) == NaipeCarta(mesa -> trunfo))
            {
                if(NULL == cartaGanhadora)
                {
                    cartaGanhadora = aux;
                }
                else if(ValorCarta(cartaGanhadora) < ValorCarta(aux))
                {
                    cartaGanhadora = aux;
                }
            }
            aux = aux -> proximo;
        }
    }
    else
    {
        cartaGanhadora = aux;
        aux = aux -> proximo;
        while(aux != NULL)
        {
            if(NaipeCarta(aux) == NaipeCarta(cartaGanhadora) && ValorCarta(aux) > ValorCarta(cartaGanhadora))
            {
                cartaGanhadora = aux;
            }
            aux = aux -> proximo;
        }
    }
    
    posicaoCarta = PosicaoDaCarta(cartaGanhadora, mesa -> monte);
    AvancaListaJogadores(jogadores, posicaoCarta - 1);
    int tamanho = TamListaCartas(mesa -> monte);
    for(int i = 1; i <= tamanho; i++)
    {
        InsereCarta(jogadores -> lista -> pontosCartas, RetiraCarta(mesa -> monte, 1));
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

void LiberaJogador(tJogador* jogador)
{
    LiberaLista(jogador -> mao);
    LiberaLista(jogador -> pontosCartas);
    free(jogador);
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


tMesa* InicializaMesa()
{
    tMesa *novaMesa = (tMesa*)malloc(sizeof(tMesa));
    novaMesa -> baralho = NovaListaCartas();
    novaMesa -> monte = NovaListaCartas();
    novaMesa -> trunfo = NULL;

    InicializaBaralho(novaMesa -> baralho);

    return novaMesa;
}

void LiberaMesa(tMesa* mesa)
{
    LiberaLista(mesa -> baralho);
    LiberaLista(mesa -> monte);
    free(mesa);
}

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