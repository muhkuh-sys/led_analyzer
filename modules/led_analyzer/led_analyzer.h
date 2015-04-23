/***************************************************************************
 *   Copyright (C) 2014 by Subhan Waizi                           		   *
 *                                     									   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

 
 
#include "ftdi.h"

#ifndef __LED_ANALYZER_H__
#define __LED_ANALYZER_H__




			  /* Scans for color controller devices connected to the pc and stores their serial number in asSerial */
int 		  scan_devices(char** asSerial, unsigned int uiLength);	
			  /* returns the amount of color controllers the computer has connected to */
int 		  connect_to_devices(void** apHandles, int apHlength, char** asLength);
			  /* Detects all devices and stores the device handles into the apHandles Array, returns number of devices found if successful, else
			  returns -1 */
int 		  detect_devices(void** apHandles, int apHlength);
			  /* Reads the colors of a device (devIndex starting with 0) and stores the 4x 16 unsigned short values into the argument parameters */
int 		  read_colors(void** apHandles, int devIndex, unsigned short *ausClear, unsigned short* ausRed,
			  unsigned short *ausGreen, unsigned short* ausBlue, float* afBrightness);
			  /* Initializing = turn sensor on, clear relevant flags */						   
int 		  init_sensors(void** apHandles, int devIndex);
		      /* Returns number of handles in apHandles (1device = 2 handles) Note: May only be called after detect_devices has been called, otherwise apHandles will be empty */
int 		  get_handleLength(void ** apHandles);
			  /* Frees all devices and closes the usb connection */
int 		  free_devices(void** apHandles);
			  /* Checks the sensor data for validity / exceedings of maximum clear */
int			  check_validity(void** apHandles, int devIndex, unsigned short* ausClear, unsigned char* aucIntegrationtime);
			  /* Returns device # to a given handle # */
int 		  handleToDevice(int handle);
			  /* Set gain of all sensors */
int			  set_gain(void** apHandles, int devIndex, unsigned char gain);
			  /* Set gain for sensor uiX (0 ... 15) */
int			  set_gain_x(void** apHandles, int devIndex, unsigned char gain, unsigned int uiX);
			  /* Get gain of all sensors and store them in aucGains */
int			  get_gain(void** apHandles, int devIndex, unsigned char* aucGains);	
			  /* Set integration time of all sensors */
int			  set_intTime(void** apHandles, int devIndex, unsigned char integrationtime);
			  /* Set integration time for sensor uiX (0 ... 15) */
int			  set_intTime_x(void** apHandles, int devIndex, unsigned char integrationtime, unsigned int uiX);
			  /* Get integration time of all sensors and store them in aucIntTimeSettings */
int			  get_intTime(void** apHandles, int devIndex, unsigned char* aucIntTimeSettings);
			  /* returns the amount of serial numbers in the serial number array */
int 		  get_number_of_serials(char** asSerial);
			  /* Swap two serial numbers, so the order of opening color controllers can be chosen */
int 		  swap_serialPos(char** asSerial, unsigned int swap1, unsigned int swap2);
			  /* Wait for uiWaitTime ms time, to give the sensor some time for color measurement */
void          wait4Conversion(unsigned int uiWaitTime);


#endif	/* __BIT_H__ */

