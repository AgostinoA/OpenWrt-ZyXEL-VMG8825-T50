Guida sblocco by dariuccio83

E' bastato accedere alla GUI completa con l'account supervisor, andare su Backup/Ripristino e scaricare il file di configurazione che nel nostro caso sarà completo di tutte le impostazioni e di tutti gli account, compreso root, con le password criptate.

Basta editare il file con un editor compatibile con i file JSON e fare le seguenti modifiche:

1) Individuate questa sezione:
Codice:
"X_ZYXEL_RemoteManagement":{
    "SPRemoteTimer":20,
    "Service":[
      {
        "Name":"HTTP",
        "Enable":true,
        "Protocol":6,
        "Port":80,
        "Mode":"LAN_ONLY",
        "TrustAll":true
      },
      {
        "Name":"HTTPS",
        "Enable":true,
        "Protocol":6,
        "Port":443,
        "Mode":"LAN_ONLY",
        "TrustAll":true
      },
      {
        "Name":"FTP",
        "Enable":true,
        "Protocol":6,
        "Port":21,
        "Mode":"LAN_ONLY",
        "TrustAll":true
      },
      {
        "Name":"TELNET",
        "Enable":true,
        "Protocol":6,
        "Port":23,
        "Mode":"",
        "TrustAll":true
      },
      {
        "Name":"SSH",
        "Enable":true,
        "Protocol":6,
        "Port":22,
        "Mode":"",
        "TrustAll":true
      },
      {
        "Name":"PING",
        "Enable":true,
        "Protocol":1,
        "Mode":"LAN_WAN",
        "TrustAll":true
      }
    ]
e aggiungete "LAN_ONLY" anche sotto SSH e TELNET (come per gli altri servizi).

2) Copiate la password root criptata da questa sezione:
Codice:
"X_ZYXEL_LoginCfg":{
    "LoginGroupConfigurable":true,
    "LogGp":[
      {
        "GP_Privilege":"_encrypt_xxxxxxxxxxxxxxxxx",
        "Account":[
          {
            "AutoShowQuickStart":false,
            "Enabled":true,
            "EnableQuickStart":true,
            "Page":"",
            "Username":"root",
            "Password":"",
            "PasswordHash":"",
            "Privilege":"_encrypt_xxxxxxxxxxxxxxxxxxxx",
            "DefaultPassword":"_encrypt_PASSWORD_CRIPTATA_DA_COPIARE"
e incollatela nella sezione DynamicDNS modificandola come segue:
Codice:
"X_ZYXEL_EXT":{
  	"DynamicDNS":{
      "Enable":true,
      "ServiceProvider":"userdefined",
      "DDNSType":"",
      "HostName":"foobar",
      "UserName":"foobar",
      "Password":"_encrypt_INCOLLARE_QUI_LA_PASSWORD_CRIPTATA",
      "IPAddressPolicy":0,
      "UserIPAddress":"0.0.0.0",
      "Wildcard":false,
      "Offline":false,
      "Interface":"",
      "UpdateURL":"foobar",
      "ConnectionType":"HTTP"
    }
3) Ripristinate il file appena modificato tramite GUI (sempre con account tiscali) e attendete il riavvio

4) Accedete alla GUI sempre con lo stesso account, andate nella pagina Dynamic DNS e cliccate sull'occhio per visualizzare la password root in chiaro!


In base alla changelist, non dovrebbe esserci alcuna differenza tra il firmware V5.50b5 in ns possesso e quello V5.50C0 disponibile sul sito del produttore.