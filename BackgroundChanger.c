// Benjamin Laws, 5/23/13

#include "aquaterm/aquaterm.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <fnmatch.h>

// input passed from GetFiles.c
int main(void){
  srand(time(NULL));
  int windowW=1280,windowH=800;

  // get list of .bmp files in directory
  system("find *.bmp > tmp.txt");
  int i;
  FILE* file = fopen("tmp.txt","r");
  char* names[100];
  for(i=0;i<100;i++) names[i] = malloc(1000*sizeof(char));
  i=0;
  while(fgets(names[i],1000,file)){
    sscanf(names[i],"%s\n",names[i]);  // get rid of newline character
    i++;
  }
  fclose(file);
  system("rm tmp.txt");

  // choose image
  if(i==0){
    printf("No .bmp files found in this directory.\n");
    return 1;
  }
  int imageIndex = rand()%i;

  // read bitmap image
  int j,k,width,height,begin,incr;
  int* value = malloc(sizeof(int));
  char* filler = malloc(100*sizeof(char));

  file = fopen(names[imageIndex],"rb");
  if(!file){
    printf("File error.\n");
    return 1;
  }
  fread(filler,18,1,file);  // ignore first 18 bytes of .bmp header
  fread(&width,4,1,file);  // get width
  fread(&height,4,1,file);  // get height
  if(height<0){
    height*=-1;
    begin = 0;
    incr = 1;
  }
  else{
    begin = height-1;
    incr = -1;
  }
  fread(filler,28,1,file);  // ignore rest of .bmp header

  unsigned char* colorArray = malloc(width*height*3*sizeof(unsigned char));
  for(i=begin;i>=0&&i<height;i+=incr){
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
  free(filler);

  // add bitmap to screen buffer
  aqtInit();
  aqtOpenPlot(1);
  aqtSetPlotSize(windowW,windowH);
  aqtSetPlotTitle("BackgroundChanger");
  aqtAddImageWithBitmap(colorArray,width,height,0,0,windowW,windowH);
  free(colorArray);

  // pick random quote from quotes.txt
  file = fopen("quotes.txt","r");
  i=0;
  while(fgets(names[i],1000,file)) i++;
  fclose(file);
  int quoteIndex = rand()%i;
  // break quote into lines
  int charsPerLine = windowW/20 - 5;
  int quoteLines = strlen(names[quoteIndex])/(charsPerLine+5) + 1;
  for(i=1;i<=quoteLines;i++){
    j=0;
    while(names[quoteIndex+i-1][charsPerLine+j]!=' ') j++;
    strcpy(names[quoteIndex+i],&names[quoteIndex+i-1][charsPerLine+j]);
    names[quoteIndex+i-1][charsPerLine+j] = 0;
  }

  // add quote to screen buffer
  int currentY=50*quoteLines+50;
  aqtSetFontname("Helvetica");
  aqtSetFontsize(40.0);
  aqtSetColor(rand()/(double)RAND_MAX,rand()/(double)RAND_MAX,rand()/(double)RAND_MAX);
  for(i=0;i<quoteLines;i++){
    aqtAddLabel(names[quoteIndex+i],50,currentY,0,AQTAlignLeft);
    currentY -= 50;
  }

  // render and wait
  aqtRenderPlot();
  aqtClosePlot();
  aqtTerminate();

  return 0;
}
