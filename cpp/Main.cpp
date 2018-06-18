#include <iostream>
#include "/home/rodrigoalves/Documentos/UFPB/LP2/Projeto Final/Stream--vlc/include/proj.h"
#include <unistd.h>
using namespace std;

int main() {
	
	
	Produtor *produz = new Produtor; /* Criando o PRODUTOR */
	Consumidor *consome = new Consumidor( *produz ); /* Criando o CONSUMIDOR */
	produz->addConsumidor( consome ); /* Adicionando o CONSUMIDOR */ 
	consome->start(1234); /* Iniciar o CONSUMIDOR */
	produz->start(); /* Iniciar o PRODUTOR */
	
	Consumidor *consome2 = new Consumidor( *produz );    /* Segundo Cliente */
	produz->addConsumidor( consome2 );
	consome2->start(2345);
	
	Consumidor *consome3 = new Consumidor( *produz );   /* Terceiro Cliente */
	produz->addConsumidor( consome3 );
	consome3->start(3456);
	
	sleep(200000);

	return 0;
}
