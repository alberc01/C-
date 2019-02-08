#include "listaPartidas.h"
//Practica5
void iniciar(tListaPartidas &partidas){
	for(int i=0;i<partidas.contador;i++){
		partidas.lisPar[i]=new tPartida;
	}
}
void destruir(tListaPartidas &partidas){
	for (int i = 0; i < partidas.contador; i++){
		delete partidas.lisPar[i];
	}
	partidas.contador =0;
}
void guardarHistorico(tListaPartidas  &partidas)
{
    ofstream archivo;
    archivo.open("historico.txt", ios::app);
    if (archivo.is_open()) {
        for (int i = 0; i < partidas.contador; i++)
        {
            if (partidas.lisPar[i]->estadoPartida ==  terminada)
            {
                guardar(*partidas.lisPar[i], archivo);
            }
        }
    }
    archivo.close();
}
void apagar(tListaPartidas &partidas,ofstream & archivo){
	guardar(partidas,archivo);
	guardarHistorico(partidas);
	destruir(partidas);
}
//Practica5

void guardar(tListaPartidas const &partidas, ofstream &archivo)
{
	int i = 0;
	archivo << partidas.contador << endl;
	do{
		guardar(*partidas.lisPar[i], archivo);
		i++;
	} while (i < partidas.contador);
}


bool cargar(tListaPartidas &partidas, ifstream &archivo)
{
	bool cargado = false;
	int i = 0;
	iniciar(partidas);
	for (int i = 0; i < partidas.contador; i++)
	{
		if (cargar(*partidas.lisPar[i], archivo)) cargado = true;
	}
	archivo.close();

	return cargado;
}

bool insertarPartida(tListaPartidas &partidas, tPartida const &partida, int &pos){
	bool insertar = false;

	if (partidas.contador < MAXPART){
		pos = partidas.contador;
		partidas.lisPar[pos]=new tPartida;
		*partidas.lisPar[pos] = partida;
		partidas.contador++;
		insertar = true;
	}
	return insertar;
}
