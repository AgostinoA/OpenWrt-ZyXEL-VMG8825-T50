define Profile/Default
	NAME:=Default Profile (all drivers)
	PACKAGES:=
endef

define Profile/Default/Description
	Default package set compatible with most boards.
endef
$(eval $(call Profile,Default))
