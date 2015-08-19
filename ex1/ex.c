#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

char* anythingToBoolean(void* voidPointer, int sizeBytes) { //function returs dynamically allocated memory !!! must free after pointer use!

    char* charPointer = (char*) voidPointer;
    int bufferLenght = sizeBytes * CHAR_BIT + 1;
    int lastBufferIndex = bufferLenght - 1;
    int lastSizesIndex = sizeBytes - 1;
    char *buffer = malloc(bufferLenght); //allocate number of bytes * number of bits in char (number of bits in 1 byte) + 1 bit for null
    int i, j;

    if (!buffer) { // check whether we have the desired memory, otherwise exit
        return NULL;
    }

    buffer[lastBufferIndex] = 0; // set last bit to null - C-style strings

    for (j = lastSizesIndex ; j >= 0 ; j--) {
        for (i = lastBufferIndex - 1 - (lastSizesIndex - j) * CHAR_BIT ; i >= j * CHAR_BIT ; i--) {
            *(buffer + i) = (*(charPointer + j) & 0b00000001) + 48; // take the current p and apply bitmask with value 1
            *(charPointer + j) >>= 1; // left roll bits
        }
    }
    return buffer;
}

int main () {

    struct P {
        int k;
        int p;
    } ad;

    ad.k = 134;
    ad.p = 1324;
    int de = 15126;
    unsigned long lo = 1231231231312312;
    float f = 34.4;
    char * buffer = anythingToBoolean(&ad, sizeof(ad));
    printf("struct:%s\n", buffer);
    free(buffer);
    buffer = anythingToBoolean(&de, sizeof(de));
    printf("int:%s\n", buffer);
    free(buffer);
    buffer = anythingToBoolean(&lo, sizeof(lo));
    printf("long:%s\n", buffer);
    free(buffer);
    buffer = anythingToBoolean(&f, sizeof(f));
    printf("float:%s\n", buffer);
    free(buffer);


    return 0;
}