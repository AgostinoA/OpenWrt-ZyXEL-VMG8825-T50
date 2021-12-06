scan_pppoe() {
	scan_ppp "$@"
}

setup_interface_pppoe() {
	local iface="$1"
	local config="$2"
	
	for module in slhc ppp_generic pppox pppoe; do
		/sbin/insmod $module 2>&- >&-
	done
	config_get pppoeServiceName "$config" pppoeServiceName 

	# make sure the network state references the correct ifname
	scan_ppp "$config"
	config_get ifname "$config" ifname
	set_interface_ifname "$config" "$ifname"

	config_get mtu "$config" mtu
	mtu=${mtu:-1492}
	start_pppd "$config" \
		plugin rp-pppoe.so \
		mtu $mtu mru $mtu \
        lcp-echo-interval 10 \
        lcp-echo-failure 2 \
		${pppoeServiceName:+rp_pppoe_service $pppoeServiceName} \
		"nic-$iface"
}
