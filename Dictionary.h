/**
 * Proyecto TDA Dictionary Creado Por:
 * Juan Pablo de Alba Tamayo
 * Jaime Alberto Camacho Ortiz
 */

#ifndef DICTIONARY_DICTIONARY_H
#define DICTIONARY_DICTIONARY_H

typedef struct strDictionary *Dictionary;


//Crear una nueva instancia tipo Dictionary
Dictionary dict_create();

//Destruir la instancia Diccionary creada
void dict_destroy(Dictionary);

//devuelve el tamaño del diccionario
unsigned int dict_size(Dictionary);

//Agregar una nueva palabra al diccionario
void dict_set(Dictionary d1, char* word, char* definition);

//Obtener la definición de una palabra
char*	dict_get(Dictionary, char* word);

//Obtiene todas las llaves del diccionario
char** dict_keys(Dictionary d);


#endif //DICTIONARY_DICTIONARY_H
