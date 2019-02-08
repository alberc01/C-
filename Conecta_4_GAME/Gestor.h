#ifndef gestor_h
#define gestor_h
#include <iostream>
#include <string>
#include <fstream>
#include "listaUsuarios.h"
#include "listaPartidas.h"

using namespace std;

typedef struct{
	tListaPartidas listaPartidas;
	tListaUsuarios listaUsuarios;
	int posUsuario;
	int accPar;
	//tListaAccesoPartidas listaAccesos;
}tGestor;
void buscarYcrear(tGestor  &gestor, bool &ok); /*Se encarga de buscar una partida y crearla, tiene como parametros de E/S al gestor y un booleano*/
bool tieneAvisos(tGestor const &gestor, string &aviso); /*Se encarga de comprobar si el Usuario tiene avisos, tiene por parametros de entrada
														y salida el gestor, y los avisos*/
void crearNueva(tGestor  &gestor, bool &ok, int &posPartida, int &posUsuario);/*Se ecncarga de crear una nueva partida, tiene por parametros de 
																			  entrada y salida al gestor, un booleano, la posicion de la partida y la posicion del usuario*/
bool compararTurno(tGestor gestor, tPartida par1, tPartida par2);/*Se encarga de comparar los turnos para ver a quien le toca jugar, tiene
																 por parametros de entrada al gestor, y dos arrays de tPartida*/
void ordenar_Turno(tGestor  &gestor);/*Se encarga de ordenar las partidas por turno y fecha, tiene por parametros de entrada y salida al gestor*/
void ordenar_Fecha(tGestor  &gestor); /*Se encarga de ordenar las partidas por ultima actualizacion, tiene por parametros de entrada y salida
									  al gestor*/
void aplicarFinPartidaPerdedor(tGestor  &gestor,int pos);/*Actualiza las rachas y controla los niveles, tiene por parametros de entrada y salida al gestor,
														 y de entrada la posicion*/
bool comprobarGanadores(tGestor &gestor, int &pos, ostringstream &aviso);/*Comprueba y muestra quien ha sido el ganador, tiene por parametros
																		 de entrada y salida el gestor, la posicion y un ostringstream de aviso*/
void elimSum(tGestor &gestor);/*Elimina partidas y suma rachas, tiene como parametros de entrada y salida al gestor*/
/*bool comprobarUsu(tGestor gestor, int i, int &indice);*//*Se encarga de comrpobar a los usuarios, tiene como parametros de entrada al gestor, 
													  una posicion, y como entrada y salida al indice*/
void jugarPartida(tGestor &gestor, int col); /*Se encarga de jugar la partida, tiene como parametros de entrada y salida al gestor, y de entrada
											 la columna*/
void abandonarPartida(tGestor &gestor, ostringstream &aviso); /*Gestiona el abandono de una partida, tiene como parametros de entrada y salida
															  el gestro y un ostringstream de aviso*/
bool nuevaPartidaG(tGestor &gestor); /*Se encarga de comprobar si puede crear cuenta o no, tiene como parametros de entrada y salida al gestor */
void cambiarEstadoUsu(tGestor &gestor); /*Se encarga de cambiar el estado si ha encontraod partida o no, tiene como parametros de entrada y salida
										al gestor*/
void errorCrearPartida(tGestor &gestor, bool ok); /*Muestra error si no se ha podido crear cuenta, tiene como parametros de entrada y salida
												  al gestor, y de entrada un booleano*/
string resumenActividad(tGestor const &gestor); /*Muestra los datos de cada usuario, tiene como parametros de entrada y salida al gestor */
string cabecera(tGestor const &gestor, int posEncurso); /*Muestra las partidas del usuario, tiene como parametros de entrada y salida al gestor,
														y de entrada la posicion en curso*/
bool arrancar(tGestor &gestor); /*Recorre las listas de usuarios y partidas, tiene como parametros de E/S al gestor*/
bool iniciarSesionG(tGestor &gestor, string const &idUsu, string const &clave); /*Comprueba e inicia sesion, tiene como parametros de E/S al 
																				gestor, el id del usuario y la contraseña*/
bool crearCuentaG(tGestor &gestor, string const &idUsu, string const&clave); /*Comprueba y crea una cuenta nueva, tiene como parametros de E/S al
																			 gestor al id del usuario y la clave*/
void generarAccesos(tGestor & gestor); /*Recorre e inserta la lista de partidas, tiene como parametros de E/S al gestor*/
void apagar(tGestor &gestor); /*Guarda las listas, tiene como parametros de E/S al gestor*/
void apuntarPartida(tGestor &gestor, int posParEnCurso); /*Apunta la partida que el usuario quiere ver, tiene como parametro s de E/S al gestor,
														 y de entrada la posicion de la partida en curso*/
bool esSuTurno(tGestor const &gestor); /*Comprueba de quien es el turno, tiene como parametros de E/S al gestor*/
void mostrarPartida(tGestor &gestor); /*Muestra una partida, tiene como parametros de E/S al gestor*/
void limpiarAvisosG(tGestor &gestor);
int partidasUsuario(tGestor const& gestor);
#endif