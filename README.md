# ES7243E Driver


## Example
```c
static bool i2c_write_reg(uint8_t addr, uint8_t data)
{
    return your_i2c_write(ES7243E_I2C_ADDR, addr, data);
}

void your_main(void)
{
	...
	struct es7243e es = {
		.write_reg = i2c_write_reg,
	};
	es7243e_init(&es);
	...
}
```
