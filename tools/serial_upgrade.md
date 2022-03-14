
# OTHER TERMINAL
sudo picocom -b 115200 /dev/ttyUSB0
    Hit any key to stop autoboot:  5
    ZHAL>

    Con help vediamo quali comandi possiamo effettuare:
        ZHAL> help
            ATEN x[,y]         set BootExtension Debug Flag (y=password)
            ATSE x             show the seed of password generator
            ATDC               disable check model mechanism
            ATSH               dump manufacturer related data in ROM
            ATRT [x,y,z,u]     RAM read/write test (x=level, y=start addr, z=end addr, u=iterations)
            ATGO               boot up whole system
            ATSR [x]           system reboot
            ATUR x[,y]         upgrade RAS image (filename, partition number)

    Disabilitiamo il model check mechanism
        ZHAL> atdc
        Model ID chcek: disabled

    E ora attiviamo il TFTP server del modem per attendere l'invio del nuovo firmware dal nostro computer:
        ZHAL> atur V550ABOM3C0.bin
        Upgrade to rootfs partition 1
        TFTP server is started, put your file 'V550ABOM3C0.bin' to server (IP is 192.168.1.1)

# OTHER TERMINAL
atftp 192.168.1.1
    tftp> put V550ABOM3C0.bin

    TFTP server is started, put your file 'V550ABOM3C0.bin' to server (IP is 192.168.1.1).
    ......................................................................................
    Total 23049891 (0x15FB6A3) bytes received

    File download to memory address 0x80020000, length is 23049891
    Ignore checking model ID!

    Please be patient, start to upgrade RAS!

    ............................................................................................
    Update boot flag to 1
    ...Auto reboot after 2 seconds

    ... se tutto è andato come dovrebbe avremo il nuovo firmware installato.

    IMPORTANTE
    A questo punto si dovrebbe riuscire a fare il Log-In nell'interfaccia con le credenziali precedenti e bisognerebbe salvarle nella Rom-D perchè se si fa un reset di fabbrica come ho fatto io carica
    la Rom-D di default Zyxel che cambia le credenziali autogenerandole dal seriale.
    Questa cosa purtroppo non la posso confermare.

    Ad ogni modo è possibile recuperare la password supervisore o admin.

    Rimango a disposizione per eventuali chiarimenti.
    Ciao!!