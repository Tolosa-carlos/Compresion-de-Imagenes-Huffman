//
// Created by carlo_cq0emdi on 11/5/2024.
//

#ifndef TPFINAL_HUFFMAN_H
#define TPFINAL_HUFFMAN_H


#include <iostream>
#include <unordered_map>
#include <vector>

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

bool leerImagen(const char* nombreArchivo, std::vector<unsigned char>& datosImagen, int& ancho, int& alto, int& canales); // canales: 1- escala de grisees, 3- RGB, 4- RGBA
bool escribirImagen(const char* nombreArchivo, const std::vector<unsigned char>& datosImagen, int ancho, int alto, int canales);

#endif //TPFINAL_HUFFMAN_H
