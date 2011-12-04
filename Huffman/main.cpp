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
int main(int argc, char ** argv) {
    /*Estruturas utilizadas para contar o tempo de execução do programa*/
    struct timeval inicio;
    struct timeval fim;
    /* Verifica se os argumentos (argc e argv) foram digitados corretamente */
    if ((argc < 3) || (argc > 4)) {
        cout << "Uso: huffman [opção] [arq_origem] [arq_destino]" << endl;

        return 1;
    }

    /* Verifica se existe arquivo de origem */
    if (verificaArquivo(argv[2])) {
        return 1;
    }
    gettimeofday(&inicio, NULL);
    if (strcmp(argv[1], "-c") == 0) {
        /* Instancia o objeto a compactar */
        Arquivo * compactar;

        compactar = new Arquivo(argv[2]);
        int k = 0;
        char* fileName = argv[2];
        char* original;
        while (argv[2][k]!= '\0')
            k++;
        original = (char*) malloc(k+1);
        k=0;
        while (argv[2][k]!= '\0'){
            original[k] = argv[2][k];
            k++;
        }
        k++;
        original[k] = '\0';
        k = 0;
        /* Conta caracteres do arquivo */
        compactar -> contaCaracteres();
        /*Cria objeto para a classe Estatistica e retira as frequencias de valor 0 da lista
         * de frequencia */
        Estatistica * estatistica = new Estatistica();
        estatistica -> filtraFrequencia(compactar -> getTamanhoVetorAscii(), compactar -> getFrequenciaCaracteres());

        Huffman * codifica = new Huffman(compactar->getTamanhoArquivoOrigem());
        codifica -> encodeHuffman(estatistica -> getFrequenciaAscii());
        codifica -> criaCodigo(codifica -> getRoot(), codifica -> getCodigoBinario());
        codifica->imprimeTeste(compactar->getTextoOriginal(), compactar->getTamanhoArquivoOrigem());
        if (argc == 3) {
            while (fileName[k] != '\0') {
                k++;
                if (fileName[k] == '.') {
                    fileName[++k] = 'h';
                    fileName[++k] = 'u';
                    fileName[++k] = 'f';
                    fileName[++k] = '\0';
                }
            }
        } else if (argc == 4) {
            fileName = argv[3];
        }
        compactar->gravaArquivoDestino(codifica->getTextoArquivoDestino(), fileName, original);
        gettimeofday(&fim, NULL);
        // Calculando tempo de execução em microsegundos
        double tI = inicio.tv_sec*1000000 + (inicio.tv_usec);
        double tF = fim.tv_sec*1000000  + (fim.tv_usec);
        int comp = ((float)compactar -> getTamanhoArquivoDestino()/(float)compactar -> getTamanhoArquivoOrigem())*100;
        //Informações mostradas ao usuário
        cout << "Arquivo compactado........... : " << fileName << endl;
        cout << "Tamanho do arquivo original.. : " << compactar -> getTamanhoArquivoOrigem() << " bytes" << endl;
        cout << "Tamanho do arquivo compactado : " << compactar -> getTamanhoArquivoDestino() << " bytes" << endl;
        cout << "Taxa de compactação.......... : " << comp << "%" << endl;
        cout << "Média de bits por caractere.. : " << codifica -> getMediaBits() << endl;
        printf("Tempo consumido.............. : %.f ms", (tF-tI)/1000);
        cout << endl;
    }/*Descompacta arquivo*/
    else if (strcmp(argv[1], "-d") == 0) {
        Arquivo * descompactar;
        int k = 0;
        descompactar = new Arquivo(argv[2]);
        char* fileName = argv[2];


        descompactar->leArquivoDestino(fileName);
        /*Cria objeto para a classe Estatistica e retira as frequencias de valor 0 da lista
         * de frequencia */
        Estatistica * estatistica = new Estatistica();
        estatistica -> filtraFrequencia(descompactar -> getTamanhoVetorAscii(), descompactar -> getFrequenciaCaracteres());

        Huffman * decodifica = new Huffman(descompactar->getTamanhoArquivoOrigem());
        //cout << "encode" << endl;
        decodifica -> encodeHuffman(estatistica -> getFrequenciaAscii());
        //cout << "cria codigo" << endl;
        decodifica -> criaCodigo(decodifica -> getRoot(), decodifica -> getCodigoBinario());
        //cout << "decodifica" << endl;
        float z = 0;
        while (decodifica->getStringSize() < descompactar->getTamanhoCaracteresBinarios()) {
            decodifica -> decodeHuffman(decodifica -> getRoot(), descompactar -> getArquivoDescompactado());
            //cout << (z++ / descompactar->getTamanhoCaracteresBinarios())*100 << "%" << endl;
        }
        if (argc == 3) {
            descompactar->gravaArquivoTxt(decodifica->getTextoArquivoDestino());
            gettimeofday(&fim, NULL);
            // Calculando tempo de execução em microsegundos
            double tI = inicio.tv_sec * 1000000 + (inicio.tv_usec);
            double tF = fim.tv_sec * 1000000 + (fim.tv_usec);
            printf("Tempo consumido.............. : %.f ms", (tF - tI) / 1000);
            cout << endl;
        } else {
            cout << "Uso: huffman [opção] [arq_origem] [arq_destino]" << endl;
            return 1;
        }
    } else {
        cout << "Uso: huffman [opção] [arq_origem] [arq_destino]" << endl;
        return 1;
    }
    return 0;
}


//~ Formatted by Jindent --- http://www.jindent.com
