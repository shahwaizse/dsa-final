#include<winsock2.h>
#include<iostream>
#include<ws2tcpip.h>
#include<iostream>
#include<thread>
#include"fo.h"
using namespace std;

ht table(10);

void load(){
	fstream file;
	string x, filename;
	char* y;
	file.open("storage/log.txt", ios::in);
	while(file >> x){
		y = &x[1];
		filename = y;
		if(x[0] == 'c'){
			table.add(filename);
		}
		if(x[0] == 'd'){
			table.del(filename);
		}
	}
	file.close();
}

void uploadfile(SOCKET x, string filename){
	string path = "storage/";
	path += filename;
	char buf[500] = {0};
	int buflen = 500;
	fstream file;
	file.open(path, ios::in | ios::binary);
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
	string path = "storage/";
	path += filename;
	char buf[500] = {0};
	int buflen = 500;
	fstream file;
	file.open(path, ios::out | ios::binary);
	while(recv(x, buf, buflen, 0) != 0){
		if(buf[0] == 't' && buf[1] == 'y'){
			break;
		}
		file.write(buf, buflen);
	}
	file.close();
}

void clientThread(SOCKET x){
	//char buf[300] = {0};
	int buflen = 300;
	char* f;
	string filename;
	for(;;){
		char buf[300] = {0};
		if(recv(x, buf, buflen, 0) == -1){
			break;
		}
		f = &buf[1];
		filename = f;
		char msgbuf[2];
		int msgbuflen = 2;
		if(buf[0] == 'u'){
			if(create_file(&table, filename) == 1){
				msgbuf[0] = 'o';
				msgbuf[1] = 'k';
				send(x, msgbuf, msgbuflen, 0);
				downloadfile(x, filename);
			}
			else{
				msgbuf[0] = 'n';
				msgbuf[1] = 'o';
				send(x, msgbuf, msgbuflen, 0);
			}
		}
		if(buf[0] == 'd'){
			if(delete_file(&table, filename) == 1){
				msgbuf[0] = 'o';
				msgbuf[1] = 'k';
				send(x, msgbuf, msgbuflen, 0);
			}
			else{
				msgbuf[0] = 'n';
				msgbuf[1] = 'o';
				send(x, msgbuf, msgbuflen, 0);
			}
		}
		if(buf[0] == 's'){
			if(search_file(&table, filename) == 1){
				msgbuf[0] = 'o';
				msgbuf[1] = 'k';
				send(x, msgbuf, msgbuflen, 0);
				uploadfile(x, filename);
			}
			else{
				msgbuf[0] = 'n';
				msgbuf[1] = 'o';
				send(x, msgbuf, msgbuflen, 0);
			}
		}
	}
	shutdown(x, SD_SEND);
	closesocket(x);
	cout << "Client disconnected.\n";
}

int main()
{
	load();
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	addrinfo* result = NULL;
	addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	getaddrinfo("192.168.201.109", "6000", &hints, &result);
	SOCKET listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);       
	SOCKET serverSocket = INVALID_SOCKET;
	bind(listenSocket, result->ai_addr, result->ai_addrlen);
	listen(listenSocket, SOMAXCONN);
	for(;;){
		serverSocket = accept(listenSocket, NULL, NULL);
		cout<<"Client connected.\n";
		thread newthread(clientThread, serverSocket);
		newthread.detach();
	}
}