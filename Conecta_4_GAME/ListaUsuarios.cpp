#include "listaUsuarios.h"

bool cargar(tListaUsuarios &usuarios, ifstream &archivo)
{
	bool cargado = false;
	for (int i = 0; i < usuarios.contador; i++)
	{
		if (cargar(usuarios.LisUsu[i], archivo)) cargado = true;
	}
	return cargado;
}

void guardar(tListaUsuarios const &usuarios, ofstream &archivo) //revisar
{
	archivo << usuarios.contador << endl;
	for (int i = 0; i < usuarios.contador; i++)	guardar(usuarios.LisUsu[i], archivo);
}

bool buscarUsuario(tListaUsuarios const& usuarios, string const& idUsu, int &pos){
	bool encontrado = false;
	int ini = 0, fin = usuarios.contador - 1, mitad;
	while (ini <= fin && !encontrado) {

		mitad = (ini + fin) / 2;
		if (idUsu == usuarios.LisUsu[mitad].id) encontrado = true;
		else if (idUsu < usuarios.LisUsu[mitad].id) fin = mitad - 1;
		else ini = mitad + 1;
	}
	if (encontrado) pos = mitad;
	else pos = ini;

	return encontrado;
}

bool insertar(tListaUsuarios &usuarios, tUsuario const &usuario, int &pos){
	tUsuario usuarioAux;
	bool insertar = false;
	if (usuarios.contador == MAXUSU){
		insertar = false;
	}
	else{
		if (!buscarUsuario(usuarios, usuario.id, pos)){
			usuarioAux = usuario;
			desplazarDerecha(usuarios, pos);
			usuarios.LisUsu[pos] = usuarioAux;
			usuarios.contador++;
			pos = usuarios.contador;
			insertar = true;
		}
		else insertar = false;
	}
	return insertar;
}

bool buscarUsuarioEsperando(tListaUsuarios &usuarios, tNivel nivel, int &pos){
	bool encontrado = false;
	while (pos < usuarios.contador && !encontrado){
		if (usuarios.LisUsu[pos].estadoJugador){
			if ((pos < usuarios.contador) && (usuarios.LisUsu[pos].nivel == nivel)){
				encontrado = true;
			}
			else pos++;
		}
		else pos++;
	}
	return encontrado;
}

void desplazarDerecha(tListaUsuarios &usuarios, int &pos){
	for (int i = usuarios.contador; i > pos; i--){
		usuarios.LisUsu[i] = usuarios.LisUsu[i - 1];
	}
}