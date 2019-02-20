#include<stdio.h>
#include<stdlib.h>
#include <string.h>

typedef struct {
	unsigned int imageSize;
	unsigned int width;
	unsigned int height;
	unsigned int headerSize;
	unsigned int pixelSize;
	unsigned short numBperP;
	unsigned char *header;
	unsigned char *pixels;
}Bmp;
//------------------------------------------------------------------------------------
Bmp extract(Bmp image,Bmp image1){
	unsigned int a=0,j=0,k=0;
	unsigned short byte_per_pixel=image.numBperP/8;
	unsigned char *newPixels=(unsigned char *)malloc((image.pixelSize+image1.pixelSize)*sizeof(unsigned char));

	for(int i=0;i<=image.height;i++){ 
		for(;j<(i*image.width*byte_per_pixel);j++){
			newPixels[a]=image.pixels[j]; a++;
		}
		for(;k<(i*image1.width*byte_per_pixel);k++){
			newPixels[a]=image1.pixels[k]; a++;
		}
	}
	
	image.pixels=newPixels;
	image.width=image.width+image1.width;
	image.pixelSize=a;
	image.imageSize=(image.headerSize+a);
	return image;
}
//------------------------------------------------------------------------------------
Bmp info(unsigned char *original_name ){
	Bmp myImage;
	FILE *fp;
	fp = fopen(original_name,"rb");
	if(fp==NULL){
		printf("ERROR IN OPENING FILE\n");  
		exit(1);	
	}
	fseek(fp,2,SEEK_SET);
	fread(&(myImage.imageSize),sizeof(int),1,fp);
	fseek(fp,10,SEEK_SET);
	fread(&(myImage.headerSize),sizeof(int),1,fp);
	fseek(fp,18,SEEK_SET);
	fread(&(myImage.width),sizeof(int),1,fp);
	fseek(fp,22,SEEK_SET);
	fread(&(myImage.height),sizeof(int),1,fp);
	fseek(fp,28,SEEK_SET);
	fread(&(myImage.numBperP),2,1,fp);   
	fclose(fp);
	myImage.pixelSize=myImage.imageSize-myImage.headerSize;
	myImage.pixels=(unsigned char *)malloc(myImage.pixelSize*sizeof(unsigned char));
	myImage.header=(unsigned char *)malloc(myImage.headerSize*sizeof(unsigned char));
	return myImage;
}
//------------------------------------------------------------------------------------
void BMPwrite(unsigned char *firstImage,unsigned char *secondImage){

	Bmp Image1=info(firstImage);
	FILE * fp1;
	fp1=fopen(firstImage,"rb");
	if(fp1==NULL){
		printf("ERROR IN OPENING FILE\n");
		exit(1);}	
	fread(Image1.header,Image1.headerSize,1,fp1);
	fseek(fp1,Image1.headerSize,SEEK_SET);
	fread(Image1.pixels,Image1.pixelSize,1,fp1);
	fclose(fp1);

	Bmp Image2=info(secondImage);
	FILE * fp2;
	fp2=fopen(secondImage,"rb");
	if(fp1==NULL){
		printf("ERROR IN OPENING FILE\n");
		exit(1);}	
	fread(Image2.header,Image2.headerSize,1,fp2);
	fseek(fp2,Image2.headerSize,SEEK_SET);
	fread(Image2.pixels,Image2.pixelSize,1,fp2);
	fclose(fp2);
	
	Image1=extract(Image1,Image2);
	FILE *file;
	file = fopen("concat.bmp", "wb");       
	fwrite(Image1.header,Image1.headerSize,1,file);
	fseek(file,Image1.headerSize,SEEK_SET);
	fwrite(Image1.pixels,Image1.pixelSize,1,file); 

	fseek(file,2,SEEK_SET);
	fwrite(&(Image1.imageSize),sizeof(int),1,file);
	fseek(file,18,SEEK_SET);
	fwrite(&(Image1.width),sizeof(int),1,file);
	
	fclose(file);
}
//------------------------------------------------------------------------------------
int main(int argc, char *argv[]){
	BMPwrite(argv[2],argv[1]);
}
