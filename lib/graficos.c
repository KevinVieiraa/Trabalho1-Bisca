#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAUS 1
#define OUROS 2
#define ESPADAS 3
#define COPAS 4

//-----[Simbolos dos Naipes]
#define SIMBOLOPAUS "\u2663"
#define SIMBOLOOUROS "\u2666"
#define SIMBOLOESPADAS "\u2660"
#define SIMBOLOCOPAS "\u2665"
//-----[Borda Simples]
#define DBOXH "\u2500"
#define DBOXV "\u2502"
#define DBOXUR "\u2514"
#define DBOXUL "\u2518"
#define DBOXDL "\u2510"
#define DBOXDR "\u250C"
//-----[Borda Dupla]
#define DDBOXH "\u2550"
#define DDBOXV "\u2551"
#define DDBOXUR "\u255A"
#define DDBOXUL "\u255D"
#define DDBOXDL "\u2557"
#define DDBOXDR "\u2554"
//-----[Dimensões da Janela]
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


void DesenhaLayout(int x, int y, int posX, int posY)
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

void ConverteNaipe(char string[], int valor)
{   
    switch(valor)
    {
        case OUROS:
            strcpy(string, SIMBOLOOUROS);
            break;
        case PAUS:
            strcpy(string, SIMBOLOPAUS);
            break;
        case COPAS:
            strcpy(string, SIMBOLOCOPAS);
            break;
        case ESPADAS:
            strcpy(string, SIMBOLOESPADAS);
            break;
    }
}

void DesenhaCarta(int naipeCarta, int valor, int xInicial, int yInicial)
{
    char naipe[4];
    char valorCarta = ConverteValor(valor);
    ConverteNaipe(naipe, naipeCarta);

    DesenhaCaixa(xInicial, yInicial, 7, 5);

    CursorPosicao(xInicial+1, yInicial+1);
    printf("%c", valorCarta);
    CursorPosicao(xInicial+3, yInicial+2);
    printf("%s", naipe);
    CursorPosicao(xInicial+5, yInicial+3);
    printf("%c", valorCarta);
}

void Espaco(int altura)
{
    for(int i = 0; i <= altura; i++)
    {
        printf("\n");
    }
}
void AtualizaPontuacao()
{
    CursorPosicao(LARGURA - 13, ALTURA + 3);
    printf("P1: 000");
    CursorPosicao(LARGURA - 13, ALTURA + 4);
    printf("P2: 000");
    CursorPosicao(LARGURA - 13, ALTURA + 5);
    printf("P3: 000");
    CursorPosicao(LARGURA - 13, ALTURA + 6);
    printf("P4: 000");
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


void DesenhaItensJogo()
{
    DesenhaLayout(LARGURA - 21, 6, 0, ALTURA + 1);
    DesenhaLayout(20, 6, LARGURA - 20, ALTURA + 1);
    CursorPosicao(LARGURA - 15, ALTURA + 2);
    printf(">PONTUACAO<");
    AtualizaPontuacao();
    DesenhaIndicesCartas();

    DesenhaCaixa(25, 15, 7, 5);
    DesenhaCaixa(32, 15, 7, 5);
    DesenhaCaixa(39, 15, 7, 5);

    DesenhaCaixa(2, 7, 7, 5);
    DesenhaCaixa(2, 12, 7, 5);

    DesenhaCaixa(21, 5, 7, 5);    
    DesenhaCaixa(28, 5, 7, 5);    
    DesenhaCaixa(35, 5, 7, 5);    
    DesenhaCaixa(42, 5, 7, 5);    
}

