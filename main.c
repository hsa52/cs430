#include <stdlib.h>
#include <stdio.h>
#include <string.h>
void read_p6(FILE*,char,FILE*);
void read_p3(FILE*,char format_to,FILE * output);
void parse_white_space(FILE*);
int get_number(FILE* fp);
void write_p6(FILE *fp,char* data,int size);
void write_p3(FILE *fp,unsigned char*data);

typedef struct Pixel {
    unsigned char r, g, b;
} Pixel;

int main(int argc,char* argv[]) {
    FILE * fp ;
    fp= fopen(argv[2],"r");
    FILE* output=fopen(argv[3],"w+");

    if (*argv[1] == '3' || *argv[1] == '6'){}
    else{
        fprintf(stderr,"The output format is incorrect");
        exit(-1);
    }
//opening files
    if (fp==NULL ||output==NULL){
        //printf("%s",argv[2]);
        fprintf(stderr,"Either the input or output file does not exist");
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
            fprintf(stderr,"Problem reading your file");
            //error checking file reading
        }
        if(header[0]=='P'&&header[1]=='6'){
            printf("%c",*argv[1]);
            read_p6(fp,*argv[1],output);
            //if p6 sending it to function for converting to p3
        }
        else if (header[0]=='P'&&header[1]=='3'){
            // printf("%c",*argv[1]);
            read_p3(fp,*argv[1],output);
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

void read_p6(FILE * fp,char format_to,FILE* output){
    int width,height,temp,max,temp2,i=0;
    if(fgetc(fp)=='#') {
        do temp = fgetc(fp); while (temp != '\n');
    }
    //read in the height width and max values
    fscanf(fp,"%i ",&height);
    fscanf(fp,"%i ",&width);
    fscanf(fp,"%i ",&max);
    //error checking
    if(max>255){
        fprintf(stderr,"This converter does no accept a max val of more than 255");
    }


    int f =ftell(fp);
    fseek(fp,-f,SEEK_CUR);

    int buffer_size =width*height*3+f;
    char buffer[buffer_size];
    //buffer for characters

    fread(buffer,1,buffer_size,fp);
    //reading in values
    if(format_to=='6'){
        // printf("na");
        write_p6(output,buffer,buffer_size);
    }
    if(format_to=='3'){
        // if format converting from is 3 send it
        write_p3(output,buffer);
    }
}
void write_p6(FILE *fp,char* data,int size){
    fwrite(data,1,size,fp);
    //writing buffer to file
    fseek(fp,1,SEEK_SET);
    fwrite("6",1,1,fp);
    //writing p6 to make sure it is in proper format

}
void write_p3(FILE *fp,unsigned char*data){
    fprintf(fp,"%s",data);
    //writing buffer to file
    fseek(fp,1,SEEK_SET);
    fwrite("3",1,1,fp);
    //writing p3 to make sure it is in proper format





}

void read_p3(FILE * fp,char format_to,FILE * output){

    int width,height,temp,max,temp2,i=0,j=0,u=0;
    parse_white_space(fp);

    if(fgetc(fp)=='#') {
        do temp = fgetc(fp); while (temp != '\n');
    }
    //read in the height width and max values
    fscanf(fp,"%i ",&height);
    fscanf(fp,"%i ",&width);
    fscanf(fp,"%i ",&max);
    if(max>255){
        fprintf(stderr,"This converter does no accept a max val of more than 255");
    }


//getting position in file for usage in reading in header and buffersize
    int f =ftell(fp);
    //size of header
    int buffer_size=height*width*3+f;
    Pixel pix[height*width];
    unsigned char buffer2[buffer_size];



    fseek(fp,-f,SEEK_CUR);
    fread(buffer2,1,f,fp);
    j=f;
//looping through rgb pixels
    for(i =0;i<height*width;i++){
        pix[i].r=get_number(fp);
        pix[i].g=get_number(fp);
        pix[i].b=get_number(fp);
    }

    //  looping through and adding pixel data to buffer
    while(u!=height*width) {
        buffer2[j++] = pix[u].r;
        buffer2[j++]='\n';
        buffer2[j++] = pix[u].g;
        buffer2[j++]='\n';
        buffer2[j++] = pix[u++].b;
        buffer2[j++]='\n';
    }
    //sending the buffer to the proper write file
    if(format_to=='6'){
        write_p6(output,buffer2,buffer_size);
    }
    if(format_to=='3'){
        write_p3(output,buffer2);
    }

}

int get_number(FILE* fp){
    //getting int from file and returning to buffer
    int number;
    fscanf(fp,"%i",&number);
    return number;
}
void parse_white_space(FILE *fp){
    //.go through whitespace in file
    while (fgetc(fp)==' '){
        fseek(fp,1,SEEK_CUR);
    }
}