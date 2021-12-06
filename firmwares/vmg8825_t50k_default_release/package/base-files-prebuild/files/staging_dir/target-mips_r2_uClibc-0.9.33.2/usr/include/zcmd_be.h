#include "zcfg_eid.h"

typedef struct zcmdBeConfigRegData_s {
	zcfg_offset_t rdmObjId;
	int (*beConfigLoad)(void *, void *, objIndex_t *, zcfgEid_t);
	int (*beStatsUpdate)(void *, objIndex_t *);
	int (*beValidate)(void *, zcfgEid_t, char *);
} zcmdBeConfigRegData_t;

int zcmdBeDataModelMode();
void zcmdBeRegConfigObj(const zcmdBeConfigRegData_t *);
void zcmdBeAcsSpvNotifyRequired(bool);
void zcmdBeforceNotifyRequired(bool notifyRequried);
