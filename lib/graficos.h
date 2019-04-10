#ifndef __GRAFICOS_H
#define __GRAFICOS_H
void AtualizaPontuacao();
void ApagaLinha(int linha, int tamanho);
void CursorPosicao(int XPos, int YPos);
char ConverteValor(int valorCarta);
void ConverteNaipe(char string[], int valor);
void DesenhaLayout(int x, int y, int posX, int posY);
void DesenhaCaixa(int x, int y, int tamX, int tamY);
void DesenhaCarta(int naipeCarta, int valor, int xInicial, int yInicial);
void DesenhaIndicesCartas();
void DesenhaItensMenu();
void DesenhaItensAjuda();
void DesenhaItensConfig();
void DesenhaItensJogo();
void Espaco(int altura);
#endif