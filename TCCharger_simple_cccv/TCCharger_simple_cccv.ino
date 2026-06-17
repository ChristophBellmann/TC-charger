// TC Charger - einfache CC/CV-Steuerung fuer Arduino Leonardo CAN-BUS Board
// Basis: Code von Lennart O. / adaptiert.
//
// CC/CV macht das Ladegeraet selbst:
//   - Wir senden Sollspannung 116,2 V und Maxstrom 32 A.
//   - Das Geraet faehrt erst Konstantstrom (CC) mit 32 A, bis 116,2 V erreicht sind.
//   - Dann haelt es 116,2 V (CV), der Strom faellt frei ab.
//
// Es wird jede Sekunde der Sollwert gesendet (Watchdog des Ladegeraets) und
// die gemessene Spannung/Strom ueber USB (Serial, 115200 Baud) ausgegeben.
//
// CAN: Sende-ID 0x1806E5F4, Empfangs-ID 0x18FF50E5 (Protokoll 1430)

#include <SPI.h>
#include <mcp_can.h>

// CS-Pin des MCP2515. Das Leonardo-CAN-BUS-Board (CANBed) nutzt Pin 17.
// Bei separatem CAN-Shield ggf. auf 10 aendern.
#define SPI_CS_PIN 17

// Sollwerte (Offset 0,1  ->  Wert = Volt*10 bzw. Ampere*10)
word outputvoltage = 1162;  // 116,2 V  -> CV-Zielspannung
word outputcurrent = 320;   // 32,0 A   -> CC-Maximalstrom

const unsigned long sendId    = 0x1806E5F4; // Befehl an Ladegeraet
const unsigned long chargerId = 0x18FF50E5; // Status vom Ladegeraet

MCP_CAN CAN(SPI_CS_PIN);

unsigned char len = 0;
unsigned char buf[8];
unsigned long lastSend = 0;

void sendSetpoint() {
  unsigned char voltamp[8] = {
    highByte(outputvoltage), lowByte(outputvoltage),
    highByte(outputcurrent), lowByte(outputcurrent),
    0x00, 0x00, 0x00, 0x00
  };
  CAN.sendMsgBuf(sendId, 1, 8, voltamp); // (ID, extended frame=1, Laenge=8, Daten)
}

void readCharger() {
  while (CAN_MSGAVAIL == CAN.checkReceive()) {
    CAN.readMsgBuf(&len, buf);
    if (CAN.getCanId() == chargerId) {
      float v = (((float)buf[0] * 256.0) + (float)buf[1]) / 10.0;
      float i = (((float)buf[2] * 256.0) + (float)buf[3]) / 10.0;
      Serial.print("U = ");
      Serial.print(v, 1);
      Serial.print(" V    I = ");
      Serial.print(i, 1);
      Serial.print(" A");
      byte err = buf[4];
      if (err) {
        Serial.print("    Fehler:");
        if (err & 0x01) Serial.print(" Hardware");
        if (err & 0x02) Serial.print(" Uebertemperatur");
        if (err & 0x04) Serial.print(" Eingangsspannung-unzulaessig");
        if (err & 0x08) Serial.print(" Batterie-nicht-verbunden");
        if (err & 0x10) Serial.print(" CAN-Fehler");
      }
      Serial.println();
    }
  }
}

void setup() {
  Serial.begin(115200);
  while (CAN_OK != CAN.begin(CAN_250KBPS)) {
    Serial.println("CAN Init fehlgeschlagen, neuer Versuch...");
    delay(200);
  }
  Serial.println("CAN Init OK");
  Serial.println("Soll: U = 116.2 V (CV)   I = 32.0 A (CC)");
}

void loop() {
  readCharger(); // laufend empfangen -> immer aktuelle Messwerte

  if (millis() - lastSend >= 1000) {
    lastSend = millis();
    sendSetpoint(); // jede Sekunde Sollwert senden (haelt Ladegeraet aktiv)
  }
}
