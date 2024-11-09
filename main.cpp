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

    return 0;
}
