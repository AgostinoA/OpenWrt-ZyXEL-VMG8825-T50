#!/bin/sh
port=$1
protocol=$2
RUN=1
PROCESS="/usr/bin/iperf"
PROCESS_ARG=""
PROCESS_PID=
kill_process() {
	trap '' INT TERM QUIT
	echo "stop ${PROCESS}......."
	if [ -e "/proc/$PROCESS_PID/status" ]; then
		kill -TERM $PROCESS_PID
	else
		killall ${PROCESS##*/}
	fi
	if [ -e "/proc/$PROCESS_PID/status" ]; then
		kill -KILL $PROCESS_PID
	fi
	wait
	RUN=0
	exit
}
trap 'kill_process' INT TERM QUIT
while [ $RUN == 1 ]
do
	(trap - INT TERM QUIT; exec ${PROCESS} -s ${protocol} -p ${port} -C) &
	PROCESS_PID=$!
	wait
	sleep 2
	echo "${PROCESS} restart....."
done
