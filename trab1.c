#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lib/graficos.h"

#define ESAIR -1
#define EMENU 0
#define ECONFIG 1
#define EAJUDA 2
#define EJOGO 3

//-----[Dimensões da Janela]
#define ALTURA 20
#define LARGURA 72

#define SIMBOLOPAUS "\u2663"
#define SIMBOLOOUROS "\u2666"
#define SIMBOLOESPADAS "\u2660"
#define SIMBOLOCOPAS "\u2665"

#define PAUS 1
#define OUROS 2
#define ESPADAS 3
#define COPAS 4

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
}tListaCartas;

tCarta* NovaCarta(int valor, int naipe);
tListaCartas* NovaListaCartas();
void InsereCarta(tListaCartas  *cartas, tCarta *carta);
void InicializaBaralho(tListaCartas *baralho);
void ImprimeLista(tListaCartas *lista);
int TamLista(tListaCartas *cartas);
void ImprimeCarta(tCarta carta);
tCarta* RetiraCarta(tListaCartas *cartas, int pos);
void Embaralha(tListaCartas *cartas);

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
	return nova;
}

void InsereCarta(tListaCartas *cartas, tCarta *carta)
{
	if(cartas -> lista == NULL)
	{
		cartas -> lista = carta;
		cartas -> ultimo = carta;
	}
	else
	{
		cartas -> ultimo -> proximo = (tCarta*)carta;
		cartas -> ultimo = carta;
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
	int i = 1;
	
	if(cartas == NULL || cartas -> lista == NULL)
	{
		return 0;
	}
	else
	{
		tCarta *aux = cartas -> lista;
		while(aux != cartas -> ultimo)
		{
			i++;
			aux = aux -> proximo;
		}
	}
	
	return i;
}


void ImprimeCarta(tCarta carta)
{
    char naipe[4];

    switch(carta.naipe)
    {
        case OUROS:
            strcpy(naipe, SIMBOLOOUROS);
            break;
        case PAUS:
            strcpy(naipe, SIMBOLOPAUS);
            break;
        case COPAS:
            strcpy(naipe, SIMBOLOCOPAS);
            break;
        case ESPADAS:
            strcpy(naipe, SIMBOLOESPADAS);
            break;
    }
    printf("%s%c\n", naipe, ConverteValor(carta.valor));
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
                cartas -> ultimo == NULL;
            }
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
	for(int i = 1; i < tamanhoLista*4 ; i++)
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


int main()
{
    tListaCartas *baralho = NovaListaCartas();
    int estado = 0;
    char opcao;

	srand(time(NULL));
    
	InicializaBaralho(baralho);
	
	//printf("Baralho:\n");
	//ImprimeLista(baralho);
	int tam = TamLista(baralho);
	//printf("Tamanho: %d\n", tam);
	
	//printf("Baralho embaralhado:\n");
	Embaralha(baralho);
	//ImprimeLista(baralho);
	tam = TamLista(baralho);
	//printf("Tamanho: %d\n", tam);
	/*
	printf("Retirou a carta:\n");
	tCarta *retirada;
	retirada = RetiraCarta(baralho, 3);
	ImprimeCarta(*retirada);
	
	printf("Baralho:\n");
	ImprimeLista(baralho);
	tam = TamLista(baralho);
	printf("Tamanho: %d\n", tam);
    */
    getchar();
    Espaco(ALTURA + 6);
    while(1)
    {
        if(estado == EMENU)
        {
            opcao = '-';
            DesenhaLayout(LARGURA, ALTURA, 0, 0);
            DesenhaItensMenu();
            
            while( opcao != '1' && opcao != '2' && opcao != '3' )
            {
                printf(">");
                opcao = getchar();
                ApagaLinha(ALTURA + 1, 100);
            }

            switch(opcao)
            {
                case '1':
                    estado = 1;
                    break;
                case '2':
                    estado = 2;
                    break;
                case '3':
                    estado = -1;
            }

            ApagaLinha(ALTURA + 1, 100);
        }

        if(estado == ECONFIG)
        {
            opcao = '-';
            DesenhaLayout(LARGURA, ALTURA, 0, 0);
            DesenhaItensConfig();
            while(opcao <= '0' || opcao >= '3')
            {
                ApagaLinha(ALTURA + 1, 100);
                printf(">Jogadores: ");
                opcao = getchar();
            }

            opcao = '-';
            while(opcao <= '0' || opcao >= '3')
            {
                ApagaLinha(ALTURA + 2, 100);
                printf(">Dificuldade: ");
                opcao = getchar();
            }
            ApagaLinha(ALTURA + 1, 100);
            ApagaLinha(ALTURA + 2, 100);
            estado = 3;
        }

        if(estado == EAJUDA)
        {
            opcao = '-';
            DesenhaLayout(LARGURA, ALTURA, 0, 0);
            DesenhaItensAjuda();
            while( opcao != '0' )
            {
                printf(">");
                opcao = getchar();
                ApagaLinha(ALTURA + 1, 100);
            }

            estado = 0;
            ApagaLinha(ALTURA + 1, 100);
        }

        if(estado == EJOGO)
        {
            DesenhaLayout(LARGURA, ALTURA, 0, 0);
            DesenhaItensJogo();
            CursorPosicao(0, 28);
            while(1)
            {   
                printf(">");
                getchar();
                ApagaLinha(28, 100);
            }
            
        }

        if(estado == ESAIR)
        {
            LiberaLista(baralho);
            break;
        }
    }

    return 0;
}



/*
♠ - 6
♣ - 5
♦ - 4
♥ - 3

┌─────┐
│3    │
│  ♥  │
│    3│
└─────┘

*/









