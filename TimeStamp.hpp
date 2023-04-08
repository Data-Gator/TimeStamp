#ifndef TIMESTAMP_H
#define TIMESTAMP_H
#include <NTPClient.h>
#include <WiFiUdp.h>


/**
 * Class for building time stamps with the 
 *  format:
 *      <year>-<month>-<day>T<hours>:<minutes>:<seconds>+<minutes_offset>
 *
 *  Time stamps may be built from date and time formatted as integers
 *      or strings, or from data requested from an NTPClient.
 */
class TimeStampBuilder {
    
    private:
        
        NTPClient* ntp_client;

    public:

        TimeStampBuilder(NTPClient*);

        std::string get_date_time();                                                        // use NTPClient
        std::string get_date_time(std::string date, std::string time, std::string offset);  // build from strings

        std::string format_time(int hours, int minutes, int seconds);
        std::string format_date(unsigned long epoch_time);
};


/**
 * Class for parsing and modifying time stamps constructed
 *  according to the format used by TimeStampBuilder.
 *
 * Needed for extracting data for checking time ranges etc.
 */
class TimeStampParser {
    
    private:
       
        std::string timestamp;

    public:

        TimeStampParser(std::string timestamp);

        int get_day();
        int get_month();
        int get_year();

        int get_hours();
        int get_minutes();
        int get_seconds();
        
        int get_offset();

};

#endif
