
#include <cr_section_macros.h>
#include <NXP/crp.h>
#include "LPC17xx.h"
#include "ssp.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>



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

// Define colors
#define GREEN 0x00FF00
#define DARKBLUE 0x000033
#define BLUE 0x000083
#define BLACK 0x00000
#define SKYBLUE 0x0000FF
#define LIGHTBLUE 0x000044
#define RED 0xFF0000
#define MAROON 0xFFF000
#define NEARRED 0xFE0000
#define PINK 0x00F81F
#define MAGENTA 0x00F82F
#define WHITE 0xFFFFFF
#define PURPLE 0xCC33FF
#define YELLOW 0xFFFF00
#define SILVER 0xC0C0C0
#define LIME 0x00FF00
#define ORANGE 0xFFA500
#define ORANGERED 0xFFA800
#define PEACH 0x800000
#define LIGHTGREEN 0x228B22
#define FOREST 0x218B22
#define DARKGREEN 0x006400
#define GREENSHADE1 0X90EE90
#define SEAGREEN 0X2E8B57
#define DARKPINK 0XFF4500
#define GOLD 0XFFD700
#define GRAY 0X808080
#define SHADOW 0X8A795D

#define swap(x, y) {x = x + y; y = x - y; x = x - y ;}

int _height = ST7735_TFTHEIGHT;
int _width = ST7735_TFTWIDTH;


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
 printf("LCD Demo of CmpE 240 Rotating Squares \n");
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
 if ((x < 0) || (x >= _width) || (y < 0) || (y >= _height))
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

/* Draw Squares*/

//Define 2d Point data structure
typedef struct{
	int16_t x;
	int16_t y;
}point_s;



point_s point_calculation(point_s p0, point_s p1,float lambda){
	point_s p = {0};
	p.x = p0.x + lambda * (p1.x - p0.x);
	p.y = p0.y + lambda * (p1.y - p0.y);

	return p;
}




void draw_line_with_points(point_s p0, point_s p1, uint32_t color){
	int16_t x1,y1,x2,y2;
	x1 = p0.x;
	y1 = p0.y;
	x2 = p1.x;
	y2 = p1.y;
	drawLine(x1,y1,x2,y2,color);
}



void draw_one_square(point_s p0, point_s p1, point_s p2, point_s p3, uint32_t color){

	draw_line_with_points(p0,p1,color);
	draw_line_with_points(p1,p2,color);
	draw_line_with_points(p2,p3,color);
	draw_line_with_points(p3,p0,color);
}



void draw_rotating_squares(point_s p0,point_s p1, point_s p2,point_s p3,float lamda,int number_of_rotations_of_each_square){
	uint32_t available_colors[] = {
	        NEARRED,
	        PEACH,
	        LIGHTBLUE,
	        GREEN,
	        DARKBLUE,
	        BLACK,
	        BLUE,
	        SKYBLUE,
	        RED,
	        MAGENTA,
	        WHITE,
	        PURPLE,
	        PINK,
	        DARKPINK,
	        YELLOW,
	        SILVER,
	        LIME,
	        ORANGE,
	        MAROON,
	        FOREST,
	        DARKGREEN,
	        LIGHTGREEN,
	        SEAGREEN,
	        ORANGERED,
	        GOLD,
	        GREENSHADE1
	        };

	time_t t;
			srand((unsigned) time(&t));
			int16_t random_color =rand()%25;

	while(number_of_rotations_of_each_square>0)
	{
		draw_one_square(p0,p1,p2, p3,available_colors[random_color]);

		point_s p0_prime= point_calculation(p0,p1,lamda);
		point_s p1_prime= point_calculation(p1,p2,lamda);
		point_s p2_prime= point_calculation(p2,p3,lamda);
		point_s p3_prime= point_calculation(p3,p0,lamda);

		p0= p0_prime;
		p1= p1_prime;
		p2= p2_prime;
		p3= p3_prime;
		number_of_rotations_of_each_square--;
	}
}



void draw_square_patterns(int number_of_squares,int number_of_rotations_of_each_square){

	int choice;float lamda;
		printf("Enter 1 for default lambda= 0.8 and 2 for user defined lambda= 0.2\n");
		scanf("%d",&choice);
		if(choice==1)
		{
			lamda=0.8;
		}
		else if(choice==2)
		{
			lamda=0.2;
		}
		else
		{
			printf("Invalid choice of lamda\n");
		}

	while(number_of_squares>0){
		time_t t;
		srand((unsigned) time(&t));
		int x_sq,y_sq,len_sq;
		x_sq = rand()%80;
		y_sq = rand()%80;
		len_sq=rand()%90 + 15;
		point_s p0i={x_sq,y_sq};
		point_s p1i={x_sq,y_sq+len_sq};
		point_s p2i={x_sq+len_sq,y_sq+len_sq};
		point_s p3i={x_sq+len_sq,y_sq};

		draw_rotating_squares(p0i,p1i,p2i,p3i,lamda,number_of_rotations_of_each_square);

		number_of_squares--;
	}
}


/*Main Function */
int main (void){
	uint32_t pnum = PORT_NUM;
	if ( pnum == 0)
	SSP0Init();
	else
	puts("Port number is not correct");
	lcd_init();
	fillrect(0, 0, ST7735_TFTWIDTH,ST7735_TFTHEIGHT, BLACK);
	int number_of_squares= 70, number_of_rotations_of_each_square= 7;
    draw_square_patterns(number_of_squares,number_of_rotations_of_each_square);

return 0;

}

