#include <stdio.h>
#include <string.h>

int main(void){
    FILE *f;
    char c;
    int llaves=0;
    int corchetes=0;
    int comillas=0;
    char cadena[100];
    int contador=0;
    int debug=1;
    int parametros=2;
    int valores=0;

    f = fopen("json.txt","r");

    if(f==NULL){
        printf("\nError al abrir el fichero.");
        exit(-1);
    }
    else{
        do{
            if(llaves==0 && corchetes==0){
                if(debug) printf("\n0,0\n");
                do{
                    c = fgetc(f);
                    if(debug) putc(c,stdout);
                }while(c!='{');
                llaves++;
            }
            else if(llaves==1 && corchetes==0){
                if (debug) printf("\n1,0\n");
                do{
                    c = fgetc(f);
                    if(debug) putc(c,stdout);
                }while(c!='[');
                corchetes++;
            }
            else if(llaves==1 && corchetes==1){
                if(debug) printf("\n1,1\n");
                do{
                    c = fgetc(f);
                    if(debug) putc(c,stdout);
                }while(c!='{');
                llaves++;
            }
            else if(llaves==1 && corchetes==1 && parametros==0 && valores==0){
                if(debug) printf("\n1,1-parametros\n");
                do{
                    c = fgetc(f);
                    if(debug) putc(c,stdout);
                }while(c!='{');
                llaves=3;
                corchetes=2;
                valores=1;
            }
            else if(llaves==2 && corchetes==1 && parametros!=0){ //nombre de comando
                parametros--;
                if(debug) printf("\n2,1-comando\n");
                comillas=0;
                do{
                    c = fgetc(f);
                    if(debug) putc(c,stdout);
                    if(c=='"') comillas++;
                }while(comillas<3);
                contador = 0;
                c = fgetc(f);
                if(debug) putc(c,stdout);
                while(c!='"'){
                    cadena[contador]=c;
                    c = fgetc(f);
                    if(debug) putc(c,stdout);
                    contador++;
                }
                cadena[contador]='\0';
                printf("\nNombre: %s\n",cadena);
                do{
                    c = fgetc(f);
                    if(debug) putc(c,stdout);
                }while(c!='[');
                corchetes++;
                do{
                    c = fgetc(f);
                    if(debug) putc(c,stdout);
                }while(c!='{');
                llaves++;
//                printf("\nllaves %d corchetes %d",llaves,corchetes);
            }
            else if(llaves==2 && corchetes==1 && parametros==0 && valores==0){ //estamos en parámetros
                if(debug) printf("\n2,1-parametros\n");
                do{
                    c=fgetc(f);
                    if(debug) putc(c,stdout);
                }while(c!='}');
                llaves=3;
                corchetes=2;
            }
            else if(llaves==3 && corchetes==2 && valores==0){ //valores especificos
                if(debug) printf("\n3,2\n");
                comillas=0;
                do{
                    c = fgetc(f);
                    if(debug) putc(c,stdout);
                    if(c=='"') comillas++;
                }while(comillas<3);
                contador = 0;
                c = fgetc(f);
                if(debug) putc(c,stdout);
                while(c!='"'){
                    cadena[contador]=c;
                    c = fgetc(f);
                    if(debug) putc(c,stdout);
                    contador++;
                }
                cadena[contador]='\0';
                printf("\nNombre especifico: %s\n",cadena);
                comillas=0;
                do{
                    c = fgetc(f);
                    if(debug) putc(c,stdout);
                    if(c=='"') comillas++;
                }while(comillas<3);
                contador = 0;
                c = fgetc(f);
                if(debug) putc(c,stdout);
                while(c!='"'){
                    cadena[contador]=c;
                    c = fgetc(f);
                    if(debug) putc(c,stdout);
                    contador++;
                }
                cadena[contador]='\0';
                printf("\nValor especifico: %s\n",cadena);
                do{
                    c = fgetc(f);
                    if(debug) putc(c,stdout);
                }while(c!='{' && c!=']');
                if(c==']'){
                    llaves=2;
                    corchetes=1;

                }
//                llaves=0;
            }
            else if(llaves==3 && corchetes==2 && valores==1){ //valores especificos
                if(debug) printf("\n3,2-parametros\n");
                comillas=0;
                do{
                    c = fgetc(f);
                    if(debug) putc(c,stdout);
                    if(c=='"') comillas++;
                }while(comillas<3);
                contador = 0;
                c = fgetc(f);
                if(debug) putc(c,stdout);
                while(c!='"'){
                    cadena[contador]=c;
                    c = fgetc(f);
                    if(debug) putc(c,stdout);
                    contador++;
                }
                cadena[contador]='\0';
                printf("\nNombre parametro: %s\n",cadena);
                comillas=0;
                do{
                    c = fgetc(f);
                    if(debug) putc(c,stdout);
                    if(c=='"') comillas++;
                }while(comillas<3);
                contador = 0;
                c = fgetc(f);
                if(debug) putc(c,stdout);
                while(c!='"'){
                    cadena[contador]=c;
                    c = fgetc(f);
                    if(debug) putc(c,stdout);
                    contador++;
                }
                cadena[contador]='\0';
                printf("\nValor parametro: %s\n",cadena);
                do{
                    c = fgetc(f);
                    if(debug) putc(c,stdout);
                }while(c!=']');
                llaves=3;
                corchetes=2;
            }
        }while(llaves>0);

        fclose(f);
    }
}

