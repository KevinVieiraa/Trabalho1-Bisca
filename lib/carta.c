#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "carta.h"
#include "graficos.h"

tCarta* NovaCarta(int valor, int naipe)
{
	tCarta *nova = (tCarta*)malloc(sizeof(tCarta));
	nova -> valor = valor;
	nova -> naipe = naipe;
	nova -> proximo = NULL;
	
	return nova;
}

tListaCartas* NovaListaCartas()
{
	tListaCartas *nova = (tListaCartas*)malloc(sizeof(tListaCartas));
	
	nova -> lista = NULL;
	nova -> ultimo = NULL;
    nova -> tamanho = 0;
	return nova;
}

void ModificaTamanho(tListaCartas *cartas, int valor)
{
    cartas -> tamanho += valor;
}

void InsereCarta(tListaCartas *cartas, tCarta *carta)
{
	if(cartas -> lista == NULL)
	{
		cartas -> lista = carta;
		cartas -> ultimo = carta;
        ModificaTamanho(cartas, 1);
	}
	else
	{
		cartas -> ultimo -> proximo = (tCarta*)carta;
		cartas -> ultimo = carta;
        ModificaTamanho(cartas, 1);
	}
}

void InicializaBaralho(tListaCartas *baralho)
{
    for(int i = 1;i <= 4;i++)
	{
		for(int j = 1;j <= 10;j++)
		{
			InsereCarta(baralho, NovaCarta(j + 1, i));
		}
	}
}

void ImprimeCarta(tCarta carta)
{
    printf("%s%c\n", RetornaNaipe(carta.naipe), ConverteValor(carta.valor));
}

void ImprimeLista(tListaCartas *lista)
{
	if(lista != NULL && lista -> lista != NULL)
	{
		tCarta *aux = lista -> lista;
		while(aux != NULL)
		{
			ImprimeCarta(*aux);
			aux = aux -> proximo;
		}
	}
}

int TamLista(tListaCartas *cartas)
{
	return cartas -> tamanho;
}

tCarta* RetiraCarta(tListaCartas *cartas, int pos)
{
	tCarta *carta;
	
    int tamanho = TamLista(cartas);
    if(tamanho != 0 && pos > 0 && pos <= tamanho)
    {
        if(pos == 1)
        {
            carta = cartas -> lista;
            cartas -> lista = carta -> proximo;
            carta -> proximo = NULL;
            if(tamanho == 1)
            {
                cartas -> ultimo = NULL;
            }
            ModificaTamanho(cartas, -1);
        }
        else
        {
            int i = 1;
            tCarta *aux = cartas -> lista;
            while(i < pos - 1)
            {
                aux = aux -> proximo;
                i++;
            }

            carta = aux -> proximo;
            aux -> proximo = carta -> proximo;
            carta -> proximo = NULL;
            if(cartas -> ultimo == carta && aux -> proximo == NULL)
            {
                cartas -> ultimo = aux;
            }
            ModificaTamanho(cartas, -1);
        }
    }
    else
    {
        carta = NULL;
    }
	
	return carta;
}

void Embaralha(tListaCartas *cartas)
{
	int tamanhoLista = TamLista(cartas);
	for(int i = 1; i < tamanhoLista*25 ; i++)
	{   
        InsereCarta(cartas, RetiraCarta(cartas, 1 + rand() % tamanhoLista));
	}
}

void LiberaLista(tListaCartas *cartas)
{
    tListaCartas *tmp = cartas;
    while(tmp -> lista != NULL)
    {
        tCarta *aux = tmp -> lista -> proximo;
        free(tmp -> lista);
        tmp -> lista = aux;
    }
    free(cartas);
}

void Saca(tListaCartas *baralho, tListaCartas *maoDestino)
{
    InsereCarta(maoDestino, RetiraCarta(baralho, 1));
}


tJogador* InicializaJogador(tListaCartas *baralho)
{
    tJogador *novoJogador = (tJogador*)malloc(sizeof(tJogador));
    novoJogador -> mao = NovaListaCartas();
    novoJogador -> pontosCartas = NovaListaCartas();
    novoJogador -> pontos = 0;

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

void DesenhaMao(tListaCartas *mao, int posX, int posY, char* param)
{
    tCarta *carta1, *carta2, *carta3;
    int tam = TamLista(mao);
    int parametro = strcmp(param, "1") == 0;

    ApagaArea(posX, posY, 21, 5);

    switch(tam)
    {
        case 1:
            if(parametro)
            {
                carta1 = mao -> lista;
                DesenhaCarta(carta1 -> naipe, carta1 -> valor, posX + 7, posY);
            }
            else
            {
                DesenhaCaixa(posX + 7, posY, 7, 5);
            }
            break;
        case 2:
            if(parametro)
            {
                carta1 = mao -> lista;
                carta2 = carta1 -> proximo;
                carta3 = carta2 -> proximo;
                DesenhaCarta(carta1 -> naipe, carta1 -> valor, posX + 3, posY);
                DesenhaCarta(carta2 -> naipe, carta2 -> valor, posX + 10, posY);
            }
            else
            {
                DesenhaCaixa(posX + 3, posY, 7, 5);
                DesenhaCaixa(posX + 10, posY, 7, 5);
            }
            break;
        case 3:
            if(parametro)
            {
                carta1 = mao -> lista;
                carta2 = carta1 -> proximo;
                carta3 = carta2 -> proximo;
                DesenhaCarta(carta1 -> naipe, carta1 -> valor, posX, posY);
                DesenhaCarta(carta2 -> naipe, carta2 -> valor, posX + 7, posY);
                DesenhaCarta(carta3 -> naipe, carta3 -> valor, posX + 14, posY);
            }
            else
            {
                DesenhaCaixa(posX, posY, 7, 5);
                DesenhaCaixa(posX + 7, posY, 7, 5);
                DesenhaCaixa(posX + 14, posY, 7, 5);
            }
            break;
    }
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

void DesenhaMesa(tListaCartas *monte, int jogadores)
{
    tCarta *carta1, *carta2, *carta3, *carta4;
    int tam = TamLista(monte);

    ApagaArea(24, 8, 28, 5);

    switch(tam)
        {
            case 1:
                carta1 = monte -> lista;
                DesenhaCarta(carta1 -> naipe, carta1 -> valor, 33, 8);
                break;
            case 2:
                carta1 = monte -> lista;
                carta2 = carta1 -> proximo;
                DesenhaCarta(carta1 -> naipe, carta1 -> valor, 31, 8);
                DesenhaCarta(carta2 -> naipe, carta2 -> valor, 38, 8);
                break;
            case 3:
                carta1 = monte -> lista;
                carta2 = carta1 -> proximo;
                carta3 = carta2 -> proximo;
                DesenhaCarta(carta1 -> naipe, carta1 -> valor, 28, 8);
                DesenhaCarta(carta2 -> naipe, carta2 -> valor, 35, 8);
                DesenhaCarta(carta3 -> naipe, carta3 -> valor, 42, 8);
                break;
            case 4: 
                carta1 = monte -> lista;
                carta2 = carta1 -> proximo;
                carta3 = carta2 -> proximo;
                carta4 = carta3 -> proximo;
                DesenhaCarta(carta1 -> naipe, carta1 -> valor, 24, 8);
                DesenhaCarta(carta2 -> naipe, carta2 -> valor, 31, 8);
                DesenhaCarta(carta3 -> naipe, carta3 -> valor, 38, 8);
                DesenhaCarta(carta4 -> naipe, carta4 -> valor, 45, 8);
                break;
        }
}