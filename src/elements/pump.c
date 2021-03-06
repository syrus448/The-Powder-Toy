/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <element.h>

int update_PUMP(UPDATE_FUNC_ARGS) {
	int r, rx, ry;
	if (parts[i].life>0 && parts[i].life!=10)
		parts[i].life--;
	if (parts[i].life==10)
	{
		if (parts[i].temp>=256.0+273.15)
			parts[i].temp=256.0+273.15;
		if (parts[i].temp<= -256.0+273.15)
			parts[i].temp = -256.0+273.15;

		if (pv[y/CELL][x/CELL]<(parts[i].temp-273.15))
			pv[y/CELL][x/CELL] += 0.1f*((parts[i].temp-273.15)-pv[y/CELL][x/CELL]);
		if (y+CELL<YRES && pv[y/CELL+1][x/CELL]<(parts[i].temp-273.15))
			pv[y/CELL+1][x/CELL] += 0.1f*((parts[i].temp-273.15)-pv[y/CELL+1][x/CELL]);
		if (x+CELL<XRES)
		{
			pv[y/CELL][x/CELL+1] += 0.1f*((parts[i].temp-273.15)-pv[y/CELL][x/CELL+1]);
			if (y+CELL<YRES)
				pv[y/CELL+1][x/CELL+1] += 0.1f*((parts[i].temp-273.15)-pv[y/CELL+1][x/CELL+1]);
		}
		for (rx=-2; rx<3; rx++)
			for (ry=-2; ry<3; ry++)
				if (x+rx>=0 && y+ry>0 && x+rx<XRES && y+ry<YRES && (rx || ry))
				{
					r = pmap[y+ry][x+rx];
					if (!r)
						continue;
					if ((r&0xFF)==PT_PUMP)
					{
						if (parts[r>>8].life<10&&parts[r>>8].life>0)
							parts[i].life = 9;
						else if (parts[r>>8].life==0)
							parts[r>>8].life = 10;
					}
				}
	}
	return 0;
}
