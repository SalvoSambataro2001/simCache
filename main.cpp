#include <iostream>
#include "posCache.h"
#include <cstdlib>
#include <ctime>
#include<conio.h>
#include<windows.h>
#include<math.h>

using namespace std;

bool potenzaDiDue(int);
void colora(int);

int main(){

	int dimMemoria,dimCache,dimBlocco;
	int scelta;
	int i,j;
	int dato;

	cout<<"\t\t ________________________________________________________________________"<<endl<<"\t\t|"<<"\t\t\t\t\t\t\t\t\t |"<<endl;
	cout<<"\t        | Simulatore di indirizzamento della cache. BY Salvatore Alfio Sambataro |"<<endl;
	cout<<"\t\t|________________________________________________________________________|"<<endl<<endl<<endl;

					///////////////////  DIMENSIONE BLOCCO   /////////////////////////
	cout<<"Scrivi il numero di parole in un singolo blocco di memoria: ";
	cin>>dimBlocco;
	while(dimBlocco<1 || !potenzaDiDue(dimBlocco)){
		if(dimBlocco<1){
			colora(12);
			cout<<"Ogni blocco deve avere almeno una parola. Riscrivi il numero di parole per blocco: ";
			colora(7);
			cin>>dimBlocco;
		}

		else{
			colora(12);
			cout<<"Le parole devono essere una potenza di due. Riscrivi il numero di parole per blocco: ";
			colora(7);
			cin>>dimBlocco;
		}
	}

					///////////////////  CREAZIONE CACHE   /////////////////////////

	cout<<"Scrivi il numero di posizioni di cache disponibili: ";
	cin>>dimCache;
	while(dimCache<1 || !potenzaDiDue(dimCache)){
		if(dimCache<1){
			colora(12);
			cout<<"La cache deve avere almeno una posizione! Riscrivi la dimensione: ";
			colora(7);
			cin>>dimCache;
		}

		else{
			colora(12);
			cout<<"La dimensione della cache deve essere una potenza di due. Riscrivi la dimensione: ";
			colora(7);
			cin>>dimCache;
		}
	}

	posCache cache[dimCache][dimBlocco];


			/////////////////// CREAZIONE E INIZIALIZZAZIONE MEMORIA   /////////////////////////

	cout<<"Scrivi il numero di posizioni di memoria disponibili: ";
	cin>>dimMemoria;
	while(dimMemoria<1 || !potenzaDiDue(dimMemoria) || dimMemoria <= dimCache){
		if(dimMemoria<1){
			colora(12);
			cout<<"La memoria deve avere almeno una posizione! Riscrivi la dimensione: ";
			colora(7);
			cin>>dimMemoria;
		}

		else if(dimMemoria <= dimCache){
			colora(12);
			cout<<"La memoria deve essere piu' grande della cache. Riscrivi la dimensione: ";
			colora(7);
			cin>>dimMemoria;
		}

		else{
			colora(12);
			cout<<"La dimensione della memoria deve essere una potenza di due. Riscrivi la dimensione: ";
			colora(7);
			cin>>dimMemoria;
		}
	}

	cout<<endl<<" ********** CARICAMENTO DELLA MEMORIA **********"<<endl<<endl;
	int memoria [dimMemoria][dimBlocco];

	cout<<"0. Inserisci manualmente i valori;"<<endl;
	cout<<"1. Inizializzazione random (valori da -128 a +127)"<<endl;
	cout<<"Scegli: ";
	cin>>scelta;

	while(scelta!=0 && scelta!=1){
		colora(12);
		cout<<"Scelta non riconosciuta. Riprova a inserire: ";
		colora(7);
		cin>>scelta;
	}

	if(scelta==0){
		for(i=0;i<dimMemoria;i++){
			for(j=0;j<dimBlocco;j++){
				cout<<"Inserisci il dato alla posizione di memoria " <<i<<" parola "<<j<<":  ";
				cin>>memoria[i][j];
			}
		}
	}

	else{
		srand(time(0));
		for(i=0;i<dimMemoria;i++)
			for(j=0;j<dimBlocco;j++){
				memoria[i][j]=rand()%256-128;
			}
	}

	/////////////////// SCELTA INDIRIZZAMENTO /////////////////////

	cout<<endl<<" ********** SCELTA TIPO DI INDIRIZZAMENTO **********"<<endl<<endl;

	cout<<endl<<"Che tipo di indirizzamento di cache vuoi simulare?"<<endl;
	cout<<"1 : Indirizzamento diretto;"<<endl;
	cout<<"2 : Indirizzamento associativo;"<<endl;
	cout<<"3 : Indirizzamento associativo a gruppi;"<<endl;
	cout<<"Fai la tua scelta: ";
	cin>>scelta;
	while(scelta!=1 && scelta !=2 && scelta !=3){
		colora(12);
		cout<<"Scelta non riconosciuta. Riprova a inserire: ";
		colora(7);
		cin>>scelta;
	}
	system("cls");

	switch(scelta){

					//////////////////////// DIRETTO //////////////////////

		case 1:
			scelta=-1;
			while(scelta!=6){
				cout<<endl<<endl<<"*********************"<<endl<<endl<<"\t\tMenu'\t\t"<<endl<<endl;
				cout<<"1. Inserisci nuovo valore in cache;"<<endl;
				cout<<"2. Modifica valori in memoria;"<<endl;
				cout<<"3. Stampa la cache;"<<endl;
				cout<<"4. Stampa il contenuto della memoria;"<<endl;
				cout<<"5. Leggi un blocco di cache;"<<endl;
				cout<<"6. Fine programma;"<<endl<<endl;
				cout<<"Scegli: ";
				cin>>scelta;
				if(scelta==1){
					int pos;
					cout<<"Quale posizione di memoria vuoi caricare in cache: ";
					cin>>pos;
					while(pos>=dimMemoria || pos<0){
						colora(12);
						cout<<"Le posizioni di memoria vanno da 0 a "<<(dimMemoria-1)<<". Inserisci un valore adeguato: ";
						colora(7);
						cin>>pos;
					}
					if(cache[pos%dimCache][0].libera==false){
						colora(12);
						cout<<"Impossibile salvare in cache le parole di memoria del blocco di posizione "<<pos<<" perche' la posizione di cache corrispondente e' gia' occupata..."<<endl;
						colora(7);
					}
					else{
						for(j=0;j<dimBlocco;j++){
							posCache c(memoria[pos][j]);
							cache[pos%dimCache][j]=c;
						}

						for(j=0;j<dimBlocco;j++)
							cache[pos%dimCache][j].contFIFO=0;

						for(i=0;i<dimCache;i++)
							if(i!=pos%dimCache)
								for(j=0;j<dimBlocco;j++){
									cache[i][j].contFIFO++;
									cache[i][j].contLRU++;
						}

					}

				}

				else if(scelta==2){
					int pos,parola,val;
					cout<<endl<<" ********  STAMPA DELLA MEMORIA   ********"<<endl<<endl;
					for( i=0;i<dimMemoria;i++){
						cout<<"\t\t"<<i<<". | ";
						for( j=0;j<dimBlocco;j++)
							cout<<memoria[i][j]<<" | ";
						cout<<endl;
					}
					cout<<endl<<endl<<"Quale posizione della memoria devo modificare: ";
					cin>>pos;
					while(pos>=dimMemoria || pos<0){
						colora(12);
						cout<<"Le posizioni di memoria vanno da 0 a "<<(dimMemoria-1)<<". Inserisci un valore adeguato: ";
						colora(7);
						cin>>pos;
					}
					cout<<"Quale parola di memoria devo modificare: ";
					cin>>parola;
					while(parola>=dimBlocco || parola<0){
						colora(12);
						cout<<"Ogni blocco di memoria ha parole che vanno da 0 a "<<(dimBlocco-1)<<". Inserisci un valore adeguato: ";
						colora(7);
						cin>>parola;
					}

					cout<<"La parola "<<parola<<" della posizione "<<pos<<" conteneva il valore "<<memoria[pos][parola]<<endl;
					cout<<"Inserire un nuovo valore: ";
					cin>>val;
					memoria[pos][parola]=val;
				}

				else if(scelta==3){
					cout<<endl<<" ********  STAMPA DELLA CACHE ATTUALE   ********"<<endl<<endl;
					for(i=0;i<dimCache;i++){
						if(cache[i][0].libera==false)
							cout<<" FIFO: "<<cache[i][0].contFIFO<<" ; LRU: "<<cache[i][0].contLRU<<" --> ";
						else
							cout<<"\t\t      ";
						cout<<i<<". | ";
						for(j=0;j<dimBlocco;j++)
							cout<<cache[i][j]<<" | ";
						cout<<endl;
					}
				}

				else if(scelta==4){
					cout<<endl<<" ********  STAMPA DELLA MEMORIA   ********"<<endl<<endl;
					for( i=0;i<dimMemoria;i++){
						cout<<"\t\t"<<i<<". | ";
						for( j=0;j<dimBlocco;j++)
							cout<<memoria[i][j]<<" | ";
						cout<<endl;
					}
					cout<<endl<<endl;

				}

				else if(scelta==5){
					int blocco;
					cout<<endl<<"Quale blocco di cache si vuole leggere? ";
					cin>>blocco;
					while(blocco>=dimCache || blocco<0){
							colora(12);
							cout<<"Le posizioni di cache vanno da 0 a "<<(dimCache-1)<<". Inserisci un valore adeguato: ";
							colora(7);
							cin>>blocco;
					}

					if(cache[blocco][0].libera==true){
						colora(12);
						cout<<"Il blocco di cache "<<blocco<<" non e' ancora stato caricato..."<<endl<<endl;
						colora(7);
					}

					else{
						cout<<endl<<"\t\t**** BLOCCO DI CACHE "<<blocco<<" ****"<<endl<<endl;
							cout<<" FIFO: "<<cache[blocco][0].contFIFO<<" ; LRU: "<<cache[blocco][0].contLRU<<" --> ";
						cout<<blocco<<". | ";
						for(j=0;j<dimBlocco;j++)
							cout<<cache[blocco][j]<<" | ";

						for(j=0;j<dimBlocco;j++)
								cache[blocco][j].contLRU=0;

						for(i=0;i<dimCache;i++)
							if(i!=blocco)
								for(j=0;j<dimBlocco;j++)
									cache[i][j].contLRU++;
					}
				}

				else if(scelta==6){}

				else{
					colora(12);
					cout<<"Errore nella scelta. Riprova..."<<endl;
					colora(7);
				}			
				
			}
			break;


					////////////////////// ASSOCIATIVO /////////////////////


		case 2:
			
			scelta=-1;
			while(scelta!=6){
				cout<<endl<<endl<<"*********************"<<endl<<endl<<"\t\tMenu'\t\t"<<endl<<endl;
				cout<<"1. Inserisci nuovo valore in cache;"<<endl;
				cout<<"2. Modifica valori in memoria;"<<endl;
				cout<<"3. Stampa la cache;"<<endl;
				cout<<"4. Stampa il contenuto della memoria;"<<endl;
				cout<<"5. Leggi un blocco di cache;"<<endl;
				cout<<"6. Fine programma;"<<endl<<endl;
				cout<<"Scegli: ";
				cin>>scelta;
				if(scelta==1){
					int pos;
					cout<<"Quale posizione di memoria vuoi caricare in cache: ";
					cin>>pos;
					while(pos>=dimMemoria || pos<0){
						colora(12);
						cout<<"Le posizioni di memoria vanno da 0 a "<<(dimMemoria-1)<<". Inserisci un valore adeguato: ";
						colora(7);
						cin>>pos;
					}

					cout<<"Posizioni di cache disponibili: ";
					int posLibere=0;

					for(i=0;i<dimCache;i++)
						if(cache[i][0].libera==true){
							cout<<" "<<i<<" ;";
							posLibere++;
						}
					cout<<endl;

					if(posLibere==0) {
						colora(12);
						cout<<"NESSUNA.";
						colora(7);
						cout<<endl<<endl<<"\t\t***** SOSTITUZIONE BLOCCO DI CACHE *****"<<endl<<endl;
						cout<<"0. Non sostituire posizioni"<<endl;
						cout<<"1. Sostituzione casuale;"<<endl;
						cout<<"2. Sostituzione FIFO;"<<endl;
						cout<<"3. Sostituzione LRU;"<<endl;
						cout<<"Scegli:"<<endl;
						cin>>scelta;
						while(scelta!=0 && scelta!= 1 && scelta!= 2 && scelta!= 3){
							colora(12);
							cout<<"Carattere non riconosciuto. Reinserisci: ";
							colora(7);
							cin>>scelta;
						}

						if(scelta==1){
							srand(time(0));
							int casuale= rand()%dimCache;
							cout<<"Sto caricando il blocco di memoria nella posizione di cache "<<casuale<<" (scelta casuale) ..."<<endl;
							for(j=0;j<dimBlocco;j++){
								posCache c(memoria[pos][j]);
								cache[casuale][j]=c;
							}

							for(j=0;j<dimBlocco;j++)
								cache[casuale][j].contFIFO=0;

							for(i=0;i<dimCache;i++)
								if(i!=casuale)
									for(j=0;j<dimBlocco;j++){
										cache[i][j].contFIFO++;
										cache[i][j].contLRU++;
									}

						}

						else if (scelta==2){
							int maxFIFO=-1;
							int maxIndice=-1;
							for(i=0;i<dimCache;i++)
								if(cache[i][0].contFIFO > maxFIFO){
									maxFIFO = cache[i][0].contFIFO;
									maxIndice = i;
								}

							cout<<"Sto caricando il blocco di memoria nella posizione di cache "<<maxIndice<<" (blocco CARICATO meno recentemente) ..."<<endl;
							for(j=0;j<dimBlocco;j++){
								posCache c(memoria[pos][j]);
								cache[maxIndice][j]=c;
							}

							for(j=0;j<dimBlocco;j++)
								cache[maxIndice][j].contFIFO=0;

							for(i=0;i<dimCache;i++)
								if(i!=maxIndice)
									for(j=0;j<dimBlocco;j++){
										cache[i][j].contFIFO++;
										cache[i][j].contLRU++;
									}

						}

						else if(scelta==3){
							int maxLRU=-1;
							int maxIndice=-1;
							for(i=0;i<dimCache;i++)
								if(cache[i][0].contLRU > maxLRU){
									maxLRU = cache[i][0].contLRU;
									maxIndice= i;
								}

							cout<<"Sto caricando il blocco di memoria nella posizione di cache "<<maxIndice<<" (blocco USATO meno recentemente) ..."<<endl;
							for(j=0;j<dimBlocco;j++){
								posCache c(memoria[pos][j]);
								cache[maxIndice][j]=c;
							}

							for(j=0;j<dimBlocco;j++)
								cache[maxIndice][j].contFIFO=0;

							for(i=0;i<dimCache;i++)
								if(i!=maxIndice)
									for(j=0;j<dimBlocco;j++){
										cache[i][j].contFIFO++;
										cache[i][j].contLRU++;
									}
						}

						else{
							colora(12);
							cout<<"Nessuna modifica alla cache effettuata."<<endl;
							colora(7);
						}
					}

					else{
						int posizioneCache=0;

						while(cache[posizioneCache][0].libera==false)
							posizioneCache++;

						cout<<"Carico il blocco di memoria scelto nella posizione di cache "<<posizioneCache<<" (la prima disponibile) ..."<<endl<<endl;

						for(j=0;j<dimBlocco;j++){
								posCache c(memoria[pos][j]);
								cache[posizioneCache][j]=c;
						}

						for(j=0;j<dimBlocco;j++)
							cache[posizioneCache][j].contFIFO=0;

						for(i=0;i<dimCache;i++)
							if(i!=posizioneCache)
								for(j=0;j<dimBlocco;j++){
									cache[i][j].contFIFO++;
									cache[i][j].contLRU++;
								}
					}


					cout<<endl;
				}

				else if(scelta==2){
					int pos,parola,val;
					cout<<endl<<" ********  STAMPA DELLA MEMORIA   ********"<<endl<<endl;
					for( i=0;i<dimMemoria;i++){
						cout<<"\t\t"<<i<<". | ";
						for( j=0;j<dimBlocco;j++)
							cout<<memoria[i][j]<<" | ";
						cout<<endl;
					}

					cout<<endl<<endl<<"Quale posizione della memoria devo modificare: ";
					cin>>pos;
					while(pos>=dimMemoria || pos<0){
						colora(12);
						cout<<"Le posizioni di memoria vanno da 0 a "<<(dimMemoria-1)<<". Inserisci un valore adeguato: ";
						colora(7);
						cin>>pos;
					}
					cout<<"Quale parola di memoria devo modificare: ";
					cin>>parola;
					while(parola>=dimBlocco || parola<0){
						colora(12);
						cout<<"Ogni blocco di memoria ha parole che vanno da 0 a "<<(dimBlocco-1)<<". Inserisci un valore adeguato: ";
						colora(7);
						cin>>parola;
					}

					cout<<"La parola "<<parola<<" della posizione "<<pos<<" conteneva il valore "<<memoria[pos][parola]<<endl;
					cout<<"Inserire un nuovo valore: ";
					cin>>val;
					memoria[pos][parola]=val;
				}

				else if(scelta==3){
					cout<<endl<<" ********  STAMPA DELLA CACHE ATTUALE   ********"<<endl<<endl;
					for(i=0;i<dimCache;i++){
						if(cache[i][0].libera==false)
							cout<<" FIFO: "<<cache[i][0].contFIFO<<" ; LRU: "<<cache[i][0].contLRU<<" --> ";
						else
							cout<<"\t\t      ";
						cout<<i<<". | ";
						for(j=0;j<dimBlocco;j++)
							cout<<cache[i][j]<<" | ";
						cout<<endl;
					}
				}

				else if(scelta==4){
					cout<<endl<<" ********  STAMPA DELLA MEMORIA   ********"<<endl<<endl;
					for( i=0;i<dimMemoria;i++){
						cout<<"\t\t"<<i<<". | ";
						for( j=0;j<dimBlocco;j++)
							cout<<memoria[i][j]<<" | ";
						cout<<endl;
					}

					cout<<endl<<endl;

				}

				else if(scelta==5){
					int blocco;
					cout<<"Quale blocco di cache si vuole leggere? ";
					cin>>blocco;
					while(blocco>=dimCache || blocco<0){
							colora(12);
							cout<<"Le posizioni di cache vanno da 0 a "<<(dimCache-1)<<". Inserisci un valore adeguato: ";
							colora(7);
							cin>>blocco;
					}

					if(cache[blocco][0].libera==true){
						colora(12);
						cout<<"Il blocco di cache "<<blocco<<" non e' ancora stato caricato..."<<endl<<endl;
						colora(7);
					}

					else{
						cout<<endl<<"\t\t**** BLOCCO DI CACHE "<<blocco<<" ****"<<endl<<endl;
							cout<<" FIFO: "<<cache[blocco][0].contFIFO<<" ; LRU: "<<cache[blocco][0].contLRU<<" --> ";
						cout<<blocco<<". | ";
						for(j=0;j<dimBlocco;j++)
							cout<<cache[blocco][j]<<" | ";

						cout<<endl<<endl;

						for(j=0;j<dimBlocco;j++)
								cache[blocco][j].contLRU=0;

						for(i=0;i<dimCache;i++)
							if(i!=blocco)
								for(j=0;j<dimBlocco;j++)
									cache[i][j].contLRU++;
					}

				}

				else if(scelta==6){}

				else{
					colora(12);
					cout<<"Errore nella scelta. Riprova..."<<endl;
					colora(7);
				}			
				
			}
			break;

							////////////////////// ASSOCIATIVO A GRUPPI/////////////////////

		case 3:
			int nGruppi;
				cout<<"Quanti gruppi vuoi formare: ";
				cin>>nGruppi;
				while(dimCache%nGruppi!=0){
					colora(12);
					cout<<"Hai inserito un numero tale che i gruppi non possono avere uguale dimensione"<<endl;
					colora(7);
					cout<<"Inserisci un nuovo numero di gruppi (divisore di "<<dimCache<<") : ";
					cin>>nGruppi;
				}

			scelta=-1;
			while(scelta!=7){
				cout<<endl<<endl<<"*********************"<<endl<<endl<<"\t\tMenu'\t\t"<<endl<<endl;
				cout<<"1. Inserisci nuovo valore in cache;"<<endl;
				cout<<"2. Modifica valori in memoria;"<<endl;
				cout<<"3. Stampa la cache;"<<endl;
				cout<<"4. Stampa il contenuto della memoria;"<<endl;
				cout<<"5. Stampa intervalli dei gruppi;"<<endl;
				cout<<"6. Leggi un blocco di cache"<<endl;
				cout<<"7. Fine programma;"<<endl<<endl;
				cout<<"Scegli: ";
				cin>>scelta;
				if(scelta==1){
					int pos;
					cout<<"Quale posizione di memoria vuoi caricare in cache: ";
					cin>>pos;
					while(pos>=dimMemoria || pos<0){
						colora(12);
						cout<<"Le posizioni di memoria vanno da 0 a "<<(dimMemoria-1)<<". Inserisci un valore adeguato: ";
						colora(7);
						cin>>pos;
					}

					int inizioGruppo = (dimCache/nGruppi) * (pos % nGruppi);
					int fineGruppo = ((dimCache/nGruppi) * (pos % nGruppi)) + (dimCache/nGruppi) - 1;

					cout<<endl<<"Aggiunta nel "<<((pos%nGruppi)+1)<<"o gruppo"<<endl;
					cout<<"INDICE POSIZIONE DI INIZIO GRUPPO : "<<inizioGruppo<<endl;
					cout<<"INDICE POSIZIONE DI FINE GRUPPO : "<<fineGruppo<<endl;


					cout<<"Posizioni di cache disponibili nel gruppo: ";
					int posLibere=0;

					for(i=inizioGruppo; i<=fineGruppo ; i++){
						if(cache[i][0].libera==true){
							cout<<" "<<i<<" ;";
							posLibere++;
						}
					}

					cout<<endl;

					if(posLibere==0) {
						colora(12);
						cout<<"NESSUNA.";
						colora(7);
						cout<<endl<<endl<<"\t\t***** SOSTITUZIONE BLOCCO DI CACHE *****"<<endl<<endl;
						cout<<"0. Non sostituire posizioni"<<endl;
						cout<<"1. Sostituzione casuale;"<<endl;
						cout<<"2. Sostituzione FIFO;"<<endl;
						cout<<"3. Sostituzione LRU;"<<endl;
						cout<<"Scegli:"<<endl;
						cin>>scelta;
						while(scelta!=0 && scelta!= 1 && scelta!= 2 && scelta!= 3){
							colora(12);
							cout<<"Carattere non riconosciuto. Reinserisci: ";
							colora(7);
							cin>>scelta;
						}

						if(scelta==1){
							srand(time(0));
							int casuale= rand()%(dimCache/nGruppi)+inizioGruppo;
							cout<<"Sto caricando il blocco di memoria nella posizione di cache "<<casuale<<" (scelta casuale) ..."<<endl;
							for(j=0;j<dimBlocco;j++){
								posCache c(memoria[pos][j]);
								cache[casuale][j]=c;
							}

							for(j=0;j<dimBlocco;j++)
								cache[casuale][j].contFIFO=0;

							for(i=inizioGruppo;i<=fineGruppo;i++)
								if(i!=casuale)
									for(j=0;j<dimBlocco;j++){
										cache[i][j].contFIFO++;
										cache[i][j].contLRU++;
									}
						}

						else if(scelta==2){
							int maxFIFO=-1;
							int maxIndice=-1;
							for(i=inizioGruppo;i<=fineGruppo;i++)
								if(cache[i][0].contFIFO > maxFIFO){
									maxFIFO = cache[i][0].contFIFO;
									maxIndice=i;
								}

							cout<<"Sto caricando il blocco di memoria nella posizione di cache "<<maxIndice<<" (blocco CARICATO meno recentemente) ..."<<endl;
							for(j=0;j<dimBlocco;j++){
								posCache c(memoria[pos][j]);
								cache[maxIndice][j]=c;
							}

							for(j=0;j<dimBlocco;j++)
								cache[maxIndice][j].contFIFO=0;

							for(i=inizioGruppo;i<=fineGruppo;i++)
								if(i!=maxIndice)
									for(j=0;j<dimBlocco;j++){
										cache[i][j].contFIFO++;
										cache[i][j].contLRU++;
									}
						}

						else if(scelta==3){
							int maxLRU=-1;
							int maxIndice=-1;

							for(i=inizioGruppo;i<=fineGruppo;i++)
								if(cache[i][0].contLRU > maxLRU){
									maxLRU = cache[i][0].contLRU;
									maxIndice=i;
								}

							cout<<"Sto caricando il blocco di memoria nella posizione di cache "<<maxIndice<<" (blocco USATO meno recentemente) ..."<<endl;
							for(j=0;j<dimBlocco;j++){
								posCache c(memoria[pos][j]);
								cache[maxIndice][j]=c;
							}

							for(j=0;j<dimBlocco;j++)
								cache[maxIndice][j].contFIFO=0;

							for(i=inizioGruppo;i<=fineGruppo;i++)
								if(i!=maxIndice)
									for(j=0;j<dimBlocco;j++){
										cache[i][j].contFIFO++;
										cache[i][j].contLRU++;
									}
						}


						else{
							colora(12);
							cout<<"Nessuna modifica alla cache effettuata."<<endl;
							colora(7);
						}
					}

					else{
						int posizioneCache=inizioGruppo;

						while(cache[posizioneCache][0].libera==false)
							posizioneCache++;

						cout<<"Carico il blocco di memoria scelto nella posizione di cache "<<posizioneCache<<" (la prima disponibile) ..."<<endl<<endl;

						for(j=0;j<dimBlocco;j++){
							posCache c(memoria[pos][j]);
							cache[posizioneCache][j]=c;
						}

						for(j=0;j<dimBlocco;j++)
							cache[posizioneCache][j].contFIFO=0;

						for(i=inizioGruppo;i<=fineGruppo;i++)
							if(i!=posizioneCache)
								for(j=0;j<dimBlocco;j++){
									cache[i][j].contFIFO++;
									cache[i][j].contLRU++;
								}

					}

					cout<<endl;

				}

				else if(scelta==2){
					int pos,parola,val;
					cout<<endl<<" ********  STAMPA DELLA MEMORIA   ********"<<endl<<endl;
					for(i=0;i<dimMemoria;i++){
						cout<<"\t\t"<<i<<". | ";
						for(j=0;j<dimBlocco;j++)
							cout<<memoria[i][j]<<" | ";
						cout<<endl;
					}
					cout<<endl<<endl<<"Quale posizione della memoria devo modificare: ";
					cin>>pos;
					while(pos>=dimMemoria || pos<0){
						colora(12);
						cout<<"Le posizioni di memoria vanno da 0 a "<<(dimMemoria-1)<<". Inserisci un valore adeguato: ";
						colora(7);
						cin>>pos;
					}
					cout<<"Quale parola di memoria devo modificare: ";
					cin>>parola;
					while(parola>=dimBlocco || parola<0){
						colora(12);
						cout<<"Ogni blocco di memoria ha parole che vanno da 0 a "<<(dimBlocco-1)<<". Inserisci un valore adeguato: ";
						colora(7);
						cin>>parola;
					}

					cout<<"La parola "<<parola<<" della posizione "<<pos<<" conteneva il valore "<<memoria[pos][parola]<<endl;
					cout<<"Inserire un nuovo valore: ";
					cin>>val;
					memoria[pos][parola]=val;
				}

				else if(scelta==3){
					cout<<endl<<" ********  STAMPA DELLA CACHE ATTUALE   ********"<<endl<<endl;
					for(i=0;i<dimCache;i++){
						if(cache[i][0].libera==false)
							cout<<" FIFO: "<<cache[i][0].contFIFO<<" ; LRU: "<<cache[i][0].contLRU<<" --> ";
						else
							cout<<"\t\t      ";
						cout<<i<<". | ";
						for(j=0;j<dimBlocco;j++)
							cout<<cache[i][j]<<" | ";
						cout<<endl;
					}
				}

				else if(scelta==4){
					cout<<endl<<" ********  STAMPA DELLA MEMORIA   ********"<<endl<<endl;
					for(i=0;i<dimMemoria;i++){
						cout<<"\t\t"<<i<<". | ";
						for(j=0;j<dimBlocco;j++)
							cout<<memoria[i][j]<< " | ";
						cout<<endl;
					}
					cout<<endl<<endl;

				}

				else if(scelta==5){
					int cont=0;
					for(i=0; i<nGruppi;i++){
						cont++;
						cout<<cont<<"o gruppo : "<<i*(dimCache/nGruppi)<<" --> "<< i*(dimCache/nGruppi)+(dimCache/nGruppi)-1<<endl;

					}
				}

				else if(scelta==6){
					int blocco;
					cout<<"Quale blocco di cache si vuole leggere? ";
					cin>>blocco;
					while(blocco>=dimCache || blocco<0){
							colora(12);
							cout<<"Le posizioni di cache vanno da 0 a "<<(dimCache-1)<<". Inserisci un valore adeguato: ";
							colora(7);
							cin>>blocco;
					}

					if(cache[blocco][0].libera==true){
						colora(12);
						cout<<"Il blocco di cache "<<blocco<<" non e' ancora stato caricato..."<<endl<<endl;
						colora(7);
					}

					else{
						cout<<endl<<"\t\t**** BLOCCO DI CACHE "<<blocco<<" ****"<<endl<<endl;
						cout<<" FIFO: "<<cache[blocco][0].contFIFO<<" ; LRU: "<<cache[blocco][0].contLRU<<" --> ";
						cout<<blocco<<". | ";
						for(j=0;j<dimBlocco;j++)
							cout<<cache[blocco][j]<<" | ";

						for(j=0;j<dimBlocco;j++)
							cache[blocco][j].contLRU=0;

						int inizioGruppo = (dimCache/nGruppi) * (floor(blocco/(dimCache/nGruppi)));
						int fineGruppo = ((dimCache/nGruppi) * (floor(blocco/(dimCache/nGruppi)))) + (dimCache/nGruppi) - 1;

						for(i=inizioGruppo;i<=fineGruppo;i++)
							if(i!=blocco)
								for(j=0;j<dimBlocco;j++)
									cache[i][j].contLRU++;
					}

					cout<<endl<<endl;

				}

				else if(scelta==7){}

				else{
					colora(12);
					cout<<"Errore nella scelta. Riprova..."<<endl;
					colora(7);
				}			
				
			}
			break;
	}

	cout<<"   *******    FINE PROGRAMMA    *******"<<endl;
}

bool potenzaDiDue(int n)
{
   if(n==0)
   return false;
 
   return (ceil(log2(n)) == floor(log2(n)));
}

void colora(int color)
{
 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}