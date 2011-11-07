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
int main(int argc, char** argv) {
    if (argc < 3 || argc >4){
       cout << "Uso: huffman [opção] [arq_origem] [arq_destino]" << endl;
       return 1;
    }
    if(verificaArquivo(argv[2]))
        return 1;
    cout << argc << endl;
    while(argc-- > 0){
        cout << argv[argc] << endl;
    }
    
    return 0;
}

