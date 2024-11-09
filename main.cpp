#include "Huffman.h"
#include <iostream>
#include <unordered_map>

int main() {
    std::unordered_map<char, int> frecuencias = {
        {'a', 5}, {'b', 9}, {'c', 12}, {'d', 13}, {'e', 16}, {'f', 45}
    };

    NodoHuffman* raiz = construirArbol(frecuencias);

    std::unordered_map<char, std::string> huffmanCodigo;
    generarCodigos(raiz, "", huffmanCodigo);

    std::cout << "Códigos de Huffman para los caracteres:" << std::endl;
    imprimirCodigos(huffmanCodigo);

    liberarArbol(raiz);

    return 0;
}
