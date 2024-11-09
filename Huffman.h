//
// Created by carlo_cq0emdi on 11/5/2024.
//

#ifndef TPFINAL_HUFFMAN_H
#define TPFINAL_HUFFMAN_H


#include <iostream>
#include <unordered_map>
#include <vector>

#include <stdint.h>
#include <cstdio>

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
void generarCodigo(nodoHuffman* ruta, const std::string& caracter, std::unordered_map<char, std::string>& codigoHuffman);
void liberarArbol(nodoHuffman* raiz);




unsigned char* leerImagen(const char* nombreArchivo, int& ancho, int& alto, int& canales); // canales: 1- escala de grisees, 3- RGB, 4- RGBA
bool escribirImagen(const char* nombreArchivo, unsigned char* datosImagen, int ancho, int alto, int canales);



/*

enum tipoImagen{
    PNG, JPG, BMP, TGA
};

struct imagen{
    uint8_t* datos = NULL;
    size_t tamano = 0;
    int ancho;
    int alto;
    int canales;

    imagen(const char* nombreArchivo);
    imagen(int ancho, int alto, int canales);
    imagen(const imagen& img);
    imagen();
    bool leer(const char* nombreArchivo);
    bool escribir(const char* nombreArchivo);

};


tipoImagen getTipoImagen(const char* nombreArchivo);*/
/*imagen f1(imagen* img, const char* nombreArchivo);
imagen f2(imagen* img);
imagen f3(const imagen& img);
imagen eliminarDatosImagen(const imagen* img);



bool leer(imagen* img, const char* nombreArchivo);
bool escribir(imagen *img, const char* nombreArchivo);
*/















/*
void inicializarCentroides(std::vector<std::vector<int>>& centroides, int k, int ancho, int alto, const std::vector<unsigned char>& datosImagen);
int centroideCercano(const std::vector<int>& pixel, const std::vector<std::vector<int>>& centroide);
void algoritmoKMeans(std::vector<unsigned char>& datosImagen, int ancho, int alto, int k);
*/
#endif //TPFINAL_HUFFMAN_H
