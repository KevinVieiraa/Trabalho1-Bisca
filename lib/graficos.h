#ifndef __GRAFICOS_H
#define __GRAFICOS_H

typedef struct carta tCarta;

typedef struct listaCartas tListaCartas;

typedef struct jogador tJogador;

typedef struct listaJogadores tListaJogadores;

typedef struct mesa tMesa;

// > Apaga uma linha informada no terminal
void ApagaLinha(int linha, int tamanho);

// > Posiciona o cursor numa determinada posicao do terminal
void CursorPosicao(int XPos, int YPos);

// > Converte o valor da carta (2-11) em seu correspondente em char ('2' - 'A')
char ConverteValor(int valorCarta);

// > Retorna em formato unicode o naipe informado
char* RetornaNaipe(int naipe);

// > Desenha uma janela com o caractere do tipo 'linha dupla'
void DesenhaBordaDupla(int x, int y, int posX, int posY);

// > Desenha uma janela com o caractere do tipo 'linha simples'
void DesenhaCaixa(int x, int y, int tamX, int tamY);

// > Desenha uma carta com naipe e valor informado
void DesenhaCarta(int naipeCarta, int valor, int xInicial, int yInicial);

// > Desenha os itens especificos do estado "Menu"
void DesenhaItensMenu();

// > Desenha os itens específicos do estado "Ajuda"
void DesenhaItensAjuda();

// > Desenha os itens específicos do estado "Config"
void DesenhaItensConfig();

// > Desenha os itens especificos do estado "Jogo"
void DesenhaItensJogo();

// > Desenha a representação da primeira carta do baralho ou a primeira carta.
void DesenhaBaralho(tListaCartas* baralho, char* param);

// > Desenha as mãos de todos os jogadores
void DesenhaMaos(tListaJogadores* jogadores, int numJogadores, char* param);

// > Desenha um espaço em branco (necessario para o valgrind)
void DesenhaEspaco(int altura);

// > Desenha as pontuações dos jogadores
void DesenhaPontuacao(tListaJogadores* jogadores);

// > Apaga uma área do terminal informada
void ApagaArea(int xInic, int yInic, int tamX, int tamY);

// > Imprime todas as mensagens do chat
void ImprimeChat(char chat[5][50]);

// > Atualiza o chat, inserindo uma nova mensagem
void AtualizaChat(char chat[5][50], char string[50]);

// > Desenha uma mão de um jogador
void DesenhaMao(tListaCartas* mao, int posX, int posY, char* param);

// > Mostra, no chat, o baralho completo do jogo, na ordem em que ele esta
void MostraBaralho(tListaCartas* baralho, int nJogadores);

// > Desenha a representação da carta definida como trunfo no inicio da partida
void DesenhaTrunfo(tCarta* trunfo);

// > Desenha as cartas depositadas na mesa pelos jogadores
void DesenhaMesa(tListaCartas* monte);
#endif