//
// Created by carlo_cq0emdi on 11/5/2024.
//

#include "Huffman.h"
#include <queue>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"


// Función para construir el árbol de Huffman a partir de las frecuencias de los caracteres
NodoHuffman* construirArbol(const std::unordered_map<char, int>& frecuencias) {
    std::priority_queue<NodoHuffman*, std::vector<NodoHuffman*>, Comparador> minHeap;

    // Insertar cada carácter y su frecuencia en la cola de prioridad
    for (const auto& par : frecuencias) {
        NodoHuffman* nodo = new NodoHuffman{par.first, par.second, nullptr, nullptr};
        minHeap.push(nodo);
    }

    // Construir el árbol de Huffman
    while (minHeap.size() > 1) {
        NodoHuffman* izquierda = minHeap.top();
        minHeap.pop();
        NodoHuffman* derecha = minHeap.top();
        minHeap.pop();

        // Crear un nuevo nodo con la suma de frecuencias y establecer sus hijos
        int suma = izquierda->frecuencia + derecha->frecuencia;
        NodoHuffman* nodo = new NodoHuffman{'\0', suma, izquierda, derecha};

        minHeap.push(nodo);
    }

    // El último nodo en la cola es la raíz del árbol de Huffman
    return minHeap.empty() ? nullptr : minHeap.top();
}

// Función recursiva para generar los códigos de Huffman desde el árbol
void generarCodigos(NodoHuffman* raiz, const std::string& codigo, std::unordered_map<char, std::string>& huffmanCodigo) {
    if (!raiz) {
        return;
    }

    // Si es una hoja, almacenar el código correspondiente al carácter
    if (!raiz->izquierda && !raiz->derecha) {
        huffmanCodigo[raiz->dato] = codigo;
    }

    // Recursión hacia la izquierda y la derecha con los códigos "0" y "1" respectivamente
    generarCodigos(raiz->izquierda, codigo + "0", huffmanCodigo);
    generarCodigos(raiz->derecha, codigo + "1", huffmanCodigo);
}

// Función para imprimir los códigos de Huffman generados
void imprimirCodigos(const std::unordered_map<char, std::string>& huffmanCodigo) {
    for (const auto& par : huffmanCodigo) {
        std::cout << par.first << ": " << par.second << std::endl;
    }
}

// Función para liberar la memoria ocupada por el árbol de Huffman
void liberarArbol(NodoHuffman* raiz) {
    if (!raiz) return;

    liberarArbol(raiz->izquierda);
    liberarArbol(raiz->derecha);

    delete raiz;
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