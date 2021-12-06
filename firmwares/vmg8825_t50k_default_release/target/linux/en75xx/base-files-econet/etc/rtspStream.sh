conntrack  -L  -p TCP --dport 554 > /tmp/rtspInfo
rtsp=`cat /tmp/rtspInfo | awk '{print substr ($6,5)}'`
for stream in $rtsp; do
	conntrack  -U -s $stream -p udp -t 70
done

