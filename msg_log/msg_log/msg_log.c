#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/time.h>
#define LOG_ERR 0
#define LOG_INFO 1

void LogString(int type, const char *szFormat, ...)
{
#ifdef DEBUG_LOG
    switch(type)
    {
        case LOG_ERR:
            printf("\033[31m%s\033[0m", szFormat);
            break;
        case LOG_INFO:
            printf("%s", szFormat);
            break;
        default:
            break;
    }
#endif
}
void ESLOG_ERR(const char *szFormat, ...)
{
    char pDate[512] = {0};
#ifdef TIME_LOG
    struct timeval start;
    gettimeofday(&start, NULL);
    sprintf(pDate, "time->%ld:%ld [%d-%ld] %s(%d) ERR:", start.tv_sec, start.tv_usec, getpid(), pthread_self(), __FILE__, __LINE__);
#else //NOT TIME_LOG
    sprintf(pDate, "[%d-%ld] %s(%d) ERR:", getpid(), pthread_self(), __FILE__, __LINE__);
#endif
    char *szBufTemp = pDate + strlen(pDate);

    va_list valist;
    va_start(valist, szFormat);
    vsnprintf(szBufTemp, 512 - strlen(pDate), szFormat, valist);
    va_end(valist);

    LogString(LOG_ERR, pDate);
}
void ESLOG_INFO(const char *szFormat, ...)
{
    char pDate[512] = {0};
#ifdef TIME_LOG
    struct timeval start;
    gettimeofday(&start,NULL);
    sprintf(pDate, "time->%ld:%ld [%d-%ld] INFO:", start.tv_sec, start.tv_usec, getpid(), pthread_self());
#else //NOT TIME_LOG
    sprintf(pDate, "[%d-%ld] INFO:", getpid(), pthread_self());
#endif

    char *szBufTemp = pDate + strlen(pDate);

    va_list valist;
    va_start(valist, szFormat);
    vsnprintf(szBufTemp, 512 - strlen(pDate), szFormat, valist);
    va_end(valist);

    LogString(LOG_INFO, pDate);
}
void ESLOG_BIN(const char * name,char * data,unsigned int len)
{
#ifdef DEBUG_LOG
    int i = 0;
    char *tmpData = data;
    printf("%s",name);
    for (i = 0; i<len; i++) {
        if(0 == i%16)
            printf("\n%02x ",data[i]);
        else
            printf("\033[%dC%02x ",3*(i%16),data[i]);

        printf("\033[%dC%c\033[u",60-(1*(i%16)),data[i]);
    }

    printf("\n");
#endif
}
