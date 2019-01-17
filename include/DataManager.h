#ifndef data_manager_h
#define data_manager_h
#include "libraries.h"

/*
 * Wrapper class for managing multiple file streams.
 * map of file stream pointers, access by file name.
 * if the map contains a stream pointer, that stream is opened.
 * 	-due to this property, don't think [] operator can be supported as an access to the underlying files map
 * absolute path encoded into file name
 */ 

class DataManager
{
	protected:
		std::map<std::string, std::ofstream*> files;

	public:
		DataManager(std::map<std::string, std::ofstream* > f){files = f;}
		DataManager() : DataManager(std::map<std::string, std::ofstream*>({})){}
		~DataManager(){for(auto it = files.begin(); it != files.end(); it++) {it->second->close(); delete it->second;} }
		void open(std::string file_name, std::ios_base::openmode mode){files.insert(std::make_pair(file_name, new std::ofstream())); files.at(file_name)->open(file_name.c_str(), mode);}
		bool is_open(std::string file_name){return files.at(file_name)->is_open();}
		void close(std::string file_name){files.at(file_name)->close();}
		std::ofstream& file(std::string file_name){return *files.at(file_name);}
};

#endif
