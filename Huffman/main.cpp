/*
 * File:   main.cpp
 * Author: fguira
 *
 * Created on 5 de Novembro de 2011, 18:48
 */

#include "huffman.h"

using namespace std;

/*
 *
 */
int main(int argc, char ** argv)
{
    /* Verifica se os argumentos (argc e argv) foram digitados corretamente */
    if ((argc < 3) || (argc > 4))
    {
        cout << "Uso: huffman [opção] [arq_origem] [arq_destino]" << endl;

        return 1;
    }

    /* Verifica se existe arquivo de origem */
    if (verificaArquivo(argv[2]))
    {
        return 1;
    }

    /* Instancia o objeto a compactar */
    Arquivo * compactar;

    compactar = new Arquivo(argv[2]);

    /* Conta caracteres do arquivo */
    compactar -> contaCaracteres();

    Estatistica * estatistica = new Estatistica();

    estatistica -> filtraFrequencia(compactar -> getTamanhoVetorAscii(), compactar -> getFrequenciaCaracteres());

    Huffman * codifica = new Huffman();

    codifica -> encodeHuffman(estatistica -> getFrequenciaAscii());
    codifica -> criaCodigo(codifica -> getRoot(), codifica -> getCodigoBinario());
    codifica->imprimeTeste(compactar->getTextoOriginal(), compactar->getTamanhoArquivoOrigem());

    /* Testes com argc e argv */
    cout << endl;
    cout << argc << endl;

    int i = argc;

    while (argc-- > 0)
    {
        cout << *argv++ << "[" << i - argc << "]" << endl;
    }

    return 0;
}


//~ Formatted by Jindent --- http://www.jindent.com
