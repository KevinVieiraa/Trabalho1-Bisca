#ifndef __CARTA_H
#define __CARTA_H

typedef struct carta
{
 	int valor;
 	int naipe;
 	struct carta* proximo;
}tCarta;

typedef tCarta Endereco;

typedef struct listaCartas
{
    tCarta* lista;
    Endereco* ultimo;
    int tamanho;
}tListaCartas;

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

tCarta* NovaCarta(int valor, int naipe);

tListaCartas* NovaListaCartas();

void ModificaTamanho(tListaCartas *cartas, int valor);

void InsereCarta(tListaCartas *cartas, tCarta *carta);

void InicializaBaralho(tListaCartas *baralho);

void ImprimeCarta(tCarta carta);

void ImprimeLista(tListaCartas *lista);

int TamLista(tListaCartas *cartas);

tCarta* RetiraCarta(tListaCartas *cartas, int pos);

void Embaralha(tListaCartas *cartas);

void LiberaLista(tListaCartas *cartas);

void Saca(tListaCartas *baralho, tListaCartas *maoDestino);


tJogador* InicializaJogador(tListaCartas *baralho);

void LiberaJogador(tJogador *jogador);

void DesenhaMao(tListaCartas *mao, int posX, int posY, char* param);

tCarta* IACartaJogada(tJogador *jogador, int dificuldade);


tMesa* InicializaMesa();

void LiberaMesa(tMesa *mesa);

void DesenhaMesa(tListaCartas *monte, int jogadores);
#endif