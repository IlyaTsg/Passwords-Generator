#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define max_len 1000

int arr_delimiters(char *);
/*Generation array of special symblols*/

void pass_generation();
/*Password's generation*/

void enter_func(int , int*);

int menu();

int main(void)
{
    char **arr_pass;
    char *pass, *symb_arr;
    char delim_string[] = "--------------------\n";
    int n, choice;
    int i, k;
    int len_s_arr;
    int num_pass;
    int mode;

    //Memory allocation
    symb_arr = (char*)malloc(max_len*sizeof(char));
    pass = (char*)calloc(n, sizeof(char));

    FILE *dfile;
    dfile = fopen("passwords.txt", "a");

    if(dfile != NULL){
        if(symb_arr!=NULL && pass!=NULL){
            printf("Hello, this is a password generator!\n");
            do{
                mode = menu(0);
                if(mode == 1){
                    enter_func(1, &num_pass);
                    mode = menu(1);
                    if(mode == 1){
                        enter_func(2, &n);
                        len_s_arr = arr_delimiters(symb_arr);//Generation array of special symbols
                    }
                    else{
                        len_s_arr = arr_delimiters(symb_arr);//Generation array of special symbols
                        enter_func(2, &n);
                    }
                }
                else if(mode == 2){
                    enter_func(2, &n);
                    mode = menu(2);
                    if(mode == 1){
                        enter_func(1, &num_pass);
                        len_s_arr = arr_delimiters(symb_arr);//Generation array of special symbols
                    }
                    else{
                        len_s_arr = arr_delimiters(symb_arr);//Generation array of special symbols
                        enter_func(1, &num_pass);
                    }
                }
                else if(mode == 3){
                    len_s_arr = arr_delimiters(symb_arr);//Generation array of special symbols
                    mode = menu(3);
                    if(mode == 1){
                        enter_func(1, &num_pass);
                        enter_func(2, &n);
                    }
                    else{
                        enter_func(2, &n);
                        enter_func(1, &num_pass);
                    }
                }

                fflush(stdin);

                arr_pass = (char**)malloc(num_pass*sizeof(char*));//Memory allocation
                if(arr_pass){
                    srand(time(NULL));
                    for(k = 0; k < num_pass; k++){
                        pass_generation(n, pass, len_s_arr, symb_arr);//Password's generations
                        arr_pass[k] = (char*)malloc((n+2)*sizeof(char));//Memory allocation
                        if(arr_pass[k]){
                            for(i = 0; i < n; i++) arr_pass[k][i] = pass[i];
                            arr_pass[k][i] = '\0';
                            arr_pass[k][i+1] = '\n';
                        }
                        else{
                            num_pass--;//Reduction in number of passwords
                            printf("Error of memory allocation!\n");
                        }
                    }

                    system("cls");
                    if(num_pass){
                        //Control print
                        printf("Generation is successful!\n");
                        for(i = 0; i < num_pass; i++) printf("Password number %d: %s\n", i+1, arr_pass[i]);
                        //Writing result in file
                        for(i = 0; i < num_pass; i++) fwrite(arr_pass[i], n+2, 1, dfile);
                        fwrite(delim_string, 21, 1, dfile);
                    }else printf("Error of generation!\n");
                }else printf("Out of memory!\n");
                printf("Continue the program?(YES - 1, NO - 0): ");
                scanf("%d", &choice);
                system("cls");
            }while(choice);
        }else printf("Out of memory!\n");
        fclose(dfile);
    }else perror("Opening error\n");

    //Freeing memory
    for(i = 0; i < num_pass; i++){
        free(arr_pass[i]);
        arr_pass[i] = NULL;
    }
    free(arr_pass);
    arr_pass = NULL;
    free(pass);
    free(symb_arr);
    pass = NULL;
    symb_arr = NULL;

    return 0;
}

int arr_delimiters(char *end_arr)
{
    char *beg_arr;
    int len;
    int i, j;
    int correct;

    beg_arr = (char*)malloc(max_len*sizeof(char));//Memory allocation
    if(beg_arr){
        do{
            printf("Please enter array of special symbols(limit 100): ");
            fgets(beg_arr, max_len, stdin);
            len = strlen(beg_arr) - 1;
            for(i = 0, j = 0; i < len; i++){
                if(beg_arr[i] != ' '){
                    end_arr[j] = beg_arr[i];
                    j++;
                }
            }
            printf("Array of special symbols: [");
            for(i = 0; i < j; i++) printf("%c", end_arr[i]);
            printf("]\n");
            printf("It is correct?(YES - 1, NO - 0): ");
            scanf("%d", &correct);
            fflush(stdin);
        }while(correct == 0);
    }
    else{
        end_arr = NULL;
        j = 0;
    }

    //Freeing memory
    free(beg_arr);
    beg_arr = NULL;
    return j;
}

void pass_generation(int len, char *pass, int len_s_arr, char *symb_arr)
{
    int count_1, count_w, count_sp;
    int i;
    int tmp;

    count_1 = 1 + rand()%(len-2);
    for(i = 0; i < count_1; i++) pass[i] = 49 + rand()%(9);

    count_w = 1 + rand()%(len-1-count_1);
    for(i = count_1; i < count_1+count_w; i++) pass[i] = 97 + rand()%(26);

    count_sp = len-count_1-count_w;
    for(i = count_1+count_w; i < count_1+count_w+count_sp; i++) pass[i] = symb_arr[rand()%(len_s_arr)];

    for(i = 0; i < len/2; i++){
        if(i%2 == 0){
            tmp = pass[i];
            pass[i] = pass[len-len/2-1+i];
            pass[len-len/2-1+i] = tmp;
        }
    }
}

int menu(int done)
{
    int choice;
    if(done == 0){
        printf("----Menu----\n1 - Enter number of passwords\n");
        printf("2 - Enter length of password\n3 - Enter array of special symbols\n------------\n");
        do{
            printf("Your choice: ");
            scanf("%d", &choice);
        }while(choice<1 || choice>3);
    }
    else if(done == 1){
        system("cls");
        printf("----Menu----\n");
        printf("1 - Enter length of password\n2 - Enter array of special symbols\n------------\n");
        do{
            printf("Your choice: ");
            scanf("%d", &choice);
        }while(choice<1 || choice>2);
    }
    else if(done == 2){
        system("cls");
        printf("----Menu----\n1 - Enter number of passwords\n");
        printf("2 - Enter array of special symbols\n------------\n");
        do{
            printf("Your choice: ");
            scanf("%d", &choice);
        }while(choice<1 || choice>2);
    }
    else if(done == 3){
        system("cls");
        printf("----Menu----\n1 - Enter number of passwords\n");
        printf("2 - Enter length of password\n");
        do{
            printf("Your choice: ");
            scanf("%d", &choice);
        }while(choice<1 || choice>2);
    }
    fflush(stdin);
    return choice;
}

void enter_func(int mode, int *value)
{
    if(mode == 1){
        do{
            printf("Please enter number of passwords(more 0): ");
            scanf("%d", value);
        }while(*value<1);
    }
    else{
        do{
            printf("Please enter length of password(more 7 and less 16): ");
            scanf("%d", value);
        }while(*value<8 || *value>15);
    }
    fflush(stdin);
}
