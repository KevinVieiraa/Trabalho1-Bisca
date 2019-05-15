#ifndef __BISCA_H
#define __BISCA_H

typedef struct carta tCarta;

typedef struct listaCartas tListaCartas;

typedef struct jogador
{
    tListaCartas* mao;
    tListaCartas* pontosCartas;
    struct jogador* prox;
    int pontos;
    int id;
}tJogador;

typedef tJogador Posicao;

typedef struct listaJogadores
{
    tJogador* lista;
    Posicao* primeiro;
    Posicao* ultimo;
    int tamanho;
}tListaJogadores;

typedef struct mesa
{
    tListaCartas* baralho;
    tListaCartas* monte;
    tCarta *trunfo;
}tMesa;

/*
*  > Aloca e cria um novo jogador
* - Inputs: Uma lista de onde irao ser sacadas as cartas e um identificador
* - Output: Um ponteiro para um jogador inicializado
* - Pre-condicao: A lista informada deve ter no minimo tamanho 3
* - Pos-condicao: Jogador inicializado
*/
tJogador* CriaJogador(tListaCartas* lista, int identificador);

/*
*  > Aloca uma lista circular de jogadores
* - Inputs: Nenhum
* - Output: Ponteiro para lista inicializada
* - Pre-condicao: Nenhum
* - Pos-condicao: Lista inicializada
*/
tListaJogadores* NovaListaJogadores();

/*
*  > Modifica o tamanho da lista de jogadores informada
* - Inputs: A lista a ser modificada e o valor (positivo ou negativo)
* - Output: A lista com tamanho modificado
* - Pre-condicao: Nenhum
* - Pos-condicao: Lista com seu tamanho alterado
*/
void ModificaTamanhoJogadores(tListaJogadores* lista, int valor);

/*
*  > Retorna o identificador de um jogador
* - Inputs: O jogador a ser informado o id
* - Output: O identificador do jogador
* - Pre-condicao: Jogador deve ter sido inicializado
* - Pos-condicao: Numero inteiro retornado
*/
int IdJogador(tJogador* jogador);

/*
*  > Retorna os pontos de um jogador
* - Inputs: O jogador a ser informado os pontos
* - Output: Os pontos do jogador
* - Pre-condicao: Jogador deve ter sido inicializado
* - Pos-condicao: Numero inteiro retornado
*/
int PontosJogador(tJogador* jogador);

/*
*  > Informa o tamanho de uma lista de jogadores
* - Inputs: A lista a ser informada o tamanho
* - Output: O tamanho da lista
* - Pre-condicao: A lista deve ter sido inicializada
* - Pos-condicao: Um valor inteiro retornado
*/
int TamJogadores(tListaJogadores* jogadores);

/*
*  > a
* - Inputs: 
* - Output: 
* - Pre-condicao: 
* - Pos-condicao: 
*/
void ModificaPontosJogador(tJogador* jogador, int valor);

/*
*  > a
* - Inputs: 
* - Output: 
* - Pre-condicao: 
* - Pos-condicao: 
*/
void CalculaPontos(tJogador* jogador);

/*
*  > a
* - Inputs: 
* - Output: 
* - Pre-condicao: 
* - Pos-condicao: 
*/
void InsereJogador(tListaJogadores* jogadores, tJogador* jogador);

/*
*  > a
* - Inputs: 
* - Output: 
* - Pre-condicao: 
* - Pos-condicao: 
*/
void AdicionaJogadores(tListaJogadores* jogadores, tListaCartas* listaOrigem, int qtd);

/*
*  > a
* - Inputs: 
* - Output: 
* - Pre-condicao: 
* - Pos-condicao: 
*/
void ResetaListaJogadores(tListaJogadores* jogadores);

/*
*  > a
* - Inputs: 
* - Output: 
* - Pre-condicao: 
* - Pos-condicao: 
*/
void AvancaListaJogadores(tListaJogadores* jogadores, int qtd);

/*
*  > a
* - Inputs: 
* - Output: 
* - Pre-condicao: 
* - Pos-condicao: 
*/
tJogador* DecidePrimeiroJogador(tListaJogadores* jogadores);

/*
*  > a
* - Inputs: 
* - Output: 
* - Pre-condicao: 
* - Pos-condicao: 
*/
void InicializaBaralho(tListaCartas* baralho);

/*
*  > a
* - Inputs: 
* - Output: 
* - Pre-condicao: 
* - Pos-condicao: 
*/
void CortaBaralho(tMesa* mesa);

/*
*  > a
* - Inputs: 
* - Output: 
* - Pre-condicao: 
* - Pos-condicao: 
*/
void Saca(tListaCartas* baralho, tListaCartas* maoDestino);

/*
*  > a
* - Inputs: 
* - Output: 
* - Pre-condicao: 
* - Pos-condicao: 
*/
void DistribuiCartas(tListaJogadores* jogadores, tListaCartas* origem);

/*
*  > a
* - Inputs: 
* - Output: 
* - Pre-condicao: 
* - Pos-condicao: 
*/
tCarta* IACartaJogada(tJogador* jogador, tMesa* mesa, int dificuldade);

/*
*  > a
* - Inputs: 
* - Output: 
* - Pre-condicao: 
* - Pos-condicao: 
*/
void DecideRodada(tMesa* mesa, tListaJogadores* jogadores);

/*
*  > a
* - Inputs: 
* - Output: 
* - Pre-condicao: 
* - Pos-condicao: 
*/
tJogador* DecideVencedor(tListaJogadores* jogadores);

/*
*  > a
* - Inputs: 
* - Output: 
* - Pre-condicao: 
* - Pos-condicao: 
*/
void LiberaJogador(tJogador* jogador);

/*
*  > a
* - Inputs: 
* - Output: 
* - Pre-condicao: 
* - Pos-condicao: 
*/
void LiberaListaJogadores(tListaJogadores* jogadores);

/*
*  > a
* - Inputs: 
* - Output: 
* - Pre-condicao: 
* - Pos-condicao: 
*/
tMesa* InicializaMesa();

/*
*  > a
* - Inputs: 
* - Output: 
* - Pre-condicao: 
* - Pos-condicao: 
*/
void LiberaMesa(tMesa *mesa);

/*
*  > a
* - Inputs: 
* - Output: 
* - Pre-condicao: 
* - Pos-condicao: 
*/
void Espera();
#endif