#include "./getTime.h"

void configTimeJst() {
    const int JST = 3600 * 9;
    const char* ntpServer1 = "ntp.nict.jp";
    const char* ntpServer2 = "time.google.com";
    const char* ntpServer3 = "ntp.jst.mfeed.ad.jp";
    configTime(JST, 0, ntpServer1, ntpServer2, ntpServer3);
}

const String getTime() {
    const time_t t = time(NULL);
    const struct tm* tm = localtime(&t);
    String timeStr;
    timeStr += tm->tm_hour < 10 ? "0" + (String)tm->tm_hour : tm->tm_hour ;
    timeStr += ':';
    timeStr += tm->tm_min < 10 ? "0" + (String)tm->tm_min : tm->tm_min ;
    timeStr += ':';
    timeStr += tm->tm_sec < 10 ? "0" + (String)tm->tm_sec : tm->tm_sec ;
    return timeStr;
}
