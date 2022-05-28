//-----------------------------------------------------------------------------
// SPMGR.c
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  include
//-----------------------------------------------------------------------------
#include <sys/file.h>
#include <sys/types.h>
//#include <asm.h>
//#include <r3000.h>
#include <libapi.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libcd.h>
#include <libds.h>
#include <stdio.h>
//
#include "SPCONT.h"
#include "SPMGR.h"
//-----------------------------------------------------------------------------
//  define
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  typdef
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  extern
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  variable
//-----------------------------------------------------------------------------
//------------------登録
static int EntrySpriteNum;                                 //登録枚数
ENTRY_SPRITE_DATA EntrySpriteBuffer[MAX_ENTRY_SPRITE_NUM]; //スプライト登録バッファ

//------------------描画
static int DrawSpriteNum;                               //描画枚数
static SPRITE_DATA *pSpriteBuffer[MAX_DRAW_SPRITE_NUM]; //スプライトバッファポインタ
static SPRITE_DATA SpriteBuffer[MAX_DRAW_SPRITE_NUM];   //スプライトバッファ

//-----------------------------------------------------------------------------
//  prototype
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// codes
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  関数名 :InitSprite
//  機能   :スプライト管理初期化
//  注意   :なし
//-----------------------------------------------------------------------------
void InitSprite(void)
{
    int i;
    SPRITE_DATA *pSpData;
    ENTRY_SPRITE_DATA *pEntrySpData;

    //----------------描画
    //描画バッファデータ初期化
    for (i = 0, pSpData = SpriteBuffer; i < MAX_DRAW_SPRITE_NUM; i++, pSpData++)
    {
        //描画スプライトバッファの初期化
        pSpData->No = -1;            //インデックス番号
        pSpData->PosX = 0;           //X位置
        pSpData->PosY = 0;           //Y位置
        pSpData->PosZ = 0;           //優先順位
        pSpData->ScaleX = SCALE10;   //スケールX
        pSpData->ScaleY = SCALE10;   //スケールY
        pSpData->Rotate = ROTATE000; //回転角
        pSpData->Reverse = NOREVERS; //反転コード

        //描画スプライトポインタバッファ初期化
        pSpriteBuffer[i] = NULL;
    }

    //描画枚数クリア
    DrawSpriteNum = 0;

    //----------------登録バッファ
    //登録バッファ初期化
    for (i = 0, pEntrySpData = EntrySpriteBuffer; i < MAX_ENTRY_SPRITE_NUM; i++, pEntrySpData++)
    {
        pEntrySpData->No = 0;        //テクスチャ番号
        pEntrySpData->OffSetX = 0;   //TIMの中のスプライト左上開始X位置
        pEntrySpData->OffSetY = 0;   //TIMの中のスプライト左上開始Y位置
        pEntrySpData->Height = 0;    //TIMの中のテクスチャの高さ
        pEntrySpData->Width = 0;     //TIMの中のテクスチャの幅
        pEntrySpData->PaletteNo = 0; //TIMの中のテクスチャパレット番号
    }

    //登録枚数クリア
    EntrySpriteNum = 0;
}

//-----------------------------------------------------------------------------
//  関数名 :AllocSprite
//  機能   :描画スプライトデータの取得チェック
//  注意   :なし
//-----------------------------------------------------------------------------
static SPRITE_DATA *AllocSprite(void)
{
    SPRITE_DATA *pSpData;

    if (DrawSpriteNum > MAX_DRAW_SPRITE_NUM - 1)
    { //空いていない
        return NULL;
    }

    //空いている描画バッファのアドレス
    pSpData = &(SpriteBuffer[DrawSpriteNum]);

    //データOK
    return pSpData;
}

//-----------------------------------------------------------------------------
//  関数名 :SortSprite
//  機能   :描画スプライトデータへのポインタをソート
//  注意   :PosZに対して昇順にのみ対応
//-----------------------------------------------------------------------------
static void SortSprite(SPRITE_DATA *i_pSpDataArr[], int i_num)
{
    int i, j, k, gap;
    SPRITE_DATA *ppSpData;

    // numより小さい範囲で最大のを gap 決める
    for (gap = 1; gap < i_num / 3; gap = 3 * gap + 1)
        ;

    while (gap > 0)
    {
        for (i = gap; i < i_num; i++)
        {
            for (j = i - gap; j >= 0; j = j - gap)
            {
                if (i_pSpDataArr[j]->PosZ > i_pSpDataArr[j + gap]->PosZ)
                {
                    ppSpData = i_pSpDataArr[j];
                    i_pSpDataArr[j] = i_pSpDataArr[j + gap];
                    i_pSpDataArr[j + gap] = ppSpData;
                }
                else
                {
                    break;
                }
            }
        }
        gap /= 3;
    }
}

//-----------------------------------------------------------------------------
//  関数名 :DrawSprite
//  機能   :スプライト描画（バッファへ登録）
//  注意   :PosZの値が小さいほど手前表示されます
//-----------------------------------------------------------------------------
int DrawSprite(SPRITE_DATA *i_pSpData)
{
    SPRITE_DATA *pSpData;

    //登録のチェック
    if ((pSpData = AllocSprite()) == NULL)
    {
        return FALSE; // 表示できない
    }

    //セット
    pSpriteBuffer[DrawSpriteNum] = pSpData;

    //登録されていない場合はエラー
    if (EntrySpriteNum == 0)
        return FALSE;

    //登録したスプライト数より大きいインデックス値が指定された場合はエラー
    if (i_pSpData->No > EntrySpriteNum - 1)
        return FALSE;

    //取得した情報をスプライトへセットする
    pSpData->No = i_pSpData->No;           //インデックス番号
    pSpData->PosX = i_pSpData->PosX;       //X位置
    pSpData->PosY = i_pSpData->PosY;       //Y位置
    pSpData->PosZ = i_pSpData->PosZ;       //優先順位　（数値大きいほど優先順位は低くなる）
    pSpData->ScaleX = i_pSpData->ScaleX;   //スケールX
    pSpData->ScaleY = i_pSpData->ScaleY;   //スケールY
    pSpData->Rotate = i_pSpData->Rotate;   //回転角
    pSpData->Reverse = i_pSpData->Reverse; //反転コード

    //描画枚数カウント
    DrawSpriteNum++;

    return TRUE;
}

//-----------------------------------------------------------------------------
//  関数名 :TransSprite
//  機能   :スプライトを転送
//  注意   :なし
//-----------------------------------------------------------------------------
void TransSprite(void)
{
    int i;
    SPRITE_DATA **ppSpData;
    SPRITE_DATA *pSpData;

    //ソート
    SortSprite(pSpriteBuffer, DrawSpriteNum);

    //転送
    for (i = 0, ppSpData = pSpriteBuffer; i < DrawSpriteNum; i++, ppSpData++)
    {
        //---------
        Spx = (*ppSpData)->PosX;                             //表示位置X
        Spy = (*ppSpData)->PosY;                             //表示位置Y
        Sptox = EntrySpriteBuffer[(*ppSpData)->No].OffSetX;  //TIMの中のスプライト左上開始X位置
        Sptoy = EntrySpriteBuffer[(*ppSpData)->No].OffSetY;  //TIMの中のスプライト左上開始Y位置
        Spsw = EntrySpriteBuffer[(*ppSpData)->No].Width;     //TIMの中のテクスチャの幅
        Spsh = EntrySpriteBuffer[(*ppSpData)->No].Height;    //TIMの中のテクスチャの高さ
        Sppost = EntrySpriteBuffer[(*ppSpData)->No].No;      //テクスチャ番号
        Sppn = EntrySpriteBuffer[(*ppSpData)->No].PaletteNo; //パレット番号
                                                             //      Sppri       = (*ppSpData)->PosZ;                            //優先順位
        Sppri = DRAW_SPRITE_OT_NO;                           //優先順位
        Spscalex = (*ppSpData)->ScaleX;                      //スケールX
        Spscaley = (*ppSpData)->ScaleY;                      //スケールY
        Sprotate = (*ppSpData)->Rotate;                      //回転各
        Sprevers = (*ppSpData)->Reverse;                     //反転
        Sptrans = 0;                                         //透明度フラグ

        //
        TimImg.pmode = TimImgData[Sppost].pmode;
        TimImg.px = TimImgData[Sppost].px;
        TimImg.py = TimImgData[Sppost].py;
        TimImg.pw = TimImgData[Sppost].pw;
        TimImg.ph = TimImgData[Sppost].ph;
        TimImg.pixel = TimImgData[Sppost].pixel;
        TimImg.cx = TimImgData[Sppost].cx;
        TimImg.cy = TimImgData[Sppost].cy;
        TimImg.cw = TimImgData[Sppost].cw;
        TimImg.ch = TimImgData[Sppost].ch;
        TimImg.clut = TimImgData[Sppost].clut;

        RegisterSP(&TimImg);

        // バッファとポインタの全てクリアする
        //バッファクリア
        pSpData->No = -1;            //インデックス番号
        pSpData->PosX = 0;           //X位置
        pSpData->PosY = 0;           //Y位置
        pSpData->PosZ = 0;           //優先順位
        pSpData->ScaleX = SCALE10;   //スケールX
        pSpData->ScaleY = SCALE10;   //スケールY
        pSpData->Rotate = ROTATE000; //回転角
        pSpData->Reverse = NOREVERS; //反転コード

        //ポインタクリア
        pSpriteBuffer[i] = NULL;
    }

    //全て転送したので描画枚数をクリア
    DrawSpriteNum = 0;
}

//-----------------------------------------------------------------------------
//  関数名 :EntrySprite
//  機能   :スプライトの登録
//  注意   :なし
//-----------------------------------------------------------------------------
void EntrySprite(ENTRY_SPRITE_DATA *i_pEntrySpData)
{
    int i;
    ENTRY_SPRITE_DATA *pEntrySpData;

    //最大でも MAX_ENTRY_SPRITE_NUM しか登録しない
    for (i = 0, pEntrySpData = i_pEntrySpData; i < MAX_ENTRY_SPRITE_NUM; i++, pEntrySpData++)
    {
        if (pEntrySpData->No == ENTRY_SPRITE_DATA_END)
            break;

        EntrySpriteBuffer[i].No = pEntrySpData->No;               //テクスチャー番号
        EntrySpriteBuffer[i].OffSetX = pEntrySpData->OffSetX;     //TIMの中のスプライト左上開始X位置
        EntrySpriteBuffer[i].OffSetY = pEntrySpData->OffSetY;     //TIMの中のスプライト左上開始Y位置
        EntrySpriteBuffer[i].Height = pEntrySpData->Height;       //テクスチャの高さ
        EntrySpriteBuffer[i].Width = pEntrySpData->Width;         //テクスチャの幅
        EntrySpriteBuffer[i].PaletteNo = pEntrySpData->PaletteNo; //パレット番号

        //登録枚数カウント
        EntrySpriteNum++;
    }
}

//-----------------------------------------------------------------------------
//  関数名 :ReleaseSprite
//  機能   :スプライトの登録解除
//  注意   :InitSprite関数と同じ：意味合いを変えたいのでこの関数を使用
//-----------------------------------------------------------------------------
void ReleaseSprite(void)
{
    int i;
    ENTRY_SPRITE_DATA *pEntrySpData;

    //----------------登録バッファ
    //登録バッファ初期化
    for (i = 0, pEntrySpData = EntrySpriteBuffer; i < MAX_ENTRY_SPRITE_NUM; i++, pEntrySpData++)
    {
        pEntrySpData->No = 0;        //テクスチャ番号
        pEntrySpData->OffSetX = 0;   //TIMの中のスプライト左上開始X位置
        pEntrySpData->OffSetY = 0;   //TIMの中のスプライト左上開始Y位置
        pEntrySpData->Height = 0;    //TIMの中のテクスチャの高さ
        pEntrySpData->Width = 0;     //TIMの中のテクスチャの幅
        pEntrySpData->PaletteNo = 0; //TIMの中のテクスチャパレット番号
    }

    //登録枚数クリア
    EntrySpriteNum = 0;
}

//-----------------------------------------------------------------------------
//  関数名 :GetDrawSpriteNum
//  機能   :描画枚数取得
//  注意   :なし
//-----------------------------------------------------------------------------
int GetDrawSpriteNum(void)
{
    return DrawSpriteNum;
}

//-----------------------------------------------------------------------------
//  関数名 :GetEntrySpriteNum
//  機能   :登録枚数取得
//  注意   :なし
//-----------------------------------------------------------------------------
int GetEntrySpriteNum(void)
{
    return EntrySpriteNum;
}

//-----------------------------------------------------------------------------
// end of SPMGR.c
//-----------------------------------------------------------------------------