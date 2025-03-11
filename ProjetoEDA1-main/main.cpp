
#include "funcoes.h"
#include "gestao.h"
#include <ctime>
#include <string>
using namespace std;

int main(int argc,char *argv[]) {
    srand(time(0));
    int numero_seccoes=numerodesec();

    seccao*sec=new seccao[numero_seccoes];
    Peca*pecas=new Peca[8];

    const int MAX_PRODUTOS = 100;
    const int num_encomendas = 10;
    string marcas[MAX_PRODUTOS];
    string categorias[MAX_PRODUTOS];
    int nmarcas, ncategorias;
    Peca*produtos=new Peca[ MAX_PRODUTOS];

    lerficheiro(marcas, categorias, nmarcas, ncategorias);
    preenche( numero_seccoes,sec, num_encomendas, marcas,  nmarcas, categorias,  ncategorias,produtos);

    dia(numero_seccoes,sec,produtos,num_encomendas,  pecas,marcas,  nmarcas,  categorias, ncategorias,argc,argv);


    delete[] produtos;
    delete[] sec;
    return 0;
}