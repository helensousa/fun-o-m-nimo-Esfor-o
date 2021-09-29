#include <locale.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>


using namespace std;
struct TipoCavaleiro{
    int pontos;
    int esforco;
};

void menu(){
    int i = 0;
    //Moldura superior
    printf("%c",201);
    for(i=0;i<31;i++){
        printf("%c",205);
    }
    printf("%c\n",187);
    //Informação
    printf("%c\t Bem Vindo!!!\t\t%c\n",186, 186);
    printf("%c\t 1-Gera arquivo\t\t%c\n",186, 186);
    printf("%c\t 2-Simula batalha\t%c\n",186, 186);
    printf("%c\t 0-Sair\t\t\t%c\n",186, 186);
    //Moldura inferior
    printf("%c",200);
    for(i=0;i<31;i++){
        printf("%c",205);
    }
    printf("%c\n",188);
}

void quickSort(int *vetor, int esquerda, int direita){
    int temp;
    int pivo;
    int i, j;
    i = esquerda;
    j = direita;
    pivo = vetor[(esquerda + direita) / 2];
    while(i <= j){
        while(vetor[i] > pivo && i < direita)
            i++;
        while(vetor[j] < pivo && j > esquerda)
            j--;
        if(i <= j){
            temp = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = temp;
            i++;
            j--;
        }
    }
    if(j > esquerda)
        quickSort(vetor, esquerda, j);
    if(i < direita)
        quickSort(vetor, i, direita);
}

void gerarPontos_e_Esforco(int *pontuacao,int *esforco,int n){
    srand(time(NULL));
    for(int i = 0;i < n;i++){
        esforco[i] = 1 + (rand()%5);
        pontuacao[i] = rand()%n;
    }
    quickSort(pontuacao,0,n-1);

}

void gerarArquivoTxt(int n,int k,char *nome){
    FILE *arquivo = fopen(nome,"w");
    if(!arquivo){
        cout<<"\nt///////ERRO!!!///////// \a\n\tO arquivo não foi criado";
    }else{
        int *pontuacao = (int*) malloc(n * sizeof(int));
        int *esforco =  (int*) malloc(n * sizeof(int));
        gerarPontos_e_Esforco(pontuacao,esforco,n);

        fprintf(arquivo,"%d-%d\n",n,k);
        for(int i = 0;i < n;i++){
            fprintf(arquivo,"%d %d\n",pontuacao[i],esforco[i]);
        }
        free(pontuacao);
        free(esforco);
        cout<<"\nO arquivo foi criado com sucesso";
    }
    fclose(arquivo);
}

bool lerArquivoTxt(int &n,int &k,TipoCavaleiro *cavaleiro){
    char nomeArquivo[25];
    bool existe = true;
    sprintf(nomeArquivo,"arquivo%d.txt",n);
    FILE *arquivo = fopen(nomeArquivo,"r");
    if(!arquivo){
        cout<<"\n\t****ERRO**** Arquivo nao encontrado.";
        cout<<"\nVoce pode criar um novo arquivo atraves da opcao '1' no menu de opcoes\n";
        fclose(arquivo);
        return false;
    }else{
        fscanf(arquivo,"%d-%d\n",&n,&k);
        for(int i = 0;i < n;i++){
            fscanf(arquivo,"%d %d\n",&cavaleiro[i].pontos,&cavaleiro[i].esforco);
        }
    }
    fclose(arquivo);
    return existe;

}
//procedimento para determinar o número de 1's em cada linha
void soma_esforco (int **tabela, TipoCavaleiro *cavaleiro, int linha, int coluna, int *soma)
{
    for (int i = 0; i < linha; i++){
        soma[i] = 0;
        for (int j = 0; j < coluna; j++){
            if(tabela[i][j] == 1)
                soma[i] += cavaleiro[j].esforco;
        }
    }
}

//procedimento para gerar tabela verdade
void Tbinaria (int linha, int coluna, int **tabela)
{
    int aux = linha;
    for (int i = 0; i < linha; i++)
    {
        aux = i;
        //laço para preencher a tabela com os valores de trás para frente
        for (int j = coluna-1; j >= 0; j--)
        {
            tabela[i][j] = aux%2;
            aux = aux/2;
        }
    }
}

void quickSort(TipoCavaleiro *vetor, int esquerda, int direita){
    TipoCavaleiro temp;
    int pivo;
    int i, j;
    i = esquerda;
    j = direita;
    pivo = vetor[(esquerda + direita) / 2].pontos;
    while(i <= j){
        while(vetor[i].pontos > pivo && i < direita)
            i++;
        while(vetor[j].pontos < pivo && j > esquerda)
            j--;
        if(i <= j){
            temp = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = temp;
            i++;
            j--;
        }
    }
    if(j > esquerda)
        quickSort(vetor, esquerda, j);
    if(i < direita)
        quickSort(vetor, i, direita);
}

void insertionSort(TipoCavaleiro *vetor,int tam){

    int i, j;
    TipoCavaleiro key;
    for (i = 1; i < tam; i++){
       key = vetor[i];
       j = i-1;

       while (j >= 0 && vetor[j].pontos < key.pontos){
           vetor[j+1] = vetor[j];
           j--;
       }
       vetor[j+1] = key;
   }

}
int esforcoNecessario(int **tabela,int n,int k,TipoCavaleiro *cavaleiro,int *somaEsf){
    int pontosGanhos,pontosNecessarios,minimoEsforco = 99999999;
    int i,j,m;
    for(i = 0; i < pow(2, n);i++){
        pontosGanhos = 0;
        lerArquivoTxt(n,k,cavaleiro);
        for(j = 0;j < n;j++){
            if(tabela[i][j] == 0){
                cavaleiro[j].pontos++;
            }else{
                pontosGanhos++;
            }

        }
        insertionSort(cavaleiro,n);
        m = 0;
        while(m < k){
            if(cavaleiro[m].pontos >= cavaleiro[m+1].pontos){
                pontosNecessarios = cavaleiro[m].pontos;
            }
            m++;
        }
        if(pontosGanhos == pontosNecessarios && minimoEsforco > somaEsf[i])
            minimoEsforco = somaEsf[i];

    }
    if (minimoEsforco == 99999999) return -1;
    else return minimoEsforco;

}
//§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
int main()
{
    TipoCavaleiro *cavaleiro;
    char aux1[10], aux2[10];
    int esforcoMinimo,k,coluna, linha, **tabela;
    int *somaesfo, opcao = 0;
    int a;
    char aux,auxN[10];
    int n;
    char nomeArquivo[30];
    bool arquivoExiste = false;

    srand(time(NULL));
    setlocale(LC_ALL, "portuguese");

    do
    {
        menu();
        do{
            a=0;
            cout << "Digite a opção desejada" << endl;
            fflush(stdin);
            cin >> aux;
            if(isalpha(aux)){
                cout << "Você digitou um caracter! Entrada inválida\n";
                a = 1;
            }
            opcao = aux -48;
        }while(a == 1 || opcao < 0 || opcao>2);
        system("cls");
        switch(opcao){
        case 1:
            do{
                system("cls");
                do{
                    system("cls");
                    a = 0;
                    cout<<"Digite o valor de N: ";
                    fflush(stdin);
                    cin>>auxN;
                    n = atoi(auxN);
                    if(isalpha(auxN[0])){
                        cout << "Você digitou um caracter! Entrada inválida\n";
                        a = 1;
                    }
                    cout<<"Digite o valor de K: ";
                    fflush(stdin);
                    cin>>auxN;
                    k = atoi(auxN);
                    if(isalpha(auxN[0])){
                        cout << "Você digitou um caracter! Entrada inválida\n";
                        a = 2;
                    }
                }while(n <= 0 || k <= 0 || a == 1 || a == 2);
                sprintf(nomeArquivo,"arquivo%d.txt",n);
                gerarArquivoTxt(n,k,nomeArquivo);
                do{
                    system("cls");
                    a = 0;
                    cout<<"\nGerar outro arquivo??(digite '1 para Sim e '0' para Sair): ";
                    cin>>auxN;
                    if(isalpha(auxN[0])){
                        cout << "Você digitou um caracter! Entrada inválida\n";
                        a = 1;
                    }
                    opcao = atoi(auxN);
                }while(a == 1 || opcao < 0 ||opcao > 1);
            }while(opcao == 1);
            system("cls");
            break;
        case 2:
            do{
                cout << "Qual é a quantidade de cavaleiros? ";
                fflush(stdin);
                gets(auxN);
                fflush(stdin);
                coluna = atoi(auxN);
                if(coluna <= 0)
                    cout << "Entrada inválida!\n";
                //alocação da memória
                cavaleiro = (TipoCavaleiro*) malloc(coluna * sizeof(TipoCavaleiro));
                //ler Arquivo
                arquivoExiste = lerArquivoTxt(coluna,k,cavaleiro);
                if(!arquivoExiste)
                    break;
            }while(coluna <= 0);
            if(arquivoExiste){

            //número de linhas da tabela = 2^(quantidade de cavaleiros)
            linha = pow(2, coluna);

            tabela = (int**) malloc (linha * sizeof(int*));
            //alocação da memória para as linhas da tabela
            for( int i = 0; i < linha; i++)
                tabela[i] = (int*) malloc (coluna * sizeof(int));

            Tbinaria(linha, coluna, tabela);

            somaesfo = (int *) malloc (linha * sizeof(int));

            soma_esforco(tabela, cavaleiro, linha, coluna, somaesfo);
            cout<<"\n\tTabela verdade antes da entrada de Sor Duncan\n";
            for (int i = 0; i < linha; i++){
                for( int j = 0; j < coluna; j++)
                    cout << tabela[i][j];   //imprimir a tabela
                cout << "\t"<< somaesfo[i] << endl;//imprimir o esforço necessário para vencer a quantidade de vitórias impresa naquela linha
            }
            cout<<"\n\tPontuacao antes da entrada de Sor Duncan\n";
            for (int i = 0; i < coluna; i++){
                cout << "Cavaleiro " << i+1 << ": " << cavaleiro[i].esforco;//imprimir o esforço de cada cavaleiro
                cout << "\tPontuação: " << cavaleiro[i].pontos << endl;//imprimir a pontuação de cada cavaleiro
            }
            esforcoMinimo = esforcoNecessario(tabela,coluna,k,cavaleiro,somaesfo);
            system("pause");
            system("cls");
            cout<<"\nEsforço minimo necessário para passar : "<<esforcoMinimo<<endl;
            cout<<endl;


            //desalocar a memória
            for (int i = 0; i < coluna; i++)
                free(tabela[i]);

            free(tabela);
            free(cavaleiro);
            free(somaesfo);
            break;

        default:
            break;
        }
        }//fim do if(arquivoexiste)
        system("pause");
         do{
            a=0;
            system("cls");
            cout << "Deseja continuar? 0-Não 1-Sim" << endl;
            fflush(stdin);
            cin >> aux;
            if(isalpha(aux)){
                cout << "Você digitou um caracter! Entrada inválida\n";
                a = 1;
            }
        }while(a == 1);
        opcao = aux -48;
        system("cls");

    }while(opcao != 0);

    return 0;
}
