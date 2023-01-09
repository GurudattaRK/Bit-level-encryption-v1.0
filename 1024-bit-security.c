#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#define setbit(x,y) x|=((unsigned int)0x00000001 << y)
#define resetbit(x,y) x&= ~((unsigned int)0x00000001 << y)
#define checkbit(x,y) ((x >>y) & 0x1)
int main()
{
    printf("\t\t\t\t                 *|*\n\t\t\t\t               **/|\\** \n");
    printf("\t\t\t\t    **     ******/|\\******     **\n\t\t\t\t    *************/|\\************* \n");           
    printf("\t\t\t\t    *************/|\\************* \n\t1024-Bit      \t\t    *************/|\\*************\n");
    printf("\tBIT LEVEL ENCRYPTION\t     ************/ \\************\n\t\t\t1.0\t     <<<<<<<<<<<  *  >>>>>>>>>>>\n");
    printf("\t\t\t \t      ***********\\ /*********** \n\t\t\t\t       **********\\|/********** \n");
    printf("\t\t\t\t        *********\\|/********* \n\t\t\t\t         ********\\|/******** \n");      
    printf("\t\t\t\t           ******\\|/****** \n\t\t\t\t              ***\\|/*** \n\t\t\t\t                 *|* \n\n"); 

    char ch;
    printf("what do you want to do?\n1.Encrypt a file\n2.Decrypt a file\nenter your option's number:");
    scanf("%s",&ch);

    short int i=0,j=0,k=0,l=0,f=0,s=0,q=0,x=0,b,e,round=0,inp_data[1024],key_array[1024],data[32][32];
    unsigned int row_data_bit[32],col_data_bit[32],key_bit_array[32];
    unsigned char buffer[1],inp_key_array[1024];
    unsigned char inputlist[128],binaryarray[1024];
    short int t=0,h,v,binstr[8];
    unsigned long long int bytes=0,bytecount;
    
    if(ch=='1') //ENCRYPTION
    {

        char file[100],lockedfile[100],keyfile[100];
        printf("\nEnter the file's name which u wanna encrypt:\n");
        scanf("%s",file);
        printf("\nEnter keyfile's name:\n");
        scanf("%s",keyfile);
        printf("\nwhat do u want to call the encrypted file:\n");
        scanf("%s",lockedfile);

        FILE *reader = fopen(file,"rb");
        FILE *keyreader = fopen(keyfile,"rb");
        if(reader==NULL){
            printf("\nError in opening/finding the file %s",file);
            return 0;
        }
        if(keyreader==NULL){
            printf("\nError in opening/finding the file %s",keyfile);
            return 0;
        }
        fseeko64(keyreader,0,SEEK_END);
        bytes=ftello64(keyreader);
        fseeko64(keyreader,0,SEEK_SET);
        if(bytes<128){
            printf("\n%s is too small.For security reasons keyfile's size should be at least 128 bytes.",keyfile);
            return 0;
        }
        clock_t begin,end;
        begin = clock();
        double time_spent;
        printf("ENCRYPTION STARTED...\n");

        FILE *writer = fopen(lockedfile,"wb");


        t=0;
        fread(inputlist,128,1,keyreader); 
        for(int i=0;i<128;i++)
        {
            for (int bit = 8; bit; --bit)  // count from 8 to 1
            { 
                inp_key_array[t]=(inputlist[i] & (1 << (bit - 1)) ? '1' : '0');
                if(inp_key_array[t]=='1')
                key_array[t]=1;
                else
                key_array[t]=0;
                t++;

            }
        }
        fclose(keyreader);

        fseeko64(reader,0,SEEK_END);
        bytecount=ftello64(reader);
        fseeko64(reader,0,SEEK_SET);
        
        h=bytecount%128;
        if(h==0)
        bytecount=bytecount;
        else
        {
            v=128-h;
            bytecount=bytecount+v;
        }

        for(k=0;k<1024;k++)
        {
            if(49==inp_key_array[k])
            key_array[k]=1;
            else
            key_array[k]=0;
            if(key_array[k]=='1')
            setbit(key_bit_array[j],i);
            else
            resetbit(key_bit_array[j],i);
            i++;
            if(i==32)
            {i=0;  
            j++;}
        }
        while(!feof(reader))
        {
            /*encryption stuff starts here*/
            t=0;
            fread(inputlist,1,128,reader); 
            for(int i=0;i<128;i++)
            {
                for (int bit = 8; bit; --bit)  // count from 8 to 1
                { 
                    binaryarray[t]=(inputlist[i] & (1 << (bit - 1)) ? '1' : '0');
                    if(binaryarray[t]=='1'){
                    inp_data[t]=1;}
                    else{
                    inp_data[t]=0;}
                    t++;

                }
            }
            //core starts here
            j=0;
            i=0;
            t=0;
            while(j<32)
            {
                if(inp_data[t]==1)
                    setbit(row_data_bit[j],i);
                else
                    resetbit(row_data_bit[j],i);
                i++;
                t++;
                if(i==32){
                    i=0;
                    j++;
                }
            }

            
            i=0;
            j=0;
            t=0;
            while (i<32)
            {
                row_data_bit[0] = (row_data_bit[0] << (key_bit_array[i]%32)) | (row_data_bit[0] >> (32 - (key_bit_array[i]%32)));
                row_data_bit[1] = (row_data_bit[1] >> (key_bit_array[i]%33)) | (row_data_bit[1] << (32 - (key_bit_array[i]%33)));
                row_data_bit[2] = (row_data_bit[2] << (key_bit_array[i]%34)) | (row_data_bit[2] >> (32 - (key_bit_array[i]%34)));
                row_data_bit[3] = (row_data_bit[3] >> (key_bit_array[i]%35)) | (row_data_bit[3] << (32 - (key_bit_array[i]%35)));
                row_data_bit[4] = (row_data_bit[4] << (key_bit_array[i]%36)) | (row_data_bit[4] >> (32 - (key_bit_array[i]%36)));
                row_data_bit[5] = (row_data_bit[5] >> (key_bit_array[i]%37)) | (row_data_bit[5] << (32 - (key_bit_array[i]%37)));
                row_data_bit[6] = (row_data_bit[6] << (key_bit_array[i]%38)) | (row_data_bit[6] >> (32 - (key_bit_array[i]%38)));
                row_data_bit[7] = (row_data_bit[7] >> (key_bit_array[i]%39)) | (row_data_bit[7] << (32 - (key_bit_array[i]%39)));
                row_data_bit[8] = (row_data_bit[8] << (key_bit_array[i]%40)) | (row_data_bit[8] >> (32 - (key_bit_array[i]%40)));
                row_data_bit[9] = (row_data_bit[9] >> (key_bit_array[i]%41)) | (row_data_bit[9] << (32 - (key_bit_array[i]%41)));
                row_data_bit[10] = (row_data_bit[10] << (key_bit_array[i]%42)) | (row_data_bit[10] >> (32 - (key_bit_array[i]%42)));
                row_data_bit[11] = (row_data_bit[11] >> (key_bit_array[i]%43)) | (row_data_bit[11] << (32 - (key_bit_array[i]%43)));
                row_data_bit[12] = (row_data_bit[12] << (key_bit_array[i]%44)) | (row_data_bit[12] >> (32 - (key_bit_array[i]%44)));
                row_data_bit[13] = (row_data_bit[13] >> (key_bit_array[i]%45)) | (row_data_bit[13] << (32 - (key_bit_array[i]%45)));
                row_data_bit[14] = (row_data_bit[14] << (key_bit_array[i]%46)) | (row_data_bit[14] >> (32 - (key_bit_array[i]%46)));
                row_data_bit[15] = (row_data_bit[15] >> (key_bit_array[i]%47)) | (row_data_bit[15] << (32 - (key_bit_array[i]%47)));
                row_data_bit[16] = (row_data_bit[16] << (key_bit_array[i]%48)) | (row_data_bit[16] >> (32 - (key_bit_array[i]%48)));
                row_data_bit[17] = (row_data_bit[17] >> (key_bit_array[i]%49)) | (row_data_bit[17] << (32 - (key_bit_array[i]%49)));
                row_data_bit[18] = (row_data_bit[18] << (key_bit_array[i]%50)) | (row_data_bit[18] >> (32 - (key_bit_array[i]%50)));
                row_data_bit[19] = (row_data_bit[19] >> (key_bit_array[i]%51)) | (row_data_bit[19] << (32 - (key_bit_array[i]%51)));
                row_data_bit[20] = (row_data_bit[20] << (key_bit_array[i]%52)) | (row_data_bit[20] >> (32 - (key_bit_array[i]%52)));
                row_data_bit[21] = (row_data_bit[21] >> (key_bit_array[i]%53)) | (row_data_bit[21] << (32 - (key_bit_array[i]%53)));
                row_data_bit[22] = (row_data_bit[22] << (key_bit_array[i]%54)) | (row_data_bit[22] >> (32 - (key_bit_array[i]%54)));
                row_data_bit[23] = (row_data_bit[23] >> (key_bit_array[i]%55)) | (row_data_bit[23] << (32 - (key_bit_array[i]%55)));
                row_data_bit[24] = (row_data_bit[24] << (key_bit_array[i]%56)) | (row_data_bit[24] >> (32 - (key_bit_array[i]%56)));
                row_data_bit[25] = (row_data_bit[25] >> (key_bit_array[i]%57)) | (row_data_bit[25] << (32 - (key_bit_array[i]%57)));
                row_data_bit[26] = (row_data_bit[26] << (key_bit_array[i]%58)) | (row_data_bit[26] >> (32 - (key_bit_array[i]%58)));
                row_data_bit[27] = (row_data_bit[27] >> (key_bit_array[i]%59)) | (row_data_bit[27] << (32 - (key_bit_array[i]%59)));
                row_data_bit[28] = (row_data_bit[28] << (key_bit_array[i]%60)) | (row_data_bit[28] >> (32 - (key_bit_array[i]%60)));
                row_data_bit[29] = (row_data_bit[29] >> (key_bit_array[i]%61)) | (row_data_bit[29] << (32 - (key_bit_array[i]%61)));
                row_data_bit[30] = (row_data_bit[30] << (key_bit_array[i]%62)) | (row_data_bit[30] >> (32 - (key_bit_array[i]%62)));
                row_data_bit[31] = (row_data_bit[31] >> (key_bit_array[i]%63)) | (row_data_bit[31] << (32 - (key_bit_array[i]%63)));

                i++;
                row_data_bit[31]=(row_data_bit[31])^(key_bit_array[i]);
                i++;
            
                k=0;
                j=0;
                while(k<32)
                {
                    if(checkbit(row_data_bit[j],k)){
                    setbit(col_data_bit[k],j);
                    }
                    else{
                    resetbit(col_data_bit[k],j);
                    }
                    j++;
                    if(j==32)
                    {
                        j=0;
                        k++;
                    }
                }

                col_data_bit[0] = (col_data_bit[0] >> (key_bit_array[i]%32)) | (col_data_bit[0] << (32 - (key_bit_array[i]%32)));
                col_data_bit[1] = (col_data_bit[1] << (key_bit_array[i]%33)) | (col_data_bit[1] >> (32 - (key_bit_array[i]%33)));
                col_data_bit[2] = (col_data_bit[2] >> (key_bit_array[i]%34)) | (col_data_bit[2] << (32 - (key_bit_array[i]%34)));
                col_data_bit[3] = (col_data_bit[3] << (key_bit_array[i]%35)) | (col_data_bit[3] >> (32 - (key_bit_array[i]%35)));
                col_data_bit[4] = (col_data_bit[4] >> (key_bit_array[i]%36)) | (col_data_bit[4] << (32 - (key_bit_array[i]%36)));
                col_data_bit[5] = (col_data_bit[5] << (key_bit_array[i]%37)) | (col_data_bit[5] >> (32 - (key_bit_array[i]%37)));
                col_data_bit[6] = (col_data_bit[6] >> (key_bit_array[i]%38)) | (col_data_bit[6] << (32 - (key_bit_array[i]%38)));
                col_data_bit[7] = (col_data_bit[7] << (key_bit_array[i]%39)) | (col_data_bit[7] >> (32 - (key_bit_array[i]%39)));
                col_data_bit[8] = (col_data_bit[8] >> (key_bit_array[i]%40)) | (col_data_bit[8] << (32 - (key_bit_array[i]%40)));
                col_data_bit[9] = (col_data_bit[9] << (key_bit_array[i]%41)) | (col_data_bit[9] >> (32 - (key_bit_array[i]%41)));
                col_data_bit[10] = (col_data_bit[10] >> (key_bit_array[i]%42)) | (col_data_bit[10] << (32 - (key_bit_array[i]%42)));
                col_data_bit[11] = (col_data_bit[11] << (key_bit_array[i]%43)) | (col_data_bit[11] >> (32 - (key_bit_array[i]%43)));
                col_data_bit[12] = (col_data_bit[12] >> (key_bit_array[i]%44)) | (col_data_bit[12] << (32 - (key_bit_array[i]%44)));
                col_data_bit[13] = (col_data_bit[13] << (key_bit_array[i]%45)) | (col_data_bit[13] >> (32 - (key_bit_array[i]%45)));
                col_data_bit[14] = (col_data_bit[14] >> (key_bit_array[i]%46)) | (col_data_bit[14] << (32 - (key_bit_array[i]%46)));
                col_data_bit[15] = (col_data_bit[15] << (key_bit_array[i]%47)) | (col_data_bit[15] >> (32 - (key_bit_array[i]%47)));
                col_data_bit[16] = (col_data_bit[16] >> (key_bit_array[i]%48)) | (col_data_bit[16] << (32 - (key_bit_array[i]%48)));
                col_data_bit[17] = (col_data_bit[17] << (key_bit_array[i]%49)) | (col_data_bit[17] >> (32 - (key_bit_array[i]%49)));
                col_data_bit[18] = (col_data_bit[18] >> (key_bit_array[i]%50)) | (col_data_bit[18] << (32 - (key_bit_array[i]%50)));
                col_data_bit[19] = (col_data_bit[19] << (key_bit_array[i]%51)) | (col_data_bit[19] >> (32 - (key_bit_array[i]%51)));
                col_data_bit[20] = (col_data_bit[20] >> (key_bit_array[i]%52)) | (col_data_bit[20] << (32 - (key_bit_array[i]%52)));
                col_data_bit[21] = (col_data_bit[21] << (key_bit_array[i]%53)) | (col_data_bit[21] >> (32 - (key_bit_array[i]%53)));
                col_data_bit[22] = (col_data_bit[22] >> (key_bit_array[i]%54)) | (col_data_bit[22] << (32 - (key_bit_array[i]%54)));
                col_data_bit[23] = (col_data_bit[23] << (key_bit_array[i]%55)) | (col_data_bit[23] >> (32 - (key_bit_array[i]%55)));
                col_data_bit[24] = (col_data_bit[24] >> (key_bit_array[i]%56)) | (col_data_bit[24] << (32 - (key_bit_array[i]%56)));
                col_data_bit[25] = (col_data_bit[25] << (key_bit_array[i]%57)) | (col_data_bit[25] >> (32 - (key_bit_array[i]%57)));
                col_data_bit[26] = (col_data_bit[26] >> (key_bit_array[i]%58)) | (col_data_bit[26] << (32 - (key_bit_array[i]%58)));
                col_data_bit[27] = (col_data_bit[27] << (key_bit_array[i]%59)) | (col_data_bit[27] >> (32 - (key_bit_array[i]%59)));
                col_data_bit[28] = (col_data_bit[28] >> (key_bit_array[i]%60)) | (col_data_bit[28] << (32 - (key_bit_array[i]%60)));
                col_data_bit[29] = (col_data_bit[29] << (key_bit_array[i]%61)) | (col_data_bit[29] >> (32 - (key_bit_array[i]%61)));
                col_data_bit[30] = (col_data_bit[30] >> (key_bit_array[i]%62)) | (col_data_bit[30] << (32 - (key_bit_array[i]%62)));
                col_data_bit[31] = (col_data_bit[31] << (key_bit_array[i]%63)) | (col_data_bit[31] >> (32 - (key_bit_array[i]%63)));

                i++;

                col_data_bit[31]=(col_data_bit[31])^(key_bit_array[i]);
                i++;

                k=0;
                j=0;
                while(k<32)
                {
                    if(checkbit(col_data_bit[j],k)){
                    setbit(row_data_bit[k],j);
                    }
                    else{
                    resetbit(row_data_bit[k],j);
                    }
                    j++;
                    if(j==32)
                    {
                        j=0;
                        k++;
                    }
                }
                k=0;
                j=0;
            
            }
            //core ends here
            fwrite(row_data_bit,128,1,writer);
            /*encryption stuff ends here*/
        }
        
        fclose(reader);
        fclose(writer);
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;    
        printf("\n\nEncryption of %llu bytes completed in %f seconds ",bytecount,time_spent);
        printf("\n\nPress any key to exit\n");
        getch();
        return 0;

    }
    else if (ch=='2') //DECRYPTION
    {

        char lockedfile[100],unlockedfile[100],keyfile[100];
        printf("\nEnter the file's name which u wanna decrypt:\n");
        scanf("%s",lockedfile);
        printf("\nEnter keyfile's name:\n");
        scanf("%s",keyfile);
        printf("\nwhat do u wanna name the decrypted file:\n");
        scanf("%s",unlockedfile);

        FILE *reader = fopen(lockedfile,"rb");
        FILE *keyreader = fopen(keyfile,"rb");

        if(reader==NULL){
            printf("\nError in opening/finding the file %s",lockedfile);
            return 0;
        }
        if(keyreader==NULL){
            printf("\nError in opening/finding the file %s",keyfile);
            return 0;
        }
        fseeko64(keyreader,0,SEEK_END);
        bytes=ftello64(keyreader);
        fseeko64(keyreader,0,SEEK_SET);
        if(bytes<128){
            printf("\n%s is too small.For security reasons keyfile's should be at least 128 bytes.",keyfile);
            return 0;
        }
        clock_t begin,end;
        begin = clock();
        double time_spent;
        printf("DECRYPTION STARTED....\n");

        FILE *writer = fopen(unlockedfile,"wb");


        t=0;
        fread(inputlist,128,1,keyreader); 
        for(int i=0;i<128;i++)
        {
            for (int bit = 8; bit; --bit)  // count from 8 to 1
            { 
                inp_key_array[t]=(inputlist[i] & (1 << (bit - 1)) ? '1' : '0');
                if(inp_key_array[t]=='1')
                key_array[t]=1;
                else
                key_array[t]=0;
                t++;

            }
        }
        fclose(keyreader);

        fseeko64(reader,0,SEEK_END);
        bytecount=ftello64(reader);
        fseeko64(reader,0,SEEK_SET);

        for(k=0;k<1024;k++)
        {
            if(49==inp_key_array[k])
            key_array[k]=1;
            else
            key_array[k]=0;
            if(key_array[k]=='1')
            setbit(key_bit_array[j],i);
            else
            resetbit(key_bit_array[j],i);
            i++;
            if(i==32)
            {i=0;  
            j++;}
        }

        while(!feof(reader))
        {
            /*encryption stuff starts here*/
            
            //core starts here
            fread(row_data_bit,128,1,reader);
            
            i=31;
            while(i> -1)
            {
                k=0;
                j=0;
                while(k<32)
                {
                    if(checkbit(row_data_bit[j],k)){
                    setbit(col_data_bit[k],j);
                    }
                    else{
                    resetbit(col_data_bit[k],j);
                    }
                    j++;
                    if(j==32)
                    {
                        j=0;
                        k++;
                    }
                }
                
                col_data_bit[31]=(col_data_bit[31])^(key_bit_array[i]);
                
                i--;

                col_data_bit[0] = (col_data_bit[0] << (key_bit_array[i]%32)) | (col_data_bit[0] >> (32 - (key_bit_array[i]%32)));
                col_data_bit[1] = (col_data_bit[1] >> (key_bit_array[i]%33)) | (col_data_bit[1] << (32 - (key_bit_array[i]%33)));
                col_data_bit[2] = (col_data_bit[2] << (key_bit_array[i]%34)) | (col_data_bit[2] >> (32 - (key_bit_array[i]%34)));
                col_data_bit[3] = (col_data_bit[3] >> (key_bit_array[i]%35)) | (col_data_bit[3] << (32 - (key_bit_array[i]%35)));
                col_data_bit[4] = (col_data_bit[4] << (key_bit_array[i]%36)) | (col_data_bit[4] >> (32 - (key_bit_array[i]%36)));
                col_data_bit[5] = (col_data_bit[5] >> (key_bit_array[i]%37)) | (col_data_bit[5] << (32 - (key_bit_array[i]%37)));
                col_data_bit[6] = (col_data_bit[6] << (key_bit_array[i]%38)) | (col_data_bit[6] >> (32 - (key_bit_array[i]%38)));
                col_data_bit[7] = (col_data_bit[7] >> (key_bit_array[i]%39)) | (col_data_bit[7] << (32 - (key_bit_array[i]%39)));
                col_data_bit[8] = (col_data_bit[8] << (key_bit_array[i]%40)) | (col_data_bit[8] >> (32 - (key_bit_array[i]%40)));
                col_data_bit[9] = (col_data_bit[9] >> (key_bit_array[i]%41)) | (col_data_bit[9] << (32 - (key_bit_array[i]%41)));
                col_data_bit[10] = (col_data_bit[10] << (key_bit_array[i]%42)) | (col_data_bit[10] >> (32 - (key_bit_array[i]%42)));
                col_data_bit[11] = (col_data_bit[11] >> (key_bit_array[i]%43)) | (col_data_bit[11] << (32 - (key_bit_array[i]%43)));
                col_data_bit[12] = (col_data_bit[12] << (key_bit_array[i]%44)) | (col_data_bit[12] >> (32 - (key_bit_array[i]%44)));
                col_data_bit[13] = (col_data_bit[13] >> (key_bit_array[i]%45)) | (col_data_bit[13] << (32 - (key_bit_array[i]%45)));
                col_data_bit[14] = (col_data_bit[14] << (key_bit_array[i]%46)) | (col_data_bit[14] >> (32 - (key_bit_array[i]%46)));
                col_data_bit[15] = (col_data_bit[15] >> (key_bit_array[i]%47)) | (col_data_bit[15] << (32 - (key_bit_array[i]%47)));
                col_data_bit[16] = (col_data_bit[16] << (key_bit_array[i]%48)) | (col_data_bit[16] >> (32 - (key_bit_array[i]%48)));
                col_data_bit[17] = (col_data_bit[17] >> (key_bit_array[i]%49)) | (col_data_bit[17] << (32 - (key_bit_array[i]%49)));
                col_data_bit[18] = (col_data_bit[18] << (key_bit_array[i]%50)) | (col_data_bit[18] >> (32 - (key_bit_array[i]%50)));
                col_data_bit[19] = (col_data_bit[19] >> (key_bit_array[i]%51)) | (col_data_bit[19] << (32 - (key_bit_array[i]%51)));
                col_data_bit[20] = (col_data_bit[20] << (key_bit_array[i]%52)) | (col_data_bit[20] >> (32 - (key_bit_array[i]%52)));
                col_data_bit[21] = (col_data_bit[21] >> (key_bit_array[i]%53)) | (col_data_bit[21] << (32 - (key_bit_array[i]%53)));
                col_data_bit[22] = (col_data_bit[22] << (key_bit_array[i]%54)) | (col_data_bit[22] >> (32 - (key_bit_array[i]%54)));
                col_data_bit[23] = (col_data_bit[23] >> (key_bit_array[i]%55)) | (col_data_bit[23] << (32 - (key_bit_array[i]%55)));
                col_data_bit[24] = (col_data_bit[24] << (key_bit_array[i]%56)) | (col_data_bit[24] >> (32 - (key_bit_array[i]%56)));
                col_data_bit[25] = (col_data_bit[25] >> (key_bit_array[i]%57)) | (col_data_bit[25] << (32 - (key_bit_array[i]%57)));
                col_data_bit[26] = (col_data_bit[26] << (key_bit_array[i]%58)) | (col_data_bit[26] >> (32 - (key_bit_array[i]%58)));
                col_data_bit[27] = (col_data_bit[27] >> (key_bit_array[i]%59)) | (col_data_bit[27] << (32 - (key_bit_array[i]%59)));
                col_data_bit[28] = (col_data_bit[28] << (key_bit_array[i]%60)) | (col_data_bit[28] >> (32 - (key_bit_array[i]%60)));
                col_data_bit[29] = (col_data_bit[29] >> (key_bit_array[i]%61)) | (col_data_bit[29] << (32 - (key_bit_array[i]%61)));
                col_data_bit[30] = (col_data_bit[30] << (key_bit_array[i]%62)) | (col_data_bit[30] >> (32 - (key_bit_array[i]%62)));
                col_data_bit[31] = (col_data_bit[31] >> (key_bit_array[i]%63)) | (col_data_bit[31] << (32 - (key_bit_array[i]%63)));

                i--;
            
                k=0;
                j=0;
                while(k<32)
                {
                    if(checkbit(col_data_bit[j],k)){
                    setbit(row_data_bit[k],j);
                    }
                    else{
                    resetbit(row_data_bit[k],j);
                    }
                    j++;
                    if(j==32)
                    {
                        j=0;
                        k++;
                    }
                }
            
            
                row_data_bit[31]=(row_data_bit[31])^(key_bit_array[i]);
                i--;

                row_data_bit[0] = (row_data_bit[0] >> (key_bit_array[i]%32)) | (row_data_bit[0] << (32 - (key_bit_array[i]%32)));
                row_data_bit[1] = (row_data_bit[1] << (key_bit_array[i]%33)) | (row_data_bit[1] >> (32 - (key_bit_array[i]%33)));
                row_data_bit[2] = (row_data_bit[2] >> (key_bit_array[i]%34)) | (row_data_bit[2] << (32 - (key_bit_array[i]%34)));
                row_data_bit[3] = (row_data_bit[3] << (key_bit_array[i]%35)) | (row_data_bit[3] >> (32 - (key_bit_array[i]%35)));
                row_data_bit[4] = (row_data_bit[4] >> (key_bit_array[i]%36)) | (row_data_bit[4] << (32 - (key_bit_array[i]%36)));
                row_data_bit[5] = (row_data_bit[5] << (key_bit_array[i]%37)) | (row_data_bit[5] >> (32 - (key_bit_array[i]%37)));
                row_data_bit[6] = (row_data_bit[6] >> (key_bit_array[i]%38)) | (row_data_bit[6] << (32 - (key_bit_array[i]%38)));
                row_data_bit[7] = (row_data_bit[7] << (key_bit_array[i]%39)) | (row_data_bit[7] >> (32 - (key_bit_array[i]%39)));
                row_data_bit[8] = (row_data_bit[8] >> (key_bit_array[i]%40)) | (row_data_bit[8] << (32 - (key_bit_array[i]%40)));
                row_data_bit[9] = (row_data_bit[9] << (key_bit_array[i]%41)) | (row_data_bit[9] >> (32 - (key_bit_array[i]%41)));
                row_data_bit[10] = (row_data_bit[10] >> (key_bit_array[i]%42)) | (row_data_bit[10] << (32 - (key_bit_array[i]%42)));
                row_data_bit[11] = (row_data_bit[11] << (key_bit_array[i]%43)) | (row_data_bit[11] >> (32 - (key_bit_array[i]%43)));
                row_data_bit[12] = (row_data_bit[12] >> (key_bit_array[i]%44)) | (row_data_bit[12] << (32 - (key_bit_array[i]%44)));
                row_data_bit[13] = (row_data_bit[13] << (key_bit_array[i]%45)) | (row_data_bit[13] >> (32 - (key_bit_array[i]%45)));
                row_data_bit[14] = (row_data_bit[14] >> (key_bit_array[i]%46)) | (row_data_bit[14] << (32 - (key_bit_array[i]%46)));
                row_data_bit[15] = (row_data_bit[15] << (key_bit_array[i]%47)) | (row_data_bit[15] >> (32 - (key_bit_array[i]%47)));
                row_data_bit[16] = (row_data_bit[16] >> (key_bit_array[i]%48)) | (row_data_bit[16] << (32 - (key_bit_array[i]%48)));
                row_data_bit[17] = (row_data_bit[17] << (key_bit_array[i]%49)) | (row_data_bit[17] >> (32 - (key_bit_array[i]%49)));
                row_data_bit[18] = (row_data_bit[18] >> (key_bit_array[i]%50)) | (row_data_bit[18] << (32 - (key_bit_array[i]%50)));
                row_data_bit[19] = (row_data_bit[19] << (key_bit_array[i]%51)) | (row_data_bit[19] >> (32 - (key_bit_array[i]%51)));
                row_data_bit[20] = (row_data_bit[20] >> (key_bit_array[i]%52)) | (row_data_bit[20] << (32 - (key_bit_array[i]%52)));
                row_data_bit[21] = (row_data_bit[21] << (key_bit_array[i]%53)) | (row_data_bit[21] >> (32 - (key_bit_array[i]%53)));
                row_data_bit[22] = (row_data_bit[22] >> (key_bit_array[i]%54)) | (row_data_bit[22] << (32 - (key_bit_array[i]%54)));
                row_data_bit[23] = (row_data_bit[23] << (key_bit_array[i]%55)) | (row_data_bit[23] >> (32 - (key_bit_array[i]%55)));
                row_data_bit[24] = (row_data_bit[24] >> (key_bit_array[i]%56)) | (row_data_bit[24] << (32 - (key_bit_array[i]%56)));
                row_data_bit[25] = (row_data_bit[25] << (key_bit_array[i]%57)) | (row_data_bit[25] >> (32 - (key_bit_array[i]%57)));
                row_data_bit[26] = (row_data_bit[26] >> (key_bit_array[i]%58)) | (row_data_bit[26] << (32 - (key_bit_array[i]%58)));
                row_data_bit[27] = (row_data_bit[27] << (key_bit_array[i]%59)) | (row_data_bit[27] >> (32 - (key_bit_array[i]%59)));
                row_data_bit[28] = (row_data_bit[28] >> (key_bit_array[i]%60)) | (row_data_bit[28] << (32 - (key_bit_array[i]%60)));
                row_data_bit[29] = (row_data_bit[29] << (key_bit_array[i]%61)) | (row_data_bit[29] >> (32 - (key_bit_array[i]%61)));
                row_data_bit[30] = (row_data_bit[30] >> (key_bit_array[i]%62)) | (row_data_bit[30] << (32 - (key_bit_array[i]%62)));
                row_data_bit[31] = (row_data_bit[31] << (key_bit_array[i]%63)) | (row_data_bit[31] >> (32 - (key_bit_array[i]%63)));

                i--;

                k=0;
                j=0;
                while(k<32)
                {
                    if(checkbit(row_data_bit[j],k)){
                    setbit(col_data_bit[k],j);
                    }
                    else{
                    resetbit(col_data_bit[k],j);
                    }
                    j++;
                    if(j==32)
                    {
                        j=0;
                        k++;
                    }
                }
            
            }
            

            j=0;
            i=0;
            t=0;
            while(j<32)
            {
                if(checkbit(row_data_bit[j],i)){
                inp_data[t]=1;
                }
                else{
                inp_data[t]=0;
                }
                i++;
                t++;
                if(i==32){
                    i=0;
                    j++;

                }
            }

            //core ends here
            

            k=0;
            t=0;
            while(k<1024)
            {
                binstr[0]=inp_data[k];
                k++;
                binstr[1]=inp_data[k];
                k++;
                binstr[2]=inp_data[k];
                k++;
                binstr[3]=inp_data[k];
                k++;
                binstr[4]=inp_data[k];
                k++;
                binstr[5]=inp_data[k];
                k++;
                binstr[6]=inp_data[k];
                k++;
                binstr[7]=inp_data[k];
                k++;
                int x,b=0,q=1;
                i=7;
                while(i> -1)
                {
                    x=binstr[i--];
                    b=b+x*q;
                    q=q*2;
                }
                inputlist[t]=b;
                t++;
            }
            fwrite(inputlist,128,1,writer);
            /*encryption stuff ends here*/
        }
        fclose(reader);
        fclose(writer);
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;    
        printf("\n\nDecryption of %llu bytes completed in %f seconds ",bytecount,time_spent);
        printf("\n\nPress any key to exit\n");
        getch();
        return 0;
        
    }
    else
    {
        printf("invalid input");
        return 0;
    }
    
}
