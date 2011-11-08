#include "huffman.h"

using namespace std;

Arquivo::Arquivo(char* nomeArquivo): tamanhoVetorAscii(256){
    frequenciaCaracteres = new int[tamanhoVetorAscii];
    int i;
    for (i = 0; i < tamanhoVetorAscii; i++)
        frequenciaCaracteres[i] = 0;
    arquivoOrigem = fopen(nomeArquivo, "r");
}

void Arquivo::contaCaracteres(){
    int i, caracterArquivo;
    caracterArquivo = getc(arquivoOrigem);
    while (caracterArquivo != EOF){
        frequenciaCaracteres[caracterArquivo]++;
        //putchar(caracterArquivo);
        //cout << caracterArquivo << endl;
        caracterArquivo = getc(arquivoOrigem);
    }
    /*Teste para mostrar a tabela de frequencia*/
    for (i =0; i < tamanhoVetorAscii; i++)
        cout << frequenciaCaracteres[i]<< "[" << i << "]" << endl;
    fclose(arquivoOrigem);
}

void Arquivo::filtraFrequencia(){
    int i;
    i = tamanhoVetorAscii;
    while (--i > 0){
        if (frequenciaCaracteres[i] > 0){
            Contagem.caracterAscii = [i]
            Contagem.frequenciaCaracterAscii = frequenciaCaracteres[i];
            Contagem.frequenciaAscii.push();
        }
            
        
    }
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