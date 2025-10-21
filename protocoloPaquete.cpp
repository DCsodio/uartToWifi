#include "protocoloPaquete.h"
//ETAPA DE RECEPCION DE DATOS DE UART
uint32_t calcularChecksum(Paquete* pkt);
Paquete pkt;
uint32_t checksum=0;
uint8_t buffer[sizeof(Paquete)];
bool headerEncontrado=false;
bool nuevoPaquete=false;
uint32_t idx = 0;

uint32_t calcularChecksum(Paquete* pkt) {
    uint32_t sum = 0;
    // Sumar todos los bytes excepto los del campo checksum
    for (size_t i = 0; i < sizeof(Paquete) - sizeof(pkt->checksum); i++) {
        sum += ((uint8_t*)pkt)[i];  // convertimos pkt a bytes directamente
    }
    return sum;
}

void analizarPaquete(void){
    while(Serial1.available()!=0 && nuevoPaquete==false) {
        buffer[idx]=Serial1.read();
        if(headerEncontrado==true){
            idx++; //leemos todos los bytes restantes
            if(idx>=sizeof(Paquete)){ // si es igual debemos copiarlo
                memcpy(&pkt,buffer,sizeof(Paquete)); //copiamos buffer en pkt
                Serial.println("estoy aca");
                checksum=calcularChecksum(&pkt);
                if (pkt.checksum==checksum){//SEGUIR LA MAQUINA DE ESTADO
                    Serial.printf("OK -> %u | %f | %d \n",pkt.distanciaMm, pkt.grados, pkt.analizando);
                    nuevoPaquete=true;
                
                }else{
                    Serial.println("ERROR EN EL CHECKSUM");
                   
                }
                idx=0;
                headerEncontrado=false;
            }
        }else{
            if(buffer[0]==HEADERONE && idx==0){// espero el primer header[0]
                idx++;
            }else if(buffer[1]==HEADERTWO && idx==1){ // espero el segundo header[1]
                headerEncontrado=true;
                idx++;
            }else if(buffer[1]!=HEADERTWO && idx==1){ //si es distinto reinciamos
                headerEncontrado=false;
                Serial.println("ERROR EN EL PAQUETE");
                idx=0;
            }
        }
    }
}

Paquete getPaquete(void){
    nuevoPaquete=false;
    return pkt;
}
bool nuevoPaquete(void){
    return nuevoPaquete;
}
