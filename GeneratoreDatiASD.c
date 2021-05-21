/* inclusione delle librerio */
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>

/***********/
/* definizione strutture */

typedef struct array
{
    char id[7];
}array;

typedef struct modello
{
    char modello[19];
}modello_t;

/* dichiarazione funzioni */
/* funzione di controllo valori interi*/
int ValidazioneNumeroVeicoli();

/* funzione che acquisisce gli entremi per il calcolo randomico */
int GeneraAnno();

/* funzione che genera gli id dei veicoli */
void GeneraIdVeicoli(int num_veicoli, char id_veicolo[7], array *lista_id);

/* funzione che genera i nomi dei proprietari */
void GeneraProprietari(int num_veicoli, char nome_proprietario[7], array *lista_proprietari);

/* funzio ne che legge da file i modelli di auto e li assegna a una struttura */
void GeneraModelli(int num_veicoli, FILE *Modelli, char modelli[67][19], modello_t *lista_modelli);

int ApriFile(FILE **file);

/* -------------------- */
/*  DEFINIZIONE FUNZIONE MAIN*/
/*--------------------*/
int main (void)
{
    /* dichiarazioni variabili locali*/
    int     numero_veicoli,
            anno,
            i;
    char    id_veicolo[7];
    char    nome_proprietario[7];
    char    modelli[67][19];
    array   *lista_id;
    array   *lista_proprietari;
    modello_t *lista_modelli;
    FILE    *Modelli = NULL;
    FILE    *dati = NULL;
    
    srand(time(NULL));

    /* acquisizione numero veicoli da voler visualizzare*/
    numero_veicoli = ValidazioneNumeroVeicoli();

    /* allocazione della memoria in base al numero di veicoli*/
    lista_id            = (array *)malloc(numero_veicoli*sizeof(array));
    lista_proprietari   = (array *)malloc(numero_veicoli*sizeof(array));
    lista_modelli       = (modello_t *)malloc(numero_veicoli*sizeof(modello_t));

    /* generazione id veicoli*/
    GeneraIdVeicoli(numero_veicoli, id_veicolo, lista_id);

    /* generazione nomi proprietari*/
    GeneraProprietari(numero_veicoli, nome_proprietario, lista_proprietari);

    /* generazione modelli*/
    GeneraModelli(numero_veicoli, Modelli, modelli, lista_modelli);

    /* apertura del file per la scrittura e verifica della corretta apertura*/
    dati = fopen("dati.txt", "w");
    if(dati == NULL)
        printf("Errore nell'apertura del file 'dati'\nControllare l'esistenza e/o la posizione del file\n");
    /* se il file viene aperto correttamente si procede con il calcolo casuale dell'anno e la scrittura di questi nel file*/
    else
    {
        for(i = 0; i < numero_veicoli; i++)
        {
            anno = GeneraAnno();
            fprintf(dati, "%s\t%s\t%s\t%d\n\r", 
                    lista_id[i].id, lista_proprietari[i].id, lista_modelli[i].modello, anno);
        }
    }
    fclose(dati);
    printf("\nFile Generato con Successo\n");
    return 0;
}/* end main */


/* -------------------- */
/*  DEFINIZIONE FUNZIONi*/
/*--------------------*/

/* definizone ValidazioneNumeroVeicoli*/
int ValidazioneNumeroVeicoli()
{
    /*dichiarazione variabili locali*/
    int num,
        temp;
    
    printf("Inserire il numero di veicoli che si vogliono analizzare\n");

    /* acquisizione e verifica valori*/
    do
    {
        temp = scanf ("%d", &num);
        if ((num <= 0) || (temp == 0))
            printf("\nIl valore inserito non e' accettabile\nPerfavore inserire un numero naturale diverso da 0\nReinserire il valore:\t");
        while (getchar() != '\n');
    }while((num <= 0 ) || (temp == 0));

    /*ritorna il primo valore valido*/
    return num;
} /* end ValidazioneNumeroVeicoli*/

/* definizione GeneraAnno*/
int GeneraAnno()
{
    /* dichiarazione variabili locali*/
    int ritorno; /* variabile di ritorno */

    /* espressione per ottenere un numero randomico in un intervallo */
    ritorno = rand()%(2021-1900+1)+1900;

    return ritorno;
}

/* funzione che genera gli id dei veicoli */
void GeneraIdVeicoli(int num_veicoli, char id_veicolo[7], array *lista_id)
{
    int i, 
        j;

    for( i = 0; i < num_veicoli; i++)
    {
        for( j = 0; j < 6; j++)
        {
            /* per fare cio' va consultata la tabella ascii*/
            /* per i primi 4 valori vengono inserite delle lettere maiuscole casuali*/
            if(j < 4)
                id_veicolo[j] = 65 + rand() % (90 - 65);
            /* per gli ultimi 2 valori vengono inseriti dei numeri tra 0 e 9*/
            else if(j == 6)
                id_veicolo[j] = 0;
            else 
                id_veicolo[j] = 48 + rand() % (57-48);
        }

        /* inserimento valore ottenuto nella struttura*/
        strcpy(lista_id[i].id, id_veicolo);
    }
}/* end GeneraIdVeicoli*/

/* funzione che genera i nomi dei proprietari */
void GeneraProprietari(int num_veicoli, char nome_proprietario[7], array *lista_proprietari)
{
    int i, 
        j;
    for( i = 0; i < num_veicoli; i++)
    {
        for( j = 0; j < 6; j++)
        {
            /* per fare cio' va consultata la tabella ascii*/
            /* per i primi 4 valori vengono inserite delle lettere maiuscole casuali*/
            if(j < 3)
                nome_proprietario[j] = 65 + rand() % (90 - 65);
            /* per gli ultimi 2 valori vengono inseriti dei numeri tra 0 e 9*/
            else if(j == 6)
                nome_proprietario[j] = 0;
            else 
                nome_proprietario[j] = 48 + rand() % (57-48);
        }

        /* inserimento valore ottenuto nella struttura */
        strcpy(lista_proprietari[i].id, nome_proprietario);
    }    
}/* end GeneraProprietari */



/* Definizione GeneraModelli */
void GeneraModelli(int num_veicoli, FILE *Modelli, char modelli[67][19], modello_t *lista_modelli)
{
    int controllo;
    int esito;
    int n = 0,
        y = 0,
        i = 0;
    controllo = ApriFile(&Modelli);   /* apro il file in lettura*/

    if(controllo == 1)   /* caso in cui sia stato aperto corretamente il file*/
    {   
        do  /* aquisizione dei dati dal file*/
        {
            esito = fscanf(Modelli, "%s", modelli[i]);
            i++;
            /*printf("errore Porca Madonna");*/
        }while(esito != EOF);
        /*finita l'aquisizione dei dati si procede con la chiusura del file*/
        fclose(Modelli);
    }
    for ( y = 0; y < num_veicoli; y++)
    {
        n = rand() % 67;
        strcpy(lista_modelli[y].modello, modelli[n]);
    }
}

int ApriFile(FILE **file)
{
    /* apro il file in lettura*/
    *file = fopen("Modelli.txt", "r");
    /* verifico la corretta apertura del file*/
    if(*file == NULL)
    {
        return 0;
    }
    else
    {
        return 1; 
    }
           
}/* END 'ApriFile'*/