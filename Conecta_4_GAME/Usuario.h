#ifndef usuario_h
#define usuario_h
#include "fecha.h"
#include "listaPartidas.h"
#include "listaAccesoPartidas.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

const string CENTINELA = "_X_X_X_";
const int NRN = 3;

typedef enum { Principiante, Medio, Experto }tNivel;
typedef enum { Gana, Pierde, Empata }tResultado;

typedef struct{
	string id;
	string contrasenia;
	tNivel nivel;
	int ultimaRacha;
	bool estadoJugador;
	int ganadas, perdidas, empatadas;
	tFecha fecha;
	string avisos; // se van concatenando
	tListaAccesoPartidas lista;
}tUsuario;
void controlNiveles(tUsuario &usuario);
void aplicarFinPartida(tUsuario &usuario,string idPar,tEstado estado );
string nivelInfo(tUsuario const &usuario);
string resumenUsuario(tUsuario const &usuario);
void iniciar(tUsuario &usuario, string const &id, string const &pas);
void guardar(tUsuario const &usuario, ofstream &archivo);
bool cargar(tUsuario &usuario, ifstream &archivo);
void mostrarUsu(tUsuario usuario);
void  actualizarAvisos(tUsuario &usuario, string const &aviso);
string leerAviso(tUsuario &usuario, ifstream &archivo);
bool iniSesionUsuario(tUsuario & usuario, string const& clave);
void limpiarAvisos(tUsuario &usuario);

bool nuevaPartidaUsuario(tUsuario &usuario, tParIdEn const &list);
#endif