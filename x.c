#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 50

//주민번호는 공개안했음.


typedef struct Cmanage cmanage;
struct Cmanage{
	int cnum; 
	int scnum; //학번
	char cname[30];
	int ssnum;
	int phnum;
	char address[30];
};
typedef struct Vmanage vmanage;
struct Vmanage{
	int vnum;
	char vname[30];
	char genre[30];
	int fee;
	int returned; //return 돼있을 때 1 없을 때 0
};
typedef struct Remanage rmanage;
struct Remanage{
	int rnum;
	int vnum;
	int cnum;
	int returned;  //rental ->1 not->0
};
cmanage *c1[MAX];
vmanage *v1[MAX];
rmanage *r1[MAX];

void init();
void Run();
int selectmenu();
int getnum();
void cregist();
void cinfor();
void viewcostumer(cmanage *c1);
void viewallcusinfor();
void vregist();
void vinfor();
void viewvideo(vmanage *v1);
void viewallvidinfor();
void rental();
void retur();
void exit1();

void main() //main
{
	init();
	Run();
	exit1();
}
void init()
{
	FILE *fp1 = fopen("Customerdata.txt", "r");
	int i;
	if (fp1)
	{
		while (1)
		{
			if (fread(&i, sizeof(int), 1, fp1) < 1)
			{
				break;
			}
			c1[i] = (cmanage *)malloc(sizeof(cmanage));
			fread(c1[i], sizeof(cmanage), 1, fp1);
		}
		fclose(fp1);
	}
	FILE *fp2 = fopen("Videodata.txt", "r");
	if (fp2)
	{
		while (1)
		{
			if (fread(&i, sizeof(int), 1, fp2) < 1)
			{
				break;
			}
			v1[i] = (vmanage *)malloc(sizeof(vmanage));
			fread(v1[i], sizeof(vmanage), 1, fp2);
		}
		fclose(fp2);
	}
}
int getnum()
{
	int num = 0;
	if ((scanf("%d", &num) == 0))
	{
		char buf[256];
		gets_s(buf, sizeof(buf));
	}
	return num;
}
int selectmenu()
{
	printf("<Video rental management program> \n");
	printf("1. New customer registration\n2. Customer information inquiry \n");
	printf("3. View all customer information\n4. New video registration\n");
	printf("5. View video information\n6. View full video information\n");
	printf("7. Rental\n8. Return\n0.Exit\n");
	return getnum();
}


void Run()
{
	int key = 0;
	while ((key = selectmenu()) != 0)
	{
		switch (key)
		{
		case 1: cregist(); break;
		case 2: cinfor(); break;
		case 3: viewallcusinfor(); break;
		case 4: vregist(); break;
		case 5: vinfor(); break;
		case 6: viewallvidinfor(); break;
		case 7: rental(); break;
		case 8: retur(); break;
		default: printf("No number \n"); break;
		}
	}
}

void cregist() //case1
{
	int n = 0;
	cmanage *cman = 0;

	printf("What is your customer number?(1~%d)", MAX);
	n = getnum();
	if ((n < 1) || (n>MAX))
	{
		printf("out of range \n");
		return;
	}
	cman = c1[n - 1];
	if (cman)
	{
		printf("There are already materials \n");
		return;
	}
	cman = (cmanage *)malloc(sizeof(cmanage));
	cman->cnum = n;
	printf("what is your name?");
	scanf("%s", cman->cname);
	printf("학번?");
	scanf("%d", &cman->scnum);
	printf("what is your social security number?");
	scanf("%d", &cman->ssnum);
	printf("what is your phone number?");
	scanf("%d", &cman->phnum);
	printf("address?");
	scanf("%s", cman->address);
	c1[n - 1] = cman;
}

void cinfor() //case 2
{
	int n=0;
	cmanage *cman;
	printf("Write down costumer number do you want");
	n = getnum();
	if ((n < 1) || (n > MAX))
	{
		printf("out of range \n");
		return;
	}
	cman = c1[n - 1];
	if (!cman)
	{
		printf("There are no costumer \n");
		return;
	}
	printf("costumer name : %s \n", cman->cname);
	printf("phone number : %d \n", cman->phnum);
	printf("adderss : %s \n", cman->address);
}
void viewcostumer(cmanage *c1)
{
	printf("costumer name : %s phonenum : %d address : %s\n", c1->cname, c1->phnum, c1->address);
}
void viewallcusinfor() //case 3
{
	int i = 0;
	for (i = 0; i < MAX; i++)
	{
		if (c1[i])
		{
			viewcostumer(c1[i]);
		}
	}
}

void vregist() //case 4
{
	int n = 0;
	vmanage *vman = 0;

	printf("What is video number?(1~%d)", MAX);
	n = getnum();
	if ((n < 1) || (n > MAX))
	{
		printf("out of range \n");
		return;
	}
	vman = v1[n - 1];
	if (vman)
	{
		printf("There are already materials \n");
		return;
	}
	vman = (vmanage *)malloc(sizeof(vmanage));
	vman->vnum = n;
	printf("video name?");
	scanf("%s", vman->vname);
	printf("video genre?");
	scanf("%s", vman->genre);
	printf("fee?");
	scanf("%d", &vman->fee);
	vman->returned = 1;
	v1[n - 1] = vman;
}

void vinfor() //case 5
{
	int n = 0;
	vmanage *vman;
	printf("Write down video number");
	n = getnum();
	if ((n < 1) || (n > MAX))
	{
		printf("out of range \n");
		return;
	}
	vman = v1[n - 1];
	if (!vman)
	{
		printf("There are no video \n");
		return;
	}
	printf("video name : %s \n", vman->vname);
	printf("genre : %s \n", vman->genre);
	printf("fee : %d \n", vman->fee);
	printf("반납 상태 : %d\n", vman->returned); //반납 or 있을 시 1 없을 시 0
}
void viewvideo(vmanage *v1)
{
	printf("video name : %s number : %d genre : %s fee : %d returned : %d\n", v1->vname, v1->vnum, v1->genre, v1->fee, v1->returned);
}
void viewallvidinfor() //case 6
{
	int i = 0;
	for (i = 0; i < MAX; i++)
	{
		if (v1[i])
		{
			viewvideo(v1[i]);
		}
	}
}
void rental() //case 7
{
	int n1 = 0;
	int n2 = 0;
	int n3=0;
	cmanage *cman=0;
	vmanage *vman=0;
	rmanage *rman=0;
	printf("what is your costumer number");
	n1 = getnum();
	if ((n1 < 1) || (n1 > MAX))
	{
		printf("out of range \n");
		return;
	}
	cman = c1[n1 - 1];
	if (!cman)
	{
		printf("Not regist costumer\n");
		return;
	}
	printf("select video\n");
	viewallvidinfor();
	n2 = getnum();
	vman = v1[n2 - 1];
	if ((n2 < 1) || (n2 > MAX))
	{
		printf("out of range \n");
		return;
	}
	if (!vman)
	{
		printf("Not regist video \n");
		return;
	}
	if ((vman->returned) == 0)
	{
		printf("not returned video \n");
		return;
	}
	printf("write rental number(1~%d)", MAX);
	n3 = getnum();
	if ((n3 < 1) || (n3 > MAX))
	{
		printf("out of range \n");
		return;
	}
	rman = r1[n3 - 1];
	rman = (rmanage *)malloc(sizeof(rmanage));
	rman->rnum = n3;
	rman->vnum = n2;
	rman->cnum = n1;
	rman->returned = 1;
	v1[n2 - 1]->returned = 0;
	r1[n3 - 1] = rman;
}

void retur() //case 8
{
	int n;
	int a;
	vmanage *vman;
	rmanage *rman=0;
	printf("write rental number :");
	n = getnum();
	rman = r1[n - 1];
	if (!(rman->rnum))
	{
		printf("not rentaled or wrong rental number");
		return;
	}
	rman = r1[n - 1];
	if (!(rman->returned))
	{
		printf("이미 반납되거나 빌린 적이 없습니다.");
		return;
	}
	a = rman->vnum;
	v1[a - 1]->returned = 1;
	rman->returned = 0;
	rman->cnum = 0;
	rman->rnum = 0;
	rman->vnum = 0;
	r1[n - 1] = rman;
}

void exit1()
{
	FILE *fp1 = fopen("Customerdata.txt", "w");
	int i;
	if (fp1)
	{
		for (i = 0; i < MAX; i++)
		{
			if (c1[i])
			{
				fwrite(&i, sizeof(int), 1, fp1);
				fwrite(c1[i], sizeof(cmanage), 1, fp1);
				free(c1[i]);
			}
		}
		fclose(fp1);
	}
	FILE *fp2 = fopen("Videodata.txt", "w");
	if (fp2)
	{
		for (i = 0; i < MAX; i++)
		{
			if (v1[i])
			{
				fwrite(&i, sizeof(int), 1, fp2);
				fwrite(v1[i], sizeof(vmanage), 1, fp2);
				free(v1[i]);
			}
		}
		fclose(fp2);
	}
	
		for (i = 0; i < MAX; i++)
		{
			if (r1[i])
			{
				free(r1[i]);
			}
		}
	
}
