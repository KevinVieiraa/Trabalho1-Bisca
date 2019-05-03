#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "carta.h"
#include "bisca.h"
#include "graficos.h"


tJogador* InicializaJogador(tListaCartas *baralho, int identificador)
{
    tJogador *novoJogador = (tJogador*)malloc(sizeof(tJogador));
    novoJogador -> mao = NovaListaCartas();
    novoJogador -> pontosCartas = NovaListaCartas();
    novoJogador -> pontos = 0;
    novoJogador -> id = identificador;

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


tCarta* IACartaJogada(tJogador *jogador, int dificuldade)
{
    tCarta *retirada = RetiraCarta(jogador -> mao, 1 + rand() % TamLista(jogador -> mao));

    return retirada;
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

