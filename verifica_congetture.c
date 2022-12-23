/*********************************************************************/
/* PROGRAMMA PER VERIFICARE LE CONGETTURE DI BEAL, COLLATZ E CRAMER */
/*******************************************************************/

/* INCLUSIONE DELLE LIBRERIE */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* DEFINIZIONE DEI TIPI */

/* Tipo ricorsivo per creare liste dinamiche */
typedef struct lista 
{
	unsigned int elemento; /* numero intero */
	struct lista *succ;    /* indirizzo dell'elemento successivo */
} lista_t; 

/* DICHIARAZIONE DELLE FUNZIONI */
int acquisisci_operazione(void); 
void acquisisci_valori(unsigned int *, 
                       char *, 
					             int);
int primo(unsigned int);
int verifica_beal(lista_t **);
int verifica_collatz(lista_t **);  
int verifica_cramer(void);
int inserisci_elemento(lista_t **, 
                        unsigned int);
void stampa_lista(lista_t *);

/******************************/
/* DEFINIZIONE DELLE FUNZONI */
/****************************/

/* DEFINIZIONE DELLA FUNZIONE MAIN */
int main(void)
{   
   /* Dichiarazione variabili locali alla funzione*/
   int op;          /* INPUT: operazione scelta dall'utente */
   lista_t *valori  /* OUTPUT: i valori prodotti dalla congettura scelta */
   int esito;       /* OUTPUT: l'esito della verifica */  
   
   valori = NULL;

   /* Stampare il titolo del programma */
   printf("\nPROGRAMMA PER LA VERIFICA DI CONGETTURE\n");
   putchar('\n');	
   
   /* Acquisire l'operazione scelta dall'utente */
   op = acquisisci_operazione();
       
   /* Verificare la congettura scelta dall' utente */
   switch (op)
   {   
     case 1:
       esito = verifica_beal(&valori);
       break;  
     case 2:
       esito = verifica_collatz(&valori);
       break;
     
     case 3:
       esito = verifica_cramer();
       break;
   }
   
   /* Stampare l'esito complessivo della verifica */
   putchar('\n');
   printf("Congettura %s.\n", 
          (esito)? 
   	      "verificata": 
   	      "non verificata"); 

   return(0);
}

/* DEFINIZIONE DELLA FUNZIONE PER SCEGLIERE LA CONGETTURA DA VERIFICARE */
int acquisisci_operazione(void)
{
   /* Dichiarazione delle variabili locali alla funzione */
   int operazione;          /* INPUT/OUTPUT: operazione scelta dall'utente */
   int esito_acquisizione,  /* LAVORO: esito della scanf */
       acquisizione_errata; /* LAVORO: esito globale dell'acquisizione */  
	   
   do
   {
     /* Stampare le istruzioni per la selezione */
     putchar('\n');
     printf("Scegliere una congettura da verificare:\n\n");
     printf("(1) - Beal\n");
     printf("(2) - Collatz\n");
     printf("(3) - Cramer.\n");

     printf("Digitare la propria scelta e premere invio: ");

   	 /* Acquisire l'operazione scelta */
   	 esito_acquisizione = scanf("%d",
   	                            &operazione);

   	 /* Validare l'acquisizione */
   	 acquisizione_errata = esito_acquisizione != 1 || operazione < 1 || operazione > 3; 

   	 /* Stampare un messaggio di errore in caso di acquisizione errata */
   	 if (acquisizione_errata)
   	   printf("Valore non accettabile!\n");
   	 while (getchar() != '\n'); 
   } 
   while (acquisizione_errata);   

   return(operazione);
}

/* DEFINIZIONE DELLA FUNZIONE PER VERIFICARE SE UN NUMERO È PRIMO */
int primo(unsigned int valore) /* INPUT: il valore da controllare */
{   
   /* Dichiarazione delle variabili locali */
   int primo;      /* OUTPUT: esito della verifica */
   unsigned int i; /* LAVORO: indice di scorrimento */ 
   
   if (valore == 2)
     primo = 1;

   /* Verificare se il valore ha divisori */
   for (i = 2,
          primo = 1;
        i < sqrt(valore) && primo != 0; 
   	    i++)
	{
   	  if(valore % i == 0)
   	     primo = 0;
   	}   

   return(primo);
}

/* Definizione della funzione per acquisire e validare valori numerici */
void acquisisci_valori(unsigned int *valore, /*INPUT/OUTPUT: valore da acquisire */
                       char *messaggio,      /* LAVORO: messaggio specifico */
                       int min)              /* LAVORO: limite inferiore per l'acquisizione */
{   
   /* Dichiarazione delle variabili locali */
   int esito_acquisizione,  /* LAVORO: esito della scanf*/
       acquisizione_errata; /* LAVORO: esito complessivo dell' acquisizione */
   
   do
   {
   	 /* Stampare il messaggio specifico */
   	 printf("Digita %s:  ", 
   	        messaggio);   

   	 /* Acquisire il valore */
   	 esito_acquisizione = scanf("%u", 
   	                            valore);
        
   	 /* Verificare l'esito dell'acquisizione */
   	 if (min >= 11)		
   	   acquisizione_errata = esito_acquisizione != 1 || *valore < min || primo(*valore) != 1;	
   	 else
   	   acquisizione_errata = esito_acquisizione != 1 || *valore < min;		
   	    
   	 /* Stampare un messaggio di errore */
   	 if (acquisizione_errata)
   	   printf("Valore non accettabile!\n");
   	 while (getchar() != '\n');
   } 
   while (acquisizione_errata);
}

/* DEFINIZIONE DELLA FUNZIONE PER VERIFICARE LA CONGETTURA DI BEAL */
int verifica_beal(lista_t **fattori_comuni) /* OUTPUT: fattori primi comuni trovati */
{   
   /* Dichiarazione delle variabili locali */
   unsigned int basi[3], /* INPUT: basi delle tre potenze */
                esp[3]; /* INPUT: esponenti delle tre potenze */
   unsigned int i;     /* LAVORO: indice di scorrimento */
   int div;          /* LAVORO: divisore per la scomposizione in fattori primi */
   int esito_eq, /* OUTPUT: esito della verifica dell' equazione */
   	   esito;    /* OUTPUT: esito complessivo della verifica */

   /* Stampare la scelta effettuata */
   printf("\nCONGETTURA DI BEAL.\n");
   
   /* Acquisire le tre potenze */
   for (i = 0; 
        i < 3; 
        i++)
   {   
   	 putchar('\n');
   	 acquisisci_valori(basi + i, 
   	                   "una base (>= 1)", 
   	                   1);

   	 acquisisci_valori(esp + i, 
   	                   "un esponente (>= 3)", 
   	                   3);
   }

   /* Verificare l' equazione a^x + b^y = c^z */
   esito_eq = ((pow(basi[0], esp[0]) + pow(basi[1], esp[1])) == pow(basi[2], esp[2]));
   
   /* Scomporre la prima base in fattori primi */
   div = 2;

   while (basi[0] > 1) 
   {   
   	  if (basi[0] % div == 0)
   	  {   
   	  	basi[0] = basi[0] / div;

        /* Verificare se i fattori primi trovati dividono le altre due basi */
   	  	if (primo(div) == 1 && basi[1] % div == 0 && basi[2] % div == 0)
   	  	   inserisci_elemento(fattori_comuni, 
   	  	                     div);
   	  }
   	  else
   	    div += 1;
   }
    
   if (esito_eq == 1)
   {
   	 printf("\nL'equazione a^x + b^y = c^z è soddisfatta dai valori inseriti.\n");

   	 if (*fattori_comuni != NULL)
     {  		
       printf("Sono stati trovati i seguenti fattori primi comuni:\n");
   	   stampa_lista(*fattori_comuni);
       esito = 1;
     }
     else
     {
       printf("Non sono stati trovati fattori primi comuni.\n");
       esito = 0;
     }
   }
   else 
   {   
	  printf("\nL'equazione a^x + b^y = c^z non è soddisfatta dai valori inseriti.\n");
   	  esito = 0;

   	  if (*fattori_comuni != NULL)
   	  {
   	    printf("Sono comunque stati trovati fattori primi comuni:\n");
   	    stampa_lista(*fattori_comuni);
   	  }
   }

   return(esito);	   
}

/* DEFINIZIONE DELLA FUNZIONE PER VERIFICARE LA CONGETTURA DI COLLATZ */
int verifica_collatz(lista_t **valori_generati) /* OUTPUT: valori generati dalla funzione */
{
   /* Dichiarazione delle variabili locali alla funzione */
   unsigned int val_corr; /* INPUT: valore inserito dall'utente */
   int esito_ins;         /* LAVORO: esito dell'inserimento nella lista*/
   int verifica;          /* OUTPUT: esito della verifica */
   
   /* Stampare la scelta effettuata */
   printf("\nCONGETTURA DI COLLATZ.\n");

   /* Acquisire il valore di partenza */
   putchar('\n');
   acquisisci_valori(&val_corr, 
                     "un numero intero (> 0)", 
   				           1);
   
   do 
   {
      /* Inserire il valore attuale nella lista */
   	  esito_ins = inserisci_elemento(valori_generati, 
   	                                 val_corr);
         
   	  /* Verificare se il valore è pari */
   	  if (val_corr % 2 == 0)
   	  {  
   	  	val_corr = val_corr / 2;
   	  } 
   	  else 
   	  {   
   	  	val_corr = 3 * val_corr + 1;
   	  }
   } 
   while (val_corr != 1 && esito_ins == 1);

   /* Stabilire l'esito della congettura */
   verifica = (val_corr == 1)? 
               1: 
               0;
   
   /* Stampare i valori generati */
   stampa_lista(*valori_generati);
   putchar('1');

   return(verifica);
}

/* DEFINIZIONE DELLA FUNZIONE PER INSERIRE UN INTERO IN UNA LISTA */
int inserisci_elemento(lista_t **pos, /* INPUT/OUTPUT: indirizzo prima locazione */
                        unsigned int valore) /* INPUT: il valore da inserire */
{   
   /* Dichiarazione delle variabili locali */
   lista_t *pos_corr,  /* LAVORO: primo puntatore di scorrimento */
           *pos_prec,  /* LAVORO: secondo puntatore di scorrimento */
   		     *nuova_pos; /* LAVORO: puntatore nuova locazione */
    int esito_ins;     /* OUTPUT: esito dell'inserimento*/
   
   /* Scorrere la lista fino a trovare una locazione vuota */
   for (pos_corr = pos_prec = *pos; 
        pos_corr != NULL && pos_corr->elemento != valore; 
   	    pos_prec = pos_corr, 
   	      pos_corr = pos_corr->succ);
   if (pos_corr != NULL && pos_corr->elemento == valore)
     esito_ins = 0;
   else
   {
     esito_ins = 1;
     /* Allocare e inizializzare il nuovo elemento */
     nuova_pos = (lista_t *)malloc(sizeof(lista_t));
     nuova_pos->elemento = valore;
     nuova_pos->succ = pos_corr;
  
     if (pos_corr == *pos)
       /* Posizionare il nuovo elemento all'inizio della lista */
       *pos = nuova_pos;
     else
       /* Posizionare il nuovo elemento in fondo alla lista */
       pos_prec->succ = nuova_pos;
   }

   return(esito_ins);
}

/* DEFINIZIONE DELLA FUNZIONE PER VERIFICARE LA CONGETTURA DI CRAMER */
int verifica_cramer(void)
{   
   /* Dichiarazione delle variabili locali */
   unsigned int primo1, /* INPUT: primo numero primo*/
                primo2; /* INPUT: secondo numero primo*/
   int i,         /* LAVORO: indice di scorrimento */
       acquisizione_errata;  /* LAVORO: esito acquisizione */
   unsigned int abs_diff,  /* OUTPUT: valore assoluto della differenza dei due numeri */
                pow_ln;    /* OUTPUT: quadrato del ln del numero minore */
   int verifica;/* OUTPUT: esito della verifica */
   
   /* Stampare la scelta effettuata */
   printf("\nCONGETTURA DI CRAMER.\n");
   putchar('\n');

   do 
   { /* Acquisire il primo numero primo */
     acquisisci_valori(&primo1, 
   	                   "il primo numero primo (> 10)", 
   	                   11);
 
   	 /* Acquisire il secondo numero primo */
   	 acquisisci_valori(&primo2, 
   	                   "il secondo numero primo (maggiore del precedente)", 
   	                   primo1);
        
   	 
     /* Verificare che siano consecutivi */
   	 for(i = (primo1 + 1), 
   	       acquisizione_errata = 0; 
   	     i < primo2; 
   	 	 i++)
   	 {   
   	   if (primo(i) == 1) 
   	     acquisizione_errata = 1;
   	 			    	
   	 }

   	 /* Stampare messaggio di errore */
   	 if (acquisizione_errata)		
   	   printf("\nI due numeri devono essere consecutivi!\n");
   }   
   while (acquisizione_errata);
   
   /* Calcolare il valore assoluto della differenza */
   abs_diff = abs(primo1 - 
                  primo2);
   
   /* Calcolare il quadrato del logaritmo naturale */
   pow_ln = pow(log(primo1), 
                2);
       
   /* Stabilire l'esito della verifica */
   verifica = abs_diff < pow_ln;
   
   /* Stampare i risultati */
   printf("Il valore assoluto della differenza tra %u e %u è %u.\n", 
          primo1, 
          primo2, 
          abs_diff);

   printf("Il quadrato del logaritmo naturale del numero minore vale %u.\n",  
          pow_ln);

   printf("Il valore assoluto della differenza %s minore del quadrato del logaritmo naturale del numero minore.\n", 
          (verifica)? 
          "è": 
          "non è");

   return(verifica);
}

/* DEFINIZIONE DELLA FUNZIONE PER STAMPARE UNA LISTA DI NUMERI */
void stampa_lista(lista_t *lista) /* INPUT: l'indirizzo della prima locazione della lista */
{
   lista_t *corr; /* LAVORO: puntatore di scorrimento della lista */

   for (corr = lista; 
        corr != NULL; 
        corr = corr->succ)
   {
   	 printf("%u\n", 
   	        corr->elemento);
   }
}