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
#ifndef _CONFIG_H_
#define _CONFIG_H_ 1
#include"System.h"
#include<typeinfo>

/**
 *	Responsible for the configuration
 *	of the application.
 */
class PVDECLSPEC Config{
public:	/*	Get and set methods.	*/

	/**
	 *	Get configuration value.
	 *
	 *	\key key associated with the configuration value.
	 *
	 *	@throws invalid_argument: if the configuration key
	 *	did not exist.
	 *
	 *	@Return configuration value.
	 */
	template<class T>
	T get(const std::string& key)const{
		T tmp;
		this->getInternal(key, (void*)&tmp, typeid(T));
		return tmp;
	}

	/**
	 *	Set configuration value.
	 *
	 *	\key key associated with the value.
	 *
	 *	\value value
	 *
	 *	@throws invalid_argument: if value type is not supported.
	 */
	template<class T>
	void set(const std::string& key, const T& value){
		this->setInternal(key, (const void*)&value, typeid(T));
	}

	/**
	 *	Save current configuration of the engine
	 *	to a xml file.
	 *
	 *	\path path where the xml will be saved.
	 *	@throw exception if fails.
	 */
	void save(const char* path);

private:	/*	Internal methods.	*/

	/**
	 *	Set internal configuration value.
	 *
	 *	\key key associated with the value.
	 *
	 *	\value pointer to the value.
	 *
	 *	\type object describing the value data type.
	 */
	void setInternal(const std::string& key, const void* value,
	        const std::type_info& type);

	/**
	 *	Get configuration value.
	 *
	 *	\key key associated with the value.
	 *
	 *	\value pointer to the value.
	 *
	 *	\type object describing the value data type.
	 */
	void getInternal(const std::string& key, void* value,
	        const std::type_info& type)const;

	/**
	 *	Parser getopt option argument and
	 *	assign it to config object.
	 *
	 */
	void parseGetOpt(int argc, const char** argv);

	/**
	 *	Parse configuration file.
	 *
	 *	\path xml configuration file.
	 *
	 *	@throws exception: if failed parsing the configuration
	 *	file.
	 */
	void parseConfigFile(const char* path);

	/**
	 *	Set default configuration options
	 *	for this application.
	 */
	void setDefaultOption(void);

private:	/*	*/

	Config(void);
	Config(const Config& other);
	~Config(void);

	std::map<std::string, int> iconfig;         /*	Integer.	*/
	std::map<std::string, float> fconfig;       /*	Float.	*/
	std::map<std::string, std::string> sconfig; /*	String.	*/

public:	/*	Static factory methods.	*/

	/**
	 *	Create configuration file.
	 *
	 *	\argc number of argument in argv pointer array.
	 *
	 *	\argv string pointer array.
	 *
	 *	\configpath path for override the default
	 *	configuration of the system
	 *
	 *	@throws invalid_argument: for invalid configuration file path.
	 *
	 *	@Return non-null Config object.
	 */
	static Config* createConfig(int argc, const char** argv,
	        const char* configpath);

	/**
	 *	Get configuration file path.
	 *
	 *	@Return non-null string.
	 */
	static const char* getConfigFilePath(int argc, const char** argv);

};

#endif
