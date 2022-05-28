//-----------------------------------------------------------------------------
// BAND.C
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  include
//-----------------------------------------------------------------------------
#include "COMMON.H"
#include "KAZU.H"
#include "SPMGR.H"
#include "TASKMGR.H"
#include "SPCONT.H"
#include "SOUND.H"
#include "BAND.H"
//-----------------------------------------------------------------------------
//  define
//-----------------------------------------------------------------------------
//----SW
//  #define __DEBUG_BAND__

//--------テクスチャー枚数と位置
//----GAME
#define BAND_GAME_TIM_POS               0+4
#define BAND_GAME_TIM_NUM               5

//----EVENT
#define BAND_EVENT_TIM_POS              0+4
#define BAND_EVENT_TIM_NUM              7

//----GAME
#define TIM_POS_BAND_GAME_Z1_01_A       0+4
#define TIM_POS_BAND_GAME_Z1_01_B       1+4
#define TIM_POS_BAND_GAME_Z1_02_A       2+4
#define TIM_POS_BAND_GAME_Z1_02_B       3+4
#define TIM_POS_BAND_GAME_Z1_03         4+4

//----EVENT
#define TIM_POS_BAND_EVENT_FONT         0       //選択処理テクスチャ
#define TIM_POS_BAND_EVENT_YORNO        1       //選択処理テクスチャ
#define TIM_POS_BAND_EVENT_Z2_01_A      0+4
#define TIM_POS_BAND_EVENT_Z2_01_B      1+4
#define TIM_POS_BAND_EVENT_Z2_01_C      2+4
#define TIM_POS_BAND_EVENT_Z2_02_A      3+4
#define TIM_POS_BAND_EVENT_Z2_02_B      4+4
#define TIM_POS_BAND_EVENT_Z2_03        5+4
#define TIM_POS_BAND_EVENT_Z2_04        6+4


//-----------------------------------------------------------------------------
//■キャラ番号
//-----------------------------------------------------------------------------
//----Game
//-------------------------------------------------------------------------------[Z1_01_A.TIM]
#define BAND_CHAR_GAME_BG_00                        0       //ゲーム背景左
//-------------------------------------------------------------------------------[Z1_01_B.TIM]
#define BAND_CHAR_GAME_BG_01                        1       //ゲーム背景右
#define BAND_CHAR_GAME_DANTYOU_BIG_00               2       //団長出現時のパターン１
#define BAND_CHAR_GAME_DANTYOU_BIG_01               3       //団長出現時のパターン２
#define BAND_CHAR_GAME_LEVEL_SELECT_PLATE           4       //レベルセレクトプレート
#define BAND_CHAR_GAME_LEVEL_SELECT_PLATE_WAKU      5       //レベルセレクトプレート枠
//-------------------------------------------------------------------------------[Z1_02_A.TIM]
#define BAND_CHAR_GAME_LEVEL_SELECT_BG_00           6       //レベルセレクト背景左
//-------------------------------------------------------------------------------[Z1_02_B.TIM]
#define BAND_CHAR_GAME_LEVEL_SELECT_BG_01           7       //レベルセレクト背景右
//-------------------------------------------------------------------------------[Z1_03.TIM]
#define BAND_CHAR_GAME_DANTYOU_00                   8       //団長↓    １パターン
#define BAND_CHAR_GAME_DANTYOU_01                   9       //団長↓    ２パターン
#define BAND_CHAR_GAME_DANTYOU_02                   10      //団長→    １パターン
#define BAND_CHAR_GAME_DANTYOU_03                   11      //団長→    ２パターン
#define BAND_CHAR_GAME_DANTYOU_04                   12      //団長↑    １パターン
#define BAND_CHAR_GAME_DANTYOU_05                   13      //団長↑    ２パターン
#define BAND_CHAR_GAME_DANTYOU_06                   14      //団長←    １パターン
#define BAND_CHAR_GAME_DANTYOU_07                   15      //団長←    ２パターン
#define BAND_CHAR_GAME_DANIN_A_00                   16      //団員A     １パターン
#define BAND_CHAR_GAME_DANIN_A_01                   17      //団員A     ２パターン
#define BAND_CHAR_GAME_DANIN_B_00                   18      //団員B     １パターン
#define BAND_CHAR_GAME_DANIN_B_01                   19      //団員B     ２パターン
#define BAND_CHAR_GAME_DANIN_C_00                   20      //団員C     １パターン
#define BAND_CHAR_GAME_DANIN_C_01                   21      //団員C     ２パターン
#define BAND_CHAR_GAME_DANIN_D_00                   22      //団員D     １パターン
#define BAND_CHAR_GAME_DANIN_D_01                   23      //団員D     ２パターン
#define BAND_CHAR_GAME_DANIN_E_00                   24      //団員E     １パターン
#define BAND_CHAR_GAME_DANIN_E_01                   25      //団員E     ２パターン
#define BAND_CHAR_GAME_DANIN_F_00                   26      //団員F     １パターン
#define BAND_CHAR_GAME_DANIN_F_01                   27      //団員F     ２パターン
#define BAND_CHAR_GAME_DANIN_G_00                   28      //団員G     １パターン
#define BAND_CHAR_GAME_DANIN_G_01                   29      //団員G     ２パターン
#define BAND_CHAR_GAME_NUM_00                       30      //番号０
#define BAND_CHAR_GAME_NUM_01                       31      //番号１
#define BAND_CHAR_GAME_NUM_02                       32      //番号２
#define BAND_CHAR_GAME_NUM_03                       33      //番号３
#define BAND_CHAR_GAME_NUM_04                       34      //番号４
#define BAND_CHAR_GAME_NUM_05                       35      //番号５
#define BAND_CHAR_GAME_NUM_06                       36      //番号６
#define BAND_CHAR_GAME_NUM_07                       37      //番号７
#define BAND_CHAR_GAME_NUM_08                       38      //番号８
#define BAND_CHAR_GAME_NUM_09                       39      //番号９
#define BAND_CHAR_GAME_ARROW_LEFT                   40      //矢印←
#define BAND_CHAR_GAME_ARROW_UP                     41      //矢印↑
#define BAND_CHAR_GAME_ARROW_RIGHT                  42      //矢印→
#define BAND_CHAR_GAME_ARROW_DOWN                   43      //矢印↓
#define BAND_CHAR_GAME_SMOKE_00                     44      //団員出現煙    １パターン
#define BAND_CHAR_GAME_SMOKE_01                     45      //団員出現煙    ２パターン
#define BAND_CHAR_GAME_DOOR_00                      46      //ドア１
#define BAND_CHAR_GAME_DOOR_01                      47      //ドア２
#define BAND_CHAR_GAME_DOOR_02                      48      //ドア３
#define BAND_CHAR_GAME_DOOR_03                      49      //ドア４
//-------------------------------------------------------------------------------[Z1_02_B.TIM]追加
#define BAND_CHAR_GAME_LEVEL_SELECT_BG_MASK         50      //レベルセレクトマスク


//----Event
#define BAND_CHAR_EVENT_CLEAR_BG_00                 0       //クリア用入れ替え背景1
#define BAND_CHAR_EVENT_CLEAR_BG_01                 1       //クリア用入れ替え背景2
#define BAND_CHAR_EVENT_CLEAR_BG_02                 2       //クリア用入れ替え背景1
#define BAND_CHAR_EVENT_CLEAR_BG_03                 3       //クリア用入れ替え背景2
#define BAND_CHAR_EVENT_ALLCLEAR_BG_00              4       //全クリア用背景1
#define BAND_CHAR_EVENT_ALLCLEAR_BG_01              5       //全クリア用背景2
#define BAND_CHAR_EVENT_ALLCLEAR_BG_02              6       //全クリア用背景3
#define BAND_CHAR_EVENT_ALLCLEAR_BG_03              7       //全クリア用背景4
#define BAND_CHAR_EVENT_CLEAR_DANTYOU_00            8       //クリアデカイ団長１
#define BAND_CHAR_EVENT_CLEAR_DANTYOU_01            9       //クリアデカイ団長２
#define BAND_CHAR_EVENT_ALLCLEAR_DANTYOU_00         10      //全クリア演出用団長１
#define BAND_CHAR_EVENT_ALLCLEAR_DANTYOU_01         11      //全クリア演出用団長２
#define BAND_CHAR_EVENT_ALLCLEAR_BACK_DANIN_00      12      //全クリア演出用合唱団1（後列）シンバル
#define BAND_CHAR_EVENT_ALLCLEAR_BACK_DANIN_01      13      //全クリア演出用合唱団1（後列）シンバル
#define BAND_CHAR_EVENT_ALLCLEAR_BACK_DANIN_02      14      //全クリア演出用合唱団2（後列）ラッパ
#define BAND_CHAR_EVENT_ALLCLEAR_BACK_DANIN_03      15      //全クリア演出用合唱団2（後列）ラッパ
#define BAND_CHAR_EVENT_ALLCLEAR_BACK_DANIN_04      16      //全クリア演出用合唱団3（後列）タイコ
#define BAND_CHAR_EVENT_ALLCLEAR_BACK_DANIN_05      17      //全クリア演出用合唱団3（後列）タイコ
#define BAND_CHAR_EVENT_ALLCLEAR_BACK_DANIN_06      18      //全クリア演出用合唱団4（後列）タンバリン
#define BAND_CHAR_EVENT_ALLCLEAR_BACK_DANIN_07      19      //全クリア演出用合唱団4（後列）タンバリン
#define BAND_CHAR_EVENT_ICON_00                     20      //ゲーム終了か否かを選択するアイコン押すとパレット変化
#define BAND_CHAR_EVENT_ICON_01                     21      //ゲーム終了か否かを選択するアイコン押すとパレット変化
#define BAND_CHAR_EVENT_ICON_02                     22      //ゲーム終了か否かを選択するアイコン押すとパレット変化
#define BAND_CHAR_EVENT_ICON_03                     23      //パレット変化
#define BAND_CHAR_EVENT_ICON_04                     24      //パレット変化
#define BAND_CHAR_EVENT_ICON_05                     25      //パレット変化
#define BAND_CHAR_EVENT_ALLCLEAR_FRONT_DANIN_00     26      //全クリア演出用合唱団1（前列）風船
#define BAND_CHAR_EVENT_ALLCLEAR_FRONT_DANIN_01     27      //全クリア演出用合唱団1（前列）風船
#define BAND_CHAR_EVENT_ALLCLEAR_FRONT_DANIN_02     28      //全クリア演出用合唱団2（前列）旗１
#define BAND_CHAR_EVENT_ALLCLEAR_FRONT_DANIN_03     29      //全クリア演出用合唱団2（前列）旗１
#define BAND_CHAR_EVENT_ALLCLEAR_FRONT_DANIN_04     30      //全クリア演出用合唱団3（前列）旗２
#define BAND_CHAR_EVENT_ALLCLEAR_FRONT_DANIN_05     31      //全クリア演出用合唱団3（前列）旗２
#define BAND_CHAR_EVENT_ALLCLEAR_FRONT_DANIN_06     32      //全クリア演出用合唱団4（前列）1.2をパレット変えました。
#define BAND_CHAR_EVENT_ALLCLEAR_FRONT_DANIN_07     33      //全クリア演出用合唱団4（前列）1.2をパレット変えました。
#define BAND_CHAR_EVENT_SELECT_CONTINUE_PLATE       34      //プレート
#define BAND_CHAR_EVENT_SELECT_CONTINUE_YES_DARK    35      //非選択・はい
#define BAND_CHAR_EVENT_SELECT_CONTINUE_NO_DARK     36      //非選択・いいえ
#define BAND_CHAR_EVENT_SELECT_CONTINUE_YES_LIGHT   37      //選択・はい
#define BAND_CHAR_EVENT_SELECT_CONTINUE_NO_LIGHT    38      //選択・いいえ
#define BAND_CHAR_EVENT_SELECT_CONTINUE_BUPE_00     39      //プーぺ１
#define BAND_CHAR_EVENT_SELECT_CONTINUE_BUPE_01     40      //プーぺ２
#define BAND_CHAR_EVENT_SELECT_CONTINUE_RETRY_H     41      //もういちど
#define BAND_CHAR_EVENT_SELECT_CONTINUE_END_H       42      //おわり
#define BAND_CHAR_EVENT_SELECT_CONTINUE_CONTINUE_H  43      //つづけ
#define BAND_CHAR_EVENT_SELECT_CONTINUE_CURSOR      44      //指カーソル
#define BAND_CHAR_EVENT_SELECT_CONTINUE_ERABU       45      //えらぶ
#define BAND_CHAR_EVENT_SELECT_CONTINUE_KETEI       46      //けってい
#define BAND_CHAR_EVENT_SELECT_CONTINUE_MENU        47      //めにゅー


//-----------------------------------------------------------------------------
//  typdef
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  class
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  extern
//-----------------------------------------------------------------------------
//PAD
extern u_long   pad;
extern u_long   NewPad; 
extern u_long   OldPad; 
extern u_long   JstPad; 
extern u_long   WorkPad;

//GAME
extern u_long   Z1_01_A_image[];
extern u_long   Z1_01_A_clut[];
extern u_long   Z1_01_B_image[];
extern u_long   Z1_01_B_clut[];
extern u_long   Z1_02_A_image[];
extern u_long   Z1_02_A_clut[];
extern u_long   Z1_02_B_image[];
extern u_long   Z1_02_B_clut[];
extern u_long   Z1_03_image[];
extern u_long   Z1_03_clut[];

//EVENT
extern u_long   Z2_01_A_image[];
extern u_long   Z2_01_A_clut[];
extern u_long   Z2_01_B_image[];
extern u_long   Z2_01_B_clut[];
extern u_long   Z2_01_C_image[];
extern u_long   Z2_01_C_clut[];
extern u_long   Z2_02_A_image[];
extern u_long   Z2_02_A_clut[];
extern u_long   Z2_02_B_image[];
extern u_long   Z2_02_B_clut[];
extern u_long   Z2_03_image[];
extern u_long   Z2_03_clut[];
extern u_long   Z2_04_image[];
extern u_long   Z2_04_clut[];
extern u_long   font_image[];
extern u_long   YorN_image[];
extern u_long   name_image[];
extern u_long   MMENU_image[];
extern u_long   font_clut[];
extern u_long   YorN_clut[];
extern u_long   name_clut[];
extern u_long   MMENU_clut[];
extern u_long   help_00_image[];
extern u_long   help_00_clut[];

extern int      active; /* アクティブ(でない）描画領域 */
extern GsOT     Wot[2];
static GsBOXF   Box;
static GsBOXF   BoxDataBlack[] =    {0x00000000,  0,  0,320,240,0x00,0x00,0x00};
static GsBOXF   BoxDataWhite[] =    {0x00000000,  0,  0,320,240,0xFF,0xFF,0xFF};


//FUNC


//-----------------------------------------------------------------------------
//  variable
//-----------------------------------------------------------------------------
//----ゲームデータ
static BAND_GAME BGameMgr;

//----
static TIMD BandGameTextureFile[] = {
    //  デモタイトル名、    BINファイル名
    {   "RCUBE3",           "\\TIM\\BANDGD.B;1"},
};

static TIMD BandEventTextureFile[] = {
    //  デモタイトル名、    BINファイル名
    {   "RCUBE2",           "\\TIM\\BANDED.B;1"},
};

static GsIMAGE BandGameTextureImage[]=
{
    //color             tpos        size        image           pos         size    clut
    {   TIM_COLOR_16,   384,0,      64,256,     font_image,     16,480,     16,6,   font_clut       },
    {   TIM_COLOR_16,   448,0,      64,256,     YorN_image,     0,480,      16,16,  YorN_clut       },
    {   TIM_COLOR_16,   512,0,      64,256,     help_00_image,  0,496,      16,2,   help_00_clut    },
    {   TIM_COLOR_16,   320,0,      64,256,     MMENU_image,    16,489,     16,7,   MMENU_clut      },
    {   TIM_COLOR_16,   768,0,       64,256,    Z1_01_A_image,  80,480,      16,1,  Z1_01_A_clut    },
    {   TIM_COLOR_16,   704,0,       64,256,    Z1_01_B_image,  96,480,      16,3,  Z1_01_B_clut    },
    {   TIM_COLOR_256,  576,0,      128,256,    Z1_02_A_image,   0,510,     256,1,  Z1_02_A_clut    },
    {   TIM_COLOR_256,  896,0,      128,256,    Z1_02_B_image,   0,509,     256,1,  Z1_02_B_clut    },
    {   TIM_COLOR_16,   832,0,       64,256,    Z1_03_image,    64,480,      16,5,  Z1_03_clut      },
};

static GsIMAGE BandEventTextureImage[]=
{
    //color             tpos        size        image           pos         size    clut
    {   TIM_COLOR_16,   384,0,      64,256,     font_image,     16,480,     16,6,   font_clut       },
    {   TIM_COLOR_16,   448,0,      64,256,     YorN_image,     0,480,      16,16,  YorN_clut       },
    {   TIM_COLOR_16,   512,0,      64,256,     help_00_image,  0,496,      16,2,   help_00_clut    },
    {   TIM_COLOR_16,   320,0,      64,256,     MMENU_image,    16,489,     16,7,   MMENU_clut      },
    {   TIM_COLOR_256,  704,  0,    128,256,    Z2_01_A_image,   0,508,     256,1,  Z2_01_A_clut    },
    {   TIM_COLOR_256,  320,256,    128,256,    Z2_01_B_image,   0,509,     256,1,  Z2_01_B_clut    },
    {   TIM_COLOR_256,  576,0,      128,256,    Z2_01_C_image,   0,510,     256,1,  Z2_01_C_clut    },
    {   TIM_COLOR_256,  448,256,    128,256,    Z2_02_A_image,   0,507,     256,1,  Z2_02_A_clut    },
    {   TIM_COLOR_256,  832,0,      128,256,    Z2_02_B_image,   0,511,     256,1,  Z2_02_B_clut    },
    {   TIM_COLOR_16,   576,256,     64,256,    Z2_03_image,    80,480,      16,5,  Z2_03_clut      },
    {   TIM_COLOR_16,   960,0,       64,256,    Z2_04_image,    64,480,      16,3,  Z2_04_clut      },
};


//ゲーム部登録データ
static ENTRY_SPRITE_DATA BandGameSpriteData[] =
{
    //  TexNo                       TimLX   TimLY   Height  Width   PalNo
    //---------------------------------------------------------------------------[Z1_01_A.TIM]
    {   TIM_POS_BAND_GAME_Z1_01_A,  0,      0,      240,    256,    0   },  //ゲーム背景左
    //---------------------------------------------------------------------------[Z1_01_B.TIM]
    {   TIM_POS_BAND_GAME_Z1_01_B,  0,      0,      240,    64,     0   },  //ゲーム背景右
    {   TIM_POS_BAND_GAME_Z1_01_B,  66,     0,      126,    144,    1   },  //団長出現時のパターン１
    {   TIM_POS_BAND_GAME_Z1_01_B,  66,     128,    126,    144,    1   },  //団長出現時のパターン２
    {   TIM_POS_BAND_GAME_Z1_01_B,  212,    0,      10,     18,     2   },  //レベルセレクトプレート
    {   TIM_POS_BAND_GAME_Z1_01_B,  212,    12,     14,     20,     2   },  //レベルセレクトプレート枠
    //---------------------------------------------------------------------------[Z1_02_A.TIM]
    {   TIM_POS_BAND_GAME_Z1_02_A,  0,      0,      240,    256,    0   },  //レベルセレクト背景左
    //---------------------------------------------------------------------------[Z1_02_B.TIM]
    {   TIM_POS_BAND_GAME_Z1_02_B,  0,      0,      240,    64,     0   },  //レベルセレクト背景右
    //---------------------------------------------------------------------------[Z1_03.TIM]
    {   TIM_POS_BAND_GAME_Z1_03,    0,      0,      38,     44,     0   },  //団長↓    １パターン
    {   TIM_POS_BAND_GAME_Z1_03,    44,     0,      38,     44,     0   },  //団長↓    ２パターン
    {   TIM_POS_BAND_GAME_Z1_03,    88,     0,      38,     44,     0   },  //団長→    １パターン
    {   TIM_POS_BAND_GAME_Z1_03,    132,    0,      38,     44,     0   },  //団長→    ２パターン
    {   TIM_POS_BAND_GAME_Z1_03,    0,      40,     38,     44,     0   },  //団長↑    １パターン
    {   TIM_POS_BAND_GAME_Z1_03,    44,     40,     38,     44,     0   },  //団長↑    ２パターン
    {   TIM_POS_BAND_GAME_Z1_03,    88,     40,     38,     44,     0   },  //団長←    １パターン
    {   TIM_POS_BAND_GAME_Z1_03,    132,    40,     38,     44,     0   },  //団長←    ２パターン
    {   TIM_POS_BAND_GAME_Z1_03,    0,      80,     30,     44,     1   },  //団員A     １パターン
    {   TIM_POS_BAND_GAME_Z1_03,    46,     80,     30,     44,     1   },  //団員A     ２パターン
    {   TIM_POS_BAND_GAME_Z1_03,    92,     80,     30,     44,     1   },  //団員B     １パターン
    {   TIM_POS_BAND_GAME_Z1_03,    138,    80,     30,     44,     1   },  //団員B     ２パターン
    {   TIM_POS_BAND_GAME_Z1_03,    0,      112,    30,     44,     1   },  //団員C     １パターン
    {   TIM_POS_BAND_GAME_Z1_03,    46,     112,    30,     44,     1   },  //団員C     ２パターン
    {   TIM_POS_BAND_GAME_Z1_03,    92,     112,    30,     44,     1   },  //団員D     １パターン
    {   TIM_POS_BAND_GAME_Z1_03,    138,    112,    30,     44,     1   },  //団員D     ２パターン
    {   TIM_POS_BAND_GAME_Z1_03,    0,      144,    30,     44,     1   },  //団員E     １パターン
    {   TIM_POS_BAND_GAME_Z1_03,    46,     144,    30,     44,     1   },  //団員E     ２パターン
    {   TIM_POS_BAND_GAME_Z1_03,    92,     144,    30,     44,     1   },  //団員F     １パターン
    {   TIM_POS_BAND_GAME_Z1_03,    138,    144,    30,     44,     1   },  //団員F     ２パターン
    {   TIM_POS_BAND_GAME_Z1_03,    0,      176,    30,     44,     1   },  //団員G     １パターン
    {   TIM_POS_BAND_GAME_Z1_03,    46,     176,    30,     44,     1   },  //団員G     ２パターン
    {   TIM_POS_BAND_GAME_Z1_03,    196,    246,    10,     6,      4   },  //番号０
    {   TIM_POS_BAND_GAME_Z1_03,    202,    246,    10,     6,      4   },  //番号１
    {   TIM_POS_BAND_GAME_Z1_03,    208,    246,    10,     6,      4   },  //番号２
    {   TIM_POS_BAND_GAME_Z1_03,    214,    246,    10,     6,      4   },  //番号３
    {   TIM_POS_BAND_GAME_Z1_03,    220,    246,    10,     6,      4   },  //番号４
    {   TIM_POS_BAND_GAME_Z1_03,    226,    246,    10,     6,      4   },  //番号５
    {   TIM_POS_BAND_GAME_Z1_03,    232,    246,    10,     6,      4   },  //番号６
    {   TIM_POS_BAND_GAME_Z1_03,    238,    246,    10,     6,      4   },  //番号７
    {   TIM_POS_BAND_GAME_Z1_03,    244,    246,    10,     6,      4   },  //番号８
    {   TIM_POS_BAND_GAME_Z1_03,    250,    246,    10,     6,      4   },  //番号９
    {   TIM_POS_BAND_GAME_Z1_03,    0,      218,    18,     18,     2   },  //矢印←
    {   TIM_POS_BAND_GAME_Z1_03,    20,     218,    18,     18,     2   },  //矢印↑
    {   TIM_POS_BAND_GAME_Z1_03,    40,     218,    18,     18,     2   },  //矢印→
    {   TIM_POS_BAND_GAME_Z1_03,    60,     218,    18,     18,     2   },  //矢印↓
    {   TIM_POS_BAND_GAME_Z1_03,    92,     208,    36,     32,     2   },  //団員出現煙    １パターン
    {   TIM_POS_BAND_GAME_Z1_03,    126,    208,    36,     32,     2   },  //団員出現煙    ２パターン
    {   TIM_POS_BAND_GAME_Z1_03,    208,    0,      56,     48,     2   },  //ドア１
    {   TIM_POS_BAND_GAME_Z1_03,    208,    58,     56,     48,     2   },  //ドア２
    {   TIM_POS_BAND_GAME_Z1_03,    208,    116,    56,     48,     2   },  //ドア３
    {   TIM_POS_BAND_GAME_Z1_03,    208,    174,    56,     48,     3   },  //ドア４
    //---------------------------------------------------------------------------[Z1_02_B.TIM]
    {   TIM_POS_BAND_GAME_Z1_02_B,  80,     0,      104,    148,    0   },  //レベルセレクトマスク
    //---------------------------------------------------------------------
    {   ENTRY_SPRITE_DATA_END,0,0,0,0,0 }   // データエンド
};


//イベント部登録データ
static ENTRY_SPRITE_DATA BandEventSpriteData[] =
{
    //  TexNo                       TimLX   TimLY   Height  Width   PalNo
    //---------------------------------------------------------------------------[Z2_01_A.TIM]
    {   TIM_POS_BAND_EVENT_Z2_01_A, 0,      0,      240,    256,    0   },      //クリア用入れ替え背景1
    //---------------------------------------------------------------------------[Z2_01_B.TIM]
    {   TIM_POS_BAND_EVENT_Z2_01_B, 0,      0,      240,    256,    0   },      //クリア用入れ替え背景2
    //---------------------------------------------------------------------------[Z2_01_C.TIM]
    {   TIM_POS_BAND_EVENT_Z2_01_C, 0,      0,      240,    64,     0   },      //クリア用入れ替え背景1
    {   TIM_POS_BAND_EVENT_Z2_01_C, 72,     0,      240,    64,     0   },      //クリア用入れ替え背景2
    //---------------------------------------------------------------------------[Z2_02_A.TIM]
    {   TIM_POS_BAND_EVENT_Z2_02_A, 0,      0,      240,    68,     0   },      //全クリア用背景1
    {   TIM_POS_BAND_EVENT_Z2_02_A, 68,     0,      240,    184,    0   },      //全クリア用背景1
    {   TIM_POS_BAND_EVENT_Z2_02_A, 252,    0,      240,    4,      0   },      //全クリア用背景1
    //---------------------------------------------------------------------------[Z2_02_B.TIM]
    {   TIM_POS_BAND_EVENT_Z2_02_B, 0,      0,      240,    256,    0   },      //全クリア用背景2
    //---------------------------------------------------------------------------[Z2_03.TIM]
    {   TIM_POS_BAND_EVENT_Z2_03,   0,      0,      126,    144,    0   },      //クリアデカイ団長１
    {   TIM_POS_BAND_EVENT_Z2_03,   0,      128,    126,    144,    0   },      //クリアデカイ団長２
    {   TIM_POS_BAND_EVENT_Z2_03,   146,    0,      48,     48,     1   },      //全クリア演出用団長１
    {   TIM_POS_BAND_EVENT_Z2_03,   196,    0,      48,     48,     1   },      //全クリア演出用団長２
    {   TIM_POS_BAND_EVENT_Z2_03,   146,    50,     32,     32,     2   },      //全クリア演出用合唱団1（後列）の２パターン
    {   TIM_POS_BAND_EVENT_Z2_03,   180,    50,     32,     32,     2   },      //全クリア演出用合唱団1（後列）の２パターン
    {   TIM_POS_BAND_EVENT_Z2_03,   146,    84,     32,     32,     2   },      //全クリア演出用合唱団2（後列）
    {   TIM_POS_BAND_EVENT_Z2_03,   180,    84,     32,     32,     2   },      //全クリア演出用合唱団2（後列）
    {   TIM_POS_BAND_EVENT_Z2_03,   146,    118,    32,     32,     2   },      //全クリア演出用合唱団3（後列）
    {   TIM_POS_BAND_EVENT_Z2_03,   180,    118,    32,     32,     2   },      //全クリア演出用合唱団3（後列）
    {   TIM_POS_BAND_EVENT_Z2_03,   146,    152,    32,     32,     2   },      //全クリア演出用合唱団4（後列）
    {   TIM_POS_BAND_EVENT_Z2_03,   180,    152,    32,     32,     2   },      //全クリア演出用合唱団4（後列）
    {   TIM_POS_BAND_EVENT_Z2_03,   146,    186,    20,     102,    3   },      //ゲーム終了か否かを選択するアイコン押すとパレット変化
    {   TIM_POS_BAND_EVENT_Z2_03,   146,    208,    20,     90,     3   },      //ゲーム終了か否かを選択するアイコン押すとパレット変化
    {   TIM_POS_BAND_EVENT_Z2_03,   146,    230,    20,     62,     3   },      //ゲーム終了か否かを選択するアイコン押すとパレット変化
    {   TIM_POS_BAND_EVENT_Z2_03,   146,    186,    20,     102,    4   },      //パレット変化
    {   TIM_POS_BAND_EVENT_Z2_03,   146,    208,    20,     90,     4   },      //パレット変化
    {   TIM_POS_BAND_EVENT_Z2_03,   146,    230,    20,     62,     4   },      //パレット変化
    //---------------------------------------------------------------------------[Z2_04.TIM]
    {   TIM_POS_BAND_EVENT_Z2_04,   0,      0,      34,     38,     0   },      //全クリア演出用合唱団1（前列）の２パターン
    {   TIM_POS_BAND_EVENT_Z2_04,   40,     0,      34,     38,     0   },      //全クリア演出用合唱団1（前列）の２パターン
    {   TIM_POS_BAND_EVENT_Z2_04,   80,     0,      34,     38,     0   },      //全クリア演出用合唱団2（前列）
    {   TIM_POS_BAND_EVENT_Z2_04,   120,    0,      34,     38,     0   },      //全クリア演出用合唱団2（前列）
    {   TIM_POS_BAND_EVENT_Z2_04,   160,    0,      34,     38,     2   },      //全クリア演出用合唱団3前列）
    {   TIM_POS_BAND_EVENT_Z2_04,   200,    0,      34,     38,     2   },      //全クリア演出用合唱団3前列）
    {   TIM_POS_BAND_EVENT_Z2_04,   0,      0,      34,     38,     1   },      //全クリア演出用合唱団4（前列）　　　1.2をパレット変えました。
    {   TIM_POS_BAND_EVENT_Z2_04,   40,     0,      34,     38,     1   },      //全クリア演出用合唱団4（前列）　　　1.2をパレット変えました。
    //---------------------------------------------------------------------------[YorNo.TIM]
    {   TIM_POS_BAND_EVENT_YORNO,   0,      0,      115,    186,    0   },      //プレート
    {   TIM_POS_BAND_EVENT_YORNO,   0,      115,    40,     38,     1   },      //非選択・はい 74,57
    {   TIM_POS_BAND_EVENT_YORNO,   38,     115,    40,     44,     1   },      //非選択・いいえ 126,57
    {   TIM_POS_BAND_EVENT_YORNO,   82,     115,    40,     44,     2   },      //選択・はい 72,57
    {   TIM_POS_BAND_EVENT_YORNO,   126,    115,    40,     44,     2   },      //選択・いいえ 126,57
    {   TIM_POS_BAND_EVENT_YORNO,   186,    0,      69,     58,     3   },      //プーぺ１
    {   TIM_POS_BAND_EVENT_YORNO,   186,    69,     69,     58,     3   },      //プーぺ２
    {   TIM_POS_BAND_EVENT_YORNO,   0,      155,    14,     148,    4   },      //もういちど
    {   TIM_POS_BAND_EVENT_YORNO,   0,      170,    14,     148,    4   },      //おわり
    {   TIM_POS_BAND_EVENT_YORNO,   20,     20,     14,     148,    4   },      //つづけ
    //---------------------------------------------------------------------------[font.TIM]
    {   TIM_POS_BAND_EVENT_FONT,     24,    200,    24,     26,     2   },      //指カーソル
    {   TIM_POS_BAND_EVENT_FONT,      0,    232,    15,     52,     4   },      //えらぶ
    {   TIM_POS_BAND_EVENT_FONT,     52,    232,    15,     52,     4   },      //けってい
    {   TIM_POS_BAND_EVENT_FONT,    104,    232,    15,     52,     4   },      //めにゅー
    //---------------------------------------------------------------------------
    {   ENTRY_SPRITE_DATA_END,0,0,0,0,0 }   // データエンド
};



//--------マップデータ
static char InitMapData[SQUARE_H_NUM+2][SQUARE_W_NUM+2]=
{
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
    { -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
    { -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
    { -1,  0,  0,  0,  0,  0, -1, -1,  0,  0,  0,  0,  0, -1 },
    { -1,  0,  0,  0,  0,  0, -1, -1,  0,  0,  0,  0,  0, -1 },
    { -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
    { -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
};

//--------団員番号
static int DaninNoTable[]={
    BAND_CHAR_GAME_NUM_00,
    BAND_CHAR_GAME_NUM_01,
    BAND_CHAR_GAME_NUM_02,
    BAND_CHAR_GAME_NUM_03,
    BAND_CHAR_GAME_NUM_04,
    BAND_CHAR_GAME_NUM_05,
    BAND_CHAR_GAME_NUM_06,
    BAND_CHAR_GAME_NUM_07,
    BAND_CHAR_GAME_NUM_08,
    BAND_CHAR_GAME_NUM_09,
};

//--------オールクリア団員アニメ
static int GakudaninAnmTable[]={
    BAND_CHAR_EVENT_ALLCLEAR_DANTYOU_00,            //全クリア演出用団長１                      0
    BAND_CHAR_EVENT_ALLCLEAR_DANTYOU_01,            //全クリア演出用団長２                      
    BAND_CHAR_EVENT_ALLCLEAR_BACK_DANIN_00,         //全クリア演出用合唱団1（後列）シンバル     2
    BAND_CHAR_EVENT_ALLCLEAR_BACK_DANIN_01,         //全クリア演出用合唱団1（後列）シンバル     
    BAND_CHAR_EVENT_ALLCLEAR_BACK_DANIN_06,         //全クリア演出用合唱団4（後列）タンバリン   4
    BAND_CHAR_EVENT_ALLCLEAR_BACK_DANIN_07,         //全クリア演出用合唱団4（後列）タンバリン   
    BAND_CHAR_EVENT_ALLCLEAR_BACK_DANIN_04,         //全クリア演出用合唱団3（後列）タイコ       6
    BAND_CHAR_EVENT_ALLCLEAR_BACK_DANIN_05,         //全クリア演出用合唱団3（後列）タイコ       
    BAND_CHAR_EVENT_ALLCLEAR_BACK_DANIN_02,         //全クリア演出用合唱団2（後列）ラッパ       8
    BAND_CHAR_EVENT_ALLCLEAR_BACK_DANIN_03,         //全クリア演出用合唱団2（後列）ラッパ       
    BAND_CHAR_EVENT_ALLCLEAR_FRONT_DANIN_00,        //全クリア演出用合唱団1（前列）風船１       10
    BAND_CHAR_EVENT_ALLCLEAR_FRONT_DANIN_01,        //全クリア演出用合唱団1（前列）風船１       
    BAND_CHAR_EVENT_ALLCLEAR_FRONT_DANIN_02,        //全クリア演出用合唱団2（前列）旗１         12
    BAND_CHAR_EVENT_ALLCLEAR_FRONT_DANIN_03,        //全クリア演出用合唱団2（前列）旗１         
    BAND_CHAR_EVENT_ALLCLEAR_FRONT_DANIN_04,        //全クリア演出用合唱団3（前列）旗２         14
    BAND_CHAR_EVENT_ALLCLEAR_FRONT_DANIN_05,        //全クリア演出用合唱団3（前列）旗２         
    BAND_CHAR_EVENT_ALLCLEAR_FRONT_DANIN_06,        //全クリア演出用合唱団4（前列）風船２       16
    BAND_CHAR_EVENT_ALLCLEAR_FRONT_DANIN_07,        //全クリア演出用合唱団4（前列）風船２       
    BAND_CHAR_EVENT_ALLCLEAR_FRONT_DANIN_06,        //全クリア演出用合唱団4（前列）風船３       18
    BAND_CHAR_EVENT_ALLCLEAR_FRONT_DANIN_07,        //全クリア演出用合唱団4（前列）風船３       
};


static GAKUDANIN_DATA InitDataAllClearGkudan[]={
    //  ステータス                          //存在      X       Y       優先                        X移動方向   Y移動方向   表示待ち    停止X   停止Y
    {   ALL_CLEAR_EVENT_GAKUDANIN_WAIT,     1,          140,    76,     PRIORITY_EVENT_DANTYOU,      0,         0,            0,        140,    76  },  //団長
    {   ALL_CLEAR_EVENT_GAKUDANIN_WAIT,     0,          146,    88,     PRIORITY_EVENT_DANIN_BACK,   1,         0,           60,        188,    88  },  //シンバル
    {   ALL_CLEAR_EVENT_GAKUDANIN_WAIT,     0,          146,    88,     PRIORITY_EVENT_DANIN_BACK,  -1,         0,          120,        108,    88  },  //タンバリン
    {   ALL_CLEAR_EVENT_GAKUDANIN_WAIT,     0,          188,    88,     PRIORITY_EVENT_DANIN_BACK,   1,         0,          180,        224,    88  },  //タイコ
    {   ALL_CLEAR_EVENT_GAKUDANIN_WAIT,     0,          108,    88,     PRIORITY_EVENT_DANIN_BACK,  -1,         0,          240,         72,    88  },  //ラッパ
    {   ALL_CLEAR_EVENT_GAKUDANIN_WAIT,     0,          280,    144,    PRIORITY_EVENT_DANIN_FRONT, -1,         0,          300,        146,    144 },  //風船中央
    {   ALL_CLEAR_EVENT_GAKUDANIN_WAIT,     0,            0,    120,    PRIORITY_EVENT_DANIN_FRONT,  1,         0,          360,        110,    120 },  //旗左
    {   ALL_CLEAR_EVENT_GAKUDANIN_WAIT,     0,          280,    120,    PRIORITY_EVENT_DANIN_FRONT, -1,         0,          420,        180,    120 },  //旗右
    {   ALL_CLEAR_EVENT_GAKUDANIN_WAIT,     0,            0,    134,    PRIORITY_EVENT_DANIN_FRONT,  1,         0,          480,        76,     134 },  //風船左
    {   ALL_CLEAR_EVENT_GAKUDANIN_WAIT,     0,          280,    134,    PRIORITY_EVENT_DANIN_FRONT, -1,         0,          540,        210,    134 },  //風船右
};

//144+40 104
//120+40 80
//120+40 80
//134+40 94
//134+40 94


//--------問題
static BAND_PROBLEM BandProblemTable[50][DANIN_NUM]=
{
    {// 00                      //---- LEVEL1
        {   1,  10, 3   },
        {   2,  8,  2   },
        {   3,  4,  4   },
        {   4,  3,  1   },
        {   5,  5,  2   },
        {   6,  1,  6   },
    },      
    {//01
        {   2,  10, 3   },
        {   3,  8,  2   },
        {   4,  4,  4   },
        {   5,  3,  1   },
        {   6,  5,  2   },
        {   7,  1,  6   },
    },      
    {//02
        {   3,  11, 5   },
        {   4,  2,  4   },
        {   5,  4,  6   },
        {   6,  5,  2   },
        {   7,  8,  3   },
        {   8,  12, 1   },
    },
    {//03
        {   4,  11, 5   },
        {   5,  2,  4   },
        {   6,  4,  6   },
        {   7,  5,  2   },
        {   8,  8,  3   },
        {   9,  12, 1   },
    },      
    {//04
        {   5,  2,  4   },
        {   6,  6,  6   },
        {   7,  1,  5   },
        {   8,  10, 2   },
        {   9,  10, 5   },
        {   10, 2,  2   },
    },
    {//05
        {   1,  2,  4   },
        {   2,  6,  6   },
        {   3,  1,  5   },
        {   4,  10, 2   },
        {   5,  10, 5   },
        {   6,  2,  2   },
    },      
    {//06   
        {   2,  7,  6   },
        {   3,  2,  2   },
        {   4,  8,  4   },
        {   5,  1,  6   },
        {   6,  3,  5   },
        {   7,  11, 2   },
    },        
    {//07   
        {   3,  7,  6   },
        {   4,  2,  2   },
        {   5,  8,  4   },
        {   6,  1,  6   },
        {   7,  3,  5   },
        {   8,  11, 2   },
    },      
    {//08   
        {   4,  11, 2   },
        {   5,  9,  4   },
        {   6,  4,  6   },
        {   7,  3,  3   },
        {   8,  2,  5   },
        {   9,  6,  2   },
    },      
    {//09   
        {   5,  11, 2   },
        {   6,  9,  4   },
        {   7,  4,  6   },
        {   8,  3,  3   },
        {   9,  2,  5   },
        {   10, 6,  2   },
    },
    {//10                       //---- LEVEL2
        {   6,  4,  3   },
        {   7,  4,  5   },
        {   8,  10, 3   },
        {   9,  7,  1   },
        {   10, 9,  6   },
        {   11, 2,  4   },
    },      
    {//11
        {   7,  4,  3   },
        {   8,  4,  5   },
        {   9,  10, 3   },
        {   10, 7,  1   },
        {   11, 9,  6   },
        {   12, 2,  4   },
    },
    {//12
        {   8,  6,  1   },
        {   9,  2,  3   },
        {   10, 4,  5   },
        {   11, 4,  2   },
        {   12, 10, 3   },
        {   13, 11, 5   },
    },      
    {//13
        {   9,  6,  1   },
        {   10, 2,  3   },
        {   11, 4,  5   },
        {   12, 4,  2   },
        {   13, 10, 3   },
        {   14, 11, 5   },
    },
    {//14
        {   10, 2,  3   },
        {   11, 4,  4   },
        {   12, 9,  5   },
        {   13, 2,  5   },
        {   14, 12, 1   },
        {   15, 10, 3   },
    },      
    {//15   
        {   11, 2,  3   },
        {   12, 4,  4   },
        {   13, 9,  5   },
        {   14, 2,  5   },
        {   15, 12, 1   },
        {   16, 10, 3   },
    },      
    {//16   
        {   12, 11, 4   },
        {   13, 8,  2   },
        {   14, 3,  2   },
        {   15, 4,  5   },
        {   16, 1,  6   },
        {   17, 9,  6   },
    },      
    {//17   
        {   13, 11, 4   },
        {   14, 8,  2   },
        {   15, 3,  2   },
        {   16, 4,  5   },
        {   17, 1,  6   },
        {   18, 9,  6   },
    },      
    {//18   
        {   14, 2,  2   },
        {   15, 9,  2   },
        {   16, 9,  4   },
        {   17, 2,  4   },
        {   18, 3,  6   },
        {   19, 11, 6   },
    },      
    {//19   
        {   15, 2,  2   },
        {   16, 9,  2   },
        {   17, 9,  4   },
        {   18, 2,  4   },
        {   19, 3,  6   },
        {   20, 11, 6   },
    },
    {//20                       //---- LEVEL3
        {   26, 7,  2   },
        {   27, 1,  3   },
        {   28, 3,  5   },
        {   29, 9,  6   },
        {   30, 11, 4   },
        {   31, 10, 3   },
    },      
    {//21
        {   37, 7,  2   },
        {   38, 1,  3   },
        {   39, 3,  5   },
        {   40, 9,  6   },
        {   41, 11, 4   },
        {   42, 10, 3   },
    },      
    {//22
        {   45, 2,  3   },
        {   46, 4,  4   },
        {   47, 12, 6   },
        {   48, 9,  4   },
        {   49, 9,  3   },
        {   50, 4,  2   },
    },
    {//23
        {   48, 2,  3   },
        {   49, 4,  4   },
        {   50, 12, 6   },
        {   51, 9,  4   },
        {   52, 9,  3   },
        {   53, 4,  2   },
    },
    {//24
        {   59, 4,  2   },
        {   60, 12, 5   },
        {   61, 1,  4   },
        {   62, 4,  5   },
        {   63, 9,  2   },
        {   64, 9,  4   },
    },
    {//25
        {   60, 4,  2   },
        {   61, 12, 5   },
        {   62, 1,  4   },
        {   63, 4,  5   },
        {   64, 9,  2   },
        {   65, 9,  4   },
    },
    {//26
        {   67, 5,  4   },
        {   68, 3,  5   },
        {   69, 8,  6   },
        {   70, 2,  2   },
        {   71, 11, 2   },
        {   72, 11, 5   },
    },      
    {//27
        {   78, 5,  4   },
        {   79, 3,  5   },
        {   80, 8,  6   },
        {   81, 2,  2   },
        {   82, 11, 2   },
        {   83, 11, 5   },
    },      
    {//28
        {   88, 9,  3   },
        {   89, 11, 5   },
        {   90, 2,  5   },
        {   91, 3,  2   },
        {   92, 4,  4   },
        {   93, 11, 3   },
    },
    {//29
        {   88, 9,  3   },  //  {   95, 9,  3   },
        {   89, 11, 5   },  //  {   96, 11, 5   },
        {   90, 2,  5   },  //  {   97, 2,  5   },
        {   91, 3,  2   },  //  {   98, 3,  2   },
        {   92, 4,  4   },  //  {   99, 4,  4   },
        {   93, 11, 3   },  //  {   100,11, 3   },
    },
    {//30                       //---- LEVEL4
        {   10, 9,  2   },
        {   20, 10, 4   },
        {   30, 3,  6   },
        {   40, 7,  6   },
        {   50, 2,  4   },
        {   60, 3,  3   },
    },      
    {//31
        {   20, 9,  2   },
        {   30, 10, 4   },
        {   40, 3,  6   },
        {   50, 7,  6   },
        {   60, 2,  4   },
        {   70, 3,  3   },
    },      
    {//32
        {   30, 8,  1   },
        {   40, 10, 4   },
        {   50, 3,  3   },
        {   60, 1,  5   },
        {   70, 9,  3   },
        {   80, 4,  4   },
    },
    {//33
        {   40, 8,  1   },
        {   50, 10, 4   },
        {   60, 3,  3   },
        {   70, 1,  5   },
        {   80, 9,  3   },
        {   90, 4,  4   },
    },
    {//34
        {   30, 8,  1   },  //  {   50, 2,  2   },
        {   40, 10, 4   },  //  {   60, 4,  3   },
        {   50, 3,  3   },  //  {   70, 3,  5   },
        {   60, 1,  5   },  //  {   80, 8,  2   },
        {   70, 9,  3   },  //  {   90, 11, 3   },
        {   80, 4,  4   },  //  {   100,9,  4   },
    },      
    {//35   
        {   10, 2,  2   },
        {   20, 4,  3   },
        {   30, 3,  5   },
        {   40, 8,  2   },
        {   50, 11, 3   },
        {   60, 9,  4   },
    },      
    {//36   
        {   20, 4,  2   },
        {   30, 8,  4   },
        {   40, 1,  5   },
        {   50, 1,  1   },
        {   60, 12, 1   },
        {   70, 11, 5   },
    },      
    {//37   
        {   30, 4,  2   },
        {   40, 8,  4   },
        {   50, 1,  5   },
        {   60, 1,  1   },
        {   70, 12, 1   },
        {   80, 11, 5   },
    },      
    {//38   
        {   40, 3,  2   },
        {   50, 9,  5   },
        {   60, 4,  4   },
        {   70, 8,  2   },
        {   80, 3,  5   },
        {   90, 11, 3   },
    },      
    {//39   
        {   40, 3,  2   },  //{ 50, 3,  2   },
        {   50, 9,  5   },  //{ 60, 9,  5   },
        {   60, 4,  4   },  //{ 70, 4,  4   },
        {   70, 8,  2   },  //{ 80, 8,  2   },
        {   80, 3,  5   },  //{ 90, 3,  5   },
        {   90, 11, 3   },  //{ 100,11, 3   },
    },
    {//40                       //---- LEVEL5
        {   1,  1,  5   },
        {   3,  11, 1   },
        {   5,  9,  4   },
        {   7,  4,  3   },
        {   9,  3,  5   },
        {   11, 10, 6   },
    },
    {//41
        {   5,  1,  5   },
        {   7,  11, 1   },
        {   9,  9,  4   },
        {   11, 4,  3   },
        {   13, 3,  5   },
        {   15, 10, 6   },
    },
    {//42
        {   14, 3,  2   },
        {   16, 2,  5   },
        {   18, 10, 6   },
        {   20, 9,  3   },
        {   22, 4,  4   },
        {   24, 12, 4   },
    },
    {//43
        {   27, 3,  2   },
        {   29, 2,  5   },
        {   31, 10, 6   },
        {   33, 9,  3   },
        {   35, 4,  4   },
        {   37, 12, 4   },
    },
    {//44
        {   30, 9,  3   },
        {   32, 11, 5   },
        {   34, 8,  6   },
        {   36, 8,  2   },
        {   38, 2,  3   },
        {   40, 3,  4   },
    },
    {//45
        {   38, 9,  3   },
        {   40, 11, 5   },
        {   42, 8,  6   },
        {   44, 8,  2   },
        {   46, 2,  3   },
        {   48, 3,  4   },
    },      
    {//46
        {   53, 3,  2   },
        {   55, 9,  2   },
        {   57, 9,  6   },
        {   59, 2,  4   },
        {   61, 10, 4   },
        {   63, 11, 4   },
    },      
    {//47
        {   66, 3,  2   },
        {   68, 9,  2   },
        {   70, 9,  6   },
        {   72, 2,  4   },
        {   74, 10, 4   },
        {   76, 11, 4   },
    },      
    {//48
        {   79, 2,  2   },
        {   81, 9,  5   },
        {   83, 4,  4   },
        {   85, 2,  4   },
        {   87, 10, 2   },
        {   89, 4,  3   },
    },
    {//49
        {   79, 2,  2   },  //      {   90, 2,  2   },
        {   81, 9,  5   },  //      {   92, 9,  5   },
        {   83, 4,  4   },  //      {   94, 4,  4   },
        {   85, 2,  4   },  //      {   96, 2,  4   },
        {   87, 10, 2   },  //      {   98, 10, 2   },
        {   89, 4,  3   },  //      {   100,4,  3   },
    },  
};


//--------BGM
static int BGMIndexTable[]={
    BAND_BGM_00,    
    BAND_BGM_01,    
    BAND_BGM_02,    
    BAND_BGM_03,    
    BAND_BGM_04,    
    BAND_BGM_05,    
    BAND_BGM_06,    
};


//  MetuseijiFlag   <-  OFF　でスクリプトのメッセージ終了を確認

//------------------------------------------------------------------------XA
//----勧誘成功音
static int XaCatchWaitTable[]=
{
    2,  
    14, 
    3,  
    4,  
    15, 
    13, 
};


//------------------------------------------------------------------------SCRIPT
//----初プレイデモ団長
#define INIT_PLAY_DEMO_SCRIPT_BASE                  0
#define INIT_PLAY_DEMO_SCRIPT_NUM                   2
//----ゲーム開始時ビック団長のお話
#define DANTYOU_SPEAK_SCRIPT_BASE                   2
#define DANTYOU_SPEAK_SCRIPT_NUM                    2
//----クリア時の団長のお話
#define DANTYOU_CLEAR_SCRIPT_BASE                   4
#define DANTYOU_CLEAR_SCRIPT_NUM                    2
//----オールクリア時の団長のお話
#define DANTYOU_ALL_CLEAR_SCRIPT_BASE               6
#define DANTYOU_ALL_CLEAR_SCRIPT_NUM                2
//----レベルセレクト時の団長のお話
#define DANTYOU_SELECT_LEVEL_SCRIPT_BASE            8
#define DANTYOU_SELECT_LEVEL_SCRIPT_NUM             1


//----スクリプト本体
static SCRIP_DATA BandScript[]=
{
    //----------------初プレイデモ団長
    {//ワシは、この　「ぞろぞろバンド」のリーダーなのだ。
        0,
        NamePlateDan,
        XA_FILE_BAND00,
        0,
        "初音時０６わしは、この　「ぞろぞろバンド」の改リーダーなのだ。待２４０終"
    },
    {//おおっ、たいへん！もうすぐ、パレードなのだ！
        0,
        NamePlateDan,
        XA_FILE_BAND00,
        1,
        "初音時０６おおっ、たいへん！　もうすぐ　改パレードなのだ！待４００終"
    },
    //----------------ゲーム開始時ビック団長のお話
    {//メンバー、しゅうごう！
        0,
        NamePlateDan,
        XA_FILE_BAND01,
        0,
        "初音時０６メンバー、しゅうごう！待１８０終"
    },
    {//じゅんばんに　ならぶのだぁぁ！
        0,
        NamePlateDan,
        XA_FILE_BAND01,
        1,
        "初音時０６じゅんばんに　ならぶのだ！待３００終"
    },
    //----------------クリア時の団長のお話
    {//やったぁ～！おみごと～。
        0,
        NamePlateDan,
        XA_FILE_BAND02,
        0,
        "初音時０６やった！　おみごと。待２４０終"
    },
    {//パレードにしゅっぱつなのだ！
        0,
        NamePlateDan,
        XA_FILE_BAND02,
        1,
        "初音時０６パレードに　しゅっぱつなのだ！待２８０終"
    },
    //----------------オールクリア時の団長のお話
    {//スバラシイのだぁぁ！
        0,
        NamePlateDan,
        XA_FILE_BAND02,
        3,
        "初音時０６すばらしいのだ！待２２０終"
    },
    {//ワシの　バンドは、せかいいちなのだぁぁ！
        0,
        NamePlateDan,
        XA_FILE_BAND02,
        4,
        "初音時０６ワシの　バンドは、改せかいいちなのだぁぁ！待３００終"
    },
    //----------------レベルセレクト時の団長のお話
    {//ひかっている　すうじを　えらんでくれ。
        0,
        NamePlateDan,
        XA_FILE_BAND00,
        4,
        "初音時０６ひかっている　すうじを　えらんでくれ。待３００終"
    },
};




//-----------------------------------------------------------------------------
// codes 
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  関数名 :Band
//  機能   :ゲームタスク
//  注意   :なし
//-----------------------------------------------------------------------------
int Band(GAMEMGR * ip_GameMgr)
{
    TASK Task;
    int i;

    switch( ip_GameMgr->SubMode )
    {
        case INIT:
            //----メインモード
            ip_GameMgr->SubMode = MAIN;

            //----スプライトマネージャ初期化
            InitSprite();

            //----タスクマネージャ初期化
            InitTaskMgr();

            //----ランダム設定
            srand(ip_GameMgr->Timer);

            //----岩澤担当部分：初期化
            SfileRead2(BAND_SOUNDFILE_00);
            HelpInit();
            GameMgr.WaitFlag    = ON;


#ifdef __DEBUG_BAND__
            GameMgr.FadeFlag    = FadeIn;
#endif

            //---- ゲーム管理情報初期化
            BGameMgr.BgmIndex       = 0;
            BGameMgr.Level          = ip_GameMgr->Level[GAME_BAND]; //ゲームレベル
            BGameMgr.PlayLevel      = 0;                            //ゲームプレイレベル
            BGameMgr.GetNum         = 0;                            //取得人数
            BGameMgr.ContinueFlag   = 0;                            //継続フラグ
            BGameMgr.ProblemIndex   = 0;                            //問題インデックス
            BGameMgr.ClearFlag      = 0;                            //クリアフラグ
            BGameMgr.AllClearFlag   = 0;                            //オールクリアフラグ
            BGameMgr.ExitFlag       = 0;                            //終了フラグ

#ifdef __DEBUG_BAND__
            if(NewPad & PADR1){
                Task.func       = AllClearEventTask;
                Task.priority   = TASK_NO_DEBUG;
                Task.attribute  = ATTR_USER;
                Task.status     = TASK_NEW_ENTRY;
                Task.id         = TASK_NO_DEBUG;
                Task.wait_time  = 0;
                Task.buf        = NULL;
                Task.name       = "AllClearEventTask";
                Task.mode       = TASK_MODE_INIT;
                CreateTask(&Task);
            }else
            if(NewPad & PADL1)
            {//
                Task.func       = DebugGameSpriteTask;
                Task.priority   = TASK_NO_DEBUG;
                Task.attribute  = ATTR_USER;
                Task.status     = TASK_NEW_ENTRY;
                Task.id         = TASK_NO_DEBUG;
                Task.wait_time  = 0;
                Task.buf        = NULL;
                Task.name       = "DebugGameSpriteTask";
                Task.mode       = TASK_MODE_INIT;
                CreateTask(&Task);
            }else
            if(NewPad & PADL2)
            {//
                Task.func       = DebugEventSpriteTask;
                Task.priority   = TASK_NO_DEBUG;
                Task.attribute  = ATTR_USER;
                Task.status     = TASK_NEW_ENTRY;
                Task.id         = TASK_NO_DEBUG;
                Task.wait_time  = 0;
                Task.buf        = NULL;
                Task.name       = "DebugEventSpriteTask";
                Task.mode       = TASK_MODE_INIT;
                CreateTask(&Task);
            }else
            if(NewPad & PADR2)
            {
                Task.func       = ClearEventTask;
                Task.priority   = TASK_NO_DEBUG;
                Task.attribute  = ATTR_USER;
                Task.status     = TASK_NEW_ENTRY;
                Task.id         = TASK_NO_DEBUG;
                Task.wait_time  = 0;
                Task.buf        = NULL;
                Task.name       = "ClearEventTask";
                Task.mode       = TASK_MODE_INIT;
                CreateTask(&Task);
            }else
            {//
                if(BGameMgr.Level==0)
                {//レベル１をクリアしていない場合はゲームコントローラタスクを呼ぶ
                    Task.func       = GameControllTask;
                    Task.priority   = TASK_NO_GAME_CONTROLL;
                    Task.attribute  = ATTR_USER;
                    Task.status     = TASK_NEW_ENTRY;
                    Task.id         = TASK_NO_GAME_CONTROLL;
                    Task.wait_time  = 0;
                    Task.buf        = NULL;
                    Task.name       = "GameControllTask";
                    Task.mode       = TASK_MODE_INIT;
                    CreateTask(&Task);
                }else
                {//レベル１以上をクリアしていル場合はレベルセレクトタスクを呼ぶ
                    Task.func       = SelectLevelTask;
                    Task.priority   = TASK_NO_GAME_SELECT_LEVEL;
                    Task.attribute  = ATTR_USER;
                    Task.status     = TASK_NEW_ENTRY;
                    Task.id         = TASK_NO_GAME_SELECT_LEVEL;
                    Task.wait_time  = 0;
                    Task.buf        = NULL;
                    Task.name       = "SelectLevelTask";
                    Task.mode       = TASK_MODE_INIT;
                    CreateTask(&Task);
                }
            }
#else
            if(BGameMgr.Level==0)
            {//レベル１をクリアしていない場合はゲームコントローラタスクを呼ぶ
                Task.func       = GameControllTask;
                Task.priority   = TASK_NO_GAME_CONTROLL;
                Task.attribute  = ATTR_USER;
                Task.status     = TASK_NEW_ENTRY;
                Task.id         = TASK_NO_GAME_CONTROLL;
                Task.wait_time  = 0;
                Task.buf        = NULL;
                Task.name       = "GameControllTask";
                Task.mode       = TASK_MODE_INIT;
                CreateTask(&Task);
            }else
            {//レベル１以上をクリアしていル場合はレベルセレクトタスクを呼ぶ
                Task.func       = SelectLevelTask;
                Task.priority   = TASK_NO_GAME_SELECT_LEVEL;
                Task.attribute  = ATTR_USER;
                Task.status     = TASK_NEW_ENTRY;
                Task.id         = TASK_NO_GAME_SELECT_LEVEL;
                Task.wait_time  = 0;
                Task.buf        = NULL;
                Task.name       = "SelectLevelTask";
                Task.mode       = TASK_MODE_INIT;
                CreateTask(&Task);
            }
#endif

            break;
        case MAIN:
            //-----------------------------------------ゲームメインループ▼
            //ゲームタスクは登録
            FntPrint("");   //呼んでおかないとダメ

            ExecuteTask();
            TransSprite();
            SpraitControl();

            //終了チェック
            if(BGameMgr.ExitFlag) ip_GameMgr->SubMode = EXIT;
            //-----------------------------------------------------------▲
            break;
        case EXIT:

            //ゲームレベル
            ip_GameMgr->Level[GAME_BAND]    = BGameMgr.Level;

            //----岩澤担当部分：終了
            SpraitCharClr();
            SpraitControl();
            GameMgr.WaitFlag = ON;
            //[♪] 内臓音源ストップ
            for(i=0;i<MAX_BGM_NUM;i++){
                ssStopBgm(BGMIndexTable[i]);
            }
            //[♪] サウンド停止
            ssStopAll();
            ssCloseVab();

            //メインメニューへ
            ip_GameMgr->MainMode    = MAIN_MODE_TOP_MENU;
            ip_GameMgr->SubMode     = INIT;
            
            break;
        default:
            break;
    }
    
    return TRUE;
}


//-----------------------------------------------------------------------------
//  関数名 :GameControllTask
//  機能   :ゲームコントロールタスク
//  注意   :なし
//-----------------------------------------------------------------------------
static int GameControllTask(TASK* ip_task)
{
    TASK Task;
    int i;


    switch( ip_task->mode )
    {
        case TASK_MODE_INIT:
            //next main
            ip_task->mode = TASK_MODE_MAIN;

            //----texture read sram -> vram
            if((file_read(BandGameTextureFile[0].fn,LoadAddress)) == -1)
            {//read error
                return FALSE;
            }

            //----texture init
            TexInit( BAND_GAME_TIM_NUM, &BandGameTextureImage[BAND_GAME_TIM_POS] );
            TimImgData = BandGameTextureImage;

            //----ゲーム用スプライト登録
            EntrySprite( BandGameSpriteData );

            //---- ゲーム管理情報初期化
            BGameMgr.BgmIndex       = 0;
        //  BGameMgr.Level          = 0;        //ゲームレベル
            BGameMgr.GetNum         = 0;        //取得人数
            BGameMgr.ProblemIndex   = 0;        //問題インデックス
            BGameMgr.ClearFlag      = 0;        //クリアフラグ
            BGameMgr.AllClearFlag   = 0;        //オールクリアフラグ

            //ガイドセット
            GaidoInit();

            if(BGameMgr.ContinueFlag==0)
            {//初プレイ
                BGameMgr.ContinueFlag = 1;
                
                //出現タスク
                Task.func       = AppearDantyouTask;
                Task.priority   = TASK_NO_GAME_APPEAR_DANTYOU;
                Task.attribute  = ATTR_USER;
                Task.status     = TASK_NEW_ENTRY;
                Task.id         = TASK_NO_GAME_APPEAR_DANTYOU;
                Task.wait_time  = 0;
                Task.buf        = NULL;
                Task.name       = "AppearDantyouTask";
                Task.mode       = TASK_MODE_INIT;
                CreateTask(&Task);
            }else
            {//継続プレイ
                //団長タスク
                Task.func       = DantyouTask;
                Task.priority   = TASK_NO_GAME_DANTYOU;
                Task.attribute  = ATTR_USER;
                Task.status     = TASK_NEW_ENTRY;
                Task.id         = TASK_NO_GAME_DANTYOU;
                Task.wait_time  = 0;
                Task.buf        = NULL;
                Task.name       = "DantyouTask";
                Task.mode       = TASK_MODE_INIT;
                CreateTask(&Task);
                
                //背景タスク
                Task.func       = GameBgTask;
                Task.priority   = TASK_NO_GAME_BG;
                Task.attribute  = ATTR_USER;
                Task.status     = TASK_NEW_ENTRY;
                Task.id         = TASK_NO_GAME_BG;
                Task.wait_time  = 0;
                Task.buf        = NULL;
                Task.name       = "GameBgTask";
                Task.mode       = TASK_MODE_INIT;
                CreateTask(&Task);
            }
            
            break;
        case TASK_MODE_MAIN:
            //------------▼

#ifdef __DEBUG_BAND__
            FntPrint("LEVEL____=%d\n",  BGameMgr.Level);
            FntPrint("PLAYLEVEL=%d\n",  BGameMgr.PlayLevel);
#endif
            if(BGameMgr.ClearFlag){
                ip_task->mode=TASK_MODE_EXIT;
            }

            //------------▲
            break;
        case TASK_MODE_EXIT:

            //[♪] 内臓音源ストップ
            for(i=0;i<MAX_BGM_NUM;i++){
                ssStopBgm(BGMIndexTable[i]);
            }

            //念のため全削除
            RemoveTask(TASK_NO_GAME_DANTYOU);
            RemoveTask(TASK_NO_GAME_DANIN);
            RemoveTask(TASK_NO_GAME_BG);
            RemoveTask(TASK_NO_GAME_PAUSE);

            //登録スプライト開放
            ReleaseSprite();

            //ガイド破棄
            SpraitCharClr();

            //クリアタスク
            Task.func       = ClearEventTask;
            Task.priority   = TASK_NO_GAME_CLEAR_EVENT;
            Task.attribute  = ATTR_USER;
            Task.status     = TASK_NEW_ENTRY;
            Task.id         = TASK_NO_GAME_CLEAR_EVENT;
            Task.wait_time  = 0;
            Task.buf        = NULL;
            Task.name       = "ClearEventTask";
            Task.mode       = TASK_MODE_INIT;
            CreateTask(&Task);

            //自分を削除
            ExitTask(ip_task->id);
            break;
        default:
    }

    return TRUE;
}


//-----------------------------------------------------------------------------
//  関数名  :AppearDantyouTask
//
//  work    :出現タスク
//  in      :TASK* ip_task
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int AppearDantyouTask(TASK* ip_task)
{
    static int AppearDantyouAnmTable[]={
        BAND_CHAR_GAME_DANTYOU_BIG_00,
        BAND_CHAR_GAME_DANTYOU_BIG_01,
    };
    TASK Task;
    SPRITE_DATA SpData;

    switch(ip_task->mode)
    {
        //--------------------------------------------------------------------
        case TASK_MODE_INIT:
            //next main
            ip_task->mode = TASK_MODE_MAIN;

            // フェードINます
            GameMgr.FadeFlag    = FadeIn;

            BGameMgr.AppearDantyou.Character.Anm.Data.no    = 0;
            BGameMgr.AppearDantyou.Character.Anm.Data.wt    = 0;
            BGameMgr.AppearDantyou.Character.Anm.Index      = 0;
            BGameMgr.AppearDantyou.Character.Pos.x          = 0;
            BGameMgr.AppearDantyou.Character.Pos.y          = 0;
            BGameMgr.AppearDantyou.Character.Pos.x          = 0;
            BGameMgr.AppearDantyou.Character.Pos.y          = 0;
            BGameMgr.AppearDantyou.Character.Pos.z          = 0;
            BGameMgr.AppearDantyou.Character.OPos.x         = 0;
            BGameMgr.AppearDantyou.Character.OPos.y         = 0;
            BGameMgr.AppearDantyou.Character.OPos.z         = 0;
            BGameMgr.AppearDantyou.WaitTimer                = 0;
            BGameMgr.AppearDantyou.WaitFlag                 = 0;

            //スクリプト
            BGameMgr.Script.Flag= 1;
            Task.func           = ScriptTask;
            Task.priority       = TASK_NO_GAME_SCRIPT;
            Task.attribute      = ATTR_USER;
            Task.status         = TASK_NEW_ENTRY;
            Task.id             = TASK_NO_GAME_SCRIPT;
            Task.wait_time      = 0;
            Task.buf            = NULL;
            Task.name           = "ScriptTask";
            Task.mode           = TASK_MODE_INIT;
            Task.user[0]        = SCRIPT_LINE_2;
            Task.user[1]        = INIT_PLAY_DEMO_SCRIPT_BASE;
            Task.user[2]        = INIT_PLAY_DEMO_SCRIPT_NUM;
            CreateTask(&Task);

            break;
        //--------------------------------------------------------------------
        case TASK_MODE_MAIN:
            if(!BGameMgr.AppearDantyou.WaitFlag){
                if(++BGameMgr.AppearDantyou.WaitTimer > EVENT_APPEAR_DANTYOU_TIME)
                {
                    if(!BGameMgr.Script.Flag){
                        BGameMgr.AppearDantyou.WaitFlag = 1;
                        Task.func           = EventFadeOutTask;
                        Task.priority       = TASK_NO_GAME_FADE;
                        Task.attribute      = ATTR_USER;
                        Task.status         = TASK_NEW_ENTRY;
                        Task.id             = TASK_NO_GAME_FADE;
                        Task.wait_time      = 0;
                        Task.buf            = NULL;
                        Task.name           = "EventFadeOutTask";
                        Task.mode           = TASK_MODE_INIT;
                        Task.user[0]        = ip_task->id;
                        CreateTask(&Task);
                    }
                }
            }

            //----団長
            if(++BGameMgr.AppearDantyou.Character.Anm.Data.wt>EVENT_SELECT_LEVEL_ANM_TIME){

                BGameMgr.AppearDantyou.Character.Anm.Data.wt    = 0;
                BGameMgr.AppearDantyou.Character.Anm.Index      ^=1;
            }

            //団長
            SpData.No       = AppearDantyouAnmTable[BGameMgr.AppearDantyou.Character.Anm.Index];
            SpData.PosX     = 96;
            SpData.PosY     = 56+42;
            SpData.PosZ     = PRIORITY_EVENT_BG-2;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );

            //マスク
            SpData.No       = BAND_CHAR_GAME_LEVEL_SELECT_BG_MASK;
            SpData.PosX     = 88;
            SpData.PosY     = 12;
            SpData.PosZ     = PRIORITY_EVENT_BG;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );

            //背景←
            SpData.No       = BAND_CHAR_GAME_LEVEL_SELECT_BG_00;
            SpData.PosX     = 0;
            SpData.PosY     = 0;
            SpData.PosZ     = PRIORITY_EVENT_BG;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );
            
            //背景→
            SpData.No       = BAND_CHAR_GAME_LEVEL_SELECT_BG_01;
            SpData.PosX     = 256;
            SpData.PosY     = 0;
            SpData.PosZ     = PRIORITY_EVENT_BG;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );
            
            break;
        //--------------------------------------------------------------------
        case TASK_MODE_EXIT:
            //スクリプトOFF
            MetuseijiFlag=OFF;
            
            //団長タスク
            Task.func       = DantyouTask;
            Task.priority   = TASK_NO_GAME_DANTYOU;
            Task.attribute  = ATTR_USER;
            Task.status     = TASK_NEW_ENTRY;
            Task.id         = TASK_NO_GAME_DANTYOU;
            Task.wait_time  = 0;
            Task.buf        = NULL;
            Task.name       = "DantyouTask";
            Task.mode       = TASK_MODE_INIT;
            CreateTask(&Task);
            
            //背景タスク
            Task.func       = GameBgTask;
            Task.priority   = TASK_NO_GAME_BG;
            Task.attribute  = ATTR_USER;
            Task.status     = TASK_NEW_ENTRY;
            Task.id         = TASK_NO_GAME_BG;
            Task.wait_time  = 0;
            Task.buf        = NULL;
            Task.name       = "GameBgTask";
            Task.mode       = TASK_MODE_INIT;
            CreateTask(&Task);

            //自分を削除
            ExitTask(ip_task->id);
            break;
        default:
    }

    return TRUE;
}


//-----------------------------------------------------------------------------
//  関数名 :DantyouTask
//  機能   :団長のタスク
//  注意   :なし
//-----------------------------------------------------------------------------
static int DantyouTask(TASK* ip_task)
{
    int i,dir;
    SPRITE_DATA SpData;
    TASK Task;

    static int DantyouAnmTable[]={
        BAND_CHAR_GAME_DANTYOU_00,BAND_CHAR_GAME_DANTYOU_01,    //↓/0
        BAND_CHAR_GAME_DANTYOU_02,BAND_CHAR_GAME_DANTYOU_03,    //→/2
        BAND_CHAR_GAME_DANTYOU_04,BAND_CHAR_GAME_DANTYOU_05,    //↑/4
        BAND_CHAR_GAME_DANTYOU_06,BAND_CHAR_GAME_DANTYOU_07,    //←/6
    };

    static ANMDATA DoorAnmTable[]={
        {   BAND_CHAR_GAME_DOOR_00, DOOR_ANM_00_TIME    },
        {   BAND_CHAR_GAME_DOOR_01, DOOR_ANM_01_TIME    },
        {   BAND_CHAR_GAME_DOOR_02, DOOR_ANM_02_TIME    },
        {   BAND_CHAR_GAME_DOOR_02, DOOR_ANM_03_TIME    },
        {   BAND_CHAR_GAME_DOOR_01, DOOR_ANM_04_TIME    },
        {   BAND_CHAR_GAME_DOOR_00, DOOR_ANM_05_TIME    },
        {   BAND_CHAR_GAME_DOOR_00, DOOR_ANM_05_TIME    },
        {   BAND_CHAR_GAME_DOOR_00, DOOR_ANM_05_TIME    },
        {   BAND_CHAR_GAME_DOOR_00, DOOR_ANM_05_TIME    },
        {   BAND_CHAR_GAME_DOOR_00, DOOR_ANM_05_TIME    },
        {   BAND_CHAR_GAME_DOOR_00, DOOR_ANM_05_TIME    },
        {   BAND_CHAR_GAME_DOOR_00, DOOR_ANM_05_TIME    },
        {   BAND_CHAR_GAME_DOOR_00, DOOR_ANM_05_TIME    },
        {   BAND_CHAR_GAME_DOOR_00, DOOR_ANM_05_TIME    },
//      {   BAND_CHAR_GAME_DOOR_00, DOOR_ANM_05_TIME    },
//      {   BAND_CHAR_GAME_DOOR_00, DOOR_ANM_05_TIME    },
        {   ANM_STOP,0  },
    };

    static ANMDATA DantyouOpenningTalkAnmTable[]={
        {   BAND_CHAR_GAME_DANTYOU_BIG_00,  30          },
        {   BAND_CHAR_GAME_DANTYOU_BIG_01,  30          },
        {   BAND_CHAR_GAME_DANTYOU_BIG_00,  30          },
        {   BAND_CHAR_GAME_DANTYOU_BIG_01,  30          },
        {   BAND_CHAR_GAME_DANTYOU_BIG_00,  30          },
        {   BAND_CHAR_GAME_DANTYOU_BIG_01,  30          },
        {   BAND_CHAR_GAME_DANTYOU_BIG_00,  30          },
        {   BAND_CHAR_GAME_DANTYOU_BIG_01,  30          },
        {   BAND_CHAR_GAME_DANTYOU_BIG_00,  30          },
        {   BAND_CHAR_GAME_DANTYOU_BIG_01,  30          },
        {   BAND_CHAR_GAME_DANTYOU_BIG_00,  30          },
        {   BAND_CHAR_GAME_DANTYOU_BIG_01,  30          },
        {   BAND_CHAR_GAME_DANTYOU_BIG_00,  30          },
        {   BAND_CHAR_GAME_DANTYOU_BIG_01,  30          },
//      {   BAND_CHAR_GAME_DANTYOU_BIG_00,  30          },
//      {   BAND_CHAR_GAME_DANTYOU_BIG_01,  30          },
        {   ANM_STOP,0  },
    };

    static ARR_POS ClearAlignmenTable[]={
        {   3,  2   },{ 10, 2   },      //左上(AREA-A)  /   0
        {   10, 2   },{ 3,  2   },      //右上(AREA-B)  /   2
        {   3,  5   },{ 10, 5   },      //左下(AREA-C)  /   4
        {   10, 5   },{ 3,  5   },      //右下(AREA-D)  /   6
    };


    switch(ip_task->mode)
    {
        case TASK_MODE_INIT:
            //next main
            ip_task->mode = TASK_MODE_MAIN;

            // フェードINます
            GameMgr.FadeFlag    = FadeIn;

            //団長初期化
            BGameMgr.Dantyou.Status                 = DANTYOU_APPEAR;
            BGameMgr.Dantyou.Character.Anm.Data.no  = BAND_CHAR_GAME_DANTYOU_00;
            BGameMgr.Dantyou.Character.Anm.Data.wt  = 0;
            BGameMgr.Dantyou.Character.Anm.Index    = 0;
            BGameMgr.Dantyou.AnmBase                = 0;
            BGameMgr.Dantyou.AppearTimer            = 0;
            BGameMgr.Dantyou.DoorOpenTime           = DOOR_ANM_00_TIME + DOOR_ANM_01_TIME + DOOR_ANM_02_TIME;
            BGameMgr.Dantyou.DoorAnmIndex           = 0;
            BGameMgr.Dantyou.DoorAnmNo              = DoorAnmTable[BGameMgr.Dantyou.DoorAnmIndex].no;
            BGameMgr.Dantyou.DoorAnmWaitTimer       = DoorAnmTable[BGameMgr.Dantyou.DoorAnmIndex].wt;
            BGameMgr.Dantyou.AppearMode             = 0;
            BGameMgr.Dantyou.ClearArea              = 0;
            BGameMgr.Dantyou.ClearWaitTimer         = CLEAR_WAIT_TIMER;

    //      BGameMgr.Dantyou.Character.Pos.x        = MAP_LEFT_X + (SQUARE_W * (7-1))+SQUARE_W/2;
    //      BGameMgr.Dantyou.Character.Pos.y        = MAP_LEFT_Y + (SQUARE_H * (5-1))+SQUARE_H/2;
            BGameMgr.Dantyou.Character.Pos.x        = MAP_LEFT_X + (SQUARE_W * (7-1));
            BGameMgr.Dantyou.Character.Pos.y        = MAP_LEFT_Y + (SQUARE_H * (5-1))-SQUARE_H;
            BGameMgr.Dantyou.Character.Pos.z        = PRIORITY_GAME_BG-6;
            BGameMgr.Dantyou.Character.OPos.x       = 18;
            BGameMgr.Dantyou.Character.OPos.y       = 20;
            BGameMgr.Dantyou.Index                  = START_POS_INDEX;
            
            for(i=0;i<POS_ARR_NUM;i++){
                BGameMgr.Dantyou.Xarr[i] = BGameMgr.Dantyou.Character.Pos.x;
                BGameMgr.Dantyou.Yarr[i] = BGameMgr.Dantyou.Character.Pos.y;
            }
            
            BGameMgr.Dantyou.GetIndex               = 0;
            BGameMgr.Dantyou.Px                     = INIT_ARR_POSX;
            BGameMgr.Dantyou.Py                     = INIT_ARR_POSY;
            BGameMgr.Dantyou.MoveX                  = 0;
            BGameMgr.Dantyou.MoveY                  = 0;
            BGameMgr.Dantyou.MoveCount              = 0;
            
            //マップ初期化
            InitMap();
            
            //[♪] ドア開き
            ssPlaySe(BAND_SE_01);
            
            //スクリプト
            Task.func           = ScriptTask;
            Task.priority       = TASK_NO_GAME_SCRIPT;
            Task.attribute      = ATTR_USER;
            Task.status         = TASK_NEW_ENTRY;
            Task.id             = TASK_NO_GAME_SCRIPT;
            Task.wait_time      = 0;
            Task.buf            = NULL;
            Task.name           = "ScriptTask";
            Task.mode           = TASK_MODE_INIT;
            Task.user[0]        = SCRIPT_LINE_2;
            Task.user[1]        = DANTYOU_SPEAK_SCRIPT_BASE;
            Task.user[2]        = DANTYOU_SPEAK_SCRIPT_NUM;
            CreateTask(&Task);
            
            break;
        case TASK_MODE_MAIN:
        //  FntPrint("DoorOpenTime=%d\n",BGameMgr.Dantyou.DoorOpenTime);
            //キャラ動作
            switch(BGameMgr.Dantyou.Status)
            {
                case DANTYOU_APPEAR:        //出現
                    //小さいキャラ→ビックで話す
                    if(BGameMgr.Dantyou.AppearMode==0)
                    {//ドアオープン
                        //団長描画
                        SpData.No       = BGameMgr.Dantyou.Character.Anm.Data.no;
                        SpData.PosX     = BGameMgr.Dantyou.Character.Pos.x - BGameMgr.Dantyou.Character.OPos.x;
                        SpData.PosY     = BGameMgr.Dantyou.Character.Pos.y - BGameMgr.Dantyou.Character.OPos.y;
                        SpData.PosZ     = BGameMgr.Dantyou.Character.Pos.z;
                        SpData.ScaleX   = SCALE10;
                        SpData.ScaleY   = SCALE10;
                        SpData.Rotate   = ROTATE000;
                        SpData.Reverse  = NOREVERS;
                        DrawSprite( &SpData );

                        if(--BGameMgr.Dantyou.DoorOpenTime < 0)
                        {//
                            BGameMgr.Dantyou.AppearMode=1;
                            BGameMgr.Dantyou.Character.Pos.x        = (320-128)/2;
                            BGameMgr.Dantyou.Character.Pos.y        = (240-128)/2 - 10;
                            BGameMgr.Dantyou.Character.Pos.z        = PRIORITY_GAME_EFFECT;
                            BGameMgr.Dantyou.Character.Anm.Data.no  = DantyouOpenningTalkAnmTable[BGameMgr.Dantyou.Character.Anm.Index].no;
                            BGameMgr.Dantyou.Character.Anm.Data.wt  = DantyouOpenningTalkAnmTable[BGameMgr.Dantyou.Character.Anm.Index].wt;
                        }
                        
                    }else
                    if(BGameMgr.Dantyou.AppearMode==1)
                    {//オープニングトーク
                        
                        
                        if(--BGameMgr.Dantyou.Character.Anm.Data.wt<0){
                            BGameMgr.Dantyou.Character.Anm.Index++;
                            BGameMgr.Dantyou.Character.Anm.Data.wt = DantyouOpenningTalkAnmTable[BGameMgr.Dantyou.Character.Anm.Index].wt;
                        }
                        
                        if(DantyouOpenningTalkAnmTable[BGameMgr.Dantyou.Character.Anm.Index].no != ANM_STOP)
                        {
                            BGameMgr.Dantyou.Character.Anm.Data.no = DantyouOpenningTalkAnmTable[BGameMgr.Dantyou.Character.Anm.Index].no;
                            
                            //団長描画
                            SpData.No       = BGameMgr.Dantyou.Character.Anm.Data.no;
                            SpData.PosX     = BGameMgr.Dantyou.Character.Pos.x;
                            SpData.PosY     = BGameMgr.Dantyou.Character.Pos.y;
                            SpData.PosZ     = BGameMgr.Dantyou.Character.Pos.z;
                            SpData.ScaleX   = SCALE10;
                            SpData.ScaleY   = SCALE10;
                            SpData.Rotate   = ROTATE000;
                            SpData.Reverse  = NOREVERS;
                            DrawSprite( &SpData );
                        }else
                        {
                            //[♪] BGMスタート
                            ssPlayBgm(BGMIndexTable[BGameMgr.BgmIndex]);
                            
                            //[♪] ドア閉まり
                            //ssPlaySe(BAND_SE_00);
                            
                            //スクリプトOFF
                            MetuseijiFlag=OFF;
                            
                            //団長初期化
                            BGameMgr.Dantyou.Status                 = DANTYOU_WAIT;
                            BGameMgr.Dantyou.Character.Anm.Data.no  = BAND_CHAR_GAME_DANTYOU_00;
                            BGameMgr.Dantyou.Character.Anm.Data.wt  = DANTYOU_ANM_WAIT_TIME;
                            BGameMgr.Dantyou.Character.Anm.Index    = 0;
                            BGameMgr.Dantyou.AnmBase                = 0;
                            
                            BGameMgr.Dantyou.Character.Pos.x        = MAP_LEFT_X + (SQUARE_W * (INIT_ARR_POSX-1))+SQUARE_W/2;
                            BGameMgr.Dantyou.Character.Pos.y        = MAP_LEFT_Y + (SQUARE_H * (INIT_ARR_POSY-1))+SQUARE_H/2;
                            BGameMgr.Dantyou.Character.Pos.z        = PRIORITY_GAME_DANTYOU;
                            BGameMgr.Dantyou.Character.OPos.x       = 18;
                            BGameMgr.Dantyou.Character.OPos.y       = 20;
                            BGameMgr.Dantyou.Index                  = START_POS_INDEX;
                            
                            for(i=0;i<POS_ARR_NUM;i++){
                                BGameMgr.Dantyou.Xarr[i] = BGameMgr.Dantyou.Character.Pos.x;
                                BGameMgr.Dantyou.Yarr[i] = BGameMgr.Dantyou.Character.Pos.y;
                            }
                            
                            BGameMgr.Dantyou.GetIndex               = 0;
                            BGameMgr.Dantyou.Px                     = INIT_ARR_POSX;
                            BGameMgr.Dantyou.Py                     = INIT_ARR_POSY;
                            BGameMgr.Dantyou.MoveX                  = 0;
                            BGameMgr.Dantyou.MoveY                  = 0;
                            BGameMgr.Dantyou.MoveCount              = 0;

                            //団員タスク
                            Task.func       = DaninTask;
                            Task.priority   = TASK_NO_GAME_DANIN;
                            Task.attribute  = ATTR_USER;
                            Task.status     = TASK_NEW_ENTRY;
                            Task.id         = TASK_NO_GAME_DANIN;
                            Task.wait_time  = 0;
                            Task.buf        = NULL;
                            Task.name       = "DaninTask";
                            Task.mode       = TASK_MODE_INIT;
                            CreateTask(&Task);
                            
                            //ポーズ監視タスク
                            Task.func       = PauseTask;
                            Task.priority   = TASK_NO_GAME_PAUSE;
                            Task.attribute  = ATTR_USER;
                            Task.status     = TASK_NEW_ENTRY;
                            Task.id         = TASK_NO_GAME_PAUSE;
                            Task.wait_time  = 0;
                            Task.buf        = NULL;
                            Task.name       = "PauseTask";
                            Task.mode       = TASK_MODE_INIT;
                            CreateTask(&Task);
                        }
                    }
                    
                    //----扉の開閉
                    if(--BGameMgr.Dantyou.DoorAnmWaitTimer < 0)
                    {
                        BGameMgr.Dantyou.DoorAnmIndex++;
                        BGameMgr.Dantyou.DoorAnmWaitTimer = DoorAnmTable[BGameMgr.Dantyou.DoorAnmIndex].wt;
                    }
                    
                    if(DoorAnmTable[BGameMgr.Dantyou.DoorAnmIndex].no != ANM_STOP)
                    {
                        BGameMgr.Dantyou.DoorAnmNo = DoorAnmTable[BGameMgr.Dantyou.DoorAnmIndex].no;
                    }else
                    {
                        
                    }
                    
                    //扉
                    SpData.No       = BGameMgr.Dantyou.DoorAnmNo;
                    SpData.PosX     = 136;
                    SpData.PosY     = 84;
                    SpData.PosZ     = PRIORITY_GAME_BG-7;
                    SpData.ScaleX   = SCALE10;
                    SpData.ScaleY   = SCALE10;
                    SpData.Rotate   = ROTATE000;
                    SpData.Reverse  = NOREVERS;
                    DrawSprite( &SpData );
                    
                    //扉背景
                    SpData.No       = BAND_CHAR_GAME_DOOR_03;
                    SpData.PosX     = 136;
                    SpData.PosY     = 84;
                    SpData.PosZ     = PRIORITY_GAME_BG-5;
                    SpData.ScaleX   = SCALE10;
                    SpData.ScaleY   = SCALE10;
                    SpData.Rotate   = ROTATE000;
                    SpData.Reverse  = NOREVERS;
                    DrawSprite( &SpData );
                    
                    break;
                case DANTYOU_WAIT:          //移動待ち
                    if( CheckKeyDir(&dir) )
                    {//方向キーが押された
                        switch( CheckCharacter(dir) )
                        {
                            case CHAR_NONE:     //何もないので移動
                                BGameMgr.Dantyou.Status = DANTYOU_WALK;
                                
                                if(dir==KEY_DIR_UP){
                                    if(--BGameMgr.Dantyou.Py < 1){
                                        BGameMgr.Dantyou.Py=1;
                                    }
                                    
                                    BGameMgr.Dantyou.MoveX      = 0;
                                    BGameMgr.Dantyou.MoveY      = -1;
                                    BGameMgr.Dantyou.MoveCount  = SQUARE_H;
                                    
                                    BGameMgr.Dantyou.AnmBase    = 4;
                                }else if(dir==KEY_DIR_DOWN){
                                    if(++BGameMgr.Dantyou.Py >= SQUARE_H_NUM+1){
                                        BGameMgr.Dantyou.Py=SQUARE_H_NUM-1+1;
                                    }
                                    
                                    BGameMgr.Dantyou.MoveX      = 0;
                                    BGameMgr.Dantyou.MoveY      = 1;
                                    BGameMgr.Dantyou.MoveCount  = SQUARE_H;
                                    
                                    BGameMgr.Dantyou.AnmBase    = 0;
                                }else if(dir==KEY_DIR_LEFT){
                                    if(--BGameMgr.Dantyou.Px < 1){
                                        BGameMgr.Dantyou.Px=1;
                                    }
                                    
                                    BGameMgr.Dantyou.MoveX      = -1;
                                    BGameMgr.Dantyou.MoveY      = 0;
                                    BGameMgr.Dantyou.MoveCount  = SQUARE_W;
                                    
                                    BGameMgr.Dantyou.AnmBase    = 6;
                                }else if(dir==KEY_DIR_RIGHT){
                                    if(++BGameMgr.Dantyou.Px>=SQUARE_W_NUM+1){
                                        BGameMgr.Dantyou.Px=SQUARE_W_NUM-1+1;
                                    }
                                    
                                    BGameMgr.Dantyou.MoveX      = 1;
                                    BGameMgr.Dantyou.MoveY      = 0;
                                    BGameMgr.Dantyou.MoveCount  = SQUARE_W;
                                    
                                    BGameMgr.Dantyou.AnmBase    = 2;
                                }else{
                                    BGameMgr.Dantyou.MoveX      = 0;
                                    BGameMgr.Dantyou.MoveY      = 0;
                                }
                                break;
                            case CHAR_WALL:     //wall
                                //なにもしない
                                BGameMgr.Dantyou.MoveX=0;
                                BGameMgr.Dantyou.MoveY=0;
                                break;
                            case CHAR_DANIN:    //Danin
                                if(CheckDanin(dir))
                                {//捕まえる
                                    GameMgr.WaitFlag = ON;          // iwasawa Correction (2003/4/27)
                                    BGameMgr.Dantyou.Status = DANTYOU_CATCH_WALK;
                                    
                                    
                                    if(++BGameMgr.GetNum>DANIN_NUM){
                                        BGameMgr.GetNum = DANIN_NUM;
                                    }
                                    
                                    if(dir==KEY_DIR_UP){
                                        if(--BGameMgr.Dantyou.Py < 1){
                                            BGameMgr.Dantyou.Py=1;
                                        }
                                        
                                        BGameMgr.Dantyou.MoveX      = 0;
                                        BGameMgr.Dantyou.MoveY      = -1;
                                        BGameMgr.Dantyou.MoveCount  = SQUARE_H;
                                        
                                        BGameMgr.Dantyou.AnmBase    = 4;
                                    }else if(dir==KEY_DIR_DOWN){
                                        if(++BGameMgr.Dantyou.Py >= SQUARE_H_NUM+1){
                                            BGameMgr.Dantyou.Py=SQUARE_H_NUM-1+1;
                                        }
                                        
                                        BGameMgr.Dantyou.MoveX      = 0;
                                        BGameMgr.Dantyou.MoveY      = 1;
                                        BGameMgr.Dantyou.MoveCount  = SQUARE_H;
                                        
                                        BGameMgr.Dantyou.AnmBase    = 0;
                                    }else if(dir==KEY_DIR_LEFT){
                                        if(--BGameMgr.Dantyou.Px < 1){
                                            BGameMgr.Dantyou.Px=1;
                                        }
                                        
                                        BGameMgr.Dantyou.MoveX      = -1;
                                        BGameMgr.Dantyou.MoveY      = 0;
                                        BGameMgr.Dantyou.MoveCount  = SQUARE_W;
                                        
                                        BGameMgr.Dantyou.AnmBase    = 6;
                                    }else if(dir==KEY_DIR_RIGHT){
                                        if(++BGameMgr.Dantyou.Px>=SQUARE_W_NUM+1){
                                            BGameMgr.Dantyou.Px=SQUARE_W_NUM-1+1;
                                        }
                                        
                                        BGameMgr.Dantyou.MoveX      = 1;
                                        BGameMgr.Dantyou.MoveY      = 0;
                                        BGameMgr.Dantyou.MoveCount  = SQUARE_W;
                                        
                                        BGameMgr.Dantyou.AnmBase    = 2;
                                    }else{
                                        BGameMgr.Dantyou.MoveX      = 0;
                                        BGameMgr.Dantyou.MoveY      = 0;
                                    }
                                }else
                                {//
                                    BGameMgr.Dantyou.Status = DANTYOU_WAIT;
                                }
                                break;
                            default:
                                break;
                            }
                    }else
                    {//押されていない
                        
                    }
                    
                    break;
                case DANTYOU_WALK:          //移動中
                    
                    BGameMgr.Dantyou.Character.Pos.x+=BGameMgr.Dantyou.MoveX;
                    BGameMgr.Dantyou.Character.Pos.y+=BGameMgr.Dantyou.MoveY;
                    BGameMgr.Dantyou.Xarr[BGameMgr.Dantyou.Index%POS_ARR_NUM] = BGameMgr.Dantyou.Character.Pos.x;
                    BGameMgr.Dantyou.Yarr[BGameMgr.Dantyou.Index%POS_ARR_NUM] = BGameMgr.Dantyou.Character.Pos.y;
                    BGameMgr.Dantyou.Index++;
                    
                    if(--BGameMgr.Dantyou.MoveCount <= 0)
                    {//移動終了なら待ちへ
                        BGameMgr.Dantyou.Status = DANTYOU_WAIT;
                    }
                    
                    break;
                case DANTYOU_CATCH_WALK:    //勧誘移動
                    BGameMgr.Dantyou.Character.Pos.x+=BGameMgr.Dantyou.MoveX;
                    BGameMgr.Dantyou.Character.Pos.y+=BGameMgr.Dantyou.MoveY;
                    BGameMgr.Dantyou.Xarr[BGameMgr.Dantyou.Index%POS_ARR_NUM] = BGameMgr.Dantyou.Character.Pos.x;
                    BGameMgr.Dantyou.Yarr[BGameMgr.Dantyou.Index%POS_ARR_NUM] = BGameMgr.Dantyou.Character.Pos.y;
                    BGameMgr.Dantyou.Index++;
                    
                    if(--BGameMgr.Dantyou.MoveCount <= 0)
                    {//勧誘移動終了なら
                        //団長ステータス変更：勧誘する
                        BGameMgr.Dantyou.Status = DANTYOU_CATCH;
                        
                        //勧誘した
                        BGameMgr.Danin[BGameMgr.Dantyou.GetIndex].Status=DANIN_CATCH_WALK;
                        
                        //マップクリア
                        BGameMgr.Map.Data[BGameMgr.Danin[BGameMgr.Dantyou.GetIndex].Py][BGameMgr.Danin[BGameMgr.Dantyou.GetIndex].Px]=0;
                        
                        //次の団員番号
                        if( ++BGameMgr.Dantyou.GetIndex > DANIN_NUM-1) BGameMgr.Dantyou.GetIndex=DANIN_NUM-1;
                    }
                    break;
                case DANTYOU_CATCH: //勧誘
                    //団員の移動待ち、終了したら団員の方がステータスを変更します
                    
                    
                    break;
                case DANTYOU_CATCH_WAIT:    //勧誘待ち
                    //勧誘終了へ
                    BGameMgr.Dantyou.Status = DANTYOU_CATCH_END;
                    
                    
                    //人数分の楽器の音がなります。鳴り終わるまでここで待ち。
                    
                    
                    
                    break;
                case DANTYOU_CATCH_END:     //勧誘終了
                    //団長ステータス変更
                    BGameMgr.Dantyou.Status = DANTYOU_CATCH_END_WAIT;
                    
                    //[♪] ドレミファソラ
                    dsPlayXa(XA_FILE_BAND04,XaCatchWaitTable[BGameMgr.BgmIndex]);
                    
                    //[♪] BGMストップ
                    ssStopBgm(BGMIndexTable[BGameMgr.BgmIndex]);
                    //次
                    if(++BGameMgr.BgmIndex >= MAX_BGM_NUM){
                        BGameMgr.BgmIndex = MAX_BGM_NUM-1;
                    }
                    
                    //[♪] ピンポーン
                    ssPlaySe(BAND_SE_02);
                    
                    break;
                case DANTYOU_CATCH_END_WAIT:
                    //XA再生のが終了まで待つ
                //  if(){
                        //勧誘終了へ
                        if(BGameMgr.GetNum==DANIN_NUM)
                        {//整列処理へ
                            //団長ステータス変更
                            BGameMgr.Dantyou.Status = DANTYOU_ALIGNMENT;
                            
                            //サブモード　初期化へ
                            BGameMgr.Dantyou.Mode   = MODE_ALIGNMENT_00;
                        }else
                        {//まだまだ探しますよ
                            GameMgr.WaitFlag = OFF;         // iwasawa Correction (2003/4/27)
                            //[♪] BGMスタート
                            ssPlayBgm(BGMIndexTable[BGameMgr.BgmIndex]);
                            
                            //団長ステータス変更
                            BGameMgr.Dantyou.Status = DANTYOU_WAIT;
                        }
                //  }
                    
                    break;
                case DANTYOU_ALIGNMENT:     //整列処理
                    
//                  FntPrint("STAT=DANTYOU_ALIGNMENT\n");
//                  FntPrint("MODE=%d / ",      BGameMgr.Dantyou.Mode);
//                  FntPrint("AREA=%d\n",       BGameMgr.Dantyou.ClearArea);
//                  FntPrint("PX/PY=%d/%d\n",   BGameMgr.Dantyou.Px,BGameMgr.Dantyou.Py);
//                  FntPrint("AlignmentMoveArr[0]:%d\n",BGameMgr.Dantyou.AlignmentMoveArr[0]);
//                  FntPrint("AlignmentMoveArr[1]:%d\n",BGameMgr.Dantyou.AlignmentMoveArr[1]);
//                  FntPrint("AlignmentMoveArr[2]:%d\n",BGameMgr.Dantyou.AlignmentMoveArr[2]);
//                  FntPrint("AlignmentMoveArr[3]:%d\n",BGameMgr.Dantyou.AlignmentMoveArr[3]);
                    
                    
                    switch(BGameMgr.Dantyou.Mode)
                    {
                        case MODE_ALIGNMENT_00:     //初期化
                            //初期化
                            for(i=0;i<4;i++){
                                BGameMgr.Dantyou.AlignmentMoveArr[i] = 0;
                            }
                            
                            //クリア時のエリアを取得
                            BGameMgr.Dantyou.ClearArea  = GetMapPos(BGameMgr.Dantyou.Px,BGameMgr.Dantyou.Py);
                            
                            //次の整列のための移動位置を取得
                            BGameMgr.Dantyou.AlignmentMoveArr[0]    = ClearAlignmenTable[BGameMgr.Dantyou.ClearArea+NEXT_1].Px - BGameMgr.Dantyou.Px;
                            BGameMgr.Dantyou.AlignmentMoveArr[1]    = ClearAlignmenTable[BGameMgr.Dantyou.ClearArea+NEXT_1].Py - BGameMgr.Dantyou.Py;
                            BGameMgr.Dantyou.AlignmentMoveArr[2]    = ClearAlignmenTable[BGameMgr.Dantyou.ClearArea+NEXT_2].Px - ClearAlignmenTable[BGameMgr.Dantyou.ClearArea+NEXT_1].Px;
                            BGameMgr.Dantyou.AlignmentMoveArr[3]    = ClearAlignmenTable[BGameMgr.Dantyou.ClearArea+NEXT_2].Py - ClearAlignmenTable[BGameMgr.Dantyou.ClearArea+NEXT_1].Py;
                            
                            //縦移動方向
                            if(BGameMgr.Dantyou.AlignmentMoveArr[1] < 0){
                                BGameMgr.Dantyou.MoveY      = -1;   //上
                                BGameMgr.Dantyou.AnmBase    =  0;
                            }else{
                                BGameMgr.Dantyou.MoveY      =  1;   //下
                                BGameMgr.Dantyou.AnmBase    =  4;
                            }
                            
                            //横移動方向
                            BGameMgr.Dantyou.MoveX  = 0;
                            
                            //移動カウント
                            BGameMgr.Dantyou.MoveCount = ABS(BGameMgr.Dantyou.AlignmentMoveArr[1])*SQUARE_H;
                            
                            //モード：最初の縦移動へ
                            BGameMgr.Dantyou.Mode       = MODE_ALIGNMENT_01;
                            
                            break;
                        case MODE_ALIGNMENT_01:     //NEXT1-縦
                            
                            //移動
                            BGameMgr.Dantyou.Character.Pos.x+=BGameMgr.Dantyou.MoveX;
                            BGameMgr.Dantyou.Character.Pos.y+=BGameMgr.Dantyou.MoveY;
                            BGameMgr.Dantyou.Xarr[BGameMgr.Dantyou.Index%POS_ARR_NUM] = BGameMgr.Dantyou.Character.Pos.x;
                            BGameMgr.Dantyou.Yarr[BGameMgr.Dantyou.Index%POS_ARR_NUM] = BGameMgr.Dantyou.Character.Pos.y;
                            BGameMgr.Dantyou.Index++;
                            
                            //横の移動
                            if(--BGameMgr.Dantyou.MoveCount <= 0)
                            {//移動終了
                                //モード変更
                                BGameMgr.Dantyou.Mode = MODE_ALIGNMENT_02;
                                
                                //横移動方向
                                if(BGameMgr.Dantyou.AlignmentMoveArr[0] < 0){
                                    BGameMgr.Dantyou.MoveX      = -1;   //左
                                    BGameMgr.Dantyou.AnmBase    =  6;
                                    
                                }else{
                                    BGameMgr.Dantyou.MoveX      =  1;   //右
                                    BGameMgr.Dantyou.AnmBase    =  2;
                                }
                                
                                //縦は移動しない
                                BGameMgr.Dantyou.MoveY = 0;
                                
                                //次のモードの移動カウント
                                BGameMgr.Dantyou.MoveCount=ABS(BGameMgr.Dantyou.AlignmentMoveArr[0])*SQUARE_W;
                                
                            }else
                            {
                                
                            }
                            break;
                        case MODE_ALIGNMENT_02:     //NEXT1-横
                            //移動
                            BGameMgr.Dantyou.Character.Pos.x+=BGameMgr.Dantyou.MoveX;
                            BGameMgr.Dantyou.Character.Pos.y+=BGameMgr.Dantyou.MoveY;
                            BGameMgr.Dantyou.Xarr[BGameMgr.Dantyou.Index%POS_ARR_NUM] = BGameMgr.Dantyou.Character.Pos.x;
                            BGameMgr.Dantyou.Yarr[BGameMgr.Dantyou.Index%POS_ARR_NUM] = BGameMgr.Dantyou.Character.Pos.y;
                            BGameMgr.Dantyou.Index++;
                            
                            //横の移動
                            if(--BGameMgr.Dantyou.MoveCount <= 0)
                            {//移動終了
                                //モード変更
                                BGameMgr.Dantyou.Mode = MODE_ALIGNMENT_03;
                                
                                //横移動方向
                                if(BGameMgr.Dantyou.AlignmentMoveArr[2] < 0){
                                    BGameMgr.Dantyou.MoveX      = -1;   //左
                                    BGameMgr.Dantyou.AnmBase    =  6;
                                }else{
                                    BGameMgr.Dantyou.MoveX      =  1;   //右
                                    BGameMgr.Dantyou.AnmBase    =  2;
                                }
                                
                                //縦は移動しない
                                BGameMgr.Dantyou.MoveY = 0;
                                
                                //次のモードの移動カウント
                                BGameMgr.Dantyou.MoveCount=ABS(BGameMgr.Dantyou.AlignmentMoveArr[2])*SQUARE_W;
                                
                            }else
                            {
                                
                            }
                            
                            break;
                        case MODE_ALIGNMENT_03:     //NEXT2-横
                            //移動
                            BGameMgr.Dantyou.Character.Pos.x+=BGameMgr.Dantyou.MoveX;
                            BGameMgr.Dantyou.Character.Pos.y+=BGameMgr.Dantyou.MoveY;
                            BGameMgr.Dantyou.Xarr[BGameMgr.Dantyou.Index%POS_ARR_NUM] = BGameMgr.Dantyou.Character.Pos.x;
                            BGameMgr.Dantyou.Yarr[BGameMgr.Dantyou.Index%POS_ARR_NUM] = BGameMgr.Dantyou.Character.Pos.y;
                            BGameMgr.Dantyou.Index++;
                            
                            //横の移動
                            if(--BGameMgr.Dantyou.MoveCount <= 0)
                            {//移動終了
                                //モード変更
                                BGameMgr.Dantyou.Mode = MODE_ALIGNMENT_04;
                            }else
                            {
                                
                            }
                            
                            break;
                        case MODE_ALIGNMENT_04:     //終了
                            //整列終了後クリアへ
                            //団長ステータス変更
                            BGameMgr.Dantyou.Status = DANTYOU_CLEAR;
                            
                            //[♪] 面クリアファンファーレ / FAN2.XA
                            dsPlayXa(XA_FILE_BAND04,6);
                            
                            break;
                        default:
                    }
                    
                    break;
                case DANTYOU_CLEAR:         //クリア
                    if(--BGameMgr.Dantyou.ClearWaitTimer < 0)
                    {
                        //本来はセリフの音声再生、整列処理
                        //クリアフラグセット
                        BGameMgr.ClearFlag=1;
                        
                        //団長ステータス変更
                        BGameMgr.Dantyou.Status = DANTYOU_CLEAR_END;
                        
                        //ポーズタスク削除
                        RemoveTask(TASK_NO_GAME_PAUSE);
                        
                        //レベルアップ
                        if(++BGameMgr.PlayLevel>BAND_GAME_MAX_LEVEL_NUM-1){
                            BGameMgr.PlayLevel=BAND_GAME_MAX_LEVEL_NUM-1;
                            
                            //オールクリアフラグセット
                            BGameMgr.AllClearFlag   = 1;
                        }
                        
                        //
                        if(BGameMgr.PlayLevel>BGameMgr.Level)
                        {//前回のレベルより高い場合は書き換える
                            BGameMgr.Level=BGameMgr.PlayLevel;
                        }
                    }
                    break;
                case DANTYOU_CLEAR_END:
                    
                    
                    break;
                default:
            }
            
            
            if(BGameMgr.Dantyou.Status!=DANTYOU_APPEAR)
            {//出現時以外は処理
                //----アニメ
                if(++BGameMgr.Dantyou.Character.Anm.Data.wt>DANTYOU_ANM_WAIT_TIME)
                {
                    BGameMgr.Dantyou.Character.Anm.Index^=1;
                    BGameMgr.Dantyou.Character.Anm.Data.wt = 0;
                }
                BGameMgr.Dantyou.Character.Anm.Data.no = DantyouAnmTable[BGameMgr.Dantyou.AnmBase + BGameMgr.Dantyou.Character.Anm.Index];
                
                //----団長描画
                SpData.No       = BGameMgr.Dantyou.Character.Anm.Data.no;
                SpData.PosX     = BGameMgr.Dantyou.Character.Pos.x - BGameMgr.Dantyou.Character.OPos.x;
                SpData.PosY     = BGameMgr.Dantyou.Character.Pos.y - BGameMgr.Dantyou.Character.OPos.y;
                SpData.PosZ     = BGameMgr.Dantyou.Character.Pos.z;
                SpData.ScaleX   = SCALE10;
                SpData.ScaleY   = SCALE10;
                SpData.Rotate   = ROTATE000;
                SpData.Reverse  = NOREVERS;
                DrawSprite( &SpData );
            }
            
            break;
        case TASK_MODE_EXIT:
            
            //自分を削除
            ExitTask(ip_task->id);
            break;
        default:
    }

    return TRUE;
}


//-----------------------------------------------------------------------------
//  関数名 :DaninTask
//  機能   :団員のタスク
//  注意   :なし
//-----------------------------------------------------------------------------
int DaninTask(TASK* ip_task)
{
    static int RandPtn;
    SPRITE_DATA SpData;
    int i,r1,r2;
    int j,k;

    static ANMDATA DaninAppearAnmTable[]={
        {   BAND_CHAR_GAME_SMOKE_00,    12  },
        {   BAND_CHAR_GAME_SMOKE_01,    12  },
        {   BAND_CHAR_GAME_SMOKE_00,    12  },
        {   BAND_CHAR_GAME_SMOKE_01,    12  },
        {   ANM_STOP,0},
    };


    static int DaninAnmTable[][7][2]={
        {
            BAND_CHAR_GAME_DANIN_A_00,BAND_CHAR_GAME_DANIN_A_01,    //マラカス          0
            BAND_CHAR_GAME_DANIN_B_00,BAND_CHAR_GAME_DANIN_B_01,    //ボーン            2
            BAND_CHAR_GAME_DANIN_C_00,BAND_CHAR_GAME_DANIN_C_01,    //トライアングル    4
            BAND_CHAR_GAME_DANIN_D_00,BAND_CHAR_GAME_DANIN_D_01,    //ハンドベル        6
            BAND_CHAR_GAME_DANIN_E_00,BAND_CHAR_GAME_DANIN_E_01,    //タイコ            8
            BAND_CHAR_GAME_DANIN_F_00,BAND_CHAR_GAME_DANIN_F_01,    //タンバリン        10
            BAND_CHAR_GAME_DANIN_G_00,BAND_CHAR_GAME_DANIN_G_01,    //ボウ              12
        },
        {
            BAND_CHAR_GAME_DANIN_A_00,BAND_CHAR_GAME_DANIN_A_01,    //マラカス          0
            BAND_CHAR_GAME_DANIN_F_00,BAND_CHAR_GAME_DANIN_F_01,    //タンバリン        10
            BAND_CHAR_GAME_DANIN_D_00,BAND_CHAR_GAME_DANIN_D_01,    //ハンドベル        6
            BAND_CHAR_GAME_DANIN_B_00,BAND_CHAR_GAME_DANIN_B_01,    //ボーン            2
            BAND_CHAR_GAME_DANIN_G_00,BAND_CHAR_GAME_DANIN_G_01,    //ボウ              12
            BAND_CHAR_GAME_DANIN_C_00,BAND_CHAR_GAME_DANIN_C_01,    //トライアングル    4
            BAND_CHAR_GAME_DANIN_E_00,BAND_CHAR_GAME_DANIN_E_01,    //タイコ            8
        },
        {
            BAND_CHAR_GAME_DANIN_C_00,BAND_CHAR_GAME_DANIN_C_01,    //トライアングル    4
            BAND_CHAR_GAME_DANIN_A_00,BAND_CHAR_GAME_DANIN_A_01,    //マラカス          0
            BAND_CHAR_GAME_DANIN_F_00,BAND_CHAR_GAME_DANIN_F_01,    //タンバリン        10
            BAND_CHAR_GAME_DANIN_B_00,BAND_CHAR_GAME_DANIN_B_01,    //ボーン            2
            BAND_CHAR_GAME_DANIN_E_00,BAND_CHAR_GAME_DANIN_E_01,    //タイコ            8
            BAND_CHAR_GAME_DANIN_D_00,BAND_CHAR_GAME_DANIN_D_01,    //ハンドベル        6
            BAND_CHAR_GAME_DANIN_G_00,BAND_CHAR_GAME_DANIN_G_01,    //ボウ              12
        },
        {
            BAND_CHAR_GAME_DANIN_F_00,BAND_CHAR_GAME_DANIN_F_01,    //タンバリン        10
            BAND_CHAR_GAME_DANIN_A_00,BAND_CHAR_GAME_DANIN_A_01,    //マラカス          0
            BAND_CHAR_GAME_DANIN_B_00,BAND_CHAR_GAME_DANIN_B_01,    //ボーン            2
            BAND_CHAR_GAME_DANIN_D_00,BAND_CHAR_GAME_DANIN_D_01,    //ハンドベル        6
            BAND_CHAR_GAME_DANIN_G_00,BAND_CHAR_GAME_DANIN_G_01,    //ボウ              12
            BAND_CHAR_GAME_DANIN_C_00,BAND_CHAR_GAME_DANIN_C_01,    //トライアングル    4
            BAND_CHAR_GAME_DANIN_E_00,BAND_CHAR_GAME_DANIN_E_01,    //タイコ            8
        },
        {
            BAND_CHAR_GAME_DANIN_G_00,BAND_CHAR_GAME_DANIN_G_01,    //ボウ              12
            BAND_CHAR_GAME_DANIN_B_00,BAND_CHAR_GAME_DANIN_B_01,    //ボーン            2
            BAND_CHAR_GAME_DANIN_E_00,BAND_CHAR_GAME_DANIN_E_01,    //タイコ            8
            BAND_CHAR_GAME_DANIN_C_00,BAND_CHAR_GAME_DANIN_C_01,    //トライアングル    4
            BAND_CHAR_GAME_DANIN_A_00,BAND_CHAR_GAME_DANIN_A_01,    //マラカス          0
            BAND_CHAR_GAME_DANIN_F_00,BAND_CHAR_GAME_DANIN_F_01,    //タンバリン        10
            BAND_CHAR_GAME_DANIN_D_00,BAND_CHAR_GAME_DANIN_D_01,    //ハンドベル        6
        },
    };


    switch(ip_task->mode)
    {
        case TASK_MODE_INIT:
            //next main
            ip_task->mode = TASK_MODE_MAIN;

            //問題インデックス設定
            BGameMgr.ProblemIndex                       = (rand()%10) + BGameMgr.PlayLevel*10;

            //団員初期化
            for(i=0;i<DANIN_NUM;i++)
            {
                BGameMgr.Danin[i].Character.Anm.Index   = 0;
                BGameMgr.Danin[i].Character.Anm.Data.no = DaninAppearAnmTable[0].no;
                BGameMgr.Danin[i].Character.Anm.Data.wt = DaninAppearAnmTable[0].wt;
                BGameMgr.Danin[i].AnmBase               = i*2;
                BGameMgr.Danin[i].AppearTimer           = 0;

                BGameMgr.Danin[i].Index                 = DANIN_REFRANCE_INDEX*(1+i);
                BGameMgr.Danin[i].EntryIndex            = i;                                                //処理番号
                BGameMgr.Danin[i].No                    = BandProblemTable[BGameMgr.ProblemIndex][i].No;    //表示番号
                BGameMgr.Danin[i].Px                    = BandProblemTable[BGameMgr.ProblemIndex][i].PosX;  //配置X
                BGameMgr.Danin[i].Py                    = BandProblemTable[BGameMgr.ProblemIndex][i].PosY;  //配置Y
                BGameMgr.Danin[i].CatchMoveIndex        = 0;
                BGameMgr.Danin[i].Status                = DANIN_CATCH_APPEAR;

                BGameMgr.Danin[i].Character.OPos.x      = 15;
                BGameMgr.Danin[i].Character.OPos.y      = 20;
                BGameMgr.Danin[i].Character.Pos.x       = (MAP_LEFT_X + (SQUARE_W * (BGameMgr.Danin[i].Px))+SQUARE_W/2)-SQUARE_W;
                BGameMgr.Danin[i].Character.Pos.y       = (MAP_LEFT_Y + (SQUARE_H * (BGameMgr.Danin[i].Py))+SQUARE_H/2)-SQUARE_H;
                BGameMgr.Danin[i].Character.Pos.z       = PRIORITY_GAME_DANIN+5*i;

                //Mapset
                BGameMgr.Map.Data[BGameMgr.Danin[i].Py][BGameMgr.Danin[i].Px]=CHAR_DANIN;
            }

            //パターンランダム初期化
            RandPtn=rand()%5;
            
            break;
        case TASK_MODE_MAIN:
            for(i=0;i<DANIN_NUM;i++)
            {
                switch(BGameMgr.Danin[i].Status)
                {
                    case DANIN_CATCH_APPEAR:    //出現
                        
                        if(--BGameMgr.Danin[i].Character.Anm.Data.wt<0)
                        {
                            BGameMgr.Danin[i].Character.Anm.Index++;
                            BGameMgr.Danin[i].Character.Anm.Data.wt = DaninAppearAnmTable[BGameMgr.Danin[i].Character.Anm.Index].wt;
                        }
                        
                        if(DaninAppearAnmTable[BGameMgr.Danin[i].Character.Anm.Index].no!=ANM_STOP)
                        {//出現アニメ中
                            //set
                            BGameMgr.Danin[i].Character.Anm.Data.no = DaninAppearAnmTable[BGameMgr.Danin[i].Character.Anm.Index].no;
                        }else
                        {//停止→団長待ちへ
                            //出現後セット
                            BGameMgr.Danin[i].Character.Anm.Data.no = i*2;
                            BGameMgr.Danin[i].Character.Anm.Data.wt = 0;
                            BGameMgr.Danin[i].Character.Anm.Index   = 0;
                            //BGameMgr.Danin[i].AnmBase             = i*2;
                            BGameMgr.Danin[i].Status                = DANIN_CATCH_WAIT;
                            
                            BGameMgr.Danin[i].Character.OPos.x      = 19;
                            BGameMgr.Danin[i].Character.OPos.y      = 15;
                        }
                        
                        break;
                    case DANIN_CATCH_WAIT:      //団長待ち
                        
                        break;
                    case DANIN_CATCH_WALK:      //勧誘されて後ろに移動
                        
                        BGameMgr.Danin[i].Character.Pos.x   = BGameMgr.Dantyou.Xarr[((BGameMgr.Dantyou.Index - 1 - BGameMgr.Danin[i].CatchMoveIndex) % POS_ARR_NUM)];
                        BGameMgr.Danin[i].Character.Pos.y   = BGameMgr.Dantyou.Yarr[((BGameMgr.Dantyou.Index - 1 - BGameMgr.Danin[i].CatchMoveIndex) % POS_ARR_NUM)];
                        
                        if(++BGameMgr.Danin[i].CatchMoveIndex == DANIN_REFRANCE_INDEX*(1+i) )
                        {
                            //ステータス変更
                            BGameMgr.Danin[i].Status=DANIN_WALK;
                            
                            //団長のステータスを勧誘待ちへ
                            BGameMgr.Dantyou.Status = DANTYOU_CATCH_WAIT;
                        }

                        break;
                    case DANIN_WALK:            //勧誘されて一緒に歩く
                        
                        BGameMgr.Danin[i].Character.Pos.x   = BGameMgr.Dantyou.Xarr[(BGameMgr.Dantyou.Index - BGameMgr.Danin[i].Index) % POS_ARR_NUM];
                        BGameMgr.Danin[i].Character.Pos.y   = BGameMgr.Dantyou.Yarr[(BGameMgr.Dantyou.Index - BGameMgr.Danin[i].Index) % POS_ARR_NUM];
                        break;
                    case DANIN_CLEAR:
                        break;
                    default:
                        break;
                }

                if(BGameMgr.Danin[i].Status != DANIN_CATCH_APPEAR)
                {//出現時は別処理
                    //----アニメ
                    if(++BGameMgr.Danin[i].Character.Anm.Data.wt>DANIN_ANM_WAIT_TIME)
                    {
                        BGameMgr.Danin[i].Character.Anm.Index^=1;
                        BGameMgr.Danin[i].Character.Anm.Data.wt = 0;
                    }
                    BGameMgr.Danin[i].Character.Anm.Data.no = DaninAnmTable[RandPtn][i][BGameMgr.Danin[i].Character.Anm.Index];
                }

                //----団員描画
                SpData.No       = BGameMgr.Danin[i].Character.Anm.Data.no;
                SpData.PosX     = BGameMgr.Danin[i].Character.Pos.x - BGameMgr.Danin[i].Character.OPos.x;
                SpData.PosY     = BGameMgr.Danin[i].Character.Pos.y - BGameMgr.Danin[i].Character.OPos.y;
                SpData.PosZ     = BGameMgr.Danin[i].Character.Pos.z;
                SpData.ScaleX   = SCALE10;
                SpData.ScaleY   = SCALE10;
                SpData.Rotate   = ROTATE000;
                SpData.Reverse  = NOREVERS;
                DrawSprite( &SpData );

                if(BGameMgr.Danin[i].Status != DANIN_CATCH_APPEAR)
                {//出現時は表示しません
                    //----団員番号描画
                    DrawDaninNo(BGameMgr.Danin[i].No,
                            5,
                            DaninNoTable,
                            BGameMgr.Danin[i].Character.Pos.x - 9,
                            BGameMgr.Danin[i].Character.Pos.y - 4,
                            BGameMgr.Danin[i].Character.Pos.z-1);
                }
            }
            
            break;
        case TASK_MODE_EXIT:
            //自分を削除
            ExitTask(ip_task->id);
            break;
    }

    return TRUE;
}

//-----------------------------------------------------------------------------
//  関数名 :BgTask
//  機能   :背景タスク
//  注意   :なし
//-----------------------------------------------------------------------------
static int GameBgTask(TASK* ip_task)
{
    SPRITE_DATA SpData;

    switch(ip_task->mode)
    {
        case TASK_MODE_INIT:
            //next main
            ip_task->mode = TASK_MODE_MAIN;
            break;
            
        case TASK_MODE_MAIN:
            
            //扉
            SpData.No       = BAND_CHAR_GAME_DOOR_00;
            SpData.PosX     = 136;
            SpData.PosY     = 84;
            SpData.PosZ     = PRIORITY_GAME_BG-1;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );

            //背景←
            SpData.No       = BAND_CHAR_GAME_BG_00;
            SpData.PosX     = 0;
            SpData.PosY     = 0;
            SpData.PosZ     = PRIORITY_GAME_BG;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );
            
            //背景→
            SpData.No       = BAND_CHAR_GAME_BG_01;
            SpData.PosX     = 256;
            SpData.PosY     = 0;
            SpData.PosZ     = PRIORITY_GAME_BG;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );
            
            break;
        case TASK_MODE_EXIT:
            //自分を削除
            ExitTask(ip_task->id);
            break;
        default:
    }

    return TRUE;
}


//-----------------------------------------------------------------------------
//  関数名 :SelectLevelTask
//  機能   :レベルセレクトタスク
//  注意   :なし
//-----------------------------------------------------------------------------
static int SelectLevelTask(TASK* ip_task)
{
    static int SelectLevelDantyouAnmTable[]={
        BAND_CHAR_GAME_DANTYOU_BIG_00,
        BAND_CHAR_GAME_DANTYOU_BIG_01,
    };


    SPRITE_DATA SpData;
    TASK Task;
    int i,j;

    switch(ip_task->mode)
    {
        case TASK_MODE_INIT:
            SpraitCharSet(&GaidoLevelSpControl00[0], NULL);     // iwasawa Correction (2003/4/27)
            //next MAIN
            ip_task->mode       = TASK_MODE_MAIN;
            
            //----texture read sram -> vram
            if((file_read(BandGameTextureFile[0].fn,LoadAddress)) == -1)
            {//read error
                return FALSE;
            }
            
            //----texture init
            TexInit( BAND_GAME_TIM_NUM, &BandGameTextureImage[BAND_GAME_TIM_POS] );
            TimImgData = BandGameTextureImage;

            //----継続プレイフラグOFF
            BGameMgr.ContinueFlag   = 0;

            // フェードINます
            GameMgr.FadeFlag    = FadeIn;
            
            //----ゲーム用スプライト登録
            EntrySprite( BandGameSpriteData );
            
            //----プレイレベルクリア
            BGameMgr.PlayLevel  = 0;
            
            //----レベルセレクトワーク初期化
            BGameMgr.SelectLevel.DantyouNo          = 0;
            BGameMgr.SelectLevel.DantyouWt          = 0;
            BGameMgr.SelectLevel.DantyouIndex       = 0;
            BGameMgr.SelectLevel.Mode               = SELECT_LEVEL_MODE_00;
            BGameMgr.SelectLevel.Timer              = 0;
            BGameMgr.SelectLevel.BlockNo            = 0;
            BGameMgr.SelectLevel.BlockWt            = 0;
            BGameMgr.SelectLevel.KeteiWt            = 0;
            BGameMgr.SelectLevel.KeteiFlushIndex    = 0;
            BGameMgr.SelectLevel.KeteiFlushWt       = 0;
            BGameMgr.SelectLevel.WaitFlag           = 0;
//          ip_task->user[0]                        = 0;                        //Flag
//          ip_task->user[1]                        = GET_DA_STATUS_WAIT_TIME;  //timer
            
            //スクリプト
            BGameMgr.Script.Flag=1;
            Task.func           = ScriptTask;
            Task.priority       = TASK_NO_GAME_SCRIPT;
            Task.attribute      = ATTR_USER;
            Task.status         = TASK_NEW_ENTRY;
            Task.id             = TASK_NO_GAME_SCRIPT;
            Task.wait_time      = 0;
            Task.buf            = NULL;
            Task.name           = "ScriptTask";
            Task.mode           = TASK_MODE_INIT;
            Task.user[0]        = SCRIPT_LINE_1;
            Task.user[1]        = DANTYOU_SELECT_LEVEL_SCRIPT_BASE;
            Task.user[2]        = DANTYOU_SELECT_LEVEL_SCRIPT_NUM;
            CreateTask(&Task);

            break;
        case TASK_MODE_MAIN:
            SsinScriptFlag = BGameMgr.Script.Flag;          // iwasawa Correction (2003/4/27)
        //  FntPrint("SELECT LEVEL=%d\n", BGameMgr.PlayLevel);
        
            //----選択可能レベルをプレートのアニメで表現する
            switch(BGameMgr.SelectLevel.Mode)
            {
                case SELECT_LEVEL_MODE_00:  //選択可能なレベルまで明るく
            //      ++BGameMgr.SelectLevel.Timer;
            //      if(BGameMgr.SelectLevel.Timer > EVENT_SELECT_LEVEL_MODE_00_TIME){
            //          BGameMgr.SelectLevel.Mode = SELECT_LEVEL_MODE_01;
            //      }

                    
                    if(!BGameMgr.Script.Flag){//スクリプト終了待ち
                        BGameMgr.SelectLevel.Mode = SELECT_LEVEL_MODE_01;
                    }
                    
//                  //XA終了まで待ち
//                  if(!ip_task->user[0]){
//                      if(--ip_task->user[1]<=0){
//                          if(dSoundStatus == DslStatStandby)
//                          {//スタンバイなら次を読みに行く
//                              ip_task->user[0]=1;
//                              BGameMgr.SelectLevel.Mode = SELECT_LEVEL_MODE_01;
//                          }
//                      }
//                  }
                    
                    for(i=0;i<BGameMgr.Level+1;i++)
                    {//横
                        for(j=0;j<5;j++)
                        {//縦
                            if(j>i) continue;
                            //レベルセレクトプレート
                            SpData.No       = BAND_CHAR_GAME_LEVEL_SELECT_PLATE;
                            SpData.PosX     = 101 + 25*i;
                            SpData.PosY     = 95 - 10*j;
                            SpData.PosZ     = PRIORITY_EVENT_BG-1;
                            SpData.ScaleX   = SCALE10;
                            SpData.ScaleY   = SCALE10;
                            SpData.Rotate   = ROTATE000;
                            SpData.Reverse  = NOREVERS;
                            DrawSprite( &SpData );
                        }
                    }
                    break;
                case SELECT_LEVEL_MODE_01:  //下から上へ明るく
                    //----操作
                    if(JstPad &  PADLright)
                    {
                        //[♪] レバー音
                        ssPlaySe(BUTONSE_LEVER);

                        if(++BGameMgr.PlayLevel>BGameMgr.Level){
                            BGameMgr.PlayLevel=0;
                        }
                    }else
                    if(JstPad &  PADLleft){
                        //[♪] レバー音
                        ssPlaySe(BUTONSE_LEVER);
                        
                        if(--BGameMgr.PlayLevel<0){
                            BGameMgr.PlayLevel=BGameMgr.Level;
                        }
                    }else{
                        
                    }
                    
                    //----決定
                    if(JstPad &  PADRright)
                    {//next EXIT
                        BGameMgr.SelectLevel.Mode=SELECT_LEVEL_MODE_02;
                        
                        //[♪]決定
                        ssPlaySe(BUTONSE_MARU);
                    }
                    
                    //----描画
                    if( ++BGameMgr.SelectLevel.BlockWt > EVENT_SELECT_LEVEL_FLUSH_ANM_TIME)
                    {//
                        BGameMgr.SelectLevel.BlockWt=0;
                        if(++BGameMgr.SelectLevel.BlockNo > BAND_GAME_MAX_LEVEL_NUM)
                        {
                            BGameMgr.SelectLevel.BlockNo=0;
                        }
                    }
                    
                    for(i=0;i<BGameMgr.Level+1;i++)
                    {//横
                        for(j=0;j<5;j++)
                        {//縦
                            if(j>i) continue;
                            if(BGameMgr.SelectLevel.BlockNo <= j) continue;
                            
                            //レベルセレクトプレート
                            SpData.No       = BAND_CHAR_GAME_LEVEL_SELECT_PLATE;
                            SpData.PosX     = 101 + 25*i;
                            SpData.PosY     = 95 - 10*j;
                            SpData.PosZ     = PRIORITY_EVENT_BG-1;
                            SpData.ScaleX   = SCALE10;
                            SpData.ScaleY   = SCALE10;
                            SpData.Rotate   = ROTATE000;
                            SpData.Reverse  = NOREVERS;
                            DrawSprite( &SpData );
                        }
                    }
                    break;
                case SELECT_LEVEL_MODE_02:  //選んだレベルのみフラッシュ

                    if(!BGameMgr.SelectLevel.WaitFlag)
                    {
                        if(++BGameMgr.SelectLevel.KeteiWt>EVENT_SELECT_LEVEL_KETEI_WAIT_TIME)
                        {
                            //フラッシュ後抜ける
                            BGameMgr.SelectLevel.WaitFlag   = 1;
                            
                            Task.func           = EventFadeOutTask;
                            Task.priority       = TASK_NO_GAME_FADE;
                            Task.attribute      = ATTR_USER;
                            Task.status         = TASK_NEW_ENTRY;
                            Task.id             = TASK_NO_GAME_FADE;
                            Task.wait_time      = 0;
                            Task.buf            = NULL;
                            Task.name           = "EventFadeOutTask";
                            Task.mode           = TASK_MODE_INIT;
                            Task.user[0]        = ip_task->id;
                            CreateTask(&Task);
                        }
                    }
                    
                    if( ++BGameMgr.SelectLevel.KeteiFlushWt > EVENT_SELECT_LEVEL_KETEI_FLUSH_TIME ){
                        BGameMgr.SelectLevel.KeteiFlushWt = 0;
                        BGameMgr.SelectLevel.KeteiFlushIndex^=1;
                    }
                    
                    if(BGameMgr.SelectLevel.KeteiFlushIndex){
                        for(i=0;i<5;i++)
                        {//縦
                            if(BGameMgr.PlayLevel>=i){
                                //レベルセレクトプレート
                                SpData.No       = BAND_CHAR_GAME_LEVEL_SELECT_PLATE;
                                SpData.PosX     = 101 + 25*BGameMgr.PlayLevel;
                                SpData.PosY     = 95 - 10*i;
                                SpData.PosZ     = PRIORITY_EVENT_BG-1;
                                SpData.ScaleX   = SCALE10;
                                SpData.ScaleY   = SCALE10;
                                SpData.Rotate   = ROTATE000;
                                SpData.Reverse  = NOREVERS;
                                DrawSprite( &SpData );
                            }
                        }
                    }
                    
                    break;
                default:
            }
            
            //----団長
            if(++BGameMgr.SelectLevel.DantyouWt>EVENT_SELECT_LEVEL_ANM_TIME){
                BGameMgr.SelectLevel.DantyouWt      = 0;
                BGameMgr.SelectLevel.DantyouIndex   ^=1;
            }
            
            SpData.No       = SelectLevelDantyouAnmTable[BGameMgr.SelectLevel.DantyouIndex];
            SpData.PosX     = 96;
            SpData.PosY     = 56+42;
            SpData.PosZ     = PRIORITY_EVENT_BG-2;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );

            //----レベルセレクトプレートワク
            SpData.No       = BAND_CHAR_GAME_LEVEL_SELECT_PLATE_WAKU;
            SpData.PosX     = 100 + 25 * BGameMgr.PlayLevel;
            SpData.PosY     = 80 - 10 * BGameMgr.PlayLevel;
            SpData.PosZ     = PRIORITY_EVENT_BG-2;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );

            //----レベルセレクト背景左
            SpData.No       = BAND_CHAR_GAME_LEVEL_SELECT_BG_00;
            SpData.PosX     = 0;
            SpData.PosY     = 0;
            SpData.PosZ     = PRIORITY_EVENT_BG;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );
            
            //----レベルセレクト背景右
            SpData.No       = BAND_CHAR_GAME_LEVEL_SELECT_BG_01;
            SpData.PosX     = 256;
            SpData.PosY     = 0;
            SpData.PosZ     = PRIORITY_EVENT_BG;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );
            
            break;
        case TASK_MODE_EXIT:
            //スクリプトOFF
            MetuseijiFlag=OFF;

            //---- ゲームコントロールタスク
            Task.func       = GameControllTask;
            Task.priority   = TASK_NO_GAME_CONTROLL;
            Task.attribute  = ATTR_USER;
            Task.status     = TASK_NEW_ENTRY;
            Task.id         = TASK_NO_GAME_CONTROLL;
            Task.wait_time  = 0;
            Task.buf        = NULL;
            Task.name       = "GameControllTask";
            Task.mode       = TASK_MODE_INIT;
            CreateTask(&Task);

            //自分を削除
            ExitTask(ip_task->id);
            break;
        default:
    }
}


//-----------------------------------------------------------------------------
//  関数名 :PauseTask
//  機能   :ポーズ監視タスク
//  注意   :なし
//-----------------------------------------------------------------------------
static int PauseTask(TASK* ip_task)
{
    SPRITE_DATA SpData;
    TASK Task;
    int ret;

    switch( ip_task->mode )
    {
        //---------------------------------------------------------------------
        case TASK_MODE_INIT:
            //next MAIN
            ip_task->mode       = TASK_MODE_MAIN;
            
            //Flag
            ip_task->user[0]    = 0;

            //メニューフラグチェック
            GameMgr.WaitFlag    = OFF;
            break;
        //---------------------------------------------------------------------
        case TASK_MODE_MAIN:
            if( !ip_task->user[0] )
            {//メニューオープン待ち
                ret = MainMenuCheck10();
                
                if(ret==ON)
                {//スタートボタン押される
                    //停止コントロールフラグセット
                    ip_task->user[0] = 1;
                    
                    //タスクスリープ
                    SleepTask(TASK_NO_GAME_DANTYOU);    //団長
                    SleepTask(TASK_NO_GAME_DANIN);      //団員
                }else{
                }
            }else
            {//メニュー選択中
                ret = MainMenuCheck10();
                
                if(ret==OFF)
                {//メニューオフ
                    //起動コントロールフラグセット
                    ip_task->user[0] = 0;
                    
                    //タスクウェイクアップ
                    WakeupTask(TASK_NO_GAME_DANTYOU);   //団長
                    WakeupTask(TASK_NO_GAME_DANIN);     //団員
                }else
                if(ret==MEIN_MENU_OWARI)
                {//ゲーム終了
                    Task.func       = PauseMenuFadeOutTask;
                    Task.priority   = TASK_NO_GAME_FADE;
                    Task.attribute  = ATTR_USER;
                    Task.status     = TASK_NEW_ENTRY;
                    Task.id         = TASK_NO_GAME_FADE;
                    Task.wait_time  = 0;
                    Task.buf        = NULL;
                    Task.name       = "PauseMenuFadeOutTask";
                    Task.mode       = TASK_MODE_INIT;
                    CreateTask(&Task);
                    
                    //タスク終了
                    ip_task->mode = TASK_MODE_EXIT;
                }else{
                    
                }
            }
            break;
        //---------------------------------------------------------------------
        case TASK_MODE_EXIT:
            //メニューフラグチェック
            GameMgr.WaitFlag    = ON;
            
            //自分を削除
            ExitTask(ip_task->id);
            break;
        default:
    }
    return TRUE;
}


//-----------------------------------------------------------------------------
//  関数名 :ClearEventTask
//  機能   :クリアイベントタスク
//  注意   :なし
//-----------------------------------------------------------------------------
static int ClearEventTask(TASK *ip_task)
{
    TASK Task;

    switch(ip_task->mode)
    {
        case TASK_MODE_INIT:
            //next main
            ip_task->mode = TASK_MODE_MAIN;

            if((file_read(BandEventTextureFile[0].fn,LoadAddress)) == -1)
            {//read error
                return FALSE;
            }

            TexInit( BAND_EVENT_TIM_NUM, &BandEventTextureImage[BAND_EVENT_TIM_POS] );
            TimImgData = BandEventTextureImage;

            //イベントテクスチャ登録
            EntrySprite( BandEventSpriteData );

            //イベント変数初期化
            BGameMgr.Event.BgNo         = 0;
            BGameMgr.Event.BgWt         = 0;
            BGameMgr.Event.DantyouNo    = 0;
            BGameMgr.Event.DantyouWt    = 0;
            BGameMgr.Event.Timer        = 0;
            BGameMgr.Event.EndFlag      = 0;

            //終了処理メニュー
            BGameMgr.SelectContinue.Val         = 0;
            BGameMgr.SelectContinue.Type        = SELECT_RETRY_H;
            BGameMgr.SelectContinue.No          = 0;
            BGameMgr.SelectContinue.Wt          = 0;
            BGameMgr.SelectContinue.FadeFlag    = 0;

            //スクリプト
            Task.func           = ScriptTask;
            Task.priority       = TASK_NO_GAME_SCRIPT;
            Task.attribute      = ATTR_USER;
            Task.status         = TASK_NEW_ENTRY;
            Task.id             = TASK_NO_GAME_SCRIPT;
            Task.wait_time      = 0;
            Task.buf            = NULL;
            Task.name           = "ScriptTask";
            Task.mode           = TASK_MODE_INIT;
            Task.user[0]        = SCRIPT_LINE_2;
            Task.user[1]        = DANTYOU_CLEAR_SCRIPT_BASE;
            Task.user[2]        = DANTYOU_CLEAR_SCRIPT_NUM;
            CreateTask(&Task);

            break;
        case TASK_MODE_MAIN:
            ++BGameMgr.Event.Timer;

            //クリアイベント終了時間
            if(BGameMgr.Event.Timer>CLEAR_EVENT_END_TIME){
                BGameMgr.Event.EndFlag=1;
            }

            ClearEventDantyou();
            ClearEventBg();
            
            if(BGameMgr.Event.EndFlag && BGameMgr.AllClearFlag)
            {//オールクリアの場合はすぐにクリアイベントからオールクリアイベントへ
                //next EXIT
                ip_task->mode = TASK_MODE_EXIT;
            }else
            {//通常のクリアの時はこちら
                //イベント終了後この処理を起動
                if(BGameMgr.Event.EndFlag)
                {
                    if(SelectContinue(!BGameMgr.SelectContinue.FadeFlag))
                    {//●ボタンが押された
                        if(!BGameMgr.SelectContinue.FadeFlag)
                        {//フェード中
                            if((BGameMgr.SelectContinue.Val==0) && (BGameMgr.SelectContinue.Type==SELECT_RETRY_H))
                            {//もう一度プレイしますか？　はい
                                BGameMgr.SelectContinue.FadeFlag    = 1;
                                
                                Task.func           = EventFadeOutTask;
                                Task.priority       = TASK_NO_GAME_FADE;
                                Task.attribute      = ATTR_USER;
                                Task.status         = TASK_NEW_ENTRY;
                                Task.id             = TASK_NO_GAME_FADE;
                                Task.wait_time      = 0;
                                Task.buf            = NULL;
                                Task.name           = "EventFadeOutTask";
                                Task.mode           = TASK_MODE_INIT;
                                Task.user[0]        = ip_task->id;
                                CreateTask(&Task);
                            }else
                            if( (BGameMgr.SelectContinue.Val==1) && (BGameMgr.SelectContinue.Type==SELECT_RETRY_H))
                            {//もう一度プレイしますか？　いいえ
                                BGameMgr.SelectContinue.Type    =SELECT_END_H;
                                BGameMgr.SelectContinue.Val     = 0;
                            }else
                            if((BGameMgr.SelectContinue.Type==SELECT_END_H) && (BGameMgr.SelectContinue.Val==0))
                            {//やめますか？　はい
                                BGameMgr.SelectContinue.FadeFlag    = 1;
                                
                                Task.func           = EventFadeOutTask;
                                Task.priority       = TASK_NO_GAME_FADE;
                                Task.attribute      = ATTR_USER;
                                Task.status         = TASK_NEW_ENTRY;
                                Task.id             = TASK_NO_GAME_FADE;
                                Task.wait_time      = 0;
                                Task.buf            = NULL;
                                Task.name           = "EventFadeOutTask";
                                Task.mode           = TASK_MODE_INIT;
                                Task.user[0]        = ip_task->id;
                                CreateTask(&Task);
                            }else
                            if((BGameMgr.SelectContinue.Type==SELECT_END_H) && (BGameMgr.SelectContinue.Val==1))
                            {//やめますか？　いいえ
                                BGameMgr.SelectContinue.Type    = SELECT_RETRY_H;
                                BGameMgr.SelectContinue.Val     = 0;
                            }else
                            {
                                
                            }
                        }
                    }else{
                        
                    }
                }
            }
            
            break;
        case TASK_MODE_EXIT:
            //登録スプライト開放
            ReleaseSprite();
            
            //ここは3択 レベルセレクト
            //          メインメニュー
            //          オールクリア
            if(BGameMgr.AllClearFlag)
            {   //オールクリアタスク
                Task.func       = AllClearEventTask;
                Task.priority   = TASK_NO_GAME_ALL_CLEAR_EVENT;
                Task.attribute  = ATTR_USER;
                Task.status     = TASK_NEW_ENTRY;
                Task.id         = TASK_NO_GAME_ALL_CLEAR_EVENT;
                Task.wait_time  = 0;
                Task.buf        = NULL;
                Task.name       = "AllClearEventTask";
                Task.mode       = TASK_MODE_INIT;
                CreateTask(&Task);
            }else
            if((BGameMgr.SelectContinue.Val==0) && (BGameMgr.SelectContinue.Type==SELECT_RETRY_H))
            {   //レベルセレクトタスク
                Task.func       = SelectLevelTask;
                Task.priority   = TASK_NO_GAME_SELECT_LEVEL;
                Task.attribute  = ATTR_USER;
                Task.status     = TASK_NEW_ENTRY;
                Task.id         = TASK_NO_GAME_SELECT_LEVEL;
                Task.wait_time  = 0;
                Task.buf        = NULL;
                Task.name       = "SelectLevelTask";
                Task.mode       = TASK_MODE_INIT;
                CreateTask(&Task);
            }else
            {   //ゲームをおわります
                BGameMgr.ExitFlag=1;
            }
            
            //自分を削除
            ExitTask(ip_task->id);
            break;
        default:
    }
}


//-----------------------------------------------------------------------------
//  関数名 :AllClearEventTask
//  機能   :オールクリアイベントタスク
//  注意   :なし
//-----------------------------------------------------------------------------
static int AllClearEventTask(TASK *ip_task)
{
    TASK Task;
    int i;


    switch(ip_task->mode)
    {
        case TASK_MODE_INIT:
            //next main
            ip_task->mode = TASK_MODE_MAIN;
            
#ifdef __DEBUG_BAND__
            if((file_read(BandEventTextureFile[0].fn,LoadAddress)) == -1)
            {//read error
                return FALSE;
            }
            TexInit( BAND_EVENT_TIM_NUM, &BandEventTextureImage[BAND_EVENT_TIM_POS] );
            TimImgData = BandEventTextureImage;
#endif
            //スプライト登録
            EntrySprite( BandEventSpriteData );

            //初期化
            for(i=0;i<10;i++)
            {
                BGameMgr.Event.Gakudanin[i].Status          = InitDataAllClearGkudan[i].Status;
                BGameMgr.Event.Gakudanin[i].ExitFlag        = InitDataAllClearGkudan[i].ExitFlag;
                BGameMgr.Event.Gakudanin[i].PosX            = InitDataAllClearGkudan[i].PosX;
                BGameMgr.Event.Gakudanin[i].PosY            = InitDataAllClearGkudan[i].PosY;
                BGameMgr.Event.Gakudanin[i].PosZ            = InitDataAllClearGkudan[i].PosZ;
                BGameMgr.Event.Gakudanin[i].DirX            = InitDataAllClearGkudan[i].DirX;
                BGameMgr.Event.Gakudanin[i].DirY            = InitDataAllClearGkudan[i].DirY;
                BGameMgr.Event.Gakudanin[i].Base            = i*2;
                BGameMgr.Event.Gakudanin[i].No              = GakudaninAnmTable[BGameMgr.Event.Gakudanin[i].Base];
                BGameMgr.Event.Gakudanin[i].Index           = 0;
                BGameMgr.Event.Gakudanin[i].Wt              = 0;
                BGameMgr.Event.Gakudanin[i].AppearWaitTime  = InitDataAllClearGkudan[i].AppearWaitTime;
                BGameMgr.Event.Gakudanin[i].MoveCount       = 0;
                BGameMgr.Event.Gakudanin[i].StopPosX        = InitDataAllClearGkudan[i].StopPosX;
                BGameMgr.Event.Gakudanin[i].StopPosY        = InitDataAllClearGkudan[i].StopPosY;
            }
            
            //イベントタイマー初期化
            BGameMgr.Event.Timer    = 0;
            
            //音が入るまで暫定
            BGameMgr.Event.EndFlag  = 0;
            
            //終了処理メニュー
            BGameMgr.SelectContinue.Val         = 0;
            BGameMgr.SelectContinue.Type        = SELECT_RETRY_H;
            BGameMgr.SelectContinue.No          = 0;
            BGameMgr.SelectContinue.Wt          = 0;
            BGameMgr.SelectContinue.FadeFlag    = 0;

            //スクリプト
            Task.func           = ScriptTask;
            Task.priority       = TASK_NO_GAME_SCRIPT;
            Task.attribute      = ATTR_USER;
            Task.status         = TASK_NEW_ENTRY;
            Task.id             = TASK_NO_GAME_SCRIPT;
            Task.wait_time      = 0;
            Task.buf            = NULL;
            Task.name           = "ScriptTask";
            Task.mode           = TASK_MODE_INIT;
            Task.user[0]        = SCRIPT_LINE_2;
            Task.user[1]        = DANTYOU_ALL_CLEAR_SCRIPT_BASE;
            Task.user[2]        = DANTYOU_ALL_CLEAR_SCRIPT_NUM;
            CreateTask(&Task);

            break;
        case TASK_MODE_MAIN:
            //イベントタイマー
            ++BGameMgr.Event.Timer;
            
            if(BGameMgr.Event.Timer>ALL_CLEAR_EVENT_END_TIME){
                BGameMgr.Event.EndFlag=1;
            }

            //処理
            AllClearEventGakudan();
            AllClearEventBg();
            
            //イベント終了後この処理を起動
            if(BGameMgr.Event.EndFlag)
            {
                if(SelectContinue(!BGameMgr.SelectContinue.FadeFlag))
                {//●ボタンが押された
                    if(!BGameMgr.SelectContinue.FadeFlag)
                    {//フェード中
                        if((BGameMgr.SelectContinue.Val==0) && (BGameMgr.SelectContinue.Type==SELECT_RETRY_H))
                        {//もう一度プレイしますか？　はい
                            BGameMgr.SelectContinue.FadeFlag    = 1;
                            
                            Task.func           = EventFadeOutTask;
                            Task.priority       = TASK_NO_GAME_FADE;
                            Task.attribute      = ATTR_USER;
                            Task.status         = TASK_NEW_ENTRY;
                            Task.id             = TASK_NO_GAME_FADE;
                            Task.wait_time      = 0;
                            Task.buf            = NULL;
                            Task.name           = "EventFadeOutTask";
                            Task.mode           = TASK_MODE_INIT;
                            Task.user[0]        = ip_task->id;
                            CreateTask(&Task);
                        }else
                        if( (BGameMgr.SelectContinue.Val==1) && (BGameMgr.SelectContinue.Type==SELECT_RETRY_H))
                        {//もう一度プレイしますか？　いいえ
                            BGameMgr.SelectContinue.Type    =SELECT_END_H;
                            BGameMgr.SelectContinue.Val     = 0;
                        }else
                        if((BGameMgr.SelectContinue.Type==SELECT_END_H) && (BGameMgr.SelectContinue.Val==0))
                        {//やめますか？　はい
                            BGameMgr.SelectContinue.FadeFlag    = 1;
                            
                            Task.func           = EventFadeOutTask;
                            Task.priority       = TASK_NO_GAME_FADE;
                            Task.attribute      = ATTR_USER;
                            Task.status         = TASK_NEW_ENTRY;
                            Task.id             = TASK_NO_GAME_FADE;
                            Task.wait_time      = 0;
                            Task.buf            = NULL;
                            Task.name           = "EventFadeOutTask";
                            Task.mode           = TASK_MODE_INIT;
                            Task.user[0]        = ip_task->id;
                            CreateTask(&Task);
                        }else
                        if((BGameMgr.SelectContinue.Type==SELECT_END_H) && (BGameMgr.SelectContinue.Val==1))
                        {//やめますか？　いいえ
                            BGameMgr.SelectContinue.Type    = SELECT_RETRY_H;
                            BGameMgr.SelectContinue.Val     = 0;
                        }else
                        {
                            
                        }
                    }
                }else{
                    
                }
            }
            break;
        case TASK_MODE_EXIT:
            //登録スプライト開放
            ReleaseSprite();
            
            //ここは2択レベルセレクトとメインメニューから
            //  (1)レベルセレクト
            //  (2)メインメニュー
            
            if((BGameMgr.SelectContinue.Val==0) && (BGameMgr.SelectContinue.Type==SELECT_RETRY_H))
            {   //レベルセレクトタスク
                Task.func       = SelectLevelTask;
                Task.priority   = TASK_NO_GAME_SELECT_LEVEL;
                Task.attribute  = ATTR_USER;
                Task.status     = TASK_NEW_ENTRY;
                Task.id         = TASK_NO_GAME_SELECT_LEVEL;
                Task.wait_time  = 0;
                Task.buf        = NULL;
                Task.name       = "SelectLevelTask";
                Task.mode       = TASK_MODE_INIT;
                CreateTask(&Task);
            }else
            {   //ゲームをおわります
                BGameMgr.ExitFlag=1;
            }
            
            //自分を削除
            ExitTask(ip_task->id);
            break;
        default:
    }
}




//-----------------------------------------------------------------------------
//  関数名  :EventFadeOutTask
//
//  work    :フェードアウトタスク
//  in      :タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static  int EventFadeOutTask(TASK* ip_task)
{
    TASK* pTask;

    switch( ip_task->mode )
    {
        //---------------------------------------------------------------------
        case TASK_MODE_INIT:
            //next MAIN
            ip_task->mode       = TASK_MODE_MAIN;
            
            // フェードOUTします
            GameMgr.FadeFlag = FadeOut; 
            break;
        //---------------------------------------------------------------------
        case TASK_MODE_MAIN:
            
            //フェードアウト
            if(GameMgr.FadeFlag==FadeOutOk){
                ip_task->mode = TASK_MODE_EXIT;
            }
            
            break;
        //---------------------------------------------------------------------
        case TASK_MODE_EXIT:
            pTask = SearchTask(ip_task->user[0]);
            if(pTask!=NULL){
                pTask->mode = TASK_MODE_EXIT;
            }
            
            //自分を削除
            ExitTask(ip_task->id);
            break;
        default:
    }
    return TRUE;
}




//-----------------------------------------------------------------------------
//  関数名  :PauseMenuFadeOutTask
//
//  work    :フェードアウトタスク
//  in      :タスクポインタ
//  out     :TRUE
//  note    :タスク終了後ゲーム終了フラグをセットします。
//-----------------------------------------------------------------------------
static int PauseMenuFadeOutTask(TASK* ip_task)
{
    switch( ip_task->mode )
    {
        //---------------------------------------------------------------------
        case TASK_MODE_INIT:
            //next MAIN
            ip_task->mode       = TASK_MODE_MAIN;
            
            GameMgr.FadeFlag = FadeOut; // フェードOUTします
            break;
        //---------------------------------------------------------------------
        case TASK_MODE_MAIN:
            
            //フェードアウト
            if(GameMgr.FadeFlag==FadeOutOk){
                ip_task->mode = TASK_MODE_EXIT;
            }
            
            break;
        //---------------------------------------------------------------------
        case TASK_MODE_EXIT:
            
            //終了フラグセット
            BGameMgr.ExitFlag   = 1;
            
            //自分を削除
            ExitTask(ip_task->id);
            break;
        default:
    }
    return TRUE;
}




//      //-----------------------------------------------------------------------------
//      //  関数名  :ScriptTask
//      //
//      //  work    :スクリプトタスク
//      //  in      :TASK* ip_task 
//      //  out     :TRUE
//      //  note    :なし
//      //-----------------------------------------------------------------------------
//      static int ScriptTask(TASK* ip_task)
//      {
//
//          switch( ip_task->mode )
//          {
//              //---------------------------------------------------------------------
//              case TASK_MODE_INIT:
//                  //next MAIN
//                  ip_task->mode       = TASK_MODE_MAIN;
//                  
//                  BGameMgr.Script.Flag    = 0;
//                  BGameMgr.Script.Index   = 0;
//                  BGameMgr.Script.Line    = ip_task->user[0];
//                  BGameMgr.Script.Base    = ip_task->user[1];
//                  BGameMgr.Script.Num     = ip_task->user[2];
//                  
//                  break;
//              //---------------------------------------------------------------------
//              case TASK_MODE_MAIN:
//                  
//                  if(MetuseijiFlag==OFF)
//                  {
//                      switch(BGameMgr.Script.Line)
//                      {
//                          case SCRIPT_LINE_1:
//                              MenuMessageSet10(&BandScript[BGameMgr.Script.Base + BGameMgr.Script.Index]);
//                              break;
//                          case SCRIPT_LINE_2:
//                              MenuMessageSet20(&BandScript[BGameMgr.Script.Base + BGameMgr.Script.Index]);
//                              break;
//                          case SCRIPT_LINE_3:
//                              MenuMessageSet30(&BandScript[BGameMgr.Script.Base + BGameMgr.Script.Index]);
//                              break;
//                          default:
//                      }
//                      
//                      if(++BGameMgr.Script.Index >= BGameMgr.Script.Num)
//                      {
//                          ip_task->mode = TASK_MODE_EXIT;
//                      }
//                  }
//                  break;
//              //---------------------------------------------------------------------
//              case TASK_MODE_EXIT:
//                  
//                  
//                  //自分を削除
//                  ExitTask(ip_task->id);
//                  break;
//              default:
//          }
//          return TRUE;
//      }




//-----------------------------------------------------------------------------
//  関数名  :ScriptTask
//
//  work    :スクリプトタスク
//  in      :TASK* ip_task 
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int ScriptTask(TASK* ip_task)
{
    switch( ip_task->mode )
    {
        //---------------------------------------------------------------------init
        case TASK_MODE_INIT:
            //next MAIN
            ip_task->mode       = TASK_MODE_MAIN;

            BGameMgr.Script.Flag    = 1;
            BGameMgr.Script.Index   = 0;
            BGameMgr.Script.Line    = ip_task->user[0];
            BGameMgr.Script.Base    = ip_task->user[1];
            BGameMgr.Script.Num     = ip_task->user[2];
            ip_task->user[0]        = 0;                            //mode
            ip_task->user[1]        = GET_DA_STATUS_WAIT_TIME*3;    //timer

            break;
        //---------------------------------------------------------------------main
        case TASK_MODE_MAIN:
            
            switch(ip_task->user[0])
            {
                //--------------------XAプレイ
                case 0:
                    if(MetuseijiFlag==OFF)
                    {
                        switch(BGameMgr.Script.Line)
                        {
                            case SCRIPT_LINE_1:
                                MenuMessageSet10(&BandScript[BGameMgr.Script.Base + BGameMgr.Script.Index]);
                                break;
                            case SCRIPT_LINE_2:
                                MenuMessageSet20(&BandScript[BGameMgr.Script.Base + BGameMgr.Script.Index]);
                                break;
                            case SCRIPT_LINE_3:
                                MenuMessageSet30(&BandScript[BGameMgr.Script.Base + BGameMgr.Script.Index]);
                                break;
                            default:
                        }
                        
                        if(++BGameMgr.Script.Index >= BGameMgr.Script.Num){
                            ip_task->user[0] = 1;
                        }
                    }
                    break;
                //--------------------XA終了チェック
                case 1:
                    if(--ip_task->user[1]<=0){
                        if(dSoundStatus == DslStatStandby){
                            ip_task->mode = TASK_MODE_EXIT;
                        }
                    }
                    break;
                default:
            }
            
            break;
        //---------------------------------------------------------------------exit
        case TASK_MODE_EXIT:
            
            BGameMgr.Script.Flag    = 0;
            
            //自分を削除
            ExitTask(ip_task->id);
            break;
        default:
    }
    return TRUE;
}






//-----------------------------------------------------------------------------
//  関数名 :CheckKeyDir
//  機能   :キー方向を取得
//  注意   :なし
//-----------------------------------------------------------------------------
static int CheckKeyDir(int *ip_dir)
{

    if(NewPad & PADLup){
        *ip_dir=KEY_DIR_UP;
        return TRUE;
    }else
    if(NewPad & PADLdown){
        *ip_dir=KEY_DIR_DOWN;
        return TRUE;
    }
    else
    if(NewPad & PADLleft){
        *ip_dir=KEY_DIR_LEFT;
        return TRUE;
    }
    else
    if(NewPad & PADLright){
        *ip_dir=KEY_DIR_RIGHT;
        return TRUE;
    }else{
        *ip_dir=KEY_DIR_NOTHING;
        return FALSE;
    }
}


//-----------------------------------------------------------------------------
//  関数名 :CheckCharacter
//  機能   :キャラクターチェック
//  注意   :なし
//-----------------------------------------------------------------------------
static int CheckCharacter(int i_dir)
{
    int ofx,ofy;

    //検索方向よりオフセット選択
    switch(i_dir)
    {
        case KEY_DIR_UP:
            ofx=0;
            ofy=-1;
            break;
        case KEY_DIR_DOWN:
            ofx=0;
            ofy=1;
            break;
        case KEY_DIR_LEFT:
            ofx=-1;
            ofy=0;
            break;
        case KEY_DIR_RIGHT:
            ofx=1;
            ofy=0;
            break;
        default:
            ofx=0;
            ofy=0;
            break;
    }

    //調べる
    switch( BGameMgr.Map.Data[BGameMgr.Dantyou.Py+ofy][BGameMgr.Dantyou.Px+ofx] )
    {
        case CHAR_NONE:
            return CHAR_NONE;
            break;
        case CHAR_WALL:
            return CHAR_WALL;
            break;
        case CHAR_DANIN:
            return CHAR_DANIN;
            break;
        default:
            return CHAR_WALL;
            break;
    }
}

//-----------------------------------------------------------------------------
//  関数名 :CheckDanin
//  機能   :団員チェック
//  注意   :なし
//-----------------------------------------------------------------------------
static int CheckDanin(int i_dir)
{
    int ofx,ofy,i;

    //検索方向よりオフセット選択
    switch(i_dir)
    {
        case KEY_DIR_UP:
            ofx=0;
            ofy=-1;
            break;
        case KEY_DIR_DOWN:
            ofx=0;
            ofy=1;
            break;
        case KEY_DIR_LEFT:
            ofx=-1;
            ofy=0;
            break;
        case KEY_DIR_RIGHT:
            ofx=1;
            ofy=0;
            break;
        default:
            ofx=0;
            ofy=0;
            break;
    }

    //団員を調べる
    for(i=0;i<DANIN_NUM;i++)
    {
        if( BGameMgr.Danin[i].Py == BGameMgr.Dantyou.Py+ofy && BGameMgr.Danin[i].Px == BGameMgr.Dantyou.Px+ofx)
        {
            if( BGameMgr.Danin[i].EntryIndex == BGameMgr.Dantyou.GetIndex )
            {//ゲット
                return TRUE;
            }
        }
    }
    return FALSE;
}


//-----------------------------------------------------------------------------
//  関数名 :InitMap
//  機能   :マップ初期化
//  注意   :なし
//-----------------------------------------------------------------------------
static void InitMap(void)
{
    memcpy(BGameMgr.Map.Data,InitMapData, (SQUARE_W_NUM+2)*(SQUARE_H_NUM+2) );
}


//-----------------------------------------------------------------------------
//  関数名 :DrawDaninNo
//  機能   :団員の数字描画
//  注意   :なし
//-----------------------------------------------------------------------------
static void DrawDaninNo(int i_num,int i_wsize,int *ip_numtbl,int i_x,int i_y,int i_z)
{
    int i,bx,by,offsetx;
    int numarr[3];
    SPRITE_DATA SpData;

    if(i_num>99)    i_num=99;
    if(i_num<0)     i_num=0;

    //一桁と２桁の位置
    offsetx=0;
    if(i_num<10)    offsetx=-2;


    numarr[0] = i_num/100;                              //100
    numarr[1] = (i_num-numarr[0]*100)/10;               //10
    numarr[2] = (i_num-numarr[0]*100-numarr[1]*10)/1;   //1

    //
    bx=i_x;
    by=i_y;

    for(i=0;i<3;i++){
        if(numarr[i]==0){
            if(i==0)
            {//100の桁がゼロの時は次の桁へ
                //次の桁へ
                bx+=i_wsize;
            }else if(i==1)
            {//10の桁がゼロの時
                if(i_num<100)
                {//
                    //次の桁へ
                    bx+=i_wsize;
                }else
                {//ゼロを描画
                    //描画
                    SpData.No       = ip_numtbl[0];
                    SpData.PosX     = bx;
                    SpData.PosY     = by;
                    SpData.PosZ     = i_z;
                    SpData.ScaleX   = SCALE10;
                    SpData.ScaleY   = SCALE10;
                    SpData.Rotate   = ROTATE000;
                    SpData.Reverse  = NOREVERS;
                    DrawSprite( &SpData );

                    //次の桁へ
                    bx+=i_wsize;
                }
            }else if(i==2)
            {//一桁がゼロを描画
                SpData.No       = ip_numtbl[0];
                SpData.PosX     = bx+offsetx;
                SpData.PosY     = by;
                SpData.PosZ     = i_z;
                SpData.ScaleX   = SCALE10;
                SpData.ScaleY   = SCALE10;
                SpData.Rotate   = ROTATE000;
                SpData.Reverse  = NOREVERS;
                DrawSprite( &SpData );
            }
        }else{
            //描画
            SpData.No       = ip_numtbl[numarr[i]];
            SpData.PosX     = bx+offsetx;
            SpData.PosY     = by;
            SpData.PosZ     = i_z;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );
            
            //次の桁へ
            bx+=i_wsize;
        }
    }

}


//-----------------------------------------------------------------------------
//  関数名 :GetMapPos
//  機能   :マップ上の位置を求める（４分割）
//  注意   :なし
//-----------------------------------------------------------------------------
static int GetMapPos(int i_x,int i_y)
{
    if( i_x>=1 && i_x<=6 )
    {//横：1-6
        if( i_y>=1 && i_y<=3 )
        {//縦：1-３
            return MAP_AREA_00;
        }else
        if( i_y>=4 && i_y<=6 )
        {//縦：4-6
            return MAP_AREA_02;
        }else
        {
            return MAP_AREA_FALSE;
        }
    }else 
    if( i_x>=7 && i_x<=12 )
    {//横：7～12
        if( i_y>=1 && i_y<=3 )
        {//縦：1-３
            return MAP_AREA_01;
        }else
        if( i_y>=4 && i_y<=6 )
        {//縦：4-6
            return MAP_AREA_03;
        }else
        {
            return MAP_AREA_FALSE;
        }
    }else
    {
        return MAP_AREA_FALSE;
    }
}


//-----------------------------------------------------------------------------
//  関数名 :ClearEventDantyou
//  機能   :クリアイベント団長
//  注意   :なし
//-----------------------------------------------------------------------------
static void ClearEventDantyou(void)
{
    static int ClearEventDantyouAnmTable[]={
        BAND_CHAR_EVENT_CLEAR_DANTYOU_00,
        BAND_CHAR_EVENT_CLEAR_DANTYOU_01,
    };
    SPRITE_DATA SpData;

    if(++BGameMgr.Event.DantyouWt>CLEAR_EVENT_DANTYOU_CHANGE_TIMER){
        BGameMgr.Event.DantyouWt    = 0;
        BGameMgr.Event.DantyouNo    ^=1;
    }

    SpData.No       = ClearEventDantyouAnmTable[BGameMgr.Event.DantyouNo];  //インデックス番号
    SpData.PosX     = 96;                               //X位置
    SpData.PosY     = 56;                               //Y位置
    SpData.PosZ     = PRIORITY_EVENT_BG;                //優先順位
    SpData.ScaleX   = SCALE10;                          //スケールX
    SpData.ScaleY   = SCALE10;                          //スケールY
    SpData.Rotate   = ROTATE000;                        //回転角
    SpData.Reverse  = NOREVERS;                         //反転コード
    DrawSprite( &SpData );                              //スプライト描画
}


//-----------------------------------------------------------------------------
//  関数名 :AllClearEventGakudan
//  機能   :クリアイベント楽団
//  注意   :なし
//-----------------------------------------------------------------------------
static void AllClearEventGakudan(void)
{
    SPRITE_DATA SpData;
    int i;


    //
    for(i=0;i<10;i++)
    {
        switch(BGameMgr.Event.Gakudanin[i].Status)
        {
            case ALL_CLEAR_EVENT_GAKUDANIN_WAIT:    //待ち
                if(--BGameMgr.Event.Gakudanin[i].AppearWaitTime<0)
                {
                    //描画許可
                    BGameMgr.Event.Gakudanin[i].ExitFlag = 1;
                    //ステータスを変更
                    BGameMgr.Event.Gakudanin[i].Status=ALL_CLEAR_EVENT_GAKUDANIN_MOVE;
                }
                break;
            case ALL_CLEAR_EVENT_GAKUDANIN_MOVE:    //移動
                //移動
                BGameMgr.Event.Gakudanin[i].PosX += BGameMgr.Event.Gakudanin[i].DirX*2;
                BGameMgr.Event.Gakudanin[i].PosY += BGameMgr.Event.Gakudanin[i].DirY*2;
                
                if( (BGameMgr.Event.Gakudanin[i].PosX == BGameMgr.Event.Gakudanin[i].StopPosX) ){
                    BGameMgr.Event.Gakudanin[i].Status = ALL_CLEAR_EVENT_GAKUDANIN_STOP;
                }
                
                break;
            case ALL_CLEAR_EVENT_GAKUDANIN_STOP:    //停止
                // 
                break;
            default:
        }
        
        if(++BGameMgr.Event.Gakudanin[i].Wt > ALL_CLEAR_EVENT_GAKUDANIN_ANM_TIME)
        {
            BGameMgr.Event.Gakudanin[i].Wt=0;
            BGameMgr.Event.Gakudanin[i].Index ^= 1;
        }

        //描画
        if(BGameMgr.Event.Gakudanin[i].ExitFlag)
        {
            SpData.No       = BGameMgr.Event.Gakudanin[i].No+BGameMgr.Event.Gakudanin[i].Index;     //インデックス番号
            SpData.PosX     = BGameMgr.Event.Gakudanin[i].PosX;     //X位置
            SpData.PosY     = BGameMgr.Event.Gakudanin[i].PosY;     //Y位置
            SpData.PosZ     = BGameMgr.Event.Gakudanin[i].PosZ;     //優先順位
            SpData.ScaleX   = SCALE10;                              //スケールX
            SpData.ScaleY   = SCALE10;                              //スケールY
            SpData.Rotate   = ROTATE000;                            //回転角
            SpData.Reverse  = NOREVERS;                             //反転コード
            DrawSprite( &SpData );                                  //スプライト描画
        }
    }

}


//-----------------------------------------------------------------------------
//  関数名 :ClearEventBg
//  機能   :クリアイベント背景
//  注意   :なし
//-----------------------------------------------------------------------------
static void ClearEventBg(void)
{
    SPRITE_DATA SpData;


    if(++BGameMgr.Event.BgWt>CLEAR_EVENT_BG_CHANGE_TIMER){
        BGameMgr.Event.BgWt = 0;
        BGameMgr.Event.BgNo^=1;
    }

    if(BGameMgr.Event.BgNo){
        SpData.No       = BAND_CHAR_EVENT_CLEAR_BG_00;  //インデックス番号
        SpData.PosX     = 0;                            //X位置
        SpData.PosY     = 0;                            //Y位置
        SpData.PosZ     = PRIORITY_EVENT_BG;            //優先順位
        SpData.ScaleX   = SCALE10;                      //スケールX
        SpData.ScaleY   = SCALE10;                      //スケールY
        SpData.Rotate   = ROTATE000;                    //回転角
        SpData.Reverse  = NOREVERS;                     //反転コード
        DrawSprite( &SpData );                          //スプライト描画

        SpData.No       = BAND_CHAR_EVENT_CLEAR_BG_02;  //インデックス番号
        SpData.PosX     = 256;                          //X位置
        SpData.PosY     = 0;                            //Y位置
        SpData.PosZ     = PRIORITY_EVENT_BG;            //優先順位
        SpData.ScaleX   = SCALE10;                      //スケールX
        SpData.ScaleY   = SCALE10;                      //スケールY
        SpData.Rotate   = ROTATE000;                    //回転角
        SpData.Reverse  = NOREVERS;                     //反転コード
        DrawSprite( &SpData );                          //スプライト描画
    }else{
        SpData.No       = BAND_CHAR_EVENT_CLEAR_BG_01;  //インデックス番号
        SpData.PosX     = 0;                            //X位置
        SpData.PosY     = 0;                            //Y位置
        SpData.PosZ     = PRIORITY_EVENT_BG;            //優先順位
        SpData.ScaleX   = SCALE10;                      //スケールX
        SpData.ScaleY   = SCALE10;                      //スケールY
        SpData.Rotate   = ROTATE000;                    //回転角
        SpData.Reverse  = NOREVERS;                     //反転コード
        DrawSprite( &SpData );                          //スプライト描画

        SpData.No       = BAND_CHAR_EVENT_CLEAR_BG_03;  //インデックス番号
        SpData.PosX     = 256;                          //X位置
        SpData.PosY     = 0;                            //Y位置
        SpData.PosZ     = PRIORITY_EVENT_BG;            //優先順位
        SpData.ScaleX   = SCALE10;                      //スケールX
        SpData.ScaleY   = SCALE10;                      //スケールY
        SpData.Rotate   = ROTATE000;                    //回転角
        SpData.Reverse  = NOREVERS;                     //反転コード
        DrawSprite( &SpData );                          //スプライト描画
    }
}


//-----------------------------------------------------------------------------
//  関数名 :AllClearEventBg
//  機能   :オールクリアイベント背景
//  注意   :なし
//-----------------------------------------------------------------------------
static void AllClearEventBg(void)
{
    SPRITE_DATA SpData;

    //背景１
    SpData.No       = BAND_CHAR_EVENT_ALLCLEAR_BG_00;   //インデックス番号
    SpData.PosX     = 0;                                //X位置
    SpData.PosY     = 0;                                //Y位置
    SpData.PosZ     = PRIORITY_EVENT_BG_FRONT;          //優先順位
    SpData.ScaleX   = SCALE10;                          //スケールX
    SpData.ScaleY   = SCALE10;                          //スケールY
    SpData.Rotate   = ROTATE000;                        //回転角
    SpData.Reverse  = NOREVERS;                         //反転コード
    DrawSprite( &SpData );                              //スプライト描画

    //背景２
    SpData.No       = BAND_CHAR_EVENT_ALLCLEAR_BG_01;   //インデックス番号
    SpData.PosX     = 68;                               //X位置
    SpData.PosY     = 0;                                //Y位置
    SpData.PosZ     = PRIORITY_EVENT_BG;                //優先順位
    SpData.ScaleX   = SCALE10;                          //スケールX
    SpData.ScaleY   = SCALE10;                          //スケールY
    SpData.Rotate   = ROTATE000;                        //回転角
    SpData.Reverse  = NOREVERS;                         //反転コード
    DrawSprite( &SpData );                              //スプライト描画

    //背景３
    SpData.No       = BAND_CHAR_EVENT_ALLCLEAR_BG_02;   //インデックス番号
    SpData.PosX     = 252;                              //X位置
    SpData.PosY     = 0;                                //Y位置
    SpData.PosZ     = PRIORITY_EVENT_BG_FRONT;          //優先順位
    SpData.ScaleX   = SCALE10;                          //スケールX
    SpData.ScaleY   = SCALE10;                          //スケールY
    SpData.Rotate   = ROTATE000;                        //回転角
    SpData.Reverse  = NOREVERS;                         //反転コード
    DrawSprite( &SpData );                              //スプライト描画

    //背景４
    SpData.No       = BAND_CHAR_EVENT_ALLCLEAR_BG_03;   //インデックス番号
    SpData.PosX     = 256;                              //X位置
    SpData.PosY     = 0;                                //Y位置
    SpData.PosZ     = PRIORITY_EVENT_BG_FRONT;          //優先順位
    SpData.ScaleX   = SCALE10;                          //スケールX
    SpData.ScaleY   = SCALE10;                          //スケールY
    SpData.Rotate   = ROTATE000;                        //回転角
    SpData.Reverse  = NOREVERS;                         //反転コード
    DrawSprite( &SpData );                              //スプライト描画
}


//-----------------------------------------------------------------------------
//  関数名 :SelectContinue
//  機能   :クリアイベント後の選択
//  注意   :なし
//-----------------------------------------------------------------------------
static int SelectContinue(int i_flag)
{
    static int BupeAnmTable[] ={
        BAND_CHAR_EVENT_SELECT_CONTINUE_BUPE_00,BAND_CHAR_EVENT_SELECT_CONTINUE_BUPE_01,
    };

    static int MaruBatuTable[]={
        BAND_CHAR_EVENT_SELECT_CONTINUE_YES_LIGHT,  BAND_CHAR_EVENT_SELECT_CONTINUE_NO_DARK,
        BAND_CHAR_EVENT_SELECT_CONTINUE_YES_DARK,   BAND_CHAR_EVENT_SELECT_CONTINUE_NO_LIGHT,
    };

    SPRITE_DATA SpData;
    int o_ret;

    if(i_flag){
        //選択
        o_ret=FALSE;
        if(JstPad &  PADRright){
            //[♪]決定
            ssPlaySe(BUTONSE_MARU);
            o_ret=TRUE;
        }

        //選択
        if(JstPad &  PADLright || JstPad &  PADLleft){
            BGameMgr.SelectContinue.Val^=1;
            //[♪] レバー音
            ssPlaySe(BUTONSE_LEVER);
        }
    }


    //はい・いいえ
    SpData.No       = MaruBatuTable[BGameMgr.SelectContinue.Val*2];     //インデックス番号
    SpData.PosX     = 68+72;                                            //X位置
    SpData.PosY     = 73+57;                                            //Y位置
    SpData.PosZ     = PRIORITY_EVENT_MENU-2;                            //優先順位
    SpData.ScaleX   = SCALE10;                                          //スケールX
    SpData.ScaleY   = SCALE10;                                          //スケールY
    SpData.Rotate   = ROTATE000;                                        //回転角
    SpData.Reverse  = NOREVERS;                                         //反転コード
    DrawSprite( &SpData );                                              //スプライト描画

    SpData.No       = MaruBatuTable[BGameMgr.SelectContinue.Val*2+1];   //インデックス番号
    SpData.PosX     = 68+126;                                           //X位置
    SpData.PosY     = 73+57;                                            //Y位置
    SpData.PosZ     = PRIORITY_EVENT_MENU-2;                            //優先順位
    SpData.ScaleX   = SCALE10;                                          //スケールX
    SpData.ScaleY   = SCALE10;                                          //スケールY
    SpData.Rotate   = ROTATE000;                                        //回転角
    SpData.Reverse  = NOREVERS;                                         //反転コード
    DrawSprite( &SpData );                                              //スプライト描画

    //プレート文字
    switch(BGameMgr.SelectContinue.Type)
    {
        case SELECT_RETRY_H:
            SpData.No       = BAND_CHAR_EVENT_SELECT_CONTINUE_RETRY_H;  //インデックス番号
            SpData.PosX     = 68+20;                                    //X位置
            SpData.PosY     = 73+20;                                    //Y位置
            SpData.PosZ     = PRIORITY_EVENT_MENU-2;                    //優先順位
            SpData.ScaleX   = SCALE10;                                  //スケールX
            SpData.ScaleY   = SCALE10;                                  //スケールY
            SpData.Rotate   = ROTATE000;                                //回転角
            SpData.Reverse  = NOREVERS;                                 //反転コード
            DrawSprite( &SpData );                                      //スプライト描画
            break;
        case SELECT_END_H:
            SpData.No       = BAND_CHAR_EVENT_SELECT_CONTINUE_END_H;    //インデックス番号
            SpData.PosX     = 68+20;                                    //X位置
            SpData.PosY     = 73+20;                                    //Y位置
            SpData.PosZ     = PRIORITY_EVENT_MENU-2;                    //優先順位
            SpData.ScaleX   = SCALE10;                                  //スケールX
            SpData.ScaleY   = SCALE10;                                  //スケールY
            SpData.Rotate   = ROTATE000;                                //回転角
            SpData.Reverse  = NOREVERS;                                 //反転コード
            DrawSprite( &SpData );                                      //スプライト描画
            break;
        case SELECT_CONTINUE_H:
            SpData.No       = BAND_CHAR_EVENT_SELECT_CONTINUE_CONTINUE_H;//インデックス番号
            SpData.PosX     = 68+20;                                    //X位置
            SpData.PosY     = 73+20;                                    //Y位置
            SpData.PosZ     = PRIORITY_EVENT_MENU-2;                    //優先順位
            SpData.ScaleX   = SCALE10;                                  //スケールX
            SpData.ScaleY   = SCALE10;                                  //スケールY
            SpData.Rotate   = ROTATE000;                                //回転角
            SpData.Reverse  = NOREVERS;                                 //反転コード
            DrawSprite( &SpData );                                      //スプライト描画
            break;
        default:
    }

    //ブーぺ
    if(++BGameMgr.SelectContinue.Wt>SELECT_LEVEL_PUPE_ANM_TIME){
        BGameMgr.SelectContinue.No^=1;
        BGameMgr.SelectContinue.Wt=0;
    }
    SpData.No       = BupeAnmTable[BGameMgr.SelectContinue.No]; //インデックス番号
    SpData.PosX     = 68+12;                                    //X位置
    SpData.PosY     = 73+34;                                    //Y位置
    SpData.PosZ     = PRIORITY_EVENT_MENU-10;                       //優先順位
    SpData.ScaleX   = SCALE10;                                  //スケールX
    SpData.ScaleY   = SCALE10;                                  //スケールY
    SpData.Rotate   = ROTATE000;                                //回転角
    SpData.Reverse  = NOREVERS;                                 //反転コード
    DrawSprite( &SpData );                                      //スプライト描画

    //プレート
    SpData.No       = BAND_CHAR_EVENT_SELECT_CONTINUE_PLATE;    //インデックス番号
    SpData.PosX     = 68;                                       //X位置
    SpData.PosY     = 73;                                       //Y位置
    SpData.PosZ     = PRIORITY_EVENT_MENU;                      //優先順位
    SpData.ScaleX   = SCALE10;                                  //スケールX
    SpData.ScaleY   = SCALE10;                                  //スケールY
    SpData.Rotate   = ROTATE000;                                //回転角
    SpData.Reverse  = NOREVERS;                                 //反転コード
    DrawSprite( &SpData );                                      //スプライト描画

    //えらぶ
    SpData.No       = BAND_CHAR_EVENT_SELECT_CONTINUE_ERABU;    //インデックス番号
    SpData.PosX     = (320-130)/2;                              //X位置
    SpData.PosY     = 206;                                      //Y位置
    SpData.PosZ     = PRIORITY_EVENT_MENU-1;                    //優先順位
    SpData.ScaleX   = SCALE10;                                  //スケールX
    SpData.ScaleY   = SCALE10;                                  //スケールY
    SpData.Rotate   = ROTATE000;                                //回転角
    SpData.Reverse  = NOREVERS;                                 //反転コード
    DrawSprite( &SpData );                                      //スプライト描画

    //けってい
    SpData.No       = BAND_CHAR_EVENT_SELECT_CONTINUE_KETEI;    //インデックス番号
    SpData.PosX     = (320-130)/2+78;                           //X位置
    SpData.PosY     = 206;                                      //Y位置
    SpData.PosZ     = PRIORITY_EVENT_MENU-1;                    //優先順位
    SpData.ScaleX   = SCALE10;                                  //スケールX
    SpData.ScaleY   = SCALE10;                                  //スケールY
    SpData.Rotate   = ROTATE000;                                //回転角
    SpData.Reverse  = NOREVERS;                                 //反転コード
    DrawSprite( &SpData );                                      //スプライト描画

    return o_ret;
}





#ifdef __DEBUG_BAND__

//-----------------------------------------------------------------------------
//  関数名 :DebugGameSpriteTask
//  機能   :ゲームスプライトデバッグ
//  注意   :なし
//-----------------------------------------------------------------------------
static int DebugGameSpriteTask(TASK* ip_task)
{
    static int SpIndex;
    static int SpEntryNum;
    static int Counter;
    static int FlushFlag;

    SPRITE_DATA SpData;


    switch(ip_task->mode)
    {
        case TASK_MODE_INIT:
            ip_task->mode = TASK_MODE_MAIN;

            //----texture read sram -> vram
            if((file_read(BandGameTextureFile[0].fn,LoadAddress)) == -1)
            {//read error
                return FALSE;
            }

            //----texture init
            TexInit( BAND_GAME_TIM_NUM, &BandGameTextureImage[BAND_GAME_TIM_POS] );
            TimImgData = BandGameTextureImage;

            //----開放
            ReleaseSprite();

            //----ゲーム用スプライト登録
            EntrySprite( BandGameSpriteData );

            // フェードINます
            GameMgr.FadeFlag    = FadeIn;

            SpIndex     = 0;
            SpEntryNum  = GetEntrySpriteNum();
            Counter     = 0;
            FlushFlag   = 0;

            break;
        case TASK_MODE_MAIN:

            if( JstPad & PADLdown ){
                SpIndex++;
            if(SpIndex > SpEntryNum-1) SpIndex = 0;
            }else
            if( JstPad & PADLup ){
                SpIndex--;
                if( SpIndex < 0 ) SpIndex = SpEntryNum-1;
            }else{
                
            }

            if(JstPad & PADRright)
            {
                FlushFlag^=1;
            }
            if(FlushFlag)   GsSortBoxFill(&BoxDataBlack, &Wot[active], 4);
            else            GsSortBoxFill(&BoxDataWhite, &Wot[active], 4);

            SpData.No       = SpIndex;                                          //インデックス番号
            SpData.PosX     = (320 - BandGameSpriteData[SpIndex].Width)  / 2;   //X位置
            SpData.PosY     = (240 - BandGameSpriteData[SpIndex].Height) / 2;   //Y位置
            SpData.PosZ     = 10;                                               //優先順位
            SpData.ScaleX   = SCALE10;                                          //スケールX
            SpData.ScaleY   = SCALE10;                                          //スケールY
            SpData.Rotate   = ROTATE000;                                        //回転角
            SpData.Reverse  = NOREVERS;                                         //反転コード
            DrawSprite( &SpData );                                              //スプライト描画

            //info
            FntPrint("SNO=%d/%d\n", SpIndex,SpEntryNum-1 );
            FntPrint("OfX=%d\n",    BandGameSpriteData[SpIndex].OffSetX );      //TIMの中のスプライト左上開始X位置
            FntPrint("OfY=%d\n",    BandGameSpriteData[SpIndex].OffSetY );      //TIMの中のスプライト左上開始Y位置
            FntPrint("W__=%d\n",    BandGameSpriteData[SpIndex].Width   );      //TIMの中のテクスチャの幅
            FntPrint("H__=%d\n",    BandGameSpriteData[SpIndex].Height  );      //TIMの中のテクスチャの高さ
            FntPrint("PNO=%d\n",    BandGameSpriteData[SpIndex].PaletteNo );    //TIMの中のテクスチャパレット番号
            FntPrint("CNT=%d\n",    ++Counter );

            break;
        case TASK_MODE_EXIT:
            //自分を削除
            ExitTask(ip_task->id);
            break;
        default:
            break;
    }

    return TRUE;
}



//-----------------------------------------------------------------------------
//  関数名 :DebugEventSpriteTask
//  機能   :イベントスプライトデバッグ
//  注意   :なし
//-----------------------------------------------------------------------------
static int DebugEventSpriteTask(TASK* ip_task)
{
    static int SpIndex;
    static int SpEntryNum;
    static int Counter;
    static int FlushFlag;

    SPRITE_DATA SpData;


    switch(ip_task->mode)
    {
        case TASK_MODE_INIT:
            ip_task->mode = TASK_MODE_MAIN;

            if((file_read(BandEventTextureFile[0].fn,LoadAddress)) == -1)
            {//read error
                return FALSE;
            }

            TexInit( BAND_EVENT_TIM_NUM, &BandEventTextureImage[BAND_EVENT_TIM_POS] );
            TimImgData = BandEventTextureImage;

            //開放
            ReleaseSprite();

            //イベントテクスチャ登録
            EntrySprite( BandEventSpriteData );

            // フェードINます
            GameMgr.FadeFlag    = FadeIn;

            SpIndex     = 0;
            SpEntryNum  = GetEntrySpriteNum();
            Counter     = 0;
            FlushFlag   = 0;

            break;
        case TASK_MODE_MAIN:

            if( JstPad & PADLdown ){
                SpIndex++;
            if(SpIndex > SpEntryNum-1) SpIndex = 0;
            }else
            if( JstPad & PADLup ){
                SpIndex--;
                if( SpIndex < 0 ) SpIndex = SpEntryNum-1;
            }else{
                
            }

            if(JstPad & PADRright)
            {
                FlushFlag^=1;
            }
            if(FlushFlag)   GsSortBoxFill(&BoxDataBlack, &Wot[active], 4);
            else            GsSortBoxFill(&BoxDataWhite, &Wot[active], 4);

            SpData.No       = SpIndex;                                          //インデックス番号
            SpData.PosX     = (320 - BandEventSpriteData[SpIndex].Width)  / 2;  //X位置
            SpData.PosY     = (240 - BandEventSpriteData[SpIndex].Height) / 2;  //Y位置
            SpData.PosZ     = 10;                                               //優先順位
            SpData.ScaleX   = SCALE10;                                          //スケールX
            SpData.ScaleY   = SCALE10;                                          //スケールY
            SpData.Rotate   = ROTATE000;                                        //回転角
            SpData.Reverse  = NOREVERS;                                         //反転コード
            DrawSprite( &SpData );                                              //スプライト描画

            //info
            FntPrint("SNO=%d/%d\n", SpIndex,SpEntryNum-1 );
            FntPrint("OfX=%d\n",    BandEventSpriteData[SpIndex].OffSetX );     //TIMの中のスプライト左上開始X位置
            FntPrint("OfY=%d\n",    BandEventSpriteData[SpIndex].OffSetY );     //TIMの中のスプライト左上開始Y位置
            FntPrint("W__=%d\n",    BandEventSpriteData[SpIndex].Width   );     //TIMの中のテクスチャの幅
            FntPrint("H__=%d\n",    BandEventSpriteData[SpIndex].Height  );     //TIMの中のテクスチャの高さ
            FntPrint("PNO=%d\n",    BandEventSpriteData[SpIndex].PaletteNo );   //TIMの中のテクスチャパレット番号
            FntPrint("CNT=%d\n",    ++Counter );

            break;
        case TASK_MODE_EXIT:
            //自分を削除
            ExitTask(ip_task->id);
            break;
        default:
            break;
    }

    return TRUE;
}

#endif


//-----------------------------------------------------------------------------
// end of BAND.C
//-----------------------------------------------------------------------------