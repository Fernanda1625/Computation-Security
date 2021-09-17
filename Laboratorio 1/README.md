# Laboratorio N° 1 
## Funciones elementales de Criptografía
### Texto claro
#### HERALDOSNEGROS.txt

```bash  
Hay golpes en la vida, tan fuertes... ¡Yo no sé!
Golpes como del odio de Dios; como si ante ellos,
la resaca de todo lo sufrido
se empozara en el alma... ¡Yo no sé!

Son pocos; pero son... Abren zanjas oscuras
en el rostro más fiero y en el lomo más fuerte.
Serán tal vez los potros de bárbaros Atilas;
o los heraldos negros que nos manda la Muerte.

Son las caídas hondas de los Cristos del alma
de alguna fe adorable que el Destino blasfema.
Esos golpes sangrientos son las crepitaciones
de algún pan que en la puerta del horno se nos quema.

Y el hombre... Pobre... ¡pobre! Vuelve los ojos, como
cuando por sobre el hombro nos llama una palmada;
vuelve los ojos locos, y todo lo vivido
se empoza, como charco de culpa, en la mirada.

Hay golpes en la vida, tan fuertes... ¡Yo no sé!
```

## Actividades

### 1. Realizar las siguientes sustituciones: j x i, h x i, ñ x n, k x l, u x v, w x v, y x z

```c++ 
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
```


### 2. Elimine las tildes
```c++ 
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
```

### 3. Convierta todas las letras a mayúsculas

```c++ 
void aMayusculas(string& text) {
	for (auto i = text.begin(); i < text.end(); ++i) {
		if (*i >= 'a' && *i <= 'z')
			*i -= 32;
	}
}
```

### 4. Elimine los espacios en blanco y los signos de puntuación.

```c++ 
void eliminarEspaciosSignos(string &text) {
	for (auto i = text.begin(); i < text.end(); ++i) {
		if (*i < 'A' || * i > 'Z')
			*i = '\0';
	}
}
```
### Guarde el resultado en el archivo “HERALDOSNEGROS_pre.txt”

```c++ 
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

```
> Resultado en: HERALDOSNEGROS_pre.txt

### 5. Abra el archivo generado e implementar una función que calcule una tabla de frecuencias para cada letra de la 'A' a la 'Z'. La función deberá definirse como frecuencias(archivo) deberá devolver un diccionario cuyos índices son las letras analizadas y cuyos valores son las frecuencias de las mismas en el texto (número de veces que aparecen). Reconozca en el resultado obtenido los cinco caracteres de mayor frecuencia

```c++ 
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
```

> Resultado en:  HERALDOSNEGROS_pre_FRECUENCIAS.txt

### 6. Aplicar el método Kasiski, que recorre el texto preprocesado y halla los trigramas en el mismo (sucesión de tres letras seguidas que se repiten) y las distancias (número de caracteres entre ellos) entre los trigramas

```c++ 
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
```
> Resultado en:  HERALDOSNEGROS_pre_KASISKI.txt
### 7. Volver a preprocesar el archivo cambiando cada carácter según UNICODE-8

```c++ 
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
```
> Resultado en:  HERALDOSNEGROS_pre_UTF8.txt

### 9. Volver a preprocesar el archivo insertando la cadena AQUÍ cada 20 caracteres, el texto resultante deberá contener un número de caracteres que sea múltiplo de 4, si es necesario rellenar al final con caracteres X según se necesite

```c++ 
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
```
> Resultado en: HERALDOSNEGROS_pre_AQUI.txt
