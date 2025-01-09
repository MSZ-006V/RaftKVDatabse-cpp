#include"util.h"

void DebugPrint(const char* format, ...){
    if(DebugPrint){
        time_t now = time(nullptr);
        tm *nowtm = localtime(&now);
        va_list args;
        va_start(args, format);
        std::printf("[%d-%d-%d-%d-%d-%d] ", nowtm->tm_year + 1900, nowtm->tm_mon + 1, nowtm->tm_mday, nowtm->tm_hour,
                    nowtm->tm_min, nowtm->tm_sec);
        std::vprintf(format, args);
        std::printf("\n");
        va_end(args);
    }
}