/**
 * Proyecto TDA Dictionary Creado Por:
 * Juan Pablo de Alba Tamayo
 * Jaime Alberto Camacho Ortiz
 */

#include "Dictionary.h"
#include <stdio.h>


int main(){


    Dictionary diccionario = dict_create();

    dict_set(diccionario,"Arbol","estructura con hojas, hecha de madera");

    dict_set(diccionario,"Botella", "Estructura de vidrio");

    dict_set(diccionario,"Pie", "Extremidad del cuerpo humano");

    dict_set(diccionario,"zapato", "Objeto que cubre al pie");

    dict_set(diccionario, "azucar", "dulzura");

    dict_set(diccionario, "Arandano", "fruta roja");
    dict_set(diccionario, "Anillo", "Oro");




    printf("\n\nTamano del diccionario: %d\n", dict_size(diccionario));


    printf("\n%s:   %s\n","Arbol", dict_get(diccionario, "Arbol"));
    printf("\n%s:   %s\n","Botella", dict_get(diccionario, "botella"));
    printf("\n%s:   %s\n","Pie", dict_get(diccionario, "Pie"));
    printf("\n%s:   %s\n\n","Zapato", dict_get(diccionario, "Zapato"));
    printf("\n%s:   %s\n\n","azucar", dict_get(diccionario, "azucar"));
    printf("\n%s:   %s\n\n","Arandano", dict_get(diccionario, "Arandano"));
    printf("\n%s:   %s\n\n","Anillo", dict_get(diccionario, "Anillo"));


    char** keys = dict_keys(diccionario);

    for(int i=0; i<dict_size(diccionario); i++){
        printf("%s\n", keys[i]);
    }

    dict_destroy(diccionario);

    return 0;
}
