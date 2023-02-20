#include"ht.h"
#include<fstream>
using namespace std;
int create_file(ht* table, string filename){
	string path = "storage/";
	path += filename;
	if(table->add(filename) == 1){
		fstream file;
		file.open(path, ios::out | ios::binary);
		file.close();
		fstream log;
		log.open("storage/log.txt", ios::out | ios::app);
		log << 'c' << filename << endl;
		log.close();
		return 1;
	}
	return 0;
}
int delete_file(ht* table, string filename){
	string path = "storage/";
	path += filename;
	if(table->del(filename) == 1){
		const char* fname = path.data();
		remove(fname);
		fstream log;
		log.open("storage/log.txt", ios::out | ios::app);
		log << 'd' << filename << endl;
		log.close();
		return 1;
	}
	return 0;
}
int search_file(ht* table, string filename){
	string path = "storage/";
	path += filename;
	if(table->look(filename) == 1){
		fstream file;
		file.open(path, ios::in | ios::binary);
		file.close();
		return 1;
	}
	return 0;
}