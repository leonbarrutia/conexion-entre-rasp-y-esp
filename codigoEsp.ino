#include <WiFi.h>
#include <WebServer.h>

// WIFI
const char* ssid = "MECA-IoT";
const char* password = "IoT&2026";

// LUZ
const int PIN_LUZ = 25;

bool estadoLuz = false;

WebServer server(80);


// RECIBIR ORDEN
void recibirAccion() {

    String mensaje = server.arg("mensaje");

    Serial.print("Mensaje recibido: ");
    Serial.println(mensaje);

    if (mensaje == "Gesto_Luz_P1_1") {

        estadoLuz = !estadoLuz;

        digitalWrite(PIN_LUZ, estadoLuz);

        if (estadoLuz) {
            Serial.println("ENCENDIDA");
        } else {
            Serial.println("APAGADA");
        }
    }

    else if (mensaje == "Gesto_Luz_P1_2") {

        digitalWrite(PIN_LUZ, HIGH);

        Serial.println("ENCENDIDA");
    }
}


// SETUP
void setup() {

    Serial.begin(115200);

    pinMode(PIN_LUZ, OUTPUT);
    digitalWrite(PIN_LUZ, LOW);

    WiFi.begin(ssid, password);

    Serial.print("Conectando al Wi-Fi");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("Wi-Fi conectado");

    Serial.print("IP del ESP32: ");
    Serial.println(WiFi.localIP());

    server.on("/accion", recibirAccion);

    server.begin();

    Serial.println("Servidor iniciado");
}


// LOOP
void loop() {

    server.handleClient();
}
