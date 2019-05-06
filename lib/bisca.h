#ifndef __MESA_H
#define __MESA_H

typedef struct carta tCarta;

typedef struct listaCartas tListaCartas;

typedef struct jogador
{
    tListaCartas* mao;
    tListaCartas* pontosCartas;
    struct jogador* prox;
    int pontos;
    int id;
}tJogador;

typedef tJogador Posicao;

typedef struct listaJogadores
{
    tJogador* lista;
    Posicao* primeiro;
    Posicao* ultimo;
    int tamanho;
}tListaJogadores;

typedef struct mesa
{
    tListaCartas* baralho;
    tListaCartas* monte;
    tCarta *corte;
}tMesa;



tJogador* CriaJogador(tListaCartas* lista, int identificador);

void LiberaJogador(tJogador* jogador);

tCarta* IACartaJogada(tJogador* jogador, int dificuldade);



tMesa* InicializaMesa();

void LiberaMesa(tMesa *mesa);

#endif