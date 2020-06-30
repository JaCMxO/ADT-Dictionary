/**
 * Proyecto TDA Dictionary Creado Por:
 * Juan Pablo de Alba Tamayo
 * Jaime Alberto Camacho Ortiz
 */
#include "Dictionary.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//--------------Estructuras---------------//

struct strNode
{
    char *key;		  //llave generada con las mayusculas de la palabra
    char *Word;		  //palabra que se guardara
    char *Definition; //definicion de la misma
    struct strNode **alphabet;
};

typedef struct strNode *Node;

struct strDictionary
{
    Node root;
    unsigned int size;
};

//-------------------------------------------//

//------------Funciones extras---------------//

int convert_index(char letra)
{
    if (letra == '_')
        return 26;
    else
        return letra - 'A';
}

char *keyGenerator(const char *str)
{
    int indexA = 0;
    char *str2 = strdup(str);

    while (str[indexA] != '\0')
    {
        if (str2[indexA] >= 'a' && str2[indexA] <= 'z')
        {
            str2[indexA] = str2[indexA] - ('a' - 'A');
        }
        else if (str2[indexA] >= 'A' && str2[indexA] <= 'Z')
        {
            str2[indexA] = str2[indexA];
        }
        else
            str2[indexA] = '_';
        indexA++;
    }

    return str2;
}

//---------------------------------------------//

//-------------Funciones extras 2--------------//

Node create_node(char *word, char *definition)
{
    Node n1;
    n1 = (Node)malloc(sizeof(struct strNode));
    n1->Word = strdup(word);
    n1->Definition = strdup(definition);

    n1->key = keyGenerator(word);

    n1->alphabet = (struct strNode**)calloc(27, sizeof(struct strNode*));

    return n1;
}

//index es 0 la primera vez que se llama, despues aumenta 1
int add_node(Dictionary s, Node root, char *key, char *word, char *definition, int index)
{
    if (index < strlen(key))
    { //mientras index sea menor al tamano de la palabra
        if (root->alphabet[convert_index(key[index])])
        { //si el root tiene algo (index) en la letra de su lista
            int iguales = strcmp(key, root->alphabet[convert_index(key[index])]->key); //revisa si ese algo es lo mismo que vamos a insertar

            if (iguales == 0){//si ese algo es lo mismo
                root->alphabet[convert_index(key[index])]->Word = word; //solo cambia el como esta escrita la palabra y la definicion
                root->alphabet[convert_index(key[index])]->Definition = definition;
            }
            else{ //si no es la misma palabra
                add_node(s, root->alphabet[convert_index(key[index])], key, word, definition, index + 1); //ese se convierte en el root
            }
        }
        else
        {																			   //si no tiene nada en la letra (index) de la lista de root
            root->alphabet[convert_index(key[index])] = create_node(word, definition); //anade el nodo en esa posicion
            return 1;																   //se sale de la recursividad
        }
    }

    //return 0; //si index fue mayor que el tamano de la palabra ya termino (caso de emergencia)
}

Node search_Node(Node root, char *key, int index)
{

    if (index < strlen(key))
    {
        //caso 1: Verifica si el root es igual
        int iguales = strcmp(root->key, key);
        //si es igual, regresa el root
        if (!iguales)
        {
            return root;
        }
        else
        {
            //caso 2: El root no es igual al key
            //revisamos si hay algo almacenada en la letra de nuestro root
            //si hay algo almacenado
            if (root->alphabet[convert_index(key[index])])
            {
                iguales = strcmp(key, root->alphabet[convert_index(key[index])]->key);

                if (iguales == 0)
                {

                    return root->alphabet[convert_index(key[index])];
                }
                else
                {
                    root = root->alphabet[convert_index(key[index])];
                    search_Node(root, key, index + 1);
                }
            }
            else
            { //no habia nada almacenado y por lo tanto no esta la palabra
                return NULL;
            }
        }
    }

    //return NULL;
}

void coverAllKeys(Node root, char** listkeys, int index){

    if(root){       //anade siempre el root
        listkeys[index] = root->key;
        index++;
    }
    //anade los hijos
    for(int i=0; i<27; i++) {
        if (root->alphabet[i]) {
            listkeys[index] = root->alphabet[i]->key;
            index++;
        }
    }
}

void removeNodes(Node root){
    for(int i=0; i<27; i++){
        if(root->alphabet[i]){
            removeNodes(root->alphabet[i]);
            free(root->alphabet[i]);
        }
    }
    free(root);
}

//---------------------------------------------//


//---------Funciones Principales-------------//

Dictionary dict_create()
{
    Dictionary d1 = (Dictionary)malloc(sizeof(struct strDictionary));
    d1->root = NULL;
    d1->size = 0;
    return d1;
}

unsigned int dict_size(Dictionary d1)
{
    if (d1)
        return d1->size;
    return 0;
}

void dict_set(Dictionary d1, char *word, char *definition)
{
    char* key = keyGenerator(word);
    if (d1->root != NULL)
    { //caso 1: ya existe un root
        int iguales = strcmp(key, d1->root->key);

        if (iguales == 0)
        { //caso 1.1: el root (key) original es igual al introducido
            d1->root->Word = word;
            d1->root->Definition = definition;
        }
        else
        {//caso 1.2: existe un root y es diferente al introducido
            int indexA = add_node(d1, d1->root, key, word, definition, 0); //en 0 porque comienza con la primer letra del key
            if (indexA == 1){
                d1->size++;
                printf("\nPalabra Anadida con exito!");
            }
        }
    }
    else
    { //caso 2: Esta vacio
        //printf("hola");
        d1->root = create_node(word, definition);
        d1->size++;
        printf("\nPalabra Anadida con exito!");
    }
}

char *dict_get(Dictionary d1, char *word)
{

    if (d1->root)
    {
        Node search = search_Node(d1->root, keyGenerator(word), 0);
        if (search != NULL)
        {
            // printf("HOLA1");
            return search->Definition;
        }
        else
        {

            return NULL;
        }
    }
    return NULL;
}

//Obtiene todas las llaves del diccionario
char** dict_keys(Dictionary d){
    int size = d->size;    //de este tamano sera el arreglo
    char ** listKeys;
    listKeys = (char **)calloc(size, sizeof(char *));
    //caso 1: solo esta el root
    if(size == 1){
        listKeys[0] = d->root->key;
    }
    else if(size>1){    //caso 2: hay mas keys
        coverAllKeys(d->root,listKeys,0);
    }

    return listKeys;
}

//Destruir la instancia Diccionary creada
void dict_destroy(Dictionary d){
    removeNodes(d->root);
    free(d);
}
