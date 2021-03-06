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
#ifndef _LIBRARY_H_
#define _LIBRARY_H_ 1
#include"Def.h"

/**
 *	Load dynamic library in runtime.
 */
class PVDECLSPEC Library{
public:
	Library(void);
	Library(const char* clibrary);
	Library(const Library& library);
	~Library(void);

	/**
	 *	Open library.
	 *
	 *	@Return true if successfully.
	 */
	bool open(const char* clibrary);

	/**
	 *	Close library.
	 *	This will unload all function pointer loaded
	 *	from this library object.
	 */
	void close(void);

	/**
	 *	Determine if loaded library is valid.
	 *
	 *	@Return true if valid library.
	 */
	bool isValid(void)const;

	/**
	 *	Get function pointer.
	 *
	 *	@Return function pointer if successfully.
	 */
	void* getfunc(const char* pProcName);

private:	/*	Attributes.	*/

	void* mlib;
};

#endif
