#include "Huffman.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <queue>
#include <string>
#include <cstdlib>
using namespace std;

int main() {

    /*const unordered_map<char, int> frecuencias = {
            {'a', 5}, {'b', 9}, {'c', 12}, {'d', 13}
    };

    arbolHuffman(frecuencias);*/


    // Supongamos que cargamos la imagen en un vector de colores de 32 bits
    const char* rutaEntrada = "prueba.raw";
    int ancho = 640, alto = 480; // Ajustar el tamaño según tu imagen RAW
    int k = 16; // Número de colores en la paleta

    // Leer la imagen desde el archivo RAW
    std::vector<uint32_t> imagen = leerImagenRAW(rutaEntrada, ancho, alto);
    if (imagen.empty()) {
        return 1;
    }

    // Cuantización de colores
    std::vector<uint32_t> imagenCuantizada = cuantizarColores(imagen, k);

    // Calcular frecuencias de colores cuantizados
    std::unordered_map<uint32_t, int> frecuencias;
    for (uint32_t color : imagenCuantizada) {
        frecuencias[color]++;
    }

    // Construir el árbol de Huffman y generar códigos
    nodoHuffman* raiz = arbolHuffman(frecuencias);
    std::unordered_map<uint32_t, std::string> codigoHuffman;
    generarCodigo(raiz, "", codigoHuffman);

    // Comprimir la imagen usando Huffman
    std::string datosComprimidos = comprimirImagen(imagenCuantizada, codigoHuffman);

    // Guardar la imagen comprimida
    const char* rutaSalida = "imagen_comprimida.huff";
    if (!guardarImagenComprimida(rutaSalida, datosComprimidos, codigoHuffman)) {
        std::cerr << "Error al escribir el archivo comprimido.\n";
    }

    // Liberar memoria
    liberarArbol(raiz);
    // Función para liberar el árbol de Huffman...
    return 0;

/*
    imagen prueba("prueba.png");
    prueba.escribir("new.png");
    imagen copia = prueba;
    for (int i = 0; i < copia.ancho*copia.canales; ++i) {
        copia.datos[i] = 255;
    }
    copia.escribir("copia.png");
    imagen blank(100, 100, 3);
    blank.escribir("blank.png");


*/



    return 0;
}
