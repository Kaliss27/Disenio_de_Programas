/*Tarea 5
  Peralta Luna Karen Lisseth
  S17002346
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct nodoBinario
{
	int dato;
	struct nodoBinario *izq;
	struct nodoBinario *der;	
}nodoB;

int insertar(nodoB **axraiz,int d);
nodoB* crearNodo(int d);
void ver_Arbol(nodoB *raiz,int c,int i);
int borrar_dato(nodoB **raiz,int d);
void avance(nodoB **aux,nodoB **aux1,int *bo);
int buscar_dato(nodoB *raiz,int d);
void contar_hojas(nodoB *raiz,int *hojas);
int altura_arbol(nodoB *raiz);
int equilibrio_arbol(nodoB *raiz);

int main(int argc, char const *argv[])
{
	nodoB *raiz=NULL;
	int d,opc,n,total_hojas=0,h,fe;
	/*do{
		printf("1->Ingresar datos al arbol\n2->Ver arbol\n3->Eliminar datos del arbol\n4->Buscar dato en el arbol\n5->Contar hojas del arbol\n6->Salir\nOpcion:");
		scanf("%i",&opc);
		switch(opc){
			case 1: 
			printf("Ingresar un numero entero:");
			scanf("%i",&d);
			insertar(&raiz,d);
			break;
			case 2:
			printf("==Arbol binario==\n");
			ver_Arbol(raiz,0,0);
			sleep(5);
			break;
			case 3:
			printf("==Arbol binario==\n");
            ver_Arbol(raiz,0,0);
			printf("Ingresar un numero entero:");
			scanf("%i",&d);
			borrar_dato(&raiz,d);
			break;
			case 4:
			printf("Ingrese un numero entero a buscar:");
			scanf("%i",&d);
			n=buscar_dato(raiz,d);
			if(n==1)
				printf("Se encontro el valor en el arbol\n");
			if(n==0)
				printf("No se encontro el valor en el arbol\n");
			sleep(2);
			break;
			case 5:
			contar_hojas(raiz,&total_hojas);
			printf("Total de hojas: %i\n",total_hojas);
			total_hojas=0;
			sleep(3);
			break;
		}	
		system("clear");
	}while(opc!=6);*/
	insertar(&raiz,120);
	insertar(&raiz,87);
	insertar(&raiz,43);
	insertar(&raiz,65);
	insertar(&raiz,140);
	insertar(&raiz,99);
	insertar(&raiz,130);
	insertar(&raiz,22);
	insertar(&raiz,56);
	insertar(&raiz,93);
	insertar(&raiz,135);

	ver_Arbol(raiz,0,0);

	h=altura_arbol(raiz);

	contar_hojas(raiz,&total_hojas);

	fe=equilibrio_arbol(raiz);

    printf("Total de hojas: %i\nAltura del arbol:%i\n",total_hojas,h);
    printf("FE:%i\n",fe);
	return 0;
}
nodoB* crearNodo(int d){
	nodoB *newe=(nodoB*)malloc(sizeof(nodoB));
	if(!newe)
		return NULL;
	newe->dato=d;
	newe->der=NULL;
    newe->izq=NULL;		
	return newe;	
}
///////////INSERTAR NODO A ARBOL BINARIO////////////////////////
int insertar(nodoB **axraiz,int d){
	if(!(*axraiz)){
		(*axraiz)=crearNodo(d);
		return 1;
	}
	if(d>(*axraiz)->dato){
		return insertar(&(*axraiz)->der,d);
	}else{
		if((*axraiz)->dato==d) return 2;
		return insertar(&(*axraiz)->izq,d);
	}	
}
//////////Imprime arbol//////////////
void ver_Arbol(nodoB *raiz,int c,int i){
	if(!raiz){
		return;
	}
	else{
		ver_Arbol(raiz->der,c+1,0);
		for(i=0;i<c;i++){
			printf("   ");
		}
		printf("%i\n",raiz->dato);
		ver_Arbol(raiz->izq,c+1,0);
	}
	
}
//////////////////Eliminar nodo de arbol/////////////////////////////////
int borrar_dato(nodoB **raiz,int d){
	nodoB *aux,*aux1,*otro;
	int bo;
	if((*raiz)!=NULL){
		if(d<(*raiz)->dato){
			borrar_dato(&(*raiz)->izq,d);
		}else{
			if(d>(*raiz)->dato){
				borrar_dato(&(*raiz)->der,d);
			}else{
				otro=(*raiz);
				if(otro->der==NULL){
					(*raiz)=otro->izq;
				}else{
					if(otro->izq==NULL){
						(*raiz)=otro->der;
					}else{
						aux=(*raiz)->izq;
						bo=0;
						avance(&aux,&aux1,&bo);
						(*raiz)->dato=aux->dato;
						otro=aux;
						if(bo==1){
							aux1->der=aux->izq;
						}else{
							(*raiz)->izq=aux->izq;
						}
					}
				}
				free(otro);
				return 1;
			}
		}
	}
	return 0;
}

void avance(nodoB **aux,nodoB **aux1,int *bo){
	if((*aux)->der!=NULL){
		(*aux1)=(*aux);
		(*aux)=(*aux)->der;
		*bo=1;
		avance(&(*aux),&(*aux1),bo);
	}
	return;
}
////////Buscar dato en el arbol//////////////////
int buscar_dato(nodoB *raiz,int d){
	if(!raiz)
		return 0;
	if(raiz->dato==d)
		return 1;
	if(d<raiz->dato)
		return buscar_dato(raiz->izq,d);
	return buscar_dato(raiz->der,d);
}
/////////////Contar hojas del arbol/////////////////
void contar_hojas(nodoB *raiz,int *hojas)
{
	if(!raiz)
		return;
	if(!(raiz->der) && !(raiz->izq))
		*hojas=*hojas+1;
	if(raiz->izq)
		contar_hojas(raiz->izq,hojas);
    if(raiz->der)
    	contar_hojas(raiz->der,hojas);	
	return;
}

///////////////Calcular altura del arbol///////////////////////
int altura_arbol(nodoB *raiz){
	int h1,h2;
	if(!raiz)
		return 0;
	h1=altura_arbol(raiz->izq);
	h2=altura_arbol(raiz->der);
	if(h1>h2)
		return h1+1;
	return h2+1;
}
/////////Calcular Factor de Equilibrio/////////////////////
int equilibrio_arbol(nodoB *raiz){
	int h1,h2;
	if(!raiz)
		return 0;
	h1=altura_arbol(raiz->izq);
	h2=altura_arbol(raiz->der);
	return h2-h1;
}