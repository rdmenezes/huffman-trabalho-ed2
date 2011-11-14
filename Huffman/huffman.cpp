#include "huffman.h"

using namespace std;

Arquivo::Arquivo(char* nomeArquivo) : tamanhoVetorAscii(256) {
    frequenciaCaracteres = new int[tamanhoVetorAscii];
    int i;
    for (i = 0; i < tamanhoVetorAscii; i++)
        frequenciaCaracteres[i] = 0;
    arquivoOrigem = fopen(nomeArquivo, "r");
    /*Lê tamanho arquivo*/
    fseek(arquivoOrigem, 0, SEEK_END);
    tamanhoArquivoOrigem = ftell(arquivoOrigem);
    rewind(arquivoOrigem);
}

const int Arquivo::getTamanhoVetorAscii() const {
    return tamanhoVetorAscii;
}

int* Arquivo::getFrequenciaCaracteres() const {
    return frequenciaCaracteres;
}

int* Arquivo::contaCaracteres() {
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


int Filtragem::getCaracterAscii() const {
    return caracterAscii;
}

int Filtragem::getFrequenciaCaracterAscii() const {
    return frequenciaCaracterAscii;
}

/*Sobrecarga do operador << para a classe Filtragem*/
std::ostream & operator <<(std::ostream &os, const Filtragem & p) {
    os << "caractere: " << p.getCaracterAscii() << ", frequencia: " <<
            p.getFrequenciaCaracterAscii();
    return os;
}

bool Filtragem::operator<(const Filtragem &A) const {
    if (frequenciaCaracterAscii < A.frequenciaCaracterAscii)
        return true;
    return false;
}

bool Filtragem::operator==(const Filtragem &A) const {
    if (frequenciaCaracterAscii == A.frequenciaCaracterAscii)
        return true;
    return false;
}


void Estatistica::filtraFrequencia(int tamanhoVetor,
        int* vetorFrequenciaCaracteres) {
    int i;
    i = tamanhoVetor;
    cout <<"ENTRA NA PILHA ASSIM:" << endl;
    while (--i > 0) {
        if (vetorFrequenciaCaracteres[i] > 0) {
            Filtragem* contagem = new Filtragem();
            contagem->caracterAscii = i;
            contagem->frequenciaCaracterAscii = vetorFrequenciaCaracteres[i];
            cout << (*contagem) << endl;
            frequenciaAscii.push(contagem);
        }
    }
    cout <<"FICA NA PILHA ASSIM:" << endl;
    while (!frequenciaAscii.empty()) {
        Filtragem* frequencia = frequenciaAscii.top();
        cout << (*frequencia) << endl; // Print highest priority string
        frequenciaAscii.pop(); // Remmove highest priority string
    }

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
