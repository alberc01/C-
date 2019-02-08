#ifndef listaAccesoPartido_h
#define listaAccesoPartido_h
#include <iostream>
#include <string>
#include "partidas.h"
using namespace std;

const int MAX_PAR_US = 3;

//typedef struct{
//	string idPartida;
//	int pos;
//}tParIdEn;

typedef struct{
	tPartida *listaAccesoPartidas[MAX_PAR_US];
	int contador;
}tListaAccesoPartidas;
bool llena(tListaAccesoPartidas const&lista); /*Se encarga de devolver true si la lista de accesos esta llena*/
bool eliminar(tListaAccesoPartidas &lista, string const &id); /*Se encarga de eliminar la partida, tiene como parametros de E/S una lista, y un id*/
bool insertarPartidaAP(tListaAccesoPartidas &lista, tPartida &par);/*Se encarga de insertar la partida, tiene como parametros de E/S el array de lista,
																  y de entrada el array par*/
void iniciar(tListaAccesoPartidas &lista); /*Inicia la lista, tiene por parametros de E/S la lista*/
bool buscarSinOrden(tListaAccesoPartidas &lista, string buscado, int &pos); /*Busca un usuarios, tiene como parametros de E/S la lista y una 
																			posicion y de entrada tiene un string*/
bool eliminarAux(tListaAccesoPartidas &lista, int pos); /*Funcion secundaria de eliminar, tiene como parametros de E/S la lista, y de entrada la
														posicion*/
#endif