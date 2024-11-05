//
// Created by carlo_cq0emdi on 11/5/2024.
//

#include "Huffman.h"
#include <queue>
#include <vector>
#include <bitset>

nodoHuffman* crearNodo(char caracter, int frecuencia, nodoHuffman* izq, nodoHuffman* der){
    nodoHuffman* nodo = new nodoHuffman();
    nodo->caracter = caracter;
    nodo->frecuencia = frecuencia;
    nodo->izq = izq;
    nodo->der = der;

    return nodo;
}


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

