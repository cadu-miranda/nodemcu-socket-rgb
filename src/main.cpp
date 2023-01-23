
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char *ssid = "SSID";
const char *password = "PASSWORD";

AsyncWebServer server(8081);
AsyncWebSocket ws("/rgb");

const int redLedPin = 12, greenLedPin = 4, blueLedPin = 15;

DynamicJsonDocument doc(1024);

void notifyClients() { ws.textAll("connection"); }

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {

  deserializeJson(doc, (char *)data);

  int redLight = doc["data"]["r"], greenLight = doc["data"]["g"],
      blueLight = doc["data"]["b"];

  analogWrite(redLedPin, redLight);
  analogWrite(greenLedPin, greenLight);
  analogWrite(blueLedPin, blueLight);

  AwsFrameInfo *info = (AwsFrameInfo *)arg;

  if (info->final && info->index == 0 && info->len == len &&
      info->opcode == WS_TEXT) {
    data[len] = 0;

    if (strcmp((char *)data, "connection") == 0)

      notifyClients();
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client,
             AwsEventType type, void *arg, uint8_t *data, size_t len) {

  switch (type) {

  case WS_EVT_CONNECT:
    Serial.printf("Cliente #%u conectado do IP: %s\n", client->id(),
                  client->remoteIP().toString().c_str());
    break;

  case WS_EVT_DISCONNECT:
    Serial.printf("Cliente #%u desconectado do IP: \n", client->id());
    break;

  case WS_EVT_DATA:
    handleWebSocketMessage(arg, data, len);
    break;

  case WS_EVT_PONG:
  case WS_EVT_ERROR:
    break;
  }
}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);

  while (WiFi.status() != WL_CONNECTED) {

    delay(1000);

    Serial.println("Conectando ao Wi-Fi..");
  }

  Serial.println(WiFi.localIP());

  initWebSocket();

  server.begin();
}

void loop() { ws.cleanupClients(); }
