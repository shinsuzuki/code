//-----------------------------------------------------------------------------
// THOU.C
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
#include <libsnd.h>

#include "COMMON.H"
#include "SYSTEM.H"
#include "SOUND.H"
#include "KAZU.H"
#include "SPMGR.H"
#include "TASKMGR.H"
#include "SPCONT.H"
#include "THOU.H"
//-----------------------------------------------------------------------------
//  define
//-----------------------------------------------------------------------------
//----debug sw「デバッグ時はコメントを外してください」
//  #define __DEBUG_THOU__
//  #define __DEBUG_THOU_TIME__

//  dSoundStatus
//  #define DslStatSeek         <-シーク中      /* seeking */
//  #define DslStatRead         <-再生中        /* reading data sectors */
//  #define DslStatShellOpen    <-              /* once shell open */
//  #define DslStatSeekError    <-              /* seek error detected */
//  #define DslStatStandby      <-再生終了      /* spindle motor rotating */
//  #define DslStatError        <-              /* command error detected */

//テクスチャー枚数と位置
#define THOU_GAME_TIM_POS 0 + 4
#define THOU_GAME_TIM_NUM 9

#define THOU_EVENT_TIM_POS 0 + 4
#define THOU_EVENT_TIM_NUM 5
//----------------------------------------------------------------------------- TIM位置
//----システム部
#define TIM_POS_THOU_EVENT_FONT 0  //選択処理テクスチャ
#define TIM_POS_THOU_EVENT_YORNO 1 //選択処理テクスチャ

//---- ゲーム部
#define TIM_POS_THOU_GAME_S1_01 0 + 4
#define TIM_POS_THOU_GAME_S1_02 1 + 4
#define TIM_POS_THOU_GAME_S1_03 2 + 4
#define TIM_POS_THOU_GAME_S1_04_A 3 + 4
#define TIM_POS_THOU_GAME_S1_04_B 4 + 4
#define TIM_POS_THOU_GAME_S1_04_C 5 + 4
#define TIM_POS_THOU_GAME_S1_04_D 6 + 4
#define TIM_POS_THOU_GAME_S1_05_A 7 + 4
#define TIM_POS_THOU_GAME_S1_05_B 8 + 4

//---- イベント部
#define TIM_POS_THOU_EVENT_C2_01_A 0 + 4
#define TIM_POS_THOU_EVENT_C2_01_B 1 + 4
#define TIM_POS_THOU_EVENT_C2_02_A 2 + 4
#define TIM_POS_THOU_EVENT_C2_02_B 3 + 4
#define TIM_POS_THOU_EVENT_C2_02_C 4 + 4

//-----------------------------------------------------------------------------
// ■キャラ番号
//-----------------------------------------------------------------------------
//---- ゲーム部スプライト番号
#define THOU_CHAR_GAME_BASS 0                    //バス反転アリ
#define THOU_CHAR_GAME_TRAIN 1                   //電車
#define THOU_CHAR_GAME_TAXI 2                    //タクシー反転アリ
#define THOU_CHAR_GAME_BASS_STATION_00 3         //バス停パレチェンあり
#define THOU_CHAR_GAME_TAXI_STATION_00 4         //タクシー乗り場パレチェンあり
#define THOU_CHAR_GAME_TRAIN_STATION 5           //駅
#define THOU_CHAR_GAME_TRAIN_STATION_PLATE_00 6  //駅看板パレチェンあり
#define THOU_CHAR_GAME_SCORE_PLATE 7             //得点プレート
#define THOU_CHAR_GAME_VISITOR_NUM_001 8         //流れる人々1人
#define THOU_CHAR_GAME_VISITOR_NUM_010 9         //流れる人々10人
#define THOU_CHAR_GAME_VISITOR_NUM_100 10        //流れる人々100人
#define THOU_CHAR_GAME_HISCORE_NUM_00 11         //最高記録用数字０
#define THOU_CHAR_GAME_HISCORE_NUM_01 12         //最高記録用数字１
#define THOU_CHAR_GAME_HISCORE_NUM_02 13         //最高記録用数字２
#define THOU_CHAR_GAME_HISCORE_NUM_03 14         //最高記録用数字３
#define THOU_CHAR_GAME_HISCORE_NUM_04 15         //最高記録用数字４
#define THOU_CHAR_GAME_HISCORE_NUM_05 16         //最高記録用数字５
#define THOU_CHAR_GAME_HISCORE_NUM_06 17         //最高記録用数字６
#define THOU_CHAR_GAME_HISCORE_NUM_07 18         //最高記録用数字７
#define THOU_CHAR_GAME_HISCORE_NUM_08 19         //最高記録用数字８
#define THOU_CHAR_GAME_HISCORE_NUM_09 20         //最高記録用数字９
#define THOU_CHAR_GAME_COUNTER_NUM_00 21         //得点用数字０
#define THOU_CHAR_GAME_COUNTER_NUM_01 22         //得点用数字１
#define THOU_CHAR_GAME_COUNTER_NUM_02 23         //得点用数字２
#define THOU_CHAR_GAME_COUNTER_NUM_03 24         //得点用数字３
#define THOU_CHAR_GAME_COUNTER_NUM_04 25         //得点用数字４
#define THOU_CHAR_GAME_COUNTER_NUM_05 26         //得点用数字５
#define THOU_CHAR_GAME_COUNTER_NUM_06 27         //得点用数字６
#define THOU_CHAR_GAME_COUNTER_NUM_07 28         //得点用数字７
#define THOU_CHAR_GAME_COUNTER_NUM_08 29         //得点用数字８
#define THOU_CHAR_GAME_COUNTER_NUM_09 30         //得点用数字９
#define THOU_CHAR_GAME_BASS_STATION_01 31        //バス停パレチェン
#define THOU_CHAR_GAME_TAXI_STATION_01 32        //タクシー乗り場パレチェン
#define THOU_CHAR_GAME_TRAIN_STATION_PLATE_01 33 //駅看板パレチェン
#define THOU_CHAR_GAME_WINDOW_SCENE_00 34        //時間を表す風景0
#define THOU_CHAR_GAME_WINDOW_SCENE_01 35        //時間を表す風景1
#define THOU_CHAR_GAME_WINDOW_SCENE_02 36        //時間を表す風景2
#define THOU_CHAR_GAME_WINDOW_SCENE_03 37        //時間を表す風景3
#define THOU_CHAR_GAME_WINDOW_SCENE_04 38        //時間を表す風景4
#define THOU_CHAR_GAME_WINDOW_SCENE_05 39        //時間を表す風景5
#define THOU_CHAR_GAME_WINDOW_SCENE_06 40        //時間を表す風景6
#define THOU_CHAR_GAME_WINDOW_SCENE_07 41        //時間を表す風景7
#define THOU_CHAR_GAME_WINDOW_SCENE_08 42        //時間を表す風景8
#define THOU_CHAR_GAME_GAKUDANIN_FUUSEN_B_00 43  //1000人到達時に出る演奏団
#define THOU_CHAR_GAME_GAKUDANIN_FUUSEN_B_01 44  //1000人到達時に出る演奏団
#define THOU_CHAR_GAME_GAKUDANIN_HATA_T_00 45    //1000人到達時に出る演奏団
#define THOU_CHAR_GAME_GAKUDANIN_HATA_T_01 46    //1000人到達時に出る演奏団
#define THOU_CHAR_GAME_GAKUDANIN_HATA_Y_00 47    //1000人到達時に出る演奏団
#define THOU_CHAR_GAME_GAKUDANIN_HATA_Y_01 48    //1000人到達時に出る演奏団
#define THOU_CHAR_GAME_DANTYOU_00 49             //1000人到達時に出る団長１
#define THOU_CHAR_GAME_DANTYOU_01 50             //1000人到達時に出る団長２
#define THOU_CHAR_GAME_GAKUDANIN_FUUSEN_O_00 51  //1000人到達時に出る演奏団　《パレットチェンジ》
#define THOU_CHAR_GAME_GAKUDANIN_FUUSEN_O_01 52  //1000人到達時に出る演奏団　《パレットチェンジ》
#define THOU_CHAR_GAME_LION_00 53                //先導ライオン.旗振り１
#define THOU_CHAR_GAME_LION_01 54                //先導ライオン.旗振り２
#define THOU_CHAR_GAME_LION_02 55                //先導ライオン.時間切れ振り向き
#define THOU_CHAR_GAME_LION_03 56                //先導ライオン.走り１
#define THOU_CHAR_GAME_LION_04 57                //先導ライオン.走り２
#define THOU_CHAR_GAME_BIG_LION_00 58            //ライオンの挨拶　ゲーム前演出１
#define THOU_CHAR_GAME_BIG_LION_01 59            //ライオンの挨拶　ゲーム前演出２
#define THOU_CHAR_GAME_BIG_LION_02 60            //ライオンの走り　ゲーム前演出１
#define THOU_CHAR_GAME_BIG_LION_03 61            //ライオンの走り　ゲーム前演出２
#define THOU_CHAR_GAME_BG_00 62                  //ゲーム背景
#define THOU_CHAR_GAME_BG_01 63                  //ゲーム背景

//---- イベント部スプライト番号
#define THOU_CHAR_EVENT_CLEAR_00 0                    //１０００人到達時クリア演出背景
#define THOU_CHAR_EVENT_CLEAR_01 1                    //１０００人到達時クリア演出背景
#define THOU_CHAR_EVENT_CLEAR_02 2                    //手を振ります。
#define THOU_CHAR_EVENT_FALSE_00 3                    //１０００人以下クリア演出背景
#define THOU_CHAR_EVENT_FALSE_01 4                    //１０００人以下時クリア演出背景
#define THOU_CHAR_EVENT_FALSE_02 5                    //手を振ります。
#define THOU_CHAR_EVENT_PLATE_00 6                    //得点プレート０
#define THOU_CHAR_EVENT_PLATE_01 7                    //得点プレート１
#define THOU_CHAR_EVENT_PLATE_NUM_00 8                //プレート用数字０
#define THOU_CHAR_EVENT_PLATE_NUM_01 9                //プレート用数字１
#define THOU_CHAR_EVENT_PLATE_NUM_02 10               //プレート用数字２
#define THOU_CHAR_EVENT_PLATE_NUM_03 11               //プレート用数字３
#define THOU_CHAR_EVENT_PLATE_NUM_04 12               //プレート用数字４
#define THOU_CHAR_EVENT_PLATE_NUM_05 13               //プレート用数字５
#define THOU_CHAR_EVENT_PLATE_NUM_06 14               //プレート用数字６
#define THOU_CHAR_EVENT_PLATE_NUM_07 15               //プレート用数字７
#define THOU_CHAR_EVENT_PLATE_NUM_08 16               //プレート用数字８
#define THOU_CHAR_EVENT_PLATE_NUM_09 17               //プレート用数字９
#define THOU_CHAR_EVENT_SELECT_CONTINUE_PLATE 18      //プレート
#define THOU_CHAR_EVENT_SELECT_CONTINUE_YES_DARK 19   //非選択・はい 74,57
#define THOU_CHAR_EVENT_SELECT_CONTINUE_NO_DARK 20    //非選択・いいえ 126,57
#define THOU_CHAR_EVENT_SELECT_CONTINUE_YES_LIGHT 21  //選択・はい 72,57
#define THOU_CHAR_EVENT_SELECT_CONTINUE_NO_LIGHT 22   //選択・いいえ 126,57
#define THOU_CHAR_EVENT_SELECT_CONTINUE_BUPE_00 23    //プーぺ１
#define THOU_CHAR_EVENT_SELECT_CONTINUE_BUPE_01 24    //プーぺ２
#define THOU_CHAR_EVENT_SELECT_CONTINUE_RETRY_H 25    //もういちど
#define THOU_CHAR_EVENT_SELECT_CONTINUE_END_H 26      //おわり
#define THOU_CHAR_EVENT_SELECT_CONTINUE_CONTINUE_H 27 //つづけ
#define THOU_CHAR_EVENT_SELECT_CONTINUE_CURSOR 28     //指カーソル
#define THOU_CHAR_EVENT_SELECT_CONTINUE_ERABU 29      //えらぶ
#define THOU_CHAR_EVENT_SELECT_CONTINUE_KETEI 30      //けってい
#define THOU_CHAR_EVENT_SELECT_CONTINUE_MENU 31       //めにゅー

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
extern u_long pad;
extern u_long NewPad;
extern u_long OldPad;
extern u_long JstPad;
extern u_long WorkPad;

//SYSTEM
extern u_long font_image[];
extern u_long YorN_image[];
extern u_long name_image[];
extern u_long MMENU_image[];
extern u_long font_clut[];
extern u_long YorN_clut[];
extern u_long name_clut[];
extern u_long MMENU_clut[];

//GAME
extern u_long S1_01_image[];
extern u_long S1_01_clut[];
extern u_long S1_02_image[];
extern u_long S1_02_clut[];
extern u_long S1_03_image[];
extern u_long S1_03_clut[];
extern u_long S1_04_A_image[];
extern u_long S1_04_A_clut[];
extern u_long S1_04_B_image[];
extern u_long S1_04_B_clut[];
extern u_long S1_04_C_image[];
extern u_long S1_04_C_clut[];
extern u_long S1_04_D_image[];
extern u_long S1_04_D_clut[];
extern u_long S1_05_A_image[];
extern u_long S1_05_A_clut[];
extern u_long S1_05_B_image[];
extern u_long S1_05_B_clut[];

//EVENT
extern u_long C2_01_A_image[];
extern u_long C2_01_A_clut[];
extern u_long C2_01_B_image[];
extern u_long C2_01_B_clut[];
extern u_long C2_02_A_image[];
extern u_long C2_02_A_clut[];
extern u_long C2_02_B_image[];
extern u_long C2_02_B_clut[];
extern u_long C2_02_C_image[];
extern u_long C2_02_C_clut[];
extern u_long help_00_image[];
extern u_long help_00_clut[];

extern int active; /* アクティブ(でない）描画領域 */
extern GsOT Wot[2];
static GsBOXF Box;
static GsBOXF BoxDataBlack[] = {0x00000000, 0, 0, 320, 240, 0x00, 0x00, 0x00};
static GsBOXF BoxDataWhite[] = {0x00000000, 0, 0, 320, 240, 0xFF, 0xFF, 0xFF};

//-----------------------------------------------------------------------------
//  variable
//-----------------------------------------------------------------------------
//------------------------------------------ロードファイル名
//----GAME
static TIMD ThouGameTextureFile[] = {
    //  デモタイトル名、    BINファイル名
    {"RCUBE3", "\\TIM\\THOUGD.B;1"},
};

//----EVENT
static TIMD ThouEventTextureFile[] = {
    //  デモタイトル名、    BINファイル名
    {"RCUBE2", "\\TIM\\THOUED.B;1"},
};

//------------------------------------------テクスチャデータ
//----GAME
static GsIMAGE ThouGameTextureImage[] =
    {
        //                  tpos        size        image               pos         size        clut
        //-------------------------------------------------------------------------------------------------------
        {TIM_COLOR_16, 384, 0, 64, 256, font_image, 16, 480, 16, 6, font_clut},
        {TIM_COLOR_16, 448, 0, 64, 256, YorN_image, 0, 480, 16, 16, YorN_clut},
        {TIM_COLOR_16, 512, 0, 64, 256, help_00_image, 0, 496, 16, 2, help_00_clut},
        {TIM_COLOR_16, 320, 0, 64, 256, MMENU_image, 16, 489, 16, 7, MMENU_clut},
        //-------------------------------------------------------------------------------------------------------
        {TIM_COLOR_16, 576, 0, 64, 256, S1_01_image, 144, 480, 16, 11, S1_01_clut},
        {TIM_COLOR_16, 896, 0, 64, 256, S1_02_image, 160, 480, 16, 12, S1_02_clut},
        {TIM_COLOR_16, 960, 0, 64, 256, S1_03_image, 112, 480, 16, 1, S1_03_clut},
        {TIM_COLOR_16, 640, 0, 64, 256, S1_04_A_image, 96, 480, 16, 1, S1_04_A_clut},
        {TIM_COLOR_16, 704, 0, 64, 256, S1_04_B_image, 80, 480, 16, 1, S1_04_B_clut},
        {TIM_COLOR_16, 704, 256, 64, 256, S1_04_C_image, 128, 480, 16, 1, S1_04_C_clut},
        {TIM_COLOR_16, 768, 256, 64, 256, S1_04_D_image, 64, 480, 16, 1, S1_04_D_clut},
        {TIM_COLOR_256, 576, 256, 128, 256, S1_05_A_image, 0, 510, 256, 1, S1_05_A_clut},
        {TIM_COLOR_256, 768, 0, 128, 256, S1_05_B_image, 0, 509, 256, 1, S1_05_B_clut},
};

//----EVENT
static GsIMAGE ThouEventTextureImage[] =
    {
        //  type            tpos        size        image               pos         size        clut
        //-------------------------------------------------------------------------------------------------------
        {TIM_COLOR_16, 384, 0, 64, 256, font_image, 16, 480, 16, 6, font_clut},
        {TIM_COLOR_16, 448, 0, 64, 256, YorN_image, 0, 480, 16, 16, YorN_clut},
        {TIM_COLOR_16, 512, 0, 64, 256, help_00_image, 0, 496, 16, 2, help_00_clut},
        {TIM_COLOR_16, 320, 0, 64, 256, MMENU_image, 16, 489, 16, 7, MMENU_clut},
        //-------------------------------------------------------------------------------------------------------
        {TIM_COLOR_256, 768, 0, 128, 256, C2_01_A_image, 0, 511, 256, 1, C2_01_A_clut},
        {TIM_COLOR_256, 896, 0, 128, 256, C2_01_B_image, 0, 510, 256, 1, C2_01_B_clut},
        {TIM_COLOR_256, 640, 0, 128, 256, C2_02_A_image, 0, 509, 256, 1, C2_02_A_clut},
        {TIM_COLOR_256, 704, 256, 128, 256, C2_02_B_image, 0, 508, 256, 1, C2_02_B_clut},
        {TIM_COLOR_16, 832, 256, 64, 256, C2_02_C_image, 64, 480, 16, 2, C2_02_C_clut},
};

//------------------------------------------スプライト登録データ
//----ENTRY GAME SPRITE
static ENTRY_SPRITE_DATA ThouGameSpriteData[] =
    {
        //-----------------------------------------------------------------------------------------
        //  TexNo                       TimLX   TimLY   Height  Width   PalNo
        //-----------------------------------------------------------------------------------------[C1_01.TIM]
        {TIM_POS_THOU_GAME_S1_01, 0, 0, 36, 58, 0},      //バス反転アリ
        {TIM_POS_THOU_GAME_S1_01, 60, 0, 38, 124, 0},    //電車
        {TIM_POS_THOU_GAME_S1_01, 186, 0, 26, 44, 0},    //タクシー反転アリ
        {TIM_POS_THOU_GAME_S1_01, 0, 40, 58, 26, 1},     //バス停パレチェンあり
        {TIM_POS_THOU_GAME_S1_01, 28, 40, 38, 42, 3},    //タクシー乗り場パレチェンあり
        {TIM_POS_THOU_GAME_S1_01, 72, 40, 42, 80, 5},    //駅
        {TIM_POS_THOU_GAME_S1_01, 154, 40, 28, 60, 6},   //駅看板パレチェンあり
        {TIM_POS_THOU_GAME_S1_01, 154, 72, 64, 96, 9},   //得点プレート
        {TIM_POS_THOU_GAME_S1_01, 28, 84, 14, 10, 8},    //流れる人々
        {TIM_POS_THOU_GAME_S1_01, 0, 100, 22, 38, 8},    //流れる人々
        {TIM_POS_THOU_GAME_S1_01, 40, 84, 78, 72, 8},    //流れる人々
        {TIM_POS_THOU_GAME_S1_01, 0, 168, 12, 12, 10},   //最高記録用数字
        {TIM_POS_THOU_GAME_S1_01, 16, 168, 12, 12, 10},  //最高記録用数字
        {TIM_POS_THOU_GAME_S1_01, 32, 168, 12, 12, 10},  //最高記録用数字
        {TIM_POS_THOU_GAME_S1_01, 48, 168, 12, 12, 10},  //最高記録用数字
        {TIM_POS_THOU_GAME_S1_01, 64, 168, 12, 12, 10},  //最高記録用数字
        {TIM_POS_THOU_GAME_S1_01, 80, 168, 12, 12, 10},  //最高記録用数字
        {TIM_POS_THOU_GAME_S1_01, 96, 168, 12, 12, 10},  //最高記録用数字
        {TIM_POS_THOU_GAME_S1_01, 112, 168, 12, 12, 10}, //最高記録用数字
        {TIM_POS_THOU_GAME_S1_01, 128, 168, 12, 12, 10}, //最高記録用数字
        {TIM_POS_THOU_GAME_S1_01, 144, 168, 12, 12, 10}, //最高記録用数字
        {TIM_POS_THOU_GAME_S1_01, 0, 184, 18, 18, 10},   //得点用数字
        {TIM_POS_THOU_GAME_S1_01, 20, 184, 18, 18, 10},  //得点用数字
        {TIM_POS_THOU_GAME_S1_01, 40, 184, 18, 18, 10},  //得点用数字
        {TIM_POS_THOU_GAME_S1_01, 60, 184, 18, 18, 10},  //得点用数字
        {TIM_POS_THOU_GAME_S1_01, 80, 184, 18, 18, 10},  //得点用数字
        {TIM_POS_THOU_GAME_S1_01, 100, 184, 18, 18, 10}, //得点用数字
        {TIM_POS_THOU_GAME_S1_01, 120, 184, 18, 18, 10}, //得点用数字
        {TIM_POS_THOU_GAME_S1_01, 140, 184, 18, 18, 10}, //得点用数字
        {TIM_POS_THOU_GAME_S1_01, 0, 204, 18, 18, 10},   //得点用数字
        {TIM_POS_THOU_GAME_S1_01, 20, 204, 18, 18, 10},  //得点用数字
        {TIM_POS_THOU_GAME_S1_01, 0, 40, 58, 26, 2},     //バス停パレチェン
        {TIM_POS_THOU_GAME_S1_01, 28, 40, 38, 42, 4},    //タクシー乗り場パレチェン
        {TIM_POS_THOU_GAME_S1_01, 154, 40, 28, 60, 7},   //駅看板パレチェン
        //-----------------------------------------------------------------------------------------[C1_02.TIM]
        {TIM_POS_THOU_GAME_S1_02, 0, 0, 48, 78, 0},      //時間を表す風景１
        {TIM_POS_THOU_GAME_S1_02, 80, 0, 48, 78, 1},     //時間を表す風景２
        {TIM_POS_THOU_GAME_S1_02, 160, 0, 48, 78, 2},    //時間を表す風景３
        {TIM_POS_THOU_GAME_S1_02, 0, 52, 48, 78, 3},     //時間を表す風景４
        {TIM_POS_THOU_GAME_S1_02, 80, 52, 48, 78, 4},    //時間を表す風景５
        {TIM_POS_THOU_GAME_S1_02, 160, 52, 48, 78, 5},   //時間を表す風景６
        {TIM_POS_THOU_GAME_S1_02, 0, 104, 48, 78, 6},    //時間を表す風景７
        {TIM_POS_THOU_GAME_S1_02, 80, 104, 48, 78, 7},   //時間を表す風景８
        {TIM_POS_THOU_GAME_S1_02, 160, 104, 48, 78, 8},  //時間を表す風景９
        {TIM_POS_THOU_GAME_S1_02, 0, 156, 34, 38, 9},    //1000人到達時に出る演奏団１
        {TIM_POS_THOU_GAME_S1_02, 40, 156, 34, 38, 9},   //1000人到達時に出る演奏団２
        {TIM_POS_THOU_GAME_S1_02, 80, 156, 34, 38, 9},   //1000人到達時に出る演奏団３
        {TIM_POS_THOU_GAME_S1_02, 120, 156, 34, 38, 9},  //1000人到達時に出る演奏団４
        {TIM_POS_THOU_GAME_S1_02, 160, 156, 34, 38, 11}, //1000人到達時に出る演奏団５
        {TIM_POS_THOU_GAME_S1_02, 200, 156, 34, 38, 11}, //1000人到達時に出る演奏団６
        {TIM_POS_THOU_GAME_S1_02, 0, 192, 42, 48, 9},    //1000人到達時に出る団長１
        {TIM_POS_THOU_GAME_S1_02, 50, 192, 42, 48, 9},   //1000人到達時に出る団長２
        {TIM_POS_THOU_GAME_S1_02, 0, 156, 34, 38, 10},   //1000人到達時に出る演奏団　《パレットチェンジ》
        {TIM_POS_THOU_GAME_S1_02, 40, 156, 34, 38, 10},  //1000人到達時に出る演奏団　《パレットチェンジ》
        //-----------------------------------------------------------------------------------------[C1_03.TIM]
        {TIM_POS_THOU_GAME_S1_03, 0, 0, 64, 64, 0},   //先導ライオン.旗振り１
        {TIM_POS_THOU_GAME_S1_03, 66, 0, 64, 64, 0},  //先導ライオン.旗振り２
        {TIM_POS_THOU_GAME_S1_03, 132, 0, 64, 64, 0}, //先導ライオン.時間切れ振り向き
        {TIM_POS_THOU_GAME_S1_03, 0, 66, 64, 64, 0},  //先導ライオン.走り１
        {TIM_POS_THOU_GAME_S1_03, 66, 66, 64, 64, 0}, //先導ライオン.走り２
        //-----------------------------------------------------------------------------------------[C1_04_A.TIM]
        {TIM_POS_THOU_GAME_S1_04_A, 0, 0, 200, 218, 0}, //ライオンの挨拶　ゲーム前演出１
        //-----------------------------------------------------------------------------------------[C1_04_B.TIM]
        {TIM_POS_THOU_GAME_S1_04_B, 0, 0, 200, 218, 0}, //ライオンの挨拶　ゲーム前演出２
        //-----------------------------------------------------------------------------------------[C1_04_C.TIM]
        {TIM_POS_THOU_GAME_S1_04_C, 0, 0, 200, 218, 0}, //ライオンの走り　ゲーム前演出１
        //-----------------------------------------------------------------------------------------[C1_04_D.TIM]
        {TIM_POS_THOU_GAME_S1_04_D, 0, 0, 200, 218, 0}, //ライオンの走り　ゲーム前演出２
        //-----------------------------------------------------------------------------------------[C1_05_A.TIM]
        {TIM_POS_THOU_GAME_S1_05_A, 0, 0, 240, 256, 0}, //ゲーム背景
        //-----------------------------------------------------------------------------------------[C1_05_B.TIM]
        {TIM_POS_THOU_GAME_S1_05_B, 0, 0, 240, 64, 0}, //ゲーム背景
        //-----------------------------------------------------------------------------------------
        {ENTRY_SPRITE_DATA_END, 0, 0, 0, 0, 0} // データエンド
};

//----ENTRY EVENT SPRITE
static ENTRY_SPRITE_DATA ThouEventSpriteData[] =
    {
        //-----------------------------------------------------------------------------------------
        //  TexNo                           TimLX   TimLY   Height  Width   PalNo
        //-----------------------------------------------------------------------------------------[C2_01_A.TIM]
        {TIM_POS_THOU_EVENT_C2_01_A, 0, 0, 240, 256, 0}, //１０００人到達時クリア演出背景
        //-----------------------------------------------------------------------------------------[C2_01_B.TIM]
        {TIM_POS_THOU_EVENT_C2_01_B, 0, 0, 240, 64, 0}, //１０００人到達時クリア演出背景
        {TIM_POS_THOU_EVENT_C2_01_B, 68, 0, 88, 78, 0}, //手を振ります。
        //-----------------------------------------------------------------------------------------[C2_02_A.TIM]
        {TIM_POS_THOU_EVENT_C2_02_A, 0, 0, 240, 256, 0}, //１０００人以下クリア演出背景
        //-----------------------------------------------------------------------------------------[C2_02_B.TIM]
        {TIM_POS_THOU_EVENT_C2_02_B, 0, 0, 240, 64, 0}, //１０００人以下時クリア演出背景
        {TIM_POS_THOU_EVENT_C2_02_B, 68, 0, 92, 78, 0}, //手を振ります。
        //-----------------------------------------------------------------------------------------[C2_02_C.TIM]
        {TIM_POS_THOU_EVENT_C2_02_C, 0, 0, 88, 204, 0},    //得点プレート
        {TIM_POS_THOU_EVENT_C2_02_C, 0, 88, 88, 204, 0},   //
        {TIM_POS_THOU_EVENT_C2_02_C, 0, 176, 36, 26, 1},   //プレート用数字
        {TIM_POS_THOU_EVENT_C2_02_C, 28, 176, 36, 26, 1},  //
        {TIM_POS_THOU_EVENT_C2_02_C, 56, 176, 36, 26, 1},  //
        {TIM_POS_THOU_EVENT_C2_02_C, 84, 176, 36, 26, 1},  //
        {TIM_POS_THOU_EVENT_C2_02_C, 112, 176, 36, 26, 1}, //
        {TIM_POS_THOU_EVENT_C2_02_C, 140, 176, 36, 26, 1}, //
        {TIM_POS_THOU_EVENT_C2_02_C, 168, 176, 36, 26, 1}, //
        {TIM_POS_THOU_EVENT_C2_02_C, 196, 176, 36, 26, 1}, //
        {TIM_POS_THOU_EVENT_C2_02_C, 224, 176, 36, 26, 1}, //
        {TIM_POS_THOU_EVENT_C2_02_C, 0, 214, 36, 26, 1},   //
        //-----------------------------------------------------------------------------------------[YorNo.TIM]
        {TIM_POS_THOU_EVENT_YORNO, 0, 0, 115, 186, 0},   //プレート
        {TIM_POS_THOU_EVENT_YORNO, 0, 115, 40, 38, 1},   //非選択・はい 74,57
        {TIM_POS_THOU_EVENT_YORNO, 38, 115, 40, 44, 1},  //非選択・いいえ 126,57
        {TIM_POS_THOU_EVENT_YORNO, 82, 115, 40, 44, 2},  //選択・はい 72,57
        {TIM_POS_THOU_EVENT_YORNO, 126, 115, 40, 44, 2}, //選択・いいえ 126,57
        {TIM_POS_THOU_EVENT_YORNO, 186, 0, 69, 58, 3},   //プーぺ１
        {TIM_POS_THOU_EVENT_YORNO, 186, 69, 69, 58, 3},  //プーぺ２
        {TIM_POS_THOU_EVENT_YORNO, 0, 155, 14, 148, 4},  //もういちど
        {TIM_POS_THOU_EVENT_YORNO, 0, 170, 14, 148, 4},  //おわり
        {TIM_POS_THOU_EVENT_YORNO, 20, 20, 14, 148, 4},  //つづけ
        //-----------------------------------------------------------------------------------------[font.TIM]
        {TIM_POS_THOU_EVENT_FONT, 24, 200, 24, 26, 2},  //指カーソル
        {TIM_POS_THOU_EVENT_FONT, 0, 232, 15, 52, 4},   //えらぶ
        {TIM_POS_THOU_EVENT_FONT, 52, 232, 15, 52, 4},  //けってい
        {TIM_POS_THOU_EVENT_FONT, 104, 232, 15, 52, 4}, //めにゅー
        //-----------------------------------------------------------------------------------------
        {ENTRY_SPRITE_DATA_END, 0, 0, 0, 0, 0} // データエンド
};

//----スプライトテーブル
static int GameLionSpriteTable[] =
    {
        THOU_CHAR_GAME_LION_00, //先導ライオン.旗振り１
        THOU_CHAR_GAME_LION_01, //先導ライオン.旗振り２
        THOU_CHAR_GAME_LION_02, //先導ライオン.時間切れ振り向き
        THOU_CHAR_GAME_LION_02, //先導ライオン.時間切れ振り向き
        THOU_CHAR_GAME_LION_03, //先導ライオン.走り１
        THOU_CHAR_GAME_LION_04, //先導ライオン.走り２
};

//----基本位置
static LION_WAIT_POS GameLionWaitPosTable[] =
    {
        {134, 48},  //基本位置
        {216, 51},  //バス待ち
        {31, 31},   //タクシー待ち
        {189, 134}, //電車待ち
};

//----スコアスプライトテーブル
static int VisitorScoreSpriteTable[] =
    {
        THOU_CHAR_GAME_COUNTER_NUM_00,
        THOU_CHAR_GAME_COUNTER_NUM_01,
        THOU_CHAR_GAME_COUNTER_NUM_02,
        THOU_CHAR_GAME_COUNTER_NUM_03,
        THOU_CHAR_GAME_COUNTER_NUM_04,
        THOU_CHAR_GAME_COUNTER_NUM_05,
        THOU_CHAR_GAME_COUNTER_NUM_06,
        THOU_CHAR_GAME_COUNTER_NUM_07,
        THOU_CHAR_GAME_COUNTER_NUM_08,
        THOU_CHAR_GAME_COUNTER_NUM_09,
};

//----ハイスコアスプライトテーブル
static int HighScoreSpriteTable[] =
    {
        THOU_CHAR_GAME_HISCORE_NUM_00,
        THOU_CHAR_GAME_HISCORE_NUM_01,
        THOU_CHAR_GAME_HISCORE_NUM_02,
        THOU_CHAR_GAME_HISCORE_NUM_03,
        THOU_CHAR_GAME_HISCORE_NUM_04,
        THOU_CHAR_GAME_HISCORE_NUM_05,
        THOU_CHAR_GAME_HISCORE_NUM_06,
        THOU_CHAR_GAME_HISCORE_NUM_07,
        THOU_CHAR_GAME_HISCORE_NUM_08,
        THOU_CHAR_GAME_HISCORE_NUM_09,
};

//----残念スコアスプライトテーブル
static int FalseScoreSpriteTable[] = {
    THOU_CHAR_EVENT_PLATE_NUM_00,
    THOU_CHAR_EVENT_PLATE_NUM_01,
    THOU_CHAR_EVENT_PLATE_NUM_02,
    THOU_CHAR_EVENT_PLATE_NUM_03,
    THOU_CHAR_EVENT_PLATE_NUM_04,
    THOU_CHAR_EVENT_PLATE_NUM_05,
    THOU_CHAR_EVENT_PLATE_NUM_06,
    THOU_CHAR_EVENT_PLATE_NUM_07,
    THOU_CHAR_EVENT_PLATE_NUM_08,
    THOU_CHAR_EVENT_PLATE_NUM_09,
};

//----シーンスプライトテーブル
static int SceneSpriteTable[] =
    {
        34, //  THOU_CHAR_GAME_WINDOW_SCENE_00,
        35, //  THOU_CHAR_GAME_WINDOW_SCENE_01,
        36, //  THOU_CHAR_GAME_WINDOW_SCENE_02,
        37, //  THOU_CHAR_GAME_WINDOW_SCENE_03,
        38, //  THOU_CHAR_GAME_WINDOW_SCENE_04,
        39, //  THOU_CHAR_GAME_WINDOW_SCENE_05,
        40, //  THOU_CHAR_GAME_WINDOW_SCENE_06,
        41, //  THOU_CHAR_GAME_WINDOW_SCENE_07,
        42, //  THOU_CHAR_GAME_WINDOW_SCENE_08,
};

//----プレートテーブル
static int PlateSpriteTable[] = {
    THOU_CHAR_EVENT_PLATE_00,
    THOU_CHAR_EVENT_PLATE_01,
};

//----反転テーブル
static int ReverseTable[] = {
    NOREVERS,
    HREVERS,
};

//------------------------------------------ゲーム管理
static THOU_GAME TGameMgr;

//------------------------------------------------------------------------SCRIPT
//----初プレイデモ開始時
#define INIT_PLAY_DEMO_SCRIPT_BASE 0
#define INIT_PLAY_DEMO_SCRIPT_NUM 2
//----プレイ開始時
#define PLAY_START_SCRIPT_BASE 2
#define PLAY_START_SCRIPT_NUM 2
//----1000人達成－クリア
#define PLAY_CLEAR_SCRIPT_BASE 4
#define PLAY_CLEAR_SCRIPT_NUM 3
//----1000人達成できず－失敗１
#define PLAY_FALSE_1_SCRIPT_BASE 7
#define PLAY_FALSE_1_SCRIPT_NUM 1
//----1000人達成できず－失敗２
#define PLAY_FALSE_2_SCRIPT_BASE 8
#define PLAY_FALSE_2_SCRIPT_NUM 1
//----1000人達成できず－失敗　前回の値を更新した場合
#define PLAY_FALSE_UP_SCRIPT_BASE 9
#define PLAY_FALSE_UP_SCRIPT_NUM 1
//----ゲーム終了
#define PLAY_GAME_END_SCRIPT_BASE 10
#define PLAY_GAME_END_SCRIPT_NUM 1

//----スクリプト本体
static SCRIP_DATA ThouScript[] =
    {
        //----------------初プレイデモ団長
        {//やぁ、わたしは　プーペ。
         0,
         NamePlatePuupe,
         XA_FILE_THOU00,
         0,
         "初消音時０６やぁ、わたしは　プーペ。待１２０終"},
        {//パニポニナンバーズフェスティバルに、おきゃくさん　をいっぱい　いれよう！
         0,
         NamePlatePuupe,
         XA_FILE_THOU00,
         1,
         "初消音時０６パニポニナンバーズフェスティバルに、改おきゃくさんを　いっぱい　いれよう！待４００終"},
        //----------------プレイ開始時
        {//さっそく　やってきましたよ。
         0,
         NamePlatePuupe,
         XA_FILE_THOU00,
         3,
         "初消音時０６さっそく　やってきましたよ。待１２０終"},
        {//がんばろうね。
         0,
         NamePlatePuupe,
         XA_FILE_THOU00,
         2,
         "初消音時０６がんばろうね。待１２０終"},
        //----------------1000人達成－クリア
        {//せんにん、たっせい！　ありがとう。
         0,
         NamePlatePuupe,
         XA_FILE_THOU01,
         5,
         "初消音時０６１０００にん、たっせい！　ありがとう。待１５０終"},
        {//きみのおかげで、フェスティバルはちょうまんいん！
         0,
         NamePlatePuupe,
         XA_FILE_THOU01,
         7,
         "初消音時０６きみの　おかげで、フェスティバルは改ちょうまんいん！待２２０終"},
        {//つぎも、この　ちょうしで　がんばろう～！
         0,
         NamePlatePuupe,
         XA_FILE_THOU01,
         8,
         "初消音時０６つぎも、この　ちょうしで改がんばろう～！待２４０終"},
        //----------------1000人達成できず－失敗１
        {//さぁ、なんにん、はいったかな？
         0,
         NamePlatePuupe,
         XA_FILE_THOU01,
         2,
         "初消音時０６さぁ、なんにん、はいったかな？待２８０終"},
        //----------------1000人達成できず－失敗２
        {//つぎもがんばろう～
         0,
         NamePlatePuupe,
         XA_FILE_THOU01,
         3,
         "初消音時０６つぎもがんばろう～待２４０終"},
        //----------------1000人達成できず－失敗　前回の値を更新した場合
        {//おおっ！　いままでの　さいこうきろくですね。
         0,
         NamePlatePuupe,
         XA_FILE_THOU01,
         4,
         "初消音時０６おおっ！　いままでの　改さいこうきろくですね。待２４０終"},
        //----------------ゲーム終了
        {//きょうはこれでおしまいで～す。
         0,
         NamePlatePuupe,
         XA_FILE_THOU01,
         1,
         "初消音時０６きょうは　これで　おしまいで～す。待１８０終"},
};

//------------------------------------------------------------------------CALL_COUNT
static CALLCOUNT CallCountData[] =
    {
        {1, {XA_FILE_YOMI01, 0}, {-1, -1}},              //0
        {1, {XA_FILE_YOMI01, 1}, {-1, -1}},              //1
        {1, {XA_FILE_YOMI01, 2}, {-1, -1}},              //2
        {1, {XA_FILE_YOMI01, 3}, {-1, -1}},              //3
        {1, {XA_FILE_YOMI01, 4}, {-1, -1}},              //4
        {1, {XA_FILE_YOMI01, 5}, {-1, -1}},              //5
        {1, {XA_FILE_YOMI01, 6}, {-1, -1}},              //6
        {1, {XA_FILE_YOMI01, 7}, {-1, -1}},              //7
        {1, {XA_FILE_YOMI01, 8}, {-1, -1}},              //8
        {1, {XA_FILE_YOMI01, 9}, {-1, -1}},              //9
        {1, {XA_FILE_YOMI01, 10}, {-1, -1}},             //10
        {1, {XA_FILE_YOMI01, 11}, {-1, -1}},             //11
        {1, {XA_FILE_YOMI01, 12}, {-1, -1}},             //12
        {1, {XA_FILE_YOMI01, 13}, {-1, -1}},             //13
        {1, {XA_FILE_YOMI01, 14}, {-1, -1}},             //14
        {1, {XA_FILE_YOMI01, 15}, {-1, -1}},             //15
        {1, {XA_FILE_YOMI02, 0}, {-1, -1}},              //16
        {1, {XA_FILE_YOMI02, 1}, {-1, -1}},              //17
        {1, {XA_FILE_YOMI02, 2}, {-1, -1}},              //18
        {1, {XA_FILE_YOMI02, 3}, {-1, -1}},              //19
        {1, {XA_FILE_YOMI02, 4}, {-1, -1}},              //20
        {1, {XA_FILE_YOMI02, 5}, {-1, -1}},              //21
        {1, {XA_FILE_YOMI02, 6}, {-1, -1}},              //22
        {1, {XA_FILE_YOMI02, 7}, {-1, -1}},              //23
        {1, {XA_FILE_YOMI02, 8}, {-1, -1}},              //24
        {1, {XA_FILE_YOMI02, 9}, {-1, -1}},              //25
        {1, {XA_FILE_YOMI02, 10}, {-1, -1}},             //26
        {1, {XA_FILE_YOMI02, 11}, {-1, -1}},             //27
        {1, {XA_FILE_YOMI02, 12}, {-1, -1}},             //28
        {1, {XA_FILE_YOMI02, 13}, {-1, -1}},             //29
        {1, {XA_FILE_YOMI02, 14}, {-1, -1}},             //30
        {1, {XA_FILE_YOMI02, 15}, {-1, -1}},             //31
        {1, {XA_FILE_YOMI03, 0}, {-1, -1}},              //32
        {1, {XA_FILE_YOMI03, 1}, {-1, -1}},              //33
        {1, {XA_FILE_YOMI03, 2}, {-1, -1}},              //34
        {1, {XA_FILE_YOMI03, 3}, {-1, -1}},              //35
        {1, {XA_FILE_YOMI03, 4}, {-1, -1}},              //36
        {1, {XA_FILE_YOMI03, 5}, {-1, -1}},              //37
        {1, {XA_FILE_YOMI03, 6}, {-1, -1}},              //38
        {1, {XA_FILE_YOMI03, 7}, {-1, -1}},              //39
        {1, {XA_FILE_YOMI03, 8}, {-1, -1}},              //40
        {1, {XA_FILE_YOMI03, 9}, {-1, -1}},              //41
        {1, {XA_FILE_YOMI03, 10}, {-1, -1}},             //42
        {1, {XA_FILE_YOMI03, 11}, {-1, -1}},             //43
        {1, {XA_FILE_YOMI03, 12}, {-1, -1}},             //44
        {1, {XA_FILE_YOMI03, 13}, {-1, -1}},             //45
        {1, {XA_FILE_YOMI03, 14}, {-1, -1}},             //46
        {1, {XA_FILE_YOMI03, 15}, {-1, -1}},             //47
        {1, {XA_FILE_YOMI04, 0}, {-1, -1}},              //48
        {1, {XA_FILE_YOMI04, 1}, {-1, -1}},              //49
        {1, {XA_FILE_YOMI04, 2}, {-1, -1}},              //50
        {1, {XA_FILE_YOMI04, 3}, {-1, -1}},              //51
        {1, {XA_FILE_YOMI04, 4}, {-1, -1}},              //52
        {1, {XA_FILE_YOMI04, 5}, {-1, -1}},              //53
        {1, {XA_FILE_YOMI04, 6}, {-1, -1}},              //54
        {1, {XA_FILE_YOMI04, 7}, {-1, -1}},              //55
        {1, {XA_FILE_YOMI04, 8}, {-1, -1}},              //56
        {1, {XA_FILE_YOMI04, 9}, {-1, -1}},              //57
        {1, {XA_FILE_YOMI04, 10}, {-1, -1}},             //58
        {1, {XA_FILE_YOMI04, 11}, {-1, -1}},             //59
        {1, {XA_FILE_YOMI04, 12}, {-1, -1}},             //60
        {1, {XA_FILE_YOMI04, 13}, {-1, -1}},             //61
        {1, {XA_FILE_YOMI04, 14}, {-1, -1}},             //62
        {1, {XA_FILE_YOMI04, 15}, {-1, -1}},             //63
        {1, {XA_FILE_YOMI05, 0}, {-1, -1}},              //64
        {1, {XA_FILE_YOMI05, 1}, {-1, -1}},              //65
        {1, {XA_FILE_YOMI05, 2}, {-1, -1}},              //66
        {1, {XA_FILE_YOMI05, 3}, {-1, -1}},              //67
        {1, {XA_FILE_YOMI05, 4}, {-1, -1}},              //68
        {1, {XA_FILE_YOMI05, 5}, {-1, -1}},              //69
        {1, {XA_FILE_YOMI05, 6}, {-1, -1}},              //70
        {1, {XA_FILE_YOMI05, 7}, {-1, -1}},              //71
        {1, {XA_FILE_YOMI05, 8}, {-1, -1}},              //72
        {1, {XA_FILE_YOMI05, 9}, {-1, -1}},              //73
        {1, {XA_FILE_YOMI05, 10}, {-1, -1}},             //74
        {1, {XA_FILE_YOMI05, 11}, {-1, -1}},             //75
        {1, {XA_FILE_YOMI05, 12}, {-1, -1}},             //76
        {1, {XA_FILE_YOMI05, 13}, {-1, -1}},             //77
        {1, {XA_FILE_YOMI05, 14}, {-1, -1}},             //78
        {1, {XA_FILE_YOMI05, 15}, {-1, -1}},             //79
        {1, {XA_FILE_YOMI06, 0}, {-1, -1}},              //80
        {1, {XA_FILE_YOMI06, 1}, {-1, -1}},              //81
        {1, {XA_FILE_YOMI06, 2}, {-1, -1}},              //82
        {1, {XA_FILE_YOMI06, 3}, {-1, -1}},              //83
        {1, {XA_FILE_YOMI06, 4}, {-1, -1}},              //84
        {1, {XA_FILE_YOMI06, 5}, {-1, -1}},              //85
        {1, {XA_FILE_YOMI06, 6}, {-1, -1}},              //86
        {1, {XA_FILE_YOMI06, 7}, {-1, -1}},              //87
        {1, {XA_FILE_YOMI06, 8}, {-1, -1}},              //88
        {1, {XA_FILE_YOMI06, 9}, {-1, -1}},              //89
        {1, {XA_FILE_YOMI06, 10}, {-1, -1}},             //90
        {1, {XA_FILE_YOMI06, 11}, {-1, -1}},             //91
        {1, {XA_FILE_YOMI06, 12}, {-1, -1}},             //92
        {1, {XA_FILE_YOMI06, 13}, {-1, -1}},             //93
        {1, {XA_FILE_YOMI06, 14}, {-1, -1}},             //94
        {1, {XA_FILE_YOMI06, 15}, {-1, -1}},             //95
        {1, {XA_FILE_YOMI07, 0}, {-1, -1}},              //96
        {1, {XA_FILE_YOMI07, 1}, {-1, -1}},              //97
        {1, {XA_FILE_YOMI07, 2}, {-1, -1}},              //98
        {1, {XA_FILE_YOMI07, 3}, {-1, -1}},              //99
        {1, {XA_FILE_YOMI07, 4}, {-1, -1}},              //100
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI01, 1}},   //101
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI01, 2}},   //102
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI01, 3}},   //103
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI01, 4}},   //104
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI01, 5}},   //105
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI01, 6}},   //106
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI01, 7}},   //107
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI01, 8}},   //108
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI01, 9}},   //109
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI01, 10}},  //110
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI01, 11}},  //111
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI01, 12}},  //112
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI01, 13}},  //113
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI01, 14}},  //114
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI01, 15}},  //115
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI02, 0}},   //116
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI02, 1}},   //117
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI02, 2}},   //118
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI02, 3}},   //119
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI02, 4}},   //120
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI02, 5}},   //121
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI02, 6}},   //122
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI02, 7}},   //123
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI02, 8}},   //124
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI02, 9}},   //125
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI02, 10}},  //126
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI02, 11}},  //127
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI02, 12}},  //128
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI02, 13}},  //129
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI02, 14}},  //130
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI02, 15}},  //131
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI03, 0}},   //132
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI03, 1}},   //133
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI03, 2}},   //134
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI03, 3}},   //135
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI03, 4}},   //136
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI03, 5}},   //137
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI03, 6}},   //138
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI03, 7}},   //139
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI03, 8}},   //140
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI03, 9}},   //141
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI03, 10}},  //142
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI03, 11}},  //143
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI03, 12}},  //144
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI03, 13}},  //145
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI03, 14}},  //146
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI03, 15}},  //147
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI04, 0}},   //148
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI04, 1}},   //149
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI04, 2}},   //150
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI04, 3}},   //151
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI04, 4}},   //152
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI04, 5}},   //153
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI04, 6}},   //154
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI04, 7}},   //155
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI04, 8}},   //156
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI04, 9}},   //157
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI04, 10}},  //158
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI04, 11}},  //159
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI04, 12}},  //160
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI04, 13}},  //161
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI04, 14}},  //162
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI04, 15}},  //163
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI05, 0}},   //164
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI05, 1}},   //165
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI05, 2}},   //166
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI05, 3}},   //167
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI05, 4}},   //168
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI05, 5}},   //169
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI05, 6}},   //170
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI05, 7}},   //171
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI05, 8}},   //172
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI05, 9}},   //173
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI05, 10}},  //174
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI05, 11}},  //175
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI05, 12}},  //176
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI05, 13}},  //177
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI05, 14}},  //178
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI05, 15}},  //179
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI06, 0}},   //180
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI06, 1}},   //181
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI06, 2}},   //182
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI06, 3}},   //183
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI06, 4}},   //184
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI06, 5}},   //185
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI06, 6}},   //186
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI06, 7}},   //187
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI06, 8}},   //188
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI06, 9}},   //189
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI06, 10}},  //190
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI06, 11}},  //191
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI06, 12}},  //192
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI06, 13}},  //193
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI06, 14}},  //194
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI06, 15}},  //195
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI07, 0}},   //196
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI07, 1}},   //197
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI07, 2}},   //198
        {2, {XA_FILE_YOMI07, 4}, {XA_FILE_YOMI07, 3}},   //199
        {1, {XA_FILE_YOMI07, 5}, {-1, -1}},              //200
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI01, 1}},   //201
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI01, 2}},   //202
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI01, 3}},   //203
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI01, 4}},   //204
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI01, 5}},   //205
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI01, 6}},   //206
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI01, 7}},   //207
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI01, 8}},   //208
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI01, 9}},   //209
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI01, 10}},  //210
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI01, 11}},  //211
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI01, 12}},  //212
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI01, 13}},  //213
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI01, 14}},  //214
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI01, 15}},  //215
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI02, 0}},   //216
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI02, 1}},   //217
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI02, 2}},   //218
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI02, 3}},   //219
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI02, 4}},   //220
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI02, 5}},   //221
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI02, 6}},   //222
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI02, 7}},   //223
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI02, 8}},   //224
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI02, 9}},   //225
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI02, 10}},  //226
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI02, 11}},  //227
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI02, 12}},  //228
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI02, 13}},  //229
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI02, 14}},  //230
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI02, 15}},  //231
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI03, 0}},   //232
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI03, 1}},   //233
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI03, 2}},   //234
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI03, 3}},   //235
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI03, 4}},   //236
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI03, 5}},   //237
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI03, 6}},   //238
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI03, 7}},   //239
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI03, 8}},   //240
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI03, 9}},   //241
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI03, 10}},  //242
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI03, 11}},  //243
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI03, 12}},  //244
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI03, 13}},  //245
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI03, 14}},  //246
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI03, 15}},  //247
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI04, 0}},   //248
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI04, 1}},   //249
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI04, 2}},   //250
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI04, 3}},   //251
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI04, 4}},   //252
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI04, 5}},   //253
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI04, 6}},   //254
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI04, 7}},   //255
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI04, 8}},   //256
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI04, 9}},   //257
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI04, 10}},  //258
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI04, 11}},  //259
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI04, 12}},  //260
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI04, 13}},  //261
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI04, 14}},  //262
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI04, 15}},  //263
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI05, 0}},   //264
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI05, 1}},   //265
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI05, 2}},   //266
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI05, 3}},   //267
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI05, 4}},   //268
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI05, 5}},   //269
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI05, 6}},   //270
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI05, 7}},   //271
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI05, 8}},   //272
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI05, 9}},   //273
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI05, 10}},  //274
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI05, 11}},  //275
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI05, 12}},  //276
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI05, 13}},  //277
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI05, 14}},  //278
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI05, 15}},  //279
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI06, 0}},   //280
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI06, 1}},   //281
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI06, 2}},   //282
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI06, 3}},   //283
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI06, 4}},   //284
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI06, 5}},   //285
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI06, 6}},   //286
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI06, 7}},   //287
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI06, 8}},   //288
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI06, 9}},   //289
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI06, 10}},  //290
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI06, 11}},  //291
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI06, 12}},  //292
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI06, 13}},  //293
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI06, 14}},  //294
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI06, 15}},  //295
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI07, 0}},   //296
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI07, 1}},   //297
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI07, 2}},   //298
        {2, {XA_FILE_YOMI07, 5}, {XA_FILE_YOMI07, 3}},   //299
        {1, {XA_FILE_YOMI07, 6}, {-1, -1}},              //300
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI01, 1}},   //301
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI01, 2}},   //302
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI01, 3}},   //303
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI01, 4}},   //304
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI01, 5}},   //305
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI01, 6}},   //306
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI01, 7}},   //307
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI01, 8}},   //308
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI01, 9}},   //309
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI01, 10}},  //310
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI01, 11}},  //311
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI01, 12}},  //312
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI01, 13}},  //313
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI01, 14}},  //314
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI01, 15}},  //315
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI02, 0}},   //316
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI02, 1}},   //317
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI02, 2}},   //318
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI02, 3}},   //319
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI02, 4}},   //320
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI02, 5}},   //321
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI02, 6}},   //322
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI02, 7}},   //323
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI02, 8}},   //324
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI02, 9}},   //325
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI02, 10}},  //326
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI02, 11}},  //327
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI02, 12}},  //328
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI02, 13}},  //329
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI02, 14}},  //330
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI02, 15}},  //331
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI03, 0}},   //332
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI03, 1}},   //333
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI03, 2}},   //334
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI03, 3}},   //335
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI03, 4}},   //336
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI03, 5}},   //337
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI03, 6}},   //338
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI03, 7}},   //339
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI03, 8}},   //340
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI03, 9}},   //341
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI03, 10}},  //342
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI03, 11}},  //343
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI03, 12}},  //344
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI03, 13}},  //345
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI03, 14}},  //346
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI03, 15}},  //347
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI04, 0}},   //348
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI04, 1}},   //349
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI04, 2}},   //350
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI04, 3}},   //351
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI04, 4}},   //352
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI04, 5}},   //353
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI04, 6}},   //354
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI04, 7}},   //355
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI04, 8}},   //356
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI04, 9}},   //357
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI04, 10}},  //358
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI04, 11}},  //359
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI04, 12}},  //360
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI04, 13}},  //361
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI04, 14}},  //362
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI04, 15}},  //363
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI05, 0}},   //364
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI05, 1}},   //365
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI05, 2}},   //366
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI05, 3}},   //367
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI05, 4}},   //368
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI05, 5}},   //369
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI05, 6}},   //370
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI05, 7}},   //371
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI05, 8}},   //372
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI05, 9}},   //373
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI05, 10}},  //374
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI05, 11}},  //375
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI05, 12}},  //376
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI05, 13}},  //377
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI05, 14}},  //378
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI05, 15}},  //379
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI06, 0}},   //380
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI06, 1}},   //381
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI06, 2}},   //382
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI06, 3}},   //383
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI06, 4}},   //384
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI06, 5}},   //385
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI06, 6}},   //386
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI06, 7}},   //387
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI06, 8}},   //388
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI06, 9}},   //389
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI06, 10}},  //390
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI06, 11}},  //391
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI06, 12}},  //392
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI06, 13}},  //393
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI06, 14}},  //394
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI06, 15}},  //395
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI07, 0}},   //396
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI07, 1}},   //397
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI07, 2}},   //398
        {2, {XA_FILE_YOMI07, 6}, {XA_FILE_YOMI07, 3}},   //399
        {1, {XA_FILE_YOMI07, 7}, {-1, -1}},              //400
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI01, 1}},   //401
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI01, 2}},   //402
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI01, 3}},   //403
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI01, 4}},   //404
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI01, 5}},   //405
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI01, 6}},   //406
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI01, 7}},   //407
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI01, 8}},   //408
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI01, 9}},   //409
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI01, 10}},  //410
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI01, 11}},  //411
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI01, 12}},  //412
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI01, 13}},  //413
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI01, 14}},  //414
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI01, 15}},  //415
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI02, 0}},   //416
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI02, 1}},   //417
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI02, 2}},   //418
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI02, 3}},   //419
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI02, 4}},   //420
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI02, 5}},   //421
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI02, 6}},   //422
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI02, 7}},   //423
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI02, 8}},   //424
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI02, 9}},   //425
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI02, 10}},  //426
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI02, 11}},  //427
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI02, 12}},  //428
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI02, 13}},  //429
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI02, 14}},  //430
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI02, 15}},  //431
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI03, 0}},   //432
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI03, 1}},   //433
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI03, 2}},   //434
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI03, 3}},   //435
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI03, 4}},   //436
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI03, 5}},   //437
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI03, 6}},   //438
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI03, 7}},   //439
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI03, 8}},   //440
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI03, 9}},   //441
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI03, 10}},  //442
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI03, 11}},  //443
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI03, 12}},  //444
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI03, 13}},  //445
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI03, 14}},  //446
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI03, 15}},  //447
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI04, 0}},   //448
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI04, 1}},   //449
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI04, 2}},   //450
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI04, 3}},   //451
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI04, 4}},   //452
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI04, 5}},   //453
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI04, 6}},   //454
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI04, 7}},   //455
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI04, 8}},   //456
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI04, 9}},   //457
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI04, 10}},  //458
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI04, 11}},  //459
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI04, 12}},  //460
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI04, 13}},  //461
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI04, 14}},  //462
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI04, 15}},  //463
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI05, 0}},   //464
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI05, 1}},   //465
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI05, 2}},   //466
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI05, 3}},   //467
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI05, 4}},   //468
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI05, 5}},   //469
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI05, 6}},   //470
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI05, 7}},   //471
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI05, 8}},   //472
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI05, 9}},   //473
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI05, 10}},  //474
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI05, 11}},  //475
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI05, 12}},  //476
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI05, 13}},  //477
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI05, 14}},  //478
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI05, 15}},  //479
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI06, 0}},   //480
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI06, 1}},   //481
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI06, 2}},   //482
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI06, 3}},   //483
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI06, 4}},   //484
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI06, 5}},   //485
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI06, 6}},   //486
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI06, 7}},   //487
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI06, 8}},   //488
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI06, 9}},   //489
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI06, 10}},  //490
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI06, 11}},  //491
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI06, 12}},  //492
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI06, 13}},  //493
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI06, 14}},  //494
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI06, 15}},  //495
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI07, 0}},   //496
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI07, 1}},   //497
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI07, 2}},   //498
        {2, {XA_FILE_YOMI07, 7}, {XA_FILE_YOMI07, 3}},   //499
        {1, {XA_FILE_YOMI07, 8}, {-1, -1}},              //500
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI01, 1}},   //501
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI01, 2}},   //502
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI01, 3}},   //503
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI01, 4}},   //504
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI01, 5}},   //505
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI01, 6}},   //506
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI01, 7}},   //507
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI01, 8}},   //508
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI01, 9}},   //509
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI01, 10}},  //510
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI01, 11}},  //511
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI01, 12}},  //512
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI01, 13}},  //513
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI01, 14}},  //514
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI01, 15}},  //515
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI02, 0}},   //516
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI02, 1}},   //517
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI02, 2}},   //518
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI02, 3}},   //519
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI02, 4}},   //520
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI02, 5}},   //521
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI02, 6}},   //522
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI02, 7}},   //523
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI02, 8}},   //524
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI02, 9}},   //525
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI02, 10}},  //526
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI02, 11}},  //527
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI02, 12}},  //528
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI02, 13}},  //529
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI02, 14}},  //530
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI02, 15}},  //531
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI03, 0}},   //532
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI03, 1}},   //533
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI03, 2}},   //534
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI03, 3}},   //535
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI03, 4}},   //536
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI03, 5}},   //537
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI03, 6}},   //538
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI03, 7}},   //539
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI03, 8}},   //540
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI03, 9}},   //541
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI03, 10}},  //542
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI03, 11}},  //543
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI03, 12}},  //544
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI03, 13}},  //545
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI03, 14}},  //546
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI03, 15}},  //547
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI04, 0}},   //548
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI04, 1}},   //549
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI04, 2}},   //550
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI04, 3}},   //551
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI04, 4}},   //552
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI04, 5}},   //553
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI04, 6}},   //554
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI04, 7}},   //555
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI04, 8}},   //556
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI04, 9}},   //557
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI04, 10}},  //558
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI04, 11}},  //559
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI04, 12}},  //560
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI04, 13}},  //561
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI04, 14}},  //562
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI04, 15}},  //563
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI05, 0}},   //564
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI05, 1}},   //565
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI05, 2}},   //566
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI05, 3}},   //567
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI05, 4}},   //568
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI05, 5}},   //569
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI05, 6}},   //570
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI05, 7}},   //571
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI05, 8}},   //572
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI05, 9}},   //573
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI05, 10}},  //574
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI05, 11}},  //575
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI05, 12}},  //576
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI05, 13}},  //577
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI05, 14}},  //578
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI05, 15}},  //579
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI06, 0}},   //580
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI06, 1}},   //581
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI06, 2}},   //582
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI06, 3}},   //583
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI06, 4}},   //584
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI06, 5}},   //585
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI06, 6}},   //586
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI06, 7}},   //587
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI06, 8}},   //588
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI06, 9}},   //589
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI06, 10}},  //590
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI06, 11}},  //591
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI06, 12}},  //592
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI06, 13}},  //593
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI06, 14}},  //594
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI06, 15}},  //595
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI07, 0}},   //596
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI07, 1}},   //597
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI07, 2}},   //598
        {2, {XA_FILE_YOMI07, 8}, {XA_FILE_YOMI07, 3}},   //599
        {1, {XA_FILE_YOMI07, 9}, {-1, -1}},              //600
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI01, 1}},   //601
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI01, 2}},   //602
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI01, 3}},   //603
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI01, 4}},   //604
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI01, 5}},   //605
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI01, 6}},   //606
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI01, 7}},   //607
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI01, 8}},   //608
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI01, 9}},   //609
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI01, 10}},  //610
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI01, 11}},  //611
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI01, 12}},  //612
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI01, 13}},  //613
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI01, 14}},  //614
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI01, 15}},  //615
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI02, 0}},   //616
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI02, 1}},   //617
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI02, 2}},   //618
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI02, 3}},   //619
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI02, 4}},   //620
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI02, 5}},   //621
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI02, 6}},   //622
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI02, 7}},   //623
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI02, 8}},   //624
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI02, 9}},   //625
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI02, 10}},  //626
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI02, 11}},  //627
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI02, 12}},  //628
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI02, 13}},  //629
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI02, 14}},  //630
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI02, 15}},  //631
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI03, 0}},   //632
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI03, 1}},   //633
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI03, 2}},   //634
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI03, 3}},   //635
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI03, 4}},   //636
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI03, 5}},   //637
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI03, 6}},   //638
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI03, 7}},   //639
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI03, 8}},   //640
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI03, 9}},   //641
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI03, 10}},  //642
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI03, 11}},  //643
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI03, 12}},  //644
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI03, 13}},  //645
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI03, 14}},  //646
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI03, 15}},  //647
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI04, 0}},   //648
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI04, 1}},   //649
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI04, 2}},   //650
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI04, 3}},   //651
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI04, 4}},   //652
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI04, 5}},   //653
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI04, 6}},   //654
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI04, 7}},   //655
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI04, 8}},   //656
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI04, 9}},   //657
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI04, 10}},  //658
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI04, 11}},  //659
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI04, 12}},  //660
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI04, 13}},  //661
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI04, 14}},  //662
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI04, 15}},  //663
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI05, 0}},   //664
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI05, 1}},   //665
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI05, 2}},   //666
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI05, 3}},   //667
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI05, 4}},   //668
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI05, 5}},   //669
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI05, 6}},   //670
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI05, 7}},   //671
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI05, 8}},   //672
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI05, 9}},   //673
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI05, 10}},  //674
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI05, 11}},  //675
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI05, 12}},  //676
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI05, 13}},  //677
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI05, 14}},  //678
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI05, 15}},  //679
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI06, 0}},   //680
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI06, 1}},   //681
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI06, 2}},   //682
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI06, 3}},   //683
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI06, 4}},   //684
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI06, 5}},   //685
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI06, 6}},   //686
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI06, 7}},   //687
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI06, 8}},   //688
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI06, 9}},   //689
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI06, 10}},  //690
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI06, 11}},  //691
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI06, 12}},  //692
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI06, 13}},  //693
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI06, 14}},  //694
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI06, 15}},  //695
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI07, 0}},   //696
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI07, 1}},   //697
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI07, 2}},   //698
        {2, {XA_FILE_YOMI07, 9}, {XA_FILE_YOMI07, 3}},   //699
        {1, {XA_FILE_YOMI07, 10}, {-1, -1}},             //700
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI01, 1}},  //701
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI01, 2}},  //702
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI01, 3}},  //703
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI01, 4}},  //704
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI01, 5}},  //705
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI01, 6}},  //706
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI01, 7}},  //707
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI01, 8}},  //708
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI01, 9}},  //709
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI01, 10}}, //710
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI01, 11}}, //711
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI01, 12}}, //712
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI01, 13}}, //713
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI01, 14}}, //714
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI01, 15}}, //715
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI02, 0}},  //716
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI02, 1}},  //717
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI02, 2}},  //718
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI02, 3}},  //719
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI02, 4}},  //720
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI02, 5}},  //721
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI02, 6}},  //722
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI02, 7}},  //723
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI02, 8}},  //724
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI02, 9}},  //725
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI02, 10}}, //726
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI02, 11}}, //727
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI02, 12}}, //728
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI02, 13}}, //729
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI02, 14}}, //730
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI02, 15}}, //731
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI03, 0}},  //732
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI03, 1}},  //733
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI03, 2}},  //734
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI03, 3}},  //735
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI03, 4}},  //736
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI03, 5}},  //737
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI03, 6}},  //738
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI03, 7}},  //739
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI03, 8}},  //740
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI03, 9}},  //741
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI03, 10}}, //742
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI03, 11}}, //743
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI03, 12}}, //744
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI03, 13}}, //745
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI03, 14}}, //746
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI03, 15}}, //747
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI04, 0}},  //748
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI04, 1}},  //749
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI04, 2}},  //750
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI04, 3}},  //751
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI04, 4}},  //752
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI04, 5}},  //753
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI04, 6}},  //754
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI04, 7}},  //755
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI04, 8}},  //756
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI04, 9}},  //757
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI04, 10}}, //758
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI04, 11}}, //759
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI04, 12}}, //760
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI04, 13}}, //761
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI04, 14}}, //762
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI04, 15}}, //763
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI05, 0}},  //764
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI05, 1}},  //765
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI05, 2}},  //766
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI05, 3}},  //767
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI05, 4}},  //768
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI05, 5}},  //769
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI05, 6}},  //770
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI05, 7}},  //771
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI05, 8}},  //772
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI05, 9}},  //773
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI05, 10}}, //774
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI05, 11}}, //775
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI05, 12}}, //776
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI05, 13}}, //777
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI05, 14}}, //778
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI05, 15}}, //779
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI06, 0}},  //780
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI06, 1}},  //781
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI06, 2}},  //782
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI06, 3}},  //783
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI06, 4}},  //784
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI06, 5}},  //785
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI06, 6}},  //786
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI06, 7}},  //787
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI06, 8}},  //788
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI06, 9}},  //789
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI06, 10}}, //790
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI06, 11}}, //791
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI06, 12}}, //792
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI06, 13}}, //793
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI06, 14}}, //794
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI06, 15}}, //795
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI07, 0}},  //796
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI07, 1}},  //797
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI07, 2}},  //798
        {2, {XA_FILE_YOMI07, 10}, {XA_FILE_YOMI07, 3}},  //799
        {1, {XA_FILE_YOMI07, 11}, {-1, -1}},             //800
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI01, 1}},  //801
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI01, 2}},  //802
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI01, 3}},  //803
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI01, 4}},  //804
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI01, 5}},  //805
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI01, 6}},  //806
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI01, 7}},  //807
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI01, 8}},  //808
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI01, 9}},  //809
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI01, 10}}, //810
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI01, 11}}, //811
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI01, 12}}, //812
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI01, 13}}, //813
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI01, 14}}, //814
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI01, 15}}, //815
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI02, 0}},  //816
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI02, 1}},  //817
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI02, 2}},  //818
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI02, 3}},  //819
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI02, 4}},  //820
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI02, 5}},  //821
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI02, 6}},  //822
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI02, 7}},  //823
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI02, 8}},  //824
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI02, 9}},  //825
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI02, 10}}, //826
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI02, 11}}, //827
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI02, 12}}, //828
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI02, 13}}, //829
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI02, 14}}, //830
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI02, 15}}, //831
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI03, 0}},  //832
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI03, 1}},  //833
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI03, 2}},  //834
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI03, 3}},  //835
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI03, 4}},  //836
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI03, 5}},  //837
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI03, 6}},  //838
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI03, 7}},  //839
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI03, 8}},  //840
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI03, 9}},  //841
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI03, 10}}, //842
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI03, 11}}, //843
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI03, 12}}, //844
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI03, 13}}, //845
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI03, 14}}, //846
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI03, 15}}, //847
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI04, 0}},  //848
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI04, 1}},  //849
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI04, 2}},  //850
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI04, 3}},  //851
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI04, 4}},  //852
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI04, 5}},  //853
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI04, 6}},  //854
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI04, 7}},  //855
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI04, 8}},  //856
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI04, 9}},  //857
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI04, 10}}, //858
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI04, 11}}, //859
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI04, 12}}, //860
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI04, 13}}, //861
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI04, 14}}, //862
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI04, 15}}, //863
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI05, 0}},  //864
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI05, 1}},  //865
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI05, 2}},  //866
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI05, 3}},  //867
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI05, 4}},  //868
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI05, 5}},  //869
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI05, 6}},  //870
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI05, 7}},  //871
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI05, 8}},  //872
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI05, 9}},  //873
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI05, 10}}, //874
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI05, 11}}, //875
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI05, 12}}, //876
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI05, 13}}, //877
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI05, 14}}, //878
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI05, 15}}, //879
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI06, 0}},  //880
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI06, 1}},  //881
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI06, 2}},  //882
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI06, 3}},  //883
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI06, 4}},  //884
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI06, 5}},  //885
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI06, 6}},  //886
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI06, 7}},  //887
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI06, 8}},  //888
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI06, 9}},  //889
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI06, 10}}, //890
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI06, 11}}, //891
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI06, 12}}, //892
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI06, 13}}, //893
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI06, 14}}, //894
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI06, 15}}, //895
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI07, 0}},  //896
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI07, 1}},  //897
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI07, 2}},  //898
        {2, {XA_FILE_YOMI07, 11}, {XA_FILE_YOMI07, 3}},  //899
        {1, {XA_FILE_YOMI07, 12}, {-1, -1}},             //900
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI01, 1}},  //901
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI01, 2}},  //902
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI01, 3}},  //903
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI01, 4}},  //904
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI01, 5}},  //905
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI01, 6}},  //906
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI01, 7}},  //907
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI01, 8}},  //908
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI01, 9}},  //909
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI01, 10}}, //910
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI01, 11}}, //911
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI01, 12}}, //912
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI01, 13}}, //913
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI01, 14}}, //914
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI01, 15}}, //915
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI02, 0}},  //916
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI02, 1}},  //917
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI02, 2}},  //918
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI02, 3}},  //919
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI02, 4}},  //920
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI02, 5}},  //921
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI02, 6}},  //922
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI02, 7}},  //923
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI02, 8}},  //924
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI02, 9}},  //925
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI02, 10}}, //926
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI02, 11}}, //927
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI02, 12}}, //928
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI02, 13}}, //929
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI02, 14}}, //930
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI02, 15}}, //931
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI03, 0}},  //932
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI03, 1}},  //933
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI03, 2}},  //934
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI03, 3}},  //935
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI03, 4}},  //936
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI03, 5}},  //937
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI03, 6}},  //938
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI03, 7}},  //939
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI03, 8}},  //940
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI03, 9}},  //941
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI03, 10}}, //942
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI03, 11}}, //943
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI03, 12}}, //944
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI03, 13}}, //945
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI03, 14}}, //946
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI03, 15}}, //947
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI04, 0}},  //948
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI04, 1}},  //949
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI04, 2}},  //950
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI04, 3}},  //951
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI04, 4}},  //952
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI04, 5}},  //953
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI04, 6}},  //954
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI04, 7}},  //955
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI04, 8}},  //956
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI04, 9}},  //957
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI04, 10}}, //958
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI04, 11}}, //959
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI04, 12}}, //960
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI04, 13}}, //961
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI04, 14}}, //962
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI04, 15}}, //963
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI05, 0}},  //964
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI05, 1}},  //965
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI05, 2}},  //966
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI05, 3}},  //967
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI05, 4}},  //968
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI05, 5}},  //969
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI05, 6}},  //970
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI05, 7}},  //971
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI05, 8}},  //972
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI05, 9}},  //973
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI05, 10}}, //974
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI05, 11}}, //975
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI05, 12}}, //976
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI05, 13}}, //977
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI05, 14}}, //978
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI05, 15}}, //979
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI06, 0}},  //980
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI06, 1}},  //981
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI06, 2}},  //982
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI06, 3}},  //983
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI06, 4}},  //984
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI06, 5}},  //985
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI06, 6}},  //986
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI06, 7}},  //987
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI06, 8}},  //988
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI06, 9}},  //989
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI06, 10}}, //990
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI06, 11}}, //991
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI06, 12}}, //992
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI06, 13}}, //993
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI06, 14}}, //994
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI06, 15}}, //995
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI07, 0}},  //996
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI07, 1}},  //997
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI07, 2}},  //998
        {2, {XA_FILE_YOMI07, 12}, {XA_FILE_YOMI07, 3}},  //999
        {1, {XA_FILE_YOMI07, 13}, {-1, -1}},             //1000
};

//-----------------------------------------------------------------------------
//  prototype
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// codes
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  関数名 :Thou
//
//  work   :めざせ1000人
//  in     :GAMEMGR*    ゲームマネージャへのポインタ
//  out    :TRUE        成功
//  note   :なし
//-----------------------------------------------------------------------------
int Thou(GAMEMGR *ip_GameMgr)
{
    SPRITE_DATA SpData;
    TASK Task;

    switch (ip_GameMgr->SubMode)
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

        //---- ゲーム管理情報初期化
        TGameMgr.SceneNo = 0;
        TGameMgr.VisitorScore = 0;                         //入場者数
        TGameMgr.HighScore = ip_GameMgr->Level[GAME_THOU]; //最高値の入場者数
        TGameMgr.HighScoreFlag = 0;                        //
        TGameMgr.Timer = 0;                                //ゲーム時間
        TGameMgr.TimerFlag = 0;                            //ゲーム時間
        TGameMgr.ContinureFlag = 0;                        //継続プレイフラグ
        TGameMgr.TimeUpFlag = 0;                           //時間切れフラグ
        TGameMgr.ClearFlag = 0;                            //クリアフラグ
        TGameMgr.EventTimer = 0;                           //タイマー
        TGameMgr.ClearEndFlag = 0;                         //クリア終了
        TGameMgr.ExitFlag = 0;                             //終了フラグ

        //----岩澤担当部分：初期化
        SfileRead2(THOU_SOUNDFILE);
        HelpInit();
        GameMgr.WaitFlag = ON;

#ifdef __DEBUG_THOU__

        if (NewPad & PADL1)
        { //----デバッグタスク
            Task.func = DebugGameSpriteTask;
            Task.priority = TASK_NO_DEBUG;
            Task.attribute = ATTR_USER;
            Task.status = TASK_NEW_ENTRY;
            Task.id = TASK_NO_DEBUG;
            Task.wait_time = 0;
            Task.buf = NULL;
            Task.name = "DebugGameSpriteTask";
            Task.mode = TASK_MODE_INIT;
            CreateTask(&Task);
        }
        else if (NewPad & PADL2)
        {

            Task.func = DebugEventSpriteTask;
            Task.priority = TASK_NO_DEBUG;
            Task.attribute = ATTR_USER;
            Task.status = TASK_NEW_ENTRY;
            Task.id = TASK_NO_DEBUG;
            Task.wait_time = 0;
            Task.buf = NULL;
            Task.name = "DebugEventSpriteTask";
            Task.mode = TASK_MODE_INIT;
            CreateTask(&Task);
        }
        else if (NewPad & PADR1)
        {

            Task.func = ClearGameEventTask;
            Task.priority = TASK_NO_CLEAR_EVENT;
            Task.attribute = ATTR_USER;
            Task.status = TASK_NEW_ENTRY;
            Task.id = TASK_NO_CLEAR_EVENT;
            Task.wait_time = 0;
            Task.buf = NULL;
            Task.name = "ClearGameEventTask";
            Task.mode = TASK_MODE_INIT;
            CreateTask(&Task);

            //              Task.func       = ThouClearEventTask;
            //              Task.priority   = TASK_NO_CLEAR_EVENT;
            //              Task.attribute  = ATTR_USER;
            //              Task.status     = TASK_NEW_ENTRY;
            //              Task.id         = TASK_NO_CLEAR_EVENT;
            //              Task.wait_time  = 0;
            //              Task.buf        = NULL;
            //              Task.name       = "ThouClearEventTask";
            //              Task.mode       = TASK_MODE_INIT;
            //              CreateTask(&Task);
        }
        else if (NewPad & PADR2)
        {
            TGameMgr.VisitorScore = 888;

            Task.func = ThouFalseEventTask;
            Task.priority = TASK_NO_FALSE_EVENT;
            Task.attribute = ATTR_USER;
            Task.status = TASK_NEW_ENTRY;
            Task.id = TASK_NO_FALSE_EVENT;
            Task.wait_time = 0;
            Task.buf = NULL;
            Task.name = "ThouFalseEventTask";
            Task.mode = TASK_MODE_INIT;
            CreateTask(&Task);
        }
        else
        { //----
            //----ゲームコントロールタスク
            Task.func = GameControllTask;
            Task.priority = TASK_NO_GAME_CONTROLL;
            Task.attribute = ATTR_USER;
            Task.status = TASK_NEW_ENTRY;
            Task.id = TASK_NO_GAME_CONTROLL;
            Task.wait_time = 0;
            Task.buf = NULL;
            Task.name = "GameControllTask";
            Task.mode = TASK_MODE_INIT;
            CreateTask(&Task);
        }
#else
        //----ゲームコントロールタスク
        Task.func = GameControllTask;
        Task.priority = TASK_NO_GAME_CONTROLL;
        Task.attribute = ATTR_USER;
        Task.status = TASK_NEW_ENTRY;
        Task.id = TASK_NO_GAME_CONTROLL;
        Task.wait_time = 0;
        Task.buf = NULL;
        Task.name = "GameControllTask";
        Task.mode = TASK_MODE_INIT;
        CreateTask(&Task);
#endif

        break;
    case MAIN:
        //-----------------------------------------ゲームメインループ▼
        FntPrint(""); //呼んでおかないとダメ

        ExecuteTask();
        TransSprite();
        SpraitControl();

        //----終了チェック
        if (TGameMgr.ExitFlag)
            ip_GameMgr->SubMode = EXIT;

        //-----------------------------------------------------------▲
        break;
    case EXIT:
        //----岩澤担当部分：終了
        SpraitCharClr();
        SpraitControl();
        GameMgr.WaitFlag = ON;
        //[♪] サウンド停止
        ssStopAll();
        ssCloseVab();

        //----最高値の入場者数
        ip_GameMgr->Level[GAME_THOU] = TGameMgr.HighScore;

        //----メインメニューへ
        ip_GameMgr->MainMode = MAIN_MODE_TOP_MENU;
        ip_GameMgr->SubMode = INIT;
        break;
    default:
    }

    return TRUE;
}

//-----------------------------------------------------------------------------
//  関数名 :GameControllTask
//
//  work   :ゲームマネージャタスク
//  in     :TASK*   タスクポインタ
//  out    :TRUE
//  note   :なし
//-----------------------------------------------------------------------------
static int GameControllTask(TASK *ip_task)
{
    TASK Task;

    switch (ip_task->mode)
    {
    //------------------------------------------------------------------------
    case TASK_MODE_INIT:
        //next main
        ip_task->mode = TASK_MODE_MAIN;

        //----texture read sram -> vram
        if ((file_read(ThouGameTextureFile[0].fn, LoadAddress)) == -1)
        { //read error
            return FALSE;
        }

        //----texture init
        TexInit(THOU_GAME_TIM_NUM, &ThouGameTextureImage[THOU_GAME_TIM_POS]);
        TimImgData = ThouGameTextureImage;

        //----ゲーム用スプライト登録
        EntrySprite(ThouGameSpriteData);

        //---- ゲーム管理情報初期化
        TGameMgr.SceneNo = 0;
        TGameMgr.VisitorScore = 0;  //入場者数
                                    //  TGameMgr.HighScore      = ;                 //最高値の入場者数
        TGameMgr.HighScoreFlag = 0; //最高値の入場者数フラグ
        TGameMgr.Timer = 0;         //ゲーム時間
        TGameMgr.TimerFlag = 0;     //ゲーム時間
                                    //  TGameMgr.ContinureFlag  = 0;                //継続プレイフラグ
        TGameMgr.TimeUpFlag = 0;    //時間切れフラグ
        TGameMgr.ClearFlag = 0;     //クリアフラグ
        TGameMgr.EventTimer = 0;    //タイマー
        TGameMgr.ClearEndFlag = 0;  //クリア終了
        TGameMgr.ExitFlag = 0;      //終了フラグ

        //ガイドセット
        GaidoInit();

        if (!TGameMgr.ContinureFlag)
        { //----新規にプレイ
            //----ライオン出現タスク
            Task.func = LionAppearTask;
            Task.priority = TASK_NO_GAME_LION_APPEAR;
            Task.attribute = ATTR_USER;
            Task.status = TASK_NEW_ENTRY;
            Task.id = TASK_NO_GAME_LION_APPEAR;
            Task.wait_time = 0;
            Task.buf = NULL;
            Task.name = "LionAppearTask";
            Task.mode = TASK_MODE_INIT;
            CreateTask(&Task);
        }
        else
        { //----継続プレイ
            //----ライオンタスク起動
            Task.func = LionTask;
            Task.priority = TASK_NO_GAME_LION;
            Task.attribute = ATTR_USER;
            Task.status = TASK_NEW_ENTRY;
            Task.id = TASK_NO_GAME_LION;
            Task.wait_time = 0;
            Task.buf = NULL;
            Task.name = "LionTask";
            Task.mode = TASK_MODE_INIT;
            CreateTask(&Task);
        }

        //----背景タスク
        Task.func = GameBgTask;
        Task.priority = TASK_NO_GAME_BG;
        Task.attribute = ATTR_USER;
        Task.status = TASK_NEW_ENTRY;
        Task.id = TASK_NO_GAME_BG;
        Task.wait_time = 0;
        Task.buf = NULL;
        Task.name = "GameBgTask";
        Task.mode = TASK_MODE_INIT;
        CreateTask(&Task);

        //----ハイスコアタスク
        Task.func = HighScoreTask;
        Task.priority = TASK_NO_GAME_HIGH_SCORE;
        Task.attribute = ATTR_USER;
        Task.status = TASK_NEW_ENTRY;
        Task.id = TASK_NO_GAME_HIGH_SCORE;
        Task.wait_time = 0;
        Task.buf = NULL;
        Task.name = "HighScoreTask";
        Task.mode = TASK_MODE_INIT;
        CreateTask(&Task);

        break;
    //------------------------------------------------------------------------
    case TASK_MODE_MAIN:

#ifdef
        FntPrint("TGameMgr.CallCount.Flag[%d]\n", TGameMgr.CallCount.Flag);
#endif
        if (TGameMgr.ClearEndFlag || TGameMgr.TimeUpFlag)
            ip_task->mode = TASK_MODE_EXIT;

        break;
    //------------------------------------------------------------------------
    case TASK_MODE_EXIT:
        //[♪]BGN停止
        ssStopBgm(THOU_BGM_00);

        //----ゲームタスク終了
        RemoveTask(TASK_NO_GAME_PAUSE);
        RemoveTask(TASK_NO_GAME_SCRIPT);
        RemoveTask(TASK_NO_GAME_TIMER_EXIT);
        RemoveTask(TASK_NO_GAME_LION_APPEAR);
        RemoveTask(TASK_NO_GAME_LION);
        RemoveTask(TASK_NO_GAME_TAXI);
        RemoveTask(TASK_NO_GAME_BASS);
        RemoveTask(TASK_NO_GAME_TRAIN);
        RemoveTask(TASK_NO_GAME_WINDOWS_SCENE);
        RemoveTask(TASK_NO_GAME_VISITOR_SCORE);
        RemoveTask(TASK_NO_GAME_VISITOR);
        RemoveTask(TASK_NO_GAME_HIGH_SCORE);
        RemoveTask(TASK_NO_GAME_BG);

        //----ハイスコア更新
        if (TGameMgr.VisitorScore > TGameMgr.HighScore)
        {
            TGameMgr.HighScore = TGameMgr.VisitorScore;
            TGameMgr.HighScoreFlag = 1;
        }

        //----登録スプライト開放
        ReleaseSprite();

        //ガイド破棄
        SpraitCharClr();

        //スクリプト強制OFF
        MetuseijiFlag = OFF;

        //----イベントタスク起動
        if (TGameMgr.TimeUpFlag)
        { //----残念イベント
            Task.func = ThouFalseEventTask;
            Task.priority = TASK_NO_FALSE_EVENT;
            Task.attribute = ATTR_USER;
            Task.status = TASK_NEW_ENTRY;
            Task.id = TASK_NO_FALSE_EVENT;
            Task.wait_time = 0;
            Task.buf = NULL;
            Task.name = "ThouFalseEventTask";
            Task.mode = TASK_MODE_INIT;
            CreateTask(&Task);
        }
        else
        { //----クリアイベント
            Task.func = ThouClearEventTask;
            Task.priority = TASK_NO_CLEAR_EVENT;
            Task.attribute = ATTR_USER;
            Task.status = TASK_NEW_ENTRY;
            Task.id = TASK_NO_CLEAR_EVENT;
            Task.wait_time = 0;
            Task.buf = NULL;
            Task.name = "ThouClearEventTask";
            Task.mode = TASK_MODE_INIT;
            CreateTask(&Task);
        }

        //自分を削除
        ExitTask(ip_task->id);
        break;
    default:
    }

    return TRUE;
}

//-----------------------------------------------------------------------------
//  関数名  :LionAppearTask
//
//  work    :ライオン出現タスク
//  in      :TASK* ip_task  タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int LionAppearTask(TASK *ip_task)
{
    static int BigLionSpriteTable[] = {
        THOU_CHAR_GAME_BIG_LION_00, //ライオンの挨拶　ゲーム前演出１
        THOU_CHAR_GAME_BIG_LION_00, //ライオンの挨拶　ゲーム前演出１
        THOU_CHAR_GAME_BIG_LION_00, //ライオンの挨拶　ゲーム前演出１
        THOU_CHAR_GAME_BIG_LION_01, //ライオンの挨拶　ゲーム前演出２
        THOU_CHAR_GAME_BIG_LION_02, //ライオンの走り　ゲーム前演出１
        THOU_CHAR_GAME_BIG_LION_03, //ライオンの走り　ゲーム前演出２
    };

    SPRITE_DATA SpData;
    TASK Task;

    switch (ip_task->mode)
    {
    //----------------------------------------------------------------タスク初期化
    case TASK_MODE_INIT:
        //next MAIN
        ip_task->mode = TASK_MODE_MAIN;

        //----ワーク初期化
        ip_task->user[0] = 0;   //Mode
        ip_task->user[1] = 0;   //No
        ip_task->user[2] = 0;   //Index
        ip_task->user[3] = 0;   //Base
        ip_task->user[4] = 0;   //WaitTime
        ip_task->user[5] = 80;  //PosX
        ip_task->user[6] = 340; //PosY
        ip_task->user[7] = 0;   //Timer
        ip_task->user[8] = 0;   //WaitFlag

        //フェードイン
        GameMgr.FadeFlag = FadeIn;

        //----SET
        ip_task->user[1] = BigLionSpriteTable[ip_task->user[3] + ip_task->user[2]];

        //[♪] ビヨーン
        ssPlaySe(THOU_SE_01);

        break;
    //----------------------------------------------------------------タスクメイン
    case TASK_MODE_MAIN:

        switch (ip_task->user[0])
        {
        //--------------------下から上へ出現
        case 0:
            ip_task->user[6] -= 3;
            if (ip_task->user[6] <= 4)
            {
                ip_task->user[0] = 1; //Mode
            }

            break;
        //--------------------上から下へ
        case 1:
            ip_task->user[6] += 2;

            if (ip_task->user[6] >= 20)
            {
                ip_task->user[0] = 2;                             //Mode
                ip_task->user[6] = 20;                            //PosY
                ip_task->user[2] = 0;                             //Index
                ip_task->user[3] = 2;                             //Base
                ip_task->user[4] = THOU_BIG_LION_SPEAK_WAIT_TIME; //WaitTime

                //スクリプト
                Task.func = ScriptTask;
                Task.priority = TASK_NO_GAME_SCRIPT;
                Task.attribute = ATTR_USER;
                Task.status = TASK_NEW_ENTRY;
                Task.id = TASK_NO_GAME_SCRIPT;
                Task.wait_time = 0;
                Task.buf = NULL;
                Task.name = "ScriptTask";
                Task.mode = TASK_MODE_INIT;
                Task.user[0] = SCRIPT_LINE_2;
                Task.user[1] = INIT_PLAY_DEMO_SCRIPT_BASE;
                Task.user[2] = INIT_PLAY_DEMO_SCRIPT_NUM;
                CreateTask(&Task);
            }
            break;
        //--------------------話
        case 2:
            //----話時間待ち
            if (++ip_task->user[7] > THOU_BIG_LION_SPEAK_WAIT_TIME)
            {
                ip_task->user[0] = 3;                             //Mode
                ip_task->user[2] = 0;                             //Index
                ip_task->user[3] = 4;                             //Base
                ip_task->user[4] = THOU_BIG_LION_SPEAK_WAIT_TIME; //WaitTime
            }

            break;
        //--------------------横移動
        case 3:
            ip_task->user[5] += 2;
            if (ip_task->user[5] > 400)
            { //PosX
                ip_task->user[5] = 500;

                if (!ip_task->user[8])
                {
                    ip_task->user[8] = 1;
                    //----EXIT
                    Task.func = EventFadeOutTask;
                    Task.priority = TASK_NO_GAME_FADE;
                    Task.attribute = ATTR_USER;
                    Task.status = TASK_NEW_ENTRY;
                    Task.id = TASK_NO_GAME_FADE;
                    Task.wait_time = 0;
                    Task.buf = NULL;
                    Task.name = "EventFadeOutTask";
                    Task.mode = TASK_MODE_INIT;
                    Task.user[0] = ip_task->id;
                    CreateTask(&Task);
                }
                //ip_task->mode=TASK_MODE_EXIT;
            }

            break;
        default:
        }

        //----アニメ
        if (++ip_task->user[4] > THOU_LION_ANM_WAIT_TIME)
        {
            ip_task->user[4] = 0;
            ip_task->user[2] ^= 1;
            ip_task->user[1] = BigLionSpriteTable[ip_task->user[3] + ip_task->user[2]];
        }

        //----描画
        SpData.No = ip_task->user[1];
        SpData.PosX = ip_task->user[5];
        SpData.PosY = ip_task->user[6];
        SpData.PosZ = PRIORITY_THOU_GAME_LION;
        SpData.ScaleX = SCALE10;
        SpData.ScaleY = SCALE10;
        SpData.Rotate = ROTATE000;
        SpData.Reverse = NOREVERS;
        DrawSprite(&SpData);

        break;
    //----------------------------------------------------------------タスク終了
    case TASK_MODE_EXIT:

        //スクリプトOFF
        MetuseijiFlag = OFF;

        //----ライオンタスク起動
        Task.func = LionTask;
        Task.priority = TASK_NO_GAME_LION;
        Task.attribute = ATTR_USER;
        Task.status = TASK_NEW_ENTRY;
        Task.id = TASK_NO_GAME_LION;
        Task.wait_time = 0;
        Task.buf = NULL;
        Task.name = "LionTask";
        Task.mode = TASK_MODE_INIT;
        CreateTask(&Task);

        //自分を削除
        ExitTask(ip_task->id);
        break;
    default:
    }
    return TRUE;
}

//-----------------------------------------------------------------------------
//  関数名  :LionTask
//
//  work    :ライオンタスク
//  in      :TASK* ip_task  タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int LionTask(TASK *ip_task)
{
    SPRITE_DATA SpData;
    TASK Task;

    switch (ip_task->mode)
    {
    //----------------------------------------------------------------初期化
    case TASK_MODE_INIT:
        //----next main
        ip_task->mode = TASK_MODE_MAIN;

        //----ライオンデータ初期化
        TGameMgr.Lion.Character.Status = LION_APPEAR;
        TGameMgr.Lion.Character.Anm.Data.no = 0;
        TGameMgr.Lion.Character.Anm.Data.wt = 0;
        TGameMgr.Lion.Character.Anm.Index = 0;
        TGameMgr.Lion.Character.Pos.x = THOU_GAME_LION_INIT_POS_X;
        TGameMgr.Lion.Character.Pos.y = THOU_GAME_LION_INIT_POS_Y;
        TGameMgr.Lion.Character.Pos.z = PRIORITY_THOU_GAME_LION;
        TGameMgr.Lion.Character.OPos.x = 0;
        TGameMgr.Lion.Character.OPos.y = 0;
        TGameMgr.Lion.Character.OPos.z = 0;
        TGameMgr.Lion.Character.Spd.dx = THOU_GAME_LION_APPEAR_DIRECT_X;
        TGameMgr.Lion.Character.Spd.dy = THOU_GAME_LION_APPEAR_DIRECT_Y;
        TGameMgr.Lion.Character.Spd.sx = THOU_GAME_LION_APPEAR_SPEED_X;
        TGameMgr.Lion.Character.Spd.sy = THOU_GAME_LION_APPEAR_SPEED_Y;
        TGameMgr.Lion.AnmBase = LION_ANM_BASE_RUN;
        TGameMgr.Lion.WaitPlace = PLACE_BASE;
        TGameMgr.Lion.WaitTimer = 0;

        //ANM SET
        TGameMgr.Lion.Character.Anm.Data.no = GameLionSpriteTable[TGameMgr.Lion.AnmBase + TGameMgr.Lion.Character.Anm.Index];

        //フェードイン
        GameMgr.FadeFlag = FadeIn;

        //スクリプト
        Task.func = ScriptTask;
        Task.priority = TASK_NO_GAME_SCRIPT;
        Task.attribute = ATTR_USER;
        Task.status = TASK_NEW_ENTRY;
        Task.id = TASK_NO_GAME_SCRIPT;
        Task.wait_time = 0;
        Task.buf = NULL;
        Task.name = "ScriptTask";
        Task.mode = TASK_MODE_INIT;
        Task.user[0] = SCRIPT_LINE_2;
        Task.user[1] = PLAY_START_SCRIPT_BASE;
        Task.user[2] = PLAY_START_SCRIPT_NUM;
        CreateTask(&Task);

        break;
    //----------------------------------------------------------------メイン
    case TASK_MODE_MAIN:

        switch (TGameMgr.Lion.Character.Status)
        {
        //------------------------------------------------出現
        case LION_APPEAR:
            //----優先順位
            TGameMgr.Lion.Character.Pos.z = PRIORITY_THOU_GAME_LION;

            //----移動
            TGameMgr.Lion.Character.Pos.x += TGameMgr.Lion.Character.OPos.x + TGameMgr.Lion.Character.Spd.dx * TGameMgr.Lion.Character.Spd.sx;
            TGameMgr.Lion.Character.Pos.y += TGameMgr.Lion.Character.OPos.y + TGameMgr.Lion.Character.Spd.dy * TGameMgr.Lion.Character.Spd.sy;

            if (TGameMgr.Lion.Character.Pos.y >= GameLionWaitPosTable[PLACE_BASE].PosY)
            {
                //----ライオンステータス変更：ベース出現待ち
                TGameMgr.Lion.Character.Status = LION_APPEAR_WAIT;

                //----アニメと位置の補正
                TGameMgr.Lion.Character.Anm.Index = 0;
                TGameMgr.Lion.Character.Anm.Data.wt = THOU_LION_ANM_WAIT_TIME;
                TGameMgr.Lion.AnmBase = LION_ANM_BASE_HATA;
                TGameMgr.Lion.Character.Pos.x = GameLionWaitPosTable[TGameMgr.Lion.WaitPlace].PosX;
                TGameMgr.Lion.Character.Pos.y = GameLionWaitPosTable[TGameMgr.Lion.WaitPlace].PosY;
                TGameMgr.Lion.WaitTimer = THOU_GAME_LION_APPEAR_WAIT_TIME;
            }

            break;
        //------------------------------------------------ライオン位置
        case LION_APPEAR_WAIT:

            if (--TGameMgr.Lion.WaitTimer <= 0)
            {
                //----ライオンステータス変更：ベース位置で待ち
                TGameMgr.Lion.Character.Status = LION_BASE_WAIT;

                //ゲーム内の待ち時間をセット
                TGameMgr.Lion.WaitTimer = THOU_GAME_LION_BASE_WAIT_TIME;

                //                      //----アニメと位置の補正
                //                      TGameMgr.Lion.Character.Anm.Index   = 0;
                //                      TGameMgr.Lion.Character.Anm.Data.wt = THOU_LION_ANM_WAIT_TIME;
                //                      TGameMgr.Lion.AnmBase               = LION_ANM_BASE_HATA;
                //                      TGameMgr.Lion.Character.Pos.x       = GameLionWaitPosTable[TGameMgr.Lion.WaitPlace].PosX;
                //                      TGameMgr.Lion.Character.Pos.y       = GameLionWaitPosTable[TGameMgr.Lion.WaitPlace].PosY;
                //                      TGameMgr.Lion.WaitTimer             = THOU_GAME_LION_BASE_WAIT_TIME;

                //----ポーズ監視タスク
                Task.func = PauseTask;
                Task.priority = TASK_NO_GAME_PAUSE;
                Task.attribute = ATTR_USER;
                Task.status = TASK_NEW_ENTRY;
                Task.id = TASK_NO_GAME_PAUSE;
                Task.wait_time = 0;
                Task.buf = NULL;
                Task.name = "PauseTask";
                Task.mode = TASK_MODE_INIT;
                CreateTask(&Task);

                //----バスタスク
                Task.func = BassTask;
                Task.priority = TASK_NO_GAME_BASS;
                Task.attribute = ATTR_USER;
                Task.status = TASK_NEW_ENTRY;
                Task.id = TASK_NO_GAME_BASS;
                Task.wait_time = 0;
                Task.buf = NULL;
                Task.name = "BassTask";
                Task.mode = TASK_MODE_INIT;
                CreateTask(&Task);

                //----タクシータスク
                Task.func = TaxiTask;
                Task.priority = TASK_NO_GAME_TAXI;
                Task.attribute = ATTR_USER;
                Task.status = TASK_NEW_ENTRY;
                Task.id = TASK_NO_GAME_TAXI;
                Task.wait_time = 0;
                Task.buf = NULL;
                Task.name = "TaxiTask";
                Task.mode = TASK_MODE_INIT;
                CreateTask(&Task);

                //----電車タスク
                Task.func = TrainTask;
                Task.priority = TASK_NO_GAME_TRAIN;
                Task.attribute = ATTR_USER;
                Task.status = TASK_NEW_ENTRY;
                Task.id = TASK_NO_GAME_TRAIN;
                Task.wait_time = 0;
                Task.buf = NULL;
                Task.name = "TrainTask";
                Task.mode = TASK_MODE_INIT;
                CreateTask(&Task);

                //----シーンタスク
                Task.func = WindowSceneTask;
                Task.priority = TASK_NO_GAME_WINDOWS_SCENE;
                Task.attribute = ATTR_USER;
                Task.status = TASK_NEW_ENTRY;
                Task.id = TASK_NO_GAME_WINDOWS_SCENE;
                Task.wait_time = 0;
                Task.buf = NULL;
                Task.name = "WindowSceneTask";
                Task.mode = TASK_MODE_INIT;
                CreateTask(&Task);

                //----スコアタスク
                Task.func = VisitorScoreTask;
                Task.priority = TASK_NO_GAME_VISITOR_SCORE;
                Task.attribute = ATTR_USER;
                Task.status = TASK_NEW_ENTRY;
                Task.id = TASK_NO_GAME_VISITOR_SCORE;
                Task.wait_time = 0;
                Task.buf = NULL;
                Task.name = "VisitorScoreTask";
                Task.mode = TASK_MODE_INIT;
                Task.user[0] = -40;
                CreateTask(&Task);

                //[♪]　BGM
                ssPlayBgm(THOU_BGM_00);
            }

            break;
        //------------------------------------------------ベース位置で待ち
        case LION_BASE_WAIT:
            if (--TGameMgr.Lion.WaitTimer <= 0)
            {
                //----優先順位
                TGameMgr.Lion.Character.Pos.z = PRIORITY_THOU_GAME_LION;

                if (JstPad & PADLdown)
                {
                    //[♪] レバー音
                    ssPlaySe(BUTONSE_LEVER);

                    //----ライオンステータス変更：電車待ち
                    TGameMgr.Lion.Character.Status = LION_TRAIN_STATION_WAIT;

                    //----優先順位
                    TGameMgr.Lion.Character.Pos.z = PRIORITY_THOU_GAME_TRAIN + 1;

                    //----位置変更：電車待ち
                    TGameMgr.Lion.WaitPlace = PLACE_TRAIN_STATION;
                }
                else if (JstPad & PADLleft)
                {
                    //[♪] レバー音
                    ssPlaySe(BUTONSE_LEVER);

                    //----ライオンステータス変更：タクシー待ち
                    TGameMgr.Lion.Character.Status = LION_TAXI_STATION_WAIT;

                    //----優先順位
                    TGameMgr.Lion.Character.Pos.z = PRIORITY_THOU_GAME_TAXI + 1;

                    //----位置変更：タクシー待ち
                    TGameMgr.Lion.WaitPlace = PLACE_TAXI_STATION;
                }
                else if (JstPad & PADLright)
                {
                    //[♪] レバー音
                    ssPlaySe(BUTONSE_LEVER);

                    //----ライオンステータス変更：バス待ち
                    TGameMgr.Lion.Character.Status = LION_BASS_STATION_WAIT;

                    //----優先順位
                    TGameMgr.Lion.Character.Pos.z = PRIORITY_THOU_GAME_BASS + 1;

                    //----位置変更：バス待ち
                    TGameMgr.Lion.WaitPlace = PLACE_BASS_STATION;
                }
                else
                {
                }
            }
            if (--TGameMgr.Lion.WaitTimer == 0)
            {
                GameMgr.WaitFlag = OFF; // iwasawa Correction (2003/4/27)
            }

            break;
        //------------------------------------------------タクシー待ち
        case LION_TAXI_STATION_WAIT:
            if (JstPad & PADLdown)
            {
                //[♪] レバー音
                ssPlaySe(BUTONSE_LEVER);

                //----ライオンステータス変更：電車待ち
                TGameMgr.Lion.Character.Status = LION_TRAIN_STATION_WAIT;

                //----優先順位
                TGameMgr.Lion.Character.Pos.z = PRIORITY_THOU_GAME_TRAIN + 1;

                //----位置変更：電車待ち
                TGameMgr.Lion.WaitPlace = PLACE_TRAIN_STATION;
            }
            else if (JstPad & PADLright)
            {
                //[♪] レバー音
                ssPlaySe(BUTONSE_LEVER);

                //----ライオンステータス変更：バス待ち
                TGameMgr.Lion.Character.Status = LION_BASS_STATION_WAIT;

                //----優先順位
                TGameMgr.Lion.Character.Pos.z = PRIORITY_THOU_GAME_BASS + 1;

                //----位置変更：バス待ち
                TGameMgr.Lion.WaitPlace = PLACE_BASS_STATION;
            }
            else if (JstPad & PADLleft)
            {
                //[♪] レバー音
                ssPlaySe(BUTONSE_LEVER);

                //----ライオンステータス変更：電車待ち
                TGameMgr.Lion.Character.Status = LION_TRAIN_STATION_WAIT;

                //----優先順位
                TGameMgr.Lion.Character.Pos.z = PRIORITY_THOU_GAME_TRAIN + 1;

                //----位置変更：電車待ち
                TGameMgr.Lion.WaitPlace = PLACE_TRAIN_STATION;
            }
            else
            {
            }
            break;
        //------------------------------------------------バス待ち
        case LION_BASS_STATION_WAIT:
            if (JstPad & PADLdown)
            {
                //[♪] レバー音
                ssPlaySe(BUTONSE_LEVER);

                //----ライオンステータス変更：電車待ち
                TGameMgr.Lion.Character.Status = LION_TRAIN_STATION_WAIT;

                //----優先順位
                TGameMgr.Lion.Character.Pos.z = PRIORITY_THOU_GAME_TRAIN + 1;

                //----位置変更：電車待ち
                TGameMgr.Lion.WaitPlace = PLACE_TRAIN_STATION;
            }
            else if (JstPad & PADLleft)
            {
                //[♪] レバー音
                ssPlaySe(BUTONSE_LEVER);

                //----ライオンステータス変更：タクシー待ち
                TGameMgr.Lion.Character.Status = LION_TAXI_STATION_WAIT;

                //----優先順位
                TGameMgr.Lion.Character.Pos.z = PRIORITY_THOU_GAME_TAXI + 1;

                //----位置変更：タクシー待ち
                TGameMgr.Lion.WaitPlace = PLACE_TAXI_STATION;
            }
            else if (JstPad & PADLright)
            {
                //[♪] レバー音
                ssPlaySe(BUTONSE_LEVER);

                //----ライオンステータス変更：電車待ち
                TGameMgr.Lion.Character.Status = LION_TRAIN_STATION_WAIT;

                //----優先順位
                TGameMgr.Lion.Character.Pos.z = PRIORITY_THOU_GAME_TRAIN + 1;

                //----位置変更：電車待ち
                TGameMgr.Lion.WaitPlace = PLACE_TRAIN_STATION;
            }
            else
            {
            }
            break;
        //------------------------------------------------電車待ち
        case LION_TRAIN_STATION_WAIT:

            if (JstPad & PADLleft)
            {
                //[♪] レバー音
                ssPlaySe(BUTONSE_LEVER);

                //----ライオンステータス変更：バス待ち
                TGameMgr.Lion.Character.Status = LION_BASS_STATION_WAIT;

                //----優先順位
                TGameMgr.Lion.Character.Pos.z = PRIORITY_THOU_GAME_BASS + 1;

                //----位置変更：バス待ち
                TGameMgr.Lion.WaitPlace = PLACE_BASS_STATION;
            }
            else if (JstPad & PADLright)
            {
                //[♪] レバー音
                ssPlaySe(BUTONSE_LEVER);

                //----ライオンステータス変更：タクシー待ち
                TGameMgr.Lion.Character.Status = LION_TAXI_STATION_WAIT;

                //----優先順位
                TGameMgr.Lion.Character.Pos.z = PRIORITY_THOU_GAME_TAXI + 1;

                //----位置変更：タクシー待ち
                TGameMgr.Lion.WaitPlace = PLACE_TAXI_STATION;
            }
            else if (JstPad & PADLup)
            {
                //[♪] レバー音
                ssPlaySe(BUTONSE_LEVER);

                //----ライオンステータス変更：バス待ち
                TGameMgr.Lion.Character.Status = LION_BASS_STATION_WAIT;

                //----優先順位
                TGameMgr.Lion.Character.Pos.z = PRIORITY_THOU_GAME_BASS + 1;

                //----位置変更：バス待ち
                TGameMgr.Lion.WaitPlace = PLACE_BASS_STATION;
            }
            else
            {
            }
            break;
        //------------------------------------------------歓迎待ち
        case LION_WELCOME_WAIT:
            //VisitorTaskからの連絡待ち
            break;
        //------------------------------------------------画面外へ
        case LION_DISAPPEAR:

            break;
        case LION_WAIT:

            break;
        default:
        }

        //----アニメ
        if (++TGameMgr.Lion.Character.Anm.Data.wt > THOU_LION_ANM_WAIT_TIME)
        {
            TGameMgr.Lion.Character.Anm.Data.wt = 0;
            TGameMgr.Lion.Character.Anm.Index ^= 1;
            TGameMgr.Lion.Character.Anm.Data.no = GameLionSpriteTable[TGameMgr.Lion.AnmBase + TGameMgr.Lion.Character.Anm.Index];
        }

        //----位置
        if (TGameMgr.Lion.Character.Status != LION_APPEAR)
        {
            TGameMgr.Lion.Character.Pos.x = GameLionWaitPosTable[TGameMgr.Lion.WaitPlace].PosX;
            TGameMgr.Lion.Character.Pos.y = GameLionWaitPosTable[TGameMgr.Lion.WaitPlace].PosY;
        }

        //----描画
        SpData.No = TGameMgr.Lion.Character.Anm.Data.no;
        SpData.PosX = TGameMgr.Lion.Character.Pos.x + TGameMgr.Lion.Character.OPos.x;
        SpData.PosY = TGameMgr.Lion.Character.Pos.y + TGameMgr.Lion.Character.OPos.y;
        SpData.PosZ = TGameMgr.Lion.Character.Pos.z + TGameMgr.Lion.Character.OPos.z;
        SpData.ScaleX = SCALE10;
        SpData.ScaleY = SCALE10;
        SpData.Rotate = ROTATE000;
        SpData.Reverse = NOREVERS;
        DrawSprite(&SpData);

        break;
    //----------------------------------------------------------------終了
    case TASK_MODE_EXIT:
        //----クリアイベントタスク
        Task.func = ClearGameEventTask;
        Task.priority = TASK_NO_GAME_CLEAR_EVENT;
        Task.attribute = ATTR_USER;
        Task.status = TASK_NEW_ENTRY;
        Task.id = TASK_NO_GAME_CLEAR_EVENT;
        Task.wait_time = 0;
        Task.buf = NULL;
        Task.name = "ClearGameEventTask";
        Task.mode = TASK_MODE_INIT;
        CreateTask(&Task);

        //----自分を削除
        ExitTask(ip_task->id);
        break;
    default:
    }

    return TRUE;
}

//-----------------------------------------------------------------------------
//  関数名  :TaxiTask
//
//  work    :タクシータスク
//  in      :TASK* ip_task  タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int TaxiTask(TASK *ip_task)
{
    SPRITE_DATA SpData;
    TASK Task;

    switch (ip_task->mode)
    {
    //----------------------------------------------------------------初期化
    case TASK_MODE_INIT:
        //---- main
        ip_task->mode = TASK_MODE_MAIN;

        //----バスデータクリア
        TGameMgr.Taxi.Character.Status = VEHICLE_APPEAR;
        TGameMgr.Taxi.Character.Anm.Data.no = THOU_CHAR_GAME_TAXI;
        TGameMgr.Taxi.Character.Anm.Data.wt = 0;
        TGameMgr.Taxi.Character.Anm.Index = 0;
        TGameMgr.Taxi.Character.Pos.x = INIT_POSX_TAXI;
        TGameMgr.Taxi.Character.Pos.y = 84;
        TGameMgr.Taxi.Character.Pos.z = PRIORITY_THOU_GAME_TAXI;
        TGameMgr.Taxi.Character.OPos.x = 0;
        TGameMgr.Taxi.Character.OPos.y = 0;
        TGameMgr.Taxi.Character.OPos.z = 0;
        TGameMgr.Taxi.Character.Spd.dx = 1;
        TGameMgr.Taxi.Character.Spd.dy = 0;
        TGameMgr.Taxi.Character.Spd.sx = VEHICLE_SPEED_X;
        TGameMgr.Taxi.Character.Spd.sy = 0;
        TGameMgr.Taxi.CheckStopX = CHECK_POSX_WELCOME_TAXI;
        TGameMgr.Taxi.Reverse = 1;
        TGameMgr.Taxi.BirthWaitTime = 0;
        TGameMgr.Taxi.VisitorFlag = 1;

        break;
    //----------------------------------------------------------------メイン
    case TASK_MODE_MAIN:
        switch (TGameMgr.Taxi.Character.Status)
        {
        //----------------------------------------出現
        case VEHICLE_APPEAR:
            if (--TGameMgr.Taxi.BirthWaitTime < 0)
            {
                //----ステータス変更：移動へ
                TGameMgr.Taxi.Character.Status = VEHICLE_MOVE;

                //----初期設定
                TGameMgr.Taxi.Character.Pos.x = INIT_POSX_TAXI;
                TGameMgr.Taxi.Character.Spd.dx = 1;
                TGameMgr.Taxi.Reverse = 1;
                TGameMgr.Taxi.VisitorFlag = 1;

                //[♪] プップー
                ssPlaySe(THOU_SE_03);
            }
            break;
        //----------------------------------------移動
        case VEHICLE_MOVE:

            //----移動計算
            TGameMgr.Taxi.Character.Pos.x += TGameMgr.Taxi.Character.Spd.sx * TGameMgr.Taxi.Character.Spd.dx;

            if (TGameMgr.Taxi.VisitorFlag)
            {
                if (TGameMgr.Taxi.Character.Pos.x >= CHECK_POSX_WELCOME_TAXI)
                { //----停止チェック、反転
                    //----ライオンの位置確認：ウェルカムチェック
                    if (TGameMgr.Lion.WaitPlace == PLACE_TAXI_STATION)
                    {
                        GameMgr.WaitFlag = ON; // iwasawa Correction (2003/4/27)
                        //----ステータス変更：停止へ
                        TGameMgr.Taxi.Character.Status = VEHICLE_STOP;

                        //----ライオンステータス変更：ウェルカムウエイト
                        TGameMgr.Lion.Character.Status = LION_WELCOME_WAIT;

                        //----入場者タスク
                        Task.func = VisitorTask;
                        Task.priority = TASK_NO_GAME_VISITOR;
                        Task.attribute = ATTR_USER;
                        Task.status = TASK_NEW_ENTRY;
                        Task.id = TASK_NO_GAME_VISITOR;
                        Task.wait_time = 0;
                        Task.buf = NULL;
                        Task.name = "VisitorTask";
                        Task.mode = TASK_MODE_INIT;
                        Task.user[0] = VISITOR_TYPE_TAXI;
                        CreateTask(&Task);

                        //降ろす
                        TGameMgr.Taxi.VisitorFlag = 0;
                    }
                    else
                    {
                        //----ステータス変更：帰りへ
                        TGameMgr.Taxi.Character.Status = VEHICLE_RETURN;
                        //----反転
                        TGameMgr.Taxi.Character.Spd.dx = -1;
                        TGameMgr.Taxi.Reverse = 0;
                    }
                }
            }

            break;
        //----------------------------------------帰り
        case VEHICLE_RETURN:
            //----移動計算
            TGameMgr.Taxi.Character.Pos.x += TGameMgr.Taxi.Character.Spd.sx * TGameMgr.Taxi.Character.Spd.dx;

            if (TGameMgr.Taxi.Character.Pos.x <= INIT_POSX_TAXI)
            {
                //----ステータス変更：消えるへ
                TGameMgr.Taxi.Character.Status = VEHICLE_DISAPPEAR;
            }
            break;
        //----------------------------------------停止
        case VEHICLE_STOP:
            break;
        //----------------------------------------消える
        case VEHICLE_DISAPPEAR:

            //----ステータス変更：出現へ
            TGameMgr.Taxi.Character.Status = VEHICLE_APPEAR;

            //----生成時間
            TGameMgr.Taxi.BirthWaitTime = rand() % 120 + 60;
            break;
        default:
        }

        //----描画
        SpData.No = TGameMgr.Taxi.Character.Anm.Data.no;
        SpData.PosX = TGameMgr.Taxi.Character.Pos.x + TGameMgr.Taxi.Character.OPos.x;
        SpData.PosY = TGameMgr.Taxi.Character.Pos.y + TGameMgr.Taxi.Character.OPos.y;
        SpData.PosZ = TGameMgr.Taxi.Character.Pos.z + TGameMgr.Taxi.Character.OPos.z;
        SpData.ScaleX = SCALE10;
        SpData.ScaleY = SCALE10;
        SpData.Rotate = ROTATE000;
        SpData.Reverse = ReverseTable[TGameMgr.Taxi.Reverse];
        DrawSprite(&SpData);

        break;
    //----------------------------------------------------------------終了
    case TASK_MODE_EXIT:

        //----自分を削除
        ExitTask(ip_task->id);
        break;
    default:
    }
    return TRUE;
}

//-----------------------------------------------------------------------------
//  関数名  :BassTask
//
//  work    :バスタスク
//  in      :TASK* ip_task  タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int BassTask(TASK *ip_task)
{
    SPRITE_DATA SpData;
    TASK Task;

    switch (ip_task->mode)
    {
    //----------------------------------------------------------------初期化
    case TASK_MODE_INIT:
        //---- main
        ip_task->mode = TASK_MODE_MAIN;

        //----バスデータクリア
        TGameMgr.Bass.Character.Status = VEHICLE_APPEAR;
        TGameMgr.Bass.Character.Anm.Data.no = THOU_CHAR_GAME_BASS;
        TGameMgr.Bass.Character.Anm.Data.wt = 0;
        TGameMgr.Bass.Character.Anm.Index = 0;
        TGameMgr.Bass.Character.Pos.x = INIT_POSX_BASS;
        TGameMgr.Bass.Character.Pos.y = 106;
        TGameMgr.Bass.Character.Pos.z = PRIORITY_THOU_GAME_BASS;
        TGameMgr.Bass.Character.OPos.x = 0;
        TGameMgr.Bass.Character.OPos.y = 0;
        TGameMgr.Bass.Character.OPos.z = 0;
        TGameMgr.Bass.Character.Spd.dx = -1;
        TGameMgr.Bass.Character.Spd.dy = 0;
        TGameMgr.Bass.Character.Spd.sx = VEHICLE_SPEED_X;
        TGameMgr.Bass.Character.Spd.sy = 0;
        TGameMgr.Bass.CheckStopX = CHECK_POSX_WELCOME_BASS;
        TGameMgr.Bass.Reverse = 0;
        TGameMgr.Bass.BirthWaitTime = 0;
        TGameMgr.Bass.VisitorFlag = 1;
        break;
    //----------------------------------------------------------------メイン
    case TASK_MODE_MAIN:
        switch (TGameMgr.Bass.Character.Status)
        {
        //----------------------------------------出現
        case VEHICLE_APPEAR:
            if (--TGameMgr.Bass.BirthWaitTime < 0)
            {
                //----ステータス変更：移動へ
                TGameMgr.Bass.Character.Status = VEHICLE_MOVE;

                //----初期設定
                TGameMgr.Bass.Character.Pos.x = INIT_POSX_BASS;
                TGameMgr.Bass.Character.Spd.dx = -1;
                TGameMgr.Bass.Reverse = 0;
                TGameMgr.Bass.VisitorFlag = 1;

                //[♪] バスバス
                ssPlaySe(THOU_SE_00);
            }
            break;
        //----------------------------------------移動
        case VEHICLE_MOVE:

            //----移動計算
            TGameMgr.Bass.Character.Pos.x += TGameMgr.Bass.Character.Spd.sx * TGameMgr.Bass.Character.Spd.dx;

            if (TGameMgr.Bass.VisitorFlag)
            {
                if (TGameMgr.Bass.Character.Pos.x <= CHECK_POSX_WELCOME_BASS)
                { //----停止チェック、反転
                    //----ライオンの位置確認：ウェルカムチェック
                    if (TGameMgr.Lion.WaitPlace == PLACE_BASS_STATION)
                    {
                        GameMgr.WaitFlag = ON; // iwasawa Correction (2003/4/27)
                        //----ステータス変更：停止へ
                        TGameMgr.Bass.Character.Status = VEHICLE_STOP;

                        //----ライオンステータス変更：ウェルカムウエイト
                        TGameMgr.Lion.Character.Status = LION_WELCOME_WAIT;

                        //----入場者タスク
                        Task.func = VisitorTask;
                        Task.priority = TASK_NO_GAME_VISITOR;
                        Task.attribute = ATTR_USER;
                        Task.status = TASK_NEW_ENTRY;
                        Task.id = TASK_NO_GAME_VISITOR;
                        Task.wait_time = 0;
                        Task.buf = NULL;
                        Task.name = "VisitorTask";
                        Task.mode = TASK_MODE_INIT;
                        Task.user[0] = VISITOR_TYPE_BASS;
                        CreateTask(&Task);

                        TGameMgr.Bass.VisitorFlag = 0;
                        TGameMgr.Bass.Character.Pos.x = CHECK_POSX_WELCOME_BASS + 1;
                    }
                    else
                    {
                        //----ステータス変更：帰りへ
                        TGameMgr.Bass.Character.Status = VEHICLE_RETURN;
                        //----反転
                        TGameMgr.Bass.Character.Spd.dx = 1;
                        TGameMgr.Bass.Reverse = 1;
                    }
                }
            }

            break;
        //----------------------------------------帰り
        case VEHICLE_RETURN:

            //----移動計算
            TGameMgr.Bass.Character.Pos.x += TGameMgr.Bass.Character.Spd.sx * TGameMgr.Bass.Character.Spd.dx;

            if (TGameMgr.Bass.Character.Pos.x > INIT_POSX_BASS)
            {
                //----ステータス変更：消えるへ
                TGameMgr.Bass.Character.Status = VEHICLE_DISAPPEAR;
            }
            break;
        //----------------------------------------停止
        case VEHICLE_STOP:
            break;
        //----------------------------------------消える
        case VEHICLE_DISAPPEAR:
            //----入場者数が980人以上の時はタスク削除
            if (TGameMgr.VisitorScore >= 990)
            {
                ip_task->mode = TASK_MODE_EXIT;
            }
            else
            {
                //----ステータス変更：出現へ
                TGameMgr.Bass.Character.Status = VEHICLE_APPEAR;

                //----生成時間
                TGameMgr.Bass.BirthWaitTime = rand() % 120 + 120;
            }
            break;
        default:
        }

        //----描画
        SpData.No = TGameMgr.Bass.Character.Anm.Data.no;
        SpData.PosX = TGameMgr.Bass.Character.Pos.x + TGameMgr.Bass.Character.OPos.x;
        SpData.PosY = TGameMgr.Bass.Character.Pos.y + TGameMgr.Bass.Character.OPos.y;
        SpData.PosZ = TGameMgr.Bass.Character.Pos.z + TGameMgr.Bass.Character.OPos.z;
        SpData.ScaleX = SCALE10;
        SpData.ScaleY = SCALE10;
        SpData.Rotate = ROTATE000;
        SpData.Reverse = ReverseTable[TGameMgr.Bass.Reverse];
        DrawSprite(&SpData);

        break;
    //----------------------------------------------------------------終了
    case TASK_MODE_EXIT:

        //----自分を削除
        ExitTask(ip_task->id);
        break;
    default:
    }
    return TRUE;
}

//-----------------------------------------------------------------------------
//  関数名  :TrainTask
//
//  work    :電車タスク
//  in      :TASK* ip_task  タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int TrainTask(TASK *ip_task)
{
    SPRITE_DATA SpData;
    TASK Task;

    switch (ip_task->mode)
    {
    //----------------------------------------------------------------初期化
    case TASK_MODE_INIT:
        //---- main
        ip_task->mode = TASK_MODE_MAIN;

        //----バスデータクリア
        TGameMgr.Train.Character.Status = VEHICLE_APPEAR;
        TGameMgr.Train.Character.Anm.Data.no = THOU_CHAR_GAME_TRAIN;
        TGameMgr.Train.Character.Anm.Data.wt = 0;
        TGameMgr.Train.Character.Anm.Index = 0;
        TGameMgr.Train.Character.Pos.x = INIT_POSX_TRAIN;
        TGameMgr.Train.Character.Pos.y = 172;
        TGameMgr.Train.Character.Pos.z = PRIORITY_THOU_GAME_TRAIN;
        TGameMgr.Train.Character.OPos.x = 0;
        TGameMgr.Train.Character.OPos.y = 0;
        TGameMgr.Train.Character.OPos.z = 0;
        TGameMgr.Train.Character.Spd.dx = 1;
        TGameMgr.Train.Character.Spd.dy = 0;
        TGameMgr.Train.Character.Spd.sx = VEHICLE_SPEED_X;
        TGameMgr.Train.Character.Spd.sy = 0;
        TGameMgr.Train.CheckStopX = CHECK_POSX_WELCOME_TRAIN;
        TGameMgr.Train.Reverse = 1;
        TGameMgr.Train.BirthWaitTime = 0;

        break;
    //----------------------------------------------------------------メイン
    case TASK_MODE_MAIN:
        switch (TGameMgr.Train.Character.Status)
        {
        //----------------------------------------出現
        case VEHICLE_APPEAR:
            if (--TGameMgr.Train.BirthWaitTime < 0)
            {
                //----ステータス変更：移動へ
                TGameMgr.Train.Character.Status = VEHICLE_MOVE;

                //----初期設定
                TGameMgr.Train.Character.Pos.x = INIT_POSX_TRAIN;
                TGameMgr.Train.Character.Spd.dx = -1;
                TGameMgr.Train.Reverse = 0;

                //[♪] ガタンガタン
                ssPlaySe(THOU_SE_04);
            }
            break;
        //----------------------------------------移動
        case VEHICLE_MOVE:

            //----移動計算
            TGameMgr.Train.Character.Pos.x += TGameMgr.Train.Character.Spd.sx * TGameMgr.Train.Character.Spd.dx;

            if (TGameMgr.Train.Character.Pos.x == CHECK_POSX_WELCOME_TRAIN)
            { //----停止チェック
                //----ライオンの位置確認：ウェルカムチェック
                if (TGameMgr.Lion.WaitPlace == PLACE_TRAIN_STATION)
                {
                    GameMgr.WaitFlag = ON; // iwasawa Correction (2003/4/27)
                    //----ステータス変更：停止へ
                    TGameMgr.Train.Character.Status = VEHICLE_STOP;

                    //----ライオンステータス変更：ウェルカムウエイト
                    TGameMgr.Lion.Character.Status = LION_WELCOME_WAIT;

                    //----入場者タスク
                    Task.func = VisitorTask;
                    Task.priority = TASK_NO_GAME_VISITOR;
                    Task.attribute = ATTR_USER;
                    Task.status = TASK_NEW_ENTRY;
                    Task.id = TASK_NO_GAME_VISITOR;
                    Task.wait_time = 0;
                    Task.buf = NULL;
                    Task.name = "VisitorTask";
                    Task.mode = TASK_MODE_INIT;
                    Task.user[0] = VISITOR_TYPE_TRAIN;
                    CreateTask(&Task);
                }
                else
                {
                    //[♪] ガタンガタン
                    ssPlaySe(THOU_SE_04);
                }
            }

            if (TGameMgr.Train.Character.Pos.x <= STOP_POSX_TRAIN)
            {
                //----ステータス変更：消えるへ
                TGameMgr.Train.Character.Status = VEHICLE_DISAPPEAR;
            }

            break;
        //----------------------------------------停止
        case VEHICLE_STOP:

            break;
        //----------------------------------------消える
        case VEHICLE_DISAPPEAR:

            //----入場者数が850人以上の時は削除
            if (TGameMgr.VisitorScore > 850)
            {
                ip_task->mode = TASK_MODE_EXIT;
            }
            else
            {
                //----ステータス変更：出現へ
                TGameMgr.Train.Character.Status = VEHICLE_APPEAR;

                //----生成時間
                TGameMgr.Train.BirthWaitTime = rand() % 180 + 180;
            }
            break;
        default:
        }

        //----描画
        SpData.No = TGameMgr.Train.Character.Anm.Data.no;
        SpData.PosX = TGameMgr.Train.Character.Pos.x + TGameMgr.Train.Character.OPos.x;
        SpData.PosY = TGameMgr.Train.Character.Pos.y + TGameMgr.Train.Character.OPos.y;
        SpData.PosZ = TGameMgr.Train.Character.Pos.z + TGameMgr.Train.Character.OPos.z;
        SpData.ScaleX = SCALE10;
        SpData.ScaleY = SCALE10;
        SpData.Rotate = ROTATE000;
        SpData.Reverse = NOREVERS;
        DrawSprite(&SpData);

        break;
    //----------------------------------------------------------------終了
    case TASK_MODE_EXIT:

        //----自分を削除
        ExitTask(ip_task->id);
        break;
    default:
    }
    return TRUE;
}

//-----------------------------------------------------------------------------
//  関数名  :VisitorTask
//
//  work    :入場者タスク
//  in      :TASK* ip_task  タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int VisitorTask(TASK *ip_task)
{
    static int VisitorSpriteTable[] = {
        THOU_CHAR_GAME_VISITOR_NUM_001,
        THOU_CHAR_GAME_VISITOR_NUM_010,
        THOU_CHAR_GAME_VISITOR_NUM_100,
    };

    static int VisitorNumTable[] = {
        1,
        10,
        100};

    static VISITOR_POS VisitorInitPosTable[] = {
        {104, 88},  //TAXI
        {154, 104}, //BASS
        {124, 124}, //TRAIN
    };

    static int VisitorTaskNoTable[] = {
        TASK_NO_GAME_TAXI,
        TASK_NO_GAME_BASS,
        TASK_NO_GAME_TRAIN,
    };

    SPRITE_DATA SpData;
    TASK Task;
    TASK *pTask;

    switch (ip_task->mode)
    {
    //----------------------------------------------------------------初期化
    case TASK_MODE_INIT:
        //---- main
        ip_task->mode = TASK_MODE_MAIN;

        //----初期化
        ip_task->user[1] = VisitorInitPosTable[ip_task->user[0]].PosX;
        ip_task->user[2] = VisitorInitPosTable[ip_task->user[0]].PosY;
        ip_task->user[3] = 0;
        break;
    //----------------------------------------------------------------メイン
    case TASK_MODE_MAIN:

        if (ip_task->user[3] == 0)
        { //移動
            switch (ip_task->user[0])
            {
            case VISITOR_TYPE_TAXI:
                ip_task->user[1] += 1;
                ip_task->user[2] -= 1;
                if (ip_task->user[2] < -50)
                {
                    ip_task->user[3] = 1;
                    //----スコアアップ
                    TGameMgr.VisitorScore += VisitorNumTable[ip_task->user[0]];
                    //call count init
                    TGameMgr.CallCount.Flag = 1;
                    Task.func = CallCountTask;
                    Task.priority = TASK_NO_GAME_CALL_COUNT;
                    Task.attribute = ATTR_USER;
                    Task.status = TASK_NEW_ENTRY;
                    Task.id = TASK_NO_GAME_CALL_COUNT;
                    Task.wait_time = 0;
                    Task.buf = NULL;
                    Task.name = "CallCountTask";
                    Task.mode = TASK_MODE_INIT;
                    Task.user[0] = TGameMgr.VisitorScore;
                    CreateTask(&Task);
                }
                break;
            case VISITOR_TYPE_BASS:
                ip_task->user[2] -= 1;
                if (ip_task->user[2] < -50)
                {
                    ip_task->user[3] = 1;
                    //----スコアアップ
                    TGameMgr.VisitorScore += VisitorNumTable[ip_task->user[0]];
                    //call count init
                    TGameMgr.CallCount.Flag = 1;
                    Task.func = CallCountTask;
                    Task.priority = TASK_NO_GAME_CALL_COUNT;
                    Task.attribute = ATTR_USER;
                    Task.status = TASK_NEW_ENTRY;
                    Task.id = TASK_NO_GAME_CALL_COUNT;
                    Task.wait_time = 0;
                    Task.buf = NULL;
                    Task.name = "CallCountTask";
                    Task.mode = TASK_MODE_INIT;
                    Task.user[0] = TGameMgr.VisitorScore;
                    CreateTask(&Task);
                }
                break;
            case VISITOR_TYPE_TRAIN:
                ip_task->user[2] -= 1;
                if (ip_task->user[2] < -50)
                {
                    ip_task->user[3] = 1;
                    //----スコアアップ
                    TGameMgr.VisitorScore += VisitorNumTable[ip_task->user[0]];
                    //call count init
                    TGameMgr.CallCount.Flag = 1;
                    Task.func = CallCountTask;
                    Task.priority = TASK_NO_GAME_CALL_COUNT;
                    Task.attribute = ATTR_USER;
                    Task.status = TASK_NEW_ENTRY;
                    Task.id = TASK_NO_GAME_CALL_COUNT;
                    Task.wait_time = 0;
                    Task.buf = NULL;
                    Task.name = "CallCountTask";
                    Task.mode = TASK_MODE_INIT;
                    Task.user[0] = TGameMgr.VisitorScore;
                    CreateTask(&Task);
                }
                break;
            default:
            }

            //---
            SpData.No = VisitorSpriteTable[ip_task->user[0]]; //インデックス番号
            SpData.PosX = ip_task->user[1];                   //X位置
            SpData.PosY = ip_task->user[2];                   //Y位置
            SpData.PosZ = PRIORITY_THOU_GAME_VISITOR;         //優先順位
            SpData.ScaleX = SCALE10;                          //スケールX
            SpData.ScaleY = SCALE10;                          //スケールY
            SpData.Rotate = ROTATE000;                        //回転角
            SpData.Reverse = NOREVERS;                        //反転コード
            DrawSprite(&SpData);                              //スプライト描画
        }
        else
        { //カウント
            if (TGameMgr.CallCount.Flag == 0)
            {
                ip_task->mode = TASK_MODE_EXIT;
            }
        }
        break;
    //----------------------------------------------------------------終了
    case TASK_MODE_EXIT:
        if (TGameMgr.VisitorScore >= 1000)
        {
            TGameMgr.VisitorScore = 1000;
            GameMgr.WaitFlag = ON; // iwasawa Correction (2003/4/27)
            //----クリアフラグセット
            TGameMgr.ClearFlag = 1;

            //----ライオンと乗り物タスク削除
            RemoveTask(TASK_NO_GAME_LION);
            RemoveTask(TASK_NO_GAME_TAXI);
            RemoveTask(TASK_NO_GAME_BASS);
            RemoveTask(TASK_NO_GAME_TRAIN);
            SleepTask(TASK_NO_GAME_WINDOWS_SCENE);
            RemoveTask(TASK_NO_GAME_PAUSE);

            //----ゲーム内クリアイベント
            Task.func = ClearGameEventTask;
            Task.priority = TASK_NO_GAME_CLEAR_EVENT;
            Task.attribute = ATTR_USER;
            Task.status = TASK_NEW_ENTRY;
            Task.id = TASK_NO_GAME_CLEAR_EVENT;
            Task.wait_time = 0;
            Task.buf = NULL;
            Task.name = "ClearGameEventTask";
            Task.mode = TASK_MODE_INIT;
            CreateTask(&Task);
        }
        else
        {
            //----ライオンステータス変更：ベース位置で待ち
            TGameMgr.Lion.Character.Status = LION_BASE_WAIT;
            TGameMgr.Lion.WaitTimer = THOU_GAME_LION_BASE_WAIT_TIME;

            //----アニメと位置の補正
            TGameMgr.Lion.WaitPlace = PLACE_BASE;
            TGameMgr.Lion.Character.Anm.Index = 0;
            TGameMgr.Lion.Character.Anm.Data.wt = THOU_LION_ANM_WAIT_TIME;
            TGameMgr.Lion.AnmBase = LION_ANM_BASE_HATA;
            TGameMgr.Lion.Character.Pos.x = GameLionWaitPosTable[TGameMgr.Lion.WaitPlace].PosX;
            TGameMgr.Lion.Character.Pos.y = GameLionWaitPosTable[TGameMgr.Lion.WaitPlace].PosY;

            //----乗り物タスクステータス変更
            switch (ip_task->user[0])
            {
            case VISITOR_TYPE_TAXI:
                //----ステータス変更：帰りへ
                TGameMgr.Taxi.Character.Status = VEHICLE_RETURN;

                //----反転
                TGameMgr.Taxi.Character.Spd.dx = -1;
                TGameMgr.Taxi.Reverse = 0;
                break;
            case VISITOR_TYPE_BASS:
                //----ステータス変更：帰りへ
                TGameMgr.Bass.Character.Status = VEHICLE_RETURN;

                //----反転
                TGameMgr.Bass.Character.Spd.dx = 1;
                TGameMgr.Bass.Reverse = 1;
                //[♪] ガタンガタン
                ssPlaySe(THOU_SE_04);
                break;
            case VISITOR_TYPE_TRAIN:
                //----ステータス変更：移動へ
                TGameMgr.Train.Character.Status = VEHICLE_MOVE;
                break;
            default:
            }
        }

        //----自分を削除
        ExitTask(ip_task->id);
        break;
    default:
    }
    return TRUE;
}

//-----------------------------------------------------------------------------
//  関数名  :WindowSceneTask
//
//  work    :風景タスク
//  in      :TASK* ip_task  タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int WindowSceneTask(TASK *ip_task)
{
    SPRITE_DATA SpData;
    TASK Task;
    static int Counter = 0;

    switch (ip_task->mode)
    {
    //----------------------------------------------------------------初期化
    case TASK_MODE_INIT:
        //---- main
        ip_task->mode = TASK_MODE_MAIN;

        //----初期化
        TGameMgr.SceneNo = 0;
        TGameMgr.Timer = 0;
        TGameMgr.TimerFlag = 0;

        //          //debug
        //          Counter = 100;
        //          TGameMgr.CallCount.Flag = 0;

        break;
    //----------------------------------------------------------------メイン
    case TASK_MODE_MAIN:
        //          if(JstPad & PADLup){
        //              if(++Counter>=1000) Counter = 0;
        //          } else
        //          if(JstPad & PADLdown){
        //              if(--Counter<=0) Counter = 1000;
        //          }else{
        //
        //          }
        //
        //          if( JstPad & PADRright )
        //          {
        //              if(!TGameMgr.CallCount.Flag)
        //              {
        //                  Task.func       = CallCountTask;
        //                  Task.priority   = TASK_NO_GAME_CALL_COUNT;
        //                  Task.attribute  = ATTR_USER;
        //                  Task.status     = TASK_NEW_ENTRY;
        //                  Task.id         = TASK_NO_GAME_CALL_COUNT;
        //                  Task.wait_time  = 0;
        //                  Task.buf        = NULL;
        //                  Task.name       = "CallCountTask";
        //                  Task.mode       = TASK_MODE_INIT;
        //                  Task.user[0]    = Counter;
        //                  CreateTask(&Task);
        //              }
        //          }
        //          FntPrint("CALL NO:[%d]",Counter);

        //----シーン切り替えチェック
#ifdef __DEBUG_THOU_TIME__
        TGameMgr.Timer += 80;
#else
        ++TGameMgr.Timer;
#endif

        if (!TGameMgr.TimerFlag)
        {
            if (TGameMgr.Timer >= TYOU_GAME_CHANGE_SCENE_TIME)
            {
                TGameMgr.Timer = 0;
                if (++TGameMgr.SceneNo >= TYOU_GAME_SCENE_NUM - 1)
                {
                    TGameMgr.TimerFlag = 1;
                    TGameMgr.SceneNo = TYOU_GAME_SCENE_NUM - 1;

                    //  //[♪]BGN停止
                    //  ssStopBgm(THOU_BGM_00);

                    //スクリプト
                    Task.func = ScriptTask;
                    Task.priority = TASK_NO_GAME_SCRIPT;
                    Task.attribute = ATTR_USER;
                    Task.status = TASK_NEW_ENTRY;
                    Task.id = TASK_NO_GAME_SCRIPT;
                    Task.wait_time = 0;
                    Task.buf = NULL;
                    Task.name = "ScriptTask";
                    Task.mode = TASK_MODE_INIT;
                    Task.user[0] = SCRIPT_LINE_2;
                    Task.user[1] = PLAY_GAME_END_SCRIPT_BASE;
                    Task.user[2] = PLAY_GAME_END_SCRIPT_NUM;
                    CreateTask(&Task);

                    //スクリプト終了待ち
                    Task.func = TaskModeExitTimerTask;
                    Task.priority = TASK_NO_GAME_TIMER_EXIT;
                    Task.attribute = ATTR_USER;
                    Task.status = TASK_NEW_ENTRY;
                    Task.id = TASK_NO_GAME_TIMER_EXIT;
                    Task.wait_time = 0;
                    Task.buf = NULL;
                    Task.name = "TaskModeExitTimerTask";
                    Task.mode = TASK_MODE_INIT;
                    Task.user[0] = ip_task->id;
                    Task.user[1] = TIME_UP_SCRIPT_WAIT_TIME;
                    CreateTask(&Task);

                    //----ステータス変更：待ち
                    TGameMgr.Lion.Character.Status = LION_WAIT;
                    TGameMgr.Taxi.Character.Status = VEHICLE_STOP;
                    TGameMgr.Bass.Character.Status = VEHICLE_STOP;
                    TGameMgr.Train.Character.Status = VEHICLE_STOP;

                    //削除
                    RemoveTask(TASK_NO_GAME_VISITOR);
                    RemoveTask(TASK_NO_GAME_PAUSE);
                }
            }
        }

        //---風景
        SpData.No = SceneSpriteTable[TGameMgr.SceneNo]; //インデックス番号
        SpData.PosX = 13;                               //X位置
        SpData.PosY = 20;                               //Y位置
        SpData.PosZ = PRIORITY_THOU_GAME_WINDOW_SCENE;  //優先順位
        SpData.ScaleX = SCALE10;                        //スケールX
        SpData.ScaleY = SCALE10;                        //スケールY
        SpData.Rotate = ROTATE000;                      //回転角
        SpData.Reverse = NOREVERS;                      //反転コード
        DrawSprite(&SpData);                            //スプライト描画

        break;
    //----------------------------------------------------------------終了
    case TASK_MODE_EXIT:
        //----タイムアップフラグセット
        GameMgr.WaitFlag = ON; // iwasawa Correction (2003/4/27)
        TGameMgr.TimeUpFlag = 1;

        //----自分を削除
        ExitTask(ip_task->id);
        break;
    default:
    }
    return TRUE;
}

//-----------------------------------------------------------------------------
//  関数名  :GameBgTask
//
//  work    :背景タスク
//  in      :TASK* ip_task  タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int GameBgTask(TASK *ip_task)
{
    static int TaxiStationPlateSpriteTable[] = {
        THOU_CHAR_GAME_TAXI_STATION_00,
        THOU_CHAR_GAME_TAXI_STATION_01,
    };

    static int BassStationPlateSpriteTable[] = {
        THOU_CHAR_GAME_BASS_STATION_00,
        THOU_CHAR_GAME_BASS_STATION_01,
    };

    static int TrainStationPlateSpriteTable[] = {
        THOU_CHAR_GAME_TRAIN_STATION_PLATE_00,
        THOU_CHAR_GAME_TRAIN_STATION_PLATE_01,
    };

    SPRITE_DATA SpData;

    switch (ip_task->mode)
    {
    //----------------------------------------------------------------初期化
    case TASK_MODE_INIT:
        //---- main
        ip_task->mode = TASK_MODE_MAIN;

        break;
    //----------------------------------------------------------------メイン
    case TASK_MODE_MAIN:

        //----タクシー
        if (TGameMgr.Lion.WaitPlace == PLACE_TAXI_STATION)
            SpData.No = TaxiStationPlateSpriteTable[1];
        else
            SpData.No = TaxiStationPlateSpriteTable[0];
        SpData.PosX = 74;
        SpData.PosY = 68;
        SpData.PosZ = PRIORITY_THOU_GAME_BG - 1;
        SpData.ScaleX = SCALE10;
        SpData.ScaleY = SCALE10;
        SpData.Rotate = ROTATE000;
        SpData.Reverse = NOREVERS;
        DrawSprite(&SpData);

        //----バス
        if (TGameMgr.Lion.WaitPlace == PLACE_BASS_STATION)
            SpData.No = BassStationPlateSpriteTable[1];
        else
            SpData.No = BassStationPlateSpriteTable[0];
        SpData.PosX = 198;
        SpData.PosY = 80;
        SpData.PosZ = PRIORITY_THOU_GAME_BG - 1;
        SpData.ScaleX = SCALE10;
        SpData.ScaleY = SCALE10;
        SpData.Rotate = ROTATE000;
        SpData.Reverse = NOREVERS;
        DrawSprite(&SpData);

        //----駅プレート
        if (TGameMgr.Lion.WaitPlace == PLACE_TRAIN_STATION)
            SpData.No = TrainStationPlateSpriteTable[1];
        else
            SpData.No = TrainStationPlateSpriteTable[0];
        SpData.PosX = 128;
        SpData.PosY = 126;
        SpData.PosZ = PRIORITY_THOU_GAME_STATION - 1;
        SpData.ScaleX = SCALE10;
        SpData.ScaleY = SCALE10;
        SpData.Rotate = ROTATE000;
        SpData.Reverse = NOREVERS;
        DrawSprite(&SpData);

        //----駅
        SpData.No = THOU_CHAR_GAME_TRAIN_STATION;
        SpData.PosX = 119;
        SpData.PosY = 154;
        SpData.PosZ = PRIORITY_THOU_GAME_STATION;
        SpData.ScaleX = SCALE10;
        SpData.ScaleY = SCALE10;
        SpData.Rotate = ROTATE000;
        SpData.Reverse = NOREVERS;
        DrawSprite(&SpData);

        //----背景左
        SpData.No = THOU_CHAR_GAME_BG_00;
        SpData.PosX = 0;
        SpData.PosY = 0;
        SpData.PosZ = PRIORITY_THOU_GAME_BG;
        SpData.ScaleX = SCALE10;
        SpData.ScaleY = SCALE10;
        SpData.Rotate = ROTATE000;
        SpData.Reverse = NOREVERS;
        DrawSprite(&SpData);

        //----背景右
        SpData.No = THOU_CHAR_GAME_BG_01;
        SpData.PosX = 256;
        SpData.PosY = 0;
        SpData.PosZ = PRIORITY_THOU_GAME_BG;
        SpData.ScaleX = SCALE10;
        SpData.ScaleY = SCALE10;
        SpData.Rotate = ROTATE000;
        SpData.Reverse = NOREVERS;
        DrawSprite(&SpData);

        break;
    //----------------------------------------------------------------終了
    case TASK_MODE_EXIT:

        //----自分を削除
        ExitTask(ip_task->id);
        break;
    default:
    }
}

//-----------------------------------------------------------------------------
//  関数名  :VisitorScoreTask
//
//  work    :入場者数タスク
//  in      :TASK* ip_task
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int VisitorScoreTask(TASK *ip_task)
{
    SPRITE_DATA SpData;

    switch (ip_task->mode)
    {
    //----------------------------------------------------------------初期化
    case TASK_MODE_INIT:
        //---- main
        ip_task->mode = TASK_MODE_MAIN;

        //----初期化

        break;
    //----------------------------------------------------------------メイン
    case TASK_MODE_MAIN:

        if (ip_task->user[0] != 0)
        {
            if (++ip_task->user[0] > 0)
                ip_task->user[0] = 0;
        }

        DrawScore(TGameMgr.VisitorScore,
                  VISITOR_SCORE_NUM_WIDE,
                  VisitorScoreSpriteTable,
                  121,
                  ip_task->user[0] + 35,
                  PRIORITY_THOU_GAME_VISITOR_SCORE - 1);

        //----プレート
        SpData.No = THOU_CHAR_GAME_SCORE_PLATE;         //インデックス番号
        SpData.PosX = 112;                              //X位置
        SpData.PosY = ip_task->user[0];                 //Y位置
        SpData.PosZ = PRIORITY_THOU_GAME_VISITOR_SCORE; //優先順位
        SpData.ScaleX = SCALE10;                        //スケールX
        SpData.ScaleY = SCALE10;                        //スケールY
        SpData.Rotate = ROTATE000;                      //回転角
        SpData.Reverse = NOREVERS;                      //反転コード
        DrawSprite(&SpData);                            //スプライト描画

        break;
    //----------------------------------------------------------------終了
    case TASK_MODE_EXIT:

        //----自分を削除
        ExitTask(ip_task->id);
        break;
    default:
    }
    return TRUE;
}

//-----------------------------------------------------------------------------
//  関数名  :HighScoreTask
//
//  work    :ハイスコアタスク
//  in      :TASK* ip_task
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int HighScoreTask(TASK *ip_task)
{

    switch (ip_task->mode)
    {
    //----------------------------------------------------------------初期化
    case TASK_MODE_INIT:
        //---- main
        ip_task->mode = TASK_MODE_MAIN;

        break;
    //----------------------------------------------------------------メイン
    case TASK_MODE_MAIN:
        DrawScore(TGameMgr.HighScore,
                  HIGH_SCORE_NUM_WIDE,
                  HighScoreSpriteTable,
                  250,
                  33,
                  PRIORITY_THOU_GAME_HIGH_SCORE);
        break;
    //----------------------------------------------------------------終了
    case TASK_MODE_EXIT:

        //----自分を削除
        ExitTask(ip_task->id);
        break;
    default:
    }
}

//-----------------------------------------------------------------------------
//  関数名  :PauseTask
//
//  work    :ポーズ監視タスク
//  in      :TASK* ip_task  タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int PauseTask(TASK *ip_task)
{
    TASK Task;
    int ret;

    switch (ip_task->mode)
    {
    //----------------------------------------------------------------タスク初期化
    case TASK_MODE_INIT:
        //next MAIN
        ip_task->mode = TASK_MODE_MAIN;

        //Flag
        ip_task->user[0] = 0;

        //メニューフラグチェック
        GameMgr.WaitFlag = OFF;

        break;
    //----------------------------------------------------------------タスクメイン
    case TASK_MODE_MAIN:
        if (!ip_task->user[0])
        { //メニューオープン待ち
            ret = MainMenuCheck10();

            if (ret == ON)
            { //スタートボタン押される
                //停止コントロールフラグセット
                ip_task->user[0] = 1;

                //タスクスリープ
                SleepTask(TASK_NO_GAME_LION);
                SleepTask(TASK_NO_GAME_BASS);
                SleepTask(TASK_NO_GAME_TAXI);
                SleepTask(TASK_NO_GAME_TRAIN);
                SleepTask(TASK_NO_GAME_WINDOWS_SCENE);
                SleepTask(TASK_NO_GAME_VISITOR);
            }
            else
            {
            }
        }
        else
        { //メニュー選択中
            ret = MainMenuCheck10();

            if (ret == OFF)
            { //メニューオフ
                //起動コントロールフラグセット
                ip_task->user[0] = 0;

                //タスクウェイクアップ
                WakeupTask(TASK_NO_GAME_LION);
                WakeupTask(TASK_NO_GAME_BASS);
                WakeupTask(TASK_NO_GAME_TAXI);
                WakeupTask(TASK_NO_GAME_TRAIN);
                WakeupTask(TASK_NO_GAME_WINDOWS_SCENE);
                WakeupTask(TASK_NO_GAME_VISITOR);
            }
            else if (ret == MEIN_MENU_OWARI)
            { //ゲーム終了
                Task.func = PauseMenuFadeOutTask;
                Task.priority = TASK_NO_GAME_FADE;
                Task.attribute = ATTR_USER;
                Task.status = TASK_NEW_ENTRY;
                Task.id = TASK_NO_GAME_FADE;
                Task.wait_time = 0;
                Task.buf = NULL;
                Task.name = "PauseMenuFadeOutTask";
                Task.mode = TASK_MODE_INIT;
                CreateTask(&Task);

                //タスク終了
                ip_task->mode = TASK_MODE_EXIT;
            }
            else
            {
            }
        }

        break;
    //----------------------------------------------------------------タスク終了
    case TASK_MODE_EXIT:
        //メニューフラグチェック
        GameMgr.WaitFlag = ON;

        //自分を削除
        ExitTask(ip_task->id);

        break;
    default:
    }
    return TRUE;
}

//-----------------------------------------------------------------------------
//  関数名  :EventFadeOutTask
//
//  work    :フェードアウトタスク
//  in      :タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int EventFadeOutTask(TASK *ip_task)
{
    TASK *pTask;

    switch (ip_task->mode)
    {
    //---------------------------------------------------------------------
    case TASK_MODE_INIT:
        //next MAIN
        ip_task->mode = TASK_MODE_MAIN;

        // フェードOUTします
        GameMgr.FadeFlag = FadeOut;
        break;
    //---------------------------------------------------------------------
    case TASK_MODE_MAIN:

        //フェードアウト
        if (GameMgr.FadeFlag == FadeOutOk)
        {
            ip_task->mode = TASK_MODE_EXIT;
        }

        break;
    //---------------------------------------------------------------------
    case TASK_MODE_EXIT:
        pTask = SearchTask(ip_task->user[0]);
        if (pTask != NULL)
        {
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
static int PauseMenuFadeOutTask(TASK *ip_task)
{
    switch (ip_task->mode)
    {
    //---------------------------------------------------------------------
    case TASK_MODE_INIT:
        //next MAIN
        ip_task->mode = TASK_MODE_MAIN;

        GameMgr.FadeFlag = FadeOut; // フェードOUTします
        break;
    //---------------------------------------------------------------------
    case TASK_MODE_MAIN:

        //フェードアウト
        if (GameMgr.FadeFlag == FadeOutOk)
        {
            ip_task->mode = TASK_MODE_EXIT;
        }

        break;
    //---------------------------------------------------------------------
    case TASK_MODE_EXIT:

        //終了フラグセット
        TGameMgr.ExitFlag = 1;

        //自分を削除
        ExitTask(ip_task->id);
        break;
    default:
    }
    return TRUE;
}

//-----------------------------------------------------------------------------
//  関数名  :ScriptTask
//
//  work    :スクリプトタスク
//  in      :TASK* ip_task
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int ScriptTask(TASK *ip_task)
{

    switch (ip_task->mode)
    {
    //---------------------------------------------------------------------
    case TASK_MODE_INIT:
        //next MAIN
        ip_task->mode = TASK_MODE_MAIN;

        TGameMgr.Script.Flag = 0;
        TGameMgr.Script.Index = 0;
        TGameMgr.Script.Line = ip_task->user[0];
        TGameMgr.Script.Base = ip_task->user[1];
        TGameMgr.Script.Num = ip_task->user[2];

        break;
    //---------------------------------------------------------------------
    case TASK_MODE_MAIN:

        if (MetuseijiFlag == OFF)
        {
            switch (TGameMgr.Script.Line)
            {
            case SCRIPT_LINE_1:
                MenuMessageSet10(&ThouScript[TGameMgr.Script.Base + TGameMgr.Script.Index]);
                break;
            case SCRIPT_LINE_2:
                MenuMessageSet20(&ThouScript[TGameMgr.Script.Base + TGameMgr.Script.Index]);
                break;
            case SCRIPT_LINE_3:
                MenuMessageSet30(&ThouScript[TGameMgr.Script.Base + TGameMgr.Script.Index]);
                break;
            default:
            }

            if (++TGameMgr.Script.Index >= TGameMgr.Script.Num)
            {
                ip_task->mode = TASK_MODE_EXIT;
            }
        }
        break;
    //---------------------------------------------------------------------
    case TASK_MODE_EXIT:

        //自分を削除
        ExitTask(ip_task->id);
        break;
    default:
    }
    return TRUE;
}

//-----------------------------------------------------------------------------
//  関数名  :TaskModeExitTimerTask
//
//  work    :タイマーで指定したタスクのモードをEXITにする
//  in      :TASK* ip_task  タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int TaskModeExitTimerTask(TASK *ip_task)
{
    TASK *pTask;

    switch (ip_task->mode)
    {
    //---------------------------------------------------------------------
    case TASK_MODE_INIT:
        //next MAIN
        ip_task->mode = TASK_MODE_MAIN;

        break;
    //---------------------------------------------------------------------
    case TASK_MODE_MAIN:

        if (--ip_task->user[1] <= 0)
        {
            pTask = SearchTask(ip_task->user[0]);
            if (pTask != NULL)
            {
                pTask->mode = TASK_MODE_EXIT;
            }
            ip_task->mode = TASK_MODE_EXIT;
        }
        break;
    //---------------------------------------------------------------------
    case TASK_MODE_EXIT:

        //自分を削除
        ExitTask(ip_task->id);
        break;
    default:
    }
    return TRUE;
}

//-----------------------------------------------------------------------------
//  関数名  :CallCountTask
//
//  work    :数字を読み上げタスク
//  in      :TASK* ip_task  タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int CallCountTask(TASK *ip_task)
{
    TASK *pTask;

    switch (ip_task->mode)
    {
    //---------------------------------------------------------------------
    case TASK_MODE_INIT:
        //next MAIN
        ip_task->mode = TASK_MODE_MAIN;

        if (ip_task->user[0] > 1000)
            ip_task->user[0] = 1000;
        if (ip_task->user[0] < 0)
            ip_task->user[0] = 0;

        ip_task->user[1] = 0; //mode
        ip_task->user[2] = 0; //timer

        //コールカウントフラグセット
        TGameMgr.CallCount.Flag = 1;
        TGameMgr.CallCount.Num = CallCountData[ip_task->user[0]].FileNum;
        TGameMgr.CallCount.Timer = GET_DA_STATUS_WAIT_TIME;
        //一つ目をコール
        //[♪]：
        dsPlayXa(CallCountData[ip_task->user[0]].Xa1.FileNo,
                 CallCountData[ip_task->user[0]].Xa1.ChannelNo);

        break;
    //---------------------------------------------------------------------
    case TASK_MODE_MAIN:
        if (--TGameMgr.CallCount.Timer <= 0)
        {
            if (ip_task->user[1] == 0)
            { //
                if (dSoundStatus == DslStatStandby)
                { //スタンバイなら次を読みに行く
                    if (--TGameMgr.CallCount.Num <= 0)
                    { //抜ける
                        ip_task->mode = TASK_MODE_EXIT;
                    }
                    else
                    {
                        //２つ目をコール
                        //[♪]：
                        dsPlayXa(CallCountData[ip_task->user[0]].Xa2.FileNo,
                                 CallCountData[ip_task->user[0]].Xa2.ChannelNo);

                        TGameMgr.CallCount.Timer = GET_DA_STATUS_WAIT_TIME;
                        ip_task->user[1] = 1;
                    }
                }
                else if ((dSoundStatus & DslStatSeek) || (dSoundStatus & DslStatRead))
                {
#ifdef __DEBUG_THOU__
                    FntPrint("DslStatSeek or DslStatRead \n");
#endif
                }
                else
                {
                }
            }
            else
            { //
                if (dSoundStatus == DslStatStandby)
                { //スタンバイなら終了へ
                    ip_task->mode = TASK_MODE_EXIT;
                }
                else if ((dSoundStatus & DslStatSeek) || (dSoundStatus & DslStatRead))
                {
#ifdef __DEBUG_THOU__
                    FntPrint("DslStatSeek or DslStatRead \n");
#endif
                }
                else
                {
                }
            }
        }
        break;
    //---------------------------------------------------------------------
    case TASK_MODE_EXIT:

        //コールカウントフラグオフ
        TGameMgr.CallCount.Flag = 0;

        //自分を削除
        ExitTask(ip_task->id);
        break;
    default:
    }
    return TRUE;
}

//-----------------------------------------------------------------------------
//  関数名  :ClearGameEventTask
//
//  work    :ゲーム内クリアイベント
//  in      :TASK* ip_task  タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int ClearGameEventTask(TASK *ip_task)
{
    static int GakudaninSpriteTable[] = {
        THOU_CHAR_GAME_DANTYOU_00,
        THOU_CHAR_GAME_DANTYOU_01,
        THOU_CHAR_GAME_GAKUDANIN_FUUSEN_B_00,
        THOU_CHAR_GAME_GAKUDANIN_FUUSEN_B_01,
        THOU_CHAR_GAME_GAKUDANIN_HATA_T_00,
        THOU_CHAR_GAME_GAKUDANIN_HATA_T_01,
        THOU_CHAR_GAME_GAKUDANIN_HATA_Y_00,
        THOU_CHAR_GAME_GAKUDANIN_HATA_Y_01,
        THOU_CHAR_GAME_GAKUDANIN_FUUSEN_O_00,
        THOU_CHAR_GAME_GAKUDANIN_FUUSEN_O_01,
    };
    int i;
    SPRITE_DATA SpData;

    switch (ip_task->mode)
    {
    //----------------------------------------------------------------タスク初期化
    case TASK_MODE_INIT:
        //next MAIN
        ip_task->mode = TASK_MODE_MAIN;

        //----初期化
        TGameMgr.ClearGame.Mode = 0;
        TGameMgr.ClearGame.Index = 0;
        TGameMgr.ClearGame.WaitTime = 0;
        TGameMgr.ClearGame.Timer = 0;
        TGameMgr.ClearGame.Pos[0].PosX = 330;
        TGameMgr.ClearGame.Pos[0].PosY = 174;
        TGameMgr.ClearGame.Pos[1].PosX = -98;
        TGameMgr.ClearGame.Pos[1].PosY = 84;
        TGameMgr.ClearGame.Pos[2].PosX = -58;
        TGameMgr.ClearGame.Pos[2].PosY = 84;
        TGameMgr.ClearGame.Pos[3].PosX = 354;
        TGameMgr.ClearGame.Pos[3].PosY = 106;
        TGameMgr.ClearGame.Pos[4].PosX = 394;
        TGameMgr.ClearGame.Pos[4].PosY = 106;

        //[♪]BGN停止
        ssStopBgm(THOU_BGM_00);
        //[♪]　BGM
        ssPlayBgm(THOU_BGM_00);

        break;
    //----------------------------------------------------------------タスクメイン
    case TASK_MODE_MAIN:
        switch (TGameMgr.ClearGame.Mode)
        {
        //----------------団長出現
        case 0:
            //----移動
            if (--TGameMgr.ClearGame.Pos[0].PosX <= 136)
            {
                TGameMgr.ClearGame.Mode = 1;
            }

            break;
        //----------------団員出現
        case 1:
            //----移動
            ++TGameMgr.ClearGame.Pos[1].PosX;
            ++TGameMgr.ClearGame.Pos[2].PosX;
            --TGameMgr.ClearGame.Pos[3].PosX;
            --TGameMgr.ClearGame.Pos[4].PosX;

            if (++TGameMgr.ClearGame.Timer > 130)
            {
                TGameMgr.ClearGame.Timer = 0;
                TGameMgr.ClearGame.Mode = 2;
            }
            break;
        //----------------音楽演奏終了まで
        case 2:
            if (++TGameMgr.ClearGame.Timer > 300)
            {
                ip_task->mode = TASK_MODE_EXIT;
            }

            break;
        default:
        }

        //----アニメ
        if (++TGameMgr.ClearGame.WaitTime > 30)
        {
            TGameMgr.ClearGame.WaitTime = 0;
            TGameMgr.ClearGame.Index ^= 1;
        }
        //----描画
        for (i = 0; i < 5; i++)
        {
            SpData.No = GakudaninSpriteTable[i * 2 + TGameMgr.ClearGame.Index]; //インデックス番号
            SpData.PosX = TGameMgr.ClearGame.Pos[i].PosX;                       //X位置
            SpData.PosY = TGameMgr.ClearGame.Pos[i].PosY;                       //Y位置
            SpData.PosZ = PRIORITY_THOU_GAME_GAKUDANIN;                         //優先順位
            SpData.ScaleX = SCALE10;                                            //スケールX
            SpData.ScaleY = SCALE10;                                            //スケールY
            SpData.Rotate = ROTATE000;                                          //回転角
            SpData.Reverse = NOREVERS;                                          //反転コード
            DrawSprite(&SpData);                                                //スプライト描画
        }
        break;
    //----------------------------------------------------------------タスク終了
    case TASK_MODE_EXIT:

        //----ゲームコントローラ終了
        TGameMgr.ClearEndFlag = 1;

        //----自分を削除
        ExitTask(ip_task->id);
        break;
    default:
    }
    return TRUE;
}

//-----------------------------------------------------------------------------
//  関数名  :ThouClearEventTask
//
//  work    :クリアイベントタスク
//  in      :TASK* ip_task  タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int ThouClearEventTask(TASK *ip_task)
{
    SPRITE_DATA SpData;
    TASK Task;

    switch (ip_task->mode)
    {
    //----------------------------------------------------------------タスク初期化
    case TASK_MODE_INIT:
        //next MAIN
        ip_task->mode = TASK_MODE_MAIN;

        //----texture read sram -> vram
        if ((file_read(ThouEventTextureFile[0].fn, LoadAddress)) == -1)
        { //read error
            return FALSE;
        }

        //----texture init
        TexInit(THOU_EVENT_TIM_NUM, &ThouEventTextureImage[THOU_EVENT_TIM_POS]);
        TimImgData = ThouEventTextureImage;

        //----イベント用スプライト登録
        EntrySprite(ThouEventSpriteData);

        //----初期化
        ip_task->user[0] = 0;
        ip_task->user[1] = 0;
        ip_task->user[2] = 0; //flag
        ip_task->user[3] = 0; //timer
        TGameMgr.EventTimer = 0;
        TGameMgr.EventEndFlag = 0;

        //----終了処理メニュー
        TGameMgr.SelectContinue.Val = 0;
        TGameMgr.SelectContinue.Type = SELECT_RETRY_H;
        TGameMgr.SelectContinue.No = 0;
        TGameMgr.SelectContinue.Wt = 0;
        TGameMgr.SelectContinue.FadeFlag = 0;

#ifdef __DEBUG_THOU__
        //フェードイン
        GameMgr.FadeFlag = FadeIn;
#endif

        //[♪]：パッパパカー
        dsPlayXa(XA_FILE_THOU02, 5);
        ip_task->user[3] = GET_DA_STATUS_WAIT_TIME;

        break;
    //----------------------------------------------------------------タスクメイン
    case TASK_MODE_MAIN:
        //----クリアイベント終了チェック
        if (++TGameMgr.EventTimer >= TOUH_GAME_CLEAR_EVENT_END_TIME)
        {
            TGameMgr.EventEndFlag = 1;
        }

        if (--ip_task->user[3] <= 0)
        {
            if (!ip_task->user[2])
            {
                if (dSoundStatus == DslStatStandby)
                {
                    ip_task->user[2] = 1;
                    //スクリプト
                    Task.func = ScriptTask;
                    Task.priority = TASK_NO_GAME_SCRIPT;
                    Task.attribute = ATTR_USER;
                    Task.status = TASK_NEW_ENTRY;
                    Task.id = TASK_NO_GAME_SCRIPT;
                    Task.wait_time = 0;
                    Task.buf = NULL;
                    Task.name = "ScriptTask";
                    Task.mode = TASK_MODE_INIT;
                    Task.user[0] = SCRIPT_LINE_2;
                    Task.user[1] = PLAY_CLEAR_SCRIPT_BASE;
                    Task.user[2] = PLAY_CLEAR_SCRIPT_NUM;
                    CreateTask(&Task);
                }
            }
        }

        //----手アニメ
        if (++ip_task->user[0] > 30)
        {
            ip_task->user[0] = 0;
            ip_task->user[1] ^= 1;
        }

        //----手
        if (ip_task->user[1])
        {
            SpData.No = THOU_CHAR_EVENT_CLEAR_02;     //インデックス番号
            SpData.PosX = 144;                        //X位置
            SpData.PosY = 104;                        //Y位置
            SpData.PosZ = PRIORITY_THOU_EVENT_BG - 2; //優先順位
            SpData.ScaleX = SCALE10;                  //スケールX
            SpData.ScaleY = SCALE10;                  //スケールY
            SpData.Rotate = ROTATE000;                //回転角
            SpData.Reverse = NOREVERS;                //反転コード
            DrawSprite(&SpData);                      //スプライト描画
        }

        //----背景左
        SpData.No = THOU_CHAR_EVENT_CLEAR_00; //インデックス番号
        SpData.PosX = 0;                      //X位置
        SpData.PosY = 0;                      //Y位置
        SpData.PosZ = PRIORITY_THOU_EVENT_BG; //優先順位
        SpData.ScaleX = SCALE10;              //スケールX
        SpData.ScaleY = SCALE10;              //スケールY
        SpData.Rotate = ROTATE000;            //回転角
        SpData.Reverse = NOREVERS;            //反転コード
        DrawSprite(&SpData);                  //スプライト描画

        //----背景右
        SpData.No = THOU_CHAR_EVENT_CLEAR_01;     //インデックス番号
        SpData.PosX = 256;                        //X位置
        SpData.PosY = 0;                          //Y位置
        SpData.PosZ = PRIORITY_THOU_EVENT_BG - 1; //優先順位
        SpData.ScaleX = SCALE10;                  //スケールX
        SpData.ScaleY = SCALE10;                  //スケールY
        SpData.Rotate = ROTATE000;                //回転角
        SpData.Reverse = NOREVERS;                //反転コード
        DrawSprite(&SpData);                      //スプライト描画

        //----もう一度プレイしますか？
        if (TGameMgr.EventEndFlag)
        {
            if (SelectContinue())
            { //●ボタンが押された
                if (!TGameMgr.SelectContinue.FadeFlag)
                { //フェード中
                    if ((TGameMgr.SelectContinue.Val == 0) && (TGameMgr.SelectContinue.Type == SELECT_RETRY_H))
                    { //もう一度プレイしますか？　はい
                        //next EXIT
                        TGameMgr.SelectContinue.FadeFlag = 1;

                        Task.func = EventFadeOutTask;
                        Task.priority = TASK_NO_GAME_FADE;
                        Task.attribute = ATTR_USER;
                        Task.status = TASK_NEW_ENTRY;
                        Task.id = TASK_NO_GAME_FADE;
                        Task.wait_time = 0;
                        Task.buf = NULL;
                        Task.name = "EventFadeOutTask";
                        Task.mode = TASK_MODE_INIT;
                        Task.user[0] = ip_task->id;
                        CreateTask(&Task);
                    }
                    else if ((TGameMgr.SelectContinue.Val == 1) && (TGameMgr.SelectContinue.Type == SELECT_RETRY_H))
                    { //もう一度プレイしますか？　いいえ
                        TGameMgr.SelectContinue.Type = SELECT_END_H;
                        TGameMgr.SelectContinue.Val = 0;
                    }
                    else if ((TGameMgr.SelectContinue.Type == SELECT_END_H) && (TGameMgr.SelectContinue.Val == 0))
                    { //やめますか？　はい
                        //next EXIT
                        TGameMgr.SelectContinue.FadeFlag = 1;

                        Task.func = EventFadeOutTask;
                        Task.priority = TASK_NO_GAME_FADE;
                        Task.attribute = ATTR_USER;
                        Task.status = TASK_NEW_ENTRY;
                        Task.id = TASK_NO_GAME_FADE;
                        Task.wait_time = 0;
                        Task.buf = NULL;
                        Task.name = "EventFadeOutTask";
                        Task.mode = TASK_MODE_INIT;
                        Task.user[0] = ip_task->id;
                        CreateTask(&Task);
                    }
                    else if ((TGameMgr.SelectContinue.Type == SELECT_END_H) && (TGameMgr.SelectContinue.Val == 1))
                    { //やめますか？　いいえ
                        TGameMgr.SelectContinue.Type = SELECT_RETRY_H;
                        TGameMgr.SelectContinue.Val = 0;
                    }
                    else
                    {
                    }
                }
            }
            else
            {
            }
        }

        break;
    //----------------------------------------------------------------タスク終了
    case TASK_MODE_EXIT:
        //----登録スプライト開放
        ReleaseSprite();

        //継続プレイフラグ
        TGameMgr.ContinureFlag = 1;

        //--------------------ここは２択
        //  (1)ゲームを続ける
        //  (2)メインメニュー
        if ((TGameMgr.SelectContinue.Type == SELECT_END_H) && (TGameMgr.SelectContinue.Val == 0))
        { //----ゲームをおわります
            TGameMgr.ExitFlag = 1;
        }
        else
        { //----ゲームコントロールタスク
            Task.func = GameControllTask;
            Task.priority = TASK_NO_GAME_CONTROLL;
            Task.attribute = ATTR_USER;
            Task.status = TASK_NEW_ENTRY;
            Task.id = TASK_NO_GAME_CONTROLL;
            Task.wait_time = 0;
            Task.buf = NULL;
            Task.name = "GameControllTask";
            Task.mode = TASK_MODE_INIT;
            CreateTask(&Task);
        }

        //自分を削除
        ExitTask(ip_task->id);
        break;
    default:
    }
    return TRUE;
}

//-----------------------------------------------------------------------------
//  関数名  :ThouFalseEventTask
//
//  work    :失敗イベントタスク
//  in      :TASK* ip_task  タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int ThouFalseEventTask(TASK *ip_task)
{
    TASK Task;
    SPRITE_DATA SpData;

    switch (ip_task->mode)
    {
    //----------------------------------------------------------------タスク初期化
    case TASK_MODE_INIT:
        //next MAIN
        ip_task->mode = TASK_MODE_MAIN;

        //----texture read sram -> vram
        if ((file_read(ThouEventTextureFile[0].fn, LoadAddress)) == -1)
        { //read error
            return FALSE;
        }

        //----texture init
        TexInit(THOU_EVENT_TIM_NUM, &ThouEventTextureImage[THOU_EVENT_TIM_POS]);
        TimImgData = ThouEventTextureImage;

        //----イベント用スプライト登録
        EntrySprite(ThouEventSpriteData);

        //----初期化
        ip_task->user[0] = 0;
        ip_task->user[1] = 0;
        ip_task->user[2] = 0;
        ip_task->user[3] = 0;
        ip_task->user[4] = 0; //コールカウントフラグ
        ip_task->user[5] = 0;
        ip_task->user[6] = 0;
        ip_task->user[7] = 0;
        TGameMgr.EventTimer = 0;
        TGameMgr.EventEndFlag = 0;

        //----終了処理メニュー
        TGameMgr.SelectContinue.Val = 0;
        TGameMgr.SelectContinue.Type = SELECT_RETRY_H;
        TGameMgr.SelectContinue.No = 0;
        TGameMgr.SelectContinue.Wt = 0;
        TGameMgr.SelectContinue.FadeFlag = 0;

#ifdef __DEBUG_THOU__
        //フェードイン
        GameMgr.FadeFlag = FadeIn;
#endif

        //スクリプト
        Task.func = ScriptTask;
        Task.priority = TASK_NO_GAME_SCRIPT;
        Task.attribute = ATTR_USER;
        Task.status = TASK_NEW_ENTRY;
        Task.id = TASK_NO_GAME_SCRIPT;
        Task.wait_time = 0;
        Task.buf = NULL;
        Task.name = "ScriptTask";
        Task.mode = TASK_MODE_INIT;
        Task.user[0] = SCRIPT_LINE_2;
        Task.user[1] = PLAY_FALSE_1_SCRIPT_BASE;
        Task.user[2] = PLAY_FALSE_1_SCRIPT_NUM;
        CreateTask(&Task);

        break;
    //----------------------------------------------------------------タスクメイン
    case TASK_MODE_MAIN:
        //----イベント終了チェック
        if (++TGameMgr.EventTimer > TOUH_GAME_FALSE_EVENT_END_TIME)
        {
            TGameMgr.EventEndFlag = 1;
        }

        //コールカウント
        if (TGameMgr.EventTimer == TOUH_GAME_FALSE_CALL_COUNT_TIME)
        {
            ip_task->user[4] = 1;
            TGameMgr.CallCount.Flag = 1;
            Task.func = CallCountTask;
            Task.priority = TASK_NO_GAME_CALL_COUNT;
            Task.attribute = ATTR_USER;
            Task.status = TASK_NEW_ENTRY;
            Task.id = TASK_NO_GAME_CALL_COUNT;
            Task.wait_time = 0;
            Task.buf = NULL;
            Task.name = "CallCountTask";
            Task.mode = TASK_MODE_INIT;
            Task.user[0] = TGameMgr.VisitorScore;
            CreateTask(&Task);
        }

        //コールカウント終了後
        if (!ip_task->user[5])
        {
            if (ip_task->user[4] && (TGameMgr.CallCount.Flag == 0))
            {
                //[♪]：パッパパカー
                dsPlayXa(XA_FILE_THOU02, 5);
                ip_task->user[5] = 1;
                ip_task->user[7] = GET_DA_STATUS_WAIT_TIME;
            }
        }

        //更新の場合処理
        if (TGameMgr.HighScoreFlag)
        {
            //上のXAがなり終わったら更新のXA
            if (ip_task->user[5])
            {
                if (--ip_task->user[7] <= 0)
                {
                    if (!ip_task->user[6])
                    {
                        if (dSoundStatus == DslStatStandby)
                        {
                            ip_task->user[6] = 1;
                            //スクリプト
                            Task.func = ScriptTask;
                            Task.priority = TASK_NO_GAME_SCRIPT;
                            Task.attribute = ATTR_USER;
                            Task.status = TASK_NEW_ENTRY;
                            Task.id = TASK_NO_GAME_SCRIPT;
                            Task.wait_time = 0;
                            Task.buf = NULL;
                            Task.name = "ScriptTask";
                            Task.mode = TASK_MODE_INIT;
                            Task.user[0] = SCRIPT_LINE_2;
                            Task.user[1] = PLAY_FALSE_UP_SCRIPT_BASE;
                            Task.user[2] = PLAY_FALSE_UP_SCRIPT_NUM;
                            CreateTask(&Task);
                        }
                    }
                }
            }
        }

        //----アニメ
        if (++ip_task->user[0] > 30)
        {
            ip_task->user[0] = 0;
            ip_task->user[1] ^= 1;
        }

        if (++ip_task->user[2] > 20)
        {
            ip_task->user[2] = 0;
            ip_task->user[3] ^= 1;
        }

        //----パネル
        SpData.No = PlateSpriteTable[ip_task->user[3]];
        SpData.PosX = 31;
        SpData.PosY = 10;
        SpData.PosZ = PRIORITY_THOU_EVENT_BG - 2;
        SpData.ScaleX = SCALE10;
        SpData.ScaleY = SCALE10;
        SpData.Rotate = ROTATE000;
        SpData.Reverse = NOREVERS;
        DrawSprite(&SpData);

        //----スコア
        DrawScore(TGameMgr.VisitorScore,
                  FALSE_EVENT_SCORE_NUM_WIDE,
                  FalseScoreSpriteTable,
                  58,
                  42,
                  PRIORITY_THOU_EVENT_BG - 3);

        //----手
        if (ip_task->user[1])
        {
            SpData.No = THOU_CHAR_EVENT_FALSE_02;     //インデックス番号
            SpData.PosX = 146;                        //X位置
            SpData.PosY = 112;                        //Y位置
            SpData.PosZ = PRIORITY_THOU_EVENT_BG - 2; //優先順位
            SpData.ScaleX = SCALE10;                  //スケールX
            SpData.ScaleY = SCALE10;                  //スケールY
            SpData.Rotate = ROTATE000;                //回転角
            SpData.Reverse = NOREVERS;                //反転コード
            DrawSprite(&SpData);                      //スプライト描画
        }

        //----背景左
        SpData.No = THOU_CHAR_EVENT_FALSE_00; //インデックス番号
        SpData.PosX = 0;                      //X位置
        SpData.PosY = 0;                      //Y位置
        SpData.PosZ = PRIORITY_THOU_EVENT_BG; //優先順位
        SpData.ScaleX = SCALE10;              //スケールX
        SpData.ScaleY = SCALE10;              //スケールY
        SpData.Rotate = ROTATE000;            //回転角
        SpData.Reverse = NOREVERS;            //反転コード
        DrawSprite(&SpData);                  //スプライト描画

        //----背景右
        SpData.No = THOU_CHAR_EVENT_FALSE_01;     //インデックス番号
        SpData.PosX = 256;                        //X位置
        SpData.PosY = 0;                          //Y位置
        SpData.PosZ = PRIORITY_THOU_EVENT_BG - 1; //優先順位
        SpData.ScaleX = SCALE10;                  //スケールX
        SpData.ScaleY = SCALE10;                  //スケールY
        SpData.Rotate = ROTATE000;                //回転角
        SpData.Reverse = NOREVERS;                //反転コード
        DrawSprite(&SpData);                      //スプライト描画

        //----もう一度プレイしますか？
        if (TGameMgr.EventEndFlag)
        {
            if (SelectContinue())
            { //●ボタンが押された
                if (!TGameMgr.SelectContinue.FadeFlag)
                { //フェード中
                    if ((TGameMgr.SelectContinue.Val == 0) && (TGameMgr.SelectContinue.Type == SELECT_RETRY_H))
                    { //もう一度プレイしますか？　はい
                        //next EXIT
                        TGameMgr.SelectContinue.FadeFlag = 1;
                        Task.func = EventFadeOutTask;
                        Task.priority = TASK_NO_GAME_FADE;
                        Task.attribute = ATTR_USER;
                        Task.status = TASK_NEW_ENTRY;
                        Task.id = TASK_NO_GAME_FADE;
                        Task.wait_time = 0;
                        Task.buf = NULL;
                        Task.name = "EventFadeOutTask";
                        Task.mode = TASK_MODE_INIT;
                        Task.user[0] = ip_task->id;
                        CreateTask(&Task);
                    }
                    else if ((TGameMgr.SelectContinue.Val == 1) && (TGameMgr.SelectContinue.Type == SELECT_RETRY_H))
                    { //もう一度プレイしますか？　いいえ
                        TGameMgr.SelectContinue.Type = SELECT_END_H;
                        TGameMgr.SelectContinue.Val = 0;
                    }
                    else if ((TGameMgr.SelectContinue.Type == SELECT_END_H) && (TGameMgr.SelectContinue.Val == 0))
                    { //やめますか？　はい
                        //next EXIT
                        TGameMgr.SelectContinue.FadeFlag = 1;
                        Task.func = EventFadeOutTask;
                        Task.priority = TASK_NO_GAME_FADE;
                        Task.attribute = ATTR_USER;
                        Task.status = TASK_NEW_ENTRY;
                        Task.id = TASK_NO_GAME_FADE;
                        Task.wait_time = 0;
                        Task.buf = NULL;
                        Task.name = "EventFadeOutTask";
                        Task.mode = TASK_MODE_INIT;
                        Task.user[0] = ip_task->id;
                        CreateTask(&Task);
                    }
                    else if ((TGameMgr.SelectContinue.Type == SELECT_END_H) && (TGameMgr.SelectContinue.Val == 1))
                    { //やめますか？　いいえ
                        TGameMgr.SelectContinue.Type = SELECT_RETRY_H;
                        TGameMgr.SelectContinue.Val = 0;
                    }
                    else
                    {
                    }
                }
            }
            else
            {
            }
        }

        break;
    //----------------------------------------------------------------タスク終了
    case TASK_MODE_EXIT:
        //----登録スプライト開放
        ReleaseSprite();

        //継続プレイフラグ
        TGameMgr.ContinureFlag = 1;

        //--------------------ここは２択
        //  (1)ゲームを続ける
        //  (2)メインメニュー
        if ((TGameMgr.SelectContinue.Type == SELECT_END_H) && (TGameMgr.SelectContinue.Val == 0))
        { //----ゲームをおわります
            TGameMgr.ExitFlag = 1;
        }
        else
        { //----ゲームコントロールタスク
            Task.func = GameControllTask;
            Task.priority = TASK_NO_GAME_CONTROLL;
            Task.attribute = ATTR_USER;
            Task.status = TASK_NEW_ENTRY;
            Task.id = TASK_NO_GAME_CONTROLL;
            Task.wait_time = 0;
            Task.buf = NULL;
            Task.name = "GameControllTask";
            Task.mode = TASK_MODE_INIT;
            CreateTask(&Task);
        }

        //自分を削除
        ExitTask(ip_task->id);
        break;
    default:
    }
    return TRUE;
}

//-----------------------------------------------------------------------------
//  関数名  :DrawScore
//  機能    :数字表示
//  in      :int i_num
//          :int i_wsize
//          :int *ip_numtbl
//          :int i_x
//          :int i_y
//          :int i_z
//  out     :なし
//  注意    :なし
//-----------------------------------------------------------------------------
static void DrawScore(int i_num, int i_wsize, int *ip_numtbl, int i_x, int i_y, int i_z)
{
    int i, bx, by;
    int numarr[4];
    SPRITE_DATA SpData;

    if (i_num > 1000)
        i_num = 1000;
    if (i_num < 0)
        i_num = 0;

    numarr[0] = i_num / 1000;                                                  //1000
    numarr[1] = (i_num - numarr[0] * 1000) / 100;                              //100
    numarr[2] = (i_num - numarr[0] * 1000 - numarr[1] * 100) / 10;             //10
    numarr[3] = (i_num - numarr[0] * 1000 - numarr[1] * 100 - numarr[2] * 10); //1

    bx = i_x;
    by = i_y;

    for (i = 0; i < 4; i++)
    {
        SpData.No = ip_numtbl[numarr[i]]; //インデックス番号
        SpData.PosX = bx;                 //X位置
        SpData.PosY = by;                 //Y位置
        SpData.PosZ = i_z;                //優先順位
        SpData.ScaleX = SCALE10;          //スケールX
        SpData.ScaleY = SCALE10;          //スケールY
        SpData.Rotate = ROTATE000;        //回転角
        SpData.Reverse = NOREVERS;        //反転コード
        DrawSprite(&SpData);              //スプライト描画
        //次の桁へ
        bx += i_wsize;
    }
}

//-----------------------------------------------------------------------------
//  関数名  :SelectContinue
//
//  work    :クリアイベント後の選択
//  in      :なし
//  out     :TRUE
//          :FALSE
//  note    :なし
//-----------------------------------------------------------------------------
static int SelectContinue(void)
{
    static int BupeAnmTable[] = {
        THOU_CHAR_EVENT_SELECT_CONTINUE_BUPE_00,
        THOU_CHAR_EVENT_SELECT_CONTINUE_BUPE_01,
    };

    static int MaruBatuTable[] = {
        THOU_CHAR_EVENT_SELECT_CONTINUE_YES_LIGHT,
        THOU_CHAR_EVENT_SELECT_CONTINUE_NO_DARK,
        THOU_CHAR_EVENT_SELECT_CONTINUE_YES_DARK,
        THOU_CHAR_EVENT_SELECT_CONTINUE_NO_LIGHT,
    };

    SPRITE_DATA SpData;
    int o_ret;

    //選択
    o_ret = FALSE;
    if (JstPad & PADRright)
    {
        o_ret = TRUE;
        //[♪]決定
        ssPlaySe(BUTONSE_MARU);
    }

    //選択
    if (JstPad & PADLright || JstPad & PADLleft)
    {
        TGameMgr.SelectContinue.Val ^= 1;
        //[♪] レバー音
        ssPlaySe(BUTONSE_LEVER);
    }

    //はい・いいえ
    SpData.No = MaruBatuTable[TGameMgr.SelectContinue.Val * 2]; //インデックス番号
    SpData.PosX = 68 + 72;                                      //X位置
    SpData.PosY = 73 + 57;                                      //Y位置
    SpData.PosZ = PRIORITY_THOU_EVENT_MENU - 2;                 //優先順位
    SpData.ScaleX = SCALE10;                                    //スケールX
    SpData.ScaleY = SCALE10;                                    //スケールY
    SpData.Rotate = ROTATE000;                                  //回転角
    SpData.Reverse = NOREVERS;                                  //反転コード
    DrawSprite(&SpData);                                        //スプライト描画

    SpData.No = MaruBatuTable[TGameMgr.SelectContinue.Val * 2 + 1]; //インデックス番号
    SpData.PosX = 68 + 126;                                         //X位置
    SpData.PosY = 73 + 57;                                          //Y位置
    SpData.PosZ = PRIORITY_THOU_EVENT_MENU - 2;                     //優先順位
    SpData.ScaleX = SCALE10;                                        //スケールX
    SpData.ScaleY = SCALE10;                                        //スケールY
    SpData.Rotate = ROTATE000;                                      //回転角
    SpData.Reverse = NOREVERS;                                      //反転コード
    DrawSprite(&SpData);                                            //スプライト描画

    //プレート文字
    switch (TGameMgr.SelectContinue.Type)
    {
    case SELECT_RETRY_H:
        SpData.No = THOU_CHAR_EVENT_SELECT_CONTINUE_RETRY_H; //インデックス番号
        SpData.PosX = 68 + 20;                               //X位置
        SpData.PosY = 73 + 20;                               //Y位置
        SpData.PosZ = PRIORITY_THOU_EVENT_MENU - 2;          //優先順位
        SpData.ScaleX = SCALE10;                             //スケールX
        SpData.ScaleY = SCALE10;                             //スケールY
        SpData.Rotate = ROTATE000;                           //回転角
        SpData.Reverse = NOREVERS;                           //反転コード
        DrawSprite(&SpData);                                 //スプライト描画
        break;
    case SELECT_END_H:
        SpData.No = THOU_CHAR_EVENT_SELECT_CONTINUE_END_H; //インデックス番号
        SpData.PosX = 68 + 20;                             //X位置
        SpData.PosY = 73 + 20;                             //Y位置
        SpData.PosZ = PRIORITY_THOU_EVENT_MENU - 2;        //優先順位
        SpData.ScaleX = SCALE10;                           //スケールX
        SpData.ScaleY = SCALE10;                           //スケールY
        SpData.Rotate = ROTATE000;                         //回転角
        SpData.Reverse = NOREVERS;                         //反転コード
        DrawSprite(&SpData);                               //スプライト描画
        break;
    case SELECT_CONTINUE_H:
        SpData.No = THOU_CHAR_EVENT_SELECT_CONTINUE_CONTINUE_H; //インデックス番号
        SpData.PosX = 68 + 20;                                  //X位置
        SpData.PosY = 73 + 20;                                  //Y位置
        SpData.PosZ = PRIORITY_THOU_EVENT_MENU - 2;             //優先順位
        SpData.ScaleX = SCALE10;                                //スケールX
        SpData.ScaleY = SCALE10;                                //スケールY
        SpData.Rotate = ROTATE000;                              //回転角
        SpData.Reverse = NOREVERS;                              //反転コード
        DrawSprite(&SpData);                                    //スプライト描画
        break;
    default:
    }

    //ブーぺ
    if (++TGameMgr.SelectContinue.Wt > SELECT_LEVEL_PUPE_ANM_TIME)
    {
        TGameMgr.SelectContinue.No ^= 1;
        TGameMgr.SelectContinue.Wt = 0;
    }
    SpData.No = BupeAnmTable[TGameMgr.SelectContinue.No]; //インデックス番号
    SpData.PosX = 68 + 12;                                //X位置
    SpData.PosY = 73 + 34;                                //Y位置
    SpData.PosZ = PRIORITY_THOU_EVENT_MENU - 10;          //優先順位
    SpData.ScaleX = SCALE10;                              //スケールX
    SpData.ScaleY = SCALE10;                              //スケールY
    SpData.Rotate = ROTATE000;                            //回転角
    SpData.Reverse = NOREVERS;                            //反転コード
    DrawSprite(&SpData);                                  //スプライト描画

    //プレート
    SpData.No = THOU_CHAR_EVENT_SELECT_CONTINUE_PLATE; //インデックス番号
    SpData.PosX = 68;                                  //X位置
    SpData.PosY = 73;                                  //Y位置
    SpData.PosZ = PRIORITY_THOU_EVENT_MENU;            //優先順位
    SpData.ScaleX = SCALE10;                           //スケールX
    SpData.ScaleY = SCALE10;                           //スケールY
    SpData.Rotate = ROTATE000;                         //回転角
    SpData.Reverse = NOREVERS;                         //反転コード
    DrawSprite(&SpData);                               //スプライト描画

    //えらぶ
    SpData.No = THOU_CHAR_EVENT_SELECT_CONTINUE_ERABU; //インデックス番号
    SpData.PosX = (320 - 130) / 2;                     //X位置
    SpData.PosY = 206;                                 //Y位置
    SpData.PosZ = PRIORITY_THOU_EVENT_MENU - 1;        //優先順位
    SpData.ScaleX = SCALE10;                           //スケールX
    SpData.ScaleY = SCALE10;                           //スケールY
    SpData.Rotate = ROTATE000;                         //回転角
    SpData.Reverse = NOREVERS;                         //反転コード
    DrawSprite(&SpData);                               //スプライト描画

    //けってい
    SpData.No = THOU_CHAR_EVENT_SELECT_CONTINUE_KETEI; //インデックス番号
    SpData.PosX = (320 - 130) / 2 + 78;                //X位置
    SpData.PosY = 206;                                 //Y位置
    SpData.PosZ = PRIORITY_THOU_EVENT_MENU - 1;        //優先順位
    SpData.ScaleX = SCALE10;                           //スケールX
    SpData.ScaleY = SCALE10;                           //スケールY
    SpData.Rotate = ROTATE000;                         //回転角
    SpData.Reverse = NOREVERS;                         //反転コード
    DrawSprite(&SpData);                               //スプライト描画

    return o_ret;
}

#ifdef __DEBUG_THOU__
//-----------------------------------------------------------------------------
//  関数名 :DebugGameSpriteTask
//
//  work   :スプライトタスク
//  in     :TASK*       タスクポインタ
//  out    :TRUE
//  note   :なし
//-----------------------------------------------------------------------------
static int DebugGameSpriteTask(TASK *ip_task)
{
    static int SpIndex;
    static int SpEntryNum;
    static int Counter;
    static int FlushFlag;

    SPRITE_DATA SpData;

    switch (ip_task->mode)
    {
    case TASK_MODE_INIT:
        //----
        ip_task->mode = TASK_MODE_MAIN;

        //----texture read sram -> vram
        if ((file_read(ThouGameTextureFile[0].fn, LoadAddress)) == -1)
        { //read error
            return FALSE;
        }

        //----texture init
        TexInit(THOU_GAME_TIM_NUM, &ThouGameTextureImage[THOU_GAME_TIM_POS]);
        TimImgData = ThouGameTextureImage;

        //----ゲーム用スプライト登録
        EntrySprite(ThouGameSpriteData);

        //フェードイン
        GameMgr.FadeFlag = FadeIn;

        //----
        SpIndex = 0;
        SpEntryNum = GetEntrySpriteNum();
        Counter = 0;
        FlushFlag = 0;
        break;
    case TASK_MODE_MAIN:

        if (JstPad & PADLdown)
        {
            SpIndex++;
            if (SpIndex > SpEntryNum - 1)
                SpIndex = 0;
        }
        else if (JstPad & PADLup)
        {
            SpIndex--;
            if (SpIndex < 0)
                SpIndex = SpEntryNum - 1;
        }
        else
        {
        }

        if (JstPad & PADRright)
        {
            FlushFlag ^= 1;
        }
        if (FlushFlag)
            GsSortBoxFill(&BoxDataBlack, &Wot[active], 4);
        else
            GsSortBoxFill(&BoxDataWhite, &Wot[active], 4);

        SpData.No = SpIndex;                                          //インデックス番号
        SpData.PosX = (320 - ThouGameSpriteData[SpIndex].Width) / 2;  //X位置
        SpData.PosY = (240 - ThouGameSpriteData[SpIndex].Height) / 2; //Y位置
        SpData.PosZ = 10;                                             //優先順位
        SpData.ScaleX = SCALE10;                                      //スケールX
        SpData.ScaleY = SCALE10;                                      //スケールY
        SpData.Rotate = ROTATE000;                                    //回転角
        SpData.Reverse = NOREVERS;                                    //反転コード
        DrawSprite(&SpData);                                          //スプライト描画

        //info
        FntPrint("SNO=%d/%d\n", SpIndex, SpEntryNum - 1);
        FntPrint("OfX=%d\n", ThouGameSpriteData[SpIndex].OffSetX);   //TIMの中のスプライト左上開始X位置
        FntPrint("OfY=%d\n", ThouGameSpriteData[SpIndex].OffSetY);   //TIMの中のスプライト左上開始Y位置
        FntPrint("W__=%d\n", ThouGameSpriteData[SpIndex].Width);     //TIMの中のテクスチャの幅
        FntPrint("H__=%d\n", ThouGameSpriteData[SpIndex].Height);    //TIMの中のテクスチャの高さ
        FntPrint("PNO=%d\n", ThouGameSpriteData[SpIndex].PaletteNo); //TIMの中のテクスチャパレット番号
        FntPrint("CNT=%d\n", ++Counter);

        break;
    case TASK_MODE_EXIT:
        break;
    default:
        break;
    }
}

//-----------------------------------------------------------------------------
//  関数名 :DebugEventSpriteTask
//
//  work   :スプライトタスク
//  in     :TASK*       タスクポインタ
//  out    :TRUE
//  note   :なし
//-----------------------------------------------------------------------------
static int DebugEventSpriteTask(TASK *ip_task)
{
    static int SpIndex;
    static int SpEntryNum;
    static int Counter;
    static int FlushFlag;

    SPRITE_DATA SpData;

    switch (ip_task->mode)
    {
    case TASK_MODE_INIT:
        //----
        ip_task->mode = TASK_MODE_MAIN;

        //----texture read sram -> vram
        if ((file_read(ThouEventTextureFile[0].fn, LoadAddress)) == -1)
        { //read error
            return FALSE;
        }

        //----texture init
        TexInit(THOU_EVENT_TIM_NUM, &ThouEventTextureImage[THOU_EVENT_TIM_POS]);
        TimImgData = ThouEventTextureImage;

        //----イベント用スプライト登録
        EntrySprite(ThouEventSpriteData);

        //フェードイン
        GameMgr.FadeFlag = FadeIn;

        //----
        SpIndex = 0;
        SpEntryNum = GetEntrySpriteNum();
        Counter = 0;
        FlushFlag = 0;
        break;
    case TASK_MODE_MAIN:

        if (JstPad & PADLdown)
        {
            SpIndex++;
            if (SpIndex > SpEntryNum - 1)
                SpIndex = 0;
        }
        else if (JstPad & PADLup)
        {
            SpIndex--;
            if (SpIndex < 0)
                SpIndex = SpEntryNum - 1;
        }
        else
        {
        }

        if (JstPad & PADRright)
        {
            FlushFlag ^= 1;
        }
        if (FlushFlag)
            GsSortBoxFill(&BoxDataBlack, &Wot[active], 4);
        else
            GsSortBoxFill(&BoxDataWhite, &Wot[active], 4);

        SpData.No = SpIndex;                                           //インデックス番号
        SpData.PosX = (320 - ThouEventSpriteData[SpIndex].Width) / 2;  //X位置
        SpData.PosY = (240 - ThouEventSpriteData[SpIndex].Height) / 2; //Y位置
        SpData.PosZ = 10;                                              //優先順位
        SpData.ScaleX = SCALE10;                                       //スケールX
        SpData.ScaleY = SCALE10;                                       //スケールY
        SpData.Rotate = ROTATE000;                                     //回転角
        SpData.Reverse = NOREVERS;                                     //反転コード
        DrawSprite(&SpData);                                           //スプライト描画

        //info
        FntPrint("SNO=%d/%d\n", SpIndex, SpEntryNum - 1);
        FntPrint("OfX=%d\n", ThouEventSpriteData[SpIndex].OffSetX);   //TIMの中のスプライト左上開始X位置
        FntPrint("OfY=%d\n", ThouEventSpriteData[SpIndex].OffSetY);   //TIMの中のスプライト左上開始Y位置
        FntPrint("W__=%d\n", ThouEventSpriteData[SpIndex].Width);     //TIMの中のテクスチャの幅
        FntPrint("H__=%d\n", ThouEventSpriteData[SpIndex].Height);    //TIMの中のテクスチャの高さ
        FntPrint("PNO=%d\n", ThouEventSpriteData[SpIndex].PaletteNo); //TIMの中のテクスチャパレット番号
        FntPrint("CNT=%d\n", ++Counter);

        break;
    case TASK_MODE_EXIT:
        break;
    default:
        break;
    }
}

#endif

//-----------------------------------------------------------------------------
// end of THOU.C
//-----------------------------------------------------------------------------