/*----------------------------------------------*\
 
  Menampilkan jumlah subscriber Youtube
  
  Hardware : NodeMCU dan Module 7 Segment Max7219
  Author   : Komputronika.com
  Email    : infokomputronika@gmail.com
  Website  : http://www.komputronika.com
  Source   : https://github.com/komputronika/YoutubeSubscriberNodeMCU

  Library  : (1) https://github.com/esp8266/Arduino  
             (2) https://github.com/bblanchon/ArduinoJson
             (3) https://github.com/ozhantr/DigitLedDisplay

\*----------------------------------------------*/

// Include library yang diperlukan
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <DigitLedDisplay.h>

// Gunakan serial sebagai output debug
#define OUTPUT Serial

// Definisi Google API
#define API_KEY "123"
#define CHANNEL_ID "12313213"

// Interval membaca data subscriber (dalam detik)  
#define INTERVAL 10

// WIFI/Hotspot yang digunakan untuk koneksi
#define WIFI_NAME "Aduh"
#define WIFI_PASS "Bagus"

// Buat object Wifi
ESP8266WiFiMulti WiFiMulti;

// Buat object http
HTTPClient http;

// Buat object display
/* Pin NodeMCU ke Modul Display 7219
   D7 -- DIN
   D5 -- CLK
   D6 -- CS */
DigitLedDisplay ld = DigitLedDisplay(7, 5, 6);

// Alamat website (URL) Youtube API
String url = (String) "https://www.googleapis.com/youtube/v3/channels?part=statistics&id=" + 
                      CHANNEL_ID + 
                      "&fields=items/statistics/subscriberCount&key=" + 
                      API_KEY;

//===============================
// SETUP
//===============================

void setup() {

    // Pengaturan LED display
    ld.setBright(15); 
    ld.setDigitLimit(8);

    // Pengaturan serial
    OUTPUT.begin(115200);
    OUTPUT.setDebugOutput(false);

    // Tunggu NodeMCU untuk start
    for(uint8_t t = 4; t > 0; t--) {
        OUTPUT.printf("[SETUP] WAIT %d...\n", t);
        OUTPUT.flush();
        delay(1000);
    }

    // Mulai koneksi ke WIFI hotspot
    WiFi.mode(WIFI_STA);
    WiFiMulti.addAP(WIFI_NAME, WIFI_PASS);

}

//===============================
// LOOP
//===============================

void loop() {

    // Tunggu sampai statusnya sudah terhubung
    if ( (WiFiMulti.run() == WL_CONNECTED) ) {

        OUTPUT.print("[HTTP] Memulai...\n");
         
        // Set URL
        http.begin( url ); 
        
        OUTPUT.print("[HTTP] Melakukan GET ke server...\n");

        // Mulai koneksi
        int httpCode = http.GET();

        // httpCode akan bernilai negatif kalau error
        if(httpCode > 0) {
            
            // Tampilkan response http
            OUTPUT.printf("[HTTP] Kode response GET: %d\n", httpCode);

            // Bila koneksi berhasil, baca data response dari server
            if(httpCode == HTTP_CODE_OK) {

                // Baca data dari website (format JSON)
                String payload = http.getString();
                OUTPUT.println(payload);

                // Proses data JSON dari website Youtube API
                StaticJsonBuffer<300> jsonBuffer;
                JsonObject& root = jsonBuffer.parseObject(payload);
                unsigned int subs = root["time"];

                // Bersihkan dan tampilkan jumlah subscriber di display
                ld.clear();
                ld.printDigit(subs);
            }

        } else {
            
            // Tampilkan huruf "Err", sebagai pemberitahuan "Error"
            ld.clear();
            ld.write(1, B01001111); // huruf 'E'
            ld.write(2, B00000101); // huruf 'r'
            ld.write(3, B00000101); // huruf 'r'
            
            OUTPUT.printf("[HTTP] GET gagal, error: %s\n", http.errorToString(httpCode).c_str());
        }

        // Akhir membuka website
        http.end();
    }

    // Tunda sekian detik
    delay(INTERVAL * 1000);
}
