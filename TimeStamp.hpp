#ifndef TIMESTAMP_H
#define TIMESTAMP_H
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <string>

using namespace std;

/**
 * Class defining a TimeStamp's fields (date, time, offset)
 *  as well as basic manipulation functions
 */
class TimeStamp {
    private:
        int day;
        int month;
        int year;

        int hour;
        int minutes;
        int seconds;

        int offset;

        long int epoch_time;
        struct tm* ptm;

    public:
        TimeStamp(){};
        TimeStamp(time_t epoch_time){
            this->epoch_time = epoch_time;
            this->ptm = gmtime ((time_t *)&epoch_time);

            this->day = ptm->tm_mday;
            this->month = ptm->tm_mon+1;
            this->year = ptm->tm_year+1900;

            // get hours, minutes, seconds
            this->hour = ptm->tm_hour;
            this->minutes = ptm->tm_min;
            this->seconds = ptm->tm_sec;

            this->offset = 0;
        }

        TimeStamp(int day, int month, int year, int hour, int minutes, int seconds, int offset);

        // get "mm/dd/yyThh:mm:ss+offset"
        string to_string(){
            return std::to_string(this->month) + "/" + std::to_string(this->day) + "/" + std::to_string(this->year) + "T" + 
                std::to_string(this->hour) + ":" + std::to_string(this->minutes) + ":" + std::to_string(this->seconds) + "+" + 
                std::to_string(this->offset);
        } 

        long int get_epoch(){return this->epoch_time;}

        friend bool operator< (const TimeStamp& l, const TimeStamp& r) {
            if(l.epoch_time < r.epoch_time){
                return true;
            }else{
                return false;
            }
        }


};


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
        std::string get_date_time(std::string date, 
                std::string time, 
                std::string offset);  // build from strings

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

        std::string get_timestamp(void){return this->timestamp;}

        int get_day();
        int get_month();
        int get_year();

        int get_hours();
        int get_minutes();
        int get_seconds();
        
        int get_offset();
};

#endif
