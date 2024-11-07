//
// Created by carlo_cq0emdi on 11/5/2024.
//

#include "Huffman.h"
#include <queue>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
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
    if(!datos){
        std::cerr<< "Error al leer la imagen." << std::endl;
        return false;
    }

    datosImagen.assign(datos, datos + (ancho*alto*canales));
    stbi_image_free(datos);
    return true;
}

//5.
bool escribirImagen(const char* nombreArchivo, const std::vector<unsigned char>& datosImagen, int ancho, int alto, int canales){
    if(!stbi_write_png(nombreArchivo, ancho, alto, canales, datosImagen.data(), ancho*canales)){
        std::cerr<< "Error al escribir la imagen."<< std::endl;
        return false;
    }
    return true;
}

//6.
void inicializarCentroides(std::vector<std::vector<int>>& centroides, int k, int ancho, int alto, const std::vector<unsigned char>& datosImagen){
    for (int i = 0; i < k; ++i) {
        int indice = (rand() % (ancho*alto))*3;
        centroides[i] = {datosImagen[indice], datosImagen[indice + 1], datosImagen[indice + 2]};
    }
}

//7.
int centroideCercano(const std::vector<int>& pixel, const std::vector<std::vector<int>>& centroide){
    int minimoIndice = 0;
    double mininaDistancia = std::numeric_limits<double>::max();

    for (int i = 0; i < centroide.size(); ++i) {
        double distancia = sqrt(pow(pixel[0] - centroide[i][0], 2) + pow(pixel[1] - centroide[i][1], 2) + pow(pixel[2] - centroide[i][2], 2));

        if(distancia < mininaDistancia){
            mininaDistancia = distancia;
            minimoIndice = i;
        }
    }
    return minimoIndice;
}

//8.
void algoritmoKMeans(std::vector<unsigned char>& datosImagen, int ancho, int alto, int k){
    std::vector<std::vector<int>> centroide(k, std::vector<int>(3));
    inicializarCentroides(centroide, k, ancho, alto, datosImagen);

    std::vector<int> dims(ancho*alto);
    bool cambio = true;
    int contador = 0;

    while (cambio && contador < 100){
        cambio = false;
        contador++;

        for (int i = 0; i < ancho*alto; ++i) {
            std::vector<int> pixel = {datosImagen[i*3], datosImagen[i*3 + 1], datosImagen[i*3 + 2]};
            int cercano = centroideCercano(pixel, centroide);

            if(dims[i] != cercano){
                dims[i] = cercano;
                cambio = true;
            }
        }

        std::vector<std::vector<int>> nuevoCentroide(k, std::vector<int>(3,0));
        std::vector<int> total(k, 0);

        for (int i = 0; i < ancho*alto; ++i) {
            int dim = dims[i];
            nuevoCentroide[dim][0] += datosImagen[i*3];
            nuevoCentroide[dim][1] += datosImagen[i*3 + 1];
            nuevoCentroide[dim][2] += datosImagen[i*3 + 2];
            total[dim]++;
        }

        for (int i = 0; i < k; ++i) {
            if(total[i] != 0){
                centroide[i][0] = nuevoCentroide[i][0] / total[i];
                centroide[i][1] = nuevoCentroide[i][1] / total[i];
                centroide[i][2] = nuevoCentroide[i][2] / total[i];
            }
        }

    }

    for (int i = 0; i < ancho*alto; ++i) {
        int dim = dims[i];
        datosImagen[i*3] = centroide[dim][0];
        datosImagen[i*3 + 1] = centroide[dim][1];
        datosImagen[i*3 + 2] = centroide[dim][2];
    }
}







/*
 1. Crea un nuevo nodo y lo retorna.

 2. Construye el árbol de Huffman utilizando una cola de prioridad minima segun la frecuencia de los caracteres (de menor a mayor frecuencia).
    Suma los nodos de dicha cola e ingresa el resultado a la misma hasta que haya solamente un nodo en la cola con la suma total.

 3. Recorre el árbol y genera los codigos de Huffman (f:=f_{01}=f_0 + f_1, con 0 si se encuentra a la izquierda del nodo raiz
    y con 1 si se encuentra a la derecha).

 4. Utiliza la biblioteca stb_image.h para leer la imagen y guardar los datos en la variable datosImagen junto con las dimensiones de la misma
    y el numero de canales (por ejemplo si es RGB o RGBA).

 5. Utiliza la biblioteca stb_image_write.h para escribir una imagen en formato PNG.

 6. Inicializa los centroides de manera aleatoria seleccionando pixeles de la imagen.

 7. Encuentra el centroide mas cercano a un pixel utilizando la distancia euclidiana.

 8. Aplica el algoritmo K-Means asignando cada pixel a un centroide y recalculando los centroides hasta que se equilibren o se alcance un numero
    maximo de iteraciones.
 */