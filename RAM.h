#include <stdlib.h>
#include <stdio.h>
typedef struct NODOF{
	struct NODOF *sig;
	int posicion;
	int ini;
	int fin;
	int pagina;
	int dir[4];
	int actv;	
}nodof;
typedef struct RAM{
	nodof *ini;
	nodof *fin;
	int tam;
}RAM;
nodof* CreaNodoFisco();
void Iniciar_nodof(nodof *);
void IniciarRAM(RAM *);
void AnadeNodoFisico(RAM *,nodof *);
void invertirF (nodof *);
void binarioF(nodof *); 
void Crear_Mem_Fis(RAM *);
void direccionesF(RAM *);
nodof* ir_a_posF(RAM *, int );
nodof* MarcoDisponible(RAM *);
nodof* LiberarMarco(RAM *, int );


nodof* CreaNodoFisco(){
	nodof *neow;
	neow = (nodof *) malloc (sizeof(nodof));
	return neow;
}
void Iniciar_nodof(nodof *nod){
	nod->sig = NULL;
	nod->actv = 0;
	nod->dir[0]=0;
	nod->dir[1]=0;
	nod->dir[2]=0;
    nod->dir[3]=0;	
	nod->fin=0;
	nod->ini=0;
	nod->posicion=0;
	nod->pagina=-1;
}
void IniciarRAM(RAM *vir){
	vir->fin=NULL;
	vir->ini=NULL;
	vir->tam=0;
}
void AnadeNodoFisico(RAM *vir,nodof *nod){
	if (vir->ini==NULL && vir->fin==NULL){
		vir->fin=vir->ini=nod;
		nod->fin=128;
	}else{
		vir->fin->sig=nod;
		nod->ini=vir->fin->fin;
		nod->fin= nod->ini + 128;
		nod->posicion=vir->fin->posicion + 1;
		vir->fin=nod;
		binarioF(nod);
		vir->tam +=1;
	}
	
}
void invertirF (nodof *nodv){
int org[3];
int i,j;
for(i=0; i<3;i++){
    org[i]=nodv->dir[i];
} 
for(i = 0,j=2; i<3;i++,j--){
    nodv->dir[i]=org[j];
}
}
void binarioF(nodof *nodv){
	int i;
	int res=nodv->posicion;
	for(i=0;i<4;i++){
		nodv->dir[i]=res%2;
		res=(int)res/2;
	}
}
void Crear_Mem_Fis(RAM *Mem){
	nodof *now;
	int i;
	for (i = 0; i < 16; i++){
		now = CreaNodoFisco();
		Iniciar_nodof(now);
		AnadeNodoFisico(Mem,now);		
	}
}
void direccionesF(RAM *Mem){
	nodof *nod=Mem->ini;
	int i;
    printf(" \n\n\t\t\t\t\t\tRAM\n\n ");
	printf("\t\tInicio Fin                  Pagina	        Activo\n ");	
	for(i=0; i<=Mem->tam; i++){
	    printf("\t\t %d Bytes -   %d Bytes         %d          %d\n",nod->ini,nod->fin,nod->pagina,nod->actv);
	    if(i!=Mem->tam){
	    nod=nod->sig;
		}	
	}	
}
nodof* ir_a_posF(RAM *Mem, int pos){
 nodof *aux=Mem->ini;
 nodof *ret;
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
nodof* MarcoDisponible(RAM *Mem){
	nodof *nod=Mem->ini;
	nodof *Resp=NULL;
	int i;	
	for(i=0; i<=Mem->tam; i++){
		if(nod->actv==0){
			Resp=nod;
			break;
		}
	    if(i!=Mem->tam){
	    nod=nod->sig;
		}	
	}	
	return Resp;
}
nodof* LiberarMarco(RAM *Mem, int num){
	nodof *nod=ir_a_posF(Mem, num);
	nodof *Resp=NULL;
        Resp=nod;	
	return Resp;
}
