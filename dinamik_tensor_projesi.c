#include <stdio.h>
#include <stdint.h> 
#include <stdlib.h> 

typedef enum {
    TIP_FLOAT32,
    TIP_INT8
} VeriTipi;

typedef struct {
    VeriTipi tip;
    int eleman_sayisi;
    union {
        float* f32_ptr;  
        int8_t* i8_ptr;  
    } veri;
} TinyTensor;

void nicemle_ve_ata(TinyTensor* t, float* ham_veri, float olcek) {
    int i; 
    t->tip = TIP_INT8;
    t->veri.i8_ptr = (int8_t*)malloc(t->eleman_sayisi * sizeof(int8_t));

    for (i = 0; i < t->eleman_sayisi; i++) {
        float hesaplanan = ham_veri[i] / olcek;
        if (hesaplanan > 127) hesaplanan = 127;
        if (hesaplanan < -128) hesaplanan = -128;
        t->veri.i8_ptr[i] = (int8_t)hesaplanan;
    }
}

int main() {
    int i; 
    float sensor_okumalari[] = {12.5, -5.2, 22.1, 100.0};
    int n = 4;
    float scale = 0.5;
    TinyTensor myTensor;

    printf("--- TinyML Dinamik Tensor Projesi ---\n\n");

    myTensor.eleman_sayisi = n;
    nicemle_ve_ata(&myTensor, sensor_okumalari, scale);

    printf("TEKNIK ANALIZ:\n");
    printf("--------------------------------------------\n");
    printf("Veri Tipi: INT8 (Quantized)\n");
    printf("Union Adresi (Float): %p\n", (void*)myTensor.veri.f32_ptr);
    printf("Union Adresi (Int8):  %p\n", (void*)myTensor.veri.i8_ptr);
    printf("--------------------------------------------\n\n");

    for (i = 0; i < n; i++) {
        printf("Index [%d] | Orjinal: %6.1f | Quantized: %d\n", 
                i, sensor_okumalari[i], myTensor.veri.i8_ptr[i]);
    }

    free(myTensor.veri.i8_ptr);
    printf("\nIslem Basarili.\n");
    system("PAUSE"); 
    return 0;
}
