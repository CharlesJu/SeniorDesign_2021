#include "Nanogrid_GPS.h"
#include "Constants.h"
Nanogrid_GPS gps;

void setup(){
    Serial.begin(115200);
    delay(1000);

    gps.waitForFix();
}

void loop(){
    gps.update();

    Serial.print("[GPS] Lat: "); Serial.println(gps.getLat());
    Serial.print("[GPS] Min: "); Serial.println(gps.getMin());
    Serial.print("[GPS] Day: "); Serial.println(gps.getDay());
}
