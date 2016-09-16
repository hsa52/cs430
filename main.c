#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

void p6_to_p3(FILE*);
void p3_to_p6(FILE*);
void parse_white_space(FILE*);

int main() {
    FILE * fp ;
    //fp= fopen("/Users/Hayden/ClionProjects/cs430_project1/boxes_1.ppm","r");
    //opening file
    if (fp==NULL){
        perror("That file does not exist");
        exit(-1);
        //error checking file opening
    }
    else{
        size_t result;
        int header_size=2;
        char header[header_size];
        //creating buffer for checking what format the file is in
        result=fread(header,1,header_size,fp);

        //reading in file format
        if(result!=header_size){
            perror("Could not read your file");
            //error checking file reading
        }
        if(header[0]=='P'&&header[1]=='6'){
            //printf("req");
            p6_to_p3(fp);
            //if p6 sending it to function for converting to p3
        }
        else if (header[0]=='P'&&header[1]=='3'){
            //printf("req");
            p3_to_p6(fp);
            //if p3 sending it to function for converting to p6
        }
        else{
            perror("Your file is not a PPM file");
            //if it is not a PPM file giving user an error message
        }




    }

    fclose(fp);

    return 0;
}

void p6_to_p3(FILE * fp){
    int width,height,temp,max,temp2,i=0;


    if(fgetc(fp)=='#') {
        do temp = fgetc(fp); while (temp != '\n');
    }

    fscanf(fp,"%i ",&height);
    fscanf(fp,"%i ",&width);
    fscanf(fp,"%i ",&max);

    int buffer_size =width*height* sizeof(int);
    printf("%i",width*height* sizeof(int));


    int buffer[width*height* sizeof(int)];
    int f =ftell(fp);
    fseek(fp,-f,SEEK_CUR);


    //printf("%c",*header);
    //FILE* output=fopen("/Users/Hayden/ClionProjects/cs430_project1/output.ppm","w+");
    int header[f];
    fread(header, 1, f,fp);
    fwrite(header,1, f,output);


    //printf("%i",buffer_size);
    fread(buffer,1,buffer_size,fp);
    fwrite(buffer,1,buffer_size,output);
    //fprintf(, 1, buffer_size, output);


    //int temp = fgetc(fp);
    //printf("%c",temp);






    //nothing yet
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
    printf("%i",max);
    int buffer[width*height];


    int f =ftell(fp);
    fseek(fp,-f,SEEK_CUR);
    int header[f];
    fread(header, 1, f,fp);
    //printf("%c",*header);
    //FILE* output=fopen("/Users/Hayden/ClionProjects/cs430_project1output.ppm","w+");
    fwrite(header,1, f,output);
    int u =0;
    while((temp2=fgetc(fp))!=EOF){



    }

    fwrite(buffer,1,height*width,output);

    fclose(output);

    //fgets(buffer,(height*width)-f,fp);
    //fread(buffer,1,width*height,fp);
    //atoi(buffer);
    // fwrite(buffer,1,width*height,output);


/*
    do{
        temp2=fgetc(fp);
        buffer[i++]=temp2;

    } while(temp2!=' ');
    fwrite(buffer,1,width*height,output);
    */












    //


    //fseek(fp,0,SEEK_END);
    //   int a = ftell(fp);
    //  printf("%i",a);
    // fsetpos(fp,f);
    // fread(buffer,1,a-f,fp);
    // fwrite(buffer,1,a-f,output);




    //fseek(output,1,SEEK_SET);
    //fwrite("6",1,1,output);


    // *buffer=fgetc(fp);
    //temp2 =fgetc(fp);
    //   printf("%c %i",header[2], f);










}
void parse_white_space(FILE *fp){
    while (fgetc(fp)==' '){
        fseek(fp,1,SEEK_CUR);
    }
}

