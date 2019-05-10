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

void LiberaJogador(tJogador* jogador)
{
    LiberaLista(jogador -> mao);
    LiberaLista(jogador -> pontosCartas);
    free(jogador);
}


tCarta* IACartaJogada(tJogador* jogador, int dificuldade)
{
    tCarta *retirada = RetiraCarta(jogador -> mao, 1 + rand() % TamLista(jogador -> mao));

    return retirada;
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

