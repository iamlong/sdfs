#include "./storlistener.h"

storage_listener::storage_listener(command_pusher pusher, storage_command_q * q, std::string ip, int port){

	m_pusher = pusher;
    m_q = q;
	m_ip = ip;
	m_port = port;
	return;
}

void storage_listener::listener(command_pusher pusher, storage_command_q * q, std::string ip, int port){
	
	int udpsock = networkhelper::CreateUDPv4(ip, port);
	
	sd_uint32_t buffsize = 1024*5;
	sd_uint8_t * buff = (sd_uint8_t *)malloc(buffsize);
	bzero(buff, buffsize);
	sd_uint32_t recved;
    
    cout<<"start listening\n, port creaded: fd="<<udpsock<<"\n";
	struct sockaddr reqaddr;
	int addr_len=sizeof(reqaddr);

	if(udpsock== -1)
		return;
	
	storage_command * cmd = new storage_command(1024*4); //max cmd buffsize = 4k;
	for(;;){

		//receive command from udp port
		//add command to command_pusher
		recved = recvfrom(udpsock, buff, buffsize, 0, &reqaddr, (socklen_t *)&addr_len);
        cout<<"received:"<<recved<<"\n";
		DeSerializer cmdSerializer(buff, recved);
		if(!cmd->DeSerialize(&cmdSerializer))
		  continue;
		cout<<cmd->getCommand()<<"\n";
        pusher(q, cmd);
		cout<<"QueueSize:"<<q->QSize()<<"\n";
		cmd = new storage_command(1024*4);

	}



}

bool storage_listener::start(){
	
	try {
		m_listener = new thread (listener, m_pusher, m_q, m_ip, m_port);
	}catch(...){
		cerr<<"fail to create thread to start listener\n";
		return false;
	}

	return true;
}

thread* storage_listener::getThread(){
    return m_listener;
}
