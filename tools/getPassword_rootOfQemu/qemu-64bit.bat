@ECHO OFF
CLS
if not exist "C:\Program Files\qemu\qemu-system-arm.exe" goto no.QEMU
REM set QEMU_AUDIO_DRV="none"
"C:\Program Files\qemu\qemu-system-arm" -M vexpress-a9 -cpu cortex-a9 -m 512 -nographic -kernel zImage -drive file=rootfs.ext2,index=0,media=disk,format=raw,if=sd -dtb vexpress-v2p-ca9.dtb -net nic -net      user,hostfwd=tcp::2222-:22 -append   "rw console=ttyAMA0 console=tty root=/dev/mmcblk0"
goto end

:no.QEMU

ECHO File C:\Program Files\qemu\qemu-system-arm.exe non presente.
ECHO.
ECHO Verifica di aver installato QEMU a 64bit.
ECHO.
ECHO.
ECHO      #### Premi un tasto per uscire ####
PAUSE >NUL

:end
ECHO.
ECHO.
