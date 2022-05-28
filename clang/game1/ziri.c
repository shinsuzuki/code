//-----------------------------------------------------------------------------
// ZIRI.C
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
#include "ZIRI.H"
//-----------------------------------------------------------------------------
//  define
//-----------------------------------------------------------------------------
//----debug sw「デバッグ時はコメントを外してください」
//  #define __DEBUG_ZIRI__


//テクスチャー枚数と位置
#define ZIRI_TIM_POS                        0+4
#define ZIRI_TIM_NUM                        17

//----システム部
#define TIM_POS_ZIRI_EVENT_FONT             0       //選択処理テクスチャ
#define TIM_POS_ZIRI_EVENT_YORNO            1       //選択処理テクスチャ

//---- ゲーム部（イベントとゲーム部のテクスチャを統合：2003年03月13日/12時48分）
#define TIM_POS_ZIRI_GAME_BG_A00        0+4
#define TIM_POS_ZIRI_GAME_BG_A01        1+4
#define TIM_POS_ZIRI_GAME_BG_B00        2+4
#define TIM_POS_ZIRI_GAME_BG_B01        3+4
#define TIM_POS_ZIRI_GAME_C02           4+4
#define TIM_POS_ZIRI_GAME_C03           5+4
#define TIM_POS_ZIRI_GAME_C06           6+4
#define TIM_POS_ZIRI_GAME_PARTS         7+4
#define TIM_POS_ZIRI_EVENT_BAKU00       8+4
#define TIM_POS_ZIRI_EVENT_BAKU01       9+4
#define TIM_POS_ZIRI_EVENT_BG_D00       10+4
#define TIM_POS_ZIRI_EVENT_BG_D01       11+4
#define TIM_POS_ZIRI_EVENT_C00          12+4
#define TIM_POS_ZIRI_EVENT_C01          13+4
#define TIM_POS_ZIRI_EVENT_C04          14+4
#define TIM_POS_ZIRI_EVENT_C05          15+4
#define TIM_POS_ZIRI_GAME_NEEDLE        16+4


//----ゲームキャラ番号
enum{
    ZIRI_CHAR_GAME_SELECT_LEVEL_BG_00,          //レベル選択用背景１
    ZIRI_CHAR_GAME_SELECT_LEVEL_BG_01,          //レベル選択用背景2
    ZIRI_CHAR_GAME_GAME_BG_00,                  //ゲーム中背景１
    ZIRI_CHAR_GAME_GAME_BG_01,                  //ゲーム中背景2
    ZIRI_CHAR_GAME_CLOCKMAN_00,                 //とけいマンA00     　　上段　　（41,28）　（204,28）
    ZIRI_CHAR_GAME_CLOCKMAN_01,                 //とけいマンA01       　　下段　　（0,102）　（85,102）　（165,102）　（246,102）
    ZIRI_CHAR_GAME_CLOCKMAN_02,                 //とけいマンB00
    ZIRI_CHAR_GAME_CLOCKMAN_03,                 //とけいマンB01
    ZIRI_CHAR_GAME_CLOCKMAN_04,                 //とけいマンC00
    ZIRI_CHAR_GAME_CLOCKMAN_05,                 //とけいマンC01
    ZIRI_CHAR_GAME_CLOCKMAN_06,                 //とけいマンD00
    ZIRI_CHAR_GAME_CLOCKMAN_07,                 //とけいマンD01
    ZIRI_CHAR_GAME_CLOCKMAN_08,                 //とけいマンE00
    ZIRI_CHAR_GAME_ARROW_LEFT,                  //左向き矢印
    ZIRI_CHAR_GAME_ARROW_UP,                    //上向き矢印
    ZIRI_CHAR_GAME_ARROW_RIGHT,                 //右向き矢印
    ZIRI_CHAR_GAME_CLOCKMAN_SMALL_00,           //とけいマンアニメ00
    ZIRI_CHAR_GAME_CLOCKMAN_SMALL_01,           //とけいマンアニメ01
    ZIRI_CHAR_GAME_CLOCKMAN_APPEAR_00,          //とけいマン登場登場１  92,160/97,69    
    ZIRI_CHAR_GAME_CLOCKMAN_APPEAR_01,          //とけいマン登場登場２  100,130         
    ZIRI_CHAR_GAME_CLOCKMAN_APPEAR_02,          //とけいマン登場登場３  100,106         
    ZIRI_CHAR_GAME_CLOCKMAN_APPEAR_03,          //とけいマン登場登場４  114,62          
    ZIRI_CHAR_GAME_CLOCKMAN_09,                 //とけいマンE01
    ZIRI_CHAR_GAME_CLOCKMAN_10,                 //とけいマンF00
    ZIRI_CHAR_GAME_CLOCKMAN_11,                 //とけいマンF01
    ZIRI_CHAR_GAME_CLOCKMAN_12,                 //とけいマンG00
    ZIRI_CHAR_GAME_CLOCKMAN_13,                 //とけいマンG01
    ZIRI_CHAR_GAME_CLOCKMAN_BREAK_00,           //こわれたとけいマン
    ZIRI_CHAR_GAME_CLOCKMAN_APPEAR_04,          //胴体
    ZIRI_CHAR_GAME_CLOCKMAN_APPEAR_04_FOOT_00,  //足A       0,93
    ZIRI_CHAR_GAME_CLOCKMAN_APPEAR_04_FOOT_01,  //足B       -10,86
    ZIRI_CHAR_GAME_LIGHT_GREEN,                 //信号用緑      ※表示座標　　（115,16）から横に13ドット単位で7個並べて下さい。
    ZIRI_CHAR_GAME_LIGHT_YELLOW,                //信号用黄色
    ZIRI_CHAR_GAME_LIGHT_RED,                   //信号用赤
    ZIRI_CHAR_GAME_CLOCK_NUM_00,                //「0」数字表示座標　（134,85）　（146,85）　　　（166,85）　（178,85）
    ZIRI_CHAR_GAME_CLOCK_NUM_01,                //「1」
    ZIRI_CHAR_GAME_CLOCK_NUM_02,                //「2」
    ZIRI_CHAR_GAME_CLOCK_NUM_03,                //「3」
    ZIRI_CHAR_GAME_CLOCK_NUM_04,                //「4」
    ZIRI_CHAR_GAME_CLOCK_NUM_05,                //「5」
    ZIRI_CHAR_GAME_CLOCK_NUM_06,                //「6」
    ZIRI_CHAR_GAME_CLOCK_NUM_07,                //「7」
    ZIRI_CHAR_GAME_CLOCK_NUM_08,                //「8」
    ZIRI_CHAR_GAME_CLOCK_NUM_09,                //「9」
    ZIRI_CHAR_GAME_CLOCK_NUM_CORON,             //「:」コロン表示座標　　（156,85）
    ZIRI_CHAR_GAME_PLATE_CONGRATULATIONS,       //「おめでとう」プレート    　129,81
    ZIRI_CHAR_GAME_FUSE,                        //導火線        184,33
    ZIRI_CHAR_GAME_LONG_HAND_00,                //時計長針 0分  ※時計の針の座標は別テキスト（clock.txt)を参照してください。
    ZIRI_CHAR_GAME_LONG_HAND_05,                //時計長針 5分  
    ZIRI_CHAR_GAME_LONG_HAND_10,                //時計長針 10分
    ZIRI_CHAR_GAME_LONG_HAND_15,                //時計長針 15分
    ZIRI_CHAR_GAME_LONG_HAND_20,                //時計長針 20分
    ZIRI_CHAR_GAME_LONG_HAND_25,                //時計長針 25分
    ZIRI_CHAR_GAME_LONG_HAND_30,                //時計長針 30分
    ZIRI_CHAR_GAME_LONG_HAND_35,                //時計長針 35分
    ZIRI_CHAR_GAME_LONG_HAND_40,                //時計長針 40分
    ZIRI_CHAR_GAME_LONG_HAND_45,                //時計長針 45分
    ZIRI_CHAR_GAME_LONG_HAND_50,                //時計長針 50分
    ZIRI_CHAR_GAME_LONG_HAND_55,                //時計長針 55分
    ZIRI_CHAR_GAME_SHORT_HAND_00_24,            //時計短針 00/24    
    ZIRI_CHAR_GAME_SHORT_HAND_01_24,            //時計短針 01/24
    ZIRI_CHAR_GAME_SHORT_HAND_02_24,            //時計短針 02/24
    ZIRI_CHAR_GAME_SHORT_HAND_03_24,            //時計短針 03/24
    ZIRI_CHAR_GAME_SHORT_HAND_04_24,            //時計短針 04/24
    ZIRI_CHAR_GAME_SHORT_HAND_05_24,            //時計短針 05/24
    ZIRI_CHAR_GAME_SHORT_HAND_06_24,            //時計短針 06/24
    ZIRI_CHAR_GAME_SHORT_HAND_07_24,            //時計短針 07/24
    ZIRI_CHAR_GAME_SHORT_HAND_08_24,            //時計短針 08/24
    ZIRI_CHAR_GAME_SHORT_HAND_09_24,            //時計短針 09/24
    ZIRI_CHAR_GAME_SHORT_HAND_10_24,            //時計短針 10/24
    ZIRI_CHAR_GAME_SHORT_HAND_11_24,            //時計短針 11/24
    ZIRI_CHAR_GAME_SHORT_HAND_12_24,            //時計短針 12/24
    ZIRI_CHAR_GAME_SHORT_HAND_13_24,            //時計短針 13/24
    ZIRI_CHAR_GAME_SHORT_HAND_14_24,            //時計短針 14/24
    ZIRI_CHAR_GAME_SHORT_HAND_15_24,            //時計短針 15/24
    ZIRI_CHAR_GAME_SHORT_HAND_16_24,            //時計短針 16/24
    ZIRI_CHAR_GAME_SHORT_HAND_17_24,            //時計短針 17/24
    ZIRI_CHAR_GAME_SHORT_HAND_18_24,            //時計短針 18/24
    ZIRI_CHAR_GAME_SHORT_HAND_19_24,            //時計短針 19/24
    ZIRI_CHAR_GAME_SHORT_HAND_20_24,            //時計短針 20/24
    ZIRI_CHAR_GAME_SHORT_HAND_21_24,            //時計短針 21/24
    ZIRI_CHAR_GAME_SHORT_HAND_22_24,            //時計短針 22/24
    ZIRI_CHAR_GAME_SHORT_HAND_23_24,            //時計短針 23/24
    ZIRI_CHAR_GAME_DANTYOU_00,                  //団長アニメ00
    ZIRI_CHAR_GAME_DANTYOU_01,                  //団長アニメ01
    ZIRI_CHAR_GAME_DANIN_FUUSENN_BLUE_00,       //団員（風船）アニメ00（青風船）
    ZIRI_CHAR_GAME_DANIN_FUUSENN_BLUE_01,       //団員（風船）アニメ00（青風船）
    ZIRI_CHAR_GAME_DANIN_FUUSENN_ORANGE_00,     //団員（風船）アニメ07（橙風船）
    ZIRI_CHAR_GAME_DANIN_FUUSENN_ORANGE_01,     //団員（風船）アニメ07（橙風船）
    ZIRI_CHAR_GAME_DANIN_HATA_TATE_00,          //団員（旗）アニメ00
    ZIRI_CHAR_GAME_DANIN_HATA_TATE_01,          //団員（旗）アニメ01
    ZIRI_CHAR_GAME_DANIN_HATA_YOKO_01,          //団員（ピンク旗）アニメ00
    ZIRI_CHAR_GAME_DANIN_HATA_YOKO_02,          //団員（ピンク旗）アニメ01
    ZIRI_CHAR_GAME_SELECT_LEVEL_CURSOR,         //カーソル（レベル選択時に使用）
    ZIRI_CHAR_GAME_SELECT_LEVEL_PLATE_LIGHT,    //レベル選択用チップ
    ZIRI_CHAR_GAME_SELECT_LEVEL_PLATE_DARK,     //レベル選択用チップ
    ZIRI_CHAR_GAME_SELECT_LEVEL_NUM_1,          //レベル選択用数字1
    ZIRI_CHAR_GAME_SELECT_LEVEL_NUM_2,          //レベル選択用数字2
    ZIRI_CHAR_GAME_SELECT_LEVEL_NUM_3,          //レベル選択用数字3
    ZIRI_CHAR_GAME_SELECT_LEVEL_NUM_4,          //レベル選択用数字4
    ZIRI_CHAR_GAME_SELECT_LEVEL_NUM_5,          //レベル選択用数字5
    ZIRI_CHAR_GAME_CURSOR_FINGER,               //指カーソル
    ZIRI_CHAR_GAME_CLOCKMAN_14,                 //とけいマン
    ZIRI_CHAR_GAME_CLOCKMAN_15,                 //とけいマン
    ZIRI_CHAR_GAME_CLOCKMAN_16,                 //とけいマン
    ZIRI_CHAR_GAME_CLOCKMAN_BREAK_01,           //こわれたとけいマン
    ZIRI_CHAR_GAME_CLOCKMAN_BREAK_02,           //こわれたとけいマン
    ZIRI_CHAR_GAME_CLOCKMAN_BREAK_03,           //こわれたとけいマン
    ZIRI_CHAR_EVENT_BAKU_00,                    //エフェクト1   表示座標　（6,18）
    ZIRI_CHAR_EVENT_BAKU_01,                    //エフェクト2
    ZIRI_CHAR_EVENT_BG_FLUSH_00,                //背景１－０
    ZIRI_CHAR_EVENT_BG_FLUSH_01,                //背景２－０
    ZIRI_CHAR_EVENT_BG_FLUSH_02,                //背景１－１
    ZIRI_CHAR_EVENT_BG_FLUSH_03,                //背景２－１
    ZIRI_CHAR_EVENT_CLOCMAN_BREAK_00,           //ぼろぼろとけいマンA,ぼろぼろトケイマンBとアニメさせて下さい。82,63
    ZIRI_CHAR_EVENT_PLATE_YATA,                 //やったねパーツ　（ゲーム成功時のトケイマンの上に重ねて表示させてください。）      109,90          
    ZIRI_CHAR_EVENT_CLOCKMAN_LEFT_ARM_02,       //腕パーツA　（ぼかし小）　※トケイマン本体　（ぼかし小）に重ねてください。78,48
    ZIRI_CHAR_EVENT_CLOCKMAN_LEFT_ARM_03,       //腕パーツA　（ぼかし大）　※トケイマン本体　（ぼかし大）に重ねてください。 78,48
    ZIRI_CHAR_EVENT_CLOCKMAN_RIGHT_ARM_02,      //腕パーツB　（ぼかし小）　※トケイマン本体　（ぼかし小）に重ねてください。202,17
    ZIRI_CHAR_EVENT_CLOCKMAN_RIGHT_ARM_03,      //腕パーツB　（ぼかし大）　※トケイマン本体　（ぼかし大）に重ねてください。     202,17
    ZIRI_CHAR_EVENT_CLOCMAN_BREAK_01,           //ぼろぼろとけいマンB　 82,63　　　ぼろぼろトケイマンAとアニメさせて下さい。
    ZIRI_CHAR_EVENT_JUMP_CLOCMAN_00,            //飛び出すトケイマン大A　（ゲーム成功時の画面でトケイマンのお腹の扉からでてきます。）108,95
    ZIRI_CHAR_EVENT_JUMP_CLOCMAN_01,            //飛び出すトケイマン大B　（ゲーム成功時の画面でトケイマンのお腹の扉からでてきます。）108,86
    ZIRI_CHAR_EVENT_JUMP_CLOCMAN_02,            //飛び出すトケイマン小　（ゲーム成功時の画面でトケイマンのお腹の扉からでてきます。）        121,105
    ZIRI_CHAR_EVENT_STAR_EFFECT_00,             //星エフェクトA00・A01　（ゲーム成功時に使用します。）      65,51　　　　A00
    ZIRI_CHAR_EVENT_STAR_EFFECT_01,             //星エフェクトA00・A01　（ゲーム成功時に使用します。）      199*55　　　　　A01
    ZIRI_CHAR_EVENT_STAR_EFFECT_02,             //星エフェクトB00・B01　（ゲーム成功時に使用します。）      44,46　　　　　　B00
    ZIRI_CHAR_EVENT_STAR_EFFECT_03,             //星エフェクトB00・B01　（ゲーム成功時に使用します。）      206,46　　　　　B01
    ZIRI_CHAR_EVENT_STAR_00,                    //星A       　　星A　（50,66）　（63,99）　（104,97）　（153,72）　（189,45）　（85,169）　（200,90）　（232,112）　（238,173）
    ZIRI_CHAR_EVENT_STAR_01,                    //星B     　　星B　（78,47）　（123,178）　（228,153）
    ZIRI_CHAR_EVENT_STAR_02,                    //星C     　　星C　（147,45）　（64,99）　（44,148）　（171,178）　（258,88）
    ZIRI_CHAR_EVENT_STAR_03,                    //星D     　　星D　（115,64）
    ZIRI_CHAR_EVENT_STAR_04,                    //星E     　　星E　（240,55）　（39,120）
    ZIRI_CHAR_EVENT_STAR_05,                    //星F     　　星F　（80,78）
    ZIRI_CHAR_EVENT_EFFECT_00,                  //エフェクト00      75,134
    ZIRI_CHAR_EVENT_EFFECT_01,                  //エフェクト01      210,131
    ZIRI_CHAR_EVENT_CLOCKMAM_BODY_00,           //トケイマン本体　（ノーマル）      98,27           
    ZIRI_CHAR_EVENT_CLOCKMAM_LEFT_ARM_00,       //腕パーツC00・C01　※トケイマン本体　（ノーマル）に重ねてください。    58,64               
    ZIRI_CHAR_EVENT_CLOCKMAM_RIGHT_ARM_00,      //腕パーツC00・C01　※トケイマン本体　（ノーマル）に重ねてください。    212,67              
    ZIRI_CHAR_EVENT_CLOCKMAM_LEFT_ARM_01,       //腕パーツD00・D01　※トケイマン本体　（ノーマル）に重ねてください。        78,48
    ZIRI_CHAR_EVENT_CLOCKMAM_RIGHT_ARM_01,      //腕パーツD00・D01　※トケイマン本体　（ノーマル）に重ねてください。        202,48
    ZIRI_CHAR_EVENT_CLOCKMAM_FADCE,             //顔パーツ　※トケイマン本体　（ノーマル）に重ねてください。            132,41
    ZIRI_CHAR_EVENT_CLOCKMAM_RIGHT_ARM_04,      //腕パーツE00・E01　※トケイマン本体　（ノーマル）に重ねてください。        212,33　　　E00
    ZIRI_CHAR_EVENT_CLOCKMAM_RIGHT_ARM_05,      //腕パーツE00・E01　※トケイマン本体　（ノーマル）に重ねてください。        202,17　　　E01
    ZIRI_CHAR_EVENT_CLOCK_PARTS,                //時計文字盤12時　（上記の腕パーツE01に重ねてください。）
    ZIRI_CHAR_EVENT_DOOR_00,                    //扉パーツ　　※トケイマン本体　（ノーマル）に重ねてください。139,112　　　扉基本
    ZIRI_CHAR_EVENT_DOOR_01,                    //扉パーツ　　※トケイマン本体　（ノーマル）に重ねてください。135,112　　　扉A00
    ZIRI_CHAR_EVENT_DOOR_02,                    //扉パーツ　　※トケイマン本体　（ノーマル）に重ねてください。159,112　　　扉A01
    ZIRI_CHAR_EVENT_DOOR_03,                    //扉パーツ　　※トケイマン本体　（ノーマル）に重ねてください。120,112　　　扉B00
    ZIRI_CHAR_EVENT_DOOR_04,                    //扉パーツ　　※トケイマン本体　（ノーマル）に重ねてください。178,112　　　扉B01
    ZIRI_CHAR_EVENT_DOOR_05,                    //扉パーツ　　※トケイマン本体　（ノーマル）に重ねてください。120,112　　　扉C00
    ZIRI_CHAR_EVENT_DOOR_06,                    //扉パーツ　　※トケイマン本体　（ノーマル）に重ねてください。178,112　　　扉C01
    ZIRI_CHAR_EVENT_DOOR_07,                    //扉パーツ　　※トケイマン本体　（ノーマル）に重ねてください。120,112　　　扉D00
    ZIRI_CHAR_EVENT_DOOR_08,                    //扉パーツ　　※トケイマン本体　（ノーマル）に重ねてください。178,112　　　扉D01
    ZIRI_CHAR_EVENT_CLOKMAM_BODY_01,            //トケイマン本体　（ぼかし小）      98,27
    ZIRI_CHAR_EVENT_CLOKMAM_BODY_02,            //□トケイマン本体　（ぼかし大）98,27
    ZIRI_CHAR_EVENT_SELECT_CONTINUE_PLATE,      //プレート
    ZIRI_CHAR_EVENT_SELECT_CONTINUE_YES_DARK,   //非選択・はい
    ZIRI_CHAR_EVENT_SELECT_CONTINUE_NO_DARK,    //非選択・いいえ
    ZIRI_CHAR_EVENT_SELECT_CONTINUE_YES_LIGHT,  //選択・はい
    ZIRI_CHAR_EVENT_SELECT_CONTINUE_NO_LIGHT,   //選択・いいえ
    ZIRI_CHAR_EVENT_SELECT_CONTINUE_BUPE_00,    //プーぺ１
    ZIRI_CHAR_EVENT_SELECT_CONTINUE_BUPE_01,    //プーぺ２
    ZIRI_CHAR_EVENT_SELECT_CONTINUE_RETRY_H,    //もういちど
    ZIRI_CHAR_EVENT_SELECT_CONTINUE_END_H,      //おわり
    ZIRI_CHAR_EVENT_SELECT_CONTINUE_CONTINUE_H, //つづけ
    ZIRI_CHAR_EVENT_SELECT_CONTINUE_CURSOR,     //指カーソル
    ZIRI_CHAR_EVENT_SELECT_CONTINUE_ERABU,      //えらぶ
    ZIRI_CHAR_EVENT_SELECT_CONTINUE_KETEI,      //けってい
    ZIRI_CHAR_EVENT_SELECT_CONTINUE_MENU,       //めにゅー
    ZIRI_CHAR_GAME_NEEDLE_SHORT_00,             //短針00
    ZIRI_CHAR_GAME_NEEDLE_SHORT_01,             //短針01
    ZIRI_CHAR_GAME_NEEDLE_SHORT_02,             //短針02
    ZIRI_CHAR_GAME_NEEDLE_SHORT_03,             //短針03
    ZIRI_CHAR_GAME_NEEDLE_SHORT_04,             //短針04
    ZIRI_CHAR_GAME_NEEDLE_SHORT_05,             //短針05
    ZIRI_CHAR_GAME_NEEDLE_SHORT_06,             //短針06
    ZIRI_CHAR_GAME_NEEDLE_SHORT_07,             //短針07
    ZIRI_CHAR_GAME_NEEDLE_SHORT_08,             //短針08
    ZIRI_CHAR_GAME_NEEDLE_SHORT_09,             //短針09
    ZIRI_CHAR_GAME_NEEDLE_SHORT_10,             //短針10
    ZIRI_CHAR_GAME_NEEDLE_SHORT_11,             //短針11
    ZIRI_CHAR_GAME_NEEDLE_SHORT_12,             //短針12
    ZIRI_CHAR_GAME_NEEDLE_SHORT_13,             //短針13
    ZIRI_CHAR_GAME_NEEDLE_SHORT_14,             //短針14
    ZIRI_CHAR_GAME_NEEDLE_SHORT_15,             //短針15
    ZIRI_CHAR_GAME_NEEDLE_SHORT_16,             //短針16
    ZIRI_CHAR_GAME_NEEDLE_SHORT_17,             //短針17
    ZIRI_CHAR_GAME_NEEDLE_SHORT_18,             //短針18
    ZIRI_CHAR_GAME_NEEDLE_SHORT_19,             //短針19
    ZIRI_CHAR_GAME_NEEDLE_SHORT_20,             //短針20
    ZIRI_CHAR_GAME_NEEDLE_SHORT_21,             //短針21
    ZIRI_CHAR_GAME_NEEDLE_SHORT_22,             //短針22
    ZIRI_CHAR_GAME_NEEDLE_SHORT_23,             //短針23
    ZIRI_CHAR_GAME_NEEDLE_SHORT_24,             //短針24
    ZIRI_CHAR_GAME_NEEDLE_SHORT_25,             //短針25
    ZIRI_CHAR_GAME_NEEDLE_SHORT_26,             //短針26
    ZIRI_CHAR_GAME_NEEDLE_SHORT_27,             //短針27
    ZIRI_CHAR_GAME_NEEDLE_SHORT_28,             //短針28
    ZIRI_CHAR_GAME_NEEDLE_SHORT_29,             //短針29
    ZIRI_CHAR_GAME_NEEDLE_SHORT_30,             //短針30
    ZIRI_CHAR_GAME_NEEDLE_SHORT_31,             //短針31
    ZIRI_CHAR_GAME_NEEDLE_SHORT_32,             //短針32
    ZIRI_CHAR_GAME_NEEDLE_SHORT_33,             //短針33
    ZIRI_CHAR_GAME_NEEDLE_SHORT_34,             //短針34
    ZIRI_CHAR_GAME_NEEDLE_SHORT_35,             //短針35
    ZIRI_CHAR_GAME_NEEDLE_SHORT_36,             //短針36
    ZIRI_CHAR_GAME_NEEDLE_SHORT_37,             //短針37
    ZIRI_CHAR_GAME_NEEDLE_SHORT_38,             //短針38
    ZIRI_CHAR_GAME_NEEDLE_SHORT_39,             //短針39
    ZIRI_CHAR_GAME_NEEDLE_SHORT_40,             //短針40
    ZIRI_CHAR_GAME_NEEDLE_SHORT_41,             //短針41
    ZIRI_CHAR_GAME_NEEDLE_SHORT_42,             //短針42
    ZIRI_CHAR_GAME_NEEDLE_SHORT_43,             //短針43
    ZIRI_CHAR_GAME_NEEDLE_SHORT_44,             //短針44
    ZIRI_CHAR_GAME_NEEDLE_SHORT_45,             //短針45
    ZIRI_CHAR_GAME_NEEDLE_SHORT_46,             //短針46
    ZIRI_CHAR_GAME_NEEDLE_SHORT_47,             //短針47
    ZIRI_CHAR_GAME_NEEDLE_LONG_00,              //長針00
    ZIRI_CHAR_GAME_NEEDLE_LONG_01,              //長針01
    ZIRI_CHAR_GAME_NEEDLE_LONG_02,              //長針02
    ZIRI_CHAR_GAME_NEEDLE_LONG_03,              //長針03
    ZIRI_CHAR_GAME_NEEDLE_LONG_04,              //長針04
    ZIRI_CHAR_GAME_NEEDLE_LONG_05,              //長針05
    ZIRI_CHAR_GAME_NEEDLE_LONG_06,              //長針06
    ZIRI_CHAR_GAME_NEEDLE_LONG_07,              //長針07
    ZIRI_CHAR_GAME_NEEDLE_LONG_08,              //長針08
    ZIRI_CHAR_GAME_NEEDLE_LONG_09,              //長針09
    ZIRI_CHAR_GAME_NEEDLE_LONG_10,              //長針10
    ZIRI_CHAR_GAME_NEEDLE_LONG_11,              //長針11
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
extern u_long   BG_A00_image[];
extern u_long   BG_A00_clut[];
extern u_long   BG_A01_image[];
extern u_long   BG_A01_clut[];
extern u_long   BG_B00_image[];
extern u_long   BG_B00_clut[];
extern u_long   BG_B01_image[];
extern u_long   BG_B01_clut[];
extern u_long   C02_image[];
extern u_long   C02_clut[];
extern u_long   C03_image[];
extern u_long   C03_clut[];
extern u_long   C06_image[];
extern u_long   C06_clut[];
extern u_long   PARTS_image[];
extern u_long   PARTS_clut[];

//EVENT
extern u_long   BAKU00_image[];
extern u_long   BAKU00_clut[];
extern u_long   BAKU01_image[];
extern u_long   BAKU01_clut[];
extern u_long   BG_C00_image[];
extern u_long   BG_C00_clut[];
extern u_long   BG_C01_image[];
extern u_long   BG_C01_clut[];
extern u_long   BG_D00_image[];
extern u_long   BG_D00_clut[];
extern u_long   BG_D01_image[];
extern u_long   BG_D01_clut[];
extern u_long   C00_image[];
extern u_long   C00_clut[];
extern u_long   C01_image[];
extern u_long   C01_clut[];
extern u_long   C04_image[];
extern u_long   C04_clut[];
extern u_long   C05_image[];
extern u_long   C05_clut[];
extern u_long   help_00_image[];
extern u_long   help_00_clut[];
extern u_long   ZNEEDLE_image[];
extern u_long   ZNEEDLE_clut[];


extern int      active; /* アクティブ(でない）描画領域 */
extern GsOT     Wot[2];
static GsBOXF   Box;
static GsBOXF   BoxDataBlack[] =    {0x00000000,  0,  0,320,240,0x00,0x00,0x00};
static GsBOXF   BoxDataWhite[] =    {0x00000000,  0,  0,320,240,0xFF,0xFF,0xFF};


//-----------------------------------------------------------------------------
//  variable
//-----------------------------------------------------------------------------
//------------------------------------------ゲーム管理
static ZIRI_GAME ZGameMgr;


//------------------------------------------ロードファイル名
//GAME
static TIMD ZiriTextureFile[] = {
    //  デモタイトル名、    BINファイル名
    {   "RCUBE3",           "\\TIM\\ZIRID.B;1"},
};


//------------------------------------------テクスチャデータ
//GAME
static GsIMAGE ZiriTextureImage[]=
{
    //                  tpos        size        image               pos         size        clut
    //-------------------------------------------------------------------------------------------------------
    {   TIM_COLOR_16,   384,0,      64,256,     font_image,         16,480,     16,6,       font_clut       },
    {   TIM_COLOR_16,   448,0,      64,256,     YorN_image,         0,480,      16,16,      YorN_clut       },
    {   TIM_COLOR_16,   512,0,      64,256,     help_00_image,      0,496,      16,2,       help_00_clut    },
    {   TIM_COLOR_16,   320,0,      64,256,     MMENU_image,        16,489,     16,7,       MMENU_clut      },
    //-------------------------------------------------------------------------------------------------------
    {   TIM_COLOR_256,  768,256,    128,256,    BG_A00_image,       0,508,      256,1,      BG_A00_clut     },
    {   TIM_COLOR_256,  640,256,    32,256,     BG_A01_image,       0,507,      256,1,      BG_A01_clut     },
    {   TIM_COLOR_256,  896,0,      128,256,    BG_B00_image,       0,510,      256,1,      BG_B00_clut     },
    {   TIM_COLOR_256,  672,256,    32,256,     BG_B01_image,       0,509,      256,1,      BG_B01_clut     },
    {   TIM_COLOR_16,   576,0,      64,256,     C02_image,          96,482,     16,2,       C02_clut        },
    {   TIM_COLOR_16,   512,256,    64,256,     C03_image,          96,485,     16,1,       C03_clut        },
    {   TIM_COLOR_16,   640,0,      64,256,     C06_image,          96,484,     16,1,       C06_clut        },
    {   TIM_COLOR_16,   704,0,      64,256,     PARTS_image,        128,480,    16,12,      PARTS_clut      },
    {   TIM_COLOR_16,   704,256,    64,256,     BAKU00_image,       96,487,     16,1,       BAKU00_clut     },
    {   TIM_COLOR_16,   576,256,    13,256,     BAKU01_image,       96,486,     16,1,       BAKU01_clut     },
    {   TIM_COLOR_16,   768,0,      64,256,     BG_D00_image,       96,480,     16,2,       BG_D00_clut     },
    {   TIM_COLOR_16,   589,256,    16,256,     BG_D01_image,       96,488,     16,2,       BG_D01_clut     },
    {   TIM_COLOR_16,   384,256,    64,256,     C00_image,          112,485,    16,7,       C00_clut        },
    {   TIM_COLOR_16,   832,0,      64,256,     C01_image,          96,490,     16,2,       C01_clut        },
    {   TIM_COLOR_16,   448,256,    64,256,     C04_image,          112,480,    16,3,       C04_clut        },
    {   TIM_COLOR_16,   320,256,    64,256,     C05_image,          112,483,    16,2,       C05_clut        },
    {   TIM_COLOR_16,   896,256,    64,256,     ZNEEDLE_image,      144,480,    16,1,       ZNEEDLE_clut    },
};


//------------------------------------------スプライト登録データ
static ENTRY_SPRITE_DATA ZiriSpriteData[] =
{
    //-----------------------------------------------------------------------------------------
    //  TexNo                       TimLX   TimLY   Height  Width   PalNo
    //---------------------------------------------------------------------------BGA_00,TIM]
    {   TIM_POS_ZIRI_GAME_BG_A00,   0,      0,      240,    256,    0   },              //レベル選択用背景１
    //---------------------------------------------------------------------------BGA_01,TIM]
    {   TIM_POS_ZIRI_GAME_BG_A01,   0,      0,      240,    64,     0   },              //レベル選択用背景2
    //---------------------------------------------------------------------------BGB_00,TIM]
    {   TIM_POS_ZIRI_GAME_BG_B00,   0,      0,      240,    256,    0   },              //ゲーム中背景１
    //---------------------------------------------------------------------------BGB_01,TIM]
    {   TIM_POS_ZIRI_GAME_BG_B01,   0,      0,      240,    64,     0   },              //ゲーム中背景2
    //---------------------------------------------------------------------------C02.TIM]
    {   TIM_POS_ZIRI_GAME_C02,      0,      0,      68,     74,     0   },              //とけいマンA00     　　上段　　（41,28）　（204,28）
    {   TIM_POS_ZIRI_GAME_C02,      74,     0,      68,     74,     0   },              //とけいマンA01       　　下段　　（0,102）　（85,102）　（165,102）　（246,102）
    {   TIM_POS_ZIRI_GAME_C02,      148,    0,      68,     74,     0   },              //とけいマンB00
    {   TIM_POS_ZIRI_GAME_C02,      0,      68,     68,     74,     0   },              //とけいマンB01
    {   TIM_POS_ZIRI_GAME_C02,      74,     68,     68,     74,     0   },              //とけいマンC00
    {   TIM_POS_ZIRI_GAME_C02,      148,    68,     68,     74,     0   },              //とけいマンC01
    {   TIM_POS_ZIRI_GAME_C02,      0,      136,    68,     74,     0   },              //とけいマンD00
    {   TIM_POS_ZIRI_GAME_C02,      74,     136,    68,     74,     0   },              //とけいマンD01
    {   TIM_POS_ZIRI_GAME_C02,      148,    136,    68,     74,     0   },              //とけいマンE00
    {   TIM_POS_ZIRI_GAME_C02,      0,      204,    36,     44,     1   },              //左向き矢印
    {   TIM_POS_ZIRI_GAME_C02,      44,     204,    36,     44,     1   },              //上向き矢印
    {   TIM_POS_ZIRI_GAME_C02,      88,     204,    36,     44,     1   },              //右向き矢印
    {   TIM_POS_ZIRI_GAME_C02,      132,    204,    28,     24,     1   },              //とけいマンアニメ00
    {   TIM_POS_ZIRI_GAME_C02,      156,    204,    28,     24,     1   },              //とけいマンアニメ01
    //---------------------------------------------------------------------------C03.TIM]
    {   TIM_POS_ZIRI_GAME_C03,      132,    123,    116,    115,    0   },              //とけいマン登場登場１  92,160/97,69    
    {   TIM_POS_ZIRI_GAME_C03,      0,      0,      123,    131,    0   },              //とけいマン登場登場２  100,130         
    {   TIM_POS_ZIRI_GAME_C03,      0,      123,    123,    131,    0   },              //とけいマン登場登場３  100,106         
    {   TIM_POS_ZIRI_GAME_C03,      132,    0,      116,    115,    0   },              //とけいマン登場登場４  114,62          
    //---------------------------------------------------------------------------C06,TIM]
    {   TIM_POS_ZIRI_GAME_C06,      0,      0,      68,     74,     0   },              //とけいマンE01
    {   TIM_POS_ZIRI_GAME_C06,      74,     0,      68,     74,     0   },              //とけいマンF00
    {   TIM_POS_ZIRI_GAME_C06,      148,    0,      68,     74,     0   },              //とけいマンF01
    {   TIM_POS_ZIRI_GAME_C06,      0,      68,     68,     74,     0   },              //とけいマンG00
    {   TIM_POS_ZIRI_GAME_C06,      74,     68,     68,     74,     0   },              //とけいマンG01
    {   TIM_POS_ZIRI_GAME_C06,      148,    68,     70,     74,     0   },              //こわれたとけいマン
    //---------------------------------------------------------------------------PARTS,TIM]
    {   TIM_POS_ZIRI_GAME_PARTS,    0,      0,      94,     72,     0   },              //胴体
    {   TIM_POS_ZIRI_GAME_PARTS,    0,      94,     34,     72,     0   },              //足A       0,93
    {   TIM_POS_ZIRI_GAME_PARTS,    72,     0,      29,     88,     0   },              //足B       -10,86
    {   TIM_POS_ZIRI_GAME_PARTS,    160,    0,      12,     12,     1   },              //信号用緑      ※表示座標　　（115,16）から横に13ドット単位で7個並べて下さい。
    {   TIM_POS_ZIRI_GAME_PARTS,    172,    0,      12,     12,     1   },              //信号用黄色
    {   TIM_POS_ZIRI_GAME_PARTS,    184,    0,      12,     12,     1   },              //信号用赤
    {   TIM_POS_ZIRI_GAME_PARTS,    72,     29,     17,     12,     2   },              //「0」数字表示座標　（134,85）　（146,85）　　　（166,85）　（178,85）
    {   TIM_POS_ZIRI_GAME_PARTS,    84,     29,     17,     12,     2   },              //「1」
    {   TIM_POS_ZIRI_GAME_PARTS,    96,     29,     17,     12,     2   },              //「2」
    {   TIM_POS_ZIRI_GAME_PARTS,    108,    29,     17,     12,     2   },              //「3」
    {   TIM_POS_ZIRI_GAME_PARTS,    120,    29,     17,     12,     2   },              //「4」
    {   TIM_POS_ZIRI_GAME_PARTS,    132,    29,     17,     12,     2   },              //「5」
    {   TIM_POS_ZIRI_GAME_PARTS,    144,    29,     17,     12,     2   },              //「6」
    {   TIM_POS_ZIRI_GAME_PARTS,    156,    29,     17,     12,     2   },              //「7」
    {   TIM_POS_ZIRI_GAME_PARTS,    168,    29,     17,     12,     2   },              //「8」
    {   TIM_POS_ZIRI_GAME_PARTS,    180,    29,     17,     12,     2   },              //「9」
    {   TIM_POS_ZIRI_GAME_PARTS,    192,    29,     17,     12,     2   },              //「:」コロン表示座標　　（156,85）
    {   TIM_POS_ZIRI_GAME_PARTS,    72,     46,     24,     66,     3   },              //「おめでとう」プレート    　129,81
    {   TIM_POS_ZIRI_GAME_PARTS,    160,    12,     16,     20,     4   },              //□導火線      184,33
    {   TIM_POS_ZIRI_GAME_PARTS,    0,      128,    12,     12,     5   },              //□時計長針0分 ※時計の針の座標は別テキスト（clock.txt)を参照してください。
    {   TIM_POS_ZIRI_GAME_PARTS,    12,     128,    12,     12,     5   },              //□時計長針5分 
    {   TIM_POS_ZIRI_GAME_PARTS,    24,     128,    12,     12,     5   },              //□時計長針10分
    {   TIM_POS_ZIRI_GAME_PARTS,    36,     128,    12,     12,     5   },              //□時計長針15分
    {   TIM_POS_ZIRI_GAME_PARTS,    48,     128,    12,     12,     5   },              //□時計長針20分
    {   TIM_POS_ZIRI_GAME_PARTS,    60,     128,    12,     12,     5   },              //□時計長針25分
    {   TIM_POS_ZIRI_GAME_PARTS,    72,     128,    12,     12,     5   },              //□時計長針30分
    {   TIM_POS_ZIRI_GAME_PARTS,    84,     128,    12,     12,     5   },              //□時計長針35分
    {   TIM_POS_ZIRI_GAME_PARTS,    96,     128,    12,     12,     5   },              //□時計長針40分
    {   TIM_POS_ZIRI_GAME_PARTS,    108,    128,    12,     12,     5   },              //□時計長針45分
    {   TIM_POS_ZIRI_GAME_PARTS,    120,    128,    12,     12,     5   },              //□時計長針50分
    {   TIM_POS_ZIRI_GAME_PARTS,    132,    128,    12,     12,     5   },              //□時計長針55分
    {   TIM_POS_ZIRI_GAME_PARTS,    0,      140,    6,      6,      5   },              //□時計短針    00/24
    {   TIM_POS_ZIRI_GAME_PARTS,    6,      140,    6,      6,      5   },              //□時計短針    01/24
    {   TIM_POS_ZIRI_GAME_PARTS,    12,     140,    6,      6,      5   },              //□時計短針    02/24
    {   TIM_POS_ZIRI_GAME_PARTS,    18,     140,    6,      6,      5   },              //□時計短針    03/24
    {   TIM_POS_ZIRI_GAME_PARTS,    24,     140,    6,      6,      5   },              //□時計短針    04/24
    {   TIM_POS_ZIRI_GAME_PARTS,    30,     140,    6,      6,      5   },              //□時計短針    05/24
    {   TIM_POS_ZIRI_GAME_PARTS,    36,     140,    6,      6,      5   },              //□時計短針    06/24
    {   TIM_POS_ZIRI_GAME_PARTS,    42,     140,    6,      6,      5   },              //□時計短針    07/24
    {   TIM_POS_ZIRI_GAME_PARTS,    48,     140,    6,      6,      5   },              //□時計短針    08/24
    {   TIM_POS_ZIRI_GAME_PARTS,    54,     140,    6,      6,      5   },              //□時計短針    09/24
    {   TIM_POS_ZIRI_GAME_PARTS,    60,     140,    6,      6,      5   },              //□時計短針    10/24
    {   TIM_POS_ZIRI_GAME_PARTS,    66,     140,    6,      6,      5   },              //□時計短針    11/24
    {   TIM_POS_ZIRI_GAME_PARTS,    72,     140,    6,      6,      5   },              //□時計短針    12/24
    {   TIM_POS_ZIRI_GAME_PARTS,    78,     140,    6,      6,      5   },              //□時計短針    13/24
    {   TIM_POS_ZIRI_GAME_PARTS,    84,     140,    6,      6,      5   },              //□時計短針    14/24
    {   TIM_POS_ZIRI_GAME_PARTS,    90,     140,    6,      6,      5   },              //□時計短針    15/24
    {   TIM_POS_ZIRI_GAME_PARTS,    96,     140,    6,      6,      5   },              //□時計短針    16/24
    {   TIM_POS_ZIRI_GAME_PARTS,    102,    140,    6,      6,      5   },              //□時計短針    17/24
    {   TIM_POS_ZIRI_GAME_PARTS,    108,    140,    6,      6,      5   },              //□時計短針    18/24
    {   TIM_POS_ZIRI_GAME_PARTS,    114,    140,    6,      6,      5   },              //□時計短針    19/24
    {   TIM_POS_ZIRI_GAME_PARTS,    120,    140,    6,      6,      5   },              //□時計短針    20/24
    {   TIM_POS_ZIRI_GAME_PARTS,    126,    140,    6,      6,      5   },              //□時計短針    21/24
    {   TIM_POS_ZIRI_GAME_PARTS,    132,    140,    6,      6,      5   },              //□時計短針    22/24
    {   TIM_POS_ZIRI_GAME_PARTS,    138,    140,    6,      6,      5   },              //□時計短針    23/24
    {   TIM_POS_ZIRI_GAME_PARTS,    0,      147,    42,     48,     6   },              //団長アニメ00
    {   TIM_POS_ZIRI_GAME_PARTS,    48,     147,    42,     48,     6   },              //団長アニメ01
    {   TIM_POS_ZIRI_GAME_PARTS,    0,      189,    33,     40,     6   },              //団員（風船）アニメ00（青風船）
    {   TIM_POS_ZIRI_GAME_PARTS,    40,     189,    33,     40,     6   },              //団員（風船）アニメ00（青風船）
    {   TIM_POS_ZIRI_GAME_PARTS,    0,      189,    33,     40,     7   },              //団員（風船）アニメ07（橙風船）
    {   TIM_POS_ZIRI_GAME_PARTS,    40,     189,    33,     40,     7   },              //団員（風船）アニメ07（橙風船）
    {   TIM_POS_ZIRI_GAME_PARTS,    80,     189,    33,     40,     6   },              //団員（旗）アニメ00
    {   TIM_POS_ZIRI_GAME_PARTS,    120,    189,    33,     40,     6   },              //団員（旗）アニメ01
    {   TIM_POS_ZIRI_GAME_PARTS,    160,    189,    33,     40,     8   },              //団員（ピンク旗）アニメ00
    {   TIM_POS_ZIRI_GAME_PARTS,    200,    189,    33,     40,     8   },              //団員（ピンク旗）アニメ01
    {   TIM_POS_ZIRI_GAME_PARTS,    96,     147,    14,     20,     9   },              //□カーソル（レベル選択時に使用）
    {   TIM_POS_ZIRI_GAME_PARTS,    96,     161,    9,      18,     9   },              //レベル選択用チップ
    {   TIM_POS_ZIRI_GAME_PARTS,    96,     161,    9,      18,     10  },              //レベル選択用チップ
    {   TIM_POS_ZIRI_GAME_PARTS,    96,     170,    10,     8,      11  },              //レベル選択用数字1
    {   TIM_POS_ZIRI_GAME_PARTS,    104,    170,    10,     8,      11  },              //レベル選択用数字2
    {   TIM_POS_ZIRI_GAME_PARTS,    112,    170,    10,     8,      11  },              //レベル選択用数字3
    {   TIM_POS_ZIRI_GAME_PARTS,    120,    170,    10,     8,      11  },              //レベル選択用数字4
    {   TIM_POS_ZIRI_GAME_PARTS,    128,    170,    10,     8,      11  },              //レベル選択用数字5
    //------------------------------------------------------------------------------------
    {   TIM_POS_ZIRI_EVENT_FONT,    24,     200,    24,     26,     2   },              //指カーソル
    //------------------------------------------------------------------------------------
    {   TIM_POS_ZIRI_GAME_C02,      0,      68,     14,     74,     0   },              //とけいマンB01
    {   TIM_POS_ZIRI_GAME_C02,      0,      68,     30,     74,     0   },              //とけいマンB01
    {   TIM_POS_ZIRI_GAME_C02,      0,      68,     50,     74,     0   },              //とけいマンB01
    {   TIM_POS_ZIRI_GAME_C06,      148,    68,     14,     74,     0   },              //こわれたとけいマン
    {   TIM_POS_ZIRI_GAME_C06,      148,    68,     30,     74,     0   },              //こわれたとけいマン
    {   TIM_POS_ZIRI_GAME_C06,      148,    68,     50,     74,     0   },              //こわれたとけいマン
    //------------------------------------------------------------------------------------[BAKU00,TIM]　（爆発エフェクト）
    {   TIM_POS_ZIRI_EVENT_BAKU00,  0,      0,      200,    256,    0   },              //エフェクト1           表示座標　（6,18）
    //------------------------------------------------------------------------------------[BGA_01,TIM]　（レベル選択用BG）
    {   TIM_POS_ZIRI_EVENT_BAKU01,  0,      0,      200,    50,     0   },              //エフェクト2               
    //------------------------------------------------------------------------------------[BGD_00,TIM]　（ゲーム成功時BG）
    {   TIM_POS_ZIRI_EVENT_BG_D00,  0,      0,      240,    256,    0   },              //背景１－０
    {   TIM_POS_ZIRI_EVENT_BG_D00,  0,      0,      240,    256,    1   },              //背景２－０
    //------------------------------------------------------------------------------------[BGD_01,TIM]　（ゲーム成功時BG）
    {   TIM_POS_ZIRI_EVENT_BG_D01,  0,      0,      240,    64,     0   },              //背景１－１
    {   TIM_POS_ZIRI_EVENT_BG_D01,  0,      0,      240,    64,     1   },              //背景２－１
    //------------------------------------------------------------------------------------[C00,TIM]
    {   TIM_POS_ZIRI_EVENT_C00,     0,      0,      149,    153,    0   },              //ぼろぼろとけいマンA,ぼろぼろトケイマンBとアニメさせて下さい。82,63　　　
    {   TIM_POS_ZIRI_EVENT_C00,     154,    0,      86,     100,    0   },              //やったねパーツ　（ゲーム成功時のトケイマンの上に重ねて表示させてください。）      109,90          
    {   TIM_POS_ZIRI_EVENT_C00,     154,    86,     63,     38,     1   },              //腕パーツA　（ぼかし小）　※トケイマン本体　（ぼかし小）に重ねてください。78,48
    {   TIM_POS_ZIRI_EVENT_C00,     192,    86,     63,     38,     2   },              //腕パーツA　（ぼかし大）　※トケイマン本体　（ぼかし大）に重ねてください。 78,48
    {   TIM_POS_ZIRI_EVENT_C00,     0,      149,    91,     50,     3   },              //腕パーツB　（ぼかし小）　※トケイマン本体　（ぼかし小）に重ねてください。202,17
    {   TIM_POS_ZIRI_EVENT_C00,     50,     149,    91,     50,     4   },              //腕パーツB　（ぼかし大）　※トケイマン本体　（ぼかし大）に重ねてください。     202,17
    //------------------------------------------------------------------------------------[C01,TIM]
    {   TIM_POS_ZIRI_EVENT_C01,     0,      0,      126,    144,    0   },              //ぼろぼろとけいマンB　 82,63　　　ぼろぼろトケイマンAとアニメさせて下さい。
    {   TIM_POS_ZIRI_EVENT_C01,     0,      126,    72,     102,    0   },              //飛び出すトケイマン大A　（ゲーム成功時の画面でトケイマンのお腹の扉からでてきます。）108,95
    {   TIM_POS_ZIRI_EVENT_C01,     140,    128,    72,     102,    0   },              //飛び出すトケイマン大B　（ゲーム成功時の画面でトケイマンのお腹の扉からでてきます。）108,86
    {   TIM_POS_ZIRI_EVENT_C01,     0,      198,    52,     74,     0   },              //飛び出すトケイマン小　（ゲーム成功時の画面でトケイマンのお腹の扉からでてきます。）        121,105
    {   TIM_POS_ZIRI_EVENT_C01,     144,    0,      36,     52,     1   },              //星エフェクトA00・A01　（ゲーム成功時に使用します。）      65,51　　　　A00
    {   TIM_POS_ZIRI_EVENT_C01,     198,    0,      36,     52,     1   },              //星エフェクトA00・A01　（ゲーム成功時に使用します。）      199*55　　　　　A01
    {   TIM_POS_ZIRI_EVENT_C01,     144,    36,     46,     74,     1   },              //星エフェクトB00・B01　（ゲーム成功時に使用します。）      44,46　　　　　　B00
    {   TIM_POS_ZIRI_EVENT_C01,     144,    82,     46,     74,     1   },              //星エフェクトB00・B01　（ゲーム成功時に使用します。）      206,46　　　　　B01
    {   TIM_POS_ZIRI_EVENT_C01,     218,    36,     14,     16,     1   },              //星A       　　星A　（50,66）　（63,99）　（104,97）　（153,72）　（189,45）　（85,169）　（200,90）　（232,112）　（238,173）
    {   TIM_POS_ZIRI_EVENT_C01,     218,    50,     14,     16,     1   },              //星B     　　星B　（78,47）　（123,178）　（228,153）
    {   TIM_POS_ZIRI_EVENT_C01,     218,    64,     14,     16,     1   },              //星C     　　星C　（147,45）　（64,99）　（44,148）　（171,178）　（258,88）
    {   TIM_POS_ZIRI_EVENT_C01,     218,    78,     14,     16,     1   },              //星D     　　星D　（115,64）
    {   TIM_POS_ZIRI_EVENT_C01,     218,    92,     14,     16,     1   },              //星E     　　星E　（240,55）　（39,120）
    {   TIM_POS_ZIRI_EVENT_C01,     218,    106,    14,     16,     1   },              //星F     　　星F　（80,78）
    {   TIM_POS_ZIRI_EVENT_C01,     102,    126,    20,     38,     1   },              //エフェクト00      75,134
    {   TIM_POS_ZIRI_EVENT_C01,     102,    147,    20,     38,     1   },              //エフェクト01      210,131
    //------------------------------------------------------------------------------------[C04,TIM]
    {   TIM_POS_ZIRI_EVENT_C04,     0,      0,      194,    122,    0   },              //トケイマン本体　（ノーマル）      98,27           
    {   TIM_POS_ZIRI_EVENT_C04,     122,    0,      55,     50,     0   },              //腕パーツC00・C01　※トケイマン本体　（ノーマル）に重ねてください。    58,64               
    {   TIM_POS_ZIRI_EVENT_C04,     172,    0,      55,     50,     0   },              //腕パーツC00・C01　※トケイマン本体　（ノーマル）に重ねてください。    212,67              
    {   TIM_POS_ZIRI_EVENT_C04,     122,    55,     63,     38,     0   },              //腕パーツD00・D01　※トケイマン本体　（ノーマル）に重ねてください。        78,48
    {   TIM_POS_ZIRI_EVENT_C04,     160,    55,     63,     38,     0   },              //腕パーツD00・D01　※トケイマン本体　（ノーマル）に重ねてください。        202,48
    {   TIM_POS_ZIRI_EVENT_C04,     198,    55,     38,     56,     0   },              //顔パーツ　※トケイマン本体　（ノーマル）に重ねてください。            132,41
    {   TIM_POS_ZIRI_EVENT_C04,     122,    118,    89,     64,     1   },              //腕パーツE00・E01　※トケイマン本体　（ノーマル）に重ねてください。        212,33　　　E00
    {   TIM_POS_ZIRI_EVENT_C04,     186,    118,    91,     50,     1   },              //腕パーツE00・E01　※トケイマン本体　（ノーマル）に重ねてください。        202,17　　　E01
    {   TIM_POS_ZIRI_EVENT_C04,     222,    0,      16,     16,     1   },              //時計文字盤12時　（上記の腕パーツE01に重ねてください。）
    {   TIM_POS_ZIRI_EVENT_C04,     0,      209,    40,     40,     2   },              //扉パーツ　　※トケイマン本体　（ノーマル）に重ねてください。139,112　　　扉基本
    {   TIM_POS_ZIRI_EVENT_C04,     40,     209,    40,     20,     2   },              //扉パーツ　　※トケイマン本体　（ノーマル）に重ねてください。135,112　　　扉A00
    {   TIM_POS_ZIRI_EVENT_C04,     60,     209,    40,     20,     2   },              //扉パーツ　　※トケイマン本体　（ノーマル）に重ねてください。159,112　　　扉A01
    {   TIM_POS_ZIRI_EVENT_C04,     80,     209,    40,     20,     2   },              //扉パーツ　　※トケイマン本体　（ノーマル）に重ねてください。120,112　　　扉B00
    {   TIM_POS_ZIRI_EVENT_C04,     100,    209,    40,     20,     2   },              //扉パーツ　　※トケイマン本体　（ノーマル）に重ねてください。178,112　　　扉B01
    {   TIM_POS_ZIRI_EVENT_C04,     120,    209,    40,     20,     2   },              //扉パーツ　　※トケイマン本体　（ノーマル）に重ねてください。120,112　　　扉C00
    {   TIM_POS_ZIRI_EVENT_C04,     140,    209,    40,     20,     2   },              //扉パーツ　　※トケイマン本体　（ノーマル）に重ねてください。178,112　　　扉C01
    {   TIM_POS_ZIRI_EVENT_C04,     160,    209,    40,     20,     2   },              //扉パーツ　　※トケイマン本体　（ノーマル）に重ねてください。120,112　　　扉D00
    {   TIM_POS_ZIRI_EVENT_C04,     180,    209,    40,     20,     2   },              //扉パーツ　　※トケイマン本体　（ノーマル）に重ねてください。178,112　　　扉D01
    //------------------------------------------------------------------------------------[C05,TIM]
    {   TIM_POS_ZIRI_EVENT_C05,     0,      0,      194,    122,    0   },              //トケイマン本体　（ぼかし小）      98,27
    {   TIM_POS_ZIRI_EVENT_C05,     122,    0,      194,    122,    1   },              //□トケイマン本体　（ぼかし大）98,27
    //-----------------------------------------------------------------------------------------[YorNo.TIM]
    {   TIM_POS_ZIRI_EVENT_YORNO,   0,      0,      115,    186,    0   },              //プレート
    {   TIM_POS_ZIRI_EVENT_YORNO,   0,      115,    40,     38,     1   },              //非選択・はい 74,57
    {   TIM_POS_ZIRI_EVENT_YORNO,   38,     115,    40,     44,     1   },              //非選択・いいえ 126,57
    {   TIM_POS_ZIRI_EVENT_YORNO,   82,     115,    40,     44,     2   },              //選択・はい 72,57
    {   TIM_POS_ZIRI_EVENT_YORNO,   126,    115,    40,     44,     2   },              //選択・いいえ 126,57
    {   TIM_POS_ZIRI_EVENT_YORNO,   186,    0,      69,     58,     3   },              //プーぺ１
    {   TIM_POS_ZIRI_EVENT_YORNO,   186,    69,     69,     58,     3   },              //プーぺ２
    {   TIM_POS_ZIRI_EVENT_YORNO,   0,      155,    14,     148,    4   },              //もういちど
    {   TIM_POS_ZIRI_EVENT_YORNO,   0,      170,    14,     148,    4   },              //おわり
    {   TIM_POS_ZIRI_EVENT_YORNO,   20,     20,     14,     148,    4   },              //つづけ
    //-----------------------------------------------------------------------------------------[font.TIM]
    {   TIM_POS_ZIRI_EVENT_FONT,    24,     200,    24,     26,     2   },              //指カーソル
    {   TIM_POS_ZIRI_EVENT_FONT,    0,      232,    15,     52,     4   },              //えらぶ
    {   TIM_POS_ZIRI_EVENT_FONT,    52,     232,    15,     52,     4   },              //けってい
    {   TIM_POS_ZIRI_EVENT_FONT,    104,    232,    15,     52,     4   },              //めにゅー
    //-----------------------------------------------------------------------------------------[緊急追加]
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*0,   22*0,   22,     22,     0   },              //短針00
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*1,   22*0,   22,     22,     0   },              //短針01
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*2,   22*0,   22,     22,     0   },              //短針02
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*3,   22*0,   22,     22,     0   },              //短針03
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*4,   22*0,   22,     22,     0   },              //短針04
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*5,   22*0,   22,     22,     0   },              //短針05
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*6,   22*0,   22,     22,     0   },              //短針06
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*7,   22*0,   22,     22,     0   },              //短針07
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*8,   22*0,   22,     22,     0   },              //短針08
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*9,   22*0,   22,     22,     0   },              //短針09
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*10,  22*0,   22,     22,     0   },              //短針10
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*0,   22*1,   22,     22,     0   },              //短針11
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*1,   22*1,   22,     22,     0   },              //短針12
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*2,   22*1,   22,     22,     0   },              //短針13
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*3,   22*1,   22,     22,     0   },              //短針14
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*4,   22*1,   22,     22,     0   },              //短針15
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*5,   22*1,   22,     22,     0   },              //短針16
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*6,   22*1,   22,     22,     0   },              //短針17
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*7,   22*1,   22,     22,     0   },              //短針18
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*8,   22*1,   22,     22,     0   },              //短針19
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*9,   22*1,   22,     22,     0   },              //短針20
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*10,  22*1,   22,     22,     0   },              //短針21
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*0,   22*2,   22,     22,     0   },              //短針22
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*1,   22*2,   22,     22,     0   },              //短針23
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*2,   22*2,   22,     22,     0   },              //短針24
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*3,   22*2,   22,     22,     0   },              //短針25
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*4,   22*2,   22,     22,     0   },              //短針26
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*5,   22*2,   22,     22,     0   },              //短針27
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*6,   22*2,   22,     22,     0   },              //短針28
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*7,   22*2,   22,     22,     0   },              //短針29
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*8,   22*2,   22,     22,     0   },              //短針30
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*9,   22*2,   22,     22,     0   },              //短針31
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*10,  22*2,   22,     22,     0   },              //短針32
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*0,   22*3,   22,     22,     0   },              //短針33
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*1,   22*3,   22,     22,     0   },              //短針34
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*2,   22*3,   22,     22,     0   },              //短針35
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*3,   22*3,   22,     22,     0   },              //短針36
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*4,   22*3,   22,     22,     0   },              //短針37
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*5,   22*3,   22,     22,     0   },              //短針38
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*6,   22*3,   22,     22,     0   },              //短針39
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*7,   22*3,   22,     22,     0   },              //短針40
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*8,   22*3,   22,     22,     0   },              //短針41
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*9,   22*3,   22,     22,     0   },              //短針42
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*10,  22*3,   22,     22,     0   },              //短針43
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*0,   22*4,   22,     22,     0   },              //短針44
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*1,   22*4,   22,     22,     0   },              //短針45
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*2,   22*4,   22,     22,     0   },              //短針46
    {   TIM_POS_ZIRI_GAME_NEEDLE,   22*3,   22*4,   22,     22,     0   },              //短針47
    {   TIM_POS_ZIRI_GAME_NEEDLE,   0,      120,    30,     30,     0   },              //長針00
    {   TIM_POS_ZIRI_GAME_NEEDLE,   30,     120,    30,     30,     0   },              //長針01
    {   TIM_POS_ZIRI_GAME_NEEDLE,   60,     120,    30,     30,     0   },              //長針02
    {   TIM_POS_ZIRI_GAME_NEEDLE,   90,     120,    30,     30,     0   },              //長針03
    {   TIM_POS_ZIRI_GAME_NEEDLE,   120,    120,    30,     30,     0   },              //長針04
    {   TIM_POS_ZIRI_GAME_NEEDLE,   150,    120,    30,     30,     0   },              //長針05
    {   TIM_POS_ZIRI_GAME_NEEDLE,   0,      150,    30,     30,     0   },              //長針06
    {   TIM_POS_ZIRI_GAME_NEEDLE,   30,     150,    30,     30,     0   },              //長針07
    {   TIM_POS_ZIRI_GAME_NEEDLE,   60,     150,    30,     30,     0   },              //長針08
    {   TIM_POS_ZIRI_GAME_NEEDLE,   90,     150,    30,     30,     0   },              //長針09
    {   TIM_POS_ZIRI_GAME_NEEDLE,   120,    150,    30,     30,     0   },              //長針10
    {   TIM_POS_ZIRI_GAME_NEEDLE,   150,    150,    30,     30,     0   },              //長針11
    //-----------------------------------------------------------------------------------------
    {   ENTRY_SPRITE_DATA_END,0,0,0,0,0 },
};


//------------------------------------------時間表示
static int ClockNumSpriteTable[]=
{
    ZIRI_CHAR_GAME_CLOCK_NUM_00,
    ZIRI_CHAR_GAME_CLOCK_NUM_01,
    ZIRI_CHAR_GAME_CLOCK_NUM_02,
    ZIRI_CHAR_GAME_CLOCK_NUM_03,
    ZIRI_CHAR_GAME_CLOCK_NUM_04,
    ZIRI_CHAR_GAME_CLOCK_NUM_05,
    ZIRI_CHAR_GAME_CLOCK_NUM_06,
    ZIRI_CHAR_GAME_CLOCK_NUM_07,
    ZIRI_CHAR_GAME_CLOCK_NUM_08,
    ZIRI_CHAR_GAME_CLOCK_NUM_09,
};

//------------------------------------------時計マン配置テーブル
static POS2D ClockManPosTable[]={
    {   0,      102 },      //CLOCK_POS_00
    {   41,     28  },      //CLOCK_POS_01
    {   85,     102 },      //CLOCK_POS_02
    {   165,    102 },      //CLOCK_POS_03
    {   204,    28  },      //CLOCK_POS_04
    {   246,    102 },      //CLOCK_POS_05
};


//------------------------------------------時計マンアニメベース
static int ClockManAnmBaseTable[]=
{
    CLOCKMAN_ANM_BASE_00,
    CLOCKMAN_ANM_BASE_01,
    CLOCKMAN_ANM_BASE_02,
    CLOCKMAN_ANM_BASE_03,
    CLOCKMAN_ANM_BASE_04,
    CLOCKMAN_ANM_BASE_05,
    CLOCKMAN_ANM_BASE_06,
    CLOCKMAN_ANM_BASE_07,
};


//------------------------------------------時計マンスプライトテーブル
static ZIRI_SPRITE_DATA ClockManSpriteTable[]=
{
    {   ZIRI_CHAR_GAME_CLOCKMAN_00,         0,      0       },  //時計マン_00
    {   ZIRI_CHAR_GAME_CLOCKMAN_01,         0,      0       },
    {   ZIRI_CHAR_GAME_CLOCKMAN_02,         0,      0       },  //時計マン_01
    {   ZIRI_CHAR_GAME_CLOCKMAN_03,         0,      0       },
    {   ZIRI_CHAR_GAME_CLOCKMAN_04,         0,      0       },  //時計マン_02
    {   ZIRI_CHAR_GAME_CLOCKMAN_05,         0,      0       },
    {   ZIRI_CHAR_GAME_CLOCKMAN_06,         0,      0       },  //時計マン_03
    {   ZIRI_CHAR_GAME_CLOCKMAN_07,         0,      0       },
    {   ZIRI_CHAR_GAME_CLOCKMAN_08,         0,      0       },  //時計マン_04
    {   ZIRI_CHAR_GAME_CLOCKMAN_09,         0,      0       },
    {   ZIRI_CHAR_GAME_CLOCKMAN_10,         0,      0       },  //時計マン_05
    {   ZIRI_CHAR_GAME_CLOCKMAN_11,         0,      0       },
    {   ZIRI_CHAR_GAME_CLOCKMAN_12,         0,      0       },  //時計マン_06
    {   ZIRI_CHAR_GAME_CLOCKMAN_13,         0,      0       },
    {   ZIRI_CHAR_GAME_CLOCKMAN_14,         0,      54-2    },  //通常つぶれ状態（頭のみ）
    {   ZIRI_CHAR_GAME_CLOCKMAN_14,         0,      54-2    },
    {   ZIRI_CHAR_GAME_CLOCKMAN_BREAK_01,   0,      54-2    },  //壊れつぶれ状態（頭のみ）
    {   ZIRI_CHAR_GAME_CLOCKMAN_BREAK_01,   0,      54-2    },
    {   ZIRI_CHAR_GAME_CLOCKMAN_16,         0,      18-2    },  //正解下降
    {   ZIRI_CHAR_GAME_CLOCKMAN_15,         0,      38-2    },
    {   ZIRI_CHAR_GAME_CLOCKMAN_15,         0,      38-2    },  //上昇
    {   ZIRI_CHAR_GAME_CLOCKMAN_16,         0,      18-2    },
    {   ZIRI_CHAR_GAME_CLOCKMAN_BREAK_03,   0,      18-2    },  //不正解下降
    {   ZIRI_CHAR_GAME_CLOCKMAN_BREAK_02,   0,      38-2    },
};


static ZIRI_SPRITE_DATA ClockHandOffsetTable[]=
{
    {   0,  0,      0   },  //時計マン_00
    {   0,  0,      0   },
    {   0,  0,      0   },  //時計マン_01
    {   0,  0,      0   },
    {   0,  0,      2   },  //時計マン_02
    {   0,  0,      2   },
    {   0,  0,      2   },  //時計マン_03
    {   0,  0,      2   },
    {   0,  0,      2   },  //時計マン_04
    {   0,  0,      2   },
    {   0,  0,      0   },  //時計マン_05
    {   0,  0,      0   },
    {   0,  0,      0   },  //時計マン_06
    {   0,  0,      0   },
    {   0,  0,      0   },  //通常つぶれ状態（頭のみ）
    {   0,  0,      0   },
    {   0,  0,      0   },  //壊れつぶれ状態（頭のみ）
    {   0,  0,      0   },
    {   0,  0,      0   },  //正解下降
    {   0,  0,      0   },
    {   0,  0,      0   },  //正解上昇
    {   0,  0,      0   },
    {   0,  0,      0   },  //不正解下降
    {   0,  0,      0   },
};


//------------------------------------------配置テーブル
static int ClockManPosDataTable[][MAX_CLOCKMAN_NUM]=
{
    CLOCK_POS_00,   CLOCK_POS_03,   CLOCK_POS_04,   CLOCK_POS_05,   CLOCK_POS_01,   CLOCK_POS_02,   //0
    CLOCK_POS_05,   CLOCK_POS_02,   CLOCK_POS_00,   CLOCK_POS_01,   CLOCK_POS_04,   CLOCK_POS_03,   //1
    CLOCK_POS_01,   CLOCK_POS_00,   CLOCK_POS_03,   CLOCK_POS_04,   CLOCK_POS_05,   CLOCK_POS_02,   //2
    CLOCK_POS_04,   CLOCK_POS_01,   CLOCK_POS_02,   CLOCK_POS_00,   CLOCK_POS_03,   CLOCK_POS_05,   //3
    CLOCK_POS_00,   CLOCK_POS_03,   CLOCK_POS_04,   CLOCK_POS_02,   CLOCK_POS_01,   CLOCK_POS_05,   //4
    CLOCK_POS_03,   CLOCK_POS_00,   CLOCK_POS_04,   CLOCK_POS_05,   CLOCK_POS_02,   CLOCK_POS_01,   //5
    CLOCK_POS_02,   CLOCK_POS_05,   CLOCK_POS_00,   CLOCK_POS_01,   CLOCK_POS_04,   CLOCK_POS_03,   //6
    CLOCK_POS_00,   CLOCK_POS_03,   CLOCK_POS_05,   CLOCK_POS_02,   CLOCK_POS_04,   CLOCK_POS_01,   //7
    CLOCK_POS_04,   CLOCK_POS_02,   CLOCK_POS_01,   CLOCK_POS_03,   CLOCK_POS_00,   CLOCK_POS_05,   //8
    CLOCK_POS_01,   CLOCK_POS_05,   CLOCK_POS_00,   CLOCK_POS_03,   CLOCK_POS_04,   CLOCK_POS_02,   //9
};


//------------------------------------------初期問題データ
static int FirstQuestionData[][FIRST_QUESTION_INDEX_NUM][MAX_CLOCKMAN_NUM]=
{
    {//Level-1
        {   CLOCK_00_00,    CLOCK_01_00,    CLOCK_02_00,    CLOCK_03_00,    CLOCK_04_00,    CLOCK_05_00     },
        {   CLOCK_06_00,    CLOCK_07_00,    CLOCK_08_00,    CLOCK_09_00,    CLOCK_10_00,    CLOCK_11_00     },
        {   CLOCK_02_00,    CLOCK_03_00,    CLOCK_04_00,    CLOCK_05_00,    CLOCK_06_00,    CLOCK_07_00     },
        {   CLOCK_03_00,    CLOCK_04_00,    CLOCK_05_00,    CLOCK_06_00,    CLOCK_07_00,    CLOCK_08_00     },
        {   CLOCK_04_00,    CLOCK_05_00,    CLOCK_06_00,    CLOCK_07_00,    CLOCK_08_00,    CLOCK_09_00     },
    },
    {//Level-2
        {   CLOCK_04_00,    CLOCK_04_30,    CLOCK_02_00,    CLOCK_02_30,    CLOCK_10_00,    CLOCK_10_30     },
        {   CLOCK_01_00,    CLOCK_01_30,    CLOCK_05_00,    CLOCK_05_30,    CLOCK_11_00,    CLOCK_11_30     },
        {   CLOCK_07_00,    CLOCK_07_30,    CLOCK_01_00,    CLOCK_01_30,    CLOCK_09_00,    CLOCK_09_30     },
        {   CLOCK_03_00,    CLOCK_03_30,    CLOCK_06_00,    CLOCK_06_30,    CLOCK_00_00,    CLOCK_00_30     },
        {   CLOCK_01_00,    CLOCK_01_30,    CLOCK_08_00,    CLOCK_08_30,    CLOCK_00_00,    CLOCK_00_30     },
    },
    {//Level-3
        {   CLOCK_00_15,    CLOCK_00_45,    CLOCK_02_15,    CLOCK_02_45,    CLOCK_08_15,    CLOCK_08_45     },
        {   CLOCK_11_15,    CLOCK_11_45,    CLOCK_04_15,    CLOCK_04_45,    CLOCK_07_15,    CLOCK_07_45     },
        {   CLOCK_06_15,    CLOCK_06_45,    CLOCK_01_15,    CLOCK_01_45,    CLOCK_05_15,    CLOCK_05_45     },
        {   CLOCK_09_15,    CLOCK_09_45,    CLOCK_10_15,    CLOCK_10_45,    CLOCK_03_15,    CLOCK_03_45     },
        {   CLOCK_05_15,    CLOCK_05_45,    CLOCK_00_15,    CLOCK_00_45,    CLOCK_11_15,    CLOCK_11_45     },
    },
    {//Level-4
        {   CLOCK_10_15,    CLOCK_10_45,    CLOCK_01_00,    CLOCK_01_30,    CLOCK_02_15,    CLOCK_02_45     },
        {   CLOCK_00_15,    CLOCK_00_45,    CLOCK_05_00,    CLOCK_05_30,    CLOCK_08_15,    CLOCK_08_45     },
        {   CLOCK_03_00,    CLOCK_03_30,    CLOCK_07_00,    CLOCK_07_30,    CLOCK_04_15,    CLOCK_04_45     },
        {   CLOCK_09_00,    CLOCK_09_30,    CLOCK_11_00,    CLOCK_11_30,    CLOCK_06_15,    CLOCK_06_45     },
        {   CLOCK_07_00,    CLOCK_07_30,    CLOCK_04_15,    CLOCK_04_45,    CLOCK_11_00,    CLOCK_11_30     },
    },
    {//Level-5
        {   CLOCK_00_25,    CLOCK_00_35,    CLOCK_07_20,    CLOCK_07_40,    CLOCK_05_05,    CLOCK_05_55     },
        {   CLOCK_03_20,    CLOCK_03_40,    CLOCK_08_25,    CLOCK_08_35,    CLOCK_05_05,    CLOCK_05_55     },
        {   CLOCK_06_10,    CLOCK_06_50,    CLOCK_01_05,    CLOCK_01_55,    CLOCK_10_10,    CLOCK_10_50     },
        {   CLOCK_09_05,    CLOCK_09_55,    CLOCK_06_10,    CLOCK_06_50,    CLOCK_11_20,    CLOCK_11_40     },
        {   CLOCK_03_20,    CLOCK_03_40,    CLOCK_07_20,    CLOCK_07_40,    CLOCK_10_10,    CLOCK_10_50     },
    },
};


//------------------------------------------問題データ
static QUESTION_DATA QuestionData[MAX_GAME_LEVEL]=
{
    {   //-------------------- LEVEL-1
        CLOCK_00_00,CLOCK_01_00,CLOCK_02_00,CLOCK_03_00,CLOCK_04_00,CLOCK_05_00,
        CLOCK_06_00,CLOCK_07_00,CLOCK_08_00,CLOCK_09_00,CLOCK_10_00,CLOCK_11_00,
        CLOCK_00_00,CLOCK_01_00,CLOCK_02_00,CLOCK_03_00,CLOCK_04_00,CLOCK_05_00,
        CLOCK_06_00,CLOCK_07_00,CLOCK_08_00,CLOCK_09_00,CLOCK_10_00,CLOCK_11_00
    },
    {   //-------------------- LEVEL-2
        CLOCK_00_00,CLOCK_01_00,CLOCK_02_00,CLOCK_03_00,CLOCK_04_00,CLOCK_05_00,
        CLOCK_06_00,CLOCK_07_00,CLOCK_08_00,CLOCK_09_00,CLOCK_10_00,CLOCK_11_00,
        CLOCK_00_30,CLOCK_01_30,CLOCK_02_30,CLOCK_03_30,CLOCK_04_30,CLOCK_05_30,
        CLOCK_06_30,CLOCK_07_30,CLOCK_08_30,CLOCK_09_30,CLOCK_10_30,CLOCK_11_30
    },
    {   //-------------------- LEVEL-3
        CLOCK_00_15,CLOCK_00_45,CLOCK_01_15,CLOCK_01_45,CLOCK_02_15,CLOCK_02_45,
        CLOCK_03_15,CLOCK_03_45,CLOCK_04_15,CLOCK_04_45,CLOCK_05_15,CLOCK_05_45,
        CLOCK_06_15,CLOCK_06_45,CLOCK_07_15,CLOCK_07_45,CLOCK_08_15,CLOCK_08_45,
        CLOCK_09_15,CLOCK_09_45,CLOCK_10_15,CLOCK_10_45,CLOCK_11_15,CLOCK_11_45
    },
    {   //-------------------- LEVEL-4
        CLOCK_00_15,CLOCK_00_45,CLOCK_01_00,CLOCK_01_30,CLOCK_02_15,CLOCK_02_45,
        CLOCK_03_00,CLOCK_03_30,CLOCK_04_15,CLOCK_04_45,CLOCK_05_00,CLOCK_05_30,
        CLOCK_06_15,CLOCK_06_45,CLOCK_07_00,CLOCK_07_30,CLOCK_08_15,CLOCK_08_45,
        CLOCK_09_00,CLOCK_09_30,CLOCK_10_15,CLOCK_10_45,CLOCK_11_00,CLOCK_11_30
    },
    {   //-------------------- LEVEL-5
        CLOCK_00_25,CLOCK_00_35,CLOCK_01_05,CLOCK_01_55,CLOCK_02_10,CLOCK_02_50,
        CLOCK_03_20,CLOCK_03_40,CLOCK_04_25,CLOCK_04_35,CLOCK_05_05,CLOCK_05_55,
        CLOCK_06_10,CLOCK_06_50,CLOCK_07_20,CLOCK_07_40,CLOCK_08_25,CLOCK_08_35,
        CLOCK_09_05,CLOCK_09_55,CLOCK_10_10,CLOCK_10_50,CLOCK_11_20,CLOCK_11_40
    },
};


//------------------------------------------時間XAデータ
static XA_DATA ClockXaTable[]=
    {
        {   XA_FILE_ZIRI09,     6   },          //          CLOCK_00_00     000
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_00_05     001
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_00_10     002
        {   XA_FILE_ZIRI09,     7   },          //          CLOCK_00_15     003
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_00_20     004
        {   XA_FILE_ZIRI09,     8   },          //          CLOCK_00_25     005
        {   XA_FILE_ZIRI09,     9   },          //          CLOCK_00_30     006
        {   XA_FILE_ZIRI09,     10  },          //          CLOCK_00_35     007
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_00_40     008
        {   XA_FILE_ZIRI09,     11  },          //          CLOCK_00_45     009
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_00_50     010
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_00_55     011
        {   XA_FILE_ZIRI04,     0   },          //          CLOCK_01_00     012
        {   XA_FILE_ZIRI04,     1   },          //          CLOCK_01_05     013
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_01_10     014
        {   XA_FILE_ZIRI04,     2   },          //          CLOCK_01_15     015
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_01_20     016
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_01_25     017
        {   XA_FILE_ZIRI04,     3   },          //          CLOCK_01_30     018
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_01_35     019
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_01_40     020
        {   XA_FILE_ZIRI04,     4   },          //          CLOCK_01_45     021
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_01_50     022
        {   XA_FILE_ZIRI04,     5   },          //          CLOCK_01_55     023
        {   XA_FILE_ZIRI04,     6   },          //          CLOCK_02_00     024
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_02_05     025
        {   XA_FILE_ZIRI04,     7   },          //          CLOCK_02_10     026
        {   XA_FILE_ZIRI04,     8   },          //          CLOCK_02_15     027
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_02_20     028
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_02_25     029
        {   XA_FILE_ZIRI04,     9   },          //          CLOCK_02_30     030
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_02_35     031
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_02_40     032
        {   XA_FILE_ZIRI04,     10  },          //          CLOCK_02_45     033
        {   XA_FILE_ZIRI04,     11  },          //          CLOCK_02_50     034
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_02_55     035
        {   XA_FILE_ZIRI05,     0   },          //          CLOCK_03_00     036
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_03_05     037
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_03_10     038
        {   XA_FILE_ZIRI05,     1   },          //          CLOCK_03_15     039
        {   XA_FILE_ZIRI05,     2   },          //          CLOCK_03_20     040
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_03_25     041
        {   XA_FILE_ZIRI05,     3   },          //          CLOCK_03_30     042
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_03_35     043
        {   XA_FILE_ZIRI05,     4   },          //          CLOCK_03_40     044
        {   XA_FILE_ZIRI05,     5   },          //          CLOCK_03_45     045
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_03_50     046
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_03_55     047
        {   XA_FILE_ZIRI05,     6   },          //          CLOCK_04_00     048
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_04_05     049
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_04_10     050
        {   XA_FILE_ZIRI05,     7   },          //          CLOCK_04_15     051
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_04_20     052
        {   XA_FILE_ZIRI05,     8   },          //          CLOCK_04_25     053
        {   XA_FILE_ZIRI05,     9   },          //          CLOCK_04_30     054
        {   XA_FILE_ZIRI05,     10  },          //          CLOCK_04_35     055
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_04_40     056
        {   XA_FILE_ZIRI05,     11  },          //          CLOCK_04_45     057
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_04_50     058
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_04_55     059
        {   XA_FILE_ZIRI06,     0   },          //          CLOCK_05_00     060
        {   XA_FILE_ZIRI06,     1   },          //          CLOCK_05_05     061
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_05_10     062
        {   XA_FILE_ZIRI06,     2   },          //          CLOCK_05_15     063
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_05_20     064
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_05_25     065
        {   XA_FILE_ZIRI06,     3   },          //          CLOCK_05_30     066
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_05_35     067
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_05_40     068
        {   XA_FILE_ZIRI06,     4   },          //          CLOCK_05_45     069
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_05_50     070
        {   XA_FILE_ZIRI06,     5   },          //          CLOCK_05_55     071
        {   XA_FILE_ZIRI06,     6   },          //          CLOCK_06_00     072
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_06_05     073
        {   XA_FILE_ZIRI06,     7   },          //          CLOCK_06_10     074
        {   XA_FILE_ZIRI06,     8   },          //          CLOCK_06_15     075
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_06_20     076
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_06_25     077
        {   XA_FILE_ZIRI06,     9   },          //          CLOCK_06_30     078
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_06_35     079
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_06_40     080
        {   XA_FILE_ZIRI06,     10  },          //          CLOCK_06_45     081
        {   XA_FILE_ZIRI06,     11  },          //          CLOCK_06_50     082
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_06_55     083
        {   XA_FILE_ZIRI07,     0   },          //          CLOCK_07_00     084
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_07_05     085
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_07_10     086
        {   XA_FILE_ZIRI07,     1   },          //          CLOCK_07_15     087
        {   XA_FILE_ZIRI07,     2   },          //          CLOCK_07_20     088
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_07_25     089
        {   XA_FILE_ZIRI07,     3   },          //          CLOCK_07_30     090
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_07_35     091
        {   XA_FILE_ZIRI07,     4   },          //          CLOCK_07_40     092
        {   XA_FILE_ZIRI07,     5   },          //          CLOCK_07_45     093
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_07_50     094
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_07_55     095
        {   XA_FILE_ZIRI07,     6   },          //          CLOCK_08_00     096
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_08_05     097
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_08_10     098
        {   XA_FILE_ZIRI07,     7   },          //          CLOCK_08_15     099
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_08_20     100
        {   XA_FILE_ZIRI07,     8   },          //          CLOCK_08_25     101
        {   XA_FILE_ZIRI07,     9   },          //          CLOCK_08_30     102
        {   XA_FILE_ZIRI07,     10  },          //          CLOCK_08_35     103
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_08_40     104
        {   XA_FILE_ZIRI07,     11  },          //          CLOCK_08_45     105
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_08_50     106
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_08_55     107
        {   XA_FILE_ZIRI08,     0   },          //          CLOCK_09_00     108
        {   XA_FILE_ZIRI08,     1   },          //          CLOCK_09_05     109
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_09_10     110
        {   XA_FILE_ZIRI08,     2   },          //          CLOCK_09_15     111
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_09_20     112
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_09_25     113
        {   XA_FILE_ZIRI08,     3   },          //          CLOCK_09_30     114
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_09_35     115
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_09_40     116
        {   XA_FILE_ZIRI08,     4   },          //          CLOCK_09_45     117
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_09_50     118
        {   XA_FILE_ZIRI08,     5   },          //          CLOCK_09_55     119
        {   XA_FILE_ZIRI08,     6   },          //          CLOCK_10_00     120
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_10_05     121
        {   XA_FILE_ZIRI08,     7   },          //          CLOCK_10_10     122
        {   XA_FILE_ZIRI08,     8   },          //          CLOCK_10_15     123
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_10_20     124
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_10_25     125
        {   XA_FILE_ZIRI08,     9   },          //          CLOCK_10_30     126
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_10_35     127
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_10_40     128
        {   XA_FILE_ZIRI08,     10  },          //          CLOCK_10_45     129
        {   XA_FILE_ZIRI08,     11  },          //          CLOCK_10_50     130
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_10_55     131
        {   XA_FILE_ZIRI09,     0   },          //          CLOCK_11_00     132
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_11_05     133
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_11_10     134
        {   XA_FILE_ZIRI09,     1   },          //          CLOCK_11_15     135
        {   XA_FILE_ZIRI09,     2   },          //          CLOCK_11_20     136
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_11_25     137
        {   XA_FILE_ZIRI09,     3   },          //          CLOCK_11_30     138
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_11_35     139
        {   XA_FILE_ZIRI09,     4   },          //          CLOCK_11_40     140
        {   XA_FILE_ZIRI09,     5   },          //          CLOCK_11_45     141
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_11_50     142
        {   XA_FILE_NONE,       -1  },          //  [×]    CLOCK_11_55     143
    };



//----------------------------------------------------------------------------
//----初プレイデモ開始時
#define INIT_PLAY_DEMO_SCRIPT_BASE              0
#define INIT_PLAY_DEMO_SCRIPT_NUM               5

//----クリアデモ
#define CLEAR_DEMO_SCRIPT_BASE                  5
#define CLEAR_DEMO_SCRIPT_NUM                   2

//----オールクリアデモ
#define ALL_CLEAR_DEMO_SCRIPT_BASE              7
#define ALL_CLEAR_DEMO_SCRIPT_NUM               3

//----失敗
#define FALSE_DEMO_SCRIPT_BASE                  10
#define FALSE_DEMO_SCRIPT_NUM                   1

//----レベルセレクト
#define SELECT_LEVEL_SCRIPT_BASE                11
#define SELECT_LEVEL_SCRIPT_NUM                 1


//----スクリプト本体
static SCRIP_DATA ZiriScript[]=
{
    //----------------------------------------初プレイデモ
    {//よいしょっと。
        0,
        NamePlateTokei,
        XA_FILE_ZIRI00,
        0,
        "初消音時０６よいしょっと。待１２０終"
    },
    {//あのね、ボク、とけいマン。
        0,
        NamePlateTokei,
        XA_FILE_ZIRI00,
        1,
        "初消音時０６あのね、ぼく、とけいマン。待１２０終"
    },
    {//ジリジリパニックへ　ようこそ。
        0,
        NamePlateTokei,
        XA_FILE_ZIRI00,
        2,
        "初消音時０６「ジリジリパニック」へ　ようこそ。待１２０終"
    },
    {//あ、もう　ゲームの　じかん。
        0,
        NamePlateTokei,
        XA_FILE_ZIRI00,
        3,
        "初消音時０６あ、もう　ゲームの　じかん。待１２０終"
    },
    {//がんばって！
        0,
        NamePlateTokei,
        XA_FILE_ZIRI00,
        4,
        "初消音時０６がんばって！待１２０終"
    },
    //----------------------------------------クリア
    {//うわぉ、スバラシイ！
        0,
        NamePlateTokei,
        XA_FILE_ZIRI01,
        0,
        "初消音時０６うわあ、すばらしい！待１００終"
    },
    {//つぎもがんばれ。
        0,
        NamePlateTokei,
        XA_FILE_ZIRI01,
        1,
        "初消音時０６つぎも　がんばれ。待２４０終"
    },
    //----------------------------------------オールクリア
    {//うわぉ、ブラボー。
        0,
        NamePlateTokei,
        XA_FILE_ZIRI01,
        2,
        "初消音時０６うわ、ブラボー。待１２０終"
    },
    {//とっておきの　おいわいだよぉん。
        0,
        NamePlateTokei,
        XA_FILE_ZIRI01,
        3,
        "初消音時０６とっておきの　おいわいだよ。待１２０終"
    },
    {//おめでとぉぉぉぉぉ。
        0,
        NamePlateTokei,
        XA_FILE_ZIRI01,
        4,
        "初消音時０６おめでとう。待１２０終"
    },
    //----------------------------------------失敗
    {//ひょえぇぇぇぇぇー。
        0,
        NamePlateTokei,
        XA_FILE_ZIRI01,
        5,
        "初消音時０６ひょえぇぇぇぇぇー。待１２０終"
    },
    //----------------------------------------レベルセレクト
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
//  関数名  :Ziri
//
//  work   :ジリジリパニック
//  in     :GAMEMGR*    ゲームマネージャへのポインタ
//  out    :TRUE        成功
//  note    :なし
//-----------------------------------------------------------------------------
int Ziri(GAMEMGR* ip_GameMgr)
{
    TASK Task;


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
            SfileRead2(ZIRI_SOUNDFILE);
            HelpInit();
            GameMgr.WaitFlag    = ON;

            //----texture read sram -> vram
            if((file_read(ZiriTextureFile[0].fn,LoadAddress)) == -1)
            {//read error
                return FALSE;
            }
            
            //----texture init
            TexInit( ZIRI_TIM_NUM, &ZiriTextureImage[ZIRI_TIM_POS] );
            TimImgData = ZiriTextureImage;

            //----ゲーム用スプライト登録
            EntrySprite( ZiriSpriteData );

            //---- ゲーム管理情報初期化
            ZGameMgr.Timer          = 0;                            //ゲーム時間
            ZGameMgr.Level          = ip_GameMgr->Level[GAME_ZIRI]; //レベル
            ZGameMgr.PlayLevel      = 0;                            //ゲームレベル
            ZGameMgr.TimeUpFlag     = 0;                            //時間切れフラグ
            ZGameMgr.ContinueFlag   = 0;                            //継続プレイフラグ
            ZGameMgr.ClearEndFlag   = 0;                            //クリア終了
            ZGameMgr.EventEndFlag   = 0;                            //イベント終了フラグ
            ZGameMgr.ClearFlag      = 0;                            //クリアフラグ
            ZGameMgr.AllClearFlag   = 0;                            //オールクリアフラグ
            ZGameMgr.ExitFlag       = 0;                            //終了フラグ

#ifdef __DEBUG_ZIRI__

            if( NewPad & PADL1 )
            {//----デバッグタスク
                Task.func       = DebugSpriteTask;
                Task.priority   = TASK_NO_DEBUG;
                Task.attribute  = ATTR_USER;
                Task.status     = TASK_NEW_ENTRY;
                Task.id         = TASK_NO_DEBUG;
                Task.wait_time  = 0;
                Task.buf        = NULL;
                Task.name       = "DebugSpriteTask";
                Task.mode       = TASK_MODE_INIT;
                CreateTask(&Task);
            }else
            if(NewPad & PADL2){
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
            if(NewPad & PADR2){
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
            {//----
                if(ZGameMgr.Level==0)
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
            if(ZGameMgr.Level==0)
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
            if(ZGameMgr.ExitFlag) ip_GameMgr->SubMode = EXIT;
            
            //-----------------------------------------------------------▲
            break;
        case EXIT:
            //----スプライト開放
            ReleaseSprite();

            //----ゲームレベル
            ip_GameMgr->Level[GAME_ZIRI] = ZGameMgr.Level;

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
//  関数名  :ClockManAppearTask
//
//  work    :ゲーム開始時のイベントタスク
//  in      :TASK*  タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int ClockManAppearTask(TASK* ip_task)
{
    static ZIRI_SPRITE_DATA AppearSpriteTable[]={
        {   ZIRI_CHAR_GAME_CLOCKMAN_APPEAR_00,  92,     160 },          //とけいマン登場登場１  92,160
        {   ZIRI_CHAR_GAME_CLOCKMAN_APPEAR_00,  97,     69, },          //とけいマン登場登場１  97,69
        {   ZIRI_CHAR_GAME_CLOCKMAN_APPEAR_01,  100,    130 },          //とけいマン登場登場２  100,130
        {   ZIRI_CHAR_GAME_CLOCKMAN_APPEAR_02,  100,    106 },          //とけいマン登場登場３  100,106
        {   ZIRI_CHAR_GAME_CLOCKMAN_APPEAR_03,  112,    65  },          //とけいマン登場登場４  114,62
    };

    static ZIRI_SPRITE_DATA OutClockManSpriteTable[]={
        {   ZIRI_CHAR_GAME_CLOCKMAN_APPEAR_04,          0,      0   },  //胴体
        {   ZIRI_CHAR_GAME_CLOCKMAN_APPEAR_04_FOOT_00,  0,      93  },  //足A   0,93
        {   ZIRI_CHAR_GAME_CLOCKMAN_APPEAR_04_FOOT_01,  -10,    86  },  //足B   -10,86
    };

    static int AppearClockManAnmIndexTable[]={
        0,      //下から1
        0,      //下から1
        2,      //下から2
        3,      //下から3
        -1,
    };

    static int AppearClockManDanceAnmIndexTable[]={
        1,4,    //踊る1
        1,4,    //踊る2
    };


    SPRITE_DATA SpData;
    TASK Task;


    switch( ip_task->mode )
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //next MAIN
            ip_task->mode       = TASK_MODE_MAIN;

            //----初期化
            ip_task->user[APPEAR_TASK_USER_MODE]        = APPEAR_CLOCKMAN_MODE_00;  //モード
            ip_task->user[APPEAR_TASK_USER_TIMER]       = 0;                        //タイマー
            ip_task->user[APPEAR_TASK_USER_INDEX]       = 0;                        //アニメインデックス
            ip_task->user[APPEAR_TASK_USER_ANMWT]       = 0;                        //ウェイトタイマー
            ip_task->user[APPEAR_TASK_USER_CLOCKMAN_X]  = (320-72)/2;               //位置Ｘ
            ip_task->user[APPEAR_TASK_USER_CLOCKMAN_Y]  = 69;                       //位置Ｙ
            ip_task->user[APPEAR_TASK_FADE_FLAG]        = 0;                        //Flag
            ip_task->user[APPEAR_TASK_DANCE_INDEX]      = 0;                        //Dance Index

            // フェードInします
            GameMgr.FadeFlag = FadeIn;

            //スクリプト
            ZGameMgr.Script.Flag=1;
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
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:
//          FntPrint("MOD=[%4d]\n",ip_task->user[APPEAR_TASK_USER_MODE]         );
//          FntPrint("TIM=[%4d]\n",ip_task->user[APPEAR_TASK_USER_TIMER]        );
//          FntPrint("IDX=[%4d]\n",ip_task->user[APPEAR_TASK_USER_INDEX]        );
//          FntPrint("AWT=[%4d]\n",ip_task->user[APPEAR_TASK_USER_ANMWT]        );
//          FntPrint("POX=[%4d]\n",ip_task->user[APPEAR_TASK_USER_CLOCKMAN_X]   );
//          FntPrint("POY=[%4d]\n",ip_task->user[APPEAR_TASK_USER_CLOCKMAN_Y]   );

            switch(ip_task->user[APPEAR_TASK_USER_MODE])
            {
                case APPEAR_CLOCKMAN_MODE_00:
                    
                    //----描画
                    SpData.No       = AppearSpriteTable[ AppearClockManAnmIndexTable[ip_task->user[APPEAR_TASK_USER_INDEX]] ].No;
                    SpData.PosX     = AppearSpriteTable[ AppearClockManAnmIndexTable[ip_task->user[APPEAR_TASK_USER_INDEX]] ].Ofx;
                    SpData.PosY     = AppearSpriteTable[ AppearClockManAnmIndexTable[ip_task->user[APPEAR_TASK_USER_INDEX]] ].Ofy;
                    SpData.PosZ     = PRIORITY_APPEAR_CLOCKMAN;
                    SpData.ScaleX   = SCALE10;
                    SpData.ScaleY   = SCALE10;
                    SpData.Rotate   = ROTATE000;
                    SpData.Reverse  = NOREVERS;
                    DrawSprite( &SpData );
                    
                    if(++ip_task->user[APPEAR_TASK_USER_ANMWT] > APPEAR_CLOCKMAN_ANM_WAIT_TIME)
                    {
                        ip_task->user[APPEAR_TASK_USER_ANMWT]   = 0;                        //タイマークリア
                        
                        if( AppearClockManAnmIndexTable[ ++ip_task->user[APPEAR_TASK_USER_INDEX] ] == -1)
                        {
                            ip_task->user[APPEAR_TASK_USER_INDEX]   = 0;                        //インデックス戻し
                            ip_task->user[APPEAR_TASK_USER_MODE]    = APPEAR_CLOCKMAN_MODE_01;  //ダンス終了
                        }
                    }
                    
                    break;
                case APPEAR_CLOCKMAN_MODE_01:
                    
                    //----描画
                    SpData.No       = AppearSpriteTable[ AppearClockManDanceAnmIndexTable[ip_task->user[APPEAR_TASK_DANCE_INDEX]] ].No;
                    SpData.PosX     = AppearSpriteTable[ AppearClockManDanceAnmIndexTable[ip_task->user[APPEAR_TASK_DANCE_INDEX]] ].Ofx;
                    SpData.PosY     = AppearSpriteTable[ AppearClockManDanceAnmIndexTable[ip_task->user[APPEAR_TASK_DANCE_INDEX]] ].Ofy;
                    SpData.PosZ     = PRIORITY_APPEAR_CLOCKMAN;
                    SpData.ScaleX   = SCALE10;
                    SpData.ScaleY   = SCALE10;
                    SpData.Rotate   = ROTATE000;
                    SpData.Reverse  = NOREVERS;
                    DrawSprite( &SpData );

                    if(++ip_task->user[APPEAR_TASK_USER_ANMWT] > APPEAR_CLOCKMAN_ANM_WAIT_TIME)
                    {
                        ip_task->user[APPEAR_TASK_USER_ANMWT]   = 0;
                        ip_task->user[APPEAR_TASK_DANCE_INDEX]  ^=1;
                    }

                    if(!ZGameMgr.Script.Flag){
                        ip_task->user[APPEAR_TASK_USER_INDEX]   = 0;                        //インデックス戻し
                        ip_task->user[APPEAR_TASK_USER_MODE]    = APPEAR_CLOCKMAN_MODE_02;  //ダンス終了
                            
                        //[♪]カーン
                        dsPlayXa(XA_FILE_ZIRI11,0);
                    }
                    
                    break;
                case APPEAR_CLOCKMAN_MODE_02:
                    
                    //----BODY
                    SpData.No       = OutClockManSpriteTable[0].No;
                    SpData.PosX     = ip_task->user[APPEAR_TASK_USER_CLOCKMAN_X];
                    SpData.PosY     = ip_task->user[APPEAR_TASK_USER_CLOCKMAN_Y];
                    SpData.PosZ     = PRIORITY_APPEAR_CLOCKMAN;
                    SpData.ScaleX   = SCALE10;
                    SpData.ScaleY   = SCALE10;
                    SpData.Rotate   = ROTATE000;
                    SpData.Reverse  = NOREVERS;
                    DrawSprite( &SpData );
                    
                    //----FOOT
                    SpData.No       = OutClockManSpriteTable[1 + ip_task->user[APPEAR_TASK_USER_INDEX]].No;
                    SpData.PosX     = ip_task->user[APPEAR_TASK_USER_CLOCKMAN_X] + OutClockManSpriteTable[1 + ip_task->user[APPEAR_TASK_USER_INDEX] ].Ofx;
                    SpData.PosY     = ip_task->user[APPEAR_TASK_USER_CLOCKMAN_Y] + OutClockManSpriteTable[1 + ip_task->user[APPEAR_TASK_USER_INDEX] ].Ofy;
                    SpData.PosZ     = PRIORITY_APPEAR_CLOCKMAN;
                    SpData.ScaleX   = SCALE10;
                    SpData.ScaleY   = SCALE10;
                    SpData.Rotate   = ROTATE000;
                    SpData.Reverse  = NOREVERS;
                    DrawSprite( &SpData );
                    
                    //----RUN
                    //ip_task->user[APPEAR_TASK_USER_CLOCKMAN_Y]
                    ip_task->user[APPEAR_TASK_USER_CLOCKMAN_X] -= 4;
                    if(ip_task->user[APPEAR_TASK_USER_CLOCKMAN_X] < -100 ){

                        if(!ip_task->user[APPEAR_TASK_FADE_FLAG]){
                            ip_task->user[APPEAR_TASK_FADE_FLAG] = 1;
                            //----EXIT
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
                    
                    //----アニメ
                    if( ++ip_task->user[APPEAR_TASK_USER_ANMWT] > APPEAR_CLOCKMAN_ANM_WAIT_TIME){
                        ip_task->user[APPEAR_TASK_USER_ANMWT]   = 0;
                        ip_task->user[APPEAR_TASK_USER_INDEX]   ^= 1;
                    }
                    
                    break;
                default:
            }

            break;
        //----------------------------------------------------------------タスク終了
        case TASK_MODE_EXIT:
            //スクリプトOFF
            MetuseijiFlag=OFF;

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
            
            //----時計マンタスク
            Task.func       = ClockManTask;
            Task.priority   = TASK_NO_GAME_CLOCKMAN;
            Task.attribute  = ATTR_USER;
            Task.status     = TASK_NEW_ENTRY;
            Task.id         = TASK_NO_GAME_CLOCKMAN;
            Task.wait_time  = 0;
            Task.buf        = NULL;
            Task.name       = "ClockManTask";
            Task.mode       = TASK_MODE_INIT;
            CreateTask(&Task);
            
            //----質問タスク
            Task.func       = QuestionTask;
            Task.priority   = TASK_NO_GAME_QUESTION;
            Task.attribute  = ATTR_USER;
            Task.status     = TASK_NEW_ENTRY;
            Task.id         = TASK_NO_GAME_QUESTION;
            Task.wait_time  = 0;
            Task.buf        = NULL;
            Task.name       = "QuestionTask";
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
            
            //----タイマータスク
            Task.func       = TimerTask;
            Task.priority   = TASK_NO_GAME_TIMER;
            Task.attribute  = ATTR_USER;
            Task.status     = TASK_NEW_ENTRY;
            Task.id         = TASK_NO_GAME_TIMER;
            Task.wait_time  = 0;
            Task.buf        = NULL;
            Task.name       = "TimerTask";
            Task.mode       = TASK_MODE_INIT;
            CreateTask(&Task);
            
            //----自分を削除
            ExitTask(ip_task->id);
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


    switch( ip_task->mode )
    {
        //----------------------------------------------------------------初期化
        case TASK_MODE_INIT:
            //next main
            ip_task->mode = TASK_MODE_MAIN;
            
            //---- ゲーム管理情報初期化
        //  ZGameMgr.Timer                  = 0;        //ゲーム時間
        //  ZGameMgr.Level                  = ;         //レベル
        //  ZGameMgr.PlayLevel              = 0;        //ゲームレベル
            ZGameMgr.TimeUpFlag             = 0;        //時間切れフラグ
        //  ZGameMgr.ContinueFlag           = 0;        //継続プレイフラグ
            ZGameMgr.ClearEndFlag           = 0;        //クリア終了
            ZGameMgr.EventEndFlag           = 0;        //イベント終了フラグ
            ZGameMgr.ClearFlag              = 0;        //クリアフラグ
            ZGameMgr.ClearEndFlag           = 0;        //クリアエンドフラグ
            ZGameMgr.AllClearFlag           = 0;        //オールクリアフラグ
            ZGameMgr.ExitFlag               = 0;        //終了フラグ

            //ガイドセット
            GaidoInit();

            if(ZGameMgr.ContinueFlag==0)
            {//----初プレイ：
                //----継続プレイフラグオン
                ZGameMgr.ContinueFlag = 1;
                
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
                
                //----出現タスク
                Task.func       = ClockManAppearTask;
                Task.priority   = TASK_NO_GAME_APPEAR;
                Task.attribute  = ATTR_USER;
                Task.status     = TASK_NEW_ENTRY;
                Task.id         = TASK_NO_GAME_APPEAR;
                Task.wait_time  = 0;
                Task.buf        = NULL;
                Task.name       = "ClockManAppearTask";
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
                
                //----時計マンタスク
                Task.func       = ClockManTask;
                Task.priority   = TASK_NO_GAME_CLOCKMAN;
                Task.attribute  = ATTR_USER;
                Task.status     = TASK_NEW_ENTRY;
                Task.id         = TASK_NO_GAME_CLOCKMAN;
                Task.wait_time  = 0;
                Task.buf        = NULL;
                Task.name       = "ClockManTask";
                Task.mode       = TASK_MODE_INIT;
                CreateTask(&Task);
                
                //----質問タスク
                Task.func       = QuestionTask;
                Task.priority   = TASK_NO_GAME_QUESTION;
                Task.attribute  = ATTR_USER;
                Task.status     = TASK_NEW_ENTRY;
                Task.id         = TASK_NO_GAME_QUESTION;
                Task.wait_time  = 0;
                Task.buf        = NULL;
                Task.name       = "QuestionTask";
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
                
                //----タイマータスク
                Task.func       = TimerTask;
                Task.priority   = TASK_NO_GAME_TIMER;
                Task.attribute  = ATTR_USER;
                Task.status     = TASK_NEW_ENTRY;
                Task.id         = TASK_NO_GAME_TIMER;
                Task.wait_time  = 0;
                Task.buf        = NULL;
                Task.name       = "TimerTask";
                Task.mode       = TASK_MODE_INIT;
                CreateTask(&Task);
            }
            
            break;
        //----------------------------------------------------------------メイン
        case TASK_MODE_MAIN:
#ifdef __DEBUG_ZIRI__
            FntPrint("A/Q=[%d/%d]\n",       ZGameMgr.Player.CorrectAnswerNum,ZGameMgr.Question.Index);
            FntPrint("PLAY_LEVEL=[%d]\n",   ZGameMgr.PlayLevel);
#endif

            if( ZGameMgr.ClearEndFlag || ZGameMgr.TimeUpFlag )  ip_task->mode = TASK_MODE_EXIT;

            break;
        //----------------------------------------------------------------終了
        case TASK_MODE_EXIT:
            //----ゲームタスク終了
            RemoveTask(TASK_NO_GAME_PLAYER);
            RemoveTask(TASK_NO_GAME_CLOCKMAN);
            RemoveTask(TASK_NO_GAME_QUESTION);
            RemoveTask(TASK_NO_GAME_PAUSE);
            RemoveTask(TASK_NO_GAME_TIMER);
            RemoveTask(TASK_NO_GAME_CONGRATULATIONS);

            //[♪]BGM
            ssStopBgm(ZIRI_BGM_00);

            //ガイド破棄
            SpraitCharClr();

            //----レベル更新
            if(ZGameMgr.PlayLevel > ZGameMgr.Level)
            {//前回のレベルより高い場合は書き換える
                ZGameMgr.Level = ZGameMgr.PlayLevel;
            }
            
            //----イベントタスク起動
            if(ZGameMgr.AllClearFlag)
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
            if(ZGameMgr.ClearFlag)
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


#define L_OFFSET_Y      -14

//-----------------------------------------------------------------------------
//  関数名  :SelectLevelTask
//
//  work    :セレクトレベル
//  in      :TASK*  タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int SelectLevelTask(TASK* ip_task)
{
    static int LevelNumTable[]={
        ZIRI_CHAR_GAME_SELECT_LEVEL_NUM_1,
        ZIRI_CHAR_GAME_SELECT_LEVEL_NUM_2,
        ZIRI_CHAR_GAME_SELECT_LEVEL_NUM_3,
        ZIRI_CHAR_GAME_SELECT_LEVEL_NUM_4,
        ZIRI_CHAR_GAME_SELECT_LEVEL_NUM_5,
    };

    static ZIRI_SPRITE_DATA GakudaninSpriteTable[]=
    {
        {   ZIRI_CHAR_GAME_DANTYOU_00,                  0,      -6  },  //団長アニメ00
        {   ZIRI_CHAR_GAME_DANTYOU_01,                  0,      -6  },  //団長アニメ01
        {   ZIRI_CHAR_GAME_DANIN_FUUSENN_BLUE_00,       0,      0   },  //団員（風船）アニメ00（青風船）
        {   ZIRI_CHAR_GAME_DANIN_FUUSENN_BLUE_01,       0,      0   },  //団員（風船）アニメ00（青風船）
        {   ZIRI_CHAR_GAME_DANIN_HATA_TATE_00,          0,      0   },  //団員（旗）アニメ00
        {   ZIRI_CHAR_GAME_DANIN_HATA_TATE_01,          0,      0   },  //団員（旗）アニメ01
        {   ZIRI_CHAR_GAME_DANIN_HATA_YOKO_01,          0,      0   },  //団員（ピンク旗）アニメ00
        {   ZIRI_CHAR_GAME_DANIN_HATA_YOKO_02,          0,      0   },  //団員（ピンク旗）アニメ01
        {   ZIRI_CHAR_GAME_DANIN_FUUSENN_ORANGE_00,     0,      0   },  //団員（風船）アニメ07（橙風船）
        {   ZIRI_CHAR_GAME_DANIN_FUUSENN_ORANGE_01,     0,      0   },  //団員（風船）アニメ07（橙風船）
    };

    SPRITE_DATA SpData;
    TASK Task;
    int i,j;


    switch(ip_task->mode)
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //next MAIN
            ip_task->mode       = TASK_MODE_MAIN;


            //----プレイレベルクリア
            ZGameMgr.PlayLevel      = 0;

            //----継続プレイフラグOFF
            ZGameMgr.ContinueFlag   = 0;
            
            //----レベルセレクトワーク初期化
            ZGameMgr.SelectLevel.Mode               = ZIRI_GAME_SELECT_LEVEL_MODE_00;
            ZGameMgr.SelectLevel.Timer              = 0;
            ZGameMgr.SelectLevel.BlockNo            = 0;
            ZGameMgr.SelectLevel.BlockWt            = 0;
            ZGameMgr.SelectLevel.KeteiWt            = 0;
            ZGameMgr.SelectLevel.KeteiFlushIndex    = 0;
            ZGameMgr.SelectLevel.KeteiFlushWt       = 0;
            ZGameMgr.SelectLevel.AnmIndex           = 0;
            ZGameMgr.SelectLevel.AnmNo              = GakudaninSpriteTable[0].No;
            ZGameMgr.SelectLevel.AnmWt              = 0;
            ZGameMgr.SelectLevel.AnmBase            = 0;
            ZGameMgr.SelectLevel.PosX               = ZIRI_GAME_SELECT_LEVEL_GAKUDANIN_INIT_X;
            ZGameMgr.SelectLevel.PosY               = ZIRI_GAME_SELECT_LEVEL_GAKUDANIN_INIT_Y;
            ZGameMgr.SelectLevel.WaitFlag           = 0;

            // フェードINます
            GameMgr.FadeFlag    = FadeIn;

            //[♪]パンパカパーん
            dsPlayXa(XA_FILE_ZIRI10,5);

            break;
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:
        //  FntPrint("SELECT LEVEL=%d\n", ZGameMgr.PlayLevel);
        
            //----選択可能レベルをプレートのアニメで表現する
            switch(ZGameMgr.SelectLevel.Mode)
            {
                //----------------------------------選択可能なレベルまで明るく(楽団員現る)
                case ZIRI_GAME_SELECT_LEVEL_MODE_00:
                    
                    for(i=0;i<ZGameMgr.Level+1;i++){//横
                        for(j=0;j<5;j++){//縦
                            if(j>i) continue;
                            //レベルセレクトプレート
                            SpData.No       = ZIRI_CHAR_GAME_SELECT_LEVEL_PLATE_LIGHT;
                            SpData.PosX     = 101 + 25*i - 2;
                            SpData.PosY     = 40 + 95 - 10*j + 3 + L_OFFSET_Y;
                            SpData.PosZ     = PRIORITY_BG-2;
                            SpData.ScaleX   = SCALE10;
                            SpData.ScaleY   = SCALE10;
                            SpData.Rotate   = ROTATE000;
                            SpData.Reverse  = NOREVERS;
                            DrawSprite( &SpData );
                        }
                    }
                    
                    //----楽団員移動
                    ZGameMgr.SelectLevel.PosX -= ZIRI_GAME_SELECT_LEVEL_GAKUDANIN_SPEED_X; 
                    if(ZGameMgr.SelectLevel.PosX <= ZIRI_GAME_SELECT_LEVEL_GAKUDANIN_STOP_X)
                    {
                        ZGameMgr.SelectLevel.PosX = ZIRI_GAME_SELECT_LEVEL_GAKUDANIN_STOP_X;
                        
                        if(dSoundStatus == DslStatStandby){
                            ZGameMgr.SelectLevel.Mode = ZIRI_GAME_SELECT_LEVEL_MODE_01;
                            
                            //スクリプト
                            ZGameMgr.Script.Flag=1;
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
                    }
                    
                    break;
                //----------------------------------下から上へ明るく
                case ZIRI_GAME_SELECT_LEVEL_MODE_01:
                    SsinScriptFlag = ZGameMgr.Script.Flag;          // iwasawa Correction (2003/4/27)
                    if(!ZGameMgr.Script.Flag){
                        //----操作
                        if(JstPad &  PADLright)
                        {
                            //[♪] レバー音
                            ssPlaySe(BUTONSE_LEVER);
                            if(++ZGameMgr.PlayLevel>ZGameMgr.Level){
                                ZGameMgr.PlayLevel=0;
                            }
                        }else
                        if(JstPad &  PADLleft){
                            //[♪] レバー音
                            ssPlaySe(BUTONSE_LEVER);
                            if(--ZGameMgr.PlayLevel<0){
                                ZGameMgr.PlayLevel=ZGameMgr.Level;
                            }
                        }else{
                            
                        }
                        
                        //----決定
                        if(JstPad &  PADRright)
                        {//next EXIT
                            ZGameMgr.SelectLevel.Mode = ZIRI_GAME_SELECT_LEVEL_MODE_02;
                            
                            //[♪]決定
                            ssPlaySe(BUTONSE_MARU);
                        }
                    }
                    
                    //----描画
                    if( ++ZGameMgr.SelectLevel.BlockWt > ZIRI_GAME_SELECT_LEVEL_FLUSH_ANM_TIME)
                    {//
                        ZGameMgr.SelectLevel.BlockWt=0;
                        if(++ZGameMgr.SelectLevel.BlockNo > ZIRI_GAME_MAX_LEVEL_NUM)
                        {
                            ZGameMgr.SelectLevel.BlockNo=0;
                        }
                    }
                    
                    for(i=0;i<ZGameMgr.Level+1;i++){//横
                        for(j=0;j<5;j++){//縦
                            if(j>i) continue;
                            if(ZGameMgr.SelectLevel.BlockNo <= j) continue;
                            
                            //レベルセレクトプレート
                            SpData.No       = ZIRI_CHAR_GAME_SELECT_LEVEL_PLATE_LIGHT;
                            SpData.PosX     = 101 + 25*i - 2;
                            SpData.PosY     = 40 + 95 - 10*j + 3 + L_OFFSET_Y;
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
                case ZIRI_GAME_SELECT_LEVEL_MODE_02:
                    
                    if(!ZGameMgr.SelectLevel.WaitFlag){
                        if(++ZGameMgr.SelectLevel.KeteiWt > ZIRI_GAME_SELECT_LEVEL_KETEI_WAIT_TIME)
                        {//フラッシュ後抜ける
                            ZGameMgr.SelectLevel.WaitFlag=1;
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
                    
                    if( ++ZGameMgr.SelectLevel.KeteiFlushWt > ZIRI_GAME_SELECT_LEVEL_KETEI_FLUSH_TIME ){
                        ZGameMgr.SelectLevel.KeteiFlushWt = 0;
                        ZGameMgr.SelectLevel.KeteiFlushIndex^=1;
                    }
                    
                    if(ZGameMgr.SelectLevel.KeteiFlushIndex){
                        for(i=0;i<5;i++){//縦
                            if(ZGameMgr.PlayLevel>=i){
                                //レベルセレクトプレート
                                SpData.No       = ZIRI_CHAR_GAME_SELECT_LEVEL_PLATE_LIGHT;
                                SpData.PosX     = 101 + 25*ZGameMgr.PlayLevel - 2;
                                SpData.PosY     = 40 + 95 - 10*i + 3 + L_OFFSET_Y;
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
            if(++ZGameMgr.SelectLevel.AnmWt > ZIRI_GAME_SELECT_LEVEL_GAKUDANIN_ANM_WAIT_TIME){
                ZGameMgr.SelectLevel.AnmWt      = 0;
                ZGameMgr.SelectLevel.AnmIndex   ^=1;
            }
            
            for(i=0;i<5;i++)
            {
                ZGameMgr.SelectLevel.AnmBase    = i*2;
                ZGameMgr.SelectLevel.AnmNo      = GakudaninSpriteTable[ZGameMgr.SelectLevel.AnmBase + ZGameMgr.SelectLevel.AnmIndex].No;
                
                SpData.No                       = ZGameMgr.SelectLevel.AnmNo;
                SpData.PosX                     = ZGameMgr.SelectLevel.PosX + i*40 + GakudaninSpriteTable[ZGameMgr.SelectLevel.AnmBase + ZGameMgr.SelectLevel.AnmIndex].Ofx;
                SpData.PosY                     = ZGameMgr.SelectLevel.PosY + GakudaninSpriteTable[ZGameMgr.SelectLevel.AnmBase + ZGameMgr.SelectLevel.AnmIndex].Ofy + L_OFFSET_Y;
                SpData.PosZ                     = PRIORITY_BG - 4;
                SpData.ScaleX                   = SCALE10;
                SpData.ScaleY                   = SCALE10;
                SpData.Rotate                   = ROTATE000;
                SpData.Reverse                  = NOREVERS;
                DrawSprite( &SpData );
            }

            //----レベルセレクトプレートワク
            SpData.No       = ZIRI_CHAR_GAME_SELECT_LEVEL_CURSOR;
            SpData.PosX     = 100 + 25 * ZGameMgr.PlayLevel - 2;
            SpData.PosY     = 40 + 80 - 10 * ZGameMgr.PlayLevel + 3 + L_OFFSET_Y;
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
                SpData.PosY     = 27 + 95 - 10*i + 3 + L_OFFSET_Y;
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
                    SpData.No       = ZIRI_CHAR_GAME_SELECT_LEVEL_PLATE_DARK;
                    SpData.PosX     = 101 + 25*i - 2;
                    SpData.PosY     = 40 + 95 - 10*j + 3 + L_OFFSET_Y;
                    SpData.PosZ     = PRIORITY_BG-1;
                    SpData.ScaleX   = SCALE10;
                    SpData.ScaleY   = SCALE10;
                    SpData.Rotate   = ROTATE000;
                    SpData.Reverse  = NOREVERS;
                    DrawSprite( &SpData );
                }
            }

            //----レベルセレクト背景左
            SpData.No       = ZIRI_CHAR_GAME_SELECT_LEVEL_BG_00;
            SpData.PosX     = 0;
            SpData.PosY     = 0;
            SpData.PosZ     = PRIORITY_BG;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );
            
            //----レベルセレクト背景右
            SpData.No       = ZIRI_CHAR_GAME_SELECT_LEVEL_BG_01;
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
//  関数名  :PlayerTask
//
//  work    :プレイヤータスク
//  in      :TASK* ip_task
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int PlayerTask(TASK* ip_task)
{
    static dscale=0;

    SPRITE_DATA SpData;
    int dir,index,nextindex;
    TASK Task;

    switch(ip_task->mode)
    {
        //----------------------------------------------------------------初期化
        case TASK_MODE_INIT:
            //----NEXTMAIN
            ip_task->mode = TASK_MODE_MAIN;
            
            //----初期化
            ZGameMgr.Player.AnmBase                 = 0;
            ZGameMgr.Player.CursorPos               = CLOCK_POS_03;         //選択する位置
            ZGameMgr.Player.CorrectAnswerNum        = 0;                    //正解数
            ZGameMgr.Player.WaitTimer               = 0;
            ZGameMgr.Player.Character.Status        = PLAYER_WAIT;
            ZGameMgr.Player.Character.Anm.Data.no   = ZIRI_CHAR_GAME_CURSOR_FINGER;
            ZGameMgr.Player.Character.Anm.Data.wt   = 0;
            ZGameMgr.Player.Character.Anm.Index     = 0;
            ZGameMgr.Player.Character.Pos.x         = ClockManPosTable[ZGameMgr.Player.CursorPos].x;
            ZGameMgr.Player.Character.Pos.y         = ClockManPosTable[ZGameMgr.Player.CursorPos].y;
            ZGameMgr.Player.Character.Pos.z         = PRIORITY_PLAYER_CURSOR;
            ZGameMgr.Player.Character.OPos.x        = 40;
            ZGameMgr.Player.Character.OPos.y        = 16;
            ZGameMgr.Player.Character.OPos.z        = 0;
            ZGameMgr.Player.Character.Spd.dx        = 0;
            ZGameMgr.Player.Character.Spd.dy        = 0;
            ZGameMgr.Player.Character.Spd.sx        = 0;
            ZGameMgr.Player.Character.Spd.sy        = 0;

            //[♪]BGM
            ssPlayBgm(ZIRI_BGM_00);

            //debug
            dscale = SCALE10;

            //フェードイン
            GameMgr.FadeFlag    = FadeIn;

            break;
        //----------------------------------------------------------------メイン
        case TASK_MODE_MAIN:
            
            switch(ZGameMgr.Player.Character.Status)
            {
                //--------------------------------------------待ち
                case PLAYER_WAIT:
                    ZGameMgr.Player.Character.Status = PLAYER_SELECT;
                    
                    break;
                //--------------------------------------------選択中
                case PLAYER_SELECT:
                    
                    //----方向チェック
                    if(CheckKeyDir(&dir)){
                        //[♪] レバー音
                        ssPlaySe(BUTONSE_LEVER);
                        switch(ZGameMgr.Player.CursorPos)
                        {
                            case CLOCK_POS_00:
                                if(dir==DIR_UP){            //上
                                    ZGameMgr.Player.CursorPos = CLOCK_POS_01;
                                }else if(dir==DIR_RIGHT){   //右
                                    ZGameMgr.Player.CursorPos = CLOCK_POS_02;
                                }else if(dir==DIR_LEFT){    //左
                                    ZGameMgr.Player.CursorPos = CLOCK_POS_04;
                                }else{
                                    
                                }
                                break;
                            case CLOCK_POS_01:
                                if(dir==DIR_DOWN){          //下
                                    ZGameMgr.Player.CursorPos = CLOCK_POS_02;
                                }else if(dir==DIR_RIGHT){   //右
                                    ZGameMgr.Player.CursorPos = CLOCK_POS_04;
                                }else if(dir==DIR_LEFT){    //左
                                    ZGameMgr.Player.CursorPos = CLOCK_POS_05;
                                }else{
                                    
                                }
                                break;
                            case CLOCK_POS_02:
                                if(dir==DIR_UP){            //上
                                    ZGameMgr.Player.CursorPos = CLOCK_POS_01;
                                }else if(dir==DIR_LEFT){    //左
                                    ZGameMgr.Player.CursorPos = CLOCK_POS_00;
                                }else if(dir==DIR_RIGHT){   //右
                                    ZGameMgr.Player.CursorPos = CLOCK_POS_03;
                                }else{
                                    
                                }
                                break;
                            case CLOCK_POS_03:
                                if(dir==DIR_UP){            //上
                                    ZGameMgr.Player.CursorPos = CLOCK_POS_04;
                                }else if(dir==DIR_LEFT){    //左
                                    ZGameMgr.Player.CursorPos = CLOCK_POS_02;
                                }else if(dir==DIR_RIGHT){   //右
                                    ZGameMgr.Player.CursorPos = CLOCK_POS_05;
                                }else{
                                    
                                }
                                break;
                            case CLOCK_POS_04:
                                if(dir==DIR_DOWN){          //下
                                    ZGameMgr.Player.CursorPos = CLOCK_POS_03;
                                }else if(dir==DIR_LEFT){    //左
                                    ZGameMgr.Player.CursorPos = CLOCK_POS_01;
                                }else if(dir==DIR_RIGHT){   //右
                                    ZGameMgr.Player.CursorPos = CLOCK_POS_00;
                                }else{
                                    
                                }
                                break;
                            case CLOCK_POS_05:
                                if(dir==DIR_UP){            //上
                                    ZGameMgr.Player.CursorPos = CLOCK_POS_04;
                                }else if(dir==DIR_LEFT){    //左
                                    ZGameMgr.Player.CursorPos = CLOCK_POS_03;
                                }else if(dir==DIR_RIGHT){   //右
                                    ZGameMgr.Player.CursorPos = CLOCK_POS_01;
                                }else{
                                    
                                }
                                break;
                            default:
                        }
                        
                        ZGameMgr.Player.Character.Pos.x = ClockManPosTable[ZGameMgr.Player.CursorPos].x;
                        ZGameMgr.Player.Character.Pos.y = ClockManPosTable[ZGameMgr.Player.CursorPos].y;
                    }
                    
                    //----選択チェック
                    if(JstPad & PADRright){
                        //[♪]決定
                        ssPlaySe(BUTONSE_MARU);
                        
                        //----判定
                        switch( CheckAnswer(ZGameMgr.Player.CursorPos, &(ZGameMgr.Question.SelectIndex) ) )
                        {
                            //----------------正解
                            case ANSWER_OK:
                                GameMgr.WaitFlag = ON;          // iwasawa Correction (2003/4/27)
                                //[♪]せいかい
                                ssPlaySe(ZIRI_SE_00);
                                
                                //----ステータス変更：決定
                                ZGameMgr.Player.Character.Status    = PLAYER_DECISION;
                                
                                dscale  = SCALE20;
                                ZGameMgr.Player.WaitTimer = PLAYER_DECISION_WAIT_TIME;
                                
                                //----質問フラグ
                                ZGameMgr.Question.GetDataFlag[ZGameMgr.Question.SelectIndex]    = 0;
                                ZGameMgr.Question.ExistFlag[ZGameMgr.Question.SelectIndex]      = 0;
                                
                                //----クリアチェック
                                if(++ZGameMgr.Player.CorrectAnswerNum >= MAX_CORRECT_ANSWER_NUM)
                                {
                                    ZGameMgr.Player.CorrectAnswerNum    = MAX_CORRECT_ANSWER_NUM;
                                    ZGameMgr.ClearFlag                  = 1;    //クリアフラグセット
                                    
                                    //----オールクリアチェック
                                    if(ZGameMgr.PlayLevel==ZIRI_GAME_MAX_LEVEL_NUM-1){
                                        ZGameMgr.AllClearFlag   = 1;
                                    }
                                    
                                    //----プレイレベル更新
                                    if(++ZGameMgr.PlayLevel > ZIRI_GAME_MAX_LEVEL_NUM-1){
                                        ZGameMgr.PlayLevel = ZIRI_GAME_MAX_LEVEL_NUM-1;
                                    }
                                }
                                
                                //----ステ-タス変更：消えるへ
                                ZGameMgr.ClockMan[ZGameMgr.Question.SelectIndex].Character.Status   = CLOCKMAN_DISAPPEAR;
                                ZGameMgr.ClockMan[ZGameMgr.Question.SelectIndex].Time               = -1;
                                ZGameMgr.ClockMan[ZGameMgr.Question.SelectIndex].RevivalWait        = 1;
                                
                                //----アニメベース
                                ZGameMgr.ClockMan[ZGameMgr.Question.SelectIndex].AnmBase                = CLOCKMAN_ANM_BASE_09;
                                ZGameMgr.ClockMan[ZGameMgr.Question.SelectIndex].Character.Anm.Index    = 0;
                                ZGameMgr.ClockMan[ZGameMgr.Question.SelectIndex].Character.Anm.Data.wt  = 0;
                                ZGameMgr.ClockMan[ZGameMgr.Question.SelectIndex].Character.Anm.Data.no  = ClockManSpriteTable[ ZGameMgr.ClockMan[ZGameMgr.Question.SelectIndex].AnmBase + ZGameMgr.ClockMan[ZGameMgr.Question.SelectIndex].Character.Anm.Index ].No;
                                ZGameMgr.ClockMan[ZGameMgr.Question.SelectIndex].Character.OPos.x       = ClockManSpriteTable[ ZGameMgr.ClockMan[ZGameMgr.Question.SelectIndex].AnmBase ].Ofx;
                                ZGameMgr.ClockMan[ZGameMgr.Question.SelectIndex].Character.OPos.y       = ClockManSpriteTable[ ZGameMgr.ClockMan[ZGameMgr.Question.SelectIndex].AnmBase ].Ofy;
                                ZGameMgr.ClockMan[ZGameMgr.Question.SelectIndex].AnmCount               = 0;
                                
                                break;
                            //----------------不正解
                            case ANSWER_NG:
                                GameMgr.WaitFlag = ON;          // iwasawa Correction (2003/4/27)
                                //[♪]まちがい
                                ssPlaySe(ZIRI_SE_01);
                                
                                //----ステータス変更：決定
                                ZGameMgr.Player.Character.Status    = PLAYER_DECISION;
                                
                                dscale  = SCALE05;
                                ZGameMgr.Player.WaitTimer = PLAYER_DECISION_WAIT_TIME;
                                
                                //----今の問題はクリアします、新しく生成する場合は空いているところに
                                ZGameMgr.Question.GetDataFlag[ZGameMgr.Question.SelectIndex]    = 0;
                                ZGameMgr.Question.ExistFlag[ZGameMgr.Question.SelectIndex]      = 1;
                                
                                //----ステ-タス変更：壊れるへ
                                ZGameMgr.ClockMan[ZGameMgr.Question.SelectIndex].Character.Status   = CLOCKMAN_BREAK;
                                ZGameMgr.ClockMan[ZGameMgr.Question.SelectIndex].Time               = -1;
                                ZGameMgr.ClockMan[ZGameMgr.Question.SelectIndex].RevivalWait        = 1;
                                
                                //----アニメベース
                                ZGameMgr.ClockMan[ZGameMgr.Question.SelectIndex].AnmBase                = CLOCKMAN_ANM_BASE_11;
                                ZGameMgr.ClockMan[ZGameMgr.Question.SelectIndex].Character.Anm.Index    = 0;
                                ZGameMgr.ClockMan[ZGameMgr.Question.SelectIndex].Character.Anm.Data.wt  = 0;
                                ZGameMgr.ClockMan[ZGameMgr.Question.SelectIndex].Character.Anm.Data.no  = ClockManSpriteTable[ ZGameMgr.ClockMan[ZGameMgr.Question.SelectIndex].AnmBase + ZGameMgr.ClockMan[ZGameMgr.Question.SelectIndex].Character.Anm.Index ].No;
                                ZGameMgr.ClockMan[ZGameMgr.Question.SelectIndex].Character.OPos.x       = ClockManSpriteTable[ ZGameMgr.ClockMan[ZGameMgr.Question.SelectIndex].AnmBase ].Ofx;
                                ZGameMgr.ClockMan[ZGameMgr.Question.SelectIndex].Character.OPos.y       = ClockManSpriteTable[ ZGameMgr.ClockMan[ZGameMgr.Question.SelectIndex].AnmBase ].Ofy;
                                ZGameMgr.ClockMan[ZGameMgr.Question.SelectIndex].AnmCount               = 0;
                                
                                break;
                            //----------------存在しない
                            case ANSWER_NONE:
                            default:
                                break;
                        }
                    }
                    
                    break;
                //--------------------------------------------決定
                case PLAYER_DECISION:
                    //----復活する時計マンがいるので、復活まで待ちます
                    if(--ZGameMgr.Player.WaitTimer < 0)
                    {
                        GameMgr.WaitFlag = OFF;         // iwasawa Correction (2003/4/27)
                        //----ステータス変更：選択へ
                        ZGameMgr.Player.Character.Status    = PLAYER_SELECT;
                        
                        dscale                              = SCALE10;
                        
                        //----正解、不正解にかかわらず次の問題へインデックを取得
                        if( GetQuestionIndex(&nextindex) ){
                            ZGameMgr.Question.Index = nextindex;
                            
                            //[♪]時間をコール
                            dsPlayXa(   ClockXaTable[ ZGameMgr.Question.Time[ ZGameMgr.Question.Index ] ].FileNo,
                                        ClockXaTable[ ZGameMgr.Question.Time[ ZGameMgr.Question.Index ] ].ChannelNo);
                        }
                    }
                    break;
                default:
            }
            
            
            //----カーソル
            SpData.No       = ZGameMgr.Player.Character.Anm.Data.no;
            SpData.PosX     = ZGameMgr.Player.Character.Pos.x + ZGameMgr.Player.Character.OPos.x;
            SpData.PosY     = ZGameMgr.Player.Character.Pos.y + ZGameMgr.Player.Character.OPos.y;
            SpData.PosZ     = ZGameMgr.Player.Character.Pos.z + ZGameMgr.Player.Character.OPos.z;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
        //  SpData.ScaleX   = dscale;
        //  SpData.ScaleY   = dscale;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );
            
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
//  関数名  :ClockManTask
//
//  work    :時計マンタスク
//  in      :TASK* ip_task
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int ClockManTask(TASK* ip_task)
{
    TASK Task;
    SPRITE_DATA SpData;
    int i,j,rval,rval2,pchk;


    switch(ip_task->mode)
    {
        //----------------------------------------------------------------初期化
        case TASK_MODE_INIT:
            //----
            ip_task->mode = TASK_MODE_MAIN;
            
            //----初期化
            rval    = rand()%10;
            rval2   = rand()%5;
            for(i=0;i<MAX_CLOCKMAN_NUM;i++)
            {
                ZGameMgr.ClockMan[i].AnmBase                = ClockManAnmBaseTable[rand() % MAX_CLOCKMAN_TYPE]; //アニメベース
                ZGameMgr.ClockMan[i].Pos                    = ClockManPosDataTable[rval][i];    //配置位置
            //  ZGameMgr.ClockMan[i].Time                   = GetQuestion(ZGameMgr.PlayLevel);  //問題の時間
                //初期値を設定するように変更
                ZGameMgr.ClockMan[i].Time                   = GetQuestionFirst(ZGameMgr.PlayLevel,rval2,i); //問題の時間

                ZGameMgr.ClockMan[i].RevivalWait            = 0;                                //待ちフラグ
                ZGameMgr.ClockMan[i].AnmCount               = 0;
                ZGameMgr.ClockMan[i].Character.Status       = CLOCKMAN_SELECT;
                ZGameMgr.ClockMan[i].Character.Anm.Data.no  = ClockManSpriteTable[ ZGameMgr.ClockMan[i].AnmBase ].No;
                ZGameMgr.ClockMan[i].Character.Anm.Data.wt  = 0;
                ZGameMgr.ClockMan[i].Character.Anm.Index    = 0;
                ZGameMgr.ClockMan[i].Character.Pos.x        = ClockManPosTable[ ZGameMgr.ClockMan[i].Pos ].x;
                ZGameMgr.ClockMan[i].Character.Pos.y        = ClockManPosTable[ ZGameMgr.ClockMan[i].Pos ].y;
                ZGameMgr.ClockMan[i].Character.Pos.z        = PRIORITY_CLOCK;
                ZGameMgr.ClockMan[i].HandOfx                = ClockHandOffsetTable[ ZGameMgr.ClockMan[i].AnmBase ].Ofx;
                ZGameMgr.ClockMan[i].HandOfy                = ClockHandOffsetTable[ ZGameMgr.ClockMan[i].AnmBase ].Ofy;
                ZGameMgr.ClockMan[i].Character.OPos.z       = 0;
                ZGameMgr.ClockMan[i].Character.Spd.dx       = 0;
                ZGameMgr.ClockMan[i].Character.Spd.dy       = 0;
                ZGameMgr.ClockMan[i].Character.Spd.sx       = 0;
                ZGameMgr.ClockMan[i].Character.Spd.sy       = 0;
            }
            
            break;
        //----------------------------------------------------------------メイン
        case TASK_MODE_MAIN:
            
            for(i=0;i<MAX_CLOCKMAN_NUM;i++)
            {
                switch(ZGameMgr.ClockMan[i].Character.Status)
                {
                    //--------------------------------------------選択中
                    case CLOCKMAN_SELECT:
                        break;
                    //--------------------------------------------復活待ち
                    case CLOCKMAN_REVIVAL_WAIT:
                        
                        if(ZGameMgr.ClockMan[i].RevivalWait==0)
                        {//----復活待ちフラグ
                            //----ステータス変更:復活へ
                            ZGameMgr.ClockMan[i].Character.Status   = CLOCKMAN_APPEAR;
                            
                            ZGameMgr.ClockMan[i].AnmCount                   = 0;
                            //----
                            ZGameMgr.ClockMan[i].AnmBase                    = CLOCKMAN_ANM_BASE_10;
                            ZGameMgr.ClockMan[i].Character.Anm.Data.wt      = 0;
                            ZGameMgr.ClockMan[i].Character.Anm.Index        = 0;
                            ZGameMgr.ClockMan[i].Character.Anm.Data.no      = ClockManSpriteTable[ ZGameMgr.ClockMan[i].AnmBase + ZGameMgr.ClockMan[i].Character.Anm.Index ].No;
                            ZGameMgr.ClockMan[i].Character.OPos.x           = ClockManSpriteTable[ ZGameMgr.ClockMan[i].AnmBase ].Ofx;
                            ZGameMgr.ClockMan[i].Character.OPos.y           = ClockManSpriteTable[ ZGameMgr.ClockMan[i].AnmBase ].Ofy;
                        }
                        break;
                    //--------------------------------------------復活中（復活アニメ）
                    case CLOCKMAN_APPEAR:
                        
                        //----アニメ終了後：選択中へ
                        if(++ZGameMgr.ClockMan[i].AnmCount >= 2*CLOCKMAN_ANM_WAIT_TIME)
                        {
                            //----ステータス変更：選択中へ
                            ZGameMgr.ClockMan[i].Character.Status = CLOCKMAN_SELECT;
                            
                            //----問題の時間
                            ZGameMgr.ClockMan[i].Time               = GetQuestion(ZGameMgr.PlayLevel);
                            
                            //----新しい問題を登録
                            ZGameMgr.Question.Time[i]               = ZGameMgr.ClockMan[i].Time;
                            
                            //----取得OKフラグセット
                            ZGameMgr.Question.GetDataFlag[i]        = 1;
                            
                            //----アニメベース：時計の形はランダム取得
                            ZGameMgr.ClockMan[i].AnmBase            = ClockManAnmBaseTable[rand() % MAX_CLOCKMAN_TYPE]; 
                            
                            //----オフセット
                            ZGameMgr.ClockMan[i].HandOfx            = ClockHandOffsetTable[ ZGameMgr.ClockMan[i].AnmBase ].Ofx;
                            ZGameMgr.ClockMan[i].HandOfy            = ClockHandOffsetTable[ ZGameMgr.ClockMan[i].AnmBase ].Ofy;
                            ZGameMgr.ClockMan[i].Character.OPos.x   = ClockManSpriteTable[ ZGameMgr.ClockMan[i].AnmBase ].Ofx;
                            ZGameMgr.ClockMan[i].Character.OPos.y   = ClockManSpriteTable[ ZGameMgr.ClockMan[i].AnmBase ].Ofy;
                        }
                        
                        break;
                    //--------------------------------------------消える(正解で消える)
                    case CLOCKMAN_DISAPPEAR:
                        //----アニメ終了後：終了へ
                        if(++ZGameMgr.ClockMan[i].AnmCount >= 2*CLOCKMAN_ANM_WAIT_TIME)
                        {
                            //----復活待ちがいたら復活させる
                            for(j=0;j<MAX_CLOCKMAN_NUM;j++){
                                if(j==i) continue;  //自分は無視
                                if(ZGameMgr.ClockMan[j].Character.Status==CLOCKMAN_REVIVAL_WAIT){
                                    ZGameMgr.ClockMan[j].RevivalWait=0;
                                }
                            }
                            
                            //----アニメ修正
                            ZGameMgr.ClockMan[i].AnmBase                = CLOCKMAN_ANM_BASE_07;
                            ZGameMgr.ClockMan[i].Character.Anm.Index    = 0;
                            ZGameMgr.ClockMan[i].Character.Anm.Data.wt  = 0;
                            ZGameMgr.ClockMan[i].Character.Anm.Data.no  = ClockManSpriteTable[ ZGameMgr.ClockMan[i].AnmBase + ZGameMgr.ClockMan[i].Character.Anm.Index ].No;
                            ZGameMgr.ClockMan[i].Character.OPos.x       = ClockManSpriteTable[ ZGameMgr.ClockMan[i].AnmBase ].Ofx;
                            ZGameMgr.ClockMan[i].Character.OPos.y       = ClockManSpriteTable[ ZGameMgr.ClockMan[i].AnmBase ].Ofy;
                            
                            //----ステータス変更:終了へ
                            ZGameMgr.ClockMan[i].Character.Status = CLOCKMAN_END;
                            
                            //----おめでとうフラグセット
                            if(ZGameMgr.ClearFlag){
                                //----時計マンタスク終了
                                ip_task->mode = TASK_MODE_EXIT;
                            }
                        }
                        break;
                    //--------------------------------------------壊れ中(不正解壊れる)
                    case CLOCKMAN_BREAK:
                        //----アニメ終了後：復活待ちへ 
                        if(++ZGameMgr.ClockMan[i].AnmCount >= 2*CLOCKMAN_ANM_WAIT_TIME)
                        {
                            //----復活待ちがいたら復活させる
                            for(j=0;j<MAX_CLOCKMAN_NUM;j++){
                                if(j==i) continue;  //自分は無視
                                if(ZGameMgr.ClockMan[j].Character.Status==CLOCKMAN_REVIVAL_WAIT){
                                    ZGameMgr.ClockMan[j].RevivalWait=0;
                                }
                            }
                            
                            //----アニメ修正
                            ZGameMgr.ClockMan[i].AnmBase                = CLOCKMAN_ANM_BASE_08;
                            ZGameMgr.ClockMan[i].Character.Anm.Index    = 0;
                            ZGameMgr.ClockMan[i].Character.Anm.Data.wt  = 0;
                            ZGameMgr.ClockMan[i].Character.Anm.Data.no  = ClockManSpriteTable[ ZGameMgr.ClockMan[i].AnmBase + ZGameMgr.ClockMan[i].Character.Anm.Index ].No;
                            ZGameMgr.ClockMan[i].Character.OPos.x       = ClockManSpriteTable[ ZGameMgr.ClockMan[i].AnmBase ].Ofx;
                            ZGameMgr.ClockMan[i].Character.OPos.y       = ClockManSpriteTable[ ZGameMgr.ClockMan[i].AnmBase ].Ofy;
                            
                            //----ステータス変更:復活待ちへ 
                            ZGameMgr.ClockMan[i].Character.Status = CLOCKMAN_REVIVAL_WAIT;
                        }
                        break;
                    //--------------------------------------------終了
                    case CLOCKMAN_END:
                        break;
                    default:
                }
                
                
                //----アニメ
                if(++ZGameMgr.ClockMan[i].Character.Anm.Data.wt > CLOCKMAN_ANM_WAIT_TIME)
                {
                    ZGameMgr.ClockMan[i].Character.Anm.Data.wt      = 0;
                    ZGameMgr.ClockMan[i].Character.Anm.Index        ^= 1;
                    ZGameMgr.ClockMan[i].Character.Anm.Data.no      = ClockManSpriteTable[ ZGameMgr.ClockMan[i].AnmBase + ZGameMgr.ClockMan[i].Character.Anm.Index ].No;
                    ZGameMgr.ClockMan[i].Character.OPos.x           = ClockManSpriteTable[ ZGameMgr.ClockMan[i].AnmBase + ZGameMgr.ClockMan[i].Character.Anm.Index ].Ofx;
                    ZGameMgr.ClockMan[i].Character.OPos.y           = ClockManSpriteTable[ ZGameMgr.ClockMan[i].AnmBase + ZGameMgr.ClockMan[i].Character.Anm.Index ].Ofy;
                }
                
                //----時計描画
                SpData.No       = ZGameMgr.ClockMan[i].Character.Anm.Data.no;
                SpData.PosX     = ZGameMgr.ClockMan[i].Character.Pos.x + ZGameMgr.ClockMan[i].Character.OPos.x;
                SpData.PosY     = ZGameMgr.ClockMan[i].Character.Pos.y + ZGameMgr.ClockMan[i].Character.OPos.y;
                SpData.PosZ     = ZGameMgr.ClockMan[i].Character.Pos.z + ZGameMgr.ClockMan[i].Character.OPos.z;
                SpData.ScaleX   = SCALE10;
                SpData.ScaleY   = SCALE10;
                SpData.Rotate   = ROTATE000;
                SpData.Reverse  = NOREVERS;
                DrawSprite( &SpData );
                
                //-----時計の針描画
                if(ZGameMgr.ClockMan[i].Character.Status==CLOCKMAN_SELECT)
                {
                    if(ZGameMgr.ClockMan[i].Time != -1){
//                      DrawClockHand(  ZGameMgr.ClockMan[i].Time,
//                                      ZGameMgr.ClockMan[i].Character.Pos.x + ZGameMgr.ClockMan[i].Character.OPos.x + ZGameMgr.ClockMan[i].HandOfx,
//                                      ZGameMgr.ClockMan[i].Character.Pos.y + ZGameMgr.ClockMan[i].Character.OPos.y + ZGameMgr.ClockMan[i].HandOfy,
//                                      ZGameMgr.ClockMan[i].Character.Pos.z + ZGameMgr.ClockMan[i].Character.OPos.z-1 );

                        DrawClock(ZGameMgr.ClockMan[i].Time,
                                  ZGameMgr.ClockMan[i].Character.Pos.x + ZGameMgr.ClockMan[i].Character.OPos.x + ZGameMgr.ClockMan[i].HandOfx,
                                  ZGameMgr.ClockMan[i].Character.Pos.y + ZGameMgr.ClockMan[i].Character.OPos.y + ZGameMgr.ClockMan[i].HandOfy,
                                  ZGameMgr.ClockMan[i].Character.Pos.z + ZGameMgr.ClockMan[i].Character.OPos.z-1 );
                    }
                }
            }
            
            break;
        //----------------------------------------------------------------終了
        case TASK_MODE_EXIT:
            //----タスク終了
            RemoveTask(TASK_NO_GAME_PLAYER);
            RemoveTask(TASK_NO_GAME_QUESTION);
            RemoveTask(TASK_NO_GAME_PAUSE);
            RemoveTask(TASK_NO_GAME_TIMER);
                                
            //----おめでとうタスク
            Task.func       = CongratulationsTask;
            Task.priority   = TASK_NO_GAME_CONGRATULATIONS;
            Task.attribute  = ATTR_USER;
            Task.status     = TASK_NEW_ENTRY;
            Task.id         = TASK_NO_GAME_CONGRATULATIONS;
            Task.wait_time  = 0;
            Task.buf        = NULL;
            Task.name       = "CongratulationsTask";
            Task.mode       = TASK_MODE_INIT;
            CreateTask(&Task);
            
            //----自分を削除
            ExitTask(ip_task->id);
            break;
        default:
    }
    
    return TRUE;
}


//-----------------------------------------------------------------------------
//  関数名  :QuestionTask
//
//  work    :質問タスク
//  in      :TASK* ip_task
//  out     :TRUE
//  note    :ClockManTaskの後に起動
//-----------------------------------------------------------------------------
static int QuestionTask(TASK* ip_task)
{
    int i;

    switch(ip_task->mode)
    {
        //----------------------------------------------------------------初期化
        case TASK_MODE_INIT:
            //----
            ip_task->mode = TASK_MODE_MAIN;
            
            
            //----初期化
            ZGameMgr.Question.Index         = 0;
            ZGameMgr.Question.SelectIndex   = 0;
            
            //----答え取得、存在フラグセット
            for(i=0;i<MAX_CLOCKMAN_NUM;i++){
                ZGameMgr.Question.GetDataFlag[i]    = 1;
                ZGameMgr.Question.ExistFlag[i]      = 1;
                ZGameMgr.Question.Time[i]           = ZGameMgr.ClockMan[i].Time;
            }


            //１問目のみコール
            //[♪]時間をコール
            dsPlayXa(   ClockXaTable[ ZGameMgr.Question.Time[ ZGameMgr.Question.Index ] ].FileNo,
                        ClockXaTable[ ZGameMgr.Question.Time[ ZGameMgr.Question.Index ] ].ChannelNo);

            break;
        //----------------------------------------------------------------メイン
        case TASK_MODE_MAIN:
            
            //----デジタル時計の描画
            DrawClockTime( ZGameMgr.Question.Time[ ZGameMgr.Question.Index ] );
            
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
//  関数名  :GameBgTask
//
//  work    :背景タスク
//  in      :TASK* ip_task
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int GameBgTask(TASK* ip_task)
{
    SPRITE_DATA SpData;


    switch(ip_task->mode)
    {
        //----------------------------------------------------------------初期化
        case TASK_MODE_INIT:
            //----
            ip_task->mode = TASK_MODE_MAIN;
            break;
        //----------------------------------------------------------------メイン
        case TASK_MODE_MAIN:
            
            //----背景左
            SpData.No       = ZIRI_CHAR_GAME_GAME_BG_00;
            SpData.PosX     = 0;
            SpData.PosY     = 0;
            SpData.PosZ     = PRIORITY_BG;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );
            
            //----背景右
            SpData.No       = ZIRI_CHAR_GAME_GAME_BG_01;
            SpData.PosX     = 256;
            SpData.PosY     = 0;
            SpData.PosZ     = PRIORITY_BG-1;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );
            
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
                    SleepTask(TASK_NO_GAME_PLAYER);
                    SleepTask(TASK_NO_GAME_CLOCKMAN);
                    SleepTask(TASK_NO_GAME_QUESTION);
                    SleepTask(TASK_NO_GAME_TIMER);
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
                    WakeupTask(TASK_NO_GAME_PLAYER);
                    WakeupTask(TASK_NO_GAME_CLOCKMAN);
                    WakeupTask(TASK_NO_GAME_QUESTION);
                    WakeupTask(TASK_NO_GAME_TIMER);
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
//  関数名  :TimerTask
//
//  work    :タイマータスク
//  in      :TASK* ip_task
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int TimerTask(TASK* ip_task)
{
    static int TimerLightSpriteTable[]={
        ZIRI_CHAR_GAME_LIGHT_GREEN,     //信号用緑
        ZIRI_CHAR_GAME_LIGHT_GREEN,     //信号用緑
        ZIRI_CHAR_GAME_LIGHT_GREEN,     //信号用緑
        ZIRI_CHAR_GAME_LIGHT_YELLOW,    //信号用黄色
        ZIRI_CHAR_GAME_LIGHT_YELLOW,    //信号用黄色
        ZIRI_CHAR_GAME_LIGHT_RED,       //信号用赤
        ZIRI_CHAR_GAME_LIGHT_RED,       //信号用赤
    };

    SPRITE_DATA SpData;
    int i;

    switch( ip_task->mode )
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //----NEXT
            ip_task->mode       = TASK_MODE_MAIN;
            
            //----初期化
            ZGameMgr.TimerLight.Timer   = 0;
            ZGameMgr.TimerLight.Count   = 0;
            
            break;
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:
            
            //----タイマー
            if(++ZGameMgr.TimerLight.Timer > TIMER_LIGHT_WAIT_TIME){
                ZGameMgr.TimerLight.Timer = 0;
                
                if(++ZGameMgr.TimerLight.Count>MAX_TIMER_LIGHT_NUM){
                    ZGameMgr.TimerLight.Count = MAX_TIMER_LIGHT_NUM;
                    
                    GameMgr.WaitFlag = ON;          // iwasawa Correction (2003/4/27)
                    //----タイムアップ
                    ZGameMgr.TimeUpFlag = 1;
                    RemoveTask(TASK_NO_GAME_PAUSE);
                }
            }
            
            //----描画
            for(i=0;i<ZGameMgr.TimerLight.Count;i++)
            {
                SpData.No       = TimerLightSpriteTable[i];
                SpData.PosX     = 115 + i*13;
                SpData.PosY     = 16;
                SpData.PosZ     = PRIORITY_TIMER_LIGHT;
                SpData.ScaleX   = SCALE10;
                SpData.ScaleY   = SCALE10;
                SpData.Rotate   = ROTATE000;
                SpData.Reverse  = NOREVERS;
                DrawSprite( &SpData );
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
//                  ZGameMgr.Script.Flag    = 0;
//                  ZGameMgr.Script.Index   = 0;
//                  ZGameMgr.Script.Line    = ip_task->user[0];
//                  ZGameMgr.Script.Base    = ip_task->user[1];
//                  ZGameMgr.Script.Num     = ip_task->user[2];
//                  
//                  break;
//              //---------------------------------------------------------------------
//              case TASK_MODE_MAIN:
//                  
//                  if(MetuseijiFlag==OFF)
//                  {
//                      switch(ZGameMgr.Script.Line)
//                      {
//                          case SCRIPT_LINE_1:
//                              MenuMessageSet10(&ZiriScript[ZGameMgr.Script.Base + ZGameMgr.Script.Index]);
//                              break;
//                          case SCRIPT_LINE_2:
//                              MenuMessageSet20(&ZiriScript[ZGameMgr.Script.Base + ZGameMgr.Script.Index]);
//                              break;
//                          case SCRIPT_LINE_3:
//                              MenuMessageSet30(&ZiriScript[ZGameMgr.Script.Base + ZGameMgr.Script.Index]);
//                              break;
//                          default:
//                      }
//                      
//                      if(++ZGameMgr.Script.Index >= ZGameMgr.Script.Num)
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

            ZGameMgr.Script.Flag    = 1;
            ZGameMgr.Script.Index   = 0;
            ZGameMgr.Script.Line    = ip_task->user[0];
            ZGameMgr.Script.Base    = ip_task->user[1];
            ZGameMgr.Script.Num     = ip_task->user[2];
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
                        switch(ZGameMgr.Script.Line)
                        {
                            case SCRIPT_LINE_1:
                                MenuMessageSet10(&ZiriScript[ZGameMgr.Script.Base + ZGameMgr.Script.Index]);
                                break;
                            case SCRIPT_LINE_2:
                                MenuMessageSet20(&ZiriScript[ZGameMgr.Script.Base + ZGameMgr.Script.Index]);
                                break;
                            case SCRIPT_LINE_3:
                                MenuMessageSet30(&ZiriScript[ZGameMgr.Script.Base + ZGameMgr.Script.Index]);
                                break;
                            default:
                        }
                        
                        if(++ZGameMgr.Script.Index >= ZGameMgr.Script.Num){
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
            
            ZGameMgr.Script.Flag    = 0;
            
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
            ZGameMgr.ExitFlag   = 1;
            
            //自分を削除
            ExitTask(ip_task->id);
            break;
        default:
    }
    return TRUE;
}



//-----------------------------------------------------------------------------
//  関数名  :CongratulationsTask
//
//  work    :おめでとうタスク
//  in      :TASK* ip_task
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int CongratulationsTask(TASK* ip_task)
{
    SPRITE_DATA SpData;

    switch( ip_task->mode )
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //----NEXT
            ip_task->mode       = TASK_MODE_MAIN;

            //----初期化
            ip_task->user[0]    = 0;

            //[♪] おめでとう
            dsStopXa();
            ssPlaySe(ZIRI_SE_02);

            break;
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:

            //----おめでとうタイマー
            if( ++ip_task->user[0] > CONGRATULATIONS_WAIT_TIME ){
                ZGameMgr.ClearEndFlag = 1;
            }

            //----おめでとう描画
            SpData.No       = ZIRI_CHAR_GAME_PLATE_CONGRATULATIONS;
            SpData.PosX     = 129;
            SpData.PosY     = 81;
            SpData.PosZ     = PRIORITY_CONGRATULATIONS;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );
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
//  関数名  :ClearEventTask
//
//  work    :クリアイベントタスク
//  in      :TASK* ip_task
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int ClearEventTask(TASK* ip_task)
{
    TASK Task;

    switch( ip_task->mode )
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //----NEXT
            ip_task->mode       = TASK_MODE_MAIN;

            //----初期化
            ZGameMgr.Event.Timer                        = 0;
            ZGameMgr.Event.EndFlag                      = 0;
            ZGameMgr.Event.Clear.BgAnmWaitTimer         = 0;
            ZGameMgr.Event.Clear.BgAnmIndex             = 0;
            ZGameMgr.Event.Clear.ClockManAnmNo          = 0;
            ZGameMgr.Event.Clear.ClockManAnmWaitTimer   = 0;
            ZGameMgr.Event.Clear.ClockManAnmIndex       = 0;

            //----終了処理メニュー
            ZGameMgr.SelectContinue.Val         = 0;
            ZGameMgr.SelectContinue.Type        = SELECT_RETRY_H;
            ZGameMgr.SelectContinue.No          = 0;
            ZGameMgr.SelectContinue.Wt          = 0;
            ZGameMgr.SelectContinue.FadeFlag    = 0;

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
            Task.user[1]        = CLEAR_DEMO_SCRIPT_BASE;
            Task.user[2]        = CLEAR_DEMO_SCRIPT_NUM;
            CreateTask(&Task);


#ifdef __DEBUG_ZIRI__
            //フェードイン
            GameMgr.FadeFlag    = FadeIn;
#endif

            break;
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:
            //----終了メニューチェック
            if(++ZGameMgr.Event.Timer > ZIRI_GAME_CLEAR_EVENT_END_TIME){
                ZGameMgr.Event.EndFlag = 1;
            }

            //----背景と時計マン
            ClearEventClockMan();
            ClearEventBg();

            //----もう一度プレイしますか？
            if(ZGameMgr.Event.EndFlag)
            {
                if(SelectContinue(!ZGameMgr.SelectContinue.FadeFlag))
                {//●ボタンが押された
                    if(!ZGameMgr.SelectContinue.FadeFlag)
                    {//フェード中

                        if((ZGameMgr.SelectContinue.Val==0) && (ZGameMgr.SelectContinue.Type==SELECT_RETRY_H))
                        {//もう一度プレイしますか？　はい
                            ZGameMgr.SelectContinue.FadeFlag    = 1;
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
                        if( (ZGameMgr.SelectContinue.Val==1) && (ZGameMgr.SelectContinue.Type==SELECT_RETRY_H))
                        {//もう一度プレイしますか？　いいえ
                            ZGameMgr.SelectContinue.Type    =SELECT_END_H;
                            ZGameMgr.SelectContinue.Val     = 0;
                        }else
                        if((ZGameMgr.SelectContinue.Type==SELECT_END_H) && (ZGameMgr.SelectContinue.Val==0))
                        {//やめますか？　はい
                            ZGameMgr.SelectContinue.FadeFlag    = 1;
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
                        if((ZGameMgr.SelectContinue.Type==SELECT_END_H) && (ZGameMgr.SelectContinue.Val==1))
                        {//やめますか？　いいえ
                            ZGameMgr.SelectContinue.Type    = SELECT_RETRY_H;
                            ZGameMgr.SelectContinue.Val     = 0;
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
            if((ZGameMgr.SelectContinue.Val==0) && (ZGameMgr.SelectContinue.Type==SELECT_RETRY_H))
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
                ZGameMgr.ExitFlag=1;
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
//  work    :オールクリアイベント
//  in      :TASK* ip_task
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int AllClearEventTask(TASK* ip_task)
{
    TASK Task;

    switch( ip_task->mode )
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //----NEXT
            ip_task->mode       = TASK_MODE_MAIN;
            
            //----初期化
            ZGameMgr.Event.Timer                = 0;
            ZGameMgr.Event.EndFlag              = 0;
            
            ZGameMgr.Event.AllClear.Mode                        = 0;
            ZGameMgr.Event.AllClear.Timer                       = 0;
            ZGameMgr.Event.AllClear.BgAnmWaitTimer              = 0;
            ZGameMgr.Event.AllClear.BgAnmIndex                  = 0;

            //----clockman
            ZGameMgr.Event.AllClear.ClockManMode                = 0;
            ZGameMgr.Event.AllClear.ClockManAnmWaitTimer        = 0;
            ZGameMgr.Event.AllClear.ClockManBodyAnmIndex        = 0;
            ZGameMgr.Event.AllClear.ClockManArmAnmIndex         = 0;
            ZGameMgr.Event.AllClear.ClockManClockMaskFlag       = 0;

            //----small clockman
            ZGameMgr.Event.AllClear.SmallClockManMode           = 0;
            ZGameMgr.Event.AllClear.SmallClockManAnmWaitTimer   = 0;
            ZGameMgr.Event.AllClear.SmallClockManAnmIndex       = 0;

            ZGameMgr.Event.AllClear.StarTimer                   = 0;
            ZGameMgr.Event.AllClear.StarMode                    = 0;
            
            //----終了処理メニュー
            ZGameMgr.SelectContinue.Val         = 0;
            ZGameMgr.SelectContinue.Type        = SELECT_RETRY_H;
            ZGameMgr.SelectContinue.No          = 0;
            ZGameMgr.SelectContinue.Wt          = 0;
            ZGameMgr.SelectContinue.FadeFlag    = 0;

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
            Task.user[1]        = ALL_CLEAR_DEMO_SCRIPT_BASE;
            Task.user[2]        = ALL_CLEAR_DEMO_SCRIPT_NUM;
            CreateTask(&Task);

#ifdef __DEBUG_ZIRI__
            //フェードイン
            GameMgr.FadeFlag    = FadeIn;
#endif

            break;
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:
            //----終了メニューチェック
            if(++ZGameMgr.Event.Timer > ZIRI_GAME_ALL_CLEAR_EVENT_END_TIME){
                ZGameMgr.Event.EndFlag = 1;
            }
            
            //----時計マン、小時計マン、★、背景
            AllClearEventClockMan();
            AllClearEventSmallClockMan();
            AllClearEventStar();
            AllClearEventBg();
            
            //----もう一度プレイしますか？
            if(ZGameMgr.Event.EndFlag)
            {
                if(SelectContinue(!ZGameMgr.SelectContinue.FadeFlag))
                {//●ボタンが押された
                    if(!ZGameMgr.SelectContinue.FadeFlag)
                    {//フェード中

                        if((ZGameMgr.SelectContinue.Val==0) && (ZGameMgr.SelectContinue.Type==SELECT_RETRY_H))
                        {//もう一度プレイしますか？　はい
                            ZGameMgr.SelectContinue.FadeFlag    = 1;
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
                        if( (ZGameMgr.SelectContinue.Val==1) && (ZGameMgr.SelectContinue.Type==SELECT_RETRY_H))
                        {//もう一度プレイしますか？　いいえ
                            ZGameMgr.SelectContinue.Type    =SELECT_END_H;
                            ZGameMgr.SelectContinue.Val     = 0;
                        }else
                        if((ZGameMgr.SelectContinue.Type==SELECT_END_H) && (ZGameMgr.SelectContinue.Val==0))
                        {//やめますか？　はい
                            ZGameMgr.SelectContinue.FadeFlag    = 1;
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
                        if((ZGameMgr.SelectContinue.Type==SELECT_END_H) && (ZGameMgr.SelectContinue.Val==1))
                        {//やめますか？　いいえ
                            ZGameMgr.SelectContinue.Type    = SELECT_RETRY_H;
                            ZGameMgr.SelectContinue.Val     = 0;
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
            if((ZGameMgr.SelectContinue.Val==0) && (ZGameMgr.SelectContinue.Type==SELECT_RETRY_H))
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
                ZGameMgr.ExitFlag=1;
            }
            
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
//  work    :失敗イベント
//  in      :TASK* ip_task
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int FalseEventTask(TASK* ip_task)
{
    TASK Task;

    switch( ip_task->mode )
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //----NEXT
            ip_task->mode       = TASK_MODE_MAIN;
            
            //----初期化
            ZGameMgr.Event.Timer                        = 0;
            ZGameMgr.Event.EndFlag                      = 0;
            ZGameMgr.Event.False.Mode                   = FALSE_EVENT_MODE_BAKU;
            ZGameMgr.Event.False.Timer                  = 0;
            ZGameMgr.Event.False.ClockManAnmWaitTimer   = 0;
            ZGameMgr.Event.False.ClockManAnmIndex       = 0;
            ZGameMgr.Event.False.ClockManAngle          = 0;
            ZGameMgr.Event.False.ClockManPosX           = 0;
            ZGameMgr.Event.False.ClockManPosY           = 0;
            ZGameMgr.Event.False.ClockManWorkPosX       = 0;

            //----終了処理メニュー
            ZGameMgr.SelectContinue.Val         = 0;
            ZGameMgr.SelectContinue.Type        = SELECT_RETRY_H;
            ZGameMgr.SelectContinue.No          = 0;
            ZGameMgr.SelectContinue.Wt          = 0;
            ZGameMgr.SelectContinue.FadeFlag    = 0;

//          //スクリプト
//          Task.func           = ScriptTask;
//          Task.priority       = TASK_NO_GAME_SCRIPT;
//          Task.attribute      = ATTR_USER;
//          Task.status         = TASK_NEW_ENTRY;
//          Task.id             = TASK_NO_GAME_SCRIPT;
//          Task.wait_time      = 0;
//          Task.buf            = NULL;
//          Task.name           = "ScriptTask";
//          Task.mode           = TASK_MODE_INIT;
//          Task.user[0]        = SCRIPT_LINE_2;
//          Task.user[1]        = FALSE_DEMO_SCRIPT_BASE;
//          Task.user[2]        = FALSE_DEMO_SCRIPT_NUM;
//          CreateTask(&Task);

            //[♪]ヒョエー
            dsPlayXa(XA_FILE_ZIRI01,5);

            //[♪]バーン
            ssPlaySe(ZIRI_SE_03);


#ifdef __DEBUG_ZIRI__
            //フェードイン
            GameMgr.FadeFlag    = FadeIn;
#endif

            break;
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:
            //----終了メニューチェック
            if(++ZGameMgr.Event.Timer > ZIRI_GAME_FALSE_EVENT_END_TIME){
                ZGameMgr.Event.EndFlag = 1;
            }

            //----時計マン
            FalseEventClockMan();

            //----もう一度プレイしますか？
            if(ZGameMgr.Event.EndFlag)
            {
                if(SelectContinue(!ZGameMgr.SelectContinue.FadeFlag))
                {//●ボタンが押された
                    if(!ZGameMgr.SelectContinue.FadeFlag){
                        if((ZGameMgr.SelectContinue.Val==0) && (ZGameMgr.SelectContinue.Type==SELECT_RETRY_H))
                        {//もう一度プレイしますか？　はい
                            ZGameMgr.SelectContinue.FadeFlag    = 1;
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
                        if( (ZGameMgr.SelectContinue.Val==1) && (ZGameMgr.SelectContinue.Type==SELECT_RETRY_H))
                        {//もう一度プレイしますか？　いいえ
                            ZGameMgr.SelectContinue.Type    =SELECT_END_H;
                            ZGameMgr.SelectContinue.Val     = 0;
                        }else
                        if((ZGameMgr.SelectContinue.Type==SELECT_END_H) && (ZGameMgr.SelectContinue.Val==0))
                        {//やめますか？　はい
                            ZGameMgr.SelectContinue.FadeFlag    = 1;
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
                        if((ZGameMgr.SelectContinue.Type==SELECT_END_H) && (ZGameMgr.SelectContinue.Val==1))
                        {//やめますか？　いいえ
                            ZGameMgr.SelectContinue.Type    = SELECT_RETRY_H;
                            ZGameMgr.SelectContinue.Val     = 0;
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
            
            //----背景タスク削除
            RemoveTask(TASK_NO_GAME_BG);
            
            //--------------------ここは３択
            //  (1)セレクトレベルへ
            //  (2)メインメニュー
            //　(3)ゲーム
            if((ZGameMgr.SelectContinue.Type==SELECT_END_H) && (ZGameMgr.SelectContinue.Val==0))
            {//----ゲームをおわります
                ZGameMgr.ExitFlag=1;
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
//  関数名  :DrawClock
//
//  work    :時計描画
//  in      :int i_time
//          :int i_x
//          :int i_y
//          :int i_z
//  out     :なし
//  note    :なし
//-----------------------------------------------------------------------------
typedef struct {
    int tyousin;
    int tansin;
}CLOCK_ANGLE;

static void DrawClock(int i_time,int i_x,int i_y,int i_z)
{
    SPRITE_DATA SpData;

    static CLOCK_ANGLE ClockAngleTable[]=
    {
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_00,  ZIRI_CHAR_GAME_NEEDLE_SHORT_00  },      //CLOCK_00_00
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_01,  ZIRI_CHAR_GAME_NEEDLE_SHORT_00  },      //CLOCK_00_05
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_02,  ZIRI_CHAR_GAME_NEEDLE_SHORT_00  },      //CLOCK_00_10
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_03,  ZIRI_CHAR_GAME_NEEDLE_SHORT_01  },      //CLOCK_00_15
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_04,  ZIRI_CHAR_GAME_NEEDLE_SHORT_01  },      //CLOCK_00_20
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_05,  ZIRI_CHAR_GAME_NEEDLE_SHORT_01  },      //CLOCK_00_25
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_06,  ZIRI_CHAR_GAME_NEEDLE_SHORT_02  },      //CLOCK_00_30
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_07,  ZIRI_CHAR_GAME_NEEDLE_SHORT_02  },      //CLOCK_00_35
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_08,  ZIRI_CHAR_GAME_NEEDLE_SHORT_02  },      //CLOCK_00_40
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_09,  ZIRI_CHAR_GAME_NEEDLE_SHORT_03  },      //CLOCK_00_45
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_10,  ZIRI_CHAR_GAME_NEEDLE_SHORT_03  },      //CLOCK_00_50
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_11,  ZIRI_CHAR_GAME_NEEDLE_SHORT_03  },      //CLOCK_00_55
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_00,  ZIRI_CHAR_GAME_NEEDLE_SHORT_04  },      //CLOCK_01_00
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_01,  ZIRI_CHAR_GAME_NEEDLE_SHORT_04  },      //CLOCK_01_05
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_02,  ZIRI_CHAR_GAME_NEEDLE_SHORT_04  },      //CLOCK_01_10
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_03,  ZIRI_CHAR_GAME_NEEDLE_SHORT_05  },      //CLOCK_01_15
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_04,  ZIRI_CHAR_GAME_NEEDLE_SHORT_05  },      //CLOCK_01_20
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_05,  ZIRI_CHAR_GAME_NEEDLE_SHORT_05  },      //CLOCK_01_25
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_06,  ZIRI_CHAR_GAME_NEEDLE_SHORT_06  },      //CLOCK_01_30
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_07,  ZIRI_CHAR_GAME_NEEDLE_SHORT_06  },      //CLOCK_01_35
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_08,  ZIRI_CHAR_GAME_NEEDLE_SHORT_06  },      //CLOCK_01_40
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_09,  ZIRI_CHAR_GAME_NEEDLE_SHORT_07  },      //CLOCK_01_45
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_10,  ZIRI_CHAR_GAME_NEEDLE_SHORT_07  },      //CLOCK_01_50
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_11,  ZIRI_CHAR_GAME_NEEDLE_SHORT_07  },      //CLOCK_01_55
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_00,  ZIRI_CHAR_GAME_NEEDLE_SHORT_08  },      //CLOCK_02_00
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_01,  ZIRI_CHAR_GAME_NEEDLE_SHORT_08  },      //CLOCK_02_05
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_02,  ZIRI_CHAR_GAME_NEEDLE_SHORT_08  },      //CLOCK_02_10
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_03,  ZIRI_CHAR_GAME_NEEDLE_SHORT_09  },      //CLOCK_02_15
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_04,  ZIRI_CHAR_GAME_NEEDLE_SHORT_09  },      //CLOCK_02_20
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_05,  ZIRI_CHAR_GAME_NEEDLE_SHORT_09  },      //CLOCK_02_25
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_06,  ZIRI_CHAR_GAME_NEEDLE_SHORT_10  },      //CLOCK_02_30
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_07,  ZIRI_CHAR_GAME_NEEDLE_SHORT_10  },      //CLOCK_02_35
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_08,  ZIRI_CHAR_GAME_NEEDLE_SHORT_10  },      //CLOCK_02_40
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_09,  ZIRI_CHAR_GAME_NEEDLE_SHORT_11  },      //CLOCK_02_45
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_10,  ZIRI_CHAR_GAME_NEEDLE_SHORT_11  },      //CLOCK_02_50
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_11,  ZIRI_CHAR_GAME_NEEDLE_SHORT_11  },      //CLOCK_02_55
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_00,  ZIRI_CHAR_GAME_NEEDLE_SHORT_12  },      //CLOCK_03_00
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_01,  ZIRI_CHAR_GAME_NEEDLE_SHORT_12  },      //CLOCK_03_05
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_02,  ZIRI_CHAR_GAME_NEEDLE_SHORT_12  },      //CLOCK_03_10
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_03,  ZIRI_CHAR_GAME_NEEDLE_SHORT_13  },      //CLOCK_03_15
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_04,  ZIRI_CHAR_GAME_NEEDLE_SHORT_13  },      //CLOCK_03_20
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_05,  ZIRI_CHAR_GAME_NEEDLE_SHORT_13  },      //CLOCK_03_25
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_06,  ZIRI_CHAR_GAME_NEEDLE_SHORT_14  },      //CLOCK_03_30
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_07,  ZIRI_CHAR_GAME_NEEDLE_SHORT_14  },      //CLOCK_03_35
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_08,  ZIRI_CHAR_GAME_NEEDLE_SHORT_14  },      //CLOCK_03_40
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_09,  ZIRI_CHAR_GAME_NEEDLE_SHORT_15  },      //CLOCK_03_45
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_10,  ZIRI_CHAR_GAME_NEEDLE_SHORT_15  },      //CLOCK_03_50
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_11,  ZIRI_CHAR_GAME_NEEDLE_SHORT_15  },      //CLOCK_03_55
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_00,  ZIRI_CHAR_GAME_NEEDLE_SHORT_16  },      //CLOCK_04_00
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_01,  ZIRI_CHAR_GAME_NEEDLE_SHORT_16  },      //CLOCK_04_05
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_02,  ZIRI_CHAR_GAME_NEEDLE_SHORT_16  },      //CLOCK_04_10
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_03,  ZIRI_CHAR_GAME_NEEDLE_SHORT_17  },      //CLOCK_04_15
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_04,  ZIRI_CHAR_GAME_NEEDLE_SHORT_17  },      //CLOCK_04_20
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_05,  ZIRI_CHAR_GAME_NEEDLE_SHORT_17  },      //CLOCK_04_25
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_06,  ZIRI_CHAR_GAME_NEEDLE_SHORT_18  },      //CLOCK_04_30
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_07,  ZIRI_CHAR_GAME_NEEDLE_SHORT_18  },      //CLOCK_04_35
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_08,  ZIRI_CHAR_GAME_NEEDLE_SHORT_18  },      //CLOCK_04_40
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_09,  ZIRI_CHAR_GAME_NEEDLE_SHORT_19  },      //CLOCK_04_45
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_10,  ZIRI_CHAR_GAME_NEEDLE_SHORT_19  },      //CLOCK_04_50
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_11,  ZIRI_CHAR_GAME_NEEDLE_SHORT_19  },      //CLOCK_04_55
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_00,  ZIRI_CHAR_GAME_NEEDLE_SHORT_20  },      //CLOCK_05_00
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_01,  ZIRI_CHAR_GAME_NEEDLE_SHORT_20  },      //CLOCK_05_05
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_02,  ZIRI_CHAR_GAME_NEEDLE_SHORT_20  },      //CLOCK_05_10
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_03,  ZIRI_CHAR_GAME_NEEDLE_SHORT_21  },      //CLOCK_05_15
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_04,  ZIRI_CHAR_GAME_NEEDLE_SHORT_21  },      //CLOCK_05_20
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_05,  ZIRI_CHAR_GAME_NEEDLE_SHORT_21  },      //CLOCK_05_25
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_06,  ZIRI_CHAR_GAME_NEEDLE_SHORT_22  },      //CLOCK_05_30
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_07,  ZIRI_CHAR_GAME_NEEDLE_SHORT_22  },      //CLOCK_05_35
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_08,  ZIRI_CHAR_GAME_NEEDLE_SHORT_22  },      //CLOCK_05_40
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_09,  ZIRI_CHAR_GAME_NEEDLE_SHORT_23  },      //CLOCK_05_45
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_10,  ZIRI_CHAR_GAME_NEEDLE_SHORT_23  },      //CLOCK_05_50
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_11,  ZIRI_CHAR_GAME_NEEDLE_SHORT_23  },      //CLOCK_05_55
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_00,  ZIRI_CHAR_GAME_NEEDLE_SHORT_24  },      //CLOCK_06_00
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_01,  ZIRI_CHAR_GAME_NEEDLE_SHORT_24  },      //CLOCK_06_05
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_02,  ZIRI_CHAR_GAME_NEEDLE_SHORT_24  },      //CLOCK_06_10
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_03,  ZIRI_CHAR_GAME_NEEDLE_SHORT_25  },      //CLOCK_06_15
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_04,  ZIRI_CHAR_GAME_NEEDLE_SHORT_25  },      //CLOCK_06_20
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_05,  ZIRI_CHAR_GAME_NEEDLE_SHORT_25  },      //CLOCK_06_25
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_06,  ZIRI_CHAR_GAME_NEEDLE_SHORT_26  },      //CLOCK_06_30
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_07,  ZIRI_CHAR_GAME_NEEDLE_SHORT_26  },      //CLOCK_06_35
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_08,  ZIRI_CHAR_GAME_NEEDLE_SHORT_26  },      //CLOCK_06_40
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_09,  ZIRI_CHAR_GAME_NEEDLE_SHORT_27  },      //CLOCK_06_45
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_10,  ZIRI_CHAR_GAME_NEEDLE_SHORT_27  },      //CLOCK_06_50
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_11,  ZIRI_CHAR_GAME_NEEDLE_SHORT_27  },      //CLOCK_06_55
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_00,  ZIRI_CHAR_GAME_NEEDLE_SHORT_28  },      //CLOCK_07_00
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_01,  ZIRI_CHAR_GAME_NEEDLE_SHORT_28  },      //CLOCK_07_05
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_02,  ZIRI_CHAR_GAME_NEEDLE_SHORT_28  },      //CLOCK_07_10
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_03,  ZIRI_CHAR_GAME_NEEDLE_SHORT_29  },      //CLOCK_07_15
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_04,  ZIRI_CHAR_GAME_NEEDLE_SHORT_29  },      //CLOCK_07_20
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_05,  ZIRI_CHAR_GAME_NEEDLE_SHORT_29  },      //CLOCK_07_25
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_06,  ZIRI_CHAR_GAME_NEEDLE_SHORT_30  },      //CLOCK_07_30
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_07,  ZIRI_CHAR_GAME_NEEDLE_SHORT_30  },      //CLOCK_07_35
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_08,  ZIRI_CHAR_GAME_NEEDLE_SHORT_30  },      //CLOCK_07_40
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_09,  ZIRI_CHAR_GAME_NEEDLE_SHORT_31  },      //CLOCK_07_45
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_10,  ZIRI_CHAR_GAME_NEEDLE_SHORT_31  },      //CLOCK_07_50
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_11,  ZIRI_CHAR_GAME_NEEDLE_SHORT_31  },      //CLOCK_07_55
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_00,  ZIRI_CHAR_GAME_NEEDLE_SHORT_32  },      //CLOCK_08_00
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_01,  ZIRI_CHAR_GAME_NEEDLE_SHORT_32  },      //CLOCK_08_05
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_02,  ZIRI_CHAR_GAME_NEEDLE_SHORT_32  },      //CLOCK_08_10
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_03,  ZIRI_CHAR_GAME_NEEDLE_SHORT_33  },      //CLOCK_08_15
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_04,  ZIRI_CHAR_GAME_NEEDLE_SHORT_33  },      //CLOCK_08_20
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_05,  ZIRI_CHAR_GAME_NEEDLE_SHORT_33  },      //CLOCK_08_25
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_06,  ZIRI_CHAR_GAME_NEEDLE_SHORT_34  },      //CLOCK_08_30
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_07,  ZIRI_CHAR_GAME_NEEDLE_SHORT_34  },      //CLOCK_08_35
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_08,  ZIRI_CHAR_GAME_NEEDLE_SHORT_34  },      //CLOCK_08_40
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_09,  ZIRI_CHAR_GAME_NEEDLE_SHORT_35  },      //CLOCK_08_45
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_10,  ZIRI_CHAR_GAME_NEEDLE_SHORT_35  },      //CLOCK_08_50
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_11,  ZIRI_CHAR_GAME_NEEDLE_SHORT_35  },      //CLOCK_08_55
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_00,  ZIRI_CHAR_GAME_NEEDLE_SHORT_36  },      //CLOCK_09_00
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_01,  ZIRI_CHAR_GAME_NEEDLE_SHORT_36  },      //CLOCK_09_05
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_02,  ZIRI_CHAR_GAME_NEEDLE_SHORT_36  },      //CLOCK_09_10
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_03,  ZIRI_CHAR_GAME_NEEDLE_SHORT_37  },      //CLOCK_09_15
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_04,  ZIRI_CHAR_GAME_NEEDLE_SHORT_37  },      //CLOCK_09_20
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_05,  ZIRI_CHAR_GAME_NEEDLE_SHORT_37  },      //CLOCK_09_25
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_06,  ZIRI_CHAR_GAME_NEEDLE_SHORT_38  },      //CLOCK_09_30
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_07,  ZIRI_CHAR_GAME_NEEDLE_SHORT_38  },      //CLOCK_09_35
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_08,  ZIRI_CHAR_GAME_NEEDLE_SHORT_38  },      //CLOCK_09_40
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_09,  ZIRI_CHAR_GAME_NEEDLE_SHORT_39  },      //CLOCK_09_45
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_10,  ZIRI_CHAR_GAME_NEEDLE_SHORT_39  },      //CLOCK_09_50
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_11,  ZIRI_CHAR_GAME_NEEDLE_SHORT_39  },      //CLOCK_09_55
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_00,  ZIRI_CHAR_GAME_NEEDLE_SHORT_40  },      //CLOCK_10_00
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_01,  ZIRI_CHAR_GAME_NEEDLE_SHORT_40  },      //CLOCK_10_05
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_02,  ZIRI_CHAR_GAME_NEEDLE_SHORT_40  },      //CLOCK_10_10
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_03,  ZIRI_CHAR_GAME_NEEDLE_SHORT_41  },      //CLOCK_10_15
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_04,  ZIRI_CHAR_GAME_NEEDLE_SHORT_41  },      //CLOCK_10_20
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_05,  ZIRI_CHAR_GAME_NEEDLE_SHORT_41  },      //CLOCK_10_25
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_06,  ZIRI_CHAR_GAME_NEEDLE_SHORT_42  },      //CLOCK_10_30
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_07,  ZIRI_CHAR_GAME_NEEDLE_SHORT_42  },      //CLOCK_10_35
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_08,  ZIRI_CHAR_GAME_NEEDLE_SHORT_42  },      //CLOCK_10_40
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_09,  ZIRI_CHAR_GAME_NEEDLE_SHORT_43  },      //CLOCK_10_45
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_10,  ZIRI_CHAR_GAME_NEEDLE_SHORT_43  },      //CLOCK_10_50
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_11,  ZIRI_CHAR_GAME_NEEDLE_SHORT_43  },      //CLOCK_10_55
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_00,  ZIRI_CHAR_GAME_NEEDLE_SHORT_44  },      //CLOCK_11_00
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_01,  ZIRI_CHAR_GAME_NEEDLE_SHORT_44  },      //CLOCK_11_05
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_02,  ZIRI_CHAR_GAME_NEEDLE_SHORT_44  },      //CLOCK_11_10
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_03,  ZIRI_CHAR_GAME_NEEDLE_SHORT_45  },      //CLOCK_11_15
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_04,  ZIRI_CHAR_GAME_NEEDLE_SHORT_45  },      //CLOCK_11_20
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_05,  ZIRI_CHAR_GAME_NEEDLE_SHORT_45  },      //CLOCK_11_25
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_06,  ZIRI_CHAR_GAME_NEEDLE_SHORT_46  },      //CLOCK_11_30
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_07,  ZIRI_CHAR_GAME_NEEDLE_SHORT_46  },      //CLOCK_11_35
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_08,  ZIRI_CHAR_GAME_NEEDLE_SHORT_46  },      //CLOCK_11_40
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_09,  ZIRI_CHAR_GAME_NEEDLE_SHORT_47  },      //CLOCK_11_45
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_10,  ZIRI_CHAR_GAME_NEEDLE_SHORT_47  },      //CLOCK_11_50
        {   ZIRI_CHAR_GAME_NEEDLE_LONG_11,  ZIRI_CHAR_GAME_NEEDLE_SHORT_47  },      //CLOCK_11_55
    };

    SpData.No       = ClockAngleTable[i_time].tansin;
    SpData.PosX     = i_x+25;
    SpData.PosY     = i_y+27;
    SpData.PosZ     = i_z-2;
    SpData.ScaleX   = SCALE10;
    SpData.ScaleY   = SCALE10;
    SpData.Rotate   = ROTATE000;
    SpData.Reverse  = NOREVERS;
    DrawSprite( &SpData );

    SpData.No       = ClockAngleTable[i_time].tyousin;
    SpData.PosX     = i_x+21;
    SpData.PosY     = i_y+23;
    SpData.PosZ     = i_z-1;
    SpData.ScaleX   = SCALE10;
    SpData.ScaleY   = SCALE10;
    SpData.Rotate   = ROTATE000;
    SpData.Reverse  = NOREVERS;
    DrawSprite( &SpData );
}


//-----------------------------------------------------------------------------
//  関数名  :DrawClockHand
//
//  work    :時計の針描画
//  in      :int i_time
//          :int i_x
//          :int i_y
//          :int i_z
//  out     :なし
//  note    :長針は５分単位
//          :短針は２分３０秒
//-----------------------------------------------------------------------------
static void DrawClockHand(int i_time,int i_x, int i_y, int i_z)
{
    //----長針(分)
    static ZIRI_SPRITE_DATA LongHandSpriteTable[]=
    {
        {   ZIRI_CHAR_GAME_LONG_HAND_00,        30, 24  },
        {   ZIRI_CHAR_GAME_LONG_HAND_05,        36, 24  },
        {   ZIRI_CHAR_GAME_LONG_HAND_10,        37, 24  },
        {   ZIRI_CHAR_GAME_LONG_HAND_15,        37, 30  },
        {   ZIRI_CHAR_GAME_LONG_HAND_20,        37, 36  },
        {   ZIRI_CHAR_GAME_LONG_HAND_25,        36, 36  },
        {   ZIRI_CHAR_GAME_LONG_HAND_30,        30, 37  },
        {   ZIRI_CHAR_GAME_LONG_HAND_35,        24, 36  },
        {   ZIRI_CHAR_GAME_LONG_HAND_40,        23, 36  },
        {   ZIRI_CHAR_GAME_LONG_HAND_45,        23, 30  },
        {   ZIRI_CHAR_GAME_LONG_HAND_50,        23, 24  },
        {   ZIRI_CHAR_GAME_LONG_HAND_55,        24, 24  },
    };

    //----短針(時)
    static ZIRI_SPRITE_DATA ShortHandSpriteTable[]={
        {   ZIRI_CHAR_GAME_SHORT_HAND_00_24,    33, 29  },
        {   ZIRI_CHAR_GAME_SHORT_HAND_01_24,    35, 29  },
        {   ZIRI_CHAR_GAME_SHORT_HAND_02_24,    36, 30  },
        {   ZIRI_CHAR_GAME_SHORT_HAND_03_24,    37, 30  },
        {   ZIRI_CHAR_GAME_SHORT_HAND_04_24,    37, 31  },
        {   ZIRI_CHAR_GAME_SHORT_HAND_05_24,    38, 31  },
        {   ZIRI_CHAR_GAME_SHORT_HAND_06_24,    38, 33  },
        {   ZIRI_CHAR_GAME_SHORT_HAND_07_24,    38, 34  },
        {   ZIRI_CHAR_GAME_SHORT_HAND_08_24,    37, 35  },
        {   ZIRI_CHAR_GAME_SHORT_HAND_09_24,    37, 36  },
        {   ZIRI_CHAR_GAME_SHORT_HAND_10_24,    36, 37  },
        {   ZIRI_CHAR_GAME_SHORT_HAND_11_24,    35, 38  },
        {   ZIRI_CHAR_GAME_SHORT_HAND_12_24,    33, 38  },
        {   ZIRI_CHAR_GAME_SHORT_HAND_13_24,    30, 38  },
        {   ZIRI_CHAR_GAME_SHORT_HAND_14_24,    30, 37  },
        {   ZIRI_CHAR_GAME_SHORT_HAND_15_24,    29, 36  },
        {   ZIRI_CHAR_GAME_SHORT_HAND_16_24,    29, 35  },
        {   ZIRI_CHAR_GAME_SHORT_HAND_17_24,    28, 34  },
        {   ZIRI_CHAR_GAME_SHORT_HAND_18_24,    28, 33  },
        {   ZIRI_CHAR_GAME_SHORT_HAND_19_24,    28, 31  },
        {   ZIRI_CHAR_GAME_SHORT_HAND_20_24,    29, 31  },
        {   ZIRI_CHAR_GAME_SHORT_HAND_21_24,    29, 30  },
        {   ZIRI_CHAR_GAME_SHORT_HAND_22_24,    30, 30  },
        {   ZIRI_CHAR_GAME_SHORT_HAND_23_24,    30, 29  },
    };

    static CLOCK_HAND ClockHandTable[]=
    {
        //短針  長針
        {   0,  0   },          //  CLOCK_00_00
        {   0,  1   },          //  CLOCK_00_05
        {   0,  2   },          //  CLOCK_00_10
        {   0,  3   },          //  CLOCK_00_15
        {   0,  4   },          //  CLOCK_00_20
        {   0,  5   },          //  CLOCK_00_25
        {   1,  6   },          //  CLOCK_00_30
        {   1,  7   },          //  CLOCK_00_35
        {   1,  8   },          //  CLOCK_00_40
        {   1,  9   },          //  CLOCK_00_45
        {   1,  10  },          //  CLOCK_00_50
        {   1,  11  },          //  CLOCK_00_55
        {   2,  0   },          //  CLOCK_01_00
        {   2,  1   },          //  CLOCK_01_05
        {   2,  2   },          //  CLOCK_01_10
        {   2,  3   },          //  CLOCK_01_15
        {   2,  4   },          //  CLOCK_01_20
        {   2,  5   },          //  CLOCK_01_25
        {   3,  6   },          //  CLOCK_01_30
        {   3,  7   },          //  CLOCK_01_35
        {   3,  8   },          //  CLOCK_01_40
        {   3,  9   },          //  CLOCK_01_45
        {   3,  10  },          //  CLOCK_01_50
        {   3,  11  },          //  CLOCK_01_55
        {   4,  0   },          //  CLOCK_02_00
        {   4,  1   },          //  CLOCK_02_05
        {   4,  2   },          //  CLOCK_02_10
        {   4,  3   },          //  CLOCK_02_15
        {   4,  4   },          //  CLOCK_02_20
        {   4,  5   },          //  CLOCK_02_25
        {   5,  6   },          //  CLOCK_02_30
        {   5,  7   },          //  CLOCK_02_35
        {   5,  8   },          //  CLOCK_02_40
        {   5,  9   },          //  CLOCK_02_45
        {   5,  10  },          //  CLOCK_02_50
        {   5,  11  },          //  CLOCK_02_55
        {   6,  0   },          //  CLOCK_03_00
        {   6,  1   },          //  CLOCK_03_05
        {   6,  2   },          //  CLOCK_03_10
        {   6,  3   },          //  CLOCK_03_15
        {   6,  4   },          //  CLOCK_03_20
        {   6,  5   },          //  CLOCK_03_25
        {   7,  6   },          //  CLOCK_03_30
        {   7,  7   },          //  CLOCK_03_35
        {   7,  8   },          //  CLOCK_03_40
        {   7,  9   },          //  CLOCK_03_45
        {   7,  10  },          //  CLOCK_03_50
        {   7,  11  },          //  CLOCK_03_55
        {   8,  0   },          //  CLOCK_04_00
        {   8,  1   },          //  CLOCK_04_05
        {   8,  2   },          //  CLOCK_04_10
        {   8,  3   },          //  CLOCK_04_15
        {   8,  4   },          //  CLOCK_04_20
        {   8,  5   },          //  CLOCK_04_25
        {   9,  6   },          //  CLOCK_04_30
        {   9,  7   },          //  CLOCK_04_35
        {   9,  8   },          //  CLOCK_04_40
        {   9,  9   },          //  CLOCK_04_45
        {   9,  10  },          //  CLOCK_04_50
        {   9,  11  },          //  CLOCK_04_55
        {   10, 0   },          //  CLOCK_05_00
        {   10, 1   },          //  CLOCK_05_05
        {   10, 2   },          //  CLOCK_05_10
        {   10, 3   },          //  CLOCK_05_15
        {   10, 4   },          //  CLOCK_05_20
        {   10, 5   },          //  CLOCK_05_25
        {   11, 6   },          //  CLOCK_05_30
        {   11, 7   },          //  CLOCK_05_35
        {   11, 8   },          //  CLOCK_05_40
        {   11, 9   },          //  CLOCK_05_45
        {   11, 10  },          //  CLOCK_05_50
        {   11, 11  },          //  CLOCK_05_55
        {   12, 0   },          //  CLOCK_06_00
        {   12, 1   },          //  CLOCK_06_05
        {   12, 2   },          //  CLOCK_06_10
        {   12, 3   },          //  CLOCK_06_15
        {   12, 4   },          //  CLOCK_06_20
        {   12, 5   },          //  CLOCK_06_25
        {   13, 6   },          //  CLOCK_06_30
        {   13, 7   },          //  CLOCK_06_35
        {   13, 8   },          //  CLOCK_06_40
        {   13, 9   },          //  CLOCK_06_45
        {   13, 10  },          //  CLOCK_06_50
        {   13, 11  },          //  CLOCK_06_55
        {   14, 0   },          //  CLOCK_07_00
        {   14, 1   },          //  CLOCK_07_05
        {   14, 2   },          //  CLOCK_07_10
        {   14, 3   },          //  CLOCK_07_15
        {   14, 4   },          //  CLOCK_07_20
        {   14, 5   },          //  CLOCK_07_25
        {   15, 6   },          //  CLOCK_07_30
        {   15, 7   },          //  CLOCK_07_35
        {   15, 8   },          //  CLOCK_07_40
        {   15, 9   },          //  CLOCK_07_45
        {   15, 10  },          //  CLOCK_07_50
        {   15, 11  },          //  CLOCK_07_55
        {   16, 0   },          //  CLOCK_08_00
        {   16, 1   },          //  CLOCK_08_05
        {   16, 2   },          //  CLOCK_08_10
        {   16, 3   },          //  CLOCK_08_15
        {   16, 4   },          //  CLOCK_08_20
        {   16, 5   },          //  CLOCK_08_25
        {   17, 6   },          //  CLOCK_08_30
        {   17, 7   },          //  CLOCK_08_35
        {   17, 8   },          //  CLOCK_08_40
        {   17, 9   },          //  CLOCK_08_45
        {   17, 10  },          //  CLOCK_08_50
        {   17, 11  },          //  CLOCK_08_55
        {   18, 0   },          //  CLOCK_09_00
        {   18, 1   },          //  CLOCK_09_05
        {   18, 2   },          //  CLOCK_09_10
        {   18, 3   },          //  CLOCK_09_15
        {   18, 4   },          //  CLOCK_09_20
        {   18, 5   },          //  CLOCK_09_25
        {   19, 6   },          //  CLOCK_09_30
        {   19, 7   },          //  CLOCK_09_35
        {   19, 8   },          //  CLOCK_09_40
        {   19, 9   },          //  CLOCK_09_45
        {   19, 10  },          //  CLOCK_09_50
        {   19, 11  },          //  CLOCK_09_55
        {   20, 0   },          //  CLOCK_10_00
        {   20, 1   },          //  CLOCK_10_05
        {   20, 2   },          //  CLOCK_10_10
        {   20, 3   },          //  CLOCK_10_15
        {   20, 4   },          //  CLOCK_10_20
        {   20, 5   },          //  CLOCK_10_25
        {   21, 6   },          //  CLOCK_10_30
        {   21, 7   },          //  CLOCK_10_35
        {   21, 8   },          //  CLOCK_10_40
        {   21, 9   },          //  CLOCK_10_45
        {   21, 10  },          //  CLOCK_10_50
        {   21, 11  },          //  CLOCK_10_55
        {   22, 0   },          //  CLOCK_11_11
        {   22, 1   },          //  CLOCK_11_15
        {   22, 2   },          //  CLOCK_11_11
        {   22, 3   },          //  CLOCK_11_15
        {   22, 4   },          //  CLOCK_11_21
        {   22, 5   },          //  CLOCK_11_25
        {   23, 6   },          //  CLOCK_11_31
        {   23, 7   },          //  CLOCK_11_35
        {   23, 8   },          //  CLOCK_11_41
        {   23, 9   },          //  CLOCK_11_45
        {   23, 10  },          //  CLOCK_11_51
        {   23, 11  },          //  CLOCK_11_55
    };


    int LongNo,ShortNo;
    SPRITE_DATA SpData;


    
    LongNo = ShortNo = 0;

    //----長針
    SpData.No       = LongHandSpriteTable[ClockHandTable[i_time].LongNo].No;
    SpData.PosX     = i_x + LongHandSpriteTable[ClockHandTable[i_time].LongNo].Ofx;
    SpData.PosY     = i_y + LongHandSpriteTable[ClockHandTable[i_time].LongNo].Ofy;
    SpData.PosZ     = i_z - 1;
    SpData.ScaleX   = SCALE10;
    SpData.ScaleY   = SCALE10;
    SpData.Rotate   = ROTATE000;
    SpData.Reverse  = NOREVERS;
    DrawSprite( &SpData );

    //----短針
    SpData.No       = ShortHandSpriteTable[ClockHandTable[i_time].ShortNo].No;
    SpData.PosX     = i_x + ShortHandSpriteTable[ClockHandTable[i_time].ShortNo].Ofx;
    SpData.PosY     = i_y + ShortHandSpriteTable[ClockHandTable[i_time].ShortNo].Ofy;
    SpData.PosZ     = i_z;
    SpData.ScaleX   = SCALE10;
    SpData.ScaleY   = SCALE10;
    SpData.Rotate   = ROTATE000;
    SpData.Reverse  = NOREVERS;
    DrawSprite( &SpData );

}


//-----------------------------------------------------------------------------
//  関数名  :DrawClockTime
//
//  work    :時計描画
//  in      :int i_time
//  out     :なし
//  note    :なし
//-----------------------------------------------------------------------------
static void DrawClockTime(int i_time)
{
    static HOUR_DATA ClockTimeTable[]=
    {
        //  時  分
        {   12,  0  },          //  CLOCK_00_00     000
        {   12,  5  },          //  CLOCK_00_05     001
        {   12, 10  },          //  CLOCK_00_10     002
        {   12, 15  },          //  CLOCK_00_15     003
        {   12, 20  },          //  CLOCK_00_20     004
        {   12, 25  },          //  CLOCK_00_25     005
        {   12, 30  },          //  CLOCK_00_30     006
        {   12, 35  },          //  CLOCK_00_35     007
        {   12, 40  },          //  CLOCK_00_40     008
        {   12, 45  },          //  CLOCK_00_45     009
        {   12, 50  },          //  CLOCK_00_50     010
        {   12, 55  },          //  CLOCK_00_55     011
        {   1,   0  },          //  CLOCK_01_00     012
        {   1,   5  },          //  CLOCK_01_05     013
        {   1,  10  },          //  CLOCK_01_10     014
        {   1,  15  },          //  CLOCK_01_15     015
        {   1,  20  },          //  CLOCK_01_20     016
        {   1,  25  },          //  CLOCK_01_25     017
        {   1,  30  },          //  CLOCK_01_30     018
        {   1,  35  },          //  CLOCK_01_35     019
        {   1,  40  },          //  CLOCK_01_40     020
        {   1,  45  },          //  CLOCK_01_45     021
        {   1,  50  },          //  CLOCK_01_50     022
        {   1,  55  },          //  CLOCK_01_55     023
        {   2,   0  },          //  CLOCK_02_00     024
        {   2,   5  },          //  CLOCK_02_05     025
        {   2,  10  },          //  CLOCK_02_10     026
        {   2,  15  },          //  CLOCK_02_15     027
        {   2,  20  },          //  CLOCK_02_20     028
        {   2,  25  },          //  CLOCK_02_25     029
        {   2,  30  },          //  CLOCK_02_30     030
        {   2,  35  },          //  CLOCK_02_35     031
        {   2,  40  },          //  CLOCK_02_40     032
        {   2,  45  },          //  CLOCK_02_45     033
        {   2,  50  },          //  CLOCK_02_50     034
        {   2,  55  },          //  CLOCK_02_55     035
        {   3,   0  },          //  CLOCK_03_00     036
        {   3,   5  },          //  CLOCK_03_05     037
        {   3,  10  },          //  CLOCK_03_10     038
        {   3,  15  },          //  CLOCK_03_15     039
        {   3,  20  },          //  CLOCK_03_20     040
        {   3,  25  },          //  CLOCK_03_25     041
        {   3,  30  },          //  CLOCK_03_30     042
        {   3,  35  },          //  CLOCK_03_35     043
        {   3,  40  },          //  CLOCK_03_40     044
        {   3,  45  },          //  CLOCK_03_45     045
        {   3,  50  },          //  CLOCK_03_50     046
        {   3,  55  },          //  CLOCK_03_55     047
        {   4,   0  },          //  CLOCK_04_00     048
        {   4,   5  },          //  CLOCK_04_05     049
        {   4,  10  },          //  CLOCK_04_10     050
        {   4,  15  },          //  CLOCK_04_15     051
        {   4,  20  },          //  CLOCK_04_20     052
        {   4,  25  },          //  CLOCK_04_25     053
        {   4,  30  },          //  CLOCK_04_30     054
        {   4,  35  },          //  CLOCK_04_35     055
        {   4,  40  },          //  CLOCK_04_40     056
        {   4,  45  },          //  CLOCK_04_45     057
        {   4,  50  },          //  CLOCK_04_50     058
        {   4,  55  },          //  CLOCK_04_55     059
        {   5,   0  },          //  CLOCK_05_00     060
        {   5,   5  },          //  CLOCK_05_05     061
        {   5,  10  },          //  CLOCK_05_10     062
        {   5,  15  },          //  CLOCK_05_15     063
        {   5,  20  },          //  CLOCK_05_20     064
        {   5,  25  },          //  CLOCK_05_25     065
        {   5,  30  },          //  CLOCK_05_30     066
        {   5,  35  },          //  CLOCK_05_35     067
        {   5,  40  },          //  CLOCK_05_40     068
        {   5,  45  },          //  CLOCK_05_45     069
        {   5,  50  },          //  CLOCK_05_50     070
        {   5,  55  },          //  CLOCK_05_55     071
        {   6,   0  },          //  CLOCK_06_00     072
        {   6,   5  },          //  CLOCK_06_05     073
        {   6,  10  },          //  CLOCK_06_10     074
        {   6,  15  },          //  CLOCK_06_15     075
        {   6,  20  },          //  CLOCK_06_20     076
        {   6,  25  },          //  CLOCK_06_25     077
        {   6,  30  },          //  CLOCK_06_30     078
        {   6,  35  },          //  CLOCK_06_35     079
        {   6,  40  },          //  CLOCK_06_40     080
        {   6,  45  },          //  CLOCK_06_45     081
        {   6,  50  },          //  CLOCK_06_50     082
        {   6,  55  },          //  CLOCK_06_55     083
        {   7,   0  },          //  CLOCK_07_00     084
        {   7,   5  },          //  CLOCK_07_05     085
        {   7,  10  },          //  CLOCK_07_10     086
        {   7,  15  },          //  CLOCK_07_15     087
        {   7,  20  },          //  CLOCK_07_20     088
        {   7,  25  },          //  CLOCK_07_25     089
        {   7,  30  },          //  CLOCK_07_30     090
        {   7,  35  },          //  CLOCK_07_35     091
        {   7,  40  },          //  CLOCK_07_40     092
        {   7,  45  },          //  CLOCK_07_45     093
        {   7,  50  },          //  CLOCK_07_50     094
        {   7,  55  },          //  CLOCK_07_55     095
        {   8,   0  },          //  CLOCK_08_00     096
        {   8,   5  },          //  CLOCK_08_05     097
        {   8,  10  },          //  CLOCK_08_10     098
        {   8,  15  },          //  CLOCK_08_15     099
        {   8,  20  },          //  CLOCK_08_20     100
        {   8,  25  },          //  CLOCK_08_25     101
        {   8,  30  },          //  CLOCK_08_30     102
        {   8,  35  },          //  CLOCK_08_35     103
        {   8,  40  },          //  CLOCK_08_40     104
        {   8,  45  },          //  CLOCK_08_45     105
        {   8,  50  },          //  CLOCK_08_50     106
        {   8,  55  },          //  CLOCK_08_55     107
        {   9,   0  },          //  CLOCK_09_00     108
        {   9,   5  },          //  CLOCK_09_05     109
        {   9,  10  },          //  CLOCK_09_10     110
        {   9,  15  },          //  CLOCK_09_15     111
        {   9,  20  },          //  CLOCK_09_20     112
        {   9,  25  },          //  CLOCK_09_25     113
        {   9,  30  },          //  CLOCK_09_30     114
        {   9,  35  },          //  CLOCK_09_35     115
        {   9,  40  },          //  CLOCK_09_40     116
        {   9,  45  },          //  CLOCK_09_45     117
        {   9,  50  },          //  CLOCK_09_50     118
        {   9,  55  },          //  CLOCK_09_55     119
        {   10,  0  },          //  CLOCK_10_00     120
        {   10,  5  },          //  CLOCK_10_05     121
        {   10, 10  },          //  CLOCK_10_10     122
        {   10, 15  },          //  CLOCK_10_15     123
        {   10, 20  },          //  CLOCK_10_20     124
        {   10, 25  },          //  CLOCK_10_25     125
        {   10, 30  },          //  CLOCK_10_30     126
        {   10, 35  },          //  CLOCK_10_35     127
        {   10, 40  },          //  CLOCK_10_40     128
        {   10, 45  },          //  CLOCK_10_45     129
        {   10, 50  },          //  CLOCK_10_50     130
        {   10, 55  },          //  CLOCK_10_55     131
        {   11,  0  },          //  CLOCK_11_11     132
        {   11,  5  },          //  CLOCK_11_15     133
        {   11, 10  },          //  CLOCK_11_11     134
        {   11, 15  },          //  CLOCK_11_15     135
        {   11, 20  },          //  CLOCK_11_21     136
        {   11, 25  },          //  CLOCK_11_25     137
        {   11, 30  },          //  CLOCK_11_31     138
        {   11, 35  },          //  CLOCK_11_35     139
        {   11, 40  },          //  CLOCK_11_41     140
        {   11, 45  },          //  CLOCK_11_45     141
        {   11, 50  },          //  CLOCK_11_51     142
        {   11, 55  },          //  CLOCK_11_55     143
    };

    static POS2D NumPosTable[]={
        {134,85},
        {146,85},
        {166,85},
        {178,85},
    };

    int result[4];
    int i;
    SPRITE_DATA SpData;


    result[0]   = ClockTimeTable[i_time].Hour / 10;
    result[1]   = ClockTimeTable[i_time].Hour - (result[0]*10);
    result[2]   = ClockTimeTable[i_time].Min  / 10;
    result[3]   = ClockTimeTable[i_time].Min  - (result[2]*10);

    //----時間
    for(i=0;i<4;i++){
        if( (result[i] == 0) && (i==0) ) continue;
        
        SpData.No       = ClockNumSpriteTable[result[i]];
        SpData.PosX     = NumPosTable[i].x;
        SpData.PosY     = NumPosTable[i].y;
        SpData.PosZ     = PRIORITY_CLOCK_NUM;
        SpData.ScaleX   = SCALE10;
        SpData.ScaleY   = SCALE10;
        SpData.Rotate   = ROTATE000;
        SpData.Reverse  = NOREVERS;
        DrawSprite( &SpData );
    }

    //----コロン
    SpData.No       = ZIRI_CHAR_GAME_CLOCK_NUM_CORON;
    SpData.PosX     = 156;
    SpData.PosY     = 85;
    SpData.PosZ     = PRIORITY_CLOCK_NUM;
    SpData.ScaleX   = SCALE10;
    SpData.ScaleY   = SCALE10;
    SpData.Rotate   = ROTATE000;
    SpData.Reverse  = NOREVERS;
    DrawSprite( &SpData );

}




//-----------------------------------------------------------------------------
//  関数名  :GetQuestionFirst
//
//  work    :初期化時の問題取得
//  in      :int i_level
//          :int i_index
//          :int i_rand
//  out     :時間
//  note    :なし
//-----------------------------------------------------------------------------
static int GetQuestionFirst(int i_level,int i_line,int i_index)
{
    return FirstQuestionData[i_level][i_line][i_index];
}




//-----------------------------------------------------------------------------
//  関数名  :GetQuestion
//
//  work    :問題取得
//  in      :int i_level
//  out     :時間
//  note    :なし
//-----------------------------------------------------------------------------
static int GetQuestion(int i_level)
{
    return QuestionData[i_level].Data[ rand() % MAX_SELECT_QUESTION_NUM ];
}


//-----------------------------------------------------------------------------
//  関数名  :CheckKeyDir
//
//  work    :キー方向を取得
//  in      :
//  out     :TRUE   入力あり
//          :FALSE  入力なし
//  note    :なし
//-----------------------------------------------------------------------------
static int CheckKeyDir(int *ip_dir)
{
    if(JstPad & PADLup){
        *ip_dir=DIR_UP;
        return TRUE;
    }else
    if(JstPad & PADLdown){
        *ip_dir=DIR_DOWN;
        return TRUE;
    }
    else
    if(JstPad & PADLleft){
        *ip_dir=DIR_LEFT;
        return TRUE;
    }
    else
    if(JstPad & PADLright){
        *ip_dir=DIR_RIGHT;
        return TRUE;
    }else{
        *ip_dir=DIR_NOTHING;
        return FALSE;
    }
}


//-----------------------------------------------------------------------------
//  関数名  :CheckAnswer
//
//  work    :答えチェック
//  in      :int i_pos
//          :int* ip_index
//  out     :ANSWER_OK      正解
//          :ANSWER_NG      不正解
//          :ANSWER_NONE    存在しない
//  note    :なし
//-----------------------------------------------------------------------------
static int CheckAnswer(int i_pos,int* ip_index)
{
    int i;

    for(i=0;i<MAX_CLOCKMAN_NUM;i++)
    {
        if( ZGameMgr.Player.CursorPos == ZGameMgr.ClockMan[i].Pos )
        {//----位置が同じ時判定する
            if(ZGameMgr.ClockMan[i].Character.Status==CLOCKMAN_SELECT)
            {//----選択中の場合のみ返す
                *ip_index = i;
                if( ZGameMgr.ClockMan[i].Time ==  ZGameMgr.Question.Time[ ZGameMgr.Question.Index ] )
                {//----今の質問とカーソル位置の時計マンの時刻を比較
                    return ANSWER_OK;
                }else{
                    return ANSWER_NG;
                }
            }
        }
    }

    *ip_index = -1;
    return ANSWER_NONE;
}


//-----------------------------------------------------------------------------
//  関数名  :GetQuestionIndex
//
//  work    :質問インデックス取得
//  in      :int *ip_index
//  out     :TRUE
//          :FALSE
//  note    :なし
//-----------------------------------------------------------------------------
static int GetQuestionIndex(int *ip_index)
{
    int tindex[MAX_CLOCKMAN_NUM],i,count;

    count = 0;
    for(i=0;i<MAX_CLOCKMAN_NUM;i++)
    {
        if( (ZGameMgr.Question.ExistFlag[i] != 0) && (ZGameMgr.Question.GetDataFlag[i] != 0) )
        {//----有効な答えのインデックスを取得
            tindex[count] = i;
            ++count;
        }
    }

    //----有効な答えがない
    if(count==0)
    {
        *ip_index = -1;
        return FALSE;
    }else
    {
        *ip_index = tindex[rand() % count];
        return TRUE;
    }
}




//-----------------------------------------------------------------------------
//  関数名  :ClearEventClockMan
//
//  work    :クリアイベント時計マン
//  in      :なし
//  out     :なし
//  note    :なし
//-----------------------------------------------------------------------------
static void ClearEventClockMan(void)
{
    static ZIRI_SPRITE_DATA ClearClockManSpriteTable[]=
    {
        {   ZIRI_CHAR_EVENT_CLOCKMAM_LEFT_ARM_00,   58,     64  },
        {   ZIRI_CHAR_EVENT_CLOCKMAM_RIGHT_ARM_00,  212,    67  },
        {   ZIRI_CHAR_EVENT_CLOCKMAM_LEFT_ARM_01,   78,     48  },
        {   ZIRI_CHAR_EVENT_CLOCKMAM_RIGHT_ARM_01,  202,    48  },
    };
    SPRITE_DATA SpData;

    if(!ZGameMgr.Event.EndFlag){
        if(++ZGameMgr.Event.Clear.ClockManAnmWaitTimer >= EVENT_ANM_WAIT_TIME){
            ZGameMgr.Event.Clear.ClockManAnmWaitTimer = 0;
            ZGameMgr.Event.Clear.ClockManAnmIndex ^= 1;
        }
    }

    //----左腕
    SpData.No       = ClearClockManSpriteTable[ZGameMgr.Event.Clear.ClockManAnmIndex*2].No;     //インデックス番号
    SpData.PosX     = ClearClockManSpriteTable[ZGameMgr.Event.Clear.ClockManAnmIndex*2].Ofx;    //X位置
    SpData.PosY     = ClearClockManSpriteTable[ZGameMgr.Event.Clear.ClockManAnmIndex*2].Ofy;    //Y位置
    SpData.PosZ     = PRIORITY_EVENT_CLOCKMAN;          //優先順位
    SpData.ScaleX   = SCALE10;                          //スケールX
    SpData.ScaleY   = SCALE10;                          //スケールY
    SpData.Rotate   = ROTATE000;                        //回転角
    SpData.Reverse  = NOREVERS;                         //反転コード
    DrawSprite( &SpData );                              //スプライト描画

    //----右腕
    SpData.No       = ClearClockManSpriteTable[ZGameMgr.Event.Clear.ClockManAnmIndex*2+1].No;;  //インデックス番号
    SpData.PosX     = ClearClockManSpriteTable[ZGameMgr.Event.Clear.ClockManAnmIndex*2+1].Ofx;  //X位置
    SpData.PosY     = ClearClockManSpriteTable[ZGameMgr.Event.Clear.ClockManAnmIndex*2+1].Ofy;  //Y位置
    SpData.PosZ     = PRIORITY_EVENT_CLOCKMAN;          //優先順位
    SpData.ScaleX   = SCALE10;                          //スケールX
    SpData.ScaleY   = SCALE10;                          //スケールY
    SpData.Rotate   = ROTATE000;                        //回転角
    SpData.Reverse  = NOREVERS;                         //反転コード
    DrawSprite( &SpData );                              //スプライト描画

    //----顔
    SpData.No       = ZIRI_CHAR_EVENT_CLOCKMAM_FADCE;   //インデックス番号
    SpData.PosX     = 132;                              //X位置
    SpData.PosY     = 41;                               //Y位置
    SpData.PosZ     = PRIORITY_EVENT_CLOCKMAN;          //優先順位
    SpData.ScaleX   = SCALE10;                          //スケールX
    SpData.ScaleY   = SCALE10;                          //スケールY
    SpData.Rotate   = ROTATE000;                        //回転角
    SpData.Reverse  = NOREVERS;                         //反転コード
    DrawSprite( &SpData );                              //スプライト描画
    
    //----ボディ
    SpData.No       = ZIRI_CHAR_EVENT_CLOCKMAM_BODY_00; //インデックス番号
    SpData.PosX     = 98;                               //X位置
    SpData.PosY     = 27;                               //Y位置
    SpData.PosZ     = PRIORITY_EVENT_CLOCKMAN;          //優先順位
    SpData.ScaleX   = SCALE10;                          //スケールX
    SpData.ScaleY   = SCALE10;                          //スケールY
    SpData.Rotate   = ROTATE000;                        //回転角
    SpData.Reverse  = NOREVERS;                         //反転コード
    DrawSprite( &SpData );                              //スプライト描画

    //----やったパネル
    SpData.No       = ZIRI_CHAR_EVENT_PLATE_YATA;       //インデックス番号
    SpData.PosX     = 109;                              //X位置
    SpData.PosY     = 90;                               //Y位置
    SpData.PosZ     = PRIORITY_EVENT_CLOCKMAN-1;        //優先順位
    SpData.ScaleX   = SCALE10;                          //スケールX
    SpData.ScaleY   = SCALE10;                          //スケールY
    SpData.Rotate   = ROTATE000;                        //回転角
    SpData.Reverse  = NOREVERS;                         //反転コード
    DrawSprite( &SpData );                              //スプライト描画
}


//-----------------------------------------------------------------------------
//  関数名  :ClearEventBg
//
//  work    :クリアイベント背景
//  in      :なし
//  out     :なし
//  note    :なし
//-----------------------------------------------------------------------------
static void ClearEventBg(void)
{
    static int ClearBgSpriteTable[]=
    {
        ZIRI_CHAR_EVENT_BG_FLUSH_00,ZIRI_CHAR_EVENT_BG_FLUSH_02,
        ZIRI_CHAR_EVENT_BG_FLUSH_01,ZIRI_CHAR_EVENT_BG_FLUSH_03,
    };

    SPRITE_DATA SpData;

    
    if(!ZGameMgr.Event.EndFlag){
        if(++ZGameMgr.Event.Clear.BgAnmWaitTimer >= EVENT_ANM_WAIT_TIME){
            ZGameMgr.Event.Clear.BgAnmWaitTimer = 0;
            ZGameMgr.Event.Clear.BgAnmIndex ^= 1;
        }
    }


    SpData.No       = ClearBgSpriteTable[ZGameMgr.Event.Clear.BgAnmIndex*2];
    SpData.PosX     = 0;
    SpData.PosY     = 0;
    SpData.PosZ     = PRIORITY_BG;
    SpData.ScaleX   = SCALE10;
    SpData.ScaleY   = SCALE10;
    SpData.Rotate   = ROTATE000;
    SpData.Reverse  = NOREVERS;
    DrawSprite( &SpData );

    SpData.No       = ClearBgSpriteTable[ZGameMgr.Event.Clear.BgAnmIndex*2 + 1];
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
//  関数名  :FalseEventClockMan
//
//  work    :失敗イベント時計マン
//  in      :なし
//  out     :なし
//  note    :なし
//-----------------------------------------------------------------------------
static void FalseEventClockMan(void)
{
    static ZIRI_SPRITE_DATA FalseEventClockManSpriteTable[]={
        {   ZIRI_CHAR_EVENT_CLOCMAN_BREAK_00,   83, 45  },
        {   ZIRI_CHAR_EVENT_CLOCMAN_BREAK_01,   88, 57  },
    };
    SPRITE_DATA SpData;

    switch(ZGameMgr.Event.False.Mode)
    {
        case FALSE_EVENT_MODE_BAKU:             //爆発
            if(++ZGameMgr.Event.False.Timer >= FALSE_EVENT_MODE_BAKU_TIME){
                ZGameMgr.Event.False.Timer  = 0;
                ZGameMgr.Event.False.Mode   = FALSE_EVENT_MODE_CLOCKMAN_STOP;
                
                ZGameMgr.Event.False.ClockManPosX   = FalseEventClockManSpriteTable[0].Ofx;
                ZGameMgr.Event.False.ClockManPosY   = FalseEventClockManSpriteTable[0].Ofy;
            }
            
            SpData.No       = ZIRI_CHAR_EVENT_BAKU_00;
            SpData.PosX     = 6;
            SpData.PosY     = 18;
            SpData.PosZ     = PRIORITY_EVENT_CLOCKMAN-1;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );
            
            SpData.No       = ZIRI_CHAR_EVENT_BAKU_01;
            SpData.PosX     = 256+6;
            SpData.PosY     = 18;
            SpData.PosZ     = PRIORITY_EVENT_CLOCKMAN-1;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );
            
            break;
        case FALSE_EVENT_MODE_CLOCKMAN_STOP:    //停止
            //----モードタイマー
            if(++ZGameMgr.Event.False.Timer >= FALSE_EVENT_MODE_CLOCKMAN_STOP_TIME){
                ZGameMgr.Event.False.Timer  = 0;
                ZGameMgr.Event.False.Mode   = FALSE_EVENT_MODE_CLOCKMAN_DOWN;
                
                //[♪]ひゅーーー／落下音です。
                dsPlayXa(XA_FILE_ZIRI11,1);
            }
            
            //----アニメ
            if(++ZGameMgr.Event.False.ClockManAnmWaitTimer >= EVENT_ANM_WAIT_TIME){
                ZGameMgr.Event.False.ClockManAnmWaitTimer   = 0;
                ZGameMgr.Event.False.ClockManAnmIndex       ^= 1;
            }
            
            ZGameMgr.Event.False.ClockManPosX = FalseEventClockManSpriteTable[ZGameMgr.Event.False.ClockManAnmIndex].Ofx;
            ZGameMgr.Event.False.ClockManPosY = FalseEventClockManSpriteTable[ZGameMgr.Event.False.ClockManAnmIndex].Ofy;
            
            SpData.No       = FalseEventClockManSpriteTable[ZGameMgr.Event.False.ClockManAnmIndex].No;
            SpData.PosX     = ZGameMgr.Event.False.ClockManPosX;
            SpData.PosY     = ZGameMgr.Event.False.ClockManPosY;
            SpData.PosZ     = PRIORITY_EVENT_CLOCKMAN-1;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );

            break;
        case FALSE_EVENT_MODE_CLOCKMAN_DOWN:    //落下
            ZGameMgr.Event.False.ClockManAngle += 4;
            if(ZGameMgr.Event.False.ClockManAngle >= 360){
                ZGameMgr.Event.False.ClockManAngle = 0;
            }
            
            ZGameMgr.Event.False.ClockManWorkPosX   = (double)(FalseEventClockManSpriteTable[ZGameMgr.Event.False.ClockManAnmIndex].Ofx + 60 * sin( DEG2RAD(ZGameMgr.Event.False.ClockManAngle) ));
            ZGameMgr.Event.False.ClockManPosX       = (int)ZGameMgr.Event.False.ClockManWorkPosX;
            
            ZGameMgr.Event.False.ClockManPosY+=1;
            if(ZGameMgr.Event.False.ClockManPosY>400){
                ZGameMgr.Event.False.ClockManPosY = 400;
            }
            
        //  SpData.No       = FalseEventClockManSpriteTable[0].No;
            SpData.No       = FalseEventClockManSpriteTable[ZGameMgr.Event.False.ClockManAnmIndex].No;
            SpData.PosX     = ZGameMgr.Event.False.ClockManPosX;
            SpData.PosY     = ZGameMgr.Event.False.ClockManPosY;
            SpData.PosZ     = PRIORITY_EVENT_CLOCKMAN-1;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );
            
            break;
        default:
    }
}


//-----------------------------------------------------------------------------
//  関数名  :AllClearEventClockMan
//
//  work    :オールクリア時計マン
//  in      :なし
//  out     :なし
//  note    :なし
//-----------------------------------------------------------------------------
static void AllClearEventClockMan(void)
{
    static ZIRI_SPRITE_DATA ClockManBodySpriteTable[]=
    {
        {   ZIRI_CHAR_EVENT_CLOCKMAM_BODY_00,   98, 27  },
        {   ZIRI_CHAR_EVENT_CLOKMAM_BODY_01,    98, 27  },
        {   ZIRI_CHAR_EVENT_CLOKMAM_BODY_02,    98, 27  },
    };

    static ZIRI_SPRITE_DATA ClockManArmSpriteTable[]=
    {
        {   ZIRI_CHAR_EVENT_CLOCKMAM_LEFT_ARM_00,       58,     64  },      //ノーマル手１          （画面に対して←）
        {   ZIRI_CHAR_EVENT_CLOCKMAM_RIGHT_ARM_04,      212,    33  },      //時計をもっ手いる手１  （画面に対して→）
        {   ZIRI_CHAR_EVENT_CLOCKMAM_LEFT_ARM_01,       78,     48  },      //ノーマル手２          （画面に対して←）
        {   ZIRI_CHAR_EVENT_CLOCKMAM_RIGHT_ARM_05,      202,    17  },      //時計をもっ手いる手２  （画面に対して→）
        {   ZIRI_CHAR_EVENT_CLOCKMAN_LEFT_ARM_02,       78,     48  },      //ぼかし小              （画面に対して←）
        {   ZIRI_CHAR_EVENT_CLOCKMAN_RIGHT_ARM_02,      202,    17  },      //ぼかし小              （画面に対して→）
        {   ZIRI_CHAR_EVENT_CLOCKMAN_LEFT_ARM_03,       78,     48  },      //ぼかし大              （画面に対して←）
        {   ZIRI_CHAR_EVENT_CLOCKMAN_RIGHT_ARM_03,      202,    17  },      //ぼかし大              （画面に対して→）
    };

    SPRITE_DATA SpData;
    int i;


    switch(ZGameMgr.Event.AllClear.ClockManMode)
    {
        //--------------------------------腕１
        case CLOCKMAN_MODE_00:
            if(++ZGameMgr.Event.AllClear.ClockManAnmWaitTimer > ALL_CLEAR_CLOCKMAN_MODE_00_TIME){
                ZGameMgr.Event.AllClear.ClockManAnmWaitTimer    = 0;
                ZGameMgr.Event.AllClear.ClockManMode            = CLOCKMAN_MODE_01;
                ZGameMgr.Event.AllClear.ClockManArmAnmIndex     = 2;
            }
            
            break;
        //--------------------------------腕２
        case CLOCKMAN_MODE_01:
            if(++ZGameMgr.Event.AllClear.ClockManAnmWaitTimer > ALL_CLEAR_CLOCKMAN_MODE_01_TIME){
                ZGameMgr.Event.AllClear.ClockManAnmWaitTimer    = 0;
                ZGameMgr.Event.AllClear.ClockManMode            = CLOCKMAN_MODE_02;
                ZGameMgr.Event.AllClear.ClockManClockMaskFlag   = 1;        //mask clock on
            }
            
            break;
        //--------------------------------時計12:00
        case CLOCKMAN_MODE_02:
            if(++ZGameMgr.Event.AllClear.ClockManAnmWaitTimer > ALL_CLEAR_CLOCKMAN_MODE_02_TIME){
                ZGameMgr.Event.AllClear.ClockManAnmWaitTimer    = 0;
                ZGameMgr.Event.AllClear.ClockManMode            = CLOCKMAN_MODE_03;
                
                ZGameMgr.Event.AllClear.ClockManClockMaskFlag   = 0;        //mask clock offs
                
                ZGameMgr.Event.AllClear.ClockManBodyAnmIndex    = 1;
                ZGameMgr.Event.AllClear.ClockManArmAnmIndex     = 4;
            }
            
            break;
        //--------------------------------ぼかし１
        case CLOCKMAN_MODE_03:
            if(++ZGameMgr.Event.AllClear.ClockManAnmWaitTimer > ALL_CLEAR_CLOCKMAN_MODE_03_TIME){
                ZGameMgr.Event.AllClear.ClockManAnmWaitTimer    = 0;
                ZGameMgr.Event.AllClear.ClockManMode            = CLOCKMAN_MODE_04;
                
                ZGameMgr.Event.AllClear.ClockManBodyAnmIndex    = 2;
                ZGameMgr.Event.AllClear.ClockManArmAnmIndex     = 6;
            }
            
            break;
        //--------------------------------ぼかし２
        case CLOCKMAN_MODE_04:
            
            
            
            
            break;
        default:
    }

    if(ZGameMgr.Event.AllClear.ClockManClockMaskFlag){
        //----時計１２：００を指す
        SpData.No       = ZIRI_CHAR_EVENT_CLOCK_PARTS;      //インデックス番号
        SpData.PosX     = 218;                              //X位置 DMY
        SpData.PosY     = 31;                               //Y位置 DMY
        SpData.PosZ     = PRIORITY_EVENT_CLOCKMAN-1;        //優先順位
        SpData.ScaleX   = SCALE10;                          //スケールX
        SpData.ScaleY   = SCALE10;                          //スケールY
        SpData.Rotate   = ROTATE000;                        //回転角
        SpData.Reverse  = NOREVERS;                         //反転コード
        DrawSprite( &SpData );                              //スプライト描画
    }

    //----ボディ
    SpData.No       = ClockManBodySpriteTable[ZGameMgr.Event.AllClear.ClockManBodyAnmIndex].No;     //インデックス番号
    SpData.PosX     = ClockManBodySpriteTable[ZGameMgr.Event.AllClear.ClockManBodyAnmIndex].Ofx;    //X位置
    SpData.PosY     = ClockManBodySpriteTable[ZGameMgr.Event.AllClear.ClockManBodyAnmIndex].Ofy;    //Y位置
    SpData.PosZ     = PRIORITY_EVENT_CLOCKMAN;          //優先順位
    SpData.ScaleX   = SCALE10;                          //スケールX
    SpData.ScaleY   = SCALE10;                          //スケールY
    SpData.Rotate   = ROTATE000;                        //回転角
    SpData.Reverse  = NOREVERS;                         //反転コード
    DrawSprite( &SpData );                              //スプライト描画

    //----左手
    SpData.No       = ClockManArmSpriteTable[ZGameMgr.Event.AllClear.ClockManArmAnmIndex].No;       //インデックス番号
    SpData.PosX     = ClockManArmSpriteTable[ZGameMgr.Event.AllClear.ClockManArmAnmIndex].Ofx;      //X位置
    SpData.PosY     = ClockManArmSpriteTable[ZGameMgr.Event.AllClear.ClockManArmAnmIndex].Ofy;      //Y位置
    SpData.PosZ     = PRIORITY_EVENT_CLOCKMAN;          //優先順位
    SpData.ScaleX   = SCALE10;                          //スケールX
    SpData.ScaleY   = SCALE10;                          //スケールY
    SpData.Rotate   = ROTATE000;                        //回転角
    SpData.Reverse  = NOREVERS;                         //反転コード
    DrawSprite( &SpData );                              //スプライト描画

    //----右手
    SpData.No       = ClockManArmSpriteTable[ZGameMgr.Event.AllClear.ClockManArmAnmIndex+1].No;     //インデックス番号
    SpData.PosX     = ClockManArmSpriteTable[ZGameMgr.Event.AllClear.ClockManArmAnmIndex+1].Ofx;    //X位置
    SpData.PosY     = ClockManArmSpriteTable[ZGameMgr.Event.AllClear.ClockManArmAnmIndex+1].Ofy;    //Y位置
    SpData.PosZ     = PRIORITY_EVENT_CLOCKMAN;          //優先順位
    SpData.ScaleX   = SCALE10;                          //スケールX
    SpData.ScaleY   = SCALE10;                          //スケールY
    SpData.Rotate   = ROTATE000;                        //回転角
    SpData.Reverse  = NOREVERS;                         //反転コード
    DrawSprite( &SpData );                              //スプライト描画

}


//-----------------------------------------------------------------------------
//  関数名  :AllClearEventSmallClockMan
//
//  work    :オールクリア時計マン（小）
//  in      :なし
//  out     :なし
//  note    :なし
//-----------------------------------------------------------------------------
static void AllClearEventSmallClockMan(void)
{

    static ZIRI_SPRITE_DATA DoorOpenClockManBodySpriteTable[]=
    {
        {   ZIRI_CHAR_EVENT_DOOR_00,    139,    112 },      //扉基本
    };

    static ZIRI_SPRITE_DATA DoorOpenClockManSpriteTable[]=
    {
        {   ZIRI_CHAR_EVENT_DOOR_01,    135,    112 },      //扉A00
        {   ZIRI_CHAR_EVENT_DOOR_02,    159,    112 },      //扉A01
        {   ZIRI_CHAR_EVENT_DOOR_03,    120,    112 },      //扉B00
        {   ZIRI_CHAR_EVENT_DOOR_04,    178,    112 },      //扉B01
        {   ZIRI_CHAR_EVENT_DOOR_05,    120,    112 },      //扉C00
        {   ZIRI_CHAR_EVENT_DOOR_06,    178,    112 },      //扉C01
        {   ZIRI_CHAR_EVENT_DOOR_07,    120,    112 },      //扉D00
        {   ZIRI_CHAR_EVENT_DOOR_08,    178,    112 },      //扉D01
        {   ZIRI_CHAR_EVENT_DOOR_07,    120,    112 },      //扉D00 DMY
        {   ZIRI_CHAR_EVENT_DOOR_08,    178,    112 },      //扉D01 DMY
    };

    static ZIRI_SPRITE_DATA JumpClockManSpriteTable[]=
    {
        {   ZIRI_CHAR_EVENT_JUMP_CLOCMAN_02,    121,    105 },          //飛び出すトケイマン小  
        {   ZIRI_CHAR_EVENT_JUMP_CLOCMAN_00,    108,    95  },          //飛び出すトケイマン大00
        {   ZIRI_CHAR_EVENT_JUMP_CLOCMAN_01,    108,    86  },          //飛び出すトケイマン大01
        {   ZIRI_CHAR_EVENT_JUMP_CLOCMAN_00,    108,    95  },          //飛び出すトケイマン大00
    };
    SPRITE_DATA SpData;


    if(ZGameMgr.Event.Timer >= SMALL_CLOCKMAN_JUMP_START_TIME)
    {
        switch(ZGameMgr.Event.AllClear.SmallClockManMode)
        {
            //------------------------------------扉オープン
            case SMALL_CLOCKMAN_MODE_00:
                
                //----時計マン(小)描画
                SpData.No       = DoorOpenClockManBodySpriteTable[0].No;    //インデックス番号
                SpData.PosX     = DoorOpenClockManBodySpriteTable[0].Ofx;   //X位置
                SpData.PosY     = DoorOpenClockManBodySpriteTable[0].Ofy;   //Y位置
                SpData.PosZ     = PRIORITY_EVENT_SMALL_CLOCKMAN;            //優先順位
                SpData.ScaleX   = SCALE10;                                  //スケールX
                SpData.ScaleY   = SCALE10;                                  //スケールY
                SpData.Rotate   = ROTATE000;                                //回転角
                SpData.Reverse  = NOREVERS;                                 //反転コード
                DrawSprite( &SpData );                                      //スプライト描画

                //----扉左描画
                SpData.No       = DoorOpenClockManSpriteTable[ZGameMgr.Event.AllClear.SmallClockManAnmIndex].No;    //インデックス番号
                SpData.PosX     = DoorOpenClockManSpriteTable[ZGameMgr.Event.AllClear.SmallClockManAnmIndex].Ofx;   //X位置
                SpData.PosY     = DoorOpenClockManSpriteTable[ZGameMgr.Event.AllClear.SmallClockManAnmIndex].Ofy;   //Y位置
                SpData.PosZ     = PRIORITY_EVENT_SMALL_CLOCKMAN-1;  //優先順位
                SpData.ScaleX   = SCALE10;                          //スケールX
                SpData.ScaleY   = SCALE10;                          //スケールY
                SpData.Rotate   = ROTATE000;                        //回転角
                SpData.Reverse  = NOREVERS;                         //反転コード
                DrawSprite( &SpData );                              //スプライト描画

                //----扉右描画
                SpData.No       = DoorOpenClockManSpriteTable[ZGameMgr.Event.AllClear.SmallClockManAnmIndex + 1].No;;   //インデックス番号
                SpData.PosX     = DoorOpenClockManSpriteTable[ZGameMgr.Event.AllClear.SmallClockManAnmIndex + 1].Ofx;   //X位置
                SpData.PosY     = DoorOpenClockManSpriteTable[ZGameMgr.Event.AllClear.SmallClockManAnmIndex + 1].Ofy;   //Y位置
                SpData.PosZ     = PRIORITY_EVENT_SMALL_CLOCKMAN-1;  //優先順位
                SpData.ScaleX   = SCALE10;                          //スケールX
                SpData.ScaleY   = SCALE10;                          //スケールY
                SpData.Rotate   = ROTATE000;                        //回転角
                SpData.Reverse  = NOREVERS;                         //反転コード
                DrawSprite( &SpData );                              //スプライト描画


                if(++ZGameMgr.Event.AllClear.SmallClockManAnmWaitTimer >= EVENT_ANM_WAIT_TIME)
                {
                    ZGameMgr.Event.AllClear.SmallClockManAnmWaitTimer = 0;
                    ZGameMgr.Event.AllClear.SmallClockManAnmIndex += 2;
                    if(ZGameMgr.Event.AllClear.SmallClockManAnmIndex >= 8)
                    {
                        ZGameMgr.Event.AllClear.SmallClockManAnmIndex   = 0;
                        ZGameMgr.Event.AllClear.SmallClockManMode       = SMALL_CLOCKMAN_MODE_01;
                    }
                }

                break;
            //------------------------------------飛び出す
            case SMALL_CLOCKMAN_MODE_01:
                
                //----描画
                SpData.No       = JumpClockManSpriteTable[ZGameMgr.Event.AllClear.SmallClockManAnmIndex].No;    //インデックス番号
                SpData.PosX     = JumpClockManSpriteTable[ZGameMgr.Event.AllClear.SmallClockManAnmIndex].Ofx;   //X位置
                SpData.PosY     = JumpClockManSpriteTable[ZGameMgr.Event.AllClear.SmallClockManAnmIndex].Ofy;   //Y位置
                SpData.PosZ     = PRIORITY_EVENT_SMALL_CLOCKMAN;    //優先順位
                SpData.ScaleX   = SCALE10;                          //スケールX
                SpData.ScaleY   = SCALE10;                          //スケールY
                SpData.Rotate   = ROTATE000;                        //回転角
                SpData.Reverse  = NOREVERS;                         //反転コード
                DrawSprite( &SpData );                              //スプライト描画

                if(++ZGameMgr.Event.AllClear.SmallClockManAnmWaitTimer >= EVENT_ANM_WAIT_TIME){
                    ZGameMgr.Event.AllClear.SmallClockManAnmWaitTimer = 0;
                    if(++ZGameMgr.Event.AllClear.SmallClockManAnmIndex >= 3){
                        ZGameMgr.Event.AllClear.SmallClockManAnmIndex = 3;
                    }
                }
                break;
            default:
        }
    }
}


//-----------------------------------------------------------------------------
//  関数名  :AllClearEventStar
//
//  work    :オールクリア★
//  in      :なし
//  out     :なし
//  note    :なし
//-----------------------------------------------------------------------------
static void AllClearEventStar(void)
{
    static ZIRI_SPRITE_DATA StarSpriteTable[]=
    {
        //----
        {   ZIRI_CHAR_EVENT_STAR_EFFECT_00, 65,     51 },   //星エフェクトA00
        {   ZIRI_CHAR_EVENT_STAR_EFFECT_01, 199,    55 },  //星エフェクトA01
        //----
        {   ZIRI_CHAR_EVENT_STAR_EFFECT_02, 44,     46 },   //星エフェクトB00
        {   ZIRI_CHAR_EVENT_STAR_EFFECT_03, 206,    46 },  //星エフェクトB01
        //----
        {   ZIRI_CHAR_EVENT_STAR_00,        50,     66  },  //星A
        {   ZIRI_CHAR_EVENT_STAR_00,        63,     99  },  //星A
        {   ZIRI_CHAR_EVENT_STAR_00,        104,    97  },  //星A
        {   ZIRI_CHAR_EVENT_STAR_00,        153,    72  },  //星A
        {   ZIRI_CHAR_EVENT_STAR_00,        189,    45  },  //星A
        {   ZIRI_CHAR_EVENT_STAR_00,        85,     169 },  //星A
        {   ZIRI_CHAR_EVENT_STAR_00,        200,    90  },  //星A
        {   ZIRI_CHAR_EVENT_STAR_00,        232,    112 },  //星A
        {   ZIRI_CHAR_EVENT_STAR_00,        238,    173 },  //星A
        {   ZIRI_CHAR_EVENT_STAR_01,        78,     47  },  //星B
        {   ZIRI_CHAR_EVENT_STAR_01,        123,    178 },  //星B
        {   ZIRI_CHAR_EVENT_STAR_01,        228,    153 },  //星B
        {   ZIRI_CHAR_EVENT_STAR_02,        147,    45  },  //星C
        {   ZIRI_CHAR_EVENT_STAR_02,        64,     99  },  //星C
        {   ZIRI_CHAR_EVENT_STAR_02,        44,     148 },  //星C
        {   ZIRI_CHAR_EVENT_STAR_02,        171,    178 },  //星C
        {   ZIRI_CHAR_EVENT_STAR_02,        258,    88  },  //星C
        {   ZIRI_CHAR_EVENT_STAR_03,        115,    64  },  //星D
        {   ZIRI_CHAR_EVENT_STAR_04,        240,    55  },  //星E
        {   ZIRI_CHAR_EVENT_STAR_04,        39,     120 },  //星E
        {   ZIRI_CHAR_EVENT_STAR_05,        80,     78  },  //星F
        {   ZIRI_CHAR_EVENT_EFFECT_00,      75,     134 },  //エフェクト00
        {   ZIRI_CHAR_EVENT_EFFECT_01,      210,    131 },  //エフェクト00
    };

    SPRITE_DATA SpData;
    int i;


    
    if( ZGameMgr.Event.Timer >= STAR_DRAW_START_TIME){
        if(++ZGameMgr.Event.AllClear.StarTimer >= EVENT_ANM_WAIT_TIME)
        {
            ZGameMgr.Event.AllClear.StarTimer = 0;
            
            if(++ZGameMgr.Event.AllClear.StarMode > STAR_MODE_02){
                ZGameMgr.Event.AllClear.StarMode = STAR_MODE_02;
            }
        }

        switch(ZGameMgr.Event.AllClear.StarMode)
        {
            case STAR_MODE_00:
                for(i=0;i<2;i++){
                    SpData.No       = StarSpriteTable[i].No;
                    SpData.PosX     = StarSpriteTable[i].Ofx;
                    SpData.PosY     = StarSpriteTable[i].Ofy;
                    SpData.PosZ     = PRIORITY_EVENT_STAR;
                    SpData.ScaleX   = SCALE10;
                    SpData.ScaleY   = SCALE10;
                    SpData.Rotate   = ROTATE000;
                    SpData.Reverse  = NOREVERS;
                    DrawSprite( &SpData );
                }
                break;
            case STAR_MODE_01:
                for(i=0;i<2;i++){
                    SpData.No       = StarSpriteTable[2+i].No;
                    SpData.PosX     = StarSpriteTable[2+i].Ofx;
                    SpData.PosY     = StarSpriteTable[2+i].Ofy;
                    SpData.PosZ     = PRIORITY_EVENT_STAR;
                    SpData.ScaleX   = SCALE10;
                    SpData.ScaleY   = SCALE10;
                    SpData.Rotate   = ROTATE000;
                    SpData.Reverse  = NOREVERS;
                    DrawSprite( &SpData );
            }
                break;
            case STAR_MODE_02:
                for(i=0;i<23;i++){
                    SpData.No       = StarSpriteTable[4+i].No;
                    SpData.PosX     = StarSpriteTable[4+i].Ofx;
                    SpData.PosY     = StarSpriteTable[4+i].Ofy;
                    SpData.PosZ     = PRIORITY_EVENT_STAR;
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

}


//-----------------------------------------------------------------------------
//  関数名  :AllClearEventBg
//
//  work    :オールクリア背景
//  in      :なし
//  out     :なし
//  note    :なし
//-----------------------------------------------------------------------------
static void AllClearEventBg(void)
{
    static int AllClearBgSpriteTable[]=
    {
        ZIRI_CHAR_EVENT_BG_FLUSH_00,ZIRI_CHAR_EVENT_BG_FLUSH_02,
        ZIRI_CHAR_EVENT_BG_FLUSH_01,ZIRI_CHAR_EVENT_BG_FLUSH_03,
    };

    SPRITE_DATA SpData;

    if(!ZGameMgr.Event.EndFlag){
        if(++ZGameMgr.Event.AllClear.BgAnmWaitTimer > EVENT_BG_ANM_WAIT_TIME){
            ZGameMgr.Event.AllClear.BgAnmWaitTimer  = 0;
            ZGameMgr.Event.AllClear.BgAnmIndex      ^= 1;
        }
    }

    SpData.No       = AllClearBgSpriteTable[ZGameMgr.Event.AllClear.BgAnmIndex*2];
    SpData.PosX     = 0;
    SpData.PosY     = 0;
    SpData.PosZ     = PRIORITY_BG;
    SpData.ScaleX   = SCALE10;
    SpData.ScaleY   = SCALE10;
    SpData.Rotate   = ROTATE000;
    SpData.Reverse  = NOREVERS;
    DrawSprite( &SpData );

    SpData.No       = AllClearBgSpriteTable[ZGameMgr.Event.AllClear.BgAnmIndex*2 + 1];
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
        ZIRI_CHAR_EVENT_SELECT_CONTINUE_BUPE_00,
        ZIRI_CHAR_EVENT_SELECT_CONTINUE_BUPE_01,
    };

    static int MaruBatuTable[]={
        ZIRI_CHAR_EVENT_SELECT_CONTINUE_YES_LIGHT,  ZIRI_CHAR_EVENT_SELECT_CONTINUE_NO_DARK,
        ZIRI_CHAR_EVENT_SELECT_CONTINUE_YES_DARK,   ZIRI_CHAR_EVENT_SELECT_CONTINUE_NO_LIGHT,
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
            ZGameMgr.SelectContinue.Val^=1;
            //[♪] レバー音
            ssPlaySe(BUTONSE_LEVER);
        }
    }


    //はい・いいえ
    SpData.No       = MaruBatuTable[ZGameMgr.SelectContinue.Val*2];     //インデックス番号
    SpData.PosX     = 68+72;                                            //X位置
    SpData.PosY     = 73+57;                                            //Y位置
    SpData.PosZ     = PRIORITY_EVENT_MENU-2;                            //優先順位
    SpData.ScaleX   = SCALE10;                                          //スケールX
    SpData.ScaleY   = SCALE10;                                          //スケールY
    SpData.Rotate   = ROTATE000;                                        //回転角
    SpData.Reverse  = NOREVERS;                                         //反転コード
    DrawSprite( &SpData );                                              //スプライト描画

    SpData.No       = MaruBatuTable[ZGameMgr.SelectContinue.Val*2+1];   //インデックス番号
    SpData.PosX     = 68+126;                                           //X位置
    SpData.PosY     = 73+57;                                            //Y位置
    SpData.PosZ     = PRIORITY_EVENT_MENU-2;                            //優先順位
    SpData.ScaleX   = SCALE10;                                          //スケールX
    SpData.ScaleY   = SCALE10;                                          //スケールY
    SpData.Rotate   = ROTATE000;                                        //回転角
    SpData.Reverse  = NOREVERS;                                         //反転コード
    DrawSprite( &SpData );                                              //スプライト描画

    //プレート文字
    switch(ZGameMgr.SelectContinue.Type)
    {
        case SELECT_RETRY_H:
            SpData.No       = ZIRI_CHAR_EVENT_SELECT_CONTINUE_RETRY_H;  //インデックス番号
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
            SpData.No       = ZIRI_CHAR_EVENT_SELECT_CONTINUE_END_H;    //インデックス番号
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
            SpData.No       = ZIRI_CHAR_EVENT_SELECT_CONTINUE_CONTINUE_H;//インデックス番号
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
    if(++ZGameMgr.SelectContinue.Wt>SELECT_LEVEL_PUPE_ANM_TIME){
        ZGameMgr.SelectContinue.No^=1;
        ZGameMgr.SelectContinue.Wt=0;
    }
    SpData.No       = BupeAnmTable[ZGameMgr.SelectContinue.No]; //インデックス番号
    SpData.PosX     = 68+12;                                    //X位置
    SpData.PosY     = 73+34;                                    //Y位置
    SpData.PosZ     = PRIORITY_EVENT_MENU-10;                   //優先順位
    SpData.ScaleX   = SCALE10;                                  //スケールX
    SpData.ScaleY   = SCALE10;                                  //スケールY
    SpData.Rotate   = ROTATE000;                                //回転角
    SpData.Reverse  = NOREVERS;                                 //反転コード
    DrawSprite( &SpData );                                      //スプライト描画

    //プレート
    SpData.No       = ZIRI_CHAR_EVENT_SELECT_CONTINUE_PLATE;    //インデックス番号
    SpData.PosX     = 68;                                       //X位置
    SpData.PosY     = 73;                                       //Y位置
    SpData.PosZ     = PRIORITY_EVENT_MENU;                      //優先順位
    SpData.ScaleX   = SCALE10;                                  //スケールX
    SpData.ScaleY   = SCALE10;                                  //スケールY
    SpData.Rotate   = ROTATE000;                                //回転角
    SpData.Reverse  = NOREVERS;                                 //反転コード
    DrawSprite( &SpData );                                      //スプライト描画

    //えらぶ
    SpData.No       = ZIRI_CHAR_EVENT_SELECT_CONTINUE_ERABU;    //インデックス番号
    SpData.PosX     = (320-130)/2;                              //X位置
    SpData.PosY     = 206;                                      //Y位置
    SpData.PosZ     = PRIORITY_EVENT_MENU-1;                    //優先順位
    SpData.ScaleX   = SCALE10;                                  //スケールX
    SpData.ScaleY   = SCALE10;                                  //スケールY
    SpData.Rotate   = ROTATE000;                                //回転角
    SpData.Reverse  = NOREVERS;                                 //反転コード
    DrawSprite( &SpData );                                      //スプライト描画

    //けってい
    SpData.No       = ZIRI_CHAR_EVENT_SELECT_CONTINUE_KETEI;    //インデックス番号
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




#ifdef __DEBUG_ZIRI__
//-----------------------------------------------------------------------------
//  関数名 :DebugSpriteTask
//
//  work   :デバッグスプライトタスク
//  in     :TASK*       タスクポインタ
//  out    :TRUE
//  note   :なし
//-----------------------------------------------------------------------------
static int DebugSpriteTask(TASK* ip_task)
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

//          //----texture read sram -> vram
//          if((file_read(ZiriTextureFile[0].fn,LoadAddress)) == -1)
//          {//read error
//              return FALSE;
//          }
//
//          //----texture init
//          TexInit( ZIRI_TIM_NUM, &ZiriTextureImage[ZIRI_TIM_POS] );
//          TimImgData = ZiriTextureImage;
//
//          //----スプライト登録
//          EntrySprite( ZiriSpriteData );

            //フェードイン
            GameMgr.FadeFlag    = FadeIn;

            //----
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


            SpData.No       = SpIndex;                                      //インデックス番号
            SpData.PosX     = (320 - ZiriSpriteData[SpIndex].Width)  / 2;   //X位置
            SpData.PosY     = (240 - ZiriSpriteData[SpIndex].Height) / 2;   //Y位置
            SpData.PosZ     = 10;                                           //優先順位
            SpData.ScaleX   = SCALE10;                                      //スケールX
            SpData.ScaleY   = SCALE10;                                      //スケールY
            SpData.Rotate   = ROTATE000;                                    //回転角
            SpData.Reverse  = NOREVERS;                                     //反転コード
            DrawSprite( &SpData );                                          //スプライト描画

            //info
            FntPrint("SNO=%d/%d\n", SpIndex,SpEntryNum-1 );
            FntPrint("OfX=%d\n",    ZiriSpriteData[SpIndex].OffSetX );      //TIMの中のスプライト左上開始X位置
            FntPrint("OfY=%d\n",    ZiriSpriteData[SpIndex].OffSetY );      //TIMの中のスプライト左上開始Y位置
            FntPrint("W__=%d\n",    ZiriSpriteData[SpIndex].Width   );      //TIMの中のテクスチャの幅
            FntPrint("H__=%d\n",    ZiriSpriteData[SpIndex].Height  );      //TIMの中のテクスチャの高さ
            FntPrint("PNO=%d\n",    ZiriSpriteData[SpIndex].PaletteNo );    //TIMの中のテクスチャパレット番号
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
// end of ZIRI.C
//-----------------------------------------------------------------------------