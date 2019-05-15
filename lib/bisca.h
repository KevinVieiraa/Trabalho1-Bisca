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
*  > Modifica a quantidade de pontos de um jogador
* - Inputs: O jogador a ser modificado e o valor
* - Output: O jogador com os pontos modificados
* - Pre-condicao: Jogador deve ter sido inicializado
* - Pos-condicao: Pontos do jogador alterados
*/
void ModificaPontosJogador(tJogador* jogador, int valor);

/*
*  > Calcula os pontos totais de um jogador de acordo com as cartas que possui
* - Inputs: O jogador a calcular os pontos
* - Output: O jogador com os pontos calculados
* - Pre-condicao: Jogador deve ter sido inicializado
* - Pos-condicao: Pontos do jogador calculados
*/
void CalculaPontos(tJogador* jogador);

/*
*  > Insere um jogador em uma lista circular
* - Inputs: Jogador a ser inserido na lista
* - Output: Lista devidamente modificada
* - Pre-condicao: Jogador deve ter sido inicializado
* - Pos-condicao: Jogador inserido apontando para o primeiro jogador da lista
*/
void InsereJogador(tListaJogadores* jogadores, tJogador* jogador);

/*
*  > Cria e adiciona os jogadores da partida numa lista
* - Inputs: Uma lista, a lista de cartas e a quantidade de jogadores
* - Output: Lista com todos os jogadores inseridos
* - Pre-condicao: Lista de jogadores e de cartas devem ter sido inicializadas
* - Pos-condicao: Jogadores inseridos na lista
*/
void AdicionaJogadores(tListaJogadores* jogadores, tListaCartas* listaOrigem, int qtd);

/*
*  > Faz o apontador atual "lista" apontar para o primeiro
* - Inputs: A lista a ser resetada
* - Output: "lista" apontando para o primeiro elemento
* - Pre-condicao: Lista deve ter sido inicializada
* - Pos-condicao: Apontador "lista" igual ao apontador "primeiro"
*/
void ResetaListaJogadores(tListaJogadores* jogadores);

/*
*  > Faz o apontador atual "lista" apontar para o proximo jogador
* - Inputs: A lista a ser modificada
* - Output: "lista" apontando para o proximo elemento
* - Pre-condicao: Lista deve ter sido inicializada
* - Pos-condicao: Apontador "lista" igual ao apontador "lista -> proximo"
*/
void AvancaListaJogadores(tListaJogadores* jogadores, int qtd);

/*
*  > Escolhe o primeiro jogador a jogar a paritida
* - Inputs: A lista de jogadores e o tamanho dela
* - Output: Um ponteiro apontando para o jogador da lista a ser o primeiro
* - Pre-condicao: A lista deve ter sido inicializada
* - Pos-condicao: Ponteiro valido
*/
tJogador* DecidePrimeiroJogador(tListaJogadores* jogadores);

/*
*  > Inicializa o baralho com os devidos naipes e valores
* - Inputs: Um ponteiro para uma lista de cartas
* - Output: Uma lista de cartas com os valores corretos
* - Pre-condicao: O ponteiro para a lista deve ter sido inicializado
* - Pos-condicao: Todas as cartas inseridas na lista
*/
void InicializaBaralho(tListaCartas* baralho);

/*
*  > Escolhe o trunfo da partida
* - Inputs: A mesa atual da partida
* - Output: O trunfo devidamente escolhido
* - Pre-condicao: A mesa deve ter sido inicializada
* - Pos-condicao: O trunfo apontado corretamente
*/
void CortaBaralho(tMesa* mesa);

/*
*  > Saca uma carta da lista
* - Inputs: A lista a ser retirada a carta e a lista destino da carta
* - Output: A carta na lista destino
* - Pre-condicao: Ambas listas devem ter sido inicializadas
* - Pos-condicao: O endereço da carta removido da lista inicial e inserido na final
*/
void Saca(tListaCartas* baralho, tListaCartas* maoDestino);

/*
*  > Distribui as cartas para todos os jogadores
* - Inputs: A lista de jogadores e a lista de cartas origem
* - Output: As cartas distribuidas
* - Pre-condicao: As listas de jogadores e de cartas devem ter sido inicializadas
* - Pos-condicao: Todos receberem uma carta
*/
void DistribuiCartas(tListaJogadores* jogadores, tListaCartas* origem);

/*
*  > A I.A. Decide uma carta a ser jogada de acordo com as regras
* - Inputs: O jogador que irá jogar, a mesa destino e o nivel de dificuldade
* - Output: Uma carta escolhida
* - Pre-condicao: Jogador e mesa devem ser inicializados e a dificuldade válida.
* - Pos-condicao: Um ponteiro valido para uma carta escolhida
*/
tCarta* IACartaJogada(tJogador* jogador, tMesa* mesa, int dificuldade);

/*
*  > Decide quem venceu a rodada atual
* - Inputs: A mesa no estado atual e a lista de jogadores
* - Output: Nenhum
* - Pre-condicao: A mesa e jogadores devem ter sido inicializados
* - Pos-condicao: A lista de jogadores apontando para o vencedor da rodada
*/
void DecideRodada(tMesa* mesa, tListaJogadores* jogadores);

/*
*  > Decide o vencedor da partida
* - Inputs: A lista de jogadores
* - Output: O ponteiro para o jogador vencedor
* - Pre-condicao: A lista de jogadores ter sido inicializada
* - Pos-condicao: O jogador retornado deve ser valido
*/
tJogador* DecideVencedor(tListaJogadores* jogadores);

/*
*  > Libera a variavel do tipo jogador da memoria
* - Inputs: A variavel a ser liberada
* - Output: Nenhum
* - Pre-condicao: Nenhum
* - Pos-condicao: Posiçao de memoria liberada
*/
void LiberaJogador(tJogador* jogador);

/*
*  > Libera a variavel do tipo lista de jogadores da memoria
* - Inputs: A variiavel a ser liberada
* - Output: Nenhum
* - Pre-condicao: Nenhum
* - Pos-condicao: Posicao de memoria liberada
*/
void LiberaListaJogadores(tListaJogadores* jogadores);

/*
*  > Inicializa uma variavel do tipo mesa
* - Inputs: Nenhum
* - Output: Um ponteiro para uma variavel mesa inicializada
* - Pre-condicao: Nenhum
* - Pos-condicao: Ponteiro retornado seja valido
*/
tMesa* InicializaMesa();

/*
*  > Libera a variavel do tipo mesa da memoria
* - Inputs: A variiavel a ser liberada
* - Output: Nenhum
* - Pre-condicao: Nenhum
* - Pos-condicao: Posicao de memoria liberada
*/
void LiberaMesa(tMesa *mesa);

/*
*  > Espera o char '0' para poder continuar a executar o programa
* - Inputs: Nenhum
* - Output: Nenhum
* - Pre-condicao: Nenhum
* - Pos-condicao: Char correto inserido e execução continuada
*/
void Espera();
#endif