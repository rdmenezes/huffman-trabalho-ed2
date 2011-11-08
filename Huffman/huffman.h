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
    friend class Contagem;
private:
    FILE* arquivoOrigem;
    FILE* arquivoDestino;
    int tamanhoArquivoOrigem;
    int tamanhoArquivoDestino;
    int const tamanhoVetorAscii;
    int* frequenciaCaracteres;
    int* quantidadeBits;


public:
    Arquivo(char* nomeArquivo);
    void contaCaracteres();
    void filtraFrequencia();
    void contaBits(std::vector<int>* quantidadeBits);
    void criaArquivoDestino(FILE* arquivoDestino);
    int gravaArquivoDestino(FILE* arquivoDestino, int* tamanhoArquivoDestino);
};

class Contagem {
    friend class Arquivo;
private:
    int caracterAscii;
    int frequenciaCaracterAscii;
    std::priority_queue<Contagem> frequenciaAscii;
};

class Estatistica {
private:
    int taxaCompactacao;
    int mediaBits;
    int tempoConsumido;

public:
};

class Huffman {
private:

public:
    void encodeHuffman();
    void decodeHuffman();

};

bool verificaArquivo(char* nomeArquivo);

#endif	/* HUFFMAN_H */

