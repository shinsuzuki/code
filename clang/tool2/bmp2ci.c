/*---------------------------------------------------------------------------*
 | bmp2ci.c 
 *---------------------------------------------------------------------------*/ 
/*------------------------------------------------------------*
 |  include
 *------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "bmp.h"
#include "bmp2ci.h"
/*------------------------------------------------------------*
 |  defines
 *------------------------------------------------------------*/
#define MAX_CHAR   256
#define MAX_PAL        256
#define PAL_16     16
#define PAL_256        256
#define MAX_PIXEL  320*240
/*------------------------------------------------------------*
 |  typdefs
 *------------------------------------------------------------*/
typedef struct {
    int count;
    struct {
        long flag;
        long pal_no;
    }info[MAX_PAL];
}NUKI;

typedef struct {
    long count;
    struct {
        long flag;
        long pixel_no;
    }info[MAX_PIXEL];
}NUKI16BIT;


/*------------------------------------------------------------*
 |  macros
 *------------------------------------------------------------*/
#define    RGBA16CIP(r,g,b,a)  (u16)(((r)<<11)|((g)<<6)|((b)<<1)|((a)&1))
/*------------------------------------------------------------*
 |  globals
 *------------------------------------------------------------*/
char fileName[MAX_CHAR];               /* ﾌｧｲﾙ名             */
char fileName_OUT[MAX_CHAR];           /* 出力ﾌｧｲﾙ名           */
char fileName_TMF_IMG[MAX_CHAR];       /* ﾋﾟｸｾﾙのｲﾝﾃﾞｯｸｽﾃﾞｰﾀ */
char fileName_TMF[MAX_CHAR];           /* ﾋﾟｸｾﾙの情報            */
char fileName_TLF_TLUT[MAX_CHAR];      /* ﾊﾟﾚｯﾄﾃﾞｰﾀ         */
char fileName_TLF[MAX_CHAR];           /* ﾊﾟﾚｯﾄ情報           */

char inFileName[MAX_CHAR];             /* 入力ﾌｧｲﾙ名           */
char outFileName[MAX_CHAR];                /* 出力ﾌｧｲﾙ名           */


/*---------------------------------------------------------------------------*
 |  code area
 *---------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    FILE   *infile, *outfile;
    static char*  helpTbl[] = {"-h","-?","/h","/?"};  // item=4
    
    static BITMAPFILEHEADER bmfh;
    static BITMAPINFOHEADER bmih;
    
    ulong TableCount;           /* 使用しているｶﾗｰﾃｰﾌﾞﾙ数 */
    int i;
    
    
    /*--------------------------------------*/
    /* 引数のチェック                       */
    switch(argc){
    case 1:
        DispUsage();
        exit(1);
        break;
    case 2:
        for(i=0;i<4;i++){
            if(!strcmp(argv[1],helpTbl[i])){
                DispUsage();
                exit(1);
            }
        }
        DispErr(1);
        exit(1);
        break;
    case 3:
        // fopen error check in macro. exit in macro.
        FOPEN(infile, argv[1],RB);
        FOPEN(outfile,argv[2],WT);
        break;
    default:
        DispErr(2);
        exit(1);
    }
    
    /*--------------------------------------*/
    /* ﾌｧｲﾙ名取得                           */
    getFilename(argv[1],fileName);
    getFilename(argv[2],fileName_OUT);
    
    /* 入力＆出力ファイル名取得 */
    getFilenameAll(argv[1],inFileName);
    getFilenameAll(argv[2],outFileName);
    
    /* ﾋﾟｸｾﾙのｲﾝﾃﾞｯｸｽ情報 */
    getFilename(argv[1],fileName_TMF_IMG);
    strcat(fileName_TMF_IMG,"_tmf_img");
    
    /* ﾋﾟｸｾﾙ情報 */
    getFilename(argv[1],fileName_TMF);
    strcat(fileName_TMF,"_tmf");
    
    /* ﾊﾟﾚｯﾄﾃﾞｰﾀ */
    getFilename(argv[1],fileName_TLF_TLUT);
    strcat(fileName_TLF_TLUT,"_tlf_tlut");
    
    /* ﾊﾟﾚｯﾄ情報 */
    getFilename(argv[1],fileName_TLF);
    strcat(fileName_TLF,"_tlf");
    
    
    /*--------------------------------------*/
    /* BMPﾌｧｲﾙﾍｯﾀﾞﾁｪｯｸ                     */
    if( !checkFileHeader(&bmfh,infile) ){
        fclose(infile);
        fclose(outfile);
        DispErr(1);
        exit(1);
    }
    
    
    /*--------------------------------------*/
    /* BMPｲﾝﾌｫﾒｰｼｮﾝﾍｯﾀﾞﾁｪｯｸ                  */
    TableCount = checkBmpInfo(&bmfh,&bmih,infile,outfile);
    
    
    /*--------------------------------------*/
    /* ﾋﾞｯﾄｶｳﾝﾄﾁｪｯｸ(4bit,8bit,24bit support)       */
    switch(bmih.biBitCount){
    case 4:
        Bmp4Bit2Ci4Bit(&bmih,TableCount,infile,outfile);
        break;
    case 8:
        Bmp8Bit2Ci8Bit(&bmih,TableCount,infile,outfile);
        break;
    case 24:
        Bmp24Bit2RGBA16Bit(&bmih,infile,outfile);
        break;
    case 1:
        puts("ERR: Sorry, this bitcount is not supported.\n");
        break;
    default:
        puts("ERR: Unknown color format.\n");
        break;
    }
    
    
    fclose(infile);
    fclose(outfile);
    
    return EXIT_SUCCESS;
}


/*-----------------------------------------------------------------------------
   関数名   :

   work    :24ﾋﾞｯﾄBMPﾌｧｲﾙを16ﾋﾞｯﾄRGBAﾌｧｲﾙへ変換する
   in      :BITMAPINFOHEADER *pBmih,
            ulong TblCnt,
            FILE* iFile,
            FILE* oFile
   out     :nothing
   note    :
            
-----------------------------------------------------------------------------*/
void Bmp24Bit2RGBA16Bit(BITMAPINFOHEADER *pBmih,FILE* iFile,FILE* oFile)
{
    RGBQUAD24 *pPixelHead;      /* ﾋﾟｸｾﾙﾃﾞｰﾀへのﾎﾟｲﾝﾀ（1677万色）*/
    RGBQUAD24 pdat;
    long i,j;
    uchar elRed,elGreen,elBlue;
    ushort *pixTmp,*pixTmp2;
    NUKI16BIT nuki16b;
    
    /*******************/
    /* nuki16b init */
    nuki16b.count=0;

    for(i=0;i<MAX_PIXEL;i++){
        nuki16b.info[i].flag        = OFF;
        nuki16b.info[i].pixel_no    = 0;
    }

    /*-- ﾋﾟｸｾﾙﾃﾞｰﾀの先頭へ-- */
    // 24-bit ｶﾗｰはｶﾗｰﾃｰﾌﾞﾙが存在しません
    //1677万色だから4ﾊﾞｲﾄで１ﾋﾟｸｾﾙ分ﾃﾞｰﾀを読み込む
    pPixelHead=(RGBQUAD24 *)malloc(sizeof(RGBQUAD24) * pBmih->biWidth * pBmih->biHeight);
    fread(pPixelHead,sizeof(RGBQUAD24),pBmih->biWidth * pBmih->biHeight,iFile);

    /* 中間ﾃﾞｰﾀ作成 */
    pixTmp = (ushort *)malloc(sizeof(ushort) * pBmih->biWidth * pBmih->biHeight);
    
    for(i=0;i<pBmih->biHeight;i++){
        for(j=0;j<pBmih->biWidth;j++){
            pdat = *(pPixelHead+(i*pBmih->biWidth)+(j));
            
            elRed   = pdat.rgbRed;
            elGreen = pdat.rgbGreen;
            elBlue  = pdat.rgbBlue;
            
            /* 888->555 Convert */
            elRed   >>= 3;
            elGreen >>= 3;
            elBlue  >>= 3;
            
            if( 0x0000 == (elRed|elGreen|elBlue) ){
            /* nuki on*/
                pixTmp[i*pBmih->biWidth + j]=(elRed<<11) | (elGreen<<6) | (elBlue<<1) | 0x0000;
                
                /* 透明ﾋﾟｸｾﾙをﾁｪｯｸ */
                nuki16b.info[nuki16b.count].flag     = ON;
                nuki16b.info[nuki16b.count].pixel_no = (i*pBmih->biWidth) + (j);
                nuki16b.count++;
                
            }else{
            /* nuki off */
                pixTmp[i*pBmih->biWidth + j]=(elRed<<11) | (elGreen<<6) | (elBlue<<1) | 0x0001;
                
            }
        }
    }
    
    /* 上下反転 */
    pixTmp2 = (ushort *)malloc(sizeof(ushort) * pBmih->biWidth * pBmih->biHeight);
    for(i=0;i<pBmih->biHeight * pBmih->biWidth;i++){
        pixTmp2[i]=pixTmp[(pBmih->biHeight * pBmih->biWidth)-i-1];
    }
    
    /* 左右反転 */
    for(i=0;i<pBmih->biHeight;i++){
        for(j=0;j<pBmih->biWidth;j++){
            pixTmp[i*pBmih->biWidth + (pBmih->biWidth-1-j)]=
                                    pixTmp2[i * pBmih->biWidth + j];
        }
    }
    
    /*------------------------------------------------------------*
    |  
    *------------------------------------------------------------*/
    /* ﾌｧｲﾙﾍｯﾀﾞ出力 */
    fprintf(oFile,"/*---------------------------------------------------------------------------*\n");
    fprintf(oFile," | %s",outFileName);
    fprintf(oFile," - BETA/16BIT-RGBA\n",outFileName);
    fprintf(oFile," |\n");
    fprintf(oFile," |  in  file = %s \n",inFileName);
    fprintf(oFile," |  out file = %s \n",outFileName);
    fprintf(oFile," |\n");
    fprintf(oFile," |  image height   = %d\n",pBmih->biHeight);
    fprintf(oFile," |  image width    = %d\n",pBmih->biWidth);
    fprintf(oFile," |  image format   = G_IM_FMT_RGBA\n");
    fprintf(oFile," |  image bit size = G_IM_SIZ_16b\n");
    fprintf(oFile," |  tlut type      = nothing\n");
    fprintf(oFile," |  tlut size      = 0\n");
    fprintf(oFile," |\n");
    fprintf(oFile," *---------------------------------------------------------------------------*/ \n");
    fprintf(oFile,"#ifndef _%s_H_\n",fileName);
    fprintf(oFile,"#define _%s_H_\n",fileName);

    fprintf(oFile,"/*------------------------------------------------------------*\n");
    fprintf(oFile," | include\n");
    fprintf(oFile," *------------------------------------------------------------*/\n");
    fprintf(oFile,"#include \"sprite.h\"\n");

    fprintf(oFile,"/*------------------------------------------------------------*\n");
    fprintf(oFile," | externs\n");
    fprintf(oFile," *------------------------------------------------------------*/\n");
    
    fprintf(oFile,"extern TMF %s;\n",fileName_TMF);
    fprintf(oFile,"extern u16 %s[];\n",fileName_TLF_TLUT);
    fprintf(oFile,"extern TLF %s;\n",fileName_TLF);
    fprintf(oFile,"extern PICTURE %s;\n",fileName);
    
    fprintf(oFile,"/*------------------------------------------------------------*\n");
    fprintf(oFile," | SPRITE DATA\n");
    fprintf(oFile," *------------------------------------------------------------*/\n");
    
    
    /*------------------------------*/
    /* ｲﾝﾃﾞｯｸｽ情報出力               */
    fprintf(oFile,"static Gfx %s_C_dummy_aligner1[] = { gsSPEndDisplayList() };\n",fileName_TMF_IMG);
    fprintf(oFile,"\n");
    fprintf(oFile,"static u32 %s[]\n",fileName_TMF_IMG);
    fprintf(oFile,"={\n");
    
    for(i=0; i<(pBmih->biWidth * pBmih->biHeight);i++){

        if(!i) fprintf(oFile,"\t");                   /* 最初のみ */
        if( !(i&1) ) fprintf(oFile,"0x");         /* 2回に一回  */

        fprintf(oFile,"%04x",pixTmp[i]);

        if( !((i+1)&1) ) fprintf(oFile,",");     /* 2回に一回 */
        
        if( ((i+1)&15) == 0 ){                     /* 16回に一回 */
            fprintf(oFile,"\n");
            fprintf(oFile,"\t");
        }
    }
    
    
    fprintf(oFile,"\n");
    fprintf(oFile,"};\n");              /* ﾋﾟｸｾﾙの情報出力終了 */
    
    /*------------------------------*/
    /* ｲﾝﾃﾞｯｸｽ情報出力               */
    fprintf(oFile,"\n");
    fprintf(oFile,"\n");
    fprintf(oFile,"static Gfx %s_C_dummy_aligner1[] = { gsSPEndDisplayList() };\n",fileName_TMF);
    fprintf(oFile,"\n");

    fprintf(oFile,"static TMF %s\n",fileName_TMF);
    fprintf(oFile,"={\n");
    fprintf(oFile,"\t%s,\t/* image address\t*/\n",fileName_TMF_IMG);
    fprintf(oFile,"\tG_IM_FMT_RGBA,\t/* image format\t\t*/\n");
    fprintf(oFile,"\tG_IM_SIZ_16b,\t/* image bit size\t*/\n");
    fprintf(oFile,"\t%d,\t\t\t/* image width\t\t*/\n",pBmih->biWidth);
    fprintf(oFile,"\t%d,\t\t\t/* image height\t\t*/\n",pBmih->biHeight);
    fprintf(oFile,"};\n");
    
    
    /* ﾀﾞﾐｰﾊﾟﾚｯﾄ */
    fprintf(oFile,"\n");
    fprintf(oFile,"\n");
    fprintf(oFile,"static Gfx %s_C_dummy_aligner1[] = { gsSPEndDisplayList() };\n",fileName_TLF_TLUT);
    fprintf(oFile,"\n");
    fprintf(oFile,"static u16 %s[]\n",fileName_TLF_TLUT);
    fprintf(oFile,"={0};\n");           /* ﾋﾟｸｾﾙのｲﾝﾃﾞｯｸｽ情報出力終了 */

        /*------------------------------*/
    /* ﾊﾟﾚｯﾄ情報出力             */
    fprintf(oFile,"\n");
    fprintf(oFile,"\n");
    fprintf(oFile,"static Gfx %s_C_dummy_aligner1[] = { gsSPEndDisplayList() };\n",fileName_TLF);
    fprintf(oFile,"\n");
    fprintf(oFile,"static TLF %s\n",fileName_TLF);
    fprintf(oFile,"={\n");
    fprintf(oFile,"\tG_TT_RGBA16,\t\t/* TLUT type\t\t*/\n");
    fprintf(oFile,"\t0,\t/* TLUT address\t\t*/\n",fileName_TLF_TLUT);
    fprintf(oFile,"\t0,\t\t\t\t\t/* TLUT size\t\t*/\n");
    fprintf(oFile,"};\n");

    /*------------------------------*/
    /* ｽﾌﾟﾗｲﾄ情報出力              */
    fprintf(oFile,"\n");
    fprintf(oFile,"\n");
    fprintf(oFile,"static Gfx %s_C_dummy_aligner1[] = { gsSPEndDisplayList() };\n",fileName);
    fprintf(oFile,"\n");
// fprintf(oFile,"static PICTURE %s\n",fileName);
    fprintf(oFile,"PICTURE %s\n",fileName);
    fprintf(oFile,"={\n");
    fprintf(oFile,"\t&%s,\n",fileName_TMF);
    fprintf(oFile,"\t&%s,\n",fileName_TLF);
    fprintf(oFile,"\t0,\n");
    fprintf(oFile,"};\n");
    
    fprintf(oFile,"/*------------------------------------------------------------*\n");
    fprintf(oFile," | end of %s\n",outFileName);
    fprintf(oFile," *------------------------------------------------------------*/\n");
    
    fprintf(oFile,"#endif\n");

    printf("--------[ 16Bit-RGBA Texture Information ]\n");
    printf("  FILE        = [%s]\n",outFileName);          /* 出力ﾌｧｲﾙ名   */
    printf("  Width       = %ld\n", pBmih->biWidth);     /* 幅         */
    printf("  Height      = %ld\n", pBmih->biHeight);        /* 高さ          */
    printf("  Colors      = 16-Bit : 65536 colors\n");      /* ｶﾗｰ           */
    printf("--------[ Alpha Information ]\n");
    printf("  AlphaCount  = %d\n",nuki16b.count);           /* 透明ﾋﾟｸｾﾙ数    */
    for(i=0;i<nuki16b.count;i++){                             /* 透明ﾋﾟｸｾﾙ番号*/
        printf("  AlphaPixelNO  = %d\n",nuki16b.info[i].pixel_no);
    }
    printf("-----------------------------------------------------------\n");
    
    free(pixTmp);
    free(pixTmp2);
}


/*-----------------------------------------------------------------------------
   関数名   :Bmp4Bit2Ci4Bit

   work    :4ﾋﾞｯﾄBMPﾌｧｲﾙを4ﾋﾞｯﾄCIﾌｧｲﾙへ変換する
   in      :BITMAPINFOHEADER *pBmih,
            ulong TblCnt,
            FILE* iFile,
            FILE* oFile
   out     :nothing
   note    :CIﾌｧｲﾙ内に、ｲﾝﾃﾞｯｸｽﾃﾞｰﾀとﾊﾟﾚｯﾄﾃﾞｰﾀ、各情報も付属して出力します。
            ﾊﾟﾚｯﾄ数が16個未満の場合は、ﾀﾞﾐｰを出力してﾊﾟﾚｯﾄ数を合わせます。
-----------------------------------------------------------------------------*/
void Bmp4Bit2Ci4Bit(BITMAPINFOHEADER *pBmih,ulong TblCnt,FILE* iFile,FILE* oFile)
{
    uchar *pPixelHead;                  /* ﾋﾟｸｾﾙﾃﾞｰﾀへのﾎﾟｲﾝﾀ（16色用） */
    uchar *pTmpPixel_1,*pTmpPixel_2;    /* 作業ｴﾘｱへのﾎﾟｲﾝﾀ */
    
    RGBQUAD *pColTblHead;       /* ｶﾗｰﾃｰﾌﾞﾙへのﾎﾟｲﾝﾀ */
    RGBQUAD wColTbl;            /* ﾊﾟﾚｯﾄの作業用 */
    ushort palRed,palGreen,palBlue,palAlpha;
    long i,j;
    
    NUKI nuki;
    
    
    /*--------------------------------------------------*/
    /* 抜きﾁｪｯｸ初期化                                 */
    nuki.count=0;
    for(i=0;i<MAX_PAL;i++){
        nuki.info[i].flag   = OFF;
        nuki.info[i].pal_no = 0;
    }

    /* 4,8bitColorの時はｶﾗｰﾃｰﾌﾞﾙ有り */
    /* ｶﾗｰﾃｰﾌﾞﾙ読み込み */
    pColTblHead = (RGBQUAD *)malloc( sizeof(RGBQUAD) * TblCnt );
    fread(pColTblHead,sizeof(RGBQUAD),TblCnt,iFile);
    
    
    /*-- ﾋﾟｸｾﾙﾃﾞｰﾀの先頭へ-- */
    /*16色だから1index=１/2ﾊﾞｲﾄ(4bit)、ﾋﾟｸｾﾙ分ﾃﾞｰﾀを読み込む*/
    /*うまくいかないので uchar で処理する、読み込むサイズは半分になる*/
    /* ﾋﾟｸｾﾙのｲﾝﾃﾞｯｸｽﾃﾞｰﾀを１８０度反転して出力すればＯＫ */
    pPixelHead=(uchar *)malloc( sizeof(uchar)* pBmih->biWidth * (pBmih->biHeight/2) );
    fread(pPixelHead,sizeof(uchar),(pBmih->biWidth * pBmih->biHeight)/2,iFile);

#if DEBUG_OFF
    printf("Color Table Count = [%ld]\n",TblCnt);
    printf("Color Table size  = [%ld]\n",TblCnt*sizeof(RGBQUAD));
    printf("Pixel Data size   = [%ld]\n",(long)( (sizeof(uchar) * pBmih->biWidth * pBmih->biHeight)/2) );
#endif
    
    /* 中間ﾃﾞｰﾀ作成 */
    pTmpPixel_1 = (uchar *)malloc( sizeof(uchar) * pBmih->biWidth * (pBmih->biHeight/2) );
    pTmpPixel_2 = (uchar *)malloc( sizeof(uchar) * pBmih->biWidth * (pBmih->biHeight/2) );
    
    /* 上下反転 */
    for(i=0;i<pBmih->biHeight * (pBmih->biWidth/2);i++){
        pTmpPixel_1[i]=pPixelHead[(pBmih->biHeight * (pBmih->biWidth/2))-i-1];
    }

    
    /* 左右反転 */
    for(i=0;i<pBmih->biHeight;i++){
        for(j=0;j<(pBmih->biWidth/2);j++){
            pTmpPixel_2[i*(pBmih->biWidth/2) + ((pBmih->biWidth/2)-1-j)]=
                                    pTmpPixel_1[i * (pBmih->biWidth/2) + j];
        }
    }

/*------------------------------------------------------------*
 |  ファイルへ出力します
 *------------------------------------------------------------*/
    /* ﾌｧｲﾙﾍｯﾀﾞ出力 */
    fprintf(oFile,"/*---------------------------------------------------------------------------*\n");
    fprintf(oFile," | %s",outFileName);
    fprintf(oFile," - 16色/16BIT-RGBA\n");
    fprintf(oFile," |\n");
    fprintf(oFile," |  in  file = %s \n",inFileName);
    fprintf(oFile," |  out file = %s \n",outFileName);
    fprintf(oFile," |\n");
    fprintf(oFile," |  image height   = %d\n",pBmih->biHeight);
    fprintf(oFile," |  image width    = %d\n",pBmih->biWidth);
    fprintf(oFile," |  image format   = G_IM_FMT_CI\n");
    fprintf(oFile," |  image bit size = G_IM_SIZ_4b\n");
    fprintf(oFile," |  tlut type      = G_TT_RGBA16\n");
    fprintf(oFile," |  tlut size      = 16\n");
    fprintf(oFile," |  usePalette     = %2d/16\n",TblCnt);
    fprintf(oFile," |  dmyPalette     = %2d/16\n",PAL_16 - TblCnt);
    fprintf(oFile," |\n");
    fprintf(oFile," *---------------------------------------------------------------------------*/ \n");
    fprintf(oFile,"#ifndef _%s_H_\n",fileName);
    fprintf(oFile,"#define _%s_H_\n",fileName);

    fprintf(oFile,"/*------------------------------------------------------------*\n");
    fprintf(oFile," | include\n");
    fprintf(oFile," *------------------------------------------------------------*/\n");
    fprintf(oFile,"#include \"sprite.h\"\n");

    fprintf(oFile,"/*------------------------------------------------------------*\n");
    fprintf(oFile," | externs\n");
    fprintf(oFile," *------------------------------------------------------------*/\n");
    
    fprintf(oFile,"extern TMF %s;\n",fileName_TMF);
    fprintf(oFile,"extern u16 %s[];\n",fileName_TLF_TLUT);
    fprintf(oFile,"extern TLF %s;\n",fileName_TLF);
    fprintf(oFile,"extern PICTURE %s;\n",fileName);
    
    fprintf(oFile,"/*------------------------------------------------------------*\n");
    fprintf(oFile," | SPRITE DATA\n");
    fprintf(oFile," *------------------------------------------------------------*/\n");
    
    
    /*------------------------------*/
    /* ｲﾝﾃﾞｯｸｽ情報出力               */
    fprintf(oFile,"static Gfx %s_C_dummy_aligner1[] = { gsSPEndDisplayList() };\n",fileName_TMF_IMG);
    fprintf(oFile,"\n");
    fprintf(oFile,"static u32 %s[]\n",fileName_TMF_IMG);
    fprintf(oFile,"={\n");
    /* 
       ﾋﾟｸｾﾙのｲﾝﾃﾞｯｸｽﾃﾞｰﾀは１ﾊﾞｲﾄで２ﾋﾟｸｾﾙ分だが、１ﾊﾞｲﾄ単位で出力。
       出力ｻｲｽﾞは （縦ﾋﾟｸｾﾙ数＊横ﾋﾟｸｾﾙ数/２）ﾊﾞｲﾄです。
   */
    for(i=0;i<pBmih->biHeight*(pBmih->biWidth/2);i++){

        if(!i) fprintf(oFile,"\t");                   /* 最初のみ */
        if( !(i&3) ) fprintf(oFile,"0x");         /*  4回に一回  */
        fprintf(oFile,"%02x",pTmpPixel_2[i]);
        if( !((i+1)&3) ) fprintf(oFile,",");
        
        if( ((i+1)&15) == 0 ){                     /* 16回に一回 */
            fprintf(oFile,"\n") ;
            fprintf(oFile,"\t");
        }
    }
    fprintf(oFile,"\n");
    fprintf(oFile,"};\n");              /* ﾋﾟｸｾﾙのｲﾝﾃﾞｯｸｽ情報出力終了 */
    
    /*------------------------------*/
    /* ｲﾝﾃﾞｯｸｽ情報出力               */
    fprintf(oFile,"\n");
    fprintf(oFile,"\n");
    fprintf(oFile,"static Gfx %s_C_dummy_aligner1[] = { gsSPEndDisplayList() };\n",fileName_TMF);
    fprintf(oFile,"\n");
    fprintf(oFile,"static TMF %s\n",fileName_TMF);
    fprintf(oFile,"={\n");
    fprintf(oFile,"\t%s,\t/* image address\t*/\n",fileName_TMF_IMG);
    fprintf(oFile,"\tG_IM_FMT_CI,\t/* image format\t\t*/\n");
    fprintf(oFile,"\tG_IM_SIZ_4b,\t/* image bit size\t*/\n");
    fprintf(oFile,"\t%d,\t\t\t/* image width\t\t*/\n",pBmih->biWidth);
    fprintf(oFile,"\t%d,\t\t\t/* image height\t\t*/\n",pBmih->biHeight);
    fprintf(oFile,"};\n");


    /*------------------------------*/
    /* ﾊﾟﾚｯﾄﾃﾞｰﾀ出力               */
    fprintf(oFile,"\n");
    fprintf(oFile,"\n");
    fprintf(oFile,"static Gfx %s_C_dummy_aligner1[] = { gsSPEndDisplayList() };\n",fileName_TLF_TLUT);
    fprintf(oFile,"\n");
    fprintf(oFile,"static u16 %s[]\n",fileName_TLF_TLUT);
    fprintf(oFile,"={\n");

    for(i=0;i<16;i++){
        if(i<TblCnt){
            /* ﾃｰﾌﾞﾙ数出力 */
            wColTbl=pColTblHead[i];

            palRed = wColTbl.rgbRed;
            palBlue = wColTbl.rgbBlue;
            palGreen = wColTbl.rgbGreen;

//         palRed   >>= 3;   /* 下位３ﾋﾞｯﾄを切る */
//         palGreen >>= 3;   
//         palBlue  >>= 3;   
            
            if( 0x0000==(palRed | palGreen | palBlue) ){
                nuki.info[nuki.count].flag      = ON;
                nuki.info[nuki.count].pal_no    = i;
                nuki.count++;
                
                palAlpha = 0;      /* ヌキにします */
            }else{
                palAlpha = 1;      /* ベタ */
            }
            
            if( ((i)&15) == 0 ){
                fprintf(oFile,"\t");
                fprintf(oFile,"/* entry_tlut_no_%d */",i/16);
                fprintf(oFile,"\n") ;
                fprintf(oFile,"\t");
            }
            
            fprintf(oFile,"IAP(255,%3d)",palBlue);
            
            fprintf(oFile,",") ;
            
            if( ((i+1)&3) == 0 ){
                fprintf(oFile,"\n") ;
                fprintf(oFile,"\t");
            }
        }else{
            if( ((i)&15) == 0 ){
                fprintf(oFile,"/* entry_tlut_no_%d */",i/16);
                fprintf(oFile,"\n") ;
                fprintf(oFile,"\t");
            }
            /* 16個に足りない分ﾀﾞﾐｰで出力 */
            fprintf(oFile,"IAP( 255,0)");
            fprintf(oFile,",") ;
            
            if( ((i+1)&3) == 0 ){
                fprintf(oFile,"\n") ;
                fprintf(oFile,"\t");
            }
        }
    }

    fprintf(oFile,"\n");
    fprintf(oFile,"};\n");              /* ﾋﾟｸｾﾙのｲﾝﾃﾞｯｸｽ情報出力終了 */
    
    

    /*--------------------------------------*
    |  ﾃｸｽﾁｬ各情報表示
    *--------------------------------------*/
    printf("--------[ CI-4Bit Texture Information ]\n");
    printf("  FILE        = [%s]\n",outFileName);          /* 出力ﾌｧｲﾙ名   */
    printf("  Width       = %ld\n", pBmih->biWidth);     /* 幅         */
    printf("  Height      = %ld\n", pBmih->biHeight);        /* 高さ          */
    printf("  Colors      = 4-Bit : Index 16 colors\n");            /* ｶﾗｰ           */
    printf("  UsePalette  = %2d/16\n",TblCnt);             /* 使用ﾊﾟﾚｯﾄ数    */
    printf("  DmyPalette  = %2d/16\n",PAL_16 - TblCnt);        /* ﾀﾞﾐｰﾊﾟﾚｯﾄ数  */
    if((PAL_16 - TblCnt)){
        printf("  DmyPalOut   = RGBA16CIP( 0, 0, 0, 0)\n");     /* ﾀﾞﾐｰ出力      */   
    }
    
    printf("--------[ Alpha Information ]\n");
    printf("  AlphaCount  = %d\n",nuki.count);              /* 透明ﾊﾟﾚｯﾄ数    */
    for(j=0;j<nuki.count;j++){                                /* 透明ﾊﾟﾚｯﾄ番号*/
        printf("  AlphaPalNO  = %d\n",nuki.info[j].pal_no);
    }
    printf("-----------------------------------------------------------\n");
    
    
    /*------------------------------*/
    /* ﾊﾟﾚｯﾄ情報出力             */
    fprintf(oFile,"\n");
    fprintf(oFile,"\n");
    fprintf(oFile,"static Gfx %s_C_dummy_aligner1[] = { gsSPEndDisplayList() };\n",fileName_TLF);
    fprintf(oFile,"\n");
    fprintf(oFile,"static TLF %s\n",fileName_TLF);
    fprintf(oFile,"={\n");
    fprintf(oFile,"\tG_TT_RGBA16,\t\t/* TLUT type\t\t*/\n");
    fprintf(oFile,"\t%s,\t/* TLUT address\t\t*/\n",fileName_TLF_TLUT);
    fprintf(oFile,"\t16,\t\t\t\t\t/* TLUT size\t\t*/\n");
    fprintf(oFile,"};\n");

    /*------------------------------*/
    /* ｽﾌﾟﾗｲﾄ情報出力              */
    fprintf(oFile,"\n");
    fprintf(oFile,"\n");
    fprintf(oFile,"static Gfx %s_C_dummy_aligner1[] = { gsSPEndDisplayList() };\n",fileName);
    fprintf(oFile,"\n");
// fprintf(oFile,"static PICTURE %s\n",fileName);
    fprintf(oFile,"PICTURE %s\n",fileName);
    fprintf(oFile,"={\n");
    
    fprintf(oFile,"\t&%s,\n",fileName_TMF);
    fprintf(oFile,"\t&%s,\n",fileName_TLF);
    fprintf(oFile,"\t0,\n");
    fprintf(oFile,"};\n");
    
    fprintf(oFile,"/*------------------------------------------------------------*\n");
    fprintf(oFile," | end of %s\n",outFileName);
    fprintf(oFile," *------------------------------------------------------------*/\n");
    
    fprintf(oFile,"#endif\n");
    
    free(pPixelHead);
    free(pColTblHead);
    free(pTmpPixel_1);
    free(pTmpPixel_2);
}


/*-----------------------------------------------------------------------------
   関数名   :Bmp8Bit2Ci8Bit

   work    :8ﾋﾞｯﾄBMPﾌｧｲﾙを8ﾋﾞｯﾄCIﾌｧｲﾙへ変換する
   in      :BITMAPINFOHEADER *pBmih,
            ulong TblCnt,
            FILE* iFile,
            FILE* oFile
   out     :nothing
   note    :CIﾌｧｲﾙ内に、ﾋﾟｸｾﾙﾃﾞｰﾀとﾊﾟﾚｯﾄﾃﾞｰﾀ、各情報も付属して出力します。
            ﾊﾟﾚｯﾄ数が256個未満の場合は、ﾀﾞﾐｰ(0x0000)を出力してﾊﾟﾚｯﾄ数を合
            わせます。
-----------------------------------------------------------------------------*/
void Bmp8Bit2Ci8Bit(BITMAPINFOHEADER *pBmih,ulong TblCnt,FILE* iFile,FILE* oFile)
{
    uchar *pPixelHead;                  /* ﾋﾟｸｾﾙﾃﾞｰﾀへのﾎﾟｲﾝﾀ（256色用） */
    uchar *pTmpPixel_1,*pTmpPixel_2;    /* 作業ｴﾘｱへのﾎﾟｲﾝﾀ */
    
    RGBQUAD *pColTblHead;       /* ｶﾗｰﾃｰﾌﾞﾙへのﾎﾟｲﾝﾀ */
    RGBQUAD wColTbl;            /* ﾊﾟﾚｯﾄの作業用 */
    ushort palRed,palGreen,palBlue,palAlpha;
    long i,j;

    NUKI nuki;
    int lpcnt=0;
    
    
    
    /*--------------------------------------------------*/
    /* 抜きﾁｪｯｸ初期化                                 */
    nuki.count=0;
    for(i=0;i<MAX_PAL;i++){
        nuki.info[i].flag   = OFF;
        nuki.info[i].pal_no = 0;
    }
    
    
    /*--------------------------------------------------*/
    /* ｶﾗｰﾃｰﾌﾞﾙ読み込み,4,8bitColorの時はｶﾗｰﾃｰﾌﾞﾙ有り */
    pColTblHead = (RGBQUAD *)malloc( sizeof(RGBQUAD) * TblCnt );
    fread(pColTblHead,sizeof(RGBQUAD),TblCnt,iFile);
    
    
    /*----------------------------------------------------------*/
    /* 256色だから1index=１ﾊﾞｲﾄ(8bit)、ﾋﾟｸｾﾙ分ﾃﾞｰﾀを読み込む */
    pPixelHead=(uchar *)malloc( sizeof(uchar)* pBmih->biWidth * (pBmih->biHeight) );
    fread(pPixelHead,sizeof(uchar),(pBmih->biWidth * pBmih->biHeight),iFile);

#if DEBUG_OFF
    printf("\tColor Table Count = [%ld]\n",TblCnt);
    printf("\tColor Table size  = [%ld]\n",TblCnt*sizeof(RGBQUAD));
    printf("\tPixel Data size   = [%ld]\n",(long)( (sizeof(uchar) * pBmih->biWidth * pBmih->biHeight)) );
#endif
    
    /* 中間ﾃﾞｰﾀ作成 */
    pTmpPixel_1 = (uchar *)malloc( sizeof(uchar) * pBmih->biWidth * (pBmih->biHeight) );
    pTmpPixel_2 = (uchar *)malloc( sizeof(uchar) * pBmih->biWidth * (pBmih->biHeight) );
    
    
    /* 上下反転 */
    for(i=0;i<pBmih->biHeight * pBmih->biWidth;i++){
        pTmpPixel_1[i]=pPixelHead[(pBmih->biHeight * pBmih->biWidth)-i-1];
    }
    
    /* 左右反転 */
    for(i=0;i<pBmih->biHeight;i++){
        for(j=0;j<pBmih->biWidth;j++){
            pTmpPixel_2[i*pBmih->biWidth + (pBmih->biWidth-1-j)]=
                                    pTmpPixel_1[i * pBmih->biWidth + j];
        }
    }


/*------------------------------------------------------------*
 |  ▼ファイルへ出力します▼
 *------------------------------------------------------------*/

    /* ﾌｧｲﾙﾍｯﾀﾞ出力 */
    fprintf(oFile,"/*---------------------------------------------------------------------------*\n");
    fprintf(oFile," | %s",outFileName);
    fprintf(oFile," - 256色/16BIT-RGBA \n");
    fprintf(oFile," |\n");
    fprintf(oFile," |  in  file = %s \n",inFileName);
    fprintf(oFile," |  out file = %s \n",outFileName);
    fprintf(oFile," |\n");
    fprintf(oFile," |  image height   = %d\n",pBmih->biHeight);
    fprintf(oFile," |  image width    = %d\n",pBmih->biWidth);
    fprintf(oFile," |  image format   = G_IM_FMT_CI\n");
    fprintf(oFile," |  image bit size = G_IM_SIZ_8b\n");
    fprintf(oFile," |  tlut type      = G_TT_RGBA16\n");
    fprintf(oFile," |  tlut size      = 256\n");
    fprintf(oFile," |  usePalette     = %2d/256\n",TblCnt);
    fprintf(oFile," |  dmyPalette     = %2d/256\n",PAL_256 - TblCnt);
    fprintf(oFile," |\n");
    fprintf(oFile," *---------------------------------------------------------------------------*/ \n");
    fprintf(oFile,"#ifndef _%s_H_\n",fileName);
    fprintf(oFile,"#define _%s_H_\n",fileName);

    fprintf(oFile,"/*------------------------------------------------------------*\n");
    fprintf(oFile," | include\n");
    fprintf(oFile," *------------------------------------------------------------*/\n");
    fprintf(oFile,"#include \"sprite.h\"\n");

    fprintf(oFile,"/*------------------------------------------------------------*\n");
    fprintf(oFile," | externs\n");
    fprintf(oFile," *------------------------------------------------------------*/\n");
    
    fprintf(oFile,"extern TMF %s;\n",fileName_TMF);
    fprintf(oFile,"extern u16 %s[];\n",fileName_TLF_TLUT);
    fprintf(oFile,"extern TLF %s;\n",fileName_TLF);
    fprintf(oFile,"extern PICTURE %s;\n",fileName);
    
    fprintf(oFile,"/*------------------------------------------------------------*\n");
    fprintf(oFile," | SPRITE DATA\n");
    fprintf(oFile," *------------------------------------------------------------*/\n");
    
    
    /*------------------------------*/
    /* ｲﾝﾃﾞｯｸｽ情報出力               */
    fprintf(oFile,"static Gfx %s_C_dummy_aligner1[] = { gsSPEndDisplayList() };\n",fileName_TMF_IMG);
    fprintf(oFile,"\n");
    fprintf(oFile,"static u32 %s[]\n",fileName_TMF_IMG);
    fprintf(oFile,"={\n");

    for(i=0;i<pBmih->biHeight*pBmih->biWidth;i++){
        if(!i){
            fprintf(oFile,"\t");
        }
        
        if( !(i&3) ){        //4回に一回
            fprintf(oFile,"0x");
        }
        fprintf(oFile,"%02x",pTmpPixel_2[i]);
        
        if( !((i+1)&3) ){
            fprintf(oFile,",") ;
        }
        
        if( ((i+1)&15) == 0 ){
            fprintf(oFile,"\n") ;
            fprintf(oFile,"\t");
        }
    }
    
    
    fprintf(oFile,"\n");
    fprintf(oFile,"};\n");              /* ﾋﾟｸｾﾙのｲﾝﾃﾞｯｸｽ情報出力終了 */

    /*------------------------------*/
    /* ｲﾝﾃﾞｯｸｽ情報出力               */
    fprintf(oFile,"\n");
    fprintf(oFile,"\n");
    fprintf(oFile,"static Gfx %s_C_dummy_aligner1[] = { gsSPEndDisplayList() };\n",fileName_TMF);
    fprintf(oFile,"\n");
    fprintf(oFile,"static TMF %s\n",fileName_TMF);
    fprintf(oFile,"={\n");
    fprintf(oFile,"\t%s,\t/* image address\t*/\n",fileName_TMF_IMG);
    fprintf(oFile,"\tG_IM_FMT_CI,\t/* image format\t\t*/\n");
    fprintf(oFile,"\tG_IM_SIZ_8b,\t/* image bit size\t*/\n");
    fprintf(oFile,"\t%d,\t\t\t/* image width\t\t*/\n",pBmih->biWidth);
    fprintf(oFile,"\t%d,\t\t\t/* image height\t\t*/\n",pBmih->biHeight);
    fprintf(oFile,"};\n");


    /*------------------------------*/
    /* ﾊﾟﾚｯﾄﾃﾞｰﾀ出力               */
    fprintf(oFile,"\n");
    fprintf(oFile,"\n");
    fprintf(oFile,"static Gfx %s_C_dummy_aligner1[] = { gsSPEndDisplayList() };\n",fileName_TLF_TLUT);
    fprintf(oFile,"\n");
    fprintf(oFile,"static u16 %s[]\n",fileName_TLF_TLUT);
    fprintf(oFile,"={\n");

    
    /* 
       BMP   PAL   :BBBBBBBBGGGGGGGGRRRRRRRRYYYYYYYY
       RGA16 PAL   :RRRRRGGGGGBBBBBBA
    */
    
    for(i=0;i<256;i++){
        if(i<TblCnt){
            /* ﾃｰﾌﾞﾙ数出力 */
            wColTbl=pColTblHead[i];

            palRed = wColTbl.rgbRed;
            palBlue = wColTbl.rgbBlue;
            palGreen = wColTbl.rgbGreen;

            palRed   >>= 3;  /* 下位３ﾋﾞｯﾄを切る */
            palGreen >>= 3;  
            palBlue  >>= 3;  
            
            /*
               減色時に抜きを設定、しかしこの方法ではｶﾗｰﾚﾍﾞﾙ８未満の
               ＲＧＢ数値は減色で、ｶﾗｰﾚﾍﾞﾙ０になるので、注意が必要に
               なります。
               ＜ｶﾗｰﾚﾍﾞﾙ：RGB＞
               
                   ０～２５５     段階を
                   ０～３２        段階にするためです
               
            */
            
            if( 0x0000==(palRed | palGreen | palBlue) ){
                nuki.info[nuki.count].flag      = ON;
                nuki.info[nuki.count].pal_no    = i;
                nuki.count++;
                
                palAlpha = 0;      /* ヌキにします */
            }else{
                palAlpha = 1;      /* ベタ */
            }
            
            
            if( ((i)&15) == 0 ){
                fprintf(oFile,"\t");
                fprintf(oFile,"/* entry_tlut_no_%d */",i/16);
                fprintf(oFile,"\n") ;
                fprintf(oFile,"\t");
            }

            fprintf(oFile,"RGBA16CIP(%2d,%2d,%2d,%2d)",palRed,palGreen,palBlue,palAlpha);
            
            fprintf(oFile,",") ;
            
            if( ((i+1)&3) == 0 ){
                fprintf(oFile,"\n") ;
                fprintf(oFile,"\t");
            }
        }else{
            if( ((i)&15) == 0 ){
                fprintf(oFile,"/* entry_tlut_no_%d */",i/16);
                fprintf(oFile,"\n") ;
                fprintf(oFile,"\t");
            }
            /* 256個に足りない分ﾀﾞﾐｰで出力 */
            fprintf(oFile,"RGBA16CIP( 0, 0, 0, 0)");
            fprintf(oFile,",") ;
            
            if( ((i+1)&3) == 0 ){
                fprintf(oFile,"\n") ;
                fprintf(oFile,"\t");
            }
        }
    }
    fprintf(oFile,"\n");
    fprintf(oFile,"};\n");              /* ﾋﾟｸｾﾙのｲﾝﾃﾞｯｸｽ情報出力終了 */
    
    

    /*--------------------------------------*
   |  
   *--------------------------------------*/
    printf("--------[ CI-8Bit Texture Information ]\n");    
    printf("  FILE        = [%s]\n",outFileName);          /* 出力ﾌｧｲﾙ名   */
    printf("  Width       = %ld\n", pBmih->biWidth);     /* 幅         */
    printf("  Height      = %ld\n", pBmih->biHeight);        /* 高さ          */
    printf("  Colors      = 8-Bit : Index 256 colors\n");           /* ｶﾗｰ           */
    printf("  UsePalette  = %2d/256\n",TblCnt);                /* 使用ﾊﾟﾚｯﾄ数    */
    printf("  DmyPalette  = %2d/256\n",PAL_256 - TblCnt);  /* ﾀﾞﾐｰﾊﾟﾚｯﾄ数  */
    if((PAL_256 - TblCnt)){
        printf("  DmyPalOut   = RGBA16CIP( 0, 0, 0, 0)\n");     /* ﾀﾞﾐｰ出力      */
    }
    
    printf("--------[ Alpha Information ]\n");              /* ﾀﾞﾐｰ出力      */
    printf("  AlphaCount  = %d\n",nuki.count);              /* 透明ﾊﾟﾚｯﾄ数    */
    for(j=0;j<nuki.count;j++){                                /* 透明ﾊﾟﾚｯﾄ番号 */
        printf("  AlphaPalNO  = %d\n",nuki.info[j].pal_no);
    }
    printf("-----------------------------------------------------------\n");

    
    
    
    /*------------------------------*/
    /* ﾊﾟﾚｯﾄ情報出力             */
    fprintf(oFile,"\n");
    fprintf(oFile,"\n");
    fprintf(oFile,"static Gfx %s_C_dummy_aligner1[] = { gsSPEndDisplayList() };\n",fileName_TLF);
    fprintf(oFile,"\n");
    fprintf(oFile,"static TLF %s\n",fileName_TLF);
    fprintf(oFile,"={\n");
    fprintf(oFile,"\tG_TT_RGBA16,\t\t/* TLUT type\t\t*/\n");
    fprintf(oFile,"\t%s,\t/* TLUT address\t\t*/\n",fileName_TLF_TLUT);
    fprintf(oFile,"\t256,\t\t\t\t\t/* TLUT size\t\t*/\n");
    fprintf(oFile,"};\n");

    /*------------------------------*/
    /* ｽﾌﾟﾗｲﾄ情報出力              */
    fprintf(oFile,"\n");
    fprintf(oFile,"\n");
    fprintf(oFile,"static Gfx %s_C_dummy_aligner1[] = { gsSPEndDisplayList() };\n",fileName);
    fprintf(oFile,"\n");
// fprintf(oFile,"static PICTURE %s\n",fileName);
    fprintf(oFile,"PICTURE %s\n",fileName);
    fprintf(oFile,"={\n");

    fprintf(oFile,"\t&%s,\n",fileName_TMF);
    fprintf(oFile,"\t&%s,\n",fileName_TLF);
    fprintf(oFile,"\t0,\n");
    fprintf(oFile,"};\n");
    
    fprintf(oFile,"/*------------------------------------------------------------*\n");
    fprintf(oFile," | end of %s\n",outFileName);
    fprintf(oFile," *------------------------------------------------------------*/\n");
    
    fprintf(oFile,"#endif\n");
    
    free(pPixelHead);
    free(pColTblHead);
    free(pTmpPixel_1);
    free(pTmpPixel_2);
    
    
}




/*-----------------------------------------------------------------------------
   関数名   :getFilename

   work    :ﾌｧｲﾙ名から拡張子を取り除く
   in      :*fullName = ﾌｧｲﾙ名のﾎﾟｲﾝﾀ
            *newName  = 出力ﾌｧｲﾙ名のﾎﾟｲﾝﾀ
   out     :拡張子が在る : 1
            拡張子が無し : 0
   note    :
-----------------------------------------------------------------------------*/
int getFilename(char *fullName, char *newName)
{
   #define GF_MOZI_MAX     256
    int i,j;
    i = j = 0;
    
    while(*fullName != '\0'){
        if(*fullName == '\\'){
            j=0 ;              //文字列 ｶｳﾝﾄ ｸﾘｱ
        }
        
        if(j>GF_MOZI_MAX){
            DispErr(4);
            exit(0);
        }
        if(*fullName == '.'){
            newName[i] = '\0';
            return 1;
        }
        newName[i++] = *fullName++;
        j++;        //文字列カウント
    }
    return 0;
}


/*-----------------------------------------------------------------------------
   関数名   :getFilenameAll

   work    :ﾌｧｲﾙ名＋拡張子を取得する
   in      :*fullName = ﾌｧｲﾙ名のﾎﾟｲﾝﾀ
            *newName  = 出力ﾌｧｲﾙ名のﾎﾟｲﾝﾀ
   out     :拡張子が在る : 1
            拡張子が無し : 0
   note    :
-----------------------------------------------------------------------------*/
int getFilenameAll(char *fullName, char *newName)
{
   #define GFA_MOZI_MAX        256

    int i,j;
    i = j = 0;
    
    while(*fullName != '\0'){
        if(*fullName == '\\'){
            j=0 ;              //文字列 ｶｳﾝﾄ ｸﾘｱ
        }
        
        if(j>GFA_MOZI_MAX){
            DispErr(4);
            exit(0);
        }
        if(*fullName == '\0'){
            newName[i] = '\0';
            return 1;
        }
        newName[i++] = *fullName++;
        j++;        //文字列カウント
    }
    return 0;
}


/*-----------------------------------------------------------------------------
   関数名   :checkFileHeader

   work    :BMPﾌｧｲﾙﾍｯﾀﾞ確認
   in      :
   out     :TRUE       / BMPﾌｧｲﾙです
            FALSE      / BMPﾌｧｲﾙではありません
   note    :先頭の”BM”を確認します
   #inc    :nothing
   expl    :nothing
-----------------------------------------------------------------------------*/
int checkFileHeader( BITMAPFILEHEADER *pBmfh ,FILE* iFile )
{
    fread(pBmfh, 14, 1, iFile);       /* ｻｲｽﾞが合わないので直接指定 */
    // fread(pBmfh, sizeof(BITMAPFILEHEADER), 1, iFile);
    
    if(pBmfh->bfType != 19778)    return FALSE;
    else                      return TRUE;
}


/*-----------------------------------------------------------------------------
   関数名   :checkBmpInfo

   work    :ﾌｧｲﾙ情報確認
   in      :BITMAPFILEHEADER *pBmfh, 
            BITMAPINFOHEADER *pBmih,
            FILE *iFile
            FILE *oFile
   out     :ulong tblcnt
   note    :4-bit、8-bit、24-bit以外のBMPファイルを落とすのだが 1-bit BMP
            ファイルの作成方法がわからん
   #inc    :nothing
   expl    :nothing
-----------------------------------------------------------------------------*/
ulong checkBmpInfo( BITMAPFILEHEADER *pBmfh, BITMAPINFOHEADER *pBmih,
                    FILE *iFile, FILE *oFile)
{
    ulong tblcnt;

/* ------------------ */
    fread(pBmih, 40, 1, iFile);
// fread(pBmih, sizeof(BITMAPINFOHEADER), 1, iFile);
    printf("--------< File Information (*.bmp,*.ci,alpha) >------------\n");
    printf("--------[ BMP Image Information ]\n");
    printf("  FILE        = [%s]\n",inFileName);
    printf("  Width       = %ld\n", pBmih->biWidth);
    printf("  Height      = %ld\n", pBmih->biHeight);
    printf("  Colors      = ");
    switch(pBmih->biBitCount){
        case 1:
            printf("1-bit monochrome\n");
            break;
        case 4:
            printf("4-bit 16 colors\n");
            break;
        case 8:
            printf("8-bit 256 colors\n");
            break;
        case 24:
            printf("24-bit colors\n");
            break;
        default:
            printf("Unknown color format\n");
            break;
    }

    printf("  Compression = ");
    switch(pBmih->biCompression){
        case BI_RGB:
            printf("No Compression\n");
            break;
        case BI_RLE8:
            printf("RLE8\n");
            break;
        case BI_RLE4:
            printf("RLE4\n");
            break;
        default:
            printf("Unknown compression format\n");
            fclose(oFile);
            fclose(iFile);
            DispErr(2);
            exit(1);
    }
/*
   printf("=================================\n");
*/

    /* 無圧縮のみ対応します */
    if(pBmih->biCompression != BI_RGB){
        fclose(oFile);
        fclose(iFile);
        DispErr(3);
        exit(1);
    }

    /* 色数のﾁｪｯｸ＆ﾃｰﾌﾞﾙ数のﾁｪｯｸ */
    switch(pBmih->biBitCount){
    case  4: /* 16色 */
    case  8: /* 256色 */
        if(   !pBmih->biClrUsed )  tblcnt = (ulong)pow(2, pBmih->biBitCount);
        else                  tblcnt = pBmih->biClrUsed;
        break;
    case  24:    /* 1677万色 */
        tblcnt = pBmih->biClrUsed;
        break;
    case  1:     /* ｾｰﾌﾞ方法が解らない？ */
    case  16:
    case  32:
    default:
        fclose(iFile);
        fclose(oFile);
        DispErr(2);
        exit(1);
    }
    
    return tblcnt;
}


/*-----------------------------------------------------------------------------
   関数名   :DispErr

   work    :エラーメッセージの表示
   in      : ErrNum    メッセージ番号
   out     :nothing
   note    :
-----------------------------------------------------------------------------*/
void DispErr(int errnum)
{
    switch (errnum) {
    case 1 :
        puts("ERR: InputFile is not a BMP file.\n");
        break;
    case 2 :
        puts("ERR: Sorry, this bitcount is not supported.\n");
        break;
    case 3 :
        puts("ERR: Sorry, RLE bitmap is not supported.\n");
        break;
    case 4 :
        puts("ERR: ﾌｧｲﾙ名称を確認してください.\n");
        break;
    default :
        puts("ERR: Sorry,Sorry,Sorry,Sorry. ");
        break;
    }
}


/*-----------------------------------------------------------------------------
   関数名   :chendian16

   work    :Change Endian (16bit)
   in      :unsigned short *num
   out     :unsigned short
   note    :nothing
-----------------------------------------------------------------------------*/
unsigned short chendian16(unsigned short *num)
{
    unsigned char high, low;
    unsigned short out;
    
    high = (*num >> 8) & 0x00FF;
    low = *num & 0x00FF;
    
    out = ((unsigned int)low << 8) | (unsigned int)high;
    
    *num = out;
    return out;
}


/*-----------------------------------------------------------------------------
   関数名   :chendian32

   work    :Change Endian (32bit)
   in      :unsigned long *num
   out     :unsigned long
   note    :nothing
-----------------------------------------------------------------------------*/
unsigned long chendian32(unsigned long *num)
{
    unsigned short high, low;
    unsigned long out;

    high = (*num >> 16) & 0x0000FFFF;
    low = *num & 0x0000FFFF;

    high = chendian16(&high);
    low = chendian16(&low);

    out = ((unsigned long)low << 16) | (unsigned long)high;

    *num = out;
    return out;
}


//----------------------------------------------
// void Usage() = ヘルプファイル
// in  :nothing
// out :nothing
//----------------------------------------------
void DispUsage(void){
    puts("");
    puts("bmp2ci ver 0.01 = bmpfile to cifile converter");
    puts("");
    puts("usage: bmp2ci <bmpFilename> <ciFilename>");
    puts("     : supported BMP files");
    puts("     : No Compression. 4-bit/8-bit/24-bit colors.");
    puts("     : attention.");
    puts("     : palette or pixel = Convert RGBA5551-Format.");
}
/*---------------------------------------------------------------------------*
 | end of bmp2ci.c
 *---------------------------------------------------------------------------*/ 