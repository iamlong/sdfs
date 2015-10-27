#include "./storlistener.h"

storage_listener::storage_listener(command_pusher pusher, std::string ip, int port){

	m_pusher = pusher;
	m_ip = ip;
	m_port = port;
	return;
}

void storage_listener::listener(command_pusher pusher, std::string ip, int port){
	
	int udpsock = networkhelper::CreatelistenOnUDPv4(ip, port);
	
	if(udpsock== -1)
		return;

	for(;;){

		//receive command from udp port
		//add command to command_pusher
	}



}

bool storage_listener::start(){
	
	try {
		m_listener = new thread (listener, m_pusher, m_ip, m_port);
	}catch(...){
		cerr<<"fail to create thread to start listener\n";
		return false;
	}

	return true;
}

