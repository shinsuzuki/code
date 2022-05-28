/*---------------------------------------------------------------------------*
 | bmp.h
 *---------------------------------------------------------------------------*/ 
#ifndef _BMP_H_
#define _BMP_H_
/*------------------------------------------------------------*
 |  defines
 *------------------------------------------------------------*/
#define BI_RGB   0L             /* 無圧縮 */
#define BI_RLE8  1L             /* < 256 Color > run-length (8bit/pixel) */
#define BI_RLE4  2L             /* <  16 Color > run-length (4bit/pixel) */


/*------------------------------------------------------------*
 |  typdefs
 *------------------------------------------------------------*/
/* BMPファイルヘッダ構造体 */ 
typedef struct {
    unsigned short bfType;      /* ﾌｧｲﾙﾀｲﾌﾟ (should be 'BM'(= 19778))   */
    unsigned long  bfSize;      /* ﾌｧｲﾙｻｲｽﾞ（ﾊﾞｲﾄ単位）                 */
    unsigned short bfReserved1; /* 常に 0x00                            */
    unsigned short bfReserved2; /* 常に 0x01                            */
    unsigned long  bfOffBits;   /* ﾌｧｲﾙﾍｯﾀﾞからﾋﾟｸｾﾙﾃﾞｰﾀまでのﾊﾞｲﾄ数    */
} BITMAPFILEHEADER;


//ヘッダファイル
typedef struct {
    unsigned long  biSize;          /* この構造体のサイズ（ﾊﾞｲﾄ単位）   */
    long           biWidth;         /* 横のｻｲｽﾞ（０、負数はﾀﾞﾒ）        */
    long           biHeight;        /* 縦のｻｲｽﾞ（０はﾀﾞﾒ）              */
    unsigned short biPlanes;        /* プレーン数（should be１）        */
    unsigned short biBitCount;      /* １ﾋﾟｸｾﾙのﾋﾞｯﾄ数                  */
    unsigned long  biCompression;
                                    /* ｲﾒｰｼﾞのﾃﾞｰﾀ形式          */
                                    /* BI_RGB  :無圧縮          */
                                    /* BI_RLE4 :16色ﾗﾝﾚﾝｸﾞｽ     */
                                    /* BI_RLE8 :256色ﾗﾝﾚﾝｸﾞｽ    */

    unsigned long  biSizeImage;     /* ｲﾒｰｼﾞﾃﾞｰﾀのﾊﾞｲﾄ数（間違った物がたまにあるので無視する事）    */
    long           biXPelsPerMeter; /* 水平１Mで何ﾋﾟｸｾﾙ入るか（通常は考えなくても良い） */
    long           biYPelsPerMeter; /* 垂直１Mで何ﾋﾟｸｾﾙ入るか（通常は考えなくても良い） */
    unsigned long  biClrUsed;       /* ｶﾗｰﾃｰﾌﾞﾙの数(ｲﾝﾃﾞｯｸｽ) */
    unsigned long  biClrImportant;  /* 意味不明 */
} BITMAPINFOHEADER;


// カラーテーブルみたいなものです(size = 32bit = 4byte)
typedef struct{
    unsigned char rgbBlue;
    unsigned char rgbGreen;
    unsigned char rgbRed;
    unsigned char rgbReserved; /* always 0 */
} RGBQUAD;

// ピクセルデータ
typedef struct{
    unsigned char rgbBlue;
    unsigned char rgbGreen;
    unsigned char rgbRed;
} RGBQUAD24;

#endif