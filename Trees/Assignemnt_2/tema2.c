//Antemir Andreea-Catalina - 314CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE 256
#define MAX_INPUT 1000
#define MAX_CODIFS 1000

//structura pt un nod al arborelui
typedef struct node_t node_t;
struct node_t {
	int freq;
	char *name;
	node_t *left;
	node_t *right;
};

//structura pt min_heap
//cod luat din laborator
typedef struct {
	node_t **arr;
	int size;
	int capacity;
	size_t data_size;
	int (*cmp)(const void *key1, const void *key2);
} heap_t;

//functie de comparare a doua noduri ale arborelui (qsort)
int compare_nodes(const void *a, const void *b) {
	node_t *na = *(node_t **)a; //facem cast la tipul de date
	node_t *nb = *(node_t **)b; //facem cast la tipul de dat
	if (na->freq != nb->freq)
		return na->freq - nb->freq;
	return strcmp(na->name, nb->name);
}

//functie de creare a lui min_heap
heap_t *create_heap(int capacity, size_t data_size,
	int (*cmp)(const void *key1, const void *key2)) {
	heap_t *heap = (heap_t *)malloc(sizeof(heap_t)); //alocam memorie pt heap
	if (!heap) {
		fprintf(stderr, "Error\n");
		return NULL;
	}
	//alocam memorie pt vectorul de elemente din heap
	heap->arr = malloc(capacity * data_size);
	if (!heap->arr) {
		fprintf(stderr, "Error\n");
		return NULL;
	}
	//initializam campurile pt un min_heap
	heap->capacity = capacity;
	heap->cmp = cmp;
	heap->data_size = data_size;
	heap->size = 0;
	return heap;
}

//functie de creare a unui nod
node_t *create_node(int freq, char *name) {
	//alocam memorie pt un satelit
	node_t *node = (node_t *)malloc(sizeof(node_t));
	if (!node) {
		fprintf(stderr, "Error\n");
		return NULL;
	}
	//aloc memorie pt numele unui satelit
	//strlen(name) + 1 --- +1 vine de la terminatorul de rand
	node->name = (char *)malloc(strlen(name) + 1);
	if (!node->name) {
		fprintf(stderr, "Error\n");
		free(node);
		return NULL;
	}
	//alocam memorie pt un nod din arbore
	node->freq = freq;
	strcpy(node->name, name);
	node->left = NULL;
	node->right = NULL;
	return node;
}

//functie de eliberare a memoriei nodului
void free_node(node_t *node) {
	if (!node)
		return;
	free(node->name);
	free_node(node->left);
	free_node(node->right);
	free(node);
}

//functie de eliberare a memoriei heap ului
void free_heap(heap_t *heap) {
	if (!heap)
		return;
	free(heap->arr);
	free(heap);
}

//functie care face min_heap ul sa si mentina proprietatea
//cod luat din laborator
void heapify_min(heap_t *heap, int pos) {
	if (!heap) {
		fprintf(stderr, "Error\n");
		return;
	}
	int p = pos; //presupunem min elementul de pe pos
	int l = 2 * p + 1; //fiul stanga
	int r = 2 * p + 2; //fiul drept
	//daca exista nod stang si este mai mic decat nodul curent, consideram min
	if (l < heap->size) {
		if (heap->cmp(&heap->arr[l], &heap->arr[p]) < 0)
			p = l;
	}
	//daca exista nod drept si este mai mic decat nodul curent, consideram min
	if (r < heap->size) {
		if (heap->cmp(&heap->arr[r], &heap->arr[p]) < 0)
			p = r;
	}
	//daca min nu este pe pozitia curenta,
	//actualizam pozitia si continuam cu urmatorul
	if (heap->cmp(&heap->arr[pos], &heap->arr[p]) > 0) {
		node_t *tmp = heap->arr[pos];
		heap->arr[pos] = heap->arr[p];
		heap->arr[p] = tmp;
		heapify_min(heap, p); //pastram proprietatea de min_heap
	}
}

//functie de inserare a unui nod in min_heap
//am combinat cele doua functii din curs
void insert(heap_t *heap, void *data) {
	if (!heap || !data || !heap->arr) {
		fprintf(stderr, "Error\n");
		return;
	}
	//verificam daca mai putem insera noduri in arbore
	if (heap->size == heap->capacity) {
		fprintf(stderr, "Error\n");
		return;
	}
	//daca mai este loc adaugam nodul
	int pos = heap->size; //pozitia pe care dorim sa inseram (la final)
	heap->arr[pos] = *(node_t **)data;
	heap->size++; //marim dimensiunea ca sa putem adauga
	int parent = (pos - 1) / 2; //pozitia parintelui nodului curent
	while (pos > 0 && heap->cmp(&heap->arr[pos], &heap->arr[parent]) < 0) {
		//daca fiul este mai mic decat paeintele sau facem swap
		node_t *tmp = heap->arr[pos];
		heap->arr[pos] = heap->arr[parent];
		heap->arr[parent] = tmp;
		//repetam pasii pana cand ajungem la radacina
		pos = parent;
		parent = (pos - 1) / 2;
	}
}

//returneaza cel mai mic element din min_heap(radacina)
//cod luat din laborator
node_t *heap_top(heap_t *heap) {
	if (!heap) {
		fprintf(stderr, "Error\n");
		return NULL;
	}
	//cel mai mic element din min_heap = radacina
	if (heap->size > 0)
		return heap->arr[0];
	return NULL;
}

//functie de stergere a celui mai mic element din min_heap
//cod luat din laborator
void delete(heap_t *heap) {
	if (heap->size == 0 || !heap) {
		fprintf(stderr, "Error\n");
		return;
	}
	//mutam ultimul nod in locul radacinii pe care dorim sa o stergem
	//facand swap
	node_t *tmp = heap->arr[0];
	heap->arr[0] = heap->arr[heap->size - 1];
	heap->arr[heap->size - 1] = tmp;
	heap->size--; //scadem numarul de elemente
	heapify_min(heap, 0); //pastram proprietatea de min_heap
}

//functie de afisare a arborelui
void print_tree(FILE *out, node_t *node, int n) {
	if (!node) {
		fprintf(stderr, "Error\n");
		return;
	}
	//alocam memorie pt bufferul cu care parcurgem arborele in latime
	//un arbore complet are (2 * n - 1) noduri
	node_t **elements_tree = (node_t **)malloc(sizeof(node_t*) * (2 * n - 1));
	if (!elements_tree) {
		fprintf(stderr, "Error\n");
		return;
	}
	//parcurgem in latime arborele
	//start = pozitia de pe care citim
	//end = pozitia pe care scriem
	int start = 0, end = 0;
	elements_tree[end++] = node; //primul element este radacina
	while (start < end) {
		int level = end - start; //nr de noduri aflate pe nivelul curent
		for (int i = 0; i < level; i++) {
			//afisam elementul de abia citit
			node_t *current_node = elements_tree[start++];
			if (current_node) {
				fprintf(out, "%d-%s ", current_node->freq, current_node->name);
				//ii adaugam si copiii in vector daca exista
				if (current_node->left)
					elements_tree[end++] = current_node->left;
				if (current_node->right)
					elements_tree[end++] = current_node->right;
			}
		}
		fprintf(out, "\n");
	}
	//eliberam memoria
	free(elements_tree);
}

//functie care se ocupa cu contruirea arborelui
node_t *built_tree(FILE *in, FILE *out, int *n_out) {
	int n, freqs[MAX_INPUT];
	char names[MAX_INPUT][NAME_SIZE];

	fscanf(in, "%d", &n);
	//n_out retine numarul de sateliti initiali,
	//deoarece ne folosim de acest numar pentru alocarea memoriei
	//in print_each_level si find_leaf
	if (n_out)
		*n_out = n;
	for (int i = 0; i < n; i++) {
		fscanf(in, "%d", &freqs[i]);
		fscanf(in, "%s", names[i]);
	}
	//cream min_heap ul
	heap_t *heap = create_heap(n, sizeof(node_t *), compare_nodes);
	if (!heap) {
		fprintf(stderr, "Error\n");
		return NULL;
	}
	for (int i = 0; i < n; i++) {
		node_t *node = create_node(freqs[i], names[i]);
		if (!node) {
			fprintf(stderr, "Error\n");
			free_heap(heap);
			return NULL;
		}
		insert(heap, &node);
	}
	while (heap->size > 1) {
		//extragem cele mai mici doua noduri
		node_t *a = heap_top(heap);
		delete(heap);
		node_t *b = heap_top(heap);
		delete(heap);
		//stabilim care dintre ele se afla in stanga si care se afla in dreapta
		node_t *l, *r;
		if (compare_nodes(&a, &b) <= 0) {
			l = a;
			r = b;
		} else {
			l = b;
			r = a;
		}
		//cream parintele
		//freq_parinte = freq_stanga + freq_dreapta
		//numele este forumat din concatenarea numelor celor doi copii
		char *par_name = (char *)malloc(strlen(l->name) + strlen(r->name) + 1);
		strcpy(par_name, l->name);
		strcat(par_name, r->name);
		node_t *parent = create_node(l->freq + r->freq, par_name);
		free(par_name);
		parent->left = l;
		parent->right = r;
		//inseram parintele in heap
		insert(heap, &parent);
	}
	//extragem radacina pe baza careia vom avea acces la arborele creat
	node_t *tree = heap_top(heap);
	delete(heap); //si o stergem din heap
	free_heap(heap);
	return tree;
}

//functie de procesare a cerintei -c1
void process_c1(FILE *in, FILE *out) {
	int n = 0; //numarul de sateliti (frunze)
	node_t *tree = built_tree(in, out, &n); //cream arborele
	print_tree(out, tree, n); //si il afisam in output
	free_node(tree);
}

//functie de procesare a cerintei -c2
void process_c2(FILE *in, FILE *out) {
	//construim arborele
	//nu avem nevoie de nr de frunze aici deci ii dam parametrul NULL
	node_t *tree = built_tree(in, out, NULL);
	int nr_cods;
	char codes[MAX_INPUT][MAX_CODIFS];
	fscanf(in, "%d", &nr_cods);
	for (int i = 0; i < nr_cods; i++)
		fscanf(in, "%s", codes[i]);
	//pentru fiecare cod parcurgem arborele
	for (int i = 0; i < nr_cods; i++) {
		node_t *node = tree;
		//avansam in stanga sau in drepta in functie de 0 sau 1
		for (int j = 0; j < strlen(codes[i]); j++) {
			if (codes[i][j] == '0')
				node = node->left;
			if (codes[i][j] == '1')
				node = node->right;
			//daca ajungem intr o frunza de la care nu putem avansa
			//ne intoarcem la radacina si continuam cautarea
			if (!node->left && !node->right) {
				if (j < strlen(codes[i])) {
					fprintf(out, "%s ", node->name);
					node = tree;
				}
			}
		}
		fprintf(out, "\n");
	}
	//eliberam memoria
	free_node(tree);
}

//functie care cauta frunza cu numele cautat in subarborele al
//carei radacina este nodul curent
int find_leaf(node_t *node, char *name, int n) {
	//alocam memorie pt bufferul cu care parcurgem arborele in latime
	//un arbore complet are (2 * n - 1) noduri
	node_t **satelits = (node_t **)malloc(sizeof(node_t *) * (2 * n - 1));
	//start = pozitia primului element nevizitat
	//end = prima poziitie libera
	int start = 0, end = 0;
	satelits[end++] = node; //adaugam radacina

	while (start < end) {
		node_t *aux = satelits[start++]; //verificam primul element din buffer
		//verificam daca e frunza
		if (!aux->left && !aux->right) {
			//daca este si are numele pe care il cautam returnam 1
			if (strcmp(aux->name, name) == 0) {
				free(satelits);
				return 1;
			}
		}
		//daca nu e frunza ii verificam copiii adaugandu i in buffer daca exista
		if (aux->left)
			satelits[end++] = aux->left;
		if (aux->right)
			satelits[end++] = aux->right;
	}
	//eliberam memoria si returnam 0 daca nu am gasit ce cautam
	free(satelits);
	return 0;
}

//functie de procesare a cerintei -c3
void process_c3(FILE *in, FILE *out) {
	int n = 0; //numarul de sateliti (frunze)
	node_t *tree = built_tree(in, out, &n); //construim arborele
	int nr_codes;
	//code = sirul care contine codificarea finala a tuturor frunzelor
	//names = vectorul cu toate numele frunzelor care trebuiesc codificte
	char names[MAX_INPUT][NAME_SIZE], code[MAX_CODIFS] = "";
	int len = 0;

	fscanf(in, "%d", &nr_codes);
	for (int i = 0; i < nr_codes; i++)
		fscanf(in, "%s", names[i]);
	for (int i = 0; i < nr_codes; i++) {
		node_t *node = tree;
		//parcurgem arborele pana ajungem la o frunza
		while (node->left || node->right) {
			//daca frunza cautata se afla in stanga nodului curent, punem '0'
			if (node->left && find_leaf(node->left, names[i], n) != 0) {
				code[len++] = '0';
				node = node->left;
			//daca frunza cautata se afla in dreapta nodului curent punem '1'
			} else if (node->right && find_leaf(node->right, names[i], n) != 0) {
				code[len++] = '1';
				node = node->right;
			//daca frunza nu a fost gasita pe nicio ramura oprim bucla
			} else {
				break;
			}
		}
	}
	code[len] = '\0'; //adaugam terminatorul de sir
	fprintf(out, "%s", code);
	//eliberam memoria
	free_node(tree);
}

//functie de procesare a cerintei -c4
void process_c4(FILE *in, FILE *out) {
	//construim arborele
	//nu avem nevoie de nr de frunze aici deci ii dam parametrul NULL
	node_t *tree = built_tree(in, out, NULL);
	int nr_satelits;
	char names[MAX_INPUT][NAME_SIZE];

	fscanf(in, "%d", &nr_satelits);
	for (int i = 0; i < nr_satelits; i++)
		fscanf(in, "%s", names[i]);
	//parcurgem arbborele cat timp subarborele
	//stanga sau drept contine toate numele cautate
	node_t *node = tree;
	int printed = 0;
	while (node->left || node->right) {
		//ok = contor
		//l = am coboram in stanga?
		//r = am coboram in dreapta?
		int ok = 0, l = 0, r = 0;
		//daca exista copilul stang si nu am coborat deja 
		if (node->left && ok == 0) {
			for (int i = 0; i < nr_satelits; i++) {
				//verificam daca nodul curent contine toate numele cautate
				if (strstr(node->left->name, names[i]))
					ok++;
			}
			//daca le contine coboram in stanga
			if (ok == nr_satelits) {
				node = node->left;
				l = 1;
			} else {
				ok = 0;
			}
		}
		//daca exista copilul drept si nu am coborat deja
		if (node->right && ok == 0) {
			for (int i = 0; i < nr_satelits; i++) {
				//verificam daca nodul curent contine toate numele cautate
				if (strstr(node->right->name, names[i]))
					ok++;
			}
			//daca le contine coboram in dreapta
			if (ok == nr_satelits) {
				node = node->right;
				r = 1;
			} else {
				ok = 0;
			}
		}
		//daca nu am coborat in arbore inseamna ca nodul curent este cel cautat
		if (l == 0 && r == 0) {
			fprintf(out, "%s", node->name);
			printed = 1;
			break;
		}
	}
	//daca nu am afisat niciun alt nod inseamna ca cel cautat este radacina
	if (printed == 0)
		fprintf(out, "%s", tree->name);
	free_node(tree);
}

//functie care inchide fisierele
void close_files(FILE *in, FILE *out) {
	if (in)
		fclose(in);
	if (out)
		fclose(out);
}

int main(int argc, char *argv[]) {
	if (argc != 4) {
		fprintf(stderr, "Error10\n");
		return 0;
	}
	FILE *in = fopen(argv[2], "rt");
	FILE *out = fopen(argv[3], "wt");
	if (!in || !out) {
		close_files(in, out);
		return 0;
	}
	if (strcmp(argv[1], "-c1") == 0)
		process_c1(in, out);
	else if (strcmp(argv[1], "-c2") == 0)
		process_c2(in, out);
	else if (strcmp(argv[1], "-c3") == 0)
		process_c3(in, out);
	else if (strcmp(argv[1], "-c4") == 0)
		process_c4(in, out);
	fclose(in);
	fclose(out);
	return 0;
}
