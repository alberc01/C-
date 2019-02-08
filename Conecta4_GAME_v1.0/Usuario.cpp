#include "Usuario.h"
#include "Fecha.h"

void iniciar(tUsuario &usuario, string const &id, string const &pas){
	usuario.id = id;
	usuario.contrasenia = pas;
	usuario.nivel = Principiante;
	usuario.ultimaRacha = 0;
	usuario.estadoJugador = true;
	usuario.ganadas = 0;
	usuario.empatadas = 0;
	usuario.perdidas = 0;
	usuario.fecha = fechaActual();
	usuario.avisos = "";
}

void guardar(tUsuario const &usuario, ofstream &archivo)
{
	int elementos = 0;
	archivo << usuario.id << endl;
	archivo << usuario.contrasenia << endl;
	archivo << usuario.nivel << " " << usuario.ultimaRacha << " " << usuario.estadoJugador << endl;
	archivo << usuario.ganadas << " " << usuario.perdidas << " " << usuario.empatadas << endl;
	archivo << fechaActual() << endl;
	archivo << usuario.avisos << endl;
	archivo << CENTINELA << endl;
}

bool cargar(tUsuario &usuario, ifstream &archivo)
{
	int elemntos = 0, valor = 0;
	bool cargado = true;
	archivo >> usuario.id;
	archivo >> usuario.contrasenia;
	archivo >> valor;
	usuario.nivel = tNivel(valor);
	archivo >> usuario.ultimaRacha;
	archivo >> usuario.estadoJugador;
	archivo >> usuario.ganadas;
	archivo >> usuario.perdidas;
	archivo >> usuario.empatadas;
	archivo >> usuario.fecha;
	archivo >> usuario.avisos;
	usuario.avisos = leerAviso(usuario, archivo);
	return  cargado;
}

string leerAviso(tUsuario &usuario, ifstream &archivo)
{
	string linea;
	ostringstream flujo;
	linea = usuario.avisos;
	while (linea != CENTINELA){
		flujo << linea;
		flujo << " ";
		archivo >> linea;
	}
	usuario.avisos = flujo.str();
	return flujo.str();
}
void mostrarUsu(tUsuario usuario)
{
	cout << usuario.id << endl;
	cout << usuario.contrasenia << endl;
	cout << usuario.nivel << " " << usuario.ultimaRacha << " " << usuario.estadoJugador << endl;
	cout << usuario.ganadas << " " << usuario.empatadas << " " << usuario.perdidas << endl;
	cout << usuario.fecha << endl;
	cout << usuario.avisos << endl << endl;
}
void  actualizarAvisos(tUsuario &usuario, string const &aviso)
{
	if(usuario.avisos!=""){
		usuario.avisos +="\n"+ aviso;
	}
	else{
		usuario.avisos = aviso;
	}
}

bool iniSesionUsuario(tUsuario & usuario, string const& clave)
{
	bool valida = false;
	if (clave == usuario.contrasenia)
	{
		valida = true;
		usuario.fecha = fechaActual();
	}
	return valida;
}
void limpiarAvisos(tUsuario &usuario)
{
	usuario.avisos = "";
}
string resumenUsuario(tUsuario const &usuario){
	stringstream flujo;
	flujo << "Resumen de la actividad" << endl;
	flujo << "Partidas Ganadas: " << usuario.ganadas << endl;
	flujo << "Partidas Perdidas: " << usuario.perdidas << endl;
	flujo << "Partidas Empatadas: " <<usuario.empatadas << endl;
	flujo << "Nivel actual: " << nivelInfo(usuario);
	flujo << "Racha actual: " << usuario.ultimaRacha << endl;
	return flujo.str();
}
string nivelInfo(tUsuario const &usuario){
	stringstream flujo;
	if(usuario.nivel==Principiante){
		flujo<< "Principiante. " << endl;
	}
	else if(usuario.nivel==Medio){
		flujo<<"Medio."<<endl;
	}
	else{
		flujo<<"Experto."<<endl;
	}
	return flujo.str();

}
void aplicarFinPartida(tUsuario &usuario/*,string idPar*/,tResultado resultado ){
	if(resultado==Gana){
		usuario.ganadas++;
		usuario.ultimaRacha++;
	}
	else if (resultado==Empata){
		usuario.empatadas++;
		usuario.ultimaRacha=0;
	}
	else if(resultado=Pierde){
		usuario.perdidas++;
		usuario.ultimaRacha--;
	}
	controlNiveles(usuario);
}
void controlNiveles(tUsuario &usuario){
	if(usuario.ultimaRacha == -NRN){
		if(usuario.nivel= Experto){
			usuario.nivel=Medio;
		}
		else if(usuario.nivel=Medio){
			usuario.nivel=Principiante;
		}
	}
	else if(usuario.ultimaRacha==NRN) {
		if(usuario.nivel=Medio){
			usuario.nivel=Experto;
		}
		else if(usuario.nivel=Principiante){
			usuario.nivel=Medio;
		}
	}
}
bool nuevaPartidaUsuario(tUsuario &usuario){
	bool nueva=false;
	usuario.estadoJugador = false;
	nueva = true;
	return nueva;
}