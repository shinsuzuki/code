//-----------------------------------------------------------------------------
// SPMGR.h
//-----------------------------------------------------------------------------
#ifndef _SPMGR_H_
#define _SPMGR_H_
//-----------------------------------------------------------------------------
//  include
//-----------------------------------------------------------------------------
#include <sys/types.h>
//#include <asm.h>
//#include <r3000.h>
#include <libapi.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
//-----------------------------------------------------------------------------
//  define
//-----------------------------------------------------------------------------
//#define NULL                      -1
#define TRUE                        1
#define FALSE                       0

#define MAX_ENTRY_SPRITE_NUM        400     //最大スプライト登録数
#define MAX_DRAW_SPRITE_NUM         256     //最大スプライト描画数

#define SPRITE_USE                  1       // 使用中 
#define SPRITE_NOUSE                0       // 使用していません

#define ENTRY_SPRITE_DATA_END       -1      //スプライトテクスチャ登録終了

#define DRAW_SPRITE_OT_NO           3       //OT０へ書き込み
//-----------------------------------------------------------------------------
//  typdef
//-----------------------------------------------------------------------------
//スプライト登録構造体
typedef struct _ENTRY_SPRITE_DATA{
    int     No;             //テクスチャ番号
    int     OffSetX;        //TIMの中のスプライト左上開始X位置
    int     OffSetY;        //TIMの中のスプライト左上開始Y位置
    int     Height;         //TIMの中のテクスチャの高さ
    int     Width;          //TIMの中のテクスチャの幅
    int     PaletteNo;      //TIMの中のテクスチャパレット番号
}ENTRY_SPRITE_DATA;

//スプライト構造体
typedef struct _SPRITE_DATA{
    int     No;                     //インデックス番号
    int     PosX;                   //X位置
    int     PosY;                   //Y位置
    int     PosZ;                   //優先順位
    int     ScaleX;                 //スケールX
    int     ScaleY;                 //スケールY
    int     Rotate;                 //回転角
    int     Reverse;                //反転コード
}SPRITE_DATA;

//-----------------------------------------------------------------------------
//  class
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  extern
//-----------------------------------------------------------------------------
extern GsIMAGE  TimImg;
extern GsIMAGE  *TimImgData;
extern int      Spx;
extern int      Spy;
extern int      Sptox;
extern int      Sptoy;
extern int      Spsw;
extern int      Spsh;
extern int      Sppost;
extern int      Sppn;
extern int      Sppri;
extern int      Spscalex;
extern int      Spscaley;
extern int      Sprotate;
extern int      Sprevers;
extern int      Sptrans;

extern void     InitSprite(void);                   //初期化
extern void     EntrySprite(ENTRY_SPRITE_DATA*);    //登録
extern int      DrawSprite(SPRITE_DATA*);           //描画
extern void     TransSprite(void);                  //転送
extern void     ReleaseSprite(void);                //開放
extern int      GetDrawSpriteNum(void);             //描画枚数取得
extern int      GetEntyrSpriteNum(void);            //登録枚数取得

//-----------------------------------------------------------------------------
//  variable
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  prototype
//-----------------------------------------------------------------------------
static SPRITE_DATA* AllocSprite(void);                  //取得
static void         SortSprite(SPRITE_DATA *[],int);    //ソート

void                InitSprite(void);                   //初期化
void                EntrySprite(ENTRY_SPRITE_DATA*);    //登録
int                 DrawSprite(SPRITE_DATA*);           //描画
void                TransSprite(void);                  //転送
void                ReleaseSprite(void);                //開放
int                 GetDrawSpriteNum(void);             //描画枚数取得
int                 GetEntrySpriteNum(void);            //登録枚数取得

//-----------------------------------------------------------------------------
// end of SPMGR.h
//-----------------------------------------------------------------------------
#endif