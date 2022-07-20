
/* c206.c **********************************************************}
{* Téma: Dvousměrně vázaný lineární seznam
**
**                   Návrh a referenční implementace: Bohuslav Křena, říjen 2001
**                            Přepracované do jazyka C: Martin Tuček, říjen 2004
**                                            Úpravy: Kamil Jeřábek, září 2019
**
** Implementujte abstraktní datový typ dvousměrně vázaný lineární seznam.
** Užitečným obsahem prvku seznamu je hodnota typu int.
** Seznam bude jako datová abstrakce reprezentován proměnnou
** typu tDLList (DL znamená Double-Linked a slouží pro odlišení
** jmen konstant, typů a funkcí od jmen u jednosměrně vázaného lineárního
** seznamu). Definici konstant a typů naleznete v hlavičkovém souboru c206.h.
**
** Vaším úkolem je implementovat následující operace, které spolu
** s výše uvedenou datovou částí abstrakce tvoří abstraktní datový typ
** obousměrně vázaný lineární seznam:
**
**      DLInitList ...... inicializace seznamu před prvním použitím,
**      DLDisposeList ... zrušení všech prvků seznamu,
**      DLInsertFirst ... vložení prvku na začátek seznamu,
**      DLInsertLast .... vložení prvku na konec seznamu,
**      DLFirst ......... nastavení aktivity na první prvek,
**      DLLast .......... nastavení aktivity na poslední prvek,
**      DLCopyFirst ..... vrací hodnotu prvního prvku,
**      DLCopyLast ...... vrací hodnotu posledního prvku,
**      DLDeleteFirst ... zruší první prvek seznamu,
**      DLDeleteLast .... zruší poslední prvek seznamu,
**      DLPostDelete .... ruší prvek za aktivním prvkem,
**      DLPreDelete ..... ruší prvek před aktivním prvkem,
**      DLPostInsert .... vloží nový prvek za aktivní prvek seznamu,
**      DLPreInsert ..... vloží nový prvek před aktivní prvek seznamu,
**      DLCopy .......... vrací hodnotu aktivního prvku,
**      DLActualize ..... přepíše obsah aktivního prvku novou hodnotou,
**      DLSucc .......... posune aktivitu na další prvek seznamu,
**      DLPred .......... posune aktivitu na předchozí prvek seznamu,
**      DLActive ........ zjišťuje aktivitu seznamu.
**
** Při implementaci jednotlivých funkcí nevolejte žádnou z funkcí
** implementovaných v rámci tohoto příkladu, není-li u funkce
** explicitně uvedeno něco jiného.
**
** Nemusíte ošetřovat situaci, kdy místo legálního ukazatele na seznam 
** předá někdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodně komentujte!
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako
** procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
**/

#include "c206.h"

int solved;
int errflg;

void DLError() {
/*
** Vytiskne upozornění na to, že došlo k chybě.
** Tato funkce bude volána z některých dále implementovaných operací.
**/	
    printf ("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;             /* globální proměnná -- příznak ošetření chyby */
    return;
}

void DLInitList (tDLList *L) {
/*
** Provede inicializaci seznamu L před jeho prvním použitím (tzn. žádná
** z následujících funkcí nebude volána nad neinicializovaným seznamem).
** Tato inicializace se nikdy nebude provádět nad již inicializovaným
** seznamem, a proto tuto možnost neošetřujte. Vždy předpokládejte,
** že neinicializované proměnné mají nedefinovanou hodnotu.
**/
	L->First=NULL;
	L->Last=NULL;
	L->Act=NULL;
}

void DLDisposeList (tDLList *L) {
/*
** Zruší všechny prvky seznamu L a uvede seznam do stavu, v jakém
** se nacházel po inicializaci. Rušené prvky seznamu budou korektně
** uvolněny voláním operace free. 
**/
	tDLElemPtr Elem = L->First;
	while(L->First!=NULL)
{
		L->First = L->First->rptr;
		free(Elem);
		Elem = L->First;
	}
	DLInitList(L);
 	//L->First=NULL;
	//L->Last=NULL;
	//L->Act=NULL;                  
}

void DLInsertFirst (tDLList *L, int val) {
/*
** Vloží nový prvek na začátek seznamu L.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/
		
 tDLElemPtr newElem = (tDLElemPtr) malloc(sizeof(struct tDLElem));
	if (!newElem)
	{
		DLError();
		return;
	}

	newElem->data = val; //nastavení dat
	if (L->First==NULL)
	{
		L->First= newElem; //pridany prvok bude prvy
		L->Last= newElem;
		newElem->lptr = NULL; //ostatne ukazatele sa zmenia
		newElem->rptr = NULL;
	}
	else
	{
		L->First->lptr = newElem;
		newElem->lptr = NULL;
		newElem->rptr = L->First;
		L->First = newElem;

	}
}

void DLInsertLast(tDLList *L, int val) {
/*
** Vloží nový prvek na konec seznamu L (symetrická operace k DLInsertFirst).
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/ 	
 tDLElemPtr newElem = (tDLElemPtr) malloc(sizeof(struct tDLElem));
	if (!newElem)
	{
		DLError();
		return;
	}

	newElem->data = val; //priradenie dat 
	if (L->First==NULL)
	{
		L->First = newElem;
		L->Last = newElem;
		newElem->lptr=NULL;
		newElem->rptr=NULL;
	}
	else
	{
		L->Last->rptr = newElem; //prida prvok na koniec 
		newElem->rptr = NULL;
		newElem->lptr = L->Last;
		L->Last = newElem;
	} 
}

void DLFirst (tDLList *L) {
/*
** Nastaví aktivitu na první prvek seznamu L.
** Funkci implementujte jako jediný příkaz (nepočítáme-li return),
** aniž byste testovali, zda je seznam L prázdný.
**/
L->Act = L->First;
}

void DLLast (tDLList *L) {
/*
** Nastaví aktivitu na poslední prvek seznamu L.
** Funkci implementujte jako jediný příkaz (nepočítáme-li return),
** aniž byste testovali, zda je seznam L prázdný.
**/	
 L->Act = L->Last;                   
}

void DLCopyFirst (tDLList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu prvního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/
 if (!L->First)
	{
		DLError();
		return;
	}

	*val = L->First->data;
}

void DLCopyLast (tDLList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu posledního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/
 if (!L->Last)
	{
		DLError();
		return;
	}
	*val = L->Last->data; 
}

void DLDeleteFirst (tDLList *L) {
/*
** Zruší první prvek seznamu L. Pokud byl první prvek aktivní, aktivita 
** se ztrácí. Pokud byl seznam L prázdný, nic se neděje.
**/
	
	
 tDLElemPtr first = L->First;
	if (first) 
	{
		if (first == L->Act) //kontroluje ci je prvy prvok aj aktivny prvok
		{
			L->Act = NULL;
		}

		if (first == L->Last) 
		{
			L->Last = NULL; //posledny prvok bude NULL
		}
		else 
		{
			first->rptr->lptr = NULL; 
		}
		L->First = first->rptr;
		free(first); //uvolnenie prveho prvku
	}
}	

void DLDeleteLast (tDLList *L) {
/*
** Zruší poslední prvek seznamu L. Pokud byl poslední prvek aktivní,
** aktivita seznamu se ztrácí. Pokud byl seznam L prázdný, nic se neděje.
**/ 
	tDLElemPtr last = L->Last;
	if (last)
	{
		if (last == L->Act) //kontrola ci je posledny prvok aktualny
		{
			L->Act = NULL;
		}

		if (last == L->First) //kontrola ci je posledny prvok aj prvym prvkom
		{
			L->First = NULL; 
		}
		else //ak je viacej prvkov
		{
			last->lptr->rptr = NULL; 
		}
		L->Last = last->lptr;
		free(last); //uvolnenie posledneho prvku zo zoznamu
	}
}

void DLPostDelete (tDLList *L) {
/*
** Zruší prvek seznamu L za aktivním prvkem.
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** posledním prvkem seznamu, nic se neděje.
**/		
 if (L->Act && L->Act != L->Last)
	{
		tDLElemPtr elem = L->Act->rptr; 
		L->Act->rptr = elem->rptr; //pravy ukazatel elem bude rovny s pravym ukazovatelom aktualneho prvku
		if (elem == L->Last) 
		{
			L->Last = L->Act; //posledny prvok bude aktivny
		}
		else
		{
			elem->rptr->lptr = L->Act; //lavy ukazatel bude aktivny prvok
		}
		free(elem); 
	}
}

void DLPreDelete (tDLList *L) {
/*
** Zruší prvek před aktivním prvkem seznamu L .
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** prvním prvkem seznamu, nic se neděje.
**/		
 if (L->Act && L->Act != L->First)
	{
		tDLElemPtr elem = L->Act->lptr; 
		L->Act->lptr = elem->lptr; 
		if (elem == L->First) 
		{
			L->First = L->Act; //prvy prvok bude aktivny
		}
		else //ak elem nie je prvym prvkom
		{
			elem->lptr->rptr = L->Act; 
		}
		free(elem); 
	} 
}

void DLPostInsert (tDLList *L, int val) {
/*
** Vloží prvek za aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/
 if (L->Act)
	{
		tDLElemPtr newElem = (tDLElemPtr) malloc(sizeof(struct tDLElem)); //alokacia noveho elementu
		if (!newElem) //kontrola alokacie
		{
			DLError();
			return;
		}

	newElem->data = val;
	newElem->rptr = L->Act->rptr;
	newElem->lptr = L->Act;
	L->Act->rptr = newElem;
	if (L->Act == L->Last) L->Last = newElem;
	else newElem->rptr->lptr = newElem;
	}
}

void DLPreInsert (tDLList *L, int val) {
/*
** Vloží prvek před aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/
 if (L->Act)
	{
		if (L->Act == NULL) 
		{
			return;
		}

  tDLElemPtr newElem = malloc(sizeof(struct tDLElem)); //alokacia noveho prvku
	if (!newElem) //kontrola uspesnej alokacie
	{
		DLError();
		return;
	}

	newElem->data = val;
	newElem->lptr = L->Act->lptr;
	newElem->rptr = L->Act;
	L->Act->lptr = newElem;
	if (L->Act == L->First) L->First = newElem;
	else newElem->lptr->rptr = newElem;
	}
}

void DLCopy (tDLList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu aktivního prvku seznamu L.
** Pokud seznam L není aktivní, volá funkci DLError ().
**/
 if (!L->Act)
	{
		DLError();
		return;
	}
	*val = L->Act->data; 
}

void DLActualize (tDLList *L, int val) {
/*
** Přepíše obsah aktivního prvku seznamu L.
** Pokud seznam L není aktivní, nedělá nic.
**/		
 if (L->Act)
	{
		L->Act->data = val; 
	}                   
}

void DLSucc (tDLList *L) {
/*
** Posune aktivitu na následující prvek seznamu L.
** Není-li seznam aktivní, nedělá nic.
** Všimněte si, že při aktivitě na posledním prvku se seznam stane neaktivním.
**/		
 if (L->Act)
	{
		if (L->Act == L->Last) L->Act = NULL;
		else L->Act = L->Act->rptr;  //presunie aktivitu na nasledujuci prvok zoznamu
	}                   
}


void DLPred (tDLList *L) {
/*
** Posune aktivitu na předchozí prvek seznamu L.
** Není-li seznam aktivní, nedělá nic.
** Všimněte si, že při aktivitě na prvním prvku se seznam stane neaktivním.
**/		
 if (L->Act)
	{
   if (L->Act == L->First) L->Act = NULL;
    else L->Act = L->Act->lptr;
	}                  
}

int DLActive (tDLList *L) {
/*
** Je-li seznam L aktivní, vrací nenulovou hodnotu, jinak vrací 0.
** Funkci je vhodné implementovat jedním příkazem return.
**/
  return (L->Act == NULL) ? FALSE : TRUE;
}
/* Konec c206.c*/
