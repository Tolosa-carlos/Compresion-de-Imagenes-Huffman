//
// Created by carlo_cq0emdi on 11/5/2024.
//

#ifndef TPFINAL_HUFFMAN_H
#define TPFINAL_HUFFMAN_H
#include <iostream>
#include <unordered_map>

struct nodoHuffman{ //Define un nodo del arbol de Huffman que tiene un caracter, su frecuencia y punteros a los dos nodos hijos
    char caracter;
    int frecuencia;
    nodoHuffman *izq;
    nodoHuffman *der;
};

struct comparadorFrecuencia{
    bool operator()(nodoHuffman* izq, nodoHuffman* der){ // Se compara el valor de la frecuencia entre ambos nodos hijos
        return izq->frecuencia > der->frecuencia;
    }
};

nodoHuffman* crearNodo(char caracter, int frecuencia, nodoHuffman* izq, nodoHuffman* der);
nodoHuffman* arbolHuffman(const std::unordered_map<char, int>& frecuencia); // Crea el arbol usando una cola de prioridad segun la frecuencia de los caracteres
void generarCodigo(nodoHuffman* ruta, std::string& caracter, std::unordered_map<char, std::string>& codigoHuffman);




#endif //TPFINAL_HUFFMAN_H
