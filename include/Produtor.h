/* Código adaptado do material do Professor Bruno Jefferson */

#ifndef INCLUDE_PRODUTOR_H_
#define INCLUDE_PRODUTOR_H_

#include <vector>
#include <semaphore.h>
#include <thread>
#include "Consumidor.h"
#include "sock.h"

class Consumidor;

class Produtor {
public:
	Produtor();
	virtual ~Produtor();
	int returnSock();
	int getRear();
	void addConsumidor(Consumidor *c);
	void start();
	sem_t& rcontrol();

private:
	int rear;
	socklen_t lenght;
	sem_t controller;
	int nBytes, servid;
	struct sockaddr_in servaddr;
	std::vector<Consumidor*> consumidores;
	std::thread *th_produtor;

	void run();
};

#endif /* INCLUDE_PRODUTOR_H_ */
