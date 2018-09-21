#ifndef __MSG_LOG_H__
#define __MSG_LOG_H__
void ESLOG_ERR(const char *szFormat, ...);
void ESLOG_INFO(const char *szFormat, ...);
void ESLOG_BIN(const char * name,char * data,unsigned int len);
#endif
