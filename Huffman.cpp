//
// Created by carlo_cq0emdi on 11/5/2024.
//

#include "Huffman.h"

#include <fstream>
#include <queue>
#include <vector>
using namespace std;

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

// Función para crear un nuevo nodo de Huffman
nodoHuffman* crearNodo(unsigned char caracter, int frecuencia, nodoHuffman* izq, nodoHuffman* der) {
    nodoHuffman* nodo = new nodoHuffman();
    nodo->caracter = caracter;
    nodo->frecuencia = frecuencia;
    nodo->izq = izq;
    nodo->der = der;
    return nodo;
}

// Función para construir el árbol de Huffman
nodoHuffman* arbolHuffman(const std::unordered_map<unsigned char, int>& frecuencia) {
    std::priority_queue<nodoHuffman*, std::vector<nodoHuffman*>, comparadorFrecuencia> colaMinima;

    // Crear un nodo para cada valor de píxel con su frecuencia
    for (const auto& entrada : frecuencia) {
        colaMinima.push(crearNodo(entrada.first, entrada.second, nullptr, nullptr));
    }

    // Construir el árbol de Huffman
    while (colaMinima.size() > 1) {
        nodoHuffman* izq = colaMinima.top(); colaMinima.pop();
        nodoHuffman* der = colaMinima.top(); colaMinima.pop();
        int suma = izq->frecuencia + der->frecuencia;
        colaMinima.push(crearNodo('\0', suma, izq, der));
    }

    return colaMinima.top();
}

// Función para generar códigos de Huffman
void generarCodigo(nodoHuffman* nodo, const std::string& codigoActual, std::unordered_map<unsigned char, std::string>& codigoHuffman) {
    if (!nodo) return;
    if (!nodo->izq && !nodo->der) {
        codigoHuffman[nodo->caracter] = codigoActual;
    }
    generarCodigo(nodo->izq, codigoActual + "0", codigoHuffman);
    generarCodigo(nodo->der, codigoActual + "1", codigoHuffman);
}

// Función para liberar el árbol de Huffman
void liberarArbol(nodoHuffman* raiz) {
    if (!raiz) return;
    liberarArbol(raiz->izq);
    liberarArbol(raiz->der);
    delete raiz;
}

// Leer imagen en formato RAW
unsigned char* leerImagen(const char* ruta, int ancho, int alto, int canales) {
    std::ifstream archivo(ruta, std::ios::binary);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo de entrada.\n";
        return nullptr;
    }
    int tamaño = ancho * alto * canales;
    unsigned char* datos = new unsigned char[tamaño];
    archivo.read(reinterpret_cast<char*>(datos), tamaño);
    archivo.close();
    return datos;
}

// Escribir imagen comprimida en formato binario
bool escribirImagenComprimida(const char* ruta, const std::string& datosComprimidos, const std::unordered_map<unsigned char, std::string>& codigoHuffman) {
    std::ofstream archivo(ruta, std::ios::binary);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo de salida.\n";
        return false;
    }

    // Guardar el árbol o tabla de Huffman en el archivo (ejemplo: tabla simple de códigos)
    for (const auto& par : codigoHuffman) {
        archivo.write(reinterpret_cast<const char*>(&par.first), sizeof(par.first));
        int tamaño = par.second.size();
        archivo.write(reinterpret_cast<const char*>(&tamaño), sizeof(tamaño));
        archivo.write(par.second.c_str(), tamaño);
    }

    // Escribir los datos comprimidos
    archivo.write(datosComprimidos.c_str(), datosComprimidos.size());
    archivo.close();
    return true;
}










//Forma 2

/*
imagen::imagen(const char* nombreArchivo) {
    if(leer(nombreArchivo)){
        printf("Read %s\n", nombreArchivo);
         tamano = ancho*alto*canales;
    } else{
        printf("Failed %s\n", nombreArchivo);
    };
}

imagen::imagen(int ancho, int alto, int canales) : ancho(ancho), alto(alto), canales(canales){
    tamano = ancho*alto*canales;
    datos = new uint8_t[tamano];
}

imagen::imagen(){
    stbi_image_free(datos);
}

imagen::imagen(const imagen& img) : imagen(img.ancho, img.alto, img.canales){
    memcpy(datos, img.datos, tamano);
}


bool imagen::leer(const char* nombreArchivo){
    datos = stbi_load(nombreArchivo, &ancho, &alto, &canales, 0);
    return datos != NULL;
}

bool imagen::escribir(const char* nombreArchivo){
    tipoImagen tipo = getTipoImagen(nombreArchivo);
    int resultado;
    switch (tipo) {
        case PNG:
            resultado = stbi_write_png(nombreArchivo, ancho, alto, canales, datos, ancho*canales);
            break;
        case BMP:
            resultado = stbi_write_bmp(nombreArchivo, ancho, alto, canales, datos);
            break;
        case JPG:
            resultado = stbi_write_jpg(nombreArchivo, ancho, alto, canales, datos, 100);
            break;
        case TGA:
            resultado = stbi_write_tga(nombreArchivo, ancho, alto, canales, datos);
            break;
    }
    return resultado != 0;
}

tipoImagen getTipoImagen(const char* nombreArchivo){
    const char* ext = strrchr(nombreArchivo, '.');
    if (ext != nullptr){
        if (strcmp(ext, ".png") == 0){
            return  PNG;
        }
        if (strcmp(ext, ".jpg") == 0){
            return  JPG;
        }
        if (strcmp(ext, ".bmp") == 0){
            return  BMP;
        }
        if (strcmp(ext, ".tga") == 0){
            return  TGA;
        }
    }
    return PNG;
}

*/


/*
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

    nodoHuffman* raiz = colaMinima.top();
    std::unordered_map<char, string> codigoHuffman;
    generarCodigo(raiz, "", codigoHuffman);
    cout<< "Codigos de Huffman:\n"<< endl;
    for (const auto& par : codigoHuffman) {
        std::cout << par.first << ": " << par.second << std::endl;
    }
    string caracter = " ";
    for (const auto& par : frecuencia){
        caracter += codigoHuffman[par.first];
    }

    return colaMinima.top();
}

//3.
void generarCodigo(nodoHuffman* ruta, const std::string& caracter, unordered_map<char, std::string>& codigoHuffman){
    if(!ruta){
        return;
    }
    if(!ruta->izq && !ruta->der){
        codigoHuffman[ruta->caracter] = caracter;
    }
    generarCodigo(ruta->izq, caracter + "0", codigoHuffman);
    generarCodigo(ruta->der, caracter + "1", codigoHuffman);

}

void liberarArbol(nodoHuffman* raiz) {
    if (!raiz) return;

    liberarArbol(raiz->izq);
    liberarArbol(raiz->der);

    delete raiz;
}





//Forma 1


//4.
unsigned char* leerImagen(const char* nombreArchivo, int& ancho, int& alto, int& canales){
    unsigned char* datos = stbi_load(nombreArchivo, &ancho, &alto, &canales, 0);
    if(datos == nullptr){
        std::cerr<< "Error al leer la imagen." << std::endl;
    }

    return datos;
}

//5.
bool escribirImagen(const char* nombreArchivo, unsigned char* datosImagen, int ancho, int alto, int canales){
    if(stbi_write_png(nombreArchivo, ancho, alto, canales, datosImagen, ancho*canales)){
        cout<<"Imagen guardada exitosamente"<< nombreArchivo << endl;
        return true;
    } else{
        cerr<< "Error al guardar la imagen"<< nombreArchivo << endl;
        return false;
    }
}


 */























/*
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

*/





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