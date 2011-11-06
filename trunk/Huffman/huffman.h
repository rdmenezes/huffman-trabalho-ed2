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
#include <algorithm>

class Arquivo{
private:
    FILE* arquivoOrigem;
    FILE* arquivoDestino;
    int tamanhoArquivoOrigem;
    int tamanhoArquivoDestino;
    std::vector<int>* frequenciaCaracteres;
    std::vector<int>* quantidadeBits;
    
public:
    void leArquivo(int* argc, char** argv);
    void contaCaracteres(FILE *f);
    
};

class Estatistica{
private:
    int taxaCompactacao;
    int mediaBits;
    int tempoConsumido;
    
public:
};

class Huffman{
private:
    
public:
    void encodeHuffman();
    void decodeHuffman();
     
};





#endif	/* HUFFMAN_H */

