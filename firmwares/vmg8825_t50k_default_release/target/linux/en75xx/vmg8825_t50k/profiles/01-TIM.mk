define Profile/TIM
	NAME:=TIM Profile (all drivers)
	PACKAGES:=
endef

define Profile/TIM/Description
	TIM package set compatible with most boards.
endef
$(eval $(call Profile,TIM))
