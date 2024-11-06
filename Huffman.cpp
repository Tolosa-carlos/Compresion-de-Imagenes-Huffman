//
// Created by carlo_cq0emdi on 11/5/2024.
//
#define STB_IMAGE_IMPLEMENTATION
#include "Huffman.h"
#include <queue>
#include <vector>
#include "stb_image.h"
#include "stb_image_write.h"





//1.
nodoHuffman* crearNodo(char caracter, int frecuencia, nodoHuffman* izq, nodoHuffman* der){
    nodoHuffman* nodo = new nodoHuffman();
    nodo->caracter = caracter;
    nodo->frecuencia = frecuencia;
    nodo->izq = izq;
    nodo->der = der;

    return nodo;
}

//2.
nodoHuffman* arbolHuffman(const std::unordered_map<char, int>& frecuencia){
    std::priority_queue<nodoHuffman*, std::vector<nodoHuffman*>, comparadorFrecuencia>colaMinima;
    for (const auto& entrada : frecuencia) {
        colaMinima.push(crearNodo(entrada.first, entrada.second, nullptr, nullptr));
    }

    while (colaMinima.size() > 1){
        nodoHuffman* izq = colaMinima.top();
        colaMinima.pop();
        nodoHuffman* der = colaMinima.top();
        colaMinima.pop();
        int suma = izq->frecuencia + der->frecuencia;
        colaMinima.push(crearNodo('\0', suma, izq, der));
    }

    return colaMinima.top();
}

//3.
void generarCodigo(nodoHuffman* ruta, const std::string& caracter, std::unordered_map<char, std::string>& codigoHuffman){
    if(!ruta){
        return;
    }
    if(!ruta->izq && !ruta->der){
        codigoHuffman[ruta->caracter] = caracter;
    }
    generarCodigo(ruta->izq, caracter + "0", codigoHuffman);
    generarCodigo(ruta->der, caracter + "1", codigoHuffman);
}

//4.
bool leerImagen(const char* nombreArchivo, std::vector<unsigned char>& datosImagen, int& ancho, int& alto, int& canales){
    unsigned char* datos = stbi_load(nombreArchivo, &ancho, &alto, &canales, 0);
}



















/*
 1. Crea un nuevo nodo y lo retorna.

 2. Construye el árbol de Huffman utilizando una cola de prioridad minima segun la frecuencia de los caracteres (de menor a mayor frecuencia).
    Suma los nodos de dicha cola e ingresa el resultado a la misma hasta que haya solamente un nodo en la cola con la suma total.

 3. Recorre el árbol y genera los codigos de Huffman (f:=f_{01}=f_0 + f_1, con 0 si se encuentra a la izquierda del nodo raiz
    y con 1 si se encuentra a la derecha).
 */