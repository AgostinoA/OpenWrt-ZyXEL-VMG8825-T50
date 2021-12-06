#!/bin/sh

export PATH=/home/bin:/home/scripts:/opt/bin:/bin:/sbin:/usr/bin:/usr/sbin
export LD_LIBRARY_PATH=/lib/public:/lib/private:/usr/lib:/lib:/usr/lib/ebtables:/usr/lib/iptables

EXEC_NAME=crond
EXEC_PATH=/usr/sbin
CRONTAB_DIR=/var/spool/cron/crontabs

start()
{
		if [ ! -d $CRONTAB_DIR ]; then 
			mkdir -m 755 -p $CRONTAB_DIR
		fi
		ln -s /etc/crontab $CRONTAB_DIR/root 2>/dev/null
        $EXEC_PATH/$EXEC_NAME -c $CRONTAB_DIR -b
}

stop()
{
        killall -9 $EXEC_NAME
}


case "$1" in
        start)
                PID=$(pgrep '^$EXEC_NAME$')
                if [ "$PID" == "" ] ; then
                  start
                else
                  echo 'crond is already running !!!'
                fi
                exit 0
                ;;

        stop)
                stop
                exit 0
                ;;

        restart)
                stop
                start
                exit 0
                ;;

        *)
                echo "$0: unrecognized option $1"
                exit 1
                ;;

esac