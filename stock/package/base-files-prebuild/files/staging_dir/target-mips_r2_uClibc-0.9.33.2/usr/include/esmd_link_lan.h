

enum{
	ESMD_WPS_STS_ERR = -1,
	ESMD_WPS_STS_INIT,
	ESMD_WPS_STS_ASSOCIATED,
	ESMD_WPS_STS_OK,
	ESMD_WPS_STS_MSG_ERR,
	ESMD_WPS_STS_TIMEOUT,
	ESMD_WPS_STS_SENDM2,
	ESMD_WPS_STS_SENDM7,
	ESMD_WPS_STS_MSGDONE,
	ESMD_WPS_STS_PBCOVERLAP,
	ESMD_WPS_STS_FIND_PBC_AP,
	ESMD_WPS_STS_ASSOCIATING
};

enum{
	WPSCFGRD_STS_EMPTY = 0,
	WPSCFGRD_STS_WPSRUNNING
};

void esmdLanConnectionUp(objIndex_t *);
void esmdLanMacFilterSet(objIndex_t *);
bool isBindingBridgeWan(char *ethIntfPath);
#ifdef ISKON_CUSTOMIZATION_Motorola_VIP1003
extern int removeIfaceGroup(char *portName, bool confirmed);
#else
int removeIfaceGroup(char *portName);
#endif

int wpsMsgStatusHandle(uint32_t , char *, int);
