#!/bin/sh

EXEC_NAME=mosquitto
EXEC_PATH=/usr/sbin
EXEC_OPTION=-c
EXEC_CONFIG=/etc/config/zymosquitto.conf

start()
{
	$EXEC_PATH/$EXEC_NAME $EXEC_OPTION $EXEC_CONFIG &
}

stop()
{
	killall $EXEC_NAME
}

case "$1" in
	start)
		PID=$(pgrep mosquitto)
		if [ "$PID" == "" ] ; then
		echo -e "starting mosquitto."
		start
		else
		  echo 'mosquitto is already running !!!'
		fi
		exit 0
		;;

	stop)
		echo -e "stoping mosquitto."
		stop
		exit 0
		;;

	restart)
		echo -e "restarting mosquitto."
		stop
		start
		exit 0
		;;

	*)
		echo "$0: unrecognized option $1"
		exit 1
		;;
esac
