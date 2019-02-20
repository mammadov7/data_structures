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
Bmp extract(Bmp image,int newWidth){
	unsigned int a=0,i=0;
	unsigned short byte_per_pixel=image.numBperP/8;
	unsigned char *newPixels=(unsigned char *)malloc((newWidth*image.height*byte_per_pixel)*sizeof(unsigned char));
	unsigned int startPoint=(image.width-newWidth)/2*byte_per_pixel;
	while((startPoint)<image.pixelSize){
		for(i=startPoint-byte_per_pixel;i<(startPoint-byte_per_pixel+byte_per_pixel*newWidth);i++){
			newPixels[a]=image.pixels[i];
			a++;
		}
		if((newWidth*byte_per_pixel)%4!=0) //this one for pading problem
			for(int j=0;j<4-(newWidth*byte_per_pixel)%4;j++){
				newPixels[a]=0x00;
				a++;
			}
		startPoint+=(byte_per_pixel*image.width);
	}
	image.pixels=newPixels;
	image.width=newWidth;
	image.pixelSize=a;
	image.imageSize=(image.headerSize+a);
	return image;
}
//------------------------------------------------------------------------------------
int chekFile(unsigned char *original_name,char *program_name){
	FILE *fp;
	fp = fopen(original_name,"rb");
	if(fp==NULL){
		printf("ERROR IN OPENING FILE\nUse '%s -h' or '%s --help' for help\n",program_name,program_name);  
		return 0;	
	}
	unsigned char bm[2]; //we create array for taking first two elements of file(they should be B and M)
	fscanf(fp,"%c",&bm[0]);//we put first element into b[0]
	fscanf(fp,"%c",&bm[1]);//we put second element into b[1]
	if(strcmp(bm,"BM")){
		printf("ERROR, it is not bmp file because the first two elements not BM\nUse '%s -h' or '%s --help' for help\n",program_name,program_name);
		return 0;
	} 
	int filelength=strlen(original_name);//we geting the length of name of file 
	if(strcmp(&original_name[filelength-4],".bmp")!=0){//and we comparing last 4 char of original_name with .bmp
		printf("ERROR, it is not bmp file because it is not ending with .bmp\nUse '%s -h' or '%s --help' for help\n",program_name,program_name);
		return 0;
	}
	fclose(fp);
	return 1;
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
void BMPwrite(unsigned char *original_name,unsigned char *file_new_width){
	int width_of_strip=(-1)*atoi(file_new_width);
	int j=0;
	Bmp myImage=info(original_name);
	FILE * fp;
	fp=fopen(original_name,"rb");
	if(fp==NULL){
		printf("ERROR IN OPENING FILE\n");
		exit(1);	
	}	
	fread(myImage.header,myImage.headerSize,1,fp);
	fread(myImage.pixels,myImage.pixelSize,1,fp);
	fclose(fp);
	myImage=extract(myImage,width_of_strip);	
	FILE *file;
	//Geting original_name_Sxx.bmp
	int length_of_original_name=strlen(original_name);
	sprintf(&original_name[length_of_original_name-4],"_S%s.bmp",&file_new_width[1]);
	file = fopen(original_name, "wb");
	fwrite(myImage.header,myImage.headerSize,1,file);
	fseek(file,myImage.headerSize,SEEK_SET);
	fwrite(myImage.pixels,myImage.pixelSize,1,file); 
	fseek(file,2,SEEK_SET);
	fwrite(&(myImage.imageSize),sizeof(int),1,file);
	fseek(file,18,SEEK_SET);
	fwrite(&(myImage.width),sizeof(int),1,file);
	fseek(fp,34,SEEK_SET);
	fwrite(&(myImage.pixelSize),sizeof(int),1,fp);
	fclose(file);
}
//------------------------------------------------------------------------------------
int main(int argc, char *argv[]){    
	if(argc == 2 && (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))){
		printf("Usage: %s -newWidth original_name\n",argv[0]);  
		return 1;	
	}
	if(chekFile(argv[2],argv[0])==0)
		return 1;
	Bmp myImage=info(argv[2]);
	int Strip_width=(-1)*atoi(argv[1]);
	if(Strip_width>myImage.width || Strip_width<=0){
		printf("Strip_width can't be these value\nIt must be between o and  %d(original width)\n",myImage.width);
		return 1;
	}
	BMPwrite(argv[2],argv[1]);        
	printf("Size of image %d\n", myImage.imageSize);
	printf("Size of header %d\n", myImage.headerSize);
	printf("Size of width %d\n", myImage.width);
	printf("Size of height %d\n", myImage.height);
	printf("Size of B/P %d\n", myImage.numBperP);
	printf("Done!!\n");
}
