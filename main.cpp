#include "Huffman.h"
#include "stb_image.h"
#include "stb_image_write.h"
#include <unordered_map>
using namespace std;

int main() {

    /*const unordered_map<char, int> frecuencias = {
            {'a', 5}, {'b', 9}, {'c', 12}, {'d', 13}
    };

    arbolHuffman(frecuencias);*/


    const char* rutaEntrada = "prueba2.raw";
    const char* rutaSalida = "new.raw";
    int ancho = 640, alto = 480, canales = 1;

    // Leer la imagen en datos de píxeles
    unsigned char* datosImagen = leerImagen(rutaEntrada, ancho, alto, canales);
    if (datosImagen == nullptr) {
        return 1;
    }

    // Calcular la frecuencia de cada valor de píxel
    std::unordered_map<unsigned char, int> frecuencia;
    for (int i = 0; i < ancho * alto * canales; i++) {
        frecuencia[datosImagen[i]]++;
    }

    // Construir el árbol de Huffman y generar los códigos de Huffman
    nodoHuffman* raiz = arbolHuffman(frecuencia);
    std::unordered_map<unsigned char, std::string> codigoHuffman;
    generarCodigo(raiz, "", codigoHuffman);

    // Codificar la imagen usando el árbol de Huffman
    std::string datosComprimidos;
    for (int i = 0; i < ancho * alto * canales; i++) {
        datosComprimidos += codigoHuffman[datosImagen[i]];
    }

    // Guardar los datos comprimidos en el archivo de salida
    if (!escribirImagenComprimida(rutaSalida, datosComprimidos, codigoHuffman)) {
        std::cerr << "Error al escribir el archivo comprimido.\n";
        liberarArbol(raiz);
        delete[] datosImagen;
        return 1;
    }

    liberarArbol(raiz);
    delete[] datosImagen;
    std::cout << "Compresión completada exitosamente.\n";
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
