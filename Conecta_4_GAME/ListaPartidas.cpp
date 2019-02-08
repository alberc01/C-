#include "listaPartidas.h"

void guardar(tListaPartidas const &partidas, ofstream &archivo)
{
	int i = 0;
	archivo << partidas.contador << endl;
	do{
		guardar(partidas.lisPar[i], archivo);
		i++;
	} while (i < partidas.contador);
}


bool cargar(tListaPartidas &partidas, ifstream &archivo)
{
	bool cargado = false;
	int i = 0;
	for (int i = 0; i < partidas.contador; i++)
	{
		if (cargar(partidas.lisPar[i], archivo)) cargado = true;
	}
	archivo.close();

	return cargado;
}

bool insertarPartida(tListaPartidas &partidas, tPartida const &partida, int &pos){
	bool insertar = false;

	if (partidas.contador < MAXPART){
		pos = partidas.contador;
		partidas.lisPar[pos] = partida;
		partidas.contador++;
		insertar = true;
	}
	return insertar;
}