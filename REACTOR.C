#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<stdio.h>
#include<stdlib.h>

int score1=0,score2=0;
int gd=DETECT,gm;

void printscreen(int isproneed)
{
	char sc1[10],sc2[10];
	itoa(score1,sc1,10);
	itoa(score2,sc2,10);
	//total area
	cleardevice();
	rectangle(10,10,600,450);
	//play area
	rectangle(20,40,590,420);
	outtextxy(15,15,"PLAYER 1 : ");
	outtextxy(100,15,sc1);
	outtextxy(100,440,sc2);
	outtextxy(15,440,"PLAYER 2 : ");
	if(isproneed==1)
	{
		rectangle(40,60,570,90);
	}
}

void printscreen1()
{
	char sc1[10],sc2[10];
	itoa(score1,sc1,10);
	itoa(score2,sc2,10);
	cleardevice();
	outtextxy(15,15,"PLAYER 1 : ");
	outtextxy(100,15,sc1);
	outtextxy(100,440,sc2);
	outtextxy(15,440,"PLAYER 2 : ");
}

void getResult(int a)
{
	cleardevice();
	if(a==1)
	{
		score1++;
	}
	else
	{
		score2++;
	}
	printscreen(0);
	if(a==1)
	{
		outtextxy(260,230,"PLAYER 1 SCORES!");
	}
	else
	{
		outtextxy(260,230,"PLAYER 2 SCORES!");
	}
	delay(1000);
	outtextxy(240,260,"PRESS SPACE TO CONTINUE");
	while(getch()!=32){}
}

void getEarly(int a)
{
	cleardevice();
	if(a==1)
	{
		score1--;
	}
	else
	{
		score2--;
	}
	printscreen(0);
	if(a==1)
	{
		outtextxy(240,230,"PLAYER 1 HIT TOO EARLY!");
	}
	else
	{
		outtextxy(240,230,"PLAYER 2 HIT TOO EARLY!");
	}
	delay(1000);
	outtextxy(240,260,"PRESS SPACE TO CONTINUE");
	while(getch()!=32){}
}

int getRandom(int upper)
{
	int r = rand();
	return r%upper+1;
}

//REACTION TIME
void initreact()
{
	printscreen(0);
	outtextxy(260,230,"ROUND 1");
	delay(1000);
}

void initcolorwords()
{
	printscreen(0);
	outtextxy(260,230,"ROUND 2");
	delay(1000);
}

void initcollide()
{
	printscreen(0);
	outtextxy(260,230,"ROUND 3");
	delay(1000);
	printscreen(0);
	outtextxy(260,230,"FINAL ROUND!");
	delay(1000);
	printscreen(0);
	outtextxy(260,230,"READY!");
	delay(1000);
	printscreen(0);
	outtextxy(260,230,"SET!");
	delay(1000);
	printscreen(0);
	outtextxy(260,230,"GO!");
	delay(500);
	printscreen1();
}

void getWrong(int a)
{
	cleardevice();
	if(a==1)
	{
		score1--;
	}
	else
	{
		score2--;
	}
	printscreen(0);
	if(a==1)
	{
		outtextxy(240,230,"PLAYER 1 GOT IT WRONG!");
	}
	else
	{
		outtextxy(240,230,"PLAYER 2 GOT IT WRONG!");
	}
	delay(1000);
	outtextxy(240,260,"PRESS SPACE TO CONTINUE");
	while(getch()!=32){}
}

void printwords()
{
	int j;
	for(j=0; j<3; j++)
	{
		int word,color,i;
		cleardevice();
		printscreen(0);
		outtextxy(210,230,"HIT WHEN COLOR MATCHES WORD!");
		delay(1000);
		cleardevice();
		printscreen(1);
		word = getRandom(4);
		color = getRandom(4);
		//rgby
		switch(color)
		{
			case 1:setcolor(RED);break;
			case 2:setcolor(GREEN);break;
			case 3:setcolor(BLUE);break;
			case 4:setcolor(YELLOW);break;
		}

		switch(word)
		{
			case 1:outtextxy(260,230,"RED");break;
			case 2:outtextxy(260,230,"GREEN");break;
			case 3:outtextxy(260,230,"BLUE");break;
			case 4:outtextxy(260,230,"YELLOW");break;
		}
		setcolor(WHITE);
		for(i=40;i<570;i++)
		{
			delay(5);
			line(i,60,i,90);
			if(kbhit())
			{
				if(word==color)
				{
					switch(getch())
					{
						case 'a':getResult(1);break;
						case 'l': getResult(2);break;
					}
				}
				else
				{
					switch(getch())
					{
						case 'a':getWrong(1);break;
						case 'l':getWrong(2);break;
					}
				}
				break;
			}
		}
	}
}

void print_green()
{
	int j;
	for(j=0; j<3; j++)
	{
	int flash = getRandom(500)+40,i,points[]={20,40,590,40,590,420,20,420,20,40};

	cleardevice();
	printscreen(0);
	outtextxy(230,230,"HIT WHEN GREEN!");
	delay(1000);
	cleardevice();
	printscreen(0);

	for(i=0;i<570;i++)
	{
		delay(10);
		if(i==flash)
		{
			setfillstyle(SOLID_FILL,GREEN);
			fillpoly(5,points);
			switch(getch())
			{
				case 'a': getResult(1);break;
				case 'l': getResult(2);break;

			}
			break;
		}
		if(kbhit())
		{
			switch(getch())
			{
				case 'a': getEarly(1);break;
				case 'l': getEarly(2);break;
			}
			break;
		}
	}
	}
}

void printcollide()
{
	int j,r1,r2,y1,y2,c1,c2,i,d;
	long ysub;
	for(j=0; j<3; j++)
	{
		cleardevice();
		printscreen1();
		delay(1000);

		r1 = getRandom(50)+25;
		r2 = getRandom(50)+25;
		y1 = getRandom(180)+140;
		y2 = getRandom(180)+140;
		c1 = getRandom(14);
		c2 = getRandom(14);
		d = getRandom(6)-1;
		ysub = (long)(((r1+r2)*(r1+r2))-((y2-y1)*(y2-y1)));
		for(i=0; i<=570; i++)
		{
			setcolor(BLACK);
			setfillstyle(SOLID_FILL,c1);
			fillellipse(20+i,y1,r1,r1);
			setfillstyle(SOLID_FILL,c2);
			fillellipse(590-i,y2,r2,r2);

			if(kbhit())
			{
				delay(500);
				setcolor(WHITE);
				if( ((long)(570-i-i)*(570-i-i)) < ysub )
				{
					switch(getch())
					{
						case 'a':getResult(1);break;
						case 'l':getResult(2);break;
					}
				}
				else
				{
					switch(getch())
					{
						case 'a':getEarly(1);break;
						case 'l':getEarly(2);break;
					}
				}
				break;
			}

			delay(d);
		}

	}
	setcolor(WHITE);
}

void printWinner()
{
	cleardevice();
	printscreen(0);
	if(score1>score2)
	{
		outtextxy(260,230,"PLAYER 1 WINS!");
	}
	else if(score2>score1)
	{
		outtextxy(260,230,"PLAYER 2 WINS!");
	}
	else
	{
		outtextxy(260,230,"DRAW");
	}
	outtextxy(240,260,"PRESS ANY KEY TO CONTINUE");
}

void main()
{
	clrscr();
	initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
	srand(time(NULL));
	initreact();
	print_green();
	initcolorwords();
	printwords();
	initcollide();
	printcollide();
	printWinner();
	getch();
	closegraph();
}


