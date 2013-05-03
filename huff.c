/***********************************************************************************************************************************************************************
*																				       *
*									HUFFMAN CODING                                                                                 *
* 		THIS PROGRAM IS TO COMPRESS A TEXT FILE AND TO DECOMPRESS A ENCODED FILE BY USING HUFFMAN'S ALGORITHM WITH THE HELP OF TREES                           *
*																				       *
*                             THIS IS THE PROPERTY OF SUNAD,ROHIT,RANDEEP,RAHUL.............PLEASE DONOT COPY!!!!!!!!!!!!!!!			                       **																				       **																				       *
************************************************************************************************************************************************************************/







#include "huff.h"



void encode(char *file_name1,char *file_name2)
{
	FILE *fp,*en;
	int freq[256]={0};
	info header[256];	
	char codes[256][40];
	char code[40];
	strcpy(code,"");
	List_t mylist_en;
	int num,no_of_chars;
	en=fopen(file_name2,"w");
	fp=fopen(file_name1,"r");
	if(fp)
	{	
		find_freq(fp,freq);
		fclose(fp);		
		no_of_chars=find_no_of_chars(freq);
		fp=fopen(file_name1,"r");
		if(no_of_chars)
		{
		make_tree(&mylist_en,freq);	
		num=create_header(freq,no_of_chars,header);		
		find_code(mylist_en.head,code,codes);
		compress(fp,en,codes,no_of_chars,header,freq,num);		
		}
		else
		{
			printf("\nFile Is Empty\n");
		}
	}
	else 
	{
		printf("\nFile Doesnot Exist\n");
	}
	fclose(fp);
	fclose(en);
}

void decode(char *file_name1,char *file_name2)//to decode a file
{
	info y,*ptrrr;  
    	FILE *en,*de;
    	ptrrr=&y;
    	code_generated x,*ptrr;
    	ptrr=&x;
    	List_t mylist_de;    
    	int no_of_chars;
   	int freq[256]={0};
    	int i,num; 
    	int count=0;
    	en=fopen(file_name1,"r");
    	de=fopen(file_name2,"w");
	if(en)
	{
    		fread(ptrr,sizeof(code_generated),1,en);
    		num=ptrr->c;       
    		for(i=0;i<num;++i)
    		{
          		fread(ptrrr,sizeof(info),1,en);
           		freq[(int)ptrrr->ch]=ptrrr->freq;
    		}       
    		make_tree(&mylist_de,freq);            
    		no_of_chars=find_no_of_chars(freq);    		    
    		node_t *root=mylist_de.head;
    		node_t *ptr=root;
    		while(fread(ptrr,sizeof(code_generated),1,en)==1)
    		{   
       			ptr=decode_char(de,ptr,ptrr->c,1,root,&count,no_of_chars);
    		}
	}
	else
	{
		printf("\nFile Doesnot Exist\n");
	}
	fclose(en);
	fclose(de);
}

//to decode each charcter of compressed file
node_t * decode_char(FILE *de,node_t *ptr,int x,int y,node_t *root,int *count,int no_of_chars)
{
    	if(y!=9 && (*count)!=no_of_chars)//y to track no.of bits used,count to track no of charcters decoded
    	{
        	if(ptr->llink==0 && ptr->rlink==0)//leaf node
        	{
            		fputc(ptr->c,de);
            		ptr=root;
	    		++(*count);
            		ptr=decode_char(de,ptr,x,y,root,count,no_of_chars);
        	}
        	else if(x%2==0 && ptr->llink)
        	{
            		ptr=decode_char(de,ptr->llink,x/2,++y,root,count,no_of_chars);
        	}
        	else if(x%2!=0 && ptr->rlink)
        	{
            		ptr=decode_char(de,ptr->rlink,x/2,++y,root,count,no_of_chars);
        	}
    	}
    	return ptr;
}

void insert_in_list(List_t *,node_t *);//to insert node into priority queue


void init_list(List_t *ptr)//initializing list of nodes
{
	ptr->head=0;
}


void disp_list(const List_t *ptr)//to display the list
{
	node_t *temp=ptr->head;
	while(temp)
	{	
		printf("%d( %c )\t",temp->freq,temp->c);
		temp=temp->link;
	}
	printf("\n");
}


void make_node(List_t *ptr,int n,char c)//to make node of type node_t
{
	node_t *temp;
	temp=(node_t *)malloc(sizeof(node_t));
	temp->freq=n;
	temp->c=c;
	temp->link=0;
	temp->rlink=0;
	temp->llink=0;
	insert_in_list(ptr,temp);
}


void insert_in_list(List_t *ptr,node_t *t)//node inserted in listin ascending order according to value of frequency
{
	if(ptr->head==0)//empty list
	{
		ptr->head=t;
	}
	else
	{
		node_t *prev=0;
		node_t *pres=ptr->head;
		while(pres && pres->freq<=t->freq)
		{
			prev=pres;
			pres=pres->link;
		}
		if(pres==ptr->head)
		{
			ptr->head=t;
			t->link=pres;
		}
		else if(pres==0)
		{
			prev->link=t;

		}
		else
		{
			t->link=pres;
			prev->link=t;
		}
	}
}


void make_list(List_t *ptr,int *freq)//to create list of nodes with frequency
{
	int i;
	for(i=0;i<256;++i)
	{
		if(freq[i]!=0)
		{
			make_node(ptr,freq[i],i);
		}
	}
}

void  find_freq(FILE *fp,int *freq)//to find frequency of each character
{
	char c;
	while((c=fgetc(fp))!=EOF)
	{
		++freq[(int)c];//subscript denotes the ascii value of character		
	}
}
void make_tree(List_t *ptr,int freq[])//to create tree
{
	node_t *t1,*t2;//pointer to first two nodes of queue    		
	init_list(ptr);
        make_list(ptr,freq);       		
	while(ptr->head->link!=0)
	{
		t1=ptr->head;
		t2=ptr->head->link;
		ptr->head=t2->link;
		t1->link=0;
		t2->link=0;
		node_t *temp;
		temp=(node_t *)malloc(sizeof(node_t));
		temp->freq=t1->freq+t2->freq;
		temp->c=0;
		temp->link=0;
		temp->rlink=t2;
		temp->llink=t1;
		insert_in_list(ptr,temp);//new node is added in ascending order
	}	
}

void find_code(node_t *ptr,char code[],char codes[256][40])//to find code for each character in tree
{    
    	char temp[40];//temporary storage of intermediate code    
    	if(ptr->rlink==0 && ptr->llink==0)//base condition
    	{
        	strcpy(codes[(int)(ptr->c)],code);
    	}
    	if(ptr->rlink!=0)//pointer points right
    	{
       		strcpy(temp,code);
        	strcat(temp,"1");//1 added at the end of intermediate code
        	find_code(ptr->rlink,temp,codes);
    	}
    	if(ptr->llink!=0)//pointer points left
    	{
        	strcpy(temp,code);
        	strcat(temp,"0");//0 added at the end of intermediate code
        	find_code(ptr->llink,temp,codes);
    	}   
}

int find_no_of_chars(int freq[])//to find no. of chars in original file
{
    	int i,sum=0;
    	for(i=0;i<256;++i)//0-255 ascii characters only
    	{
       		sum=sum+freq[i];
    	}
    	return sum;
}

void compress(FILE *fp,FILE *en,char codes[256][40],int no_of_chars,info header[],int freq[],int num)//to store a character of original file into encoded file
{
    	char ch;
    	int i=0,j=0,count=0,k,l;//i to keep track of string of code,j to keep track of code of each character,count to keep track of number of each character encoded
    	unsigned char c;//stores binary eqiuivalent of code    
    	code_generated x;
    	char string_rev[9];
    	x.c=num;    
    	fwrite(&x,sizeof(code_generated),1,en);	
    	for(k=0,l=0;k<256;++k)
    	{
		if(freq[k])
		{
			fwrite(&header[l],sizeof(info),1,en);			
			++l;
		}	
    	}	
    	while((ch=fgetc(fp))!=EOF)
    	{
       		j=0;
        	++count;
        	while(codes[(int)ch][j]!='\0')
        	{
            		string_rev[i]=codes[(int)ch][j];
            		++i;
            		++j;
            		if(i==8)
            		{
                		string_rev[i]='\0';
                		strre(string_rev,strlen(string_rev));//string of code is reversed since binary numbers are read from right to left              
                		c=convert_string_char(string_rev);
                		strcpy(string_rev,"");
                		i=0;
                		x.c=c;                
                		fwrite(&x,sizeof(x),1,en);
             		}
            		if(count==no_of_chars )//for last character
            		{
                		while(codes[(int)ch][j])
                		{
                        		string_rev[i]=codes[(int)ch][j];
                        		++i;
                        		++j;
                        		if(i==8)//if code of last character occupies all bits
                        		{
                            			string_rev[i]='\0';
                            			strre(string_rev,strlen(string_rev));                           
                            			c=convert_string_char(string_rev);
                            			strcpy(string_rev,"");
                            			i=0;
                            			x.c=c;
                            			fwrite(&x,sizeof(x),1,en);
                        		}
                		}
                	string_rev[i]='\0';
                	strre(string_rev,strlen(string_rev));                
                	c=convert_string_char(string_rev);
                	strcpy(string_rev,"");
                	x.c=c;
                	fwrite(&x,sizeof(x),1,en);
            		}
        	}
    	}
}




void strre(char *str,int n)//to reverse a string,n is length of string
{
    	int i=0,j=n-1;
    	char temp;
    	while(i<j)
    	{
       		temp=str[i];
        	str[i]=str[j];
        	str[j]=temp;
        	++i;
        	--j;
    	}
   	str[n]='\0';
}
int create_header(int *freq,int no_of_chars,info header[])
{	
	int i,j;
	for(i=0,j=0;i<256;++i)
	{
		if(freq[i]!=0)
		{
			header[j].freq=freq[i];
			header[j].ch=i;			
			++j;
		}
	}
	return j;	
}
unsigned char convert_string_char(char string[8])//to convert string of code into character

{
    	int i=0;
    	unsigned char c=0;//initially c=00000000
	while(string[i])
	{
        	if(string[i]=='1')//to add 1 at the end of binary of c
		{
			c=c*2;//equivalent to bitwise left shift by 1 unit
			c=c+1;
		}
        	else//to add 0 at the end of binary of c
        	{
            		c=c*2;
        	}
        	++i;
    	}
    	return c;
}


