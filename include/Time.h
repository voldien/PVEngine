/**
    Simple physic simulation with a server-client model support.
    Copyright (C) 2016  Valdemar Lindberg

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef _TIME_H_
#define _TIME_H_ 1
#include"Def.h"

/**
 *	Time class for accessing current time in
 *	various time resolution.
 */
class Time{
public:

	/**
	 *	Get delta time since last frame.
	 *
	 *	@Return seconds.
	 */
	static float deltaTime(void);

	/**
	 *	Get smooth delta time. It uses
	 *	the average delta time over multiple
	 *	frames delta time.
	 */
	static float smoothDeltaTime(void);

	/**
	 *	Get time sense engine was initialized.
	 *	@Return number of seconds.
	 */
	static unsigned int time(void);

	/**
	 *	Get time since the engine was initialized.
	 *	@Return number of seconds and fractions of seconds.
	 */
	static float timef(void);

	/**
	 *
	 *	@Return
	 */
	static double timed(void);

	/**
	 *	Get unix epoch time stamp.
	 *	@Return
	 */
	static long int  getUnixTime(void);

	/**
	 *	Get time scale.
	 */
	static float getTimeScale(void);

	/**
	 *	Set time scale.
	 */
	static void setTimeScale(float scale);

	/**
	 *	@Return
	 */
	static long int getTimeResolution(void);

	/**
	 *	Not supported.
	 */
	static float timeSinceLevelLoad(void);

	/**
	 *	Not supported.
	 */
	static void setTimeSinceLevelLoaded(long int time);

	/**
	 *	Get fixed update time in milliseconds.
	 *
	 *	@Return
	 */
	static float fixedTime(void);

	/**
	 *
	 */
	static void internalUpdate(void);

//private:	/*	*/


	static long int ticks;
	static long int ticksSinceLevel;

	static float scale;
	static float fixed;
};

#endif
