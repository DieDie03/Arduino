#include <ArduinoHttpClient.h>
#include <WiFi101.h>

const int microphone = A0;
const int treshold1 = 767;
const int treshold2 = 895;
const int treshold3 = 1023;
int id = 1;
char ssid[] = "WiFi-2.4-A1B4";
char password[] = "wfw9mbw5z7d9h";
char serverAddress[] = "192.168.1.29";  // server address
int port = 80;

WiFiClient wifi;
HttpClient client = HttpClient(wifi, serverAddress, port);
int status = WL_IDLE_STATUS;

void setup() {

  Serial.begin(9600);

  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, password);
    delay(1500);

  }
  pinMode(microphone, INPUT);
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  delay(1500);
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip); 
  delay(1500);
}

void loop() {

  code();

}


void code() {
  //int intensity = analogRead(microphone);
  //String level = " h/l/m";

  // read the status code and body of the response
  Serial.println("making POST request");
  String contentType = "application/json";
  //String data = ((String)"{\"id\" : " + id + ",\"level\": " + level + ",\"intensity\": " + intensity + "}");
  String data = "{\"id\": 4,\"level\": stringee,\"intensity\": 100}";
  if (client.connect("192.168.1.29", 80)) {
    Serial.println("connected");
  }
  else {
    Serial.println("connection failed");
  }
  client.post("MakerHub.API/api/values/post", contentType, data);
  delay(1500);
  Serial.println(data);
  int statusCode = client.responseStatusCode();
  String response = client.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  delay(1500);

  Serial.print("Response: ");
  Serial.println(response);
  delay(1500);

  Serial.println("Wait five seconds");
  delay(7000);
  id += 1;
}
