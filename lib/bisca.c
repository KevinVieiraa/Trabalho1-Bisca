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

int IdentificadorJogador(tJogador* jogador)
{
    return jogador -> id;
}

int TamJogadores(tListaJogadores* jogadores)
{
    return jogadores -> tamanho;
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

void CortaBaralho(tMesa* mesa)
{
    InsereCarta(mesa -> baralho, RetiraCarta(mesa -> baralho, 1 + rand() % TamListaCartas(mesa -> baralho)));
    mesa -> trunfo = mesa -> baralho -> ultimo;
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

