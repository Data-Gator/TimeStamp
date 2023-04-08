#include "TimeStamp.hpp"


TimeStampBuilder::TimeStampBuilder(NTPClient* ntp_client){
    this->ntp_client = ntp_client;
}

std::string TimeStampBuilder::get_date_time(){

    //if(this->ntp_client == NULL){return "00-00-00T00:00:00+0";}
    //return "00-00-00T00:00:00+0";

    //this->ntp_client.update();
    try{
    time_t epochTime = this->ntp_client->getEpochTime();

    // get day, month, year
    struct tm* ptm = gmtime ((time_t *)&epochTime);
    int month_day = ptm->tm_mday;
    int current_month = ptm->tm_mon+1;
    int current_year = ptm->tm_year+1900;

    // get hours, minutes, seconds
    int hours = ptm->tm_hour;
    int minutes = ptm->tm_min;
    int seconds = ptm->tm_sec;

    int offset = 0;

    return std::to_string(current_month) + "-" + 
        std::to_string(month_day) + "-" + 
        std::to_string(current_year) +
        "T" + 
        std::to_string(hours) + ":" + 
        std::to_string(minutes) + ":" + 
        std::to_string(seconds) + 
        "+" + 
        std::to_string(offset);


    }catch(...){
        Serial.println("ERROR WITH NTP UPDATE!!!");
    }

    return "00-00-00T00:00:00+0";

}

std::string TimeStampBuilder::get_date_time(std::string date, std::string time, std::string offset){
    return date + "T" + time + "+" + offset;
}

std::string TimeStampBuilder::format_time(int hours, int minutes, int seconds){
    return std::to_string(hours) + ":" + 
        std::to_string(minutes) + ":" + 
        std::to_string(seconds);
}

std::string TimeStampBuilder::format_date(unsigned long epoch_time){

    time_t epochTime = epoch_time;

    // get day, month, year
    struct tm* ptm = gmtime ((time_t *)&epochTime);
    int month_day = ptm->tm_mday;
    int current_month = ptm->tm_mon+1;
    int current_year = ptm->tm_year+1900;

    // get hours, minutes, seconds
    int hours = ptm->tm_hour;
    int minutes = ptm->tm_min;
    int seconds = ptm->tm_sec;

    int offset = 0;

    return std::to_string(current_month) + "-" + 
        std::to_string(month_day) + "-" + 
        std::to_string(current_year);
}


TimeStampParser::TimeStampParser(std::string timestamp){
    this->timestamp = timestamp;
}

int TimeStampParser::get_day(){
    int start = this->timestamp.find_first_of('-') + 1;
    int end = this->timestamp.find('-', start+1);

    std::string substr = this->timestamp.substr(start, end - start);

    return std::stoi(substr);
}
int TimeStampParser::get_month(){
    int len = this->timestamp.find('-');

    return std::stoi(this->timestamp.substr(0, len));
}

int TimeStampParser::get_year(){
    int start = this->timestamp.find_last_of('-') + 1;
    int len = this->timestamp.find('T') - start;

    return std::stoi(this->timestamp.substr(start, len));
}

int TimeStampParser::get_hours(){
    int start = this->timestamp.find('T') + 1;
    int len = this->timestamp.find_first_of(':') - start;

    return std::stoi(this->timestamp.substr(start, len));
}

int TimeStampParser::get_minutes(){
    int start = this->timestamp.find(':') + 1;
    int len = this->timestamp.find_last_of(':') - start;
    
    return std::stoi(this->timestamp.substr(start, len));
}

int TimeStampParser::get_seconds(){
    int start = this->timestamp.find_last_of(':') + 1;
    int len = this->timestamp.find('+') - start;

    return std::stoi(this->timestamp.substr(start, len));
}

int TimeStampParser::get_offset(){
    int start = this->timestamp.find('+') + 1;

    return std::stoi(this->timestamp.substr(start, std::string::npos));
}

