# Proyecto: Puente UART ↔ WebSocket (ESP32)

Este proyecto implementa un **puente de comunicación bidireccional** entre un dispositivo conectado por **UART** (por ejemplo, un microcontrolador LPC845) y un **servidor WebSocket**, utilizando un **ESP32**.

El objetivo es que todo lo recibido por UART se envíe al servidor WebSocket, y todo lo recibido por WebSocket se reenvíe por UART.

---

## ⚙️ Funcionamiento

1. El ESP32 se conecta a la red WiFi configurada en el código.
2. Una vez conectado, establece conexión con el servidor WebSocket (IP y puerto configurables).
3. En el bucle principal:
   - Si llega un paquete UART, se empaqueta y se envía por WebSocket en formato binario.
   - Si llega un mensaje desde el servidor WebSocket, se reenvía al UART.
4. El sistema intenta reconectarse automáticamente si se pierde la conexión WiFi o WebSocket.

---

## 🧠 Estructura del código

### Archivos principales
- **`main.ino`** → Código principal (setup y loop).
- **`protocoloPaquete.h`** → Define el formato del paquete (`Paquete`) y funciones de análisis (`analizarPaquete`, `getNuevaLectura`, etc.).
- **`websocketHl.h`** → Contiene la configuración y callbacks del cliente WebSocket (`webSocketEvent`, `webSocket`).

---

## 📡 Configuración WiFi

Editá las siguientes líneas con tus credenciales:

```cpp
const char* ssid     = "Tu_SSID";
const char* password = "Tu_Clave";
