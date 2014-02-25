// blaws, 5/23/13

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

// CHANGE THIS TO THE LOCATION OF YOUR PICTURE DIRECTORY
#define PIC_DIRECTORY "/Users/blaws/Pictures/Backgrounds"

#define LINE_WIDTH 5
#define LINE_HEIGHT 50

void drawLine(int* image, int imageWidth, int imageHeight, int color[3], int x, int y, int w, int h, double theta){
  double j;
  int r,k;
  for(r=0;abs(r*sin(theta))<h;++r){
    for(j=0;j<w;j+=.25){
      if(x+r*cos(theta)+j*sin(theta)>=0 && y-r*sin(theta)+j*cos(theta)>=0 && x+r*cos(theta)+j*sin(theta)<imageWidth && y-r*sin(theta)+j*cos(theta)<imageHeight){
        for(k=0;k<3;++k){
          image[3*(int)(x+r*cos(theta)+j*sin(theta)) + 3*imageWidth*(int)(y-r*sin(theta)+j*cos(theta)) + k] = color[k];
        }
      }
      else{
        //printf("out of bounds\n");
        //return;
      }
    }
  }
}

void drawArc(int* image, int imageWidth, int imageHeight, int color[3], int x, int y, int endR, double startTheta, double endTheta){
  int r,k;
  double theta;
  for(r=endR-LINE_WIDTH;r<endR;++r){
    for(theta=startTheta;theta<=endTheta;theta+=.01){
      if(x+r*cos(theta)>=0 && y-r*sin(theta)>=0 && x+r*cos(theta)<imageWidth && y-r*sin(theta)<imageHeight){
        for(k=0;k<3;++k){
          image[3*(int)(x+r*cos(theta)) + 3*imageWidth*(int)(y-r*sin(theta)) + k] = color[k];
        }
      }
      else{
        //printf("out of bounds\n");
        //return;
      }
    }
  }
}

void addStringToImage(char* string, int* image, int imageWidth, int imageHeight, int color[3], int xi, int y){
  if(!string || !image) return;
  int i,x=xi;
  for(i=0;string[i];++i){
    if(x+LINE_HEIGHT/2>imageWidth && string[i]!=' ' && string[i]!='\t' && string[i]!='\n'){  // add hypen and move to next line
      drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT/2, LINE_HEIGHT/3, LINE_WIDTH, M_PI/2);
      x = xi+LINE_HEIGHT/2;
      y += LINE_HEIGHT*1.5;
    }
    switch(string[i]){
      case 'a':
        drawArc(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/4, y+3*LINE_HEIGHT/4+LINE_WIDTH/2, LINE_HEIGHT/4, 0, 2*M_PI);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/2-LINE_WIDTH, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT/2, M_PI/2);
        x += LINE_HEIGHT/2+LINE_WIDTH;
        break;
      case 'A':
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT, 5*M_PI/12);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_HEIGHT*cos(5*M_PI/12)+LINE_WIDTH, y, LINE_WIDTH, LINE_HEIGHT, -5*M_PI/12);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_HEIGHT*cos(5*M_PI/12)/2, y+2*LINE_HEIGHT/3, LINE_HEIGHT/3, LINE_WIDTH, M_PI/2);
        x += LINE_HEIGHT/2+LINE_WIDTH*2;
        break;
      case 'b':
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT, M_PI/2);
        drawArc(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/4, y+3*LINE_HEIGHT/4+LINE_WIDTH/2, LINE_HEIGHT/4, 0, 2*M_PI);
        x += LINE_HEIGHT/2+LINE_WIDTH/2;
        break;
      case 'B':
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT, M_PI/2);
        drawArc(image, imageWidth, imageHeight, color, x+LINE_WIDTH, y+LINE_HEIGHT/4+LINE_WIDTH/2, LINE_HEIGHT/4+LINE_WIDTH/2, -M_PI/2, M_PI/2);
        drawArc(image, imageWidth, imageHeight, color, x+LINE_WIDTH, y+3*LINE_HEIGHT/4, LINE_HEIGHT/4+LINE_WIDTH/2, -M_PI/2, M_PI/2);
        x += LINE_HEIGHT/2-LINE_WIDTH;
        break;
      case 'c':
        drawArc(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/4, y+3*LINE_HEIGHT/4+LINE_WIDTH/2, LINE_HEIGHT/4, M_PI/4, 7*M_PI/4);
        x += LINE_HEIGHT/2;
        break;
      case 'C':
        drawArc(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/2, y+LINE_HEIGHT/2, LINE_HEIGHT/2, M_PI/4, 7*M_PI/4);
        x += LINE_HEIGHT-LINE_WIDTH;
        break;
      case 'd':
        drawLine(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/2-LINE_WIDTH, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT, M_PI/2);
        drawArc(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/4, y+3*LINE_HEIGHT/4+LINE_WIDTH/2, LINE_HEIGHT/4, 0, 2*M_PI);
        x += LINE_HEIGHT/2+LINE_WIDTH;
        break;
      case 'D':
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT, M_PI/2);
        drawArc(image, imageWidth, imageHeight, color, x+LINE_WIDTH/2, y+LINE_HEIGHT/2, LINE_HEIGHT/2+LINE_WIDTH/2, -M_PI/2, M_PI/2);
        x += LINE_HEIGHT/2+LINE_WIDTH;
        break;
      case 'e':
        drawArc(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/4, y+3*LINE_HEIGHT/4+LINE_WIDTH/2, LINE_HEIGHT/4, 0, 7*M_PI/4);
        drawLine(image, imageWidth, imageHeight, color, x, y+3*LINE_HEIGHT/4+LINE_WIDTH/2, LINE_HEIGHT/2-LINE_WIDTH, LINE_WIDTH, M_PI/2);
        x += LINE_HEIGHT/2+LINE_WIDTH;
        break;
      case 'E':
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT, M_PI/2);
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT, LINE_HEIGHT/2, LINE_WIDTH, M_PI/2);
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT/2, LINE_HEIGHT/3, LINE_WIDTH, M_PI/2);
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_WIDTH, LINE_HEIGHT/2, LINE_WIDTH, M_PI/2);
        x += LINE_HEIGHT/2+LINE_WIDTH;
        break;
      case 'f':
        drawLine(image, imageWidth, imageHeight, color, x+LINE_WIDTH/2, y+LINE_HEIGHT, LINE_WIDTH, 3*LINE_HEIGHT/4, M_PI/2);
        drawArc(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/4, y+LINE_HEIGHT/4+LINE_WIDTH/2, LINE_HEIGHT/4-LINE_WIDTH/2, 0, M_PI);
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT/2, LINE_HEIGHT/3, LINE_WIDTH, M_PI/2);
        x += LINE_HEIGHT/2;
        break;
      case 'F':
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT, M_PI/2);
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT/2, LINE_HEIGHT/3, LINE_WIDTH, M_PI/2);
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_WIDTH, LINE_HEIGHT/2, LINE_WIDTH, M_PI/2);
        x += LINE_HEIGHT/2+LINE_WIDTH;
        break;
      case 'g':
        drawArc(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/4, y+3*LINE_HEIGHT/4+LINE_WIDTH/2, LINE_HEIGHT/4, 0, 2*M_PI);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/2-LINE_WIDTH, y+9*LINE_HEIGHT/8, LINE_WIDTH, 5*LINE_HEIGHT/8, M_PI/2);
        drawArc(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/4+LINE_WIDTH/2, y+9*LINE_HEIGHT/8, LINE_HEIGHT/4, M_PI, 2*M_PI);
        x += LINE_HEIGHT/2+LINE_WIDTH;
        break;
      case 'G':
        drawArc(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/2, y+LINE_HEIGHT/2, LINE_HEIGHT/2, M_PI/4, 2*M_PI);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/2, y+LINE_HEIGHT/2, LINE_HEIGHT/2, LINE_WIDTH, M_PI/2);
        x += LINE_HEIGHT+LINE_WIDTH/2;
        break;
      case 'h':
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT, M_PI/2);
        drawArc(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/4, y+3*LINE_HEIGHT/4, LINE_HEIGHT/4, 0, M_PI);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/2-3*LINE_WIDTH/2, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT/4+LINE_WIDTH/2, M_PI/2);
        x += LINE_HEIGHT/2+LINE_WIDTH;
        break;
      case 'H':
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT, M_PI/2);
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT/2, LINE_HEIGHT/2, LINE_WIDTH, M_PI/2);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/2, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT, M_PI/2);
        x += LINE_HEIGHT/2+LINE_WIDTH*2;
        break;
      case 'i':
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT/2-LINE_WIDTH, LINE_WIDTH, LINE_WIDTH, M_PI/2);
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT/2, M_PI/2);
        x += 2*LINE_WIDTH;
        break;
      case 'I':
        drawLine(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/4-LINE_WIDTH/2, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT, M_PI/2);
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT, LINE_HEIGHT/2, LINE_WIDTH, M_PI/2);
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_WIDTH, LINE_HEIGHT/2, LINE_WIDTH, M_PI/2);
        x += LINE_HEIGHT/2+LINE_WIDTH;
        break;
      case 'j':
        drawLine(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/3-LINE_WIDTH, y+LINE_HEIGHT/2-LINE_WIDTH, LINE_WIDTH, LINE_WIDTH, M_PI/2);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/3-LINE_WIDTH, y+9*LINE_HEIGHT/8, LINE_WIDTH, 5*LINE_HEIGHT/8, M_PI/2);
        drawArc(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/12, y+9*LINE_HEIGHT/8, LINE_HEIGHT/4, M_PI, 2*M_PI);
        x += LINE_HEIGHT/3+LINE_WIDTH;
        break;
      case 'J':
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_WIDTH, LINE_HEIGHT/2, LINE_WIDTH, M_PI/2);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/2-LINE_WIDTH, y+3*LINE_HEIGHT/4, LINE_WIDTH, 3*LINE_HEIGHT/4, M_PI/2);
        drawArc(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/4, y+3*LINE_HEIGHT/4, LINE_HEIGHT/4+LINE_WIDTH/2, M_PI, 2*M_PI);
        x += LINE_HEIGHT/2+LINE_WIDTH;
        break;
      case 'k':
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT, M_PI/2);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_WIDTH, y+3*LINE_HEIGHT/4-LINE_WIDTH, LINE_WIDTH, LINE_HEIGHT/4-LINE_WIDTH/2, M_PI/4);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_WIDTH, y+3*LINE_HEIGHT/4-LINE_WIDTH, LINE_WIDTH, LINE_HEIGHT/4+LINE_WIDTH/2, -M_PI/4);
        x += LINE_HEIGHT/2;
        break;
      case 'K':
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT, M_PI/2);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_WIDTH, y+LINE_HEIGHT/2-LINE_WIDTH/2, LINE_WIDTH, LINE_HEIGHT/2-LINE_WIDTH, M_PI/4);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_WIDTH, y+LINE_HEIGHT/2-LINE_WIDTH/2, LINE_WIDTH, LINE_HEIGHT/2-LINE_WIDTH/2, -M_PI/4);
        x += LINE_HEIGHT/2+LINE_WIDTH*2;
        break;
      case 'l':
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT, M_PI/2);
        x += LINE_WIDTH*2;
        break;
      case 'L':
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT, M_PI/2);
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT, LINE_HEIGHT/2, LINE_WIDTH, M_PI/2);
        x += LINE_HEIGHT/2+LINE_WIDTH;
        break;
      case 'm':
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT/2, M_PI/2);
        drawArc(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/5, y+3*LINE_HEIGHT/4, LINE_HEIGHT/5, 0, M_PI);
        drawLine(image, imageWidth, imageHeight, color, x+2*LINE_HEIGHT/5-LINE_WIDTH, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT/4+LINE_WIDTH, M_PI/2);
        drawArc(image, imageWidth, imageHeight, color, x+3*LINE_HEIGHT/5-LINE_WIDTH, y+3*LINE_HEIGHT/4, LINE_HEIGHT/5, 0, M_PI);
        drawLine(image, imageWidth, imageHeight, color, x+3*LINE_HEIGHT/5, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT/4+LINE_WIDTH, M_PI/2);
        x += 4*LINE_HEIGHT/5;
        break;
      case 'M':
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT, M_PI/2);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_WIDTH, y+LINE_WIDTH/2, LINE_WIDTH, LINE_HEIGHT/2-LINE_WIDTH, -M_PI/3);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/2-5*LINE_WIDTH/2, y+LINE_HEIGHT/2, LINE_WIDTH, LINE_HEIGHT/2-LINE_WIDTH, M_PI/3);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/2, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT, M_PI/2);
        x += LINE_HEIGHT/2+LINE_WIDTH*2;
        break;
      case 'n':
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT/2, M_PI/2);
        drawArc(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/5, y+3*LINE_HEIGHT/4, LINE_HEIGHT/5, 0, M_PI);
        drawLine(image, imageWidth, imageHeight, color, x+2*LINE_HEIGHT/5-LINE_WIDTH, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT/4+LINE_WIDTH, M_PI/2);
        x += LINE_HEIGHT/2;
        break;
      case 'N':
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT, M_PI/2);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_WIDTH, y+LINE_WIDTH/2, LINE_WIDTH, LINE_HEIGHT-LINE_WIDTH, -M_PI/3);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/2, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT, M_PI/2);
        x += LINE_HEIGHT/2+LINE_WIDTH*2;
        break;
      case 'o':
        drawArc(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/4, y+3*LINE_HEIGHT/4, LINE_HEIGHT/4, 0, 2*M_PI);
        x += LINE_HEIGHT/2+LINE_WIDTH/2;
        break;
      case 'O':
        drawArc(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/2, y+LINE_HEIGHT/2, LINE_HEIGHT/2, 0, 2*M_PI);
        x += LINE_HEIGHT+LINE_WIDTH/2;
        break;
      case 'p':
        drawLine(image, imageWidth, imageHeight, color, x, y+11*LINE_HEIGHT/8, LINE_WIDTH, 7*LINE_HEIGHT/8, M_PI/2);
        drawArc(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/4, y+3*LINE_HEIGHT/4+LINE_WIDTH/2, LINE_HEIGHT/4, 0, 2*M_PI);
        x += LINE_HEIGHT/2+LINE_WIDTH/2;
        break;
      case 'P':
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT, M_PI/2);
        drawArc(image, imageWidth, imageHeight, color, x+LINE_WIDTH, y+LINE_HEIGHT/4+LINE_WIDTH/2, LINE_HEIGHT/4+LINE_WIDTH/2, -M_PI/2, M_PI/2);
        x += LINE_HEIGHT/2-LINE_WIDTH;
        break;
      case 'q':
        drawArc(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/4, y+3*LINE_HEIGHT/4+LINE_WIDTH/2, LINE_HEIGHT/4, 0, 2*M_PI);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/2-LINE_WIDTH, y+9*LINE_HEIGHT/8, LINE_WIDTH, 5*LINE_HEIGHT/8, M_PI/2);
        drawArc(image, imageWidth, imageHeight, color, x+3*LINE_HEIGHT/4-LINE_WIDTH, y+9*LINE_HEIGHT/8, LINE_HEIGHT/4, M_PI, 3*M_PI/2);
        x += LINE_HEIGHT/2+LINE_WIDTH;
        break;
      case 'Q':
        drawArc(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/2, y+LINE_HEIGHT/2, LINE_HEIGHT/2, 0, 2*M_PI);
        drawLine(image, imageWidth, imageHeight, color, x+2*LINE_HEIGHT/3, y+2*LINE_HEIGHT/3, LINE_WIDTH, LINE_HEIGHT/3, -M_PI/4);
        x += LINE_HEIGHT+LINE_WIDTH/2;
        break;
      case 'r':
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT/2, M_PI/2);
        drawArc(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/4, y+3*LINE_HEIGHT/4+LINE_WIDTH/2, LINE_HEIGHT/4, M_PI/5, M_PI);
        x += LINE_HEIGHT/2;
        break;
      case 'R':
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT, M_PI/2);
        drawArc(image, imageWidth, imageHeight, color, x+LINE_WIDTH, y+LINE_HEIGHT/4+LINE_WIDTH/2, LINE_HEIGHT/4+LINE_WIDTH/2, -M_PI/2, M_PI/2);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/4, y+LINE_HEIGHT/2, LINE_WIDTH, LINE_HEIGHT/2, -5*M_PI/12);
        x += LINE_HEIGHT/2-LINE_WIDTH;
        break;
      case 's':
        drawArc(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/8+LINE_WIDTH/2, y+3*LINE_HEIGHT/6+3*LINE_WIDTH/2, LINE_HEIGHT/6, 0, 3*M_PI/2);
        drawArc(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/8+LINE_WIDTH/2, y+5*LINE_HEIGHT/6+LINE_WIDTH/4, LINE_HEIGHT/6+LINE_WIDTH/4, -M_PI, M_PI/2);
        x += LINE_HEIGHT/3+LINE_WIDTH/2;
        break;
      case 'S':
        drawArc(image,imageWidth, imageHeight, color, x+LINE_HEIGHT/4+LINE_WIDTH/2, y+LINE_HEIGHT/4+3*LINE_WIDTH/4, LINE_HEIGHT/4+LINE_WIDTH/2, 0, 3*M_PI/2);
        drawArc(image,imageWidth, imageHeight, color, x+LINE_HEIGHT/4+LINE_WIDTH/2, y+3*LINE_HEIGHT/4, LINE_HEIGHT/4+LINE_WIDTH/2, -M_PI, M_PI/2);
        x += LINE_HEIGHT/2+LINE_WIDTH;
        break;
      case 't':
        drawLine(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/6-LINE_WIDTH/2, y+LINE_HEIGHT, LINE_WIDTH, 3*LINE_HEIGHT/4, M_PI/2);
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT/2, LINE_HEIGHT/3, LINE_WIDTH, M_PI/2);
        x += LINE_HEIGHT/3+LINE_WIDTH;
        break;
      case 'T':
        drawLine(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/4-LINE_WIDTH/2, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT, M_PI/2);
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_WIDTH, LINE_HEIGHT/2, LINE_WIDTH, M_PI/2);
        x += LINE_HEIGHT/2;
        break;
      case 'u':
        drawLine(image, imageWidth, imageHeight, color, x, y+3*LINE_HEIGHT/4+LINE_WIDTH, LINE_WIDTH, LINE_HEIGHT/4+LINE_WIDTH, M_PI/2);
        drawArc(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/4, y+3*LINE_HEIGHT/4+LINE_WIDTH/2, LINE_HEIGHT/4, M_PI, 2*M_PI);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/2-3*LINE_WIDTH/2, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT/2, M_PI/2);
        x += LINE_HEIGHT/2+LINE_WIDTH;
        break;
      case 'U':
        drawLine(image, imageWidth, imageHeight, color, x, y+3*LINE_HEIGHT/4, LINE_WIDTH, 3*LINE_HEIGHT/4, M_PI/2);
        drawArc(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/4+LINE_WIDTH/2, y+3*LINE_HEIGHT/4, LINE_HEIGHT/4+LINE_WIDTH/2, M_PI, 2*M_PI);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/2-LINE_WIDTH/2, y+3*LINE_HEIGHT/4, LINE_WIDTH, 3*LINE_HEIGHT/4, M_PI/2);
        x += LINE_HEIGHT/2+LINE_WIDTH*2;
        break;
      case 'v':
        drawLine(image, imageWidth, imageHeight, color, x+LINE_WIDTH/2, y+LINE_HEIGHT/2, LINE_WIDTH, LINE_HEIGHT/2, -9*M_PI/24);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/2*cos(9*M_PI/24)-LINE_WIDTH/2, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT/2, 9*M_PI/24);
        x += LINE_HEIGHT/2;
        break;
      case 'V':
        drawLine(image, imageWidth, imageHeight, color, x, y, LINE_WIDTH, LINE_HEIGHT, -5*M_PI/12);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_HEIGHT*cos(5*M_PI/12)-LINE_WIDTH, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT, 5*M_PI/12);
        x += LINE_HEIGHT/2+LINE_WIDTH*2;
        break;
      case 'w':
        drawLine(image, imageWidth, imageHeight, color, x+LINE_WIDTH/2, y+LINE_HEIGHT/2, LINE_WIDTH, LINE_HEIGHT/2, -9*M_PI/24);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/2*cos(9*M_PI/24)-LINE_WIDTH/2, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT/2, 9*M_PI/24);
        drawLine(image, imageWidth, imageHeight, color, x+2*LINE_HEIGHT/2*cos(9*M_PI/24)+LINE_WIDTH/2, y+LINE_HEIGHT/2, LINE_WIDTH, LINE_HEIGHT/2, -9*M_PI/24);
        drawLine(image, imageWidth, imageHeight, color, x+3*LINE_HEIGHT/2*cos(9*M_PI/24)-LINE_WIDTH/2, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT/2, 9*M_PI/24);
        x += LINE_HEIGHT;
        break;
      case 'W':
        drawLine(image, imageWidth, imageHeight, color, x, y, LINE_WIDTH, LINE_HEIGHT, -5*M_PI/12);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_HEIGHT*cos(5*M_PI/12)-LINE_WIDTH, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT, 5*M_PI/12);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_HEIGHT*2*cos(5*M_PI/12), y, LINE_WIDTH, LINE_HEIGHT, -5*M_PI/12);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_HEIGHT*3*cos(5*M_PI/12)-LINE_WIDTH, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT, 5*M_PI/12);
        x += LINE_HEIGHT+LINE_WIDTH*2;
        break;
      case 'x':
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT/2, LINE_WIDTH, LINE_HEIGHT/2, -7*M_PI/24);
        drawLine(image, imageWidth, imageHeight, color, x-LINE_WIDTH, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT/2, 7*M_PI/24);
        x += LINE_HEIGHT/2*cos(7*M_PI/24)+LINE_WIDTH;
        break;
      case 'X':
        drawLine(image, imageWidth, imageHeight, color, x, y, LINE_WIDTH, LINE_HEIGHT, -M_PI/3);
        drawLine(image, imageWidth, imageHeight, color, x-LINE_WIDTH, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT, M_PI/3);
        x += LINE_HEIGHT*cos(M_PI/3)+2*LINE_WIDTH;
        break;
      case 'y':
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT/2, LINE_WIDTH, LINE_HEIGHT/2, -M_PI/3);
        drawLine(image, imageWidth, imageHeight, color, x-LINE_WIDTH, y+11*LINE_HEIGHT/8, LINE_WIDTH, 7*LINE_HEIGHT/8, M_PI/3);
        x += LINE_HEIGHT/2+LINE_WIDTH;
        break;
      case 'Y':
        drawLine(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/4, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT/2, M_PI/2);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/4, y+LINE_HEIGHT/2, LINE_WIDTH, LINE_HEIGHT/2, M_PI/3);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/4, y+LINE_HEIGHT/2, LINE_WIDTH, LINE_HEIGHT/2-LINE_WIDTH/2, 2*M_PI/3);
        x += LINE_HEIGHT*cos(M_PI/3)+2*LINE_WIDTH;
        break;
      case 'z':
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT/2, LINE_HEIGHT/2, LINE_WIDTH, M_PI/2);
        drawLine(image, imageWidth, imageHeight, color, x-LINE_WIDTH/2, y+LINE_HEIGHT-LINE_WIDTH/2, LINE_WIDTH, LINE_HEIGHT/2, M_PI/4);
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT, LINE_HEIGHT/2, LINE_WIDTH, M_PI/2);
        x += LINE_HEIGHT/2+LINE_WIDTH;
        break;
      case 'Z':
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_WIDTH, LINE_HEIGHT/2, LINE_WIDTH, M_PI/2);
        drawLine(image, imageWidth, imageHeight, color, x-LINE_WIDTH, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT, M_PI/3);
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT, LINE_HEIGHT/2, LINE_WIDTH, M_PI/2);
        x += LINE_HEIGHT/2+LINE_WIDTH;
        break;
      case '0':
        drawArc(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/4+LINE_WIDTH/2, y+LINE_HEIGHT/4+LINE_WIDTH/2, LINE_HEIGHT/4+LINE_WIDTH/2, 0, M_PI);
        drawLine(image, imageWidth, imageHeight, color, x, y+3*LINE_HEIGHT/4, LINE_WIDTH, LINE_HEIGHT/2, M_PI/2);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/2-LINE_WIDTH/2, y+3*LINE_HEIGHT/4, LINE_WIDTH, LINE_HEIGHT/2, M_PI/2);
        drawArc(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/4+LINE_WIDTH/2, y+3*LINE_HEIGHT/4, LINE_HEIGHT/4+LINE_WIDTH/2, M_PI, 2*M_PI);
        x += LINE_HEIGHT/2+LINE_WIDTH*2;
        break;
      case '1':
        drawLine(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/4-LINE_WIDTH/2, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT, M_PI/2);
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT, LINE_HEIGHT/2, LINE_WIDTH, M_PI/2);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/4, y+LINE_WIDTH, LINE_WIDTH, LINE_HEIGHT/4, 5*M_PI/4);
        x += LINE_HEIGHT/2+LINE_WIDTH;
        break;
      case '2':
        drawArc(image,imageWidth, imageHeight, color, x+LINE_HEIGHT/4+LINE_WIDTH/2, y+LINE_HEIGHT/4+3*LINE_WIDTH/4, LINE_HEIGHT/4+LINE_WIDTH/2, -M_PI/4, M_PI);
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT-LINE_WIDTH, LINE_WIDTH, LINE_HEIGHT/2, 9*M_PI/32);
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT, LINE_HEIGHT/2, LINE_WIDTH, M_PI/2);
        x += LINE_HEIGHT/2+LINE_WIDTH;
        break;
      case '3':
        drawArc(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/4, y+LINE_HEIGHT/4+LINE_WIDTH/2, LINE_HEIGHT/4+LINE_WIDTH/2, -M_PI/2, M_PI);
        drawArc(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/4, y+3*LINE_HEIGHT/4, LINE_HEIGHT/4+LINE_WIDTH/2, -M_PI, M_PI/2);
        x += LINE_HEIGHT/2+LINE_WIDTH;
        break;
      case '4':
        drawLine(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/3-LINE_WIDTH/2, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT, M_PI/2);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/3+LINE_WIDTH/2, y+LINE_WIDTH, LINE_WIDTH, LINE_HEIGHT/2-LINE_WIDTH, 41*M_PI/32);
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT/2, LINE_HEIGHT/2, LINE_WIDTH, M_PI/2);
        x += LINE_HEIGHT/2+LINE_WIDTH;
        break;
      case '5':
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_WIDTH, LINE_HEIGHT/2, LINE_WIDTH, M_PI/2);
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT/2, LINE_WIDTH, LINE_HEIGHT/2, M_PI/2);
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT/2, LINE_HEIGHT/4+LINE_WIDTH, LINE_WIDTH, M_PI/2);
        drawArc(image,imageWidth, imageHeight, color, x+LINE_HEIGHT/4+LINE_WIDTH/2, y+3*LINE_HEIGHT/4, LINE_HEIGHT/3, -M_PI, M_PI/2);
        x += LINE_HEIGHT/2+LINE_WIDTH*2;
        break;
      case '6':
        drawArc(image,imageWidth, imageHeight, color, x+LINE_HEIGHT/4+LINE_WIDTH/2, y+LINE_HEIGHT/4+3*LINE_WIDTH/4, LINE_HEIGHT/4+LINE_WIDTH/2, 0, M_PI);
        drawLine(image, imageWidth, imageHeight, color, x, y+2*LINE_HEIGHT/3, LINE_WIDTH, 7*LINE_HEIGHT/16, M_PI/2);
        drawArc(image,imageWidth, imageHeight, color, x+LINE_HEIGHT/4+LINE_WIDTH/2, y+3*LINE_HEIGHT/4, LINE_HEIGHT/3-LINE_WIDTH/2, 0, 2*M_PI);
        x += LINE_HEIGHT/2+LINE_WIDTH*2;
        break;
      case '7':
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_WIDTH, LINE_HEIGHT/2, LINE_WIDTH, M_PI/2);
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT-LINE_WIDTH, LINE_WIDTH, LINE_HEIGHT-LINE_WIDTH, M_PI/3);
        x += LINE_HEIGHT/2+LINE_WIDTH*2;
        break;
      case '8':
        drawArc(image,imageWidth, imageHeight, color, x+LINE_HEIGHT/4, y+LINE_HEIGHT/4+LINE_WIDTH/2, LINE_HEIGHT/3-LINE_WIDTH/2, 0, 2*M_PI);
        drawArc(image,imageWidth, imageHeight, color, x+LINE_HEIGHT/4, y+3*LINE_HEIGHT/4, LINE_HEIGHT/3-LINE_WIDTH/2, 0, 2*M_PI);
        x += LINE_HEIGHT/2+LINE_WIDTH*2;
        break;
      case '9':
        drawArc(image,imageWidth, imageHeight, color, x+LINE_HEIGHT/4, y+LINE_HEIGHT/4, LINE_HEIGHT/3-LINE_WIDTH/2, 0, 2*M_PI);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/2-LINE_WIDTH, y+3*LINE_HEIGHT/4, LINE_WIDTH, 7*LINE_HEIGHT/16, M_PI/2);
        drawArc(image,imageWidth, imageHeight, color, x+LINE_HEIGHT/4, y+3*LINE_HEIGHT/4, LINE_HEIGHT/4+LINE_WIDTH/2, M_PI, 2*M_PI);
        x += LINE_HEIGHT/2+LINE_WIDTH*2;
        break;
      case '-':
        drawLine(image, imageWidth, imageHeight, color, x, y+2*LINE_HEIGHT/3, LINE_HEIGHT/3, LINE_WIDTH, M_PI/2);
        x += LINE_HEIGHT/3+LINE_WIDTH;
        break;
      case '"':
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT/4, LINE_WIDTH, LINE_HEIGHT/4, M_PI/2);
        drawLine(image, imageWidth, imageHeight, color, x+2*LINE_WIDTH, y+LINE_HEIGHT/4, LINE_WIDTH, LINE_HEIGHT/4, M_PI/2);
        x += 4*LINE_WIDTH;
        break;
      case '\'':
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT/4, LINE_WIDTH, LINE_HEIGHT/4, M_PI/2);
        x += 2*LINE_WIDTH;
        break;
      case '.':
        drawLine(image, imageWidth, imageHeight, color, x+LINE_WIDTH/2, y+LINE_HEIGHT-LINE_WIDTH/2, 3*LINE_WIDTH/2, 3*LINE_WIDTH/2, M_PI/2);
        x += 3*LINE_WIDTH;
        break;
      case ',':
        drawArc(image, imageWidth, imageHeight, color, x-LINE_WIDTH, y+LINE_HEIGHT-LINE_WIDTH/2, 3*LINE_WIDTH, -M_PI/3, 0);
        x += 3*LINE_WIDTH;
        break;
      case ':':
        drawLine(image, imageWidth, imageHeight, color, x+LINE_WIDTH/2, y+LINE_HEIGHT/2+LINE_WIDTH, 3*LINE_WIDTH/2, 3*LINE_WIDTH/2, M_PI/2);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_WIDTH/2, y+LINE_HEIGHT-LINE_WIDTH, 3*LINE_WIDTH/2, 3*LINE_WIDTH/2, M_PI/2);
        x += 3*LINE_WIDTH;
        break;
      case ';':
        drawLine(image, imageWidth, imageHeight, color, x+LINE_WIDTH/2, y+LINE_HEIGHT/2+LINE_WIDTH, 3*LINE_WIDTH/2, 3*LINE_WIDTH/2, M_PI/2);
        drawArc(image, imageWidth, imageHeight, color, x-LINE_WIDTH, y+LINE_HEIGHT-LINE_WIDTH, 3*LINE_WIDTH, -M_PI/3, 0);
        x += 3*LINE_WIDTH;
        break;
      case '!':
        drawLine(image, imageWidth, imageHeight, color, x+LINE_WIDTH/2, y+2*LINE_HEIGHT/3, LINE_WIDTH, 2*LINE_HEIGHT/3, M_PI/2);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_WIDTH/2, y+LINE_HEIGHT-LINE_WIDTH, LINE_WIDTH, LINE_WIDTH, M_PI/2);
        x += 3*LINE_WIDTH;
        break;
      case '?':
        drawArc(image,imageWidth, imageHeight, color, x+LINE_HEIGHT/4+LINE_WIDTH/2, y+LINE_HEIGHT/4+3*LINE_WIDTH/4, LINE_HEIGHT/4+LINE_WIDTH/2, -M_PI/2, M_PI);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/4, y+2*LINE_HEIGHT/3, LINE_WIDTH, LINE_HEIGHT/6+LINE_WIDTH/2, M_PI/2);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/4, y+LINE_HEIGHT-LINE_WIDTH, LINE_WIDTH, LINE_WIDTH, M_PI/2);
        x += LINE_HEIGHT/2+LINE_WIDTH;
        break;
      case '(':
        drawArc(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/4+LINE_WIDTH/2, y+LINE_HEIGHT/4+LINE_WIDTH/2, LINE_HEIGHT/4+LINE_WIDTH/2, M_PI/2, M_PI);
        drawLine(image, imageWidth, imageHeight, color, x, y+3*LINE_HEIGHT/4, LINE_WIDTH, LINE_HEIGHT/2, M_PI/2);
        drawArc(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/4+LINE_WIDTH/2, y+3*LINE_HEIGHT/4, LINE_HEIGHT/4+LINE_WIDTH/2, M_PI, 3*M_PI/2);
        x += LINE_HEIGHT/4+LINE_WIDTH;
	break;
      case ')':
        drawArc(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT/4+LINE_WIDTH/2, LINE_HEIGHT/4+LINE_WIDTH/2, 0, M_PI/2);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_HEIGHT/4-LINE_WIDTH/2, y+3*LINE_HEIGHT/4, LINE_WIDTH, LINE_HEIGHT/2, M_PI/2);
        drawArc(image, imageWidth, imageHeight, color, x, y+3*LINE_HEIGHT/4, LINE_HEIGHT/4+LINE_WIDTH/2, 3*M_PI/2, 2*M_PI);
        x += LINE_HEIGHT/4+LINE_WIDTH;
	break;
      case ' ':
        if(imageWidth-x < LINE_HEIGHT*4){
          x = xi+LINE_HEIGHT/2;
          y += LINE_HEIGHT*1.5;
        }
        else x+=LINE_HEIGHT/2;
        break;
      case '\t':
        if(imageWidth-x < LINE_HEIGHT*8){
          x = xi+LINE_HEIGHT/2;
          y += LINE_HEIGHT*1.5;
        }
        else x+=LINE_HEIGHT*3;
        break;
      case '\n':
        x = xi+LINE_HEIGHT/2;
        y += LINE_HEIGHT*1.5;
        break;
      default:
        drawLine(image, imageWidth, imageHeight, color, x, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT, M_PI/2);
        drawLine(image, imageWidth, imageHeight, color, x+LINE_WIDTH, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT, M_PI/2);
        drawLine(image, imageWidth, imageHeight, color, x+2*LINE_WIDTH, y+LINE_HEIGHT, LINE_WIDTH, LINE_HEIGHT, M_PI/2);
        x += 4*LINE_WIDTH;
    }
  }
}

int main(void){
  srand(time(NULL));
  //int windowW=1280,windowH=800;
  char /*PIC_DIRECTORY[1000],*/ command[1024];
  FILE* file /*= popen("pwd", "r")*/;
  //if(!file){ printf("System command error: pwd\n"); exit(1); }
  //fgets(PIC_DIRECTORY, sizeof(PIC_DIRECTORY), file);
  //pclose(file);
  //sscanf(PIC_DIRECTORY, "%s\n", PIC_DIRECTORY); // get rid of newline
  //printf("%s\n", PIC_DIRECTORY);

  // get list of .bmp files in directory
  sprintf(command, "find %s/*.bmp", PIC_DIRECTORY);
  file = popen(command, "r");
  int i;
  if(!file){ printf("System error: find\n"); exit(1); }
  char* names[1000];
  for(i=0;i<1000;i++) names[i] = malloc(1000*sizeof(char));
  i=0;
  while(fgets(names[i],1000,file)){
    sscanf(names[i],"%s\n",names[i]);  // get rid of newline character
    i++;
  }
  pclose(file);

  // choose image
  if(i==0){
    printf("No .bmp files found in this directory.\n");
    return 1;
  }
  int imageIndex = rand()%i;

  // read bitmap image
  int j,k,width,height,begin,incr;
  int* value = malloc(sizeof(int));
  char* header1 = malloc(100*sizeof(char));
  char* header2 = malloc(100*sizeof(char));
  char* filler = malloc(100*sizeof(char));

  file = fopen(names[imageIndex],"rb");
  if(!file){
    perror("File error 2");
    return 1;
  }
  fread(header1,18,1,file);  // ignore first 18 bytes of .bmp header
  fread(&width,4,1,file);  // get width
  fread(&height,4,1,file);  // get height
  if(height<0){
    begin = 0;
    incr = 1;
  }
  else{
    begin = height-1;
    incr = -1;
  }
  fread(header2,28,1,file);  // ignore rest of .bmp header

  int* colorArray = malloc(width*abs(height)*3*sizeof(int));
  for(i=begin;i>=0&&i<abs(height);i+=incr){
    for(j=0;j<width;j++){
      for(k=2;k>=0;k--){
        fread(value,1,1,file);
        colorArray[i*width*3+j*3+k] = *value;
      }
    }
    while((j++)%4) fread(filler,1,1,file);  // take padding at end of each line
  }
  fclose(file);
  free(value);

  // pick random quote from quotes.txt
  sprintf(command, "%s/quotes.txt", PIC_DIRECTORY);
  file = fopen(command, "r");
  if(!file){ perror("File error"); exit(1); }
  i=0;
  while(fgets(names[i],1000,file)) i++;
  fclose(file);
  int quoteIndex = rand()%i;

  // break quote into lines
  int charsPerLine = (width-LINE_HEIGHT)/(LINE_HEIGHT/2);
  //int currentIndex = 0;
  int quoteLines = strlen(names[quoteIndex])/(charsPerLine) + 2;
  //char quote[quoteLines+1][charsPerLine+10];
  int currentY=abs(height)-LINE_HEIGHT*1.5*(quoteLines);

  /*for(i=0;i<quoteLines;i++){
    j=0;
    while(names[quoteIndex][currentIndex+charsPerLine+j]!=' ' && j<10) j++;
    strcpy(quote[i],&names[quoteIndex][currentIndex]);
    currentIndex += charsPerLine+j;
    quote[i][charsPerLine+j] = '\0';
  }
  if(currentIndex!=strlen(names[quoteIndex])){
    strcpy(quote[i],&names[quoteIndex][currentIndex]);
    quoteLines++;
    currentY -= LINE_HEIGHT*1.5;
  }*/


  // add quote to image
  int color[3];
  for(i=0;i<3;++i) color[i] = rand()%256;

  // test string
  //addStringToImage("AaBbCcDdEeFfGgHhIiJjKkLlMmNn\nNnOoPpQqRrSsTtUuVvWwXxYyZz00\n00112233445566778899!!::;;,,..?\?(())~~", colorArray, width, abs(height), color, LINE_HEIGHT/2, LINE_HEIGHT/2);

  //for(i=0;i<quoteLines;++i){
  addStringToImage(/*quote[i]*/names[quoteIndex], colorArray, width, abs(height), color, LINE_HEIGHT/2, currentY);
    //currentY += LINE_HEIGHT*1.5;
  //}

  // save file with quote
  sprintf(command, "%s/BG.bmp", PIC_DIRECTORY);
  file = fopen(command, "w");
  if(!file){ perror("File error 4"); exit(1); }
  fwrite(header1,18,1,file);
  fwrite(&width,4,1,file);
  fwrite(&height,4,1,file);
  fwrite(header2,28,1,file);
  for(i=0;i<abs(height);i++){
    for(j=0;j<width;j++){
      for(k=2;k>=0;k--){
        fwrite(&colorArray[i*width*3+j*3+k],1,1,file);
      }
    }
    while((j++)%4) fread(filler,1,1,file);  // take padding at end of each line
  }
  fclose(file);

  return 0;
}
