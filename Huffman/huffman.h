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
    long codigobinario;
    Filtragem* esq;
    Filtragem* dir;
public:
    Filtragem();
    int getCaracterAscii() const;
    int getFrequenciaCaracterAscii() const;
    bool operator<(const Filtragem &A)const;
    bool operator==(const Filtragem &A)const;

    long getCodigobinario() const {
        return codigobinario;
    }

    void setCodigobinario(long codigobinario) {
        this->codigobinario = codigobinario;
    }

    bool isLeaf() const {
        return leaf;
    }

    void setLeaf(bool leaf) {
        this->leaf = leaf;
    }

};



/*retirado de http://www.cplusplus.com/reference/stl/priority_queue/priority_queue/*
 * e modificado para atender as necessidades do programa*/
class compara 
{
  bool reverse;
public:
  compara(const bool& revparam=false)
    {reverse=revparam;}
  bool operator() (const Filtragem* lhs, const Filtragem* rhs) const
  {
    if (reverse) return (lhs->getFrequenciaCaracterAscii()<rhs->getFrequenciaCaracterAscii());
    if (lhs->getFrequenciaCaracterAscii() == rhs->getFrequenciaCaracterAscii()) return 
            (lhs->getCaracterAscii() > rhs->getCaracterAscii());
    else return (lhs->getFrequenciaCaracterAscii()>rhs->getFrequenciaCaracterAscii());
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
public:
    void encodeHuffman(filaprioridade fila);
    void decodeHuffman();
    void imprimefila();

};

bool verificaArquivo(char* nomeArquivo);

#endif	/* HUFFMAN_H */

