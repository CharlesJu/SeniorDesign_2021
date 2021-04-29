#include "Nanogrid_GPS.h"
#include "Constants.h"


extern const uint16_t MONTH_TO_DAY_ARR [] = {0,31,59,90,120,151,181,212,243,273,304,334};

Nanogrid_GPS::Nanogrid_GPS() : serial(SoftwareSerial(GPS_A, GPS_B)), GPS(Adafruit_GPS(&serial)){
    GPS.begin(9600);
    Serial.println("Adafruit GPS Enabling...");
    
    GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
    GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); 
    GPS.sendCommand(PGCMD_ANTENNA);

    delay(2500);

    gpsData.data.status = NO_FIX;
    gpsData.data.lat = 0;
    gpsData.data.min = 0;
    gpsData.data.day = 0;

    serial.println(PMTK_Q_RELEASE);
};

void Nanogrid_GPS::update(){
    char c = GPS.read();
    if ((c) && (GPSECHO))
        Serial.write(c);
    
    if (GPS.newNMEAreceived()) {
        if (!GPS.parse(GPS.lastNMEA()))   // sets newNMEAreceived() flag to false
            return;  // we can fail to parse a sentence in which case we should just wait for another
    }

    if (GPS.fix){
        gpsData.data.status = HAS_FIX;
        gpsData.data.lat = (GPS.latitude_fixed / 78125) << 8; // fixed_lat * 2^15 / 10^7

        setTime(GPS.hour, GPS.minute, GPS.seconds, GPS.day, GPS.month, GPS.year); // Sync time with GPS
        adjustTime(HOUR_OFFSET * SECS_PER_HOUR); // Adjust for timezone
        
        gpsData.data.min = (hour()-12) * 60 + minute(); // -720 to +720, 0 being noon
        
        gpsData.data.day = MONTH_TO_DAY_ARR[GPS.month-1] + GPS.day; // Assume no leap years
        
    } else {
        gpsData.data.status = NO_FIX;
    }
}

uint8_t Nanogrid_GPS::getStatus(){
    return gpsData.byteAccess[0];
}

void Nanogrid_GPS::waitForFix(){
    while(getStatus() == NO_FIX){
        update();
        delay(1000);
    }
}

int16_t Nanogrid_GPS::getLat(){
    return gpsData.data.lat;
}

int16_t Nanogrid_GPS::getMin(){
    return gpsData.data.min;
}

uint16_t Nanogrid_GPS::getDay(){
    return gpsData.data.day;
}