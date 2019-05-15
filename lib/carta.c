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

//-----[Parametros das cartas]
#define NADA 1
#define PONTO 2
#define TRUNFO 3
#define BISCA 4

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

int CartaTrunfo(tCarta* carta, tCarta* trunfo)
{
    if(NaipeCarta(carta) == NaipeCarta(trunfo))
    {
        return 1;
    }
    return 0;
}

int CartaPonto(tCarta* carta, tCarta* trunfo)
{
    if(!CartaTrunfo(carta, trunfo) && ValorCarta(carta) >= 7 && ValorCarta(carta) <= 9)
    {
        return 1;
    }
    return 0;
}

int CartaBisca(tCarta* carta, tCarta* trunfo)
{
    if(!CartaTrunfo(carta, trunfo) && ValorCarta(carta) >= 10)
    {
        return 1;
    }
    return 0;
}

int CartaSemValor(tCarta* carta, tCarta* trunfo)
{
    if(!CartaBisca(carta, trunfo) && !CartaPonto(carta, trunfo) && !CartaTrunfo(carta, trunfo))
    {
        return 1;
    }
    return 0;
}

int TemNadaLista(tListaCartas* cartas, tCarta* trunfo)
{
    if(TamListaCartas(cartas) != 0)
    {
        tCarta* aux = cartas -> lista;
        while(aux != NULL)
        {
            if(CartaSemValor(aux, trunfo))
            {
                return 1;
            }   
            aux = aux -> proximo;
        }
    }
    else
    {
        return 1;
    }
    return 0;
}

int TemPontoLista(tListaCartas* cartas, tCarta* trunfo)
{
    if(TamListaCartas(cartas) != 0)
    {
        tCarta* aux = cartas -> lista;
        while(aux != NULL)
        {
            if(CartaPonto(aux, trunfo))
            {
                return 1;
            }   
            aux = aux -> proximo;
        }
    }
    return 0;
}

int TemTrunfoLista(tListaCartas* cartas, tCarta* trunfo)
{
    if(TamListaCartas(cartas) != 0)
    {
        tCarta* aux = cartas -> lista;
        while(aux != NULL)
        {
            if(CartaTrunfo(aux, trunfo))
            {
                return 1;
            }   
            aux = aux -> proximo;
        }
    }
    return 0;
}

int TemBiscaLista(tListaCartas* cartas, tCarta* trunfo)
{
    if(TamListaCartas(cartas) != 0)
    {
        tCarta* aux = cartas -> lista;
        while(aux != NULL)
        {
            if(CartaBisca(aux, trunfo))
            {
                return 1;
            }   
            aux = aux -> proximo;
        }
    }
    return 0;
}

tCarta* RetiraCartaEscolhida(tListaCartas* cartas, tCarta* trunfo, int param)
{
    tCarta *aux = cartas -> lista;
    while(aux != NULL)
    {
        switch(param)
        {
            case NADA:
                if(CartaSemValor(aux, trunfo))
                {
                    return RetiraCarta(cartas, PosicaoDaCarta(aux, cartas));
                }
                break;
            case PONTO:
                if(CartaPonto(aux, trunfo))
                {
                    return RetiraCarta(cartas, PosicaoDaCarta(aux, cartas));
                }
                break;
            case TRUNFO:
                if(CartaTrunfo(aux, trunfo))
                {
                    return RetiraCarta(cartas, PosicaoDaCarta(aux, cartas));
                }
                break;
            case BISCA:
                if(CartaBisca(aux, trunfo))
                {
                    return RetiraCarta(cartas, PosicaoDaCarta(aux, cartas));
                }
                break;
        }
        aux = aux -> proximo;
    }

    return RetiraCarta(cartas, 1);
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







