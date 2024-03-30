/*
 * MIT License
 *
 * Copyright (c) 2024 huxiangjs
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "es7243e.h"

struct es7243e_reg {
	uint8_t addr;
	uint8_t data;
};

static const struct es7243e_reg init_reg[] = {
	{ 0x01, 0x3A },
	{ 0x00, 0x80 },
	{ 0xF9, 0x00 },
	{ 0x04, 0x02 },
	{ 0x04, 0x01 },
	{ 0xF9, 0x01 },
	{ 0x00, 0x1E },
	{ 0x01, 0x00 },

	{ 0x02, 0x00 },
	{ 0x03, 0x20 },
	{ 0x04, 0x01 },
	{ 0x0D, 0x00 },
	{ 0x05, 0x00 },
	/* SCLK = MCLK / 4 */
	{ 0x06, 0x03 },
	/* LRCK = MCLK / 256 */
	{ 0x07, 0x00 },
	/* LRCK = MCLK / 256 */
	{ 0x08, 0xFF },

	{ 0x09, 0xCA },
	{ 0x0A, 0x85 },
	{ 0x0B, 0x00 },

	/*
	 * ADC volume control
	 * +0dB
	 * ADC_VOLUME is the maxgain when ALC on
	 */
	{ 0x0E, 0xBF },

	/*
	 * ALC enable
	 * -30.0dB
	 */
	{ 0x0F, 0xC0 },
	{ 0x13, 0x00 },

	{ 0x14, 0x0C },
	{ 0x15, 0x0C },
	{ 0x17, 0x02 },
	{ 0x18, 0x26 },
	{ 0x19, 0x77 },
	{ 0x1A, 0xF4 },
	{ 0x1B, 0x66 },
	{ 0x1C, 0x44 },
	{ 0x1E, 0x00 },
	{ 0x1F, 0x0C },

	/* PGA gain +0dB */
	{ 0x20, 0x10 },
	/* PGA gain +0dB */
	{ 0x21, 0x10 },

	/* Slave  Mode */
	{ 0x00, 0x80 },

	{ 0x01, 0x3A },
	{ 0x16, 0x3F },
	{ 0x16, 0x00 },
};

static bool es7243e_config(struct es7243e *es, const struct es7243e_reg *reg_array, size_t len)
{
	uint8_t index;
	bool ret;

	for (index = 0; index < len; index++) {
		ret = es->write_reg(reg_array[index].addr, reg_array[index].data);
		if (!ret)
			return ret;
	}

	return true;
}

/**
 * @brief Init ES7243E && Start
 *
 * @param es Configuration
 * @return true OK
 * @return false ERROR
 */
bool es7243e_init(struct es7243e *es)
{
	if (!es || !es->write_reg)
		return false;

	return es7243e_config(es, init_reg, sizeof(init_reg)/sizeof(struct es7243e_reg));
}
