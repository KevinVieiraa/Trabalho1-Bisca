/*
*   Biblioteca - "Graficos"
* Contem funcoes responsaveis pelo conteudo 
* visual do programa. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graficos.h"
#include "carta.h"
#include "bisca.h"

//-----[Valores dos naipes]
#define PAUS 1
#define OUROS 2
#define ESPADAS 3
#define COPAS 4
//-----[Simbolos dos ñaipes]
#define SIMBOLOPAUS "\u2663"
#define SIMBOLOOUROS "\u2666"
#define SIMBOLOESPADAS "\u2660"
#define SIMBOLOCOPAS "\u2665"
//-----[Borda simples]
#define DBOXH "\u2500"
#define DBOXV "\u2502"
#define DBOXUR "\u2514"
#define DBOXUL "\u2518"
#define DBOXDL "\u2510"
#define DBOXDR "\u250C"
//-----[Borda dupla]
#define DDBOXH "\u2550"
#define DDBOXV "\u2551"
#define DDBOXUR "\u255A"
#define DDBOXUL "\u255D"
#define DDBOXDL "\u2557"
#define DDBOXDR "\u2554"
//-----[Dimensões da janela]
#define ALTURA 20
#define LARGURA 72

char ConverteValor(int valorCarta)
{
    char tmp;

    if(valorCarta < 7)
    {
        tmp = valorCarta + '0';
    }
    else
    {
        switch( valorCarta )
        {
            case 7:
                tmp = 'J';
                break;
            case 8:
                tmp = 'Q';
                break;
            case 9:
                tmp = 'K';
                break;
            case 10: 
                tmp = '7';
                break;
            case 11:
                tmp = 'A';
        }
    }

    return tmp;
}

void CursorPosicao(int XPos, int YPos) 
{
    printf("\033[%d;%dH",YPos+1,XPos+1);
}


void DesenhaBordaDupla(int x, int y, int posX, int posY)
{
    CursorPosicao(posX, posY);
    for(int i = 0; i <= y; i++)
    {
        for(int j = 0; j <= x; j++ )
        {
            if(i == 0 && j == 0)
            {
                printf("%s", DDBOXDR);
            }
            else if( i == 0 && j == x)
            {
                printf("%s", DDBOXDL);
            }
            else if( i == y && j == 0 ) 
            {
                printf("%s", DDBOXUR);
            }
            else if( i == y && j == x )
            {
                printf("%s", DDBOXUL);
            }
            else if( i == 0 || i == y )
            {
                printf("%s", DDBOXH);
            }
            else if( j == 0 || j == x )
            {
                printf("%s", DDBOXV);
            }
            else 
            {
                printf(" ");
            }

        }
        CursorPosicao(posX, posY + i + 1);
    }
}


void DesenhaCaixa(int x, int y, int tamX, int tamY)
{
    CursorPosicao(x, y);
    for(int i = 0; i < tamY; i++)
    {
        CursorPosicao(x, y + i);
        for(int j = 0; j < tamX; j++ )
        {
            if(i == 0)
            {
                if(j == 0)
                {
                    printf("%s", DBOXDR);
                }
                else if(j == tamX-1)
                {
                    printf("%s", DBOXDL);
                }
                else
                {
                    printf("%s", DBOXH);
                }
            }
            else if(i >= 1 && i < tamY-1)
            {
                if(j == 0 || j == tamX-1)
                {
                    printf("%s", DBOXV);
                }
                else
                {
                    printf(" ");
                }
            }
            else if(i == tamY-1)
            {
                if(j == 0)
                {
                    printf("%s", DBOXUR);
                }
                else if(j == tamX-1)
                {
                    printf("%s", DBOXUL);
                }
                else
                {
                    printf("%s", DBOXH);
                }
            }

        }
    }
}

void DesenhaCarta(int naipeCarta, int valor, int xInicial, int yInicial)
{
    char *naipe = RetornaNaipe(naipeCarta);
    char valorCarta = ConverteValor(valor);

    DesenhaCaixa(xInicial, yInicial, 7, 5);

    CursorPosicao(xInicial+1, yInicial+1);
    printf("%c", valorCarta);
    CursorPosicao(xInicial+3, yInicial+2);
    printf("%s", naipe);
    CursorPosicao(xInicial+5, yInicial+3);
    printf("%c", valorCarta);
}

void DesenhaEspaco(int altura)
{
    for(int i = 0; i <= altura; i++)
    {
        printf("\n");
    }
}

void DesenhaPontuacao(tListaJogadores* jogadores)
{
    int tamanho = TamJogadores(jogadores);
    tJogador *aux = jogadores -> primeiro;
    
    for(int i = 1; i <= tamanho; i++)
    {
        CursorPosicao(LARGURA - 13, ALTURA + 2 + i);
        printf("P%d: %d", aux -> id, aux -> pontos);
        aux = aux -> prox;
    }
}

void DesenhaIndicesCartas()
{
        CursorPosicao(28, 14);
        printf("1");
        CursorPosicao(35, 14);
        printf("2");
        CursorPosicao(42, 14);
        printf("3");
}


void DesenhaItensMenu()
{
    CursorPosicao(28, 12);
    printf("(1) - Iniciar Jogo");
    CursorPosicao(28, 13);
    printf("(2) - Instrucoes");
    CursorPosicao(28, 14);
    printf("(3) - Sair");
    CursorPosicao(1, ALTURA - 4);
    DesenhaCarta(1 + rand() % 3, 2 + rand() % 8, 18, 5);
    DesenhaCarta(1 + rand() % 3, 2 + rand() % 8, 25, 5);
    DesenhaCarta(1 + rand() % 3, 2 + rand() % 8, 32, 5);
    DesenhaCarta(1 + rand() % 3, 2 + rand() % 8, 39, 5);
    DesenhaCarta(1 + rand() % 3, 2 + rand() % 8, 46, 5);
    CursorPosicao(0, ALTURA+1);
}


void DesenhaItensAjuda()
{
    CursorPosicao(28, 14);
    printf("(0) - Voltar");
    CursorPosicao(0, ALTURA+1);
}


void DesenhaItensConfig()
{
    CursorPosicao((LARGURA - 6)/2 , 4);
    printf("OPCOES");

    CursorPosicao(11, 7);
    printf(">Jogadores<");
    CursorPosicao(10, 9);
    printf("(2) Jogadores");
    CursorPosicao(10, 10);
    printf("(4) Jogadores");

    CursorPosicao(LARGURA - 23, 7);
    printf(">Dificuldade<");
    CursorPosicao(LARGURA - 22, 9);
    printf("(1) - Facil");
    CursorPosicao(LARGURA - 22, 10);
    printf("(2) - Medio");

    CursorPosicao(0, ALTURA+1);
}


void ApagaLinha(int linha, int tamanho)
{
    CursorPosicao(0, linha);
    for(int i = 0; i < tamanho; i++)
    {
        printf(" ");
    }
    CursorPosicao(0, linha);
}

void DesenhaItensJogo(tListaJogadores* jogadores)
{
    DesenhaBordaDupla(LARGURA, ALTURA, 0, 0);
    DesenhaBordaDupla(LARGURA - 21, 6, 0, ALTURA + 1);
    DesenhaBordaDupla(20, 6, LARGURA - 20, ALTURA + 1);
    CursorPosicao(LARGURA - 15, ALTURA + 2);
    printf(">PONTUACAO<");
    DesenhaPontuacao(jogadores);
}

void DesenhaBaralho(tListaCartas* baralho, char* param)
{
    tCarta *tmp = baralho -> lista;
    int parametro = strcmp(param, "1") == 0;
    if(TamListaCartas(baralho) != 0)
    {
        if(parametro)
        {
            CursorPosicao(1, 5);
            printf("Restantes:");
            CursorPosicao(1, 6);
            printf("%d Cartas", TamListaCartas(baralho));
            DesenhaCarta(tmp -> naipe, tmp -> valor, 1, 7);
        }
        else
        {
            DesenhaCaixa(1, 7, 7, 5);
            CursorPosicao(3, 9);
            printf("%d", TamListaCartas(baralho));
        }
    }
    else
    {
        ApagaArea(1, 5, 10, 6);
        DesenhaCaixa(1, 7, 7, 5);
        CursorPosicao(3, 9);
    }
}

void DesenhaMaos(tListaJogadores* jogadores, int numJogadores, char* param)
{
    tJogador *aux = jogadores -> primeiro;
    for(int i = 1; i < numJogadores + 1; i++)
    {
        switch(IdJogador(aux))
        {
            case 1:
                DesenhaMao(aux -> mao, 19, 15, "1");
                break;
            case 2:
                DesenhaMao(aux -> mao, 19, 1, param);
                break;
            case 3:
                DesenhaMao(aux -> mao, 49, 1, param);
                break;
            case 4:
                DesenhaMao(aux -> mao, 49, 15, param);
                break;
        }
        aux = aux -> prox;
    }
}

char* RetornaNaipe(int naipe)
{
    switch(naipe)
    {
        case OUROS:
            return SIMBOLOOUROS;
            break;
        case PAUS:
            return SIMBOLOPAUS;
            break;
        case COPAS:
            return SIMBOLOCOPAS;
            break;
        case ESPADAS:
            return SIMBOLOESPADAS;
            break;
    }

    return "E";
}

void ApagaArea(int xInic, int yInic, int tamX, int tamY)
{
    for(int i = xInic; i < xInic + tamX; i++)
    {
        for(int j = yInic; j < yInic + tamY; j++)
        {
            CursorPosicao(i, j);
            printf(" ");
        }
    }
    CursorPosicao(xInic, yInic);
}


void ImprimeChat(char chat[5][50])
{
    ApagaArea(1, ALTURA + 2, 50, 1);
    ApagaArea(1, ALTURA + 3, 50, 1);
    ApagaArea(1, ALTURA + 4, 50, 1);
    ApagaArea(1, ALTURA + 5, 50, 1);
    ApagaArea(1, ALTURA + 6, 50, 1);

    CursorPosicao(1, ALTURA + 2);
    printf("%s", chat[0]);
    CursorPosicao(1, ALTURA + 3);
    printf("%s", chat[1]);
    CursorPosicao(1, ALTURA + 4);
    printf("%s", chat[2]);
    CursorPosicao(1, ALTURA + 5);
    printf("%s", chat[3]);
    CursorPosicao(1, ALTURA + 6);
    printf("%s", chat[4]);
}

void AtualizaChat(char chat[5][50], char string[50])
{
    for(int i = 0; i < 4; i++ )
    {
        strcpy(chat[i], chat[i+1]);
    }
    strcpy(chat[4], string);
}

void DesenhaMao(tListaCartas *mao, int posX, int posY, char* param)
{
    tCarta *carta1, *carta2, *carta3;
    int tam = TamListaCartas(mao);
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

void MostraBaralho(tListaCartas* baralho)
{
    tCarta *aux = baralho -> lista;

    ApagaArea(1, 22, 50, 5);
    CursorPosicao(5, 22);
    printf("Cartas no baralho:");
    for(int i = 1; i <= 4; i++)
    {
        CursorPosicao(5, 22 + i);
        for(int j = 1; j <= TamListaCartas(baralho)/4; j++)
        {
            ImprimeCarta(aux);
            printf(" ");
            aux = aux -> proximo;
        }
    }
}

void DesenhaTrunfo(tCarta* trunfo)
{
    CursorPosicao(1, 12);
    printf("Trunfo:");
    DesenhaCarta(trunfo -> naipe, trunfo -> valor, 1, 13);
}

void DesenhaMesa(tListaCartas *monte)
{
    tCarta *carta1, *carta2, *carta3, *carta4;
    int tam = TamListaCartas(monte);

    ApagaArea(28, 8, 29, 5);

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
            DesenhaCarta(carta1 -> naipe, carta1 -> valor, 29, 8);
            DesenhaCarta(carta2 -> naipe, carta2 -> valor, 36, 8);
            DesenhaCarta(carta3 -> naipe, carta3 -> valor, 43, 8);
            DesenhaCarta(carta4 -> naipe, carta4 -> valor, 50, 8);
            break;
    }
}