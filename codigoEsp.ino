#include <WiFi.h>
#include <WebServer.h>

// =========================
// WIFI
// =========================
//Siemprer que se conecta y desconecta el ESP se le cambia la IP, entonces primero tenemosss que tener conectado el ESP y dsp reprogramar la Rasp, a no ser que le asignemos un IP especifico, veo dsp como hacerlo, pero preguntarle a chatgpt.

const char* ssid = "MECA-IoT";
const char* password = "IoT&2026";

// =========================
// PIN DE LA LUZ
// =========================

const int PIN_LUZ = 25;

// Estado actual de la luz
bool estadoLuz1 = false;
bool estadoLuz2 = false;

// Servidor web
WebServer server(80);


// =========================
// RECIBIR ORDEN
// =========================

void recibirAccion() {

    // Obtener el mensaje enviado por la Raspberry
    String mensaje = server.arg("mensaje");

    Serial.print("Mensaje recibido: ");
    Serial.println(mensaje);


    // -------------------------
    // CAMBIAR ESTADO
    // -------------------------

    if (mensaje == "Gesto_Luz_P1_1") {

        estadoLuz1 = !estadoLuz1;

        digitalWrite(PIN_LUZ, estadoLuz);

        if (estadoLuz1) {
            Serial.println("ENCENDIDA");
        } else {
            Serial.println("APAGADA");
        }

    }


    // -------------------------
    
    // -------------------------

    else if (mensaje == "Gesto_Luz_P1_2") {

        estadoLuz2 = !estadoLuz2;

        digitalWrite(PIN_LUZ, HIGH);

        if (estadoLuz2) {
            Serial.println("ENCENDIDA");
        } else {
            Serial.println("APAGADA");
        }
    }

    // -------------------------
    // MENSAJE DESCONOCIDO
    // -------------------------

    else {

        server.send(400, "text/plain", "Orden desconocida");
    }
}


// =========================
// SETUP
// =========================

void setup() {

    Serial.begin(115200);

    pinMode(PIN_LUZ, OUTPUT);

    digitalWrite(PIN_LUZ, LOW);


    // Conectarse al Wi-Fi

    WiFi.begin(ssid, password);

    Serial.print("Conectando al Wi-Fi");

    while (WiFi.status() != WL_CONNECTED) {

        delay(500);

        Serial.print(".");
    }

    Serial.println();

    Serial.println("Wi-Fi conectado");


    // Mostrar IP del ESP32

    Serial.print("IP del ESP32: ");

    Serial.println(WiFi.localIP());


    // Crear la ruta /accion

    server.on("/accion", recibirAccion);


    // Iniciar servidor

    server.begin();

    Serial.println("Servidor iniciado");
}


// =========================
// LOOP
// =========================

void loop() {

    server.handleClient();
}
