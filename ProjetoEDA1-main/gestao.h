#include "funcoes.h"
#include <string>

#ifndef PROJETO1EDA_GESTAO_H
#define PROJETO1EDA_GESTAO_H
void opcoes(int num_seccoes, seccao *sec,  Peca *produtos, int num_encomendas, Peca pecas[], string marcas[],int num_marcas, string categorias[], int num_categorias, int argc,char *argv[]);
void vendam(seccao*sec, int numerosec);
void promo( seccao*sec, int num_seccoes);
struct seccao *aplicaPromo(seccao *sec, int num_seccoes);

void alterar_categoria(seccao *sec, Peca *produtos, int numerosec, string categorias[], int num_categorias, int num_encomendas,  Peca *pecas, string marcas[], int num_marcas,int argc,char *argv[]) ;
void criasecao(int novotamanho, int num_seccao, seccao *sec, Peca*produtos, int num_encomendas, Peca *pecas, string marcas[], int num_marcas, string categorias[], int num_categorias,int argc,char *argv[]);
void grava_armazem(seccao*sec,Peca*prod, int tamanhosec, int tamanholc) ;
void carregar_armazem(seccao*sec,Peca*prod,int argc,char *argv[]);

void bubbleSortPorMarca(Peca* produtos, int num_encomendas);
void bubbleSortPorPreco(Peca *produtos, int num_produtos);

bool compararPorMarca(const Peca& p1, const Peca& p2);

void ordenarPorMarca(Peca* pecas, int tamanho);

void imprimir(seccao *secoes, int num_secoes, Peca *produtos, int num_pecas);








#endif //PROJETO1EDA_GESTAO_H
