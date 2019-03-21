/*
\file   main.c

\brief  Main source file.

(c) 2018 Microchip Technology Inc. and its subsidiaries.

Subject to your compliance with these terms, you may use Microchip software and any
derivatives exclusively with Microchip products. It is your responsibility to comply with third party
license terms applicable to your use of third party software (including open source software) that
may accompany Microchip software.

THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY
IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS
FOR A PARTICULAR PURPOSE.

IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP
HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO
THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL
CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT
OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS
SOFTWARE.
*/

#include <stdio.h>
#include "atmel_start.h"
#include "led.h"
#include "clock_config.h"
#include <util/delay.h>

#include "INA219.h"
easy_INA219 ina219;

int main(void)
{
	atmel_start_init();
	sei();

	LED_test();


	ina219.ina219_i2caddr=INA219_ADDRESS;
	ina219_begin(&ina219);
	ina219_setCalibration_16V_400mA(&ina219);

	float shuntvoltage = 0;
	float busvoltage = 0;
	float current_mA = 0;
	float loadvoltage = 0;
	float power_mW = 0;

	while (1) {
//		runScheduler();
		LED_test();
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

	return 0;
}
