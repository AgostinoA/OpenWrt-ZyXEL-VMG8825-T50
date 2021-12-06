#ifndef _ZCFG_NET_H
#define _ZCFG_NET_H

#define BR_NAME_PREFIX "br"

#ifdef USE_UDHCPD
#define UDHCPD_CONF_FILE "/var/udhcpd/udhcpd.conf"
#define UDHCPD_EXEC_FILE "/usr/sbin/udhcpd /var/udhcpd/udhcpd.conf"
//#define UDHCPD_EXEC_FILE "/bin/udhcpd &"
#else
#if 1
#define DNSMASQ_PATH "/var/dnsmasq"
#define DNSMASQ_CONF_D DNSMASQ_PATH"/conf.d"
#define DNSMASQ_DHCP_LEASE_FILE DNSMASQ_PATH"/dnsmasq.leases"
#define DNSMASQ_HOSTS DNSMASQ_PATH"/hosts"
#define DNSMASQ_DHCP_CONF_FILE DNSMASQ_CONF_D"/lan_dhcp.conf"
#define DNSMASQ_DNS_CONF_FILE DNSMASQ_CONF_D"/dns.conf"
#define DNSMASQ_DNS_TRUST_ANCHOR_CONF_FILE DNSMASQ_CONF_D"/trust-anchors.conf"
#define DNSMASQ_DHCP_SUBNET_CONF_FILE DNSMASQ_CONF_D"/subnet_dhcp.conf"
#define DNSMASQ_DNSROUTE_CONF_FILE DNSMASQ_CONF_D"/dnsroute.conf"
#define DNSMASQ_DEFAULT_DNSROUTE_CONF_FILE DNSMASQ_CONF_D"/dnsroute_default.conf"
#define DNSMASQ_DNSROUTE_TMP_CONF_FILE DNSMASQ_DNSROUTE_CONF_FILE"~"
#define DNSMASQ_RESTART_CMD "/etc/init.d/dnsmasq.sh restart"
#define DNSMASQ_START_CMD "/etc/init.d/dnsmasq.sh start"
#define DNSMASQ_STOP_CMD "/etc/init.d/dnsmasq.sh stop"
#else
#define DNSMASQ_CONF_FILE "/var/dnsmasq.conf"
#define DNSMASQ_CONF_TMP_FILE DNSMASQ_CONF_FILE".tmp"
#define DNSMASQ_EXEC_FILE "dnsmasq -u root -q --conf-file="DNSMASQ_CONF_FILE
#endif
#define ETHERS_FILE "/var/ethers"
#define ETHERS_TMP_FILE ETHERS_FILE".tmp"
#endif

#define DHCP6S_CONF_FILE "/var/dhcp6s.conf"
#define DHCP6S_EXEC_FILE "dhcp6s -c "DHCP6S_CONF_FILE" br0 &"

#define DROPBEAR_AUTH_KEY_DIR "/var/"
#define DROPBEAR_AUTH_KEY_PATH DROPBEAR_AUTH_KEY_DIR"authorized_keys"

#define MAX_URL_LEN 256

#define DDNS_EXEC_FILE "/usr/sbin/ez-ipupdate"

#define TYPE_ATM 1
#define TYPE_PTM 2

#define ITU_STD_G_992_3_Annex_K_ATM "G.992.3_Annex_K_ATM"
#define ITU_STD_G_992_3_Annex_K_PTM "G.992.3_Annex_K_PTM"
#define DSL_LINK_DESTINATION_PREFIX_PVC "PVC:"

#define IFC_WAN_MAX	16

#define VLAN_MUX_MODE	"VlanMuxMode"
#define DEFAULT_MODE	"DefaultMode"

#define ETH_IFC_STR	"eth"
#define USB_IFC_STR	"usb"
#define WLAN_IFC_STR	"wl"
#define MOCA_IFC_STR	"moca"
#define GPON_IFC_STR	"veip"
#define EPON_IFC_STR	"epon"
#define ATM_IFC_STR	"atm"
#define PTM_IFC_STR  	"ptm"
#define BRIDGE_IFC_STR	"br"
#define IPOA_IFC_STR	"ipoa"
#define IPOE_IFC_STR	"ipoe"
#define PPP_IFC_STR	"ppp"
#define PPPOE_IFC_STR	"pppoe"
#define PPPOA_IFC_STR	"pppoa"
#define IPA_IFC_STR	"ipa"
#define BRIDGE_SMUX_STR	"bridge"
#define NAS_IFC_STR     "nas"

#define IP_ROUTED	"IP_Routed"
#define IP_BRIDGED	"IP_Bridged"

#define TR98_ON		"On"
#define TR98_OFF	"Off"

/*Power Management State*/
#define TR98_L0         "L0"
#define TR98_L1         "L1"
#define TR98_L2         "L2"
#define TR98_L3         "L3"
#define TR98_L4         "L4"

/*TR98 Connection Types*/
#define TR98_IP_ROUTED	"IP_Routed"
#define TR98_IP_BRIDGED	"IP_Bridged"

/*TR98 Link Status*/
#define TR98_UP		"Up"
#define TR98_DOWN	"Down"
#define TR98_NOLINK	"NoLink"
#define TR98_DISABLED	"Disabled"
#define TR98_NOSIGNAL	"NoSignal"
#define TR98_INITIALIZING "Initializing"
#define TR98_ESTABLISHINGLINK "EstablishingLink"

/*TR181 Link Status*/
#define TR181_UP                "Up"
#define TR181_DOWN              "Down"
#define TR181_NOLINK            "NoLink"
#define TR181_DISABLED          "Disabled"
#define TR181_NOSIGNAL          "NoSignal"
#define TR181_INITIALIZING      "Initializing"
#define TR181_ESTABLISHINGLINK  "EstablishingLink"
#define TR181_UNKNOWN			"Unknown"
#define TR181_DORMANT			"Dormant"
#define TR181_NOTPRESENT		"NotPresent"
#define TR181_LOWERLAYERDOWN	"LowerLayerDown"
#define TR181_ERROR				"Error"

typedef enum{
	TR181_ST_NONE=0,
	TR181_ST_UP=1,
	TR181_ST_DOWN,
	TR181_ST_NOLINK,
	TR181_ST_DISABLED,
	TR181_ST_NOSIGNAL,
	TR181_ST_INITIALIZING,
	TR181_ST_ESTABLISHINGLINK,
	TR181_ST_UNKNOWN,
	TR181_ST_DORMANT,
	TR181_ST_NOTPRESENT,
	TR181_ST_LOWERLAYERDOWN,
	TR181_ST_ERROR,
	TR181_ST_MAX
}TR181_ST;


/*TR181 Status*/
#define TR181_ENABLED           "Enabled"
#define TR181_LOWER_LAYER_DOWN  "LowerLayerDown"


/*TR98 Modulation Type*/
#define TR98_ADSL_G_DMT         "ADSL_G.dmt"
#define TR98_ADSL_ANSI_T1_413   "ADSL_ANSI_T1.413"
#define TR98_ADSL_G_LITE        "ADSL_G.lite"
#define TR98_ADSL_G_DMT_BIS     "ADSL_G.dmt.bis"
#define TR98_ADSL_2PLUS         "ADSL_2plus"
#define TR98_ADSL_RE_ADSL       "ADSL_re-adsl"
#define TR98_VDSL2              "VDSL2"
#define TR98_G_FAST             "ADSL_G.FAST"

/* Line Encoding */
#define TR98_DMT		"DMT"
#define TR98_CAP		"CAP"
#define TR98_QAM		"QAM"

/*TR98 Connection Status*/
#define TR98_UNCONFIGURED	"Unconfigured"
#define TR98_CONNECTING		"Connecting"
#define TR98_CONNECTED		"Connected"
#define TR98_DISCONNECTED	"Disconnected"

/*TR181 PPP Connection Status*/
#define TR181_PPP_UNCONFIGURED       "Unconfigured"
#define TR181_PPP_CONNECTING         "Connecting"
#define TR181_PPP_CONNECTED          "Connected"
#define TR181_PPP_DISCONNECTED       "Disconnected"

/*TR98 Link Types*/
#define TR98_EOA	"EoA"
#define TR98_IPOA	"IPoA"
#define TR98_PPPOA	"PPPoA"
#define TR98_PPPOE	"PPPoE"
#define TR98_CIP	"CIP"

/*TR181 Link Types*/
#define TR181_EOA        "EoA"
#define TR181_IPOA       "IPoA"
#define TR181_PPPOA      "PPPoA"
#define TR181_PPPOE      "PPPoE"
#define TR181_CIP        "CIP"

#define TR181_LLC        "LLC"
#define TR181_VCMUX      "VCMUX"

/*TR181 ATM QoS*/
/*ATM QoS*/
#define TR181_UBR         "UBR"
#define TR181_CBR         "CBR"
#define TR181_VBR_NRT     "VBR-nrt"
#define TR181_VBR_RT      "VBR-rt"

/*TR181 IP Interface Type*/
#define TR181_IPINTF_NORMAL   "Normal"
#define TR181_IPINTF_LOOPBACK "Loopback"
#define TR181_IPINTF_TUNNEL   "Tunnel"
#define TR181_IPINTF_TUNNELED "Tunneled"

/*TR181 Addressing Type*/
#define TR181_STATIC     "Static"
#define TR181_DHCP       "DHCP"
#define TR181_IPCP       "IPCP"

/*IPv6 Address Type*/
#define TR181_V6_ADDR_STATIC  "Static"
#define TR181_V6_ADDR_AUTO    "AutoConfigured" //Automatically generated
#define TR181_V6_ADDR_DHCPV6  "DHCPv6"

/*IPv6 Prefix Type*/
#define TR181_PREFIX_AUTO   "AutoConfigured"   //Generated via internal CPE logic
#define TR181_PREFIX_PD     "PrefixDelegation"
#define TR181_PREFIX_RA     "RouterAdvertisement"
#define TR181_PREFIX_STATIC "Static"
#define TR181_PREFIX_CHILD  "Child"

/*IPv6 FWD Type*/
#define TR181_FWD_STATIC     "Static"
#define TR181_FWD_DHCPV6     "DHCPv6"
#define TR181_FWD_RA         "RA"

/*IPv6 RouteInformation Status*/
#define TR181_RT_INFO_CREATE_FWD "ForwardingEntryCreated"
#define TR181_RT_INFO_NO_FWD     "NoForwardingEntry"

#define MAX_DEFAULT_GATEWAY 8
#define MAX_ACTIVE_DNS_IP   4
#define MAX_DNSIFNAME       8

#define IPADDR_LENGTH  46

/*TR181 DCHP Status*/
#define TR181_DHCP_INIT 	"Init"
#define TR181_DHCP_BOUND	"Bound"
#define TR181_DHCP_RENEW	"Renewing"
/*workaround*/
#define TR181_DHCP_Release	"Release"



/*TR181 DNS Type*/
#define TR181_DNS_TYPE_DHCPV4   "DHCPv4"
#define TR181_DNS_TYPE_DHCPV6   "DHCPv6"
#define TR181_DNS_TYPE_RA       "RouterAdvertisement"
#define TR181_DNS_TYPE_IPCP     "IPCP"
#define TR181_DNS_TYPE_STATIC   "Static"

/*TR181 DSL.BondingGroup Scheme*/
#define TR181_DSL_BOND_SCHEME_ATM "ATM"
#define TR181_DSL_BOND_SCHEME_ETH "Ethernet"
#define TR181_DSL_BOND_SCHEME_TDIM "TDIM"
#define TR181_DSL_BOND_GROUP_STATUS_NONE "None"
#define TR181_DSL_BOND_GROUP_STATUS_NOPEER "NoPeer"
#define TR181_DSL_BOND_GROUP_STATUS_MISMATCH "PeerBondSchemeMismatch"
#define TR181_DSL_BOND_GROUP_STATUS_LOWRATE "LowRate"


/*Diagnostics State*/
#define DIAG_NONE                      "None"
#define DIAG_REQUESTED                 "Requested"
#define DIAG_COMPLETE                  "Complete"
#define DIAG_CANNOT_RESOLVE_HOST_NAME  "Error_CannotResolveHostName"
#define DIAG_ERROR_INTERNAL            "Error_Internal"
#define DIAG_ERROR_OTHER               "Error_Other"
#define DIAG_MAX_HOP_EXCEED            "Error_MaxHopCountExceeded"
#define DIAG_SUCCESS					"Success"
#define DIAG_DNS_SERVER_NOT_RESOLVE		"Error_DNSServerNotResolved"
#define DIAG_DNS_SERVER_NOT_AVAILABLE	"Error_DNSServerNotAvailable"
#define DIAG_HOST_NAME_NOT_RESOLV		"Error_HostNameNotResolved"
#define DIAG_TIMEOUT					"Error_Timeout"
#define DIAG_ERROR_INITCONNECTIONFAILED "Error_InitConnectionFailed"

/*Config Creator*/
#define CREATOR_ACS		"ACS"
#define CREATOR_UI		"UserInterface"

#if 1 /* for ZyIMS*/
#define ZYIMS_ANY_WAN "Any_WAN"
#define ZYIMS_MULTI_WAN "Multi_WAN"
#endif

/*X_ZYXEL_Schedule Days*/
#define DAY_SUN (0x1 << 0)
#define DAY_MON (0x1 << 1)
#define DAY_TUE (0x1 << 2)
#define DAY_WED (0x1 << 3)
#define DAY_THU (0x1 << 4)
#define DAY_FRI (0x1 << 5)
#define DAY_SAT (0x1 << 6)
#define DAY_ALL DAY_SUN|DAY_MON|DAY_TUE|DAY_WED|DAY_THU|DAY_FRI|DAY_SAT

/*TrustDomain Mode*/
#define MODE_LAN_withoutWL			"LAN_withoutWL"
#define MODE_LAN_withoutWL_WAN		"LAN_withoutWL_WAN"
#define MODE_LAN_withoutWL_TstDm	"LAN_withoutWL_TstDm"
#define MODE_WL_WAN			"WL_WAN"
#define MODE_WL_Trust_Dm	"WL_Trust_Dm"
#define MODE_WL_ONLY		"WL_ONLY"
#define MODE_WAN_ONLY		"WAN_ONLY"
#define MODE_LAN_ONLY		"LAN_ONLY"
#define MODE_Trust_Dm		"Trust_Dm"
#define MODE_LAN_WAN		"LAN_WAN"
#define MODE_LAN_TstDm		"LAN_TstDm"
#define MODE_ALL			"ALL"

/*TR069 X_ZYXEL_RemoteIfName*/
#define ANY_WAN "Any_WAN"
#define MULTI_WAN "Multi_WAN"
/*X_ZYXEL_RemoteIfList*/
#define SUPPORT_MULTI_WAN "SUPPORT_MULTI_WAN"


/*DHCP option code*/
#define DHCP_NTP_SERVER_CODE	0x2a
#define DHCP_ACS_INFO_CODE      0x2b
#define DHCP_STATIC_ROUTE_CODE  0x79
#define NTP_SERVER_MAX_NUM      5
#define NTP_RETRY_COUNT         10
#define NTPCLIENT_FILE "/bin/ntpclient"
#define SNTP_RESULT_FILE "/tmp/sntp.dat" 

/* WAN MAC type */
#define WAN_MAC_DEFAULT		"Default"
#define WAN_MAC_USER		"UserDefine"
#define WAN_MAC_CLIENTIP	"ClientIP"

#endif
