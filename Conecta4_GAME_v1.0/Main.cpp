#include "Gestor.h"
#include <iomanip>
using namespace std;

//  MENUS   //

void menuPartida(tGestor & gestor);	/*Controla el menu de la partida*/
int controlMenuPart(tGestor &gestor, ostringstream &aviso);  /*Muestra el menu de la partida*/
int opcionesUsuario(tGestor &gestor); /*Muestra el menu usuario*/
void menuUsuario(tGestor &gestor); /*Controla el menu usuario*/
int menuR(); /*Muestra el menu registro*/
void menuRegistro(tGestor &gestor); /*Controla el menu registro*/

//OTRAS FUNCIONES//

void mostrarPartidasEncurso(tGestor &gestor); /*Se encarga de mostrar las partidas del usuario*/
void mostrarDatosUsu(tGestor &gestor,string idUsu,string clave);/*Se encarga de mostrar los avisos y preguntar si quiere borrarlos*/
void accederCuenta(tGestor & gestor); /*Se encarga del acceso a la cuenta del usuario*/
void registrarse(tGestor &gestor); /*Se encarga de registrar un nuevo usuario*/
void verPartida(tGestor &gestor); /*Se encarga de seleccion y mostrar la partida que el usuario quiere ver*/
int leerJugada(); /*Devuelve la columna seleccionada por el usuario*/
void datosUsuario(tGestor &gestor, string &idUsu, string &clave); /*Recoge los datos de el usario*/
void opcionJugar(tGestor &gestor, ostringstream &aviso); /*Se encarga de llevar el juego*/


int main()
{
	tGestor gestor;
	ofstream archivo;
	if (arrancar(gestor)){
		menuRegistro(gestor);	
	}
	apagar(gestor);
	system("pause");
	return 0;
}

int menuR(){
	int opcion = 0;
	cout << "1. Acceder a mi cuenta" << endl;
	cout << "2. Registrarse" << endl;
	cout << "0. Salir" << endl;
	cout<<"Opcion: ";
	cin >> opcion;
	return opcion;
}
void menuRegistro(tGestor &gestor)
{
	bool salir = false;
	do{
		switch (menuR())
		{
		case 1: {
			accederCuenta(gestor);
				}
				break;
		case 2:{
			registrarse(gestor);
			system("pause");
			system("cls");
			   }
			   break;
		case 0:{
			salir = true;
			system("cls");
			   }
		}
	}while(!salir);
}

void datosUsuario(tGestor &gestor, string &idUsu, string &clave)
{
	cout << "ACCESO" << endl;
	cout << " nombre de usuario: ";
	cin >> idUsu;
	cout << " Clave: ";
	cin >> clave;
}
void mostrarDatosUsu(tGestor &gestor,string idUsu,string clave){

	char borrar;
	string aviso;
	if (iniciarSesionG(gestor, idUsu, clave)){
		if (tieneAvisos(gestor, aviso)){
			cout << "\nTiene avisos: " << endl;
			cout << gestor.listaUsuarios.LisUsu[gestor.posUsuario].avisos <<endl<< endl;
			cout << "Quiere borrar los avisos (S/N) ? ";
			cin >> borrar;
			if (toupper(borrar) == 'S') limpiarAvisosG(gestor);
		}
		else{
			cout<<"\nEl usuario no tiene avisos..\n\n";
		}
		cout << resumenActividad(gestor);
		menuUsuario(gestor);
	}
}
void mostrarPartidasEncurso(tGestor &gestor){
	cout << "Menu Usuario" << endl << endl << endl;
	cout << cabecera(gestor, gestor.posUsuario);
	cout << endl;

}

void accederCuenta(tGestor & gestor)
{
	string idUsu, clave;
	system("cls");
	datosUsuario(gestor, idUsu,clave);
	mostrarDatosUsu(gestor,idUsu,clave);
}

void registrarse(tGestor &gestor)
{
	string idUsu, clave;
	//if(gestor.listaUsuarios.contador < gestor.listaUsuarios.tamanio){
		datosUsuario(gestor, idUsu, clave);
		crearCuentaG(gestor, idUsu, clave);
	//}
	//else{
	//	cout<< "\nError: No caben mas usuarios en la lista\n\n";
	//}
}

void menuUsuario(tGestor &gestor)
{
	bool salir = false;
	int opcion;

	do{
		mostrarPartidasEncurso(gestor);
		opcion = opcionesUsuario(gestor);
		switch (opcion)
		{
		case 1:{
			verPartida(gestor);
			   }
			   break; 
		case 2:{
			nuevaPartidaG(gestor);
			   }
			   break;
		case 3:{
			ordenar_Fecha(gestor);
			   }
			   break;
		case 4:{
			ordenar_Turno(gestor);
			   }
			   break;
		case 0:
			salir = true;
			system("cls");
		}
	}while(!salir);
}

void verPartida(tGestor &gestor)
{
	int partida;
	if (gestor.listaAccesos.contador == 0) cout << "No existe ninguna partida" << endl;
	else{
		do{
			cout << "Seleccion la partida que desea ver: ";
			cin >> partida;
			if (partida > gestor.listaAccesos.contador || partida <= 0) cout << "Lo siento esa partida no existe" << endl;
		} while (partida <=0 || partida > gestor.listaAccesos.contador);
		apuntarPartida(gestor, partida);
		menuPartida(gestor);
		//apuntarPartidaInv(gestor,partida);
	}
}
int leerJugada(){
	int col=0;
	cout<<"Introduce una columna valida <1-"<<COLS<<"> : ";
	cin>>col;

	while(col<0 || col>7){
		cout<<"\nError: Columna no valida..\n";
		cout<<"Introduce una columna valida <1-7> : ";
		cin>>col;
	}
	return col;
}
int controlMenuPart(tGestor &gestor,ostringstream &aviso){
	int pos=0;
	int opcion=0;
	if(!comprobarGanadores(gestor,pos,aviso)){
		do{
			if (esSuTurno(gestor)){
				cout << "1. Jugar. " << endl;
			}
			cout << "2. Abandonar" << endl;
			cout << "0. Salir" << endl;
			cout << "Elija una opcion: " << endl;
			cin >> opcion;
			if(opcion<0 || opcion>2){
				cout<<"\nError: Opcion no valida..\n";
				cout<<"Elije una opcion: ";
			}
		}while(opcion<0 || opcion>2);
	}
	else{
		actualizarAvisos(gestor.listaUsuarios.LisUsu[pos],aviso.str());
		cout<<"El juego a terminado\n\n";
		system("pause");
	}
	return opcion;
}
void opcionJugar(tGestor &gestor,ostringstream &aviso){
	if(asterisco(*gestor.dirPartida,gestor.listaUsuarios.LisUsu[gestor.posUsuario].id)){
		jugarPartida(gestor,leerJugada());
	}
	else{
		cout<<"No es tu turno\n\n";
	}
}
void menuPartida(tGestor & gestor)
{
	ostringstream aviso;
	bool salir = false;
	mostrarPartida(gestor);
	do{
		switch (controlMenuPart(gestor,aviso))
		{
		case 1:{
			opcionJugar(gestor,aviso);
			   }
			   break;
		case 2:{
			abandonarPartida(gestor,aviso);
			cout<<"Has perdido la partida..\n";
			system("Pause");
			salir=true;
			   }
			   break;
		case 0:{
			salir = true;
			system("cls");
			   }
		}
	} while (!salir);

}
int opcionesUsuario(tGestor &gestor)
{
	int opcion = 0;
	cout << setw(2) << "1 - Ver Partida" << endl;
	cout << setw(2) << "2 - Nueva Partida" << endl;
	cout << setw(2) << "3 - Partidas por actualizacion" << endl;
	cout << setw(2) << "4 - Partidas por turno y fecha" << endl;
	cout << setw(2) << "0 - Salir" << endl;
	cout << setw(2) <<"Opcion: ";
	cin >> opcion;
	return opcion;
}