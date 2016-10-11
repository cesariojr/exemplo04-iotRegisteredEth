
/*
   19/07/2016
   Jose Maria Cesario Jr
   Exemplo IBM Watson IoT Platform
   https://quickstart.internetofthings.ibmcloud.com/#/
   Hardware: Arduino UNO + Ethernet Shield + sensor BMP180
   
   Logica:
   1. obtem as grandezas de temperatura, pressao e altitude do sensor BMP180
   2. formata os resultados como JSON string para ser enviado ao IBM Watson IoT Platform
   3. conecta no servidor MQTT quickstart do IBM Watson IoT Platform
   4. publica a JSON string para o topico quickstart:MAC_ADDRESS

   referencias Bluemix e IoTF:
   https://developer.ibm.com/recipes/tutorials/getting-started-with-ibm-iotf-1-data-publish/
   http://www.ibm.com/developerworks/cloud/library/cl-bluemix-arduino-iot2/index.html
   http://public.dhe.ibm.com/software/dw/cloud/cl-bluemix-arduino-iot2/MQTT_IOT_SENSORS.ino

   referencias conversao float para string
   http://www.hobbytronics.co.uk/arduino-float-vars
   http://forum.carriots.com/index.php/topic/61-wireless-gardening-with-arduino-cc3000-wifi-modules/page-2
   
*/

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;

byte mac[]    = {0x98, 0x4b, 0x4a, 0x15, 0x91, 0x1b };
char macstr[] = "984b4a15911b";

//Atualize os valores de Org, device type, device id e token
#define ORG "sua_org"
#define DEVICE_TYPE "seu_device"
#define DEVICE_ID "seu_device_id"
#define TOKEN "seu_token"

//broker messagesight server
char servername[] = ORG ".messaging.internetofthings.ibmcloud.com";
char topicName[] = "iot-2/evt/status/fmt/json";
char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientName[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;


float pressao = 0.0;
float altitude = 0.0;
float temperatura = 0.0;

char pressaostr[6];
char altitudestr[6];
char temperaturastr[6];

EthernetClient ethClient;

PubSubClient client(servername, 1883, 0, ethClient);

void setup()
{
  Serial.begin(9600);
  Serial.println("Iniciando...");
  if (!bmp.begin())
  {
    Serial.println("Sensor BMP 180 nao encontrado. Reinicialize o Arduino.");
    while (1) {}
  }

  if (Ethernet.begin(mac) == 0) {
    Serial.println("Falha em obter endereco IP via DHCP. Reinicialize o Arduino.");
    while (1) {}
  }

  Serial.print("[INFO] IP: ");
  Serial.println(Ethernet.localIP());
}

void loop()
{
  char clientStr[34];
  //clientName.toCharArray(clientStr, 34);
  char topicStr[26];
  //topicName.toCharArray(topicStr, 26);
  getData();
  if (!client.connected()) {
    Serial.print("Trying to connect to: ");
    Serial.println(clientStr);
    client.connect(clientStr);
  }
  if (client.connect(clientName, authMethod, token)) {

    // Conversao Floats para Strings
    char TempString[32];  //  array de character temporario

    // dtostrf( [Float variable] , [Minimum SizeBeforePoint] , [sizeAfterPoint] , [WhereToStoreIt] )
    dtostrf(temperatura, 2, 1, TempString);
    String temperaturastr =  String(TempString);
    dtostrf(pressao, 2, 2, TempString);
    String pressaostr =  String(TempString);
    dtostrf(altitude, 2, 2, TempString);
    String altitudestr =  String(TempString);

    // Prepara JSON para IOT Platform
    int length = 0;

    String data = "{\"d\":{\"temperatura\": \"" + String(temperaturastr) + "\",\"pressao\":\"" + String(pressaostr) + "\",\"altitude\":\"" + String(altitudestr) + "\"}}";

    length = data.length();
    Serial.print(F("\nData length"));
    Serial.println(length);

    String json = data;

    char jsonStr[100];
    json.toCharArray(jsonStr, 100);
    boolean pubresult = client.publish(topicStr, jsonStr);
    Serial.print("attempt to send ");
    Serial.println(jsonStr);
    Serial.print("to ");
    Serial.println(topicStr);
    if (pubresult)
      Serial.println("successfully sent");
    else
      Serial.println("unsuccessfully sent");
  }
  delay(5000);
}

void getData() {

  pressao = (float)bmp.readPressure();
  altitude = (float)bmp.readAltitude();
  temperatura = (float)bmp.readTemperature();

  dtostrf(pressao, 6, 0, pressaostr);
  dtostrf(altitude, 6, 0, altitudestr);
  dtostrf(temperatura, 6, 0, temperaturastr);
}



