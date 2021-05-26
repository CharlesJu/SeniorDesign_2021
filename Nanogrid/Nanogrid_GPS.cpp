#include "Nanogrid_GPS.h"
#include "Constants.h"


extern const uint16_t MONTH_TO_DAY_ARR [] = {0,31,59,90,120,151,181,212,243,273,304,334};

Nanogrid_GPS::Nanogrid_GPS(Print &print) : serial(SoftwareSerial(GPS_TX, GPS_RX)), GPS(Adafruit_GPS(&serial)){

    printer = &print;
    

    gpsData.data.status = NO_FIX;
    gpsData.data.lat = 0;
    gpsData.data.lon = 0;
    gpsData.data.time = 0;

};

void Nanogrid_GPS::setup(){
    GPS.begin(9600);

    delay(1000);
    printer->println("[GPS] Enabling...");
    
    GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
    GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); 
    GPS.sendCommand(PGCMD_ANTENNA);

    delay(2500);
    serial.println(PMTK_Q_RELEASE);
    printer->println("[GPS] Enabled");
}

void Nanogrid_GPS::update(){
    char c = GPS.read();

    if ((c) && (GPSECHO))
        printer->print(c);

    if (GPS.newNMEAreceived()) {
        if (!GPS.parse(GPS.lastNMEA()))   // sets newNMEAreceived() flag to false
            return;  // we can fail to parse a sentence in which case we should just wait for another
    }
    // if(GPSDEBUG){
    //     printer->println(digitalRead(GPS_FIX));
    // }
    
    if(GPS.fix){
        gpsData.data.status = HAS_FIX;
    } else {
        gpsData.data.status = NO_FIX;
    }

}

void Nanogrid_GPS::pollData(){
    if (gpsData.data.status == HAS_FIX){
        if(GPSSTAT)
            printer->println("[GPS] polling -- fixed");

        
        gpsData.data.status = HAS_FIX;
        gpsData.data.lat = GPS.latitude/100.0;
        gpsData.data.lon = GPS.longitude/100.0;
        setTime(GPS.hour, GPS.minute, GPS.seconds, GPS.day, GPS.month, GPS.year); // Sync time with GPS
        adjustTime(HOUR_OFFSET * SECS_PER_HOUR); // Adjust for timezone
        
        gpsData.data.time = now();

        if(GPSDEBUG){
            printer->print("[GPS] Time: "); printer->println(gpsData.data.time);
            printer->print("[GPS] Lat: "); printer->println(gpsData.data.lat);
            printer->print("[GPS] Lon: "); printer->println(gpsData.data.lon);
        }
        
    } else {
        if(GPSSTAT)
            printer->println("[GPS] polling -- no Fix");
    }
}

uint8_t Nanogrid_GPS::getStatus(){
    return gpsData.data.status;
}

void Nanogrid_GPS::waitForFix(){
    while(gpsData.data.status == NO_FIX){
        if(GPSSTAT)
            printer->println("[GPS] waiting for fix");
        update();
    }
}

float Nanogrid_GPS::getLat(){
    return gpsData.data.lat;
}

float Nanogrid_GPS::getLon(){
    return gpsData.data.lon;
}

time_t Nanogrid_GPS::getTime(){
    return gpsData.data.time;
}

// int16_t Nanogrid_GPS::getMin(){
//     return gpsData.data.min;
// }

// uint16_t Nanogrid_GPS::getDay(){
//     return gpsData.data.day;
// }
