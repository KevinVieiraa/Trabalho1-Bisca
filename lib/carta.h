#ifndef __CARTA_H
#define __CARTA_H

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
    int tamanho;
}tListaCartas;


/*
*  > Cria uma variavel valida do tipo carta
* - Inputs: O valor da carta e o naipe
* - Output: Um ponteiro para uma carta inicializada
* - Pre-condicao: Nenhum
* - Pos-condicao: Ponteiro inicializado
*/
tCarta* NovaCarta(int valor, int naipe);

/*
*  > Cria uma variavel do tipo lista de cartas
* - Inputs: Nenhum
* - Output: Um ponteiro para uma lista de cartas inicializada
* - Pre-condicao: Nenhum
* - Pos-condicao: Ponteiro inicializado
*/
tListaCartas* NovaListaCartas();

/*
*  > Modifica o tamanho da lista de cartas
* - Inputs: A lista a ser modificada e o valor
* - Output: Nenhum
* - Pre-condicao: A lista deve ter sido inicializada 
* - Pos-condicao: O tamanho da lista modificado
*/
void ModificaTamanho(tListaCartas* cartas, int valor);

/*
*  > Retorna o valor da carta
* - Inputs: A carta a ter o valor retornado
* - Output: O valor da carta
* - Pre-condicao: A carta tenha sido inicializada
* - Pos-condicao: Um numero inteiro retornado
*/
int ValorCarta(tCarta* carta);

/*
*  > Retorna o naipe da carta
* - Inputs: A carta ter o naipe retornado
* - Output: O naipe da carta
* - Pre-condicao: A carta tenha sido inicializada
* - Pos-condicao: Um numero inteiro retornado
*/
int NaipeCarta(tCarta* carta);

/*
*  > Insere uma carta em uma lista
* - Inputs: A lista a ser inserida a carta e a carta
* - Output: Nenhum
* - Pre-condicao: A lista e carta terem sido inicializadas 
* - Pos-condicao: Carta inserida na lista
*/
void InsereCarta(tListaCartas* cartas, tCarta* carta);

/*
*  > Verifica se a lista possui alguma carta com o naipe informado
* - Inputs: A lista a ser verificada e o naipe
* - Output: Um valor verdadeiro ou falso
* - Pre-condicao: A lista deve ter sido inicializada
* - Pos-condicao: Um numero inteiro retornado
*/
int BuscaPorNaipe(tListaCartas* cartas, int naipe);

/*
*  > Verifica se a carta e um trunfo
* - Inputs: A carta a ser verificada e o trunfo
* - Output: Um valor verdadeiro ou falso
* - Pre-condicao: A carta deve ter sido inicializada
* - Pos-condicao: Um numero inteiro retornado
*/
int CartaTrunfo(tCarta* carta, tCarta* trunfo);

/*
*  > Verifica se a carta e um ponto
* - Inputs: A carta a ser verificada e o trunfo
* - Output: Um valor verdadeiro ou falso
* - Pre-condicao: A carta deve ter sido inicializada
* - Pos-condicao: Um numero inteiro retornado
*/
int CartaPonto(tCarta* carta, tCarta* trunfo);

/*
*  > Verifica se a carta e uma bisca
* - Inputs: A carta a ser verificada e o trunfo
* - Output: Um valor verdadeiro ou falso
* - Pre-condicao: A carta deve ter sido inicializada
* - Pos-condicao: Um numero inteiro retornado
*/
int CartaBisca(tCarta* carta, tCarta* trunfo);

/*
*  > Verifica se a carta nao possui valor
* - Inputs: A carta a ser verificada e o trunfo
* - Output: Um valor verdadeiro ou falso
* - Pre-condicao: A carta deve ter sido inicializada
* - Pos-condicao: Um numero inteiro retornado
*/
int CartaSemValor(tCarta* carta, tCarta* trunfo);

/*
*  > Verifica se a lista possui cartas sem valor
* - Inputs: A lista a ser verificada e o trunfo
* - Output: Um valor verdadeiro ou falso
* - Pre-condicao: A lista deve ter sido inicializada
* - Pos-condicao: Um numero inteiro retornado
*/
int TemNadaLista(tListaCartas* cartas, tCarta* trunfo);

/*
*  > Verifica se a lista possui cartas que valem ponto
* - Inputs: A lista a ser verificada e o trunfo
* - Output: Um valor verdadeiro ou falso
* - Pre-condicao: A lista deve ter sido inicializada
* - Pos-condicao: Um numero inteiro retornado
*/
int TemPontoLista(tListaCartas* cartas, tCarta* trunfo);

/*
*  > Verifica se a lista possui cartas trunfo
* - Inputs: A lista a ser verificada e o trunfo
* - Output: Um valor verdadeiro ou falso
* - Pre-condicao: A lista deve ter sido inicializada
* - Pos-condicao: Um numero inteiro retornado
*/
int TemTrunfoLista(tListaCartas* cartas, tCarta* trunfo);

/*
*  > Verifica se a lista possui cartas bisca
* - Inputs: A lista a ser verificada e o trunfo
* - Output: Um valor verdadeiro ou falso
* - Pre-condicao: A lista deve ter sido inicializada
* - Pos-condicao: Um numero inteiro retornado
*/
int TemBiscaLista(tListaCartas* cartas, tCarta* trunfo);

/*
*  > Retira a primeira carta encontrada com o parametro informado
* - Inputs: A lista a ser retirada, o trunfo do jogo e o parametro 
* - Output: Um ponteiro para a carta
* - Pre-condicao: A lista e o trunfo devem ter sido inicializados
* - Pos-condicao: Ponteiro retornado valido
*/
tCarta* RetiraCartaEscolhida(tListaCartas* cartas, tCarta* trunfo, int param);

/*
*  > Retorna a posicao da carta informada
* - Inputs: A lista a ser verificada e a carta
* - Output: O valor da posicao da carta
* - Pre-condicao: A lista e a carta devem ter sido inicializadas
* - Pos-condicao: Um numero inteiro retornado
*/
int PosicaoDaCarta(tCarta* carta, tListaCartas* cartas);

/*
*  > Imprime a carta informada
* - Inputs: A carta a ser impressa
* - Output: Nenhum
* - Pre-condicao: A carta deve ter sido inicializada
* - Pos-condicao: A carta deve ter sido impressa no terminal
*/
void ImprimeCarta(tCarta* carta);

/*
*  > Imprime a lista de cartas informada
* - Inputs: A lista a ser impressa
* - Output: Nenhum
* - Pre-condicao: A lista deve ter sido inicializada
* - Pos-condicao: A lista deve ter sido impressa no terminal
*/
void ImprimeLista(tListaCartas* lista);

/*
*  > Retorna o tamanho da lista de cartas informada
* - Inputs: A lista cujo tamanho será informado
* - Output: O tamanho da lista
* - Pre-condicao: A lista deve ter sido inicializada
* - Pos-condicao: Um numero inteiro retornado
*/
int TamListaCartas(tListaCartas* cartas);

/*
*  > Remove a carta na posicao informada de uma lista
* - Inputs: A lista a ser removida a carta e a posicao
* - Output: O ponteiro para a carta removida
* - Pre-condicao: A lista deve ter sido inicializada
* - Pos-condicao: O ponteiro para a carta deve ser valido ou nulo caso a posicao nao exista
*/
tCarta* RetiraCarta(tListaCartas* cartas, int pos);

/*
*  > Embaralha uma lista de cartas
* - Inputs: A lista a ser embaralhada
* - Output: Nenhum
* - Pre-condicao: A lista deve ter sido inicializada
* - Pos-condicao: A ordem das cartas na lista deve ter sido trocada
*/
void Embaralha(tListaCartas* cartas);

/*
*  > Libera uma variavel do tipo lista de cartas da memoria
* - Inputs: A lista a ser liberada
* - Output: Nenhum
* - Pre-condicao: Nenhum 
* - Pos-condicao: Posicao da variavel liberada
*/
void LiberaLista(tListaCartas* cartas);
#endif