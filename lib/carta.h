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

tCarta* NovaCarta(int valor, int naipe);

tListaCartas* NovaListaCartas();

void ModificaTamanho(tListaCartas* cartas, int valor);

int ValorCarta(tCarta* carta);

int NaipeCarta(tCarta* carta);

void InsereCarta(tListaCartas* cartas, tCarta* carta);

int BuscaPorNaipe(tListaCartas* cartas, int naipe);

int CartaTrunfo(tCarta* carta, tCarta* trunfo);

int CartaPonto(tCarta* carta, tCarta* trunfo);

int CartaBisca(tCarta* carta, tCarta* trunfo);

int CartaSemValor(tCarta* carta, tCarta* trunfo);

int TemNadaLista(tListaCartas* cartas, tCarta* trunfo);

int TemPontoLista(tListaCartas* cartas, tCarta* trunfo);

int TemTrunfoLista(tListaCartas* cartas, tCarta* trunfo);

int TemBiscaLista(tListaCartas* cartas, tCarta* trunfo);

tCarta* RetiraCartaEscolhida(tListaCartas* cartas, tCarta* trunfo, int param);

int PosicaoDaCarta(tCarta* carta, tListaCartas* cartas);

void ImprimeCarta(tCarta* carta);

void ImprimeLista(tListaCartas* lista);

int TamListaCartas(tListaCartas* cartas);

tCarta* RetiraCarta(tListaCartas* cartas, int pos);

void Embaralha(tListaCartas* cartas);

void LiberaLista(tListaCartas* cartas);
#endif