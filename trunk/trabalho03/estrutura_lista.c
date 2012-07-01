#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "estrutura_lista.h"


int getEndRelativo()
{
	int ret=prox_end_relativo;
	prox_end_relativo++;
	return ret;
}

void alocaTabelaSimbolos()
{
  tabela = (simbolo *) malloc(MAXLENGTH * sizeof(simbolo)); 
}

void realocaTabelaSimbolos(int novo_tamanho)
{
    realoca(&tabela, novo_tamanho);
}

void realoca (simbolo **p, int novo_tamanho)
{
        simbolo *realocado;
        realocado = realloc ((*p), novo_tamanho * sizeof(simbolo));
        (*p) = realocado;
        
}

int insere (simbolo p)
{
     int i=0,j;
     while(i<numero_simbolos && strcmp(tabela[i].nome,p.nome)<0)
        ++i;
     fflush(stdout);
	 
	 /*caso exista alguma entrada na tabela de simbolos com o mesmo nome, deve-se verificar se eh permitido*/
	 if(i<numero_simbolos && strcmp(tabela[i].nome,p.nome)==0)
	 {
		 /*se as variaveis tem o mesmo tipo e pertencem ao mesmo escopo. ERRO: redeclaracao de variavel*/
		 while(i<numero_simbolos && strcmp(tabela[i].nome,p.nome)==0){
			 if(tabela[i].tipo == p.tipo && tabela[i].contexto == p.contexto)
				return 0;
			
			/*se as variaveis nao tem o mesmo tipo, isso so eh permitido se alguma delas for PROGRAM ou PROCEDURE. ERRO: tipos conflitantes*/
			if(tabela[i].tipo != p.tipo && tabela[i].tipo != PROGRAM && tabela[i].tipo !=PROCEDURE && p.tipo != PROGRAM && p.tipo !=PROCEDURE && tabela[i].contexto == p.contexto)
				return -1;
			
			i++;
		 }
	 }
	 
     for(j=numero_simbolos;j>i;--j)
          tabela[j]= tabela[j-1];
     
     tabela[i]=p;
	 return 1;
}
int busca (char *nome,int tipo,int contexto)
{
	int i=0;

	while(i<numero_simbolos && strcmp(tabela[i].nome,nome)<0)
		++i;
	
	if(i<numero_simbolos && strcmp(tabela[i].nome,nome)==0)
	{
		while(i<numero_simbolos && strcmp(tabela[i].nome,nome)==0){
			if(tabela[i].contexto==contexto){
				if((tabela[i].tipo==VAR_INT || tabela[i].tipo==PARAM_INT)  && tipo==EXPRESSAO) return INTEGER;
				if((tabela[i].tipo==VAR_REAL || tabela[i].tipo==PARAM_REAL) && tipo==EXPRESSAO) return REAL;
				if((tabela[i].tipo==VAR_INT)  && tipo==ATTR) return INTEGER;
				if((tabela[i].tipo==VAR_REAL) && tipo==ATTR) return REAL;
				if(tabela[i].tipo==PROCEDURE && tipo==PROCEDURE) return PROCEDURE_TRUE;
			}
			if(tabela[i].tipo==CONST_INT  && tipo==EXPRESSAO) return INTEGER;
			if(tabela[i].tipo==CONST_REAL  && tipo==EXPRESSAO) return REAL;
			
			if(tipo==ATTR && (tabela[i].tipo==CONST_INT || tabela[i].tipo==CONST_REAL)){
				return CONST_FALSE;
			}
			i++;
		}
	}
	
	return NAO_EXISTE;
}

int insereNumInt (char *nome, int valor, int contexto)
{
	int retorno;
    simbolo p;
    p.nome=nome;
	p.tipo = NUM_INT;
    p.contexto = contexto;
    p.valori=valor;
	p.end_relativo=getEndRelativo();
	p.valorf=-1.0;
    retorno = insere(p);
	if(retorno ==1)
	    ++numero_simbolos;
	return retorno;
}

int insereNumReal (char *nome, double valor, int contexto)
{
	int retorno;
    simbolo p;
    p.nome=nome;
	p.tipo = NUM_REAL;
    p.contexto = contexto;
    p.valorf=valor;
	p.end_relativo=getEndRelativo();
	p.valori=-1;
	retorno = insere(p);
	if(retorno ==1)
		++numero_simbolos;
	return retorno;
}

int insereConstInt (char *nome, int valor, int contexto)
{
	int retorno;
	simbolo p;
	p.nome=nome;
	p.tipo = CONST_INT;
	p.contexto = contexto;
	p.valori=valor;
	p.end_relativo=getEndRelativo();
	p.valorf=-1.0;
	retorno = insere(p);
	if(retorno ==1)
		++numero_simbolos;
 	return retorno;
}

int insereConstReal (char *nome, double valor, int contexto)
{
	int retorno;
	simbolo p;
	p.nome=nome;
	p.tipo = CONST_REAL;
	p.contexto = contexto;
	p.valorf=valor;
	p.end_relativo=getEndRelativo();
	p.valori=-1;
	retorno = insere(p);
	if(retorno ==1)
		++numero_simbolos;
	return retorno;
}

int insereProcedure (char *nome, int contexto)
{
	int retorno;
	simbolo p;
	p.nome=nome;
	p.tipo = PROCEDURE;
	p.valorf=-1;
	p.valori=-1;
	p.contexto = contexto;
	retorno = insere(p);
	if(retorno ==1)
		++numero_simbolos;
	return retorno;
}

int insereProgram (char *nome)
{
	int retorno;
	simbolo p;
	p.nome=nome;
	p.tipo = PROGRAM;
	p.valorf=-1;
	p.valori=-1;
	p.contexto = 0;
	p.end_relativo=-1;
	retorno = insere(p);
	if(retorno ==1)
		++numero_simbolos;
	return retorno;
}


int insereVarInt (char *nome, int contexto)
{
	int retorno;
	simbolo p;
	p.nome=nome;
	p.tipo = VAR_INT;
	p.contexto = contexto;
	p.end_relativo=getEndRelativo();
	p.valori=-1;
	p.valorf=-1.0;
	retorno = insere(p);
	if(retorno ==1)
		++numero_simbolos;
	return retorno;
}

int insereVarReal (char *nome, int contexto)
{
	int retorno;
	simbolo p;
	p.nome=nome;
	p.tipo = VAR_REAL;
	p.contexto = contexto;
	p.end_relativo=getEndRelativo();
	p.valori=-1;
	p.valorf=-1.0;
	retorno = insere(p);
	if(retorno ==1)
		++numero_simbolos;
	return retorno;
}

int insereParamInt (char *nome, int contexto)
{
	int retorno;
	simbolo p;
	p.nome=nome;
	p.tipo = PARAM_INT;
	p.contexto = contexto;
	p.end_relativo=getEndRelativo();
	p.valori=-1;
	p.valorf=-1.0;
	retorno = insere(p);
	if(retorno ==1)
		++numero_simbolos;
	return retorno;
}

int insereParamReal (char *nome, int contexto)
{
	int retorno;
	simbolo p;
	p.nome=nome;
	p.tipo = PARAM_REAL;
	p.contexto = contexto;
	p.end_relativo=getEndRelativo();
	p.valori=-1;
	p.valorf=-1.0;
	retorno = insere(p);
	if(retorno ==1)
		++numero_simbolos;
	return retorno;
}

int deleta (simbolo *tabela, simbolo p, int tamanho)
{
     int i=0,j;
     while(i<tamanho && strcmp(tabela[i].nome,p.nome)!= 0)
        ++i;
     /*saiu porque encontrou*/
     if(i<tamanho)
     {
      for(j=i;j<tamanho-1;++j)
          tabela[j]= tabela[j+1];
      return 1;
     }
     return 0;
}

void printTabela(){
	int i;
	printf("|Nro\tTipo\tNome\t\tValor Int\tValor Float\tEnd Relativo\tContexto\t|\n");
	for(i=0;i<numero_simbolos; i++){
		printf("|%d\t%d\t%s\t\t%8d\t%lf\t%d\t\t%d\t\t|\n",i,tabela[i].tipo,tabela[i].nome, tabela[i].valori, tabela[i].valorf, tabela[i].end_relativo, tabela[i].contexto);
	}
}
/*
int main(int argc, char **argv)
{
    alocaTabelaSimbolos();
    
    insereNumInt("baaaa",12,0);
    insereNumReal("aaaa",12.876,0);
    insereConstInt("vahne",12,0);
    insereConstReal("fabio",1.2,0);
    insereProcedure("isa",0);
    
    printf("%s %lf\n",tabela[0].nome,tabela[0].valorf);
    printf("%s %d\n",tabela[1].nome,tabela[1].valori);  
     printf("%s %lf\n",tabela[2].nome,tabela[2].valorf); 
     printf("%s\n",tabela[3].nome);  
     printf("%s %d\n",tabela[4].nome,tabela[4].valori);
     
    return 0;
}*/
