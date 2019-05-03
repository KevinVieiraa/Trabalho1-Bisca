#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jogador.h"
#include "carta.h"
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

