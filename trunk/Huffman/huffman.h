/* 
 * File:   huffman.h
 * Author: fguira
 *
 * Created on 5 de Novembro de 2011, 18:51
 */

#ifndef HUFFMAN_H
#define	HUFFMAN_H

#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <ctime>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

class Arquivo {
private:
    FILE* arquivoOrigem;
    FILE* arquivoDestino;
    long tamanhoArquivoOrigem;
    long tamanhoArquivoDestino;
    const int tamanhoVetorAscii;
    int* frequenciaCaracteres;
public:
    Arquivo(char* nomeArquivo);
    int* contaCaracteres();
    void criaArquivoDestino(FILE* arquivoDestino);
    int gravaArquivoDestino(FILE* arquivoDestino, int* tamanhoArquivoDestino);
    const int getTamanhoVetorAscii() const;
    int* getFrequenciaCaracteres() const;

};

class Filtragem {
    friend class Estatistica;
    friend class Huffman;
private:
    bool leaf;
    int caracterAscii;
    int frequenciaCaracterAscii;
    std::string codigobinario;
    Filtragem* esq;
    Filtragem* dir;
public:
    Filtragem();
    int getCaracterAscii() const;
    int getFrequenciaCaracterAscii() const;
    bool operator<(const Filtragem &A)const;
    bool operator==(const Filtragem &A)const;

    std::string getCodigobinario() const {
        return codigobinario;
    }

    void setCodigobinario(std::string codigobinario) {
        this->codigobinario = codigobinario;
    }

    bool isLeaf() const {
        return leaf;
    }

    void setLeaf(bool leaf) {
        this->leaf = leaf;
    }

    Filtragem* getDir() const {
        return dir;
    }

    void setDir(Filtragem* dir) {
        this->dir = dir;
    }

    Filtragem* getEsq() const {
        return esq;
    }

    void setEsq(Filtragem* esq) {
        this->esq = esq;
    }


};

/*retirado de http://www.cplusplus.com/reference/stl/priority_queue/priority_queue/*
 * e modificado para atender as necessidades do programa*/
class compara {
    bool reverse;
public:

    compara(const bool& revparam = false) {
        reverse = revparam;
    }

    bool operator() (const Filtragem* lhs, const Filtragem* rhs) const {
        if (reverse) return (lhs->getFrequenciaCaracterAscii() < rhs->getFrequenciaCaracterAscii());
        if (lhs->getFrequenciaCaracterAscii() == rhs->getFrequenciaCaracterAscii()) return
            (lhs->getCaracterAscii() > rhs->getCaracterAscii());
        else return (lhs->getFrequenciaCaracterAscii() > rhs->getFrequenciaCaracterAscii());
    }
};
typedef std::priority_queue<Filtragem*, std::vector<Filtragem*>, compara > filaprioridade;

class Estatistica {
private:
    int taxaCompactacao;
    int mediaBits;
    int tempoConsumido;
    filaprioridade frequenciaAscii;

public:
    void filtraFrequencia(int tamanhoVetor, int* vetorFrequenciaCaracteres);

    filaprioridade getFrequenciaAscii() {
        return frequenciaAscii;
    }
};

class Huffman {
private:
    int* quantidadeBits;
    filaprioridade arvoreCodificada;
    filaprioridade tabelaCodigoBinario;
    Filtragem* root;
    std::string codigoBinario;
public:
    filaprioridade code;
    Huffman();
    void encodeHuffman(filaprioridade fila);
    void decodeHuffman();
    void imprimeTeste();

    Filtragem* getRoot() const {
        return root;
    }

    void setRoot(Filtragem* root) {
        this->root = root;
    }

    std::string getCodigoBinario() const {
        return codigoBinario;
    }

    void setCodigoBinario(std::string codigoBinario) {
        this->codigoBinario = codigoBinario;
    }

    void setTabelaCodigoBinario(filaprioridade tabelaCodigoBinario) {
        this->tabelaCodigoBinario = tabelaCodigoBinario;
    }

    filaprioridade getTabelaCodigoBinario() const {
        return tabelaCodigoBinario;
    }
    void criaCodigo(Filtragem* root, std::string bincode);




};

bool verificaArquivo(char* nomeArquivo);

#endif	/* HUFFMAN_H */

