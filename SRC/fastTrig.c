/*
  Sept 2013

  bgc32 Rev -

  Copyright (c) 2013 John Ihlein.  All rights reserved.

  Open Source STM32 Based Brushless Gimbal Controller Software

  Includes code and/or ideas from:

  1)AeroQuad
  2)BaseFlight
  3)CH Robotics
  4)MultiWii
  5)S.O.H. Madgwick
  6)UAVX

  Designed to run on the EvvGC Brushless Gimbal Controller Board

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

///////////////////////////////////////////////////////////////////////////////
/*
 *  fasttrig.c
 *
 *  Created on: Aug 10, 2013
 *      Author: ala42
 */
#include "board.h"


short int sinDataI16[SINARRAYSIZE];  //space size =1024*4=4K byte


void initSinArray(void)
{
	int i;

	for (i = 0; i < SINARRAYSIZE; i++)
	{ 
		float x = i * M_TWOPI / SINARRAYSIZE;                       //对2π周期  采样1024个点 分辨率360°/1024=0.35度
		sinDataI16[i] = (short int)round(sinf(x) * SINARRAYSCALE);  //余弦值由[0~1]映射到[0~32767]
	}
}

float fastSin(float x)
{
	if (x >= 0)
	{
		int ix = ((int)(x / M_TWOPI * (float)SINARRAYSIZE)) % SINARRAYSIZE;
		return sinDataI16[ix] / (float)SINARRAYSCALE;
	}

	else
	{
		int ix = ((int)(-x / M_TWOPI * (float)SINARRAYSIZE)) % SINARRAYSIZE;
		return -sinDataI16[ix] / (float)SINARRAYSCALE;
	}
}
