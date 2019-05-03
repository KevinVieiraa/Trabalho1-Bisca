#ifndef __MESA_H
#define __MESA_H

typedef struct carta tCarta;

typedef struct listaCartas tListaCartas;

typedef struct jogador
{
    tListaCartas *mao;
    tListaCartas *pontosCartas;
    int pontos;
    int id;
}tJogador;

typedef struct mesa
{
    tListaCartas *baralho;
    tListaCartas *monte;
    tCarta *corte;
}tMesa;



tJogador* InicializaJogador(tListaCartas *baralho, int identificador);

void LiberaJogador(tJogador *jogador);

tCarta* IACartaJogada(tJogador *jogador, int dificuldade);



tMesa* InicializaMesa();

void LiberaMesa(tMesa *mesa);

#endif