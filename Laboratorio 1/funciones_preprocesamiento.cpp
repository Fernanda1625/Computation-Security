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
void frecuencia(string filename){
	ofstream archivoFrecuencias("HERALDOSNEGROS_pre_FRECUENCIAS.txt");
	map<char, int>	diccionario;
	ifstream archivo(filename, std::ios::in);
	string linea;
	if(archivo.is_open()){
		archivo >> linea;
		archivo.close();
	}
	for(auto letter: linea){
		auto it = diccionario.find(letter);
		if(it == diccionario.end())
			diccionario[letter] = 1;
		else
			diccionario[letter] += 1;
	}
	if(archivoFrecuencias.is_open())
	  archivoFrecuencias<<"FRECUENCIAS DEL DICCIONARIO\n";
	for(auto it = diccionario.begin(); it != diccionario.end(); ++it){
		if(archivoFrecuencias.is_open())
		  archivoFrecuencias<< it -> first << " -> " << it -> second << std::endl;
	}
	vector<std::pair<char,int>> pairs;
	for(auto it = diccionario.begin(); it != diccionario.end(); ++it){
		pairs.push_back(*it);
	}
	sort(pairs.begin(), pairs.end(),
		[=](std::pair<char,int>& p1, std::pair<char,int>&p2){
			return p1.second > p2.second;
		}
	);
	if(archivoFrecuencias.is_open())
		archivoFrecuencias <<"CINCO CARACTERES DE MAYOR FRECUENCIA\n";
	for(auto i = 0; i < 5; ++i){
		if(archivoFrecuencias.is_open())
			archivoFrecuencias << pairs[i].first << " -> " << pairs[i].second << std::endl;
	}
	archivoFrecuencias.close();
}

////////////////////////////////////////////////////////////////////////
// Actividad 6: Método Kasiski
////////////////////////////////////////////////////////////////////////
void kasiski(string filename){
	ofstream archivoKasiski("HERALDOSNEGROS_pre_KASISKI.txt");
	ifstream archivo(filename, std::ios::in);
	string linea;
	if(archivo.is_open()){
		archivo >> linea;
		archivo.close();
	}
	for( int i = 0; i < linea.length()-6; ++i){
		string primerTrigrama = "";
		primerTrigrama += linea[i];
		primerTrigrama += linea[i+1];
		primerTrigrama += linea[i+2];
		for(int j=i+3; j< linea.length()-3; ++j){
			string segundoTrigrama = "";
			segundoTrigrama += linea[j];
			segundoTrigrama += linea[j+1];
			segundoTrigrama += linea[j+2];
			if(primerTrigrama == segundoTrigrama){
				if(archivoKasiski.is_open()){
					archivoKasiski << primerTrigrama << "("<< i+1 << "," << i+3 <<")" << "->" <<
					"(" << j+1 << "," << j+3 << ")" << "\tdistancia: " << j-(i+3) << std::endl;
				}
			}
		}
	}
	archivoKasiski.close();
}

////////////////////////////////////////////////////////////////////////
// Actividad 7: Unicode-8
////////////////////////////////////////////////////////////////////////
void convertirUTF8(string filename) {
	ifstream archivo;
  ofstream archivoUTF8("HERALDOSNEGROS_pre_UTF8.txt");
	archivo.open(filename, ios::in);
  string linea;
	if (archivo.fail()) {
		cout << "No se pudo abrir el archivo" << endl;
		return;
	}
	while (!archivo.eof()) {
		getline(archivo, linea);
		archivo >> linea;
    for (auto letra : linea){
      archivoUTF8 << std::hex << (int)letra;
    }
    archivoUTF8.close();
	}
}

////////////////////////////////////////////////////////////////////////
// Actividad 9: Insertando AQUI cada 20 caracteres
////////////////////////////////////////////////////////////////////////

void insertarAQUI(string filename){
	ofstream archivoAQUI("HERALDOSNEGROS_pre_AQUI.txt");
	ifstream archivo(filename, std::ios::in);
	string linea;
	if(archivo.is_open()){
		archivo >> linea;
		archivo.close();
	}
	string cadena = "";
	for(int i =0 ; i < linea.length(); i++){
		if(!((i+1)%20)){
			cadena += "AQUI";
		}
		cadena += linea[i];
	}
	while(cadena.length() % 4){
		cadena += "X";
	}
	archivoAQUI << cadena ;
	archivoAQUI.close();
}

//////////
// main
//////////
int main() {
	string archivo = "HERALDOSNEGROS.txt";
	preprocesar(archivo);
	frecuencia("HERALDOSNEGROS_pre.txt");
	kasiski("HERALDOSNEGROS_pre.txt");
	convertirUTF8("HERALDOSNEGROS_pre.txt");
	insertarAQUI("HERALDOSNEGROS_pre.txt");

	return 0;
}
