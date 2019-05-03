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

#endif