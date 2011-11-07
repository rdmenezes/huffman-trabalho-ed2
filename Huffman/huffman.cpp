#include "huffman.h"

using namespace std;

Arquivo::Arquivo(): tamanhoVetorAscii(256){
    frequenciaCaracteres = new int[tamanhoVetorAscii];
}

bool verificaArquivo(char* nomeArquivo){
    FILE* arquivo;
    if((arquivo = fopen(nomeArquivo, "r")) == NULL){
        cout << "Arquivo não encontrado!" << endl;
        //fclose(arquivo);
        return 1;
    }
    fclose(arquivo);
    return 0;
}