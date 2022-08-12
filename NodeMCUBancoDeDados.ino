#include <ESP8266WiFi.h>           // Use this for WiFi instead of Ethernet.h
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#define LM35 A0

int leitura;
float leituraconvertida;
float leituratensao;
float leiturapotencia;
char sentenca[128];
char CORRENTE[10];
char TENSAO[10];
char POTENCIA[10];

IPAddress server_addr(185, 42, 117, 115);  // O IP DO SERVIDOR DA CLEVER CLOUD

char user[] = "XXXXX";          //Usuario MySQL
char password[] = "XXXXX";     //Senha MySQL  

char ssid[] = "XXXX";         //Nome de rede Wifi   
char pass[] = "XXXX";         //Senha Wi-Fi 

char INSERT_SQL[] = "INSERT INTO bkulbg7qoqzidjrlyyay.ENERGIA (EQUIPAMENTO, CORRENTE, TENSAO, POTENCIA) VALUES ('13', 10.1, 127, 150)";


WiFiClient client;                 // Use this for WiFi instead of EthernetClient
MySQL_Connection conn(&client);
MySQL_Cursor* cursor;


void setup()
{
  Serial.begin(115200);
  while (!Serial);   // wait for serial port to connect. Needed for Leonardo only


  // Begin WiFi section
  Serial.printf("\nConnecting to %s", ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }


  // print out info about the connection:
  Serial.println("\nConnected to network");
  Serial.print("My IP address is: ");
  Serial.println(WiFi.localIP());

 

  Serial.print("Connecting to SQL...  ");
  if (conn.connect(server_addr, 3306, user, password))
    Serial.println("OK.");
  else
    Serial.println("FAILED.");
  
  // create MySQL cursor object
  cursor = new MySQL_Cursor(&conn);
}

 

void loop()
{
  if (conn.connected())
    cursor->execute(INSERT_SQL);


  delay(5000);
}