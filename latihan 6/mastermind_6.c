#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define x 10   //jumlah banyak data yang bisa ditampung
char userName[x][20];  //array dan x itu baris, [20] jumlah kar maks
char passWord[x][20];
char userID[x][9];   //dihitung '/0'
int myindex = 0;


//func cek format password
int passval(char * p)
{
    int capital=0, small=0, digit=0, punct=0 ;
 
    while (*p && !(capital && small && digit && punct))
        capital = (*p>='A' && *p<='Z' ? 1 : capital),
        small   = (*p>='a' && *p<='z' ? 1 : small  ),
        digit   = (*p>='1' && *p<='9' ? 1 : digit  ),
        punct   = (*p=='!' || *p>='#' && *p<='*' || *p==',' || *p=='.' || *p=='@' || *p=='^' ? 1 : punct),
        p++ ;
 
    return capital && small && digit && punct;
}

//func cek format username
int usernameval(char * p)
{
    int capital=0, small=0, digit=0, dot=0 ;
 
    while (*p && !(capital && small && digit && dot))
        capital = (*p>='A' && *p<='Z' ? 1 : capital),
        small   = (*p>='a' && *p<='z' ? 1 : small  ),
        digit   = (*p>='0' && *p<='9' ? 1 : digit  ),
        dot     = (*p=='.' ? 1 : dot),
        p++ ;
 
    return capital && small && digit && dot;
}

//func cek user
int userval(const char user[]){
   int userExists = 0;
   for (int i = 0; i < x; i++)
   {
      if (strcmp(userName[i],user)==0){ //sama
         userExists = 1;
      }
   }
   return userExists;
}

//func find kode user
int findUser(const char kode[]){
    int urut = 0;
    for (int i = 0; strcmp(userID[i],kode)!=0; i++)
    {
        urut++;
    }
    return urut;
}
void loadfile(){
    FILE *con = fopen("database.txt","r+");
    if (con!=NULL)
    {
        while (!feof(con))
        {
            fscanf(con,"%[^~]~%[^~]~%[^\n]\n",&userName[myindex],&passWord[myindex],&userID[myindex]);
            myindex++;
        }
        fclose(con);
    }
}
void uploadfile(){
    FILE * upload = fopen("database.txt","w");
    for (int i = 0; i < myindex; i++)
    {
        fprintf(upload,"%s~%s~%s\n",userName[i],passWord[i],userID[i]);   
    }
    fclose(upload);
}
int main (int argc, char *argv[]) {   
    char buf[5], a[9]; //untuk kode user
    char yesno;
    int input, input2; char inputUser[20], inputPass[20], loginUser[20], loginPass[20], gantiPass[20];
    loadfile(); //load file database
    do
    {
        printf("Menu\n1. Registrasi\n2. Login\n3. Tampilkan semua data\n4. EXIT");
        printf("\nPILIH MENU : ");
        scanf("%d",&input);
        switch (input)
        {
        case 1:
            printf("==REGISTRASI==\n");
            printf("Input username : ");
            scanf("%s", &inputUser);
            printf("Input Password : ");
            scanf("%s", &inputPass);
            if (strlen(inputUser)<=6) //syarat Username
            {
                printf("Panjang Username harus Lebih dari 6 karakter\n\n");
                break;
            }else if (!usernameval(inputUser))
            {
                printf("Username Tidak Boleh ada Special Karakter, jadi yang diperbolehkan hanya a-z, A-Z, 0-9 dan '.' (titik)\n\n");
                break;
            }else if (userval(inputUser))
            {
                printf("Username sudah ada!\nTidak Boleh ada Duplikasi Username\n\n");
                break;
            }
            if (strlen(inputPass)<=8) //syarat password
            {
                printf("Panjang Password harus lebih dari 8 karakter\n\n");
                break;
            }else if (!passval(inputPass))
            {
                printf("Password Harus menyertakan minium 1 huruf kecil (a-z), 1 huruf kapital(A-Z), 1 angka(1-9),dan 1 special karakter (!@#$%c^&*().,)\n",'%');
                printf("Password Tidak boleh berbentuk Palindrome (Contoh tidak diperbolehkan abcdeedcba)\n\n");
                break;
            }
            snprintf(a,4,inputUser); //mengambil 3 karakter awal dari inputan user
           
            for (int i = 0; i<=3; i++)
            {
                if(a[i]>='a' && a[i]<='z')
                {
                    a[i] = a[i] - 32;    //to capitalize 3 alphabet
                }                
            }
            itoa(myindex+1,buf,10); //int to string //format kode user
            if (strlen(buf)==1)
            {
                strcat(a,"-000");            
            }else if (strlen(buf)==2)
            {
                strcat(a, "-00");
            }else if (strlen(buf)==3)
            {
                strcat(a,"-0");
            }else if (strlen(buf)==4)
            {
                strcat(a,"-");
            }strcat(a,buf);

            strcpy(userName[myindex],inputUser); //untuk nyimpan
            strcpy(passWord[myindex],inputPass);
            strcpy(userID[myindex],a);
            FILE * masuk = fopen("database.txt","a+");
            fprintf(masuk,"%s~%s~%s\n",userName[myindex],passWord[myindex],userID[myindex]);
            fclose(masuk);
            printf("username berhasil didaftarkan\n");
            printf("Username : %s\n",userName[myindex]);
            printf("Password : %s\n",passWord[myindex]);
            printf("Kode User : %s\n",userID[myindex]);
            myindex++;  //setiap terakses akan increment
            printf("\n");
            break;
        case 2:
            printf("==LOGIN==\n");
            printf("Input username : ");
            scanf("%s",&loginUser);
            printf("Input Password : ");
            scanf("%s",&loginPass);
            
            int x_index = findUser(loginUser);
            if (strcmp(loginPass,passWord[x_index])==0) //sama denga database
            {
                printf("SELAMAT DATANG, %s\n",userName[x_index]);
                printf("== Data Anda==\n");
                printf("Username : %s\n",userName[x_index]);
                printf("Kode User : %s\n",userID[x_index]);
                do{
                    printf("\n=Beranda=\n1. ubah password\n2. delete akun\n3. kembali\npilih : ");
                    scanf("%d",&input2);
                    switch (input2)
                    {
                    case 1:
                        printf("masukkan password baru : ");
                        scanf("%s",&gantiPass);
                        if (strlen(gantiPass)<=8) //syarat password
                        {
                            printf("Panjang Password harus lebih dari 8 karakter\n\n");
                            break;
                        }else if (!passval(gantiPass))
                        {
                            printf("Password Harus menyertakan minium 1 huruf kecil (a-z), 1 huruf kapital(A-Z), 1 angka(1-9),dan 1 special karakter (!@#$%c^&*().,)\n",'%');
                            printf("Password Tidak boleh berbentuk Palindrome (Contoh tidak diperbolehkan abcdeedcba)\n\n");
                            break;
                        }
                        strcpy(passWord[x_index],gantiPass);
                        uploadfile();
                        printf("Selamat user %s, password anda berhasil diubah\n",userID[x_index]);
                        break;
                    case 2 :
                        for (int i = x_index; i < myindex; i++)
                        {
                            strcpy(userName[i],userName[i+1]);
                            strcpy(passWord[i],passWord[i+1]);
                            strcpy(userID[i],userID[i+1]);
                        }
                        myindex--;
                        uploadfile();
                        printf("Akun berhasil dihapus\nsilahkan kembali ke menu utama\n");
                        break;
                    }
    
                }while (input2!=3);
            }else
            {
                printf("username dan password tidak sesuai!!\n");
            }
            printf("\n");
            break;
        case 3:
            printf("==LIST DATA==\n");
            if (myindex==0)
            {
                printf("Data tidak ada. Belum ada input data!!\n\n");
                break;
            }           
            for (int i = 0; i < myindex; i++)
            {
                printf("==%d==\n",i+1);
                printf("Username : %s\n",userName[i]);
                printf("Kode User : %s\n",userID[i]);
            }
            printf("\n");
            break;
        case 4 :
            printf("Program telah selesai...");
            break;
        default:
            printf("Masukkan angaka (1-4)\n");
            break;
        }
    } while (input!=4);    
   return 0;
}