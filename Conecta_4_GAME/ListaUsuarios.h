#ifndef listaUsuarios_h
#define listaUsuarios_h
#include <iostream>
#include <string>
#include "usuario.h"

using namespace std;
const int MAXUSU = 5;


typedef tUsuario tListaUsuario[MAXUSU];

typedef struct{
	tListaUsuario LisUsu;
	int contador;
}tListaUsuarios;

bool buscarUsuario(tListaUsuarios const& usuarios, string const& idUsu, int &pos);/*Busca un usuario, tiene como parametros de E/S el array
																				  de uaurios, el id y la posicion*/
bool cargar(tListaUsuarios &usuarios, ifstream &archivo); /*Carga la lista, tiene como parametros de E/S de usuarios y el archivo*/
void guardar(tListaUsuarios const &usuarios, ofstream &archivo); /*Guardar la lista, tiene como parametros de E/S de usuarios y el archivo*/
bool buscarUsuarioEsperando(tListaUsuarios &usuarios, tNivel nivel, int &pos); /*Busca algun usuario disponible, tiene como parametros de 
																			   E/S del array de usuarios, y la posicion , y como entrada el nivel*/
void desplazarDerecha(tListaUsuarios &usuarios, int &pos); /*Funcion secundaria de buscarUsuarioEsperando, tiene como parametros de E/S el
														   array de usuarios y la posicion*/
bool insertar(tListaUsuarios &usuarios, tUsuario const &usuario, int &pos); /*Inserta el usuario, tiene como parametros de E/S el array de usuarios
																			el array de usuario y la posicion*/
#endif