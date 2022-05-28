//-----------------------------------------------------------------------------
// SEES.C
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
#include "SEES.H"
//-----------------------------------------------------------------------------
//  define
//-----------------------------------------------------------------------------
//----------------------------------------debug sw「デバッグ時はコメントを外してください」
//  #define __DEBUG_SEES__

//----------------------------------------システム部
#define TIM_POS_SEES_EVENT_FONT         0       //選択処理テクスチャ
#define TIM_POS_SEES_EVENT_YORNO        1       //選択処理テクスチャ

//----------------------------------------ゲーム：テクスチャー枚数と位置
//テクスチャー枚数と位置
#define SEES_GAME_TIM_POS               0+4
#define SEES_GAME_TIM_NUM               11

//----------------------------------------イベント：テクスチャー枚数と位置
#define SEES_EVENT_TIM_POS              0+4
#define SEES_EVENT_TIM_NUM              11

//----------------------------------------ゲーム部
#define TIM_POS_SEES_GAME_BG00          0+4
#define TIM_POS_SEES_GAME_BG00_         1+4
#define TIM_POS_SEES_GAME_BGGAME        2+4
#define TIM_POS_SEES_GAME_BGGAME_       3+4
#define TIM_POS_SEES_GAME_BGLV          4+4
#define TIM_POS_SEES_GAME_BGLV_         5+4
#define TIM_POS_SEES_GAME_BORI00        6+4
#define TIM_POS_SEES_GAME_BORI01        7+4
#define TIM_POS_SEES_GAME_ITEM          8+4
#define TIM_POS_SEES_GAME_KAYO          9+4
#define TIM_POS_SEES_GAME_LEVEL         10+4

//----------------------------------------イベント部
#define TIM_POS_SEES_EVENT_BG01         0+4
#define TIM_POS_SEES_EVENT_BG01_        1+4
#define TIM_POS_SEES_EVENT_BG02         2+4
#define TIM_POS_SEES_EVENT_BG02_        3+4
#define TIM_POS_SEES_EVENT_BGEND        4+4
#define TIM_POS_SEES_EVENT_BGEND_       5+4
#define TIM_POS_SEES_EVENT_BORI00       6+4
#define TIM_POS_SEES_EVENT_HANA         7+4
#define TIM_POS_SEES_EVENT_ITEM         8+4
#define TIM_POS_SEES_EVENT_KAYO         9+4
#define TIM_POS_SEES_EVENT_MEGAHANA     10+4


//----------------------------------------ゲームキャラ番号
enum{
    SEES_CHAR_GAME_APPEAR_BG_00,                //初プレイデモ背景１
    SEES_CHAR_GAME_APPEAR_BG_01,                //初プレイデモ背景２
    SEES_CHAR_GAME_GAME_BG_00,                  //ゲーム背景１
    SEES_CHAR_GAME_GAME_BG_01,                  //ゲーム背景2
    SEES_CHAR_GAME_SELECT_LEVEL_BG_00,          //レベルセレクト背景１
    SEES_CHAR_GAME_SELECT_LEVEL_BG_01,          //レベルセレクト背景2
    SEES_CHAR_GAME_AS_MACNINE_00,               //マシン付きボーリー横向き          204,99
    SEES_CHAR_GAME_AS_MACNINE_01,               //マシン付きボーリー正面            184,99
    SEES_CHAR_GAME_AS_HAND_MACNINE_00,          //マシン付きボーリー横手・上        244,127
    SEES_CHAR_GAME_AS_HAND_MACNINE_01,          //マシン付きボーリー横手・下        244,134
    SEES_CHAR_GAME_AS_HAND_MACNINE_02,          //マシン付きボーリー正面手・上      244,117
    SEES_CHAR_GAME_AS_HAND_MACNINE_03,          //マシン付きボーリー正面手・下      244,118
    SEES_CHAR_GAME_DR_00,                       //メガトン博士口開けバンザイ        110,133     
    SEES_CHAR_GAME_DR_01,                       //メガトン博士皿持ち口閉じ        46,26     
    SEES_CHAR_GAME_DR_02,                       //メガトン博士しっぽ              46,26     
    SEES_CHAR_GAME_DR_03,                       //メガトン博士標準・口開け        46,30     
    SEES_CHAR_GAME_DR_04,                       //メガトン博士標準・口閉じ        46,30     
    SEES_CHAR_GAME_DR_05,                       //メガトン博士標準・足短          46,30     
    SEES_CHAR_GAME_DR_06,                       //メガトン博士ジャンプ            44,29     
    SEES_CHAR_GAME_DR_07,                       //メガトン博士ジャンプ・口開け    44,29     
    SEES_CHAR_GAME_DR_08,                       //メガトン博士微笑                110,133       
    SEES_CHAR_GAME_DR_09,                       //メガトン博士負け                44,29     
    SEES_CHAR_GAME_DR_10,                       //メガトン博士バンザイ・笑        44,29     
    SEES_CHAR_GAME_AS_BODY,                     //ボーリー　ばらばら胴体        44,123
    SEES_CHAR_GAME_AS_PARTS_00,                 //ボーリー　標準左手            30,126
    SEES_CHAR_GAME_AS_PARTS_01,                 //ボーリー　標準右手            120,126
    SEES_CHAR_GAME_AS_PARTS_02,                 //ボーリー　右手真下指差し      112,124
    SEES_CHAR_GAME_AS_PARTS_03,                 //ボーリー　左手下指差し        6,125   
    SEES_CHAR_GAME_AS_PARTS_04,                 //ボーリー　左手真下指差し      24,124  
    SEES_CHAR_GAME_AS_PARTS_05,                 //ボーリー　笑った顔            72,118  
    SEES_CHAR_GAME_AS_PARTS_06,                 //ボーリー　中央下指差し        74,124  
    SEES_CHAR_GAME_AS_PARTS_07,                 //ボーリー　左手上腕差し        118,93  
    SEES_CHAR_GAME_AS_PARTS_08,                 //ボーリー　首傾げ・右手曲げ    60,96   
    SEES_CHAR_GAME_AS_PARTS_09,                 //ボーリー　首傾げ。口パク      72,136  
    SEES_CHAR_GAME_AS_PARTS_10,                 //ボーリー　両手中央寄せ        34,124  
    SEES_CHAR_GAME_AS_PARTS_11,                 //ボーリー　標準・顔            60,96   
    SEES_CHAR_GAME_AS_PARTS_12,                 //ボーリー　両手合わせ          36,124  
    SEES_CHAR_GAME_AS_PARTS_13,                 //ボーリー　右手上げ            58,97   
    SEES_CHAR_GAME_AS_PARTS_14,                 //ボーリー　右手下指差し        118,125 
    SEES_CHAR_GAME_COUNT_NUM_1,                 //20,28/278,28  カウント数字1
    SEES_CHAR_GAME_COUNT_NUM_2,                 //20,28/278,28  カウント数字2
    SEES_CHAR_GAME_COUNT_NUM_3,                 //20,28/278,28  カウント数字3
    SEES_CHAR_GAME_COUNT_NUM_4,                 //20,28/278,28  カウント数字4
    SEES_CHAR_GAME_COUNT_NUM_5,                 //20,28/278,28  カウント数字5
    SEES_CHAR_GAME_COUNT_NUM_6,                 //20,28/278,28  カウント数字6
    SEES_CHAR_GAME_COUNT_NUM_7,                 //20,28/278,28  カウント数字7
    SEES_CHAR_GAME_COUNT_NUM_8,                 //20,28/278,28  カウント数字8
    SEES_CHAR_GAME_COUNT_NUM_9,                 //【×】20,28/278,28    カウント数字9
    SEES_CHAR_GAME_COUNT_NUM_0,                 //20,28/278,28  レベル１数字0
    SEES_CHAR_GAME_PLATE_NUM_WAKU,              //ゲーム用数字（数字枠
    SEES_CHAR_GAME_PLATE_NUM_01,                //ゲーム用数字（1
    SEES_CHAR_GAME_PLATE_NUM_02,                //ゲーム用数字（2
    SEES_CHAR_GAME_PLATE_NUM_03,                //ゲーム用数字（3
    SEES_CHAR_GAME_PLATE_NUM_04,                //ゲーム用数字（4
    SEES_CHAR_GAME_PLATE_NUM_05,                //ゲーム用数字（5
    SEES_CHAR_GAME_PLATE_NUM_06,                //ゲーム用数字（6
    SEES_CHAR_GAME_PLATE_NUM_07,                //ゲーム用数字（7
    SEES_CHAR_GAME_PLATE_NUM_08,                //ゲーム用数字（8
    SEES_CHAR_GAME_PLATE_NUM_09,                //ゲーム用数字（9
    SEES_CHAR_GAME_PLATE_NUM_00,                //ゲーム用数字（0
    SEES_CHAR_GAME_WAKU_BIG,                    //認識枠・大
    SEES_CHAR_GAME_WAKU_MIDDLE,                 //認識枠・中
    SEES_CHAR_GAME_WAKU_SMALL,                  //認識枠・小
    SEES_CHAR_GAME_PLATE_STAR,                  //星枠
    SEES_CHAR_GAME_BOX,                         //中身かご
    SEES_CHAR_GAME_BOX_AMI,                     //カゴ
    SEES_CHAR_GAME_FRUITS_YELLOW,               //りんご・黄
    SEES_CHAR_GAME_FRUITS_RED,                  //りんご・赤
    SEES_CHAR_GAME_WIN_PLATE,                   //ゲーム後勝ち負けプレート(かち)
    SEES_CHAR_GAME_LOSE_PLATE,                  //ゲーム後勝ち負けプレート(まけ)
    SEES_CHAR_GAME_SEESAW_LEFT,                 //シーソー左
    SEES_CHAR_GAME_SEESAW_RIGHT,                //シーソー右
    SEES_CHAR_GAME_LEFT_LIGHT_00,               //左標準
    SEES_CHAR_GAME_LEFT_LIGHT_01,               //左1
    SEES_CHAR_GAME_LEFT_LIGHT_02,               //左2
    SEES_CHAR_GAME_LEFT_LIGHT_03,               //左3
    SEES_CHAR_GAME_LEFT_LIGHT_04,               //左4
    SEES_CHAR_GAME_LEFT_LIGHT_05,               //左5
    SEES_CHAR_GAME_RIGHT_LIGHT_00,              //右標準
    SEES_CHAR_GAME_RIGHT_LIGHT_01,              //右1
    SEES_CHAR_GAME_RIGHT_LIGHT_02,              //右2
    SEES_CHAR_GAME_RIGHT_LIGHT_03,              //右3
    SEES_CHAR_GAME_RIGHT_LIGHT_04,              //右4
    SEES_CHAR_GAME_RIGHT_LIGHT_05,              //右5
    SEES_CHAR_GAME_RAINBOW_MACHINE_00,          //虹色マシンA
    SEES_CHAR_GAME_RAINBOW_MACHINE_01,          //虹色マシンB
    SEES_CHAR_GAME_LEFT_LIGHT_FLUSH,            //マシン点滅左
    SEES_CHAR_GAME_RIGHT_LIGHT_FLUSH,           //マシン点滅右
    SEES_CHAR_GAME_NEW_CARD_WAKU,               //カードワク
    SEES_CHAR_GAME_NEW_STAR_CARD,               //★ワク
    SEES_CHAR_GAME_KY_00,                       //カヨリーヌ(標準・口開け)  226,31  
    SEES_CHAR_GAME_KY_01,                       //カヨリーヌ(標準・口閉じ)  226,31  
    SEES_CHAR_GAME_KY_02,                       //カヨリーヌ(首傾げ)        226,31  
    SEES_CHAR_GAME_KY_03,                       //カヨリーヌ(両手合わせ)    226,31  
    SEES_CHAR_GAME_KY_04,                       //カヨリーヌ(バンザイ)      226,31  
    SEES_CHAR_GAME_KY_05,                       //カヨリーヌ(バンザイ)      40,129  
    SEES_CHAR_GAME_KY_06,                       //カヨリーヌ(笑う)          40,129  
    SEES_CHAR_GAME_KY_07,                       //カヨリーヌ(負けA)         228,126 
    SEES_CHAR_GAME_KY_08,                       //カヨリーヌ(負けB)         228,126 
    SEES_CHAR_GAME_KY_09,                       //カヨリーヌ(皿持ち)        222,30  
    SEES_CHAR_GAME_HANABI_00,                   //カヨリーヌ(花火)          108,20  
    SEES_CHAR_GAME_DANTYOU_00,                  //団長00アニメ
    SEES_CHAR_GAME_DANTYOU_01,                  //団長01アニメ
    SEES_CHAR_GAME_DANIN_FUUSEN_BLUE_00,        //青風船時01楽団員A00アニメ
    SEES_CHAR_GAME_DANIN_FUUSEN_BLUE_01,        //同上
    SEES_CHAR_GAME_DANIN_FUUSEN_ORANGE_00,      //橙風船時02　楽団員A00アニメ
    SEES_CHAR_GAME_DANIN_FUUSEN_ORANGE_01,      //同上
    SEES_CHAR_GAME_DANIN_HATA_YOKO_00,          //楽団員B00アニメ
    SEES_CHAR_GAME_DANIN_HATA_YOKO_01,          //楽団員B01アニメ
    SEES_CHAR_GAME_DANIN_HATA_TATE_00,          //楽団員C00アニメ
    SEES_CHAR_GAME_DANIN_HATA_TATE_01,          //楽団員C01アニメ
    SEES_CHAR_GAME_SELECT_LEVEL_CURSOR,         //レベル選択カーソル枠
    SEES_CHAR_GAME_SELECT_LEVEL_PLATE_LIGHT,    //レベルブロック明るい
    SEES_CHAR_GAME_SELECT_LEVEL_PLATE_DARK,     //レベルブロック暗い
    SEES_CHAR_GAME_SELECT_LEVEL_NUM_1,          //レベル選択用数字1
    SEES_CHAR_GAME_SELECT_LEVEL_NUM_2,          //レベル選択用数字2
    SEES_CHAR_GAME_SELECT_LEVEL_NUM_3,          //レベル選択用数字3
    SEES_CHAR_GAME_SELECT_LEVEL_NUM_4,          //レベル選択用数字4
    SEES_CHAR_GAME_SELECT_LEVEL_NUM_5,          //レベル選択用数字5
    SEES_CHAR_GAME_DR_APPEAR_MOUSE,             //メガトン博士１枚絵の口パク    82,98
    SEES_CHAR_GAME_SELECT_ANSWER_CURSOR,        //指カーソル
};


//----------------------------------------イベントキャラ番号
enum{
    SEES_CHAR_EVENT_CLEAR_ACTION_BG_00, //背景１
    SEES_CHAR_EVENT_CLEAR_ACTION_BG_01, //背景2
    SEES_CHAR_EVENT_CLEAR_ACTION_BG_02, //背景１
    SEES_CHAR_EVENT_CLEAR_ACTION_BG_03, //背景2
    SEES_CHAR_EVENT_EVENT_BG_00,            //イベント背景１
    SEES_CHAR_EVENT_EVENT_BG_01,            //イベント背景2
    SEES_CHAR_EVENT_AS_MACNINE_00,      //マシン付きボーリー横向き          204,99
    SEES_CHAR_EVENT_AS_MACNINE_01,      //マシン付きボーリー正面            184,99
    SEES_CHAR_EVENT_AS_HAND_MACNINE_00, //マシン付きボーリー横手・上        244,127
    SEES_CHAR_EVENT_AS_HAND_MACNINE_01, //マシン付きボーリー横手・下        244,134
    SEES_CHAR_EVENT_AS_HAND_MACNINE_02, //マシン付きボーリー正面手・上      244,117
    SEES_CHAR_EVENT_AS_HAND_MACNINE_03, //マシン付きボーリー正面手・下      244,118
    SEES_CHAR_EVENT_DR_00,              //メガトン博士口開けバンザイ        110,133     
    SEES_CHAR_EVENT_DR_01,              //メガトン博士皿持ち口閉じ        46,26     
    SEES_CHAR_EVENT_DR_02,              //メガトン博士しっぽ              46,26     
    SEES_CHAR_EVENT_DR_03,              //メガトン博士標準・口開け        46,30     
    SEES_CHAR_EVENT_DR_04,              //メガトン博士標準・口閉じ        46,30     
    SEES_CHAR_EVENT_DR_05,              //メガトン博士標準・足短          46,30     
    SEES_CHAR_EVENT_DR_06,              //メガトン博士ジャンプ            44,29     
    SEES_CHAR_EVENT_DR_07,              //メガトン博士ジャンプ・口開け    44,29     
    SEES_CHAR_EVENT_DR_08,              //メガトン博士微笑                110,133       
    SEES_CHAR_EVENT_DR_09,              //メガトン博士負け                44,29     
    SEES_CHAR_EVENT_DR_10,              //メガトン博士バンザイ・笑        44,29     
    SEES_CHAR_EVENT_HANABI_BIG,         //花火大                64,18   
    SEES_CHAR_EVENT_HANABI_MIDDLE,      //花火中              76,41 
    SEES_CHAR_EVENT_HANABI_SMALL_00,        //花火小              84,85 
    SEES_CHAR_EVENT_HANABI_SMALL_01,        //花火小・赤紫        162,26    
    SEES_CHAR_EVENT_STAR_00,                //星A                 64,35 
    SEES_CHAR_EVENT_STAR_01,                //星B                 64,35 
    SEES_CHAR_EVENT_HANABI_TANE_00,     //花火種A
    SEES_CHAR_EVENT_HANABI_TANE_01,     //花火種B
    SEES_CHAR_EVENT_COUNT_NUM_1,            //20,28/278,28  レベル１数字1
    SEES_CHAR_EVENT_COUNT_NUM_2,            //20,28/278,28  レベル１数字2
    SEES_CHAR_EVENT_COUNT_NUM_3,            //20,28/278,28  レベル１数字3
    SEES_CHAR_EVENT_COUNT_NUM_4,            //20,28/278,28  レベル１数字4
    SEES_CHAR_EVENT_COUNT_NUM_5,            //20,28/278,28  レベル１数字5
    SEES_CHAR_EVENT_COUNT_NUM_6,            //20,28/278,28  レベル１数字6
    SEES_CHAR_EVENT_COUNT_NUM_7,            //20,28/278,28  レベル１数字7
    SEES_CHAR_EVENT_COUNT_NUM_8,            //20,28/278,28  レベル１数字8
    SEES_CHAR_EVENT_COUNT_NUM_9,            //
    SEES_CHAR_EVENT_COUNT_NUM_0,            //20,28/278,28  レベル１数字0
    SEES_CHAR_EVENT_PLATE_NUM_WA,       //ゲーム用数字（数字枠
    SEES_CHAR_EVENT_PLATE_NUM_01,       //ゲーム用数字（1
    SEES_CHAR_EVENT_PLATE_NUM_02,       //ゲーム用数字（2
    SEES_CHAR_EVENT_PLATE_NUM_03,       //ゲーム用数字（3
    SEES_CHAR_EVENT_PLATE_NUM_04,       //ゲーム用数字（4
    SEES_CHAR_EVENT_PLATE_NUM_05,       //ゲーム用数字（5
    SEES_CHAR_EVENT_PLATE_NUM_06,       //ゲーム用数字（6
    SEES_CHAR_EVENT_PLATE_NUM_07,       //ゲーム用数字（7
    SEES_CHAR_EVENT_PLATE_NUM_08,       //ゲーム用数字（8
    SEES_CHAR_EVENT_PLATE_NUM_09,       //ゲーム用数字（9
    SEES_CHAR_EVENT_PLATE_NUM_00,       //ゲーム用数字（0
    SEES_CHAR_EVENT_WAKU_BIG,           //認識枠・大
    SEES_CHAR_EVENT_WAKU_MIDDLE,            //認識枠・中
    SEES_CHAR_EVENT_WAKU_SMALL,         //認識枠・小
    SEES_CHAR_EVENT_PLATE_STAR,         //星枠
    SEES_CHAR_EVENT_BOX,                    //中身かご
    SEES_CHAR_EVENT_BOX_AMI,                //カゴ
    SEES_CHAR_EVENT_FRUITS_YELLOW,      //りんご・黄
    SEES_CHAR_EVENT_FRUITS_RED,         //りんご・赤
    SEES_CHAR_EVENT_WIN_PLATE,          //ゲーム後勝ち負けプレート(かち)
    SEES_CHAR_EVENT_LOSE_PLATE,         //ゲーム後勝ち負けプレート(まけ)
    SEES_CHAR_EVENT_SEESAW_LEFT,            //シーソー左
    SEES_CHAR_EVENT_SEESAW_RIGHT,       //シーソー右
    SEES_CHAR_EVENT_LUMP_LEFT_00,       //左標準
    SEES_CHAR_EVENT_LUMP_LEFT_01,       //左1
    SEES_CHAR_EVENT_LUMP_LEFT_02,       //左2
    SEES_CHAR_EVENT_LUMP_LEFT_03,       //左3
    SEES_CHAR_EVENT_LUMP_LEFT_04,       //左4
    SEES_CHAR_EVENT_LUMP_LEFT_05,       //左5
    SEES_CHAR_EVENT_LUMP_RIGHT_00,      //右標準
    SEES_CHAR_EVENT_LUMP_RIGHT_01,      //右1
    SEES_CHAR_EVENT_LUMP_RIGHT_02,      //右2
    SEES_CHAR_EVENT_LUMP_RIGHT_03,      //右3
    SEES_CHAR_EVENT_LUMP_RIGHT_04,      //右4
    SEES_CHAR_EVENT_LUMP_RIGHT_05,      //右5
    SEES_CHAR_EVENT_RAINBOW_MACHINE_00, //虹色マシンA
    SEES_CHAR_EVENT_RAINBOW_MACHINE_01, //虹色マシンB
    SEES_CHAR_EVENT_LUMP_LEFT_TOP,      //マシン点滅左
    SEES_CHAR_EVENT_LUMP_RIGHT_TOP,     //マシン点滅右
    SEES_CHAR_EVENT_KY_00,              //カヨリーヌ(標準・口開け       226,31
    SEES_CHAR_EVENT_KY_01,              //カヨリーヌ(標準・口閉じ     226,31
    SEES_CHAR_EVENT_KY_02,              //カヨリーヌ(首傾げ           226,31        
    SEES_CHAR_EVENT_KY_03,              //カヨリーヌ(両手合わせ       226,31        
    SEES_CHAR_EVENT_KY_04,              //カヨリーヌ(バンザイ         222,31        
    SEES_CHAR_EVENT_KY_05,              //カヨリーヌ(バンザイ　       40,129        
    SEES_CHAR_EVENT_KY_06,              //カヨリーヌ(笑う　           40,129        
    SEES_CHAR_EVENT_KY_07,              //カヨリーヌ(負けA            228,126       
    SEES_CHAR_EVENT_KY_08,              //カヨリーヌ(負けB            228,126       
    SEES_CHAR_EVENT_KY_09,              //カヨリーヌ(皿持ち           222,30        
    SEES_CHAR_EVENT_HANABI_00,          //カヨリーヌ(花火             108,20        
    SEES_CHAR_EVENT_HANABI_DR_00,       //メガトン花火(大)      78,10   
    SEES_CHAR_EVENT_HANABI_DR_01,       //メガトン花火(小)        96,20 
    SEES_CHAR_EVENT_SELECT_CONTINUE_PLATE,      //プレート
    SEES_CHAR_EVENT_SELECT_CONTINUE_YES_DARK,   //非選択・はい
    SEES_CHAR_EVENT_SELECT_CONTINUE_NO_DARK,    //非選択・いいえ
    SEES_CHAR_EVENT_SELECT_CONTINUE_YES_LIGHT,  //選択・はい
    SEES_CHAR_EVENT_SELECT_CONTINUE_NO_LIGHT,   //選択・いいえ
    SEES_CHAR_EVENT_SELECT_CONTINUE_BUPE_00,    //プーぺ１
    SEES_CHAR_EVENT_SELECT_CONTINUE_BUPE_01,    //プーぺ２
    SEES_CHAR_EVENT_SELECT_CONTINUE_RETRY_H,    //もういちど
    SEES_CHAR_EVENT_SELECT_CONTINUE_END_H,      //おわり
    SEES_CHAR_EVENT_SELECT_CONTINUE_CONTINUE_H, //つづけ
    SEES_CHAR_EVENT_SELECT_CONTINUE_CURSOR,     //指カーソル
    SEES_CHAR_EVENT_SELECT_CONTINUE_ERABU,      //えらぶ
    SEES_CHAR_EVENT_SELECT_CONTINUE_KETEI,      //けってい
    SEES_CHAR_EVENT_SELECT_CONTINUE_MENU,       //めにゅー
};


//-----------------------------------------------------------------------------
//  extern
//-----------------------------------------------------------------------------
//PAD
extern u_long   pad;
extern u_long   NewPad; 
extern u_long   OldPad; 
extern u_long   JstPad; 
extern u_long   WorkPad;

//SYSTEM
extern u_long   font_image[];
extern u_long   YorN_image[];
extern u_long   name_image[];
extern u_long   MMENU_image[];
extern u_long   font_clut[];
extern u_long   YorN_clut[];
extern u_long   name_clut[];
extern u_long   MMENU_clut[];

//GAME
extern u_long   SG_BG00_image[];
extern u_long   SG_BG00_clut[];
extern u_long   SG_BG00__image[];
extern u_long   SG_BG00__clut[];
extern u_long   SG_BGgame_image[];
extern u_long   SG_BGgame_clut[];
extern u_long   SG_BGgame__image[];
extern u_long   SG_BGgame__clut[];
extern u_long   SG_BGlv_image[];
extern u_long   SG_BGlv_clut[];
extern u_long   SG_BGlv__image[];
extern u_long   SG_BGlv__clut[];
extern u_long   SG_BORI00_image[];
extern u_long   SG_BORI00_clut[];
extern u_long   SG_BORI01_image[];
extern u_long   SG_BORI01_clut[];
extern u_long   SG_ITEM_image[];
extern u_long   SG_ITEM_clut[];
extern u_long   SG_KAYO_image[];
extern u_long   SG_KAYO_clut[];
extern u_long   SG_LEVEL_image[];
extern u_long   SG_LEVEL_clut[];

//EVENT
extern u_long   SE_BG01_image[];
extern u_long   SE_BG01_clut[];
extern u_long   SE_BG01__image[];
extern u_long   SE_BG01__clut[];
extern u_long   SE_BG02_image[];
extern u_long   SE_BG02_clut[];
extern u_long   SE_BG02__image[];
extern u_long   SE_BG02__clut[];
extern u_long   SE_BGend_image[];
extern u_long   SE_BGend_clut[];
extern u_long   SE_BGend__image[];
extern u_long   SE_BGend__clut[];
extern u_long   SE_BORI00_image[];
extern u_long   SE_BORI00_clut[];
extern u_long   SE_HANA_image[];
extern u_long   SE_HANA_clut[];
extern u_long   SE_ITEM_image[];
extern u_long   SE_ITEM_clut[];
extern u_long   SE_KAYO_image[];
extern u_long   SE_KAYO_clut[];
extern u_long   SE_MEGAHANA_image[];
extern u_long   SE_MEGAHANA_clut[];
extern u_long   help_00_image[];
extern u_long   help_00_clut[];


extern int      active; /* アクティブ(でない）描画領域 */
extern GsOT     Wot[2];
static GsBOXF   Box;
static GsBOXF   BoxDataBlack[] =    {0x00000000,  0,  0,320,240,0x00,0x00,0x00};
static GsBOXF   BoxDataWhite[] =    {0x00000000,  0,  0,320,240,0xFF,0xFF,0xFF};


//-----------------------------------------------------------------------------
//  variable
//-----------------------------------------------------------------------------
//------------------------------------------ゲーム管理
static SEES_GAME SGameMgr;


//------------------------------------------ロードファイル名
//----GAME
static TIMD SeesGameTextureFile[] = {
    //  デモタイトル名、    BINファイル名
    {   "RCUBE3",           "\\TIM\\SEESGD.B;1"},
};

//----EVENT
static TIMD SeesEventTextureFile[] = {
    //  デモタイトル名、    BINファイル名
    {   "RCUBE3",           "\\TIM\\SEESED.B;1"},
};


//------------------------------------------テクスチャデータ
//----GAME SG_
static GsIMAGE SeesGameTextureImage[]=
{
    //-------------------------------------------------------------------------------------------------------
    //                  tpos        size        image               pos         size        clut
    //-------------------------------------------------------------------------------------------------------
    {   TIM_COLOR_16,   384,0,      64,256,     font_image,         16,480,     16,6,       font_clut       },
    {   TIM_COLOR_16,   448,0,      64,256,     YorN_image,         0,480,      16,16,      YorN_clut       },
    {   TIM_COLOR_16,   512,0,      64,256,     help_00_image,      0,496,      16,2,       help_00_clut    },
    {   TIM_COLOR_16,   320,0,      64,256,     MMENU_image,        16,489,     16,7,       MMENU_clut      },
    //-------------------------------------------------------------------------------------------------------
    {   TIM_COLOR_256,  512,256,    128,256,    SG_BG00_image,      0,509,      256,1,      SG_BG00_clut    },
    {   TIM_COLOR_256,  768,256,    32,256,     SG_BG00__image,     0,508,      256,1,      SG_BG00__clut   },
    {   TIM_COLOR_256,  576,0,      128,256,    SG_BGgame_image,    0,507,      256,1,      SG_BGgame_clut  },
    {   TIM_COLOR_256,  768,0,      32,256,     SG_BGgame__image,   0,506,      256,1,      SG_BGgame__clut },
    {   TIM_COLOR_256,  640,256,    128,256,    SG_BGlv_image,      0,511,      256,1,      SG_BGlv_clut    },
    {   TIM_COLOR_256,  832,0,      32,256,     SG_BGlv__image,     0,510,      256,1,      SG_BGlv__clut   },
    {   TIM_COLOR_16,   832,256,    64,256,     SG_BORI00_image,    144,480,    16,16,      SG_BORI00_clut  },
    {   TIM_COLOR_16,   704,0,      64,256,     SG_BORI01_image,    112,480,    16,16,      SG_BORI01_clut  },
    {   TIM_COLOR_16,   320,256,    64,256,     SG_ITEM_image,      80,480,     16,16,      SG_ITEM_clut    },
    {   TIM_COLOR_16,   384,256,    64,256,     SG_KAYO_image,      96,480,     16,16,      SG_KAYO_clut    },
    {   TIM_COLOR_16,   448,256,    64,256,     SG_LEVEL_image,     128,480,    16,16,      SG_LEVEL_clut   },
    //-------------------------------------------------------------------------------------------------------
};

//----EVENT
static GsIMAGE SeesEventTextureImage[]=
{
    //-------------------------------------------------------------------------------------------------------
    //                  tpos        size        image               pos         size        clut
    //-------------------------------------------------------------------------------------------------------
    {   TIM_COLOR_16,   384,0,      64,256,     font_image,         16,480,     16,6,       font_clut       },
    {   TIM_COLOR_16,   448,0,      64,256,     YorN_image,         0,480,      16,16,      YorN_clut       },
    {   TIM_COLOR_16,   512,0,      64,256,     help_00_image,      0,496,      16,2,       help_00_clut    },
    {   TIM_COLOR_16,   320,0,      64,256,     MMENU_image,        16,489,     16,7,       MMENU_clut      },
    //-------------------------------------------------------------------------------------------------------
    {   TIM_COLOR_256,  576,0,      128,256,    SE_BG01_image,      0,511,      256,1,      SE_BG01_clut    },
    {   TIM_COLOR_256,  768,256,    32,256,     SE_BG01__image,     0,508,      256,1,      SE_BG01__clut   },
    {   TIM_COLOR_256,  576,256,    128,256,    SE_BG02_image,      0,510,      256,1,      SE_BG02_clut    },
    {   TIM_COLOR_256,  704,256,    32,256,     SE_BG02__image,     0,509,      256,1,      SE_BG02__clut   },
    {   TIM_COLOR_16,   512,256,    64,256,     SE_BGend_image,     160,481,    16,1,       SE_BGend_clut   },
    {   TIM_COLOR_16,   832,256,    16,256,     SE_BGend__image,    160,480,    16,1,       SE_BGend__clut  },
    {   TIM_COLOR_16,   704,0,      64,256,     SE_BORI00_image,    144,480,    16,16,      SE_BORI00_clut  },
    {   TIM_COLOR_16,   768,0,      64,256,     SE_HANA_image,      128,480,    16,16,      SE_HANA_clut    },
    {   TIM_COLOR_16,   320,256,    64,256,     SE_ITEM_image,      80,480,     16,16,      SE_ITEM_clut    },
    {   TIM_COLOR_16,   384,256,    64,256,     SE_KAYO_image,      96,480,     16,16,      SE_KAYO_clut    },
    {   TIM_COLOR_16,   448,256,    64,256,     SE_MEGAHANA_image,  112,480,    16,16,      SE_MEGAHANA_clut},
    //-------------------------------------------------------------------------------------------------------
};


//----------------------------------------スプライト登録データ
//----GAME
static ENTRY_SPRITE_DATA SeesGameSpriteData[] =
{
    //-----------------------------------------------------------------------------------------
    //  TexNo                       TimLX   TimLY   Height  Width   PalNo
    //--------------------------------------------------------------------------------[BG00.TIM]
    {   TIM_POS_SEES_GAME_BG00,     0,      0,      240,    256,    0   },          //背景１
    //--------------------------------------------------------------------------------[BG00_.TIM]
    {   TIM_POS_SEES_GAME_BG00_,    256,    0,      240,    64,     0   },          //背景2
    //--------------------------------------------------------------------------------[BGgame.TIM]
    {   TIM_POS_SEES_GAME_BGGAME,   0,      0,      240,    256,    0   },          //ゲーム背景１
    //--------------------------------------------------------------------------------[BGgame_.TIM]
    {   TIM_POS_SEES_GAME_BGGAME_,  256,    0,      240,    64,     0   },          //ゲーム背景2
    //--------------------------------------------------------------------------------[BGlv.TIM]
    {   TIM_POS_SEES_GAME_BGLV,     0,      0,      240,    256,    0   },          //レベルセレクト背景１
    //--------------------------------------------------------------------------------[BGlv_.TIM]
    {   TIM_POS_SEES_GAME_BGLV_,    256,    0,      240,    64,     0   },          //レベルセレクト背景2
    //--------------------------------------------------------------------------------[BORI00.TIM]
    {   TIM_POS_SEES_GAME_BORI00,   0,      0,      90,     94,     0   },          //マシン付きボーリー横向き          204,99
    {   TIM_POS_SEES_GAME_BORI00,   94,     0,      90,     115,    0   },          //マシン付きボーリー正面            184,99
    {   TIM_POS_SEES_GAME_BORI00,   210,    0,      22,     26,     0   },          //マシン付きボーリー横手・上        244,127
    {   TIM_POS_SEES_GAME_BORI00,   210,    22,     22,     26,     0   },          //マシン付きボーリー横手・下        244,134
    {   TIM_POS_SEES_GAME_BORI00,   210,    44,     32,     28,     0   },          //マシン付きボーリー正面手・上      244,117
    {   TIM_POS_SEES_GAME_BORI00,   210,    76,     36,     28,     0   },          //マシン付きボーリー正面手・下      244,118
    {   TIM_POS_SEES_GAME_BORI00,   0,      90,     58,     72,     1   },          //メガトン博士口開けバンザイ        110,133     
    {   TIM_POS_SEES_GAME_BORI00,   72,     90,     51,     60,     1   },          //メガトン博士皿持ち口閉じ        46,26     
    {   TIM_POS_SEES_GAME_BORI00,   132,    90,     51,     60,     1   },          //メガトン博士しっぽ              46,26     
    {   TIM_POS_SEES_GAME_BORI00,   0,      148,    47,     58,     1   },          //メガトン博士標準・口開け        46,30     
    {   TIM_POS_SEES_GAME_BORI00,   58,     148,    47,     58,     1   },          //メガトン博士標準・口閉じ        46,30     
    {   TIM_POS_SEES_GAME_BORI00,   116,    148,    47,     58,     1   },          //メガトン博士標準・足短          46,30     
    {   TIM_POS_SEES_GAME_BORI00,   0,      195,    60,     58,     1   },          //メガトン博士ジャンプ            44,29     
    {   TIM_POS_SEES_GAME_BORI00,   58,     195,    48,     62,     1   },          //メガトン博士ジャンプ・口開け    44,29     
    {   TIM_POS_SEES_GAME_BORI00,   120,    195,    58,     74,     1   },          //メガトン博士微笑                110,133       
    {   TIM_POS_SEES_GAME_BORI00,   192,    112,    67,     61,     1   },          //メガトン博士負け                44,29     
    {   TIM_POS_SEES_GAME_BORI00,   194,    195,    47,     58,     1   },          //メガトン博士バンザイ・笑        44,29     
    //--------------------------------------------------------------------------------[BORI01.TIM]
    {   TIM_POS_SEES_GAME_BORI01,   0,      0,      108,    81,     0   },          //ボーリー　ばらばら胴体        44,123
    {   TIM_POS_SEES_GAME_BORI01,   82,     0,      84,     20,     0   },          //ボーリー　標準左手            30,126
    {   TIM_POS_SEES_GAME_BORI01,   210,    171,    84,     20,     0   },          //ボーリー　標準右手            120,126
    {   TIM_POS_SEES_GAME_BORI01,   118,    0,      45,     32,     0   },          //ボーリー　右手真下指差し      112,124
    {   TIM_POS_SEES_GAME_BORI01,   150,    0,      35,     44,     0   },          //ボーリー　左手下指差し        6,125   
    {   TIM_POS_SEES_GAME_BORI01,   195,    0,      36,     37,     0   },          //ボーリー　左手真下指差し      24,124  
    {   TIM_POS_SEES_GAME_BORI01,   232,    0,      24,     24,     0   },          //ボーリー　笑った顔            72,118  
    {   TIM_POS_SEES_GAME_BORI01,   118,    45,     40,     64,     0   },          //ボーリー　中央下指差し        74,124  
    {   TIM_POS_SEES_GAME_BORI01,   182,    36,     56,     40,     0   },          //ボーリー　左手上腕差し        118,93  
    {   TIM_POS_SEES_GAME_BORI01,   0,      108,    52,     92,     0   },          //ボーリー　首傾げ・右手曲げ    60,96   
    {   TIM_POS_SEES_GAME_BORI01,   210,    163,    8,      22,     0   },          //ボーリー　首傾げ。口パク      72,136  
    {   TIM_POS_SEES_GAME_BORI01,   92,     108,    55,     100,    0   },          //ボーリー　両手中央寄せ        34,124  
    {   TIM_POS_SEES_GAME_BORI01,   192,    108,    50,     47,     0   },          //ボーリー　標準・顔            60,96   
    {   TIM_POS_SEES_GAME_BORI01,   0,      162,    55,     100,    0   },          //ボーリー　両手合わせ          36,124  
    {   TIM_POS_SEES_GAME_BORI01,   100,    163,    54,     110,    0   },          //ボーリー　右手上げ            58,97   
    {   TIM_POS_SEES_GAME_BORI01,   0,      217,    33,     56,     0   },          //ボーリー　右手下指差し        118,125 
    //--------------------------------------------------------------------------------[ITEM.TIM]
    {   TIM_POS_SEES_GAME_ITEM,     0,      0,      34,     22,     0   },          //20,28/278,28  レベル１数字1
    {   TIM_POS_SEES_GAME_ITEM,     22,     0,      34,     22,     0   },          //20,28/278,28  レベル１数字2
    {   TIM_POS_SEES_GAME_ITEM,     44,     0,      34,     22,     0   },          //20,28/278,28  レベル１数字3
    {   TIM_POS_SEES_GAME_ITEM,     66,     0,      34,     22,     0   },          //20,28/278,28  レベル１数字4
    {   TIM_POS_SEES_GAME_ITEM,     88,     0,      34,     22,     0   },          //20,28/278,28  レベル１数字5
    {   TIM_POS_SEES_GAME_ITEM,     110,    0,      34,     22,     0   },          //20,28/278,28  レベル１数字6
    {   TIM_POS_SEES_GAME_ITEM,     132,    0,      34,     22,     0   },          //20,28/278,28  レベル１数字7
    {   TIM_POS_SEES_GAME_ITEM,     154,    0,      34,     22,     0   },          //20,28/278,28  レベル１数字8
    {   TIM_POS_SEES_GAME_ITEM,     176,    0,      34,     22,     0   },          //20,28/278,28  レベル１数字9
    {   TIM_POS_SEES_GAME_ITEM,     198,    0,      34,     22,     0   },          //20,28/278,28  レベル１数字0
    {   TIM_POS_SEES_GAME_ITEM,     0,      34,     18,     19,     1   },          //ゲーム用数字（数字枠
    {   TIM_POS_SEES_GAME_ITEM,     20,     34,     10,     6,      1   },          //ゲーム用数字（1
    {   TIM_POS_SEES_GAME_ITEM,     26,     34,     10,     6,      1   },          //ゲーム用数字（2
    {   TIM_POS_SEES_GAME_ITEM,     32,     34,     10,     6,      1   },          //ゲーム用数字（3
    {   TIM_POS_SEES_GAME_ITEM,     38,     34,     10,     6,      1   },          //ゲーム用数字（4
    {   TIM_POS_SEES_GAME_ITEM,     44,     34,     10,     6,      1   },          //ゲーム用数字（5
    {   TIM_POS_SEES_GAME_ITEM,     50,     34,     10,     6,      1   },          //ゲーム用数字（6
    {   TIM_POS_SEES_GAME_ITEM,     56,     34,     10,     6,      1   },          //ゲーム用数字（7
    {   TIM_POS_SEES_GAME_ITEM,     62,     34,     10,     6,      1   },          //ゲーム用数字（8
    {   TIM_POS_SEES_GAME_ITEM,     68,     34,     10,     6,      1   },          //ゲーム用数字（9
    {   TIM_POS_SEES_GAME_ITEM,     74,     34,     10,     6,      1   },          //ゲーム用数字（0
    {   TIM_POS_SEES_GAME_ITEM,     0,      53,     26,     48,     2   },          //認識枠・大
    {   TIM_POS_SEES_GAME_ITEM,     48,     53,     21,     48,     2   },          //認識枠・中
    {   TIM_POS_SEES_GAME_ITEM,     96,     53,     24,     26,     2   },          //認識枠・小
    {   TIM_POS_SEES_GAME_ITEM,     122,    53,     18,     19,     2   },          //星枠
    {   TIM_POS_SEES_GAME_ITEM,     0,      80,     15,     40,     3   },          //中身かご
    {   TIM_POS_SEES_GAME_ITEM,     40,     80,     15,     40,     3   },          //カゴ
    {   TIM_POS_SEES_GAME_ITEM,     80,     80,     8,      8,      4   },          //りんご・黄
    {   TIM_POS_SEES_GAME_ITEM,     88,     80,     8,      8,      4   },          //りんご・赤
    {   TIM_POS_SEES_GAME_ITEM,     0,      96,     19,     182,    5   },          //ゲーム後勝ち負けプレート(かち)
    {   TIM_POS_SEES_GAME_ITEM,     0,      115,    19,     182,    5   },          //ゲーム後勝ち負けプレート(まけ)
    {   TIM_POS_SEES_GAME_ITEM,     0,      134,    20,     108,    6   },          //シーソー左
    {   TIM_POS_SEES_GAME_ITEM,     108,    134,    20,     108,    6   },          //シーソー右
    {   TIM_POS_SEES_GAME_ITEM,     0,      154,    37,     8,      7   },          //左標準
    {   TIM_POS_SEES_GAME_ITEM,     8,      154,    37,     8,      7   },          //左1
    {   TIM_POS_SEES_GAME_ITEM,     16,     154,    37,     8,      7   },          //左2
    {   TIM_POS_SEES_GAME_ITEM,     24,     154,    37,     8,      7   },          //左3
    {   TIM_POS_SEES_GAME_ITEM,     32,     154,    37,     8,      7   },          //左4
    {   TIM_POS_SEES_GAME_ITEM,     40,     154,    37,     8,      7   },          //左5
    {   TIM_POS_SEES_GAME_ITEM,     48,     154,    37,     8,      7   },          //右標準
    {   TIM_POS_SEES_GAME_ITEM,     56,     154,    37,     8,      7   },          //右1
    {   TIM_POS_SEES_GAME_ITEM,     64,     154,    37,     8,      7   },          //右2
    {   TIM_POS_SEES_GAME_ITEM,     72,     154,    37,     8,      7   },          //右3
    {   TIM_POS_SEES_GAME_ITEM,     80,     154,    37,     8,      7   },          //右4
    {   TIM_POS_SEES_GAME_ITEM,     88,     154,    37,     8,      7   },          //右5
    {   TIM_POS_SEES_GAME_ITEM,     104,    154,    86,     44,     8   },          //虹色マシンA
    {   TIM_POS_SEES_GAME_ITEM,     148,    154,    86,     44,     8   },          //虹色マシンB
    {   TIM_POS_SEES_GAME_ITEM,     0,      200,    18,     20,     9   },          //マシン点滅左
    {   TIM_POS_SEES_GAME_ITEM,     0,      218,    18,     20,     9   },          //マシン点滅右
    {   TIM_POS_SEES_GAME_ITEM,     82,     34,     18,     26,     1   },          //カードワク
    {   TIM_POS_SEES_GAME_ITEM,     108,    34,     18,     26,     2   },          //★ワク
    //--------------------------------------------------------------------------------[KAYO.TIM]
    {   TIM_POS_SEES_GAME_KAYO,     0,      0,      46,     40,     0   },          //カヨリーヌ(標準・口開け)  226,31  
    {   TIM_POS_SEES_GAME_KAYO,     40,     0,      46,     40,     0   },          //カヨリーヌ(標準・口閉じ)  226,31  
    {   TIM_POS_SEES_GAME_KAYO,     80,     0,      46,     40,     0   },          //カヨリーヌ(首傾げ)        226,31  
    {   TIM_POS_SEES_GAME_KAYO,     120,    0,      46,     40,     0   },          //カヨリーヌ(両手合わせ)    226,31  
    {   TIM_POS_SEES_GAME_KAYO,     160,    0,      46,     48,     0   },          //カヨリーヌ(バンザイ)      226,31  
    {   TIM_POS_SEES_GAME_KAYO,     0,      46,     58,     64,     0   },          //カヨリーヌ(バンザイ)      40,129  
    {   TIM_POS_SEES_GAME_KAYO,     64,     46,     58,     64,     0   },          //カヨリーヌ(笑う)          40,129  
    {   TIM_POS_SEES_GAME_KAYO,     128,    46,     58,     52,     0   },          //カヨリーヌ(負けA)         228,126 
    {   TIM_POS_SEES_GAME_KAYO,     180,    46,     58,     52,     0   },          //カヨリーヌ(負けB)         228,126 
    {   TIM_POS_SEES_GAME_KAYO,     0,      104,    46,     50,     0   },          //カヨリーヌ(皿持ち)        222,30  
    {   TIM_POS_SEES_GAME_KAYO,     96,     150,    90,     105,    1   },          //カヨリーヌ(花火)          108,20  
    //--------------------------------------------------------------------------------[LEVEL.TIM]
    {   TIM_POS_SEES_GAME_LEVEL,    0,      0,      42,     48,     0   },          //団長00アニメ
    {   TIM_POS_SEES_GAME_LEVEL,    48,     0,      42,     48,     0   },          //団長01アニメ
    {   TIM_POS_SEES_GAME_LEVEL,    0,      42,     33,     40,     0   },          //青風船時01・橙風船時02　楽団員A00アニメ
    {   TIM_POS_SEES_GAME_LEVEL,    40,     42,     33,     40,     0   },          //同上  楽団員A01アニメ
    {   TIM_POS_SEES_GAME_LEVEL,    0,      42,     33,     40,     1   },          //青風船時01・橙風船時02　楽団員A00アニメ
    {   TIM_POS_SEES_GAME_LEVEL,    40,     42,     33,     40,     1   },          //同上  楽団員A01アニメ
    {   TIM_POS_SEES_GAME_LEVEL,    80,     42,     33,     40,     1   },          //楽団員B00アニメ
    {   TIM_POS_SEES_GAME_LEVEL,    120,    42,     33,     40,     1   },          //楽団員B01アニメ
    {   TIM_POS_SEES_GAME_LEVEL,    160,    42,     33,     40,     2   },          //楽団員C00アニメ
    {   TIM_POS_SEES_GAME_LEVEL,    200,    42,     33,     40,     2   },          //楽団員C01アニメ
    {   TIM_POS_SEES_GAME_LEVEL,    96,     0,      14,     20,     3   },          //レベル選択カーソル枠
    {   TIM_POS_SEES_GAME_LEVEL,    96,     14,     9,      18,     3   },          //レベルブロック明るい
    {   TIM_POS_SEES_GAME_LEVEL,    96,     14,     9,      18,     4   },          //レベルブロック暗い
    {   TIM_POS_SEES_GAME_LEVEL,    96,     24,     10,     8,      5   },          //レベル選択用数字1
    {   TIM_POS_SEES_GAME_LEVEL,    104,    24,     10,     8,      5   },          //レベル選択用数字2
    {   TIM_POS_SEES_GAME_LEVEL,    112,    24,     10,     8,      5   },          //レベル選択用数字3
    {   TIM_POS_SEES_GAME_LEVEL,    120,    24,     10,     8,      5   },          //レベル選択用数字4
    {   TIM_POS_SEES_GAME_LEVEL,    128,    24,     10,     8,      5   },          //レベル選択用数字5
    {   TIM_POS_SEES_GAME_LEVEL,    0,      80,     37,     58,     6   },          //メガトン博士１枚絵の口パク    82,98       
    //-----------------------------------------------------------------------------------------[font.TIM]
    {   TIM_POS_SEES_EVENT_FONT,    24,     200,    24,     26,     2   },          //指カーソル
    //-----------------------------------------------------------------------------------------
    {   ENTRY_SPRITE_DATA_END,0,0,0,0,0 }   // データエンド
};

//----EVENT
static ENTRY_SPRITE_DATA SeesEventSpriteData[] =
{
    //-----------------------------------------------------------------------------------------
    //  TexNo                       TimLX   TimLY   Height  Width   PalNo
    //--------------------------------------------------------------------------------[BG01.TIM]
    {   TIM_POS_SEES_EVENT_BG01,        0,      0,      240,    256,    0   },          //背景１
    //--------------------------------------------------------------------------------[BG01_.TIM]
    {   TIM_POS_SEES_EVENT_BG01_,       256,    0,      240,    64,     0   },          //背景2
    //--------------------------------------------------------------------------------[BG02.TIM]
    {   TIM_POS_SEES_EVENT_BG02,        0,      0,      240,    256,    0   },          //背景１
    //--------------------------------------------------------------------------------[BG02_.TIM]
    {   TIM_POS_SEES_EVENT_BG02_,       256,    0,      240,    64,     0   },          //背景2
    //--------------------------------------------------------------------------------[BGend.TIM]
    {   TIM_POS_SEES_EVENT_BGEND,       0,      0,      240,    256,    0   },          //イベント背景１
    //--------------------------------------------------------------------------------[BGend_.TIM]
    {   TIM_POS_SEES_EVENT_BGEND_,      256,    0,      240 ,   64,     0   },          //イベント背景2
    //--------------------------------------------------------------------------------[BORI00.TIM]
    {   TIM_POS_SEES_EVENT_BORI00,      0,      0,      90,     94,     0   },      //マシン付きボーリー横向き          204,99
    {   TIM_POS_SEES_EVENT_BORI00,      94,     0,      90,     115,    0   },      //マシン付きボーリー正面            184,99
    {   TIM_POS_SEES_EVENT_BORI00,      210,    0,      22,     26,     0   },      //マシン付きボーリー横手・上        244,127
    {   TIM_POS_SEES_EVENT_BORI00,      210,    22,     22,     26,     0   },      //マシン付きボーリー横手・下        244,134
    {   TIM_POS_SEES_EVENT_BORI00,      210,    44,     32,     28,     0   },      //マシン付きボーリー正面手・上      244,117
    {   TIM_POS_SEES_EVENT_BORI00,      210,    76,     36,     28,     0   },      //マシン付きボーリー正面手・下      244,118
    {   TIM_POS_SEES_EVENT_BORI00,      0,      90,     58,     72,     1   },      //メガトン博士口開けバンザイ        110,133     
    {   TIM_POS_SEES_EVENT_BORI00,      72,     90,     51,     60,     1   },      //メガトン博士皿持ち口閉じ        46,26     
    {   TIM_POS_SEES_EVENT_BORI00,      132,    90,     51,     60,     1   },      //メガトン博士しっぽ              46,26     
    {   TIM_POS_SEES_EVENT_BORI00,      0,      148,    47,     58,     1   },      //メガトン博士標準・口開け        46,30     
    {   TIM_POS_SEES_EVENT_BORI00,      58,     148,    47,     58,     1   },      //メガトン博士標準・口閉じ        46,30     
    {   TIM_POS_SEES_EVENT_BORI00,      116,    148,    47,     58,     1   },      //メガトン博士標準・足短          46,30     
    {   TIM_POS_SEES_EVENT_BORI00,      0,      195,    60,     58,     1   },      //メガトン博士ジャンプ            44,29     
    {   TIM_POS_SEES_EVENT_BORI00,      58,     195,    48,     62,     1   },      //メガトン博士ジャンプ・口開け    44,29     
    {   TIM_POS_SEES_EVENT_BORI00,      120,    195,    58,     74,     1   },      //メガトン博士微笑                110,133       
    {   TIM_POS_SEES_EVENT_BORI00,      192,    112,    67,     61,     1   },      //メガトン博士負け                44,29     
    {   TIM_POS_SEES_EVENT_BORI00,      194,    195,    47,     58,     1   },      //メガトン博士バンザイ・笑        44,29     
    //--------------------------------------------------------------------------------[HANA.TIM]
    {   TIM_POS_SEES_EVENT_HANA,        0,      0,      90,     194,    0   },      //花火大                64,18   
    {   TIM_POS_SEES_EVENT_HANA,        0,      90,     93,     170,    0   },      //花火中              76,41 
    {   TIM_POS_SEES_EVENT_HANA,        170,    90,     68,     77,     0   },      //花火小              84,85 
    {   TIM_POS_SEES_EVENT_HANA,        170,    158,    68,     77,     0   },      //花火小・赤紫        162,26    
    {   TIM_POS_SEES_EVENT_HANA,        0,      183,    30,     33,     1   },      //星A                 64,35 
    {   TIM_POS_SEES_EVENT_HANA,        34,     183,    30,     33,     1   },      //星B                 64,35 
    {   TIM_POS_SEES_EVENT_HANA,        168,    226,    10,     18,     2   },      //花火種A
    {   TIM_POS_SEES_EVENT_HANA,        186,    226,    10,     18,     2   },      //花火種B
    //--------------------------------------------------------------------------------[ITEM.TIM]
    {   TIM_POS_SEES_EVENT_ITEM,        0,      0,      34,     22,     0   },          //20,28/278,28  レベル１数字1
    {   TIM_POS_SEES_EVENT_ITEM,        22,     0,      34,     22,     0   },          //20,28/278,28  レベル１数字2
    {   TIM_POS_SEES_EVENT_ITEM,        44,     0,      34,     22,     0   },          //20,28/278,28  レベル１数字3
    {   TIM_POS_SEES_EVENT_ITEM,        66,     0,      34,     22,     0   },          //20,28/278,28  レベル１数字4
    {   TIM_POS_SEES_EVENT_ITEM,        88,     0,      34,     22,     0   },          //20,28/278,28  レベル１数字5
    {   TIM_POS_SEES_EVENT_ITEM,        110,    0,      34,     22,     0   },          //20,28/278,28  レベル１数字6
    {   TIM_POS_SEES_EVENT_ITEM,        132,    0,      34,     22,     0   },          //20,28/278,28  レベル１数字7
    {   TIM_POS_SEES_EVENT_ITEM,        154,    0,      34,     22,     0   },          //20,28/278,28  レベル１数字8
    {   TIM_POS_SEES_EVENT_ITEM,        176,    0,      34,     22,     0   },          //【×】20,28/278,28    レベル１数字9
    {   TIM_POS_SEES_EVENT_ITEM,        198,    0,      34,     22,     0   },          //20,28/278,28  レベル１数字0
    {   TIM_POS_SEES_EVENT_ITEM,        0,      34,     18,     20,     1   },          //ゲーム用数字（数字枠
    {   TIM_POS_SEES_EVENT_ITEM,        20,     34,     10,     6,      1   },          //ゲーム用数字（1
    {   TIM_POS_SEES_EVENT_ITEM,        26,     34,     10,     6,      1   },          //ゲーム用数字（2
    {   TIM_POS_SEES_EVENT_ITEM,        32,     34,     10,     6,      1   },          //ゲーム用数字（3
    {   TIM_POS_SEES_EVENT_ITEM,        38,     34,     10,     6,      1   },          //ゲーム用数字（4
    {   TIM_POS_SEES_EVENT_ITEM,        44,     34,     10,     6,      1   },          //ゲーム用数字（5
    {   TIM_POS_SEES_EVENT_ITEM,        50,     34,     10,     6,      1   },          //ゲーム用数字（6
    {   TIM_POS_SEES_EVENT_ITEM,        56,     34,     10,     6,      1   },          //ゲーム用数字（7
    {   TIM_POS_SEES_EVENT_ITEM,        62,     34,     10,     6,      1   },          //ゲーム用数字（8
    {   TIM_POS_SEES_EVENT_ITEM,        68,     34,     10,     6,      1   },          //ゲーム用数字（9
    {   TIM_POS_SEES_EVENT_ITEM,        74,     34,     10,     6,      1   },          //ゲーム用数字（0
    {   TIM_POS_SEES_EVENT_ITEM,        0,      53,     26,     48,     2   },          //認識枠・大
    {   TIM_POS_SEES_EVENT_ITEM,        48,     53,     21,     48,     2   },          //認識枠・中
    {   TIM_POS_SEES_EVENT_ITEM,        96,     53,     24,     26,     2   },          //認識枠・小
    {   TIM_POS_SEES_EVENT_ITEM,        122,    53,     18,     19,     2   },          //星枠
    {   TIM_POS_SEES_EVENT_ITEM,        0,      80,     15,     40,     3   },          //中身かご
    {   TIM_POS_SEES_EVENT_ITEM,        40,     80,     15,     40,     3   },          //カゴ
    {   TIM_POS_SEES_EVENT_ITEM,        80,     80,     8,      8,      4   },          //りんご・黄
    {   TIM_POS_SEES_EVENT_ITEM,        88,     80,     8,      8,      4   },          //りんご・赤
    {   TIM_POS_SEES_EVENT_ITEM,        0,      96,     19,     182,    5   },          //ゲーム後勝ち負けプレート(かち)
    {   TIM_POS_SEES_EVENT_ITEM,        0,      115,    19,     182,    5   },          //ゲーム後勝ち負けプレート(まけ)
    {   TIM_POS_SEES_EVENT_ITEM,        0,      134,    20,     108,    6   },          //シーソー左
    {   TIM_POS_SEES_EVENT_ITEM,        108,    134,    20,     108,    6   },          //シーソー右
    {   TIM_POS_SEES_EVENT_ITEM,        0,      154,    37,     8,      7   },          //左標準
    {   TIM_POS_SEES_EVENT_ITEM,        8,      154,    37,     8,      7   },          //左1
    {   TIM_POS_SEES_EVENT_ITEM,        16,     154,    37,     8,      7   },          //左2
    {   TIM_POS_SEES_EVENT_ITEM,        24,     154,    37,     8,      7   },          //左3
    {   TIM_POS_SEES_EVENT_ITEM,        32,     154,    37,     8,      7   },          //左4
    {   TIM_POS_SEES_EVENT_ITEM,        40,     154,    37,     8,      7   },          //左5
    {   TIM_POS_SEES_EVENT_ITEM,        48,     154,    37,     8,      7   },          //右標準
    {   TIM_POS_SEES_EVENT_ITEM,        56,     154,    37,     8,      7   },          //右1
    {   TIM_POS_SEES_EVENT_ITEM,        64,     154,    37,     8,      7   },          //右2
    {   TIM_POS_SEES_EVENT_ITEM,        72,     154,    37,     8,      7   },          //右3
    {   TIM_POS_SEES_EVENT_ITEM,        80,     154,    37,     8,      7   },          //右4
    {   TIM_POS_SEES_EVENT_ITEM,        88,     154,    37,     8,      7   },          //右5
    {   TIM_POS_SEES_EVENT_ITEM,        104,    154,    86,     44,     8   },          //虹色マシンA
    {   TIM_POS_SEES_EVENT_ITEM,        148,    154,    86,     44,     8   },          //虹色マシンB
    {   TIM_POS_SEES_EVENT_ITEM,        0,      200,    18,     20,     9   },          //マシン点滅左
    {   TIM_POS_SEES_EVENT_ITEM,        0,      218,    18,     20,     9   },          //マシン点滅右
    //--------------------------------------------------------------------------------[KAYO.TIM]
    {   TIM_POS_SEES_EVENT_KAYO,        0,      0,      46,     40,     0   },          //カヨリーヌ(標準・口開け       226,31
    {   TIM_POS_SEES_EVENT_KAYO,        40,     0,      46,     40,     0   },          //カヨリーヌ(標準・口閉じ     226,31
    {   TIM_POS_SEES_EVENT_KAYO,        80,     0,      46,     40,     0   },          //カヨリーヌ(首傾げ           226,31        
    {   TIM_POS_SEES_EVENT_KAYO,        120,    0,      46,     40,     0   },          //カヨリーヌ(両手合わせ       226,31        
    {   TIM_POS_SEES_EVENT_KAYO,        160,    0,      46,     48,     0   },          //カヨリーヌ(バンザイ         222,31        
    {   TIM_POS_SEES_EVENT_KAYO,        0,      46,     58,     64,     0   },          //カヨリーヌ(バンザイ　       40,129        
    {   TIM_POS_SEES_EVENT_KAYO,        64,     46,     58,     64,     0   },          //カヨリーヌ(笑う　           40,129        
    {   TIM_POS_SEES_EVENT_KAYO,        128,    46,     58,     52,     0   },          //カヨリーヌ(負けA            228,126       
    {   TIM_POS_SEES_EVENT_KAYO,        180,    46,     58,     52,     0   },          //カヨリーヌ(負けB            228,126       
    {   TIM_POS_SEES_EVENT_KAYO,        0,      104,    46,     50,     0   },          //カヨリーヌ(皿持ち           222,30        
    {   TIM_POS_SEES_EVENT_KAYO,        96,     150,    90,     105,    1   },          //カヨリーヌ(花火             108,20        
    //--------------------------------------------------------------------------------[MEGAHANA.TIM]
    {   TIM_POS_SEES_EVENT_MEGAHANA,    0,      0,      126,    165,    0   },          //メガトン花火(大)      78,10   
    {   TIM_POS_SEES_EVENT_MEGAHANA,    0,      126,    101,    132,    0   },          //メガトン花火(小)        96,20 
    //-----------------------------------------------------------------------------------------[YorNo.TIM]
    {   TIM_POS_SEES_EVENT_YORNO,       0,      0,      115,    186,    0   },          //プレート
    {   TIM_POS_SEES_EVENT_YORNO,       0,      115,    40,     38,     1   },          //非選択・はい 74,57
    {   TIM_POS_SEES_EVENT_YORNO,       38,     115,    40,     44,     1   },          //非選択・いいえ 126,57
    {   TIM_POS_SEES_EVENT_YORNO,       82,     115,    40,     44,     2   },          //選択・はい 72,57
    {   TIM_POS_SEES_EVENT_YORNO,       126,    115,    40,     44,     2   },          //選択・いいえ 126,57
    {   TIM_POS_SEES_EVENT_YORNO,       186,    0,      69,     58,     3   },          //プーぺ１
    {   TIM_POS_SEES_EVENT_YORNO,       186,    69,     69,     58,     3   },          //プーぺ２
    {   TIM_POS_SEES_EVENT_YORNO,       0,      155,    14,     148,    4   },          //もういちど
    {   TIM_POS_SEES_EVENT_YORNO,       0,      170,    14,     148,    4   },          //おわり
    {   TIM_POS_SEES_EVENT_YORNO,       20,     20,     14,     148,    4   },          //つづけ
    //-----------------------------------------------------------------------------------------[font.TIM]
    {   TIM_POS_SEES_EVENT_FONT,        24,     200,    24,     26,     2   },          //指カーソル
    {   TIM_POS_SEES_EVENT_FONT,        0,      232,    15,     52,     4   },          //えらぶ
    {   TIM_POS_SEES_EVENT_FONT,        52,     232,    15,     52,     4   },          //けってい
    {   TIM_POS_SEES_EVENT_FONT,        104,    232,    15,     52,     4   },          //めにゅー
    //-----------------------------------------------------------------------------------------
    {   ENTRY_SPRITE_DATA_END,0,0,0,0,0 }   // データエンド
};


//----------------------------------------カロリーヌスプライトデータ
static SEES_SPRITE_DATA KyGameSpriteTable[]=
{
    {   SEES_CHAR_GAME_KY_00,   0,      -36 },      //カヨリーヌ(標準・口開け)  
    {   SEES_CHAR_GAME_KY_01,   0,      -36 },      //カヨリーヌ(標準・口閉じ)  
    {   SEES_CHAR_GAME_KY_01,   0,      -36 },      //カヨリーヌ(標準・口閉じ)  
    {   SEES_CHAR_GAME_KY_02,   0,      -36 },      //カヨリーヌ(首傾げ)        
    {   SEES_CHAR_GAME_KY_03,   -1,     -36 },      //カヨリーヌ(両手合わせ)    
    {   SEES_CHAR_GAME_KY_04,   -5,     -36 },      //カヨリーヌ(バンザイ)      
    {   SEES_CHAR_GAME_KY_09,   -6,     -36 },      //カヨリーヌ(皿持ち)        
    {   SEES_CHAR_GAME_KY_09,   -6,     -36 },      //カヨリーヌ(皿持ち)        
    {   SEES_CHAR_GAME_KY_04,   -5,     -36 },      //カヨリーヌ(バンザイ)      
    {   SEES_CHAR_GAME_KY_04,   -5,     -36 },      //カヨリーヌ(バンザイ)      
};


//----------------------------------------博士スプライトデータ
static SEES_SPRITE_DATA DrGameSpriteTable[]=
{
    {   SEES_CHAR_GAME_DR_01,       -1, -41 },  //メガトン博士皿持ち口閉じ    
    {   SEES_CHAR_GAME_DR_02,       -1, -41 },  //メガトン博士しっぽ          
    {   SEES_CHAR_GAME_DR_03,       0,  -37 },  //メガトン博士標準・口開け    
    {   SEES_CHAR_GAME_DR_04,       0,  -37 },  //メガトン博士標準・口閉じ    
    {   SEES_CHAR_GAME_DR_04,       0,  -37 },  //メガトン博士標準・口閉じ    
    {   SEES_CHAR_GAME_DR_05,       0,  -37 },  //メガトン博士標準・足短      
    {   SEES_CHAR_GAME_DR_04,       0,  -37 },  //メガトン博士標準・口閉じ    
    {   SEES_CHAR_GAME_DR_07,       -2, -38 },  //メガトン博士ジャンプ・口開け
    {   SEES_CHAR_GAME_DR_04,       0,  -37 },  //メガトン博士標準・口閉じ    
    {   SEES_CHAR_GAME_DR_04,       0,  -37 },  //メガトン博士標準・口閉じ    
};


//----------------------------------------アシスタントスプライトデータ
static SEES_SPRITE_DATA AsGameSpriteTable[]=
{
    {   SEES_CHAR_GAME_AS_BODY,         44,     123 + BG_OFFSET_Y + 11  },      //ばらばら胴体
    {   SEES_CHAR_GAME_AS_PARTS_00,     30,     126 + BG_OFFSET_Y + 11  },      //標準左手
    {   SEES_CHAR_GAME_AS_PARTS_01,     120,    126 + BG_OFFSET_Y + 11  },      //標準右手
    {   SEES_CHAR_GAME_AS_PARTS_02,     112,    124 + BG_OFFSET_Y + 11  },      //右手真下指差し
    {   SEES_CHAR_GAME_AS_PARTS_03,     6,      125 + BG_OFFSET_Y + 11  },      //左手下指差し
    {   SEES_CHAR_GAME_AS_PARTS_04,     24,     124 + BG_OFFSET_Y + 11  },      //左手真下指差し
    {   SEES_CHAR_GAME_AS_PARTS_05,     72,     118 + BG_OFFSET_Y + 11  },      //笑った顔
    {   SEES_CHAR_GAME_AS_PARTS_06,     74,     124 + BG_OFFSET_Y + 11  },      //中央下指差し
    {   SEES_CHAR_GAME_AS_PARTS_07,     118,    93  + BG_OFFSET_Y + 11  },      //左手上腕差し
    {   SEES_CHAR_GAME_AS_PARTS_08,     60,     96  + BG_OFFSET_Y + 11  },      //首傾げ・右手曲げ
    {   SEES_CHAR_GAME_AS_PARTS_09,     72,     136 + BG_OFFSET_Y + 11  },      //首傾げ。口パク
    {   SEES_CHAR_GAME_AS_PARTS_10,     34,     124 + BG_OFFSET_Y + 11  },      //両手中央寄せ
    {   SEES_CHAR_GAME_AS_PARTS_11,     60,     96  + BG_OFFSET_Y + 11  },      //標準・顔
    {   SEES_CHAR_GAME_AS_PARTS_12,     36,     124 + BG_OFFSET_Y + 11  },      //両手合わせ
    {   SEES_CHAR_GAME_AS_PARTS_13,     58,     97  + BG_OFFSET_Y + 11  },      //右手上げ
    {   SEES_CHAR_GAME_AS_PARTS_14,     118,    125 + BG_OFFSET_Y + 11  },      //右手下指差し
};


//----------------------------------------アシスタントパーツインデックステーブル
static int AsGamePartsIndexTable[][10]=
{
    {   0,  12, 1,  2,  -1, 0,  0,  0,  0,  -1  },          //AS_SPTYPE_STAND                   立ち
    {   0,  1,  14, -1, 0,  0,  0,  0,  0,  -1  },          //AS_SPTYPE_QUESTION                左手上げ（答え選択中）
    {   0,  14, 1,  10, -1, 0,  0,  0,  0,  -1  },          //AS_SPTYPE_QUESTION_MOUTH_OPEN     左手上げ口開け（答え選択中）
    {   0,  12, 1,  8,  -1, 0,  0,  0,  0,  -1  },          //AS_SPTYPE_ONCE_AGAIN              もう一度（一指し指上げ）
    {   0,  1,  9,  -1, 0,  0,  0,  0,  0,  -1  },          //AS_SPTYPE_SELECT_QUESTION_00      問題選択（頭に手を置く）
    {   0,  12, 4,  2,  -1, 0,  0,  0,  0,  -1  },          //AS_SPTYPE_SELECT_QUESTION_01      問題選択（１選択）
    {   0,  12, 5,  2,  -1, 0,  0,  0,  0,  -1  },          //AS_SPTYPE_SELECT_QUESTION_02      問題選択（２選択）
    {   0,  12, 7,  1,  -1, 0,  0,  0,  0,  -1  },          //AS_SPTYPE_SELECT_QUESTION_03      問題選択（３選択）
    {   0,  12, 3,  1,  -1, 0,  0,  0,  0,  -1  },          //AS_SPTYPE_SELECT_QUESTION_04      問題選択（４選択）
    {   0,  12, 15, 1,  -1, 0,  0,  0,  0,  -1  },          //AS_SPTYPE_SELECT_QUESTION_05      問題選択（５選択）
};


//----------------------------------------数字スプライトテーブル
static int SmallNumSpriteTable[]=
{
    SEES_CHAR_GAME_PLATE_NUM_00,        //ゲーム用数字（0
    SEES_CHAR_GAME_PLATE_NUM_01,        //ゲーム用数字（1
    SEES_CHAR_GAME_PLATE_NUM_02,        //ゲーム用数字（2
    SEES_CHAR_GAME_PLATE_NUM_03,        //ゲーム用数字（3
    SEES_CHAR_GAME_PLATE_NUM_04,        //ゲーム用数字（4
    SEES_CHAR_GAME_PLATE_NUM_05,        //ゲーム用数字（5
    SEES_CHAR_GAME_PLATE_NUM_06,        //ゲーム用数字（6
    SEES_CHAR_GAME_PLATE_NUM_07,        //ゲーム用数字（7
    SEES_CHAR_GAME_PLATE_NUM_08,        //ゲーム用数字（8
    SEES_CHAR_GAME_PLATE_NUM_09,        //ゲーム用数字（9
};


static int BigNumSpriteTable[]=
{
    SEES_CHAR_GAME_COUNT_NUM_0,         //レベル１数字0
    SEES_CHAR_GAME_COUNT_NUM_1,         //カウント数字1
    SEES_CHAR_GAME_COUNT_NUM_2,         //カウント数字2
    SEES_CHAR_GAME_COUNT_NUM_3,         //カウント数字3
    SEES_CHAR_GAME_COUNT_NUM_4,         //カウント数字4
    SEES_CHAR_GAME_COUNT_NUM_5,         //カウント数字5
    SEES_CHAR_GAME_COUNT_NUM_6,         //カウント数字6
    SEES_CHAR_GAME_COUNT_NUM_7,         //カウント数字7
    SEES_CHAR_GAME_COUNT_NUM_8,         //カウント数字8
    SEES_CHAR_GAME_COUNT_NUM_9,         //カウント数字9
};


//----------------------------------------りんご位置テーブル
static POS2D ApplePosTable[]={
    {   8,      5+1     },
    {   17,     5+1     },
    {   26,     5+1     },
    {   4,      -2+1    },
    {   13,     -2+1    },
    {   21,     -2+1    },
    {   30,     -2+1    },
    {   8,      -9+1    },
    {   17,     -9+1    },
    {   26,     -9+1    },
};


//----------------------------------------ゲームキャストデータ
static int CardCastDataTable[MAX_GAME_LEVEL_NUM][MAX_GAME_PATTERN_NUM][MAX_CARD_NUM]=
{
    {//----LEVEL-1
        {   1,  2,  3,  4,  5,  6,  0,  0,  0,  0   },
        {   2,  3,  4,  5,  6,  7,  0,  0,  0,  0   },
        {   3,  4,  5,  6,  7,  8,  0,  0,  0,  0   },
        {   4,  5,  6,  7,  8,  9,  0,  0,  0,  0   },
        {   5,  6,  7,  8,  9,  10, 0,  0,  0,  0   },
        {   1,  2,  6,  7,  8,  9,  0,  0,  0,  0   },
    },
    {//----LEVEL-2
        {   1,  2,  3,  4,  5,  6,  7,  8,  9,  10  },
        {   1,  2,  3,  4,  5,  6,  7,  8,  9,  10  },
        {   1,  2,  3,  4,  5,  6,  7,  8,  9,  10  },
        {   1,  2,  3,  4,  5,  6,  7,  8,  9,  10  },
        {   1,  2,  3,  4,  5,  6,  7,  8,  9,  10  },
        {   1,  2,  3,  4,  5,  6,  7,  8,  9,  10  },
    },
    {//----LEVEL-3
        {   11, 12, 13, 14, 15, 16, 17, 18, 19, 20  },
        {   11, 12, 13, 14, 15, 16, 17, 18, 19, 20  },
        {   11, 12, 13, 14, 15, 16, 17, 18, 19, 20  },
        {   11, 12, 13, 14, 15, 16, 17, 18, 19, 20  },
        {   11, 12, 13, 14, 15, 16, 17, 18, 19, 20  },
        {   11, 12, 13, 14, 15, 16, 17, 18, 19, 20  },
    },
    {//----LEVEL-4
        {   10, 20, 30, 40, 50, 60, 70, 80, 90, 100 },
        {   10, 20, 30, 40, 50, 60, 70, 80, 90, 100 },
        {   10, 20, 30, 40, 50, 60, 70, 80, 90, 100 },
        {   10, 20, 30, 40, 50, 60, 70, 80, 90, 100 },
        {   10, 20, 30, 40, 50, 60, 70, 80, 90, 100 },
        {   10, 20, 30, 40, 50, 60, 70, 80, 90, 100 },
    },
    {//----LEVEL-5
        {   32, 38, 41, 44, 56, 58, 65, 68, 72, 81  },
        {   43, 47, 52, 53, 64, 70, 73, 80, 85, 94  },
        {   37, 54, 56, 62, 63, 72, 81, 82, 92, 100 },
        {   33, 34, 50, 64, 65, 71, 74, 80, 89, 94  },
        {   36, 46, 48, 63, 73, 76, 80, 85, 97, 98  },
        {   35, 36, 48, 50, 59, 76, 82, 87, 89, 96  },
    },
};


//----------------------------------------ゲームデータ分配テーブル
static int CardDeelDataRandomTable[MAX_GAME_LEVEL_NUM][MAX_GAME_PATTERN_NUM][MAX_USER_CARD_NUM]=
{
    {//--------------------------------------------LEVEL-1
        {   0,  1,  2,  -1, -1  },
        {   1,  2,  0,  -1, -1  },
        {   2,  0,  1,  -1, -1  },
        {   0,  1,  2,  -1, -1  },
        {   1,  2,  0,  -1, -1  },
        {   2,  0,  1,  -1, -1  },
    },
    {//--------------------------------------------LEVEL-2
        {   0,  1,  2,  3,  4   },
        {   1,  2,  3,  4,  0   },
        {   2,  3,  4,  0,  1   },
        {   3,  4,  0,  1,  2   },
        {   4,  0,  1,  2,  3   },
        {   2,  1,  0,  4,  3   },
    },
    {//--------------------------------------------LEVEL-3
        {   0,  1,  2,  3,  4   },
        {   1,  2,  3,  4,  0   },
        {   2,  3,  4,  0,  1   },
        {   3,  4,  0,  1,  2   },
        {   4,  0,  1,  2,  3   },
        {   2,  1,  0,  4,  3   },
    },
    {//--------------------------------------------LEVEL-4
        {   0,  1,  2,  3,  4   },
        {   1,  2,  3,  4,  0   },
        {   2,  3,  4,  0,  1   },
        {   3,  4,  0,  1,  2   },
        {   4,  0,  1,  2,  3   },
        {   2,  1,  0,  4,  3   },
    },
    {//--------------------------------------------LEVEL-5
        {   0,  1,  2,  3,  4   },
        {   1,  2,  3,  4,  0   },
        {   2,  3,  4,  0,  1   },
        {   3,  4,  0,  1,  2   },
        {   4,  0,  1,  2,  3   },
        {   2,  1,  0,  4,  3   },
    },
};


//----------------------------------------ゲームデータ
static int CardDeelDataTable[MAX_GAME_LEVEL_NUM][2][MAX_GAME_PATTERN_NUM][MAX_USER_CARD_NUM]=
{
    {//--------------------------------------------LEVEL-1
        {//----SIDE-A
            {   2,  3,  6,  -1, -1  },
            {   3,  4,  7,  -1, -1  },
            {   4,  5,  8,  -1, -1  },
            {   5,  6,  9,  -1, -1  },
            {   6,  7,  10, -1, -1  },
            {   7,  8,  1,  -1, -1  },
        },
        {//----SIDE-B
            {   1,  4,  5,  -1, -1  },
            {   2,  5,  6,  -1, -1  },
            {   3,  6,  7,  -1, -1  },
            {   4,  7,  8,  -1, -1  },
            {   5,  8,  9,  -1, -1  },
            {   6,  9,  2,  -1, -1  },
        },  
    },
    {//--------------------------------------------LEVEL-2
        {//----SIDE-A
            {   2,  3,  6,  7,  9   },
            {   3,  4,  7,  8,  10  },
            {   4,  5,  8,  9,  1   },
            {   5,  6,  9,  10, 2   },
            {   6,  7,  10, 1,  3   },
            {   7,  8,  1,  2,  4   },
        },
        {//----SIDE-B
            {   1,  4,  5,  8,  10  },
            {   2,  5,  6,  9,  1   },
            {   3,  6,  7,  10, 2   },
            {   4,  7,  8,  1,  3   },
            {   5,  8,  9,  2,  4   },
            {   6,  9,  10, 3,  5   },
        },
    },
    {//--------------------------------------------LEVEL-3
        {//----SIDE-A
            {   12, 13, 16, 17, 20  },
            {   13, 14, 17, 18, 11  },
            {   14, 15, 18, 19, 12  },
            {   15, 16, 19, 20, 13  },
            {   16, 17, 20, 11, 14  },
            {   17, 18, 11, 12, 15  },
        },
        {//----SIDE-B
            {   11, 14, 15, 18, 19  },
            {   12, 15, 16, 19, 20  },
            {   13, 16, 17, 20, 11  },
            {   14, 17, 18, 11, 12  },
            {   15, 18, 19, 12, 13, },
            {   16, 19, 20, 13, 14, },
        },
    },
    {//--------------------------------------------LEVEL-4
        {//----SIDE-A
            {   20, 30, 60, 70, 90  },
            {   30, 40, 70, 80, 100 },
            {   40, 50, 80, 90, 10  },
            {   50, 60, 90, 100,20  },
            {   60, 70, 100,10, 30  },
            {   70, 80, 10, 20, 40  },
        },
        {//----SIDE-B
            {   10, 40, 50, 80, 100 },
            {   20, 50, 60, 90, 10  },
            {   30, 60, 70, 100,20  },
            {   40, 70, 80, 10, 30  },
            {   50, 80, 90, 20, 40  },
            {   60, 90, 100,30, 50  },
        },
    },
    {//--------------------------------------------LEVEL-5
        {//----SIDE-A
            {   32, 44, 58, 65, 72  },
            {   43, 53, 70, 73, 85  },
            {   54, 62, 82, 81, 100 },
            {   65, 71, 94, 89, 33  },
            {   76, 80, 36, 97, 46  },
            {   87, 89, 48, 35, 59  },
        },
        {//----SIDE-B
            {   38, 41, 56, 68, 81  },
            {   47, 52, 64, 80, 94  },
            {   56, 63, 72, 92, 37  },
            {   64, 74, 80, 34, 50  },
            {   73, 85, 98, 48, 63  },
            {   82, 96, 36, 50, 76  },
        },
    },
};


//----------------------------------------答え位置
static POS2D DrCardPosTable[2][MAX_USER_CARD_NUM]=
{
    {//----------------------------箱
        {   16,     170 + BG_OFFSET_Y   },//---Dr
        {   64,     170 + BG_OFFSET_Y   },
        {   112,    170 + BG_OFFSET_Y   },
        {   0,      0   + BG_OFFSET_Y   },
        {   0,      0   + BG_OFFSET_Y   },
    },
    {//----------------------------星
        {   14,     170 + BG_OFFSET_Y   },//---Dr
        {   44,     170 + BG_OFFSET_Y   },
        {   74,     170 + BG_OFFSET_Y   },
        {   104,    170 + BG_OFFSET_Y   },
        {   134,    170 + BG_OFFSET_Y   },
    },
};


static POS2D KyCardPosTable[2][MAX_USER_CARD_NUM]=
{
    {//----------------------------箱
        {   220,    140  + BG_OFFSET_Y  },//---Ky
        {   188,    170  + BG_OFFSET_Y  },
        {   252,    170  + BG_OFFSET_Y  },
        {   0,      0    + BG_OFFSET_Y  },
        {   0,      0    + BG_OFFSET_Y  },
    },
    {//----------------------------星
        {   208,    140  + BG_OFFSET_Y  },//---Ky
        {   238,    140  + BG_OFFSET_Y  },
        {   268,    140  + BG_OFFSET_Y  },
        {   208,    170  + BG_OFFSET_Y  },
        {   238,    170  + BG_OFFSET_Y  },
    },
};


//----------------------------------------As選択インデックスデータ
static int AsSelectCardIndexTable[MAX_GAME_LEVEL_NUM][MAX_GAME_PATTERN_NUM][MAX_USER_CARD_NUM]=
{
    {//--------------------------------------------LEVEL-1
        {   1,  2,  0,  -1, -1  },
        {   0,  1,  2,  -1, -1  },
        {   2,  0,  1,  -1, -1  },
        {   0,  1,  2,  -1, -1  },
        {   1,  2,  0,  -1, -1  },
        {   2,  0,  1,  -1, -1  },
    },
    {//--------------------------------------------LEVEL-2
        {   2,  3,  4,  0,  1   },
        {   2,  1,  0,  4,  3   },
        {   3,  4,  0,  1,  2   },
        {   4,  0,  1,  2,  3   },
        {   1,  2,  3,  4,  0   },
        {   0,  1,  2,  3,  4   },
    },
    {//--------------------------------------------LEVEL-3
        {   4,  0,  1,  2,  3   },
        {   0,  1,  2,  3,  4   },
        {   3,  4,  0,  1,  2   },
        {   1,  2,  3,  4,  0   },
        {   2,  1,  0,  4,  3   },
        {   2,  3,  4,  0,  1   },
    },
    {//--------------------------------------------LEVEL-4
        {   1,  2,  3,  4,  0   },
        {   0,  1,  2,  3,  4   },
        {   3,  4,  0,  1,  2   },
        {   4,  0,  1,  2,  3   },
        {   2,  3,  4,  0,  1   },
        {   2,  1,  0,  4,  3   },
    },
    {//--------------------------------------------LEVEL-5
        {   3,  4,  0,  1,  2   },
        {   2,  3,  4,  0,  1   },
        {   0,  1,  2,  3,  4   },
        {   4,  0,  1,  2,  3   },
        {   1,  2,  3,  4,  0   },
        {   2,  1,  0,  4,  3   },
    },
};



//----------------------------------------シーソー移動データ
//----比較中：Kyから見たデータ
static SEESAW_MOVE_DATA SeesawCompareMoveData[]={
    {   16,         1},     // ↑
    {   14,         -1},    // ↓
    {   10,         1},     // ↑
    {   8,          -1},    // ↓
    {   6,          1},     // ↑
    {   4,          -1},    // ↓
    {   2,          1},     // ↑
    {   -1,     0},     // STOP
};


//static SEESAW_MOVE_DATA SeesawCompareMoveData[]={
//  {   14,         1},     // ↑
//  {   10,         -1},    // ↓
//  {   6,          1},     // ↑
//  {   2,          -1},    // ↓
//  {   -1,         0},     // STOP
//};

//----Ky上がる：Kyからみる
static SEESAW_MOVE_DATA SeesawUpKyMoveData[]={
    {   SEESAW_DISTANCE_04,     -1},    // ↑
    {   -1,                     0},     // STOP
};

//----Dr上がる：Kyからみる
static SEESAW_MOVE_DATA SeesawUpDrMoveData[]={
    {   SEESAW_DISTANCE_04,     1},     // ↓
    {   -1,                     0},     // STOP
};

//----Dr戻る：Kyからみる
static SEESAW_MOVE_DATA SeesawReturnDrMoveData[]={
    {   SEESAW_DISTANCE_04,     -1},    // ↑
    {   -1,                     0},     // STOP
};

//----Ky戻る：Kyから見る
static SEESAW_MOVE_DATA SeesawReturnKyMoveData[]={
    {   SEESAW_DISTANCE_04,     1},     // ↓
    {   -1,                     0},     // STOP
};





//----------------------------------------アシスタント選択アニメテーブル
static int AsSelectBoxAnswerSpriteTypeTable[]=
{
    AS_SP_TYPE_SELECT_QUESTION_01,      //問題選択（１選択）
    AS_SP_TYPE_SELECT_QUESTION_03,      //問題選択（３選択）
    AS_SP_TYPE_SELECT_QUESTION_04,      //問題選択（４選択）
};

static int AsSelectCardAnswerSpriteTypeTable[]=
{
    AS_SP_TYPE_SELECT_QUESTION_01,      //問題選択（１選択）
    AS_SP_TYPE_SELECT_QUESTION_02,      //問題選択（２選択）
    AS_SP_TYPE_SELECT_QUESTION_03,      //問題選択（３選択）
    AS_SP_TYPE_SELECT_QUESTION_04,      //問題選択（４選択）
    AS_SP_TYPE_SELECT_QUESTION_05,      //問題選択（５選択）

};




//----------------------------------------失敗Kyスプライトテーブル
static SEES_SPRITE_DATA FalseEventKyAnmSpriteData[]=
{
    {   SEES_CHAR_EVENT_KY_07,  0,  0   },
    {   SEES_CHAR_EVENT_KY_08,  0,  0   },
};

//----------------------------------------失敗STARスプライトテーブル
static SEES_SPRITE_DATA FalseEventStarSpriteData[]=
{
    {   SEES_CHAR_EVENT_STAR_00,    0,  0   },
    {   SEES_CHAR_EVENT_STAR_01,    0,  0   },
};


//----------------------------------------クリア花火スプライトテーブル
static SEES_SPRITE_DATA ClearEventFireworksSpriteTable[]=
{
    {   SEES_CHAR_EVENT_HANABI_SMALL_00,    120,    34  },
    {   SEES_CHAR_EVENT_HANABI_SMALL_01,    162,    26  },
    {   SEES_CHAR_EVENT_HANABI_MIDDLE,      76,     41  },
    {   SEES_CHAR_EVENT_HANABI_BIG,         64,     18  },
    {   SEES_CHAR_EVENT_HANABI_DR_01,       96,     20  },
    {   SEES_CHAR_EVENT_HANABI_DR_00,       78,     10  },
    {   SEES_CHAR_EVENT_HANABI_SMALL_01,    162,    26  },
    {   SEES_CHAR_EVENT_HANABI_SMALL_00,    100,    34  },
};


//----------------------------------------おめでとうスプライトテーブル
static SEES_SPRITE_DATA ClearEventCongratulationSpriteTable[]=
{
    {   SEES_CHAR_EVENT_CLEAR_ACTION_BG_00, 0,  0},     //背景１
    {   SEES_CHAR_EVENT_CLEAR_ACTION_BG_01, 0,  0},     //背景2
    {   SEES_CHAR_EVENT_CLEAR_ACTION_BG_02, 0,  0},     //背景１
    {   SEES_CHAR_EVENT_CLEAR_ACTION_BG_03, 0,  0},     //背景2
};


//----------------------------------------スプライトテーブル
static SEES_SPRITE_DATA ClearEventAsSpriteTable[]=
{
    {   SEES_CHAR_EVENT_AS_MACNINE_01,          184,    99  },  //マシン付きボーリー正面            184,99
    {   SEES_CHAR_EVENT_AS_HAND_MACNINE_02,     244,    117 },  //マシン付きボーリー正面手・上      244,117
    {   SEES_CHAR_EVENT_AS_HAND_MACNINE_03,     244,    118 },  //マシン付きボーリー正面手・下      244,118
    {   SEES_CHAR_EVENT_LUMP_RIGHT_TOP,         0,      0   },  //マシン点滅右
};

//----------------------------------------スプライトテーブル
static SEES_SPRITE_DATA ClearEventDrSpriteTable[]=
{
    {   SEES_CHAR_EVENT_DR_00,  110,    133     },  //メガトン博士口開けバンザイ        110,133     
    {   SEES_CHAR_EVENT_DR_08,  110,    133     },  //メガトン博士微笑                110,133       
};


//----------------------------------------スプライトテーブル
static SEES_SPRITE_DATA ClearEventKySpriteTable[]=
{
    {   SEES_CHAR_EVENT_KY_05,  40, 129     },      //カヨリーヌ(バンザイ　       40,129        
    {   SEES_CHAR_EVENT_KY_06,  40, 129     },      //カヨリーヌ(笑う　           40,129        

};

//----------------------------------------スプライトテーブル
static SEES_SPRITE_DATA ClearEventFlySmokeSpriteTable[]=
{
    {   SEES_CHAR_EVENT_HANABI_TANE_00, 0,  0   },      //花火種A
    {   SEES_CHAR_EVENT_HANABI_TANE_01, 0,  0   },      //花火種B
};




//--------------------------------------------スクリプト
//----初プレイデモ開始時
#define INIT_PLAY_DEMO_SCRIPT_BASE              0
#define INIT_PLAY_DEMO_SCRIPT_NUM               2

//----レベルセレクト
#define SELECT_LEVEL_SCRIPT_BASE                2
#define SELECT_LEVEL_SCRIPT_NUM                 1

//----カード紹介
#define INTRODUCE_CARD_CAST_SCRIPT_BASE         3
#define INTRODUCE_CARD_CAST_SCRIPT_NUM          1

//----アシスタントカード選択
#define AS_SELECT_CARD_SCRIPT_BASE              4
#define AS_SELECT_CARD_SCRIPT_NUM               1

//----プレイヤーカード選択
#define PLAYER_SELECT_CARD_SCRIPT_BASE          5
#define PLAYER_SELECT_CARD_SCRIPT_NUM           1

//----比較
#define COMPARE_CARD_SCRIPT_BASE                6
#define COMPARE_CARD_SCRIPT_NUM                 1

//----カヨリーヌ勝利
#define KY_WIN_SCRIPT_BASE                      7
#define KY_WIN_SCRIPT_NUM                       1

//----Dr勝利
#define DR_WIN_SCRIPT_BASE                      8
#define DR_WIN_SCRIPT_NUM                       1

//----もう一回
#define AS_RETRY_SCRIPT_BASE                    9
#define AS_RETRY_SCRIPT_NUM                     1

//----クリア１
#define CLEAR_1_SCRIPT_BASE                     10
#define CLEAR_1_SCRIPT_NUM                      1

//----クリア２
#define CLEAR_2_SCRIPT_BASE                     11
#define CLEAR_2_SCRIPT_NUM                      1

//----クリア３
#define CLEAR_3_SCRIPT_BASE                     12
#define CLEAR_3_SCRIPT_NUM                      1

//----オールクリア１
#define ALL_CLEAR_1_SCRIPT_BASE                 13
#define ALL_CLEAR_1_SCRIPT_NUM                  1

//----オールクリア２
#define ALL_CLEAR_2_SCRIPT_BASE                 14
#define ALL_CLEAR_2_SCRIPT_NUM                  1

//----オールクリア３
#define ALL_CLEAR_3_SCRIPT_BASE                 15
#define ALL_CLEAR_3_SCRIPT_NUM                  1

//----オールクリア４
#define ALL_CLEAR_4_SCRIPT_BASE                 16
#define ALL_CLEAR_4_SCRIPT_NUM                  1

//----失敗
#define FALSE_SCRIPT_BASE                       17
#define FALSE_SCRIPT_NUM                        1

//----クリア：こんどはまけないぞ
#define CLEAR_MAKENAI_SCRIPT_BASE               18
#define CLEAR_MAKENAI_SCRIPT_NUM                1


//----スクリプト本体
static SCRIP_DATA SeesScript[]=
{
    //----------------------------------------初プレイデモ
    {//「のっけてシーソー」に　ようこそ！
        0,
        NamePlateToma,
        XA_FILE_SEES00,
        2,
        "初消音時０６「のっけてシーソー」に　ようこそ！待１２０終"
    },
    {//ここは、ちと、あたまを　つかうゾ～。
        4,
        NamePlateToma,
        XA_FILE_SEES00,
        3,
        "初消音時０６ここは、ちょっと、あたまを　つかうぞ。待２４０終"
    },
    //----------------------------------------レベルセレクト
    {//ひかっている　すうじを　えらんでくれ。
        0,
        NamePlateDan,
        XA_FILE_BAND00,
        4,
        "初音時０６ひかっている　すうじを　えらんでくれ。待３００終"
    },
    //----------------------------------------カード紹介
    {//これで、しょうぶだよぉ。
        0,
        NamePlateBori,
        XA_FILE_SEES01,
        0,
        "初消音時０６これで、しょうぶだよ。待２４０終"
    },
    //----------------------------------------アシスタントカード選択
    {//これにしよう
        0,
        NamePlateBori,
        XA_FILE_SEES01,
        3,
        "初消音時０６これに　しよう。待１２０終"
    },
    //----------------------------------------プレイヤーカード選択
    {//さぁ、どれで　しょうぶする？
        0,
        NamePlateKayo,
        XA_FILE_SEES01,
        5,
        "初消音時０６さぁ、どれで　しょうぶする？待１２０終"
    },
    //----------------------------------------比較
    {//さぁ、おおきかずは　どちら？
        0,
        NamePlateNare,
        XA_FILE_SEES02,
        1,
        "初消音時０６さぁ、おおきい　かずは　どちら？待１８０終"
    },
    //----------------------------------------カヨリーヌ勝利
    {//やったわね～！だいしょうり～！
        0,
        NamePlateKayo,
        XA_FILE_SEES03,
        0,
        "初消音時０６やったわね！　だいしょうり！待１８０終"
    },
    //----------------------------------------Dr勝利
    {//やった。わしらの、かちじゃ！
        0,
        NamePlateToma,
        XA_FILE_SEES03,
        4,
        "初消音時０６やった。わしらの、かちじゃ！待１８０終"
    },
    //----------------------------------------もう一回
    {//もう　いっかい。
        0,
        NamePlateBori,
        XA_FILE_SEES03,
        6,
        "初消音時０６もう　いっかい。待１８０終"
    },
    //----------------------------------------クリア１
    {//ブラボ～！　きみは　すんばらしい！
        0,
        NamePlateToma,
        XA_FILE_SEES04,
        0,
        "初消音時０６ブラボ～！　きみは　すんばらしい！待１８０終"
    },
    //----------------------------------------クリア２
    {//わしらからの　プレゼント！きれいな　はなびぢゃ
        0,
        NamePlateToma,
        XA_FILE_SEES04,
        1,
        "初消音時０６わしらからの　プレゼント！　きれいな　改はなびじゃ。待２２０終"
    },
    //----------------------------------------クリア３
    {//ボーリー、スイッチオン！
        0,
        NamePlateToma,
        XA_FILE_SEES04,
        2,
        "初消音時０６ボーリー、スイッチオン！待１８０終"
    },
    //----------------------------------------オールクリア１
    {//ブラボ～！　まったく、すんばらしい！
        0,
        NamePlateToma,
        XA_FILE_SEES04,
        4,
        "初消音時０６ブラボ～！　まったく、すんばらしい！待１８０終"
    },
    //----------------------------------------オールクリア２
    {//わしらの　かんぱいぢゃ。
        0,
        NamePlateToma,
        XA_FILE_SEES04,
        5,
        "初消音時０６わしらの　かんぱいぢゃ。待１８０終"
    },
    //----------------------------------------オールクリア３
    {//では、とっておきのプレゼント、すんごくきれいなはなびぢゃ。
        0,
        NamePlateToma,
        XA_FILE_SEES04,
        6,
        "初消音時０６では、とっておきのプレゼント、改すんごくきれいなはなびじゃ。待２２０終"
    },
    //----------------------------------------オールクリア４
    {//ボーリー、スイッチオン！
        0,
        NamePlateToma,
        XA_FILE_SEES04,
        7,
        "初消音時０６ボーリー、スイッチオン！待１８０終"
    },
    //----------------------------------------失敗
    {//だいじょうぶ。こんどは、かてるわ。
        0,
        NamePlateKayo,
        XA_FILE_SEES04,
        9,
        "初消音時０６だいじょうぶ。こんどは、かてるわ。待２４０終"
    },
    //----------------------------------------失敗
    {//こんどは、まけないぞ。
        0,
        NamePlateToma,
        XA_FILE_SEES04,
        8,
        "初消音時０６こんどは、まけないぞ。待２４０終"
    },
};


//-----------------------------------------------------------------------------
// codes 
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  関数名  :Sees
//
//  work   :のっけてシーソー
//  in     :GAMEMGR*    ゲームマネージャへのポインタ
//  out    :TRUE        成功
//  note    :なし
//-----------------------------------------------------------------------------
int Sees(GAMEMGR* ip_GameMgr)
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
            SfileRead2(SEES_SOUNDFILE);
            HelpInit();
            GameMgr.WaitFlag    = ON;

            //---- ゲーム管理情報初期化
            SGameMgr.Timer          = 0;                            //ゲーム時間
            SGameMgr.Level          = ip_GameMgr->Level[GAME_SEES]; //レベル
            SGameMgr.PlayLevel      = 2;                            //ゲームレベル
            SGameMgr.ContinueFlag   = 0;                            //継続プレイフラグ
            SGameMgr.EventEndFlag   = 0;                            //イベント終了フラグ
            SGameMgr.ClearFlag      = 0;                            //クリアフラグ
            SGameMgr.FalseFlag      = 0;                            //負けイベント
            SGameMgr.AllClearFlag   = 0;                            //オールクリアフラグ
            SGameMgr.ExitFlag       = 0;                            //終了フラグ


#ifdef __DEBUG_SEES__
            if( NewPad & PADL1 )
            {//----デバッグタスク
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
            if(NewPad & PADL2){
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
            if((NewPad & PADR1) && (NewPad & PADR2)){
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
            if(NewPad & PADR1){
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
            if(NewPad & PADR2){
                Task.func       = FalseEventTask;
                Task.priority   = TASK_NO_DEBUG;
                Task.attribute  = ATTR_USER;
                Task.status     = TASK_NEW_ENTRY;
                Task.id         = TASK_NO_DEBUG;
                Task.wait_time  = 0;
                Task.buf        = NULL;
                Task.name       = "FalseEventTask";
                Task.mode       = TASK_MODE_INIT;
                CreateTask(&Task);
            }else
            {//----
                if(SGameMgr.Level==0)
                {//レベル１をクリアしていない場合はゲームコントローラタスクを呼ぶ
                    //----ゲームコントロールタスク
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
            if(SGameMgr.Level==0)
            {//レベル１をクリアしていない場合はゲームコントローラタスクを呼ぶ
                //----ゲームコントロールタスク
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
            FntPrint("");   //呼んでおかないとダメ

            ExecuteTask();
            TransSprite();
            SpraitControl();

            //----終了チェック
            if(SGameMgr.ExitFlag) ip_GameMgr->SubMode = EXIT;
            //-----------------------------------------------------------▲
            break;
        case EXIT:
            //----スプライト開放
            ReleaseSprite();

            //----ゲームレベル
            ip_GameMgr->Level[GAME_SEES] = SGameMgr.Level;

            //----岩澤担当部分：終了
            SpraitCharClr();
            SpraitControl();
            GameMgr.WaitFlag = ON;
            //[♪] サウンド停止
            ssStopAll();
            ssCloseVab();

            //----メインメニューへ
            ip_GameMgr->MainMode    = MAIN_MODE_TOP_MENU;
            ip_GameMgr->SubMode     = INIT;
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
static int GameControllTask(TASK* ip_task)
{
    TASK Task;
    int i;
    static int dcount=0;
    static int dbx=20;
    static int dby=20;


    switch( ip_task->mode )
    {
        //----------------------------------------------------------------初期化
        case TASK_MODE_INIT:
            //next main
            ip_task->mode = TASK_MODE_MAIN;
            
            //---- ゲーム管理情報初期化
        //  SGameMgr.Timer                  = 0;        //ゲーム時間
        //  SGameMgr.Level                  = ;         //レベル
        //  SGameMgr.PlayLevel              = 0;        //ゲームレベル
        //  SGameMgr.ContinueFlag           = 0;        //継続プレイフラグ
            SGameMgr.EventEndFlag           = 0;        //イベント終了フラグ
            SGameMgr.ClearFlag              = 0;        //クリアフラグ
            SGameMgr.FalseFlag              = 0;        //負けイベント
            SGameMgr.AllClearFlag           = 0;        //オールクリアフラグ
            SGameMgr.ExitFlag               = 0;        //終了フラグ
            
            
            dcount = 10;

            //----texture read sram -> vram
            if((file_read(SeesGameTextureFile[0].fn,LoadAddress)) == -1)
            {//read error
                return FALSE;
            }

            //----texture init
            TexInit( SEES_GAME_TIM_NUM, &SeesGameTextureImage[SEES_GAME_TIM_POS] );
            TimImgData = SeesGameTextureImage;

            //----スプライト登録
            EntrySprite( SeesGameSpriteData );

            //ガイド表示
            GaidoInit();

            if(SGameMgr.ContinueFlag==0)
            {//----初プレイ：
                //----継続プレイフラグオン
                SGameMgr.ContinueFlag = 1;

                Task.func       = DrAppearTasK;
                Task.priority   = TASK_NO_DEBUG;
                Task.attribute  = ATTR_USER;
                Task.status     = TASK_NEW_ENTRY;
                Task.id         = TASK_NO_DEBUG;
                Task.wait_time  = 0;
                Task.buf        = NULL;
                Task.name       = "DrAppearTasK";
                Task.mode       = TASK_MODE_INIT;
                CreateTask(&Task);

            }else
            {//----継続プレイ
                //----背景タスク
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

                //----カード紹介トタスク
                Task.func       = CardCastTask;
                Task.priority   = TASK_NO_GAME_CARD_CAST;
                Task.attribute  = ATTR_USER;
                Task.status     = TASK_NEW_ENTRY;
                Task.id         = TASK_NO_GAME_CARD_CAST;
                Task.wait_time  = 0;
                Task.buf        = NULL;
                Task.name       = "CardCastTask";
                Task.mode       = TASK_MODE_INIT;
                CreateTask(&Task);

                //----シーソータスク
                Task.func       = SeesawTask;
                Task.priority   = TASK_NO_GAME_SEESAW;
                Task.attribute  = ATTR_USER;
                Task.status     = TASK_NEW_ENTRY;
                Task.id         = TASK_NO_GAME_SEESAW;
                Task.wait_time  = 0;
                Task.buf        = NULL;
                Task.name       = "SeesawTask";
                Task.mode       = TASK_MODE_INIT;
                CreateTask(&Task);

                //----カロリーヌタスク
                Task.func       = KyTask;
                Task.priority   = TASK_NO_GAME_KY;
                Task.attribute  = ATTR_USER;
                Task.status     = TASK_NEW_ENTRY;
                Task.id         = TASK_NO_GAME_KY;
                Task.wait_time  = 0;
                Task.buf        = NULL;
                Task.name       = "KyTask";
                Task.mode       = TASK_MODE_INIT;
                CreateTask(&Task);

                //----博士タスク
                Task.func       = DrTask;
                Task.priority   = TASK_NO_GAME_DR;
                Task.attribute  = ATTR_USER;
                Task.status     = TASK_NEW_ENTRY;
                Task.id         = TASK_NO_GAME_DR;
                Task.wait_time  = 0;
                Task.buf        = NULL;
                Task.name       = "DrTask";
                Task.mode       = TASK_MODE_INIT;
                CreateTask(&Task);

                //----アシスタントタスク
                Task.func       = AsTask;
                Task.priority   = TASK_NO_GAME_AS;
                Task.attribute  = ATTR_USER;
                Task.status     = TASK_NEW_ENTRY;
                Task.id         = TASK_NO_GAME_AS;
                Task.wait_time  = 0;
                Task.buf        = NULL;
                Task.name       = "AsTask";
                Task.mode       = TASK_MODE_INIT;
                CreateTask(&Task);

                //----博士カードタスク
                Task.func       = DrCardTask;
                Task.priority   = TASK_NO_GAME_DR_CARD;
                Task.attribute  = ATTR_USER;
                Task.status     = TASK_NEW_ENTRY;
                Task.id         = TASK_NO_GAME_DR_CARD;
                Task.wait_time  = 0;
                Task.buf        = NULL;
                Task.name       = "DrCardTask";
                Task.mode       = TASK_MODE_INIT;
                CreateTask(&Task);

                //----カロリーヌカードタスク
                Task.func       = KyCardTask;
                Task.priority   = TASK_NO_GAME_KY_CARD;
                Task.attribute  = ATTR_USER;
                Task.status     = TASK_NEW_ENTRY;
                Task.id         = TASK_NO_GAME_KY_CARD;
                Task.wait_time  = 0;
                Task.buf        = NULL;
                Task.name       = "KyCardTask";
                Task.mode       = TASK_MODE_INIT;
                CreateTask(&Task);
            }

            break;
        //----------------------------------------------------------------メイン
        case TASK_MODE_MAIN:
            //------------▼

            //----ゲーム終了チェック
            if( SGameMgr.ClearFlag || SGameMgr.FalseFlag) ip_task->mode = TASK_MODE_EXIT;

#ifdef __DEBUG_SEES__
//          DrawNum(100, WIDTH_SMALL_FONT, SmallNumSpriteTable, 140, 100,   PRIORITY_NUM );
//          DrawNum( 99, WIDTH_SMALL_FONT, SmallNumSpriteTable, 140, 120,   PRIORITY_NUM );
//          DrawNum(  2, WIDTH_SMALL_FONT, SmallNumSpriteTable, 140, 140,   PRIORITY_NUM );
//          
//          DrawNum(  1, WIDTH_BIG_FONT,   BigNumSpriteTable,   240, 60,    PRIORITY_NUM );
//          DrawNum(  2, WIDTH_BIG_FONT,   BigNumSpriteTable,   240, 90,    PRIORITY_NUM );
//          DrawNum(  3, WIDTH_BIG_FONT,   BigNumSpriteTable,   240, 120,   PRIORITY_NUM );


//          if(JstPad & PADLup){
//              if(--dcount<0){
//                  dcount=100;
//              }
//          }else
//          if(JstPad & PADLdown){
//              if(++dcount>100){
//                  dcount=0;
//              }
//          }else{
//              
//          }
//

//          if(JstPad & PADLup){
//              --dby;
//          }else
//          if(JstPad & PADLdown){
//              ++dby;
//          }else{
//          }
//          if(JstPad & PADLleft){
//              --dbx;
//          }else
//          if(JstPad & PADLright){
//              ++dbx;
//          }else{
//          }
//          DrawCard(CARD_TYPE_BOX,     dcount, 0,  dbx,dby,PRIORITY_CARD);
//          FntPrint("(x-y)=(%d-%d)\n",dbx,dby);
//          DrawCard(CARD_TYPE_STAR,    dcount, 0,  dbx,dby,PRIORITY_CARD);

//          //DR
//          DrawNum(    10,
//                      WIDTH_BIG_FONT,
//                      BigNumSpriteTable,
//                      DR_SIDE_APPLE_COUNT_POS_X+11,
//                      DR_SIDE_APPLE_COUNT_POS_Y,
//                      PRIORITY_NUM );
//
//
//          //DR
//          DrawNum(    9,
//                      WIDTH_BIG_FONT,
//                      BigNumSpriteTable,
//                      DR_SIDE_APPLE_COUNT_POS_X,
//                      DR_SIDE_APPLE_COUNT_POS_Y,
//                      PRIORITY_NUM );
//
//
//
//          //KY
//          DrawNum(    10,
//                      WIDTH_BIG_FONT,
//                      BigNumSpriteTable,
//                      KR_SIDE_APPLE_COUNT_POS_X+11,
//                      KR_SIDE_APPLE_COUNT_POS_Y,
//                      PRIORITY_NUM );
//
//          //KY
//          DrawNum(    9,
//                      WIDTH_BIG_FONT,
//                      BigNumSpriteTable,
//                      KR_SIDE_APPLE_COUNT_POS_X,
//                      KR_SIDE_APPLE_COUNT_POS_Y,
//                      PRIORITY_NUM );


#endif
            //------------▲
            break;
        //----------------------------------------------------------------終了
        case TASK_MODE_EXIT:
            //----ゲームタスク終了
            RemoveTask(TASK_NO_GAME_PAUSE);
            RemoveTask(TASK_NO_GAME_APPEAR_DR);
            RemoveTask(TASK_NO_GAME_SELECT_LEVEL);
            RemoveTask(TASK_NO_GAME_CARD_CAST);
            RemoveTask(TASK_NO_GAME_APPLE_COUNT);
            RemoveTask(TASK_NO_GAME_SEESAW);
            RemoveTask(TASK_NO_GAME_PLAYER);
            RemoveTask(TASK_NO_GAME_DR);
            RemoveTask(TASK_NO_GAME_KY);
            RemoveTask(TASK_NO_GAME_AS);
            RemoveTask(TASK_NO_GAME_DR_CARD);
            RemoveTask(TASK_NO_GAME_KY_CARD);
            RemoveTask(TASK_NO_GAME_LIGHT_FLUSH);
            RemoveTask(TASK_NO_GAME_BG);

            //[♪]BGM
            ssStopBgm(SEES_BGM_00);

            //----レベル更新
            if(SGameMgr.PlayLevel > SGameMgr.Level)
            {//前回のレベルより高い場合は書き換える
                SGameMgr.Level = SGameMgr.PlayLevel;
            }

            //ガイド破棄
            SpraitCharClr();

            //----イベントタスク起動
            if(SGameMgr.AllClearFlag)
            {//----オールクリアイベント
                RemoveTask(TASK_NO_GAME_BG);
                //----オールクリアタスク
                Task.func       = AllClearEventTask;
                Task.priority   = TASK_NO_EVENT_ALL_CLEAR;
                Task.attribute  = ATTR_USER;
                Task.status     = TASK_NEW_ENTRY;
                Task.id         = TASK_NO_EVENT_ALL_CLEAR;
                Task.wait_time  = 0;
                Task.buf        = NULL;
                Task.name       = "AllClearEventTask";
                Task.mode       = TASK_MODE_INIT;
                CreateTask(&Task);
            }else
            if(SGameMgr.ClearFlag)
            {//----クリアイベント
                RemoveTask(TASK_NO_GAME_BG);
                //----クリアタスク
                Task.func       = ClearEventTask;
                Task.priority   = TASK_NO_EVENT_CLEAR;
                Task.attribute  = ATTR_USER;
                Task.status     = TASK_NEW_ENTRY;
                Task.id         = TASK_NO_EVENT_CLEAR;
                Task.wait_time  = 0;
                Task.buf        = NULL;
                Task.name       = "ClearEventTask";
                Task.mode       = TASK_MODE_INIT;
                CreateTask(&Task);
            }else
            {//----失敗イベント
                //----クリアタスク
                Task.func       = FalseEventTask;
                Task.priority   = TASK_NO_EVENT_FALSE;
                Task.attribute  = ATTR_USER;
                Task.status     = TASK_NEW_ENTRY;
                Task.id         = TASK_NO_EVENT_FALSE;
                Task.wait_time  = 0;
                Task.buf        = NULL;
                Task.name       = "FalseEventTask";
                Task.mode       = TASK_MODE_INIT;
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
//  関数名  :SelectLevelTask
//
//  work    :セレクトレベル
//  in      :TASK*      タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int SelectLevelTask(TASK* ip_task)
{
    static int LevelNumTable[]={
        SEES_CHAR_GAME_SELECT_LEVEL_NUM_1,          //レベル選択用数字1
        SEES_CHAR_GAME_SELECT_LEVEL_NUM_2,          //レベル選択用数字2
        SEES_CHAR_GAME_SELECT_LEVEL_NUM_3,          //レベル選択用数字3
        SEES_CHAR_GAME_SELECT_LEVEL_NUM_4,          //レベル選択用数字4
        SEES_CHAR_GAME_SELECT_LEVEL_NUM_5,          //レベル選択用数字5
    };

    static SEES_SPRITE_DATA GakudaninSpriteTable[]=
    {
        {   SEES_CHAR_GAME_DANTYOU_00,                  2,      -4  },  //団長00アニメ
        {   SEES_CHAR_GAME_DANTYOU_01,                  0,      -6  },  //団長01アニメ
        {   SEES_CHAR_GAME_DANIN_FUUSEN_BLUE_00,        0,      0   },  //青風船時01楽団員A00アニメ
        {   SEES_CHAR_GAME_DANIN_FUUSEN_BLUE_01,        0,      0   },  //同上
        {   SEES_CHAR_GAME_DANIN_HATA_YOKO_00,          0,      0   },  //楽団員B00アニメ
        {   SEES_CHAR_GAME_DANIN_HATA_YOKO_01,          0,      0   },  //楽団員B01アニメ
        {   SEES_CHAR_GAME_DANIN_HATA_TATE_00,          0,      0   },  //楽団員C00アニメ
        {   SEES_CHAR_GAME_DANIN_HATA_TATE_01,          0,      0   },  //楽団員C01アニメ
        {   SEES_CHAR_GAME_DANIN_FUUSEN_ORANGE_00,      0,      0   },  //橙風船時02　楽団員A00アニメ
        {   SEES_CHAR_GAME_DANIN_FUUSEN_ORANGE_01,      0,      0   },  //同上
    };

    SPRITE_DATA SpData;
    TASK Task;
    int i,j;


    switch(ip_task->mode)
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
//          SpraitCharSet(&GaidoLevelSpControl00[0], NULL);     // iwasawa Correction (2003/4/27)
//          SsinScriptFlag = SGameMgr.Script.Flag = 0;          // iwasawa Correction (2003/4/27)
            //next MAIN
            ip_task->mode       = TASK_MODE_MAIN;

            //----texture read sram -> vram
            if((file_read(SeesGameTextureFile[0].fn,LoadAddress)) == -1)
            {//read error
                return FALSE;
            }

            //----texture init
            TexInit( SEES_GAME_TIM_NUM, &SeesGameTextureImage[SEES_GAME_TIM_POS] );
            TimImgData = SeesGameTextureImage;

            //----ゲーム用スプライト登録
            EntrySprite( SeesGameSpriteData );

            //----プレイレベルクリア
            SGameMgr.PlayLevel      = 0;

            //----継続プレイフラグOFF
            SGameMgr.ContinueFlag   = 0;

            //----レベルセレクトワーク初期化
            SGameMgr.SelectLevel.Mode               = SEES_GAME_SELECT_LEVEL_MODE_00;
            SGameMgr.SelectLevel.Timer              = 0;
            SGameMgr.SelectLevel.BlockNo            = 0;
            SGameMgr.SelectLevel.BlockWt            = 0;
            SGameMgr.SelectLevel.KeteiWt            = 0;
            SGameMgr.SelectLevel.KeteiFlushIndex    = 0;
            SGameMgr.SelectLevel.KeteiFlushWt       = 0;
            SGameMgr.SelectLevel.AnmIndex           = 0;
            SGameMgr.SelectLevel.AnmNo              = GakudaninSpriteTable[0].No;
            SGameMgr.SelectLevel.AnmWt              = 0;
            SGameMgr.SelectLevel.AnmBase            = 0;
            SGameMgr.SelectLevel.PosX               = SEES_GAME_SELECT_LEVEL_GAKUDANIN_INIT_X;
            SGameMgr.SelectLevel.PosY               = SEES_GAME_SELECT_LEVEL_GAKUDANIN_INIT_Y;
            SGameMgr.SelectLevel.WaitFlag           = 0;

            // フェードInします
            GameMgr.FadeFlag = FadeIn;

            //[♪]パンパカパーん
            dsPlayXa(XA_FILE_ZIRI10,5);

            break;
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:
            SsinScriptFlag = SGameMgr.Script.Flag;          // iwasawa Correction (2003/4/27)
        //  FntPrint("SELECT LEVEL=%d\n", SGameMgr.PlayLevel);
        
            //----選択可能レベルをプレートのアニメで表現する
            switch(SGameMgr.SelectLevel.Mode)
            {
                //----------------------------------選択可能なレベルまで明るく(楽団員現る)
                case SEES_GAME_SELECT_LEVEL_MODE_00:
                    ++SGameMgr.SelectLevel.Timer;
                    if(SGameMgr.SelectLevel.Timer > SEES_GAME_SELECT_LEVEL_MODE_00_TIME){
                    }
                    
                    for(i=0;i<SGameMgr.Level+1;i++){//横
                        for(j=0;j<5;j++){//縦
                            if(j>i) continue;
                            //レベルセレクトプレート
                            SpData.No       = SEES_CHAR_GAME_SELECT_LEVEL_PLATE_LIGHT;
                            SpData.PosX     = 101 + 25*i - 2;
                            SpData.PosY     = 40 + 95 - 10*j + 3;
                            SpData.PosZ     = PRIORITY_BG-2;
                            SpData.ScaleX   = SCALE10;
                            SpData.ScaleY   = SCALE10;
                            SpData.Rotate   = ROTATE000;
                            SpData.Reverse  = NOREVERS;
                            DrawSprite( &SpData );
                        }
                    }
                    
                    //----楽団員移動
                    SGameMgr.SelectLevel.PosX -= SEES_GAME_SELECT_LEVEL_GAKUDANIN_SPEED_X; 
                    if(SGameMgr.SelectLevel.PosX < SEES_GAME_SELECT_LEVEL_GAKUDANIN_STOP_X)
                    {
                        SGameMgr.SelectLevel.PosX = SEES_GAME_SELECT_LEVEL_GAKUDANIN_STOP_X;
                        SGameMgr.SelectLevel.Mode = SEES_GAME_SELECT_LEVEL_MODE_01;
                        
                        //スクリプト
                        SGameMgr.Script.Flag=1;
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
                        Task.user[1]        = SELECT_LEVEL_SCRIPT_BASE;
                        Task.user[2]        = SELECT_LEVEL_SCRIPT_NUM;
                        CreateTask(&Task);
                        SpraitCharSet(&GaidoLevelSpControl00[0], NULL);     // iwasawa Correction (2003/4/27)
                    }
                    
                    break;
                //----------------------------------下から上へ明るく
                case SEES_GAME_SELECT_LEVEL_MODE_01:
                    //----操作
                    if(!SGameMgr.Script.Flag){
                        if(JstPad &  PADLright)
                        {
                            //[♪] レバー音
                            ssPlaySe(BUTONSE_LEVER);
                            if(++SGameMgr.PlayLevel>SGameMgr.Level){
                                SGameMgr.PlayLevel=0;
                            }
                        }else
                        if(JstPad &  PADLleft){
                            //[♪] レバー音
                            ssPlaySe(BUTONSE_LEVER);
                            if(--SGameMgr.PlayLevel<0){
                                SGameMgr.PlayLevel=SGameMgr.Level;
                            }
                        }else{
                            
                        }
                        
                        //----決定
                        if(JstPad &  PADRright)
                        {//next EXIT
                            SGameMgr.SelectLevel.Mode = SEES_GAME_SELECT_LEVEL_MODE_02;
                            
                            //[♪]決定
                            ssPlaySe(BUTONSE_MARU);
                        }
                    }

                    //----描画
                    if( ++SGameMgr.SelectLevel.BlockWt > SEES_GAME_SELECT_LEVEL_FLUSH_ANM_TIME)
                    {//
                        SGameMgr.SelectLevel.BlockWt=0;
                        if(++SGameMgr.SelectLevel.BlockNo > SEES_GAME_MAX_LEVEL_NUM)
                        {
                            SGameMgr.SelectLevel.BlockNo=0;
                        }
                    }
                    
                    for(i=0;i<SGameMgr.Level+1;i++){//横
                        for(j=0;j<5;j++){//縦
                            if(j>i) continue;
                            if(SGameMgr.SelectLevel.BlockNo <= j) continue;
                            
                            //レベルセレクトプレート
                            SpData.No       = SEES_CHAR_GAME_SELECT_LEVEL_PLATE_LIGHT;
                            SpData.PosX     = 101 + 25*i - 2;
                            SpData.PosY     = 40 + 95 - 10*j + 3;
                            SpData.PosZ     = PRIORITY_BG-3;
                            SpData.ScaleX   = SCALE10;
                            SpData.ScaleY   = SCALE10;
                            SpData.Rotate   = ROTATE000;
                            SpData.Reverse  = NOREVERS;
                            DrawSprite( &SpData );
                        }
                    }
                    break;
                //----------------------------------選んだレベルのみフラッシュ
                case SEES_GAME_SELECT_LEVEL_MODE_02:
                    
                    if(!SGameMgr.SelectLevel.WaitFlag){
                        if(++SGameMgr.SelectLevel.KeteiWt > SEES_GAME_SELECT_LEVEL_KETEI_WAIT_TIME){
                            //フラッシュ後抜ける
                            //ip_task->mode     = TASK_MODE_EXIT;
                            SGameMgr.SelectLevel.WaitFlag=1;
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
                    
                    if( ++SGameMgr.SelectLevel.KeteiFlushWt > SEES_GAME_SELECT_LEVEL_KETEI_FLUSH_TIME ){
                        SGameMgr.SelectLevel.KeteiFlushWt = 0;
                        SGameMgr.SelectLevel.KeteiFlushIndex^=1;
                    }
                    
                    if(SGameMgr.SelectLevel.KeteiFlushIndex){
                        for(i=0;i<5;i++){//縦
                            if(SGameMgr.PlayLevel>=i){
                                //レベルセレクトプレート
                                SpData.No       = SEES_CHAR_GAME_SELECT_LEVEL_PLATE_LIGHT;
                                SpData.PosX     = 101 + 25*SGameMgr.PlayLevel - 2;
                                SpData.PosY     = 40 + 95 - 10*i + 3;
                                SpData.PosZ     = PRIORITY_BG-2;
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

            //----楽団員
            if(++SGameMgr.SelectLevel.AnmWt > SEES_GAME_SELECT_LEVEL_GAKUDANIN_ANM_WAIT_TIME){
                SGameMgr.SelectLevel.AnmWt      = 0;
                SGameMgr.SelectLevel.AnmIndex   ^=1;
            }
            
            for(i=0;i<5;i++)
            {
                SGameMgr.SelectLevel.AnmBase    = i*2;
                SGameMgr.SelectLevel.AnmNo      = GakudaninSpriteTable[SGameMgr.SelectLevel.AnmBase + SGameMgr.SelectLevel.AnmIndex].No;
                
                SpData.No                       = SGameMgr.SelectLevel.AnmNo;
                SpData.PosX                     = SGameMgr.SelectLevel.PosX + i*40 + GakudaninSpriteTable[SGameMgr.SelectLevel.AnmBase + SGameMgr.SelectLevel.AnmIndex].Ofx;
                SpData.PosY                     = SGameMgr.SelectLevel.PosY + GakudaninSpriteTable[SGameMgr.SelectLevel.AnmBase + SGameMgr.SelectLevel.AnmIndex].Ofy;
                SpData.PosZ                     = PRIORITY_BG - 4;
                SpData.ScaleX                   = SCALE10;
                SpData.ScaleY                   = SCALE10;
                SpData.Rotate                   = ROTATE000;
                SpData.Reverse                  = NOREVERS;
                DrawSprite( &SpData );
            }

            //----レベルセレクトプレートワク
            SpData.No       = SEES_CHAR_GAME_SELECT_LEVEL_CURSOR;
            SpData.PosX     = 100 + 25 * SGameMgr.PlayLevel - 2;
            SpData.PosY     = 40 + 80 - 10 * SGameMgr.PlayLevel + 3;
            SpData.PosZ     = PRIORITY_BG - 3;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );

            //----レベル数字
            for(i=0;i<5;i++){
                SpData.No       = LevelNumTable[i];
                SpData.PosX     = 106 + 25*i -2 ;
                SpData.PosY     = 27 + 95 - 10*i + 3;
                SpData.PosZ     = PRIORITY_BG-4;
                SpData.ScaleX   = SCALE10;
                SpData.ScaleY   = SCALE10;
                SpData.Rotate   = ROTATE000;
                SpData.Reverse  = NOREVERS;
                DrawSprite( &SpData );
            }

            //----暗いレベルプレート
            for(i=0;i<5;i++){//横
                for(j=0;j<5;j++){//縦
                    if(j>i) continue;
                    SpData.No       = SEES_CHAR_GAME_SELECT_LEVEL_PLATE_DARK;
                    SpData.PosX     = 101 + 25*i - 2;
                    SpData.PosY     = 40 + 95 - 10*j + 3;
                    SpData.PosZ     = PRIORITY_BG-1;
                    SpData.ScaleX   = SCALE10;
                    SpData.ScaleY   = SCALE10;
                    SpData.Rotate   = ROTATE000;
                    SpData.Reverse  = NOREVERS;
                    DrawSprite( &SpData );
                }
            }

            //----レベルセレクト背景左
            SpData.No       = SEES_CHAR_GAME_SELECT_LEVEL_BG_00;
            SpData.PosX     = 0;
            SpData.PosY     = 0;
            SpData.PosZ     = PRIORITY_BG;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );
            
            //----レベルセレクト背景右
            SpData.No       = SEES_CHAR_GAME_SELECT_LEVEL_BG_01;
            SpData.PosX     = 256;
            SpData.PosY     = 0;
            SpData.PosZ     = PRIORITY_BG;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );
            
            break;

        //----------------------------------------------------------------タスク終了
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

    return TRUE;
}




//-----------------------------------------------------------------------------
//  関数名  :DrAppearTasK
//
//  work    :初プレイタスク（ドクター出現）
//  in      :TASK*      タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int DrAppearTasK(TASK* ip_task)
{
    SPRITE_DATA SpData;
    TASK Task;

    switch(ip_task->mode)
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //next MAIN
            ip_task->mode       = TASK_MODE_MAIN;

            ip_task->user[0]    = 0;    //FadeFlag
            ip_task->user[1]    = 0;    //Anmindex
            ip_task->user[2]    = 0;    //AnmTimer

            // フェードInします
            GameMgr.FadeFlag = FadeIn;

            //スクリプト
            SGameMgr.Script.Flag=1;
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
            Task.user[1]        = INIT_PLAY_DEMO_SCRIPT_BASE;
            Task.user[2]        = INIT_PLAY_DEMO_SCRIPT_NUM;
            CreateTask(&Task);

            break;
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:

            if(!ip_task->user[0]){
                if(!SGameMgr.Script.Flag){//スクリプト終了後フェード
                    ip_task->user[0]    = 1;
                    ip_task->user[1]    = 0;

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
                }else{
                    if(++ip_task->user[2]>=CAST_ANM_WAIT_TIME){
                        ip_task->user[2]=0;
                        ip_task->user[1]^=1;
                    }
                }
            }

            if(ip_task->user[1]){
                SpData.No       = SEES_CHAR_GAME_DR_APPEAR_MOUSE;
                SpData.PosX     = 82;
                SpData.PosY     = 98;
                SpData.PosZ     = PRIORITY_BG-2;
                SpData.ScaleX   = SCALE10;
                SpData.ScaleY   = SCALE10;
                SpData.Rotate   = ROTATE000;
                SpData.Reverse  = NOREVERS;
                DrawSprite( &SpData );
            }

            SpData.No       = SEES_CHAR_GAME_APPEAR_BG_00;
            SpData.PosX     = 0;
            SpData.PosY     = 0;
            SpData.PosZ     = PRIORITY_BG;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );

            SpData.No       = SEES_CHAR_GAME_APPEAR_BG_01;
            SpData.PosX     = 256;
            SpData.PosY     = 0;
            SpData.PosZ     = PRIORITY_BG-1;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );

            
            break;
        //----------------------------------------------------------------タスク終了
        case TASK_MODE_EXIT:
            //スクリプトOFF
            MetuseijiFlag=OFF;

            //----背景タスク
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

            //----カード紹介トタスク
            Task.func       = CardCastTask;
            Task.priority   = TASK_NO_GAME_CARD_CAST;
            Task.attribute  = ATTR_USER;
            Task.status     = TASK_NEW_ENTRY;
            Task.id         = TASK_NO_GAME_CARD_CAST;
            Task.wait_time  = 0;
            Task.buf        = NULL;
            Task.name       = "CardCastTask";
            Task.mode       = TASK_MODE_INIT;
            CreateTask(&Task);

            //----シーソータスク
            Task.func       = SeesawTask;
            Task.priority   = TASK_NO_GAME_SEESAW;
            Task.attribute  = ATTR_USER;
            Task.status     = TASK_NEW_ENTRY;
            Task.id         = TASK_NO_GAME_SEESAW;
            Task.wait_time  = 0;
            Task.buf        = NULL;
            Task.name       = "SeesawTask";
            Task.mode       = TASK_MODE_INIT;
            CreateTask(&Task);

            //----カロリーヌタスク
            Task.func       = KyTask;
            Task.priority   = TASK_NO_GAME_KY;
            Task.attribute  = ATTR_USER;
            Task.status     = TASK_NEW_ENTRY;
            Task.id         = TASK_NO_GAME_KY;
            Task.wait_time  = 0;
            Task.buf        = NULL;
            Task.name       = "KyTask";
            Task.mode       = TASK_MODE_INIT;
            CreateTask(&Task);

            //----博士タスク
            Task.func       = DrTask;
            Task.priority   = TASK_NO_GAME_DR;
            Task.attribute  = ATTR_USER;
            Task.status     = TASK_NEW_ENTRY;
            Task.id         = TASK_NO_GAME_DR;
            Task.wait_time  = 0;
            Task.buf        = NULL;
            Task.name       = "DrTask";
            Task.mode       = TASK_MODE_INIT;
            CreateTask(&Task);

            //----アシスタントタスク
            Task.func       = AsTask;
            Task.priority   = TASK_NO_GAME_AS;
            Task.attribute  = ATTR_USER;
            Task.status     = TASK_NEW_ENTRY;
            Task.id         = TASK_NO_GAME_AS;
            Task.wait_time  = 0;
            Task.buf        = NULL;
            Task.name       = "AsTask";
            Task.mode       = TASK_MODE_INIT;
            CreateTask(&Task);

            //----博士カードタスク
            Task.func       = DrCardTask;
            Task.priority   = TASK_NO_GAME_DR_CARD;
            Task.attribute  = ATTR_USER;
            Task.status     = TASK_NEW_ENTRY;
            Task.id         = TASK_NO_GAME_DR_CARD;
            Task.wait_time  = 0;
            Task.buf        = NULL;
            Task.name       = "DrCardTask";
            Task.mode       = TASK_MODE_INIT;
            CreateTask(&Task);

            //----カロリーヌカードタスク
            Task.func       = KyCardTask;
            Task.priority   = TASK_NO_GAME_KY_CARD;
            Task.attribute  = ATTR_USER;
            Task.status     = TASK_NEW_ENTRY;
            Task.id         = TASK_NO_GAME_KY_CARD;
            Task.wait_time  = 0;
            Task.buf        = NULL;
            Task.name       = "KyCardTask";
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
//  関数名  :SeesawTask
//
//  work    :シーソータスク
//  in      :TASK*      タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int SeesawTask(TASK *ip_task)
{
    static int AnswerLightSpriteTable[]={
        SEES_CHAR_GAME_LEFT_LIGHT_00,               //- 左標準
        SEES_CHAR_GAME_LEFT_LIGHT_01,               //  左1
        SEES_CHAR_GAME_LEFT_LIGHT_02,               //  左2
        SEES_CHAR_GAME_LEFT_LIGHT_03,               //  左3
        SEES_CHAR_GAME_LEFT_LIGHT_04,               //  左4
        SEES_CHAR_GAME_LEFT_LIGHT_05,               //  左5
        SEES_CHAR_GAME_RIGHT_LIGHT_00,              //- 右標準
        SEES_CHAR_GAME_RIGHT_LIGHT_01,              //  右1
        SEES_CHAR_GAME_RIGHT_LIGHT_02,              //  右2
        SEES_CHAR_GAME_RIGHT_LIGHT_03,              //  右3
        SEES_CHAR_GAME_RIGHT_LIGHT_04,              //  右4
        SEES_CHAR_GAME_RIGHT_LIGHT_05,              //  右5
    };

    SPRITE_DATA SpData;
    TASK Task;
    int drno,kyno;


    switch(ip_task->mode)
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //next MAIN
            ip_task->mode       = TASK_MODE_MAIN;

            //----初期化
            SGameMgr.Seesaw.Status              = SEESAW_WAIT;

            SGameMgr.Seesaw.L_Base.Status       = 0;
            SGameMgr.Seesaw.L_Base.Anm.Data.no  = SEES_CHAR_GAME_SEESAW_LEFT;
            SGameMgr.Seesaw.L_Base.Anm.Data.wt  = 0;
            SGameMgr.Seesaw.L_Base.Anm.Index    = 0;
            SGameMgr.Seesaw.L_Base.Pos.x        = SEESAW_LEFT_BASE_X;
            SGameMgr.Seesaw.L_Base.Pos.y        = SEESAW_MATCH_BASE_POS_Y;
            SGameMgr.Seesaw.L_Base.Pos.z        = PRIORITY_SEESAW;
            SGameMgr.Seesaw.L_Base.OPos.x       = 0;
            SGameMgr.Seesaw.L_Base.OPos.y       = 0;
            SGameMgr.Seesaw.L_Base.OPos.z       = 0;
            SGameMgr.Seesaw.L_Base.Spd.dx       = 0;
            SGameMgr.Seesaw.L_Base.Spd.dy       = 0;
            SGameMgr.Seesaw.L_Base.Spd.sx       = 0;
            SGameMgr.Seesaw.L_Base.Spd.sy       = 1;

            SGameMgr.Seesaw.R_Base.Status       = 0;
            SGameMgr.Seesaw.R_Base.Anm.Data.no  = SEES_CHAR_GAME_SEESAW_RIGHT;
            SGameMgr.Seesaw.R_Base.Anm.Data.wt  = 0;
            SGameMgr.Seesaw.R_Base.Anm.Index    = 0;
            SGameMgr.Seesaw.R_Base.Pos.x        = SEESAW_RIGHT_BASE_X;
            SGameMgr.Seesaw.R_Base.Pos.y        = SEESAW_MATCH_BASE_POS_Y;
            SGameMgr.Seesaw.R_Base.Pos.z        = PRIORITY_SEESAW;
            SGameMgr.Seesaw.R_Base.OPos.x       = 0;
            SGameMgr.Seesaw.R_Base.OPos.y       = 0;
            SGameMgr.Seesaw.R_Base.OPos.z       = 0;
            SGameMgr.Seesaw.R_Base.Spd.dx       = 0;
            SGameMgr.Seesaw.R_Base.Spd.dy       = 0;
            SGameMgr.Seesaw.R_Base.Spd.sx       = 0;
            SGameMgr.Seesaw.R_Base.Spd.sy       = 1;

            SGameMgr.Seesaw.MoveCount           = 0;
            SGameMgr.Seesaw.MoveDirect          = 0;
            SGameMgr.Seesaw.MoveSpeed           = SEESAW_SPEED_Y;
            SGameMgr.Seesaw.MoveIndex           = 0;
            SGameMgr.Seesaw.MoveWaitTimer       = 0;
            SGameMgr.Seesaw.L_AnswerNum         = 0;    //ドクター正解数
            SGameMgr.Seesaw.R_AnswerNum         = 0;    //カロリーヌ正解数
            SGameMgr.Seesaw.Timer               = 0;
            SGameMgr.Seesaw.WaitFlag            = 0;
            SGameMgr.Seesaw.WaitTimer           = 0;

            SGameMgr.Seesaw.CountStartFlag      = 0;
            SGameMgr.Seesaw.CountEndFlag        = 0;
            break;
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:
            
            switch(SGameMgr.Seesaw.Status)
            {
                //------------------------------------待ち
                case SEESAW_WAIT:
                    break;
                //------------------------------------つり合う？
                case SEESAW_WEIGHT_MATCH_H_WAIT:
                    
                    if(!SGameMgr.Seesaw.WaitFlag){
                        if(dSoundStatus == DslStatStandby){
                            SGameMgr.Seesaw.WaitFlag=1;
                        }
                    }
                    
                    if(SGameMgr.Seesaw.WaitFlag)
                    {//XA再生中は待つ
                        //レベル１の場合はカウントタスクを起動
                        if(SGameMgr.PlayLevel==0)
                        {//BOX
                            //レベル１はカウントしてから結果を出す
                            if(SGameMgr.Seesaw.CountStartFlag==0)
                            {
                                //カウントタスク管理情報
                                SGameMgr.Seesaw.CountStartFlag  = 1;    //start flag on
                                SGameMgr.Seesaw.CountEndFlag    = 0;    //end flag off
                                
                                //カウントタスク
                                Task.func       = AppleCountTask;
                                Task.priority   = TASK_NO_GAME_APPLE_COUNT;
                                Task.attribute  = ATTR_USER;
                                Task.status     = TASK_NEW_ENTRY;
                                Task.id         = TASK_NO_GAME_APPLE_COUNT;
                                Task.wait_time  = 0;
                                Task.buf        = NULL;
                                Task.name       = "AppleCountTask";
                                Task.mode       = TASK_MODE_INIT;
                                Task.user[0]    = SGameMgr.Dr.Card[ AsSelectCardIndexTable[SGameMgr.PlayLevel][SGameMgr.As.SelectOrderIndex][SGameMgr.As.SelectIndex] ].Data.No;
                                Task.user[1]    = SGameMgr.Ky.Card[ SGameMgr.Player.AnswerIndex ].Data.No;
                                CreateTask(&Task);
                            }
                            
                            //カウントタスク終了後、比較開始
                            if(SGameMgr.Seesaw.CountEndFlag)
                            {
                                //[♪]比較
                                if(SGameMgr.Seesaw.Timer==0)    ssPlaySe(SEES_SE_08);
                                if(SGameMgr.Seesaw.Timer==40)   ssPlaySe(SEES_SE_08);
                                
                                if(++SGameMgr.Seesaw.Timer > SEESAW_COMPARE_WAIT_TIME )
                                {//比較
                                    
                                    drno    = SGameMgr.Dr.Card[ AsSelectCardIndexTable[SGameMgr.PlayLevel][SGameMgr.As.SelectOrderIndex][SGameMgr.As.SelectIndex] ].Data.No;
                                    kyno    = SGameMgr.Ky.Card[ SGameMgr.Player.AnswerIndex ].Data.No;
                                    
                                    if(drno - kyno >= 0)
                                    {//DR勝ち
                                        //[♪]負け音
                                        ssPlaySe(SEES_SE_04);
                                        
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
                                        Task.user[0]        = SCRIPT_LINE_1;
                                        Task.user[1]        = DR_WIN_SCRIPT_BASE;
                                        Task.user[2]        = DR_WIN_SCRIPT_NUM;
                                        CreateTask(&Task);
                                        
                                        //DR下げ
                                        //シーソーステータス変更：
                                        SGameMgr.Seesaw.Status          = SEESAW_WEIGHT_HEAVY_DR;
                                        SGameMgr.Seesaw.MoveIndex       = 0;
                                        SGameMgr.Seesaw.MoveCount       = SeesawUpKyMoveData[SGameMgr.Seesaw.MoveIndex].MoveCount;
                                        SGameMgr.Seesaw.MoveDirect      = SeesawUpKyMoveData[SGameMgr.Seesaw.MoveIndex].MoveDirect;
                                        SGameMgr.Seesaw.MoveWaitTimer   = 0;
                                        SGameMgr.Seesaw.L_Base.OPos.y   = 0;
                                        SGameMgr.Seesaw.R_Base.OPos.y   = 0;
                                        
                                        //KY上げ
                                        SGameMgr.Ky.Character.Status    = CAST_RISE;
                                        
                                        //正解数
                                        if(++SGameMgr.Seesaw.L_AnswerNum >= MAX_SEESAW_LIGHT){
                                            SGameMgr.Seesaw.L_AnswerNum = MAX_SEESAW_LIGHT;
                                        }
                                        
                                        //正解ランプ
                                        Task.func       = LightFlushTask;
                                        Task.priority   = TASK_NO_GAME_LIGHT_FLUSH;
                                        Task.attribute  = ATTR_USER;
                                        Task.status     = TASK_NEW_ENTRY;
                                        Task.id         = TASK_NO_GAME_LIGHT_FLUSH;
                                        Task.wait_time  = LIGHT_FLUSH_WAIT_TIME_;
                                        Task.buf        = NULL;
                                        Task.name       = "LightFlushTask";
                                        Task.mode       = TASK_MODE_INIT;
                                        Task.user[0]    = 0;
                                        CreateTask(&Task);
                                        
                                    }else
                                    {//KY勝ち
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
                                        Task.user[0]        = SCRIPT_LINE_1;
                                        Task.user[1]        = KY_WIN_SCRIPT_BASE;
                                        Task.user[2]        = KY_WIN_SCRIPT_NUM;
                                        CreateTask(&Task);
                                        
                                        //KY下げ
                                        //シーソーステータス変更：
                                        SGameMgr.Seesaw.Status          = SEESAW_WEIGHT_HEAVY_KY;
                                        SGameMgr.Seesaw.MoveIndex       = 0;
                                        SGameMgr.Seesaw.MoveCount       = SeesawUpDrMoveData[SGameMgr.Seesaw.MoveIndex].MoveCount;
                                        SGameMgr.Seesaw.MoveDirect      = SeesawUpDrMoveData[SGameMgr.Seesaw.MoveIndex].MoveDirect;
                                        SGameMgr.Seesaw.MoveWaitTimer   = 0;
                                        SGameMgr.Seesaw.L_Base.OPos.y   = 0;
                                        SGameMgr.Seesaw.R_Base.OPos.y   = 0;
                                        
                                        //DR上げ
                                        SGameMgr.Dr.Character.Status    = CAST_RISE;
                                        
                                        //正解数
                                        if(++SGameMgr.Seesaw.R_AnswerNum >= MAX_SEESAW_LIGHT){
                                            SGameMgr.Seesaw.R_AnswerNum = MAX_SEESAW_LIGHT;
                                        }
                                        
                                        //正解ランプ
                                        Task.func       = LightFlushTask;
                                        Task.priority   = TASK_NO_GAME_LIGHT_FLUSH;
                                        Task.attribute  = ATTR_USER;
                                        Task.status     = TASK_NEW_ENTRY;
                                        Task.id         = TASK_NO_GAME_LIGHT_FLUSH;
                                        Task.wait_time  = LIGHT_FLUSH_WAIT_TIME_;
                                        Task.buf        = NULL;
                                        Task.name       = "LightFlushTask";
                                        Task.mode       = TASK_MODE_INIT;
                                        Task.user[0]    = 1;
                                        CreateTask(&Task);
                                    }
                                    
                                    //カウントタスク管理情報クリア
                                    SGameMgr.Seesaw.CountStartFlag  = 0;
                                    SGameMgr.Seesaw.CountEndFlag    = 0;
                                }
                            }
                            
                        }else
                        {//CARD
                            //[♪]比較
                            if(SGameMgr.Seesaw.Timer==0)    ssPlaySe(SEES_SE_08);
                            if(SGameMgr.Seesaw.Timer==40)   ssPlaySe(SEES_SE_08);
                            
                            if(++SGameMgr.Seesaw.Timer > SEESAW_COMPARE_WAIT_TIME )
                            {//比較
                                
                                drno    = SGameMgr.Dr.Card[ AsSelectCardIndexTable[SGameMgr.PlayLevel][SGameMgr.As.SelectOrderIndex][SGameMgr.As.SelectIndex] ].Data.No;
                                kyno    = SGameMgr.Ky.Card[ SGameMgr.Player.AnswerIndex ].Data.No;
                                
                                if(drno - kyno >= 0)
                                {//DR勝ち
                                    //[♪]負け音
                                    ssPlaySe(SEES_SE_04);
                                    
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
                                    Task.user[0]        = SCRIPT_LINE_1;
                                    Task.user[1]        = DR_WIN_SCRIPT_BASE;
                                    Task.user[2]        = DR_WIN_SCRIPT_NUM;
                                    CreateTask(&Task);
                                    
                                    //DR下げ
                                    //シーソーステータス変更：
                                    SGameMgr.Seesaw.Status          = SEESAW_WEIGHT_HEAVY_DR;
                                    SGameMgr.Seesaw.MoveIndex       = 0;
                                    SGameMgr.Seesaw.MoveCount       = SeesawUpKyMoveData[SGameMgr.Seesaw.MoveIndex].MoveCount;
                                    SGameMgr.Seesaw.MoveDirect      = SeesawUpKyMoveData[SGameMgr.Seesaw.MoveIndex].MoveDirect;
                                    SGameMgr.Seesaw.MoveWaitTimer   = 0;
                                    SGameMgr.Seesaw.L_Base.OPos.y   = 0;
                                    SGameMgr.Seesaw.R_Base.OPos.y   = 0;
                                    
                                    //KY上げ
                                    SGameMgr.Ky.Character.Status    = CAST_RISE;
                                    
                                    //正解数
                                    if(++SGameMgr.Seesaw.L_AnswerNum >= MAX_SEESAW_LIGHT){
                                        SGameMgr.Seesaw.L_AnswerNum = MAX_SEESAW_LIGHT;
                                    }
                                    
                                    //正解ランプ
                                    Task.func       = LightFlushTask;
                                    Task.priority   = TASK_NO_GAME_LIGHT_FLUSH;
                                    Task.attribute  = ATTR_USER;
                                    Task.status     = TASK_NEW_ENTRY;
                                    Task.id         = TASK_NO_GAME_LIGHT_FLUSH;
                                    Task.wait_time  = LIGHT_FLUSH_WAIT_TIME_;
                                    Task.buf        = NULL;
                                    Task.name       = "LightFlushTask";
                                    Task.mode       = TASK_MODE_INIT;
                                    Task.user[0]    = 0;
                                    CreateTask(&Task);
                                    
                                }else
                                {//KY勝ち
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
                                    Task.user[0]        = SCRIPT_LINE_1;
                                    Task.user[1]        = KY_WIN_SCRIPT_BASE;
                                    Task.user[2]        = KY_WIN_SCRIPT_NUM;
                                    CreateTask(&Task);
                                    
                                    //KY下げ
                                    //シーソーステータス変更：
                                    SGameMgr.Seesaw.Status          = SEESAW_WEIGHT_HEAVY_KY;
                                    SGameMgr.Seesaw.MoveIndex       = 0;
                                    SGameMgr.Seesaw.MoveCount       = SeesawUpDrMoveData[SGameMgr.Seesaw.MoveIndex].MoveCount;
                                    SGameMgr.Seesaw.MoveDirect      = SeesawUpDrMoveData[SGameMgr.Seesaw.MoveIndex].MoveDirect;
                                    SGameMgr.Seesaw.MoveWaitTimer   = 0;
                                    SGameMgr.Seesaw.L_Base.OPos.y   = 0;
                                    SGameMgr.Seesaw.R_Base.OPos.y   = 0;
                                    
                                    //DR上げ
                                    SGameMgr.Dr.Character.Status    = CAST_RISE;
                                    
                                    //正解数
                                    if(++SGameMgr.Seesaw.R_AnswerNum >= MAX_SEESAW_LIGHT){
                                        SGameMgr.Seesaw.R_AnswerNum = MAX_SEESAW_LIGHT;
                                    }
                                    
                                    //正解ランプ
                                    Task.func       = LightFlushTask;
                                    Task.priority   = TASK_NO_GAME_LIGHT_FLUSH;
                                    Task.attribute  = ATTR_USER;
                                    Task.status     = TASK_NEW_ENTRY;
                                    Task.id         = TASK_NO_GAME_LIGHT_FLUSH;
                                    Task.wait_time  = LIGHT_FLUSH_WAIT_TIME_;
                                    Task.buf        = NULL;
                                    Task.name       = "LightFlushTask";
                                    Task.mode       = TASK_MODE_INIT;
                                    Task.user[0]    = 1;
                                    CreateTask(&Task);
                                }
                                
                            }
                        }
                    }

                    break;
                //------------------------------------つり合う
                case SEESAW_WEIGHT_MATCH:
                    
                    break;
                //------------------------------------比較中
                case SEESAW_WEIGHT_COMPARE:
                    //----切り替え
                    if(SGameMgr.Seesaw.MoveCount <= 0)
                    {
                        if(SeesawCompareMoveData[SGameMgr.Seesaw.MoveIndex].MoveCount == -1)
                        {//----移動終了
                            //飛び先データセット
                            //ステータス変更：つり合う？へ
                            SGameMgr.Seesaw.Status          = SEESAW_WEIGHT_MATCH_H_WAIT;
                            SGameMgr.Seesaw.L_Base.OPos.y   = 0;        //念のため
                            SGameMgr.Seesaw.R_Base.OPos.y   = 0;        //念のため
                            SGameMgr.Seesaw.Timer           = 0;
                            SGameMgr.Seesaw.WaitFlag        = 0;
                            
                        }else
                        {//---継続（次の方向へ）
                            ++SGameMgr.Seesaw.MoveIndex;
                            SGameMgr.Seesaw.MoveCount   = SeesawCompareMoveData[SGameMgr.Seesaw.MoveIndex].MoveCount;
                            SGameMgr.Seesaw.MoveDirect  = SeesawCompareMoveData[SGameMgr.Seesaw.MoveIndex].MoveDirect;
                        };
                    }
                    
                    //----移動カウント減
                    --SGameMgr.Seesaw.MoveCount;
                    
                    //----タイマークリア
                    SGameMgr.Seesaw.MoveWaitTimer = 0;
                    
                    //----移動
                    SGameMgr.Seesaw.L_Base.OPos.y += SGameMgr.Seesaw.MoveDirect * SGameMgr.Seesaw.MoveSpeed * -1;
                    SGameMgr.Seesaw.R_Base.OPos.y += SGameMgr.Seesaw.MoveDirect * SGameMgr.Seesaw.MoveSpeed;
                    
                    break;
                //------------------------------------上空から戻るDR
                case SEESAW_RETURN_DR:
                    
                    if(SGameMgr.Seesaw.MoveCount<=0){
                        SGameMgr.Seesaw.Status          = SEESAW_WAIT;
                        SGameMgr.Seesaw.L_Base.OPos.y   = 0;
                        SGameMgr.Seesaw.R_Base.OPos.y   = 0;
                        
                        //終了チェック
                        if(++SGameMgr.As.SelectIndex > SGameMgr.As.EffectiveCardNum-1 )
                        {//
                            SGameMgr.As.SelectIndex = SGameMgr.As.EffectiveCardNum-1;
                            //ステータス変更：終了待ちへ
                            SGameMgr.As.Character.Status    = AS_STAND_END;
                            SGameMgr.As.AnmType             = AS_SP_TYPE_QUESTION;
                            
                            //勝敗確認
                            if(SGameMgr.Seesaw.R_AnswerNum - SGameMgr.Seesaw.L_AnswerNum > 0){
                                SGameMgr.ClearFlag = 1;
                                if(SGameMgr.PlayLevel==SEES_GAME_MAX_LEVEL_NUM-1){
                                    SGameMgr.AllClearFlag = 1;
                                }
                                
                                //----プレイレベル更新
                                if(++SGameMgr.PlayLevel > SEES_GAME_MAX_LEVEL_NUM-1){
                                    SGameMgr.PlayLevel = SEES_GAME_MAX_LEVEL_NUM-1;
                                }
                                
                            }else
                            {
                                SGameMgr.FalseFlag = 1;
                            }
                        }else
                        {//もう一度
                            //アシスタントのステータスを変更：
                            SGameMgr.As.Character.Status    = AS_ONCE_AGAIN;
                            SGameMgr.As.AnmType             = AS_SP_TYPE_ONCE_AGAIN;
                            SGameMgr.As.Timer               = 0;
                            
                            //DRとKYのアニメを待ちへ
                            SGameMgr.Dr.AnmBase             = DR_ANM_BASE_WAIT;
                            SGameMgr.Ky.AnmBase             = KY_ANM_BASE_WAIT;
                            
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
                            Task.user[0]        = SCRIPT_LINE_1;
                            Task.user[1]        = AS_RETRY_SCRIPT_BASE;
                            Task.user[2]        = AS_RETRY_SCRIPT_NUM;
                            CreateTask(&Task);
                        }
                        
                    }
                    
                    //----移動カウント減
                    --SGameMgr.Seesaw.MoveCount;
                    
                    //----タイマークリア
                    SGameMgr.Seesaw.MoveWaitTimer = 0;
                    
                    //----移動
                    SGameMgr.Seesaw.L_Base.OPos.y += SGameMgr.Seesaw.MoveDirect * SGameMgr.Seesaw.MoveSpeed * -1;
                    SGameMgr.Seesaw.R_Base.OPos.y += SGameMgr.Seesaw.MoveDirect * SGameMgr.Seesaw.MoveSpeed;
                    
                    break;
                //------------------------------------上空から戻るKY
                case SEESAW_RETURN_KY:
                    
                    if(SGameMgr.Seesaw.MoveCount<=0){
                        SGameMgr.Seesaw.Status          = SEESAW_WAIT;
                        SGameMgr.Seesaw.L_Base.OPos.y   = 0;
                        SGameMgr.Seesaw.R_Base.OPos.y   = 0;
                        
                        
                        //終了チェック
                        if(++SGameMgr.As.SelectIndex > SGameMgr.As.EffectiveCardNum-1 )
                        {//
                            SGameMgr.As.SelectIndex = SGameMgr.As.EffectiveCardNum-1;
                            //ステータス変更：終了待ちへ
                            SGameMgr.As.Character.Status    = AS_STAND_END;
                            SGameMgr.As.AnmType             = AS_SP_TYPE_QUESTION;
                            
                            //勝敗確認
                            if(SGameMgr.Seesaw.R_AnswerNum - SGameMgr.Seesaw.L_AnswerNum > 0){
                                SGameMgr.ClearFlag = 1;
                                if(SGameMgr.PlayLevel==SEES_GAME_MAX_LEVEL_NUM-1){
                                    SGameMgr.AllClearFlag = 1;
                                }
                                
                                //----プレイレベル更新
                                if(++SGameMgr.PlayLevel > SEES_GAME_MAX_LEVEL_NUM-1){
                                    SGameMgr.PlayLevel = SEES_GAME_MAX_LEVEL_NUM-1;
                                }
                                
                            }else
                            {
                                SGameMgr.FalseFlag = 1;
                            }
                            
                        }else
                        {//もう一度
                            //アシスタントのステータスを変更：
                            SGameMgr.As.Character.Status    = AS_ONCE_AGAIN;
                            SGameMgr.As.AnmType             = AS_SP_TYPE_ONCE_AGAIN;
                            SGameMgr.As.Timer               = 0;
                            
                            //DRとKYのアニメを待ちへ
                            SGameMgr.Dr.AnmBase             = DR_ANM_BASE_WAIT;
                            SGameMgr.Ky.AnmBase             = KY_ANM_BASE_WAIT;
                            
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
                            Task.user[0]        = SCRIPT_LINE_1;
                            Task.user[1]        = AS_RETRY_SCRIPT_BASE;
                            Task.user[2]        = AS_RETRY_SCRIPT_NUM;
                            CreateTask(&Task);
                        }
                    }
                    
                    //----移動カウント減
                    --SGameMgr.Seesaw.MoveCount;
                    
                    //----タイマークリア
                    SGameMgr.Seesaw.MoveWaitTimer = 0;
                    
                    //----移動
                    SGameMgr.Seesaw.L_Base.OPos.y += SGameMgr.Seesaw.MoveDirect * SGameMgr.Seesaw.MoveSpeed * -1;
                    SGameMgr.Seesaw.R_Base.OPos.y += SGameMgr.Seesaw.MoveDirect * SGameMgr.Seesaw.MoveSpeed;
                    
                    break;
                //------------------------------------下がるDR
                case SEESAW_WEIGHT_HEAVY_DR:
                    if(SGameMgr.Seesaw.MoveCount<=0){
                        SGameMgr.Seesaw.Status          = SEESAW_WAIT;
                    }
                    
                    //----移動カウント減
                    --SGameMgr.Seesaw.MoveCount;
                    
                    //----タイマークリア
                    SGameMgr.Seesaw.MoveWaitTimer = 0;
                    
                    //----移動
                    SGameMgr.Seesaw.L_Base.OPos.y += SGameMgr.Seesaw.MoveDirect * SGameMgr.Seesaw.MoveSpeed * -1;
                    SGameMgr.Seesaw.R_Base.OPos.y += SGameMgr.Seesaw.MoveDirect * SGameMgr.Seesaw.MoveSpeed;
                        
                    break;
                //------------------------------------下がるKY
                case SEESAW_WEIGHT_HEAVY_KY:
                    if(SGameMgr.Seesaw.MoveCount<=0){
                        SGameMgr.Seesaw.Status          = SEESAW_WAIT;
                    }
                    
                    //----移動カウント減
                    --SGameMgr.Seesaw.MoveCount;
                    
                    //----タイマークリア
                    SGameMgr.Seesaw.MoveWaitTimer = 0;
                    
                    //----移動
                    SGameMgr.Seesaw.L_Base.OPos.y += SGameMgr.Seesaw.MoveDirect * SGameMgr.Seesaw.MoveSpeed * -1;
                    SGameMgr.Seesaw.R_Base.OPos.y += SGameMgr.Seesaw.MoveDirect * SGameMgr.Seesaw.MoveSpeed;
                        
                    break;
                default:
            }


            //シーソー左
            SpData.No       = SGameMgr.Seesaw.L_Base.Anm.Data.no;   //インデックス番号
            SpData.PosX     = SGameMgr.Seesaw.L_Base.Pos.x;         //X位置
            SpData.PosY     = SGameMgr.Seesaw.L_Base.Pos.y + SGameMgr.Seesaw.L_Base.OPos.y; //Y位置
            SpData.PosZ     = PRIORITY_SEESAW;                      //優先順位
            SpData.ScaleX   = SCALE10;                              //スケールX
            SpData.ScaleY   = SCALE10;                              //スケールY
            SpData.Rotate   = ROTATE000;                            //回転角
            SpData.Reverse  = NOREVERS;                             //反転コード
            DrawSprite( &SpData );                                  //スプライト描画

            //シーソー右
            SpData.No       = SGameMgr.Seesaw.R_Base.Anm.Data.no;   //インデックス番号
            SpData.PosX     = SGameMgr.Seesaw.R_Base.Pos.x;         //X位置
            SpData.PosY     = SGameMgr.Seesaw.R_Base.Pos.y + SGameMgr.Seesaw.R_Base.OPos.y; //Y位置
            SpData.PosZ     = PRIORITY_SEESAW;                      //優先順位
            SpData.ScaleX   = SCALE10;                              //スケールX
            SpData.ScaleY   = SCALE10;                              //スケールY
            SpData.Rotate   = ROTATE000;                            //回転角
            SpData.Reverse  = NOREVERS;                             //反転コード
            DrawSprite( &SpData );                                  //スプライト描画

            //正解数ランプ左
            SpData.No       = AnswerLightSpriteTable[SEESAW_LEFT_LIGHT_BASE + SGameMgr.Seesaw.L_AnswerNum]; //インデックス番号
            SpData.PosX     = 140;                                  //X位置
            SpData.PosY     = 57 + BG_OFFSET_Y;                     //Y位置
            SpData.PosZ     = PRIORITY_SEESAW;                      //優先順位
            SpData.ScaleX   = SCALE10;                              //スケールX
            SpData.ScaleY   = SCALE10;                              //スケールY
            SpData.Rotate   = ROTATE000;                            //回転角
            SpData.Reverse  = NOREVERS;                             //反転コード
            DrawSprite( &SpData );                                  //スプライト描画

            //正解数ランプ右
            SpData.No       = AnswerLightSpriteTable[SEESAW_RIGHT_LIGHT_BASE + SGameMgr.Seesaw.R_AnswerNum];    //インデックス番号
            SpData.PosX     = 170;                                  //X位置
            SpData.PosY     = 57 + BG_OFFSET_Y;                     //Y位置
            SpData.PosZ     = PRIORITY_SEESAW;                      //優先順位
            SpData.ScaleX   = SCALE10;                              //スケールX
            SpData.ScaleY   = SCALE10;                              //スケールY
            SpData.Rotate   = ROTATE000;                            //回転角
            SpData.Reverse  = NOREVERS;                             //反転コード
            DrawSprite( &SpData );                                  //スプライト描画

            break;
        //----------------------------------------------------------------タスク終了
        case TASK_MODE_EXIT:
            
            //自分を削除
            ExitTask(ip_task->id);
            break;
        default:
    }

    return TRUE;

}


//-----------------------------------------------------------------------------
//  関数名  :LightFlushTask
//
//  work    :勝利時のマシーン点滅タスク
//  in      :TASK*      タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int LightFlushTask(TASK* ip_task)
{
    static SEES_SPRITE_DATA LightFlushSpriteTable[]={
        {   SEES_CHAR_GAME_LEFT_LIGHT_FLUSH,    136,    31+BG_OFFSET_Y  },
        {   SEES_CHAR_GAME_RIGHT_LIGHT_FLUSH,   164,    31+BG_OFFSET_Y  },
    };
    SPRITE_DATA SpData;


    switch(ip_task->mode)
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //next MAIN
            ip_task->mode       = TASK_MODE_MAIN;
            
            //----初期化
            ip_task->user[1]    = 0;

            //[♪]ピン
            ssPlaySe(SEES_SE_03);

            break;
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:
            SpData.No       = LightFlushSpriteTable[ ip_task->user[0] ].No;     //インデックス番号
            SpData.PosX     = LightFlushSpriteTable[ ip_task->user[0] ].Ofx;    //X位置
            SpData.PosY     = LightFlushSpriteTable[ ip_task->user[0] ].Ofy;    //Y位置
            SpData.PosZ     = PRIORITY_BG;                                      //優先順位
            SpData.ScaleX   = SCALE10;                                          //スケールX
            SpData.ScaleY   = SCALE10;                                          //スケールY
            SpData.Rotate   = ROTATE000;                                        //回転角
            SpData.Reverse  = NOREVERS;                                         //反転コード
            DrawSprite( &SpData );                                              //スプライト描画

            //----タイマー削除
            if(++ip_task->user[1] >= MACHINE_LIGHT_FLUSH_TIME){
                ip_task->mode = TASK_MODE_EXIT;
            }

            break;
        //----------------------------------------------------------------タスク終了
        case TASK_MODE_EXIT:
            
            //自分を削除
            ExitTask(ip_task->id);
            break;
        default:
    }

    return TRUE;
}




//-----------------------------------------------------------------------------
//  関数名  :CardCastTask
//
//  work    :出演カード紹介タスク
//  in      :TASK* ip_task
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int CardCastTask(TASK* ip_task)
{
    SPRITE_DATA SpData;
    int i,cardtype;
    TASK Task;


    switch(ip_task->mode)
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //next MAIN
            ip_task->mode       = TASK_MODE_MAIN;
            
            //----初期化
            ip_task->user[0]    = 0;

            //----有効カード枚数
            if(SGameMgr.PlayLevel == 0){
                SGameMgr.CardCast.EffectiveNum  = EFFECTIVE_CARD_BOX_NUM*2;
                cardtype                        = CARD_TYPE_BOX;
            }else{
                SGameMgr.CardCast.EffectiveNum  = EFFECTIVE_CARD_STAR_NUM*2;
                cardtype                        = CARD_TYPE_STAR;
            }

            
            //インデックス
            SGameMgr.CardCast.Index     = rand() % MAX_GAME_PATTERN_NUM;
            
            //サイドセット
            SGameMgr.CardCast.DeelSide  = rand() % 2;
            
            //タイマー
            SGameMgr.CardCast.Timer     = 0;

            //カードセット
            for(i=0;i<SGameMgr.CardCast.EffectiveNum;i++)
            {
                SGameMgr.CardCast.Card[i].Character.Status          = CARD_CAST_WAIT;
                SGameMgr.CardCast.Card[i].Character.Anm.Index       = 0;
                SGameMgr.CardCast.Card[i].Character.Anm.Data.no     = 0;
                SGameMgr.CardCast.Card[i].Character.Anm.Data.wt     = 0;
                
                if(cardtype==CARD_TYPE_STAR)    SGameMgr.CardCast.Card[i].Character.Pos.x   = 22+i*(26+2);
                else                            SGameMgr.CardCast.Card[i].Character.Pos.x   = 20+i*(40+8);
                
                SGameMgr.CardCast.Card[i].Character.Pos.y           = 89+BG_OFFSET_Y;
                SGameMgr.CardCast.Card[i].Character.Pos.z           = PRIORITY_CARD;
                SGameMgr.CardCast.Card[i].Character.OPos.x          = 0;
                SGameMgr.CardCast.Card[i].Character.OPos.y          = 0;
                SGameMgr.CardCast.Card[i].Character.OPos.z          = 0;
                SGameMgr.CardCast.Card[i].Character.Spd.dx          = 0;
                SGameMgr.CardCast.Card[i].Character.Spd.dy          = 0;
                SGameMgr.CardCast.Card[i].Character.Spd.sx          = 0;
                SGameMgr.CardCast.Card[i].Character.Spd.sy          = 0;
                SGameMgr.CardCast.Card[i].Data.No                   = CardCastDataTable[SGameMgr.PlayLevel][SGameMgr.CardCast.Index][i];
                SGameMgr.CardCast.Card[i].Data.Flag                 = 1;                //フラグ
                SGameMgr.CardCast.Card[i].Data.Side                 = CARD_SIDE_HEADS;  //表
                SGameMgr.CardCast.Card[i].DrawFlag                  = 1;                //描画フラグ
                SGameMgr.CardCast.Card[i].Type                      = cardtype;         //カードタイプ
                
                //分配
                SGameMgr.CardCast.CastDeelTimer[i]                  = i*CARD_DEAL_WAIT_TIME;
                SGameMgr.CardCast.CastTurnOverTimer[i]              = i*CARD_DEAL_WAIT_TIME;;
            }
            
            // フェードInします
            GameMgr.FadeFlag = FadeIn;

            //[♪]BGM
            ssPlayBgm(SEES_BGM_00);

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
            Task.user[0]        = SCRIPT_LINE_1;
            Task.user[1]        = INTRODUCE_CARD_CAST_SCRIPT_BASE;
            Task.user[2]        = INTRODUCE_CARD_CAST_SCRIPT_NUM;
            CreateTask(&Task);

            break;
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:
            
            //----裏返し待ち時間
            ++SGameMgr.CardCast.Timer;

            //----各々のカード
            for(i=0;i<SGameMgr.CardCast.EffectiveNum;i++)
            {
                switch(SGameMgr.CardCast.Card[i].Character.Status)
                {
                    //----------------------------------------待ち
                    case CARD_CAST_WAIT:
                        
                        //アシスタントからの指示待ち
                        
//                      if(SGameMgr.CardCast.Timer >= CARD_CAST_TURN_OVER_WAIT_TIME){
//                          SGameMgr.CardCast.Card[i].Character.Status = CARD_CAST_TURN_OVER;
//                      }
                        break;
                    //----------------------------------------裏返し
                    case CARD_CAST_TURN_OVER:
                        if( --SGameMgr.CardCast.CastDeelTimer[i] <= 0 ){
                            SGameMgr.CardCast.Card[i].Data.Side = CARD_SIDE_TAIL;
                            
                            //一番最後のカードが裏返しになったら配ります
                            if( SGameMgr.CardCast.Card[SGameMgr.CardCast.EffectiveNum-1].Data.Side == CARD_SIDE_TAIL ){
                                SGameMgr.CardCast.Card[i].Character.Status = CARD_CAST_DEAL;
                            }
                        }
                        
                        break;
                    //----------------------------------------配る
                    case CARD_CAST_DEAL:
                        
                        if(--SGameMgr.CardCast.CastTurnOverTimer[i] <= 0){
                            SGameMgr.CardCast.Card[i].DrawFlag          = 0;
                            SGameMgr.CardCast.Card[i].Character.Status  = CARD_CAST_END;
                            
                            //----ユーザーのカードを表示
                            SetDrawFlagUserCard(i);
                            //[♪]
                            ssPlaySe(SEES_SE_05);
                            
                            
                            if(++ip_task->user[0] >= SGameMgr.CardCast.EffectiveNum ) {
                                ip_task->mode = TASK_MODE_EXIT;
                            }
                        }
                        break;
                    case CARD_CAST_END:
                        
                        
                        break;
                    default:
                }
                
                //----描画
                if(SGameMgr.CardCast.Card[i].Character.Status != CARD_CAST_END){
                    DrawCard(   SGameMgr.CardCast.Card[i].Type,
                                SGameMgr.CardCast.Card[i].Data.No,
                                SGameMgr.CardCast.Card[i].Data.Side,
                                SGameMgr.CardCast.Card[i].Character.Pos.x + SGameMgr.CardCast.Card[i].Character.OPos.x,
                                SGameMgr.CardCast.Card[i].Character.Pos.y + SGameMgr.CardCast.Card[i].Character.OPos.y,
                                SGameMgr.CardCast.Card[i].Character.Pos.z + SGameMgr.CardCast.Card[i].Character.OPos.z);
                }
            }
            
            break;
        //----------------------------------------------------------------タスク終了
        case TASK_MODE_EXIT:
            
            //----アシスタントカード選択を開始
            //ステータス変更：手を頭へ
            SGameMgr.As.Character.Status    = AS_HAND_HEAD;
            //アニメセット
            SGameMgr.As.AnmType             = AS_SP_TYPE_SELECT_QUESTION_00;
            
            //----プレイヤータスク
            Task.func       = PlayerTask;
            Task.priority   = TASK_NO_GAME_PLAYER;
            Task.attribute  = ATTR_USER;
            Task.status     = TASK_NEW_ENTRY;
            Task.id         = TASK_NO_GAME_PLAYER;
            Task.wait_time  = 0;
            Task.buf        = NULL;
            Task.name       = "PlayerTask";
            Task.mode       = TASK_MODE_INIT;
            CreateTask(&Task);
            
            //----ポーズタスク
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
            
            //自分を削除
            ExitTask(ip_task->id);
            break;
        default:
    }

    return TRUE;
}




//-----------------------------------------------------------------------------
//  関数名  :PlayerTask
//
//  work    :プレイヤータスク
//  in      :TASK*      タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int PlayerTask(TASK* ip_task)
{
    static int ConvertTable[] ={-1,4,3,2,1,0};
    SPRITE_DATA SpData;
    int dirindex;

    switch(ip_task->mode)
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //next MAIN
            ip_task->mode       = TASK_MODE_MAIN;
            
            //----初期化
            SGameMgr.Player.AnswerIndex             = 0;
            
            if(SGameMgr.PlayLevel==0){
                SGameMgr.Player.CardType            = CARD_TYPE_BOX;
                SGameMgr.Player.EffectiveIndexNum   = EFFECTIVE_CARD_BOX_NUM;
            }
            else{
                SGameMgr.Player.CardType            = CARD_TYPE_STAR;
                SGameMgr.Player.EffectiveIndexNum   = EFFECTIVE_CARD_STAR_NUM;
            }

            SGameMgr.Player.WaitFlag                = 0;
            SGameMgr.Player.WaitTimer               = GET_DA_STATUS_WAIT_TIME;
            SGameMgr.Player.Character.Status        = PLAYER_WAIT;
            SGameMgr.Player.Character.Anm.Data.no   = SEES_CHAR_GAME_SELECT_ANSWER_CURSOR;
            SGameMgr.Player.Character.Anm.Data.wt   = 0;
            SGameMgr.Player.Character.Anm.Index     = 0;
            SGameMgr.Player.Character.Pos.x         = KyCardPosTable[SGameMgr.Player.CardType][SGameMgr.Player.AnswerIndex].x;
            SGameMgr.Player.Character.Pos.y         = KyCardPosTable[SGameMgr.Player.CardType][SGameMgr.Player.AnswerIndex].y;
            SGameMgr.Player.Character.Pos.z         = PRIORITY_CURSOR;
            SGameMgr.Player.Character.OPos.x        = 16;
            SGameMgr.Player.Character.OPos.y        = 12;
            SGameMgr.Player.Character.OPos.z        = 0;
            SGameMgr.Player.Character.Spd.dx        = 0;
            SGameMgr.Player.Character.Spd.dy        = 0;
            SGameMgr.Player.Character.Spd.sx        = 0;
            SGameMgr.Player.Character.Spd.sy        = 0;

            break;
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:
            
            switch(SGameMgr.Player.Character.Status)
            {
                //----------------------------------------待ち
                case PLAYER_WAIT:
                    
                    break;
                //----------------------------------------XA待ち
                case PLAYER_XA_WAIT:
                    if(--SGameMgr.Player.WaitTimer<=0)  SGameMgr.Player.WaitFlag=0;
                    
                    if(!SGameMgr.Player.WaitFlag){
                        if(dSoundStatus == DslStatStandby){
                            //ステータス変更：選択へ
                            SGameMgr.Player.Character.Status=PLAYER_SELECT;
                            //プレイヤーのカーソル位置変更
                            ChangePlayerCursorIndex();
                        }
                    }
                    
                    break;
                //----------------------------------------選択
                case PLAYER_SELECT:
                    if(SGameMgr.Player.CardType==CARD_TYPE_BOX)
                    {//----BOX
                        switch(SGameMgr.Player.AnswerIndex)
                        {
                            //--------------------------------------------------------------------0
                            case 0:
                                if(JstPad & PADLleft)
                                {//----------------------------------------------- ←
                                    if(SGameMgr.Ky.Card[2].Data.Flag){
                                        //[♪] レバー音
                                        ssPlaySe(BUTONSE_LEVER);
                                        SGameMgr.Player.AnswerIndex = 2;
                                    }else
                                    if(SGameMgr.Ky.Card[1].Data.Flag){
                                        //[♪] レバー音
                                        ssPlaySe(BUTONSE_LEVER);
                                        SGameMgr.Player.AnswerIndex = 1;
                                    }else{
                                        
                                    }
                                }else
                                if(JstPad & PADLright)
                                {//----------------------------------------------- →
                                    if(SGameMgr.Ky.Card[1].Data.Flag){
                                        //[♪] レバー音
                                        ssPlaySe(BUTONSE_LEVER);
                                        SGameMgr.Player.AnswerIndex = 1;
                                    }else
                                    if(SGameMgr.Ky.Card[2].Data.Flag){
                                        //[♪] レバー音
                                        ssPlaySe(BUTONSE_LEVER);
                                        SGameMgr.Player.AnswerIndex = 2;
                                    }else{
                                        
                                    }
                                }else
                                if(JstPad & PADLdown)
                                {//----------------------------------------------- ↓
                                    if(SGameMgr.Ky.Card[1].Data.Flag){
                                        //[♪] レバー音
                                        ssPlaySe(BUTONSE_LEVER);
                                        SGameMgr.Player.AnswerIndex = 1;
                                    }else
                                    if(SGameMgr.Ky.Card[2].Data.Flag){
                                        //[♪] レバー音
                                        ssPlaySe(BUTONSE_LEVER);
                                        SGameMgr.Player.AnswerIndex = 2;
                                    }else{
                                        
                                    }
                                }else{
                                    
                                }
                                break;
                            //--------------------------------------------------------------------1
                            case 1:
                                if(JstPad & PADLright)
                                {//----------------------------------------------- →
                                    if(SGameMgr.Ky.Card[2].Data.Flag){
                                        //[♪] レバー音
                                        ssPlaySe(BUTONSE_LEVER);
                                        SGameMgr.Player.AnswerIndex = 2;
                                    }else
                                    if(SGameMgr.Ky.Card[0].Data.Flag){
                                        //[♪] レバー音
                                        ssPlaySe(BUTONSE_LEVER);
                                        SGameMgr.Player.AnswerIndex = 0;
                                    }else{
                                        
                                    }
                                }else
                                if(JstPad & PADLleft)
                                {//----------------------------------------------- ←
                                    
                                    if(SGameMgr.Ky.Card[0].Data.Flag){
                                        //[♪] レバー音
                                        ssPlaySe(BUTONSE_LEVER);
                                        SGameMgr.Player.AnswerIndex = 0;
                                    }else
                                    if(SGameMgr.Ky.Card[2].Data.Flag){
                                        //[♪] レバー音
                                        ssPlaySe(BUTONSE_LEVER);
                                        SGameMgr.Player.AnswerIndex = 2;
                                    }else{
                                        
                                    }
                                }else
                                if(JstPad & PADLup)
                                {//----------------------------------------------- ↑
                                    if(SGameMgr.Ky.Card[0].Data.Flag){
                                        //[♪] レバー音
                                        ssPlaySe(BUTONSE_LEVER);
                                        SGameMgr.Player.AnswerIndex = 0;
                                    }else{
                                        
                                    }
                                }else{
                                    
                                }
                                break;
                            //--------------------------------------------------------------------2
                            case 2:
                                if(JstPad & PADLright)
                                {//----------------------------------------------- →
                                    if(SGameMgr.Ky.Card[0].Data.Flag){
                                        //[♪] レバー音
                                        ssPlaySe(BUTONSE_LEVER);
                                        SGameMgr.Player.AnswerIndex = 0;
                                    }else
                                    if(SGameMgr.Ky.Card[1].Data.Flag){
                                        //[♪] レバー音
                                        ssPlaySe(BUTONSE_LEVER);
                                        SGameMgr.Player.AnswerIndex = 1;
                                    }else{
                                        
                                    }
                                }else
                                if(JstPad & PADLleft)
                                {//----------------------------------------------- ←
                                    if(SGameMgr.Ky.Card[1].Data.Flag){
                                        //[♪] レバー音
                                        ssPlaySe(BUTONSE_LEVER);
                                        SGameMgr.Player.AnswerIndex = 1;
                                    }else
                                    if(SGameMgr.Ky.Card[0].Data.Flag){
                                        //[♪] レバー音
                                        ssPlaySe(BUTONSE_LEVER);
                                        SGameMgr.Player.AnswerIndex = 0;
                                    }else{
                                        
                                    }
                                }else
                                if(JstPad & PADLup)
                                {//----------------------------------------------- ↑
                                    if(SGameMgr.Ky.Card[0].Data.Flag){
                                        //[♪] レバー音
                                        ssPlaySe(BUTONSE_LEVER);
                                        SGameMgr.Player.AnswerIndex = 0;
                                    }else{
                                        
                                    }
                                }else{
                                    
                                }
                                break;
                            default:
                        }
                    }else
                    {//----STAR
                    //  FntPrint("INDEX:[%d]",SGameMgr.Player.AnswerIndex);
                        dirindex    = 0;
                        switch(SGameMgr.Player.AnswerIndex)
                        {
                            //--------------------------------------------------------------------0
                            case 0:
                                if(JstPad & PADLup)
                                {//----------------------------------------------- ↑
                                    if(SGameMgr.Ky.Card[3].Data.Flag){
                                        //[♪] レバー音
                                        ssPlaySe(BUTONSE_LEVER);
                                        SGameMgr.Player.AnswerIndex = 3;
                                    }
                                }else
                                if(JstPad & PADLdown)
                                {//----------------------------------------------- ↓
                                    if(SGameMgr.Ky.Card[3].Data.Flag){
                                        //[♪] レバー音
                                        ssPlaySe(BUTONSE_LEVER);
                                        SGameMgr.Player.AnswerIndex = 3;
                                    }
                                }else
                                if(JstPad & PADLleft)
                                {//----------------------------------------------- ←
                                    for(dirindex=1;dirindex<EFFECTIVE_CARD_STAR_NUM;dirindex++){
                                        if(SGameMgr.Ky.Card[(SGameMgr.Player.AnswerIndex+ConvertTable[dirindex])%EFFECTIVE_CARD_STAR_NUM].Data.Flag){
                                            SGameMgr.Player.AnswerIndex = (SGameMgr.Player.AnswerIndex+ConvertTable[dirindex])%EFFECTIVE_CARD_STAR_NUM;
                                            //[♪] レバー音
                                            ssPlaySe(BUTONSE_LEVER);
                                            break;
                                        }else{
                                            continue;
                                        }
                                    }
                                }else
                                if(JstPad & PADLright)
                                {//----------------------------------------------- →
                                    for(dirindex=1;dirindex<EFFECTIVE_CARD_STAR_NUM;dirindex++){
                                        if(SGameMgr.Ky.Card[(SGameMgr.Player.AnswerIndex+dirindex)%EFFECTIVE_CARD_STAR_NUM].Data.Flag){
                                            SGameMgr.Player.AnswerIndex = (SGameMgr.Player.AnswerIndex+dirindex)%EFFECTIVE_CARD_STAR_NUM;
                                            //[♪] レバー音
                                            ssPlaySe(BUTONSE_LEVER);
                                            break;
                                        }else{
                                            continue;
                                        }
                                    }
                                }else{
                                    
                                }
                                
                                break;
                            //--------------------------------------------------------------------1
                            case 1:
                                if(JstPad & PADLup)
                                {//----------------------------------------------- ↑
                                    if(SGameMgr.Ky.Card[4].Data.Flag){
                                        //[♪] レバー音
                                        ssPlaySe(BUTONSE_LEVER);
                                        SGameMgr.Player.AnswerIndex = 4;
                                    }
                                }else
                                if(JstPad & PADLdown)
                                {//----------------------------------------------- ↓
                                    if(SGameMgr.Ky.Card[4].Data.Flag){
                                        //[♪] レバー音
                                        ssPlaySe(BUTONSE_LEVER);
                                        SGameMgr.Player.AnswerIndex = 4;
                                    }
                                }else
                                if(JstPad & PADLleft)
                                {//----------------------------------------------- ←
                                    for(dirindex=1;dirindex<EFFECTIVE_CARD_STAR_NUM;dirindex++){
                                        if(SGameMgr.Ky.Card[(SGameMgr.Player.AnswerIndex+ConvertTable[dirindex])%EFFECTIVE_CARD_STAR_NUM].Data.Flag){
                                            SGameMgr.Player.AnswerIndex = (SGameMgr.Player.AnswerIndex+ConvertTable[dirindex])%EFFECTIVE_CARD_STAR_NUM;
                                            //[♪] レバー音
                                            ssPlaySe(BUTONSE_LEVER);
                                            break;
                                        }else{
                                            continue;
                                        }
                                    }
                                }else
                                if(JstPad & PADLright)
                                {//----------------------------------------------- →
                                    for(dirindex=1;dirindex<EFFECTIVE_CARD_STAR_NUM;dirindex++){
                                        if(SGameMgr.Ky.Card[(SGameMgr.Player.AnswerIndex+dirindex)%EFFECTIVE_CARD_STAR_NUM].Data.Flag){
                                            SGameMgr.Player.AnswerIndex = (SGameMgr.Player.AnswerIndex+dirindex)%EFFECTIVE_CARD_STAR_NUM;
                                            //[♪] レバー音
                                            ssPlaySe(BUTONSE_LEVER);
                                            break;
                                        }else{
                                            continue;
                                        }
                                    }
                                }else{
                                    
                                }
                                
                                break;
                            //--------------------------------------------------------------------2
                            case 2:
                                if(JstPad & PADLup)
                                {//----------------------------------------------- ↑
                                    
                                }else
                                if(JstPad & PADLdown)
                                {//----------------------------------------------- ↓
                                    
                                }else
                                if(JstPad & PADLleft)
                                {//----------------------------------------------- ←
                                    for(dirindex=1;dirindex<EFFECTIVE_CARD_STAR_NUM;dirindex++){
                                        if(SGameMgr.Ky.Card[(SGameMgr.Player.AnswerIndex+ConvertTable[dirindex])%EFFECTIVE_CARD_STAR_NUM].Data.Flag){
                                            SGameMgr.Player.AnswerIndex = (SGameMgr.Player.AnswerIndex+ConvertTable[dirindex])%EFFECTIVE_CARD_STAR_NUM;
                                            //[♪] レバー音
                                            ssPlaySe(BUTONSE_LEVER);
                                            break;
                                        }else{
                                            continue;
                                        }
                                    }
                                }else
                                if(JstPad & PADLright)
                                {//----------------------------------------------- →
                                    for(dirindex=1;dirindex<EFFECTIVE_CARD_STAR_NUM;dirindex++){
                                        if(SGameMgr.Ky.Card[(SGameMgr.Player.AnswerIndex+dirindex)%EFFECTIVE_CARD_STAR_NUM].Data.Flag){
                                            SGameMgr.Player.AnswerIndex = (SGameMgr.Player.AnswerIndex+dirindex)%EFFECTIVE_CARD_STAR_NUM;
                                            //[♪] レバー音
                                            ssPlaySe(BUTONSE_LEVER);
                                            break;
                                        }else{
                                            continue;
                                        }
                                    }
                                }else{
                                    
                                }
                                
                                break;
                            //--------------------------------------------------------------------3
                            case 3:
                                if(JstPad & PADLup)
                                {//----------------------------------------------- ↑
                                    if(SGameMgr.Ky.Card[0].Data.Flag){
                                        //[♪] レバー音
                                        ssPlaySe(BUTONSE_LEVER);
                                        SGameMgr.Player.AnswerIndex = 0;
                                    }
                                }else
                                if(JstPad & PADLdown)
                                {//----------------------------------------------- ↓
                                    if(SGameMgr.Ky.Card[0].Data.Flag){
                                        //[♪] レバー音
                                        ssPlaySe(BUTONSE_LEVER);
                                        SGameMgr.Player.AnswerIndex = 0;
                                    }
                                }else
                                if(JstPad & PADLleft)
                                {//----------------------------------------------- ←
                                    for(dirindex=1;dirindex<EFFECTIVE_CARD_STAR_NUM;dirindex++){
                                        if(SGameMgr.Ky.Card[(SGameMgr.Player.AnswerIndex+ConvertTable[dirindex])%EFFECTIVE_CARD_STAR_NUM].Data.Flag){
                                            SGameMgr.Player.AnswerIndex = (SGameMgr.Player.AnswerIndex+ConvertTable[dirindex])%EFFECTIVE_CARD_STAR_NUM;
                                            //[♪] レバー音
                                            ssPlaySe(BUTONSE_LEVER);
                                            break;
                                        }else{
                                            continue;
                                        }
                                    }
                                }else
                                if(JstPad & PADLright)
                                {//----------------------------------------------- →
                                    for(dirindex=1;dirindex<EFFECTIVE_CARD_STAR_NUM;dirindex++){
                                        if(SGameMgr.Ky.Card[(SGameMgr.Player.AnswerIndex+dirindex)%EFFECTIVE_CARD_STAR_NUM].Data.Flag){
                                            SGameMgr.Player.AnswerIndex = (SGameMgr.Player.AnswerIndex+dirindex)%EFFECTIVE_CARD_STAR_NUM;
                                            //[♪] レバー音
                                            ssPlaySe(BUTONSE_LEVER);
                                            break;
                                        }else{
                                            continue;
                                        }
                                    }
                                }else{
                                    
                                }
                                
                                break;
                            //--------------------------------------------------------------------4
                            case 4:
                                if(JstPad & PADLup)
                                {//----------------------------------------------- ↑
                                    if(SGameMgr.Ky.Card[1].Data.Flag){
                                        //[♪] レバー音
                                        ssPlaySe(BUTONSE_LEVER);
                                        SGameMgr.Player.AnswerIndex = 1;
                                    }
                                }else
                                if(JstPad & PADLdown)
                                {//----------------------------------------------- ↓
                                    if(SGameMgr.Ky.Card[1].Data.Flag){
                                        //[♪] レバー音
                                        ssPlaySe(BUTONSE_LEVER);
                                        SGameMgr.Player.AnswerIndex = 1;
                                    }
                                }else
                                if(JstPad & PADLleft)
                                {//----------------------------------------------- ←
                                    for(dirindex=1;dirindex<EFFECTIVE_CARD_STAR_NUM;dirindex++){
                                        if(SGameMgr.Ky.Card[(SGameMgr.Player.AnswerIndex+ConvertTable[dirindex])%EFFECTIVE_CARD_STAR_NUM].Data.Flag){
                                            SGameMgr.Player.AnswerIndex = (SGameMgr.Player.AnswerIndex+ConvertTable[dirindex])%EFFECTIVE_CARD_STAR_NUM;
                                            //[♪] レバー音
                                            ssPlaySe(BUTONSE_LEVER);
                                            break;
                                        }else{
                                            continue;
                                        }
                                    }
                                }else
                                if(JstPad & PADLright)
                                {//----------------------------------------------- →
                                    for(dirindex=1;dirindex<EFFECTIVE_CARD_STAR_NUM;dirindex++){
                                        if(SGameMgr.Ky.Card[(SGameMgr.Player.AnswerIndex+dirindex)%EFFECTIVE_CARD_STAR_NUM].Data.Flag){
                                            SGameMgr.Player.AnswerIndex = (SGameMgr.Player.AnswerIndex+dirindex)%EFFECTIVE_CARD_STAR_NUM;
                                            //[♪] レバー音
                                            ssPlaySe(BUTONSE_LEVER);
                                            break;
                                        }else{
                                            continue;
                                        }
                                    }
                                }else{
                                    
                                }

                                break;

//                          case 0:
//                              if(JstPad & PADLright)
//                              {//----------------------------------------------- →
//                                  //[♪] レバー音
//                                  ssPlaySe(BUTONSE_LEVER);
//                                  
//                                  if(SGameMgr.Ky.Card[1].Data.Flag){
//                                      SGameMgr.Player.AnswerIndex = 1;
//                                  }else
//                                  if(SGameMgr.Ky.Card[2].Data.Flag){
//                                      SGameMgr.Player.AnswerIndex = 2;
//                                  }else
//                                  if(SGameMgr.Ky.Card[4].Data.Flag){
//                                      SGameMgr.Player.AnswerIndex = 4;
//                                  }else{
//                                  }
//                              }else
//                              if(JstPad & PADLdown)
//                              {//----------------------------------------------- ↓
//                                  //[♪] レバー音
//                                  ssPlaySe(BUTONSE_LEVER);
//                                  
//                                  if(SGameMgr.Ky.Card[3].Data.Flag){
//                                      SGameMgr.Player.AnswerIndex = 3;
//                                  }else
//                                  if(SGameMgr.Ky.Card[4].Data.Flag){
//                                      SGameMgr.Player.AnswerIndex = 4;
//                                  }else{
//                                  }
//                              }else{
//                                  
//                              }
//                              break;
//                          case 1:
//                              if(JstPad & PADLleft)
//                              {//----------------------------------------------- ←
//                                  //[♪] レバー音
//                                  ssPlaySe(BUTONSE_LEVER);
//                                  
//                                  if(SGameMgr.Ky.Card[0].Data.Flag){
//                                      SGameMgr.Player.AnswerIndex = 0;
//                                  }else
//                                  if(SGameMgr.Ky.Card[3].Data.Flag){
//                                      SGameMgr.Player.AnswerIndex = 3;
//                                  }else{
//                                  }
//                              }else
//                              if(JstPad & PADLright)
//                              {//----------------------------------------------- →
//                                  //[♪] レバー音
//                                  ssPlaySe(BUTONSE_LEVER);
//                                  
//                                  if(SGameMgr.Ky.Card[2].Data.Flag){
//                                      SGameMgr.Player.AnswerIndex = 2;
//                                  }else{
//                                  }
//                              }else
//                              if(JstPad & PADLdown)
//                              {//----------------------------------------------- ↓
//                                  //[♪] レバー音
//                                  ssPlaySe(BUTONSE_LEVER);
//                                  
//                                  if(SGameMgr.Ky.Card[4].Data.Flag){
//                                      SGameMgr.Player.AnswerIndex = 4;
//                                  }else
//                                  if(SGameMgr.Ky.Card[3].Data.Flag){
//                                      SGameMgr.Player.AnswerIndex = 3;
//                                  }else{
//                                  }
//                              }else{
//                                  
//                              }
//                              break;
//                          case 2:
//                              if(JstPad & PADLleft)
//                              {//----------------------------------------------- ←
//                                  //[♪] レバー音
//                                  ssPlaySe(BUTONSE_LEVER);
//                                  
//                                  if(SGameMgr.Ky.Card[1].Data.Flag){
//                                      SGameMgr.Player.AnswerIndex = 1;
//                                  }else
//                                  if(SGameMgr.Ky.Card[0].Data.Flag){
//                                      SGameMgr.Player.AnswerIndex = 0;
//                                  }else
//                                  if(SGameMgr.Ky.Card[4].Data.Flag){
//                                      SGameMgr.Player.AnswerIndex = 4;
//                                  }else
//                                  if(SGameMgr.Ky.Card[3].Data.Flag){
//                                      SGameMgr.Player.AnswerIndex = 3;
//                                  }else{
//                                  }
//                              }else
//                              if(JstPad & PADLdown)
//                              {//----------------------------------------------- ↓
//                                  //[♪] レバー音
//                                  ssPlaySe(BUTONSE_LEVER);
//                                  
//                                  if(SGameMgr.Ky.Card[4].Data.Flag){
//                                      SGameMgr.Player.AnswerIndex = 4;
//                                  }else
//                                  if(SGameMgr.Ky.Card[3].Data.Flag){
//                                      SGameMgr.Player.AnswerIndex = 3;
//                                  }else{
//                                  }
//                              }else{
//                                  
//                              }
//                              break;
//                          case 3:
//                              if(JstPad & PADLright)
//                              {//----------------------------------------------- →
//                                  //[♪] レバー音
//                                  ssPlaySe(BUTONSE_LEVER);
//                                  
//                                  if(SGameMgr.Ky.Card[4].Data.Flag){
//                                      SGameMgr.Player.AnswerIndex = 4;
//                                  }else
//                                  if(SGameMgr.Ky.Card[1].Data.Flag){
//                                      SGameMgr.Player.AnswerIndex = 1;
//                                  }else
//                                  if(SGameMgr.Ky.Card[2].Data.Flag){
//                                      SGameMgr.Player.AnswerIndex = 2;
//                                  }else{
//                                  }
//                              }else
//                              if(JstPad & PADLup)
//                              {//----------------------------------------------- ↑
//                                  //[♪] レバー音
//                                  ssPlaySe(BUTONSE_LEVER);
//                                  
//                                  if(SGameMgr.Ky.Card[0].Data.Flag){
//                                      SGameMgr.Player.AnswerIndex = 0;
//                                  }else
//                                  if(SGameMgr.Ky.Card[1].Data.Flag){
//                                      SGameMgr.Player.AnswerIndex = 1;
//                                  }else
//                                  if(SGameMgr.Ky.Card[2].Data.Flag){
//                                      SGameMgr.Player.AnswerIndex = 2;
//                                  }else{
//                                  }
//                              }else{
//                                  
//                              }
//                              break;
//                          case 4:
//                              if(JstPad & PADLleft)
//                              {//----------------------------------------------- ←
//                                  //[♪] レバー音
//                                  ssPlaySe(BUTONSE_LEVER);
//                                  
//                                  if(SGameMgr.Ky.Card[3].Data.Flag){
//                                      SGameMgr.Player.AnswerIndex = 3;
//                                  }else
//                                  if(SGameMgr.Ky.Card[0].Data.Flag){
//                                      SGameMgr.Player.AnswerIndex = 0;
//                                  }else{
//                                  }
//                              }else
//                              if(JstPad & PADLright)
//                              {//----------------------------------------------- →
//                                  //[♪] レバー音
//                                  ssPlaySe(BUTONSE_LEVER);
//                                  
//                                  if(SGameMgr.Ky.Card[2].Data.Flag){
//                                      SGameMgr.Player.AnswerIndex = 2;
//                                  }else{
//                                  }
//                              }else
//                              if(JstPad & PADLup)
//                              {//----------------------------------------------- ↑
//                                  //[♪] レバー音
//                                  ssPlaySe(BUTONSE_LEVER);
//                                  
//                                  if(SGameMgr.Ky.Card[1].Data.Flag){
//                                      SGameMgr.Player.AnswerIndex = 1;
//                                  }else
//                                  if(SGameMgr.Ky.Card[0].Data.Flag){
//                                      SGameMgr.Player.AnswerIndex = 0;
//                                  }else
//                                  if(SGameMgr.Ky.Card[2].Data.Flag){
//                                      SGameMgr.Player.AnswerIndex = 2;
//                                  }else{
//                                  }
//                              }else{
//                                  
//                              }
//                              break;
                            default:
                        }
                    }
                    
                    
                    if(SGameMgr.Ky.Card[SGameMgr.Player.AnswerIndex].Data.Flag != 0)
                    {//カードが生きていれば
                        if(JstPad & PADRright){
                            //KYのカードタスクのステータス変更
                            SGameMgr.Ky.Card[SGameMgr.Player.AnswerIndex].Character.Status = CARD_RISE;
                            
                            //プレイヤーステータス変更：待ちへ
                            SGameMgr.Player.Character.Status    = PLAYER_WAIT;
                            
                            //[♪]決定
                            ssPlaySe(BUTONSE_MARU);
                            
                            //[♪]カード上昇音
                            ssPlaySe(SEES_SE_06);
                        }
                    }
                    
                    break;
                default:
            }
            
            SGameMgr.Player.Character.Pos.x = KyCardPosTable[SGameMgr.Player.CardType][SGameMgr.Player.AnswerIndex].x;
            SGameMgr.Player.Character.Pos.y = KyCardPosTable[SGameMgr.Player.CardType][SGameMgr.Player.AnswerIndex].y;
            
            if(SGameMgr.Player.Character.Status == PLAYER_SELECT){
                GameMgr.WaitFlag = OFF;         // iwasawa Correction (2003/4/27)
                //----描画
                SpData.No       = SGameMgr.Player.Character.Anm.Data.no;    //インデックス番号
                SpData.PosX     = SGameMgr.Player.Character.Pos.x+SGameMgr.Player.Character.OPos.x;         //X位置
                SpData.PosY     = SGameMgr.Player.Character.Pos.y+SGameMgr.Player.Character.OPos.y;         //Y位置
                SpData.PosZ     = SGameMgr.Player.Character.Pos.z;          //優先順位
                SpData.ScaleX   = SCALE10;                                  //スケールX
                SpData.ScaleY   = SCALE10;                                  //スケールY
                SpData.Rotate   = ROTATE000;                                //回転角
                SpData.Reverse  = NOREVERS;                                 //反転コード
                DrawSprite( &SpData );                                      //スプライト描画
            }
            else{           // iwasawa Correction (2003/4/27)
                GameMgr.WaitFlag = ON;
            }
            
            break;
        //----------------------------------------------------------------タスク終了
        case TASK_MODE_EXIT:
            
            //自分を削除
            ExitTask(ip_task->id);
            break;
        default:
    }

    return TRUE;
}




//-----------------------------------------------------------------------------
//  関数名  :DrTask
//
//  work    :博士タスク
//  in      :TASK*      タスクポインタ
//  out     :TRUE
//  note    :CardCastTaskの後で処理
//-----------------------------------------------------------------------------
static int DrTask(TASK* ip_task)
{
    SPRITE_DATA SpData;
    int i,count,lpc,cardtype,rval,DrCardIndex;


    switch(ip_task->mode)
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //next MAIN
            ip_task->mode       = TASK_MODE_MAIN;
            
            //----初期化
            SGameMgr.Dr.AnmBase                 = DR_ANM_BASE_WAIT;
            SGameMgr.Dr.Character.Status        = CAST_MOVE;
            SGameMgr.Dr.Character.Anm.Index     = 0;
            SGameMgr.Dr.Character.Anm.Data.no   = DrGameSpriteTable[SGameMgr.Dr.AnmBase + SGameMgr.Dr.Character.Anm.Index].No;
            SGameMgr.Dr.Character.Anm.Data.wt   = 0;
            SGameMgr.Dr.Character.Pos.x         = 46;
            SGameMgr.Dr.Character.Pos.y         = 0;
            SGameMgr.Dr.Character.Pos.z         = PRIORITY_CAST;
            SGameMgr.Dr.Character.OPos.x        = DrGameSpriteTable[SGameMgr.Dr.AnmBase + SGameMgr.Dr.Character.Anm.Index].Ofx;
            SGameMgr.Dr.Character.OPos.y        = DrGameSpriteTable[SGameMgr.Dr.AnmBase + SGameMgr.Dr.Character.Anm.Index].Ofy;
            SGameMgr.Dr.Character.OPos.z        = 0;
            SGameMgr.Dr.Character.Spd.dx        = 0;
            SGameMgr.Dr.Character.Spd.dy        = 0;
            SGameMgr.Dr.Character.Spd.sx        = 0;
            SGameMgr.Dr.Character.Spd.sy        = 0;
            SGameMgr.Dr.Timer                   = 0;

            break;
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:
            switch(SGameMgr.Dr.Character.Status)
            {
                //--------------------------------------------待ち
                case CAST_WAIT:
                    
                    break;
                //--------------------------------------------移動
                case CAST_MOVE:
                    //----シーソーオフセット
                    SGameMgr.Dr.Character.Pos.y = SGameMgr.Seesaw.L_Base.Pos.y + SGameMgr.Seesaw.L_Base.OPos.y;
                    break;
                //--------------------------------------------上昇
                case CAST_RISE:
                    SGameMgr.Dr.Character.Pos.y += CAST_RISE_SPEED_Y;
                    
                    if(SGameMgr.Dr.Character.Pos.y < CAST_RISE_STOP_Y){
                        //ステータス変更：空中で待ちへ
                        SGameMgr.Dr.Character.Status    = CAST_FLY;
                        SGameMgr.Dr.Timer               = 0;
                        
                        //相手のアニメを変更：喜びへ
                        SGameMgr.Ky.AnmBase                 = KY_ANM_BASE_PLEASURE;
                        SGameMgr.Ky.Character.Anm.Data.wt   = 0;
                        SGameMgr.Ky.Character.Anm.Index     = 0;
                        
                        //相手のカードのステータスを変更：飛んでいくへ
                        SGameMgr.Ky.Card[SGameMgr.Player.AnswerIndex].Character.Status = CARD_FLY;
                    }
                    break;
                //--------------------------------------------空中で待ち
                case CAST_FLY:
                    if(++SGameMgr.Dr.Timer > CAST_FLY_WAIT_TIME){
                        SGameMgr.Dr.Timer               = 0;
                        //ステータス変更：下降へ
                        SGameMgr.Dr.Character.Status    = CAST_FALL;
                        
                        //アニメ変更：待ちへ
                        SGameMgr.Dr.AnmBase                 = DR_ANM_BASE_FALL;
                        SGameMgr.Dr.Character.Anm.Data.wt   = 0;
                        SGameMgr.Dr.Character.Anm.Index     = 0;
                        
                        //自分のカード削除
                        DrCardIndex                                     = AsSelectCardIndexTable[SGameMgr.PlayLevel][SGameMgr.As.SelectOrderIndex][SGameMgr.As.SelectIndex];
                        SGameMgr.Dr.Card[DrCardIndex].Character.Status  = CARD_DEATH;
                        SGameMgr.Dr.Card[DrCardIndex].Data.Flag         = 0;
                        SGameMgr.Dr.Card[DrCardIndex].DrawFlag          = 0;
                    }
                    
                    break;
                //--------------------------------------------下降
                case CAST_FALL:
                    SGameMgr.Dr.Character.Pos.y += CAST_FALL_SPEED_Y;
                    if(SGameMgr.Dr.Character.Pos.y >= SGameMgr.Seesaw.L_Base.Pos.y - SEESAW_DISTANCE_04){
                        //ステータス変更：移動へ
                        SGameMgr.Dr.Character.Status    = CAST_MOVE;
                        
                        //アニメ変更：待ちへ
                        SGameMgr.Dr.AnmBase                 = DR_ANM_BASE_WAIT;
                        SGameMgr.Dr.Character.Anm.Data.wt   = 0;
                        SGameMgr.Dr.Character.Anm.Index     = 0;
                        
                        //シーソーステータス変更：
                        SGameMgr.Seesaw.Status          = SEESAW_RETURN_DR;
                        SGameMgr.Seesaw.MoveIndex       = 0;
                        SGameMgr.Seesaw.MoveCount       = SeesawReturnDrMoveData[SGameMgr.Seesaw.MoveIndex].MoveCount;
                        SGameMgr.Seesaw.MoveDirect      = SeesawReturnDrMoveData[SGameMgr.Seesaw.MoveIndex].MoveDirect;
                        SGameMgr.Seesaw.MoveWaitTimer   = 0;
                        SGameMgr.Seesaw.L_Base.OPos.y   = -8;
                        SGameMgr.Seesaw.R_Base.OPos.y   = 8;
                    
                        //[♪]キャスト台座へ着地
                        ssPlaySe(SEES_SE_07);
                    }
                    
                    break;
                default:
            }
            
            //----
    //      FntPrint("KPOS:(%3d,%3d)\n",SGameMgr.Dr.Character.Pos.x,SGameMgr.Dr.Character.Pos.y);

            if(++SGameMgr.Dr.Character.Anm.Data.wt > CAST_ANM_WAIT_TIME)
            {
                SGameMgr.Dr.Character.Anm.Data.wt   = 0;
                SGameMgr.Dr.Character.Anm.Index     ^= 1;
                SGameMgr.Dr.Character.Anm.Data.no   = DrGameSpriteTable[SGameMgr.Dr.AnmBase + SGameMgr.Dr.Character.Anm.Index].No;
                SGameMgr.Dr.Character.OPos.x        = DrGameSpriteTable[SGameMgr.Dr.AnmBase + SGameMgr.Dr.Character.Anm.Index].Ofx;
                SGameMgr.Dr.Character.OPos.y        = DrGameSpriteTable[SGameMgr.Dr.AnmBase + SGameMgr.Dr.Character.Anm.Index].Ofy;
            }

            //----描画
            SpData.No       = SGameMgr.Dr.Character.Anm.Data.no;                            //インデックス番号
            SpData.PosX     = SGameMgr.Dr.Character.Pos.x + SGameMgr.Dr.Character.OPos.x;   //X位置
            SpData.PosY     = SGameMgr.Dr.Character.Pos.y + SGameMgr.Dr.Character.OPos.y;   //Y位置
            SpData.PosZ     = SGameMgr.Dr.Character.Pos.z;                                  //優先順位
            SpData.ScaleX   = SCALE10;                                                      //スケールX
            SpData.ScaleY   = SCALE10;                                                      //スケールY
            SpData.Rotate   = ROTATE000;                                                    //回転角
            SpData.Reverse  = NOREVERS;                                                     //反転コード
            DrawSprite( &SpData );                                                          //スプライト描画
            
            break;
        //----------------------------------------------------------------タスク終了
        case TASK_MODE_EXIT:
            
            //自分を削除
            ExitTask(ip_task->id);
            break;
        default:
    }

    return TRUE;
}


//-----------------------------------------------------------------------------
//  関数名  :KyTask
//
//  work    :カロリーヌタスク
//  in      :TASK*      タスクポインタ
//  out     :TRUE
//  note    :CardCastTaskの後で処理
//-----------------------------------------------------------------------------
static int KyTask(TASK* ip_task)
{
    SPRITE_DATA SpData;
    int i,count,lpc,drno,KyCardIndex;

    switch(ip_task->mode)
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //next MAIN
            ip_task->mode       = TASK_MODE_MAIN;

            //----初期化
            SGameMgr.Ky.AnmBase                 = KY_ANM_BASE_WAIT;
            SGameMgr.Ky.Character.Status        = CAST_MOVE;
            SGameMgr.Ky.Character.Anm.Index     = 0;
            SGameMgr.Ky.Character.Anm.Data.no   = KyGameSpriteTable[SGameMgr.Ky.AnmBase + SGameMgr.Ky.Character.Anm.Index].No;
            SGameMgr.Ky.Character.Anm.Data.wt   = 0;
            SGameMgr.Ky.Character.Pos.x         = 226;
            SGameMgr.Ky.Character.Pos.y         = 0;
            SGameMgr.Ky.Character.Pos.z         = PRIORITY_CAST;
            SGameMgr.Ky.Character.OPos.x        = KyGameSpriteTable[SGameMgr.Ky.AnmBase + SGameMgr.Ky.Character.Anm.Index].Ofx;
            SGameMgr.Ky.Character.OPos.y        = KyGameSpriteTable[SGameMgr.Ky.AnmBase + SGameMgr.Ky.Character.Anm.Index].Ofy;
            SGameMgr.Ky.Character.OPos.z        = 0;
            SGameMgr.Ky.Character.Spd.dx        = 0;
            SGameMgr.Ky.Character.Spd.dy        = 0;
            SGameMgr.Ky.Character.Spd.sx        = 0;
            SGameMgr.Ky.Character.Spd.sy        = 0;
            SGameMgr.Ky.Timer                   = 0;
            break;
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:
            switch(SGameMgr.Ky.Character.Status)
            {
                //--------------------------------------------待ち
                case CAST_WAIT:
                    
                    break;
                //--------------------------------------------移動
                case CAST_MOVE:
                    //----シーソーオフセット
                    SGameMgr.Ky.Character.Pos.y = SGameMgr.Seesaw.R_Base.Pos.y + SGameMgr.Seesaw.R_Base.OPos.y;
                    break;
                //--------------------------------------------上昇
                case CAST_RISE:
                    SGameMgr.Ky.Character.Pos.y += CAST_RISE_SPEED_Y;
                    
                    if(SGameMgr.Ky.Character.Pos.y < CAST_RISE_STOP_Y){
                        //DRステータス変更：空中待ちへ
                        SGameMgr.Ky.Character.Status    = CAST_FLY;
                        SGameMgr.Ky.Timer               = 0;
                        
                        //相手のアニメを変更：喜びへ
                        SGameMgr.Dr.AnmBase = DR_ANM_BASE_PLEASURE;
                        SGameMgr.Dr.Character.Anm.Data.wt   = 0;
                        SGameMgr.Dr.Character.Anm.Index     = 0;
                        
                        //相手のカードのステータス変更：飛んでいくへ
                        SGameMgr.Dr.Card[ AsSelectCardIndexTable[SGameMgr.PlayLevel][SGameMgr.As.SelectOrderIndex][SGameMgr.As.SelectIndex]].Character.Status = CARD_FLY;
                    }
                    break;
                //--------------------------------------------空中で待ち
                case CAST_FLY:
                    if(++SGameMgr.Ky.Timer > CAST_FLY_WAIT_TIME){
                        SGameMgr.Ky.Timer               = 0;
                        //ステータス変更：下降へ
                        SGameMgr.Ky.Character.Status    = CAST_FALL;
                        
                        //アニメ変更：落下へ
                        SGameMgr.Ky.AnmBase             = KY_ANM_BASE_FALL;
                        SGameMgr.Ky.Character.Anm.Data.wt   = 0;
                        SGameMgr.Ky.Character.Anm.Index     = 0;
                        
                        //自分のカード削除
                        KyCardIndex                                     = SGameMgr.Player.AnswerIndex;
                        SGameMgr.Ky.Card[KyCardIndex].Character.Status  = CARD_DEATH;
                        SGameMgr.Ky.Card[KyCardIndex].Data.Flag         = 0;
                        SGameMgr.Ky.Card[KyCardIndex].DrawFlag          = 0;
                    }
                    
                    break;
                //--------------------------------------------下降
                case CAST_FALL:
                    SGameMgr.Ky.Character.Pos.y += CAST_FALL_SPEED_Y;
                    if(SGameMgr.Ky.Character.Pos.y >= SGameMgr.Seesaw.R_Base.Pos.y - SEESAW_DISTANCE_04){
                        //ステータス変更：移動へ
                        SGameMgr.Ky.Character.Status    = CAST_MOVE;
                        
                        //アニメ変更：待ちへ
                        SGameMgr.Ky.AnmBase                 = KY_ANM_BASE_WAIT;
                        SGameMgr.Ky.Character.Anm.Data.wt   = 0;
                        SGameMgr.Ky.Character.Anm.Index     = 0;
                        
                        //シーソーステータス変更：
                        SGameMgr.Seesaw.Status          = SEESAW_RETURN_KY;
                        SGameMgr.Seesaw.MoveIndex       = 0;
                        SGameMgr.Seesaw.MoveCount       = SeesawReturnKyMoveData[SGameMgr.Seesaw.MoveIndex].MoveCount;
                        SGameMgr.Seesaw.MoveDirect      = SeesawReturnKyMoveData[SGameMgr.Seesaw.MoveIndex].MoveDirect;
                        SGameMgr.Seesaw.MoveWaitTimer   = 0;
                        SGameMgr.Seesaw.L_Base.OPos.y   = 8;
                        SGameMgr.Seesaw.R_Base.OPos.y   = -8;

                        //[♪]キャスト台座へ着地
                        ssPlaySe(SEES_SE_07);
                    }
                    break;
                default:
            }
            //----
    //      FntPrint("KPOS:(%3d,%3d)\n",SGameMgr.Ky.Character.Pos.x,SGameMgr.Ky.Character.Pos.y);


            if(++SGameMgr.Ky.Character.Anm.Data.wt > CAST_ANM_WAIT_TIME)
            {
                SGameMgr.Ky.Character.Anm.Data.wt   = 0;
                SGameMgr.Ky.Character.Anm.Index     ^= 1;
                SGameMgr.Ky.Character.Anm.Data.no   = KyGameSpriteTable[SGameMgr.Ky.AnmBase + SGameMgr.Ky.Character.Anm.Index].No;
                SGameMgr.Ky.Character.OPos.x        = KyGameSpriteTable[SGameMgr.Ky.AnmBase + SGameMgr.Ky.Character.Anm.Index].Ofx;
                SGameMgr.Ky.Character.OPos.y        = KyGameSpriteTable[SGameMgr.Ky.AnmBase + SGameMgr.Ky.Character.Anm.Index].Ofy;
            }

            //----描画
            SpData.No       = SGameMgr.Ky.Character.Anm.Data.no;                            //インデックス番号
            SpData.PosX     = SGameMgr.Ky.Character.Pos.x + SGameMgr.Ky.Character.OPos.x;   //X位置
            SpData.PosY     = SGameMgr.Ky.Character.Pos.y + SGameMgr.Ky.Character.OPos.y;   //Y位置
            SpData.PosZ     = SGameMgr.Ky.Character.Pos.z;                                  //優先順位
            SpData.ScaleX   = SCALE10;                                                      //スケールX
            SpData.ScaleY   = SCALE10;                                                      //スケールY
            SpData.Rotate   = ROTATE000;                                                    //回転角
            SpData.Reverse  = NOREVERS;                                                     //反転コード
            DrawSprite( &SpData );                                                          //スプライト描画
            
            break;
        //----------------------------------------------------------------タスク終了
        case TASK_MODE_EXIT:
            
            //自分を削除
            ExitTask(ip_task->id);
            break;
        default:
    }

    return TRUE;
}


//-----------------------------------------------------------------------------
//  関数名  :AsTask
//
//  work    :アシスタントタスク
//  in      :TASK*      タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int AsTask(TASK* ip_task)
{
    SPRITE_DATA SpData;
    TASK Task;
    int i,DrCardIndex;

//  static int PartsIndex=0;


    switch(ip_task->mode)
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //next MAIN
            ip_task->mode       = TASK_MODE_MAIN;

            //----初期化
            if(SGameMgr.PlayLevel == 0){
                SGameMgr.As.EffectiveCardNum    = EFFECTIVE_CARD_BOX_NUM;
            }else{
                SGameMgr.As.EffectiveCardNum    = EFFECTIVE_CARD_STAR_NUM;
            }
            
            SGameMgr.As.AnmType                 = AS_SP_TYPE_STAND;
            SGameMgr.As.SelectIndex             = 0;
            SGameMgr.As.SelectOrderIndex        = rand()%MAX_GAME_PATTERN_NUM;
            SGameMgr.As.Timer                   = 0;
            SGameMgr.As.AnmIndex                = 0;
            SGameMgr.As.AnmBase                 = 0;
            SGameMgr.As.AnmWaitTime             = 0;
            
            SGameMgr.As.Character.Status        = AS_STAND;
            SGameMgr.As.Character.Anm.Index     = 0;
            SGameMgr.As.Character.Anm.Data.no   = 0;
            SGameMgr.As.Character.Anm.Data.wt   = 0;
            SGameMgr.As.Character.Pos.x         = 0;
            SGameMgr.As.Character.Pos.y         = 0;
            SGameMgr.As.Character.Pos.z         = PRIORITY_CAST;
            SGameMgr.As.Character.OPos.x        = 0;
            SGameMgr.As.Character.OPos.y        = 0;
            SGameMgr.As.Character.OPos.z        = 0;
            SGameMgr.As.Character.Spd.dx        = 0;
            SGameMgr.As.Character.Spd.dy        = 0;
            SGameMgr.As.Character.Spd.sx        = 0;
            SGameMgr.As.Character.Spd.sy        = 0;

            break;
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:

//          //------------------------
//          if(JstPad & PADRdown){
//              if(++PartsIndex >= 16){
//                  PartsIndex = 0;
//              }
//          }
//
//          //----パーツ描画
//          SpData.No       = AsGameSpriteTable[PartsIndex].No;         //インデックス番号
//          SpData.PosX     = 160 + AsGameSpriteTable[PartsIndex].Ofx;  //X位置
//          SpData.PosY     = AsGameSpriteTable[PartsIndex].Ofy;        //Y位置
//          SpData.PosZ     = SGameMgr.As.Character.Pos.z;              //優先順位
//          SpData.ScaleX   = SCALE10;                                  //スケールX
//          SpData.ScaleY   = SCALE10;                                  //スケールY
//          SpData.Rotate   = ROTATE000;                                //回転角
//          SpData.Reverse  = NOREVERS;                                 //反転コード
//          DrawSprite( &SpData );                                      //スプライト描画
//          //------------------------
//          if(JstPad & PADRright){
//              if(++SGameMgr.As.Character.Anm.Index >= 10){
//                  SGameMgr.As.Character.Anm.Index = 0;
//              }
//          }
//
//          FntPrint("TYPE_=[%2d]\n",SGameMgr.As.AnmType);
//          FntPrint("PARTS=[%2d]\n",PartsIndex);
//
//          //------------------------
//          if(JstPad & PADRup){
//              if(++SGameMgr.As.AnmType >= 10){
//                  SGameMgr.As.AnmType = 0;
//              }
//          }
            
            
    //      FntPrint("INDEX:[%d]\n",SGameMgr.As.SelectIndex);
            

            switch(SGameMgr.As.Character.Status)
            {
                //--------------------------------------------待ち
                case AS_STAND:
                    //CardCastTaskが指示するまで待つ

                    if(++SGameMgr.As.Timer >= AS_STAND_WAIT_TIME)
                    {
                        SGameMgr.As.Timer               = 0;
                        
                        //ステータス変更：左手を上げて話すへ
                        SGameMgr.As.Character.Status    = AS_SPEAK;
                        
                        //口パクアニメ
                        SGameMgr.As.AnmIndex            = 0;
                        SGameMgr.As.AnmBase             = AS_SP_TYPE_QUESTION;
                        SGameMgr.As.AnmWaitTime         = 0;
                    }
                    
                    break;
                //--------------------------------------------左手を上げて話す
                case AS_SPEAK:
                    if(++SGameMgr.As.AnmWaitTime >= AS_ANM_WAIT_TIME){
                        SGameMgr.As.AnmWaitTime = 0;
                        SGameMgr.As.AnmIndex    ^= 1;
                        SGameMgr.As.AnmType     = SGameMgr.As.AnmBase + SGameMgr.As.AnmIndex;
                    }
                    
                    if(++SGameMgr.As.Timer >= AS_SPEAK_TIME)
                    {
                        SGameMgr.As.Timer       = 0;
                        
                        //ステータス変更：左手を上げて話した後
                        SGameMgr.As.Character.Status    = AS_SPEAK_AFTER;
                        
                        //アニメセット
                        SGameMgr.As.AnmType             = AS_SP_TYPE_QUESTION;
                        
                        //カード紹介タスクへ指示を出す
                        //カードステータス変更：カードを裏返しへ
                        for(i=0;i<MAX_CARD_NUM;i++){
                            SGameMgr.CardCast.Card[i].Character.Status = CARD_CAST_TURN_OVER;
                        }
                    }
                    
                    break;
                //--------------------------------------------左手を上げて話した後
                case AS_SPEAK_AFTER:
                    //ここで待ち
                    
                    break;
                //--------------------------------------------もう一度（一指し指上げ）
                case AS_ONCE_AGAIN:
                    
                    //ここで次の選択肢へ
                    if(++SGameMgr.As.Timer >= AS_ONCE_AGAIN_TIME)
                    {
                        //ステータス変更：手を頭へ
                        SGameMgr.As.Character.Status    = AS_HAND_HEAD;
                        //アニメセット
                        SGameMgr.As.AnmType             = AS_SP_TYPE_SELECT_QUESTION_00;
                        SGameMgr.As.Timer               = 0;
                        
                        //[♪]それじゃ
                        ssPlaySe(SEES_SE_00);
                    }
                    
                    
                    break;
                //--------------------------------------------手を頭へ
                case AS_HAND_HEAD:

                    //少し待つ
                    if(++SGameMgr.As.Timer >= AS_WAIT_SELECT_CARD_TIME)
                    {
                        SGameMgr.As.Timer   = 0;

                        //ステータス変更：問題選択へ
                        SGameMgr.As.Character.Status    = AS_SELECT_QUESTION;

                        //アニメセット
                        if( SGameMgr.As.EffectiveCardNum == EFFECTIVE_CARD_BOX_NUM )
                        {//BOX
                            SGameMgr.As.AnmType = AsSelectBoxAnswerSpriteTypeTable[ AsSelectCardIndexTable[SGameMgr.PlayLevel][SGameMgr.As.SelectOrderIndex][SGameMgr.As.SelectIndex] ];
                        }else
                        {//CARD
                            SGameMgr.As.AnmType = AsSelectCardAnswerSpriteTypeTable[ AsSelectCardIndexTable[SGameMgr.PlayLevel][SGameMgr.As.SelectOrderIndex][SGameMgr.As.SelectIndex] ];
                        }

                        //[♪]ピン
                        ssPlaySe(SEES_SE_05);

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
                        Task.user[0]        = SCRIPT_LINE_1;
                        Task.user[1]        = AS_SELECT_CARD_SCRIPT_BASE;
                        Task.user[2]        = AS_SELECT_CARD_SCRIPT_NUM;
                        CreateTask(&Task);
                    }

                    break;
                //--------------------------------------------問題選択
                case AS_SELECT_QUESTION:
                    
                    if(++SGameMgr.As.Timer >= AS_SELECT_CARD_TIME)
                    {
                        SGameMgr.As.Timer   = 0;
                        //ステータス変更：手を上げるへ
                        SGameMgr.As.Character.Status    = AS_HAND_UP;
                        
                        //アニメセット
                        SGameMgr.As.AnmType             = AS_SP_TYPE_QUESTION;
                        
                        
                        //DRのカードタスクのステータス変更
                        DrCardIndex = AsSelectCardIndexTable[SGameMgr.PlayLevel][SGameMgr.As.SelectOrderIndex][SGameMgr.As.SelectIndex];
                        SGameMgr.Dr.Card[DrCardIndex].Character.Status = CARD_RISE;

                        //[♪]カード上昇音
                        ssPlaySe(SEES_SE_06);
                    }
                    
                    break;
                //--------------------------------------------手を上げる
                case AS_HAND_UP:
                    //他のタスクから変更されるためこのまま
                    
                    break;
                //--------------------------------------------終了待ち
                case AS_STAND_END:
                    break;
                default:
            }
            
            //----
            for(i=0;i<10;i++){
                if( AsGamePartsIndexTable[SGameMgr.As.AnmType][i]==-1 ) break;
                //----描画
                SpData.No       = AsGameSpriteTable[ AsGamePartsIndexTable[SGameMgr.As.AnmType][i] ].No;        //インデックス番号
                SpData.PosX     = AsGameSpriteTable[ AsGamePartsIndexTable[SGameMgr.As.AnmType][i] ].Ofx;       //X位置
                SpData.PosY     = AsGameSpriteTable[ AsGamePartsIndexTable[SGameMgr.As.AnmType][i] ].Ofy;       //Y位置
                SpData.PosZ     = SGameMgr.As.Character.Pos.z-i;        //優先順位
                SpData.ScaleX   = SCALE10;                              //スケールX
                SpData.ScaleY   = SCALE10;                              //スケールY
                SpData.Rotate   = ROTATE000;                            //回転角
                SpData.Reverse  = NOREVERS;                             //反転コード
                DrawSprite( &SpData );                                  //スプライト描画
            }
            
            break;
        //----------------------------------------------------------------タスク終了
        case TASK_MODE_EXIT:
            
            //自分を削除
            ExitTask(ip_task->id);
            break;
        default:
    }

    return TRUE;
}




//-----------------------------------------------------------------------------
//  関数名  :DrCardTask
//
//  work    :DRカードタスク
//  in      :TASK* ip_task
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int DrCardTask(TASK* ip_task)
{
    SPRITE_DATA SpData;
    TASK Task;
    int i,rval,cardtype;

    switch(ip_task->mode)
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //next MAIN
            ip_task->mode       = TASK_MODE_MAIN;
            
            //----初期化
            //----有効カード枚数
            if(SGameMgr.PlayLevel == 0){
                SGameMgr.Dr.EffectiveCardNum    = EFFECTIVE_CARD_BOX_NUM;
                cardtype                        = CARD_TYPE_BOX;
            }else{
                SGameMgr.Dr.EffectiveCardNum    = EFFECTIVE_CARD_STAR_NUM;
                cardtype                        = CARD_TYPE_STAR;
            }

            //----カード
            rval= rand() % SGameMgr.Dr.EffectiveCardNum;
            for(i=0;i<SGameMgr.Dr.EffectiveCardNum;i++)
            {
                SGameMgr.Dr.Card[i].Character.Status        = CARD_WAIT;
                SGameMgr.Dr.Card[i].Character.Anm.Index     = 0;
                SGameMgr.Dr.Card[i].Character.Anm.Data.no   = 0;
                SGameMgr.Dr.Card[i].Character.Anm.Data.wt   = 0;
                SGameMgr.Dr.Card[i].Character.Pos.x         = DrCardPosTable[cardtype][i].x;
                SGameMgr.Dr.Card[i].Character.Pos.y         = DrCardPosTable[cardtype][i].y;
                SGameMgr.Dr.Card[i].Character.Pos.z         = PRIORITY_CARD - i*2;
                SGameMgr.Dr.Card[i].Character.OPos.x        = 0;
                SGameMgr.Dr.Card[i].Character.OPos.y        = 0;
                SGameMgr.Dr.Card[i].Character.OPos.z        = 0;
                SGameMgr.Dr.Card[i].Character.Spd.dx        = 0;
                SGameMgr.Dr.Card[i].Character.Spd.dy        = 0;
                SGameMgr.Dr.Card[i].Character.Spd.sx        = 0;
                SGameMgr.Dr.Card[i].Character.Spd.sy        = 0;
                
                SGameMgr.Dr.Card[i].Data.No     = CardDeelDataTable[SGameMgr.PlayLevel][SGameMgr.CardCast.DeelSide][SGameMgr.CardCast.Index][ CardDeelDataRandomTable[SGameMgr.PlayLevel][rval][i] ];
                SGameMgr.Dr.Card[i].Data.Flag   = 1;
                SGameMgr.Dr.Card[i].Data.Side   = CARD_SIDE_TAIL;
                SGameMgr.Dr.Card[i].DrawFlag    = 0;
                SGameMgr.Dr.Card[i].Type        = cardtype;
                SGameMgr.Dr.Card[i].Timer       = 0;
            }
            
            break;
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:
            
            for(i=0;i<SGameMgr.Dr.EffectiveCardNum;i++){
                switch(SGameMgr.Dr.Card[i].Character.Status)
                {
                    //--------------------------------------------待ち
                    case CARD_WAIT:
                        break;
                    //--------------------------------------------カード選択待ち
                    case CARD_SELECT_WAIT:
                        break;
                    //--------------------------------------------上昇
                    case CARD_RISE:
                        
                        SGameMgr.Dr.Card[i].Character.Pos.y -= CARD_RISE_SPEED_Y;
                        if(SGameMgr.Dr.Card[i].Character.Pos.y < CARD_RISE_STOP_POSY){
                            //カードステータス変更：落下へ
                            SGameMgr.Dr.Card[i].Character.Status    = CARD_FALL;
                            //カードの向きを表にする
                            SGameMgr.Dr.Card[i].Data.Side           = CARD_SIDE_HEADS;
                            
                            //アニメ受けへ
                            SGameMgr.Dr.AnmBase = DR_ANM_BASE_RECEIVE;
                            
                            //位置補正
                            if(SGameMgr.Dr.Card[i].Type==CARD_TYPE_BOX)
                            {//箱
                                SGameMgr.Dr.Card[i].Character.Pos.x     = DR_BOX_RECEIVE_X;
                                SGameMgr.Dr.Card[i].Character.OPos.y    = DR_BOX_RECEIVE_OFFSET_Y;
                            }else
                            {//カード
                                SGameMgr.Dr.Card[i].Character.Pos.x     = DR_CARD_RECEIVE_X;
                                SGameMgr.Dr.Card[i].Character.OPos.y    = DR_CARD_RECEIVE_OFFSET_Y;
                            }
                        }
                        
                        break;
                    //--------------------------------------------落下
                    case CARD_FALL:
                        SGameMgr.Dr.Card[i].Character.Pos.y += CARD_FALL_SPEED_Y;
                        if(SGameMgr.Dr.Card[i].Character.Pos.y > CARD_FALL_STOP_POSY){
                            //カードステータス変更：移動（キャストと一緒）へ
                            SGameMgr.Dr.Card[i].Character.Status    = CARD_MOVE_WITH_CAST;
                            
                            //シーソーステータス変更：
                            SGameMgr.Seesaw.Status          = SEESAW_WEIGHT_HEAVY_DR;
                            SGameMgr.Seesaw.MoveIndex       = 0;
                            SGameMgr.Seesaw.MoveCount       = SeesawUpKyMoveData[SGameMgr.Seesaw.MoveIndex].MoveCount;
                            SGameMgr.Seesaw.MoveDirect      = SeesawUpKyMoveData[SGameMgr.Seesaw.MoveIndex].MoveDirect;
                            SGameMgr.Seesaw.MoveWaitTimer   = 0;
                            
                            //----位置
                            SGameMgr.Seesaw.L_Base.OPos.y   = 0;
                            SGameMgr.Seesaw.R_Base.OPos.y   = 0;
                            
                            //プレイヤーステータス変更：選択可能へ
                            SGameMgr.Player.Character.Status    = PLAYER_XA_WAIT;
                            SGameMgr.Player.WaitTimer           = GET_DA_STATUS_WAIT_TIME;
                            SGameMgr.Player.WaitFlag            = 1;
                            
                            //[♪]よいしょ
                            ssPlaySe(SEES_SE_01);
                            
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
                            Task.user[0]        = SCRIPT_LINE_1;
                            Task.user[1]        = PLAYER_SELECT_CARD_SCRIPT_BASE;
                            Task.user[2]        = PLAYER_SELECT_CARD_SCRIPT_NUM;
                            CreateTask(&Task);
                        }
                        
                        break;
                    //--------------------------------------------移動（キャストと一緒）
                    case CARD_MOVE_WITH_CAST:
                        SGameMgr.Dr.Card[i].Character.Pos.y = SGameMgr.Dr.Character.Pos.y + 
                                                                    SGameMgr.Dr.Character.OPos.y + 
                                                                        SGameMgr.Dr.Card[i].Character.OPos.y;
                        break;
                    //--------------------------------------------飛んでいく
                    case CARD_FLY:
                        
                        SGameMgr.Dr.Card[i].Character.Pos.x -= 2;
                        SGameMgr.Dr.Card[i].Character.Pos.y -= 2;
                        if( SGameMgr.Dr.Card[i].Character.Pos.y< -20){
                            SGameMgr.Dr.Card[i].Character.Status=CARD_DEATH;
                            SGameMgr.Dr.Card[i].Data.Flag   = 0;
                            SGameMgr.Dr.Card[i].DrawFlag    = 0;
                        }
                        
                        break;
                    //--------------------------------------------終了
                    case CARD_DEATH:
                    //博士タスクがここへ送ります。
                        
                        break;
                    default:
                }
                
                if(SGameMgr.Dr.Card[i].DrawFlag){
                    //----描画
                    DrawCard(   SGameMgr.Dr.Card[i].Type,
                                SGameMgr.Dr.Card[i].Data.No,
                                SGameMgr.Dr.Card[i].Data.Side,
                                SGameMgr.Dr.Card[i].Character.Pos.x,
                                SGameMgr.Dr.Card[i].Character.Pos.y,
                                SGameMgr.Dr.Card[i].Character.Pos.z);
                }
            }
            
            break;
        //----------------------------------------------------------------タスク終了
        case TASK_MODE_EXIT:
            
            //自分を削除
            ExitTask(ip_task->id);
            break;
        default:
    }

    return TRUE;
}




//-----------------------------------------------------------------------------
//  関数名  :KyCardTask
//
//  work    :Kyカードタスク
//  in      :TASK* ip_task
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int KyCardTask(TASK* ip_task)
{
    SPRITE_DATA SpData;
    TASK Task;
    int i,rval,cardtype;


    switch(ip_task->mode)
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //next MAIN
            ip_task->mode       = TASK_MODE_MAIN;
            
            //----初期化
            //----有効カード枚数
            if(SGameMgr.PlayLevel == 0){
                SGameMgr.Ky.EffectiveCardNum    = EFFECTIVE_CARD_BOX_NUM;
                cardtype                        = CARD_TYPE_BOX;
            }else{
                SGameMgr.Ky.EffectiveCardNum    = EFFECTIVE_CARD_STAR_NUM;
                cardtype                        = CARD_TYPE_STAR;
            }

            //----カード
            rval= rand() % SGameMgr.Ky.EffectiveCardNum;
            for(i=0;i<SGameMgr.Ky.EffectiveCardNum;i++)
            {
                SGameMgr.Ky.Card[i].Character.Status        = CARD_WAIT;
                SGameMgr.Ky.Card[i].Character.Anm.Index     = 0;
                SGameMgr.Ky.Card[i].Character.Anm.Data.no   = 0;
                SGameMgr.Ky.Card[i].Character.Anm.Data.wt   = 0;
                SGameMgr.Ky.Card[i].Character.Pos.x         = KyCardPosTable[cardtype][i].x;
                SGameMgr.Ky.Card[i].Character.Pos.y         = KyCardPosTable[cardtype][i].y;
                SGameMgr.Ky.Card[i].Character.Pos.z         = PRIORITY_CARD - i*2;
                SGameMgr.Ky.Card[i].Character.OPos.x        = 0;
                SGameMgr.Ky.Card[i].Character.OPos.y        = 0;
                SGameMgr.Ky.Card[i].Character.OPos.z        = 0;
                SGameMgr.Ky.Card[i].Character.Spd.dx        = 0;
                SGameMgr.Ky.Card[i].Character.Spd.dy        = 0;
                SGameMgr.Ky.Card[i].Character.Spd.sx        = 0;
                SGameMgr.Ky.Card[i].Character.Spd.sy        = 0;
                
                SGameMgr.Ky.Card[i].Data.No     = CardDeelDataTable[SGameMgr.PlayLevel][SGameMgr.CardCast.DeelSide^1][SGameMgr.CardCast.Index][ CardDeelDataRandomTable[SGameMgr.PlayLevel][rval][i] ];
                SGameMgr.Ky.Card[i].Data.Flag   = 1;
                SGameMgr.Ky.Card[i].Data.Side   = CARD_SIDE_HEADS;
                SGameMgr.Ky.Card[i].DrawFlag    = 0;
                SGameMgr.Ky.Card[i].Type        = cardtype;
                SGameMgr.Ky.Card[i].Timer       = 0;
            }


            break;
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:
            
            for(i=0;i<SGameMgr.Ky.EffectiveCardNum;i++){
                switch(SGameMgr.Ky.Card[i].Character.Status)
                {
                    //--------------------------------------------待ち
                    case CARD_WAIT:
                        break;
                    //--------------------------------------------カード選択待ち
                    case CARD_SELECT_WAIT:
                        break;
                    //--------------------------------------------上昇
                    case CARD_RISE:
                        SGameMgr.Ky.Card[i].Character.Pos.y -= CARD_RISE_SPEED_Y;
                        if(SGameMgr.Ky.Card[i].Character.Pos.y < CARD_RISE_STOP_POSY){
                            //ステータス変更:落下へ
                             SGameMgr.Ky.Card[i].Character.Status   = CARD_FALL;
                                    
                            //アニメ受けへ
                            SGameMgr.Ky.AnmBase = KY_ANM_BASE_RECEIVE;
                            
                            //位置補正
                             if(SGameMgr.Ky.Card[i].Type ==CARD_TYPE_BOX)
                             {//BOX
                                SGameMgr.Ky.Card[i].Character.Pos.x     = KY_BOX_RECEIVE_X;
                                SGameMgr.Ky.Card[i].Character.OPos.y    = KY_BOX_RECEIVE_OFFSET_Y;
                             }else
                             {//CARD
                                SGameMgr.Ky.Card[i].Character.Pos.x     = KY_CARD_RECEIVE_X;
                                SGameMgr.Ky.Card[i].Character.OPos.y    = KY_CARD_RECEIVE_OFFSET_Y;
                             }
                        }
                        break;
                    //--------------------------------------------落下
                    case CARD_FALL:
                        SGameMgr.Ky.Card[i].Character.Pos.y += CARD_FALL_SPEED_Y;
                        if(SGameMgr.Ky.Card[i].Character.Pos.y > CARD_FALL_STOP_POSY){
                            //ステータス変更:移動（キャストと一緒）へ
                            SGameMgr.Ky.Card[i].Character.Status    = CARD_MOVE_WITH_CAST;
                             
                            //シーソーステータス変更：比較へ
                            SGameMgr.Seesaw.Status          = SEESAW_WEIGHT_COMPARE;
                            SGameMgr.Seesaw.MoveIndex       = 0;
                            SGameMgr.Seesaw.MoveCount       = SeesawCompareMoveData[SGameMgr.Seesaw.MoveIndex].MoveCount;
                            SGameMgr.Seesaw.MoveDirect      = SeesawCompareMoveData[SGameMgr.Seesaw.MoveIndex].MoveDirect;
                            SGameMgr.Seesaw.MoveWaitTimer   = 0;
                            
                            //----位置
                            SGameMgr.Seesaw.L_Base.OPos.y   = 8;
                            SGameMgr.Seesaw.R_Base.OPos.y   = -8;
                            
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
                            Task.user[0]        = SCRIPT_LINE_1;
                            Task.user[1]        = COMPARE_CARD_SCRIPT_BASE;
                            Task.user[2]        = COMPARE_CARD_SCRIPT_NUM;
                            CreateTask(&Task);
                        }
                        break;
                    //--------------------------------------------移動（キャストと一緒）
                    case CARD_MOVE_WITH_CAST:
                        SGameMgr.Ky.Card[i].Character.Pos.y = SGameMgr.Ky.Character.Pos.y + SGameMgr.Ky.Character.OPos.y + SGameMgr.Ky.Card[i].Character.OPos.y;
                        break;
                    //--------------------------------------------飛んでいく
                    case CARD_FLY:
                        SGameMgr.Ky.Card[i].Character.Pos.x += 2;
                        SGameMgr.Ky.Card[i].Character.Pos.y -= 2;
                        if( SGameMgr.Ky.Card[i].Character.Pos.y< -20){
                            SGameMgr.Ky.Card[i].Character.Status=CARD_DEATH;
                            SGameMgr.Ky.Card[i].Data.Flag   = 0;
                            SGameMgr.Ky.Card[i].DrawFlag    = 0;
                        }
                        break;
                    //--------------------------------------------終了
                    case CARD_DEATH:
                        break;
                    default:
                }
                
                if(SGameMgr.Ky.Card[i].DrawFlag){
                    //----描画
                    DrawCard(   SGameMgr.Ky.Card[i].Type,
                                SGameMgr.Ky.Card[i].Data.No,
                                SGameMgr.Ky.Card[i].Data.Side,
                                SGameMgr.Ky.Card[i].Character.Pos.x,
                                SGameMgr.Ky.Card[i].Character.Pos.y,
                                SGameMgr.Ky.Card[i].Character.Pos.z);
                }
            }

            break;
        //----------------------------------------------------------------タスク終了
        case TASK_MODE_EXIT:
            
            //自分を削除
            ExitTask(ip_task->id);
            break;
        default:
    }

    return TRUE;
}




//-----------------------------------------------------------------------------
//  関数名  :AppleCountTask
//
//  work    :レベル１の時アップルカウントタスク
//  in      :TASK*      タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int AppleCountTask(TASK* ip_task)
{
    SPRITE_DATA SpData;
    int offsetx;


    switch(ip_task->mode)
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //next MAIN
            ip_task->mode       = TASK_MODE_MAIN;
            
            //初期化:Index順
        //  ip_task->user[UWORK_DR_COUNT_DATA]; 起動時にセットする値を使用
        //  ip_task->user[UWORK_KY_COUNT_DATA]; 起動時にセットする値を使用
            ip_task->user[UWORK_TIMER]          = 0;
            ip_task->user[UWORK_COUNT]          = 0;
            ip_task->user[UWORK_DR_COUNT]       = 0;
            ip_task->user[UWORK_KY_COUNT]       = 0;
            ip_task->user[UWORK_DR_STOP_COUNT]  = 0;
            ip_task->user[UWORK_KY_STOP_COUNT]  = 0;
            
            break;
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:

            if( ++ip_task->user[UWORK_TIMER] > APPLE_COUNT_WAIT_TIME)
            {
                ip_task->user[UWORK_TIMER]      = 0;
                
                //DR
                if(++ip_task->user[UWORK_DR_COUNT] > ip_task->user[UWORK_DR_COUNT_DATA]){
                    ip_task->user[UWORK_DR_COUNT]       = ip_task->user[UWORK_DR_COUNT_DATA];
                    ip_task->user[UWORK_DR_STOP_COUNT]  = 1;
                }
                
                //KY
                if(++ip_task->user[UWORK_KY_COUNT] > ip_task->user[UWORK_KY_COUNT_DATA]){
                    ip_task->user[UWORK_KY_COUNT]       = ip_task->user[UWORK_KY_COUNT_DATA];
                    ip_task->user[UWORK_KY_STOP_COUNT]  = 1;
                }
                
                //このタスク終了
                if( (ip_task->user[UWORK_DR_STOP_COUNT]==1) && (ip_task->user[UWORK_KY_STOP_COUNT]==1) )
                {
                    ip_task->mode = TASK_MODE_EXIT;
                }else
                {
                    //♪
                    ++ip_task->user[UWORK_COUNT];
                    
                    //[♪]カウント
                    dsPlayXa(XA_FILE_NUMB03,ip_task->user[UWORK_COUNT]);
                    
                }
            }
            
            if(ip_task->user[UWORK_COUNT] !=0 ){
                
                if(ip_task->user[UWORK_DR_COUNT]>=10)   offsetx = 11;
                else                                    offsetx = 0;
                
                //DR
                DrawNum(    ip_task->user[UWORK_DR_COUNT],
                            WIDTH_BIG_FONT,
                            BigNumSpriteTable,
                            DR_SIDE_APPLE_COUNT_POS_X+offsetx,
                            DR_SIDE_APPLE_COUNT_POS_Y,
                            PRIORITY_NUM );
                
                DrawBox(    ip_task->user[UWORK_DR_COUNT],
                            ip_task->user[UWORK_DR_COUNT_DATA],
                            DR_SIDE_APPLE_COUNT_BOX_POS_X,
                            DR_SIDE_APPLE_COUNT_BOX_POS_Y,
                            PRIORITY_BOX);
                
                if(ip_task->user[UWORK_KY_COUNT]>=10)   offsetx = 11;
                else                                    offsetx = 0;
                
                //KY
                DrawNum(    ip_task->user[UWORK_KY_COUNT],
                            WIDTH_BIG_FONT,
                            BigNumSpriteTable,
                            KR_SIDE_APPLE_COUNT_POS_X+offsetx,
                            KR_SIDE_APPLE_COUNT_POS_Y,
                            PRIORITY_NUM );
                            
                DrawBox(    ip_task->user[UWORK_KY_COUNT],
                            ip_task->user[UWORK_KY_COUNT_DATA],
                            KY_SIDE_APPLE_COUNT_BOX_POS_X,
                            KY_SIDE_APPLE_COUNT_BOX_POS_Y,
                            PRIORITY_BOX);
            }
            
            break;
        //----------------------------------------------------------------タスク終了
        case TASK_MODE_EXIT:
            //カウント終了
            SGameMgr.Seesaw.CountEndFlag=1;
            
            //自分を削除
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
//  in      :TASK*      タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int  GameBgTask(TASK* ip_task)
{
    SPRITE_DATA SpData;


    switch(ip_task->mode)
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //next MAIN
            ip_task->mode       = TASK_MODE_MAIN;
            
            break;
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:

            SpData.No       = SEES_CHAR_GAME_GAME_BG_00;    //インデックス番号
            SpData.PosX     = 0;                            //X位置
            SpData.PosY     = 0;                            //Y位置
            SpData.PosZ     = PRIORITY_BG;                  //優先順位
            SpData.ScaleX   = SCALE10;                      //スケールX
            SpData.ScaleY   = SCALE10;                      //スケールY
            SpData.Rotate   = ROTATE000;                    //回転角
            SpData.Reverse  = NOREVERS;                     //反転コード
            DrawSprite( &SpData );                          //スプライト描画

            SpData.No       = SEES_CHAR_GAME_GAME_BG_01;    //インデックス番号
            SpData.PosX     = 256;                          //X位置
            SpData.PosY     = 0;                            //Y位置
            SpData.PosZ     = PRIORITY_BG;                  //優先順位
            SpData.ScaleX   = SCALE10;                      //スケールX
            SpData.ScaleY   = SCALE10;                      //スケールY
            SpData.Rotate   = ROTATE000;                    //回転角
            SpData.Reverse  = NOREVERS;                     //反転コード
            DrawSprite( &SpData );                          //スプライト描画
            
            break;
        //----------------------------------------------------------------タスク終了
        case TASK_MODE_EXIT:
            
            //自分を削除
            ExitTask(ip_task->id);
            break;
        default:
    }

    return TRUE;
}





//-----------------------------------------------------------------------------
//  関数名  :PauseTask
//
//  work    :ポーズタスク
//  in      :TASK* ip_task
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int PauseTask(TASK* ip_task)
{
    TASK Task;
    int ret;

    switch( ip_task->mode )
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //next MAIN
            ip_task->mode       = TASK_MODE_MAIN;

            //Flag
            ip_task->user[0]    = 0;

            //メニューフラグチェック
            GameMgr.WaitFlag    = OFF;

            break;
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:
            if( !ip_task->user[0] )
            {//メニューオープン待ち
                ret = MainMenuCheck10();

                if(ret==ON)
                {//スタートボタン押される
                    //停止コントロールフラグセット
                    ip_task->user[0] = 1;
                    
                    //タスクスリープ
                    SleepTask(TASK_NO_GAME_SELECT_LEVEL);
                    SleepTask(TASK_NO_GAME_CARD_CAST);
                    SleepTask(TASK_NO_GAME_APPLE_COUNT);
                    SleepTask(TASK_NO_GAME_SEESAW);
                    SleepTask(TASK_NO_GAME_KY);
                    SleepTask(TASK_NO_GAME_DR);
                    SleepTask(TASK_NO_GAME_AS);
                    SleepTask(TASK_NO_GAME_DR_CARD);
                    SleepTask(TASK_NO_GAME_KY_CARD);
                    SleepTask(TASK_NO_GAME_LIGHT_FLUSH);
                    SleepTask(TASK_NO_GAME_PLAYER);
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
                    WakeupTask(TASK_NO_GAME_SELECT_LEVEL);
                    WakeupTask(TASK_NO_GAME_CARD_CAST);
                    WakeupTask(TASK_NO_GAME_APPLE_COUNT);
                    WakeupTask(TASK_NO_GAME_SEESAW);
                    WakeupTask(TASK_NO_GAME_KY);
                    WakeupTask(TASK_NO_GAME_DR);
                    WakeupTask(TASK_NO_GAME_AS);
                    WakeupTask(TASK_NO_GAME_DR_CARD);
                    WakeupTask(TASK_NO_GAME_KY_CARD);
                    WakeupTask(TASK_NO_GAME_LIGHT_FLUSH);
                    WakeupTask(TASK_NO_GAME_PLAYER);
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
        //----------------------------------------------------------------タスク終了
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
//  関数名  :FireworksTask
//
//  work    :花火タスク
//  in      :TASK* ip_task  タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int FireworksTask(TASK* ip_task)
{
    SPRITE_DATA SpData;


    switch(ip_task->mode)
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //next MAIN
            ip_task->mode       = TASK_MODE_MAIN;
            
            //----初期化
            ip_task->user[USER_WORK_FIREWORKS_MODE]             = 0;

            if(SGameMgr.AllClearFlag){
                ip_task->user[USER_WORK_FIREWORKS_PLAY_LEVEL]       = SGameMgr.PlayLevel;
            }else{
                ip_task->user[USER_WORK_FIREWORKS_PLAY_LEVEL]       = SGameMgr.PlayLevel-1;
            }

            ip_task->user[USER_WORK_FIREWORKS_ANM_INDEX]        = 0;
            ip_task->user[USER_WORK_FIREWORKS_ANM_WAIT_TIME]    = 0;
            ip_task->user[USER_WORK_FIREWORKS_ANM_END_FLAG]     = 0;
            
            ip_task->user[USER_WORK_FIREWORKS_ANM_TANE_INDEX]       = 0;
            ip_task->user[USER_WORK_FIREWORKS_ANM_TANE_WAIT_TIME]   = 0;
            ip_task->user[USER_WORK_FIREWORKS_ANM_TANE_POSX]        = 240;
            ip_task->user[USER_WORK_FIREWORKS_ANM_TANE_POSY]        = 100;

            break;
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:
            
            switch(ip_task->user[USER_WORK_FIREWORKS_MODE])
            {
                case 0:
                    if( ++ip_task->user[USER_WORK_FIREWORKS_ANM_TANE_WAIT_TIME] > SEES_GAME_EVENT_ANM_WAIT_TIME)
                    {
                        ip_task->user[USER_WORK_FIREWORKS_ANM_TANE_WAIT_TIME]   = 0;
                        ip_task->user[USER_WORK_FIREWORKS_ANM_TANE_INDEX]       ^= 1;
                    }
                    
                    ip_task->user[USER_WORK_FIREWORKS_ANM_TANE_POSX] -= 2;
                    ip_task->user[USER_WORK_FIREWORKS_ANM_TANE_POSY] -= 2;
                    if(ip_task->user[USER_WORK_FIREWORKS_ANM_TANE_POSY] < 0){
                        ip_task->user[USER_WORK_FIREWORKS_MODE] = 1;
                        
                        //[♪]バン
                        ssPlaySe(SEES_SE_11);
                    }
                    
                    //----
                    SpData.No       = ClearEventFlySmokeSpriteTable[ip_task->user[USER_WORK_FIREWORKS_ANM_TANE_INDEX]].No;//インデックス番号
                    SpData.PosX     = ip_task->user[USER_WORK_FIREWORKS_ANM_TANE_POSX]; //X位置
                    SpData.PosY     = ip_task->user[USER_WORK_FIREWORKS_ANM_TANE_POSY]; //Y位置
                    SpData.PosZ     = PRIORITY_FIRE;                                    //優先順位
                    SpData.ScaleX   = SCALE10;                                          //スケールX
                    SpData.ScaleY   = SCALE10;                                          //スケールY
                    SpData.Rotate   = ROTATE000;                                        //回転角
                    SpData.Reverse  = NOREVERS;                                         //反転コード
                    DrawSprite( &SpData );                                              //スプライト描画
                    
                    break;
                case 1:
                    switch(ip_task->user[USER_WORK_FIREWORKS_PLAY_LEVEL])
                    {
                        //----------------------------------------LEVEL-1
                        case 0:
                            if(ip_task->user[USER_WORK_FIREWORKS_ANM_END_FLAG]==1) ip_task->mode = TASK_MODE_EXIT;

                            //終了
                            if(++ip_task->user[USER_WORK_FIREWORKS_ANM_WAIT_TIME] > SEES_GAME_EVENT_FIREWORKS_DRAW_TIME)
                            {
                                ip_task->user[USER_WORK_FIREWORKS_ANM_END_FLAG] = 1;
                            }

                            //----
                            SpData.No       = ClearEventFireworksSpriteTable[0].No;     //インデックス番号
                            SpData.PosX     = ClearEventFireworksSpriteTable[0].Ofx;    //X位置
                            SpData.PosY     = ClearEventFireworksSpriteTable[0].Ofy;    //Y位置
                            SpData.PosZ     = PRIORITY_FIRE;                            //優先順位
                            SpData.ScaleX   = SCALE10;                                  //スケールX
                            SpData.ScaleY   = SCALE10;                                  //スケールY
                            SpData.Rotate   = ROTATE000;                                //回転角
                            SpData.Reverse  = NOREVERS;                                 //反転コード
                            DrawSprite( &SpData );                                      //スプライト描画

                            break;
                        //----------------------------------------LEVEL-2
                        case 1:
                            if(ip_task->user[USER_WORK_FIREWORKS_ANM_END_FLAG]==1) ip_task->mode = TASK_MODE_EXIT;
                            
                            if(++ip_task->user[USER_WORK_FIREWORKS_ANM_WAIT_TIME] > SEES_GAME_EVENT_FIREWORKS_DRAW_TIME)
                            {
                                ip_task->user[USER_WORK_FIREWORKS_ANM_WAIT_TIME]        = 0;
                                ++ip_task->user[USER_WORK_FIREWORKS_ANM_INDEX];
                                if(ip_task->user[USER_WORK_FIREWORKS_ANM_INDEX] >= 2)
                                {
                                    ip_task->user[USER_WORK_FIREWORKS_ANM_INDEX]        = 1;
                                    ip_task->user[USER_WORK_FIREWORKS_ANM_END_FLAG]     = 1;
                                }else
                                if(ip_task->user[USER_WORK_FIREWORKS_ANM_INDEX]==1){
                                    //[♪]バン
                                    ssPlaySe(SEES_SE_11);
                                }else{
                                    
                                }
                            }
                            
                            SpData.No       = ClearEventFireworksSpriteTable[ 6 + ip_task->user[USER_WORK_FIREWORKS_ANM_INDEX] ].No;        //インデックス番号
                            SpData.PosX     = ClearEventFireworksSpriteTable[ 6 + ip_task->user[USER_WORK_FIREWORKS_ANM_INDEX] ].Ofx;   //X位置
                            SpData.PosY     = ClearEventFireworksSpriteTable[ 6 + ip_task->user[USER_WORK_FIREWORKS_ANM_INDEX] ].Ofy;   //Y位置
                            SpData.PosZ     = PRIORITY_FIRE;                    //優先順位
                            SpData.ScaleX   = SCALE10;                          //スケールX
                            SpData.ScaleY   = SCALE10;                          //スケールY
                            SpData.Rotate   = ROTATE000;                        //回転角
                            SpData.Reverse  = NOREVERS;                         //反転コード
                            DrawSprite( &SpData );                              //スプライト描画
                            
                            break;
                        //----------------------------------------LEVEL-3
                        case 2:
                            if(ip_task->user[USER_WORK_FIREWORKS_ANM_END_FLAG]==1) ip_task->mode = TASK_MODE_EXIT;
                            
                            if(++ip_task->user[USER_WORK_FIREWORKS_ANM_WAIT_TIME] > SEES_GAME_EVENT_FIREWORKS_DRAW_TIME)
                            {
                                ip_task->user[USER_WORK_FIREWORKS_ANM_END_FLAG] = 1;
                            }
                            
                            //----
                            SpData.No       = ClearEventFireworksSpriteTable[2].No;     //インデックス番号
                            SpData.PosX     = ClearEventFireworksSpriteTable[2].Ofx;    //X位置
                            SpData.PosY     = ClearEventFireworksSpriteTable[2].Ofy;    //Y位置
                            SpData.PosZ     = PRIORITY_FIRE;                            //優先順位
                            SpData.ScaleX   = SCALE10;                                  //スケールX
                            SpData.ScaleY   = SCALE10;                                  //スケールY
                            SpData.Rotate   = ROTATE000;                                //回転角
                            SpData.Reverse  = NOREVERS;                                 //反転コード
                            DrawSprite( &SpData );                                      //スプライト描画
                            
                            break;
                        //----------------------------------------LEVEL-4
                        case 3:
                            if(ip_task->user[USER_WORK_FIREWORKS_ANM_END_FLAG]==1) ip_task->mode = TASK_MODE_EXIT;
                            
                            if(++ip_task->user[USER_WORK_FIREWORKS_ANM_WAIT_TIME] > SEES_GAME_EVENT_FIREWORKS_DRAW_TIME)
                            {
                                ip_task->user[USER_WORK_FIREWORKS_ANM_END_FLAG] = 1;
                            }
                            
                            //----
                            SpData.No       = ClearEventFireworksSpriteTable[3].No;     //インデックス番号
                            SpData.PosX     = ClearEventFireworksSpriteTable[3].Ofx;    //X位置
                            SpData.PosY     = ClearEventFireworksSpriteTable[3].Ofy;    //Y位置
                            SpData.PosZ     = PRIORITY_FIRE;                            //優先順位
                            SpData.ScaleX   = SCALE10;                                  //スケールX
                            SpData.ScaleY   = SCALE10;                                  //スケールY
                            SpData.Rotate   = ROTATE000;                                //回転角
                            SpData.Reverse  = NOREVERS;                                 //反転コード
                            DrawSprite( &SpData );                                      //スプライト描画
                            break;
                        //----------------------------------------LEVEL-5
                        case 4:
                            if(ip_task->user[USER_WORK_FIREWORKS_ANM_END_FLAG]==1) ip_task->mode = TASK_MODE_EXIT;
                            
                            if(++ip_task->user[USER_WORK_FIREWORKS_ANM_WAIT_TIME] > SEES_GAME_EVENT_FIREWORKS_DRAW_TIME)
                            {
                                ip_task->user[USER_WORK_FIREWORKS_ANM_WAIT_TIME]        = 0;
                                if(++ip_task->user[USER_WORK_FIREWORKS_ANM_INDEX] >= 2)
                                {
                                    ip_task->user[USER_WORK_FIREWORKS_ANM_INDEX]        = 1;
                                    ip_task->user[USER_WORK_FIREWORKS_ANM_END_FLAG]     = 1;
                                }
                            }
                            
                            //---- 
                            SpData.No       = ClearEventFireworksSpriteTable[ 4 + ip_task->user[USER_WORK_FIREWORKS_ANM_INDEX] ].No;    //インデックス番号
                            SpData.PosX     = ClearEventFireworksSpriteTable[ 4 + ip_task->user[USER_WORK_FIREWORKS_ANM_INDEX] ].Ofx;   //X位置
                            SpData.PosY     = ClearEventFireworksSpriteTable[ 4 + ip_task->user[USER_WORK_FIREWORKS_ANM_INDEX] ].Ofy;   //Y位置
                            SpData.PosZ     = PRIORITY_FIRE;                    //優先順位
                            SpData.ScaleX   = SCALE10;                          //スケールX
                            SpData.ScaleY   = SCALE10;                          //スケールY
                            SpData.Rotate   = ROTATE000;                        //回転角
                            SpData.Reverse  = NOREVERS;                         //反転コード
                            DrawSprite( &SpData );                              //スプライト描画
                            
                            break;
                        default:
                    }
                    break;
                default:
            }
            
            break;
        //----------------------------------------------------------------タスク終了
        case TASK_MODE_EXIT:
            
            
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
//                  SGameMgr.Script.Flag    = 1;
//                  SGameMgr.Script.Index   = 0;
//                  SGameMgr.Script.Line    = ip_task->user[0];
//                  SGameMgr.Script.Base    = ip_task->user[1];
//                  SGameMgr.Script.Num     = ip_task->user[2];
//                  
//                  break;
//              //---------------------------------------------------------------------
//              case TASK_MODE_MAIN:
//                  
//                  if(MetuseijiFlag==OFF)
//                  {
//                      switch(SGameMgr.Script.Line)
//                      {
//                          case SCRIPT_LINE_1:
//                              MenuMessageSet10(&SeesScript[SGameMgr.Script.Base + SGameMgr.Script.Index]);
//                              break;
//                          case SCRIPT_LINE_2:
//                              MenuMessageSet20(&SeesScript[SGameMgr.Script.Base + SGameMgr.Script.Index]);
//                              break;
//                          case SCRIPT_LINE_3:
//                              MenuMessageSet30(&SeesScript[SGameMgr.Script.Base + SGameMgr.Script.Index]);
//                              break;
//                          default:
//                      }
//                      
//                      if(++SGameMgr.Script.Index >= SGameMgr.Script.Num)
//                      {
//                          ip_task->mode = TASK_MODE_EXIT;
//                      }
//                  }
//                  break;
//              //---------------------------------------------------------------------
//              case TASK_MODE_EXIT:
//                  
//                  SGameMgr.Script.Flag=0;
//                  
//                  //自分を削除
//                  ExitTask(ip_task->id);
//                  break;
//              default:
//          }
//          return TRUE;
//      }
//




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

            SGameMgr.Script.Flag    = 1;
            SGameMgr.Script.Index   = 0;
            SGameMgr.Script.Line    = ip_task->user[0];
            SGameMgr.Script.Base    = ip_task->user[1];
            SGameMgr.Script.Num     = ip_task->user[2];
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
                        switch(SGameMgr.Script.Line)
                        {
                            case SCRIPT_LINE_1:
                                MenuMessageSet10(&SeesScript[SGameMgr.Script.Base + SGameMgr.Script.Index]);
                                break;
                            case SCRIPT_LINE_2:
                                MenuMessageSet20(&SeesScript[SGameMgr.Script.Base + SGameMgr.Script.Index]);
                                break;
                            case SCRIPT_LINE_3:
                                MenuMessageSet30(&SeesScript[SGameMgr.Script.Base + SGameMgr.Script.Index]);
                                break;
                            default:
                        }
                        
                        if(++SGameMgr.Script.Index >= SGameMgr.Script.Num){
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
            
            SGameMgr.Script.Flag    = 0;
            
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
static int EventFadeOutTask(TASK* ip_task)
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
            SGameMgr.ExitFlag   = 1;
            
            //自分を削除
            ExitTask(ip_task->id);
            break;
        default:
    }
    return TRUE;
}





//-----------------------------------------------------------------------------
//  関数名  :FalseEventTask
//
//  work    :失敗イベントタスク
//  in      :TASK*      タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int FalseEventTask(TASK* ip_task)
{
    SPRITE_DATA SpData;
    TASK Task;


    switch(ip_task->mode)
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //next MAIN
            ip_task->mode       = TASK_MODE_MAIN;

            //----texture read sram -> vram
            if((file_read(SeesEventTextureFile[0].fn,LoadAddress)) == -1)
            {//read error
                return FALSE;
            }

            //----texture init
            TexInit( SEES_EVENT_TIM_NUM, &SeesEventTextureImage[SEES_EVENT_TIM_POS] );
            TimImgData = SeesEventTextureImage;
            
            //----スプライト登録
            EntrySprite( SeesEventSpriteData );

            
            //----初期化
            SGameMgr.Event.Timer                = 0;
            SGameMgr.Event.EndFlag              = 0;

            SGameMgr.Event.False.KyIndex        = 0;
            SGameMgr.Event.False.KyWaitTime     = 0;
            SGameMgr.Event.False.StarFlag       = 0;
            SGameMgr.Event.False.StarIndex      = 0;
            SGameMgr.Event.False.StarWaitTime   = 0;
            SGameMgr.Event.False.Timer          = 0;
            
            //----終了処理メニュー
            SGameMgr.SelectContinue.Val         = 0;
            SGameMgr.SelectContinue.Type        = SELECT_RETRY_H;
            SGameMgr.SelectContinue.No          = 0;
            SGameMgr.SelectContinue.Wt          = 0;
            SGameMgr.SelectContinue.FadeFlag    = 0;

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
            Task.user[0]        = SCRIPT_LINE_1;
            Task.user[1]        = FALSE_SCRIPT_BASE;
            Task.user[2]        = FALSE_SCRIPT_NUM;
            CreateTask(&Task);


#ifdef __DEBUG_SEES__
            // フェードInします
            GameMgr.FadeFlag = FadeIn;
#endif

            break;
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:
            //----終了メニューチェック
            if(++SGameMgr.Event.Timer > SEES_GAME_FALSE_EVENT_END_TIME){
                SGameMgr.Event.EndFlag = 1;
            }


            //----星
            if(!SGameMgr.Event.False.StarFlag){
                //----星
                if( ++SGameMgr.Event.False.Timer >= SEES_GAME_FALSE_EVENT_STAR_WAIT_TIME )
                {
                    if(++SGameMgr.Event.False.StarWaitTime>SEES_GAME_EVENT_ANM_WAIT_TIME*2)
                    {
                        SGameMgr.Event.False.StarWaitTime=0;
                        if(++SGameMgr.Event.False.StarIndex >= 2)
                        {
                            SGameMgr.Event.False.StarFlag=1;
                            --SGameMgr.Event.False.StarIndex;
                        }
                    }
                    
                    
                    //Ky
                    SpData.No       = FalseEventStarSpriteData[SGameMgr.Event.False.StarIndex].No;  //インデックス番号
                    SpData.PosX     = 64;                           //X位置
                    SpData.PosY     = 35;                           //Y位置
                    SpData.PosZ     = PRIORITY_CAST;                //優先順位
                    SpData.ScaleX   = SCALE10;                      //スケールX
                    SpData.ScaleY   = SCALE10;                      //スケールY
                    SpData.Rotate   = ROTATE000;                    //回転角
                    SpData.Reverse  = NOREVERS;                     //反転コード
                    DrawSprite( &SpData );                          //スプライト描画
                }
            }


            //----星が光るまで話す
            if(SGameMgr.Event.False.Timer <= SEES_GAME_FALSE_EVENT_STAR_WAIT_TIME)
            {
                if(++SGameMgr.Event.False.KyWaitTime > SEES_GAME_EVENT_ANM_WAIT_TIME)
                {
                    SGameMgr.Event.False.KyWaitTime     = 0;
                    SGameMgr.Event.False.KyIndex        ^= 1;
                }
            }

            if(SGameMgr.Event.False.Timer==SEES_GAME_FALSE_EVENT_STAR_WAIT_TIME){
                //[♪]キラーン
                ssPlaySe(SEES_SE_12);
            }

            //Ky
            SpData.No       = FalseEventKyAnmSpriteData[SGameMgr.Event.False.KyIndex].No;   //インデックス番号
            SpData.PosX     = 228;                          //X位置
            SpData.PosY     = 126;                          //Y位置
            SpData.PosZ     = PRIORITY_CAST;                //優先順位
            SpData.ScaleX   = SCALE10;                      //スケールX
            SpData.ScaleY   = SCALE10;                      //スケールY
            SpData.Rotate   = ROTATE000;                    //回転角
            SpData.Reverse  = NOREVERS;                     //反転コード
            DrawSprite( &SpData );                          //スプライト描画
            
            //プレート
            SpData.No       = SEES_CHAR_EVENT_LOSE_PLATE;   //インデックス番号
            SpData.PosX     = 70;                           //X位置
            SpData.PosY     = 206;                          //Y位置
            SpData.PosZ     = PRIORITY_CAST;                //優先順位
            SpData.ScaleX   = SCALE10;                      //スケールX
            SpData.ScaleY   = SCALE10;                      //スケールY
            SpData.Rotate   = ROTATE000;                    //回転角
            SpData.Reverse  = NOREVERS;                     //反転コード
            DrawSprite( &SpData );                          //スプライト描画
            
            //背景
            EventBg();
            
            //----もう一度プレイしますか？
            if(SGameMgr.Event.EndFlag)
            {
                if(SelectContinue(!SGameMgr.SelectContinue.FadeFlag))
                {//●ボタンが押された
                    if(!SGameMgr.SelectContinue.FadeFlag)
                    {//フェード中
                        if((SGameMgr.SelectContinue.Val==0) && (SGameMgr.SelectContinue.Type==SELECT_RETRY_H))
                        {//もう一度プレイしますか？　はい
                            SGameMgr.SelectContinue.FadeFlag    = 1;
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
                        if( (SGameMgr.SelectContinue.Val==1) && (SGameMgr.SelectContinue.Type==SELECT_RETRY_H))
                        {//もう一度プレイしますか？　いいえ
                            SGameMgr.SelectContinue.Type    = SELECT_END_H;
                            SGameMgr.SelectContinue.Val     = 0;
                        }else
                        if((SGameMgr.SelectContinue.Type==SELECT_END_H) && (SGameMgr.SelectContinue.Val==0))
                        {//やめますか？　はい
                            SGameMgr.SelectContinue.FadeFlag    = 1;
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
                        if((SGameMgr.SelectContinue.Type==SELECT_END_H) && (SGameMgr.SelectContinue.Val==1))
                        {//やめますか？　いいえ
                            SGameMgr.SelectContinue.Type    = SELECT_RETRY_H;
                            SGameMgr.SelectContinue.Val     = 0;
                        }else
                        {
                            
                        }
                    }
                }else{
                    
                }
            }
            
            break;
        //----------------------------------------------------------------タスク終了
        case TASK_MODE_EXIT:
            
            //--------------------ここは2択
            //  (1)セレクトレベルへ
            //  (2)メインメニュー
            if((SGameMgr.SelectContinue.Type==SELECT_END_H) && (SGameMgr.SelectContinue.Val==0))
            {//----ゲームをおわります
                SGameMgr.ExitFlag=1;
            }else
            {
                //----セレクトレベルタスク
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
            
            //自分を削除
            ExitTask(ip_task->id);
            
            break;
        default:
    }

    return TRUE;
}


//-----------------------------------------------------------------------------
//  関数名  :ClearEventTask
//
//  work    :クリアイベントタスク
//  in      :TASK*      タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int ClearEventTask(TASK* ip_task)
{
    TASK Task;


    switch(ip_task->mode)
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //next MAIN
            ip_task->mode       = TASK_MODE_MAIN;

            //----texture read sram -> vram
            if((file_read(SeesEventTextureFile[0].fn,LoadAddress)) == -1)
            {//read error
                return FALSE;
            }
            
            //----texture init
            TexInit( SEES_EVENT_TIM_NUM, &SeesEventTextureImage[SEES_EVENT_TIM_POS] );
            TimImgData = SeesEventTextureImage;
            
            //----スプライト登録
            EntrySprite( SeesEventSpriteData );
            
            //----初期化
            SGameMgr.Event.Timer                = 0;
            SGameMgr.Event.EndFlag              = 0;
            SGameMgr.Event.Clear.Mode           = 0;
            ip_task->user[0]                    = GET_DA_STATUS_WAIT_TIME;      //wait
            ip_task->user[1]                    = 0;                            //flag
            ip_task->user[2]                    = GET_DA_STATUS_WAIT_TIME*5;    //wait
            ip_task->user[3]                    = 0;                            //flag
            ip_task->user[4]                    = SEES_GAME_CLEAR_EVENT_LAST_SCRIPT_WAIT_TIMER; //last script
            ip_task->user[5]                    = 0;                            //flag
            ip_task->user[6]                    = 0;                            //anmno

            SGameMgr.Event.Clear.Sup.Status         = 0;
            SGameMgr.Event.Clear.Sup.Anm.Data.no    = 0;
            SGameMgr.Event.Clear.Sup.Anm.Data.wt    = 0;
            SGameMgr.Event.Clear.Sup.Anm.Index      = 0;
            SGameMgr.Event.Clear.Sup.Pos.x          = 0;
            SGameMgr.Event.Clear.Sup.Pos.y          = 0;
            SGameMgr.Event.Clear.Sup.Pos.z          = 0;
            SGameMgr.Event.Clear.Sup.OPos.x         = 0;
            SGameMgr.Event.Clear.Sup.OPos.y         = 0;
            SGameMgr.Event.Clear.Sup.OPos.z         = 0;
            SGameMgr.Event.Clear.Sup.Spd.dx         = 0;
            SGameMgr.Event.Clear.Sup.Spd.dy         = 0;
            SGameMgr.Event.Clear.Sup.Spd.sx         = 0;
            SGameMgr.Event.Clear.Sup.Spd.sy         = 0;

            SGameMgr.Event.Clear.Dr.Status          = EVENT_DR_ANM_ON;
            SGameMgr.Event.Clear.Dr.Anm.Data.no     = 0;
            SGameMgr.Event.Clear.Dr.Anm.Data.wt     = 0;
            SGameMgr.Event.Clear.Dr.Anm.Index       = 1;
            SGameMgr.Event.Clear.Dr.Pos.x           = 0;
            SGameMgr.Event.Clear.Dr.Pos.y           = 0;
            SGameMgr.Event.Clear.Dr.Pos.z           = 0;
            SGameMgr.Event.Clear.Dr.OPos.x          = 0;
            SGameMgr.Event.Clear.Dr.OPos.y          = 0;
            SGameMgr.Event.Clear.Dr.OPos.z          = 0;
            SGameMgr.Event.Clear.Dr.Spd.dx          = 0;
            SGameMgr.Event.Clear.Dr.Spd.dy          = 0;
            SGameMgr.Event.Clear.Dr.Spd.sx          = 0;
            SGameMgr.Event.Clear.Dr.Spd.sy          = 0;

            SGameMgr.Event.Clear.Ky.Status          = EVENT_KY_ANM_ON;
            SGameMgr.Event.Clear.Ky.Anm.Data.no     = 0;
            SGameMgr.Event.Clear.Ky.Anm.Data.wt     = 0;
            SGameMgr.Event.Clear.Ky.Anm.Index       = 0;
            SGameMgr.Event.Clear.Ky.Pos.x           = 0;
            SGameMgr.Event.Clear.Ky.Pos.y           = 0;
            SGameMgr.Event.Clear.Ky.Pos.z           = 0;
            SGameMgr.Event.Clear.Ky.OPos.x          = 0;
            SGameMgr.Event.Clear.Ky.OPos.y          = 0;
            SGameMgr.Event.Clear.Ky.OPos.z          = 0;
            SGameMgr.Event.Clear.Ky.Spd.dx          = 0;
            SGameMgr.Event.Clear.Ky.Spd.dy          = 0;
            SGameMgr.Event.Clear.Ky.Spd.sx          = 0;
            SGameMgr.Event.Clear.Ky.Spd.sy          = 0;

            SGameMgr.Event.Clear.As.Status          = EVENT_AS_ANM_OFF;
            SGameMgr.Event.Clear.As.Anm.Data.no     = 0;
            SGameMgr.Event.Clear.As.Anm.Data.wt     = 0;
            SGameMgr.Event.Clear.As.Anm.Index       = 0;
            SGameMgr.Event.Clear.As.Pos.x           = 0;
            SGameMgr.Event.Clear.As.Pos.y           = 0;
            SGameMgr.Event.Clear.As.Pos.z           = 0;
            SGameMgr.Event.Clear.As.OPos.x          = 0;
            SGameMgr.Event.Clear.As.OPos.y          = 0;
            SGameMgr.Event.Clear.As.OPos.z          = 0;
            SGameMgr.Event.Clear.As.Spd.dx          = 0;
            SGameMgr.Event.Clear.As.Spd.dy          = 0;
            SGameMgr.Event.Clear.As.Spd.sx          = 0;
            SGameMgr.Event.Clear.As.Spd.sy          = 0;

            //----終了処理メニュー
            SGameMgr.SelectContinue.Val             = 0;
            SGameMgr.SelectContinue.Type            = SELECT_RETRY_H;
            SGameMgr.SelectContinue.No              = 0;
            SGameMgr.SelectContinue.Wt              = 0;
            SGameMgr.SelectContinue.FadeFlag        = 0;

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
            Task.user[0]        = SCRIPT_LINE_1;
            Task.user[1]        = CLEAR_1_SCRIPT_BASE;
            Task.user[2]        = CLEAR_1_SCRIPT_NUM;
            CreateTask(&Task);

#ifdef __DEBUG_SEES__
            // フェードInします
            GameMgr.FadeFlag = FadeIn;
#endif

            break;
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:
            //----終了メニューチェック
            if(++SGameMgr.Event.Timer > SEES_GAME_CLEAR_EVENT_END_TIME){
                SGameMgr.Event.EndFlag          = 1;
                SGameMgr.Event.Clear.Dr.Status  = EVENT_DR_ANM_OFF;
                SGameMgr.Event.Clear.Ky.Status  = EVENT_KY_ANM_OFF;
            }

            //----
            switch(SGameMgr.Event.Clear.Mode)
            {
                case 0:
                    EventCongratulations();
                    break;
                case 1:
                    //3rd
                    if(!ip_task->user[1]){
                        if(--ip_task->user[0]<=0){
                            if(dSoundStatus == DslStatStandby){
                                ip_task->user[1]=1;
                                
                                //DR ANM OFF
                            //  SGameMgr.Event.Clear.Dr.Status  = EVENT_DR_ANM_OFF;
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
                                Task.user[0]        = SCRIPT_LINE_1;
                                Task.user[1]        = CLEAR_3_SCRIPT_BASE;
                                Task.user[2]        = CLEAR_3_SCRIPT_NUM;
                                CreateTask(&Task);
                            }
                        }
                    }

                    //hanabi
                    if(!ip_task->user[3]){
                        if(ip_task->user[1]){
                            if(--ip_task->user[2]<=0){
                                if(dSoundStatus == DslStatStandby){
                                    ip_task->user[3]=1;
                                    
                                    //DR ANM ON
                            //      SGameMgr.Event.Clear.Dr.Status  = EVENT_DR_ANM_ON;
                                    
                                    //ボーリーアニメセット
                                    ip_task->user[6]=1;

                                    //[♪]ガチャ
                                    ssPlaySe(SEES_SE_09);

                                    //[♪]ヒュー
                                    ssPlaySe(SEES_SE_10);

                                    //----花火打ち上げ
                                    Task.func       = FireworksTask;
                                    Task.priority   = TASK_NO_EVENT_FIREWORKS;
                                    Task.attribute  = ATTR_USER;
                                    Task.status     = TASK_NEW_ENTRY;
                                    Task.id         = TASK_NO_EVENT_FIREWORKS;
                                    Task.wait_time  = 0;
                                    Task.buf        = NULL;
                                    Task.name       = "FireworksTask";
                                    Task.mode       = TASK_MODE_INIT;
                                    CreateTask(&Task);
                                }
                            }
                        }
                    }

                    //last script
                    if(!ip_task->user[5]){
                        if(ip_task->user[3]){
                            if(--ip_task->user[4]<=0){
                                ip_task->user[5]=1;
                                
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
                                Task.user[0]        = SCRIPT_LINE_1;
                                Task.user[1]        = CLEAR_MAKENAI_SCRIPT_BASE;
                                Task.user[2]        = CLEAR_MAKENAI_SCRIPT_NUM;
                                CreateTask(&Task);
                            }
                        }
                    }

                    EventDr();
                    EventKy();
                    EventAs(ip_task->user[6]);
                    EventBg();
                    break;
                default:
            }
            
            //----もう一度プレイしますか？
            if(SGameMgr.Event.EndFlag)
            {
                if(SelectContinue(!SGameMgr.SelectContinue.FadeFlag))
                {//●ボタンが押された
                    if(!SGameMgr.SelectContinue.FadeFlag){
                        if((SGameMgr.SelectContinue.Val==0) && (SGameMgr.SelectContinue.Type==SELECT_RETRY_H))
                        {//もう一度プレイしますか？　はい
                            SGameMgr.SelectContinue.FadeFlag    = 1;
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
                        if( (SGameMgr.SelectContinue.Val==1) && (SGameMgr.SelectContinue.Type==SELECT_RETRY_H))
                        {//もう一度プレイしますか？　いいえ
                            SGameMgr.SelectContinue.Type    =SELECT_END_H;
                            SGameMgr.SelectContinue.Val     = 0;
                        }else
                        if((SGameMgr.SelectContinue.Type==SELECT_END_H) && (SGameMgr.SelectContinue.Val==0))
                        {//やめますか？　はい
                            SGameMgr.SelectContinue.FadeFlag    = 1;
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
                        if((SGameMgr.SelectContinue.Type==SELECT_END_H) && (SGameMgr.SelectContinue.Val==1))
                        {//やめますか？　いいえ
                            SGameMgr.SelectContinue.Type    = SELECT_RETRY_H;
                            SGameMgr.SelectContinue.Val     = 0;
                        }else
                        {
                            
                        }
                    }
                }else{
                    
                }
            }
            
            break;
        //----------------------------------------------------------------タスク終了
        case TASK_MODE_EXIT:
            
            //--------------------ここは２択
            //  (1)セレクトレベルへ
            //  (2)メインメニュー
            if((SGameMgr.SelectContinue.Val==0) && (SGameMgr.SelectContinue.Type==SELECT_RETRY_H))
            {
                //----セレクトレベルタスク
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
            {
                //----ゲームをおわります
                SGameMgr.ExitFlag=1;
            }
            
            //自分を削除
            ExitTask(ip_task->id);
            
            break;
        default:
    }

    return TRUE;
}


//-----------------------------------------------------------------------------
//  関数名  :AllClearEventTask
//
//  work    :オールクリアイベントタスク
//  in      :TASK*      タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int AllClearEventTask(TASK* ip_task)
{
    TASK Task;

    switch(ip_task->mode)
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //next MAIN
            ip_task->mode       = TASK_MODE_MAIN;

            //----texture read sram -> vram
            if((file_read(SeesEventTextureFile[0].fn,LoadAddress)) == -1)
            {//read error
                return FALSE;
            }
            
            //----texture init
            TexInit( SEES_EVENT_TIM_NUM, &SeesEventTextureImage[SEES_EVENT_TIM_POS] );
            TimImgData = SeesEventTextureImage;
            
            //----スプライト登録
            EntrySprite( SeesEventSpriteData );

            //初期化
            SGameMgr.Event.Timer                = 0;
            SGameMgr.Event.EndFlag              = 0;

            //----初期化
            SGameMgr.Event.Timer                = 0;
            SGameMgr.Event.EndFlag              = 0;
            SGameMgr.Event.Clear.Mode           = 0;
            ip_task->user[0]                    = GET_DA_STATUS_WAIT_TIME;      //wait
            ip_task->user[1]                    = 0;                            //flag
            ip_task->user[2]                    = GET_DA_STATUS_WAIT_TIME*5;    //wait
            ip_task->user[3]                    = 0;                            //flag
            ip_task->user[4]                    = SEES_GAME_CLEAR_EVENT_LAST_SCRIPT_WAIT_TIMER; //last script
            ip_task->user[5]                    = 0;                            //flag
            ip_task->user[6]                    = 0;                            //anmno


            SGameMgr.Event.Clear.Sup.Status         = 0;
            SGameMgr.Event.Clear.Sup.Anm.Data.no    = 0;
            SGameMgr.Event.Clear.Sup.Anm.Data.wt    = 0;
            SGameMgr.Event.Clear.Sup.Anm.Index      = 0;
            SGameMgr.Event.Clear.Sup.Pos.x          = 0;
            SGameMgr.Event.Clear.Sup.Pos.y          = 0;
            SGameMgr.Event.Clear.Sup.Pos.z          = 0;
            SGameMgr.Event.Clear.Sup.OPos.x         = 0;
            SGameMgr.Event.Clear.Sup.OPos.y         = 0;
            SGameMgr.Event.Clear.Sup.OPos.z         = 0;
            SGameMgr.Event.Clear.Sup.Spd.dx         = 0;
            SGameMgr.Event.Clear.Sup.Spd.dy         = 0;
            SGameMgr.Event.Clear.Sup.Spd.sx         = 0;
            SGameMgr.Event.Clear.Sup.Spd.sy         = 0;

            SGameMgr.Event.Clear.Dr.Status          = EVENT_DR_ANM_ON;
            SGameMgr.Event.Clear.Dr.Anm.Data.no     = 0;
            SGameMgr.Event.Clear.Dr.Anm.Data.wt     = 0;
            SGameMgr.Event.Clear.Dr.Anm.Index       = 1;
            SGameMgr.Event.Clear.Dr.Pos.x           = 0;
            SGameMgr.Event.Clear.Dr.Pos.y           = 0;
            SGameMgr.Event.Clear.Dr.Pos.z           = 0;
            SGameMgr.Event.Clear.Dr.OPos.x          = 0;
            SGameMgr.Event.Clear.Dr.OPos.y          = 0;
            SGameMgr.Event.Clear.Dr.OPos.z          = 0;
            SGameMgr.Event.Clear.Dr.Spd.dx          = 0;
            SGameMgr.Event.Clear.Dr.Spd.dy          = 0;
            SGameMgr.Event.Clear.Dr.Spd.sx          = 0;
            SGameMgr.Event.Clear.Dr.Spd.sy          = 0;

            SGameMgr.Event.Clear.Ky.Status          = EVENT_KY_ANM_ON;
            SGameMgr.Event.Clear.Ky.Anm.Data.no     = 0;
            SGameMgr.Event.Clear.Ky.Anm.Data.wt     = 0;
            SGameMgr.Event.Clear.Ky.Anm.Index       = 0;
            SGameMgr.Event.Clear.Ky.Pos.x           = 0;
            SGameMgr.Event.Clear.Ky.Pos.y           = 0;
            SGameMgr.Event.Clear.Ky.Pos.z           = 0;
            SGameMgr.Event.Clear.Ky.OPos.x          = 0;
            SGameMgr.Event.Clear.Ky.OPos.y          = 0;
            SGameMgr.Event.Clear.Ky.OPos.z          = 0;
            SGameMgr.Event.Clear.Ky.Spd.dx          = 0;
            SGameMgr.Event.Clear.Ky.Spd.dy          = 0;
            SGameMgr.Event.Clear.Ky.Spd.sx          = 0;
            SGameMgr.Event.Clear.Ky.Spd.sy          = 0;

            SGameMgr.Event.Clear.As.Status          = EVENT_AS_ANM_OFF;
            SGameMgr.Event.Clear.As.Anm.Data.no     = 0;
            SGameMgr.Event.Clear.As.Anm.Data.wt     = 0;
            SGameMgr.Event.Clear.As.Anm.Index       = 0;
            SGameMgr.Event.Clear.As.Pos.x           = 0;
            SGameMgr.Event.Clear.As.Pos.y           = 0;
            SGameMgr.Event.Clear.As.Pos.z           = 0;
            SGameMgr.Event.Clear.As.OPos.x          = 0;
            SGameMgr.Event.Clear.As.OPos.y          = 0;
            SGameMgr.Event.Clear.As.OPos.z          = 0;
            SGameMgr.Event.Clear.As.Spd.dx          = 0;
            SGameMgr.Event.Clear.As.Spd.dy          = 0;
            SGameMgr.Event.Clear.As.Spd.sx          = 0;
            SGameMgr.Event.Clear.As.Spd.sy          = 0;


            //----終了処理メニュー
            SGameMgr.SelectContinue.Val         = 0;
            SGameMgr.SelectContinue.Type        = SELECT_RETRY_H;
            SGameMgr.SelectContinue.No          = 0;
            SGameMgr.SelectContinue.Wt          = 0;
            SGameMgr.SelectContinue.FadeFlag    = 0;

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
            Task.user[1]        = ALL_CLEAR_1_SCRIPT_BASE;
            Task.user[2]        = ALL_CLEAR_1_SCRIPT_NUM;
            CreateTask(&Task);


#ifdef __DEBUG_SEES__
            // フェードInします
            GameMgr.FadeFlag = FadeIn;
#endif

            break;
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:
            //----終了メニューチェック
            if(++SGameMgr.Event.Timer > SEES_GAME_ALL_CLEAR_EVENT_END_TIME){
                SGameMgr.Event.EndFlag          = 1;
                SGameMgr.Event.Clear.Dr.Status  = EVENT_DR_ANM_OFF;
                SGameMgr.Event.Clear.Ky.Status  = EVENT_KY_ANM_OFF;
            }

            //----
            switch(SGameMgr.Event.Clear.Mode)
            {
                case 0:
                    EventCongratulations();
                    break;
                case 1:
                    //3rd
                    if(!ip_task->user[1]){
                        if(--ip_task->user[0]<=0){
                            if(dSoundStatus == DslStatStandby){
                                ip_task->user[1]=1;
                                
                                //DR ANM OFF
                            //  SGameMgr.Event.Clear.Dr.Status  = EVENT_DR_ANM_OFF;
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
                                Task.user[0]        = SCRIPT_LINE_1;
                                Task.user[1]        = ALL_CLEAR_4_SCRIPT_BASE;
                                Task.user[2]        = ALL_CLEAR_4_SCRIPT_NUM;
                                CreateTask(&Task);
                            }
                        }
                    }

                    //hanabi
                    if(!ip_task->user[3]){
                        if(ip_task->user[1]){
                            if(--ip_task->user[2]<=0){
                                if(dSoundStatus == DslStatStandby){
                                    ip_task->user[3]=1;
                                    
                                    //DR ANM ON
                            //      SGameMgr.Event.Clear.Dr.Status  = EVENT_DR_ANM_ON;
                                    
                                    //ボーリーアニメセット
                                    ip_task->user[6]=1;

                                    //[♪]ガチャ
                                    ssPlaySe(SEES_SE_09);

                                    //[♪]ヒュー
                                    ssPlaySe(SEES_SE_10);

                                    //----花火打ち上げ
                                    Task.func       = FireworksTask;
                                    Task.priority   = TASK_NO_EVENT_FIREWORKS;
                                    Task.attribute  = ATTR_USER;
                                    Task.status     = TASK_NEW_ENTRY;
                                    Task.id         = TASK_NO_EVENT_FIREWORKS;
                                    Task.wait_time  = 0;
                                    Task.buf        = NULL;
                                    Task.name       = "FireworksTask";
                                    Task.mode       = TASK_MODE_INIT;
                                    CreateTask(&Task);
                                }
                            }
                        }
                    }

                    //last script
                    if(!ip_task->user[5]){
                        if(ip_task->user[3]){
                            if(--ip_task->user[4]<=0){
                                ip_task->user[5]=1;
                                
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
                                Task.user[0]        = SCRIPT_LINE_1;
                                Task.user[1]        = CLEAR_MAKENAI_SCRIPT_BASE;
                                Task.user[2]        = CLEAR_MAKENAI_SCRIPT_NUM;
                                CreateTask(&Task);
                            }
                        }
                    }

                    EventDr();
                    EventKy();
                    EventAs(ip_task->user[6]);
                    EventBg();
                    break;
                default:
            }





            //----もう一度プレイしますか？
            if(SGameMgr.Event.EndFlag)
            {
                if(SelectContinue(!SGameMgr.SelectContinue.FadeFlag))
                {//●ボタンが押された
                    if(!SGameMgr.SelectContinue.FadeFlag){
                        if((SGameMgr.SelectContinue.Val==0) && (SGameMgr.SelectContinue.Type==SELECT_RETRY_H))
                        {//もう一度プレイしますか？　はい
                            SGameMgr.SelectContinue.FadeFlag    = 1;
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
                        if( (SGameMgr.SelectContinue.Val==1) && (SGameMgr.SelectContinue.Type==SELECT_RETRY_H))
                        {//もう一度プレイしますか？　いいえ
                            SGameMgr.SelectContinue.Type    =SELECT_END_H;
                            SGameMgr.SelectContinue.Val     = 0;
                        }else
                        if((SGameMgr.SelectContinue.Type==SELECT_END_H) && (SGameMgr.SelectContinue.Val==0))
                        {//やめますか？　はい
                            SGameMgr.SelectContinue.FadeFlag    = 1;
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
                        if((SGameMgr.SelectContinue.Type==SELECT_END_H) && (SGameMgr.SelectContinue.Val==1))
                        {//やめますか？　いいえ
                            SGameMgr.SelectContinue.Type    = SELECT_RETRY_H;
                            SGameMgr.SelectContinue.Val     = 0;
                        }else
                        {
                            
                        }
                    }
                }else{
                    
                }
            }
            break;
        //----------------------------------------------------------------タスク終了
        case TASK_MODE_EXIT:
            //--------------------ここは２択
            //  (1)セレクトレベルへ
            //  (2)メインメニュー
            if((SGameMgr.SelectContinue.Val==0) && (SGameMgr.SelectContinue.Type==SELECT_RETRY_H))
            {
                //----セレクトレベルタスク
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
            {
                //----ゲームをおわります
                SGameMgr.ExitFlag=1;
            }
            
            //自分を削除
            ExitTask(ip_task->id);
            
            break;
        default:
    }

    return TRUE;
}



//-----------------------------------------------------------------------------
//  関数名  :SelectContinue
//
//  work    :クリアイベント後の選択
//  in      :int i_flag
//  out     :TRUE
//          :FALSE
//  note    :なし
//-----------------------------------------------------------------------------
static int SelectContinue(int i_flag)
{
    static int BupeAnmTable[] ={
        SEES_CHAR_EVENT_SELECT_CONTINUE_BUPE_00,
        SEES_CHAR_EVENT_SELECT_CONTINUE_BUPE_01,
    };

    static int MaruBatuTable[]={
        SEES_CHAR_EVENT_SELECT_CONTINUE_YES_LIGHT,  SEES_CHAR_EVENT_SELECT_CONTINUE_NO_DARK,
        SEES_CHAR_EVENT_SELECT_CONTINUE_YES_DARK,   SEES_CHAR_EVENT_SELECT_CONTINUE_NO_LIGHT,
    };

    SPRITE_DATA SpData;
    int o_ret;

    if(i_flag){
        //選択
        o_ret=FALSE;
        if(JstPad &  PADRright){
            o_ret=TRUE;
            //[♪]決定
            ssPlaySe(BUTONSE_MARU);
        }

        //選択
        if(JstPad &  PADLright || JstPad &  PADLleft){
            SGameMgr.SelectContinue.Val^=1;
            //[♪] レバー音
            ssPlaySe(BUTONSE_LEVER);
        }
    }


    //はい・いいえ
    SpData.No       = MaruBatuTable[SGameMgr.SelectContinue.Val*2];     //インデックス番号
    SpData.PosX     = 68+72;                                            //X位置
    SpData.PosY     = 73+57;                                            //Y位置
    SpData.PosZ     = PRIORITY_EVENT_MENU-2;                            //優先順位
    SpData.ScaleX   = SCALE10;                                          //スケールX
    SpData.ScaleY   = SCALE10;                                          //スケールY
    SpData.Rotate   = ROTATE000;                                        //回転角
    SpData.Reverse  = NOREVERS;                                         //反転コード
    DrawSprite( &SpData );                                              //スプライト描画

    SpData.No       = MaruBatuTable[SGameMgr.SelectContinue.Val*2+1];   //インデックス番号
    SpData.PosX     = 68+126;                                           //X位置
    SpData.PosY     = 73+57;                                            //Y位置
    SpData.PosZ     = PRIORITY_EVENT_MENU-2;                            //優先順位
    SpData.ScaleX   = SCALE10;                                          //スケールX
    SpData.ScaleY   = SCALE10;                                          //スケールY
    SpData.Rotate   = ROTATE000;                                        //回転角
    SpData.Reverse  = NOREVERS;                                         //反転コード
    DrawSprite( &SpData );                                              //スプライト描画

    //プレート文字
    switch(SGameMgr.SelectContinue.Type)
    {
        case SELECT_RETRY_H:
            SpData.No       = SEES_CHAR_EVENT_SELECT_CONTINUE_RETRY_H;  //インデックス番号
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
            SpData.No       = SEES_CHAR_EVENT_SELECT_CONTINUE_END_H;    //インデックス番号
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
            SpData.No       = SEES_CHAR_EVENT_SELECT_CONTINUE_CONTINUE_H;//インデックス番号
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
    if(++SGameMgr.SelectContinue.Wt>SELECT_LEVEL_PUPE_ANM_TIME){
        SGameMgr.SelectContinue.No^=1;
        SGameMgr.SelectContinue.Wt=0;
    }
    SpData.No       = BupeAnmTable[SGameMgr.SelectContinue.No]; //インデックス番号
    SpData.PosX     = 68+12;                                    //X位置
    SpData.PosY     = 73+34;                                    //Y位置
    SpData.PosZ     = PRIORITY_EVENT_MENU-10;                   //優先順位
    SpData.ScaleX   = SCALE10;                                  //スケールX
    SpData.ScaleY   = SCALE10;                                  //スケールY
    SpData.Rotate   = ROTATE000;                                //回転角
    SpData.Reverse  = NOREVERS;                                 //反転コード
    DrawSprite( &SpData );                                      //スプライト描画

    //プレート
    SpData.No       = SEES_CHAR_EVENT_SELECT_CONTINUE_PLATE;    //インデックス番号
    SpData.PosX     = 68;                                       //X位置
    SpData.PosY     = 73;                                       //Y位置
    SpData.PosZ     = PRIORITY_EVENT_MENU;                      //優先順位
    SpData.ScaleX   = SCALE10;                                  //スケールX
    SpData.ScaleY   = SCALE10;                                  //スケールY
    SpData.Rotate   = ROTATE000;                                //回転角
    SpData.Reverse  = NOREVERS;                                 //反転コード
    DrawSprite( &SpData );                                      //スプライト描画

    //えらぶ
    SpData.No       = SEES_CHAR_EVENT_SELECT_CONTINUE_ERABU;    //インデックス番号
    SpData.PosX     = (320-130)/2;                              //X位置
    SpData.PosY     = 206;                                      //Y位置
    SpData.PosZ     = PRIORITY_EVENT_MENU-1;                    //優先順位
    SpData.ScaleX   = SCALE10;                                  //スケールX
    SpData.ScaleY   = SCALE10;                                  //スケールY
    SpData.Rotate   = ROTATE000;                                //回転角
    SpData.Reverse  = NOREVERS;                                 //反転コード
    DrawSprite( &SpData );                                      //スプライト描画

    //けってい
    SpData.No       = SEES_CHAR_EVENT_SELECT_CONTINUE_KETEI;    //インデックス番号
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


//-----------------------------------------------------------------------------
//  関数名  :DrawNum
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
static void DrawNum(int i_num,int i_wsize,int *ip_numtbl,int i_x,int i_y,int i_z)
{
    int i,bx,by;
    int numarr[3];
    SPRITE_DATA SpData;


    if(i_num>999)   i_num=999;
    if(i_num<0)     i_num=0;

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
                    SpData.PosZ     = i_z-i;
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
                SpData.PosX     = bx;
                SpData.PosY     = by;
                SpData.PosZ     = i_z-i;
                SpData.ScaleX   = SCALE10;
                SpData.ScaleY   = SCALE10;
                SpData.Rotate   = ROTATE000;
                SpData.Reverse  = NOREVERS;
                DrawSprite( &SpData );
            }
        }else{
            //描画
            SpData.No       = ip_numtbl[numarr[i]];
            SpData.PosX     = bx;
            SpData.PosY     = by;
            SpData.PosZ     = i_z-i;
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
//  関数名  :DrawCard
//
//  work    :カード描画
//  in      :int i_type
//          :int i_no
//          :int i_side
//          :int i_x
//          :int i_y
//          :int i_z
//  out     :
//  note    :なし
//-----------------------------------------------------------------------------
static void DrawCard(int i_type,int i_no,int i_side,int i_x,int i_y,int i_z)
{
    SPRITE_DATA SpData;
    int i;


    if(i_no < 0 )   i_no=0;
    if(i_no >100 )  i_no=100;

    switch(i_type)
    {
        //--------------------------------------------箱
        case CARD_TYPE_BOX:
            
            if(i_no>10) i_no=10;
            
            if(i_side==CARD_SIDE_HEADS){
                for(i=0;i<i_no;i++){
                    //----果物
                    //描画
                    SpData.No       = SEES_CHAR_GAME_FRUITS_RED;
                    SpData.PosX     = i_x + ApplePosTable[i].x;
                    SpData.PosY     = i_y + ApplePosTable[i].y;
                    SpData.PosZ     = i_z-1;
                    SpData.ScaleX   = SCALE10;
                    SpData.ScaleY   = SCALE10;
                    SpData.Rotate   = ROTATE000;
                    SpData.Reverse  = NOREVERS;
                    DrawSprite( &SpData );
                }
                
                //----箱
                //描画
                SpData.No       = SEES_CHAR_GAME_BOX;
                SpData.PosX     = i_x;
                SpData.PosY     = i_y;
                SpData.PosZ     = i_z;
                SpData.ScaleX   = SCALE10;
                SpData.ScaleY   = SCALE10;
                SpData.Rotate   = ROTATE000;
                SpData.Reverse  = NOREVERS;
                DrawSprite( &SpData );
            }else{
                //----箱
                //描画
                SpData.No       = SEES_CHAR_GAME_BOX_AMI;
                SpData.PosX     = i_x;
                SpData.PosY     = i_y;
                SpData.PosZ     = i_z;
                SpData.ScaleX   = SCALE10;
                SpData.ScaleY   = SCALE10;
                SpData.Rotate   = ROTATE000;
                SpData.Reverse  = NOREVERS;
                DrawSprite( &SpData );
            }
            
            break;
        //--------------------------------------------カ－ド
        case CARD_TYPE_STAR:
            
            if(i_side==CARD_SIDE_HEADS){
                //----数字
                if(i_no<10){
                    DrawNum(    i_no,   WIDTH_SMALL_FONT,   SmallNumSpriteTable,    i_x-4,  i_y+4,  i_z-1);
                }else
                if(i_no<100){
                    DrawNum(    i_no,   WIDTH_SMALL_FONT,   SmallNumSpriteTable,    i_x,    i_y+4,  i_z-1);
                }else{
                    DrawNum(    i_no,   WIDTH_SMALL_FONT,   SmallNumSpriteTable,    i_x+2,  i_y+4,  i_z-1);
                }
                
                //----カード
                //描画
                SpData.No       = SEES_CHAR_GAME_NEW_CARD_WAKU;
                SpData.PosX     = i_x;
                SpData.PosY     = i_y;
                SpData.PosZ     = i_z;
                SpData.ScaleX   = SCALE10;
                SpData.ScaleY   = SCALE10;
                SpData.Rotate   = ROTATE000;
                SpData.Reverse  = NOREVERS;
                DrawSprite( &SpData );
            }else{
                //----カード
                //描画
                SpData.No       = SEES_CHAR_GAME_NEW_STAR_CARD;
                SpData.PosX     = i_x;
                SpData.PosY     = i_y;
                SpData.PosZ     = i_z;
                SpData.ScaleX   = SCALE10;
                SpData.ScaleY   = SCALE10;
                SpData.Rotate   = ROTATE000;
                SpData.Reverse  = NOREVERS;
                DrawSprite( &SpData );
            }
            break;
        default:
    }
}




//-----------------------------------------------------------------------------
//  関数名  :DrawBox
//
//  work    :箱描画
//  in      :int i_count
//          :int i_no
//          :int i_x
//          :int i_y
//          :int i_z
//  out     :なし
//  note    :なし
//-----------------------------------------------------------------------------
static void DrawBox(int i_count,int i_no,int i_x,int i_y,int i_z)
{
    SPRITE_DATA SpData;
    int i;

    if(i_no>10)     i_no    = 10;
    if(i_count>10)  i_count = 10;
    
    for(i=0;i<i_no;i++)
    {
        //----果物
        if(i_count > i )    SpData.No = SEES_CHAR_GAME_FRUITS_YELLOW;
        else                SpData.No = SEES_CHAR_GAME_FRUITS_RED;
        
        SpData.PosX     = i_x + ApplePosTable[i].x;
        SpData.PosY     = i_y + ApplePosTable[i].y;
        SpData.PosZ     = i_z-1;
        SpData.ScaleX   = SCALE10;
        SpData.ScaleY   = SCALE10;
        SpData.Rotate   = ROTATE000;
        SpData.Reverse  = NOREVERS;
        DrawSprite( &SpData );
    }
    
    //----箱
    SpData.No       = SEES_CHAR_GAME_BOX;
    SpData.PosX     = i_x;
    SpData.PosY     = i_y;
    SpData.PosZ     = i_z;
    SpData.ScaleX   = SCALE10;
    SpData.ScaleY   = SCALE10;
    SpData.Rotate   = ROTATE000;
    SpData.Reverse  = NOREVERS;
    DrawSprite( &SpData );
}




//-----------------------------------------------------------------------------
//  関数名  :SetDrawFlagUserCard
//
//  work    :ユーザーの描画フラグセット
//  in      :int i_no
//  out     :なし
//  note    :なし
//-----------------------------------------------------------------------------
static void SetDrawFlagUserCard(int i_no)
{
    //  Ky - 13579
    //  Dr - 02468
    switch(i_no)
    {
        case 0:
            SGameMgr.Dr.Card[0].DrawFlag    = 1;
            break;
        case 1:
            SGameMgr.Ky.Card[0].DrawFlag    = 1;
            break;
        case 2:
            SGameMgr.Dr.Card[1].DrawFlag    = 1;
            break;
        case 3:
            SGameMgr.Ky.Card[1].DrawFlag    = 1;
            break;
        case 4:
            SGameMgr.Dr.Card[2].DrawFlag    = 1;
            break;
        case 5:
            SGameMgr.Ky.Card[2].DrawFlag    = 1;
            break;
        case 6:
            SGameMgr.Dr.Card[3].DrawFlag    = 1;
            break;
        case 7:
            SGameMgr.Ky.Card[3].DrawFlag    = 1;
            break;
        case 8:
            SGameMgr.Dr.Card[4].DrawFlag    = 1;
            break;
        case 9:
            SGameMgr.Ky.Card[4].DrawFlag    = 1;
            break;
        default:
    }
}




//-----------------------------------------------------------------------------
//  関数名  :EventCongratulations
//
//  work    :おめでとう
//  in      :なし
//  out     :なし
//  note    :なし
//-----------------------------------------------------------------------------
static void EventCongratulations(void)
{
    SPRITE_DATA SpData;
    TASK Task;


    if(SGameMgr.Event.Timer > SEES_GAME_EVENT_CONGRATULATION_END_TIME)
    {//花火へ
        SGameMgr.Event.Clear.Mode = 1;

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

        if(SGameMgr.AllClearFlag){
            Task.user[1]        = ALL_CLEAR_3_SCRIPT_BASE;
            Task.user[2]        = ALL_CLEAR_3_SCRIPT_NUM;
        }else{
            Task.user[1]        = CLEAR_2_SCRIPT_BASE;
            Task.user[2]        = CLEAR_2_SCRIPT_NUM;
        }
        CreateTask(&Task);
    }

    if(++SGameMgr.Event.Clear.Sup.Anm.Data.wt > SEES_GAME_EVENT_ANM_WAIT_TIME){
        SGameMgr.Event.Clear.Sup.Anm.Data.wt    = 0;
        SGameMgr.Event.Clear.Sup.Anm.Index      ^=1;
    }

    //プレート
    SpData.No       = SEES_CHAR_EVENT_WIN_PLATE;    //インデックス番号
    SpData.PosX     = 70;                           //X位置
    SpData.PosY     = 206;                          //Y位置
    SpData.PosZ     = PRIORITY_BG-2;                //優先順位
    SpData.ScaleX   = SCALE10;                      //スケールX
    SpData.ScaleY   = SCALE10;                      //スケールY
    SpData.Rotate   = ROTATE000;                    //回転角
    SpData.Reverse  = NOREVERS;                     //反転コード
    DrawSprite( &SpData );                          //スプライト描画

    //背景左
    SpData.No       = ClearEventCongratulationSpriteTable[SGameMgr.Event.Clear.Sup.Anm.Index*2 + 0].No;
    SpData.PosX     = 0;
    SpData.PosY     = 0;
    SpData.PosZ     = PRIORITY_BG;
    SpData.ScaleX   = SCALE10;
    SpData.ScaleY   = SCALE10;
    SpData.Rotate   = ROTATE000;
    SpData.Reverse  = NOREVERS;
    DrawSprite( &SpData );

    //背景右
    SpData.No       = ClearEventCongratulationSpriteTable[SGameMgr.Event.Clear.Sup.Anm.Index*2 + 1].No;
    SpData.PosX     = 256;
    SpData.PosY     = 0;
    SpData.PosZ     = PRIORITY_BG-1;
    SpData.ScaleX   = SCALE10;
    SpData.ScaleY   = SCALE10;
    SpData.Rotate   = ROTATE000;
    SpData.Reverse  = NOREVERS;
    DrawSprite( &SpData );
}




//-----------------------------------------------------------------------------
//  関数名  :EventDr
//
//  work    :イベントDr
//  in      :なし
//  out     :なし
//  note    :なし
//-----------------------------------------------------------------------------
static void EventDr(void)
{
    SPRITE_DATA SpData;


    switch(SGameMgr.Event.Clear.Dr.Status)
    {
        case EVENT_DR_ANM_OFF:
            break;
        case EVENT_DR_ANM_ON:
            if(++SGameMgr.Event.Clear.Dr.Anm.Data.wt > SEES_GAME_EVENT_ANM_WAIT_TIME){
                SGameMgr.Event.Clear.Dr.Anm.Data.wt = 0;
                SGameMgr.Event.Clear.Dr.Anm.Index   ^= 1;
            }
            break;
        default:
    }
    //プレート
    SpData.No       = ClearEventDrSpriteTable[SGameMgr.Event.Clear.Dr.Anm.Index].No;    //インデックス番号
    SpData.PosX     = ClearEventDrSpriteTable[SGameMgr.Event.Clear.Dr.Anm.Index].Ofx;   //X位置
    SpData.PosY     = ClearEventDrSpriteTable[SGameMgr.Event.Clear.Dr.Anm.Index].Ofy;   //Y位置
    SpData.PosZ     = PRIORITY_CAST;    //優先順位
    SpData.ScaleX   = SCALE10;          //スケールX
    SpData.ScaleY   = SCALE10;          //スケールY
    SpData.Rotate   = ROTATE000;        //回転角
    SpData.Reverse  = NOREVERS;         //反転コード
    DrawSprite( &SpData );              //スプライト描画
}




//-----------------------------------------------------------------------------
//  関数名  :EventKy
//
//  work    :イベントKy
//  in      :なし
//  out     :なし
//  note    :なし
//-----------------------------------------------------------------------------
static void EventKy(void)
{
    SPRITE_DATA SpData;

    switch(SGameMgr.Event.Clear.Ky.Status)
    {
        case EVENT_DR_ANM_OFF:
            break;
        case EVENT_DR_ANM_ON:
            if(++SGameMgr.Event.Clear.Ky.Anm.Data.wt > SEES_GAME_EVENT_ANM_WAIT_TIME){
                SGameMgr.Event.Clear.Ky.Anm.Data.wt = 0;
                SGameMgr.Event.Clear.Ky.Anm.Index   ^= 1;
            }
            break;
        default:
    }

    //プレート
    SpData.No       = ClearEventKySpriteTable[SGameMgr.Event.Clear.Ky.Anm.Index].No;    //インデックス番号
    SpData.PosX     = ClearEventKySpriteTable[SGameMgr.Event.Clear.Ky.Anm.Index].Ofx;   //X位置
    SpData.PosY     = ClearEventKySpriteTable[SGameMgr.Event.Clear.Ky.Anm.Index].Ofy;   //Y位置
    SpData.PosZ     = PRIORITY_CAST;    //優先順位
    SpData.ScaleX   = SCALE10;          //スケールX
    SpData.ScaleY   = SCALE10;          //スケールY
    SpData.Rotate   = ROTATE000;        //回転角
    SpData.Reverse  = NOREVERS;         //反転コード
    DrawSprite( &SpData );              //スプライト描画
}




//-----------------------------------------------------------------------------
//  関数名  :EventAs
//
//  work    :イベントアシスタントと機械
//  in      :int    i_no
//  out     :なし
//  note    :なし
//-----------------------------------------------------------------------------
static void EventAs(int i_no)
{
    SPRITE_DATA SpData;

    //体
    SpData.No       = ClearEventAsSpriteTable[0].No;    //インデックス番号
    SpData.PosX     = ClearEventAsSpriteTable[0].Ofx;   //X位置
    SpData.PosY     = ClearEventAsSpriteTable[0].Ofy;   //Y位置
    SpData.PosZ     = PRIORITY_CAST;                    //優先順位
    SpData.ScaleX   = SCALE10;                          //スケールX
    SpData.ScaleY   = SCALE10;                          //スケールY
    SpData.Rotate   = ROTATE000;                        //回転角
    SpData.Reverse  = NOREVERS;                         //反転コード
    DrawSprite( &SpData );                              //スプライト描画

    //手
    SpData.No       = ClearEventAsSpriteTable[1 + i_no].No; //インデックス番号
    SpData.PosX     = ClearEventAsSpriteTable[1 + i_no].Ofx;//X位置
    SpData.PosY     = ClearEventAsSpriteTable[1 + i_no].Ofy;//Y位置
    SpData.PosZ     = PRIORITY_CAST;                        //優先順位
    SpData.ScaleX   = SCALE10;                              //スケールX
    SpData.ScaleY   = SCALE10;                              //スケールY
    SpData.Rotate   = ROTATE000;                            //回転角
    SpData.Reverse  = NOREVERS;                             //反転コード
    DrawSprite( &SpData );                                  //スプライト描画

//  //機械
//  SpData.No       = ClearEventAsSpriteTable[3].No;    //インデックス番号
//  SpData.PosX     = ClearEventAsSpriteTable[3].Ofx;   //X位置
//  SpData.PosY     = ClearEventAsSpriteTable[3].Ofy;   //Y位置
//  SpData.PosZ     = PRIORITY_CAST;    //優先順位
//  SpData.ScaleX   = SCALE10;          //スケールX
//  SpData.ScaleY   = SCALE10;          //スケールY
//  SpData.Rotate   = ROTATE000;        //回転角
//  SpData.Reverse  = NOREVERS;         //反転コード
//  DrawSprite( &SpData );              //スプライト描画
}




//-----------------------------------------------------------------------------
//  関数名  :EventBg
//
//  work    :イベント背景
//  in      :なし
//  out     :なし
//  note    :なし
//-----------------------------------------------------------------------------
static void EventBg(void)
{
    SPRITE_DATA SpData;

    //描画
    SpData.No       = SEES_CHAR_EVENT_EVENT_BG_00;
    SpData.PosX     = 0;
    SpData.PosY     = 0;
    SpData.PosZ     = PRIORITY_BG;
    SpData.ScaleX   = SCALE10;
    SpData.ScaleY   = SCALE10;
    SpData.Rotate   = ROTATE000;
    SpData.Reverse  = NOREVERS;
    DrawSprite( &SpData );

    //描画
    SpData.No       = SEES_CHAR_EVENT_EVENT_BG_01;
    SpData.PosX     = 256;
    SpData.PosY     = 0;
    SpData.PosZ     = PRIORITY_BG;
    SpData.ScaleX   = SCALE10;
    SpData.ScaleY   = SCALE10;
    SpData.Rotate   = ROTATE000;
    SpData.Reverse  = NOREVERS;
    DrawSprite( &SpData );
}




//-----------------------------------------------------------------------------
//  関数名  :ChangePlayerCursorIndex
//
//  work    :カーソルインデックスを選択可能な位置へセット
//  in      :int    i_effective     選択可能範囲
//  out     :TRUE   セット成功
//          :FALSE  セット失敗（選択できない）
//  note    :なし
//-----------------------------------------------------------------------------
static int ChangePlayerCursorIndex(void)
{
    int i;

    for(i=0;i<SGameMgr.Player.EffectiveIndexNum;i++)
    {
        if(SGameMgr.Ky.Card[i].Data.Flag==1)
        {
            SGameMgr.Player.AnswerIndex = i;
            return TRUE;
        }
    }
    return FALSE;
}




#ifdef __DEBUG_SEES__
//-----------------------------------------------------------------------------
//  関数名 :DebugGameSpriteTask
//
//  work   :デバッグゲームスプライトタスク
//  in     :TASK*       タスクポインタ
//  out    :TRUE
//  note   :なし
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
            //----
            ip_task->mode = TASK_MODE_MAIN;

            //----texture read sram -> vram
            if((file_read(SeesGameTextureFile[0].fn,LoadAddress)) == -1)
            {//read error
                return FALSE;
            }
            
            //----texture init
            TexInit( SEES_GAME_TIM_NUM, &SeesGameTextureImage[SEES_GAME_TIM_POS] );
            TimImgData = SeesGameTextureImage;
            
            //----ゲーム用スプライト登録
            EntrySprite( SeesGameSpriteData );

            //----
            SpIndex     = 0;
            SpEntryNum  = GetEntrySpriteNum();
            Counter     = 0;
            FlushFlag   = 0;

#ifdef __DEBUG_SEES__
            // フェードInします
            GameMgr.FadeFlag = FadeIn;
#endif

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


            SpData.No       = SpIndex;                                      //インデックス番号
            SpData.PosX     = (320 - SeesGameSpriteData[SpIndex].Width)  / 2;   //X位置
            SpData.PosY     = (240 - SeesGameSpriteData[SpIndex].Height) / 2;   //Y位置
            SpData.PosZ     = 10;                                           //優先順位
            SpData.ScaleX   = SCALE10;                                      //スケールX
            SpData.ScaleY   = SCALE10;                                      //スケールY
            SpData.Rotate   = ROTATE000;                                    //回転角
            SpData.Reverse  = NOREVERS;                                     //反転コード
            DrawSprite( &SpData );                                          //スプライト描画

            //info
            FntPrint("SNO=%d/%d\n", SpIndex,SpEntryNum-1 );
            FntPrint("OfX=%d\n",    SeesGameSpriteData[SpIndex].OffSetX );      //TIMの中のスプライト左上開始X位置
            FntPrint("OfY=%d\n",    SeesGameSpriteData[SpIndex].OffSetY );      //TIMの中のスプライト左上開始Y位置
            FntPrint("W__=%d\n",    SeesGameSpriteData[SpIndex].Width   );      //TIMの中のテクスチャの幅
            FntPrint("H__=%d\n",    SeesGameSpriteData[SpIndex].Height  );      //TIMの中のテクスチャの高さ
            FntPrint("PNO=%d\n",    SeesGameSpriteData[SpIndex].PaletteNo );    //TIMの中のテクスチャパレット番号
            FntPrint("CNT=%d\n",    ++Counter );



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
//  work   :デバッグイベントスプライトタスク
//  in     :TASK*       タスクポインタ
//  out    :TRUE
//  note   :なし
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
            //----
            ip_task->mode = TASK_MODE_MAIN;

            //----texture read sram -> vram
            if((file_read(SeesEventTextureFile[0].fn,LoadAddress)) == -1)
            {//read error
                return FALSE;
            }
            
            //----texture init
            TexInit( SEES_EVENT_TIM_NUM, &SeesEventTextureImage[SEES_EVENT_TIM_POS] );
            TimImgData = SeesEventTextureImage;
            
            //----スプライト登録
            EntrySprite( SeesEventSpriteData );
    
            //----
            SpIndex     = 0;
            SpEntryNum  = GetEntrySpriteNum();
            Counter     = 0;
            FlushFlag   = 0;

#ifdef __DEBUG_SEES__
            // フェードInします
            GameMgr.FadeFlag = FadeIn;
#endif

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


            SpData.No       = SpIndex;                                      //インデックス番号
            SpData.PosX     = (320 - SeesEventSpriteData[SpIndex].Width)  / 2;  //X位置
            SpData.PosY     = (240 - SeesEventSpriteData[SpIndex].Height) / 2;  //Y位置
            SpData.PosZ     = 10;                                           //優先順位
            SpData.ScaleX   = SCALE10;                                      //スケールX
            SpData.ScaleY   = SCALE10;                                      //スケールY
            SpData.Rotate   = ROTATE000;                                    //回転角
            SpData.Reverse  = NOREVERS;                                     //反転コード
            DrawSprite( &SpData );                                          //スプライト描画

            //info
            FntPrint("SNO=%d/%d\n", SpIndex,SpEntryNum-1 );
            FntPrint("OfX=%d\n",    SeesEventSpriteData[SpIndex].OffSetX );     //TIMの中のスプライト左上開始X位置
            FntPrint("OfY=%d\n",    SeesEventSpriteData[SpIndex].OffSetY );     //TIMの中のスプライト左上開始Y位置
            FntPrint("W__=%d\n",    SeesEventSpriteData[SpIndex].Width   );     //TIMの中のテクスチャの幅
            FntPrint("H__=%d\n",    SeesEventSpriteData[SpIndex].Height  );     //TIMの中のテクスチャの高さ
            FntPrint("PNO=%d\n",    SeesEventSpriteData[SpIndex].PaletteNo );   //TIMの中のテクスチャパレット番号
            FntPrint("CNT=%d\n",    ++Counter );

            break;
        case TASK_MODE_EXIT:
            break;
        default:
            break;
    }
}

#endif


//-----------------------------------------------------------------------------
// end of SEES.C
//-----------------------------------------------------------------------------