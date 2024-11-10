#include "Huffman.h"
#include "stb_image.h"
#include "stb_image_write.h"
#include <unordered_map>
using namespace std;

int main() {

    const unordered_map<char, int> frecuencias = {
            {'a', 5}, {'b', 9}, {'c', 12}, {'d', 13}
    };

    arbolHuffman(frecuencias);


    const char* rutaEntrada = "prueba2.raw";
    const char* rutaSalida = "new.raw";
    int ancho = 640, alto = 480, canales = 0;
    unsigned char* datosImagen = leerImagen(rutaEntrada, ancho, alto, canales);
    if(datosImagen == nullptr){
        return 1;
    }

    if(!escribirImagen(rutaSalida, datosImagen, ancho, alto, canales)){
        stbi_image_free(datosImagen);
        return 1;
    }

    stbi_image_free(datosImagen);


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
