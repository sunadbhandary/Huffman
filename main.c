#include"huff.h"


int main()
{
    	
	int choice;
	char file_name1[50],file_name2[50];    	
	int flag=1;
	while(flag)
	{
		printf("\n\n\t\t\tMENU\n1.Compress File\n2.Decompress File\n0.Exit\n\nEnter Choice\n");
		scanf("%d",&choice);
		
		
		
		switch(choice)
		{
			case 1:			
				printf("\nEnter Name Of File To Be Encoded\n");
				scanf("%s",file_name1);			
				printf("\nEnter Name Of Encoded File\n");
				scanf("%s",file_name2);			
				encode(file_name1,file_name2);
				break;
			case 2:				
				printf("\nEnter Name Of Encoded File\n");
                                scanf("%s",file_name1);    					
				printf("\nEnter Name Of Decompressed File \n");
                                scanf("%s",file_name2);				
    				decode(file_name1,file_name2);				
				break;
			case 0:
				flag=0;
				break;
			default:
				printf("\nWrong Choice Entered...Enter Again\n");
		}
	}
	return 0;
}
