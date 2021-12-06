#ifndef _ZCMD_TOOL_H
#define _ZCMD_TOOL_H
/*Used to transform the requested structure to json string*/
void zcmdStructToJString(void *, char **, zcfg_offset_t, void *);
/*Used to parse json string and fill up the requested structure*/
zcfgRet_t zcmdJStringToStruct(void **, const char *, zcfg_offset_t, void *);
#endif
