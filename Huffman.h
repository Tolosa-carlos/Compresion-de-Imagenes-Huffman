//
// Created by carlo_cq0emdi on 11/5/2024.
//

#ifndef TPFINAL_HUFFMAN_H
#define TPFINAL_HUFFMAN_H


#include <iostream>
#include <unordered_map>
#include <vector>

#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>

struct NodoHuffman {
    std::string dato;
    int frecuencia;
    NodoHuffman* izquierda;
    NodoHuffman* derecha;
};

struct Comparador {
    bool operator()(NodoHuffman* a, NodoHuffman* b) {
        return a->frecuencia > b->frecuencia;
    }
};

// Funciones de Huffman
NodoHuffman* construirArbol(const std::unordered_map<char, int>& frecuencias);
void generarCodigos(NodoHuffman* raiz, const std::string& codigo, std::unordered_map<char, std::string>& huffmanCodigo);
void imprimirCodigos(const std::unordered_map<char, std::string>& huffmanCodigo);
void liberarArbol(NodoHuffman* raiz);
#endif //TPFINAL_HUFFMAN_H
