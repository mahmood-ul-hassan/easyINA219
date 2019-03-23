#include <atmel_start.h>
#include "clock_config.h"
#include <util/delay.h>

#include "easyINA219.h"
easy_INA219 ina219;

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	sei();

	/* Replace with your application code */
	ina219.ina219_i2caddr=INA219_ADDRESS;
	ina219_begin(&ina219);
	ina219_setCalibration_16V_400mA(&ina219);

	float shuntvoltage = 0;
	float busvoltage = 0;
	float current_mA = 0;
	float loadvoltage = 0;
	float power_mW = 0;
	while (1) {
		shuntvoltage = ina219_getShuntVoltage_mV(&ina219);
		busvoltage = ina219_getBusVoltage_V(&ina219);
		current_mA = ina219_getCurrent_mA(&ina219);
		power_mW = ina219_getPower_mW(&ina219);
		loadvoltage = busvoltage + (shuntvoltage / 1000);
		
		printf("Bus Voltage:   %.2f V\r\n", busvoltage);
		printf("Shunt Voltage:   %.2f mV\r\n", shuntvoltage);
		printf("Load Voltage:   %.2f V\r\n", loadvoltage);
		printf("Current:   %.2f mA\r\n", current_mA);
		printf("Power:   %.2f mW\r\n\r\n", power_mW);
		_delay_ms(1000);
	}
}
