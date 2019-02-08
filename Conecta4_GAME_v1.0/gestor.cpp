#include "Gestor.h"
//1
void inactividad(tGestor &gestor){
	tFecha fecha;
	ostringstream aviso;

	bool ok=false;
	int pos1,pos2;
	for(int i=0;i< gestor.listaPartidas.contador;i++){
		fecha=fechaActual();
		fecha= fecha-gestor.listaPartidas.lisPar[i]->actualizacion;
		if(fecha > MES_SEG ){
			gestor.listaPartidas.lisPar[i]->conecta.estado=Ganador;
			gestor.listaPartidas.lisPar[i]->estadoPartida=terminada;
			gestor.dirPartida=gestor.listaPartidas.lisPar[i];
			buscarPosJugadores(gestor,pos1,pos2,i);
			gestor.posUsuario=pos1;
			if(esSuTurno(gestor)){
				aplicarFinPartida(gestor.listaUsuarios.LisUsu[pos2],Gana);
				aplicarFinPartida(gestor.listaUsuarios.LisUsu[pos1],Pierde);
				aviso << "Has perdido la partida contra " << gestor.listaUsuarios.LisUsu[pos2].id <<" Por inactividad  a fecha de " << stringFecha(fechaActual(), ok)<<endl;
				actualizarAvisos(gestor.listaUsuarios.LisUsu[gestor.posUsuario],aviso.str());
			}
			else{
				aplicarFinPartida(gestor.listaUsuarios.LisUsu[pos1],Gana);
				aplicarFinPartida(gestor.listaUsuarios.LisUsu[pos2],Pierde);
				aviso << "Has perdido la partida contra " << gestor.listaUsuarios.LisUsu[gestor.posUsuario].id <<" Por inactividad a fecha de " << stringFecha(fechaActual(), ok)<<endl;
				actualizarAvisos(gestor.listaUsuarios.LisUsu[pos2],aviso.str());
			}
		}
		aviso.str("");
	}
}
void buscarPosJugadores(tGestor gestor,int &pos1, int &pos2, int &i){
	buscarUsuario(gestor.listaUsuarios,gestor.listaPartidas.lisPar[i]->id1,pos1);
	buscarUsuario(gestor.listaUsuarios,gestor.listaPartidas.lisPar[i]->id2,pos2);
}
//void generarAccesos(tGestor & gestor){
//	int indice=0;
//	tPartida partAux;
//	iniciar(gestor.listaAccesos);
//	for(int i=0; i < gestor.listaPartidas.contador; i++){
//		if(comprobarUsu(gestor, i, indice)){
//			/*partAux. = i;*/
//			//partAux.identificador = gestor.listaPartidas.lisPar[i]->identificador;
//			if(gestor.listaPartidas.lisPar[i]->estadoPartida == enCurso){
//				insertarPartidaAP(gestor.listaAccesos,*gestor.listaPartidas.lisPar[i]);
//			}
//		}
//	}
//}
void generarAccesos(tGestor & gestor){
	int indice = 0;
	tPartida  partAux;
	for (int i = 0; i < gestor.listaPartidas.contador; i++){
		if (gestor.listaPartidas.lisPar[i]->estadoPartida == enCurso){
			if (gestor.listaPartidas.lisPar[i]->id1==gestor.listaUsuarios.LisUsu[gestor.posUsuario].id ||gestor.listaPartidas.lisPar[i]->id2==gestor.listaUsuarios.LisUsu[gestor.posUsuario].id ){
				/*insertarPartidaAP(gestor.listaAccesos,*gestor.listaPartidas.lisPar[i]);*/
				gestor.listaAccesos.listaAccesoPartidas[gestor.listaAccesos.contador]=gestor.listaPartidas.lisPar[i];
				gestor.listaAccesos.contador++;
			}
			//if (buscarUsuario(gestor.listaUsuarios, gestor.listaPartidas.lisPar[i]->id2, indice)){
			//	insertarPartidaAP(gestor.listaAccesos,*gestor.listaPartidas.lisPar[i]);
			//}
		}
	}
}

bool iniciarSesionG(tGestor &gestor, string const &idUsu, string const &clave){
	bool iniciada = false, repetir = false;
	int pos = 0;
	iniciar(gestor.listaAccesos);
	if (buscarUsuario(gestor.listaUsuarios, idUsu, pos)){
		if (!iniSesionUsuario(gestor.listaUsuarios.LisUsu[pos], clave))		cout << "Contraseña incorrecta. " << endl << endl;
		else{
			gestor.posUsuario = pos;
			iniciada = true;
			generarAccesos(gestor);
		}
	}
	else	cout << "Este usuario no existe. " << endl;
	return iniciada;
}

bool crearCuentaG(tGestor &gestor,string const &idUsu,string const&clave){
	bool creado = false;
	int ultimaPos,aux;
	if(!buscarUsuario(gestor.listaUsuarios, idUsu, aux)){
		redimensionar(gestor.listaUsuarios);
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
			gestor.listaAccesos.contador = 0;
			arrancado = true;
		}
	}
	return arrancado;
}

void apagar(tGestor &gestor)
{
	ofstream archivo;
	inactividad(gestor);
	archivo.open("usuarios.txt");
	apagar(gestor.listaUsuarios,archivo);
	archivo.close();
	archivo.open("partidas.txt");

	apagar(gestor.listaPartidas,archivo);
	archivo.close();
}

int partidasUsuario(tGestor const& gestor)
{
	return gestor.listaAccesos.contador;
}

void apuntarPartida(tGestor &gestor, int posParEnCurso){
	gestor.dirPartida = gestor.listaAccesos.listaAccesoPartidas[posParEnCurso - 1];
}
string cabecera(tGestor const &gestor, int posEncurso){

	ostringstream flujo;
	flujo << "# T    " << "Jugador1" << setw(31) << "Jugador2" << setw(15) << "Fecha" << endl;
	flujo << "---------------------------------------------------------------------" << endl;
	for (int i = 0; i < partidasUsuario(gestor); i++){
		flujo << cabeceraPartida(*gestor.listaAccesos.listaAccesoPartidas[i], i, gestor.listaUsuarios.LisUsu[gestor.posUsuario].id);
	}
	return flujo.str();
}
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
	jugador1=gestor.dirPartida->id1;
	jugador2=gestor.dirPartida->id2;
	mostrar(gestor.dirPartida->conecta,jugador1, jugador2);
}

bool esSuTurno(tGestor const &gestor){
	bool turnoActual = false;
	tTurno turno;
	if (gestor.dirPartida->id1 == gestor.listaUsuarios.LisUsu[gestor.posUsuario].id){
		turno = Jugador1;
	}
	else {
		turno = Jugador2;
	}
	if (gestor.dirPartida->conecta.turno == turno){
		turnoActual = true;
	}
	return turnoActual;
}
void errorCrearPartida(tGestor &gestor,bool ok){
	if(!ok){
		if(llena(gestor.listaAccesos)){
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
void crearNueva(tGestor &gestor, bool &ok, int &posPartida, int &posUsuario){
	tPartida partida;
	nueva(partida, gestor.listaUsuarios.LisUsu[gestor.posUsuario].id, gestor.listaUsuarios.LisUsu[posUsuario].id);
	if (insertarPartida(gestor.listaPartidas, partida, posPartida)){
		if (gestor.listaAccesos.contador < MAX_PAR_US){
			if(insertarPartidaAP(gestor.listaAccesos,partida)){
				if (nuevaPartidaUsuario(gestor.listaUsuarios.LisUsu[gestor.posUsuario]) && nuevaPartidaUsuario(gestor.listaUsuarios.LisUsu[posUsuario]) ){
					ok = true;
				}
			}
		}
	}

}
void buscarYcrear(tGestor & gestor, bool &ok){
	int posUsuario = 0, posPartida = 0;
	if (buscarUsuarioEsperando(gestor.listaUsuarios, gestor.listaUsuarios.LisUsu[gestor.posUsuario].nivel, posUsuario)){
		if (gestor.listaUsuarios.LisUsu[posUsuario].id != gestor.listaUsuarios.LisUsu[gestor.posUsuario].id){
			crearNueva(gestor, ok, posPartida, posUsuario);
		}
		else{
			posUsuario++;
			if (buscarUsuarioEsperando(gestor.listaUsuarios, gestor.listaUsuarios.LisUsu[gestor.posUsuario].nivel, posUsuario)){
				crearNueva(gestor, ok, posPartida, posUsuario);
			}
		}
	}
}
bool nuevaPartidaG(tGestor &gestor){
	bool ok = false;
	if (!llena(gestor.listaAccesos) && gestor.listaPartidas.contador < MAXPART){
		cambiarEstadoUsu(gestor);
		buscarYcrear(gestor, ok);
	}
	errorCrearPartida(gestor, ok);
	return ok;
}
void jugarPartida(tGestor &gestor,int col){
	aplicarJugada(*gestor.dirPartida,col-1);
	mostrar(gestor.dirPartida->conecta,gestor.dirPartida->id1,gestor.dirPartida->id2);
}
int posicionJugadorAct(tGestor gestor){
	int pos=0;
	if(gestor.dirPartida->id1==gestor.listaUsuarios.LisUsu[gestor.posUsuario].id){
		buscarUsuario(gestor.listaUsuarios,gestor.dirPartida->id2,pos);
	}
	else{
		buscarUsuario(gestor.listaUsuarios,gestor.dirPartida->id1,pos);
	}

	return pos;
}
void abandonarPartida(tGestor &gestor, ostringstream &aviso){
	int pos = 0;
	bool ok = false;
	pos = posicionJugadorAct(gestor);
	abandonar(*gestor.dirPartida);
	aviso << "Has ganado una partida por abandono contra "
		<< gestor.listaUsuarios.LisUsu[gestor.posUsuario].id << " el "
		<< stringFecha(gestor.dirPartida->actualizacion, ok)
		<< endl;
	actualizarAvisos(gestor.listaUsuarios.LisUsu[pos], aviso.str());
	eliminar(gestor.listaAccesos, gestor.dirPartida->identificador);
	eliminar(gestor.listaAccesos, gestor.dirPartida->identificador);
	aplicarFinPartida(gestor.listaUsuarios.LisUsu[gestor.posUsuario], Pierde);
	aplicarFinPartida(gestor.listaUsuarios.LisUsu[pos],Gana);
}
bool comprobarGanadores(tGestor &gestor,int &pos,ostringstream &aviso){
	bool ok=false;
	pos = posicionJugadorAct(gestor);
	if(gestor.dirPartida->conecta.estado==Ganador||gestor.dirPartida->conecta.estado==Bloqueo){
		ok=true;
		if (gestor.dirPartida->conecta.estado == Bloqueo){
			aviso << "Has empatado la partida contra " << gestor.listaUsuarios.LisUsu[gestor.posUsuario].id << " el " << stringFecha(fechaActual(), ok)<< endl;
		}
		else if (gestor.listaPartidas.lisPar[gestor.posUsuario]->conecta.estado == Ganador){
			aviso << "Has perdido la partida contra " << gestor.listaUsuarios.LisUsu[gestor.posUsuario].id << " a fecha de " << stringFecha(fechaActual(), ok)<<endl;
		}
		elimSum(gestor);
	}
	return ok;
}

void elimSum(tGestor &gestor){
	int pos = 0;

	pos = posicionJugadorAct(gestor);
	eliminar(gestor.listaAccesos, gestor.dirPartida->identificador);
	if (gestor.dirPartida->conecta.estado == Ganador)
	{
		aplicarFinPartida(gestor.listaUsuarios.LisUsu[gestor.posUsuario], Gana);
		aplicarFinPartida(gestor.listaUsuarios.LisUsu[pos],Pierde);
	}
	else if (gestor.dirPartida->conecta.estado == Bloqueo){
		aplicarFinPartida(gestor.listaUsuarios.LisUsu[gestor.posUsuario],Empata);
		aplicarFinPartida(gestor.listaUsuarios.LisUsu[pos],Empata);
	}
	gestor.dirPartida->estadoPartida = terminada;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////Añade las funciones para ordenar la lista por fecha y turno (con  un parámetro para el identificador del usuario del turno
void ordenar_Fecha(tGestor  &gestor){
	int j=0;
	tFecha elemento;
	tPartida partida;
	for (int i = 1; i < gestor.listaAccesos.contador; i++){
		j = i;
		partida = *gestor.listaAccesos.listaAccesoPartidas[i];
		elemento = partida.actualizacion;
		while ((j > 0) && (elemento < gestor.listaAccesos.listaAccesoPartidas[j-1]->actualizacion)){
			*gestor.listaAccesos.listaAccesoPartidas[j]=*gestor.listaAccesos.listaAccesoPartidas[j-1];
			j--;
		}
		*gestor.listaAccesos.listaAccesoPartidas[j]= partida;
	}
}
void ordenar_Turno(tGestor &gestor){
	int j=0;
	tPartida part1, part2;
	for (int i = 1; i < gestor.listaAccesos.contador; i++){
		j = i;
		part1 = *gestor.listaAccesos.listaAccesoPartidas[j - 1];
		part2 = *gestor.listaAccesos.listaAccesoPartidas[i];
		while ((j > 0) && compararTurno(gestor,part1,part2)){	
			*gestor.listaAccesos.listaAccesoPartidas[j] = *gestor.listaAccesos.listaAccesoPartidas[j-1];
			--j;
		}
		*gestor.listaAccesos.listaAccesoPartidas[j] = part2;
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