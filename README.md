# exemplo04-iotRegisteredEth

   Jose Maria Cesario Jr
   Exemplo IBM Watson IoT Platform
   https://quickstart.internetofthings.ibmcloud.com/#/
   Hardware: Arduino UNO + Ethernet Shield + sensor BMP180
   
   Logica:
   1. obtem as grandezas de temperatura, pressao e altitude do sensor BMP180
   2. formata os resultados como JSON string para ser enviado ao IBM Watson IoT Platform
   3. conecta no servidor MQTT quickstart do IBM Watson IoT Platform
   
   Referencias Bluemix e IoTF:
   https://developer.ibm.com/recipes/tutorials/getting-started-with-ibm-iotf-1-data-publish/
   http://www.ibm.com/developerworks/cloud/library/cl-bluemix-arduino-iot2/index.html
   http://public.dhe.ibm.com/software/dw/cloud/cl-bluemix-arduino-iot2/MQTT_IOT_SENSORS.ino

   referencias conversao float para string
   http://www.hobbytronics.co.uk/arduino-float-vars
   http://forum.carriots.com/index.php/topic/61-wireless-gardening-with-arduino-cc3000-wifi-modules/page-2
