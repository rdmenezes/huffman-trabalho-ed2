/*
 * File:   main.cpp
 * Author: fguira
 *
 * Created on 5 de Novembro de 2011, 18:48
 */

#include "huffman.h"

using namespace std;

/*
 *
 */
int main(int argc, char ** argv) {
    /* Verifica se os argumentos (argc e argv) foram digitados corretamente */
    if ((argc < 3) || (argc > 4)) {
        cout << "Uso: huffman [opção] [arq_origem] [arq_destino]" << endl;

        return 1;
    }

    /* Verifica se existe arquivo de origem */
    if (verificaArquivo(argv[2])) {
        return 1;
    }

    /* Instancia o objeto a compactar */
    Arquivo * compactar;

    compactar = new Arquivo(argv[2]);
    int k = 0;
    char* fileName = argv[2];
    while (fileName[k]!='\0'){
        k++;
        if(fileName[k]=='.'){
            fileName[++k]='h';
            fileName[++k]='u';
            fileName[++k]='f';
            fileName[++k]='\0';
        }
    }
//    char extension[] = ".huf";
//    strcat(fileName, extension);
    cout << fileName << endl;
    /* Conta caracteres do arquivo */
    compactar -> contaCaracteres();

    Estatistica * estatistica = new Estatistica();

    estatistica -> filtraFrequencia(compactar -> getTamanhoVetorAscii(), compactar -> getFrequenciaCaracteres());

    Huffman * codifica = new Huffman(compactar->getTamanhoArquivoOrigem());

    codifica -> encodeHuffman(estatistica -> getFrequenciaAscii());
    codifica -> criaCodigo(codifica -> getRoot(), codifica -> getCodigoBinario());
    codifica->imprimeTeste(compactar->getTextoOriginal(), compactar->getTamanhoArquivoOrigem());
    compactar->gravaArquivoDestino(codifica->getTextoArquivoDestino(), fileName);
    compactar->leArquivoDestino(fileName);

    /* Testes com argc e argv */
    cout << endl;
    cout << argc << endl;

    int i = argc;

    while (argc-- > 0) {
        cout << *argv++ << "[" << i - argc << "]" << endl;
    }
    delete codifica;
    delete compactar;
    delete estatistica;
    return 0;
}


//~ Formatted by Jindent --- http://www.jindent.com
