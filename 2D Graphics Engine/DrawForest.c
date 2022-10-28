#include <cr_section_macros.h>
#include <NXP/crp.h>
#include "LPC17xx.h"                        /* LPC17xx definitions */
#include "ssp.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>



/* Be careful with the port number and location number, because

some of the location may not exist in that port. */

#define PORT_NUM 0


uint8_t src_addr[SSP_BUFSIZE];
uint8_t dest_addr[SSP_BUFSIZE];


#define ST7735_TFTWIDTH 127
#define ST7735_TFTHEIGHT 159

#define ST7735_CASET 0x2A
#define ST7735_RASET 0x2B
#define ST7735_RAMWR 0x2C
#define ST7735_SLPOUT 0x11
#define ST7735_DISPON 0x29

#define RED3 0xCD0000
#define GRAY72 0xB7B7B7
#define BLACK 0x000000
#define BLUE  0x058AC0
#define LIGHTBLUE  0x66BBE7
#define GREEN 0x34E601
#define PARROT_GREEN 0x39FF00
#define GREEN1 0x40CA19
#define GREEN2 0x31B80B
#define GREEN3 0x0AAF05
#define DARKGREEN 0x108E0C
#define MAROON 0x800000
#define PURPLE 0x800080
#define DARKRED 0xB0171F
#define BROWN 0xA52A2A
#define RED 0xFF4500
#define WHITE 0xFFFFFF
#define YELLOW 0xFFFF00
#define MAGENTA 0xCD00CD
#define SKY 0x7EC0EE
#define CYAN 0xE0FFFF




#define swap(x, y) {x = x + y; y = x - y; x = x - y ;}


#define pi 3.14
#define alpha pi/6


int HEIGHT = ST7735_TFTHEIGHT;
int WIDTH = ST7735_TFTWIDTH;


void spiwrite(uint8_t c){
 int pnum = 0;
 src_addr[0] = c;
 SSP_SSELToggle( pnum, 0 );
 SSPSend( pnum, (uint8_t *)src_addr, 1 );
 SSP_SSELToggle( pnum, 1 );
}



void writecommand(uint8_t c){
 LPC_GPIO0->FIOCLR |= (0x1<<21);
 spiwrite(c);
}



void writedata(uint8_t c){
 LPC_GPIO0->FIOSET |= (0x1<<21);
 spiwrite(c);
}



void writeword(uint16_t c){
 uint8_t d;
 d = c >> 8;
 writedata(d);
 d = c & 0xFF;
 writedata(d);
}



void write888(uint32_t color, uint32_t repeat){
 uint8_t red, green, blue;
 int i;
 red = (color >> 16);
 green = (color >> 8) & 0xFF;
 blue = color & 0xFF;
 for (i = 0; i< repeat; i++) {
  writedata(red);
  writedata(green);
  writedata(blue);
 }

}



void setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1){
 writecommand(ST7735_CASET);
 writeword(x0);
 writeword(x1);
 writecommand(ST7735_RASET);
 writeword(y0);
 writeword(y1);
}


void fillrect(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint32_t color){
 int16_t i;
 int16_t width, height;
 width = x1-x0+1;
 height = y1-y0+1;
 setAddrWindow(x0,y0,x1,y1);
 writecommand(ST7735_RAMWR);
 write888(color,width*height);
}



void lcddelay(int ms){
 int count = 24000;
 int i;
 for ( i = count*ms; i--; i > 0);
}



void lcd_init(){
 int i;
 printf("Welcome to the Demo of Cmpe 240 2D Vector graphics\n");
 // Set pins P0.16, P0.21, P0.22 as output
 LPC_GPIO0->FIODIR |= (0x1<<16);
 LPC_GPIO0->FIODIR |= (0x1<<21);
 LPC_GPIO0->FIODIR |= (0x1<<22);
 // Hardware Reset Sequence
 LPC_GPIO0->FIOSET |= (0x1<<22);
 lcddelay(500);
 LPC_GPIO0->FIOCLR |= (0x1<<22);
 lcddelay(500);
 LPC_GPIO0->FIOSET |= (0x1<<22);
 lcddelay(500);
 // initialize buffers
 for ( i = 0; i < SSP_BUFSIZE; i++ ){
   src_addr[i] = 0;
   dest_addr[i] = 0;
 }

 // Take LCD display out of sleep mode
 writecommand(ST7735_SLPOUT);
 lcddelay(200);
 // Turn LCD display on
 writecommand(ST7735_DISPON);
 lcddelay(200);
}




void drawPixel(int16_t x, int16_t y, uint32_t color){
 if ((x < 0) || (x >= WIDTH) || (y < 0) || (y >= HEIGHT))
 return;
 setAddrWindow(x, y, x + 1, y + 1);
 writecommand(ST7735_RAMWR);
 write888(color, 1);
}



void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint32_t color){

 int16_t slope = abs(y1 - y0) > abs(x1 - x0);
 if (slope) {
  swap(x0, y0);
  swap(x1, y1);
 }

 if (x0 > x1) {
  swap(x0, x1);
  swap(y0, y1);
 }

 int16_t dx, dy;
 dx = x1 - x0;
 dy = abs(y1 - y0);
 int16_t err = dx / 2;
 int16_t ystep;
 if (y0 < y1) {
  ystep = 1;
 }

 else {
  ystep = -1;
 }

 for (; x0 <= x1; x0++) {
  if (slope) {
   drawPixel(y0, x0, color);
  }

  else {
   drawPixel(x0, y0, color);
  }

  err -= dy;
  if (err < 0) {
   y0 += ystep;
   err += dx;
  }
 }
}



//Physical to virtual
int v2p_x(int16_t x){
	return x+WIDTH/2;
}
int v2p_y(int16_t y){
	return -y+HEIGHT/2;
}



struct Point{
	int16_t x;
	int16_t y;
};

struct Point point_calculation(struct Point p0,struct Point p1,float lambda){
	struct Point p1_p = {0,0};
	p1_p.x = p0.x + lambda * (p1.x - p0.x);
	p1_p.y = p0.y + lambda * (p1.y - p0.y);
	return p1_p;
}


 struct Point draw_branch(struct Point p0,struct Point p1, int angle,int side,float lambda){

 float ang_rad = angle*pi/180;
 int16_t delta_x,delta_y;
 int16_t x_prime,y_prime,x_dbprime,y_dbprime;
 struct Point p_l = {0,0};
 struct Point p_r = {0,0};
 struct Point p1_p = {0,0};
 delta_x = -p1.x;
 delta_y = -p1.y;
 p1_p.x = p1.x + lambda * (p1.x - p0.x);
 p1_p.y = p1.y + lambda * (p1.y - p0.y);
 //Calculate delta
 x_prime = p1_p.x + delta_x;
 y_prime = p1_p.y + delta_y;
 if(side == 0)
 return p1_p;

 else if(side == 1){
	 //Rotation matrix -->left
	 x_dbprime = cos(ang_rad)*x_prime - sin(ang_rad)*y_prime;
	 y_dbprime= sin(ang_rad)*x_prime + cos(ang_rad)*y_prime;
	 //post processing
	 p_l.x= x_dbprime - delta_x;
	 p_l.y = y_dbprime - delta_y;
	 return p_l;
 }

 else if(side == 2){
 //Rotation matrix -->right
	 x_dbprime = cos(ang_rad)*x_prime + sin(ang_rad)*y_prime;
	 y_dbprime = -sin(ang_rad)*x_prime + cos(ang_rad)*y_prime;
	 //post processing
	 p_r.x = x_dbprime - delta_x;
	 p_r.y = y_dbprime - delta_y;
	 return p_r;
  }
}




//Draw Tree Trunk
 int16_t random_range(int16_t min, int16_t max){
 	 int16_t num = (rand() % (max - min + 1)) + min;
 	 return num;
}




 //Draw Tree leaves
void draw_tree(struct Point p0,struct Point p1, int angle,float lambda,int levels,uint32_t color){

	 int16_t x1,y1,x2,y2;
	 int arrLength = 3000;
	 struct Point arr[arrLength][2];
	 arr[0][0] = p0;
	 arr[0][1] = p1;
	 int line = 1;
	 int set = 0;
	 while (set <= pow(3,levels)){
	  //draw right

	 arr[line][0] = arr[set][1];
	 arr[line][1] =
	 draw_branch(arr[set][0], arr[set][1], angle,2,lambda);
	 //calculate physical values.

	 x1 = v2p_x(arr[line][0].x);
	 y1 = v2p_y(arr[line][0].y);
	 x2 = v2p_x(arr[line][1].x);
	 y2 = v2p_y(arr[line][1].y);
	 drawLine(x1, y1, x2, y2,color);
	 line++;
	 //draw straight

	 arr[line][0] = arr[set][1];
	 arr[line][1] =
	 draw_branch(arr[set][0], arr[set][1], angle,0,lambda);
	 //calculate physical values.

	 x1 = v2p_x(arr[line][0].x);
	 y1 = v2p_y(arr[line][0].y);
	 x2 = v2p_x(arr[line][1].x);
	 y2 = v2p_y(arr[line][1].y);
	 drawLine(x1, y1, x2, y2,color);
	 line++;

	 //draw left
	 arr[line][0] = arr[set][1];
	 arr[line][1] =
	 draw_branch(arr[set][0], arr[set][1], angle,1,lambda);
	 //calculate physical values.
	 x1 = v2p_x(arr[line][0].x);
	 y1 = v2p_y(arr[line][0].y);
	 x2 = v2p_x(arr[line][1].x);
	 y2 = v2p_y(arr[line][1].y);
	 drawLine(x1, y1, x2, y2,color);
	 line++;
	 set++;
	 }
 }





 void Draw_Tree_Trunk(){

	int16_t x0,x1,y0,y1,in;
	uint32_t colorList[] = {PARROT_GREEN,DARKGREEN,GREEN,GREEN1,GREEN2,GREEN3};
	int16_t xr=random_range(-WIDTH/2+20,WIDTH/2-20);
	int16_t yr=random_range(-HEIGHT/2,0);

	//Randomize trunk length
	int length = random_range(10,30);

	//Randomize angle
	int ang = random_range(20,30);
	float lambda = 0.8;

	//Define trunk points p0,p1
	struct Point p0 = {xr,yr};
	struct Point p1;
	p1.x = p0.x;
	p1.y = p0.y+length;

	//Calculate physical values.
	x0 = v2p_x(p0.x);
	x1 = v2p_x(p1.x);
	y0 = v2p_y(p0.y);
	y1 = v2p_y(p1.y);

	//Draw trunk
	for (int j = -1; j < 3; j++)
	{
		drawLine(x0+j, y0, x1+j, y1,0x683306);
	}

	//Choose a random color for each set of Tree patterns
	in = rand() % 6;
	draw_tree(p0, p1,ang,lambda,5,colorList[in]);
	lcddelay(100);
 }


// Tree Trunk


//This displays the sky background for tree
void Tree_background(){
	fillrect(0, ST7735_TFTHEIGHT*0.60, ST7735_TFTWIDTH,ST7735_TFTHEIGHT, 0x8BB36E);
	//fillrect(0, 0, ST7735_TFTWIDTH,ST7735_TFTHEIGHT*0.80, LIGHTBLUE);
//	fillrect(0, 0, ST7735_TFTWIDTH,ST7735_TFTHEIGHT*0.70, 0xADDDFC);
//	fillrect(0, 0, ST7735_TFTWIDTH,ST7735_TFTHEIGHT*0.50, 0xBFE5FC);
//	fillrect(0, 0, ST7735_TFTWIDTH,ST7735_TFTHEIGHT*0.40, 0xD2EDFD);
//	fillrect(0, 0, ST7735_TFTWIDTH,ST7735_TFTHEIGHT*0.30, 0xE5F4FE);
//	fillrect(0, 0, ST7735_TFTWIDTH,ST7735_TFTHEIGHT*0.15, 0xF8FCFF);
    fillrect(0,ST7735_TFTHEIGHT*0.85, ST7735_TFTWIDTH,ST7735_TFTHEIGHT, DARKGREEN);
	//fillrect(0,ST7735_TFTHEIGHT*0.95, ST7735_TFTWIDTH,ST7735_TFTHEIGHT, MAROON);
}

////////////////////////////////////////////////////////////////////////////////////////////

int main (void){
	uint32_t pnum = PORT_NUM;

	if ( pnum == 0)
	SSP0Init();
	else
	puts("Port number is not correct");


	lcd_init();
	fillrect(0, 0, ST7735_TFTWIDTH,ST7735_TFTHEIGHT, 0xFFFFFF);
	Tree_background();
	printf("\nEnter the number trees you want on your screen\n");
		int counter;
		scanf("%d",&counter);
		while(counter--)
		{
			Draw_Tree_Trunk();
		}

return 0;
}

