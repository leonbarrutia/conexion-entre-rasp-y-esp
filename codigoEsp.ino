#include <WiFi.h>
#include <WebServer.h>

// =========================
// WIFI
// =========================

const char* ssid = "MECA-IoT";
const char* password = "IoT&2026";

// =========================
// PIN DE LA LUZ
// =========================

const int PIN_LUZ = 25;

// Estado actual de la luz
bool estadoLuz = false;

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

        estadoLuz = !estadoLuz;

        digitalWrite(PIN_LUZ, estadoLuz);

        Serial.print("Luz: ");

        if (estadoLuz) {
            Serial.println("ENCENDIDA");
        } else {
            Serial.println("APAGADA");
        }

        server.send(200, "text/plain", "Luz cambiada");
    }


    // -------------------------
    // PRENDER
    // -------------------------

    else if (mensaje == "prender") {

        estadoLuz = true;

        digitalWrite(PIN_LUZ, HIGH);

        Serial.println("Luz ENCENDIDA");

        server.send(200, "text/plain", "Luz encendida");
    }


    // -------------------------
    // APAGAR
    // -------------------------

    else if (mensaje == "apagar") {

        estadoLuz = false;

        digitalWrite(PIN_LUZ, LOW);

        Serial.println("Luz APAGADA");

        server.send(200, "text/plain", "Luz apagada");
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
