#ifndef partida_h
#define partida_h
#include "Fecha.h"
#include "conecta4.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

typedef enum { enCurso, terminada }tEstadoPartida;

typedef struct{
	string identificador, id1, id2;
	tFecha fecha, actualizacion;
	tEstadoPartida estadoPartida;
	tConecta4 conecta;
}tPartida;

void abandonar(tPartida &partida); /*Se encarga de abandonar la partida, tiene como parametros de E/S el array de partida*/
void guardar(tPartida const&partida, ofstream & archivo);  /*Se encarga de guardar la partida, tiene como parametros de E/S el array de partida
														   y el archivo*/
bool cargar(tPartida &partida, ifstream &archivo);/*Se encarga de cargar la partida, tiene como parametros de E/S el array de partida
												  y el archivo*/
void nueva(tPartida &partida, string const &jugador1, string const &jugador2); /*Inicializa todos los datos de una nueva partida, tiene como
																			   parametros de E/S el array de partida y los dos jugadores*/
bool asterisco(tPartida const& partida, string jugador); 
string cabeceraPartida(tPartida const& partida, int posEnCurso, string jugador); /*Recorre y recoge las partidas en juego del usuario, tiene como
																				 parametros de E/S el array de aprtida, la posicion en cusro y el jugador*/
bool aplicarJugada(tPartida &partida, int col); /*Aplica la jugada elegida por el usuario, tiene como parametros de E/S el array de partida, 
												y de entrada la columna*/
#endif