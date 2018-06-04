//
// Created by Garrett Battaglia on 1/16/18.
//

#ifndef EXOS_FILE_H
#define EXOS_FILE_H
#include "Global.h"

class File {
	private:
		//TODO void* -> process*
		/**
		 * @brief who owns the file
		 * 
		 */
		void* process;
	public:
		/**
		* @brief read from file
		* 
 		* @param buffer read to
		* @param size size to read
		* @return size_t size read
	 	*/
		virtual size_t read(char* buffer, size_t size) = 0;
};
#endif //EXOS_FILE_H
