#include "huffman.h"

using namespace std;

Arquivo::Arquivo(char* nomeArquivo) : tamanhoVetorAscii(256) {
    frequenciaCaracteres = new int[tamanhoVetorAscii];
    int i;
    for (i = 0; i < tamanhoVetorAscii; i++)
        frequenciaCaracteres[i] = 0;
    arquivoOrigem = fopen(nomeArquivo, "r");
}

void Arquivo::contaCaracteres() {
    int i, caracterArquivo;
    caracterArquivo = getc(arquivoOrigem);
    while (caracterArquivo != EOF) {
        frequenciaCaracteres[caracterArquivo]++;
        //putchar(caracterArquivo);
        //cout << caracterArquivo << endl;
        caracterArquivo = getc(arquivoOrigem);
    }
    /*Teste para mostrar a tabela de frequencia*/
    for (i = 0; i < tamanhoVetorAscii; i++)
        cout << frequenciaCaracteres[i] << "[" << i << "]" << endl;
    fclose(arquivoOrigem);
}

void Arquivo::filtraFrequencia() {
    int i;
    i = tamanhoVetorAscii;
    Contagem *contagem = new Contagem();
    while (--i > 0) {
        if (frequenciaCaracteres[i] > 0) {
            contagem->caracterAscii = i;
            contagem->frequenciaCaracterAscii = frequenciaCaracteres[i];
            contagem->frequenciaAscii.push(Contagem);
        }
    }
}

bool Contagem::operator<(const Contagem &A) const {
    if (frequenciaCaracterAscii < A.frequenciaCaracterAscii)
        return true;
    return false;
}

bool Contagem::operator==(const Contagem &A) const {
    if (frequenciaCaracterAscii == A.frequenciaCaracterAscii)
        return true;
    return false;
}

bool Contagem::ordenaPorFrequencia(Contagem A, Contagem B) {
    if (A.frequenciaCaracterAscii < B.frequenciaCaracterAscii)
        return true;
    return false;
}

bool verificaArquivo(char* nomeArquivo) {
    FILE* arquivo;
    if ((arquivo = fopen(nomeArquivo, "r")) == NULL) {
        cout << "Arquivo não encontrado!" << endl;
        //fclose(arquivo);
        return 1;
    }
    fclose(arquivo);
    return 0;
}