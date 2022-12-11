/*********************************************************************/
/* PROGRAMMA PER VERIFICARE LE CONGETTURE DI BEAL, COLLATZ E CRAMER */
/*******************************************************************/

/* INCLUSIONE DELLE LIBRERIE */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* DEFINIZIONE DEI TIPI */

typedef enum {"verificata",
	          "non verificata"} esito_t /* Tipo per l'esito della verifica delle congetture*/

/* DICHIARAZIONE DELLE FUNZIONI */
int acquisisci_operazione(int); /* Funzione per acquisire l'operazione scelta dall'utente */
int acquisisci_valori(int);
esito_t verifica_bael(int *);   /* Funzione per verificare la congettura di Bael */
esito_t verifica_collatz(int,
                         int);  /* Funzione per verificare la congettura di Collatz */
esito_t verifica_cramer(int,    /* Funzione per verificare la congettura di Cramer */
		                int);
int numero_primo(int);          /* Funzione per verificare se un numero è primo */
int fattorizzazione(int,        /* Funzione per scomporre un numero in fattori primi */
		            int *);


/******************************/
/* DEFINIZIONE DELLE FUNZONI */
/****************************/

/* DEFINIZIONE DELLA FUNZIONE MAIN */
int main(void)
{   
	/* Dichiarazioni variabili locali */
	int op;        /* INPUT: operazione scelta dall'utente */
	int *valori;   /* INPUT: array dei valori di input dell'operazione scelta */
	esito_t esito; /* OUTPUT: l'esito della verifica */
    
	/* Acquisire l'operazione scelta dall'utente */
    op = acquisisci_operazione();
    
	if (op == 1){
	    
		/* Allocare lo spazio necessario nell'array degli input */
		valori = calloc(6, sizeof(int));

		for (int i = 0; i < lunghezza; i++)
		{
			printf("Inserisci un %s (>= %d): ",
			       (i % 2 == 0)? 
				               "intero": 
				               "esponente",
				   (i % 2 == 0)? 
				               1: 
				               3);
			valori[i] = acquisisci_valori();
		}
	    esito = verifica_bael(valori);
	}
	else if (op == 2){

		valori = calloc(1, sizeof(int));
        
		printf("Inserisci un numero intero(>0): ");
		valori[0] = acquisisci_valori(1);
		esito = verifica_collatz(valori[0]);

	}
	else {

		valori = calloc(2, sizeof(int));
        
		do{
		printf("Inserisci il primo numero primo(>0): ");
		valori[0] = acquisisci_valori(2);

		printf("Inserisci il secondo numero primo(>0): ");
		valori[1] = acquisisci_valori(2);
		} while (numero_primo(valori[0]) != 1 && numero_primo(valori[1]) != 1);

		esito = verifica_cramer(valori[0], valori[1]);

	}

	printf("La congettura scelta è %s per i valori immessi",
	       (char *)esito);

	return(0);


}

/* DEFINIZIONE DELLA FUNZIONE PER SCEGLIERE LA CONGETTURA DA VERIFICARE */
int acquisisci_operazione(void)
{
    /* Dichiarazione delle variabili locali alla funzione */
	int operazione; /* INPUT/OUTPUT: l'operazione scelta dall'utente */
	int acquisizione_errata, /* LAVORO: esito globale dell'acquisizione */
	    esito_acquisizione;  /* LAVORO: esito della scanf */

	do{

		printf("Scegli una congettura da verificare: 1 Beal, 2 Collatz, 3 Cramer.\n");
		/* Acquisire l'operazione scelta */
		esito_acquisizione = scanf("%d",
		                           &operazione);

		/* Verificare l'esito dell'acquisizione */
		acquisizione_errata = esito_acquisizione != 1 || (operazione != 1 && operazione != 2 && operazione != 3);

		/* Stampare un messaggio di errore in caso di acquisizione errata */
		if (acquisizione_errata)
		    printf("Valore non accettabile!");
		while (getchar() != '\n'); 

	} while (acquisizione_errata); 

	return(operazione);

}

/* Definizione della funzione per l'acquisizione e la validazione dei dati di input */
int acquisisci_valori(int min) /* INPUT: il minimo valore che il dato di input può assumere */
{   
	/* Dichiarazione delle variabili locali alla funzione */
	int acquisizione_errata, /* LAVORO: esito dell'acquisizione */
	    esito_acquisizione;  /* LAVORO: esito della scanf */
	int valore;              /* OUTPUT: il valore da acquisire */

	do
	{   /* Acquisire il valore da tastiera*/
		esito_acquisizione = scanf("%d",
		                           &valore);
		
		/* Verificare che il valore sia stato acquisito correttamente */
		acquisizione_errata = esito_acquisizione != 1 || valore < min;
        
		/* Stampare un messaggio di errore in caso di acquisizione errata */
		if (acquisizione_errata)
		    printf("Valore non accettabile!");
		while (getchar() != '\n');
	} while (acquisizione_errata); /* Ripetere l'acquisizione errata finchè il valore non è corretto */

	return(valore);
}

/* DEFINIZIONE DELLA FUNZIONE PER VERIFICARE LA CONGETTURA DI BEAL*/
esito_t verifica_bael(int *valori) /* INPUT: le tre potenze sulle quali verificare la congettura */
{   
	/* Dichiarazione delle variabili locali alla funzione */
	int exp1,            /* INPUT: la prima potenza a^x */
	    exp2,            /* INPUT: la seconda potenza b^y */
		exp3;            /* INPUT: la terza potenza c^y */
	int *fattori_comuni; /* OUTPUT: i fattori comuni alle tre basi */
	esito_t esito;       /* OUTPUT: l'esito della verifica */
    
	/* Calcolare le tre potenze */
	exp1 = pow(*(valori), *(valori + 1))
	exp2 = pow(*(valori + 2), *(valori + 3))
	exp3 = pow(*(valori + 4), *(valori + 5))
	
	/* Scomporre la prima base in fattori */
    fattorizzazione(*(valori), fattori_comuni);

	/* Verificare se i fattori primi della prima base dividono le altre due e stamparli*/
	printf("I fattori comuni a %d, %d e %d sono: \n",
	       valori[0],
		   valori[1],
		   valori[2]);

	for (int i; i < lenf; i++){
		if ((valori[2] % fattori_comuni[i]) == 0 && (valori[4] % fattori_comuni[i] == 0))
		{
            printf("%d\n",
			       fattori_comuni[i]);
		}
	}
    
	/* Verificare se la congettura è verificata */
	esito = (exp1 + exp2 == exp3)?
	                             1:
								 0;
	
	return(esito);
	
	
}

/* DEFINIZIONE DELLA FUNZIONE PER VERIFICARE LA CONGETTURA DI COLLATZ */
esito_t verifica_collatz(int valore,      /* INPUT: il valore di partenza della sequenza*/
                         int ripetizioni) /* INPUT: il numero di chiamate effettuate */
{
    /* Dichiarazione delle variabili locali alla funzione */
	int pari;
	esito_t verifica;

	printf("%d\n",
	       valore);
    
	if (valore == 1 && ripetizioni != 0)
	{
		verifica = "verificata"
	}
	else{
	
	    pari = (valore % 2 == 0)? 1: 0;
    
	    if (pari == 1)	        
	    	verifica_collatz(valore / 2, ripetizioni + 1);
    
	    else    
	        verifica_collatz(3 * valore + 1, ripetizioni + 1);
	}

	return(verifica);

}


/* DEFINIZIONE DELLA FUNZIONE PER VERIFICARE LA CONGETTURA DI CRAMER */
esito_t verifica_cramer(int valore1, /* INPUT: il primo numero primo */
                        int valore2) /* INPUT: il secondo numero primo */
{   

	/* Dichiarazione delle variabili locali alla funzione */

	int minore;       /* LAVORO: il numero primo minore tra i due inseriti */
	int differenza;   /* OUTPUT: valore assoluto della differenza tra i due numeri primi */
	int quadrato_ln;  /* OUTPUT: quadrato del logaritmo naturale del numero minore */
	esito_t verifica; /* OUTPUT: l'esito della verifica della congettura */
    
	/* Calcolare il valore assoluto della differenza tra i due numeri */
	differenza = abs(valore1 - valore2);
    
	/* Verificare quale dei due numeri è il minore */
	minore = (valore1 < valore2)? 
	                    valore1: 
			            valore2;
    
	/* Calcolare il quadrato del logaritmo naturale del numero minore */
	quadrato_ln = pow(log(minore), 
	                  2);
    
	/* Stampare il valore assoluto della differenza */
	printf("Il valore assoluto della differenza tra i numeri inseriti è: %d",
	       differenza);
    
	/* Stampare il quadrato del logaritmo */
	printf("Il quadrato del logaritmo del numero minore è: %d",
	       quadrato_ln);
    
	/* Decidere l'esito della verifica */
    verifica = (differenza < quadrato_ln)? 0: 1;

	return(verifica);
}

int fattorizzazione(int valore, int *fattori)
{
    int j = 0;

	for (int i = 2; valore > 1; i++){

		if (valore % i == 0 && numero_primo(i)){
            valore = valore / i;
			fattori[j] = i;
			j += 1;
		}
	}

	return(j);

}

int numero_primo(int valore)
{
    int primo = 1;

	for (int i = 2; i < valore; i++){

		if (valore % i == 0)
		    primo = 0;
	}

	return(primo);

}









