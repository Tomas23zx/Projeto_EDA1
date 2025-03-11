#ifndef GRUPO6_FUNCOES_H
#define GRUPO6_FUNCOES_H
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>
using namespace std;

struct Peca {
    string marca;
    string categoria;
    int numero_serie;
    int preco;
};
struct seccao {
    char letra;
    string categoria;
    int capacidade;
    int tempopromo;
    double promocao;
    int quantidade;
    int faturacao;
    Peca *pecas;
    int*registo=new int[50];
};
int numerodesec();
int gerarPreco();
bool prob();
int capacidade(int n);
void lerficheiro(string marcas[], string categorias[], int& nmarcas, int& ncategorias);
void dia(int num_secoes,seccao*sec,Peca*produto,int num_encomendas, Peca pecas[],string marcas[], int num_marcas, string categorias[], int num_categorias, int argc,char *argv[]);
int faturacao(seccao*sec, int num_seccoes);

Peca escolherProdutoAleatorio(string marcas[], int num_marcas, string categorias[], int num_categorias,Peca*produto);
void preencherProdutos(Peca* produtos, int num_encomendas, string marcas[], int num_marcas, string categorias[], int num_categorias);

void meterprod(seccao *sec, Peca *produtos, int num_secoes, int &num_encomendas, string marcas[], int num_marcas, string categorias[], int num_categorias);



void menu(int num_secoes,seccao*sec,int num_encomendas,Peca*produtos);

void preenche(int num_secoes,seccao*sec,int num_encomendas, string marcas[], int num_marcas, string categorias[], int num_categorias,Peca*produtos);
void tirapecas(seccao *sec, int indice_secao, int indice_peca);













#endif //GRUPO6_FUNCOES_H
