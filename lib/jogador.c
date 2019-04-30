#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogador.h"
#include "carta.h"

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