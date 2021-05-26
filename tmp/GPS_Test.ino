#include "Nanogrid_GPS.h"
#include "Constants.h"
#include "PID.h"
Nanogrid_GPS gps(Serial);

void setup(){
    Serial.begin(115200);
    Serial.println("Begin Program");
    delay(1000);
    gps.setup();

}

void loop(){
    gps.update();

    // Serial.print("[GPS] Lat: "); Serial.println(gps.getLat());
    // Serial.print("[GPS] Min: "); Serial.println(gps.getMin());
    // Serial.print("[GPS] Day: "); Serial.println(gps.getDay());
}
