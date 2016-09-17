#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

void read_p6(FILE*,char,FILE*);
void p3_to_p6(FILE*);
void parse_white_space(FILE*);
int get_number(FILE* fp);
void write_p6(FILE *fp,char* data,int size);
void write_p3(FILE *fp,char*data,int size);

typedef struct Pixel {
    unsigned char r, g, b;
} Pixel;

int main(int argc,char* argv[]) {
    FILE * fp ;
    fp= fopen(argv[2],"r");
    FILE* output=fopen(argv[3],"w+");
    //opening file
    if (fp==NULL){
        //printf("%s",argv[2]);
        fprintf(stderr,"That file does not exist");
        exit(-1);
        //error checking file opening
    }
    else{
        size_t result;
        int header_size=2;
        char header[header_size];
        char* buffer;
        //creating buffer for checking what format the file is in
        result=fread(header,1,header_size,fp);

        //reading in file format
        if(result!=header_size){
            perror("Could not read your file");
            //error checking file reading
        }
        if(header[0]=='P'&&header[1]=='6'){
            printf("%c",*argv[1]);
            read_p6(fp,*argv[1],output);
            //if p6 sending it to function for converting to p3
        }
        else if (header[0]=='P'&&header[1]=='3'){
            p3_to_p6(fp);
            //if p3 sending it to function for converting to p6
        }
        else{
            fprintf(stderr,"This is not a ppm File");
            //if it is not a PPM file giving user an error message
        }
    }
    fclose(fp);
    fclose(output);

    return 0;
}

void read_p6(FILE * fp,char formatto,FILE* output){
    int width,height,temp,max,temp2,i=0;
    if(fgetc(fp)=='#') {
        do temp = fgetc(fp); while (temp != '\n');
    }

    fscanf(fp,"%i ",&height);
    fscanf(fp,"%i ",&width);
    fscanf(fp,"%i ",&max);
    if(max>255){
        fprintf(stderr,"This converter does no accept a max val of more than 255");
    }


    int f =ftell(fp);
    fseek(fp,-f,SEEK_CUR);

    int buffer_size =width*height*3+f;
    char buffer[buffer_size];



    fread(buffer,1,buffer_size,fp);

    if(formatto=='6'){
        printf("na");
        write_p6(output,buffer,buffer_size);
    }
    if(formatto=='3'){
        printf("na3");
        write_p3(output,buffer,buffer_size);
    }





}
void write_p6(FILE *fp,char* data,int size){
    fwrite(data,1,size,fp);
    fseek(fp,1,SEEK_SET);
    fwrite("6",1,1,fp);
}
void write_p3(FILE *fp,char*data,int size){
    fprintf(fp,"%s",data);
    fseek(fp,1,SEEK_SET);

}

void p3_to_p6(FILE * fp){

    int width,height,temp,max,temp2,i=0;
    parse_white_space(fp);

    if(fgetc(fp)=='#') {
        do temp = fgetc(fp); while (temp != '\n');
    }
    //int* temp2=get_num(fp);
    fscanf(fp,"%i ",&height);
    fscanf(fp,"%i ",&width);
    fscanf(fp,"%i ",&max);
    if(max>255){
        fprintf(stderr,"This converter does no accept a max val of more than 255");
    }




    Pixel pix[height*width];
    int buffer_size=height*width*3;

    //printf("%i",max);
    char buffer[width*height*3];



    for(int i =0;i<buffer_size;i++){
        buffer[i]=temp;
        pix[i].r=get_number(fp);
        parse_white_space(fp);
        pix[i].g=get_number(fp);
        parse_white_space(fp);
        pix[i].b=get_number(fp);
        parse_white_space(fp);
    }








}
int get_number(FILE* fp){
    int number;
    fscanf(fp,"%i",&number);
    return number;
}
void parse_white_space(FILE *fp){
    while (fgetc(fp)==' '){
        fseek(fp,1,SEEK_CUR);
    }
}
