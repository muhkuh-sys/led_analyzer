/***************************************************************************
 *   Copyright (C) 2015 by Subhan Waizi                           		   *
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

/** \file led_analyzer.h

	 \brief led_analyzer handles all functionality on device level and provides the functions needed by the GUI application (header)
	 
The led_analyzer library will handle functionality to work with severeal color controller devices. It scans
for connected color controller devices and opens them. All devices that have been connected to will have handles. 
These handles will be stored in an array and can be used by all underlying color related functions. Furthermore this library
provides the functions which are required for the application CoCo App.
 
 */
 
#include "tcs3472.h"

#ifndef __LED_ANALYZER_H__
#define __LED_ANALYZER_H__



int  scan_devices(char** asSerial, unsigned int uiLength);	
int  connect_to_devices(void** apHandles, int apHlength, char** asLength);
int  read_colors(void** apHandles, int devIndex, unsigned short *ausClear, unsigned short* ausRed,
	 unsigned short *ausGreen, unsigned short* ausBlue, unsigned short* CCT, float* afLUX,
	 unsigned char *aucIntegrationtime, unsigned char* aucGain);
int  init_sensors(void** apHandles, int devIndex);
int  get_number_of_handles(void ** apHandles);
int  handleToDevice(int handle);
int	 set_gain(void** apHandles, int devIndex, unsigned char gain);
int	 set_gain_x(void** apHandles, int devIndex, unsigned int uiX, unsigned char gain);
int	 get_gain(void** apHandles, int devIndex, unsigned char* aucGains);	
int	 set_intTime(void** apHandles, int devIndex, unsigned char integrationtime);
int	 set_intTime_x(void** apHandles, int devIndex, unsigned int uiX, unsigned char integrationtime);
int	 get_intTime(void** apHandles, int devIndex, unsigned char* aucIntTimeSettings);
int  get_number_of_serials(char** asSerial);
int  swap_serialPos(char** asSerial, unsigned int swap1, unsigned int swap2);
int	 getSerialIndex(char** asSerial, char* curSerial);
int	 swap_up(char** asSerial, char* curSerial);
int	 swap_down(char** asSerial, char* curSerial);
void free_devices(void** apHandles);
void wait4Conversion(unsigned int uiWaitTime);

#endif	/*__LED_ANALYZER_H__*/

