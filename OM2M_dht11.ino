#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <DHT.h>

HTTPClient http;

#define MAIN_SSID "RAHUL 4G"
#define MAIN_PASS "poorva2000"

#define CSE_IP      "192.168.100.7"
#define CSE_PORT    8000
#define HTTPS       false
#define OM2M_ORGIN  "admin:admin"
#define OM2M_MN     "/~/in-cse/in-name/"
#define OM2M_AE     "AE_Farmlands"
#define OM2M_DATA_CONT  "Location-1/Data"

#define DHTPIN D2     //output pin of dht is connected
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
Serial.begin(115200);
//delay(10);
dht.begin();
WiFi.begin(MAIN_SSID,MAIN_PASS);
}

void loop() {
static int i=0; 
float h = dht.readHumidity();
float t = dht.readTemperature(true);
String data="["+String(h)+","+String(t)+"]";

String server="http://" + String() + CSE_IP + ":" + String() + CSE_PORT + String()+OM2M_MN;
http.begin(server + String() +OM2M_AE + "/" + OM2M_DATA_CONT + "/");
http.addHeader("X-M2M-Origin", OM2M_ORGIN);
http.addHeader("Content-Type", "application/json;ty=4");
http.addHeader("Content-Length", "100");

String req_data = String() + "{\"m2m:cin\": {"

  + "\"con\": \"" + data + "\","
  
  + "\"rn\": \"" + "cin"+String(i++) + "\","

  + "\"cnf\": \"text\""

  + "}}";
int code = http.POST(req_data);
http.end();
Serial.println(code);
delay(10000);
}
