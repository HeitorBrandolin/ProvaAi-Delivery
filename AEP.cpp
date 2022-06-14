#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>
FILE *arq;
int qntloja=0, qntmoto=0, qntcli=0;
int x,y;
struct q{
	char nome[55],telefone[15];
	char cpf[15], cep[10], cnpj[21], cnh[12];
};
struct loj{
	//empresa nome cnpj
	struct q a;
	char empresa[51];
}loja[100];
struct client{
	//telefone cpf nome cep estado cidade rua
	struct q a;
	char estado[10], cidade[50], rua[55];
}cliente[100];

struct mot{
	//cpf telefone cnh placa renavam ano veiculo nome
	struct q a;
	char placa[9], renavam[12], ano[5], veiculo[51];
}moto[100];

bool leitura=false;
void leituracli();
void menucli();
void leituramoto();
void menumoto();
void leituraloja();
void menuloja();
void tabelacli();
void tabelamoto();
void tabelaloja();

void salvaloja();
void salvamoto();
void salvacli();


int cadcli();
int editcli();
int delcli();

int cadmoto();
int editmoto();
int delmoto();

int cadloja();
int editloja();
int delloja();

void troca(char* aa,char*bb){
	char tmpc[200];
	strcpy(tmpc,aa);
	strcpy(aa,bb);
	strcpy(bb,tmpc);
}
void classificacao(int cont, int tipo){
	int tmp;
	for(x=0;x<cont-1;x++)
		for(y=x+1;y<cont;y++){
			if(tipo==1){
				tmp=strcmp(cliente[x].a.nome,cliente[y].a.nome);
				if(tmp==1){
					troca(cliente[x].a.nome,     cliente[y].a.nome);
					troca(cliente[x].a.cpf,      cliente[y].a.cpf);
					troca(cliente[x].a.telefone, cliente[y].a.telefone);
					troca(cliente[x].a.cep,      cliente[y].a.cep);
					troca(cliente[x].estado,     cliente[y].estado);
					troca(cliente[x].cidade,     cliente[y].cidade);
					troca(cliente[x].rua,        cliente[y].rua);
				}
			}
			
			if(tipo==2){
				tmp=strcmp(loja[x].a.nome,loja[y].a.nome);
				if(tmp==1){
					troca(loja[x].a.nome,      loja[y].a.nome);
					troca(loja[x].a.cnpj,      loja[y].a.cnpj);
					troca(loja[x].empresa,     loja[y].empresa);
				}
			}
			
			if(tipo==3){
				tmp=strcmp(moto[x].a.nome,moto[y].a.nome);
				if(tmp==1){
					troca(moto[x].a.nome,      moto[y].a.nome);
					troca(moto[x].a.cpf,       moto[y].a.cpf);
					troca(moto[x].a.telefone,  moto[y].a.telefone);
					troca(moto[x].a.cnh,       moto[y].a.cnh);
					troca(moto[x].ano,         moto[y].ano);
					troca(moto[x].renavam,     moto[y].renavam);
					troca(moto[x].placa,       moto[y].placa);
					troca(moto[x].veiculo,     moto[y].veiculo);
				}
			}
		}
}

void caixa(char* a){
	char y='=';
	
	printf("    ");
	
	for(x=0;x<28;x++)
		printf("="); //linha 1 printa   ===============
		
	for(x=0;x<3;x++){
		if(x!=1){ // linha 2 e 4 printa   |          |
			printf("\n%5c",y);
			printf("%27c",y);
		}
		else // linha 3 printa   |  (palavra)  |
			printf("\n%5c%20s%7c",y,a,y);	
	}
	
	printf("\n    ");
	
	for(x=0;x<28;x++) // linha 5 printa   ===============
		printf("=");
		
	printf("\n");
}

void MenuPrincipal(){
	int opcao=999, saida=0;
	do{
		system("cls");
		caixa("MENU     ");
		printf("\n    1 - CLIENTE");
		printf("\n    2 - ENTREGADOR");
		printf("\n    3 - LOJA");
		printf("\n    0 - SAIR");
		printf("\n\n    DIGITE O QUE QUER FAZER: ");
		scanf("%d",&opcao);
		fflush(stdin);
		
		switch(opcao){			
			case 0:
				saida=1;
				break;
			case 1:
				menucli();
				break;
			case 2:
				menumoto();
				break;
			case 3:
				menuloja();
				break;	
		}
	}while(saida!=1);
}


/*classificacao(qntcli,1);
classificacao(qntloja,2);
classificacao(qntmoto,3);
*/

int main(){
	leituramoto();
	leituraloja();
	leituracli();
	MenuPrincipal();
	
	return(0);
}


/////////////////////////////////////////////////////////
void leituracli(){
		arq=fopen("CLIENTE.txt","r");
  	if (arq==NULL)
  		leitura=false;
  	else{ 
  		leitura=true;
		while(!feof(arq)){
			fseek(arq,0,SEEK_CUR);
			fgets(cliente[qntcli].a.cpf, 15, arq); 
			cliente[qntcli].a.cpf[strlen(cliente[qntcli].a.cpf)]='\0';
			
			fseek(arq,2,SEEK_CUR);
			fgets(cliente[qntcli].a.telefone, 15, arq); 
			cliente[qntcli].a.telefone[strlen(cliente[qntcli].a.telefone)]='\0';

			fseek(arq,2,SEEK_CUR);
			fgets(cliente[qntcli].a.nome, 51, arq);
			while(cliente[qntcli].a.nome[strlen(cliente[qntcli].a.nome)-1]=='.')
				cliente[qntcli].a.nome[strlen(cliente[qntcli].a.nome)-1]='\0';
			cliente[qntcli].a.nome[strlen(cliente[qntcli].a.nome)-1]='\0';
			
			fseek(arq,2,SEEK_CUR);
			fgets(cliente[qntcli].a.cep, 10, arq); 
			cliente[qntcli].a.cep[strlen(cliente[qntcli].a.cep)]='\0';
			
			fseek(arq,1,SEEK_CUR);
			fgets(cliente[qntcli].estado, 3, arq); 
			cliente[qntcli].estado[strlen(cliente[qntcli].estado)]='\0';
			
			fseek(arq,1,SEEK_CUR);
			fgets(cliente[qntcli].cidade, 31, arq); 
			while(cliente[qntcli].cidade[strlen(cliente[qntcli].cidade)-1]=='.')
				cliente[qntcli].cidade[strlen(cliente[qntcli].cidade)-1]='\0';
			cliente[qntcli].cidade[strlen(cliente[qntcli].cidade)-1]='\0';
			
			fseek(arq,1,SEEK_CUR);
			fgets(cliente[qntcli].rua, 53, arq); 
			while(cliente[qntcli].rua[strlen(cliente[qntcli].rua)-2]=='.')
				cliente[qntcli].rua[strlen(cliente[qntcli].rua)-1]='\0';
			cliente[qntcli].rua[strlen(cliente[qntcli].rua)-2]='\0';
			qntcli++;
		}
		qntcli--;
		fclose(arq);
	}
}
void menucli(){
		int opcao=999, saida=0;
	do{
		system("cls");
		caixa("CLIENTE    ");
		printf("\n    1 - Cadastrar Cliente");
		printf("\n    2 - Editar Cliente");
		printf("\n    3 - Excluir Cliente");
		printf("\n    4 - Consultar lista de Clientes");
		printf("\n    0 - VOLTAR");
		printf("\n\n    DIGITE O QUE QUER FAZER: ");
		scanf("%d",&opcao);
		fflush(stdin);
		switch(opcao){			
			case 0:
				saida=1;
				break;
			case 1:
				cadcli();
				break;
			case 2:
				editcli();
				break;
			case 3:
				delcli();
				break;
			case 4:
				system("cls");
				tabelacli();
				system("pause");
				break;
		}
	}while(saida!=1);
}

int cadcli(){
	char nnome[100], ncpf[50], ntelefone[50], nrua[100], nestado[10], ncidade[50], ncep[50];
	int retorno;
	system("cls");
	caixa("NOVO CLIENTE  ");
	printf("    Insira 0 no Nome caso deseje retornar ao menu\n");
	printf("\n    Nome: ");
	gets(nnome);
	nnome[strlen(nnome)]='\0';
	retorno=strcmp(nnome,"0");
	if(retorno==0)
		return 0;
	nnome[0]=toupper(nnome[0]);
	
	printf("    CPF(XXX.XXX.XXX-XX): ");
	gets(ncpf);
	ncpf[strlen(ncpf)]='\0';
	
	printf("    TELEFONE( (XX)XXXXX-XXXX ): ");
	gets(ntelefone);
	ntelefone[strlen(ntelefone)]='\0';
	
	printf("    CEP(XXXXX-XXX): ");
	gets(ncep);
	ncep[strlen(ncep)]='\0';
	
	printf("    ESTADO(ex:PR): ");
	gets(nestado);
	nestado[strlen(nestado)]='\0';
	
	printf("    CIDADE: ");
	gets(ncidade);
	ncidade[strlen(ncidade)]='\0';
	
	printf("    ENDERECO: ");
	gets(nrua);
	nrua[strlen(nrua)]='\0';
	
	printf("\n    CADASTRADO COM SUCESSO, ");
	strcpy(cliente[qntcli].a.nome,nnome);
	strcpy(cliente[qntcli].a.cpf,ncpf);
	strcpy(cliente[qntcli].a.telefone,ntelefone);
	strcpy(cliente[qntcli].a.cep,ncep);
	strcpy(cliente[qntcli].cidade,ncidade);
	strcpy(cliente[qntcli].estado,nestado);
	strcpy(cliente[qntcli].rua,nrua);
	qntcli++;
	classificacao(qntcli,1);
	system("pause");
	return 0;
}

int editcli(){
	int indice,opcao,retorno;
	char cpfi[100],novo[200];
	system("cls");
	caixa("EDITAR CLIENTE");
	printf("    Insira 0 caso deseje retornar ao menu\n\n");
	printf("    Informe o CPF(XXX.XXX.XXX-XX): ");
	gets(cpfi);
	retorno=strcmp(cpfi,"0");
	if(retorno==0)
		return 0;
	cpfi[strlen(cpfi)]='\0';
	for(x=0;x<qntcli;x++){
		retorno=strcmp(cpfi,cliente[x].a.cpf);
		if(retorno==0){
			indice=x;
			break;
		}
	}
	system("cls");
	caixa("EDITAR CLIENTE");
	printf("    Insira 0 caso deseje retornar ao menu\n\n");
	printf("    1 - Nome:     %s",cliente[indice].a.nome);
	printf("\n    2 - Telefone: %s",cliente[indice].a.telefone);
	printf("\n    3 - Endereco: %s  %s - %s",cliente[indice].a.cep,cliente[indice].estado,cliente[indice].cidade);
	printf("\n                  %s",cliente[indice].rua);
	printf("\n\n    QUAL OPCAO DESEJA EDITAR: ");
	scanf("%d",&opcao);
	fflush(stdin);
	if(opcao==0)
		return 0;
	system("cls");
	caixa("EDITAR CLIENTE");
	if(opcao==1){
		printf("\n    Nome: %s",cliente[indice].a.nome);
		printf("\n    Novo NOME: ");
		gets(novo);
		novo[strlen(novo)]='\0';
		novo[0]=toupper(novo[0]);
		strcpy(cliente[indice].a.nome,novo);
	}
	if(opcao==2){
		printf("\n    Telefone: %s",cliente[indice].a.telefone);
		printf("\n    Novo TELEFONE( (XX)XXXXX-XXXX ): ");
		gets(novo);
		novo[strlen(novo)]='\0';
		strcpy(cliente[indice].a.telefone,novo);
	}
	if(opcao==3){
		printf("\n    Endereco: %s  %s - %s",cliente[indice].a.cep,cliente[indice].estado,cliente[indice].cidade);
		printf("\n              %s",cliente[indice].rua);
		printf("\n    Novo CEP(XXXXX-XXX): ");
		gets(novo);
		novo[strlen(novo)]='\0';
		strcpy(cliente[indice].a.cep,novo);
		printf("    Novo ESTADO(ex. PR): ");
		gets(novo);
		novo[strlen(novo)]='\0';
		strcpy(cliente[indice].estado,novo);
		printf("    Nova CIDADE: ");
		gets(novo);
		novo[strlen(novo)]='\0';
		strcpy(cliente[indice].cidade,novo);
		printf("    Nova RUA: ");
		gets(novo);
		novo[strlen(novo)]='\0';
		strcpy(cliente[indice].rua,novo);
	}
	classificacao(qntcli,1);
	printf("\n\n    EDITADO COM SUCESSO,");
	system("pause");
	return 0;	
}

int delcli(){
	int indice,opcao,retorno;
	char cpfi[100];
	system("cls");
	caixa("EXCLUIR CLIENTE");
	printf("    Insira 0 caso deseje retornar ao menu\n\n");
	printf("    Informe o CPF(XXX.XXX.XXX-XX): ");
	gets(cpfi);
	retorno=strcmp(cpfi,"0");
	if(retorno==0)
		return 0;
	cpfi[strlen(cpfi)]='\0';
	for(x=0;x<qntcli;x++){
		retorno=strcmp(cpfi,cliente[x].a.cpf);
		if(retorno==0){
			indice=x;
			break;
		}
	}
	system("cls");
	caixa("EXCLUIR CLIENTE");
	printf("    Insira 0 caso deseje retornar ao menu\n\n");
	printf("    CPF:      %s",cliente[indice].a.cpf);
	printf("\n    Nome:     %s",cliente[indice].a.nome);
	printf("\n    Telefone: %s",cliente[indice].a.telefone);
	printf("\n    Endereco: %s  %s - %s",cliente[indice].a.cep,cliente[indice].estado,cliente[indice].cidade);
	printf("\n              %s",cliente[indice].rua);
	printf("\n\n    DESEJA MESMO EXCLUIR CLIENTE(1=SIM / 0=NAO): ");
	scanf("%d",&opcao);
	fflush(stdin);
	if(opcao==0)
		return 0;
	else if(opcao==1){
		qntcli--;
		strcpy(cliente[indice].a.nome,cliente[qntcli].a.nome);
		strcpy(cliente[indice].a.telefone,cliente[qntcli].a.telefone);
		strcpy(cliente[indice].a.cep,cliente[qntcli].a.cep);
		strcpy(cliente[indice].a.cpf,cliente[qntcli].a.cpf);
		strcpy(cliente[indice].cidade,cliente[qntcli].cidade);
		strcpy(cliente[indice].estado,cliente[qntcli].estado);
		strcpy(cliente[indice].rua,cliente[qntcli].rua);
		classificacao(qntcli,1);
		printf("\n    ITEM DELETADO, ");
		system("pause");
		return 0;
	}
}

void tabelacli(){
	for(x=0;x<qntcli;x++){
		printf("%3d %-50s CPF:%-20s TELEFONE:%s\n",x+1,cliente[x].a.nome,cliente[x].a.cpf,cliente[x].a.telefone);
		printf("    ENDERECO:%-41s CEP:%-20s CIDADE:%s-%s \n",cliente[x].rua,cliente[x].a.cep,cliente[x].cidade,cliente[x].estado);
		for(y=0;y<110;y++)
			printf("_");
		printf("\n");
	}
}

void salvacli(){
	
}
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
void leituramoto(){
		arq=fopen("MOTORISTA.txt","r");
  	if (arq==NULL)
  		leitura=false;
  	else{ 
  		leitura=true;
		while(!feof(arq)){
			fseek(arq,0,SEEK_CUR);
			fgets(moto[qntmoto].a.cpf, 15, arq); 
			moto[qntmoto].a.cpf[strlen(moto[qntmoto].a.cpf)]='\0';
			
			fseek(arq,2,SEEK_CUR);
			fgets(moto[qntmoto].a.telefone, 15, arq); 
			moto[qntmoto].a.telefone[strlen(moto[qntmoto].a.telefone)]='\0';
			
			fseek(arq,2,SEEK_CUR);
			fgets(moto[qntmoto].a.cnh, 12, arq); 
			moto[qntmoto].a.cnh[strlen(moto[qntmoto].a.cnh)]='\0';
			
			fseek(arq,2,SEEK_CUR);
			fgets(moto[qntmoto].placa, 9, arq); 
			moto[qntmoto].placa[strlen(moto[qntmoto].placa)]='\0';
			
			fseek(arq,2,SEEK_CUR);
			fgets(moto[qntmoto].renavam, 12, arq); 
			moto[qntmoto].renavam[strlen(moto[qntmoto].renavam)]='\0';
			
			fseek(arq,2,SEEK_CUR);
			fgets(moto[qntmoto].ano, 5, arq); 
			moto[qntmoto].ano[strlen(moto[qntmoto].ano)]='\0';
			
			fseek(arq,2,SEEK_CUR);
			fgets(moto[qntmoto].veiculo, 51, arq); 
			while(moto[qntmoto].veiculo[strlen(moto[qntmoto].veiculo)-1]=='.')
				moto[qntmoto].veiculo[strlen(moto[qntmoto].veiculo)-1]='\0';
			moto[qntmoto].veiculo[strlen(moto[qntmoto].veiculo)-1]='\0';
			
			fseek(arq,2,SEEK_CUR);
			fgets(moto[qntmoto].a.nome, 53, arq);
			while(moto[qntmoto].a.nome[strlen(moto[qntmoto].a.nome)-2]=='.')
				moto[qntmoto].a.nome[strlen(moto[qntmoto].a.nome)-1]='\0';
			moto[qntmoto].a.nome[strlen(moto[qntmoto].a.nome)-2]='\0';
		
			qntmoto++;
		}
		qntmoto--;
		fclose(arq);
	}
}
void menumoto(){
		int opcao=999, saida=0;
	do{
		system("cls");
		caixa("ENTREGADOR  ");
		printf("\n    1 - Cadastrar Entregador");
		printf("\n    2 - Editar Entregador");
		printf("\n    3 - Excluir Entregador");
		printf("\n    4 - Consultar lista de Entregadores");
		printf("\n    0 - VOLTAR");
		printf("\n\n    DIGITE O QUE QUER FAZER: ");
		scanf("%d",&opcao);
		fflush(stdin);
		switch(opcao){			
			case 0:
				saida=1;
				break;
			case 1:
				cadmoto();
				break;
			case 2:
				editmoto();
				break;
			case 3:
				delmoto();
				break;	
			case 4:
				system("cls");
				tabelamoto();
				system("pause");
				break;
		}
	}while(saida!=1);
}

int cadmoto(){
	char nnome[100], ncpf[50], ntelefone[50], nveiculo[100], nano[10], nplaca[50], ncnh[50], nrenavam[50];
	int retorno;
	system("cls");
	caixa("NOVO ENTREGADOR");
	printf("    Insira 0 no Nome caso deseje retornar ao menu\n");
	printf("\n    Nome: ");
	gets(nnome);
	nnome[strlen(nnome)]='\0';
	retorno=strcmp(nnome,"0");
	if(retorno==0)
		return 0;
	nnome[0]=toupper(nnome[0]);
	
	printf("    CPF(XXX.XXX.XXX-XX): ");
	gets(ncpf);
	ncpf[strlen(ncpf)]='\0';
	
	printf("    TELEFONE( (XX)XXXXX-XXXX ): ");
	gets(ntelefone);
	ntelefone[strlen(ntelefone)]='\0';
	
	printf("    CNH: ");
	gets(ncnh);
	ncnh[strlen(ncnh)]='\0';
	
	printf("    VEICULO: ");
	gets(nveiculo);
	nveiculo[strlen(nveiculo)]='\0';
	
	printf("    ANO: ");
	gets(nano);
	nano[strlen(nano)]='\0';
	
	printf("    PLACA: ");
	gets(nplaca);
	nplaca[strlen(nplaca)]='\0';
	
	printf("    RENAVAM: ");
	gets(nrenavam);
	nrenavam[strlen(nrenavam)]='\0';
	
	printf("\n    CADASTRADO COM SUCESSO, ");
	strcpy(moto[qntmoto].a.nome,nnome);
	strcpy(moto[qntmoto].a.cpf,ncpf);
	strcpy(moto[qntmoto].a.telefone,ntelefone);
	strcpy(moto[qntmoto].a.cnh,ncnh);
	strcpy(moto[qntmoto].ano,nano);
	strcpy(moto[qntmoto].placa,nplaca);
	strcpy(moto[qntmoto].renavam,nrenavam);
	strcpy(moto[qntmoto].veiculo,nveiculo);
	qntmoto++;
	salvamoto();
	system("pause");
	return 0;
}

int editmoto(){
	int indice,opcao,retorno;
	char cpfi[100],novo[200];
	system("cls");
	caixa("EDITAR ENTREGADOR");
	printf("    Insira 0 caso deseje retornar ao menu\n\n");
	printf("    Informe o CPF(XXX.XXX.XXX-XX): ");
	gets(cpfi);
	retorno=strcmp(cpfi,"0");
	if(retorno==0)
		return 0;
	cpfi[strlen(cpfi)]='\0';
	for(x=0;x<qntmoto;x++){
		retorno=strcmp(cpfi,moto[x].a.cpf);
		if(retorno==0){
			indice=x;
			break;
		}
	}
	system("cls");
	caixa("EDITAR ENTREGADOR");
	printf("    Insira 0 caso deseje retornar ao menu\n\n");
	printf("    1 - Nome:     %s",moto[indice].a.nome);
	printf("\n    2 - Telefone: %s",moto[indice].a.telefone);
	printf("\n    3 - Veiculo:  %s  %s",moto[indice].ano,moto[indice].placa);
	printf("\n                  %s",moto[indice].veiculo);
	printf("\n         RENAVAM: %s",moto[indice].renavam);
	printf("\n\n    QUAL OPCAO DESEJA EDITAR: ");
	scanf("%d",&opcao);
	fflush(stdin);
	if(opcao==0)
		return 0;
	system("cls");
	caixa("EDITAR ENTREGADOR");
	if(opcao==1){
		printf("\n    Nome: %s",moto[indice].a.nome);
		printf("\n    Novo NOME: ");
		gets(novo);
		novo[strlen(novo)]='\0';
		novo[0]=toupper(novo[0]);
		strcpy(moto[indice].a.nome,novo);
	}
	if(opcao==2){
		printf("\n    Telefone: %s",moto[indice].a.telefone);
		printf("\n    Novo TELEFONE( (XX)XXXXX-XXXX ): ");
		gets(novo);
		novo[strlen(novo)]='\0';
		strcpy(moto[indice].a.telefone,novo);
	}
	if(opcao==3){
		printf("\n    Veiculo: %s  %s",moto[indice].ano,moto[indice].placa);
		printf("\n             %s",moto[indice].veiculo);
		printf("\n    RENAVAM: %s",moto[indice].renavam);
		printf("\n    Novo Veiculo: ");
		gets(novo);
		novo[strlen(novo)]='\0';
		strcpy(moto[indice].veiculo,novo);
		printf("    ANO: ");
		gets(novo);
		novo[strlen(novo)]='\0';
		strcpy(moto[indice].ano,novo);
		printf("    PLACA: ");
		gets(novo);
		novo[strlen(novo)]='\0';
		strcpy(moto[indice].placa,novo);
		printf("    RENAVAM: ");
		gets(novo);
		novo[strlen(novo)]='\0';
		strcpy(moto[indice].renavam,novo);
	}
	salvamoto();
	printf("\n    EDITADO COM SUCESSO,");
	system("pause");
	return 0;	
}

int delmoto(){
	int indice,opcao,retorno;
	char cpfi[100],novo[200];
	system("cls");
	caixa("EXCLUIR ENTREGADOR");
	printf("    Insira 0 caso deseje retornar ao menu\n\n");
	printf("    Informe o CPF(XXX.XXX.XXX-XX): ");
	gets(cpfi);
	retorno=strcmp(cpfi,"0");
	if(retorno==0)
		return 0;
	cpfi[strlen(cpfi)]='\0';
	for(x=0;x<qntmoto;x++){
		retorno=strcmp(cpfi,moto[x].a.cpf);
		if(retorno==0){
			indice=x;
			break;
		}
	}
	system("cls");
	caixa("EXCLUIR ENTREGADOR");
	printf("    Insira 0 caso deseje retornar ao menu\n\n");
	printf("    Nome:     %s",moto[indice].a.nome);
	printf("\n    Telefone: %s",moto[indice].a.telefone);
	printf("\n    Veiculo:  %s  %s",moto[indice].ano,moto[indice].placa);
	printf("\n              %s",moto[indice].veiculo);
	printf("\n     RENAVAM: %s",moto[indice].renavam);
	printf("\n\n    DESEJA MESMO EXCLUIR ENTREGADOR(1=SIM / 0=NAO): ");
	scanf("%d",&opcao);
	fflush(stdin);
	if(opcao==0)
		return 0;
	else if(opcao==1){
		qntmoto--;
		strcpy(moto[indice].a.nome,moto[qntmoto].a.nome);
		strcpy(moto[indice].a.telefone,moto[qntmoto].a.telefone);
		strcpy(moto[indice].a.cpf,moto[qntmoto].a.cpf);
		strcpy(moto[indice].a.cnh,moto[qntmoto].a.cnh);
		strcpy(moto[indice].ano,moto[qntmoto].ano);
		strcpy(moto[indice].veiculo,moto[qntmoto].veiculo);
		strcpy(moto[indice].placa,moto[qntmoto].placa);
		strcpy(moto[indice].renavam,moto[qntmoto].renavam);
		salvamoto();
		printf("\n    ITEM DELETADO, ");
		system("pause");
		return 0;
	}
}

void tabelamoto(){
	for(int x=0;x<qntmoto;x++){
		printf("%3d %-50s CPF:%-20s TELEFONE:%s\n",x+1,moto[x].a.nome,moto[x].a.cpf,moto[x].a.telefone);
		printf("    VEICULO:%-42s ANO:%-20s PLACA:%s\n",moto[x].veiculo,moto[x].ano,moto[x].placa);
		printf("    CNH:%-46s RENAVAM:%s\n",moto[x].a.cnh,moto[x].renavam);
		for(y=0;y<110;y++)
			printf("_");
		printf("\n");
	}
}

void salvamoto(){
	char tmpveiculo[100];
	char tmpnome[100];
	classificacao(qntmoto,3);
	arq=fopen("MOTORISTA.txt","w");
	for(x=0;x<qntmoto;x++){
		for(y=0;y<100;y++){
			tmpveiculo[y]='\0';
			tmpnome[y]='\0';
		}
		strcpy(tmpveiculo,moto[x].veiculo);
		strcpy(tmpnome,moto[x].a.nome);
		tmpveiculo[strlen(tmpveiculo)]=' ';
		tmpnome[strlen(tmpnome)]=' ';
		for(y=0;y<55;y++){
			tmpveiculo[strlen(tmpveiculo)]='.';
			tmpnome[strlen(tmpnome)]='.';
		}
		tmpveiculo[50]='\0';
		tmpnome[50]='\0';
		
		fprintf(arq,"%s  %s  %s  %s  %s  %s  %s  %s\n",moto[x].a.cpf,moto[x].a.telefone,moto[x].a.cnh,moto[x].placa,moto[x].renavam,moto[x].ano,tmpveiculo,tmpnome);
	}
	fclose(arq);
}

/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
void leituraloja(){
		arq=fopen("LOJA.txt","r");
  	if (arq==NULL)
  		leitura=false;
  	else{ 
  		leitura=true;
		while(!feof(arq)){
			fseek(arq,0,SEEK_CUR);
			fgets(loja[qntloja].a.cnpj, 19, arq); 
			loja[qntloja].a.cnpj[strlen(loja[qntloja].a.cnpj)]='\0';
			
			fseek(arq,2,SEEK_CUR);
			fgets(loja[qntloja].empresa,51, arq);
			while(loja[qntloja].empresa[strlen(loja[qntloja].empresa)-1]=='.')
				loja[qntloja].empresa[strlen(loja[qntloja].empresa)-1]='\0';
			loja[qntloja].empresa[strlen(loja[qntloja].empresa)-1]='\0';
			
			fseek(arq,2,SEEK_CUR);
			fgets(loja[qntloja].a.nome, 52, arq);
			while(loja[qntloja].a.nome[strlen(loja[qntloja].a.nome)-2]=='.')
				loja[qntloja].a.nome[strlen(loja[qntloja].a.nome)-1]='\0';
			loja[qntloja].a.nome[strlen(loja[qntloja].a.nome)-2]='\0';
			
			qntloja++;
		}
		qntloja--;
		fclose(arq);
	}
}
void menuloja(){
		int opcao=999, saida=0;
	do{
		system("cls");
		caixa("LOJA     ");
		printf("\n    1 - Cadastrar Loja");
		printf("\n    2 - Editar Loja");
		printf("\n    3 - Excluir Loja");
		printf("\n    4 - Consultar lista de Lojas");
		printf("\n    0 - VOLTAR");
		printf("\n\n    DIGITE O QUE QUER FAZER: ");
		scanf("%d",&opcao);
		fflush(stdin);
		switch(opcao){			
			case 0:
				saida=1;
				break;
			case 1:
				cadloja();
				break;
			case 2:
				editloja();
				break;
			case 3:
				delloja();
				break;	
			case 4:
				system("cls");
				tabelaloja();
				system("pause");
				break;
		}
	}while(saida!=1);
}

int cadloja(){
	char nloja[51], ncnpj[21], ntitular[55];
	int retorno;
	system("cls");
	caixa("NOVA LOJA   ");
	printf("    Insira 0 no nome da loja caso deseje retornar ao menu\n");
	
	printf("\n    Nome da Loja: ");
	gets(nloja);
	retorno=strcmp(nloja,"0");
	if(retorno==0)
		return 0;
	nloja[strlen(nloja)]='\0';
	nloja[0]=toupper(nloja[0]);
	
	printf("    Nome do Titular da Empresa: ");
	gets(ntitular);
	ntitular[strlen(ntitular)]='\0';
	ntitular[0]=toupper(ntitular[0]);
	
	printf("    CNPJ(XX.XXX.XXX/XXXX-XX): ");
	gets(ncnpj);
	ncnpj[strlen(ncnpj)]='\0';
	
	printf("\n    CADASTRADO COM SUCESSO, ");
	strcpy(loja[qntloja].empresa,nloja);
	strcpy(loja[qntloja].a.nome,ntitular);
	strcpy(loja[qntloja].a.cnpj,ncnpj);
	qntloja++;
	salvaloja();
	system("pause");
	return 0;
}

int editloja(){
	int indice,opcao;
	char novo[100];
	system("cls");
	caixa("EDITAR LOJA  ");
	printf("    Insira 0 caso deseje retornar ao menu\n\n");
	tabelaloja();
	printf("\nESCOLHA O NUMERO DA LOJA (1 a %d): ",qntloja);
	scanf("%d",&indice);
	fflush(stdin);
	if(indice==0)
		return 0;
	indice--;
	
	system("cls");
	caixa("EDITAR LOJA  ");
	printf("    Insira 0 no nome da loja caso deseje retornar ao menu\n");
	printf("\n    1- TITULAR: %s",loja[indice].a.nome);
	printf("\n    2- LOJA:    %s",loja[indice].empresa);
	printf("\n    3- CNPJ:    %s",loja[indice].a.cnpj);
	printf("\n\n    ESCOLHA A OPCAO: ");
	scanf("%d",&opcao);
	fflush(stdin);
	if(opcao==0)
		return 0;
		
	system("cls");
	caixa("EDITAR LOJA");
	if(opcao==1){
		printf("\n    TITULAR: %s",loja[indice].a.nome);
		printf("\n    NOVO TITULAR: ");
		gets(novo);
		novo[0]=toupper(novo[0]);
		strcpy(loja[indice].a.nome,novo);
	}
	else if(opcao==2){
		printf("\n    LOJA: %s",loja[indice].empresa);
		printf("\n    NOVO NOME DE LOJA: ");
		gets(novo);
		novo[0]=toupper(novo[0]);
		strcpy(loja[indice].empresa,novo);
	}
	else if(opcao==3){
		printf("\n    CNPJ: %s",loja[indice].a.cnpj);
		printf("\n    NOVO CNPJ (XX.XXX.XXX/XXXX-XX): ");
		gets(novo);
		strcpy(loja[indice].a.cnpj,novo);
	}
	salvaloja();
	printf("\n\n    EDITADO COM SUCESSO,");
	system("pause");
	return 0;
}

int delloja(){
	int indice,opcao;
	system("cls");
	caixa("EXCLUIR LOJA ");
	printf("    Insira 0 caso deseje retornar ao menu\n\n");
	tabelaloja();
	printf("\nESCOLHA O NUMERO DA LOJA (1 a %d): ",qntloja);
	scanf("%d",&indice);
	fflush(stdin);
	if(indice==0)
		return 0;
	indice--;
	
	system("cls");
	caixa("EXCLUIR LOJA ");
	printf("\n");
	printf("\n    TITULAR: %s",loja[indice].a.nome);
	printf("\n    LOJA:    %s",loja[indice].empresa);
	printf("\n    CNPJ:    %s",loja[indice].a.cnpj);
	printf("\n\n    TEM CERTEZA QUE DESEJA REMOVER (1=SIM / 0=NAO): ");
	scanf("%d",&opcao);
	fflush(stdin);
	if(opcao==0)
		return 0;
	else{
		qntloja--;
		strcpy(loja[indice].a.nome,loja[qntloja].a.nome);
		strcpy(loja[indice].empresa,loja[qntloja].empresa);
		strcpy(loja[indice].a.cnpj,loja[qntloja].a.cnpj);
		salvaloja();
		printf("\n    ITEM DELETADO, ");
		system("pause");
		return 0;
	}
	
}

void tabelaloja(){
	printf("%3s %-50s %-40s %s\n"," ","TITULAR","EMPRESA","CNPJ");
	for(x=0;x<120;x++)
		printf("_");
	printf("\n");
	for(x=0;x<qntloja;x++)
		printf("%3d %-50s %-40s %s\n",x+1,loja[x].a.nome,loja[x].empresa,loja[x].a.cnpj);
}

void salvaloja(){
	char tmpempresa[100];
	char tmpnome[100];
	classificacao(qntloja,2);
	arq=fopen("LOJA.txt","w");
	for(x=0;x<qntloja;x++){
		for(y=0;y<100;y++){
			tmpempresa[y]='\0';
			tmpnome[y]='\0';
		}
		strcpy(tmpempresa,loja[x].empresa);
		strcpy(tmpnome,loja[x].a.nome);
		tmpempresa[strlen(tmpempresa)]=' ';
		tmpnome[strlen(tmpnome)]=' ';
		for(y=0;y<55;y++){
			tmpempresa[strlen(tmpempresa)]='.';
			tmpnome[strlen(tmpnome)]='.';
		}
		tmpempresa[50]='\0';
		tmpnome[50]='\0';
		
		fprintf(arq,"%s  %s  %s\n",loja[x].a.cnpj,tmpempresa,tmpnome);
	}		
	fclose(arq);
}
/////////////////////////////////////////////////////////


