/* Código adaptado do material do Professor Bruno Jefferson */

#ifndef INCLUDE_CONSUMIDOR_H_
#define INCLUDE_CONSUMIDOR_H_

#include <semaphore.h>
#include <thread>
#include "Produtor.h"
#include "sock.h"

class Produtor;

class Consumidor {
public:
	static const int BUFFER_SIZE = 1024;
	Consumidor(Produtor& p);
	virtual ~Consumidor();
	struct sockaddr_in cliente; 
	static std::vector<char*>& getBufferLimitado();
	static int servi; 
	int getFront();
	sem_t& getEmpty();
	sem_t& getFull();
	void start(int port);
	static std::vector<char*> bufferLimitado;

private:
	int front;
	sem_t full;
	sem_t empty;
	Produtor& produtor;
	std::thread *th_consumidor;

	void run();
};

#endif /* INCLUDE_CONSUMIDOR_H_ */
