#include "huffman.h"

using namespace std;

Arquivo::Arquivo(char* nomeArquivo) : tamanhoVetorAscii(256) {
    frequenciaCaracteres = new int[tamanhoVetorAscii];
    textoArquivoOrigem = "";
    int i;
    for (i = 0; i < tamanhoVetorAscii; i++)
        frequenciaCaracteres[i] = 0;
    arquivoOrigem = fopen(nomeArquivo, "r");
    /*Lê tamanho arquivo*/
    fseek(arquivoOrigem, 0, SEEK_END);
    tamanhoArquivoOrigem = ftell(arquivoOrigem);
    rewind(arquivoOrigem);
    cout << endl << endl << endl;
    cout << "tamanho do arquivo: " << tamanhoArquivoOrigem << endl;
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
    //caracterArquivo = getc(arquivoOrigem);
    while (caracterArquivo != EOF) {

        //putchar(caracterArquivo);
        //cout << caracterArquivo << endl;
        //textoOriginal[i] = caracterArquivo;
        caracterArquivo = getc(arquivoOrigem);
        textoOriginal[i] = caracterArquivo;
        frequenciaCaracteres[caracterArquivo]++;
        i++;
    }
    /*Teste para mostrar a tabela de frequencia*/
    //for (i = 0; i < tamanhoVetorAscii; i++)
    //cout << frequenciaCaracteres[i] << "[" << i << "]" << endl;
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
    if (frequenciaCaracterAscii < A.frequenciaCaracterAscii || caracterAscii < A.caracterAscii)
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
    //cout << "ENTRA NA PILHA ASSIM:" << endl;
    while (--i > 0) {
        if (vetorFrequenciaCaracteres[i] > 0) {
            Filtragem* contagem = new Filtragem();
            contagem->dir = NULL;
            contagem->esq = NULL;
            contagem->caracterAscii = i;
            contagem->frequenciaCaracterAscii = vetorFrequenciaCaracteres[i];
            contagem->leaf = true;
            cout << (*contagem) << endl;
            frequenciaAscii.push(contagem);
        }
    }/*
    cout <<"FICA NA PILHA ASSIM:" << endl;
    while (!frequenciaAscii.empty()) {
        Filtragem* frequencia = frequenciaAscii.top();
        cout << (*frequencia) << endl; // Print highest priority string
        frequenciaAscii.pop(); // Remmove highest priority string
    }
*/
}

Huffman::Huffman(long tam) {
    codigoBinario = "";
    textoArquivoDestino = "";
    quantidadeBits = 0;
}

void Huffman::encodeHuffman(filaprioridade fila) {
    arvoreCodificada = fila;
    cout << "HUFFMAN:::FICA NA PILHA ASSIM:" << endl;
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
    cout << (*root) << endl << endl << endl;

    /*cout << "FICA NA PILHA ASSIM:" << endl;
    while (!arvoreCodificada.empty()) {
        Filtragem* frequencia = arvoreCodificada.top();
        cout << (*frequencia) << endl; // Print highest priority string
        arvoreCodificada.pop(); // Remmove highest priority string
    }*/
}

void Huffman::criaCodigo(Filtragem* root, string bincode) {
    if (root != NULL) {

        bincode += root->getCodigobinario();
        criaCodigo(root->getDir(), bincode);
        //cout<<"DIR - bincode:::::"<<bincode<<endl;
        criaCodigo(root->getEsq(), bincode);
        //cout<<"ESQ - bincode:::::"<<bincode<<endl;
        if (root->isLeaf()) {
            root->setCodigobinario(bincode);
            tabelaConversao[root->getCaracterAscii()] = root->getCodigobinario();
            //cout << *(root) << endl;
            tabelaCodigoBinario.push(root);
            //cout << *tabelaCodigoBinario.top() << endl;
        }
    }
}

void Huffman::imprimeTeste(int* texto, long tamanhoArquivo) {
    int i, quantidadeCaracteres = 0;
    long tam = tamanhoArquivo;

    int* c = new int[tamanhoArquivo];
    c = texto;
    cout << endl << endl << endl;
    cout << "IMPRIMINDO CODE:" << endl;
    cout << "tamanho do arquivo: " << tam << endl;
    for (it = tabelaConversao.begin(); it != tabelaConversao.end(); it++) {
        cout << (*it).first << " => " << (*it).second << " => " << (*it).second.length() << endl;
        quantidadeBits += (*it).second.length();
    }
    quantidadeCaracteres = (int) tabelaConversao.size();
    cout << quantidadeCaracteres << endl;
    cout << "soma dos bits: " << quantidadeBits << endl;
    cout << "média bits: " << quantidadeBits / quantidadeCaracteres << endl;

    for (i = 0; i < tam; i++) {
        //cout<< " "<<c[i];
        textoArquivoDestino += tabelaConversao.find(c[i])->second;
        //cout << tabelaConversao.find(c[i])->second;
        //cout << texto[i]; //(unsigned int)
    }
    size_t const bitstam(textoArquivoDestino.length());
    //cout << textoArquivoDestino << endl;
    /*while (!tabelaCodigoBinario.empty()) {
        cout << *tabelaCodigoBinario.top() << endl; // Print highest priority string
        tabelaCodigoBinario.pop(); // Remmove highest priority string
    }*/
}

void Arquivo::gravaArquivoDestino(string texto) {
    string leitura;
    int i = 0, k = 0;
    unsigned char teste[8];
    leitura = texto;
    cout << "tamanho texto: " << leitura.length() << endl;
    cout << sizeof(leitura)<< endl;
    cout << leitura << endl;
    arquivoDestino = fopen("teste.huf", "wb");
    boost::dynamic_bitset<> grava(texto);
    if (arquivoDestino != NULL) {
        while(i < leitura.length()) {
            while(k < 8){
                teste[k] = leitura[i];
                i++;
                k++;
            }
            k = 0;
        fwrite(&teste, 1, 1, arquivoDestino);
        teste[0] = '\0';
         }
        //leitura = fread(&texto, sizeof(texto), sizeof(texto), arquivoDestino);
        fclose(arquivoDestino);
    }
    //cout << leitura << endl;
}

void Arquivo::leArquivoDestino() {
    string leitura;
    int i = 0, k = 0;
    unsigned char teste[8];
    arquivoCompactado = fopen("teste.huf", "rb");
    if (arquivoCompactado != NULL) {
        while(!feof(arquivoCompactado)){
        fread(&teste, sizeof(teste), 1, arquivoDestino);
        //leitura += teste;
        printf ("%s", teste);
        //teste = "0";
         }
        //leitura = fread(&texto, sizeof(texto), sizeof(texto), arquivoDestino);
        fclose(arquivoDestino);
    }
    //cout << leitura << endl;
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
