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
#ifndef _PV_ZIP_FILE_H_
#define _PV_ZIP_FILE_H_ 1
#include"System.h"

/**
 *	Zip file container.
 *	Responsible for loading files from
 *	a zip file.
 */
class ZipFile{
public:

	~ZipFile(void);

	/**
	 *	Load file from file path inside the zip file.
	 *
	 *	\cfilename
	 *
	 *	\pbuf
	 *
	 *	@Return number of bytes.
	 */
	long int loadFile(const char* __restrict__ cfilename,
	        void** __restrict__ pbuf);

	/**
	 *	Load file from file path inside the zip file.
	 *
	 *	\cfilename
	 *
	 *	\pbuf
	 *
	 *	@Return number of bytes.
	 */
	long int loadString(const char* __restrict__ cfilename,
	        void** __restrict__ pbuf);

	/**
	 *	Check if file exists inside
	 *	zip file..
	 *
	 *	@Return true if exists, false otherwise.
	 */
	long int exists(const char* __restrict__ cfilename);

private:	/*	Private attributes.	*/

	void* pzip;

public:	/*	Factory method.	*/

	/**
	 *	Create zipfile.
	 *
	 *	\cfilename
	 *
	 *	@Return non-null if successfully.
	 */
	static ZipFile* createZipFileObject(const char* cfilename);

private:	/*	Prevent one from creating an instance of this class.	*/

	ZipFile(void);
	ZipFile(const ZipFile& other);

};

#endif
