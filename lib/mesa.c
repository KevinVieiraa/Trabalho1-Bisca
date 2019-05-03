#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jogador.h"
#include "carta.h"
#include "mesa.h"
#include "graficos.h"

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