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
    tCarta *trunfo;
}tMesa;



tJogador* CriaJogador(tListaCartas* lista, int identificador);

tListaJogadores* NovaListaJogadores();

void ModificaTamanhoJogadores(tListaJogadores* lista, int valor);

int IdJogador(tJogador* jogador);

int PontosJogador(tJogador* jogador);

int IdentificadorJogador(tJogador* jogador);

int TamJogadores(tListaJogadores* jogadores);

void InsereJogador(tListaJogadores* jogadores, tJogador* jogador);

void AdicionaJogadores(tListaJogadores* jogadores, tListaCartas* listaOrigem, int qtd);

void ResetaListaJogadores(tListaJogadores* jogadores);

void AvancaListaJogadores(tListaJogadores* jogadores, int qtd);

tJogador* DecidePrimeiroJogador(tListaJogadores* jogadores);

void CortaBaralho(tMesa* mesa);

void DistribuiCartas(tListaJogadores* jogadores, tListaCartas* origem);

void DecideRodada(tMesa* mesa, tListaJogadores* jogadores);

void LiberaJogador(tJogador* jogador);

void LiberaListaJogadores(tListaJogadores* jogadores);

tCarta* IACartaJogada(tJogador* jogador, int dificuldade);



tMesa* InicializaMesa();

void LiberaMesa(tMesa *mesa);

#endif