#include <iostream>
#include <sys/time.h> 

using namespace std;

int main(){
	int TLIM= 10;
	struct timeval tv1,tv2;	// gettimeofday() secs-usecs
	char k[] ="draculaso\0";
	int p = 2;
	int cont=0;
	int tan = 0;
	while(k[tan]!='\0'){
			tan++;	
	}
	p^=4;
	int clave;
	gettimeofday(&tv1,NULL);
		cout<<"Introduce la clave 1: "<<endl;
		cin>>clave;
	gettimeofday(&tv2,NULL);
	if (tv2.tv_sec - tv1.tv_sec > TLIM){
		cout<<"El tiempo es importante pequeño padawan"<<endl;
		exit(-1);
	}
	int res = p^clave;
	if(res!=0){
		cout<<"Te pille no me hagas trampas"<<endl;
		exit(-1);
	}
	else{
		char o[10];
		gettimeofday(&tv1,NULL);
		cout<<"Introduce la clave 2: "<<endl;
		cin>>o;
		gettimeofday(&tv2,NULL);
		while(o[cont]!='\0'){
			cont++;	
		}
		if(tan==cont){
			int i=0;
			for(;i<tan && o[i] == k[i];i++);
			if (tv1.tv_sec - tv2.tv_sec > TLIM){
				cout<<"El tiempo es importante pequeño padawan"<<endl;
				exit(-1);
			}
			else
			if(i!=tan){
				cout<<"Te pille no me hagas trampas"<<endl;
				exit(-1);
			}
			else
			{
				cout<<"Te lo deje facil y lo desactivaste, no sera asi la proxima"<<endl;
			}
			
			
		}
		else
		{
			cout<<"Te pille no me hagas trampas"<<endl;
		}
		
	}
	
}
