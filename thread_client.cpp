#include<winsock2.h>
#include<iostream>
#include<ws2tcpip.h>
#include<fstream>
using namespace std;

void uploadfile(SOCKET x, string filename){
	char buf[500] = {0};
	int buflen = 500;
	fstream file;
	file.open(filename, ios::in | ios::binary);
	while(true){
		file.read(buf, buflen);
		send(x, buf, buflen, 0);
		if(file.eof()){
			buf[0] = 't';
			buf[1] = 'y';
			send(x, buf, buflen, 0);
			break;
		}
	}
	file.close();
}

void downloadfile(SOCKET x, string filename){
	char buf[500] = {0};
	int buflen = 500;
	fstream file;
	file.open(filename, ios::out | ios::binary);
	while(recv(x, buf, buflen, 0) != 0){
		if(buf[0] == 't' && buf[1] == 'y'){
			break;
		}
		file.write(buf, buflen);
	}
	file.close();
}

int main(){
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	addrinfo* result = NULL;
	addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	getaddrinfo("192.168.201.109", "6000", &hints, &result);
	SOCKET clientSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	connect(clientSocket, result->ai_addr, result->ai_addrlen);
	char* buf;
	string command, filename;
	for(;;){
		cin >> command;
		if(command == "upload"){
			cin >> filename;
			fstream check(filename, ios::in);
			if(!check.is_open()){
				cout << "Upload failed. Filename/s incorrect.\n";
				break;
			}
			command = "u";
			command += filename;
			buf = &command[0];
			int buflen = command.size();
			send(clientSocket, buf, buflen, 0);
			recv(clientSocket, buf, buflen, 0);
			if(buf[0] == 'o' && buf[1] == 'k'){
				cout << "Uploading file...\n";
				uploadfile(clientSocket, filename);
				cout << "File uploaded.\n";
			}
			if(buf[0] == 'n' && buf[1] == 'o'){
				cout << "File already exists.\n";
			}
			buf = 0;
		}
		else if(command == "delete"){
			cin >> filename;
			fstream check(filename, ios::in);
			if(!check.is_open()){
				cout << "Delete failed. Filename/s incorrect.\n";
				break;
			}
			command = "d";
			command += filename;
			buf = &command[0];
			int buflen = command.size();
			send(clientSocket, buf, buflen, 0);
			recv(clientSocket, buf, buflen, 0);
			if(buf[0] == 'o' && buf[1] == 'k'){
				cout << "File deleted.\n";
			}
			if(buf[0] == 'n' && buf[1] == 'o'){
				cout << "File does not exist.\n";
			}
			buf = 0;
		}
		else if(command == "search"){
			cin >> filename;
			fstream check(filename, ios::in);
			if(!check.is_open()){
				cout << "Search failed. Filename/s incorrect.\n";
				break;
			}
			command = "s";
			command += filename;
			buf = &command[0];
			int buflen = command.size();
			send(clientSocket, buf, buflen, 0);
			recv(clientSocket, buf, buflen, 0);
			if(buf[0] == 'o' && buf[1] == 'k'){
				downloadfile(clientSocket, filename);
				cout << "File downloaded.\n";
			}
			if(buf[0] == 'n' && buf[1] == 'o'){
				cout << "File does not exist.\n";
			}
			buf = 0;
		}
		else{
			cout << "Some parameters were incorrect.\n";
		}
	}
	shutdown(clientSocket, SD_SEND);
	closesocket(clientSocket);
}