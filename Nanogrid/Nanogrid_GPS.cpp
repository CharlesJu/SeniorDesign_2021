#include "Nanogrid_GPS.h"
#include "Constants.h"


extern const uint16_t MONTH_TO_DAY_ARR [] = {0,31,59,90,120,151,181,212,243,273,304,334};

Nanogrid_GPS::Nanogrid_GPS(Print &print) : serial(SoftwareSerial(GPS_TX, GPS_RX)), GPS(Adafruit_GPS(&serial)){

    printer = &print;
    

    gpsData.data.status = NO_FIX;
    gpsData.data.lat = 0;
    gpsData.data.min = 0;
    gpsData.data.day = 0;

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
    printer->println(GPS.fix);
    // if (GPS.fix == 1){
    //     if(GPSSTAT)
    //         printer->print("[GPS] () fixed");
    //     gpsData.data.status = HAS_FIX;
    //     gpsData.data.lat = (GPS.latitude_fixed / 78125) << 8; // fixed_lat * 2^15 / 10^7

    //     setTime(GPS.hour, GPS.minute, GPS.seconds, GPS.day, GPS.month, GPS.year); // Sync time with GPS
    //     adjustTime(HOUR_OFFSET * SECS_PER_HOUR); // Adjust for timezone
        
    //     gpsData.data.min = (hour()-12) * 60 + minute(); // -720 to +720, 0 being noon
        
    //     gpsData.data.day = MONTH_TO_DAY_ARR[GPS.month-1] + GPS.day; // Assume no leap years
        
    // } else {
    //     if(GPSSTAT)
    //         printer->println("[GPS] update() no Fix");
    //     gpsData.data.status = NO_FIX;
    // }
}

uint8_t Nanogrid_GPS::getStatus(){
    return gpsData.data.status;
}

void Nanogrid_GPS::waitForFix(){
    while(getStatus() == NO_FIX){
        if(GPSSTAT)
            printer->println("[GPS] waiting for fix");
        update();
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
