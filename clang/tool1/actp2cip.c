/*---------------------------------------------------------------------------*
 | actp2cip.c - 21:45.19.March.1999
 |
 | work = ﾌｫﾄｼｮｯﾌﾟの<*.ACT>形式のﾊﾟﾚｯﾄﾌｧｲﾙを<CI-Texture>ﾌｧｲﾙに変換する
 |
 | note = ACTﾌｧｲﾙはRGBのﾃﾞｰﾀがﾊﾞｲﾅﾘ－入っているだけなのでﾌｧｲﾙの認識は
 |        ﾂｰﾙではできない。その為、確認は使用する人が自分でするのが望
 |        ましい。無条件にﾊﾞｲﾅﾘｰﾌｧｲﾙから768ﾊﾞｲﾄ読み込んで、ﾃｷｽﾄﾌｧｲﾙへ
 |        変換を行うので使う時は注意してください。
 *---------------------------------------------------------------------------*/
/*------------------------------------------------------------*
 |  include
 *------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
/*------------------------------------------------------------*
 |  defines
 *------------------------------------------------------------*/
#define TRUE            1
#define FALSE           0
#define ON                      1
#define OFF                     0
#define DEBUG           ON
#define DEBUG_ON        ON
#define DEBUG_OFF       OFF

//****ﾌｧｲﾙｵｰﾌﾟﾝﾓｰﾄﾞ****
#define RB                      "rb"            // BINARY READ
#define WB                      "wb"            // BINARY WRITE
#define RT                      "rt"            // TXT READ
#define WT                      "wt"            // TXT WRITE

#define MAX_PAL 256
#define MAX_CHAR 256


/*------------------------------------------------------------*
 |  typedefs
 *------------------------------------------------------------*/
typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;
typedef unsigned long  ulong;


typedef struct {
        int count;
        struct {
                long flag;
                long pal_no;
        }info[MAX_PAL];
}NUKI;

/*------------------------------------------------------------*
 |  macros
 *------------------------------------------------------------*/
//------------------------------
//      ファイルオープン
//------------------------------
#define FOPEN(fp,filename,mode)\
        if((fp = fopen(filename,mode)) == NULL){\
                printf("ERROR : [%s]\n",filename);\
                printf("        指定ファイルが開けません。ファイル名を確認して下さい。\n");\
                exit(1);\
        }



/*------------------------------------------------------------*
 |  prototype
 *------------------------------------------------------------*/
void dispUsage( void );
int getFilenameAll(char *, char *);


/*------------------------------------------------------------*
 |  globals
 *------------------------------------------------------------*/
char inFileName[MAX_CHAR];                              /* 入力ﾌｧｲﾙ名                   */
char outFileName[MAX_CHAR];                             /* 出力ﾌｧｲﾙ名                   */
/*------------------------------------------------------------*
 |  codes
 *------------------------------------------------------------*/
int main(int argc,char *argv[])
{
        FILE    *infile, *outfile;
        static char*    helpTbl[] = {"-h","-?","/h","/?"};      // item=4
        uchar *palHead,*wp;
        uchar tRed,tGreen,tBlue,tAlpha;
        NUKI nuki;
        long i;
        
        
        
        /*--------------------------------------------------*/
        /* 抜きﾁｪｯｸ初期化                                                                       */
        nuki.count=0;
        for(i=0;i<MAX_PAL;i++){
                nuki.info[i].flag       = 0;
                nuki.info[i].pal_no     = 0;
        }

        
        
        /*--------------------------------------*/
        /* 引数のチェック                                               */
        switch(argc){
        case 1:
        case 2:
                dispUsage();
                exit(1);
                break;
        case 3:
                // fopen error check in macro. exit in macro.
                FOPEN(infile, argv[1],RB);
                FOPEN(outfile,argv[2],WT);
                break;
        default:
                dispUsage();
                exit(1);
        }
        
        /* 入力＆出力ファイル名取得 */
        getFilenameAll(argv[1],inFileName);
        getFilenameAll(argv[2],outFileName);
        
        
        fprintf(outfile,"/*\n");
        fprintf(outfile,"    Input  File = [%s]\n",inFileName);
        fprintf(outfile,"    Output File = [%s]\n",outFileName);
        fprintf(outfile,"    １６色と２５６色のどちらのﾊﾟﾚｯﾄを使用するか確認する事\n");
        fprintf(outfile," */\n");


        // sizeofはこのｻｲｽﾞではﾀﾞﾒなので
        palHead = malloc(sizeof(uchar) * 3 * MAX_PAL);
        fread(palHead,sizeof(uchar),MAX_PAL*3,infile);
        
        wp=palHead;
        for(i=0;i<MAX_PAL;i++){
                tRed    = wp[0];
                tGreen  = wp[1];
                tBlue   = wp[2];
                
                tRed    >>= 3;
                tGreen  >>= 3;
                tBlue   >>= 3;
                if(0x0000 == (tRed|tGreen|tBlue)){
                        /* 透明 */
                        tAlpha = 0;
                        nuki.info[nuki.count].flag              = 1;
                        nuki.info[nuki.count].pal_no    = i;
                        nuki.count++;
                }else{
                        /* ベタ */
                        tAlpha = 1;
                }
                
                if( ((i)&15) == 0 ){
                        fprintf(outfile,"\t");
                        fprintf(outfile,"/* entry_tlut_no_%d */",i/16);
                        fprintf(outfile,"\n") ;
                        fprintf(outfile,"\t");
                }
                
                fprintf(outfile,"RGBA16CIP(%2d,%2d,%2d,%2d)",tRed,tGreen,tBlue,tAlpha);
                fprintf(outfile,",") ;
                
                if( ((i+1)&3) == 0 ){
                        fprintf(outfile,"\n") ;
                        fprintf(outfile,"\t");
                }
                
                wp+=3;
        }
        
        
        /*--------------------------------------*
         |  ﾌｧｲﾙ情報表示
         *--------------------------------------*/
        printf("--------[ use files ]\n");
        printf("  input  file = [%s]\n",inFileName);
        printf("  output file = [%s]\n",outFileName);
        
        /*--------------------------------------*
         |  ﾊﾟﾚｯﾄ情報表示
         *--------------------------------------*/
        printf("--------[ Alpha Information ]\n");
        printf("  AlphaCount  = %d\n",nuki.count);                              /* 透明ﾊﾟﾚｯﾄ数  */
        for(i=0;i<nuki.count;i++){                                                              /* 透明ﾊﾟﾚｯﾄ番号*/
                printf("  AlphaPalNO  = %d\n",nuki.info[i].pal_no);
        }
        printf("-----------------------------------------------------------\n");
        
        return EXIT_SUCCESS;
}


/*-----------------------------------------------------------------------------
        関数名  :getFilenameAll

        work    :ﾌｧｲﾙ名＋拡張子を取得する
        in              :*fullName = ﾌｧｲﾙ名のﾎﾟｲﾝﾀ
                         *newName  = 出力ﾌｧｲﾙ名のﾎﾟｲﾝﾀ
        out             :拡張子が在る : 1
                         拡張子が無し : 0
        note    :
-----------------------------------------------------------------------------*/
int getFilenameAll(char *fullName, char *newName)
{
        #define GFA_MOZI_MAX            256

        int i,j;
        i = j = 0;
        
        while(*fullName != '\0'){
                if(*fullName == '\\'){
                        j=0 ;                           //文字列 ｶｳﾝﾄ ｸﾘｱ
                }
                
                if(j>GFA_MOZI_MAX){
                        printf("ﾌｧｲﾙ名取得失敗\n");
                        exit(0);
                }
                if(*fullName == '\0'){
                        newName[i] = '\0';
                        return 1;
                }
                newName[i++] = *fullName++;
                j++;            //文字列カウント
        }
        return 0;
}


//----------------------------------------------
// void Usage() = ヘルプファイル
// in   :nothing
// out  :nothing
//----------------------------------------------
void dispUsage(void){
        puts("");
        puts("======================================================");
        puts("  actp2cip ver 0.01");
        puts("");
        puts("  usage: actp2cip <ActPalFile> <CiPalFile>");
        puts("       : supported PhotoShop ACT files");
        puts("======================================================");
        puts("");
}