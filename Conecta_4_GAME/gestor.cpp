#include "Gestor.h"

void generarAccesos(tGestor & gestor){
	int indice=0;
	tParIdEn partAux;
	for(int j=0; j < gestor.listaUsuarios.contador; j++){
		iniciar(gestor.listaUsuarios.LisUsu[j].lista);
	}
	for(int i=0; i < gestor.listaPartidas.contador; i++){

		if(gestor.listaPartidas.lisPar[i].estadoPartida == enCurso){
			partAux.pos = i;
			partAux.idPartida = gestor.listaPartidas.lisPar[i].identificador;
			indice=0;
			if(buscarUsuario(gestor.listaUsuarios,gestor.listaPartidas.lisPar[i].id1,indice)){
				insertarPartidaAP(gestor.listaUsuarios.LisUsu[indice].lista,partAux);
			}
			if(buscarUsuario(gestor.listaUsuarios,gestor.listaPartidas.lisPar[i].id2,indice)){
				insertarPartidaAP(gestor.listaUsuarios.LisUsu[indice].lista,partAux);
			}
		}		
	}
}

bool iniciarSesionG(tGestor &gestor, string const &idUsu, string const &clave){
	bool iniciada = false, repetir = false;
	int pos = 0;
	if (buscarUsuario(gestor.listaUsuarios, idUsu, pos)){
		if (!iniSesionUsuario(gestor.listaUsuarios.LisUsu[pos], clave))		cout << "Contraseña incorrecta. " << endl << endl;
		else{
			gestor.posUsuario = pos;
			iniciada = true;
		}
	}
	else	cout << "Este usuario no existe. " << endl;
	return iniciada;
}

bool crearCuentaG(tGestor &gestor,string const &idUsu,string const&clave){
	bool creado = false;
	int ultimaPos,aux;
	if(!buscarUsuario(gestor.listaUsuarios, idUsu, aux)){  
		ultimaPos = gestor.listaUsuarios.contador;
		iniciar(gestor.listaUsuarios.LisUsu[ultimaPos], idUsu, clave);
		insertar(gestor.listaUsuarios, gestor.listaUsuarios.LisUsu[ultimaPos], aux);
		cout << "El usuario se ha creado correctamente" << endl;
		creado = true;
	}
	else cout << "Error, el usuario ya existe" << endl;

	return creado;
}

string resumenActividad(tGestor const &gestor)
{
	return resumenUsuario(gestor.listaUsuarios.LisUsu[gestor.posUsuario]);
}

bool arrancar(tGestor &gestor)
{
	bool arrancado = false;
	ifstream archivo;
	archivo.open("partidas.txt");
	archivo >> gestor.listaPartidas.contador;
	if (cargar(gestor.listaPartidas, archivo))
	{
		archivo.close();
		archivo.open("usuarios.txt");
		archivo >> gestor.listaUsuarios.contador;
		if (cargar(gestor.listaUsuarios, archivo))
		{ 
			archivo.close();
			/*gestor.listaAccesos.contador = 0;*/
			arrancado = true;
			generarAccesos(gestor);
		}
	}
	return arrancado;
}

void apagar(tGestor &gestor)
{
	ofstream archivo;
	archivo.open("usuarios.txt");
	guardar(gestor.listaUsuarios, archivo);
	archivo.close();
	archivo.open("partidas.txt");
	guardar(gestor.listaPartidas, archivo);
	archivo.close();
}

int partidasUsuario(tGestor const& gestor)
{
	return gestor.listaUsuarios.LisUsu[gestor.posUsuario].lista.contador;
}

void apuntarPartida(tGestor &gestor, int posParEnCurso){

	gestor.accPar = gestor.listaUsuarios.LisUsu[gestor.posUsuario].lista.listaAccesoPartidas[posParEnCurso - 1].pos;
}
string cabecera(tGestor const &gestor, int posEncurso){

	ostringstream flujo;
	flujo << "# T    " << "Jugador1" << setw(31) << "Jugador2" << setw(15) << "Fecha" << endl;
	flujo << "---------------------------------------------------------------------" << endl;
	for (int i = 0; i < partidasUsuario(gestor); i++){
		flujo << cabeceraPartida(gestor.listaPartidas.lisPar[gestor.listaUsuarios.LisUsu[gestor.posUsuario].lista.listaAccesoPartidas[i].pos], i, gestor.listaUsuarios.LisUsu[gestor.posUsuario].id);
	}
	return flujo.str();
}
//
//bool comprobarUsu(tGestor gestor,int i,int &indice){
//	return gestor.listaPartidas.lisPar[i].id1 == gestor.listaUsuarios.LisUsu[indice].id || gestor.listaPartidas.lisPar[i].id2 == gestor.listaUsuarios.LisUsu[indice].id;
//}
bool tieneAvisos(tGestor const &gestor, string &aviso){
	bool tiene=false;
	if(gestor.listaUsuarios.LisUsu[gestor.posUsuario].avisos != ""){
		aviso=gestor.listaUsuarios.LisUsu[gestor.posUsuario].avisos;
		tiene=true;
	}
	return tiene;
}
void cambiarEstadoUsu(tGestor & gestor){
	if(!gestor.listaUsuarios.LisUsu[gestor.posUsuario].estadoJugador){
		gestor.listaUsuarios.LisUsu[gestor.posUsuario].estadoJugador=true;
	}
}
void mostrarPartida(tGestor &gestor)
{
	string jugador1,jugador2;
	jugador1=gestor.listaPartidas.lisPar[gestor.accPar].id1;
	jugador2=gestor.listaPartidas.lisPar[gestor.accPar].id2;
	mostrar(gestor.listaPartidas.lisPar[gestor.accPar].conecta,jugador1, jugador2);
}

bool esSuTurno(tGestor const &gestor){
	bool turnoActual = false;
	tTurno turno;

	if (gestor.listaPartidas.lisPar[gestor.accPar].id1 == gestor.listaUsuarios.LisUsu[gestor.posUsuario].id){
		turno = Jugador1;
	}
	else {
		turno = Jugador2;
	}
	if (gestor.listaPartidas.lisPar[gestor.accPar].conecta.turno == turno){
		turnoActual = true;
	}
	return turnoActual;
}
void errorCrearPartida(tGestor &gestor,bool ok){
	if(!ok){
		if(llena(gestor.listaUsuarios.LisUsu[gestor.posUsuario].lista)){
			cout<<"\n\nError: La lista de Accesos esta llena..\n\n";
		}
		else if(gestor.listaPartidas.contador >= MAXPART){
			cout<<"\n\nError: La lista de partidas esta llena..\n\n";
		}
		else{
			cout<<"Error: No hay usuarios disponibles\n";
			cout<<"Has sido añadido a la lista de espera\n\n";
		}

	}
	else{
		cout<<"Partida creada correctamente ....\n";

	}
}
void crearNueva(tGestor &gestor,bool &ok,int &posPartida,int &posUsuario){
	tParIdEn lista;
	tPartida partida;
	nueva(partida, gestor.listaUsuarios.LisUsu[gestor.posUsuario].id,gestor.listaUsuarios.LisUsu[posUsuario].id);
	if(insertarPartida(gestor.listaPartidas,partida,posPartida)){
		lista.idPartida=partida.identificador;
		lista.pos=posPartida;
		if(gestor.listaUsuarios.LisUsu[posUsuario].lista.contador<MAX_PAR_US){
			if(nuevaPartidaUsuario(gestor.listaUsuarios.LisUsu[gestor.posUsuario],lista)){
				ok=true;
			}
		}
	}

}
void buscarYcrear(tGestor & gestor,bool &ok){
	int posUsuario=0,posPartida=0;
	if(buscarUsuarioEsperando(gestor.listaUsuarios,gestor.listaUsuarios.LisUsu[gestor.posUsuario].nivel,posUsuario)){
		if(gestor.listaUsuarios.LisUsu[posUsuario].id != gestor.listaUsuarios.LisUsu[gestor.posUsuario].id){
			crearNueva(gestor,ok,posPartida,posUsuario);
		}
		else{
			posUsuario++;
			if(buscarUsuarioEsperando(gestor.listaUsuarios,gestor.listaUsuarios.LisUsu[gestor.posUsuario].nivel,posUsuario)){
				crearNueva(gestor,ok,posPartida,posUsuario);
			}
		}
	}
}
bool nuevaPartidaG(tGestor &gestor){
	bool ok=false;
	if(!llena(gestor.listaUsuarios.LisUsu[gestor.posUsuario].lista) && gestor.listaPartidas.contador < MAXPART){
		cambiarEstadoUsu(gestor);
		buscarYcrear(gestor,ok);
	}
	errorCrearPartida( gestor,ok);
	return ok;
}
void mostrarPartida(tGestor const &gestor){
	string jugador1,jugador2;
	jugador1=gestor.listaPartidas.lisPar[gestor.accPar].id1;
	jugador2=gestor.listaPartidas.lisPar[gestor.accPar].id2;
	mostrar(gestor.listaPartidas.lisPar[gestor.accPar].conecta,jugador1,jugador2);
}
void jugarPartida(tGestor &gestor,int col){
	aplicarJugada(gestor.listaPartidas.lisPar[gestor.accPar],col-1);
	mostrar(gestor.listaPartidas.lisPar[gestor.accPar].conecta,gestor.listaPartidas.lisPar[gestor.accPar].id1,gestor.listaPartidas.lisPar[gestor.accPar].id2);
}
int posicionJugadorAct(tGestor gestor){
	int pos=0;
	if(gestor.listaPartidas.lisPar[gestor.accPar].id1==gestor.listaUsuarios.LisUsu[gestor.posUsuario].id){
		buscarUsuario(gestor.listaUsuarios,gestor.listaPartidas.lisPar[gestor.accPar].id2,pos);
	}
	else{
		buscarUsuario(gestor.listaUsuarios,gestor.listaPartidas.lisPar[gestor.accPar].id1,pos);
	}

	return pos;
}
void abandonarPartida(tGestor &gestor,ostringstream &aviso){
	int pos=0;
	bool ok=false;
	pos=posicionJugadorAct(gestor);
	abandonar(gestor.listaPartidas.lisPar[gestor.accPar]);
	aviso<<"Has ganado una partida por abandono contra "
		<< gestor.listaUsuarios.LisUsu[gestor.posUsuario].id<<" el "
		<< stringFecha( gestor.listaPartidas.lisPar[gestor.accPar].actualizacion,ok)
		<<endl;
	actualizarAvisos(gestor.listaUsuarios.LisUsu[pos],aviso.str());
	elimSum(gestor);
}
bool comprobarGanadores(tGestor &gestor,int &pos,ostringstream &aviso){
	bool ok=false;
	pos = posicionJugadorAct(gestor);
	if(gestor.listaPartidas.lisPar[gestor.accPar].conecta.estado==Ganador||gestor.listaPartidas.lisPar[gestor.accPar].conecta.estado==Bloqueo){
		ok=true;
		if (gestor.listaPartidas.lisPar[gestor.accPar].conecta.estado == Bloqueo){
			aviso << "Has empatado la partida contra " << gestor.listaUsuarios.LisUsu[gestor.posUsuario].id << " el " << stringFecha(fechaActual(), ok)<< endl;
		}
		else if (gestor.listaPartidas.lisPar[gestor.posUsuario].conecta.estado == Ganador){
			aviso << "Has perdido la partida contra " << gestor.listaUsuarios.LisUsu[gestor.posUsuario].id << " a fecha de " << stringFecha(fechaActual(), ok)<<endl;
		}
		elimSum(gestor);
	}
	return ok;
}
void elimSum(tGestor &gestor){
	int pos=0;
	pos = posicionJugadorAct(gestor);
	eliminar(gestor.listaUsuarios.LisUsu[gestor.posUsuario].lista, gestor.listaPartidas.lisPar[gestor.accPar].identificador);
	eliminar(gestor.listaUsuarios.LisUsu[pos].lista, gestor.listaPartidas.lisPar[gestor.accPar].identificador);
	aplicarFinPartida(gestor.listaUsuarios.LisUsu[gestor.posUsuario], gestor.listaPartidas.lisPar[gestor.posUsuario].identificador, gestor.listaPartidas.lisPar[gestor.accPar].conecta.estado);
	aplicarFinPartidaPerdedor(gestor,pos);
	gestor.listaPartidas.lisPar[gestor.accPar].estadoPartida=terminada;
}
void aplicarFinPartidaPerdedor(tGestor &gestor,int pos){
	if( gestor.listaPartidas.lisPar[gestor.accPar].conecta.estado){
		gestor.listaUsuarios.LisUsu[pos].perdidas++;
		gestor.listaUsuarios.LisUsu[pos].ultimaRacha--;
		controlNiveles(gestor.listaUsuarios.LisUsu[pos]);
	}
}
void ordenar_Fecha(tGestor  &gestor){
	int j=0;
	tFecha elemento;
	tPartida partida;
	for (int i = 1; i < gestor.listaUsuarios.LisUsu[gestor.posUsuario].lista.contador; i++){
		j = i;
		partida = gestor.listaPartidas.lisPar[gestor.listaUsuarios.LisUsu[gestor.posUsuario].lista.listaAccesoPartidas[i].pos];
		elemento = partida.actualizacion;
		while ((j > 0) && (elemento < gestor.listaPartidas.lisPar[gestor.listaUsuarios.LisUsu[gestor.posUsuario].lista.listaAccesoPartidas[j-1].pos].actualizacion)){
			gestor.listaPartidas.lisPar[gestor.listaUsuarios.LisUsu[gestor.posUsuario].lista.listaAccesoPartidas[j].pos]=gestor.listaPartidas.lisPar[gestor.listaUsuarios.LisUsu[gestor.posUsuario].lista.listaAccesoPartidas[j-1].pos];
			j--;
		}
		gestor.listaPartidas.lisPar[gestor.listaUsuarios.LisUsu[gestor.posUsuario].lista.listaAccesoPartidas[j].pos]= partida;
	}
}
void ordenar_Turno(tGestor &gestor){
	int j=0;
	tPartida part1, part2;
	for (int i = 1; i < gestor.listaUsuarios.LisUsu[gestor.posUsuario].lista.contador; i++){
		j = i;
		part1 = gestor.listaPartidas.lisPar[gestor.listaUsuarios.LisUsu[gestor.posUsuario].lista.listaAccesoPartidas[j - 1].pos];
		part2 = gestor.listaPartidas.lisPar[gestor.listaUsuarios.LisUsu[gestor.posUsuario].lista.listaAccesoPartidas[i].pos];
		while ((j > 0) && compararTurno(gestor,part1,part2)){	
			gestor.listaPartidas.lisPar[gestor.listaUsuarios.LisUsu[gestor.posUsuario].lista.listaAccesoPartidas[j].pos] = gestor.listaPartidas.lisPar[gestor.listaUsuarios.LisUsu[gestor.posUsuario].lista.listaAccesoPartidas[j - 1].pos];
			--j;
		}
		gestor.listaPartidas.lisPar[gestor.listaUsuarios.LisUsu[gestor.posUsuario].lista.listaAccesoPartidas[j].pos] = part2;
	}
}
bool compararTurno(tGestor gestor, tPartida par1, tPartida par2){
	bool ok=false;
	if (!asterisco(par1, gestor.listaUsuarios.LisUsu[gestor.posUsuario].id) && asterisco(par2, gestor.listaUsuarios.LisUsu[gestor.posUsuario].id)){
		ok=true;
	}
	else if (asterisco(par1, gestor.listaUsuarios.LisUsu[gestor.posUsuario].id) && asterisco(par2, gestor.listaUsuarios.LisUsu[gestor.posUsuario].id)){
		if (par1.actualizacion > par2.actualizacion){
			ok=true;
		}
	}
	return ok;
}
void limpiarAvisosG(tGestor &gestor){
	limpiarAvisos(gestor.listaUsuarios.LisUsu[gestor.posUsuario]);
}