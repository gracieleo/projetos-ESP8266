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
char user[] = "ue2qqhghuh1yfa2y";          // Usuario MySQL
char password[] = "9L3PdKXc1LMDQON0Xelc";  // Senha MySQL  
char ssid[] = "MARQUES";         //  Nome de rede Wifi   
char pass[] = "familia2019";     //  Senha Wi-Fi 

char INSERT_SQL[] = "INSERT INTO bkulbg7qoqzidjrlyyay.ENERGIA (EQUIPAMENTO, CORRENTE, TENSAO, POTENCIA) VALUES ('%s', %s, %s, %s)";

WiFiClient client;                 // Use this for WiFi instead of EthernetClient
MySQL_Connection conn(&client);
MySQL_Cursor* cursor;

void setup()
{
  Serial.begin(115200);
  while (!Serial); // wait for serial port to connect. Needed for Leonardo only

  // Begin WiFi section
  Serial.printf("\nConnecting to %s", ssid);
  WiFi.begin(ssid, pass);
 
  
  while (WiFi.status() != WL_CONNECTED)
  {
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

   leitura = analogRead(LM35);
   leituraconvertida = (float(analogRead(LM35))*5/(1023))/0.01;
   leituratensao = 128.2;
   leiturapotencia = (leituratensao)*(leituraconvertida);
   
   dtostrf(leituraconvertida, 4, 1, CORRENTE);
   dtostrf(leituratensao, 4, 1, TENSAO);
   dtostrf(leiturapotencia, 4, 1, POTENCIA);
   
   sprintf(sentenca, INSERT_SQL, "VILA", CORRENTE, TENSAO, POTENCIA);
   Serial.println(INSERT_SQL);
   Serial.println(sentenca); 
   cursor->execute(sentenca);

 

  delay(5000);
}