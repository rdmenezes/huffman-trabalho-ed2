#include "huffman.h"

using namespace std;

Arquivo::Arquivo(char* nomeArquivo) : tamanhoVetorAscii(256) {
    frequenciaCaracteres = new int[tamanhoVetorAscii];
    textoArquivoOrigem = "";
    quantidadeBitsets = 0;
    numNomeOriginal = 0;
    int i;
    for (i = 0; i < tamanhoVetorAscii; i++)
        frequenciaCaracteres[i] = 0;
    arquivoOrigem = fopen(nomeArquivo, "r");
    /*Lê tamanho arquivo*/
    fseek(arquivoOrigem, 0, SEEK_END);
    tamanhoArquivoOrigem = ftell(arquivoOrigem);
    rewind(arquivoOrigem);
    textoOriginal = new int[tamanhoArquivoOrigem];
}

const int Arquivo::getTamanhoVetorAscii() const {
    return tamanhoVetorAscii;
}

int* Arquivo::getFrequenciaCaracteres() const {
    return frequenciaCaracteres;
}

int* Arquivo::contaCaracteres() {
    int i = 0;
    int caracterArquivo;
    while (caracterArquivo != EOF) {
        caracterArquivo = getc(arquivoOrigem);
        textoOriginal[i] = caracterArquivo;
        frequenciaCaracteres[caracterArquivo]++;
        i++;
    }
    fclose(arquivoOrigem);
}

Filtragem::Filtragem() : esq(NULL), dir(NULL) {

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
            p.getFrequenciaCaracterAscii() << ", folha: " << p.isLeaf() <<
            ", bincode: " << p.getCodigobinario();
    return os;
}

bool Filtragem::operator<(const Filtragem &A) const {
    if (frequenciaCaracterAscii < A.frequenciaCaracterAscii && caracterAscii < A.caracterAscii)
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
    while (--i > 0) {
        if (vetorFrequenciaCaracteres[i] > 0) {
            Filtragem* contagem = new Filtragem();
            contagem->dir = NULL;
            contagem->esq = NULL;
            contagem->caracterAscii = i;
            contagem->frequenciaCaracterAscii = vetorFrequenciaCaracteres[i];
            contagem->leaf = true;
            frequenciaAscii.push(contagem);
        }
    }
}

Huffman::Huffman(long tam) {
    codigoBinario = "";
    textoArquivoDestino = "";
    quantidadeBits = 0;
    stringSize = 0;
}

void Huffman::encodeHuffman(filaprioridade fila) {
    arvoreCodificada = fila;
    while (arvoreCodificada.size() > 1) {
        Filtragem* no = new Filtragem();
        no->esq = arvoreCodificada.top();
        no->esq->codigobinario = "0";
        arvoreCodificada.pop();
        no->dir = arvoreCodificada.top();
        no->dir->codigobinario = "1";
        arvoreCodificada.pop();
        no->leaf = false;
        no->caracterAscii = 257;
        no->frequenciaCaracterAscii = (no->dir->frequenciaCaracterAscii +
                no->esq->frequenciaCaracterAscii);
        arvoreCodificada.push(no);
    }
    root = new Filtragem;
    root = arvoreCodificada.top();
    root->leaf = false;
    root->caracterAscii = 258;
    root->frequenciaCaracterAscii = (root->dir->frequenciaCaracterAscii +
            root->esq->frequenciaCaracterAscii);
    arvoreCodificada.pop();
}

void Huffman::criaCodigo(Filtragem* root, string bincode) {
    if (root != NULL) {

        bincode += root->getCodigobinario();
        criaCodigo(root->getDir(), bincode);
        criaCodigo(root->getEsq(), bincode);
        if (root->isLeaf()) {
            root->setCodigobinario(bincode);
            tabelaConversao[root->getCaracterAscii()] = root->getCodigobinario();
            tabelaCodigoBinario.push(root);
        }
    }
}

void Huffman::decodeHuffman(Filtragem* root, string texto) {
    if (root != NULL) {
        if (root->isLeaf()) {
            textoArquivoDestino += root->getCaracterAscii();
        }
        else if (texto[stringSize] == '0') {
            stringSize++;
            decodeHuffman(root->getEsq(), texto);
        }
        else if (texto[stringSize] == '1') {
            stringSize++;
            decodeHuffman(root->getDir(), texto);
        }
    }
}

void Huffman::imprimeTeste(int* texto, long tamanhoArquivo) {
    int i, quantidadeCaracteres = 0;
    long tam = tamanhoArquivo;
    int* c = new int[tamanhoArquivo];
    c = texto;
    for (it = tabelaConversao.begin(); it != tabelaConversao.end(); it++) {
        //cout << (*it).first << " => " << (*it).second << " => " << (*it).second.length() << endl;
        quantidadeBits += (*it).second.length();
    }
    quantidadeCaracteres = (int) tabelaConversao.size();
    mediaBits = quantidadeBits / quantidadeCaracteres;
    for (i = 0; i < tam; i++) {
        textoArquivoDestino += tabelaConversao.find(c[i])->second;
    }
    size_t const bitstam(textoArquivoDestino.length());
}

void Arquivo::gravaArquivoDestino(string texto, char* nomeArquivo, char* nomeOriginal) {
    const int size = 8;
    string teste = "";
    long j=0;
    while (nomeOriginal[j]!='\0')
        j++;
    j++;
    numNomeOriginal = j;
    tamanhoCaracteresBinarios = texto.size();
    arquivoDestino = fopen(nomeArquivo, "wb+");
    fwrite(&numNomeOriginal, sizeof(int), 1, arquivoDestino);
    fwrite(nomeOriginal, sizeof(char), numNomeOriginal, arquivoDestino);
    fwrite(&tamanhoCaracteresBinarios, sizeof (int), 1, arquivoDestino);
    fwrite(frequenciaCaracteres, sizeof (int), tamanhoVetorAscii, arquivoDestino);
    //cout << endl;
    unsigned int i = 0;
    while (i < texto.size()) {
        teste += texto[i++];
        if (i % 8 == 0) {
            bitset <size> b(teste);
            teste = "";
            fwrite(&b, 1, 1, arquivoDestino);
        }
    }
    if (teste.size() != 0) {
        while (teste.size() < 8) {
            teste += "0";
        }

        bitset <size> b(teste);
        fwrite(&b, 1, 1, arquivoDestino);
    }
    rewind(arquivoDestino);
    fseek(arquivoDestino, 0, SEEK_END);
    tamanhoArquivoDestino = ftell(arquivoDestino);
    rewind(arquivoDestino);
    fclose(arquivoDestino);
    //cout << endl << endl;
}

void Arquivo::gravaArquivoTxt(string texto) {
    arquivoDestino = fopen(nomeArquivoOriginal, "w+");
    for (int i = 0; i < texto.size(); i++)
        putc(texto[i], arquivoDestino);
    fclose(arquivoDestino);
    //cout << endl << endl;
}

void Arquivo::leArquivoDestino(char* nomeArquivo) {
    const int size = 8;
    bitset <size> c;
    arquivoCompactado = fopen(nomeArquivo, "rb");
    fread(&numNomeOriginal, sizeof(int), 1, arquivoCompactado);
    nomeArquivoOriginal = (char*) malloc(numNomeOriginal+1);
    fread(nomeArquivoOriginal, sizeof(char), numNomeOriginal, arquivoCompactado);
    fread(&tamanhoCaracteresBinarios, sizeof (int), 1, arquivoCompactado);
    fread(frequenciaCaracteres, sizeof (int), tamanhoVetorAscii, arquivoCompactado);
//    for (k = 0; k < tamanhoVetorAscii; k++)
//        cout << k << "--->" << "[" << frequenciaCaracteres[k] << "]" << '\t';
    //cout << endl;
//    cout << "tamanhoCaracteresCompactados: " << tamanhoCaracteresBinarios << endl;
//    while (k++ < tamanhoVetorAscii)
//        cout << frequenciaCaracteres[k];
    while (!feof(arquivoCompactado)) {
        fread(&c, 1, 1, arquivoCompactado);
        arquivoDescompactado += c.to_string();
    }
    fclose(arquivoCompactado);
    arquivoDescompactado.resize(tamanhoCaracteresBinarios);
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
