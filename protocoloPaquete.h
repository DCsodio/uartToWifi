#ifndef PAQUETE_STRUCT_H
#define PAQUETE_STRUCT_H

#include <Arduino.h>

#define HEADERONE '{'
#define HEADERTWO '{'


#pragma pack(push, 1)
typedef struct {
    uint8_t  header[2];
    bool     analizando;   // no se puede inicializar dentro del struct
    uint16_t distanciaMm;
    float    grados;
    uint32_t posX;
    uint32_t posY;
    uint32_t checksum;
} Paquete;
#pragma pack(pop)

extern Paquete pkt;

void analizarPaquete(void);

Paquete getPaquete(void);
bool nuevoPaquete(void);

#endif // PAQUETE_STRUCT_H