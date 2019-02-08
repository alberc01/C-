#include "ListaAccesoPartidas.h"

void iniciar(tListaAccesoPartidas &lista)
{
	lista.contador = 0;
}

bool llena(tListaAccesoPartidas const&lista)
{
	return lista.contador == MAX_PAR_US;
}

bool insertarPartidaAP(tListaAccesoPartidas &lista, tPartida &par){
	bool insertar=false;
	if (!llena(lista))
	{
		lista.listaAccesoPartidas[lista.contador]=new tPartida;
		*lista.listaAccesoPartidas[lista.contador] = par;
		insertar = true;
		lista.contador++;
	}
	return insertar;
}

bool eliminar(tListaAccesoPartidas &lista, string const &id){
	bool eliminada = false;
	int pos = 0;
	if (buscarSinOrden(lista, id, pos)){
		if (eliminarAux(lista, pos)){
			eliminada = true;
		}
	}
	return eliminada;

}

bool buscarSinOrden(tListaAccesoPartidas &lista, string buscado, int &pos){
	bool encontrado = false;
	if(pos < lista.contador){
		if (buscado == lista.listaAccesoPartidas[pos]->identificador){ 
			encontrado = true;
		}
		else{ 
			++pos;
			buscarSinOrden(lista,buscado,pos);
		}
	}
	return encontrado;
}

void desplazarIzquierda(tListaAccesoPartidas &lista, int pos){
	for (int i = pos + 1; i < lista.contador; ++i){
		lista.listaAccesoPartidas[i - 1] = lista.listaAccesoPartidas[i];
	}

}

bool eliminarAux(tListaAccesoPartidas &lista, int pos){
	bool eliminada;
	if ((pos < 0) || (pos >= lista.contador)){
		eliminada = false;
	}
	else{
		desplazarIzquierda(lista, pos);
		lista.contador--;
		eliminada = true;
	}
	return eliminada;
}