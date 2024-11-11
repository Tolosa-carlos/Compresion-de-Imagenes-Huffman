//
// Created by carlo_cq0emdi on 11/5/2024.
//

#ifndef TPFINAL_HUFFMAN_H
#define TPFINAL_HUFFMAN_H


#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <queue>
#include <string>
#include <cstdlib>

//estructura de un nodo para el arbol de huffman
struct nodoHuffman{
    uint32_t color;  // Color comprimido en 32 bits (RGBA)
    int frecuencia;
    nodoHuffman *izq;
    nodoHuffman *der;
};

struct comparadorFrecuencia{
    bool operator()(nodoHuffman* izq, nodoHuffman* der){ // Se compara el valor de la frecuencia entre ambos nodos hijos
        return izq->frecuencia > der->frecuencia;
    }
};



nodoHuffman* crearNodo(uint32_t color, int frecuencia, nodoHuffman* izq, nodoHuffman* der);
nodoHuffman* arbolHuffman(const std::unordered_map<uint32_t, int>& frecuencia); // Crea el arbol usando una cola de prioridad segun la frecuencia de los caracteres
void generarCodigo(nodoHuffman* nodo, const std::string& codigoActual, std::unordered_map<uint32_t, std::string>& codigoHuffman);
std::vector<uint32_t> cuantizarColores(std::vector<uint32_t>& imagen, int k);
std::string comprimirImagen(std::vector<uint32_t>& imagenCuantizada, std::unordered_map<uint32_t, std::string>& codigoHuffman);
bool guardarImagenComprimida(const char* ruta, const std::string& datosComprimidos, const std::unordered_map<uint32_t, std::string>& codigoHuffman);
void liberarArbol(nodoHuffman* raiz);
std::vector<uint32_t> leerImagenRAW(const char* ruta, int ancho, int alto); // canales: 1- escala de grisees, 3- RGB, 4- RGBA
bool escribirImagenComprimida(const char* ruta, const std::string& datosComprimidos, const std::unordered_map<unsigned char, std::string>& codigoHuffman);



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
