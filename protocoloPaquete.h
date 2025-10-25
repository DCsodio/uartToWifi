#ifndef PAQUETE_STRUCT_H
#define PAQUETE_STRUCT_H

#include <Arduino.h>

#define HEADERONE '{'
#define HEADERTWO '{'


#pragma pack(push, 1)
typedef struct {
    uint8_t  header[2];
    uint8_t analizando; 
    uint16_t distanciaMm;
    float    grados;
    uint32_t posX;
    uint32_t posY;
    uint32_t checksum;
} Paquete;
#pragma pack(pop)

extern Paquete pkt;
extern bool nuevoPaquete;
void analizarPaquete(void);
uint32_t calcularChecksum(Paquete* pkt);
Paquete getPaquete(void);
bool getNuevaLectura(void);

#endif // PAQUETE_STRUCT_H