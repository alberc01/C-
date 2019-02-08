#include "partidas.h"

void guardar(tPartida const&partida, ofstream & archivo) 
{
	int elementos = 0, valor = 0;
	archivo << partida.identificador << endl;
	archivo << partida.id1 << endl;
	archivo << partida.id2 << endl;
	archivo << partida.fecha << " " << partida.actualizacion << endl;
	archivo << partida.estadoPartida << endl;
	guardar(partida.conecta, archivo);
}

bool cargar(tPartida &partida, ifstream &archivo)
{
	bool cargado = true;
	int  valor = 0;
	archivo >> partida.identificador;
	archivo >> partida.id1;
	archivo >> partida.id2;
	archivo >> partida.fecha;
	archivo >> partida.actualizacion;
	archivo >> valor;
	partida.estadoPartida = tEstadoPartida(valor);
	if (cargar(partida.conecta, archivo)) cargado = true;

	return cargado;
}

void nueva(tPartida &partida, string const &jugador1, string const &jugador2)
{
	int elementos = 0;
	string resultado;
	ostringstream flujo;
	flujo << fechaActual() << "_" << jugador1 << "_" << jugador2;
	partida.identificador = flujo.str();
	partida.id1 = jugador1;
	partida.id2 = jugador2;
	partida.fecha = fechaActual();
	partida.actualizacion = fechaActual();
	partida.estadoPartida = enCurso;
	iniciar(partida.conecta);
}
void abandonar(tPartida &partida){
	partida.estadoPartida=terminada;
	partida.fecha=fechaActual();
	partida.actualizacion=partida.fecha;
}
bool aplicarJugada(tPartida &partida,int col)
{
	bool ok=false;
	if(aplicarJugada(partida.conecta,col)){
		partida.estadoPartida=enCurso;
		partida.fecha=fechaActual();
		ok=true;
	}
	return ok;
}

bool asterisco(tPartida const& partida, string jugador)
{
	bool ast = false;
	if (partida.conecta.turno == Jugador1 && partida.id1 == jugador){
		ast = true;
	}
	else if (partida.conecta.turno == Jugador2 && partida.id2 == jugador){
		ast = true;
	}
	return ast;
}

string cabeceraPartida(tPartida const& partida, int posEnCurso, string jugador){
	tFecha fecha = partida.fecha;
	bool hora = true, ast = asterisco(partida, jugador);
	string tun = " ";
	ostringstream flujo;
	string cabecera;
	if (ast) tun = "*";
	flujo << posEnCurso + 1 << " " << tun << setw(10) << partida.id1 << setw(30) << partida.id2 << setw(34) << stringFecha(partida.actualizacion, hora) << endl;

	return flujo.str();
}