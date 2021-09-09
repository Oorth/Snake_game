#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define UP 72
#define DN 80
#define LF 75
#define RT 77
#define DELAY 50

const int OX=50,OY=50,EX=550,EY=550;
const int pBOX=10;

int IDX,fud,bdy[50],no;
int R,C;
int DIR;

int fSTART=0;

void REFRESH();
void DRWboard();
void DRWnBOX();
void VEL();
void GMEOVR();
void FOOD();
void BODY();
void START();


main()
{
    initwindow(600,600);
      	   
	fSTART=1;

	while(1)
	{	
		if(fSTART==1)
		{
			cleardevice();
			START();
			
			IDX=1275,fud=0,bdy[50],no=0;
			
			DIR = rand() % (5-1) + 1;	
			
			fud = rand() % (2500-0) + 0;
			bdy[0]=IDX;
			
			fSTART=0;
		}
		
		switch(DIR)
		{
			case 1://UP	
				do
				{
					IDX-=50; R = IDX / 50; C = IDX % 50; 
					REFRESH();
					delay(DELAY);
					
					if(kbhit())
					{
						char key= getch();
						
						switch(key){case 72:DIR=1;break;	case 80:DIR=3;break;	case 75:DIR=4;break;	case 77:DIR=2;break;}
						if(DIR!=1)break;
					}
					
				}while(R>=1);	 
				   
				if(DIR==1)GMEOVR();
				
				break;
					
			case 2://RT
				do
				{
					IDX++; R = IDX / 50; C = IDX % 50;
					REFRESH();
					delay(DELAY);
					
					if(kbhit())
					{
						char key= getch();
						
						switch(key){case 72:DIR=1;break;	case 80:DIR=3;break;	case 75:DIR=4;break;	case 77:DIR=2;break;}
						if(DIR!=2)break;
					}

				}while(C<49);
				
				if(DIR==2)GMEOVR();
				
				break;
		
			case 3://DN
				do
				{
					IDX+=50; R = IDX / 50; C = IDX % 50;
					REFRESH();
					delay(DELAY);
					
					if(kbhit())
					{
						char key= getch();
						
						switch(key){case 72:DIR=1;break;	case 80:DIR=3;break;	case 75:DIR=4;break;	case 77:DIR=2;break;}
						if(DIR!=3)break;
					}
		
				}while(R<49);
				
				if(DIR==3)GMEOVR();
				
				break;
		
			case 4://LT
				do
				{
					IDX--; R = IDX / 50; C = IDX % 50;
					REFRESH();
					delay(DELAY);
					
					if(kbhit())
					{
						char key= getch();
						
						switch(key){case 72:DIR=1;break;	case 80:DIR=3;break;	case 75:DIR=4;break;	case 77:DIR=2;break;}
						if(DIR!=4)break;
					}
					
				}while(C>0);
				
				if(DIR==4)GMEOVR();
				
				break;		
				
		} 		
	
	}	

}

void REFRESH()
{
	cleardevice();
	DRWboard();
	DRWnBOX();
	BODY();
	FOOD();
}

void DRWboard()
{
	setcolor(WHITE);
	setfillstyle(SOLID_FILL,RED);
	rectangle(OX,OY,EX,EY);
	
	
	for(int b=OY;b<EY;b+=pBOX) 
	{
    
   		for(int a=OX;a<EX;a+=pBOX)
   		{
   			setcolor(RED);
			//rectangle(a,b,a+pBOX,b+pBOX);
			setfillstyle(SOLID_FILL,RED);
   			//floodfill(a+1,b+1,WHITE);
			//getch();
		}	
   
	}
	
	
}

void DRWnBOX()
{
	int x= (IDX%50)*10 +OX;
	int y= (IDX/50)*10 +OY;	
	
	setcolor(RED);
	rectangle(x,y,x+pBOX,y+pBOX);
	setfillstyle(SOLID_FILL,RED);
	floodfill(x+5,y+5,RED);
	
}

void GMEOVR()
{
    while(1)
    {
	
		for(int i=1;i<=7;i++)
		{
			delay(400);
			setcolor(i);
			settextstyle(2, 0, 10);
    		outtextxy(55,250,"F , U   DED   !#&*NOOB");
    		
    		settextstyle(2, 0, 8);

   			char buffer [30];
			sprintf(buffer,"U only ate %d fud",no);
    		outtextxy(160,300,buffer);

    		    		
			if(kbhit())
			{
				fSTART=1;
				char key= getch();	
				return;
			}
		}
	}
	
}

void FOOD()
{	

	
	int fudx,fudy;
	
		fudx= (fud%50)*10 +OX;
		fudy= (fud/50)*10 +OY;
		setcolor(GREEN);
		rectangle(fudx,fudy,fudx+pBOX,fudy+pBOX);
		setfillstyle(SOLID_FILL,GREEN);
		floodfill(fudx+5,fudy+5,GREEN);
		
	if(IDX==fud)
	{
		fud = rand() % (2500-0) + 0;
		fudx= (fud%50)*10 +OX;
		fudy= (fud/50)*10 +OY;
		
		setcolor(GREEN);
		rectangle(fudx,fudy,fudx+pBOX,fudy+pBOX);
		setfillstyle(SOLID_FILL,GREEN);
		//floodfill(fudx+5,fudy+5,GREEN);
	}
			
}

void BODY()
{
	// slide body----------------------------------------
	for(int i=no;i>=0;i--)
	{
		bdy[i+1] = bdy[i]; 
	}
	bdy[0]=IDX;//head index---------------------------------
	
	//increment body----------------------------------------
	if(IDX==fud)no++;	
	
	//print bdy-----------------------------------------------
	for(int i=1;i<=no;i++)
	{
		int x= (bdy[i]%50)*10 +OX;
		int y= (bdy[i]/50)*10 +OY;	
	
		setcolor(RED);
		rectangle(x,y,x+pBOX,y+pBOX);
		setfillstyle(SLASH_FILL,RED);
		floodfill(x+5,y+5,RED);
		
	}	
	
	
	//collision detection------------------------------------------
	
	for(int i=1;i<=no;i++)
	{
		if(bdy[i]==IDX)
		{
			GMEOVR();
		}
	}
	
	
}

void START()
{
    while(1)
    {
		for(int i=1;i<=7;i++)
		{
			delay(400);
			setcolor(i);
			settextstyle(2, 0, 10);
    		outtextxy(225,250,"SNAEK");
    		
    		settextstyle(2, 0, 8);
			outtextxy(125,300,"smash keyboad to start");
	
			if(kbhit())
			{
				char key= getch();
				return;
			}
		}
		
	}
	
}


