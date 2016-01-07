#include<iostream.h>
#include<dos.h>
#include<fstream.h>
#include<bios.h>
#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#define BKEY 0x5000
#define CKEY 11875
#define DKEY 8292
#define EKEY 4709
#define GKEY 8807
#define IKEY 5993
#define LKEY 0x4b00
#define N 12654
#define PKEY 6512
#define RKEY 0x4d00
#define TKEY 0x4800
#define Y 5497
#define ESC  0x11b
#define ENTER 0x1c0d
int Linestyle;//variable in which the line style is stored
int Thickness;//variable in which the line thickness is stored
int DorDAF;//variable in which the info regarding Draw or Draw And Fill is stored
int oort1;//variable in which the size of rectangular brush is stored
int oort2;//variable in which the size of circular brush is stored
int color;//variable in which the color selected is stored
union REGS in,out;
int callmouse()
{
	in.x.ax=1;
	int86(51,&in,&out);
	return 1;
}
void mouseposi(int &xpos,int &ypos,int& click)
{
	in.x.ax=3;
	int86(51,&in,&out);
	click=out.x.bx;
	xpos=out.x.cx;
	ypos=out.x.dx;
}
int mousehide()
{
	in.x.ax=2;
	int86(51,&in,&out);
	return 1;
}
void setposi(int &xpos,int &ypos)
{
	in.x.ax=4;
	in.x.cx=xpos;
	in.x.dx=ypos;
	int86(51,&in,&out);
}
void restrictmouseptr(int x1,int y1,int x2,int y2)
{
	in.x.ax=7;
	in.x.cx=x1;
	in.x.dx=x2;
	int86(51,&in,&out);
	in.x.ax=8;
	in.x.cx=y1;
	in.x.dx=y2;
	int86(51,&in,&out);
}
void initiation()
{
	int gdriver=DETECT,gmode,errorcode;
	errorcode = graphresult();
	initgraph(&gdriver, &gmode, "");
	errorcode = graphresult();
	if (errorcode != grOk)
	{
		 printf("Graphics error: %s\n", grapherrormsg(errorcode));
		 printf("Press any key to halt:");
		 getch();
		 exit(1);
	}
}
void Loading()//Function to display the LOADING bar
{
	cleardevice();
	setbkcolor(15);
	setcolor(8);
	rectangle(260,200,360,210);
	settextstyle(2,0,6);
	outtextxy(270,230,"Loading...");
	for(int var1=0;var1<=100;var1++)
	{
		setcolor(8);
		line(260+var1,200,260+var1,210);
		delay(35);
	}
	delay(1000);

}
void Saving()//Function to display the SAVING bar
{
	cleardevice();
	setbkcolor(15);
	setcolor(8);
	rectangle(260,200,360,210);
	settextstyle(2,0,6);
	outtextxy(270,230,"Saving...");
	for(int var1=0;var1<=100;var1++)
	{
		setcolor(8);
		line(260+var1,200,260+var1,210);
		delay(35);
	}
	delay(1000);
}

class GAME
{

	private:

	int size,size2;
	int x,y;
	int cl,clfake;
	int a,b,xx,yy;
	int temp;
	int i1,j1;
	int stop,stop1,stop2,stop3;
	int kk1,jj1;
	int X,points;
	int j;
	int k2,k5;
	int mml,mmt,mmr,mmb;
	void *ship,*bomb,*aimer,*blast1,*blast2,*blast3,*black,*laser1,*laser2,*laser3,*laser4,*black2;
	char c3;

	public:

	void values();//Function that initialises all the required values before the start of the main game
	void mainmenu();//Function that displays the main menu
	void draw_n_get();//Function that draws various images and stores it in respective variables
	void start();//Function that takes care of all the work that is to be done when the game is on
	void musiq(int);//Function for background music
	void music();//Function for background music

};

class DRAWING_UTILITY
{

	private:

	int x,y;//variables in which the maximum value of x and y are stored
	int a,b;//Dimensions of the selection rectangle of the tools menu
	int k,k1,k2,k3,k4,k5,k6,k7,k8,k9,k10,k11,k12;//variables used to store the key which is pressed
	int mml,mmt,mmb,mmr;//The coordinates of the selection rectangle of the main menu
	int tml,tmt,tmr,tmb;//The coordinates of the selection rectangle of the tools menu
	int eml,emt,emr,emb;//The coordinates of the selection rectangle of the escape menu
	int cml,cmt,cmr,cmb;//The coordinates of the selection rectangle of the colours menu
	int boml,bomt,bomr,bomb;//The coordinates of the selection rectangle of the brush-options menu
	int roml,romt,romr,romb;//The coordinates of the selection rectangle of the rectangle-options menu
	int lsoml,lsomt,lsomr,lsomb;//The coordinates of the selection rectangle of the lineStyle-options menu
	int ltoml,ltomt,ltomr,ltomb;//The coordinates of the selection rectangle of the lineThickness-options menu

	public:

	void values();//Function that initialises all the required values before the start of the main game
	void mainmenu();//Function that displays the main menu
	void key();//Function that takes care of the keyboard actions
	//void mouse();//Function that takes care of the mouse actions
	void newimagescreen();//Function that displays corresponding screen if a new image is to be drawn
	void escapemenu();//Function that displays the menu if the ESC key is pressed
	void Rectangle(int color,int dordf);//Function that takes care of all the work that is to be done if the rectangle tool is selected
	void B1(int,int);//Function that takes care of all the work that is to be done if the circular brush tool is selected
	void B2(int,int);//Function that takes care of all the work that is to be done if the rectangular brush tool is selected
	void Line(int,int,int);//Function that takes care of all the work that is to be done if the line tool is selected
	void save();//Function that is used to save an image to a file, with the filename given by the user
	int check();//Function used to check if any image has previously been stored in the memory

};

void GAME::musiq(int type)
{
	float octave[7]={130.81,146.83,164.81,174.61,196,220,246.94};
	int n,i;
	switch(type)
	{
		case 1:
			while(!kbhit())
			{
				n=random(7);
				sound(octave[n]*4);
				delay(100);
			}
			nosound();
			if(getch()==0)
				getch();
			break;

		case 2:
			for(i=6;i>=0;--i)
			{
				sound(octave[i]);
				delay(54);
			}
			nosound();
			break;

		case 3:
			sound(octave[6]*2);
			delay(50);
			nosound();
			break;

	}
}
void GAME::music()
{
	int i,j;
	while(!kbhit())
	{
	for(j=0;j<3;++j)
	{
		for(i=0;i<10;++i)
		{
			sound(150+i*10);
			delay(100);
		}
		nosound();
	}
	delay(100);
	}
}
void GAME::values()
{
	size2=imagesize(95,95,185,185);
	ship=malloc(size2);
	bomb=malloc(imagesize(0,0,30,30));
	xx=1;
	yy=1;
	size=imagesize(95,95,185,185);
	aimer=malloc(size);
	black=malloc(size);
	black2=malloc(size);
	laser1=malloc(size);
	laser2=malloc(size);
	laser3=malloc(size);
	laser4=malloc(size);
	blast1=malloc(size);
	blast2=malloc(size);
	blast3=malloc(size);
	temp=0;
	i1=0;
	j1=0;
	stop=0;
	stop2=0;
	stop3=0;
	stop1=0;
	points=0;
	kk1=0;
	jj1=0;
	j=0;
	a=320;
	b=250;
	mml=319-130;
	mmt=150;
	mmr=319+95;
	mmb=200;
	k2=0;
	k5=0;
}
void GAME::draw_n_get()
{

	//To store images

	//to store the existing replacable area

	setbkcolor(0);
	getimage(x,y,x+90,y+90,black);
	getimage(95,95,185,185,black2);

	//ship

	cleardevice();
	setcolor(8);
	arc(150,150,37,140,30);
	line(126,130,115,140);
	line(174,130,185,140);
	line(185,140,115,140);
	rectangle(140,140,160,145);
	line(126,130,174,130);
	line(140,120,130,100);
	line(130,100,135,122);
	line(160,120,170,100);
	line(170,100,165,122);
	setcolor(15);
	circle(150,128,1);
	putpixel(150,128,4);
	circle(145,128,1);
	putpixel(145,128,4);
	circle(155,128,1);
	putpixel(155,128,4);
	circle(160,128,1);
	putpixel(160,128,4);
	circle(140,128,1);
	putpixel(140,128,4);
	circle(135,128,1);
	putpixel(135,128,4);
	circle(165,128,1);
	putpixel(165,128,4);

	getimage(95,95,185,155,ship);

	//bomb

	cleardevice();
	setcolor(DARKGRAY);
	circle(200,200,5);
	setfillstyle(1,8);
	floodfill(200,200,DARKGRAY);
	line(202,194,202,194);
	line(203,195,203,195);
	line(200,200,207,193);
	setcolor(4);
	circle(207,193,2);
	putpixel(207,193,14);
	setcolor(LIGHTGRAY);
	circle(198,198,2);
	setfillstyle(1,7);
	floodfill(198,198,LIGHTGRAY);

	getimage(195,191,210,206,bomb);



	//aimer

	cleardevice();
	setcolor(1);
	circle(140,140,15);
	circle(140,140,30);
	line(140,95,140,185);
	line(95,140,185,140);
	getimage(95,95,185,185,aimer);

	//laser frame 1

	cleardevice();
	setcolor(LIGHTRED);
	line(135,140,115,155);
	line(145,140,165,155);
	line(135,140,145,140);
	arc(140,140,213,-32,30);
	setfillstyle(1,LIGHTRED);
	floodfill(135,145,LIGHTRED);
	setcolor(RED);
	for(int i,j=0;j<60;++j)
	{
		i=random(6);
		line(135+i,140,115+i*2,155);
		line(145-i,140,165-i*2,155);
	}
	getimage(95,95,185,185,laser1);

	//laser frame 2

	cleardevice();
	setcolor(LIGHTRED);
	line(140,140,125,150);
	line(140,140,155,150);
	line(125,150,155,150);
	setfillstyle(1,LIGHTRED);
	floodfill(135,145,LIGHTRED);
	setcolor(RED);
	for(i,j=0;j<60;++j)
	{
		i=random(10);
		line(140,140,125+i,150);
		line(140,140,155-i,150);
	}
	getimage(95,95,185,185,laser2);

	//laser frame 3

	cleardevice();
	putimage(95,95,aimer,XOR_PUT);
	setcolor(LIGHTRED);
	line(140,140,130,145);
	line(140,140,150,145);
	line(130,145,150,145);
	setfillstyle(1,LIGHTRED);
	floodfill(140,143,LIGHTRED);
	setcolor(RED);
	for(i,j=0;j<60;++j)
	{
		 i=random(10);
		 line(140,140,130+i,145);
		 line(140,140,150-i,145);
	}
	getimage(95,95,185,185,laser3);

	//laser frame 4

	cleardevice();
	setcolor(LIGHTRED);
	circle(140,140,1);
	floodfill(140,140,LIGHTRED);
	getimage(95,95,185,185,laser4);

}
void GAME::start()
{
	//displays the city background
	fstream f2;
	cleardevice();
	f2.open("CITY1",ios::in);
	f2>>c3;
	while(!f2.eof())
	{
		if(c3=='*')
		{
			kk1=0;jj1=jj1+1;gotoxy(kk1,jj1);
		}
		else if(c3=='a')
		{
			putpixel(kk1,jj1,0);kk1++;
		}
		else if(c3=='b')
		{
			putpixel(kk1,jj1,1);kk1++;
		}
		else if(c3=='c')
		{
			putpixel(kk1,jj1,2);kk1++;
		}
		else if(c3=='d')
		{
			putpixel(kk1,jj1,3);kk1++;
		}
		else if(c3=='e')
		{
			putpixel(kk1,jj1,4);kk1++;
		}
		else if(c3=='f')
		{
			putpixel(kk1,jj1,5);kk1++;
		}
		else if(c3=='g')
		{
			putpixel(kk1,jj1,6);kk1++;
		}
		else if(c3=='h')
		{
			putpixel(kk1,jj1,7);kk1++;
		}
		else if(c3=='i')
		{
			putpixel(kk1,jj1,8);kk1++;
		}
		else if(c3=='j')
		{
			putpixel(kk1,jj1,9);kk1++;
		}
		else if(c3=='k')
		{
			putpixel(kk1,jj1,10);kk1++;
		}
		else if(c3=='l')
		{
			putpixel(kk1,jj1,11);kk1++;
		}
		else if(c3=='m')
		{
			putpixel(kk1,jj1,12);kk1++;
		}
		else if(c3=='n')
		{
			putpixel(kk1,jj1,13);kk1++;
		}
		else if(c3=='o')
		{
			putpixel(kk1,jj1,14);kk1++;
		}
		else if(c3=='p')
		{
			putpixel(kk1,jj1,15);kk1++;
		}
		f2>>c3;
	}

	 //To move the aimer

	 randomize();
	 setposi(a,b);
	 do
	 {
		 do
		 {
			 stop1=100+random(400);
			 stop2=100+random(400);
			 stop3=100+random(400);
		 }while(stop1==stop2||stop1==stop3||stop2==stop3);
		 if(stop1>stop2)
		 {
			 temp=stop1;
			 stop1=stop2;
			 stop2=temp;
		 }
		 if(stop1>stop3)
		 {
			 temp=stop1;
			 stop1=stop3;
			 stop3=temp;
		 }
		 if(stop2>stop3)
		 {
			 temp=stop2;
			 stop2=stop3;
			 stop3=temp;
		 }
		 putimage(xx,yy,aimer,XOR_PUT);
		 do
		 {
			 mouseposi(x,y,cl);
			 delay(20);
			 if(i1==stop1)
			 {
				 if(stop!=stop1)
				 j1=0;
				 stop=stop1;
			 }
			 if(i1==stop2)
			 {
				 if(stop!=stop2)
				 j1=0;
				 stop=stop2;
			 }
			 if(i1==stop3)
			 {
				 if(stop!=stop3)
				 j1=0;
				 stop=stop3;
			 }
			 mouseposi(x,y,cl);
			 if((!(xx==x)||!(yy==y)))
			 {
				 putimage(xx,yy,aimer,XOR_PUT);
			 }
			 if((cl==0||clfake==1)&&(!(xx==x)||!(yy==y)))
			 {
				 putimage(x,y,aimer,XOR_PUT);
			 }
			 if(cl==1&&clfake!=1)
			 {
				 if(i1!=stop&&i1<=670)
				 {
					 putimage(xx,yy,black,0);
					 putimage(x,y,laser1,XOR_PUT);
					 delay(100/2);
					 putimage(i1-2,5,ship,XOR_PUT);
					 putimage(i1,5,ship,1);
					 i1=i1+2;
					 putimage(xx,yy,black,0);
					 putimage(x,y,laser2,XOR_PUT);
					 delay(100/2);
					 putimage(i1-2,5,ship,1);
					 putimage(i1,5,ship,1);
					 i1=i1+2;
					 putimage(xx,yy,black,0);
					 putimage(x,y,laser3,XOR_PUT);
					 delay(100/2);
					 putimage(i1-2,5,ship,1);
					 putimage(i1,5,ship,1);
					 i1=i1+2;
					 putimage(xx,yy,black,0);
					 putimage(x,y,laser4,XOR_PUT);
					 delay(100/2);
					 putimage(i1-2,5,ship,1);
					 putimage(i1,5,ship,1);
					 i1=i1+2;
					 putimage(xx,yy,black,0);
					 putimage(x,y,aimer,XOR_PUT);
				 }
				 else
				 {
					 putimage(xx,yy,black,COPY_PUT);
					 putimage(x,y,laser1,XOR_PUT);
					 delay(100/2);
					 if(i1==stop||X==1)
					 {
						 if(j1==0)
						 {
							 putimage(i1+53,55-4,bomb,1);
							 X=1;
						 }
						 putimage(i1+53,55+j1-4,bomb,1);
						 putimage(i1+53,55+j1,bomb,1);
						 j1++;j1++;j1++;j1++;
						 if(j1==300)
						 {
							 putimage(i1-2,5,ship,1);
							 i1++;
							 j++;
							 putimage(i1-2,5,ship,1);
							 putimage(i1+52,55+j1-4,bomb,1);
							 X=0;j1=0;
							 if(j!=points)
							 {
								 musiq(2);
								 goto stop;
							 }
							 else
							 {
								 musiq(3);
							 }
						 }
					 }
					 if(i1==stop||X==1)
					 {
					 if(j1==0)
					 {
						 putimage(i1+53,55-4,bomb,1);
						 X=1;
					 }
					 putimage(i1+53,55+j1-4,bomb,1);
					 putimage(i1+53,55+j1,bomb,1);
					 j1++;j1++;j1++;j1++;
					 if(j1==300)
					 {
						 putimage(i1-2,5,ship,1);
						 i1++;
						 j++;
						 putimage(i1-2,5,ship,1);
						 putimage(i1+52,55+j1-4,bomb,1);
						 X=0;j1=0;
						 if(j!=points)
						 {
							 musiq(2);
							 goto stop;
						 }
						 else
						 {
							 musiq(3);
						 }
					 }
				 }
				 putimage(xx,yy,black,COPY_PUT);
				 putimage(x,y,laser2,XOR_PUT);
				 delay(100/2);
				 if(i1==stop||X==1)
				 {
					 if(j1==0)
					 {
						 putimage(i1+53,55-4,bomb,1);
						 X=1;
					 }
					 putimage(i1+53,55+j1-4,bomb,1);
					 putimage(i1+53,55+j1,bomb,1);
					 j1++;j1++;j1++;j1++;
					 if(j1==300)
					 {
						 putimage(i1-2,5,ship,1);
						 i1++;
						 j++;
						 putimage(i1-2,5,ship,1);
						 putimage(i1+52,55+j1-4,bomb,1);
						 X=0;j1=0;
						 if(j!=points)
						 {
							 musiq(2);
							 goto stop;
						 }
						 else
						 {
							 musiq(3);
						 }
					 }
				 }
				 if(i1==stop||X==1)
				 {
					 if(j1==0)
					 {
						 putimage(i1+53,55-4,bomb,1);
						 X=1;
					 }
					 putimage(i1+53,55+j1-4,bomb,1);
					 putimage(i1+53,55+j1,bomb,1);
					 j1++;j1++;j1++;j1++;
					 if(j1==300)
					 {
						 putimage(i1-2,5,ship,1);
						 i1++;
						 j++;
						 putimage(i1-2,5,ship,1);
						 putimage(i1+52,55+j1-4,bomb,1);
						 X=0;j1=0;
						 if(j!=points)
						 {
							 musiq(2);
							 goto stop;
						 }
						 else
						 {
							 musiq(3);
						 }
					 }
				 }
				 putimage(xx,yy,black,COPY_PUT);
				 putimage(x,y,laser3,XOR_PUT);
				 delay(100/2);
				 if(i1==stop||X==1)
				 {
					 if(j1==0)
					 {
						 putimage(i1+53,55-4,bomb,1);
						 X=1;
					 }
					 putimage(i1+53,55+j1-4,bomb,1);
					 putimage(i1+53,55+j1,bomb,1);
					 j1++;j1++;j1++;j1++;
					 if(j1==300)
					 {
						 putimage(i1-2,5,ship,1);
						 i1++;
						 j++;
						 putimage(i1-2,5,ship,1);
						 putimage(i1+52,55+j1-4,bomb,1);
						 X=0;j1=0;
						 if(j!=points)
						 {
							 musiq(2);
							 goto stop;
						 }
						 else
						 {
							 musiq(3);
						 }
					 }
				 }
				 putimage(xx,yy,black,COPY_PUT);
				 putimage(x,y,laser4,XOR_PUT);
				 delay(100/2);
				 if(i1==stop||X==1)
				 {
					 if(j1==0)
					 {
						 putimage(i1+53,55-4,bomb,1);
						 X=1;
					 }
					 putimage(i1+53,55+j1-4,bomb,1);
					 putimage(i1+53,55+j1,bomb,1);
					 j1++;j1++;j1++;j1++;
					 if(j1==300)
					 {
						 putimage(i1-2,5,ship,1);
						 i1++;
						 j++;
						 putimage(i1-2,5,ship,1);
						 putimage(i1+52,55+j1-4,bomb,1);
						 X=0;j1=0;
						 if(j!=points)
						 {
							 musiq(2);
							 goto stop;
						 }
						 else
						 {
							 musiq(3);
						 }
					 }
				 }
				 if(i1==stop)
				 {
					 putimage(i1+53,55+j1-4,bomb,1);
					 putimage(i1+53,55+j1,bomb,1);
					 j1++;j1++;j1++;j1++;
					 if(j1==300)
					 {
						 putimage(i1-2,5,ship,1);
						 i1++;
						 j++;
						 putimage(i1-2,5,ship,1);
						 putimage(i1+52,55+j1-4,bomb,1);
						 if(j!=points)
						 {
							 musiq(2);
							 goto stop;
						 }
						 else
						 {
							 musiq(3);
						 }
					 }
				 }
				 putimage(xx,yy,black,COPY_PUT);
				 putimage(xx,yy,aimer,XOR_PUT);
				 if(x>=i1-45&&x<=i1+45&&y>=j1-45&&y<=j1+45)
				 {
					 putimage(i1+53,55+j1-4,bomb,1);
					 putimage(i1+53,55+j1-4,bomb,1);
					 j1=300;
					 points++;
					 putimage(i1+53,51+j1,bomb,1);
				 }
			 }
		 }
		 xx=x;
		 yy=y;
		 clfake=cl;
		 putimage(xx,yy,aimer,XOR_PUT);
		 putimage(x,y,aimer,XOR_PUT);
		 if(i1<670&&i1!=stop)
		 {
			 if(!i1)
			 putimage(i1,5,ship,1);
			 delay(20);
			 if(i1)
			 {
				 putimage(i1-2,5,ship,1);
				 putimage(i1,5,ship,1);
			 }
			 i1=i1+2;
		 }
		 if(i1==stop||X==1)
		 {
			 if(j1==0)
			 {
				 putimage(i1+53,55-4,bomb,1);
				 X=1;
			 }
			 if(j1!=300)
			 {
				 putimage(i1+53,55+j1-4,bomb,1);
				 putimage(i1+53,55+j1,bomb,1);
				 j1++;j1++;j1++;j1++;
			 }
			 if(j1==300)
			 {
				 putimage(i1-2,5,ship,1);
				 i1++;
				 j++;
				 putimage(i1-2,5,ship,1);
				 putimage(i1+52,55+j1-4,bomb,1);
				 X=0;j1=0;
				 if(j!=points)
				 {
					 musiq(2);
					 goto stop;
				 }
				 else
				 {
					 musiq(3);
				 }
			 }
		 }
		 restrictmouseptr(0,70,515,255);
	 }while(i1<getmaxx()-50);
	 putimage(x,y,aimer,XOR_PUT);
	 i1=0;
	 j1=0;
	}while(j==points && points<=3);
	stop:
	mousehide();
	//to display the corresponding screen if the city is destroyed
	if(j!=points)
	{
		delay(500);
		cleardevice();
		setbkcolor(15);
		settextstyle(4,0,1);
		setcolor(4);
		for(int jz=0;jz<3;++jz)
		{
			for(int i=0;i<10;++i)
			{
				sound(150+i*10);
				delay(100);
				outtextxy(240,getmaxy()/2-10,"GAME OVER");
			}
			nosound();
			delay(100);
		}
	}
	//to display the corresponding screen if the player has successfully shooted more than 3 bombs
	else
	{
		delay(500);
		float octave[7]={130.81,146.83,164.81,174.61,196,220,246.94};
		int n,i;
		cleardevice();
		setbkcolor(15);
		settextstyle(3,0,2);
		setcolor(2);
		while(!kbhit())
		{
			n=random(7);
			sound(octave[n]*4);
			outtextxy(240,getmaxy()/2-10,"WELL DONE");
			delay(100);
		}
		nosound();
		getch();
		clrscr();
		cleardevice();
		cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
		cout<<"                                          "<<points;
		setcolor(1);
		outtextxy(200,getmaxy()/2-10,"Your Score Is : ");
		getch();
	}
}
void GAME::mainmenu()
{
	values();
	cleardevice();
	setbkcolor(15);
	setcolor(1);
	settextstyle(10,0,2);
	outtextxy(319-90,150,"New Game");
	setcolor(2);
	outtextxy(319-55,200,"Exit");
	if(mmt==150)
	{
		setcolor(1);
		rectangle(mml,mmt,mmr,mmb);
	}
	else
	if(mmt==200)
	{
		setcolor(2);
		rectangle(mml,mmt,mmr,mmb);
	}
	while(bioskey(1)==0)
	{
		k2=bioskey(0);
		if(k2==TKEY)//if the top arrow key is pressed
		{
			if(mmt-50>=150)
			{
				setcolor(15);
				rectangle(mml,mmt,mmr,mmb);
				mmt=mmt-50;
				mmb=mmb-50;
				setcolor(1);
				rectangle(mml,mmt,mmr,mmb);
			}
		}
		else
		if(k2==BKEY)//if the bottom arrow key is pressed
		{
			if(mmb+50<=250)
			{
				setcolor(15);
				rectangle(mml,mmt,mmr,mmb);
				mmt=mmt+50;
				mmb=mmb+50;
				setcolor(2);
				rectangle(mml,mmt,mmr,mmb);
			}
		}
		else
		if(k2==ENTER)//if ENTER key is pressed
		{
			if(mmt==150)//if NEW GAME is selected
			{
				cleardevice();
				draw_n_get();
				start();
				getch();
				exit(1);
			}
			else
			if(mmt==200)//if EXIT is selected
			{
				cleardevice();
				setcolor(8);
				settextstyle(3,0,4);
				outtextxy(100,100,"Do You Really Want To Quit?");
				setcolor(2);
				outtextxy(200,200,"[Y]es");
				setcolor(4);
				outtextxy(400,200,"[N]o");
				while(bioskey(1)==0)
				{
					k5=bioskey(0);
					if(k5==Y)
					{
						cleardevice();
						setcolor(8);
						settextstyle(3,0,4);
						outtextxy(230,200,"Good Bye...");
						getch();

						exit(1);
					}
					else
					if(k5==N)
					{
						mainmenu();
					}
				}
			}
		}
	}
}

void DRAWING_UTILITY::values()
{
	x=getmaxx();
	y=getmaxy();

	a=((y-55)/2-2)/5;
	b=(8*25)/4;

	k=0;
	k1=0;
	k2=0;
	k3=0;
	k4=0;
	k5=0;
	k6=0;
	k7=0;
	k8=0;
	k9=0;
	k10=0;
	k11=0;
	k12=0;

	tml=0;
	tmt=0;
	tmr=b;
	tmb=a;

	cml=0;
	cmt=y-50;
	cmr=25;
	cmb=y-25;

	boml=100+5-80-5+40;
	bomt=y/2+25-120-20;
	bomr=120+15-80-5+40;
	bomb=y/2+35+25-120-20;

	roml=20;
	romt=(y/2)+75-50-120;
	romr=8*25-20+3;
	romb=(y/2)+115-50-120;

	lsoml=20;
	lsomt=320-60-120-10;
	lsomr=8*25-20;
	lsomb=320-60-120+10;

	ltoml=20;
	ltomt=320-60-120-10+110;
	ltomr=8*25-20;
	ltomb=320-60-120+10+110;

	eml=x/2-170;
	emt=85;
	emr=x/2+170-25;
	emb=135;

	mml=x/2-130;
	mmt=150;
	mmr=x/2+95;
	mmb=200;

	color=15;
	oort1=1;
	oort2=1;

}
int DRAWING_UTILITY::check()
{
	fstream f;
	f.open("imagenames",ios::in);
	char ch;
	f>>ch;
	if(f.eof())
	{
		f.close();
		return 0;
	}
	else
	{
		f.close();
		return 1;
	}
}
void DRAWING_UTILITY::mainmenu()
{
	values();
	cleardevice();
	setbkcolor(15);
	setcolor(1);
	settextstyle(10,0,2);
	outtextxy(x/2-100,150,"New Image");
	setcolor(2);
	outtextxy(x/2-105,200,"Load Image");
	setcolor(3);
	outtextxy(x/2-55,250,"Exit");
	if(mmt==150)
	{
		setcolor(1);
		rectangle(mml,mmt,mmr,mmb);
	}
	else
	if(mmt==200)
	{
		setcolor(2);
		rectangle(mml,mmt,mmr,mmb);
	}
	else
	if(mmt==250)
	{
		setcolor(3);
		rectangle(mml,mmt,mmr,mmb);
	}
	while(bioskey(1)==0)
	{
		k=bioskey(0);
		if(k==TKEY||k==LKEY)//if the top arrow key or the left arrow key is pressed
		{
			if(mmt-50>=150)
			{
				if(mmt-50==150)
				{
					setcolor(15);
					rectangle(mml,mmt,mmr,mmb);
					mmt=mmt-50;
					mmb=mmb-50;
					setcolor(1);
					rectangle(mml,mmt,mmr,mmb);
				}
				else
				if(mmt-50==200)
				{
					setcolor(15);
					rectangle(mml,mmt,mmr,mmb);
					mmt=mmt-50;
					mmb=mmb-50;
					setcolor(2);
					rectangle(mml,mmt,mmr,mmb);
				}
				else
				if(mmt-50==250)
				{
					setcolor(15);
					rectangle(mml,mmt,mmr,mmb);
					mmt=mmt-50;
					mmb=mmb-50;
					setcolor(3);
					rectangle(mml,mmt,mmr,mmb);
				}
			}
		}
		else
		if(k==BKEY||k==RKEY)//if the bottom arrow key or the right arrow key is pressed
		{
			if(mmb+50<=300)
			{
				if(mmb+50==300)
				{
					setcolor(15);
					rectangle(mml,mmt,mmr,mmb);
					mmt=mmt+50;
					mmb=mmb+50;
					setcolor(3);
					rectangle(mml,mmt,mmr,mmb);
				}
				if(mmb+50==200)
				{
					setcolor(15);
					rectangle(mml,mmt,mmr,mmb);
					mmt=mmt+50;
					mmb=mmb+50;
					setcolor(1);
					rectangle(mml,mmt,mmr,mmb);
				}
				else
				if(mmb+50==250)
				{
					setcolor(15);
					rectangle(mml,mmt,mmr,mmb);
					mmt=mmt+50;
					mmb=mmb+50;
					setcolor(2);
					rectangle(mml,mmt,mmr,mmb);
				}
			}
		}
		if(k==ESC)//if ESC key is pressed
		{
			mainmenu();
		}
		else
		if(k==ENTER)//if ENTER key is pressed
		{
			if(mmt==150)//if NEW IMAGE is selected
			{
				Loading();
				newimagescreen();
				key();
			}
			else
			if(mmt==200)//if LOAD IMAGE is selected
			{
				if(check()==0)
				{
					cleardevice();
					settextstyle(3,0,2);
					outtextxy(250,210,"No Images Saved");
					getch();
					mainmenu();
				}
				else
				{
					clrscr();
					setbkcolor(15);
					cleardevice();
					char name[5];
					char line[5];
					settextstyle(4,0,4);
					setcolor(7);
					outtextxy(220,30,"Saved Images");
					settextstyle(2,0,5);
					fstream f;
					f.open("IMAGENAM",ios::in);
					f.getline(line,5);
					cout<<endl<<endl<<endl<<endl;
					while(!f.eof())
					{
						cout<<endl<<"  *   "<<line;
						f.getline(line,5);
					}
					f.close();
					cout<<endl<<endl<<"  Enter The Name Of The Image That You Want To Open : ";
					gets(name);


					cleardevice();
					setbkcolor(0);
					setcolor(15);
					int kk;
					int jj;
					char c;
					kk=0;
					jj=y-50;
					fstream f1;
					f1.open("COLOURS",ios::in);
					f1>>c;
					while(!f1.eof())
					{
						if(c=='*')
						{
							kk=0;jj=jj+1;gotoxy(kk,jj);
						}
						else if(c=='a')
						{
							putpixel(kk,jj,0);kk++;
						}
						else if(c=='b')
						{
							putpixel(kk,jj,1);kk++;
						}
						else if(c=='c')
						{
							putpixel(kk,jj,2);kk++;
						}
						else if(c=='d')
						{
							putpixel(kk,jj,3);kk++;
						}
						else if(c=='e')
						{
							putpixel(kk,jj,4);kk++;
						}
						else if(c=='f')
						{
							putpixel(kk,jj,5);kk++;
						}
						else if(c=='g')
						{
							putpixel(kk,jj,6);kk++;
						}
						else if(c=='h')
						{
							putpixel(kk,jj,7);kk++;
						}
						else if(c=='i')
						{
							putpixel(kk,jj,8);kk++;
						}
						else if(c=='j')
						{
							putpixel(kk,jj,9);kk++;
						}
						else if(c=='k')
						{
							putpixel(kk,jj,10);kk++;
						}
						else if(c=='l')
						{
							putpixel(kk,jj,11);kk++;
						}
						else if(c=='m')
						{
							putpixel(kk,jj,12);kk++;
						}
						else if(c=='n')
						{
							putpixel(kk,jj,13);kk++;
						}
						else if(c=='o')
						{
							putpixel(kk,jj,14);kk++;
						}
						else if(c=='p')
						{
							putpixel(kk,jj,15);kk++;
						}
						f1>>c;
					}
					f1.close();
					//line(200,429,200,479);
					//drawing area
					rectangle(x,0,8*25+5,y);
					//tools area
					rectangle(0,0,6*25,2*a);
					for(int j=a;j<=2*a;j=j+a)
					{
					    //	line(0,j,150,j);
					}
					for(int jj1=0;jj1<4*b;jj1=jj1+b)
					{
					      //	line(jj1,0,jj1,2*a);
					}
					settextstyle(3,0,0);
					outtextxy(20,0,"P");
					outtextxy(70,0,"L");
					outtextxy(120,0,"R");
					outtextxy(10,a,"B1");
					outtextxy(60,a,"B2");
					outtextxy(120,a,"E");
					//options area
					rectangle(8*25,(y-55)/2+2-120,0,y-55-120);
					setfillstyle(1,8);
					floodfill(20,y/2-20-120,15);
					settextstyle(3,0,1);
					setcolor(15);
					outtextxy(15,y-55-120+10+20-5,"Click 'E' To Erase");
					outtextxy(50,y-55-120+10+30+10-5,"Everything");

					setcolor(15);
					settextstyle(3,0,1);
					outtextxy(20,getmaxy()-90,"CurrentColor");
					setcolor(color);
					setfillstyle(1,color);
					bar(140,getmaxy()-85,160,getmaxy()-65);
					setcolor(15);
					rectangle(140,getmaxy()-85,160,getmaxy()-65);
					setcolor(color);
					kk=8*25+5;
					jj=0;
					fstream f01;
					f01.open(name,ios::in);
					f01>>c;
					while(!f01.eof())
					{
						if(c=='*')
						{
							kk=8*25+5;jj=jj+1;gotoxy(kk,jj);
						}
						else if(c=='a')
						{
							putpixel(kk,jj,0);kk++;
						}
						else if(c=='b')
						{
							putpixel(kk,jj,1);kk++;
						}
						else if(c=='c')
						{
							putpixel(kk,jj,2);kk++;
						}
						else if(c=='d')
						{
							putpixel(kk,jj,3);kk++;
						}
						else if(c=='e')
						{
							putpixel(kk,jj,4);kk++;
						}
						else if(c=='f')
						{
							putpixel(kk,jj,5);kk++;
						}
						else if(c=='g')
						{
							putpixel(kk,jj,6);kk++;
						}
						else if(c=='h')
						{
							putpixel(kk,jj,7);kk++;
						}
						else if(c=='i')
						{
							putpixel(kk,jj,8);kk++;
						}
						else if(c=='j')
							{
							putpixel(kk,jj,9);kk++;
						}
						else if(c=='k')
						{
							putpixel(kk,jj,10);kk++;
						}
						else if(c=='l')
						{
							putpixel(kk,jj,11);kk++;
						}
						else if(c=='m')
						{
							putpixel(kk,jj,12);kk++;
						}
						else if(c=='n')
						{
							putpixel(kk,jj,13);kk++;
						}
						else if(c=='o')
						{
							putpixel(kk,jj,14);kk++;
						}
						else if(c=='p')
						{
							putpixel(kk,jj,15);kk++;
						}
						f01>>c;
					}
					f01.close();
					getch();
					key();
				}
			}
			else
			if(mmt==250)//if EXIT is selected
			{
				cleardevice();
				setcolor(8);
				settextstyle(3,0,4);
				outtextxy(100,100,"Do You Really Want To Quit?");
				setcolor(2);
				outtextxy(200,200,"[Y]es");
				setcolor(4);
				outtextxy(400,200,"[N]o");
				while(bioskey(1)==0)
				{
					k2=bioskey(0);
					if(k2==Y)
					{
						cleardevice();
						setcolor(8);
						settextstyle(3,0,4);
						outtextxy(230,200,"Good Bye...");
						getch();

						exit(1);
					}
					else
					if(k2==N)
					{
						mainmenu();
					}
				}
			}
		}
	}
}
void DRAWING_UTILITY::newimagescreen()
{
	//displays the Colors area

	cleardevice();
	setbkcolor(0);
	setcolor(15);

	int kk;
	int jj;
	char c;
	kk=0;
	jj=y-50;
	fstream f1;
	f1.open("COLOURS",ios::in);
	f1>>c;
	while(!f1.eof())
	{
		if(c=='*')
		{
			kk=0;jj=jj+1;gotoxy(kk,jj);
		}
		else if(c=='a')
		{
			putpixel(kk,jj,0);kk++;
		}
		else if(c=='b')
		{
			putpixel(kk,jj,1);kk++;
		}
		else if(c=='c')
		{
			putpixel(kk,jj,2);kk++;
		}
		else if(c=='d')
		{
			putpixel(kk,jj,3);kk++;
		}
		else if(c=='e')
		{
			putpixel(kk,jj,4);kk++;
		}
		else if(c=='f')
		{
			putpixel(kk,jj,5);kk++;
		}
		else if(c=='g')
		{
			putpixel(kk,jj,6);kk++;
		}
		else if(c=='h')
		{
			putpixel(kk,jj,7);kk++;
		}
		else if(c=='i')
		{
			putpixel(kk,jj,8);kk++;
		}
		else if(c=='j')
		{
			putpixel(kk,jj,9);kk++;
		}
		else if(c=='k')
		{
			putpixel(kk,jj,10);kk++;
		}
		else if(c=='l')
		{
			putpixel(kk,jj,11);kk++;
		}
		else if(c=='m')
		{
			putpixel(kk,jj,12);kk++;
		}
		else if(c=='n')
		{
			putpixel(kk,jj,13);kk++;
		}
		else if(c=='o')
		{
			putpixel(kk,jj,14);kk++;
		}
		else if(c=='p')
		{
			putpixel(kk,jj,15);kk++;
		}
		f1>>c;
	}
	line(8*25,y-50,8*25,y);
	//displays the drawing area
	rectangle(x,0,8*25+5,y);
	//displays the tools area
	rectangle(0,0,6*25,2*a);
	for(int j=a;j<=2*a;j=j+a)
	{
		line(0,j,6*25,j);
	}
	for(int jj1=0;jj1<4*b;jj1=jj1+b)
	{
		line(jj1,0,jj1,2*a);
	}
	settextstyle(3,0,0);
	outtextxy(20,0,"P");
	outtextxy(70,0,"L");
	outtextxy(120,0,"R");
	outtextxy(10,a,"B1");
	outtextxy(60,a,"B2");
	outtextxy(120,a,"E");
	//displays the options area
	rectangle(8*25,(y-55)/2+2-120,0,y-55-120);
	setfillstyle(1,8);
	floodfill(20,y/2-20-120,15);
	settextstyle(3,0,1);
	setcolor(15);
	outtextxy(15,y-55-120+10+20-5,"Click 'E' To Erase");
	outtextxy(50,y-55-120+10+30+10-5,"Everything");
	setcolor(15);
	outtextxy(20,getmaxy()-90,"CurrentColor");
	setcolor(color);
	setfillstyle(1,color);
	bar(140,getmaxy()-85,160,getmaxy()-65);
	setcolor(15);
	rectangle(140,getmaxy()-85,160,getmaxy()-65);
	setcolor(color);
}
void DRAWING_UTILITY::key()
{
	setlinestyle(SOLID_LINE,1,0);
	setcolor(15);
	for(int j=a;j<=2*a;j=j+a)
	{
		line(0,j,6*25,j);
	}
	for(int jj2=0;jj2<4*b;jj2=jj2+b)
	{
		line(jj2,0,jj2,2*a);
	}
	setcolor(4);
	rectangle(tml,tmt,tmr,tmb);
	//the current image is stored in the file 'ESCIMG'
	while(bioskey(1)==0)
	{
		k3=bioskey(0);
		if(k3==ESC)//if ESC key is pressed
		{
			fstream f;
			f.open("ESCIMG",ios::out);
			for(int j=0;j<=y;++j)
			{
				for(int k=8*25+5;k<x;++k)
				{
					int g;
					g=getpixel(k,j);
					if(g==0)f<<"a";
					else if(g==1)f<<"b";
					else if(g==2)f<<"c";
					else if(g==3)f<<"d";
					else if(g==4)f<<"e";
					else if(g==5)f<<"f";
					else if(g==6)f<<"g";
					else if(g==7)f<<"h";
					else if(g==8)f<<"i";
					else if(g==9)f<<"j";
					else if(g==10)f<<"k";
					else if(g==11)f<<"l";
					else if(g==12)f<<"m";
					else if(g==13)f<<"n";
					else if(g==14)f<<"o";
					else if(g==15)f<<"p";
				}
				f<<"*";
			}
			escapemenu();
		}
		else
		if(k3==EKEY)//if E is pressed
		{
			setcolor(15);
			rectangle(x,0,8*25+5,y);
			setfillstyle(1,BLACK);
			bar(x-1,0+1,8*25+6,y-1);
		}
		else
		if(k3==CKEY)//if C is pressed
		{
			setcolor(15);
			rectangle(0,0,6*25,2*a);
			for(int j=a;j<=2*a;j=j+a)
			{
				line(0,j,6*25,j);
			}
			for(int jj1=0;jj1<4*b;jj1=jj1+b)
			{
				line(jj1,0,jj1,2*a);
			}
			if(cml==0&&cmt==y-50)setcolor(BLACK);
			else if(cml==0&&cmt==y-25)setcolor(1);
			else if(cml==25&&cmt==y-50)setcolor(2);
			else if(cml==25&&cmt==y-25)setcolor(3);
			else if(cml==50&&cmt==y-50)setcolor(4);
			else if(cml==50&&cmt==y-25)setcolor(5);
			else if(cml==75&&cmt==y-50)setcolor(6);
			else if(cml==75&&cmt==y-25)setcolor(7);
			else if(cml==100&&cmt==y-50)setcolor(8);
			else if(cml==100&&cmt==y-25)setcolor(9);
			else if(cml==125&&cmt==y-50)setcolor(10);
			else if(cml==125&&cmt==y-25)setcolor(11);
			else if(cml==150&&cmt==y-50)setcolor(12);
			else if(cml==150&&cmt==y-25)setcolor(13);
			else if(cml==175&&cmt==y-50)setcolor(14);
			else if(cml==175&&cmt==y-25)setcolor(15);
			rectangle(cml,cmt,cmr,cmb);
			while(bioskey(1)==0)
			{
				k4=bioskey(0);
				if(k4==TKEY)
				{
					if(cmt-25>=y-50)
					{
						setcolor(15);
						rectangle(cml,cmt,cmr,cmb);
						cmt=cmt-25;
						cmb=cmb-25;
						if(cml==0&&cmt==y-50)setcolor(BLACK);
						else if(cml==0&&cmt==y-25)setcolor(1);
						else if(cml==25&&cmt==y-50)setcolor(2);
						else if(cml==25&&cmt==y-25)setcolor(3);
						else if(cml==50&&cmt==y-50)setcolor(4);
						else if(cml==50&&cmt==y-25)setcolor(5);
						else if(cml==75&&cmt==y-50)setcolor(6);
						else if(cml==75&&cmt==y-25)setcolor(7);
						else if(cml==100&&cmt==y-50)setcolor(8);
						else if(cml==100&&cmt==y-25)setcolor(9);
						else if(cml==125&&cmt==y-50)setcolor(10);
						else if(cml==125&&cmt==y-25)setcolor(11);
						else if(cml==150&&cmt==y-50)setcolor(12);
						else if(cml==150&&cmt==y-25)setcolor(13);
						else if(cml==175&&cmt==y-50)setcolor(14);
						else if(cml==175&&cmt==y-25)setcolor(15);
						rectangle(cml,cmt,cmr,cmb);
					}
				}
				else
				if(k4==BKEY)//if the bottom arrow key is pressed
				{
					if(cmt+25<=y-25)
					{
						setcolor(15);
						rectangle(cml,cmt,cmr,cmb);
						cmt=cmt+25;
						cmb=cmb+25;
						if(cml==0&&cmt==y-50)setcolor(BLACK);
						else if(cml==0&&cmt==y-25)setcolor(1);
						else if(cml==25&&cmt==y-50)setcolor(2);
						else if(cml==25&&cmt==y-25)setcolor(3);
						else if(cml==50&&cmt==y-50)setcolor(4);
						else if(cml==50&&cmt==y-25)setcolor(5);
						else if(cml==75&&cmt==y-50)setcolor(6);
						else if(cml==75&&cmt==y-25)setcolor(7);
						else if(cml==100&&cmt==y-50)setcolor(8);
						else if(cml==100&&cmt==y-25)setcolor(9);
						else if(cml==125&&cmt==y-50)setcolor(10);
						else if(cml==125&&cmt==y-25)setcolor(11);
						else if(cml==150&&cmt==y-50)setcolor(12);
						else if(cml==150&&cmt==y-25)setcolor(13);
						else if(cml==175&&cmt==y-50)setcolor(14);
						else if(cml==175&&cmt==y-25)setcolor(15);
						rectangle(cml,cmt,cmr,cmb);
					}
				}
				else
				if(k4==LKEY)//if the left arrow key is pressed
				{
					if(cml-25>=0)
					{
						setcolor(15);
						rectangle(cml,cmt,cmr,cmb);
						cml=cml-25;
						cmr=cmr-25;
						if(cml==0&&cmt==y-50)setcolor(BLACK);
						else if(cml==0&&cmt==y-25)setcolor(1);
						else if(cml==25&&cmt==y-50)setcolor(2);
						else if(cml==25&&cmt==y-25)setcolor(3);
						else if(cml==50&&cmt==y-50)setcolor(4);
						else if(cml==50&&cmt==y-25)setcolor(5);
						else if(cml==75&&cmt==y-50)setcolor(6);
						else if(cml==75&&cmt==y-25)setcolor(7);
						else if(cml==100&&cmt==y-50)setcolor(8);
						else if(cml==100&&cmt==y-25)setcolor(9);
						else if(cml==125&&cmt==y-50)setcolor(10);
						else if(cml==125&&cmt==y-25)setcolor(11);
						else if(cml==150&&cmt==y-50)setcolor(12);
						else if(cml==150&&cmt==y-25)setcolor(13);
						else if(cml==175&&cmt==y-50)setcolor(14);
						else if(cml==175&&cmt==y-25)setcolor(15);
						rectangle(cml,cmt,cmr,cmb);
					}
				}
				else
				if(k4==RKEY)//if the right arrow key is pressed
				{
					if(cml+25<=8*25-25)
					{
						setcolor(15);
						rectangle(cml,cmt,cmr,cmb);
						cml=cml+25;
						cmr=cmr+25;
						if(cml==0&&cmt==y-50)setcolor(BLACK);
						else if(cml==0&&cmt==y-25)setcolor(1);
						else if(cml==25&&cmt==y-50)setcolor(2);
						else if(cml==25&&cmt==y-25)setcolor(3);
						else if(cml==50&&cmt==y-50)setcolor(4);
						else if(cml==50&&cmt==y-25)setcolor(5);
						else if(cml==75&&cmt==y-50)setcolor(6);
						else if(cml==75&&cmt==y-25)setcolor(7);
						else if(cml==100&&cmt==y-50)setcolor(8);
						else if(cml==100&&cmt==y-25)setcolor(9);
						else if(cml==125&&cmt==y-50)setcolor(10);
						else if(cml==125&&cmt==y-25)setcolor(11);
						else if(cml==150&&cmt==y-50)setcolor(12);
						else if(cml==150&&cmt==y-25)setcolor(13);
						else if(cml==175&&cmt==y-50)setcolor(14);
						else if(cml==175&&cmt==y-25)setcolor(15);
						rectangle(cml,cmt,cmr,cmb);
					}
				}
				else
				if(k4==ENTER)//if the ENTER key is pressed
				{
					if(cml==0&&cmt==y-50)color=0;
					else if(cml==0&&cmt==y-25)color=1;
					else if(cml==25&&cmt==y-50)color=2;
					else if(cml==25&&cmt==y-25)color=3;
					else if(cml==50&&cmt==y-50)color=4;
					else if(cml==50&&cmt==y-25)color=5;
					else if(cml==75&&cmt==y-50)color=6;
					else if(cml==75&&cmt==y-25)color=7;
					else if(cml==100&&cmt==y-50)color=8;
					else if(cml==100&&cmt==y-25)color=9;
					else if(cml==125&&cmt==y-50)color=10;
					else if(cml==125&&cmt==y-25)color=11;
					else if(cml==150&&cmt==y-50)color=12;
					else if(cml==150&&cmt==y-25)color=13;
					else if(cml==175&&cmt==y-50)color=14;
					else if(cml==175&&cmt==y-25)color=15;
					setcolor(15);

					int kk;
					int jj;
					char c;
					kk=0;
					jj=y-50;
					fstream f1;
					f1.open("COLOURS",ios::in);
					f1>>c;
					while(!f1.eof())
					{
						if(c=='*')
						{
							kk=0;jj=jj+1;gotoxy(kk,jj);
						}
						else if(c=='a')
						{
							putpixel(kk,jj,0);kk++;
						}
							else if(c=='b')
						{
							putpixel(kk,jj,1);kk++;
						}
						else if(c=='c')
						{
							putpixel(kk,jj,2);kk++;
						}
						else if(c=='d')
						{
							putpixel(kk,jj,3);kk++;
						}
						else if(c=='e')
						{
							putpixel(kk,jj,4);kk++;
						}
						else if(c=='f')
						{
							putpixel(kk,jj,5);kk++;
						}
						else if(c=='g')
						{
							putpixel(kk,jj,6);kk++;
						}
						else if(c=='h')
						{
							putpixel(kk,jj,7);kk++;
						}
						else if(c=='i')
						{
							putpixel(kk,jj,8);kk++;
						}
						else if(c=='j')
						{
							putpixel(kk,jj,9);kk++;
						}
						else if(c=='k')
						{
							putpixel(kk,jj,10);kk++;
						}
						else if(c=='l')
						{
							putpixel(kk,jj,11);kk++;
						}
						else if(c=='m')
						{
							putpixel(kk,jj,12);kk++;
						}
						else if(c=='n')
						{
							putpixel(kk,jj,13);kk++;
						}
						else if(c=='o')
						{
							putpixel(kk,jj,14);kk++;
						}
						else if(c=='p')
						{
							putpixel(kk,jj,15);kk++;
						}
						f1>>c;
					}
					line(8*25,y-50,8*25,y);
					setcolor(15);
					settextstyle(3,0,1);
					outtextxy(20,getmaxy()-90,"CurrentColor");
					setcolor(color);
					setfillstyle(1,color);
					bar(140,getmaxy()-85,160,getmaxy()-65);
					setcolor(15);
					rectangle(140,getmaxy()-85,160,getmaxy()-65);
					setcolor(color);
					key();
				}
			}
		}
		if(k3==TKEY)//if the TOP arrow key is pressed
		{
			if(tmt-a>=0)
			{
				setcolor(15);
				rectangle(tml,tmt,tmr,tmb);
				tmt=tmt-a;
				tmb=tmb-a;
				setcolor(4);
				rectangle(tml,tmt,tmr,tmb);
			}
		}
		else
		if(k3==BKEY)//if the BOTTOM arrow key is pressed
		{
			if(tmb+a<=2*a)
			{
				setcolor(15);
				rectangle(tml,tmt,tmr,tmb);
				tmt=tmt+a;
				tmb=tmb+a;
				setcolor(4);
				rectangle(tml,tmt,tmr,tmb);
			}
		}
		else
		if(k3==LKEY)//if the LEFT arrow key is pressed
		{
			if(tml-b>=0)
			{
				setcolor(15);
				rectangle(tml,tmt,tmr,tmb);
				tml=tml-b;
				tmr=tmr-b;
				setcolor(4);
				rectangle(tml,tmt,tmr,tmb);
			}
		}
		else
		if(k3==RKEY)//if the RIGHT arrow key is pressed
		{
			if(tmr+b<8*25)
			{
				setcolor(15);
				rectangle(tml,tmt,tmr,tmb);
				tml=tml+b;
				tmr=tmr+b;
				setcolor(4);
				rectangle(tml,tmt,tmr,tmb);
			}
		}
		else
		if(k3==ENTER)//if the ENTER key is pressed
		{
			if(tmt==a&&tml==0)//For B1
			{
				setlinestyle(SOLID_LINE,1,0);
				setcolor(15);
				circle((8*25)/2-70+5+40,y/2+140-120-20,10);
				circle((8*25)/2-30+5+40,y/2+140-120-20,5);

				settextstyle(2,0,0);
				outtextxy((8*25)/2-70+3+40,y/2+140+20-120-20,"1");
				outtextxy((8*25)/2-30+3+40,y/2+140+20-120-20,"2");

				settextstyle(1,0,0);
				outtextxy((8*25)/2-70+3-5+40,y/2+20-120-20,"1");
				outtextxy((8*25)/2-30+3-5+40,y/2+20-120-20,"2");

				setcolor(15);
				rectangle(boml,bomt,bomr,bomb);
				while(bioskey(1)==0)
				{
					k5=bioskey(0);
					if(k5==LKEY)//if the LEFT arrow key is pressed
					{
						if(boml-40>=100+5-80-5+40)
						{
							setcolor(8);
							rectangle(boml,bomt,bomr,bomb);
							setcolor(15);
							boml=boml-40;
							bomr=bomr-40;
							rectangle(boml,bomt,bomr,bomb);
						}
					}
					else
					if(k5==RKEY)//if the RIGHT arrow key is pressed
					{
						if(bomr+40<=80+40+40)
						{
							setcolor(8);
							rectangle(boml,bomt,bomr,bomb);
							setcolor(15);
							boml=boml+40;
							bomr=bomr+40;
							rectangle(boml,bomt,bomr,bomb);
						}
					}
					else
					if(k5==ENTER)//if the ENTER key is pressed
					{
						if(boml==100+5-80-5+40)
						{
							oort1=1;
						}
						else
						{
							oort1=2;
						}
						int kk;
						int jj;
						char c;
						kk=0;
						jj=(y-55)/2+2-120;
						fstream f1;
						f1.open("COLOUREI",ios::in);
						f1>>c;
						while(!f1.eof())
						{
							if(c=='*')
							{
								kk=0;jj=jj+1;gotoxy(kk,jj);
							}
							else if(c=='i')
							{
								putpixel(kk,jj,8);kk++;
							}
							else if(c=='p')
							{
								putpixel(kk,jj,15);kk++;
							}
							f1>>c;
						}
						B1(color,oort1);
					}
				}
			}
			else
			if(tmt==a&&tml==b)//for B2
			{
				setlinestyle(SOLID_LINE,1,0);
				setcolor(15);
				rectangle(100+5-40,y/2+130-120-20,120+5-40,y/2+150-120-20);
				rectangle(145+5-40,y/2+135-120-20,155+5-40,y/2+145-120-20);

				settextstyle(2,0,0);
				outtextxy(100+5+10-2-40,y/2+130+30-120-20,"1");
				outtextxy(145+5+5-2-40,y/2+135+25-120-20,"2");

				settextstyle(1,0,0);
				outtextxy(100+5+10-2-5-40,y/2+20-120-20,"1");
				outtextxy(145+5+5-2-5-40,y/2+20-120-20,"2");

				setcolor(15);
				rectangle(boml,bomt,bomr,bomb);
				while(bioskey(1)==0)
				{
					k6=bioskey(0);
					if(k6==LKEY)//if the LEFT arrow key is pressed
					{
						if(boml-40>=100+5-80-5+40)
						{
							setcolor(8);
							rectangle(boml,bomt,bomr,bomb);
							setcolor(15);
							boml=boml-40;
							bomr=bomr-40;
							rectangle(boml,bomt,bomr,bomb);
						}
					}
					else
					if(k6==RKEY)//if the RIGHT arrow key is pressed
					{
						if(bomr+40<=80+40+40)
						{
							setcolor(8);
							rectangle(boml,bomt,bomr,bomb);
							setcolor(15);
							boml=boml+40;
							bomr=bomr+40;
							rectangle(boml,bomt,bomr,bomb);
						}
					}
					else
					if(k6==ENTER)//if the ENTER key is pressed
					{
						if(boml==100+5-80-5+40)
						{
							oort2=1;
						}
						else
						{
							oort2=2;
						}
						int kk;
						int jj;
						char c;
						kk=0;
						jj=(y-55)/2+2-120;
						fstream f1;
						f1.open("COLOUREI",ios::in);
						f1>>c;
						while(!f1.eof())
						{
							if(c=='*')
							{
								kk=0;jj=jj+1;gotoxy(kk,jj);
							}
							else if(c=='i')
							{
								putpixel(kk,jj,8);kk++;
							}
							else if(c=='p')
							{
								putpixel(kk,jj,15);kk++;
							}
							f1>>c;
						}
						B2(color,oort2);
					}
				}
			}
			else
			if(tmt==a&&tml==2*b)//for E
			{

						int x,y,cl,aa,bb,xx,yy;
						int xx1,yy1,ar=0,c;
						aa=x/2+100;
						bb=y/2;
						setposi(aa,bb);
						callmouse();
						restrictmouseptr((8*25)+5+1+10+1,0+1+10+1,getmaxx()-1,getmaxy()-1);
						do
						{
							mouseposi(x,y,cl);
							if(cl==1)
							{
								setcolor(0);
								setfillstyle(1,0);
								bar(x-10,y-10,x-3,y-3);
							}
							xx=x;
							yy=y;
							c=cl;
							gotoxy(10,9);
							setcolor(15);
							rectangle(getmaxx(),0,8*25+5,getmaxy());
						}while(!kbhit());
						getch();
						mousehide();
						key();
			}
			else
			if(tmt==0&&tml==0)//for P
			{

						int x,y,cl,aa,bb,xx,yy;
						int xx1,yy1,ar=0,c;
						int k;
						aa=x/2+100;
						bb=y/2;
						setposi(aa,bb);
						callmouse();
						restrictmouseptr((8*25)+5+1+10+1,0+1+10+1,getmaxx()-1,getmaxy()-1);
						do
						{
							mouseposi(x,y,cl);
							if(cl==1)
							{
								putpixel(x-5,y-5,color);
							}
							gotoxy(10,9);
							xx=x;
							yy=y;
							cl=c;
						}while(!kbhit());
						getch();
						mousehide();
						key();
			}
			else
			if(tmt==0&&tml==2*b)//For R
			{
				setlinestyle(SOLID_LINE,1,0);
				settextstyle(2,0,7);
				setcolor(15);
				outtextxy(75,(y/2)+30-120,"Draw");
				outtextxy(30,(y/2)+80-120,"Draw And Fill");
				rectangle(roml,romt,romr,romb);
				while(bioskey(1)==0)
				{
					k7=bioskey(0);
					if(k7==TKEY)//if the TOP arrow key is pressed
					{
						if(romt-50>=(y/2)+75-50-120)
						{
							setcolor(8);
							rectangle(roml,romt,romr,romb);
							setcolor(15);
							romt=romt-50;
							romb=romb-50;
							rectangle(roml,romt,romr,romb);
						}
					}
					else
					if(k7==BKEY)//if the BOTTOM arrow key is pressed
					{
						if(romb+50<=(y/2)+155-120)
						{
							setcolor(8);
							rectangle(roml,romt,romr,romb);
							setcolor(15);
							romt=romt+50;
							romb=romb+50;
							rectangle(roml,romt,romr,romb);
						}
					}
					else
					if(k7==ENTER)//if the ENTER key is pressed
					{

						if(romt==(y/2)+75-50-120)
						{
							DorDAF=0;
						}
						else
						{
							DorDAF=1;
						}

						int kk;
						int jj;
						char c;
						kk=0;
						jj=(y-55)/2+2-120;
						fstream f1;
						f1.open("COLOUREI",ios::in);
						f1>>c;
						while(!f1.eof())
						{
							if(c=='*')
							{
								kk=0;jj=jj+1;gotoxy(kk,jj);
							}
							else if(c=='i')
							{
								putpixel(kk,jj,8);kk++;
							}
							else if(c=='p')
							{
								putpixel(kk,jj,15);kk++;
							}
							f1>>c;
						}
						Rectangle(color,DorDAF);
					}
				}
			}
			else
			if(tmt==0&&tml==b)//For L
			{
				setcolor(15);
				setlinestyle(SOLID_LINE,1,0);
				line(0,320-120,8*25,320-120);
				settextstyle(2,0,6);
				outtextxy(70,(y/2)-20-120,"Styles");
				outtextxy(55,(y/2)-20+110-120,"Thickness");
				setlinestyle(SOLID_LINE,1,0);
				line(30,320-60-120,8*25-30,320-60-120);
				setlinestyle(DOTTED_LINE,1,0);
				line(30,320-30-120,8*25-30,320-30-120);
				setlinestyle(SOLID_LINE,1,0);
				line(30,320+30+20-120,8*25-30,320+30+20-120);
				setlinestyle(SOLID_LINE,5,THICK_WIDTH);
				line(30,320+60+20-120,8*25-30,320+60+20-120);
				setlinestyle(SOLID_LINE,1,0);
				rectangle(lsoml,lsomt,lsomr,lsomb);
				while(bioskey(1)==0)
				{
					k8=bioskey(0);
					if(k8==TKEY)//if the TOP arrow key is pressed
					{
						if(lsomt-30>=320-60-120-10)
						{
							setcolor(8);
							rectangle(lsoml,lsomt,lsomr,lsomb);
							setcolor(15);
							lsomt=lsomt-30;
							lsomb=lsomb-30;
							rectangle(lsoml,lsomt,lsomr,lsomb);
						}
					}
					else
					if(k8==BKEY)//if the BOTTOM arrow key is pressed
					{
						if(lsomb+30<=320-60-120+10+30)
						{
							setcolor(8);
							rectangle(lsoml,lsomt,lsomr,lsomb);
							setcolor(15);
							lsomt=lsomt+30;
							lsomb=lsomb+30;
							rectangle(lsoml,lsomt,lsomr,lsomb);
						}
					}
					else
					if(k8==ENTER)//if the ENTER key is pressed
					{
						if(lsomt==320-60-120-10)
						{
							Linestyle=1;
						}
						else
						{
							Linestyle=2;
						}
						setcolor(8);
						rectangle(lsoml,lsomt,lsomr,lsomb);
						setcolor(15);
						rectangle(ltoml,ltomt,ltomr,ltomb);
						while(bioskey(1)==0)
						{
							k9=bioskey(0);
							if(k9==TKEY)//if the TOP arrow key is pressed
							{
								if(ltomt-30>=320-60-120-10+110)
								{
									setcolor(8);
									rectangle(ltoml,ltomt,ltomr,ltomb);
									setcolor(15);
									ltomt=ltomt-30;
									ltomb=ltomb-30;
									rectangle(ltoml,ltomt,ltomr,ltomb);
								}
							}
							else
							if(k9==BKEY)//if the BOTTOM arrow key is pressed
							{
								if(ltomb+30<=320-60-120+10+110+30)
								{
									setcolor(8);
									rectangle(ltoml,ltomt,ltomr,ltomb);
									setcolor(15);
									ltomt=ltomt+30;
									ltomb=ltomb+30;
									rectangle(ltoml,ltomt,ltomr,ltomb);
								}
							}
							else
							if(k9==ENTER)//if the ENTER key is pressed
							{
								if(ltomt==320-60-120-10+110)
								{
									Thickness=1;
								}
								else
								{
									Thickness=2;
								}
								int kk;
								int jj;
								char c;
								kk=0;
								jj=(y-55)/2+2-120;
								fstream f1;
								f1.open("COLOUREI",ios::in);
								f1>>c;
								while(!f1.eof())
								{
									if(c=='*')
									{
										kk=0;jj=jj+1;gotoxy(kk,jj);
									}
									else if(c=='i')
									{
										putpixel(kk,jj,8);kk++;
									}
									else if(c=='p')
									{
										putpixel(kk,jj,15);kk++;
									}
									f1>>c;
								}
								f1.close();
								Line(color,Linestyle,Thickness);
							}
						}
					}
				}
			}
		}
	}
}
void DRAWING_UTILITY::escapemenu()
{
	cleardevice();
	setbkcolor(15);
	settextstyle(10,0,1);
	setcolor(1);
	outtextxy(x/2-65+20,80,"Back");
	setcolor(2);
	outtextxy(x/2-65+20,130,"Save");
	setcolor(3);
	outtextxy(x/2-100-30,180,"Go To Main Menu");
	setcolor(4);
	outtextxy(x/2-65+20,230,"Exit");
	if(emt==85)
	{
		setcolor(1);
		rectangle(eml,emt,emr,emb);
	}
	else
	if(emt==135)
	{
		setcolor(2);
		rectangle(eml,emt,emr,emb);
	}
	else
	if(emt==185)
	{
		setcolor(3);
		rectangle(eml,emt,emr,emb);
	}
	else
	if(emt==235)
	{
		setcolor(4);
		rectangle(eml,emt,emr,emb);
	}
	while(bioskey(1)==0)
	{
		k10=bioskey(0);
		if(k10==TKEY)//if the TOP arrow key is pressed
		{
			if(emt-50>=85)
			{
				setcolor(15);
				rectangle(eml,emt,emr,emb);
				if(emt-50==85)
				{
					emt=emt-50;
					emb=emb-50;
					setcolor(1);
					rectangle(eml,emt,emr,emb);
				}
				else
				if(emt-50==135)
				{
					emt=emt-50;
					emb=emb-50;
					setcolor(2);
					rectangle(eml,emt,emr,emb);
				}
				else
				if(emt-50==185)
				{
					emt=emt-50;
					emb=emb-50;
					setcolor(3);
					rectangle(eml,emt,emr,emb);
				}
				else
				if(emt-50==235)
				{
					emt=emt-50;
					emb=emb-50;
					setcolor(4);
					rectangle(eml,emt,emr,emb);
				}
			}
		}
		else
		if(k10==BKEY)//if the BOTTOM arrow key is pressed
		{
			if(emb+50<=285)
			{
				setcolor(15);
				rectangle(eml,emt,emr,emb);
				if(emb+50==135)
				{
					emt=emt+50;
					emb=emb+50;
					setcolor(1);
					rectangle(eml,emt,emr,emb);
				}
				else
				if(emb+50==185)
				{
					emt=emt+50;
					emb=emb+50;
					setcolor(2);
					rectangle(eml,emt,emr,emb);
				}
				else
				if(emb+50==235)
				{
					emt=emt+50;
					emb=emb+50;
					setcolor(3);
					rectangle(eml,emt,emr,emb);
				}
				else
				if(emb+50==285)
				{
					emt=emt+50;
					emb=emb+50;
					setcolor(4);
					rectangle(eml,emt,emr,emb);
				}
			}
		}
		else
		if(k10==ENTER)//if the ENTER key is pressed
		{
			if(emt==235)//if EXIT is selected
			{
				cleardevice();
				setcolor(8);
				settextstyle(3,0,4);
				outtextxy(100,100,"Do You Really Want To Quit?");
				setcolor(2);
				outtextxy(200,200,"[Y]es");
				setcolor(4);
				outtextxy(400,200,"[N]o");
				while(bioskey(1)==0)
				{
					k11=bioskey(0);
					if(k11==Y)
					{
						cleardevice();
						setcolor(8);
						settextstyle(3,0,4);
						outtextxy(230,200,"Good Bye...");
						getch();

						exit(1);
					}
					else
					if(k11==N)
					{
						escapemenu();
					}
				}
			}
			else
			if(emt==185)//if GO TO MAIN MENU is selected
			{
				cleardevice();
				setcolor(8);
				settextstyle(3,0,4);
				outtextxy(280,120,"Sure ?");
				setcolor(2);
				outtextxy(200,200,"[Y]es");
				setcolor(4);
				outtextxy(400,200,"[N]o");
				while(bioskey(1)==0)
				{
					k12=bioskey(0);
					if(k12==Y)
					{
						clrscr();
						cleardevice();
						mainmenu();
					}
					else
					if(k12==N)
					{
						escapemenu();
					}
				}
			}
			else
			if(emt==135)//if SAVE is selected
			{
				save();
				escapemenu();
			}
			else
			if(emt==85)//if BACK is selected
			{
				cleardevice();
				setbkcolor(0);
				setcolor(15);
				int kk;
				int jj;
				char c;
				kk=0;
				jj=y-50;
				fstream f1;
				f1.open("COLOURS",ios::in);
				f1>>c;
				while(!f1.eof())
				{
					if(c=='*')
					{
						kk=0;jj=jj+1;gotoxy(kk,jj);
					}
					else if(c=='a')
					{
						putpixel(kk,jj,0);kk++;
					}
					else if(c=='b')
					{
						putpixel(kk,jj,1);kk++;
					}
					else if(c=='c')
					{
						putpixel(kk,jj,2);kk++;
					}
					else if(c=='d')
					{
						putpixel(kk,jj,3);kk++;
					}
					else if(c=='e')
					{
						putpixel(kk,jj,4);kk++;
					}
					else if(c=='f')
					{
						putpixel(kk,jj,5);kk++;
					}
					else if(c=='g')
					{
						putpixel(kk,jj,6);kk++;
					}
					else if(c=='h')
					{
						putpixel(kk,jj,7);kk++;
					}
					else if(c=='i')
					{
						putpixel(kk,jj,8);kk++;
					}
					else if(c=='j')
					{
						putpixel(kk,jj,9);kk++;
					}
					else if(c=='k')
					{
						putpixel(kk,jj,10);kk++;
					}
					else if(c=='l')
					{
						putpixel(kk,jj,11);kk++;
					}
					else if(c=='m')
					{
						putpixel(kk,jj,12);kk++;
					}
					else if(c=='n')
					{
						putpixel(kk,jj,13);kk++;
					}
					else if(c=='o')
					{
						putpixel(kk,jj,14);kk++;
					}
					else if(c=='p')
					{
						putpixel(kk,jj,15);kk++;
					}
					f1>>c;
				}
				f1.close();
				line(8*25,y-50,8*25,y);
				//drawing area
				rectangle(x,0,8*25+5,y);
				//tools area
				rectangle(0,0,6*25,2*a);
				for(int j=a;j<=2*a;j=j+a)
				{
					line(0,j,6*25,j);
				}
				for(int jj1=0;jj1<4*b;jj1=jj1+b)
				{
					line(jj1,0,jj1,2*a);
				}
				settextstyle(3,0,0);
				outtextxy(20,0,"P");
				outtextxy(70,0,"L");
				outtextxy(120,0,"R");
				outtextxy(10,a,"B1");
				outtextxy(60,a,"B2");
				outtextxy(120,a,"E");
				//options area
				rectangle(8*25,(y-55)/2+2-120,0,y-55-120);
				setfillstyle(1,8);
				floodfill(20,y/2-20-120,15);
				settextstyle(3,0,1);
				setcolor(15);
				outtextxy(15,y-55-120+10+20-5,"Click 'E' To Erase");
				outtextxy(50,y-55-120+10+30+10-5,"Everything");

				setcolor(15);
				settextstyle(3,0,1);
				outtextxy(20,getmaxy()-90,"CurrentColor");
				setcolor(color);
				setfillstyle(1,color);
				bar(140,getmaxy()-85,160,getmaxy()-65);
				setcolor(15);
				rectangle(140,getmaxy()-85,160,getmaxy()-65);
				setcolor(color);
				kk=8*25+5;
				jj=0;
				fstream f01;
				f01.open("ESCIMG",ios::in);
				f01>>c;
				while(!f01.eof())
				{
					if(c=='*')
					{
						kk=8*25+5;jj=jj+1;gotoxy(kk,jj);
					}
					else if(c=='a')
					{
						putpixel(kk,jj,0);kk++;
					}
					else if(c=='b')
					{
						putpixel(kk,jj,1);kk++;
					}
					else if(c=='c')
					{
						putpixel(kk,jj,2);kk++;
					}
					else if(c=='d')
					{
						putpixel(kk,jj,3);kk++;
					}
					else if(c=='e')
					{
						putpixel(kk,jj,4);kk++;
					}
					else if(c=='f')
					{
						putpixel(kk,jj,5);kk++;
					}
					else if(c=='g')
					{
						putpixel(kk,jj,6);kk++;
					}
					else if(c=='h')
					{
						putpixel(kk,jj,7);kk++;
					}
					else if(c=='i')
					{
						putpixel(kk,jj,8);kk++;
					}
					else if(c=='j')
					{
						putpixel(kk,jj,9);kk++;
					}
					else if(c=='k')
					{
						putpixel(kk,jj,10);kk++;
					}
					else if(c=='l')
					{
						putpixel(kk,jj,11);kk++;
					}
					else if(c=='m')
					{
						putpixel(kk,jj,12);kk++;
					}
					else if(c=='n')
					{
						putpixel(kk,jj,13);kk++;
					}
					else if(c=='o')
					{
						putpixel(kk,jj,14);kk++;
					}
					else if(c=='p')
					{
						putpixel(kk,jj,15);kk++;
					}
					f01>>c;
				}
				f01.close();
				getch();
				key();
			}
		}
	}
}
void DRAWING_UTILITY::save()
{
	char name[5];
	cleardevice();
	settextstyle(3,0,1);
	cout<<endl<<endl<<endl<<endl<<endl<<endl;
	cout<<"                                        ";
	outtextxy(30,217,"Enter The Save Name Please : ");
	gets(name);
	fstream f;
	f.open("imagenames",ios::app);
	f<<name<<endl;
	f.close();
	Saving();
	char ch;
	fstream f1;
	f1.open(name,ios::out);
	fstream e;
	e.open("ESCIMG",ios::in);
	e>>ch;
	while(!e.eof())
	{
		f1<<ch;
		e>>ch;
	}
	f1.close();
	e.close();
}
void DRAWING_UTILITY::Rectangle(int color,int dordf)
{
	if(dordf==1)
	{
		int x,y,cl,aa,bb,xx,yy;
		int xx1,yy1,ar=0,c,p=1;
		aa=getmaxx()/2+100;
		bb=getmaxy()/2;
		setposi(aa,bb);
		callmouse();
		restrictmouseptr((8*25)+5+1,0+1,getmaxx()-1,getmaxy()-1);
		do
		{
			mouseposi(x,y,cl);
			if(cl==1)
			{
				if(ar==0)
				{
					xx1=x;
					yy1=y;
					ar=1;
				}
				else if(ar==1&&c==0)
				{
					if(p)
					{
						setcolor(color);
						setfillstyle(1,color);
						bar(xx1,yy1,x,y);
					}
					ar=0;p=!(p);
				}
			}
			xx=x;
			yy=y;
			c=cl;
			gotoxy(10,9);
		}while(!kbhit());
		getch();
		mousehide();
		key();
	}
	else
	{
		int x,y,cl,aa,bb,xx,yy;
		int xx1,yy1,ar=0,c,p=1;
		aa=getmaxx()/2+100;
		bb=getmaxy()/2;
		setposi(aa,bb);
		callmouse();
		restrictmouseptr((8*25)+5+1,0+1,getmaxx()-1,getmaxy()-1);
		do
		{
			mouseposi(x,y,cl);
			if(cl==1)
			{
				if(ar==0)
				{
					xx1=x;
					yy1=y;
					ar=1;
				}
				else if(ar==1&&c==0)
				{
					if(p)
					{
						setcolor(color);
						rectangle(xx1,yy1,x,y);
					}
					ar=0;p=!(p);
				}
			}
			xx=x;
			yy=y;
			c=cl;
			gotoxy(10,9);
		}while(!kbhit());
		getch();
		mousehide();
		key();
	}
}
void DRAWING_UTILITY::Line(int color,int style,int t)
{
	if(t==1)
	{
		if(style==1)
		{
			setlinestyle(0,1,1);
		}
		else
		{
			setlinestyle(DOTTED_LINE,1,1);
		}
	}
	else
	{
		if(style==1)
		{
			setlinestyle(0,1,THICK_WIDTH);
		}
		else
		{
			setlinestyle(DOTTED_LINE,1,THICK_WIDTH);
		}
	}
	int x,y,cl,aa,bb,xx,yy;
	int xx1,yy1,ar=0,c,p=1;
	aa=getmaxx()/2+100;
	bb=getmaxy()/2;
	setposi(aa,bb);
	callmouse();
	restrictmouseptr((8*25)+5+1,0+1,getmaxx()-1,getmaxy()-1);
	do
	{
		mouseposi(x,y,cl);
		if(cl==1)
		{
			if(ar==0)
			{
				xx1=x;
				yy1=y;
				ar=1;
			}
			else if(ar==1&&c==0)
			{
				if(p)
				{
					setcolor(color);
					line(xx1,yy1,x,y);
				}
				ar=0;p=!(p);
			}
		}
		xx=x;
		yy=y;
		c=cl;
		gotoxy(10,9);
	}while(!kbhit());
	getch();
	mousehide();
	key();
}
void DRAWING_UTILITY::B1(int color,int oort)
{
	if(oort==1)
	{
		int x,y,cl,aa,bb,xx,yy;
		int xx1,yy1,ar=0,c,p=1;
		aa=getmaxx()/2+100;
		bb=getmaxy()/2;
		setposi(aa,bb);
		callmouse();
		restrictmouseptr((8*25)+5+1+20+4,0+1+20+4,getmaxx()-3,getmaxy()-3);
		do
		{
			mouseposi(x,y,cl);
			if(cl==1)
			{
				setcolor(color);
				setfillstyle(1,color);
				fillellipse(x-11,y-11,12,12);
			}
			xx=x;
			yy=y;
			c=cl;
			gotoxy(10,9);
		}while(!kbhit());
		getch();
		mousehide();
		key();
	}
	else
	{
		int x,y,cl,aa,bb,xx,yy;
		int xx1,yy1,ar=0,c,p=1;
		aa=getmaxx()/2+100;
		bb=getmaxy()/2;
		setposi(aa,bb);
		callmouse();
		restrictmouseptr((8*25)+5+1+12+2+4+1,0+1+12+2+4+1,getmaxx()+2,getmaxy()+2);
		do
		{
			mouseposi(x,y,cl);
			if(cl==1)
			{
				setcolor(color);
				setfillstyle(1,color);
				fillellipse(x-11,y-11,7,7);
			}
			xx=x;
			yy=y;
			c=cl;
			gotoxy(10,9);
		}while(!kbhit());
		getch();
		mousehide();
		key();
	}
}
void DRAWING_UTILITY::B2(int color,int oort)
{
	if(oort==1)
	{
		int x,y,cl,aa,bb,xx,yy;
		int xx1,yy1,ar=0,c,p=1;
		aa=getmaxx()/2+100;
		bb=getmaxy()/2;
		setposi(aa,bb);
		callmouse();
		restrictmouseptr((8*25)+5+1+20+3,0+1+20+3,getmaxx()-1,getmaxy()-1);
		do
		{
			mouseposi(x,y,cl);
			if(cl==1)
			{
				setcolor(color);
				setfillstyle(1,color);
				bar(10+x-12,10+y-12,x-10-12,y-10-12);
			}
			xx=x;
			yy=y;
			c=cl;
			gotoxy(10,9);
		}while(!kbhit());
		getch();
		mousehide();
		key();
	}
	else
	{
		int x,y,cl,aa,bb,xx,yy;
		int xx1,yy1,ar=0,c,p=1;
		aa=getmaxx()/2+100;
		bb=getmaxy()/2;
		setposi(aa,bb);
		callmouse();
		restrictmouseptr((8*25)+5+1+10+5,0+1+10+5,getmaxx()+1,getmaxy()+1);
		do
		{
			mouseposi(x,y,cl);
			if(cl==1)
			{
				setcolor(color);
				setfillstyle(1,color);
				bar(5+x-9,5+y-9,x-5-9,y-5-9);
			}
			xx=x;
			yy=y;
			c=cl;
			gotoxy(10,9);
		}while(!kbhit());
		getch();
		mousehide();
		key();
	}
}
int main()
{

	DRAWING_UTILITY d;
	GAME g;
	initiation();

	again:
	cleardevice();
	settextstyle(4,0,7);
	setbkcolor(15);
	setcolor(1);
	outtextxy(150,70,"[P]lay");
	setcolor(2);
	outtextxy(200,170,"[D]raw");
	setcolor(4);
	outtextxy(300,270,"[E]xit");
	int k13,k14;
	while(bioskey(1)==0)
	{
		k13=bioskey(0);
		if(k13==EKEY)//if the E is pressed
		{
			cleardevice();
			setcolor(8);
			settextstyle(3,0,4);
			outtextxy(280,120,"Sure ?");
			setcolor(2);
			outtextxy(200,200,"[Y]es");
			setcolor(4);
			outtextxy(400,200,"[N]o");
			while(bioskey(1)==0)
			{
				k14=bioskey(0);
				if(k14==Y)
				{
					exit(1);
				}
				else
				if(k14==N)
				{
					goto again;
				}
			}
		}
		else
		if(k13==DKEY)//if the D is pressed
		{
			Loading();
			d.mainmenu();
			goto go;
		}
		else
		if(k13==PKEY)//if the P is pressed
		{
			Loading();
			g.mainmenu();
			goto go;
		}
	}
	go:
	closegraph();
	return 0;
}