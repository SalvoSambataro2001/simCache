#include <iostream>
using namespace std;

class posCache{
public:
	int dato;
	bool libera;
	int contLRU;
	int contFIFO;
	posCache(int val,bool libera,int contLRU,int contFIFO) : dato(val) , libera(libera) , contLRU(contLRU) , contFIFO(contFIFO) {}
	posCache() : posCache (0,true,0,0) {}
	posCache(int val) : posCache(val,false,0,0) {}

	/*friend ostream &operator << (ostream &out , posCache p){
		if(p.libera)
			out<<"non occupata";
		else
			out<<p.dato;
		return out;
	} */

	friend ostream &operator << (ostream &out , posCache p){
		if(p.libera)
			out<<"non occupata";
		else
			out<<p.dato;
		return out;
	}

};