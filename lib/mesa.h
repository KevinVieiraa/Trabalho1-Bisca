#ifndef __MESA_H
#define __MESA_H

typedef struct carta tCarta;

typedef struct listaCartas tListaCartas;

typedef struct mesa
{
    tListaCartas *baralho;
    tListaCartas *monte;
    tCarta *corte;
}tMesa;

tMesa* InicializaMesa();

void LiberaMesa(tMesa *mesa);

void DesenhaMesa(tListaCartas *monte, int jogadores);

#endif