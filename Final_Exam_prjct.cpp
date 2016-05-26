#include "mbed.h"

/*******************************************
			Digital Output Ports
*******************************************/
DigitalOut valve_1(PB_14);
DigitalOut valve_2(PB_15);
DigitalOut valve_3(PA_8);
DigitalOut valve_4(PA_10);
DigitalOut valve_5(PA_11);
DigitalOut valve_6(PA_12);
DigitalOut valve_7(PA_13);
DigitalOut air_in(PA_15);
//DigitalOut air_out(PB_3);
DigitalOut air_out(PA_14);//It should be PB_3 but, but, but USBTX is using also PB_3 
DigitalOut pump(PB_5);
/*******************************************
			Analog Input Ports
*******************************************/
AnalogIn sensor_1(PA_6);
AnalogIn sensor_2(PA_7);
AnalogIn sensor_3(PA_4);
AnalogIn sensor_4(PA_5);
AnalogIn sensor_5(PA_2);
AnalogIn sensor_6(PA_3);
AnalogIn sensor_7(PA_0);
//AnalogIn sensor_8(PA_1);


Serial ser(USBTX, USBRX); // (PB_3, PB_4)

void static_pressure_mode();
void pulsing_pressure_mode();
void read_sensor();
/*******************************************
Gloabal variables
*******************************************/
int chamber1;
int chamber2;
int chamber3;
int chamber4;
int chamber5;
int chamber6;
int chamber7;
int chamber8;

int chamb_1_expect = 60;
int chamb_2_expect = 50;
int chamb_3_expect = 50;
int chamb_4_expect = 90;
int chamb_5_expect = 90;
int chamb_6_expect = 100;
int chamb_7_expect = 100;
//int chamber_8_expect = 300;

void read_sensor()
{
	float sensor_1_meas;
	float sensor_2_meas;
	float sensor_3_meas;
	float sensor_4_meas;
	float sensor_5_meas;
	float sensor_6_meas;
	float sensor_7_meas;
//  float sensor_8_meas;

	sensor_1_meas = sensor_1.read(); // Converts and read the analog input value (value from 0.0 to 1.0)
	sensor_1_meas *= 3300; // Change the value to be in the 0 to 3300 range
	chamber1= (((sensor_1_meas - 130) * 10) / 90); //Convert voltages to mbars
	printf("\n\rChamber 1 Pressure = %d mbar \n\r", chamber1);

	sensor_2_meas = sensor_2.read(); // Converts and read the analog input value (value from 0.0 to 1.0)
	sensor_2_meas *= 3300; // Change the value to be in the 0 to 3300 range
	chamber2 = (((sensor_2_meas - 130) * 10) / 90); //Convert voltages to mbars
	printf("\n\rChamber 2 Pressure = %d mbar \n\r", chamber2);

	sensor_3_meas = sensor_3.read(); // Converts and read the analog input value (value from 0.0 to 1.0)
	sensor_3_meas *= 3300; // Change the value to be in the 0 to 3300 range
	chamber3 = (((sensor_3_meas - 130) * 10) / 90); //Convert voltages to mbars
	printf("\n\rChamber 3 Pressure = %d mbar  \n\r", chamber3);

	sensor_4_meas = sensor_4.read(); // Converts and read the analog input value (value from 0.0 to 1.0)
	sensor_4_meas *= 3300; // Change the value to be in the 0 to 3300 range
	chamber4 = (((sensor_4_meas - 130) * 10) / 90); //Convert voltages to mbars
	printf("\n\rChamber 4 Pressure = %d mbar  \n\r", chamber4);

	sensor_5_meas = sensor_5.read(); // Converts and read the analog input value (value from 0.0 to 1.0)
	sensor_5_meas *= 3300; // Change the value to be in the 0 to 3300 range
	chamber5 = (((sensor_5_meas - 130) * 10) / 90); //Convert voltages to mbars
	printf("\n\rChamber 5 Pressure = %.d mbar  \n\r", chamber5);

	sensor_6_meas = sensor_6.read(); // Converts and read the analog input value (value from 0.0 to 1.0)
	sensor_6_meas *= 3300; // Change the value to be in the 0 to 3300 range
	chamber6 = (((sensor_6_meas - 130) * 10) / 90); //Convert voltages to mbars
	printf("\n\rChamber 6 Pressure = %d mbar  \n\r", chamber6);

	sensor_7_meas = sensor_7.read(); // Converts and read the analog input value (value from 0.0 to 1.0)
	sensor_7_meas *= 3300; // Change the value to be in the 0 to 3300 range
	chamber7 = (((sensor_7_meas - 130) * 10) / 90); //Convert voltages to mbars
	printf("\n\rChamber 7 Pressure = %d mbar  \n\r", chamber7);

/*	sensor_8_meas = sensor_8.read(); // Converts and read the analog input value (value from 0.0 to 1.0)
	sensor_8_meas *= 3300; // Change the value to be in the 0 to 3300 range
	chamber8 = (((sensor_8_meas - 130) * 10) / 90); //Convert voltages to mbars
	printf("\n\rSensor 8 Pressure = %d mbar  \n\r", chamber8);
*/
}

void static_pressure_mode()
{

	while (1) {

		valve_1 = 0;
		valve_2 = 0;
		valve_3 = 0;
		valve_4 = 0;
		valve_5 = 0;
		valve_6 = 0;
		valve_7 = 0;
		pump = 0;
		air_in = 0;
		air_out = 0;
		read_sensor();
		wait(10);

		/***********************************************************************
		LOW PRESSURE ( Pump it up )
		***********************************************************************/
		if (chamber1 < (chamb_1_expect - 5))
		{
			while (chamber1 < chamb_1_expect + 5)
			{
				valve_1 = 1;
				pump = 1;
				air_in = 1;
				air_out = 0;
				read_sensor();
				wait(0.2);
			}
		}
		valve_1 = 0;

		if (chamber2 < (chamb_2_expect - 5))
		{
			while (chamber2 < chamb_2_expect + 5)
			{
				valve_2 = 1;
				pump = 1;
				air_in = 1;
				air_out = 0;
				read_sensor();
				wait(0.2);
			}
		}
		valve_2 = 0;

		if (chamber3 < (chamb_3_expect - 5))
		{
			while (chamber3 < chamb_3_expect + 5)
			{
				valve_3 = 1;
				pump = 1;
				air_in = 1;
				air_out = 0;
				read_sensor();
				wait(0.2);
			}
		}
		valve_3 = 0;

		if (chamber4 < (chamb_4_expect - 5))
		{
			while (chamber4 < chamb_4_expect + 5)
			{
				valve_4 = 1;
				pump = 1;
				air_in = 1;
				air_out = 0;
				read_sensor();
				wait(0.2);
			}
		}
		valve_4 = 0;

		if (chamber5 < (chamb_5_expect - 5))
		{
			while (chamber5 < chamb_5_expect + 5)
			{
				valve_5 = 1;
				pump = 1;
				air_in = 1;
				air_out = 0;
				read_sensor();
				wait(0.2);
			}
		}
		valve_5 = 0;

		if (chamber6 < (chamb_6_expect - 5))
		{
			while (chamber6 < chamb_6_expect + 5)
			{
				valve_6 = 1;
				pump = 1;
				air_in = 1;
				air_out = 0;
				read_sensor();
				wait(0.2);
			}
		}
		valve_6 = 0;

		if (chamber7 < (chamb_7_expect - 5))
		{
			while (chamber7 < chamb_7_expect + 5)
			{
				valve_7 = 1;
				pump = 1;
				air_in = 1;
				air_out = 0;
				read_sensor();
				wait(0.2);
			}
		}
		valve_7 = 0;

		/***********************************************************************
		TOO HIGH PRESSURE ( Let air out )
		***********************************************************************/
		if (chamber1 > (chamb_1_expect + 10))
		{
			while (chamber1 >= chamb_1_expect)
			{
				valve_1 = 1;
				pump = 0;
				air_in = 0;
				air_out = 1;
				read_sensor();
				wait(0.2);
			}
		}
		valve_1 = 0;

		if (chamber2 > (chamb_2_expect + 10))
		{
			while (chamber2 >= chamb_2_expect)
			{
				valve_2 = 1;
				pump = 0;
				air_in = 0;
				air_out = 1;
				read_sensor();
				wait(0.2);
			}
		}
		valve_2 = 0;

		if (chamber3 > (chamb_3_expect + 10))
		{
			while (chamber3 >= chamb_3_expect)
			{
				valve_3 = 1;
				pump = 0;
				air_in = 0;
				air_out = 1;
				read_sensor();
				wait(0.2);
			}
		}
		valve_3 = 0;

		if (chamber4 > (chamb_4_expect + 10))
		{
			while (chamber4 >= chamb_4_expect)
			{
				valve_4 = 1;
				pump = 0;
				air_in = 0;
				air_out = 1;
				read_sensor();
				wait(0.2);
			}
		}
		valve_4 = 0;

		if (chamber5 > (chamb_5_expect + 10))
		{
			while (chamber5 >= chamb_5_expect)
			{
				valve_5 = 1;
				pump = 0;
				air_in = 0;
				air_out = 1;
				read_sensor();
				wait(0.2);
			}
		}
		valve_5 = 0;

		if (chamber6 > (chamb_6_expect + 10))
		{
			while (chamber6 >= chamb_6_expect)
			{
				valve_6 = 1;
				pump = 0;
				air_in = 0;
				air_out = 1;
				read_sensor();
				wait(0.2);
			}
		}
		valve_6 = 0;

		if (chamber7 > (chamb_7_expect + 10))
		{
			while (chamber7 >= chamb_7_expect)
			{
				valve_7 = 1;
				pump = 0;
				air_in = 0;
				air_out = 1;
				read_sensor();
				wait(0.2);
			}
		}
		valve_7 = 0;
	}
}

void pulsing_pressure_mode()
{
	valve_1 = 0;
	valve_2 = 0;
	valve_3 = 0;
	valve_4 = 0;
	valve_5 = 0;
	valve_6 = 0;
	valve_7 = 0;
	pump = 0;
	air_in = 0;
	air_out = 0;
	read_sensor();
	wait(0.5);

	while (1)
	{
		/***********************************************************************
		PUMP UP THE CUSHION
		***********************************************************************/
		while (chamber1 <= chamb_1_expect)
		{
			valve_1 = 1;
			pump = 1;
			air_in = 1;
			air_out = 0;
			read_sensor();
			wait(0.5);
		}
		valve_1 = 0;

		while (chamber2 <= chamb_2_expect)
		{
			valve_2 = 1;
			pump = 1;
			air_in = 1;
			air_out = 0;
			read_sensor();
			wait(0.5);
		}
		valve_2 = 0;

		while (chamber3 <= chamb_3_expect)
		{
			valve_3 = 1;
			pump = 1;
			air_in = 1;
			air_out = 0;
			read_sensor();
			wait(0.5);
		}
		valve_3 = 0;

		while (chamber4 <= chamb_4_expect)
		{
			valve_4 = 1;
			pump = 1;
			air_in = 1;
			air_out = 0;
			read_sensor();
			wait(0.5);
		}
		valve_4 = 0;

		while (chamber5 <= chamb_5_expect)
		{
			valve_5 = 1;
			pump = 1;
			air_in = 1;
			air_out = 0;
			read_sensor();
			wait(0.5);
		}
		valve_5 = 0;

		while (chamber6 <= chamb_6_expect)
		{
			valve_6 = 1;
			pump = 1;
			air_in = 1;
			air_out = 0;
			read_sensor();
			wait(0.5);
		}
		valve_6 = 0;

		while (chamber7 <= chamb_7_expect)
		{
			valve_7 = 1;
			pump = 1;
			air_in = 1;
			air_out = 0;
			read_sensor();
			wait(0.5);
		}
		valve_7 = 0;
		pump = 0;
		air_in = 0;

		/***********************************************************************
		Take one chamber - let air out - pump it up again
		***********************************************************************/
		while (chamber1 >= 5)
		{
			valve_1 = 1;
			air_out = 1;
			read_sensor();
			wait(0.5);
		}
		air_out = 0;

		while (chamber1 <= chamb_1_expect)
		{
			air_in = 1;
				pump = 1;
			read_sensor();
			wait(0.5);
		}
		pump = 0;
		valve_1 = 0;
		air_in = 0;

		while (chamber2 >= 5)
		{
			valve_2 = 1;
			air_out = 1;
			read_sensor();
			wait(0.5);
		}
		air_out = 0;

		while (chamber2 <= chamb_2_expect)
		{
			air_in = 1;
			pump = 1;
			read_sensor();
			wait(0.5);
		}
		pump = 0;
		valve_2 = 0;
		air_in = 0;


		while (chamber3 >= 5)
		{
			valve_3 = 1;
			air_out = 1;
			read_sensor();
			wait(0.5);
		}
		air_out = 0;

		while (chamber3 <= chamb_3_expect)
		{
			air_in = 1;
			pump = 1;
			read_sensor();
			wait(0.5);
		}
		pump = 0;
		valve_3 = 0;
		air_in = 0;

		while (chamber4 >= 5)
		{
			valve_4 = 1;
			air_out = 1;
			read_sensor();
			wait(0.5);
		}
		air_out = 0;

		while (chamber4 <= chamb_4_expect)
		{
			air_in = 1;
			pump = 1;
			read_sensor();
			wait(0.5);
		}
		pump = 0;
		valve_4 = 0;
		air_in = 0;

		while (chamber5 >= 5)
		{
			valve_5 = 1;
			air_out = 1;
			read_sensor();
			wait(0.5);
		}
		air_out = 0;

		while (chamber5 <= chamb_5_expect)
		{
			air_in = 1;
			pump = 1;
			read_sensor();
			wait(0.5);
		}
		pump = 0;
		valve_5 = 0;
		air_in = 0;

		while (chamber6 >= 5)
		{
			valve_6 = 1;
			air_out = 1;
			read_sensor();
			wait(0.5);
		}
		air_out = 0;

		while (chamber6 <= chamb_6_expect)
		{
			air_in = 1;
			pump = 1;
			read_sensor();
			wait(0.5);
		}
		pump = 0;
		valve_6 = 0;
		air_in = 0;

		while (chamber7 >= 5)
		{
			valve_7 = 1;
			air_out = 1;
			read_sensor();
			wait(0.5);
		}
		air_out = 0;

		while (chamber7 <= chamb_7_expect)
		{
			air_in = 1;
			pump = 1;
			read_sensor();
			wait(0.5);
		}
		pump = 0;
		valve_7 = 0;
		air_in = 0;
	}
}
int main()
{
	ser.baud(115200);
	int option;
	printf("\nInsert 1 for steady mode or 2 for puls mode :");
	scanf("%d", &option);

	
	if (option == 1)
	{
		static_pressure_mode();
	}
	else if (option == 2)
	{
		pulsing_pressure_mode();
	}

}