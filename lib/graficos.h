#ifndef __GRAFICOS_H
#define __GRAFICOS_H

typedef struct carta tCarta;

typedef struct listaCartas tListaCartas;

typedef struct jogador tJogador;

typedef struct mesa tMesa;

/*
*  > Apaga uma linha
*  - Inputs: linha a ser apagada, tamanho do espaco
*  - Output: linha apagada
*  - Pre-condicao: nenhuma
*  - Pos-condicao: linha apagada e cursor no comeco da linha
*/
void ApagaLinha(int linha, int tamanho);

/*
*  > Define a posicao do cursor
* - Inputs: coordenada x e y do cursor
* - Output: cursor posicionado em x, y
* - Pre-condicao: nenhuma
* - Pos-condicao: cursor posicionado na coordenada informada
*/
void CursorPosicao(int XPos, int YPos);

/*
*  > Converte o valor da carta para um char correspondente
* - Inputs: um valor a ser convertido
* - Output: o valor correspondente em char
* - Pre-condicao: o numero informado deve estar entre 2 e 11
* - Pos-condicao: resultado convertido entre '2' e 'A'
*/
char ConverteValor(int valorCarta);

/*
*  > Retorna o caractere especial do naipe
* - Inputs: um valor a ser convertido
* - Output: o valor correspondente em forma de simbolo especial
* - Pre-condicao: o valor informado deve estar entre 1 e 4
* - Pos-condicao: um ponteiro contendo o valor correspondente em unicode do simbolo
*/
char* RetornaNaipe(int naipe);

/*
*  > Desenha uma janela com borda dupla
* - Inputs: a altura e largura da janela e as coordenadas x e y onde sera desenhado
* - Output: a janela de tamanho b e altura h desenhado na posicao (x, y)
* - Pre-condicao: valores informados apenas positivos
* - Pos-condicao: janela desenhada
*/
void DesenhaBordaDupla(int x, int y, int posX, int posY);

/* 
*  > Desenha uma caixa com uma borda simples
* - Inputs: a altura e largura da caixa e as coordenadas x e y onde sera desenhado
* - Output: a caixa de tamanho b e altura h desenhado na posicao (x, y)
* - Pre-condicao: valores informados apenas positivos
* - Pos-condicao: a caixa desenhada
*/
void DesenhaCaixa(int x, int y, int tamX, int tamY);

/*
*  > Desenha uma carta com as informacoes
* - Inputs: o naipe da carta, o valor contido e as coordenadas x e y onde sera desenhado
* - Output: uma carta de tamanho fix com o naipe e o simbolo desenhados na posicao (x, y)
* - Pre-condicao: o naipe deve estar entre 1 e 4, o valor deve estar entre 2 e 11 e as coordenadas devem ser positivas
* - Pos-condicao: a carta desenhada
*/
void DesenhaCarta(int naipeCarta, int valor, int xInicial, int yInicial);

void DesenhaIndicesCartas();

/*
*  > Desenha os itens da janela "menu"
* - Inputs: nenhum
* - Output: 
* - Pre-condicao: nenhum
* - Pos-condicao: 
*/
void DesenhaItensMenu();

void DesenhaItensAjuda();

void DesenhaItensConfig();

void DesenhaItensJogo();

void DesenhaEspaco(int altura);

void DesenhaPontuacao(int jogadores);

/*
*  > Apaga uma area do terminal informada
* - Inputs: as coordenadas (x, y) iniciais e a largura e altura da area a ser apagada
* - Output: uma area do terminal em branco
* - Pre-condicao: apenas valores positivos
* - Pos-condicao: 
*/
void ApagaArea(int xInic, int yInic, int tamX, int tamY);

char** NovoChat();

void ImprimeChat(char chat[5][50]);

void AtualizaChat(char chat[5][50], char string[50]);

void DesenhaMao(tListaCartas* mao, int posX, int posY, char* param);

void DesenhaMesa(tListaCartas* monte);
#endif