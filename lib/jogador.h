#ifndef __JOGADOR_H
#define __JOGADOR_H

typedef struct jogador
{
    tListaCartas *mao;
    tListaCartas *pontosCartas;
    int pontos;
    int id;
}tJogador;

tJogador* InicializaJogador(tListaCartas *baralho);

void LiberaJogador(tJogador *jogador);

void DesenhaMao(tListaCartas *mao, int posX, int posY, char* param);

tCarta* IACartaJogada(tJogador *jogador, int dificuldade);

#endif