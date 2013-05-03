#include<stdlib.h>
#include<stdio.h>
#include<string.h>
struct node
{
	char c;
	int freq;
	struct node *link;
	struct node *rlink;
	struct node *llink;
};

typedef struct node node_t;

struct List
{
	node_t *head;
};

typedef struct List List_t;

struct code_generated
{
    unsigned char c :8;
};

struct info
{
	int freq;
	unsigned char ch;
};

typedef struct info info;

typedef struct code_generated code_generated;
void encode(char *,char *);

void insert_in_list(List_t *,node_t *);

void init_list(List_t *ptr);

void disp_list(const List_t *ptr);

void make_node(List_t *ptr,int n,char c);

void make_list(List_t *ptr,int *freq);

void find_freq(FILE *f1,int *freq);

void make_tree(List_t *ptr,int freq[]);

void find_code(node_t *ptr,char code[],char codes[256][40]);

void compress(FILE *fp,FILE *en,char codes[256][40],int no_of_chars,info header[],int freq[],int num);

unsigned char convert_string_char(char string[9]);

int find_no_of_chars(int freq[]);

void strre(char *,int);

node_t * decode_char(FILE *de,node_t *,int,int,node_t *,int *,int);

void decode(char *,char *);

int create_header(int *,int,info []);
