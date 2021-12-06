/*
 * (C) Copyright 2010 Quantenna Communications Inc.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include "ruby.h"

#define writel_or(b, addr) writel(readl(addr) | (b), (addr))
#define writel_and(b, addr) writel(readl(addr) & (b), (addr))

inline static void gpio_set_mode(u32 reg, u32 offset, u32 cfg)
{
	u32 tmp = readl(reg);
	tmp &= ~(0x3 << offset);
	tmp |= (cfg << offset);
	writel(tmp, reg);
}

inline static void gpio_config_pin(u32 pin, u32 cfg)
{
	if(pin < RUBY_GPIO_MODE1_MAX) {
		gpio_set_mode(RUBY_GPIO_MODE1, pin * 2, cfg);
	} else {
		gpio_set_mode(RUBY_GPIO_MODE2, (pin - RUBY_GPIO_MODE1_MAX) * 2, cfg);
	}
}

void gpio_config(u32 pin, u32 cfg)
{
	if(cfg >= RUBY_GPIO_ALT_INPUT) {
		writel_or(RUBY_BIT(pin), RUBY_GPIO_AFSEL);
	} else {
		writel_and(~RUBY_BIT(pin), RUBY_GPIO_AFSEL);
	}
	gpio_config_pin(pin, cfg & 0x3);
}

void gpio_output(u32 pin, u32 state)
{
	writel(RUBY_BIT(pin), RUBY_GPIO_OMASK);
	writel(state << pin, RUBY_GPIO_OUTPUT);
	writel(0, RUBY_GPIO_OMASK);
}

u32 gpio_input(u32 pin)
{
	return ((readl(RUBY_GPIO_INPUT) >> pin) & 0x1);
}

