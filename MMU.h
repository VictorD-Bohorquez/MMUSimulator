#include <stdio.h>
#include <stdlib.h>

typedef struct NODOV{
	struct NODOV *sig;
	int posicion;
	int ini;
	int fin;
	int marco;
	int dir[5];
	int actv;	
}nodov;

typedef struct MMU{
	nodov *ini;
	nodov *fin;
	int tam;
}MMU;

nodov* CreaNodoVirtual();
void Iniciar_nodov(nodov *);
void IniciarMMU(MMU *);
void AnadeNodoVirtual(MMU *,nodov *);
void invertirV (nodov *);
void binarioV(nodov *); 
void Crear_Mem_Vir(MMU *);
void direccionesV(MMU *);
nodov* ir_a_posV(MMU *, int );

nodov* CreaNodoVirtual(){
	nodov *neow;
	neow = (nodov *) malloc (sizeof(nodov));
	return neow;
}
void Iniciar_nodov(nodov *nod){
	nod->sig = NULL;
	nod->actv = 0;
	nod->dir[0]=0;
	nod->dir[1]=0;
	nod->dir[2]=0;
	nod->dir[3]=0;	
    nod->dir[4]=0;
	nod->fin=0;
	nod->ini=0;
	nod->posicion=0;
	nod->marco=-1;
}
void IniciarMMU(MMU *vir){
	vir->fin=NULL;
	vir->ini=NULL;
	vir->tam=0;
}
void AnadeNodoVirtual(MMU *vir,nodov *nod){
	if (vir->ini==NULL && vir->fin==NULL){
		vir->fin=vir->ini=nod;
		nod->fin=128;
	}else{
		vir->fin->sig=nod;
		nod->ini=vir->fin->fin;
		nod->fin= nod->ini + 128;
		nod->posicion=vir->fin->posicion + 1;
		vir->fin=nod;
		binarioV(nod);
		vir->tam +=1;
	}
	
}

void binarioV(nodov *nodv){
	int i;
	int res=nodv->posicion;
	for(i=0;i<5;i++){
		nodv->dir[i]=res%2;
		res=(int)res/2;
	}
}
void Crear_Mem_Vir(MMU *Mem){
	nodov *now;
	int i;
	for (i = 0; i < 32; i++){
		now = CreaNodoVirtual();
		Iniciar_nodov(now);
		AnadeNodoVirtual(Mem,now);		
	}
}
void direccionesV(MMU *Mem){
	nodov *nod=Mem->ini;
	int i;
        printf(" \n\n\t\t\t\tMMU\n\n ");
	printf(" Inicio	    Fin     Indice      Marco	        Activo \n");
	for(i=0; i<=Mem->tam; i++){
	    printf("  %d Bytes  -   %d Bytes     %d         %d               %d \n",nod->ini,nod->fin,nod->posicion,nod->marco,nod->actv);
	    if(i!=Mem->tam){
	    nod=nod->sig;
		}	
	}	
}
nodov* ir_a_posV(MMU *Mem, int pos){
 nodov *aux=Mem->ini;
 nodov *ret;
 int i;
 if (Mem->tam!=0){
 	if(pos>=0 && pos<=(Mem->tam)){
 		if (pos==0){
 			ret=Mem->ini;
 			return ret;
		 }else{
		 	if(pos==(Mem->tam)){
		 		ret=Mem->fin;
		 		return ret;
			 }else{
			 	for(i=0;i<(pos);i++){
			 		aux=aux->sig;
				 }				 
				 return aux;
			 }
		 }
	 }else{
	 	return NULL;
	 }
 }
 
}


