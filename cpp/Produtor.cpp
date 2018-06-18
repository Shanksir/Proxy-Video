/* Código adaptado do material do Professor Bruno Jefferson */

#include "/home/rodrigoalves/Documentos/UFPB/LP2/Projeto Final/Stream--vlc/include/Produtor.h"

Produtor::Produtor() {
	rear = 0;
	servid = socket( AF_INET, SOCK_DGRAM, 0 );
	std::memset( &servaddr, 0, sizeof(struct sockaddr_in) );
	servaddr.sin_family = AF_INET ; /* Informa que o protocolo é do tipo IPv4 */
    servaddr.sin_port = htons( 4000 ); /* Convertendo a porta */
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); /* Setando o IP como LOCAL HOST */
	lenght = sizeof( servaddr );
	bind ( servid, ( struct sockaddr* ) &servaddr, sizeof( servaddr )  );
	th_produtor = NULL;

	for (int i = 0; i <= Consumidor::BUFFER_SIZE; i++){
		Consumidor::getBufferLimitado()[i] = new char[1316];
	}
}

Produtor::~Produtor() {
	// TODO Auto-generated destructor stub
}

int Produtor::getRear() {
	return rear;
}

void Produtor::addConsumidor(Consumidor *c) {
	consumidores.push_back(c);
}

void Produtor::start() {
	th_produtor = new std::thread(&Produtor::run, this);
}
int Produtor::returnSock()
{
	return servid;
}

sem_t& Produtor::rcontrol(){
	return controller;
}

void Produtor::run() {
	while (true) {
		for (int i = 0; i < consumidores.size(); i++)
		sem_wait(&consumidores[i]->getEmpty()); /*Decrementa*/
		
		nBytes = recvfrom (servid, Consumidor::bufferLimitado[rear], 1316, 0, (struct sockaddr*) &servaddr, &lenght);
		rear = (rear + 1) % 1024;
		
		if( nBytes < 0 )
			throw std::runtime_error ("cant recfrom");			
		
		for (int i = 0; i < consumidores.size(); i++)
			sem_post(&consumidores[i]->getFull()); /*Incrementa*/
	}
}

