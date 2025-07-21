# Configuración IDE desarrollo

Para la configuración del entrono de desarrollo se dirige a la siguiente pagina en donde se encuentra el repositorio para poder cargar la libreria que permite programar la placa de desarrollo NodeMCU V3.0.

[https://github.com/esp8266/Arduino](https://github.com/esp8266/Arduino)

En la página se encuentra el siguiente link, para agregar los archivos necesarios para empezar a programar la tarjeta con el IDE de arduino.

El link de acontinuación se pega en el siguiente apartado luego de abrir el IDE de Arduino,  preferencies/Additional Boards Manager URls
```jsx
https://arduino.esp8266.com/stable/package_esp8266com_index.json
```
Luego de copiar el Link, se instala la nueva tarjeta de desarrollo en el siguiente apartado
```jsx
/tools/board /BoardsManager
```
En la nueva ventana en el cuadro de busqueda se inserta "ESP8266" y se hace click en instalar en el único resultado que aparece.

Finalmente se va a la ruta indicada a continuación y se selecciona la tarjeta NodeMCU V1.0.
```jsx
/tools/board /ESP8266 Boards/NodeMCU V1.0
```
Con estos pasos se finaliza la configuración del entorno de desarrollo para la tarjeta NodeMCU

------------

## Librerias descargadas .zip

Las librerias descritas a continuacion se descargan como .zip y se agregan desde el IDE de Arduino.

- Sensor huellas digitales: https://github.com/adafruit/Adafruit-Fingerprint-Sensor-Library
- Pantalla OLED: https://github.com/adafruit/Adafruit_SSD1306
- Pantalla OLED graficos: https://github.com/adafruit/Adafruit-GFX-Library
- Pantalla OLED I2C: https://github.com/adafruit/Adafruit_BusIO

- Sockets Clients: https://downloads.arduino.cc/libraries/github.com/Links2004/WebSockets-2.3.5.zip?_gl=1*1kodayt*_ga*NjI2NzQ3NTcuMTY0MTQ3NTk4Mg..*_ga_NEXN8H46L5*MTY0MTQ3ODAzMi4yLjEuMTY0MTQ3ODc5NS4w

## Librerias descargadas desde el IDE
Las librerias a continuación se definen cuando se configura la tarjeta NODE MCU;

- ESP8266WiFi.h
- ESP8266HTTPClient.h

Las librerias a continuación se descargan desde el IDE:
- ArduinoJson.h

