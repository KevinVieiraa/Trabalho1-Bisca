#ifndef __JOGADOR_H
#define __JOGADOR_H

typedef struct carta tCarta;

typedef struct listaCartas tListaCartas;

typedef struct jogador
{
    tListaCartas *mao;
    tListaCartas *pontosCartas;
    int pontos;
    int id;
}tJogador;

tJogador* InicializaJogador(tListaCartas *baralho, int identificador);

void LiberaJogador(tJogador *jogador);

tCarta* IACartaJogada(tJogador *jogador, int dificuldade);

#endif