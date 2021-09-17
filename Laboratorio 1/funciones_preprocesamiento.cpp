#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

////////////////////////////////////////////////////////////////////////
// Actividad 1: sustituir j x i, h x i, ñ x n, k x l, u x v, w x v, y x z
////////////////////////////////////////////////////////////////////////
void sustituirLetra(string &text) {
	for (auto i = text.begin(); i < text.end(); ++i) {
		switch (*i) {
			case 'j':
				*i = 'i';
				break;
			case 'h':
				*i = 'i';
				break;
			case '\x00F1':
				*i = 'n';
				break;
			case 'k':
				*i = 'l';
				break;
			case 'u':
				*i = 'v';
				break;
			case 'w':
				*i = 'v';
				break;
			case 'y':
				*i = 'z';
				break;
			default:
				break;
		}
	}
}

////////////////////////////////////////////////////////////////////////
  // Actividad 2: eliminar las tildes
  ////////////////////////////////////////////////////////////////////////
void eliminarAcentos(string &text){
    for (auto i = text.begin(); i < text.end(); ++i) {
		switch (*i) {
			// Actividad 2: Eliminar los acentos
			case '\x00E1':
				*i = 'a';
				break;
			case '\x00E9':
				*i = 'e';
				break;
			case '\x00ED':
				*i = 'i';
				break;
			case '\x00F3':
				*i = 'o';
				break;
			case '\x00FA':
				*i = 'v';
				break;
            default:
				break;
		}
	}
}


////////////////////////////////////////////////////////////////////////
// Actividad 3: convertir todas las letras a mayúsculas
////////////////////////////////////////////////////////////////////////
void aMayusculas(string& text) {
	for (auto i = text.begin(); i < text.end(); ++i) {
		if (*i >= 'a' && *i <= 'z')
			*i -= 32;
	}
}

/////////////////////////////////////////////////////////////////////////
// Actividad 4: eliminar los espacios en blanco y los signos de puntuación
/////////////////////////////////////////////////////////////////////////
void eliminarEspaciosSignos(string &text) {
	for (auto i = text.begin(); i < text.end(); ++i) {
		if (*i < 'A' || * i > 'Z')
			*i = '\0';
	}
}

//Funcion para convertir a minusculas
void aMinusculas(string& text) {
	for (auto i = text.begin(); i < text.end(); ++i) {
		if (*i >= 'A' && *i <= 'Z')
			*i += 32;
		else if (*i == '\x00D1')
			*i = '\x00F1';
	}
}

//Funcion para aplicar todas las funciones anteriores y guardar el archivo en HERALDOSNEGROS_pre.txt
void preprocesar(string filename) {
	ofstream archivoSalida;
	ifstream archivoEntrada;
	archivoEntrada.open(filename, ios::in);
	archivoSalida.open("HERALDOSNEGROS_pre.txt", ios::out);

	if (archivoEntrada.fail()) {
		cout << "No se pudo abrir el archivo." << endl;
		return;
	}

	string linea;
	while (!archivoEntrada.eof()) {
		getline(archivoEntrada, linea);
		aMinusculas(linea);
		sustituirLetra(linea);
		eliminarAcentos(linea);
		aMayusculas(linea);
		eliminarEspaciosSignos(linea);
		for (auto i = linea.begin(); i < linea.end(); ++i) {
			if (*i == '\0')
				continue;
			archivoSalida << *i;
		}
	}

	archivoEntrada.close();
	archivoSalida.close();
}

////////////////////////////////////////////////////////////////////////
// Actividad 5: Frecuencias de las letras
////////////////////////////////////////////////////////////////////////
void frecuencias(string filename) {
	map<char, int> tablaFrecuencias;
	ifstream archivo;
	archivo.open(filename, ios::in);

	if (archivo.fail()) {
		cout << "No se pudo abrir el archivo." << endl;
		return;
	}

	//Llenando la tabla
	string linea;
	while (!archivo.eof()) {
		getline(archivo, linea);
		for (auto i = linea.begin(); i < linea.end(); ++i) {
			if (tablaFrecuencias.find(*i) != tablaFrecuencias.end()) {
				tablaFrecuencias.at(*i)++;
			} else {
				tablaFrecuencias.insert_or_assign(*i, 1);
			}
		}
	}

	archivo.close();

	//Ordenando
	vector<pair<char, int>> temporal;
	copy(tablaFrecuencias.begin(), tablaFrecuencias.end(),back_inserter<std::vector<pair<char, int >>>(temporal));

	sort(temporal.begin(), temporal.end(),[](const pair<char, int> &l, const pair<char, int> &r) {
		if (l.second != r.second)
			return l.second > r.second;
		return l.first > r.first;
	});

	cout << "\t\t\tTabla de Frecuencias:\t\t\t" << endl;
	for (int i = 0; i < temporal.size(); ++i)
		cout << temporal[i].first << " " << temporal[i].second << endl;
}

////////////////////////////////////////////////////////////////////////
// Actividad 6: Método Kasiski
////////////////////////////////////////////////////////////////////////
void kasiski(string filename) {
	ifstream archivo;
	archivo.open(filename, ios::in);

	if (archivo.fail()) {
		cout << "No se pudo abrir el archivo." << endl;
		return;
	}

	string linea;
	while (!archivo.eof()) {
		getline(archivo, linea);
		auto ultimo = linea.begin();
		int distancia;

		for (auto i = linea.begin(), j = linea.begin() + 1, k = linea.begin() + 2; k < linea.end(); ++i, ++j, ++k) {
			if (*i == *j && *i == *k) {
				if (ultimo != i) {
					cout << i - ultimo << endl;
					ultimo = i;
				}
			}
		}
	}

	archivo.close();
}

////////////////////////////////////////////////////////////////////////
// Actividad 7: Unicode-8
////////////////////////////////////////////////////////////////////////
void convertirUTF8(string filename) {
	ifstream archivo;
	archivo.open(filename, ios::in);

	if (archivo.fail()) {
		cout << "No se pudo abrir el archivo" << endl;
		return;
	}

	string linea;
	while (!archivo.eof()) {
		getline(archivo, linea);
		cout << linea << endl;
	}
}


////////////////////////////////////////////////////////////////////////
// Actividad 8: Unicode-8230
////////////////////////////////////////////////////////////////////////
void convertirUTF8230(string filename) {
	ifstream archivo;
	archivo.open(filename, ios::in);

	if (archivo.fail()) {
		cout << "No se pudo abrir el archivo" << endl;
		return;
	}

	string linea;
	while (!archivo.eof()) {
		getline(archivo, linea);
		cout << linea << endl;
	}
}

////////////////////////////////////////////////////////////////////////
// Actividad 9: Insertando AQUI cada 20 caracteres
////////////////////////////////////////////////////////////////////////
void insertarAqui(string filename){
	ifstream archivo;
    archivo.open(filename, ios::in);

	if (archivo.fail()) {
		cout << "No se pudo abrir el archivo" << endl;
		return;
	}

	string linea;
	while (!archivo.eof()) {
		getline(archivo, linea);
		cout << linea << endl;
	}
}

//////////
// main
//////////
int main() {
	string archivo = "HERALDOSNEGROS.txt";
	preprocesar(archivo);
	frecuencias("HERALDOSNEGROS_pre.txt");
	kasiski("HERALDOSNEGROS_pre.txt");
	//convertirUTF8("HERALDOSNEGROS_pre.txt");


	return 0;
}
