//
// Created by Garrett Battaglia on 1/16/18.
//

#ifndef EXOS_FILE_H
#define EXOS_FILE_H
class File{
	private:
		//TODO void* -> process*
		void* process;
	public:
		size_t read(char* buffer, size_t size) = 0;
};
#endif //EXOS_FILE_H
