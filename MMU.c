#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "RAM.h"
#include "MMU.h"
void traducir(nodof *,nodov *);
int suma_bin(int,int);
void rec(int*,int);
void str_vec(char[],int[]);

void main(){
	RAM Memoria_Fisica;
	MMU Memoria_Virtual;
	IniciarRAM(&Memoria_Fisica);
	IniciarMMU(&Memoria_Virtual);
	nodov *Nodo_Virtual;
	nodof *Nodo_Fisico;
	int indice;
    int reemp;
	Crear_Mem_Fis(&Memoria_Fisica);
	Crear_Mem_Vir(&Memoria_Virtual);
        system("clear");
	while(1){
		direccionesV(&Memoria_Virtual);
		printf("\n");
		printf("Ingrese la direccion de la pagina que se va a ingresar la RAM:   ");
		scanf("%d",&indice);
		Nodo_Virtual = ir_a_posV(&Memoria_Virtual,indice);
		if(Nodo_Virtual->actv==0){
			Nodo_Fisico=MarcoDisponible(&Memoria_Fisica);
			if(Nodo_Fisico!=NULL){
				Nodo_Virtual->actv=1;
				Nodo_Virtual->marco=Nodo_Fisico->posicion;
				Nodo_Fisico->pagina=Nodo_Virtual->posicion;
				Nodo_Fisico->actv=1;
                                traducir(Nodo_Fisico,Nodo_Virtual);
			}
                        if(Nodo_Fisico==NULL){
                                printf("\n\n\t\t\t\t      MEMORIA LLENA \n\n ");
                                direccionesF(&Memoria_Fisica);   
                                printf("Ingrese la direccion de la pagina que se va a reemplazar:   ");
		                        scanf("%d",&reemp);                      
                                Nodo_Fisico=LiberarMarco(&Memoria_Fisica,reemp);
                                nodov *aux=ir_a_posV(&Memoria_Virtual, Nodo_Fisico->pagina );
                                aux->marco=-1;
                                aux->actv=0;
                                Nodo_Fisico->pagina=-1;
                                Nodo_Fisico->actv=0;
                                Nodo_Virtual->actv=1;
                                printf("\n\n Limpiando Marco de pagina  %d\n\n ",Nodo_Fisico->posicion);
                                system("sleep 3");
                                traducir(Nodo_Fisico,aux);
                                Nodo_Virtual->marco=Nodo_Fisico->posicion;
                                Nodo_Fisico->pagina=Nodo_Virtual->posicion;
                                Nodo_Fisico->actv=1;
                                printf("\n\n Poniendo Pagina  %d  en el marco de Pagina  %d\n\n ",Nodo_Virtual->posicion,Nodo_Fisico->posicion);
                                traducir(Nodo_Fisico,Nodo_Virtual);
			}
		}else{
			printf("\n\n\t Esta pagina ya se encuentra en un marco\n\n\n ");
		}

	}
}

void str_vec(char dir[], int dirR[]){
	int i,j;
	int aux[5];
	for (i = 4; i >=0;i--){
		aux[i]=dir[i]-48;
	}
	for(i = 0,j=4; i<5;i++,j--){
		dirR[i]=aux[j];
	}
}

void traducir(nodof *nodofis,nodov *nodovir){
    int dir[12]={0,0,0,0,0,0,0,0,0,0,0,0};
    int i;
    for(i=0;i<pow(2,12);i++){
        printf(" Direccion de Memoria Virtual:\t\t %d%d%d%d%d %d%d%d%d%d%d%d%d%d%d%d%d\t\t Direccion de Memoria Fisica:\t\t %d%d%d%d %d%d%d%d%d%d%d%d%d%d%d%d\n",nodovir->dir[4],nodovir->dir[3],nodovir->dir[2],nodovir->dir[1],nodovir->dir[0],dir[11],dir[10],dir[9],dir[8],dir[7],dir[6],dir[5],dir[4],dir[3],dir[2],dir[1],dir[0],nodofis->dir[3],nodofis->dir[2],nodofis->dir[1],nodofis->dir[0],dir[11],dir[10],dir[9],dir[8],dir[7],dir[6],dir[5],dir[4],dir[3],dir[2],dir[1],dir[0]);
        system("sleep .001");
        rec(dir,0);        
    }
}

int suma_bin(int numadd,int bit){
    int res=0;
    res=numadd+bit;
    return res;
}

void rec(int *dir,int num){
    int aux;
    aux=suma_bin(dir[num],1);
    if(aux==2){
        dir[num]=0;
        if(num+1<12){
            rec(dir,num+1);
        }
    }else{
        dir[num]=aux;
    }
}
