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
    int debug=0; //ver lo que esta haciendo
    int parametros=2;
    int valores=0;
    int fin=0;
    int comandos=0;
    int especificos=0;
    int segundaparte=0;

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
            if(llaves==1 && corchetes==0 && comandos<3){
                if (debug) printf("\n1,0\n");
                do{
                    c = fgetc(f);
                    if(debug) putc(c,stdout);
                }while(c!='[');
                corchetes++;
                do{
                    if(llaves==1 && corchetes==1){ //busco nombre comando
                        if(debug) printf("\n1,1\n");
                        do{
                            c = fgetc(f);
                            if(debug) putc(c,stdout);
                        }while(c!='{');
                        llaves++;
                    }
                    if(llaves==2 && corchetes==1 && comandos<2){ //nombre de comando
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
                        comandos++;
        //                printf("\nllaves %d corchetes %d",llaves,corchetes);
                    }
                    if(llaves==3 && corchetes==2 && comandos<3){ //valores especificos
                        especificos++;
                        if(debug) printf("\nEspecificos: %d",especificos);
                        if(especificos<5){
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
                        }
                        if(especificos<4){
                            do{
                                c = fgetc(f);
                                if(debug) putc(c,stdout);
                            }while(c!='}');
                            llaves--;
                            do{
                                c = fgetc(f);
                                if(debug) putc(c,stdout);
                                if(c=='}') llaves--;
                                if(c==']') corchetes--;
                                if(c=='[') corchetes++;
                            }while(c!='{');
                            llaves++;
                        }else{
                            do{
                                c = fgetc(f);
                                if(debug) putc(c,stdout);
                                if(c=='}') llaves--;
                                if(c==']') corchetes--;
                                if(c=='{') llaves++;
                            }while(c!='[');
                            corchetes++;
                            segundaparte=1;
                        }
                    }
                    if(debug) printf("\nSegunda parte: %d",segundaparte);
                }while(!segundaparte);
            }
            if(debug) printf("\nSegunda parte, llaves: %d corchetes: %d valores: %d",llaves,corchetes,valores);
            if(llaves==1 && corchetes==1 && valores<2){
                if(debug) printf("\nParametros %d,%d,%d",llaves,corchetes,valores);
                comillas=0;
                do{
                    c = fgetc(f);
                    if(debug) putc(c,stdout);
                    if(c=='"') comillas++;
                }while(comillas<3);
                llaves++;
            }
            if(llaves==2 && corchetes==1 && valores<2){
                if(debug) printf("\nParametros %d,%d,%d",llaves,corchetes,valores);
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
                valores++;
                do{
                    c = fgetc(f);
                    if(debug) putc(c,stdout);
                }while(c!='}');
                llaves--;
            }
            if(valores==2) fin=1;
        }while(!fin);

        fclose(f);
    }
}


