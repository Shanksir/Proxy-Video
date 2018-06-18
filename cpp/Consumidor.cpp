/* Código adaptado do material do Professor Bruno Jefferson */

#include "/home/rodrigoalves/Documentos/UFPB/LP2/Projeto Final/Stream--vlc/include/Consumidor.h"

std::vector<char*> Consumidor::bufferLimitado(Consumidor::BUFFER_SIZE);
int Consumidor::servi;

Consumidor::Consumidor(Produtor& p) : produtor(p) {
	std::memset( &cliente, 0, sizeof(struct sockaddr_in));
	front = 0;
	th_consumidor = NULL;
	servi = p.returnSock();
}

Consumidor::~Consumidor() {
	// TODO Auto-generated destructor stub
}

int Consumidor::getFront() {
	return front;
}

sem_t& Consumidor::getEmpty() {
	return empty;
}

sem_t& Consumidor::getFull() {
	return full;
}

std::vector<char*>& Consumidor::getBufferLimitado() {
	return bufferLimitado;
}

void Consumidor::start(int port) {
	cliente.sin_family = AF_INET;
	cliente.sin_port = htons(port);
	cliente.sin_addr.s_addr = inet_addr("127.0.0.1");
	th_consumidor = new std::thread(&Consumidor::run, this);
}

void Consumidor::run() {
	front = produtor.getRear();
	sem_init(&empty, 0, Consumidor::BUFFER_SIZE);
	sem_init(&full, 0, 0);
	int lenght = sizeof(struct sockaddr_in);

	while (true) {
		sem_wait(&full);
		sendto(servi, bufferLimitado[front], 1316, 0, (struct sockaddr *) &cliente, lenght);
		front = (front + 1) % 1024;
		sem_post(&empty);
	}

	sem_destroy(&empty);
	sem_destroy(&full);
}
