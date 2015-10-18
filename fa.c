/***************************************************************************

        FILE ATTRIBUTES (C)1991 Turgut Kalfaoglu, 1378 Sok 8/10,Izmir/Turkey
        
        Compiler: MSC 6.0. Must be compiled with /AL option.
        Operating System: OS/2 2.0. Might work with earlier releases.
        
***************************************************************************/


#define INCL_DOS
#include <os2.h>

/* let's please _fastcall */
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

void show_help(void);
void show_file(int,char *[]);
void set_file(int,char *[]);

main(argc,argv)
int argc;
char *argv[];
{
        if (argc<2) show_help();
        
        if (*(argv[1]) == '-' || *(argv[1]) == '+')
           set_file(argc,argv);
        show_file(argc,argv);
}

void show_help()
{
        printf("FA 1.0 (C)1991 Turgut Kalfaoglu,1378 Sok,8/10,Alsancak,Izmir,Turkey\n\n");
        printf("This program enables you to set the file attributes of your files.\n");
        printf("Usage: FA filespecs                - to view the current attributes\n");
        printf("       FA -attrib filespecs        - to remove an attribute\n");
        printf("       FA +attrib filespecs        - to add an attribute\n\n");
        printf("Attrib can be: (R)ead-only, (H)idden, (S)system, (V)olume,\n");
        printf("               s(U)bdirectory,(A)rchive\n");
        printf("File specs may include wildcards, and/or several files listed.\n");
        printf("Example: FA +R *.BAK MYFILE.C      - will make the files read-only\n\n");
        printf("User supported - $10 requested to the above address. Thank you.\n");
        exit(0);
}

void set_file(int n,char *fn[])
{
        int i,rc;
        unsigned a;
        char f,s;

        s = *fn[1];
        f = toupper(*(fn[1]+1));
        for(i=2;i < n;i++) {
                if ( (rc=DosQFileMode(fn[i],&a,0L)) != 0) {
                        printf("Error %d learning about %s\n",rc,fn[i]);
                        continue; } 
                switch (f) {
                        case 'R': if (s=='-') a &= 254;
                                     else a |= 1;
                                     break;
                        case 'H': if (s=='-') a &= 253;
                                     else a |= 2;
                                     break;
                        case 'S': if (s=='-') a &= 251;
                                     else a |= 4;
                                     break;
                        case 'V': if (s=='-') a &= 247;
                                     else a |= 8;
                                     break;
                        case 'U': if (s=='-') a &= 239;
                                     else a |= 16;
                                     break;
                        case 'A': if (s=='-') a &=223;
                                     else a |= 32;
                                     break;
                        default : printf("Not a known switch.\n");
                                     exit(1);
                        }
                if ( (rc=DosSetFileMode(fn[i],a,0L)) != 0)
                        printf("Error setting file attr %d for %s\n",a,fn[i]);
        }
        exit(0);
}
            
void show_file(int n, char *fn[])
{
        int i,rc;
        unsigned a;
        for (i=1;i<n;i++) {
                if ( (rc=DosQFileMode(fn[i],&a,0L)) != 0) {
                        printf("Error %d learning about %s\n",rc,fn[i]);
                        continue; }
                     
                if (a & 1)   printf("R");
                   else printf(" ");
                if (a & 2)   printf("H");
                   else printf(" ");
                if (a & 4)   printf("S");
                   else printf(" ");
                if (a & 8)   printf("V");
                   else printf(" ");
                if (a & 16)  printf("U");
                   else printf(" ");
                if (a & 32)  printf("A");
                   else printf(" ");
                if (a & 64)  printf("?");
                   else printf(" ");
                if (a & 128) printf("?");
                   else printf(" ");
                if (a & 256) printf("?");
                   else printf(" ");
                printf("     %s\n",fn[i]);
        }
        exit(0);
}
                