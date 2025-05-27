/*Antemir Andree-Catalina 314CA*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define URL_SIZE 50
#define COMMAND_LEN 100
#define LEN_SIZE 256

//struct nod lista dublu inlantuita
typedef struct node_dlist_t {
	void *data;
	struct node_dlist_t *next;
	struct node_dlist_t *prev;
} node_dlist_t;

//struct pagina
typedef struct page_t page_t;
struct page_t {
	int id;
	char url[URL_SIZE];
	char *description;
};

//struct nod lista simpla
typedef struct node_stack_t {
	page_t *data;
	struct node_stack_t *next;
} node_stack_t;

//struct lista dublu inlantuita
typedef struct d_list_t {
	node_dlist_t *head;
	unsigned int data_size;
	int size;
} d_list_t;

//struct lista simplu inlantuita
typedef struct list_t {
	node_stack_t *head;
	unsigned int data_size;
	int size;
} list_t;

//struct stiva
typedef struct stack_t {
	list_t *list;
} stack_t;

//struct tab
typedef struct tab_t tab_t;
struct tab_t {
	int id;
	page_t *current_page;
	stack_t *backwardStack;
	stack_t *forwardStack;
};

//struct browser
typedef struct browser_t browser_t;
struct browser_t {
	tab_t *current;
	d_list_t list;
};

/*Functie care creeaza un nod pentru stiva*/
node_stack_t *create_node_stack(page_t *data) {
	node_stack_t *node = (node_stack_t *)malloc(sizeof(node_stack_t));
	if (!node) {
		fprintf(stderr, "Out of memory!\n");
		return NULL;
	}
	node->data = data;
	node->next = NULL;
	return node;
}

/*Functie care creeaza un nod pentru lista de taburi*/
node_dlist_t *create_node_dlist(void *data) {
	node_dlist_t *node = (node_dlist_t *)malloc(sizeof(node_dlist_t));
	if (!node) {
		fprintf(stderr, "Out of memory!\n");
		return NULL;
	}
	node->data = data;
	node->next = NULL;
	node->prev = NULL;
	return node;
}

/*Aceasta functie este cea care adauga un element (pagina) in stiva*/
void push(stack_t *stack, page_t *page) {
	if (!stack || !stack->list || !page)
		return;
	node_stack_t *aux = create_node_stack(page);
	if (!aux)
		return;
	aux->next = stack->list->head;
	stack->list->head = aux;
	stack->list->size++;
}

/*Aceasta functie este cea care elimina un element (pagina) din stiva*/
page_t *pop(stack_t *stack) {
	if (!stack || !stack->list || !stack->list->head)
		return NULL;
	node_stack_t *temp = stack->list->head;
	page_t *aux = temp->data;
	stack->list->head = temp->next;
	stack->list->size--;
	free(temp);
	return aux;
}

/*Functie care verifica daca in stiva exista vreun element sau nu*/
int empty(stack_t *stack)
{
	if (stack->list->size == 0)
		return 1;
	return 0;
}

/*Functie care goleste intreaga stiva*/
void clear(stack_t *stack) {
	if (!stack || !stack->list)
		return;
	node_stack_t *aux = stack->list->head;
	while (aux) {
		node_stack_t *temp = aux;
		aux = aux->next;
		if (temp->data) {
			free(temp->data->description);
			free(temp->data);
		}
		free(temp);
	}
	stack->list->head = NULL;
	stack->list->size = 0;
}

/*Functie care elibereaza memoria alocata pentru intregul btowser*/
void free_browser(browser_t *browser) {
	if (!browser)
		return;
	node_dlist_t *aux = browser->list.head->next;
	while (aux != browser->list.head) {
		tab_t *tab = (tab_t *)aux->data;
		if (tab->current_page) {
			if (tab->current_page->description)
				free(tab->current_page->description);
			free(tab->current_page);
		}
		if (tab->backwardStack) {
			clear(tab->backwardStack);
			free(tab->backwardStack->list);
			free(tab->backwardStack);
		}
		if (tab->forwardStack) {
			clear(tab->forwardStack);
			free(tab->forwardStack->list);
			free(tab->forwardStack);
		}
		node_dlist_t *temp = aux;
		aux = aux->next;
		free(tab);
		free(temp);
	}
	free(browser->list.head);
	free(browser);
}

/*Functie care elibereaza memoria alocata pentru o pagina*/
void free_page(page_t *page) {
	if (page) {
		free(page->description);
		free(page);
	}
}

/*Functie care elibereaza memoria alocata pentru vectorul de pagini*/
void free_pages(page_t *pages, int nr_p) {
	for (int k = 0; k <= nr_p; k++) {
		if (pages[k].description)
			free(pages[k].description);
	}
	free(pages);
}

/*Initializeaza pagina default care va fi deschisa automat in fiecare tab*/
page_t *create_default_page(void) {
	page_t *page = malloc(sizeof(page_t));
	if (!page) {
		fprintf(stderr, "Out of memory!\n");
		return NULL;
	}
	page->id = 0;
	strcpy(page->url, "https://acs.pub.ro/");
	page->description = malloc(strlen("Computer Science") + 1);
	if (!page->description) {
		free(page);
		fprintf(stderr, "Out of memory!\n");
		return NULL;
	}
	strcpy(page->description, "Computer Science");
	return page;
}

/*Functie care creeaza un tab cu id ul specificat*/
tab_t *create_tab(int id) {
	tab_t *tab = (tab_t *)malloc(sizeof(tab_t));
	if (!tab) {
		fprintf(stderr, "Out of memory\n");
		return NULL;
	}
	//Se atribuie id ul specificat
	tab->id = id;
	//Se creeaza pagina default pentru fiecare tab
	tab->current_page = create_default_page();
	if (!tab->current_page) {
		fprintf(stderr, "Out of memory\n");
		free(tab);
		return NULL;
	}
	tab->backwardStack = (stack_t *)malloc(sizeof(stack_t));
	if (!tab->backwardStack) {
		fprintf(stderr, "Out of memory\n");
		free_page(tab->current_page);
		free(tab);
		return NULL;
	}
	tab->backwardStack->list = (list_t *)malloc(sizeof(list_t));
	if (!tab->backwardStack->list) {
		fprintf(stderr, "Out of memory\n");
		free(tab->backwardStack);
		free_page(tab->current_page);
		free(tab);
		return NULL;
	}
	tab->backwardStack->list->head = NULL;
	/*Data_size ul este initializat cu sizeof(page_t) intrucat*/
	/*se afla doar pagini in aceasta stiva*/
	tab->backwardStack->list->data_size = sizeof(page_t);
	tab->backwardStack->list->size = 0;
	tab->forwardStack = (stack_t *)malloc(sizeof(stack_t));
	if (!tab->forwardStack) {
		fprintf(stderr, "Out of memory\n");
		free(tab->backwardStack->list);
		free(tab->backwardStack);
		free_page(tab->current_page);
		free(tab);
		return NULL;
	}
	tab->forwardStack->list = (list_t *)malloc(sizeof(list_t));
	if (!tab->forwardStack->list) {
		fprintf(stderr, "Out of memory\n");
		free(tab->forwardStack);
		free(tab->backwardStack->list);
		free(tab->backwardStack);
		free_page(tab->current_page);
		free(tab);
		return NULL;
	}
	tab->forwardStack->list->head = NULL;
	tab->forwardStack->list->data_size = sizeof(page_t);
	tab->forwardStack->list->size = 0;
	return tab;
}

//Functie care creeaza browser ul
browser_t *create_browser(void) {
	browser_t *browser = (browser_t *)malloc(sizeof(browser_t));
	if (!browser) {
		fprintf(stderr, "Out of memory\n");
		return NULL;
	}
	/*Se creeaza nodul sentinela din lista dublu inlantuita*/
	/*in care sunt retinute toate tab urile*/
	node_dlist_t *sentinela = create_node_dlist(NULL);
	if (!sentinela) {
		free(browser);
		return NULL;
	}
	/*se creeaza legaturile*/
	sentinela->next = sentinela;
	sentinela->prev = sentinela;
	browser->list.head = sentinela;
	/*Data_size ul este initializat cu sizeof(tab_t) intrucat*/
	/*in lista dublu inlantuita se gasesc doar tab uri*/
	browser->list.data_size = sizeof(tab_t);
	browser->list.size = 0;
	browser->current = NULL;
	/*Se creeaza tab ul default cu id ul 0 din browser*/
	tab_t *default_tab = create_tab(0);
	if (!default_tab) {
		free(sentinela);
		free(browser);
		return NULL;
	}
	browser->current = default_tab;
	/*Se adauga tab ul default la lista dublu inlantuita de tab uri*/
	node_dlist_t *browser_node = create_node_dlist(default_tab);
	if (!browser_node) {
		free_page(default_tab->current_page);
		free(default_tab->backwardStack->list);
		free(default_tab->backwardStack);
		free(default_tab->forwardStack->list);
		free(default_tab->forwardStack);
		free(default_tab);
		free(sentinela);
		free(browser);
		return NULL;
	}
	browser_node->next = sentinela;
	browser_node->prev = sentinela;
	sentinela->next = browser_node;
	sentinela->prev = browser_node;
	browser->list.size = 1;
	return browser;
}

/*Functia adauga un nou tab in lista cu id ul reprezentaiv*/
void new_tab(browser_t *browser, int nr_tab) {
	if (!browser || !browser->list.head) {
		fprintf(stderr, "Error\n");
		return;
	}
	/*Se creeaza tab ul*/
	tab_t *tab = create_tab(nr_tab);
	if (!tab) {
		fprintf(stderr, "Error\n");
		return;
	}
	/*Se adauga tab ul creat la lista*/
	node_dlist_t *browser_node = create_node_dlist(tab);
	if (!browser_node) {
		free_page(tab->current_page);
		free(tab->backwardStack->list);
		free(tab->backwardStack);
		free(tab->forwardStack->list);
		free(tab->forwardStack);
		free(tab);
		fprintf(stderr, "Error\n");
		return;
	}
	/*Se creeaza legaturile*/
	browser->list.head->prev->next = browser_node;
	browser_node->prev = browser->list.head->prev;
	browser->list.head->prev = browser_node;
	browser_node->next = browser->list.head;
	browser->current = (tab_t *)browser_node->data;
	browser->list.size++;
}

/*Functie care sterge un tab din lista*/
void close(browser_t *browser, FILE *output) {
	if (!browser || !browser->current) {
		fprintf(stderr, "Error\n");
		return;
	}
	/*Daca se incearca sa se stearga tab ul cu id 0*/
	/*se afiseaza mesajul de eroare*/
	if (browser->current->id == 0) {
		fprintf(output, "403 Forbidden\n");
		return;
	}
	node_dlist_t *aux = browser->list.head->next;
	while (aux != browser->list.head) {
		if ((tab_t *)aux->data == browser->current) {
			/*Se seteaza tab ul curent drept cel din*/
			/*stanga tab ului care trebuie sters*/
			aux->prev->next = aux->next;
			aux->next->prev = aux->prev;
			browser->current = (tab_t *)aux->prev->data;
			browser->list.size--;
			tab_t *tab = (tab_t *)aux->data;
			if (tab) {
				free_page(tab->current_page);
				clear(tab->backwardStack);
				free(tab->backwardStack->list);
				free(tab->backwardStack);
				clear(tab->forwardStack);
				free(tab->forwardStack->list);
				free(tab->forwardStack);
				free(tab);
			}
			free(aux);
			return;
		}
		aux = aux->next;
	}
}

/*Deschide tab ul cu id ul specificat*/
void open(int id, browser_t *browser, FILE *output) {
	/*ok ul ajuta la verificarea daca tab ul cu id ul specificat exista*/
	int ok = 0;
	node_dlist_t *aux = browser->list.head->next;
	while (aux != browser->list.head) {
		/*Daca se gaseste id ul se seteaza tab ul respectiv ca tab curent*/
		/*si ok devine 1 semn ca id ul a fost gasit*/
		if (((tab_t *)aux->data)->id == id) {
			browser->current = (tab_t *)aux->data;
			ok = 1;
			break;
		}
		aux = aux->next;
	}
	/*Daca id ul nu s a gasit se afiseaza mesajul de eroare*/
	if (ok == 0) {
		fprintf(output, "403 Forbidden\n");
		return;
	}
}

/*Seteaza ca tab curent tab ul urmator*/
void next(browser_t *browser) {
	node_dlist_t *aux = browser->list.head->next;
	while (aux != browser->list.head) {
		if ((tab_t *)aux->data == browser->current) {
			/*Daca urmatorul tab este de fapt setinela atunci*/
			/*se alege tab ul cu id 0*/
			if (aux->next != browser->list.head) {
				browser->current = (tab_t *)aux->next->data;
				return;
			} else {
				browser->current = (tab_t *)aux->next->next->data;
				return;
			}
		}
		aux = aux->next;
	}
	if (aux == browser->list.head) {
		fprintf(stderr, "Empty list\n");
		return;
	}
}

/*Seteaza ca tab curent tab ul precedent*/
void prev(browser_t *browser) {
	node_dlist_t *aux = browser->list.head->next;
	while (aux != browser->list.head) {
		if ((tab_t *)aux->data == browser->current) {
			/*Daca tab ul precedent este sentinela atunci*/
			/*se alege ultimul tab din lista*/
			if (aux->prev != browser->list.head) {
				browser->current = (tab_t *)aux->prev->data;
				return;
			} else {
				browser->current = (tab_t *)aux->prev->prev->data;
				return;
			}
		}
		aux = aux->next;
	}
	if (aux == browser->list.head) {
		fprintf(stderr, "Empty list\n");
		return;
	}
}

/*Functia deschide pagina cu id ul specificat*/
void page(int id, browser_t *browser, page_t *pages, int nr_p, FILE *output) {
	/*ok verifica daca id ul exista si*/
	/*pos retine pozitia in care a fost gasita pagina cu id ul respectiv*/
	int i, ok = 0, pos = -1;
	if (!browser || !pages || !output) {
		fprintf(stderr, "Error\n");
		return;
	}
	if (!browser->current || !browser->current->backwardStack ||
		!browser->current->forwardStack) {
		fprintf(stderr, "Error\n");
		return;
	}
	for (i = 0; i <= nr_p; i++) {
		if (id == pages[i].id) {
			ok = 1;
			pos = i;
			break;
		}
	}
	if (ok == 0) {
		/*Daca nu s a gasit id ul se afiseaza mesajul de eroare*/
		fprintf(output, "403 Forbidden\n");
		return;
	} else {
		/*Daca s a gasit se seteaza ca pagina curenta,*/
		/*vechea pagina curenta se pune in stiva bacward si*/
		/*cea forward se goleste*/
		page_t *page = (page_t *)malloc(sizeof(page_t));
		if (!page) {
			fprintf(stderr, "Error\n");
			return;
		}
		if (!pages[pos].description) {
			fprintf(stderr, "Erros\n");
			free(page);
			return;
		}
		page->id = pages[pos].id;
		strcpy(page->url, pages[pos].url);
		page->description = malloc(strlen(pages[pos].description) + 1);
		if (!page->description) {
			fprintf(stderr, "Out of memory\n");
			free(page);
			return;
		}
		strcpy(page->description, pages[pos].description);
		push(browser->current->backwardStack, browser->current->current_page);
		browser->current->current_page = page;
		if (empty(browser->current->forwardStack) == 0)
			clear(browser->current->forwardStack);
	}
}

/*Afiseaza id urile taburile deschise incepand cu cel curent*/
void print(browser_t *browser, FILE *output) {
	if (!browser || !browser->list.head) {
		fprintf(stderr, "Error\n");
		return;
	}
	node_dlist_t *aux = browser->list.head->next;
	while ((tab_t *)aux->data != browser->current)
		aux = aux->next;
	for (int i = 0; i <= browser->list.size; i++) {
		if ((tab_t *)aux->data)
			fprintf(output, "%d ", ((tab_t *)aux->data)->id);
		aux = aux->next;
	}
	/*Afiseaza descrierea tabului curent*/
	fprintf(output, "\n");
	fprintf(output, "%s\n", browser->current->current_page->description);
}

/*Seteaza ca pagina curenta ultima pagina din stiva backward*/
void backward(browser_t *browser, FILE *output) {
	if (!browser || !browser->current) {
		fprintf(stderr, "Error\n");
		return;
	}
	/*Daca stiva este goala se afiseaza mesajul de eroare*/
	if (!browser->current->backwardStack->list->head) {
		fprintf(output, "403 Forbidden\n");
		return;
	}
	page_t *page = pop(browser->current->backwardStack);
	if (!page) {
		fprintf(stderr, "Error\n");
		return;
	}
	/*Se pune vechea pagina curenta in stiva forward*/
	push(browser->current->forwardStack, browser->current->current_page);
	browser->current->current_page = page;
}

/*Seteaza ca pagina curenta ultima pagina din stiva forward*/
void forward(browser_t *browser, FILE *output) {
	if (!browser || !browser->current) {
		fprintf(stderr, "Error\n");
		return;
	}
	/*Daca stiva este goala se afiseaza mesajul de eroare*/
	if (!browser->current->forwardStack->list->head) {
		fprintf(output, "403 Forbidden\n");
		return;
	}
	page_t *page = pop(browser->current->forwardStack);
	if (!page) {
		fprintf(stderr, "Error\n");
		return;
	}
	/*Se pune vechea pagina curenta in stiva backward*/
	push(browser->current->backwardStack, browser->current->current_page);
	browser->current->current_page = page;
}

/*Se afiseaza recursiv, incepand cu primul nod adaugat, stiva forward*/
void print_stack_forward(node_stack_t *node, FILE *output) {
	if (node->next)
		print_stack_forward(node->next, output);
	fprintf(output, "%s\n", node->data->url);
}

/*Se afiseaza recursiv, incepand cu ultimul nod adaugat, stiva backward*/
void print_stack_backward(node_stack_t *node, FILE *output) {
	fprintf(output, "%s\n", node->data->url);
	if (node->next)
		print_stack_backward(node->next, output);
}

/*Afiseaza toate url urile paginilor din tab ul cu id ul specificat incepand*/
/*cu stiva forward, pagina curenta si apoi stiva backward*/
void print_history(int id, browser_t *browser, FILE *output) {
	if (!browser || !browser->list.head) {
		fprintf(stderr, "Error\n");
		return;
	}
	/*Se cauta tab ul cu id ul specificat*/
	node_dlist_t *aux = browser->list.head->next;
	while (aux != browser->list.head && ((tab_t *)aux->data)->id != id)
		aux = aux->next;
	/*Daca id ul nu a fost gasit se afiseaza mesajul de eroare*/
	if (aux == browser->list.head) {
		fprintf(output, "403 Forbidden\n");
		return;
	}
	node_stack_t *aux_stack = ((tab_t *)aux->data)->forwardStack->list->head;
	if (aux_stack)
		print_stack_forward(aux_stack, output);
	fprintf(output, "%s\n", ((tab_t *)aux->data)->current_page->url);
	aux_stack = ((tab_t *)aux->data)->backwardStack->list->head;
	if (aux_stack)
		print_stack_backward(aux_stack, output);
}

/*Functie care inchide fisierele*/
void close_files(FILE *input, FILE *output) {
	if (input) {
		fclose(input);
		return;
	}
	if (output) {
		fclose(output);
		return;
	}
}

/*Functie care proceseaza comanda si apeleaza functia corespunzatoare*/
void verify_command(char *com, browser_t *b, FILE *out, FILE *in,
	int nr, page_t *pages, int nrp, int nrc) {
	for (int i = 0; i < nrc; i++) {
		if (fscanf(in, "%s", com) != 1)
			break;
		if (strcmp(com, "NEW_TAB") == 0) {
			nr++;
			new_tab(b, nr);
		} else if (strcmp(com, "CLOSE") == 0) {
			close(b, out);
		} else if (strcmp(com, "OPEN") == 0) {
			int id;
			if (fscanf(in, "%d", &id) == 1)
				open(id, b, out);
		} else if (strcmp(com, "PAGE") == 0) {
			int id;
			if (fscanf(in, "%d", &id) == 1)
				page(id, b, pages, nrp, out);
		} else if (strcmp(com, "BACKWARD") == 0) {
			backward(b, out);
		} else if (strcmp(com, "FORWARD") == 0) {
			forward(b, out);
		} else if (strcmp(com, "PRINT") == 0) {
			print(b, out);
		} else if (strcmp(com, "PRINT_HISTORY") == 0) {
			int id;
			if (fscanf(in, "%d", &id) == 1)
				print_history(id, b, out);
		} else if (strcmp(com, "NEXT") == 0) {
			next(b);
		} else if (strcmp(com, "PREV") == 0) {
			prev(b);
		}
	}
}

int main(void) {
	int i, nr_pages, nr_commands, nr = 0;
	char command[COMMAND_LEN], s[LEN_SIZE];
	FILE *input = fopen("tema1.in", "rt"), *output = fopen("tema1.out", "wt");
	if (!input || !output) {
		close_files(input, output);
		return 0;
	}
	if (fscanf(input, "%d", &nr_pages) != 1) {
		close_files(input, output);
		return 0;
	}
	/*Se aloca memorie pentru vectorul de pagini si in initializam cu 0*/
	page_t *pages = (page_t *)calloc(nr_pages + 1, sizeof(page_t));
	if (!pages) {
		fprintf(stderr, "Out of memory\n");
		close_files(input, output);
		return 0;
	}
	/*Se creeaza pagina default pentru fiecare tab*/
	page_t *default_page = create_default_page();
	if (!default_page) {
		free(pages);
		close_files(input, output);
		return 0;
	}
	pages[0] = *default_page;
	free(default_page->description);
	free(default_page);
	for (i = 1; i <= nr_pages; i++) {
		/*Se adauga paginile date in vector*/
		if (fscanf(input, "%d\n", &pages[i].id) != 1) {
			free_pages(pages, i);
			close_files(input, output);
			return 0;
		}
		if (!fgets(pages[i].url, URL_SIZE, input)) {
			free_pages(pages, i);
			close_files(input, output);
			return 0;
		}
		if (pages[i].url[strlen(pages[i].url) - 1] == '\n')
			pages[i].url[strlen(pages[i].url) - 1] = '\0';
		if (!fgets(s, LEN_SIZE, input)) {
			free_pages(pages, i);
			close_files(input, output);
			return 0;
		}
		if (s[strlen(s) - 1] == '\n')
			s[strlen(s) - 1] = '\0';
		pages[i].description = (char *)malloc(strlen(s) + 1);
		if (!pages[i].description) {
			free_pages(pages, i);
			close_files(input, output);
			return 0;
		}
		strcpy(pages[i].description, s);
	}
	if (fscanf(input, "%d\n", &nr_commands) != 1) {
		free_pages(pages, nr_pages);
		close_files(input, output);
		return 0;
	}
	/*Se creeaza browser ul*/
	browser_t *browser = create_browser();
	if (!browser) {
		free_pages(pages, nr_pages);
		close_files(input, output);
		return 0;
	}
	/*Se verifica comenzile*/
	verify_command(command, browser, output, input,
		nr, pages, nr_pages, nr_commands);
	for (i = 1; i <= nr_pages; i++)
		free(pages[i].description);
	free(pages);
	free_browser(browser);
	close_files(input, output);
	return 0;
}
