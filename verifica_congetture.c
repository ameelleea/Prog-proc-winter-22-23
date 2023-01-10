/*********************************************************************/
/* PROGRAMMA PER VERIFICARE LE CONGETTURE DI BEAL, COLLATZ E CRAMER */
/*******************************************************************/

/* INCLUSIONE DELLE LIBRERIE */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

/* DICHIARAZIONE DELLE FUNZIONI */
int acquisisci_operazione(void); 
void acquisisci_valori(unsigned int *, 
                       char *, 
					             int);
int primo(unsigned int);
int verifica_beal(void);
int verifica_collatz(void);  
int verifica_cramer(void);

/******************************/
/* DEFINIZIONE DELLE FUNZONI */
/****************************/

/* DEFINIZIONE DELLA FUNZIONE MAIN */
int main(void)
{   
   /* Dichiarazione variabili locali alla funzione*/
   int op;          /* INPUT: operazione scelta */
   int esito;       /* OUTPUT: esito della verifica */  

   /* Stampare il titolo del programma */
   printf("PROGRAMMA PER LA VERIFICA DI CONGETTURE\n");
   putchar('\n');	
   
   /* Acquisire l'operazione scelta */
   op = acquisisci_operazione();
       
   /* Verificare la congettura */
   switch (op)
   {   
     case 1:
       esito = verifica_beal();
       break;  
     case 2:
       esito = verifica_collatz();
       break;     
     case 3:
       esito = verifica_cramer();
       break;
     default:
       esito = 0;
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
   int operazione;          /* INPUT/OUTPUT: operazione scelta */
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
     putchar('\n');
     printf("Digitare la propria scelta e premere invio: ");

   	 /* Acquisire l'operazione scelta */
   	 esito_acquisizione = scanf("%d",
   	                            &operazione);

   	 acquisizione_errata = esito_acquisizione != 1 || operazione < 1 || operazione > 3; 

   	 /* Stampare un messaggio di errore */
   	 if (acquisizione_errata)
   	   printf("Valore non accettabile!\n");
   	 while (getchar() != '\n'); 
   } 
   while (acquisizione_errata);   

   return(operazione);
}

/* DEFINIZIONE DELLA FUNZIONE PER VERIFICARE I NUMERI PRIMI */
int primo(unsigned int valore) /* INPUT: il valore da verificare */
{   
   /* Dichiarazione delle variabili locali */
   int primo;      /* OUTPUT: esito della verifica */
   unsigned int i; /* LAVORO: indice di scorrimento */ 
  
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

/* DEFINIZIONE DELLA FUNZIONE PER ACQUISIRE VALORI NUMERICI */
void acquisisci_valori(unsigned int *valore, /*INPUT/OUTPUT: valore da acquisire */
                       char *messaggio,      /* LAVORO: messaggio specifico */
                       int min)              /* LAVORO: valore minimo */
{   
   /* Dichiarazione delle variabili locali */
   int esito_acquisizione,  /* LAVORO: esito della scanf*/
       acquisizione_errata; /* LAVORO: esito complessivo dell' acquisizione */
   
   do
   {
   	 /* Stampare il messaggio specifico */
     putchar('\n');
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
int verifica_beal(void)
{   
   /* Dichiarazione delle variabili locali */
   unsigned int basi[3], /* INPUT: basi delle tre potenze */
                esp[3]; /* INPUT: esponenti delle tre potenze */
   int i;     /* LAVORO: indice di scorrimento */
   int div;      /* LAVORO: divisore per la scomposizione in fattori */
   int esito;    /* OUTPUT: esito complessivo della verifica */
   int fattore_comune; /*OUTPUT: fattore comune trovato */

   /* Stampare la scelta effettuata */
   printf("\nCONGETTURA DI BEAL.\n");
   
   /* Acquisire le tre potenze */
   for (i = 0; 
        i < 3; 
        i++)
   {  
     do{
   	 acquisisci_valori(basi + i, 
   	                   "una base (>= 1)", 
   	                   1);

   	 acquisisci_valori(esp + i, 
   	                   "un esponente (>= 3)", 
   	                   3);

      if (pow(basi[i], esp[i]) >= UINT_MAX)
      {
        printf("La potenza inserita e' troppo elevata!\n");
        printf("Prego reinserirla.\n");
      }
     } 
     while(pow(basi[i], esp[i]) >= UINT_MAX);
   }
   
   /* Cercare eventuali fattori primi comuni */
   for (fattore_comune = 0,
          div = 2;
        fattore_comune == 0;
        div++)
    {
      if (primo(div) == 1)
      {
        if (basi[0] % div == 0 && basi[1] % div == 0 && basi[2] % div == 0)
          fattore_comune = div;
      }
    }
    
   if ((pow(basi[0], esp[0]) + pow(basi[1], esp[1])) == pow(basi[2], esp[2]))
   {
   	 printf("\nL'equazione a^x + b^y = c^z e' soddisfatta dai valori inseriti.\n");

   	 if (fattore_comune != 0)
     {  		
       printf("E' stato trovato un fattore primo comune: %d\n",
              fattore_comune);
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
	   printf("\nL'equazione a^x + b^y = c^z non e' soddisfatta dai valori inseriti.\n");
   	 esito = 1;  
     
   	 if (fattore_comune != 0)
   	 { 
   	   printf("E' comunque stato trovato un fattore primo comune: %d\n",
              fattore_comune);
   	 }
     else
     {
       printf("Non sono stati trovati fattori primi comuni.\n");
     }
   }

   return(esito);	   
}

/* DEFINIZIONE DELLA FUNZIONE PER VERIFICARE LA CONGETTURA DI COLLATZ */
int verifica_collatz(void) 
{
   /* Dichiarazione delle variabili locali alla funzione */
   unsigned int val_corr; /* INPUT: valore inserito dall'utente */
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
   	  /* Verificare se il valore e' pari */
   	  if (val_corr % 2 == 0)
   	  {  
   	  	val_corr = val_corr / 2;
   	  } 
   	  else 
   	  {   
   	  	val_corr = 3 * val_corr + 1;
   	  }

      printf("%d ",
             val_corr);
   } 
   while (val_corr != 1);

   /* Stabilire l'esito della verifica */
   verifica = (val_corr == 1)? 
               1: 
               0;

   return(verifica);
}

/* DEFINIZIONE DELLA FUNZIONE PER VERIFICARE LA CONGETTURA DI CRAMER */
int verifica_cramer(void)
{   
   /* Dichiarazione delle variabili locali */
   unsigned int primo1, /* INPUT: primo numero primo*/
                primo2; /* INPUT: secondo numero primo*/
   int i,         /* LAVORO: indice di scorrimento */
       acquisizione_errata;  /* LAVORO: esito acquisizione */
   unsigned int abs_diff;  /* OUTPUT: valore assoluto della differenza */
   double  pow_ln;    /* OUTPUT: quadrato del ln del numero minore */
   int verifica;/* OUTPUT: esito della verifica */
   
   /* Stampare la scelta effettuata */
   printf("\nCONGETTURA DI CRAMER.\n");
   putchar('\n');

   do 
   { /* Acquisire il primo numero primo */
     acquisisci_valori(&primo1, 
   	                   "il primo numero primo (>= 11)", 
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

   printf("Il quadrato del logaritmo naturale del numero minore vale %.2f.\n",  
          pow_ln);

   printf("Il valore assoluto della differenza %s minore del quadrato del logaritmo di %d.\n", 
          (verifica)? 
          "e'": 
          "non e'",
          primo1);

   return(verifica);
}