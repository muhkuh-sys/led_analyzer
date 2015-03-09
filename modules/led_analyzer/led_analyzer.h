/***************************************************************************
 *   Copyright (C) 2007 by Christoph Thelen                                *
 *   doc_bacardi@users.sourceforge.net                                     *
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

 
 /*
 email ams / taos
 customer.service@ams.com
 */
 
#include "ftdi.h"

#ifndef __LED_ANALYZER_H__
#define __LED_ANALYZER_H__





			  /* Detects all devices and stores the device handles into the apHandles Array, returns number of devices found if successful, else
			  returns -1 */
int 		  detect_devices(void** apHandles, int apHlength);
			  /* Reads the colors of a device (devIndex starting with 0) and stores the 4x 16 unsigned short values into the argument parameters */
int 		  read_colors(void** apHandles, int devIndex, unsigned short *ausClear, unsigned short* ausRed,
			  unsigned short *ausGreen, unsigned short* ausBlue);
			  /* used to set gain and integrationtime and to turn sensor on, last argument is used for the wait directive after tcs_on, normalle 100ms - waitAdjust */						   
int 		  init_sensors(void** apHandles, int devIndex, unsigned long integrationtime, unsigned long gain, unsigned int waitAdjust);
		      /* Returns number of handles in apHandles (1device = 2 handles) Note: May only be called after detect_devices has been called, otherwise apHandles will be empty */
int 		  get_handleLength(void ** apHandles);
			  /* Frees all devices and closes the usb connection */
int 		  free_devices(void** apHandles);
			  /* Checks the sensor data for validity / exceedings of maximum clear */

int			  check_validity(void** apHandles, int devIndex, unsigned short* ausClear, unsigned long integrationtime);
			  /* Returns device # to a given handle # */
int 		  handleToDevice(int handle);				
 
#endif	/* __BIT_H__ */
