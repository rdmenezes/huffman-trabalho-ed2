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
private:
    int caracterAscii;
    int frequenciaCaracterAscii;
public:
    bool operator<(const Filtragem &A)const;
    bool operator==(const Filtragem &A)const;
    bool ordenaPorFrequencia(Filtragem A, Filtragem B);

};

class Estatistica {
private:
    int taxaCompactacao;
    int mediaBits;
    int tempoConsumido;
    std::priority_queue<Filtragem*>frequenciaAscii;

public:
    void filtraFrequencia(int tamanhoVetor, int* vetorFrequenciaCaracteres);
};

class Huffman {
private:
    int* quantidadeBits;
public:
    void encodeHuffman();
    void decodeHuffman();

};

bool verificaArquivo(char* nomeArquivo);

#endif	/* HUFFMAN_H */

