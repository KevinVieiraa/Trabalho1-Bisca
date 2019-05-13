/*
*   Biblioteca - "Carta"
* Contem funcoes referentes à estrutura carta e
* à manipulaçao de listas do tipo carta.
*/

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

void ModificaTamanho(tListaCartas* cartas, int valor)
{
    cartas -> tamanho += valor;
}

int ValorCarta(tCarta* carta)
{
    return carta -> valor;
}

int NaipeCarta(tCarta* carta)
{
    return carta -> naipe;
}

int PosicaoDaCarta(tCarta* carta, tListaCartas* cartas)
{
    tCarta* aux = cartas -> lista;
    int pos = 1;

    while(aux != NULL)
    {
        if(NaipeCarta(aux) == NaipeCarta (carta) && ValorCarta(aux) == ValorCarta(carta))
        {
            return pos;
        }
        pos++;
        aux = aux -> proximo;
    }
    return 0;
}

int BuscaPorNaipe(tListaCartas* cartas, int naipe)
{
    tCarta* aux = cartas -> lista;
    while(aux != NULL)
    {
        if(NaipeCarta(aux) == naipe)
        {
            return 1;
        }
        aux = aux -> proximo;
    }
    return 0;
}

void InsereCarta(tListaCartas* cartas, tCarta* carta)
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

void InicializaBaralho(tListaCartas* baralho)
{
    for(int i = 1;i <= 4;i++)
	{
		for(int j = 1;j <= 10;j++)
		{
			InsereCarta(baralho, NovaCarta(j + 1, i));
		}
	}
}

void ImprimeCarta(tCarta* carta)
{
    printf("%s%c", RetornaNaipe(carta -> naipe), ConverteValor(carta -> valor));
}

void ImprimeLista(tListaCartas* lista)
{
	if(lista != NULL && lista -> lista != NULL)
	{
		tCarta *aux = lista -> lista;
		while(aux != NULL)
		{
			ImprimeCarta(aux);
			aux = aux -> proximo;
		}
	}
}

int TamListaCartas(tListaCartas* cartas)
{
	return cartas -> tamanho;
}

tCarta* RetiraCarta(tListaCartas* cartas, int pos)
{
	tCarta *carta;
	
    int tamanho = TamListaCartas(cartas);
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

void Embaralha(tListaCartas* cartas)
{
	int tamanhoLista = TamListaCartas(cartas);
	for(int i = 1; i < tamanhoLista*25 ; i++)
	{   
        InsereCarta(cartas, RetiraCarta(cartas, 1 + rand() % tamanhoLista));
	}
}

void LiberaLista(tListaCartas* cartas)
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

void Saca(tListaCartas* origem, tListaCartas* destino)
{
    InsereCarta(destino, RetiraCarta(origem, 1));
}





