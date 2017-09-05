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
#ifndef _DEF_H_
#define _DEF_H_ 1
#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>
#include<errno.h>

/**
 *	library declaration.
 */
#ifdef PV_GNUC
	#if defined(PV_UNIX)
		#define PVDECLSPEC __attribute__((__visibility__ ("default")))
	#else
		#define PVDECLSPEC
	#endif
#elif defined(PV_VC)
	#if PV_INTERNAL
		#define PVDECLSPEC __declspec(dllexport)
	#else
		#define PVDECLSPEC __declspec(dllimport)
	#endif
#else
	#define PVDECLSPEC
#endif

#endif
