#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
#include<windows.h>
#include<time.h>

static unsigned long int p, q, n, t, flag ,e[100],d[100],j;

int prime(int);
int gen();
void genPQ();
void ce();
int cd(int);
void encrypt(FILE *, FILE *); 
void decrypt(FILE *, FILE *);



void main()
{	int role;
	char ch;
	FILE *fpm, *fpe, *fpd;
	start:
	system("cls"); // clrscr();
	printf("\n-- RSA Algorithm demonstration --\n");
	SetConsoleTitle("RSA Algorithm");
	printf("\n\t+-------------+\n\t| Select Role |\n\t+---+---------+");
    printf("\n\t| 1 | Sender  |\n\t+---+---------+\n\t| 2 | Reciver |\n\t+---+---------+");
	printf("\n\nEnter choice : ");
	scanf("%d",&role);
	if(role==1)
		goto send;
	else if(role==2)
		goto recive;
	else
	{	printf("\n\tInvalid input\n");
		getch();
		goto start;
	}
	
send:
	SetConsoleTitle(" Sender --> ");
	fpm = fopen("Enter_ur_text.txt", "w");
	fpe = fopen("Encoded_data.txt", "w");
	printf("Enter Public key of reciver\n E= ");
	scanf("%d",&e[0]);
	printf(" N= ");
	scanf("%d",&n);
	printf("\n Enter Your data: \n");
	while( (ch = getchar())!= EOF)
		putc(ch,fpm);

	fclose(fpm);
	fpm = fopen("Enter_ur_text.txt", "r");
	encrypt(fpm,fpe);
	printf("\nData is encoded");
	fclose(fpe);
	fclose(fpm);
	getch();
exit(0);
	
recive:
	SetConsoleTitle(" Reciver <--");
	genPQ();
	n=p*q;
	t=(p-1)*(q-1);
	ce();
	printf("\nPublic keys E=%d, N=%d",e[0],n);
	printf("\nPlace \"Encoded_data.txt\" @");
	system("cd");
	getch();
	fpe = fopen("Encoded_data.txt","r");
    if (fpe == NULL)
    {	printf("\n Error 404: File not found\n Place your file :( \n");
        exit(0);
    }
	fpd = fopen("Decoded_data.txt", "w");
	decrypt(fpe,fpd);
	printf("\nData is decoded\n");
	printf("\nDecoded data\n");
    fclose(fpe);
	fclose(fpd);
	fpd = fopen("Decoded_data.txt", "r");
	ch = fgetc(fpd);
    while (ch != EOF)
    {	printf ("%c", ch);
        ch = fgetc(fpd);
    }
	fclose(fpd);
	getch();
exit(0);
}

int prime(int pr) {
	int i,j;
	j=sqrt(pr);
	for (i=2;i<=j;i++) {
		if(pr%i==0)
		    return 0;
	}
	if(pr==0||pr==1||pr==2)
		return 0;
	return 1;
 }

int gen()
{	int flag=0,a=0;
	srand(time(NULL));
	while(!flag)
	{	a=rand()%100000;
		flag=prime(a);
		
	}
	return a;
}

void genPQ()
{	int i;
	p=gen();
	for(i=0;i<10000;i++)
		q=gen();
	if(p==q)
		genPQ();
}

void ce() {
	int k=0,i;
	for (i=2;i<t;i++) {
		if(t%i==0)
		    continue;
		flag=prime(i);
		if(flag==1&&i!=p&&i!=q) {
			e[k]=i;
			flag=cd(e[k]);
			if(flag>0) {
				d[k]=flag;
				k++;
			}
			if(k==99)
			        break;
		}
	}
}

int cd( int x) {
	int k=1;
	while(1) {
		k=k+t;
		if(k%x==0)
		    return(k/x);
	}
}


void encrypt(FILE *fpm, FILE *fpe)
{
	unsigned long int pt,ct=1,key=e[0];
	pt=fgetc(fpm);
	while(pt!=EOF)
	{	for(j=0;j<key;j++)
		{	ct*=pt;
			ct=ct%n;
		}
		putw(ct,fpe);
		pt=fgetc(fpm);
		ct=1;
	}
	
}
 
void decrypt(FILE *fpe, FILE *fpd )
{
	unsigned long int pt=1,ct,key=d[0];
	ct=getw(fpe);
	while(ct!=EOF)		
	{	for(j=0;j<key;j++)
		{	pt*=ct;
			pt=pt%n;
		}
		fputc(pt,fpd);
		ct=getw(fpe);
		pt=1;
	}
}
 
