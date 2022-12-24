#include <ESP8266WiFi.h>           
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

IPAddress server_addr(185,42,117,115);  //IP of the MySQL *server* here
char user[] = "XXXXX";              	// MySQL user login username
char password[] = "XXXXXX";        		// MySQL user login password


//query
char INSERT_SQL[] = "INSERT INTO bancodedadosnome.tabela (colunanome) VALUES ('Hello, Arduino!')";

// WiFi
char ssid[] = "XXXXXXX";         // your SSID
char pass[] = "XXXXXX";     	// your SSID Password

WiFiClient client;                
MySQL_Connection conn(&client);
MySQL_Cursor* cursor;

void setup()
{
  Serial.begin(115200);
  while (!Serial); 

  //Begin WiFi section
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
