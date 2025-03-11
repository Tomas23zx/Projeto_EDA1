#include <iostream>
#include "funcoes.h"
#include <iomanip>
#include <cstdlib>
#include <string>
#include <fstream>
#include "gestao.h"

using namespace std;

/**
 * Esta função calcula o número de secções que o armazém terá na primeira geração.
 * @return - número de secções
 */
int numerodesec(){
    return rand() % 4 + 7;
}

/**
 * Função que calcula a probabilidade de uma peça ser vendida, que será entre 5 e 50%.
 * @return - retorna true caso esta seja vendida e retorna false caso esta não seja.
 */
int gerarPreco() {
    int precoAleatorio = ((rand() % 178) + 2) * 5;
    return precoAleatorio;
}
/**
 *Função que calcula a probabilidade de uma peça ser vendida, caso seja vendida retorna true e caso contrário retorna false
 * @return
 */
bool prob() {
    int random_number = rand() % 46 + 5;
    int comp = rand() % 101;
    if (comp <= random_number){
        return true;
    }else{
        return false;
    }
}
/**
 * calcula a capacidade de cada seccao
 * @param n a seccao a qual e dirigida
 * @return guarda o valor da capacidade num array
 */
int capacidade(int n) {
    return rand() % 4 + 3;
}
/**
 * Função que lê os ficheiros de marcas e categorias e os armazenaa em arrays de strings, neste caso marcas para as marcas e categorias para as categorias
 * @param marcas  array que guarda as marcas que estão dentro do ficheiro
 * @param categorias array que irá armazenar as categorias que estão dentro do ficheiro
 * @param nmarcas número de marcas que existem dentro do ficheiro de marcas
 * @param ncategorias número de categorias que existem dentro do ficheiro de categorias
 */
void lerficheiro(string marcas[], string categorias[], int& nmarcas, int& ncategorias){
    const int MAX_MARCAS = 100;
    const int MAX_CATEGORIAS = 100;
    nmarcas=0;
    ncategorias=0;
    string linha;

    fstream ficheiroMarcas ("marcas.txt",ios::in);
    if(ficheiroMarcas.is_open()){
        while (getline(ficheiroMarcas, linha)){
            if (nmarcas<MAX_MARCAS){
                marcas[nmarcas++]=linha;
            }
        }
        ficheiroMarcas.close();
    }else{
        cerr<<"deu erro ao abrir o ficheiro de marcas"<<endl;
    }
    fstream ficheiroCategorias ("categorias.txt",ios::in);
    if(ficheiroCategorias.is_open()){
        while (getline(ficheiroCategorias, linha)){
            if (ncategorias<MAX_CATEGORIAS){
                categorias[ncategorias++]=linha;
            }
        }
        ficheiroCategorias.close();
    }else{
        cerr<<"deu erro ao abrir o ficheiro de categorias"<<endl;
    }
}

/**
 * Função que soma a faturação de cada uma das secções e retorna o total delas
 * @param sec apontador para a struct seccao
 * @param num_seccoes inteiro que dá o número de seccoes que foi gerado aleatoriamente no main
 * @return total da faturação
 */
int faturacao(seccao*sec, int num_seccoes) {
    int faturacao = 0;
    for (int j = 0; j < num_seccoes; ++j) {
        faturacao += sec[j].faturacao;
    }
    return faturacao;
}

/**
 *Função que escolhe aleatoriamente uma marca, uma categoria, um numero de serie e um preco para cada peça da lista de chegada
 * @param marcas array de strings que contem os nomes das marcas
 * @param num_marcas inteiro que contem a quantidade de marcas que contem o array
 * @param categorias array de strings que contem os nomes das categorias
 * @param num_categorias inteiro que contem a quantidade de categorias que contem o array
 * @param produtos apontador para a struct peça
 * @return retorna um apontador para a struct peça, com os valores que forem gerados
 */
Peca escolherProdutoAleatorio(string marcas[], int num_marcas, string categorias[], int num_categorias,Peca*produtos) {

    int indiceMarca = rand() % num_marcas;
    int indiceCategoria = rand() % num_categorias;
    int serie = rand() % 9000 + 1000;

    produtos->marca = marcas[indiceMarca];
    produtos->categoria = categorias[indiceCategoria];
    produtos->numero_serie = serie;
    produtos->preco = gerarPreco();

    return *produtos;
}
/**
 * Função que preenche o array de diferentes peças, neste caso para o primeiro ciclo,garantindo que cada peça seja secolhido apenas uma vez, nada se repita
 * @param produtos apontador para a struct peça
 * @param num_encomendas número de peças que irá ter a lista de chegada
 * @param marcas inteiro que contem a quantidade de marcas que contem o array
 * @param num_marcas inteiro que contem a quantidade de marcas que contem o array
 * @param categorias inteiro que contem a quantidade de categorias que contem o array
 * @param num_categorias inteiro que contem a quantidade de categorias que contem o array
 */
void preencherProdutos(Peca* produtos, int num_encomendas, string marcas[], int num_marcas, string categorias[], int num_categorias) {
    bool produtos_selecionados[10] = {false};

    for (int i = 0; i < 10; ++i) {

        int indice_produto;
        indice_produto = rand() % num_encomendas;
        produtos_selecionados[indice_produto] = true;

        produtos[i] = escolherProdutoAleatorio(marcas, num_marcas, categorias, num_categorias, &produtos[i]);
    }
}


/**
 * Função que preenche as secções com letras, categorias e capacidade aleatorias
 * @param num_secoes inteiro que dá o número de seccoes que foi gerado aleatoriamente no main
 * @param sec apontador para a struct secção
 * @param num_encomendas número de peças que irá ter a lista de chegada
 * @param marcas inteiro que contem a quantidade de marcas que contem o array
 * @param num_marcas inteiro que contem a quantidade de marcas que contem o array
 * @param categorias inteiro que contem a quantidade de categorias que contem o array
 * @param num_categorias inteiro que contem a quantidade de categorias que contem o array
 * @param produtos apontador para a struct peça
 */
void preenche(int num_secoes,seccao*sec,int num_encomendas, string marcas[], int num_marcas, string categorias[], int num_categorias,Peca*produtos){
    int j=0;
    const char letra[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K'};
    preencherProdutos(produtos,  num_encomendas, marcas,  num_marcas, categorias,  num_categorias);

    for (int i = 0; i < num_secoes; i++) {

        sec[i].categoria = produtos[j].categoria;
        sec[i].quantidade = 0;
        sec[i].letra = letra[i];
        sec[i].capacidade = capacidade(i);
        sec[i].faturacao = 0;
        sec[i].pecas = new Peca[sec[i].capacidade];
        j++;
    }
    menu( num_secoes,sec,num_encomendas,produtos);
}


/**
 * Função que tira peças de cada secção caso estas sejam vendidas
 * @param sec apontador para a struct secção
 * @param indice_secao indice da secção
 * @param indice_peca indice da peça
 * @param num_secoes inteiro que dá o número de seccoes que foi gerado aleatoriamente no main
 */
void tirapecas(seccao *sec, int indice_secao, int indice_peca) {
    for (int i = indice_peca; i < sec[indice_secao].quantidade - 1; i++) {
        sec[indice_secao].pecas[i] = sec[indice_secao].pecas[i + 1];
        sec[indice_secao].registo[i] = sec[indice_secao].pecas[i].numero_serie;

    }
    sec[indice_secao].quantidade--;

}


/**
 * Esta função coloca produtos dentro da lista de chegada no primeiro ciclo(três primeros for),com peças geradas com as categorias das secções criadas, depois esta adiciona 5 peças completamente novas em cada ciclo (quando clicamos d), esta tambem organiza as novas peças que chegam por marca e por fim aplica a percentagem da peça ser vendida, caso exista alguma peça dentro da secção
 * @param sec apontador para a struct secção
 * @param produtos  apontador para a struct peça
 * @param num_secoes inteiro que dá o número de seccoes que foi gerado aleatoriamente no main
 * @param num_encomendas número de peças que irá ter a lista de chegada
 * @param marcas inteiro que contem a quantidade de marcas que contem o array
 * @param num_marcas inteiro que contem a quantidade de marcas que contem o array
 * @param categorias inteiro que contem a quantidade de categorias que contem o array
 * @param num_categorias inteiro que contem a quantidade de categorias que contem o array
 */
void meterprod(seccao *sec, Peca *produtos, int num_secoes,  int &num_encomendas, string marcas[], int num_marcas, string categorias[], int num_categorias) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < num_encomendas; j++) {
            if (sec[i].quantidade < sec[i].capacidade && sec[i].categoria == produtos[j].categoria) {
                sec[i].pecas[sec[i].quantidade] = produtos[j];
                sec[i].quantidade++;
                for (int k = j; k < num_encomendas - 1; k++) {
                    produtos[k] = produtos[k + 1];
                }
                num_encomendas--;
                break;
            }
        }
    }

    const int MAX_ENCOMENDAS = 50;
    const int NUM_PECAS_EXTRA = 5;
    for (int i = 0; i < NUM_PECAS_EXTRA && num_encomendas < MAX_ENCOMENDAS; i++) {
        produtos[num_encomendas] = escolherProdutoAleatorio(marcas, num_marcas, categorias, num_categorias,&produtos[num_encomendas]);
        num_encomendas++;
    }
    menu(num_secoes, sec, num_encomendas, produtos);
    bubbleSortPorMarca(produtos, num_encomendas);
    for (int i = 0; i < num_secoes; i++) {
        if (prob() && sec[i].quantidade > 0) {
            sec[i].faturacao += sec[i].pecas[sec[i].quantidade - 1].preco;
            sec[i].quantidade--;
        }
    }

}
/**
 * Menu que imprime o armazem na consola, com todas as funões já geradas anteriormente
 * @param num_secoes inteiro que dá o número de seccoes que foi gerado aleatoriamente no main
 * @param sec apontador para a struct secção
 * @param num_encomendas número de peças que irá ter a lista de chegada
 * @param produtos  apontador para a struct peça
 */
void menu(int num_secoes,seccao*sec,int num_encomendas,Peca*produtos) {

    cout << "                      "<< "***********************************************************************************" << endl;
    cout << "                      "<< "********************** Armazem EDA | Total Faturacao: " << setw(6)<<faturacao(sec,num_secoes) << " "<< "**********************" << endl;
    cout << "                      "<< "***********************************************************************************" << endl;


    for (int i = 0; i < num_secoes; i++) {

        cout << "Seccao " << sec[i].letra << "| Categoria: " << sec[i].categoria << "| Capacidade: "
             << sec[i].capacidade << "| Quantidade:"
             << sec[i].quantidade << "| Faturacao: " << sec[i].faturacao << " euros" << endl;
        if (sec[i].quantidade != 0) {

            for (int j = 0; j < sec[i].quantidade; j++) {

                cout << "           "<<sec[i].pecas[j].marca<< " | " << sec[i].pecas[j].categoria << " | " <<sec[i].pecas[j].numero_serie<<" | ";
                if(sec[i].promocao == 1){
                    cout << sec[i].pecas[j].preco<< endl;
                }else if(sec[i].promocao > 1){
                    cout<< sec[i].pecas[j].preco*(1-(sec[i].promocao/100))<< endl;
                }else {
                    cout << sec[i].pecas[j].preco << endl;
                }
            }
        }
    }

    cout <<setw(7)<<""<<"************************************************" <<endl;
    cout <<setw(7)<<""<<"***************"<< " Lista de Chegada "<< "***************"<<endl;

    for (int i = 0; i < num_encomendas; ++i) {

        cout << produtos[i].marca << " | " << produtos[i].categoria << " | " << produtos[i].numero_serie << " | " << produtos[i].preco << " euros" << endl;
    }
    cout<<endl;

}

/**
 * Esta função permite-nos escolher entre simular um dia no armazem eda, entrar no menu de gestor ou terminar o programa em sair
 * @param num_secoes inteiro que dá o número de seccoes que foi gerado aleatoriamente no main
 * @param sec apontador para a struct secção
 * @param produtos  apontador para a struct peça
 * @param num_encomendas inteiro que dá o número de peças que irá ter a lista de chegada
 * @param pecas é um apontador para objetos da struct Peca dentro da struct seccao
 * @param marcas inteiro que contem a quantidade de marcas que contem o array
 * @param num_marcas inteiro que contem a quantidade de marcas que contem o array
 * @param categorias inteiro que contem a quantidade de categorias que contem o array
 * @param num_categorias inteiro que contem a quantidade de categorias que contem o array
 * @param argc inteiro que conta a quantidade de argumentos que são passados por argumentos na execução do programa
 * @param argv char que permite acessar os argumentos que são passados por argumentos na execução do programa
 */
void dia(int num_seccoes, seccao *sec, Peca *produtos, int num_encomendas, Peca pecas[], string marcas[],int num_marcas, string categorias[], int num_categorias, int argc,char *argv[]) {
    bool sair = false;
    char op;
    do {
        cout << "(d)ia seguinte ********** (g)estao ********** (s)air" << endl;
        cout << "Escolha a sua opcao" << endl;
        cin >> op;
        switch (op) {
            case 'd':
                cout << "Dia seguinte" << endl;
                meterprod(sec, produtos, num_seccoes,  num_encomendas,  marcas, num_marcas, categorias,num_categorias);
                break;
            case 'g':
                opcoes(num_seccoes, sec,  produtos, num_encomendas, pecas, marcas, num_marcas, categorias,num_categorias, argc, argv);
                break;
            case 's':
                sair = true;
                break;
            default:
                cout << "Escolha uma opcao valida." << endl;
        }
        for(int i = 0; i < num_seccoes; i ++){
            if(sec[i].tempopromo >= 1){
                sec[i].tempopromo -= 1;
            }else if(sec[i].tempopromo == 0){
                sec[i].promocao = 1;
            }else{
                continue;
            }
        }
    } while (!sair);
}
