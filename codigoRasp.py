import requests

# IP de cada ESP32
ESP_1 = "192.168.1.50" //Aca tiene que ir la IP del ESP1
ESP_2 = "192.168.1.51" //Aca tiene que ir la IP del ESP2

// Me conviene mandar el nombre de la deteccion de manos y "switchear" como en un case los estados,. De ON -> OFF y de OFF -> ON. 
// OFF --> ON --> OFF --> ON
// Vel 1 --> Vel 2 --> Vel 3 --> OFF --> Vel 1

def enviar(ip, mensaje):
    try:
        respuesta = requests.get(
            f"http://{ip}/accion",
            params={"mensaje": mensaje},
            timeout=2
        )

        print(f"ESP32 {ip}: {respuesta.text}")

    except requests.exceptions.RequestException:
        print(f"No se pudo conectar con {ip}")



    if opcion == "Gesto_Luz_P1_1":
        enviar(ESP_LUZ, "Gesto_Luz_P1_1")

    elif opcion == "Gesto_Vent":
        enviar(ESP_CAFETERA, "Gesto_Vent")

    elif opcion == "Gesto_Per":
        enviar(ESP_CAFETERA, "Gesto_Per")

    elif opcion == "Gesto_Luz_P1_2":
        enviar(ESP_LUZ, "Gesto_Luz_P1_2")

    elif opcion == "Gesto_Tol":
        enviar(ESP_LUZ, "Gesto_Tol")

    elif opcion == "Gesto_Luz_P2_1":
        enviar(ESP_LUZ, "Gesto_Luz_P2_1")

    elif opcion == "Gesto_Luz_P2_2":
        enviar(ESP_LUZ, "Gesto_Luz_P2_2")

