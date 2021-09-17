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
#### HERALDOSNEGROS_pre.txt
```txt
IAZGOLPESENLAVIDATANFVERTESZONOSEGOLPESCOMODELODIODEDIOSCOMOSIANTEELLOSLARESACADETODOLOSVFRIDOSEEMPOZARAENELALMAZONOSESONPOCOSPEROSONABRENZANIASOSCVRASENELROSTROMASFIEROZENELLOMOMASFVERTESERANTALVEZLOSPOTROSDEBARBAROSATILASOLOSIERALDOSNEGROSQVENOSMANDALAMVERTESONLASCAIDASIONDASDELOSCRISTOSDELALMADEALGVNAFEADORABLEQVEELDESTINOBLASFEMAESOSGOLPESSANGRIENTOSSONLASCREPITACIONESDEALGVNPANQVEENLAPVERTADELIORNOSENOSQVEMAZELIOMBREPOBREPOBREVVELVELOSOIOSCOMOCVANDOPORSOBREELIOMBRONOSLLAMAVNAPALMADAVVELVELOSOIOSLOCOSZTODOLOVIVIDOSEEMPOZACOMOCIARCODECVLPAENLAMIRADAIAZGOLPESENLAVIDATANFVERTESZONOSE
```
### 5. Abra el archivo generado e implementar una función que calcule una tabla de frecuencias para cada letra de la 'A' a la 'Z'. La función deberá definirse como frecuencias(archivo) deberá devolver un diccionario cuyos índices son las letras analizadas y cuyos valores son las frecuencias de las mismas en el texto (número de veces que aparecen). Reconozca en el resultado obtenido los cinco caracteres de mayor frecuencia

```c++ 
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

```

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

### 7. Volver a preprocesar el archivo cambiando cada carácter según UNICODE-8

```c++ 
```

### 8. Volver a preprocesar el archivo cambiando cada carácter según UNICODE-8230

```c++ 
```

### 9. Volver a preprocesar el archivo insertando la cadena AQUÍ cada 20 caracteres, el texto resultante deberá contener un número de caracteres que sea múltiplo de 4, si es necesario rellenar al final con caracteres X según se necesite

```c++ 
```


