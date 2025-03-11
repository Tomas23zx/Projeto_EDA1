#include "gestao.h"
#include <iostream>
#include "funcoes.h"
#include <string>
#include <fstream>

using namespace std;

/**
 * Função que após escolher a opção de entrar no menu de gestor permite-nos escolher entre cada submenu do menu de gestor
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
void opcoes(int num_seccoes, seccao *sec,  Peca *produtos, int num_encomendas, Peca pecas[], string marcas[],int num_marcas, string categorias[], int num_categorias, int argc,char *argv[]){
    bool sair =false;
    char opcao;
    do
    {
        cout<< "***** Bem Vindo Gestor *****\n";
        cout<<"(1) .Venda Manual"<<endl;
        cout<<"(2) .Promocao"<<endl;
        cout<<"(3) .Alterar categoria"<<endl;
        cout<<"(4) .Adicionar seccao"<<endl;
        cout<<"(5) .Gravar Armazem"<<endl;
        cout<<"(6) .Carregar Armazem"<<endl;
        cout<<"(7) .Imprimir Armazem"<<endl;
        cout<<"(8) .Sair"<<endl;
        cout<<"Escolha a sua opcao:"<<endl;

        cin>>opcao;
        cout<<endl;
        switch (opcao){
            case '1':
                vendam(sec,num_seccoes);
                break;
            case'2':
                promo( sec, num_seccoes);
                break;
            case'3':
                alterar_categoria(sec,produtos,num_seccoes,categorias,num_categorias,num_encomendas,pecas,marcas,num_marcas,argc,argv);
                break;
            case '4':
                criasecao(num_seccoes+1, num_seccoes,sec,produtos, num_encomendas,pecas,marcas,num_marcas,categorias,num_categorias,argc,argv);
                break;
            case '5':
                grava_armazem(sec,produtos,num_seccoes,num_encomendas);
                break;
            case '6':
                carregar_armazem(sec,produtos, argc,argv);
                break;
            case '7':
                imprimir(sec, num_seccoes, produtos, num_encomendas);
                break;
            case '8':
                sair = true;
                break;
            default:
                cout<<"Escolha uma opcao valida."<<endl;
        }
    }while (!sair);
}

/**
 * Esta função faz com que o utilizador venda uma peça do armazem manualmente, a função pede ao utilizador a letra da secção, depois verifica se existe, pede o nome produto e verifica se existe e por fim vende o produto, atualiando a faturação e a quantidade
 * @param sec apontador para a struct secção
 * @param num_secoes inteiro que dá o número de seccoes que foi gerado aleatoriamente no main
 */
void vendam(seccao*sec, int numerosec){
    string nome;
    char letra;
    bool letraEncontrada;
    do {
        cout << "Indique a letra da seccao que deseja(em maiuscula):" << endl;
        cin >> letra;

        for (int i = 0; i < numerosec; i++) {
            if (letra == sec[i].letra) {
                cout << "Indique o nome do produto:" << endl;
                cin >> nome;

                for(int j = 0; j < sec[i].quantidade; j++) {
                    if (nome == sec[i].pecas[j].marca) {
                        cout << "Produto Vendido com sucesso" << endl;
                        sec[i].faturacao += sec[i].pecas[j].preco;
                        tirapecas(sec,j, i);
                        letraEncontrada = true;
                        break;
                    }
                }
                if (!letraEncontrada) {
                    cout << "Produto não encontrado nesta seção." << endl;
                }
                letraEncontrada = true;
                break;
            }
        }

        if (!letraEncontrada) {
            cout << "Indique uma letra valida" << endl;
        }
    } while (!letraEncontrada);
}

/**
 * Função em que podemos aplicar uma promoção em uma certa secção, nesta parte podemos escolher entre aplicar promoção e sair, pois podemos adicionar promoções a mais secções
 * @param sec apontador para a struct secção
 * @param num_secoes inteiro que dá o número de seccoes que foi gerado aleatoriamente no main
 */
void promo( seccao*sec, int num_seccoes){
    bool sair =false;
    char a;
    do
    {   cout << "Escolha uma das opcoes:"<<endl;
        cout <<"(1)Introduzir percentagem de desconto"<<endl;
        cout <<"(0)Sair"<<endl;
        cin >> a;
        switch (a){
            case '1':
                aplicaPromo(sec, num_seccoes);
                break;
            case '0':
                sair = true;
                break;
            default:
                cout<<"Escolha uma opcao valida."<<endl;
        }
    }while (!sair);
}

/**
 * Esta função é que faz propriamente a ormoção, pede ao utilizador a letra da secção, a percentagem de promoção e a duração,depois a percentagem e os dias são enviados para a struct, para serem chamados para o menu
 * @param sec apontador para a struct secção
 * @param num_secoes inteiro que dá o número de seccoes que foi gerado aleatoriamente no main
 * @return retorna um apontador para a struct seccao, que atualiza os detalhes da promoção, neste caso o tempo e a percentagem de desconto
 */
struct seccao *aplicaPromo(seccao *sec, int num_seccoes) {
    int desc;
    char se;
    int dia;
    cout << "Insira a seccao que deseja aplicar a promocao(em maiuscula):" << endl;
    cin >> se;
    cout << "Insira a percentagem de desconto(1 a 99) :" << endl;
    cin >> desc;
    cout << "Insira a duracao da promocao:" << endl;
    cin >> dia;

    while(desc < 1 || desc >=100){
        cout << "Por favor insira um valor entre 1 e 99. " << endl;
        cout << "Insira a percentagem de desconto (1 a 99):" ;
        cin >> desc;
    }

    for (int i = 0; i < num_seccoes; ++i) {
        if (se == sec[i].letra) {
            sec[i].promocao = desc;
            sec[i].tempopromo = dia;
        } else {
            sec[i].promocao = 1;
            sec[i].tempopromo = 0;
        }
    }
    return sec;
}


/**
 * Esta função permite ao utilizador que consiga alterar uma cateforia de uma qualquer secção, indicando a categoria e depois considerando a mesma se for nova, para ser gerada em novos ciclos, em novas peças
 * @param sec apontador para a struct secção
 * @param produtos  apontador para a struct peça
 * @param numerosec inteiro que dá o número de seccoes que foi gerado aleatoriamente no main
 * @param categorias inteiro que contem a quantidade de categorias que contem o array
 * @param num_categorias inteiro que contem a quantidade de categorias que contem o array
 * @param num_encomendas inteiro que dá o número de peças que irá ter a lista de chegada
 * @param pecas é um apontador para objetos da struct Peca dentro da struct seccao
 * @param marcas inteiro que contem a quantidade de marcas que contem o array
 * @param num_marcas inteiro que contem a quantidade de marcas que contem o array
 * @param argc inteiro que conta a quantidade de argumentos que são passados por argumentos na execução do programa
 * @param argv char que permite acessar os argumentos que são passados por argumentos na execução do programa
 */
void alterar_categoria(seccao *sec, Peca *produtos, int numerosec, string categorias[], int num_categorias, int num_encomendas,  Peca *pecas, string marcas[], int num_marcas,int argc,char *argv[]) {
    string cat;
    string novacat;
    bool categoriaencontrada = false;
    do {
        cout << "Indique a categoria que quer alterar:" << endl;
        cin >> cat;
        for (int i = 0; i < numerosec; i++) {
            if (cat == sec[i].categoria) {
                cout << "Categoria encontrada" << endl;
                cout << "Introduza o nome da nova categoria:" << endl;
                cin >> novacat;
                sec[i].categoria = novacat;
                sec[i].quantidade = 0;
                sec[i].faturacao = 0;
                sec[i].pecas = new Peca[sec[i].capacidade];
                for (int j = 0; j < numerosec; j++) {
                    if (produtos[j].categoria == cat) {
                        produtos[j].categoria = novacat;
                    }
                }
                bool categoria_existe = false;
                for (int k = 0; k < num_categorias; k++) {
                    if (categorias[k] == novacat) {
                        categoria_existe = true;
                        break;
                    }
                }
                if (!categoria_existe) {
                    string novas_categorias[num_categorias + 1];
                    for (int k = 0; k < num_categorias; k++) {
                        novas_categorias[k] = categorias[k];
                    }
                    novas_categorias[num_categorias] = novacat;
                    for (int k = 0; k <= num_categorias; k++) {
                        categorias[k] = novas_categorias[k];
                    }
                    num_categorias++;
                }
                categoriaencontrada = true;
                break;
            }
        }
        if (!categoriaencontrada) {
            cout << "Categoria nao encontrada" << endl;
        }
    } while (!categoriaencontrada);
    dia(numerosec, sec, produtos, num_encomendas, pecas, marcas, num_marcas, categorias, num_categorias,  argc,argv );
}

/**
 * Esta função que recebeo id da seccao, a capacidade da nova seccao e caategoria da mesma, depois define-a como "nascendo" vazia
 * @param novotamanho inteiro que será o novo tamanho do array,pois a nova secção passará a ser considerada nos ciclos seguintes
 * @param numerosec inteiro que dá o número de seccoes que foi gerado aleatoriamente no main
 * @param num_encomendas inteiro que dá o número de peças que irá ter a lista de chegada
 * @param pecas é um apontador para objetos da struct Peca dentro da struct seccao
 * @param marcas inteiro que contem a quantidade de marcas que contem o array
 * @param num_marcas inteiro que contem a quantidade de marcas que contem o array
 * @param categorias inteiro que contem a quantidade de categorias que contem o array
 * @param num_categorias inteiro que contem a quantidade de categorias que contem o array
 * @param argc inteiro que conta a quantidade de argumentos que são passados por argumentos na execução do programa
 * @param argv char que permite acessar os argumentos que são passados por argumentos na execução do programa
 */

void criasecao(int novotamanho, int num_seccao, seccao *sec, Peca*produtos, int num_encomendas, Peca *pecas, string marcas[], int num_marcas, string categorias[], int num_categorias,int argc,char *argv[]) {
    char id;
    int cap;
    string cat;
    cout << "Insira o ID da nova seccao" << endl;
    cin >> id;
    cout << "Insira a capacidade da nova secao:" << endl;
    cin >> cap;
    cout << "Insira a categoria da nova secao:" << endl;
    cin >> cat;


    seccao *novo = new seccao[novotamanho];


    for (int i = 0; i <num_seccao; i++) {
        novo[i] = sec[i];
    }

    novo[num_seccao].letra = id;
    novo[num_seccao].capacidade = cap;
    novo[num_seccao].faturacao = 0;
    novo[num_seccao].quantidade = 0;
    novo[num_seccao].categoria = cat;
    novo[num_seccao].pecas = new Peca[novo[num_seccao].capacidade];

    dia(novotamanho,novo,produtos,num_encomendas,  pecas,marcas,  num_marcas,  categorias, num_categorias,  argc,argv);

}




/**
 * Esta função grava o armazem,num ficheiro .txt. Neste ficheiro são apresentados desde o número de secções, tamanho da lista de chegada, até cada peça dentro da lista de chegada e dentro de cada secção
 * @param sec apontador para a struct secção
 * @param prod apontador para a struct Peça
 * @param tamanhosec inteiro que indica o numero de secções que foram geradas
 * @param tamanholc inteiro que diz o número de peças na lista de chegada
 */
void grava_armazem(seccao*sec,Peca*prod, int tamanhosec, int tamanholc) {
    string nomeFicheiro="armazem.txt";
    fstream file(nomeFicheiro, ios::out);
    if (file.is_open()) {
        file <<tamanhosec << endl;
        file <<tamanholc<<endl;
        for (int i = 0; i < tamanhosec; i++) {
            file<<sec[i].letra<<endl;
            file<<sec[i].categoria<<endl;
            file<<sec[i].capacidade<<endl;
            file<<sec[i].quantidade << endl;
            file<<sec[i].faturacao <<endl;
            for(int j=0;j<sec[i].quantidade;j++){
                file<<sec[i].pecas[j].marca<<endl;
                file<<sec[i].pecas[j].preco<<endl;
                file<<sec[i].pecas[j].numero_serie<<endl;
                file<<sec[i].pecas[j].categoria<<endl;
            }
        }
        for (int j=0;j<tamanholc;j++){
            file<<prod[j].marca<<endl;
            file<<prod[j].categoria<<endl;
            file<<prod[j].numero_serie<<endl;
            file<<prod[j].preco<<endl;

        }
    }else{
        cerr << "ERRO AO ESCREVER NO FICHEIRO" << endl;
    }
    file.close();
    cout<<"Dados do armazem gravados com sucesso"<<endl;
}
/**
 * Esta função, recebendo os argumentos usados na execução do programa argc e argv verifica se existe algum ficheiro contem o nome em que foi gravado na função anterior, como "armazem.txt", senão ele abre o ficheiro com esse nome
 * @param sec apontador para a struct secção
 * @param prod apontador para a struct Peça
 * @param argc inteiro que conta a quantidade de argumentos que são passados por argumentos na execução do programa
 * @param argv char que permite acessar os argumentos que são passados por argumentos na execução do programa
 */

void carregar_armazem(seccao* sec, Peca* prod,int argc,char *argv[]) {
    string nomeFicheiro;
    if(argc==2) {
        nomeFicheiro=argv[1];
        if(nomeFicheiro=="armazem.txt"){
        ifstream file(nomeFicheiro);
        if (file.is_open()) {
            int tamanhosec, tamanholc;
            file >> tamanhosec;
            file >> tamanholc;
            for (int i = 0; i < tamanhosec; i++) {
                file.ignore();
                char letra;
                string categoria;
                int capacidade, quantidade, faturacao;
                file >> letra;
                file.ignore();
                getline(file, categoria);
                file >> capacidade >> quantidade >> faturacao;
                sec[i].letra = letra;
                sec[i].categoria = categoria;
                sec[i].capacidade = capacidade;
                sec[i].quantidade = quantidade;
                sec[i].faturacao = faturacao;
                for (int j = 0; j < quantidade; j++) {
                    string marca, pecas_categoria;
                    int preco, numero_serie;
                    file >> marca >> preco >> numero_serie;
                    file.ignore();
                    getline(file, pecas_categoria);
                    sec[i].pecas[j].marca = marca;
                    sec[i].pecas[j].preco = preco;
                    sec[i].pecas[j].numero_serie = numero_serie;
                    sec[i].pecas[j].categoria = pecas_categoria;
                }
            }
            for (int j = 0; j < tamanholc; j++) {
                string marca, categoria;
                int numero_serie, preco;
                file.ignore();
                getline(file, marca);
                getline(file, categoria);
                file >> numero_serie >> preco;
                prod[j].marca = marca;
                prod[j].categoria = categoria;
                prod[j].numero_serie = numero_serie;
                prod[j].preco = preco;
            }
            cout << "Dados do armazem carregados com sucesso, com argumento passado no programa" << endl;
        } else {
            cerr << "Erro ao abrir o arquivo do armazem" << endl;
        }
        file.close();
        }else{
            cout<<"Erro ficheiro nao correspondente"<<endl;
        }

    }else{
        nomeFicheiro = "armazem.txt";
        ifstream file(nomeFicheiro);
        if (file.is_open()) {
            int tamanhosec, tamanholc;
            file >> tamanhosec;
            file >> tamanholc;
            for (int i = 0; i < tamanhosec; i++) {
                file.ignore();
                char letra;
                string categoria;
                int capacidade, quantidade, faturacao;
                file >> letra;
                file.ignore();
                getline(file, categoria);
                file >> capacidade >> quantidade >> faturacao;
                sec[i].letra = letra;
                sec[i].categoria = categoria;
                sec[i].capacidade = capacidade;
                sec[i].quantidade = quantidade;
                sec[i].faturacao = faturacao;
                for (int j = 0; j < quantidade; j++) {
                    string marca, pecas_categoria;
                    int preco, numero_serie;
                    file >> marca >> preco >> numero_serie;
                    file.ignore();
                    getline(file, pecas_categoria);
                    sec[i].pecas[j].marca = marca;
                    sec[i].pecas[j].preco = preco;
                    sec[i].pecas[j].numero_serie = numero_serie;
                    sec[i].pecas[j].categoria = pecas_categoria;
                }
            }
            for (int j = 0; j < tamanholc; j++) {
                string marca, categoria;
                int numero_serie, preco;
                file.ignore();
                getline(file, marca);
                getline(file, categoria);
                file >> numero_serie >> preco;
                prod[j].marca = marca;
                prod[j].categoria = categoria;
                prod[j].numero_serie = numero_serie;
                prod[j].preco = preco;
            }
            cout << "Dados do armazem carregados com sucesso" << endl;
        } else {
            cerr << "Erro ao abrir o arquivo do armazem" << endl;
        }
        file.close();
    }
}

/**
 * Função que organiza a lista de chegada por marca
 * @param produtos apontador para a struct Peça
 * @param num_encomendas inteiro que dá o número de peças que irá ter a lista de chegada
 */
void bubbleSortPorMarca(Peca* produtos, int num_encomendas) {
    for (int i = 0; i < num_encomendas - 1; ++i) {
        for (int j = 0; j < num_encomendas - i - 1; ++j) {
            if (produtos[j].marca > produtos[j + 1].marca) {
                Peca temp = produtos[j];
                produtos[j] = produtos[j + 1];
                produtos[j + 1] = temp;
            }
        }
    }
}
/**
 * Função que recebe um apontador de peças e um tamanho, em que ordena por ordem crescente o preço das peças
 * @param pecas  é um apontador para objetos da struct Peca dentro da struct seccao
 * @param tamanho inteiro que diz a quantidade de elementos que têm de ser ordenados
 */
void bubbleSortPorPreco(Peca* pecas, int tamanho) {
    for (int i = 0; i < tamanho - 1; ++i) {
        for (int j = 0; j < tamanho - i - 1; ++j) {
            if (pecas[j].preco > pecas[j + 1].preco) {
                swap(pecas[j], pecas[j + 1]);
            }
        }
    }
}
/**
 * A função retorna um boleano, retorna true se estiver ordenado albafeticamente e false no contrario
 * @param p1 é a referência para uma marca de Peca
 * @param p2 é a referência para uma marca de Peca
 * @return retorna um booleano em que se a marca p1 estiver alfabeticamente ordenada retorna true
 */
bool compararPorMarca(const Peca& p1, const Peca& p2) {
    return p1.marca < p2.marca;
}
/**
 * Função que recebe um apontador de peças e um tamanho, em que ordena por ordem alfabetica a marca das peças
 * @param pecas  é um apontador para objetos da struct Peca dentro da struct seccao
 * @param tamanho inteiro que diz a quantidade de elementos que têm de ser ordenados
 */
void ordenarPorMarca(Peca* pecas, int tamanho) {
    for (int i = 0; i < tamanho - 1; ++i) {
        for (int j = 0; j < tamanho - i - 1; ++j) {
            if (compararPorMarca(pecas[j + 1], pecas[j])) {
                swap(pecas[j], pecas[j + 1]);
            }
        }
    }
}

/**
 * Função que chama as funções de imprimir por ordem alfabética e por ordem crescente de preço
 * @param secoes apontador para a struct secção
 * @param num_secoes inteiro que dá o número de seccoes que foi gerado aleatoriamente no main
 * @param produtos  apontador para a struct peça
 * @param num_encomendas inteiro que dá o número de peças que irá ter a lista de chegada
 */
void imprimir(seccao *secoes, int num_secoes, Peca *produtos, int num_encomendas) {
    Peca *todasPecas = new Peca[num_encomendas + num_secoes];
    int indice = 0;
    for (int i = 0; i < num_encomendas; ++i) {
        todasPecas[indice] = produtos[i];
        indice++;
    }

    for (int i = 0; i < num_secoes; ++i) {
        for (int j = 0; j < secoes[i].quantidade; ++j) {
            todasPecas[indice] = (secoes[i].pecas[j]);
            indice++;
        }
    }

    bool sair = false;
    char opcao;
    do {
        cout << "Escolha uma das opcoes:" << endl;
        cout << "(1) Imprimir o armazem por ordem alfabetica da marca da peca" << endl;
        cout << "(2) Imprimir o armazem por preco da peca" << endl;
        cout << "(0) Sair" << endl;
        cin >> opcao;

        switch (opcao) {
            case '1':
                ordenarPorMarca(todasPecas, num_encomendas + num_secoes);
                break;
            case '2':
                bubbleSortPorPreco(todasPecas, num_encomendas + num_secoes);
                break;
            case '0':
                sair = true;
                break;
            default:
                cout << "Escolha uma opcao valida." << endl;
                continue;
        }

        for (int i = 0; i < num_encomendas+ num_secoes; ++i) {
            cout << todasPecas[i].marca << " | " << todasPecas[i].categoria << " | " << todasPecas[i].numero_serie << " | " << todasPecas[i].preco << " euros" << endl;
        }
    } while (!sair);
    delete[] todasPecas;
}