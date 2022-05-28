//-----------------------------------------------------------------------------
// MAZE.C
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  include
//-----------------------------------------------------------------------------
#include "COMMON.H"
#include "KAZU.H"
#include "SPMGR.H"
#include "TASKMGR.H"
#include "MAZE.H"
#include "SPCONT.H"
#include "SOUND.H"
//-----------------------------------------------------------------------------
//  define
//-----------------------------------------------------------------------------
//----debug sw 「デバッグ時はコメントを外してください」
//  #define __DEBUG_MAZE__

//  #define __DEBUG_MAZE_ANSWER__

//----GAME TEXTURE
#define MAZE_GAME_TIM_POS       0+4
#define MAZE_GAME_TIM_NUM       13

//----GAME TEXTURE
#define TIM_POS_MAZE_GAME_BG01A         0+4
#define TIM_POS_MAZE_GAME_BG01B         1+4
#define TIM_POS_MAZE_GAME_BG03A         2+4
#define TIM_POS_MAZE_GAME_BG03B         3+4
#define TIM_POS_MAZE_GAME_DON02         4+4
#define TIM_POS_MAZE_GAME_DON03         5+4
#define TIM_POS_MAZE_GAME_DON04         6+4
#define TIM_POS_MAZE_GAME_GUN03         7+4
#define TIM_POS_MAZE_GAME_PARTS_00      8+4
#define TIM_POS_MAZE_GAME_PARTS_01      9+4
#define TIM_POS_MAZE_GAME_GUN02G        10+4
#define TIM_POS_MAZE_GAME_GUN04G        11+4
#define TIM_POS_MAZE_GAME_GUN01G        12+4



//----EVENT TEXTURE
#define MAZE_EVENT_TIM_POS      0+4
#define MAZE_EVENT_TIM_NUM      12

//----EVENT TEXTURE
#define TIM_POS_MAZE_EVENT_FONT         0       //選択処理テクスチャ
#define TIM_POS_MAZE_EVENT_YORNO        1       //選択処理テクスチャ

#define TIM_POS_MAZE_EVENT_BAKU01A      0+4
#define TIM_POS_MAZE_EVENT_BAKU01B      1+4
#define TIM_POS_MAZE_EVENT_BG02A        2+4
#define TIM_POS_MAZE_EVENT_BG02B        3+4
#define TIM_POS_MAZE_EVENT_BG02C        4+4
#define TIM_POS_MAZE_EVENT_BG02D        5+4
#define TIM_POS_MAZE_EVENT_DON01        6+4
#define TIM_POS_MAZE_EVENT_DON03E       7+4
#define TIM_POS_MAZE_EVENT_GUN01        8+4
#define TIM_POS_MAZE_EVENT_GUN02        9+4
#define TIM_POS_MAZE_EVENT_GUN04        10+4
#define TIM_POS_MAZE_EVENT_DON02E       11+4


//----GAME SPRITE INDEX
enum{
    MAZE_CHAR_GAME_BG_00,                           //背景１
    MAZE_CHAR_GAME_BG_01,                           //背景2
    MAZE_CHAR_GAME_SELECT_LEVEL_BG_00,              //背景１
    MAZE_CHAR_GAME_SELECT_LEVEL_BG_01,              //背景2
    MAZE_CHAR_GAME_KUMA_ENTRY_00,                   //クマ登場1
    MAZE_CHAR_GAME_KUMA_ENTRY_MOUSE,                //クマの口
    MAZE_CHAR_GAME_DANTYOU_00,                      //団長00アニメ
    MAZE_CHAR_GAME_DANTYOU_01,                      //団長01アニメ
    MAZE_CHAR_GAME_DANIN_FUUSEN_BLUE_00,            //楽団員A00アニメ(青風船時)
    MAZE_CHAR_GAME_DANIN_FUUSEN_ORANGE_00,          //楽団員A00アニメ(橙風船時)
    MAZE_CHAR_GAME_DANIN_FUUSEN_BLUE_01,            //楽団員A01アニメ(青風船時)
    MAZE_CHAR_GAME_DANIN_FUUSEN_ORANGE_01,          //楽団員A01アニメ(橙風船時)
    MAZE_CHAR_GAME_DANIN_HATA_00,                   //楽団員B00アニメ
    MAZE_CHAR_GAME_DANIN_HATA_01,                   //楽団員B01アニメ
    MAZE_CHAR_GAME_DANIN_HATA_02,                   //楽団員C00アニメ
    MAZE_CHAR_GAME_DANIN_HATA_03,                   //楽団員C01アニメ
    MAZE_CHAR_GAME_SELECT_LEVEL_CURSOR,             //レベル選択カーソル枠
    MAZE_CHAR_GAME_SELECT_LEVEL_PLATE_LIGHT,        //レベル選択用チップ(明)
    MAZE_CHAR_GAME_SELECT_LEVEL_PLATE_DARK,         //レベル選択用チップ（暗い）
    MAZE_CHAR_GAME_SELECT_LEVEL_NUM_1,              //レベル表示数字”１”
    MAZE_CHAR_GAME_SELECT_LEVEL_NUM_2,              //レベル表示数字”２”
    MAZE_CHAR_GAME_SELECT_LEVEL_NUM_3,              //レベル表示数字”３”
    MAZE_CHAR_GAME_SELECT_LEVEL_NUM_4,              //レベル表示数字”４”
    MAZE_CHAR_GAME_SELECT_LEVEL_NUM_5,              //レベル表示数字”５”
    MAZE_CHAR_GAME_KUMA_ENTRY_02,                   //クマ登場2
    MAZE_CHAR_GAME_KUMA_00,                         //クマ基本・小
    MAZE_CHAR_GAME_KUMA_01,                         //クマ歩く下A
    MAZE_CHAR_GAME_KUMA_02,                         //クマ歩く下B
    MAZE_CHAR_GAME_KUMA_03,                         //クマ歩く上A
    MAZE_CHAR_GAME_KUMA_04,                         //クマ歩く上B
    MAZE_CHAR_GAME_KUMA_05,                         //クマバンザイ１
    MAZE_CHAR_GAME_KUMA_06,                         //クマバンザイ２
    MAZE_CHAR_GAME_KUMA_07,                         //クマバンザイ３
    MAZE_CHAR_GAME_KUMA_08,                         //クマ歩く右A
    MAZE_CHAR_GAME_KUMA_09,                         //クマ歩く右B
    MAZE_CHAR_GAME_KUMA_10,                         //クマ歩く左A
    MAZE_CHAR_GAME_KUMA_11,                         //クマ歩く左B
    MAZE_CHAR_GAME_KUMA_12,                         //クマ走る左A
    MAZE_CHAR_GAME_KUMA_13,                         //クマ走る左B
    MAZE_CHAR_GAME_KUMA_14,                         //クマ走る右A
    MAZE_CHAR_GAME_KUMA_15,                         //クマ走る右B
    MAZE_CHAR_GAME_KUMA_16,                         //クマ手振りA
    MAZE_CHAR_GAME_KUMA_17,                         //クマ手振りB
    MAZE_CHAR_GAME_KUMA_18,                         //クマ地団駄A
    MAZE_CHAR_GAME_KUMA_19,                         //クマ地団駄B
    MAZE_CHAR_GAME_KUMA_20,                         //クマ登場A
    MAZE_CHAR_GAME_KUMA_21,                         //クマ登場B
    MAZE_CHAR_GAME_KUMA_22,                         //クマあかんべ
    MAZE_CHAR_GAME_KUMA_23,                         //クマグングン見る
    MAZE_CHAR_GAME_KUMA_24,                         //クマ胸ドン
    MAZE_CHAR_GAME_KUMA_25,                         //クマじたばたA
    MAZE_CHAR_GAME_KUMA_26,                         //クマじたばたB
    MAZE_CHAR_GAME_KUMA_ENTRY_01,                   //クマ登場0
    MAZE_CHAR_GAME_GUNGUN_00,                       //歩く左A
    MAZE_CHAR_GAME_GUNGUN_01,                       //歩く左B
    MAZE_CHAR_GAME_GUNGUN_02,                       //歩く右A
    MAZE_CHAR_GAME_GUNGUN_03,                       //歩く右B
    MAZE_CHAR_GAME_GUNGUN_04,                       //歩く下A
    MAZE_CHAR_GAME_GUNGUN_05,                       //歩く下B
    MAZE_CHAR_GAME_GUNGUN_06,                       //歩く上A
    MAZE_CHAR_GAME_GUNGUN_07,                       //歩く上B
    MAZE_CHAR_GAME_GUNGUN_08,                       //バンザイA
    MAZE_CHAR_GAME_GUNGUN_09,                       //バンザイB
    MAZE_CHAR_GAME_GUNGUN_10,                       //手振り１A
    MAZE_CHAR_GAME_GUNGUN_11,                       //手振り１B
    MAZE_CHAR_GAME_GUNGUN_12,                       //手振り２B
    MAZE_CHAR_GAME_GUNGUN_13,                       //手振り２B
    MAZE_CHAR_GAME_GUNGUN_14,                       //ガッツA
    MAZE_CHAR_GAME_GUNGUN_15,                       //ガッツB
    MAZE_CHAR_GAME_GUNGUN_CATCH_00,                 //グングン捕まる　グングン左
    MAZE_CHAR_GAME_GUNGUN_CATCH_01,                 //グングン捕まる　グングン上
    MAZE_CHAR_GAME_GUNGUN_CATCH_02,                 //グングン捕まる　グングン右
    MAZE_CHAR_GAME_GUNGUN_CATCH_03,                 //グングン捕まる　グングン下
    MAZE_CHAR_GAME_GUNGUN_ENTRY_00,                 //登場
    MAZE_CHAR_GAME_GUNGUN_ENTRY_01,                 //登場縦長
    MAZE_CHAR_GAME_GUNGUN_ENTRY_02,                 //登場横長
    MAZE_CHAR_GAME_QUESTION_NUM_00,                 //出題の数字”０”
    MAZE_CHAR_GAME_QUESTION_NUM_01,                 //出題の数字”１”
    MAZE_CHAR_GAME_QUESTION_NUM_02,                 //出題の数字”２”
    MAZE_CHAR_GAME_QUESTION_NUM_03,                 //出題の数字”３”
    MAZE_CHAR_GAME_QUESTION_NUM_04,                 //出題の数字”４”
    MAZE_CHAR_GAME_QUESTION_NUM_05,                 //出題の数字”５”
    MAZE_CHAR_GAME_QUESTION_NUM_06,                 //出題の数字”６”
    MAZE_CHAR_GAME_QUESTION_NUM_07,                 //出題の数字”７”
    MAZE_CHAR_GAME_QUESTION_NUM_08,                 //出題の数字”８”
    MAZE_CHAR_GAME_QUESTION_NUM_09,                 //出題の数字”９”
    MAZE_CHAR_GAME_QUESTION_NUM_10,                 //出題の数字”１０”
    MAZE_CHAR_GAME_QUESTION_MARK_H,                 //出題の”？”マーク
    MAZE_CHAR_GAME_QUESTION_STR_TO,                 //出題の”と”
    MAZE_CHAR_GAME_QUESTION_STR_HA,                 //出題の”は”
    MAZE_CHAR_GAME_ANSWER_NUM_00,                   //答えの数字ボール”０”
    MAZE_CHAR_GAME_ANSWER_NUM_01,                   //答えの数字ボール”１”
    MAZE_CHAR_GAME_ANSWER_NUM_02,                   //答えの数字ボール”２”
    MAZE_CHAR_GAME_ANSWER_NUM_03,                   //答えの数字ボール”３”
    MAZE_CHAR_GAME_ANSWER_NUM_04,                   //答えの数字ボール”４”
    MAZE_CHAR_GAME_ANSWER_NUM_05,                   //答えの数字ボール”５”
    MAZE_CHAR_GAME_ANSWER_NUM_06,                   //答えの数字ボール”６”
    MAZE_CHAR_GAME_ANSWER_NUM_07,                   //答えの数字ボール”７”
    MAZE_CHAR_GAME_ANSWER_NUM_08,                   //答えの数字ボール”８”
    MAZE_CHAR_GAME_ANSWER_NUM_09,                   //答えの数字ボール”９”
    MAZE_CHAR_GAME_ANSWER_NUM_10,                   //答えの数字ボール”１０”
    MAZE_CHAR_GAME_HAI_ARROW_LEFT,                  //矢印 左・灰色
    MAZE_CHAR_GAME_HAI_ARROW_UP,                    //矢印 上・灰色
    MAZE_CHAR_GAME_HAI_ARROW_RIGHT,                 //矢印 右・灰色
    MAZE_CHAR_GAME_HAI_ARROW_DOWN,                  //矢印 下・灰色
    MAZE_CHAR_GAME_RED_ARROW_LEFT,                  //矢印 左・赤
    MAZE_CHAR_GAME_RED_ARROW_UP,                    //矢印 上・赤
    MAZE_CHAR_GAME_RED_ARROW_RIGHT,                 //矢印 右・赤
    MAZE_CHAR_GAME_RED_ARROW_DOWN,                  //矢印 下・赤
    MAZE_CHAR_GAME_SMOKE_00,                        //煙幕大
    MAZE_CHAR_GAME_SMOKE_01,                        //煙幕小
    MAZE_CHAR_GAME_SAKU_00,                         //柵    A
    MAZE_CHAR_GAME_SAKU_01,                         //柵    B
    MAZE_CHAR_GAME_SMALL_STAR,                      //星小
    MAZE_CHAR_GAME_BEE_LEFT,                        //蜂左
    MAZE_CHAR_GAME_BEE_RIGHT,                       //蜂右
    MAZE_CHAR_GAME_BIG_STAR,                        //星大
    MAZE_CHAR_GAME_BIG_ARROW_LEFT,                  //左向き矢印
    MAZE_CHAR_GAME_BIG_ARROW_RIGHT,                 //右向き矢印
    MAZE_CHAR_GAME_GUNGUN_FACE_00,                  //グングン・左顔00アニメ
    MAZE_CHAR_GAME_GUNGUN_FACE_01,                  //グングン・左顔00アニメ
    MAZE_CHAR_GAME_GUNGUN_FACE_02,                  //グングン・右顔00アニメ
    MAZE_CHAR_GAME_GUNGUN_FACE_03,                  //グングン・右顔00アニメ
    MAZE_CHAR_GAME_GUNGUN_MARK,                     //グングンマーク
    MAZE_CHAR_GAME_IWA_00,                          //赤岩
    MAZE_CHAR_GAME_IWA_01,                          //青岩
    MAZE_CHAR_GAME_GUNGUN_BOROBORO_01,              //グングンぼろ２
    MAZE_CHAR_GAME_GUNGUN_BODY,                     //グングングングン胴
    MAZE_CHAR_GAME_GUNGUN_FACE_00_DMY,              //グングン頭正面
    MAZE_CHAR_GAME_GUNGUN_FACE_01_DMY,              //グングン頭傾
    MAZE_CHAR_GAME_GUNGUN_KATATE_UE,                //グングン片手上げ上
    MAZE_CHAR_GAME_GUNGUN_KATATE_YOKO,              //グングン片手上げ横
    MAZE_CHAR_GAME_GUNGUN_MOUTH_00,                 //グングン口正面・開
    MAZE_CHAR_GAME_GUNGUN_MOUTH_01,                 //グングン口正面・閉
    MAZE_CHAR_GAME_GUNGUN_MOUTH_02,                 //グングン口傾・開
    MAZE_CHAR_GAME_GUNGUN_MOUTH_03,                 //グングン口傾・閉
    MAZE_CHAR_GAME_GUNGUN_BANZAI_BODY,              //グングンバンザイ胴・頭
    MAZE_CHAR_GAME_GUNGUN_BANZAI_ARM_UE_LEFT,       //グングンバンザイ上腕　左
    MAZE_CHAR_GAME_GUNGUN_BANZAI_ARM_UE_RIGHT,      //グングンバンザイ上腕　右
    MAZE_CHAR_GAME_GUNGUN_BANZAI_ARM_YOKO_LEFT,     //グングンバンザイ横腕　左
    MAZE_CHAR_GAME_GUNGUN_BANZAI_ARM_YOKO_RIGHT,    //グングンバンザイ横腕　右
    MAZE_CHAR_GAME_GUNGUN_BANZAI_MOUTH,             //グングンバンザイ口・開
    MAZE_CHAR_GAME_GUNGUN_JUMP,                     //グングンジャンプ本体
    MAZE_CHAR_GAME_GUNGUN_JUMP_MOUTH_00,            //グングンジャンプ口・閉
    MAZE_CHAR_GAME_GUNGUN_JUMP_MOUTH_01,            //グングンジャンプ口・開
    MAZE_CHAR_GAME_SHADOW_BIG,                      //影大
    MAZE_CHAR_GAME_SHADOW_SMALL,                    //影小
    MAZE_CHAR_GAME_KUMA_BODY,                       //クマ胴体
    MAZE_CHAR_GAME_KUMA_HEAD_00,                    //クマ頭A
    MAZE_CHAR_GAME_KUMA_HEAD_01,                    //クマ頭B
    MAZE_CHAR_GAME_KUMA_GUTS_00_ARM_LEFT,           //クマガッツ1腕 左
    MAZE_CHAR_GAME_KUMA_GUTS_00_ARM_RIGHT,          //クマガッツ1腕 右
    MAZE_CHAR_GAME_KUMA_ENTRY_ARM_LEFT,             //クマ登場腕　左
    MAZE_CHAR_GAME_KUMA_ENTRY_ARM_RIGHT,            //クマ登場腕　右
    MAZE_CHAR_GAME_KUMA_SEE_ARM_LEFT,               //クマ見る腕　左
    MAZE_CHAR_GAME_KUMA_SEE_ARM_RIGHT,              //クマ見る腕　右
    MAZE_CHAR_GAME_KUMA_BASIC_ARM_LEFT,             //クマ基本腕　左
    MAZE_CHAR_GAME_KUMA_BASIC_ARM_RIGHT,            //クマ基本腕　右
    MAZE_CHAR_GAME_KUMA_GUTS_01_ARM_LEFT,           //クマガッツ２腕　左
    MAZE_CHAR_GAME_KUMA_GUTS_01_ARM_RIGHT,          //クマガッツ２腕　右
    MAZE_CHAR_GAME_KUMA_AKANBE_ARM_LEFT,            //クマあかんべ腕　左
    MAZE_CHAR_GAME_KUMA_AKANBE_ARM_RIGHT,           //クマあかんべ腕  右
};


//----EVENT SPRITE INDEX
enum{
    MAZE_CHAR_EVENT_BAKU_BIG_00,                        //ゲーム後の効果画像
    MAZE_CHAR_EVENT_BAKU_BIG_01,                        //爆発大の続き
    MAZE_CHAR_EVENT_BAKU_MIDDLE,                        //爆発・中
    MAZE_CHAR_EVENT_BAKU_SMALL,                         //爆発・小
    MAZE_CHAR_EVENT_BG_00,                              //背景１
    MAZE_CHAR_EVENT_BG_01,                              //背景2
    MAZE_CHAR_EVENT_BG_02,                              //背景１（BG02の上の画像）
    MAZE_CHAR_EVENT_BG_03,                              //背景2（BG02の上の画像）
    MAZE_CHAR_EVENT_KUMA_BODY,                          //クマ胴体
    MAZE_CHAR_EVENT_KUMA_HEAD_00,                       //クマ頭A
    MAZE_CHAR_EVENT_KUMA_HEAD_01,                       //クマ頭B
    MAZE_CHAR_EVENT_KUMA_GUTS_00_ARM_LEFT,              //クマガッツ1腕 左
    MAZE_CHAR_EVENT_KUMA_GUTS_00_ARM_RIGHT,             //クマガッツ1腕 右
    MAZE_CHAR_EVENT_KUMA_ENTRY_ARM_LEFT,                //クマ登場腕　左
    MAZE_CHAR_EVENT_KUMA_ENTRY_ARM_RIGHT,               //クマ登場腕　右
    MAZE_CHAR_EVENT_KUMA_SEE_ARM_LEFT,                  //クマ見る腕　左
    MAZE_CHAR_EVENT_KUMA_SEE_ARM_RIGHT,                 //クマ見る腕　右
    MAZE_CHAR_EVENT_KUMA_BASIC_ARM_LEFT,                //クマ基本腕　左
    MAZE_CHAR_EVENT_KUMA_BASIC_ARM_RIGHT,               //クマ基本腕　右
    MAZE_CHAR_EVENT_KUMA_GUTS_01_ARM_LEFT,              //クマガッツ２腕　左
    MAZE_CHAR_EVENT_KUMA_GUTS_01_ARM_RIGHT,             //クマガッツ２腕　右
    MAZE_CHAR_EVENT_KUMA_AKANBE_ARM_LEFT,               //クマあかんべ腕　左
    MAZE_CHAR_EVENT_KUMA_AKANBE_ARM_RIGHT,              //クマあかんべ腕  右
    MAZE_CHAR_EVENT_KUMA_PARTS_00,                      //登場３
    MAZE_CHAR_EVENT_KUMA_PARTS_01,                      //基本・小
    MAZE_CHAR_EVENT_KUMA_PARTS_02,                      //歩く下A
    MAZE_CHAR_EVENT_KUMA_PARTS_03,                      //歩く下B
    MAZE_CHAR_EVENT_KUMA_PARTS_04,                      //歩く上A
    MAZE_CHAR_EVENT_KUMA_PARTS_05,                      //歩く上B
    MAZE_CHAR_EVENT_KUMA_PARTS_06,                      //バンザイ１
    MAZE_CHAR_EVENT_KUMA_PARTS_07,                      //バンザイ２
    MAZE_CHAR_EVENT_KUMA_PARTS_08,                      //バンザイ３
    MAZE_CHAR_EVENT_KUMA_PARTS_09,                      //歩く右A
    MAZE_CHAR_EVENT_KUMA_PARTS_10,                      //歩く右B
    MAZE_CHAR_EVENT_KUMA_PARTS_11,                      //歩く左A
    MAZE_CHAR_EVENT_KUMA_PARTS_12,                      //歩く左B
    MAZE_CHAR_EVENT_KUMA_PARTS_13,                      //走る左A
    MAZE_CHAR_EVENT_KUMA_PARTS_14,                      //走る左B
    MAZE_CHAR_EVENT_KUMA_PARTS_15,                      //走る右A
    MAZE_CHAR_EVENT_KUMA_PARTS_16,                      //走る右B
    MAZE_CHAR_EVENT_KUMA_PARTS_17,                      //手振りA
    MAZE_CHAR_EVENT_KUMA_PARTS_18,                      //手振りB
    MAZE_CHAR_EVENT_KUMA_PARTS_19,                      //地団駄A
    MAZE_CHAR_EVENT_KUMA_PARTS_20,                      //地団駄B
    MAZE_CHAR_EVENT_KUMA_PARTS_21,                      //登場A
    MAZE_CHAR_EVENT_KUMA_PARTS_22,                      //登場B
    MAZE_CHAR_EVENT_KUMA_PARTS_23,                      //あかんべ
    MAZE_CHAR_EVENT_KUMA_PARTS_24,                      //グングン見る
    MAZE_CHAR_EVENT_KUMA_PARTS_25,                      //胸ドン
    MAZE_CHAR_EVENT_KUMA_PARTS_26,                      //じたばたA
    MAZE_CHAR_EVENT_KUMA_PARTS_27,                      //じたばたB
    MAZE_CHAR_EVENT_GUNGUN_BOROBORO_00,                 //グングンぼろ１
    MAZE_CHAR_EVENT_GUNGUN_ZITANDA_00,                  //グングン地団駄A
    MAZE_CHAR_EVENT_GUNGUN_ZITANDA_01,                  //グングン地団駄B
    MAZE_CHAR_EVENT_KUMA_ZITANDA_00,                    //クマ地団駄１
    MAZE_CHAR_EVENT_KUMA_ZITANDA_01,                    //クマ地団駄２
    MAZE_CHAR_EVENT_KUMA_BANZAI_00,                     //クマバンザイ１
    MAZE_CHAR_EVENT_KUMA_BANZAI_01,                     //クマバンザイ２
    MAZE_CHAR_EVENT_KUMA_BANZAI_02,                     //クマバンザイ３
    MAZE_CHAR_EVENT_GUNGUN_BOROBORO_01,                 //グングンぼろ２
    MAZE_CHAR_EVENT_GUNGUN_BODY,                        //グングングングン胴
    MAZE_CHAR_EVENT_GUNGUN_FACE_00,                     //グングン頭正面
    MAZE_CHAR_EVENT_GUNGUN_FACE_01,                     //グングン頭傾
    MAZE_CHAR_EVENT_GUNGUN_KATATE_UE,                   //グングン片手上げ上
    MAZE_CHAR_EVENT_GUNGUN_KATATE_YOKO,                 //グングン片手上げ横
    MAZE_CHAR_EVENT_GUNGUN_MOUTH_00,                    //グングン口正面・開
    MAZE_CHAR_EVENT_GUNGUN_MOUTH_01,                    //グングン口正面・閉
    MAZE_CHAR_EVENT_GUNGUN_MOUTH_02,                    //グングン口傾・開
    MAZE_CHAR_EVENT_GUNGUN_MOUTH_03,                    //グングン口傾・閉
    MAZE_CHAR_EVENT_GUNGUN_BANZAI_BODY,                 //グングンバンザイ胴・頭
    MAZE_CHAR_EVENT_GUNGUN_BANZAI_ARM_UE_LEFT,          //グングンバンザイ上腕　左
    MAZE_CHAR_EVENT_GUNGUN_BANZAI_ARM_UE_RIGHT,         //グングンバンザイ上腕　右
    MAZE_CHAR_EVENT_GUNGUN_BANZAI_ARM_YOKO_LEFT,        //グングンバンザイ横腕　左
    MAZE_CHAR_EVENT_GUNGUN_BANZAI_ARM_YOKO_RIGHT,       //グングンバンザイ横腕　右
    MAZE_CHAR_EVENT_GUNGUN_BANZAI_MOUTH,                //グングンバンザイ口・開
    MAZE_CHAR_EVENT_GUNGUN_JUMP,                        //グングンジャンプ本体
    MAZE_CHAR_EVENT_GUNGUN_JUMP_MOUTH_00,               //グングンジャンプ口・閉
    MAZE_CHAR_EVENT_GUNGUN_JUMP_MOUTH_01,               //グングンジャンプ口・開
    MAZE_CHAR_EVENT_SHADOW_BIG,                         //影大
    MAZE_CHAR_EVENT_SHADOW_SMALL,                       //影小
    MAZE_CHAR_EVENT_SELECT_CONTINUE_PLATE,              //プレート
    MAZE_CHAR_EVENT_SELECT_CONTINUE_YES_DARK,           //非選択・はい
    MAZE_CHAR_EVENT_SELECT_CONTINUE_NO_DARK,            //非選択・いいえ
    MAZE_CHAR_EVENT_SELECT_CONTINUE_YES_LIGHT,          //選択・はい
    MAZE_CHAR_EVENT_SELECT_CONTINUE_NO_LIGHT,           //選択・いいえ
    MAZE_CHAR_EVENT_SELECT_CONTINUE_BUPE_00,            //プーぺ１
    MAZE_CHAR_EVENT_SELECT_CONTINUE_BUPE_01,            //プーぺ２
    MAZE_CHAR_EVENT_SELECT_CONTINUE_RETRY_H,            //もういちど
    MAZE_CHAR_EVENT_SELECT_CONTINUE_END_H,              //おわり
    MAZE_CHAR_EVENT_SELECT_CONTINUE_CONTINUE_H,         //つづけ
    MAZE_CHAR_EVENT_SELECT_CONTINUE_CURSOR,             //指カーソル
    MAZE_CHAR_EVENT_SELECT_CONTINUE_ERABU,              //えらぶ
    MAZE_CHAR_EVENT_SELECT_CONTINUE_KETEI,              //けってい
    MAZE_CHAR_EVENT_SELECT_CONTINUE_MENU,               //めにゅー
    MAZE_CHAR_EVENT_KUMA_ENTRY_00,                      //クマ登場1
    MAZE_CHAR_EVENT_KUMA_ENTRY_MOUSE,                   //クマの口
    MAZE_CHAR_EVENT_DANTYOU_00,                         //団長00アニメ
    MAZE_CHAR_EVENT_DANTYOU_01,                         //団長01アニメ
    MAZE_CHAR_EVENT_DANIN_FUUSEN_BLUE_00,               //楽団員A00アニメ(青風船時)
    MAZE_CHAR_EVENT_DANIN_FUUSEN_ORANGE_00,             //楽団員A00アニメ(橙風船時)
    MAZE_CHAR_EVENT_DANIN_FUUSEN_BLUE_01,               //楽団員A01アニメ(青風船時)
    MAZE_CHAR_EVENT_DANIN_FUUSEN_ORANGE_01,             //楽団員A01アニメ(橙風船時)
    MAZE_CHAR_EVENT_DANIN_HATA_00,                      //楽団員B00アニメ
    MAZE_CHAR_EVENT_DANIN_HATA_01,                      //楽団員B01アニメ
    MAZE_CHAR_EVENT_DANIN_HATA_02,                      //楽団員C00アニメ
    MAZE_CHAR_EVENT_DANIN_HATA_03,                      //楽団員C01アニメ
    MAZE_CHAR_EVENT_SELECT_LEVEL_CURSOR,                //レベル選択カーソル枠
    MAZE_CHAR_EVENT_SELECT_LEVEL_PLATE_LIGHT,           //レベル選択用チップ(明)
    MAZE_CHAR_EVENT_SELECT_LEVEL_PLATE_DARK,            //レベル選択用チップ（暗い）
    MAZE_CHAR_EVENT_SELECT_LEVEL_NUM_1,                 //レベル表示数字”１”
    MAZE_CHAR_EVENT_SELECT_LEVEL_NUM_2,                 //レベル表示数字”２”
    MAZE_CHAR_EVENT_SELECT_LEVEL_NUM_3,                 //レベル表示数字”３”
    MAZE_CHAR_EVENT_SELECT_LEVEL_NUM_4,                 //レベル表示数字”４”
    MAZE_CHAR_EVENT_SELECT_LEVEL_NUM_5,                 //レベル表示数字”５”
};


//-----------------------------------------------------------------------------
//  typdef
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  extern
//-----------------------------------------------------------------------------
//----PAD
extern u_long   pad;
extern u_long   NewPad; 
extern u_long   OldPad; 
extern u_long   JstPad; 
extern u_long   WorkPad;

//----TEXTURE
extern u_long   BG01A_image[];
extern u_long   BG01A_clut[];
extern u_long   BG01B_image[];
extern u_long   BG01B_clut[];
extern u_long   BG03A_image[];
extern u_long   BG03A_clut[];
extern u_long   BG03B_image[];
extern u_long   BG03B_clut[];
extern u_long   DON02_image[];
extern u_long   DON02_clut[];
extern u_long   DON03_image[];
extern u_long   DON03_clut[];
extern u_long   DON04_image[];
extern u_long   DON04_clut[];
extern u_long   GUN03_image[];
extern u_long   GUN03_clut[];
extern u_long   PARTS_00_image[];
extern u_long   PARTS_00_clut[];
extern u_long   PARTS_01_image[];
extern u_long   PARTS_01_clut[];
extern u_long   GUN02G_image[];
extern u_long   GUN02G_clut[];
extern u_long   GUN04G_image[];
extern u_long   GUN04G_clut[];
extern u_long   DON01G_image[];
extern u_long   DON01G_clut[];



extern u_long   BAKU01A_image[];
extern u_long   BAKU01A_clut[];
extern u_long   BAKU01B_image[];
extern u_long   BAKU01B_clut[];
extern u_long   BG02A_image[];
extern u_long   BG02A_clut[];
extern u_long   BG02B_image[];
extern u_long   BG02B_clut[];
extern u_long   BG02C_image[];
extern u_long   BG02C_clut[];
extern u_long   BG02D_image[];
extern u_long   BG02D_clut[];
extern u_long   DON01_image[];
extern u_long   DON01_clut[];
extern u_long   DON03E_image[];
extern u_long   DON03E_clut[];
extern u_long   GUN01_image[];
extern u_long   GUN01_clut[];
extern u_long   GUN02_image[];
extern u_long   GUN02_clut[];
extern u_long   GUN04_image[];
extern u_long   GUN04_clut[];
extern u_long   DON02E_image[];
extern u_long   DON02E_clut[];


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


//-----------------------------------------------------------------------------
//  variable
//-----------------------------------------------------------------------------
//----ゲームデータ
static MAZE_GAME MGameMgr;

//----ゲームテクスチャファイル情報
static TIMD MazeGameTextureFile[] = {
    //  デモタイトル名、    BINファイル名
    {   "RCUBE3",           "\\TIM\\MAZEGD.B;1"},
};

//----イベントテクスチャファイル情報
static TIMD MazeEventTextureFile[] = {
    //  デモタイトル名、    BINファイル名
    {   "RCUBE2",           "\\TIM\\MAZEED.B;1"},
};


//----ゲームテクスチャイメージ
static GsIMAGE MazeGameTextureImage[]=
{
    //color             tpos        size        image           pos         size    clut
    {   TIM_COLOR_16,   384,0,      64,256,     font_image,     16,480,     16,6,   font_clut       },
    {   TIM_COLOR_16,   448,0,      64,256,     YorN_image,     0,480,      16,16,  YorN_clut       },
    {   TIM_COLOR_16,   512,0,      64,256,     help_00_image,  0,496,      16,2,   help_00_clut    },
    {   TIM_COLOR_16,   320,0,      64,256,     MMENU_image,    16,489,     16,7,   MMENU_clut      },
    {   TIM_COLOR_16,   640,0,      64,256,     BG01A_image,    64,481,     16,1,   BG01A_clut      },  //BG01A.TIM
    {   TIM_COLOR_16,   480,256,    16,256,     BG01B_image,    48,480,     16,1,   BG01B_clut      },  //BG01B.TIM
    {   TIM_COLOR_256,  320,256,    128,256,    BG03A_image,    64,498,     256,1,  BG03A_clut      },  //BG03A.TIM
    {   TIM_COLOR_256,  448,256,    32,256,     BG03B_image,    64,497,     256,1,  BG03B_clut      },  //BG03B.TIM
    {   TIM_COLOR_16,   704,0,      64,256,     DON02_image,    48,484,     16,7,   DON02_clut      },  //DON02.TIM
    {   TIM_COLOR_16,   512,256,    64,256,     DON03_image,    64,482,     16,1,   DON03_clut      },  //DON03.TIM
    {   TIM_COLOR_16,   768,0,      64,256,     DON04_image,    48,481,     16,3,   DON04_clut      },  //DON04.TIM
    {   TIM_COLOR_16,   832,0,      64,256,     GUN03_image,    64,480,     16,1,   GUN03_clut      },  //GUN03.TIM
    {   TIM_COLOR_16,   576,0,      64,256,     PARTS_00_image, 80,480,     16,9,   PARTS_00_clut   },  //PARTS_00.TIM
    {   TIM_COLOR_16,   496,256,    16,24,      PARTS_01_image, 80,489,     16,2,   PARTS_01_clut   },  //PARTS_01.TIM
    {   TIM_COLOR_16,   640,256,    64,256,     GUN02G_image,   64,485,      16,1,  GUN02G_clut     },  //GUN02.TIM
    {   TIM_COLOR_16,   576,256,    64,256,     GUN04G_image,   64,483,      16,2,  GUN04G_clut     },  //GUN04.TIM
    {   TIM_COLOR_16,   704,256,    64,256,     DON01G_image,   64,486,      16,3,  DON01G_clut     },  //DON01G.TIM
};


//----イベントテクスチャイメージ
static GsIMAGE MazeEventTextureImage[]=
{
    //color             tpos        size        image           pos         size    clut
    {   TIM_COLOR_16,   384,0,      64,256,     font_image,     16,480,     16,6,   font_clut       },
    {   TIM_COLOR_16,   448,0,      64,256,     YorN_image,     0,480,      16,16,  YorN_clut       },
    {   TIM_COLOR_16,   512,0,      64,256,     help_00_image,  0,496,      16,2,   help_00_clut    },
    {   TIM_COLOR_16,   320,0,      64,256,     MMENU_image,    16,489,     16,7,   MMENU_clut      },
    {   TIM_COLOR_16,   576,0,      64,256,     BAKU01A_image,  32,489,     16,1,   BAKU01A_clut    },  //BAKU01A.TIM
    {   TIM_COLOR_16,   640,0,      64,256,     BAKU01B_image,  32,480,     16,1,   BAKU01B_clut    },  //BAKU01B.TIM
    {   TIM_COLOR_256,  320,256,    128,256,    BG02A_image,    0,500,      256,1,  BG02A_clut      },  //BG02A.TIM
    {   TIM_COLOR_256,  448,256,    32,256,     BG02B_image,    0,501,      256,1,  BG02B_clut      },  //BG02B.TIM
    {   TIM_COLOR_256,  704,0,      128,47,     BG02C_image,    0,502,      256,1,  BG02C_clut      },  //BG02C.TIM
    {   TIM_COLOR_256,  480,256,    32,47,      BG02D_image,    0,503,      256,1,  BG02D_clut      },  //BG02D.TIM
    {   TIM_COLOR_16,   512,256,    64,256,     DON01_image,    32,481,     16,3,   DON01_clut      },  //DON01.TIM
    {   TIM_COLOR_16,   768,256,    64,256,     DON03E_image,   32,490,     16,1,   DON03E_clut     },  //DON03E.TIM
    {   TIM_COLOR_16,   640,256,    64,256,     GUN01_image,    32,486,     16,2,   GUN01_clut      },  //GUN01.TIM
    {   TIM_COLOR_16,   704,256,    64,256,     GUN02_image,    32,488,     16,1,   GUN02_clut      },  //GUN02.TIM
    {   TIM_COLOR_16,   576,256,    64,256,     GUN04_image,    32,484,     16,2,   GUN04_clut      },  //GUN04.TIM
    {   TIM_COLOR_16,   832,256,    64,256,     DON02E_image,   48,480,     16,7,   DON02E_clut     },  //DON02.TIM
};



//----ゲーム部スプライト登録データ
static ENTRY_SPRITE_DATA MazeGameSpriteData[]=
{
    //---------------------------------------------------------------------------
    //  TexNo                       TimLX   TimLY   Height  Width   PalNo
    //---------------------------------------------------------------------------[BG01A.TIM]
    {   TIM_POS_MAZE_GAME_BG01A,    0,      0,      240,    256,    0   },      //背景１
    //---------------------------------------------------------------------------[BG01B.TIM]
    {   TIM_POS_MAZE_GAME_BG01B,    0,      0,      240,    64,     0   },      //背景2
    //---------------------------------------------------------------------------[BG03A.TIM]
    {   TIM_POS_MAZE_GAME_BG03A,    0,      0,      240,    256,    0   },      //背景１
    //---------------------------------------------------------------------------[BG03B.TIM]
    {   TIM_POS_MAZE_GAME_BG03B,    0,      0,      240,    64,     0   },      //背景2
    //---------------------------------------------------------------------------[DON02.TIM]
    {   TIM_POS_MAZE_GAME_DON02,    0,      0,      144,    133,    0   },      //登場２
    {   TIM_POS_MAZE_GAME_DON02,    134,    0,      12,     37,     0   },      //口
    {   TIM_POS_MAZE_GAME_DON02,    0,      144,    42,     48,     1   },      //団長00アニメ
    {   TIM_POS_MAZE_GAME_DON02,    48,     144,    42,     48,     1   },      //団長01アニメ
    {   TIM_POS_MAZE_GAME_DON02,    0,      186,    33,     40,     1   },      //楽団員A00アニメ(青風船時)
    {   TIM_POS_MAZE_GAME_DON02,    0,      186,    33,     40,     2   },      //楽団員A00アニメ(橙風船時)
    {   TIM_POS_MAZE_GAME_DON02,    40,     186,    33,     40,     1   },      //楽団員A01アニメ(青風船時)
    {   TIM_POS_MAZE_GAME_DON02,    40,     186,    33,     40,     2   },      //楽団員A01アニメ(橙風船時)
    {   TIM_POS_MAZE_GAME_DON02,    80,     186,    33,     40,     1   },      //楽団員B00アニメ
    {   TIM_POS_MAZE_GAME_DON02,    120,    186,    33,     40,     1   },      //楽団員B01アニメ
    {   TIM_POS_MAZE_GAME_DON02,    160,    186,    33,     40,     3   },      //楽団員C00アニメ
    {   TIM_POS_MAZE_GAME_DON02,    200,    186,    33,     40,     3   },      //楽団員C01アニメ
    {   TIM_POS_MAZE_GAME_DON02,    96,     144,    14,     20,     4   },      //レベル選択カーソル枠
    {   TIM_POS_MAZE_GAME_DON02,    96,     158,    9,      18,     4   },      //レベル選択用チップ
    {   TIM_POS_MAZE_GAME_DON02,    96,     158,    9,      18,     5   },      //レベル選択用チップ
    {   TIM_POS_MAZE_GAME_DON02,    96,     168,    10,     8,      6   },      //レベル表示数字”１”
    {   TIM_POS_MAZE_GAME_DON02,    104,    168,    10,     8,      6   },      //レベル表示数字”２”
    {   TIM_POS_MAZE_GAME_DON02,    112,    168,    10,     8,      6   },      //レベル表示数字”３”
    {   TIM_POS_MAZE_GAME_DON02,    120,    168,    10,     8,      6   },      //レベル表示数字”４”
    {   TIM_POS_MAZE_GAME_DON02,    128,    168,    10,     8,      6   },      //レベル表示数字”５”
    //---------------------------------------------------------------------------[DON03.TIM]
    {   TIM_POS_MAZE_GAME_DON03,    0,      0,      132,    140,    0   },      //登場３
    {   TIM_POS_MAZE_GAME_DON03,    0,      132,    30,     30,     0   },      //基本・小
    {   TIM_POS_MAZE_GAME_DON03,    30,     132,    30,     30,     0   },      //歩く下A
    {   TIM_POS_MAZE_GAME_DON03,    60,     132,    30,     30,     0   },      //歩く下B
    {   TIM_POS_MAZE_GAME_DON03,    90,     132,    30,     30,     0   },      //歩く上A
    {   TIM_POS_MAZE_GAME_DON03,    120,    132,    30,     30,     0   },      //歩く上B
    {   TIM_POS_MAZE_GAME_DON03,    150,    132,    30,     30,     0   },      //バンザイ１
    {   TIM_POS_MAZE_GAME_DON03,    180,    132,    30,     30,     0   },      //バンザイ２
    {   TIM_POS_MAZE_GAME_DON03,    210,    132,    30,     30,     0   },      //バンザイ３
    {   TIM_POS_MAZE_GAME_DON03,    0,      162,    30,     30,     0   },      //歩く右A
    {   TIM_POS_MAZE_GAME_DON03,    30,     162,    30,     30,     0   },      //歩く右B
    {   TIM_POS_MAZE_GAME_DON03,    60,     162,    30,     30,     0   },      //歩く左A
    {   TIM_POS_MAZE_GAME_DON03,    90,     162,    30,     30,     0   },      //歩く左B
    {   TIM_POS_MAZE_GAME_DON03,    120,    162,    30,     30,     0   },      //走る左A
    {   TIM_POS_MAZE_GAME_DON03,    150,    162,    30,     30,     0   },      //走る左B
    {   TIM_POS_MAZE_GAME_DON03,    180,    162,    30,     30,     0   },      //走る右A
    {   TIM_POS_MAZE_GAME_DON03,    210,    162,    30,     30,     0   },      //走る右B
    {   TIM_POS_MAZE_GAME_DON03,    0,      192,    30,     30,     0   },      //手振りA
    {   TIM_POS_MAZE_GAME_DON03,    30,     192,    30,     30,     0   },      //手振りB
    {   TIM_POS_MAZE_GAME_DON03,    60,     192,    30,     30,     0   },      //地団駄A
    {   TIM_POS_MAZE_GAME_DON03,    90,     192,    30,     30,     0   },      //地団駄B
    {   TIM_POS_MAZE_GAME_DON03,    120,    192,    30,     30,     0   },      //登場A
    {   TIM_POS_MAZE_GAME_DON03,    150,    192,    30,     30,     0   },      //登場B
    {   TIM_POS_MAZE_GAME_DON03,    180,    192,    30,     30,     0   },      //あかんべ
    {   TIM_POS_MAZE_GAME_DON03,    210,    192,    30,     30,     0   },      //グングン見る
    {   TIM_POS_MAZE_GAME_DON03,    0,      222,    30,     30,     0   },      //胸ドン
    {   TIM_POS_MAZE_GAME_DON03,    30,     222,    19,     35,     0   },      //じたばたA
    {   TIM_POS_MAZE_GAME_DON03,    65,     222,    19,     35,     0   },      //じたばたB
    //---------------------------------------------------------------------------[DON04.TIM]
    {   TIM_POS_MAZE_GAME_DON04,    0,      0,      144,    133,    0   },      //登場１
    {   TIM_POS_MAZE_GAME_DON04,    0,      144,    33,     30,     1   },      //歩く左A
    {   TIM_POS_MAZE_GAME_DON04,    30,     144,    33,     30,     1   },      //歩く左B
    {   TIM_POS_MAZE_GAME_DON04,    60,     144,    33,     30,     1   },      //歩く右A
    {   TIM_POS_MAZE_GAME_DON04,    90,     144,    33,     30,     1   },      //歩く右B
    {   TIM_POS_MAZE_GAME_DON04,    120,    144,    33,     30,     1   },      //歩く下A
    {   TIM_POS_MAZE_GAME_DON04,    150,    144,    33,     30,     1   },      //歩く下B
    {   TIM_POS_MAZE_GAME_DON04,    180,    144,    33,     30,     1   },      //歩く上A
    {   TIM_POS_MAZE_GAME_DON04,    210,    144,    33,     30,     1   },      //歩く上B
    {   TIM_POS_MAZE_GAME_DON04,    0,      177,    31,     32,     1   },      //バンザイA
    {   TIM_POS_MAZE_GAME_DON04,    32,     177,    31,     32,     1   },      //バンザイB
    {   TIM_POS_MAZE_GAME_DON04,    64,     177,    31,     32,     1   },      //手振り１A
    {   TIM_POS_MAZE_GAME_DON04,    96,     177,    31,     32,     1   },      //手振り１B
    {   TIM_POS_MAZE_GAME_DON04,    128,    177,    31,     32,     1   },      //手振り２B
    {   TIM_POS_MAZE_GAME_DON04,    160,    177,    31,     32,     1   },      //手振り２B
    {   TIM_POS_MAZE_GAME_DON04,    192,    177,    31,     32,     1   },      //ガッツA
    {   TIM_POS_MAZE_GAME_DON04,    224,    177,    31,     32,     1   },      //ガッツB
    {   TIM_POS_MAZE_GAME_DON04,    0,      207,    40,     40,     2   },      //グングン左
    {   TIM_POS_MAZE_GAME_DON04,    40,     207,    40,     40,     2   },      //グングン上
    {   TIM_POS_MAZE_GAME_DON04,    80,     207,    40,     40,     2   },      //グングン右
    {   TIM_POS_MAZE_GAME_DON04,    120,    207,    40,     40,     2   },      //グングン下
    //---------------------------------------------------------------------------[GUN03.TIM]
    {   TIM_POS_MAZE_GAME_GUN03,    0,      0,      127,    113,    0   },      //登場
    {   TIM_POS_MAZE_GAME_GUN03,    113,    0,      134,    109,    0   },      //登場縦長
    {   TIM_POS_MAZE_GAME_GUN03,    0,      127,    121,    124,    0   },      //登場横長
    //---------------------------------------------------------------------------[PARTS_00.TIM]
    {   TIM_POS_MAZE_GAME_PARTS_00, 0,      0,      26,     32,     0   },      //出題の数字”０”
    {   TIM_POS_MAZE_GAME_PARTS_00, 32,     0,      26,     32,     0   },      //出題の数字”１”
    {   TIM_POS_MAZE_GAME_PARTS_00, 64,     0,      26,     32,     0   },      //出題の数字”２”
    {   TIM_POS_MAZE_GAME_PARTS_00, 96,     0,      26,     32,     0   },      //出題の数字”３”
    {   TIM_POS_MAZE_GAME_PARTS_00, 128,    0,      26,     32,     0   },      //出題の数字”４”
    {   TIM_POS_MAZE_GAME_PARTS_00, 160,    0,      26,     32,     0   },      //出題の数字”５”
    {   TIM_POS_MAZE_GAME_PARTS_00, 192,    0,      26,     32,     0   },      //出題の数字”６”
    {   TIM_POS_MAZE_GAME_PARTS_00, 224,    0,      26,     32,     0   },      //出題の数字”７”
    {   TIM_POS_MAZE_GAME_PARTS_00, 0,      26,     26,     32,     0   },      //出題の数字”８”
    {   TIM_POS_MAZE_GAME_PARTS_00, 32,     26,     26,     32,     0   },      //出題の数字”９”
    {   TIM_POS_MAZE_GAME_PARTS_00, 64,     26,     26,     32,     0   },      //出題の数字”１０”
    {   TIM_POS_MAZE_GAME_PARTS_00, 96,     26,     26,     32,     0   },      //出題の”？”マーク
    {   TIM_POS_MAZE_GAME_PARTS_00, 128,    26,     26,     32,     0   },      //出題の”と”
    {   TIM_POS_MAZE_GAME_PARTS_00, 160,    26,     26,     32,     0   },      //出題の”は”
    {   TIM_POS_MAZE_GAME_PARTS_00, 0,      52,     19,     21,     1   },      //答えの数字ボール”０”
    {   TIM_POS_MAZE_GAME_PARTS_00, 22,     52,     19,     21,     1   },      //答えの数字ボール”１”
    {   TIM_POS_MAZE_GAME_PARTS_00, 44,     52,     19,     21,     1   },      //答えの数字ボール”２”
    {   TIM_POS_MAZE_GAME_PARTS_00, 66,     52,     19,     21,     1   },      //答えの数字ボール”３”
    {   TIM_POS_MAZE_GAME_PARTS_00, 88,     52,     19,     21,     1   },      //答えの数字ボール”４”
    {   TIM_POS_MAZE_GAME_PARTS_00, 110,    52,     19,     21,     1   },      //答えの数字ボール”５”
    {   TIM_POS_MAZE_GAME_PARTS_00, 132,    52,     19,     21,     1   },      //答えの数字ボール”６”
    {   TIM_POS_MAZE_GAME_PARTS_00, 154,    52,     19,     21,     1   },      //答えの数字ボール”７”
    {   TIM_POS_MAZE_GAME_PARTS_00, 176,    52,     19,     21,     1   },      //答えの数字ボール”８”
    {   TIM_POS_MAZE_GAME_PARTS_00, 198,    52,     19,     21,     1   },      //答えの数字ボール”９”
    {   TIM_POS_MAZE_GAME_PARTS_00, 220,    52,     19,     21,     1   },      //答えの数字ボール”１０”
    {   TIM_POS_MAZE_GAME_PARTS_00, 0,      71,     20,     20,     2   },      //矢印 左・灰色
    {   TIM_POS_MAZE_GAME_PARTS_00, 20,     71,     20,     20,     2   },      //矢印 上・灰色
    {   TIM_POS_MAZE_GAME_PARTS_00, 40,     71,     20,     20,     2   },      //矢印 右・灰色
    {   TIM_POS_MAZE_GAME_PARTS_00, 60,     71,     20,     20,     2   },      //矢印 下・灰色
    {   TIM_POS_MAZE_GAME_PARTS_00, 80,     71,     20,     20,     2   },      //矢印 左・赤
    {   TIM_POS_MAZE_GAME_PARTS_00, 100,    71,     20,     20,     2   },      //矢印 上・赤
    {   TIM_POS_MAZE_GAME_PARTS_00, 120,    71,     20,     20,     2   },      //矢印 右・赤
    {   TIM_POS_MAZE_GAME_PARTS_00, 140,    71,     20,     20,     2   },      //矢印 下・赤
    {   TIM_POS_MAZE_GAME_PARTS_00, 150,    91,     21,     23,     3   },      //煙幕大
    {   TIM_POS_MAZE_GAME_PARTS_00, 174,    91,     14,     15,     3   },      //煙幕小
    {   TIM_POS_MAZE_GAME_PARTS_00, 0,      117,    23,     23,     4   },      //柵    A
    {   TIM_POS_MAZE_GAME_PARTS_00, 24,     117,    23,     23,     4   },      //柵    B
    {   TIM_POS_MAZE_GAME_PARTS_00, 48,     117,    15,     14,     4   },      //星小
    {   TIM_POS_MAZE_GAME_PARTS_00, 62,     117,    15,     18,     4   },      //蜂左
    {   TIM_POS_MAZE_GAME_PARTS_00, 80,     117,    15,     18,     4   },      //蜂右
    {   TIM_POS_MAZE_GAME_PARTS_00, 0,      91,     20,     24,     8   },      //星大
    {   TIM_POS_MAZE_GAME_PARTS_00, 0,      160,    31,     40,     7   },      //左向き矢印
    {   TIM_POS_MAZE_GAME_PARTS_00, 40,     160,    31,     40,     7   },      //右向き矢印
    {   TIM_POS_MAZE_GAME_PARTS_00, 80,     160,    20,     22,     7   },      //グングン・左顔00アニメ
    {   TIM_POS_MAZE_GAME_PARTS_00, 102,    160,    20,     22,     7   },      //グングン・左顔00アニメ
    {   TIM_POS_MAZE_GAME_PARTS_00, 124,    160,    20,     22,     7   },      //グングン・右顔00アニメ
    {   TIM_POS_MAZE_GAME_PARTS_00, 146,    160,    20,     22,     7   },      //グングン・右顔00アニメ
    {   TIM_POS_MAZE_GAME_PARTS_00, 0,      140,    18,     20,     6   },      //グングンマーク
    //---------------------------------------------------------------------------[PARTS_01.TIM]
    {   TIM_POS_MAZE_GAME_PARTS_01, 3,      0,      24,     28,     0   },      //赤岩
    {   TIM_POS_MAZE_GAME_PARTS_01, 33,     0,      24,     28,     1   },      //青岩
    //-----------------------------------------------------------------------------------------[GUN02.TIM]
    {   TIM_POS_MAZE_GAME_GUN02G,   0,      0,      169,    140,    0   },      //ぼろ２（ぼろ１と一緒にアニメー　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　ションお願いします。）
    {   TIM_POS_MAZE_GAME_GUN02G,   140,    0,      81,     111,    0   },      //胴
    {   TIM_POS_MAZE_GAME_GUN02G,   148,    81,     67,     100,    0   },      //頭正面
    {   TIM_POS_MAZE_GAME_GUN02G,   160,    148,    72,     96,     0   },      //頭傾
    {   TIM_POS_MAZE_GAME_GUN02G,   50,     169,    51,     45,     0   },      //片手上げ上
    {   TIM_POS_MAZE_GAME_GUN02G,   96,     169,    31,     46,     0   },      //片手上げ横
    {   TIM_POS_MAZE_GAME_GUN02G,   0,      169,    21,     50,     0   },      //口正面・開
    {   TIM_POS_MAZE_GAME_GUN02G,   0,      190,    21,     50,     0   },      //口正面・閉
    {   TIM_POS_MAZE_GAME_GUN02G,   0,      211,    21,     50,     0   },      //口傾・開
    {   TIM_POS_MAZE_GAME_GUN02G,   0,      232,    21,     50,     0   },      //口傾・閉
    //-----------------------------------------------------------------------------------------[GUN04.TIM]
    {   TIM_POS_MAZE_GAME_GUN04G,   0,      0,      131,    92,     0   },      //バンザイ胴・頭
    {   TIM_POS_MAZE_GAME_GUN04G,   0,      131,    49,     40,     0   },      //バンザイ上腕L
    {   TIM_POS_MAZE_GAME_GUN04G,   40,     131,    49,     40,     0   },      //バンザイ上腕R
    {   TIM_POS_MAZE_GAME_GUN04G,   0,      180,    27,     44,     0   },      //バンザイ横腕L
    {   TIM_POS_MAZE_GAME_GUN04G,   0,      207,    27,     44,     0   },      //バンザイ横腕R
    {   TIM_POS_MAZE_GAME_GUN04G,   0,      234,    18,     48,     0   },      //バンザイ口・開
    {   TIM_POS_MAZE_GAME_GUN04G,   92,     0,      146,    126,    0   },      //ジャンプ本体
    {   TIM_POS_MAZE_GAME_GUN04G,   80,     146,    10,     48,     0   },      //ジャンプ口・閉
    {   TIM_POS_MAZE_GAME_GUN04G,   80,     156,    14,     26,     0   },      //ジャンプ口・開
    {   TIM_POS_MAZE_GAME_GUN04G,   80,     170,    26,     97,     1   },      //大
    {   TIM_POS_MAZE_GAME_GUN04G,   178,    170,    17,     51,     1   },      //小
    //-----------------------------------------------------------------------------------------[DON01G.TIM]
    {   TIM_POS_MAZE_GAME_GUN01G,   0,      144,    68,     94,     0   },      //胴体
    {   TIM_POS_MAZE_GAME_GUN01G,   94,     144,    66,     78,     0   },      //頭A
    {   TIM_POS_MAZE_GAME_GUN01G,   172,    144,    69,     78,     0   },      //頭B
    {   TIM_POS_MAZE_GAME_GUN01G,   0,      213,    40,     30,     0   },      //ガッツ1腕L
    {   TIM_POS_MAZE_GAME_GUN01G,   30,     213,    40,     30,     0   },      //ガッツ1腕R
    {   TIM_POS_MAZE_GAME_GUN01G,   60,     213,    36,     34,     0   },      //登場腕L
    {   TIM_POS_MAZE_GAME_GUN01G,   94,     213,    36,     34,     0   },      //登場腕R
    {   TIM_POS_MAZE_GAME_GUN01G,   128,    213,    32,     30,     0   },      //見る腕L
    {   TIM_POS_MAZE_GAME_GUN01G,   158,    213,    32,     30,     0   },      //見る腕R
    {   TIM_POS_MAZE_GAME_GUN01G,   134,    0,      42,     26,     0   },      //基本腕L
    {   TIM_POS_MAZE_GAME_GUN01G,   160,    0,      42,     26,     0   },      //基本腕R
    {   TIM_POS_MAZE_GAME_GUN01G,   186,    0,      56,     34,     0   },      //ガッツ２腕L
    {   TIM_POS_MAZE_GAME_GUN01G,   220,    0,      56,     34,     0   },      //ガッツ２腕R
    {   TIM_POS_MAZE_GAME_GUN01G,   134,    56,     34,     40,     0   },      //あかんべ腕L
    {   TIM_POS_MAZE_GAME_GUN01G,   174,    56,     46,     67,     0   },      //あかんべ腕R
    //-----------------------------------------------------------------------------------------
    {   ENTRY_SPRITE_DATA_END,0,0,0,0,0 }   // データエンド
};


//----イベント部スプライト登録データ
static ENTRY_SPRITE_DATA MazeEventSpriteData[]=
{
    //-----------------------------------------------------------------------------------------
    //  TexNo                       TimLX   TimLY   Height  Width   PalNo
    //-----------------------------------------------------------------------------------------[BAKU01A.TIM]
    {   TIM_POS_MAZE_EVENT_BAKU01A, 0,      0,      199,    256,    0   },      //ゲーム後の効果画像
    //-----------------------------------------------------------------------------------------[BG01B.TIM]
    {   TIM_POS_MAZE_EVENT_BAKU01B, 0,      0,      199,    50,     0   },      //爆発大の続き
    {   TIM_POS_MAZE_EVENT_BAKU01B, 50,     0,      154,    206,    0   },      //爆発・中
    {   TIM_POS_MAZE_EVENT_BAKU01B, 50,     154,    82,     107,    0   },      //爆発・小
    //-----------------------------------------------------------------------------------------[BG02A.TIM]
    {   TIM_POS_MAZE_EVENT_BG02A,   0,      0,      240,    256,    0   },      //背景１
    //-----------------------------------------------------------------------------------------[BG02B.TIM]
    {   TIM_POS_MAZE_EVENT_BG02B,   256,    0,      240,    64,     0   },      //背景2
    //-----------------------------------------------------------------------------------------[BG02C.TIM]
    {   TIM_POS_MAZE_EVENT_BG02C,   0,      0,      47,     256,    0   },      //背景１（BG02の上の画像）
    //-----------------------------------------------------------------------------------------[BG02D.TIM]
    {   TIM_POS_MAZE_EVENT_BG02D,   256,    0,      47,     64,     0   },      //背景2（BG02の上の画像）
    //-----------------------------------------------------------------------------------------[DON01.TIM]
    {   TIM_POS_MAZE_EVENT_DON01,   0,      144,    68,     94,     0   },      //胴体
    {   TIM_POS_MAZE_EVENT_DON01,   94,     144,    66,     78,     0   },      //頭A
    {   TIM_POS_MAZE_EVENT_DON01,   172,    144,    69,     78,     0   },      //頭B
    {   TIM_POS_MAZE_EVENT_DON01,   0,      213,    40,     30,     0   },      //ガッツ1腕L
    {   TIM_POS_MAZE_EVENT_DON01,   30,     213,    40,     30,     0   },      //ガッツ1腕R
    {   TIM_POS_MAZE_EVENT_DON01,   60,     213,    36,     34,     0   },      //登場腕L
    {   TIM_POS_MAZE_EVENT_DON01,   94,     213,    36,     34,     0   },      //登場腕R
    {   TIM_POS_MAZE_EVENT_DON01,   128,    213,    32,     30,     0   },      //見る腕L
    {   TIM_POS_MAZE_EVENT_DON01,   158,    213,    32,     30,     0   },      //見る腕R
    {   TIM_POS_MAZE_EVENT_DON01,   134,    0,      42,     26,     0   },      //基本腕L
    {   TIM_POS_MAZE_EVENT_DON01,   160,    0,      42,     26,     0   },      //基本腕R
    {   TIM_POS_MAZE_EVENT_DON01,   186,    0,      56,     34,     0   },      //ガッツ２腕L
    {   TIM_POS_MAZE_EVENT_DON01,   220,    0,      56,     34,     0   },      //ガッツ２腕R
    {   TIM_POS_MAZE_EVENT_DON01,   134,    56,     34,     40,     0   },      //あかんべ腕L
    {   TIM_POS_MAZE_EVENT_DON01,   174,    56,     46,     67,     0   },      //あかんべ腕R
    //-----------------------------------------------------------------------------------------[DON03E.TIM]
    {   TIM_POS_MAZE_EVENT_DON03E,  0,      0,      132,    140,    0   },      //登場３
    {   TIM_POS_MAZE_EVENT_DON03E,  0,      132,    30,     30,     0   },      //基本・小
    {   TIM_POS_MAZE_EVENT_DON03E,  30,     132,    30,     30,     0   },      //歩く下A
    {   TIM_POS_MAZE_EVENT_DON03E,  60,     132,    30,     30,     0   },      //歩く下B
    {   TIM_POS_MAZE_EVENT_DON03E,  90,     132,    30,     30,     0   },      //歩く上A
    {   TIM_POS_MAZE_EVENT_DON03E,  120,    132,    30,     30,     0   },      //歩く上B
    {   TIM_POS_MAZE_EVENT_DON03E,  150,    132,    30,     30,     0   },      //バンザイ１
    {   TIM_POS_MAZE_EVENT_DON03E,  180,    132,    30,     30,     0   },      //バンザイ２
    {   TIM_POS_MAZE_EVENT_DON03E,  210,    132,    30,     30,     0   },      //バンザイ３
    {   TIM_POS_MAZE_EVENT_DON03E,  0,      162,    30,     30,     0   },      //歩く右A
    {   TIM_POS_MAZE_EVENT_DON03E,  30,     162,    30,     30,     0   },      //歩く右B
    {   TIM_POS_MAZE_EVENT_DON03E,  60,     162,    30,     30,     0   },      //歩く左A
    {   TIM_POS_MAZE_EVENT_DON03E,  90,     162,    30,     30,     0   },      //歩く左B
    {   TIM_POS_MAZE_EVENT_DON03E,  120,    162,    30,     30,     0   },      //走る左A
    {   TIM_POS_MAZE_EVENT_DON03E,  150,    162,    30,     30,     0   },      //走る左B
    {   TIM_POS_MAZE_EVENT_DON03E,  180,    162,    30,     30,     0   },      //走る右A
    {   TIM_POS_MAZE_EVENT_DON03E,  210,    162,    30,     30,     0   },      //走る右B
    {   TIM_POS_MAZE_EVENT_DON03E,  0,      192,    30,     30,     0   },      //手振りA
    {   TIM_POS_MAZE_EVENT_DON03E,  30,     192,    30,     30,     0   },      //手振りB
    {   TIM_POS_MAZE_EVENT_DON03E,  60,     192,    30,     30,     0   },      //地団駄A
    {   TIM_POS_MAZE_EVENT_DON03E,  90,     192,    30,     30,     0   },      //地団駄B
    {   TIM_POS_MAZE_EVENT_DON03E,  120,    192,    30,     30,     0   },      //登場A
    {   TIM_POS_MAZE_EVENT_DON03E,  150,    192,    30,     30,     0   },      //登場B
    {   TIM_POS_MAZE_EVENT_DON03E,  180,    192,    30,     30,     0   },      //あかんべ
    {   TIM_POS_MAZE_EVENT_DON03E,  210,    192,    30,     30,     0   },      //グングン見る
    {   TIM_POS_MAZE_EVENT_DON03E,  0,      222,    30,     30,     0   },      //胸ドン
    {   TIM_POS_MAZE_EVENT_DON03E,  30,     222,    19,     35,     0   },      //じたばたA
    {   TIM_POS_MAZE_EVENT_DON03E,  65,     222,    19,     35,     0   },      //じたばたB
    //-----------------------------------------------------------------------------------------[GUN01.TIM]
    {   TIM_POS_MAZE_EVENT_GUN01,   0,      0,      151,    152,    0   },      //ぼろ１
    {   TIM_POS_MAZE_EVENT_GUN01,   152,    0,      60,     52,     0   },      //地団駄A
    {   TIM_POS_MAZE_EVENT_GUN01,   204,    0,      60,     52,     0   },      //地団駄B
    {   TIM_POS_MAZE_EVENT_GUN01,   0,      160,    57,     60,     1   },      //地団駄１
    {   TIM_POS_MAZE_EVENT_GUN01,   60,     160,    57,     60,     1   },      //地団駄２
    {   TIM_POS_MAZE_EVENT_GUN01,   120,    160,    57,     60,     1   },      //バンザイ１
    {   TIM_POS_MAZE_EVENT_GUN01,   180,    160,    57,     60,     1   },      //バンザイ２
    {   TIM_POS_MAZE_EVENT_GUN01,   180,    103,    57,     60,     1   },      //バンザイ３
    //-----------------------------------------------------------------------------------------[GUN02.TIM]
    {   TIM_POS_MAZE_EVENT_GUN02,   0,      0,      169,    140,    0   },      //ぼろ２（ぼろ１と一緒にアニメー　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　ションお願いします。）
    {   TIM_POS_MAZE_EVENT_GUN02,   140,    0,      81,     111,    0   },      //胴
    {   TIM_POS_MAZE_EVENT_GUN02,   148,    81,     67,     100,    0   },      //頭正面
    {   TIM_POS_MAZE_EVENT_GUN02,   160,    148,    72,     96,     0   },      //頭傾
    {   TIM_POS_MAZE_EVENT_GUN02,   50,     169,    51,     45,     0   },      //片手上げ上
    {   TIM_POS_MAZE_EVENT_GUN02,   96,     169,    31,     46,     0   },      //片手上げ横
    {   TIM_POS_MAZE_EVENT_GUN02,   0,      169,    21,     50,     0   },      //口正面・開
    {   TIM_POS_MAZE_EVENT_GUN02,   0,      190,    21,     50,     0   },      //口正面・閉
    {   TIM_POS_MAZE_EVENT_GUN02,   0,      211,    21,     50,     0   },      //口傾・開
    {   TIM_POS_MAZE_EVENT_GUN02,   0,      232,    21,     50,     0   },      //口傾・閉
    //-----------------------------------------------------------------------------------------[GUN04.TIM]
    {   TIM_POS_MAZE_EVENT_GUN04,   0,      0,      131,    92,     0   },      //バンザイ胴・頭
    {   TIM_POS_MAZE_EVENT_GUN04,   0,      131,    49,     40,     0   },      //バンザイ上腕L
    {   TIM_POS_MAZE_EVENT_GUN04,   40,     131,    49,     40,     0   },      //バンザイ上腕R
    {   TIM_POS_MAZE_EVENT_GUN04,   0,      180,    27,     44,     0   },      //バンザイ横腕L
    {   TIM_POS_MAZE_EVENT_GUN04,   0,      207,    27,     44,     0   },      //バンザイ横腕R
    {   TIM_POS_MAZE_EVENT_GUN04,   0,      234,    18,     48,     0   },      //バンザイ口・開
    {   TIM_POS_MAZE_EVENT_GUN04,   92,     0,      146,    126,    0   },      //ジャンプ本体
    {   TIM_POS_MAZE_EVENT_GUN04,   80,     146,    10,     48,     0   },      //ジャンプ口・閉
    {   TIM_POS_MAZE_EVENT_GUN04,   80,     156,    14,     26,     0   },      //ジャンプ口・開
    {   TIM_POS_MAZE_EVENT_GUN04,   80,     170,    26,     97,     1   },      //大
    {   TIM_POS_MAZE_EVENT_GUN04,   178,    170,    17,     51,     1   },      //小
    //-----------------------------------------------------------------------------------------[YorNo.TIM]
    {   TIM_POS_MAZE_EVENT_YORNO,   0,      0,      115,    186,    0   },      //プレート
    {   TIM_POS_MAZE_EVENT_YORNO,   0,      115,    40,     38,     1   },      //非選択・はい 74,57
    {   TIM_POS_MAZE_EVENT_YORNO,   38,     115,    40,     44,     1   },      //非選択・いいえ 126,57
    {   TIM_POS_MAZE_EVENT_YORNO,   82,     115,    40,     44,     2   },      //選択・はい 72,57
    {   TIM_POS_MAZE_EVENT_YORNO,   126,    115,    40,     44,     2   },      //選択・いいえ 126,57
    {   TIM_POS_MAZE_EVENT_YORNO,   186,    0,      69,     58,     3   },      //プーぺ１
    {   TIM_POS_MAZE_EVENT_YORNO,   186,    69,     69,     58,     3   },      //プーぺ２
    {   TIM_POS_MAZE_EVENT_YORNO,   0,      155,    14,     148,    4   },      //もういちど
    {   TIM_POS_MAZE_EVENT_YORNO,   0,      170,    14,     148,    4   },      //おわり
    {   TIM_POS_MAZE_EVENT_YORNO,   20,     20,     14,     148,    4   },      //つづけ
    //-----------------------------------------------------------------------------------------[font.TIM]
    {   TIM_POS_MAZE_EVENT_FONT,    24,     200,    24,     26,     2   },      //指カーソル
    {   TIM_POS_MAZE_EVENT_FONT,    0,      232,    15,     52,     4   },      //えらぶ
    {   TIM_POS_MAZE_EVENT_FONT,    52,     232,    15,     52,     4   },      //けってい
    {   TIM_POS_MAZE_EVENT_FONT,    104,    232,    15,     52,     4   },      //めにゅー
    //---------------------------------------------------------------------------[DON02.TIM]
    {   TIM_POS_MAZE_EVENT_DON02E,  0,      0,      144,    133,    0   },      //登場２
    {   TIM_POS_MAZE_EVENT_DON02E,  134,    0,      12,     37,     0   },      //口
    {   TIM_POS_MAZE_EVENT_DON02E,  0,      144,    42,     48,     1   },      //団長00アニメ
    {   TIM_POS_MAZE_EVENT_DON02E,  48,     144,    42,     48,     1   },      //団長01アニメ
    {   TIM_POS_MAZE_EVENT_DON02E,  0,      186,    33,     40,     1   },      //楽団員A00アニメ(青風船時)
    {   TIM_POS_MAZE_EVENT_DON02E,  0,      186,    33,     40,     2   },      //楽団員A00アニメ(橙風船時)
    {   TIM_POS_MAZE_EVENT_DON02E,  40,     186,    33,     40,     1   },      //楽団員A01アニメ(青風船時)
    {   TIM_POS_MAZE_EVENT_DON02E,  40,     186,    33,     40,     2   },      //楽団員A01アニメ(橙風船時)
    {   TIM_POS_MAZE_EVENT_DON02E,  80,     186,    33,     40,     1   },      //楽団員B00アニメ
    {   TIM_POS_MAZE_EVENT_DON02E,  120,    186,    33,     40,     1   },      //楽団員B01アニメ
    {   TIM_POS_MAZE_EVENT_DON02E,  160,    186,    33,     40,     3   },      //楽団員C00アニメ
    {   TIM_POS_MAZE_EVENT_DON02E,  200,    186,    33,     40,     3   },      //楽団員C01アニメ
    {   TIM_POS_MAZE_EVENT_DON02E,  96,     144,    14,     20,     4   },      //レベル選択カーソル枠
    {   TIM_POS_MAZE_EVENT_DON02E,  96,     158,    9,      18,     4   },      //レベル選択用チップ
    {   TIM_POS_MAZE_EVENT_DON02E,  96,     158,    9,      18,     5   },      //レベル選択用チップ
    {   TIM_POS_MAZE_EVENT_DON02E,  96,     168,    10,     8,      6   },      //レベル表示数字”１”
    {   TIM_POS_MAZE_EVENT_DON02E,  104,    168,    10,     8,      6   },      //レベル表示数字”２”
    {   TIM_POS_MAZE_EVENT_DON02E,  112,    168,    10,     8,      6   },      //レベル表示数字”３”
    {   TIM_POS_MAZE_EVENT_DON02E,  120,    168,    10,     8,      6   },      //レベル表示数字”４”
    {   TIM_POS_MAZE_EVENT_DON02E,  128,    168,    10,     8,      6   },      //レベル表示数字”５”
    //-----------------------------------------------------------------------------------------
    {   ENTRY_SPRITE_DATA_END,0,0,0,0,0 }   // データエンド
};


//----マップデータ
static char InitMapData[MAZE_GAME_SQUARE_H_NUM+2][MAZE_GAME_SQUARE_W_NUM+2]=
{
//  { -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2 },
//  { -2, -1, -3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2 },
//  { -2, -3, -3, -1, -4, -1, -3, -1, -4, -1, -3, -1, -4, -1, -2 },
//  { -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2 },
//  { -2, -1, -4, -1, -3, -1, -4, -1, -3, -1, -4, -1, -3, -1, -2 },
//  { -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2 },
//  { -2, -1, -3, -1, -4, -1, -3, -1, -4, -1, -3, -1, -4, -1, -2 },
//  { -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2 },
//  { -2, -1, -4, -1, -3, -1, -4, -1, -3, -1, -4, -1, -3, -1, -2 },
//  { -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2 },
//  { -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2 },

    { -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2 },
    { -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2 },
    { -2, -1, -3, -1, -4, -1, -3, -1, -4, -1, -3, -1, -4, -1, -2 },
    { -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2 },
    { -2, -1, -4, -1, -3, -1, -4, -1, -3, -1, -4, -1, -3, -1, -2 },
    { -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2 },
    { -2, -1, -3, -1, -4, -1, -3, -1, -4, -1, -3, -1, -4, -1, -2 },
    { -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2 },
    { -2, -1, -4, -1, -3, -1, -4, -1, -3, -1, -4, -1, -3, -1, -2 },
    { -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2 },
    { -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2 },

};


//----グングンゲームスプライトテーブル
static MAZE_SPRITE_DATA GunGunGameSpriteTable[]=
{
    //------------------------------------------------------------
    //  SpriteNo                            ofx     ofy
    //------------------------------------------------------------
    {   MAZE_CHAR_GAME_SMOKE_01,            6,      12  },  //煙幕小
    {   MAZE_CHAR_GAME_SMOKE_00,            4,      10  },  //煙幕大
    {   MAZE_CHAR_GAME_GUNGUN_00,           0,      0   },  //左移動 00
    {   MAZE_CHAR_GAME_GUNGUN_01,           -1,     0   },  //左移動 01
    {   MAZE_CHAR_GAME_GUNGUN_02,           0,      0   },  //右移動 00
    {   MAZE_CHAR_GAME_GUNGUN_03,           1,      0   },  //右移動 01
    {   MAZE_CHAR_GAME_GUNGUN_04,           -1,     2   },  //下移動 00
    {   MAZE_CHAR_GAME_GUNGUN_05,           0,      2   },  //下移動 01
    {   MAZE_CHAR_GAME_GUNGUN_06,           0,      2   },  //上移動 00
    {   MAZE_CHAR_GAME_GUNGUN_07,           -1,     2   },  //上移動 01
    {   MAZE_CHAR_GAME_GUNGUN_08,           -2,     2   },  //クリア 00
    {   MAZE_CHAR_GAME_GUNGUN_09,           -2,     2   },  //クリア 01
    {   MAZE_CHAR_GAME_GUNGUN_10,           0,      0   },  //のアクション 
    {   MAZE_CHAR_GAME_GUNGUN_11,           0,      0   },  //のアクション 
    {   MAZE_CHAR_GAME_GUNGUN_12,           0,      0   },  //のアクション 
    {   MAZE_CHAR_GAME_GUNGUN_13,           0,      0   },  //のアクション 
    {   MAZE_CHAR_GAME_GUNGUN_14,           0,      0   },  //のアクション 
    {   MAZE_CHAR_GAME_GUNGUN_15,           0,      0   },  //のアクション 
    {   MAZE_CHAR_GAME_GUNGUN_CATCH_03,     -4,     0   },  //捕まる：クマ上
    {   MAZE_CHAR_GAME_GUNGUN_CATCH_03,     -4,     0   },  //捕まる：クマ上
    {   MAZE_CHAR_GAME_GUNGUN_CATCH_01,     -4,     0   },  //捕まる：クマ下
    {   MAZE_CHAR_GAME_GUNGUN_CATCH_01,     -4,     0   },  //捕まる：クマ下
    {   MAZE_CHAR_GAME_GUNGUN_CATCH_02,     0,      0   },  //捕まる：クマ左
    {   MAZE_CHAR_GAME_GUNGUN_CATCH_02,     0,      0   },  //捕まる：クマ左
    {   MAZE_CHAR_GAME_GUNGUN_CATCH_00,     0,      0   },  //捕まる：クマ右
    {   MAZE_CHAR_GAME_GUNGUN_CATCH_00,     0,      0   },  //捕まる：クマ右
};


//----クマゲームスプライトテーブル
static MAZE_SPRITE_DATA KumaGameSpriteTable[]=
{
    //------------------------------------------------------------
    //  SpriteNo                    ofx     ofy
    //------------------------------------------------------------
    {   MAZE_CHAR_GAME_SMOKE_01,    6,      12  },  //煙幕小
    {   MAZE_CHAR_GAME_SMOKE_00,    4,      10  },  //煙幕大
    {   MAZE_CHAR_GAME_KUMA_00,     0,      0   },  //クマ基本・小
    {   MAZE_CHAR_GAME_KUMA_01,     0,      0   },  //クマ歩く下A
    {   MAZE_CHAR_GAME_KUMA_02,     0,      0   },  //クマ歩く下B
    {   MAZE_CHAR_GAME_KUMA_03,     0,      0   },  //クマ歩く上A
    {   MAZE_CHAR_GAME_KUMA_04,     0,      0   },  //クマ歩く上B
    {   MAZE_CHAR_GAME_KUMA_05,     0,      0   },  //クマバンザイ１
    {   MAZE_CHAR_GAME_KUMA_06,     0,      0   },  //クマバンザイ２
    {   MAZE_CHAR_GAME_KUMA_07,     0,      0   },  //クマバンザイ３
    {   MAZE_CHAR_GAME_KUMA_08,     0,      0   },  //クマ歩く右A
    {   MAZE_CHAR_GAME_KUMA_09,     0,      0   },  //クマ歩く右B
    {   MAZE_CHAR_GAME_KUMA_10,     0,      0   },  //クマ歩く左A
    {   MAZE_CHAR_GAME_KUMA_11,     0,      0   },  //クマ歩く左B
    {   MAZE_CHAR_GAME_KUMA_12,     0,      0   },  //クマ走る左A
    {   MAZE_CHAR_GAME_KUMA_13,     0,      0   },  //クマ走る左B
    {   MAZE_CHAR_GAME_KUMA_14,     0,      0   },  //クマ走る右A
    {   MAZE_CHAR_GAME_KUMA_15,     0,      0   },  //クマ走る右B
    {   MAZE_CHAR_GAME_KUMA_16,     0,      0   },  //クマ手振りA
    {   MAZE_CHAR_GAME_KUMA_17,     0,      0   },  //クマ手振りB
    {   MAZE_CHAR_GAME_KUMA_18,     0,      0   },  //クマ地団駄A
    {   MAZE_CHAR_GAME_KUMA_19,     0,      0   },  //クマ地団駄B
    {   MAZE_CHAR_GAME_KUMA_20,     0,      0   },  //クマ登場A
    {   MAZE_CHAR_GAME_KUMA_21,     0,      0   },  //クマ登場B
    {   MAZE_CHAR_GAME_KUMA_22,     0,      0   },  //クマあかんべ
    {   MAZE_CHAR_GAME_KUMA_23,     0,      0   },  //クマグングン見る
    {   MAZE_CHAR_GAME_KUMA_24,     0,      0   },  //クマ胸ドン
    {   MAZE_CHAR_GAME_KUMA_25,     -4,     8   },  //クマじたばたA
    {   MAZE_CHAR_GAME_KUMA_26,     -4,     8   },  //クマじたばたB
};

//----出現アニメ
static MAZE_SPRITE_DATA AppearKumaSpriteTable[]={
    {   MAZE_CHAR_GAME_KUMA_ENTRY_00,   0,  0,  },      //登場
    {   MAZE_CHAR_GAME_KUMA_ENTRY_00,   0,  0,  },      //登場
//  {   MAZE_CHAR_GAME_KUMA_ENTRY_01,   -3, 9,  },      //横長
    {   MAZE_CHAR_GAME_KUMA_ENTRY_02,   -3, 9,  },      //横長
};

//----出現アニメ
static MAZE_SPRITE_DATA AppearGunGunSpriteTable[]={
    {   MAZE_CHAR_GAME_GUNGUN_ENTRY_00, 0,  0   },      //登場
    {   MAZE_CHAR_GAME_GUNGUN_ENTRY_00, 0,  0   },      //登場
//  {   MAZE_CHAR_GAME_GUNGUN_ENTRY_01, 2,  -8  },      //縦長
    {   MAZE_CHAR_GAME_GUNGUN_ENTRY_02, -4, 5   },      //横長
};


//----方向テーブル
static int DirectTable[]=
{
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT,
};


//----方向テーブル
static MAZE_GAME_ROAD DirectRoadTable[]={
    {   0,  -1  },  //上
    {   0,  1   },  //下
    {   -1, 0   },  //左
    {   1,  0   },  //右
};

//----レベル毎の待ち時間テーブル
static int KumaWaitTimeTable[]=
{
    KUMA_WAIT_TIME_LEVEL_1,
    KUMA_WAIT_TIME_LEVEL_2,
    KUMA_WAIT_TIME_LEVEL_3,
    KUMA_WAIT_TIME_LEVEL_4,
    KUMA_WAIT_TIME_LEVEL_5,
};


//----レベル毎の思考確率テーブル
static int KumaThinkModeProbabilityTable[]={
    90, //  LEVEL-1
    92, //  LEVEL-2
    94, //  LEVEL-3
    96, //  LEVEL-4
    98, //  LEVEL-5
};


//----レベル単位問題数テーブル
static int QuestionNumTable[]={
    6,          //  LEVEL-1
    8,          //  LEVEL-2
    10,         //  LEVEL-3
    10,         //  LEVEL-4
    12          //  LEVEL-5
};

//----問題タイプテーブル
static int QuestionTypeTable[]={
    MAZE_GAME_QUESTION_TYPE_ADDITION,       //(+)   LEVEL-1
    MAZE_GAME_QUESTION_TYPE_ADDITION,       //(+)   LEVEL-2
    MAZE_GAME_QUESTION_TYPE_SUBTRACTION,    //(-)   LEVEL-3
    MAZE_GAME_QUESTION_TYPE_SUBTRACTION,    //(-)   LEVEL-4
    MAZE_GAME_QUESTION_TYPE_SUBTRACTION,    //(-)   LEVEL-5
};


//----答え配置テーブル：18箇所
static MAZE_GAME_STAR_POS StarPosTable[]={
    {1, 1}, {3, 1},{5, 1},{7, 1},{9, 1},{11, 1},{13, 1},
    {1, 3}, {3, 3},{5, 3},{7, 3},{9, 3},{11, 3},{13, 3},
    {1, 5}, {3, 5},{5, 5},{7, 5},{9, 5},{11, 5},{13, 5},
    {1, 7}, {3, 7},{5, 7},{7, 7},{9, 7},{11, 7},{13, 7},
    {1, 9}, {3, 9},{5, 9},{7, 9},{9, 9},{11, 9},{13, 9},
    {1,11}, {3,11},{5,11},{7,11},{9,11},{11,11},{13,11},
};


//----答え配置テーブル：18箇所
static MAZE_GAME_ANSWER_POS AnswerPosTable[]=
{
    {2,3},  {4,3},  {6,3},  {8,3},  {10,3}, {12,3},
    {2,5},  {4,5},  {6,5},  {8,5},  {10,5}, {12,5},
    {2,7},  {4,7},  {6,7},  {8,7},  {10,7}, {12,7},
};


static MAZE_GAME_ANSWER_POS_INDEX AnswerPosIndexTable[]=
{
    //-----------------------------------------------------------LEVEL-1
    {   5,  17, 16, 4,  10, 12, 0,  2,  11, 7,  15, 8   },
    {   5,  17, 16, 4,  10, 12, 0,  2,  11, 7,  15, 8   },      //  {   3,  0,  9,  6,  14, 4,  16, 15, 8,  5,  11, 17  },
    {   5,  17, 16, 4,  10, 12, 0,  2,  11, 7,  15, 8   },      //  {   1,  7,  12, 11, 15, 2,  3,  10, 5,  14, 4,  6   },
    {   5,  17, 16, 4,  10, 12, 0,  2,  11, 7,  15, 8   },      //  {   0,  10, 4,  14, 9,  15, 16, 12, 3,  2,  5,  17  },
    {   5,  17, 16, 4,  10, 12, 0,  2,  11, 7,  15, 8   },      //  {   10, 6,  3,  2,  1,  11, 8,  12, 15, 17, 9,  13  },
    {   5,  17, 16, 4,  10, 12, 0,  2,  11, 7,  15, 8   },      //  {   12, 6,  9,  2,  11, 17, 14, 10, 15, 3,  4,  8   },
    {   5,  17, 16, 4,  10, 12, 0,  2,  11, 7,  15, 8   },      //  {   16, 3,  10, 5,  7,  15, 13, 11, 17, 2,  12, 14  },
    {   5,  17, 16, 4,  10, 12, 0,  2,  11, 7,  15, 8   },      //  {   16, 2,  15, 8,  0,  11, 6,  17, 4,  5,  12, 3   },
    {   5,  17, 16, 4,  10, 12, 0,  2,  11, 7,  15, 8   },      //  {   1,  9,  2,  14, 13, 4,  6,  15, 12, 0,  17, 8   },
    {   5,  17, 16, 4,  10, 12, 0,  2,  11, 7,  15, 8   },      //  {   1,  17, 2,  7,  6,  5,  9,  0,  11, 10, 8,  13  },
    //-----------------------------------------------------------LEVEL-2
    {   2,  10, 9,  14, 12, 11, 13, 1,  15, 3,  17, 0   },
    {   2,  10, 9,  14, 12, 11, 13, 1,  15, 3,  17, 0   },      //  {   12, 6,  14, 2,  17, 5,  8,  1,  13, 16, 10, 11  },
    {   2,  10, 9,  14, 12, 11, 13, 1,  15, 3,  17, 0   },      //  {   2,  17, 15, 10, 4,  9,  6,  8,  3,  11, 7,  0   },
    {   2,  10, 9,  14, 12, 11, 13, 1,  15, 3,  17, 0   },      //  {   12, 11, 8,  3,  13, 0,  10, 17, 2,  15, 5,  9   },
    {   2,  10, 9,  14, 12, 11, 13, 1,  15, 3,  17, 0   },      //  {   15, 9,  7,  16, 1,  8,  4,  11, 12, 17, 14, 10  },
    {   2,  10, 9,  14, 12, 11, 13, 1,  15, 3,  17, 0   },      //  {   0,  5,  7,  14, 8,  13, 6,  10, 9,  11, 3,  4   },
    {   2,  10, 9,  14, 12, 11, 13, 1,  15, 3,  17, 0   },      //  {   1,  13, 12, 7,  11, 3,  4,  8,  10, 17, 6,  14  },
    {   2,  10, 9,  14, 12, 11, 13, 1,  15, 3,  17, 0   },      //  {   7,  8,  5,  11, 1,  9,  12, 14, 0,  10, 13, 4   },
    {   2,  10, 9,  14, 12, 11, 13, 1,  15, 3,  17, 0   },      //  {   12, 8,  1,  9,  2,  13, 5,  15, 0,  11, 3,  10  },
    {   2,  10, 9,  14, 12, 11, 13, 1,  15, 3,  17, 0   },      //  {   15, 10, 14, 8,  13, 5,  12, 11, 7,  17, 4,  0   },
    //-----------------------------------------------------------LEVEL-3
    {   17, 7,  8,  1,  12, 5,  14, 4,  2,  6,  13, 15  },
    {   17, 7,  8,  1,  12, 5,  14, 4,  2,  6,  13, 15  },      //  {   13, 16, 7,  2,  11, 15, 0,  9,  17, 14, 8,  3   },
    {   17, 7,  8,  1,  12, 5,  14, 4,  2,  6,  13, 15  },      //  {   14, 10, 1,  17, 2,  5,  13, 4,  6,  11, 8,  16  },
    {   17, 7,  8,  1,  12, 5,  14, 4,  2,  6,  13, 15  },      //  {   3,  1,  14, 10, 6,  5,  4,  15, 0,  11, 16, 9   },
    {   17, 7,  8,  1,  12, 5,  14, 4,  2,  6,  13, 15  },      //  {   13, 3,  2,  15, 14, 7,  8,  4,  11, 17, 16, 10  },
    {   17, 7,  8,  1,  12, 5,  14, 4,  2,  6,  13, 15  },      //  {   16, 8,  4,  13, 9,  3,  5,  10, 0,  2,  1,  7   },
    {   17, 7,  8,  1,  12, 5,  14, 4,  2,  6,  13, 15  },      //  {   14, 5,  12, 1,  4,  10, 13, 11, 17, 16, 7,  2   },
    {   17, 7,  8,  1,  12, 5,  14, 4,  2,  6,  13, 15  },      //  {   15, 14, 17, 1,  8,  6,  0,  7,  12, 10, 13, 3   },
    {   17, 7,  8,  1,  12, 5,  14, 4,  2,  6,  13, 15  },      //  {   8,  7,  14, 9,  12, 11, 15, 1,  4,  6,  2,  16  },
    {   17, 7,  8,  1,  12, 5,  14, 4,  2,  6,  13, 15  },      //  {   12, 16, 1,  5,  14, 11, 15, 17, 7,  6,  13, 9   },
    //-----------------------------------------------------------LEVEL-4
    {   2,  12, 13, 7,  15, 3,  5,  17, 14, 6,  0,  10  },
    {   2,  12, 13, 7,  15, 3,  5,  17, 14, 6,  0,  10  },      //  {   13, 3,  7,  8,  17, 2,  12, 6,  1,  14, 0,  5   },
    {   2,  12, 13, 7,  15, 3,  5,  17, 14, 6,  0,  10  },      //  {   12, 13, 9,  1,  15, 2,  14, 17, 7,  8,  6,  11  },
    {   2,  12, 13, 7,  15, 3,  5,  17, 14, 6,  0,  10  },      //  {   0,  1,  14, 7,  11, 2,  16, 9,  10, 5,  17, 6   },
    {   2,  12, 13, 7,  15, 3,  5,  17, 14, 6,  0,  10  },      //  {   10, 11, 3,  15, 16, 7,  0,  12, 8,  14, 9,  13  },
    {   2,  12, 13, 7,  15, 3,  5,  17, 14, 6,  0,  10  },      //  {   9,  13, 15, 16, 6,  3,  17, 0,  1,  5,  11, 10  },
    {   2,  12, 13, 7,  15, 3,  5,  17, 14, 6,  0,  10  },      //  {   3,  14, 9,  11, 1,  7,  5,  16, 12, 10, 6,  4   },
    {   2,  12, 13, 7,  15, 3,  5,  17, 14, 6,  0,  10  },      //  {   1,  16, 13, 12, 0,  4,  5,  15, 6,  17, 10, 3   },
    {   2,  12, 13, 7,  15, 3,  5,  17, 14, 6,  0,  10  },      //  {   6,  14, 0,  5,  15, 13, 8,  12, 16, 7,  9,  10  },
    {   2,  12, 13, 7,  15, 3,  5,  17, 14, 6,  0,  10  },      //  {   2,  15, 12, 4,  1,  8,  17, 5,  14, 16, 11, 3   },
    //-----------------------------------------------------------LEVEL-5
    {   0,  7,  2,  4,  6,  9,  10, 8,  13, 3,  5,  17  },
    {   0,  7,  2,  4,  6,  9,  10, 8,  13, 3,  5,  17  },      //  {   8,  5,  11, 3,  10, 15, 0,  9,  1,  17, 4,  2   },
    {   0,  7,  2,  4,  6,  9,  10, 8,  13, 3,  5,  17  },      //  {   14, 2,  17, 12, 8,  16, 6,  11, 9,  10, 13, 0   },
    {   0,  7,  2,  4,  6,  9,  10, 8,  13, 3,  5,  17  },      //  {   11, 17, 6,  0,  7,  15, 10, 16, 1,  12, 8,  2   },
    {   0,  7,  2,  4,  6,  9,  10, 8,  13, 3,  5,  17  },      //  {   13, 1,  15, 5,  10, 8,  11, 0,  14, 3,  2,  6   },
    {   0,  7,  2,  4,  6,  9,  10, 8,  13, 3,  5,  17  },      //  {   16, 14, 8,  1,  3,  4,  9,  7,  15, 5,  12, 17  },
    {   0,  7,  2,  4,  6,  9,  10, 8,  13, 3,  5,  17  },      //  {   16, 0,  12, 10, 14, 4,  5,  9,  15, 3,  13, 6   },
    {   0,  7,  2,  4,  6,  9,  10, 8,  13, 3,  5,  17  },      //  {   4,  8,  3,  0,  13, 2,  5,  1,  16, 6,  10, 17  },
    {   0,  7,  2,  4,  6,  9,  10, 8,  13, 3,  5,  17  },      //  {   5,  0,  4,  15, 17, 16, 13, 9,  2,  6,  11, 1   },
    {   0,  7,  2,  4,  6,  9,  10, 8,  13, 3,  5,  17  },      //  {   8,  9,  0,  11, 13, 15, 3,  7,  5,  2,  14, 16  },
};


//----問題テーブル／各レベル１０問
static MAZE_GAME_QUESTION_ANSWER_DATA QuestionDataTable[]=
{
    //----------------------------------------------------------------LEVEL-1
    {   1,  2,  3,  4,  5,  6,  -1, -1, -1, -1, -1, -1  },  //
    {   2,  3,  4,  5,  6,  1,  -1, -1, -1, -1, -1, -1  },  //
    {   3,  4,  5,  6,  1,  2,  -1, -1, -1, -1, -1, -1  },  //
    {   4,  5,  6,  1,  2,  3,  -1, -1, -1, -1, -1, -1  },  //
    {   5,  6,  1,  2,  3,  4,  -1, -1, -1, -1, -1, -1  },  //
    {   6,  1,  2,  3,  4,  5,  -1, -1, -1, -1, -1, -1  },  //
    {   1,  2,  3,  4,  5,  6,  -1, -1, -1, -1, -1, -1  },  //
    {   2,  3,  4,  5,  6,  1,  -1, -1, -1, -1, -1, -1  },  //
    {   3,  4,  5,  6,  1,  2,  -1, -1, -1, -1, -1, -1  },  //
    {   4,  5,  6,  1,  2,  3,  -1, -1, -1, -1, -1, -1  },  //
    //-------------------------------------------------------------LEVEL-2
    {   7,  8,  9,  10, 7,  8,  9,  10, -1, -1, -1, -1  },  //
    {   8,  9,  10, 7,  8,  9,  10, 7,  -1, -1, -1, -1  },  //
    {   9,  10, 7,  8,  9,  10, 7,  8,  -1, -1, -1, -1  },  //
    {   10, 7,  8,  9,  10, 7,  8,  9,  -1, -1, -1, -1  },  //
    {   7,  8,  9,  10, 7,  8,  9,  10, -1, -1, -1, -1  },  //
    {   8,  9,  10, 7,  8,  9,  10, 7,  -1, -1, -1, -1  },  //
    {   9,  10, 7,  8,  9,  10, 7,  8,  -1, -1, -1, -1  },  //
    {   10, 7,  8,  9,  10, 7,  8,  9,  -1, -1, -1, -1  },  //
    {   9,  10, 7,  8,  9,  10, 7,  8,  -1, -1, -1, -1  },  //
    {   10, 7,  8,  9,  10, 7,  8,  9,  -1, -1, -1, -1  },  //
    //-------------------------------------------------------------LEVEL-3
    {   0,  1,  1,  2,  2,  3,  3,  4,  4,  5,  -1, -1  },  //
    {   1,  1,  2,  2,  3,  3,  4,  4,  5,  0,  -1, -1  },  //
    {   1,  2,  2,  3,  3,  4,  4,  5,  0,  1,  -1, -1  },  //
    {   2,  2,  3,  3,  4,  4,  5,  0,  1,  1,  -1, -1  },  //
    {   2,  3,  3,  4,  4,  5,  0,  1,  1,  2,  -1, -1  },  //
    {   3,  3,  4,  4,  5,  0,  1,  1,  2,  2,  -1, -1  },  //
    {   3,  4,  4,  5,  0,  1,  1,  2,  2,  3,  -1, -1  },  //
    {   4,  4,  5,  0,  1,  1,  2,  2,  3,  3,  -1, -1  },  //
    {   4,  5,  0,  1,  1,  2,  2,  3,  3,  4,  -1, -1  },  //
    {   5,  0,  1,  1,  2,  2,  3,  3,  4,  4,  -1, -1  },  //
    //-------------------------------------------------------------LEVEL-4
    {   1,  2,  3,  4,  5,  6,  7,  8,  9,  10, -1, -1  },  //
    {   2,  3,  4,  5,  6,  7,  8,  9,  10, 1,  -1, -1  },  //
    {   3,  4,  5,  6,  7,  8,  9,  10, 1,  2,  -1, -1  },  //
    {   4,  5,  6,  7,  8,  9,  10, 1,  2,  3,  -1, -1  },  //
    {   5,  6,  7,  8,  9,  10, 1,  2,  3,  4,  -1, -1  },  //
    {   6,  7,  8,  9,  10, 1,  2,  3,  4,  5,  -1, -1  },  //
    {   7,  8,  9,  10, 1,  2,  3,  4,  5,  6,  -1, -1  },  //
    {   8,  9,  10, 1,  2,  3,  4,  5,  6,  7,  -1, -1  },  //
    {   9,  10, 1,  2,  3,  4,  5,  6,  7,  8,  -1, -1  },  //
    {   10, 1,  2,  3,  4,  5,  6,  7,  8,  9,  -1, -1  },  //
    //-------------------------------------------------------------LEVEL-5
    {   0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 10  },  //
    {   1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 10, 0   },  //
    {   2,  3,  4,  5,  6,  7,  8,  9,  10, 10, 0,  1   },  //
    {   3,  4,  5,  6,  7,  8,  9,  10, 10, 0,  1,  2   },  //
    {   4,  5,  6,  7,  8,  9,  10, 10, 0,  1,  2,  3   },  //
    {   5,  6,  7,  8,  9,  10, 10, 0,  1,  2,  3,  4   },  //
    {   6,  7,  8,  9,  10, 10, 0,  1,  2,  3,  4,  5   },  //
    {   7,  8,  9,  10, 10, 0,  1,  2,  3,  4,  5,  6   },  //
    {   8,  9,  10, 10, 0,  1,  2,  3,  4,  5,  6,  7   },  //
    {   9,  10, 10, 0,  1,  2,  3,  4,  5,  6,  7,  8   },  //
};




//--------------------------------------------------------------------取得データテーブル
//---- LEVEL-1：足算
static MQGET_VAL MazeQuestionGetTable_Level_1[]=
{
    //回答数    問題                                                                                            （答え）
    {   2,      {{ 0, 1},{ 1, 0},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}},  },  //Ans - 1
    {   3,      {{ 0, 2},{ 1, 1},{ 2, 0},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}},  },  //Ans - 2
    {   4,      {{ 0, 3},{ 1, 2},{ 2, 1},{ 3, 0},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}},  },  //Ans - 3
    {   5,      {{ 0, 4},{ 1, 3},{ 2, 2},{ 3, 1},{ 4, 0},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}},  },  //Ans - 4
    {   6,      {{ 0, 5},{ 1, 4},{ 2, 3},{ 3, 2},{ 4, 1},{ 5, 0},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}},  },  //Ans - 5
    {   5,      {{ 1, 5},{ 2, 4},{ 3, 3},{ 4, 2},{ 5, 1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}},  },  //Ans - 6
};

//---- LEVEL-2：足算
static MQGET_VAL MazeQuestionGetTable_Level_2[]=
{
    //回答数    問題                                                                                            （答え）
    {   8,      {{ 0, 7},{ 1, 6},{ 2, 5},{ 3, 4},{ 4, 3},{ 5, 2},{ 6, 1},{ 7, 0},{-1,-1},{-1,-1},{-1,-1}},  },  //Ans - 7
    {   9,      {{ 0, 8},{ 1, 7},{ 2, 6},{ 3, 5},{ 4, 4},{ 5, 3},{ 6, 2},{ 7, 1},{ 8, 0},{-1,-1},{-1,-1}},  },  //Ans - 8
    {   10,     {{ 0, 9},{ 1, 8},{ 2, 7},{ 3, 6},{ 4, 5},{ 5, 4},{ 6, 3},{ 7, 2},{ 8, 1},{ 9, 0},{-1,-1}},  },  //Ans - 9
    {   11,     {{ 0,10},{ 1, 9},{ 2, 8},{ 3, 7},{ 4, 6},{ 5, 5},{ 6, 4},{ 7, 3},{ 8, 2},{ 9, 1},{10, 0}},  },  //Ans - 10
};


//---- LEVEL-3：引算：変数１は変数２と答え
static MQGET_VAL MazeQuestionGetTable_Level_3[]=
{
    //回答数    問題                                                                                            （答え）
    {   4,      {{ 1, 1},{ 2, 2},{ 3, 3},{ 4, 4},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}},  },  //Ans - 0
    {   6,      {{ 1, 0},{ 2, 1},{ 3, 2},{ 4, 3},{ 5, 4},{ 6, 5},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}},  },  //Ans - 1
    {   6,      {{ 2, 0},{ 3, 1},{ 4, 2},{ 5, 3},{ 6, 4},{ 7, 5},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}},  },  //Ans - 2
    {   6,      {{ 3, 0},{ 4, 1},{ 5, 2},{ 6, 3},{ 7, 4},{ 8, 5},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}},  },  //Ans - 3
    {   6,      {{ 4, 0},{ 5, 1},{ 6, 2},{ 7, 3},{ 8, 4},{ 9, 5},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}},  },  //Ans - 4
    {   5,      {{ 6, 1},{ 7, 2},{ 8, 3},{ 9, 4},{10, 5},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}},  },  //Ans - 5
};


//---- LEVEL-4：引算：変数１は変数２と答え
static MQGET_VAL MazeQuestionGetTable_Level_4[]=
{
    //回答数    問題                                                                                            （答え）
    {   5,      {{ 6, 5},{ 7, 6},{ 8, 7},{ 9, 8},{10, 9},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}},  },  //Ans - 1
    {   5,      {{ 6, 4},{ 7, 5},{ 8, 6},{ 9, 7},{10, 8},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}},  },  //Ans - 2
    {   5,      {{ 6, 3},{ 7, 4},{ 8, 5},{ 9, 6},{10, 7},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}},  },  //Ans - 3
    {   5,      {{ 6, 2},{ 7, 3},{ 8, 4},{ 9, 5},{10, 6},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}},  },  //Ans - 4
    {   5,      {{ 6, 1},{ 7, 2},{ 8, 3},{ 9, 4},{10, 5},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}},  },  //Ans - 5
    {   5,      {{ 6, 0},{ 7, 1},{ 8, 2},{ 9, 3},{10, 4},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}},  },  //Ans - 6
    {   4,      {{ 7, 0},{ 8, 1},{ 9, 2},{10, 3},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}},  },  //Ans - 7
    {   3,      {{ 8, 0},{ 9, 1},{10, 2},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}},  },  //Ans - 8
    {   2,      {{ 9, 0},{10, 1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}},  },  //Ans - 9
    {   1,      {{10, 0},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}},  },  //Ans - 10
};


//---- LEVEL-5：引算：変数１は変数２と答え
static MQGET_VAL MazeQuestionGetTable_Level_5[]=
{
    //回答数    問題                                                                                            （答え）
    {   10,     {{ 1, 1},{ 2, 2},{ 3, 3},{ 4, 4},{ 5, 5},{ 6, 6},{ 7, 7},{ 8, 8},{ 9, 9},{10,10},{-1,-1}},  },  //Ans - 0
    {   10,     {{ 1, 0},{ 2, 1},{ 3, 2},{ 4, 3},{ 5, 4},{ 6, 5},{ 7, 6},{ 8, 7},{ 9, 8},{10, 9},{-1,-1}},  },  //Ans - 1
    {   8,      {{ 3, 1},{ 4, 2},{ 5, 3},{ 6, 4},{ 7, 5},{ 8, 6},{ 9, 7},{10, 8},{-1,-1},{-1,-1},{-1,-1}},  },  //Ans - 2
    {   7,      {{ 4, 1},{ 5, 2},{ 6, 3},{ 7, 4},{ 8, 5},{ 9, 6},{10, 7},{-1,-1},{-1,-1},{-1,-1},{-1,-1}},  },  //Ans - 3
    {   6,      {{ 5, 1},{ 6, 2},{ 7, 3},{ 8, 4},{ 9, 5},{10, 6},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}},  },  //Ans - 4
    {   5,      {{ 6, 1},{ 7, 2},{ 8, 3},{ 9, 4},{10, 5},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}},  },  //Ans - 5
    {   4,      {{ 7, 1},{ 8, 2},{ 9, 3},{10, 4},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}},  },  //Ans - 6
    {   3,      {{ 8, 1},{ 9, 2},{10, 3},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}},  },  //Ans - 7
    {   2,      {{ 9, 1},{10, 2},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}},  },  //Ans - 8
    {   1,      {{10, 1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}},  },  //Ans - 9
    {   1,      {{10, 0},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}},  },  //Ans - 10
};


//----------------------------------------------------スクリプト
//----レベルセレクト
#define SELECT_LEVEL_SCRIPT_BASE            0
#define SELECT_LEVEL_SCRIPT_NUM             1

//----初デモグングン１
#define INIT_DEMO_GUNGUN_1_SCRIPT_BASE      1
#define INIT_DEMO_GUNGUN_1_SCRIPT_NUM       1

//----初デモドンドン１
#define INIT_DEMO_DONDON_1_SCRIPT_BASE      2
#define INIT_DEMO_DONDON_1_SCRIPT_NUM       1

//----初デモドンドン２
#define INIT_DEMO_DONDON_2_SCRIPT_BASE      3
#define INIT_DEMO_DONDON_2_SCRIPT_NUM       2

//----初デモドンドン３
#define INIT_DEMO_DONDON_3_SCRIPT_BASE      5
#define INIT_DEMO_DONDON_3_SCRIPT_NUM       1

//----クリア
#define CLEAR_DEMO_SCRIPT_BASE              6
#define CLEAR_DEMO_SCRIPT_NUM               2

//----オールクリア
#define ALL_CLEAR_DEMO_SCRIPT_BASE          8
#define ALL_CLEAR_DEMO_SCRIPT_NUM           1

//----失敗爆発
#define FALSE_DEMO_1_SCRIPT_BASE            9
#define FALSE_DEMO_1_SCRIPT_NUM             2

//----失敗ガッツ
#define FALSE_DEMO_2_SCRIPT_BASE            11
#define FALSE_DEMO_2_SCRIPT_NUM             2


//----スクリプト本体
static SCRIP_DATA MazeScript[]=
{

    //----------------------------------------レベルセレクト
    {//ひかっている　すうじを　えらんでくれ。
        0,
        NamePlateDan,
        XA_FILE_BAND00,
        4,
        "初音時０６ひかっている　すうじを　えらんでくれ。待３００終"
    },
    //----------------------------------------初デモグングン２
    {//やぁ。ドンドンに　まけないように　改こたえの　ボールを　あつめるぞ！
        0,
        NamePlateGngn,
        XA_FILE_MAZU00,
        3,
        "初消音時０６やぁ。ドンドンに　まけないように　改こたえの　ボールを　あつめるぞ！待２４０終"
    },
    //----------------------------------------初デモドンドン１
    {//だぁーーーーーー！
        0,
        NamePlateDond,
        XA_FILE_MAZU00,
        0,
        "初消音時０６だあ！待１２０終"
    },
    //----------------------------------------初デモドンドン２
    {//オレさまの　なまえは、ドンドン。
        0,
        NamePlateDond,
        XA_FILE_MAZU00,
        1,
        "初消音時０６おれさまの　なまえは、ドンドン。待２４０終"
    },
    {//ここは　オレさまが　ジャマしてやるぞ！
        0,
        NamePlateDond,
        XA_FILE_MAZU00,
        2,
        "初消音時０６ここは　おれさまが　じゃましてやるぞ！待３００終"
    },
    //----------------------------------------初デモドンドン３
    {//べーーーーーっだ！
        0,
        NamePlateDond,
        XA_FILE_MAZU00,
        4,
        "初消音時０６べえだ！待１２０終"
    },
    //----------------------------------------クリア
    {//やったぁ～！スゴイね。！つぎも　がんばろ～。
        0,
        NamePlateGngn,
        XA_FILE_MAZU03,
        5,
        "初消音時０６やったぁ！スゴイね。　改つぎも　がんばろう。待１８０終"
    },
    {//あ～ん！　くやしーよぉ～。
        0,
        NamePlateDond,
        XA_FILE_MAZU03,
        6,
        "初消音時０６あ～ん！　くやしーよぉ。待３６０終"
    },

    //----------------------------------------オールクリア
    {//わぁーい、わぁーい！　スゴイ！　スゴイよ！
        0,
        NamePlateGngn,
        XA_FILE_MAZU03,
        7,
        "初消音時０６わぁーい、わぁーい！　改すごい！　すごいよ！待１８０終"
    },
    //----------------------------------------失敗爆発
    {//・・・つぎは　ガンバロォ・・・。
        0,
        NamePlateGngn,
        XA_FILE_MAZU03,
        9,
        "初消音時０６つぎは　がんばろう。待１８０終"
    },
    {//へ～んだ、がんばれよ～。
        0,
        NamePlateDond,
        XA_FILE_MAZU03,
        10,
        "初消音時０６へえんだ、がんばれよ。待３６０終"
    },
    //----------------------------------------失敗ガッツ

    {//へへへ～んだっ！　おれさまの　かちだぞぉ。
        0,
        NamePlateDond,
        XA_FILE_MAZU03,
        11,
        "初消音時０６へへへんだっ！　おれさまの　改かちだぞぉ。待１８０終"
    },
    {//あ～～ん、まけちゃったぁぁぁ。
        0,
        NamePlateGngn,
        XA_FILE_MAZU03,
        12,
        "初消音時０６ああん、まけちゃったぁぁぁ。待３６０終"
    },
};






#ifdef __DEBUG_MAZE__
    static int wSx;
    static int wSy;
#endif


//-----------------------------------------------------------------------------
// codes 
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  関数名  :Maze
//
//  work    :ドッキリ迷路
//  in     :GAMEMGR*    ゲームマネージャへのポインタ
//  out    :TRUE        成功
//  note   :なし
//-----------------------------------------------------------------------------
int Maze(GAMEMGR *ip_GameMgr)
{
    TASK Task;

    switch( ip_GameMgr->SubMode )
    {
        //----------------------------------------------------------------ゲーム初期化
        case INIT:
            //----スプライトマネージャ初期化
            InitSprite();

            //----タスクマネージャ初期化
            InitTaskMgr();

            //----ランダム設定
            srand(ip_GameMgr->Timer);

            //----岩澤担当部分：初期化
            SfileRead2(MAZU_SOUNDFILE);
            HelpInit();
            GameMgr.WaitFlag    = ON;

            //----ゲーム管理情報初期化
            MGameMgr.QuestionIndex  = 0;
            MGameMgr.Level          = ip_GameMgr->Level[GAME_MAZE];     //レベル
            MGameMgr.PlayLevel      = 0;                                //プレイレベル
            MGameMgr.ContinueFlag   = 0;                                //継続フラグ
            MGameMgr.GameOverFlag   = 0;                                //ゲームオーバーフラグ
            MGameMgr.CheckClearFlag = 0;                                //確認クリアフラグ
            MGameMgr.ClearFlag      = 0;                                //クリアフラグ
            MGameMgr.AllClearFlag   = 0;                                //オールクリアフラグ
            MGameMgr.ExitFlag       = 0;                                //ゲーム終了フラグ

#ifdef __DEBUG_MAZE__
            if(NewPad & PADL1){
                //デバッグスプライトタスク
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
//              //デバッグスプライトタスク
//              Task.func       = DebugEventSpriteTask;
//              Task.priority   = TASK_NO_DEBUG;
//              Task.attribute  = ATTR_USER;
//              Task.status     = TASK_NEW_ENTRY;
//              Task.id         = TASK_NO_DEBUG;
//              Task.wait_time  = 0;
//              Task.buf        = NULL;
//              Task.name       = "DebugEventSpriteTask";
//              Task.mode       = TASK_MODE_INIT;
//              CreateTask(&Task);

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
            if( (NewPad & PADR1) && (NewPad & PADR2) ){
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
                Task.func       = FalseEventBakuTask;
                Task.priority   = TASK_NO_DEBUG;
                Task.attribute  = ATTR_USER;
                Task.status     = TASK_NEW_ENTRY;
                Task.id         = TASK_NO_DEBUG;
                Task.wait_time  = 0;
                Task.buf        = NULL;
                Task.name       = "FalseEventBakuTask";
                Task.mode       = TASK_MODE_INIT;
                CreateTask(&Task);
            }else
            if(NewPad & PADR2){
                Task.func       = FalseEventGutsTask;
                Task.priority   = TASK_NO_DEBUG;
                Task.attribute  = ATTR_USER;
                Task.status     = TASK_NEW_ENTRY;
                Task.id         = TASK_NO_DEBUG;
                Task.wait_time  = 0;
                Task.buf        = NULL;
                Task.name       = "FalseEventGutsTask";
                Task.mode       = TASK_MODE_INIT;
                CreateTask(&Task);
                
            }else
            {
                if(MGameMgr.Level==0)
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
            if(MGameMgr.Level==0)
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

            //----メインモード
            ip_GameMgr->SubMode = MAIN;
            
            break;
        //----------------------------------------------------------------ゲームメイン
        case MAIN:
            FntPrint("");       //呼んでおかないとダメ
            
            ExecuteTask();      //タスク実行
            TransSprite();      //スプライト転送
            SpraitControl();
            
            //----終了チェック
            if(MGameMgr.ExitFlag) ip_GameMgr->SubMode = EXIT;
            
            break;
        //----------------------------------------------------------------ゲーム終了
        case EXIT:
            //----ゲームレベル
            ip_GameMgr->Level[GAME_MAZE]    = MGameMgr.Level;

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
            break;
    }
    
    return TRUE;
}


//-----------------------------------------------------------------------------
//  関数名  :GameControllTask
//
//  work    :ゲームコントローラ
//  in      :TASK*  タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int GameControllTask(TASK* ip_task)
{
    TASK Task;
    int i,j;

    switch( ip_task->mode )
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //next main
            ip_task->mode = TASK_MODE_MAIN;

            //----texture read sram -> vram
            if((file_read(MazeGameTextureFile[0].fn,LoadAddress)) == -1)
            {//read error
                return FALSE;
            }

            //----texture init
            TexInit( MAZE_GAME_TIM_NUM, &MazeGameTextureImage[MAZE_GAME_TIM_POS] );
            TimImgData = MazeGameTextureImage;

            //----開放
            ReleaseSprite();

            //----ゲーム用スプライト登録
            EntrySprite( MazeGameSpriteData );

            //----ゲーム管理情報初期化
            MGameMgr.QuestionIndex  = 0;                        //クエスチョンインデックス
            MGameMgr.Zanki          = MAX_GUNGUN_ZANKI_NUM;     //残機
            MGameMgr.GameOverFlag   = 0;                        //ゲームオーバーフラグ
            MGameMgr.CheckClearFlag = 0;                        //確認クリアフラグ
            MGameMgr.ClearFlag      = 0;                        //クリアフラグ
            MGameMgr.AllClearFlag   = 0;                        //オールクリアフラグ
            MGameMgr.ExitFlag       = 0;                        //ゲーム終了フラグ
            MGameMgr.ContinueFlag   = 0;

            //ガイドセット
            GaidoInit();

            //----マップセット
            InitGameMap();

            //フェードイン
            GameMgr.FadeFlag    = FadeIn;

            //----グングンタスク
            Task.func       = GunGunTask;
            Task.priority   = TASK_NO_GAME_GUNGUN;
            Task.attribute  = ATTR_USER;
            Task.status     = TASK_NEW_ENTRY;
            Task.id         = TASK_NO_GAME_GUNGUN;
            Task.wait_time  = 0;
            Task.buf        = NULL;
            Task.name       = "GunGunTask";
            Task.mode       = TASK_MODE_INIT;
            CreateTask(&Task);

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

            //----クマタスク
            Task.func       = KumaTask;
            Task.priority   = TASK_NO_GAME_KUMA;
            Task.attribute  = ATTR_USER;
            Task.status     = TASK_NEW_ENTRY;
            Task.id         = TASK_NO_GAME_KUMA;
            Task.wait_time  = 0;
            Task.buf        = NULL;
            Task.name       = "KumaTask";
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
            
            //----グングン残機タスク
            Task.func       = GunGunZankiTask;
            Task.priority   = TASK_NO_GAME_GUNGUN_ZANKI;
            Task.attribute  = ATTR_USER;
            Task.status     = TASK_NEW_ENTRY;
            Task.id         = TASK_NO_GAME_GUNGUN_ZANKI;
            Task.wait_time  = 0;
            Task.buf        = NULL;
            Task.name       = "GunGunZankiTask";
            Task.mode       = TASK_MODE_INIT;
            CreateTask(&Task);
            
            //----ポーズ監視タスク
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


            if(MGameMgr.ContinueFlag==0)
            {//----グングン出現イベント
                //----継続フラグセット
                MGameMgr.ContinueFlag   = 1;

                //----出演者出現タスク
                Task.func       = CastAppearTask;
                Task.priority   = TASK_NO_GAME_CAST_APPEAR;
                Task.attribute  = ATTR_USER;
                Task.status     = TASK_NEW_ENTRY;
                Task.id         = TASK_NO_GAME_CAST_APPEAR;
                Task.wait_time  = 0;
                Task.buf        = NULL;
                Task.name       = "CastAppearTask";
                Task.mode       = TASK_MODE_INIT;
                CreateTask(&Task);
                
                //----キャストイベント終了待ち
                SleepTask(TASK_NO_GAME_GUNGUN);
                SleepTask(TASK_NO_GAME_KUMA);
                SleepTask(TASK_NO_GAME_QUESTION);
                SleepTask(TASK_NO_GAME_GUNGUN_ZANKI);
            }
            SleepTask(TASK_NO_GAME_PAUSE);

            break;
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:
            
#ifdef __DEBUG_MAZE__
            FntPrint("Level____=[%d]\n",MGameMgr.Level);
            FntPrint("PlayLevel=[%d]\n",MGameMgr.PlayLevel);
#endif


#ifdef __DEBUG_MAZE_ANSWER__
            for(i=0;i<12;i++){
                FntPrint("ANS:[%2d][%2d]/Q:[%2d][%2d][%2d]\n",i,MGameMgr.Answer[i],MGameMgr.Question.Data[i].QuestionNum.num1,MGameMgr.Question.Data[i].QuestionNum.num2,MGameMgr.Question.Data[i].QuestionNum.num3);

            }
#endif

            //終了フラグとゲームオーバー
            if(MGameMgr.ClearFlag || MGameMgr.GameOverFlag){
                ip_task->mode = TASK_MODE_EXIT;
            }

            break;
        //----------------------------------------------------------------タスク終了
        case TASK_MODE_EXIT:
            //ガイド破棄
            SpraitCharClr();

            //[♪]BGM
            ssStopBgm(MAZU_BGM_00);

            //----タスク削除
            RemoveTask(TASK_NO_GAME_GUNGUN);
            RemoveTask(TASK_NO_GAME_KUMA);
            RemoveTask(TASK_NO_GAME_QUESTION);
            RemoveTask(TASK_NO_GAME_BG);
            RemoveTask(TASK_NO_GAME_GUNGUN_ZANKI);
            RemoveTask(TASK_NO_GAME_PAUSE);
            RemoveTask(TASK_NO_GAME_BAR);
            RemoveTask(TASK_NO_GAME_STAR);
            
            //----登録スプライト開放
            ReleaseSprite();
            
            //ガイド破棄
            SpraitCharClr();

            //----イベントタスクを起動：オールクリア→クリア→失敗の順で確認する
            if(MGameMgr.AllClearFlag)
            {
                //----オールクリアタスク
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
            if(MGameMgr.ClearFlag)
            {   
                //----クリアタスク
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
            }else
            if(MGameMgr.GameOverFlag)
            {   
                if( rand()%2 )
                {
                    //----失敗タスク：爆発
                    Task.func       = FalseEventBakuTask;
                    Task.priority   = TASK_NO_GAME_FALSE_EVENT;
                    Task.attribute  = ATTR_USER;
                    Task.status     = TASK_NEW_ENTRY;
                    Task.id         = TASK_NO_GAME_FALSE_EVENT;
                    Task.wait_time  = 0;
                    Task.buf        = NULL;
                    Task.name       = "FalseEventBakuTask";
                    Task.mode       = TASK_MODE_INIT;
                    CreateTask(&Task);
                }else
                {
                    //----失敗タスク：ガッツ
                    Task.func       = FalseEventGutsTask;
                    Task.priority   = TASK_NO_GAME_FALSE_EVENT;
                    Task.attribute  = ATTR_USER;
                    Task.status     = TASK_NEW_ENTRY;
                    Task.id         = TASK_NO_GAME_FALSE_EVENT;
                    Task.wait_time  = 0;
                    Task.buf        = NULL;
                    Task.name       = "FalseEventGutsTask";
                    Task.mode       = TASK_MODE_INIT;
                    CreateTask(&Task);
                }
            }else{
                
            }
            
            //----自分を削除
            ExitTask(ip_task->id);
            break;
        default:
    }
    
    return TRUE;
}

//-----------------------------------------------------------------------------
//  関数名  :CastAppearTask
//
//  work    :出現イベント
//  in      :TASK* ip_task
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int CastAppearTask(TASK* ip_task)
{
    static int kx,ky;
    SPRITE_DATA SpData;
    TASK Task;


    switch( ip_task->mode )
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //----next main
            ip_task->mode = TASK_MODE_MAIN;

            kx=44;
            ky=140;

            ip_task->user[0]=0;//kuma
            ip_task->user[1]=0;//kuma
            ip_task->user[2]=0;//gnu2
            ip_task->user[3]=0;//gnu2

#ifndef __DEBUG_MAZE__

            //----texture read sram -> vram
            if((file_read(MazeGameTextureFile[0].fn,LoadAddress)) == -1)
            {//read error
                return FALSE;
            }

            //----texture init
            TexInit( MAZE_GAME_TIM_NUM, &MazeGameTextureImage[MAZE_GAME_TIM_POS] );
            TimImgData = MazeGameTextureImage;

            //----開放
            ReleaseSprite();

            //----ゲーム用スプライト登録
            EntrySprite( MazeGameSpriteData );

#endif


            //----初期化
            MGameMgr.AppearEvent.Kuma.Status        = CAST_APPEAR_STATUS_WAIT;
            MGameMgr.AppearEvent.Kuma.Anm.Data.no   = AppearKumaSpriteTable[0].No;
            MGameMgr.AppearEvent.Kuma.Anm.Data.wt   = 0;
            MGameMgr.AppearEvent.Kuma.Anm.Index     = 0;
            MGameMgr.AppearEvent.Kuma.Pos.x         = KUMA_CAST_APPEAR_INIT_X;
            MGameMgr.AppearEvent.Kuma.Pos.y         = KUMA_CAST_APPEAR_INIT_Y;
            MGameMgr.AppearEvent.Kuma.Pos.z         = PRIORITY_MAZE_GAME_CAST_EVENT;
            MGameMgr.AppearEvent.Kuma.OPos.x        = 0;
            MGameMgr.AppearEvent.Kuma.OPos.y        = 0;
            MGameMgr.AppearEvent.Kuma.OPos.z        = 0;
            MGameMgr.AppearEvent.Kuma.Spd.dx        = 0;
            MGameMgr.AppearEvent.Kuma.Spd.dy        = -1;
            MGameMgr.AppearEvent.Kuma.Spd.sx        = 0;
            MGameMgr.AppearEvent.Kuma.Spd.sy        = 4;
            MGameMgr.AppearEvent.KumaTimer          = 0;

            MGameMgr.AppearEvent.GunGun.Status      = CAST_APPEAR_STATUS_WAIT;
            MGameMgr.AppearEvent.GunGun.Anm.Data.no = AppearGunGunSpriteTable[0].No;
            MGameMgr.AppearEvent.GunGun.Anm.Data.wt = 0;
            MGameMgr.AppearEvent.GunGun.Anm.Index   = 0;
            MGameMgr.AppearEvent.GunGun.Pos.x       = GUNGUN_CAST_APPEAR_INIT_X + 150;
            MGameMgr.AppearEvent.GunGun.Pos.y       = GUNGUN_CAST_APPEAR_INIT_Y;
            MGameMgr.AppearEvent.GunGun.Pos.z       = PRIORITY_MAZE_GAME_CAST_EVENT;
            MGameMgr.AppearEvent.GunGun.OPos.x      = 0;
            MGameMgr.AppearEvent.GunGun.OPos.y      = 0;
            MGameMgr.AppearEvent.GunGun.OPos.z      = 0;
            MGameMgr.AppearEvent.GunGun.Spd.dx      = 0;
            MGameMgr.AppearEvent.GunGun.Spd.dy      = -1;
            MGameMgr.AppearEvent.GunGun.Spd.sx      = 0;
            MGameMgr.AppearEvent.GunGun.Spd.sy      = 4;
            MGameMgr.AppearEvent.GunGunTimer        = 0;
            MGameMgr.AppearEvent.Timer              = 0;

            break;
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:
            //----終了タイマー
            ++MGameMgr.AppearEvent.Timer;

            //----クマ動作
            switch(MGameMgr.AppearEvent.Kuma.Status)
            {
                case CAST_APPEAR_STATUS_WAIT:
                    //ステータス変更：ドンドンジャンプ
                    MGameMgr.AppearEvent.Kuma.Status        = CAST_APPEAR_STATUS_JUMP;

                    //スクリプト：ドンドン
                    MGameMgr.Script.Flag=1;
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
                    Task.user[1]        = INIT_DEMO_DONDON_1_SCRIPT_BASE;
                    Task.user[2]        = INIT_DEMO_DONDON_1_SCRIPT_NUM;
                    CreateTask(&Task);
                    break;
                case CAST_APPEAR_STATUS_JUMP:
                    MGameMgr.AppearEvent.Kuma.Pos.y += MGameMgr.AppearEvent.Kuma.Spd.sy * MGameMgr.AppearEvent.Kuma.Spd.dy;
                    if(MGameMgr.AppearEvent.Kuma.Pos.y < KUMA_CAST_APPEAR_DOWN_START_Y){
                        MGameMgr.AppearEvent.Kuma.Status        = CAST_APPEAR_STATUS_DOWN;
                        MGameMgr.AppearEvent.Kuma.Spd.dy        = 1;
                        MGameMgr.AppearEvent.Kuma.Spd.sy        = 1;
                    //  MGameMgr.AppearEvent.Kuma.Anm.Index     = 1;
                    }
                    
                    break;
                case CAST_APPEAR_STATUS_DOWN:
                    MGameMgr.AppearEvent.Kuma.Pos.y += MGameMgr.AppearEvent.Kuma.Spd.sy * MGameMgr.AppearEvent.Kuma.Spd.dy;
                    if(MGameMgr.AppearEvent.Kuma.Pos.y>KUMA_CAST_APPEAR_STOP_Y){
                        MGameMgr.AppearEvent.Kuma.Status = CAST_APPEAR_STATUS_STOP;
                        MGameMgr.AppearEvent.Kuma.Anm.Index = 2;
                        
                        //[♪]ドン
                        ssPlaySe(MAZU_SE_07);
                    }
                    
                    break;
                case CAST_APPEAR_STATUS_STOP:
                    if(++MGameMgr.AppearEvent.Kuma.Anm.Data.wt>CAST_STOP_WAIT_TIME){
                        if(!MGameMgr.Script.Flag){
                            MGameMgr.AppearEvent.Kuma.Status        = CAST_APPEAR_STATUS_SPEAK;
                            MGameMgr.AppearEvent.Kuma.Anm.Index     = 0;
                            
                            //スクリプト：ドンドン
                            MGameMgr.Script.Flag=1;
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
                            Task.user[1]        = INIT_DEMO_DONDON_2_SCRIPT_BASE;
                            Task.user[2]        = INIT_DEMO_DONDON_2_SCRIPT_NUM;
                            CreateTask(&Task);
                        }
                    }
                    break;
                case CAST_APPEAR_STATUS_SPEAK:
                    ++MGameMgr.AppearEvent.KumaTimer;
                    
                    if(++ip_task->user[0]>=MAZE_GAME_EVENT_ANM_WAIT_TIME){
                        ip_task->user[0]=0;
                        ip_task->user[1]^=1;
                    }

                    if(!MGameMgr.Script.Flag){
                        
                        //ステータス変更:話待ちへ
                        MGameMgr.AppearEvent.Kuma.Status    = CAST_APPEAR_STATUS_SPEAK_WAIT;
                        
                        //グングンジャンプ
                        MGameMgr.AppearEvent.GunGun.Status  = CAST_APPEAR_STATUS_JUMP;
                        
                    }
                    
                    break;
                case CAST_APPEAR_STATUS_AKANBE:
                    //終了
                    if(!MGameMgr.Script.Flag){
                        ip_task->mode=TASK_MODE_EXIT;
                    }
                    break;
                case CAST_APPEAR_STATUS_SPEAK_WAIT:
                    break;
                default:
            }


            //----グングン動作
            switch(MGameMgr.AppearEvent.GunGun.Status)
            {
                case CAST_APPEAR_STATUS_WAIT:
                    
                    break;
                case CAST_APPEAR_STATUS_JUMP:
                    MGameMgr.AppearEvent.GunGun.Pos.y += MGameMgr.AppearEvent.GunGun.Spd.sy * MGameMgr.AppearEvent.GunGun.Spd.dy;
                    if(MGameMgr.AppearEvent.GunGun.Pos.y < GUNGUN_CAST_APPEAR_DOWN_START_Y){
                        MGameMgr.AppearEvent.GunGun.Status      = CAST_APPEAR_STATUS_DOWN;
                        MGameMgr.AppearEvent.GunGun.Spd.dy      = 1;
                        MGameMgr.AppearEvent.GunGun.Spd.sy      = 1;
                    //  MGameMgr.AppearEvent.GunGun.Anm.Index   = 1;
                    }
                    break;
                case CAST_APPEAR_STATUS_DOWN:
                    MGameMgr.AppearEvent.GunGun.Pos.y += MGameMgr.AppearEvent.GunGun.Spd.sy * MGameMgr.AppearEvent.GunGun.Spd.dy;
                    if(MGameMgr.AppearEvent.GunGun.Pos.y>GUNGUN_CAST_APPEAR_STOP_Y){
                        MGameMgr.AppearEvent.GunGun.Status      = CAST_APPEAR_STATUS_STOP;
                        MGameMgr.AppearEvent.GunGun.Anm.Index   = 2;
                    
                        //[♪]ドン
                        ssPlaySe(MAZU_SE_07);
                    }
                    
                    break;
                case CAST_APPEAR_STATUS_STOP:
                    if(++MGameMgr.AppearEvent.GunGun.Anm.Data.wt>CAST_STOP_WAIT_TIME){
                        if(!MGameMgr.Script.Flag){
                            MGameMgr.AppearEvent.GunGun.Status      = CAST_APPEAR_STATUS_SPEAK;
                            MGameMgr.AppearEvent.GunGun.Anm.Index   = 0;
                            
                            //スクリプト：グングン
                            MGameMgr.Script.Flag=1;
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
                            Task.user[1]        = INIT_DEMO_GUNGUN_1_SCRIPT_BASE;
                            Task.user[2]        = INIT_DEMO_GUNGUN_1_SCRIPT_NUM;
                            CreateTask(&Task);
                        }
                    }
                    break;
                case CAST_APPEAR_STATUS_SPEAK:
                    
                    if(++ip_task->user[2]>=MAZE_GAME_EVENT_ANM_WAIT_TIME){
                        ip_task->user[2]=0;
                        ip_task->user[3]^=1;
                    }

                    if(!MGameMgr.Script.Flag){
                        //ステータス変更：グングン
                        MGameMgr.AppearEvent.GunGun.Status = CAST_APPEAR_STATUS_SPEAK_WAIT;

                        //ステータス変更：ドンドン
                        MGameMgr.AppearEvent.Kuma.Status = CAST_APPEAR_STATUS_AKANBE;
                        //スクリプト：ドンドン
                        MGameMgr.Script.Flag=1;
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
                        Task.user[1]        = INIT_DEMO_DONDON_3_SCRIPT_BASE;
                        Task.user[2]        = INIT_DEMO_DONDON_3_SCRIPT_NUM;
                        CreateTask(&Task);
                    }
                    break;
                case CAST_APPEAR_STATUS_AKANBE:
                    break;
                case CAST_APPEAR_STATUS_SPEAK_WAIT:
                    
                    break;
                default:
            }


//          FntPrint("KUMA[%3d-%3d]",kx,ky);
//          if(JstPad & PADLup){
//              ky--;
//          }else
//          if(JstPad &  PADLdown){
//              ky++;
//          }else
//          if(JstPad &  PADLleft){
//              kx--;
//          }else
//          if(JstPad &  PADLright){
//              kx++;
//          }else
//          {
//              
//          }


            if(MGameMgr.AppearEvent.Kuma.Status == CAST_APPEAR_STATUS_SPEAK){
                if(ip_task->user[1]){
                    //----クマ口描画
                    SpData.No       = MAZE_CHAR_GAME_KUMA_ENTRY_MOUSE;
                    SpData.PosX     = 49 + MGameMgr.AppearEvent.Kuma.Pos.x + MGameMgr.AppearEvent.Kuma.OPos.x + AppearKumaSpriteTable[MGameMgr.AppearEvent.Kuma.Anm.Index].Ofx;
                    SpData.PosY     = 57 + MGameMgr.AppearEvent.Kuma.Pos.y + MGameMgr.AppearEvent.Kuma.OPos.y + AppearKumaSpriteTable[MGameMgr.AppearEvent.Kuma.Anm.Index].Ofy;
                    SpData.PosZ     = MGameMgr.AppearEvent.Kuma.Pos.z + MGameMgr.AppearEvent.Kuma.OPos.z;
                    SpData.ScaleX   = SCALE10;
                    SpData.ScaleY   = SCALE10;
                    SpData.Rotate   = ROTATE000;
                    SpData.Reverse  = NOREVERS;
                    DrawSprite( &SpData );
                }
            }


            if(MGameMgr.AppearEvent.Kuma.Status != CAST_APPEAR_STATUS_AKANBE){
                //----クマ描画
                MGameMgr.AppearEvent.Kuma.Anm.Data.no = AppearKumaSpriteTable[MGameMgr.AppearEvent.Kuma.Anm.Index].No;
                SpData.No       = MGameMgr.AppearEvent.Kuma.Anm.Data.no;
                SpData.PosX     = MGameMgr.AppearEvent.Kuma.Pos.x + MGameMgr.AppearEvent.Kuma.OPos.x + AppearKumaSpriteTable[MGameMgr.AppearEvent.Kuma.Anm.Index].Ofx;
                SpData.PosY     = MGameMgr.AppearEvent.Kuma.Pos.y + MGameMgr.AppearEvent.Kuma.OPos.y + AppearKumaSpriteTable[MGameMgr.AppearEvent.Kuma.Anm.Index].Ofy;
                SpData.PosZ     = MGameMgr.AppearEvent.Kuma.Pos.z + MGameMgr.AppearEvent.Kuma.OPos.z;
                SpData.ScaleX   = SCALE10;
                SpData.ScaleY   = SCALE10;
                SpData.Rotate   = ROTATE000;
                SpData.Reverse  = NOREVERS;
                DrawSprite( &SpData );
                
            }else{
                //体
                //----クマ描画
                SpData.No       = MAZE_CHAR_GAME_KUMA_BODY;
                SpData.PosX     = kx;
                SpData.PosY     = ky;
                SpData.PosZ     = PRIORITY_MAZE_GAME_CAST_EVENT;
                SpData.ScaleX   = SCALE10;
                SpData.ScaleY   = SCALE10;
                SpData.Rotate   = ROTATE000;
                SpData.Reverse  = NOREVERS;
                DrawSprite( &SpData );

                //顔１
                SpData.No       = MAZE_CHAR_GAME_KUMA_HEAD_00;
                SpData.PosX     =  8  + kx;
                SpData.PosY     = -61 + ky;
                SpData.PosZ     = PRIORITY_MAZE_GAME_CAST_EVENT;
                SpData.ScaleX   = SCALE10;
                SpData.ScaleY   = SCALE10;
                SpData.Rotate   = ROTATE000;
                SpData.Reverse  = NOREVERS;
                DrawSprite( &SpData );

                //左手
                SpData.No       = MAZE_CHAR_GAME_KUMA_AKANBE_ARM_LEFT;
                SpData.PosX     = -23 + kx;
                SpData.PosY     = -3  + ky;
                SpData.PosZ     = PRIORITY_MAZE_GAME_CAST_EVENT-1;
                SpData.ScaleX   = SCALE10;
                SpData.ScaleY   = SCALE10;
                SpData.Rotate   = ROTATE000;
                SpData.Reverse  = NOREVERS;
                DrawSprite( &SpData );

                //右手
                SpData.No       = MAZE_CHAR_GAME_KUMA_AKANBE_ARM_RIGHT;
                SpData.PosX     = 29  + kx;
                SpData.PosY     = -28 + ky;
                SpData.PosZ     = PRIORITY_MAZE_GAME_CAST_EVENT-1;
                SpData.ScaleX   = SCALE10;
                SpData.ScaleY   = SCALE10;
                SpData.Rotate   = ROTATE000;
                SpData.Reverse  = NOREVERS;
                DrawSprite( &SpData );
            }

            if(MGameMgr.AppearEvent.GunGun.Status == CAST_APPEAR_STATUS_SPEAK){
                if(ip_task->user[3]){
                //----グングン口描画
                SpData.No       = MAZE_CHAR_GAME_GUNGUN_MOUTH_00;
                SpData.PosX     = 32 + MGameMgr.AppearEvent.GunGun.Pos.x + MGameMgr.AppearEvent.GunGun.OPos.x + AppearGunGunSpriteTable[MGameMgr.AppearEvent.GunGun.Anm.Index].Ofx;
                SpData.PosY     = 37 + MGameMgr.AppearEvent.GunGun.Pos.y + MGameMgr.AppearEvent.GunGun.OPos.y + AppearGunGunSpriteTable[MGameMgr.AppearEvent.GunGun.Anm.Index].Ofy;
                SpData.PosZ     = MGameMgr.AppearEvent.GunGun.Pos.z + MGameMgr.AppearEvent.GunGun.OPos.z;
                SpData.ScaleX   = SCALE10;
                SpData.ScaleY   = SCALE10;
                SpData.Rotate   = ROTATE000;
                SpData.Reverse  = NOREVERS;
                DrawSprite( &SpData );
                }
            }


            //----グングン描画
            MGameMgr.AppearEvent.GunGun.Anm.Data.no = AppearGunGunSpriteTable[MGameMgr.AppearEvent.GunGun.Anm.Index].No;
            SpData.No       = MGameMgr.AppearEvent.GunGun.Anm.Data.no;
            SpData.PosX     = MGameMgr.AppearEvent.GunGun.Pos.x + MGameMgr.AppearEvent.GunGun.OPos.x + AppearGunGunSpriteTable[MGameMgr.AppearEvent.GunGun.Anm.Index].Ofx;
            SpData.PosY     = MGameMgr.AppearEvent.GunGun.Pos.y + MGameMgr.AppearEvent.GunGun.OPos.y + AppearGunGunSpriteTable[MGameMgr.AppearEvent.GunGun.Anm.Index].Ofy;
            SpData.PosZ     = MGameMgr.AppearEvent.GunGun.Pos.z + MGameMgr.AppearEvent.GunGun.OPos.z;
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

            //ウェイクアップタスク
            WakeupTask(TASK_NO_GAME_GUNGUN);
            WakeupTask(TASK_NO_GAME_KUMA);
            WakeupTask(TASK_NO_GAME_QUESTION);
            WakeupTask(TASK_NO_GAME_GUNGUN_ZANKI);
            
            //----自分を削除
            ExitTask(ip_task->id);
            break;
        default:
    }
    
    return TRUE;
}


//-----------------------------------------------------------------------------
//  関数名  :GunGunTask
//
//  work    :グングンタスク
//  in      :TASK* ip_task  タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int GunGunTask(TASK* ip_task)
{
    static int GunGunDirectAnmBase[]={
        GUNGUN_ANM_BASE_UP,
        GUNGUN_ANM_BASE_DOWN,
        GUNGUN_ANM_BASE_LEFT,
        GUNGUN_ANM_BASE_RIGHT,
    };

    static int GunGunCoughtAnmBase[]={
        GUNGUN_ANM_BASE_COUGHT_DOWN,    //クマは上
        GUNGUN_ANM_BASE_COUGHT_UP,      //クマは下
        GUNGUN_ANM_BASE_COUGHT_RIGHT,   //クマは右
        GUNGUN_ANM_BASE_COUGHT_LEFT,    //クマは左
    };

    static int GunGunMoveCountTable[]={
        MAZE_GAME_SQUARE_H,
        MAZE_GAME_SQUARE_H,
        MAZE_GAME_SQUARE_W,
        MAZE_GAME_SQUARE_W,
    };

    TASK *pTask,Task;
    SPRITE_DATA SpData;
    int i,dir;



    switch( ip_task->mode )
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //----next main
            ip_task->mode = TASK_MODE_MAIN;
            
            //----グングン初期化
            MGameMgr.GunGun.Character.Status        = GUNGUN_APPEAR;                //継続プレイの場合は"GUNGUN_WAIT"に設定する
            MGameMgr.GunGun.Character.Anm.Data.no   = GunGunGameSpriteTable[GUNGUN_ANM_BASE_SMOKE].No;
            MGameMgr.GunGun.Character.Anm.Data.wt   = 0;
            MGameMgr.GunGun.Character.Anm.Index     = 0;
            MGameMgr.GunGun.Character.Pos.x         = MAZE_GAME_MAP_LEFT_X + GUNGUN_INIT_MAP_OFFSET_X + (GUNGUN_INIT_PX) * MAZE_GAME_SQUARE_W;
            MGameMgr.GunGun.Character.Pos.y         = MAZE_GAME_MAP_LEFT_Y + GUNGUN_INIT_MAP_OFFSET_Y + (GUNGUN_INIT_PY) * MAZE_GAME_SQUARE_H;
            MGameMgr.GunGun.Character.Pos.z         = PRIORITY_MAZE_GAME_GUNGUN;
            MGameMgr.GunGun.Character.OPos.x        = GUNGUN_ANM_OFSET_X;
            MGameMgr.GunGun.Character.OPos.y        = GUNGUN_ANM_OFSET_Y;
            MGameMgr.GunGun.Character.OPos.z        = 0;
            MGameMgr.GunGun.Character.Spd.dx        = 0;
            MGameMgr.GunGun.Character.Spd.dy        = 0;
            MGameMgr.GunGun.Character.Spd.sx        = 1;
            MGameMgr.GunGun.Character.Spd.sy        = 1;
            MGameMgr.GunGun.AnmBase                 = GUNGUN_ANM_BASE_SMOKE;        //継続プレイの場合はアニメセットを変更する
            MGameMgr.GunGun.Timer                   = 0;
            MGameMgr.GunGun.Px                      = GUNGUN_INIT_PX;
            MGameMgr.GunGun.Py                      = GUNGUN_INIT_PY;
            MGameMgr.GunGun.KeyDirect               = DIR_NOTHING;
            
            break;
        //----------------------------------------------------------------タスクメイン
          case TASK_MODE_MAIN:
             
        //  FntPrint("GUN2_PXPY=(%2d,%2d)\n",MGameMgr.GunGun.Px,MGameMgr.GunGun.Py);
        //  FntPrint("\n\n\n\n\n\n");
        //  FntPrint("QUESINDEX=[%2d]\n",MGameMgr.QuestionIndex);
        //  FntPrint("ANS______=[%2d]\n",MGameMgr.Answer[MGameMgr.QuestionIndex]);

//          FntPrint("ANS=");
//          for(i=0;i<12;i++){
//              FntPrint("[%d]",MGameMgr.Answer[i]);
//          }
//          FntPrint("\n");


            switch(MGameMgr.GunGun.Character.Status)
            {
                //--------------------------------出現
                case GUNGUN_APPEAR:
                    if(++MGameMgr.GunGun.Timer>GUNGUN_APPEAR_TIME)
                    {
                        //----ステータス変更：出現待ちへ
                        MGameMgr.GunGun.Character.Status        = GUNGUN_APPEAR_WAIT;
                        
                        //----アニメ設定
                        MGameMgr.GunGun.AnmBase                 = GUNGUN_ANM_BASE_DOWN;
                        MGameMgr.GunGun.Character.Anm.Data.wt   = 0;
                        MGameMgr.GunGun.Character.Anm.Index     = 0;
                        MGameMgr.GunGun.Character.Anm.Data.wt   = GUNGUN_GAME_ANM_WAIT_TIME;
                        
                        //----タイマークリア
                        MGameMgr.GunGun.Timer                   = 0;
                    }
                    
                    break;
                //--------------------------------出現後の待ち
                case GUNGUN_APPEAR_WAIT:
                    //クイズタスクでXA再生が終了するのを待ちます
                    
                    break;
                //--------------------------------キー待ち
                case GUNGUN_WAIT:
                    //----判定
                    if( !CheckCought(MGameMgr.GunGun.Px,MGameMgr.GunGun.Py,MGameMgr.Kuma.Px,MGameMgr.Kuma.Py) )
                    {//----捕まっていない
                        if(CheckKeyDir(&dir))
                        {//----方向キー入力あり
                            switch(CheckCharacterMaze(MGameMgr.GunGun.Px,MGameMgr.GunGun.Py,dir))
                            {
                                //----------------------------------------障害物なしなので移動(敵はマップでは処理しないかも？)
                                case MAZE_MAP_CHAR_NONE:
                                case MAZE_MAP_CHAR_STAR:
                                    //----ステータス変更：移動へ
                                    MGameMgr.GunGun.Character.Status        = GUNGUN_WALK;
                                    
                                    //----移動&方向＆ータセット
                                    MGameMgr.GunGun.KeyDirect               = dir;
                                    MGameMgr.GunGun.Character.MoveCount     = GunGunMoveCountTable[dir];
                                    MGameMgr.GunGun.Character.Spd.dx        = DirectRoadTable[dir].Px;
                                    MGameMgr.GunGun.Character.Spd.dy        = DirectRoadTable[dir].Py;
                                    
                                    //----アニメセット
                                    MGameMgr.GunGun.AnmBase                 = GunGunDirectAnmBase[dir];
                                    MGameMgr.GunGun.Character.Anm.Data.no   = GunGunGameSpriteTable[MGameMgr.GunGun.AnmBase + MGameMgr.GunGun.Character.Anm.Index].No;
                                    
                                    break;
                                //----------------------------------------答えがある
                                case MAZE_MAP_CHAR_NUM_00:
                                case MAZE_MAP_CHAR_NUM_01:
                                case MAZE_MAP_CHAR_NUM_02:
                                case MAZE_MAP_CHAR_NUM_03:
                                case MAZE_MAP_CHAR_NUM_04:
                                case MAZE_MAP_CHAR_NUM_05:
                                case MAZE_MAP_CHAR_NUM_06:
                                case MAZE_MAP_CHAR_NUM_07:
                                case MAZE_MAP_CHAR_NUM_08:
                                case MAZE_MAP_CHAR_NUM_09:
                                case MAZE_MAP_CHAR_NUM_10:
                                    //----答えを確認
                                    if(CheckAnswer(dir))
                                    {//正解の答え
                                        GameMgr.WaitFlag = ON;          // iwasawa Correction (2003/4/27)
                                        //----ステータス変更：答え取得移動
                                        MGameMgr.GunGun.Character.Status    = GUNGUN_GET_ANSWER_WALK;
                                        
                                        //----答えインデックス++
                                        if(++MGameMgr.QuestionIndex>QuestionNumTable[MGameMgr.PlayLevel]-1)
                                        {
                                            MGameMgr.QuestionIndex  = QuestionNumTable[MGameMgr.PlayLevel]-1;
                                            MGameMgr.CheckClearFlag = 1;
                                        }
                                        
                                        //----移動&方向＆ータセット
                                        MGameMgr.GunGun.KeyDirect               = dir;
                                        MGameMgr.GunGun.Character.MoveCount     = GunGunMoveCountTable[dir];
                                        MGameMgr.GunGun.Character.Spd.dx        = DirectRoadTable[dir].Px;
                                        MGameMgr.GunGun.Character.Spd.dy        = DirectRoadTable[dir].Py;
                                        
                                        //----アニメセット
                                        MGameMgr.GunGun.AnmBase                 = GunGunDirectAnmBase[dir];
                                        MGameMgr.GunGun.Character.Anm.Data.no   = GunGunGameSpriteTable[MGameMgr.GunGun.AnmBase + MGameMgr.GunGun.Character.Anm.Index].No;
                                        
                                        
                                    }else
                                    {//不正解の答え
                                        //----移動不可、アニメはセット
                                        MGameMgr.GunGun.AnmBase                 = GunGunDirectAnmBase[dir];
                                        MGameMgr.GunGun.Character.Anm.Data.no   = GunGunGameSpriteTable[MGameMgr.GunGun.AnmBase + MGameMgr.GunGun.Character.Anm.Index].No;
                                        
                                        //----念のためクリア
                                        MGameMgr.GunGun.Character.MoveCount = 0;
                                        MGameMgr.GunGun.KeyDirect           = DIR_NOTHING;
                                        MGameMgr.GunGun.Character.Spd.dx    = 0;
                                        MGameMgr.GunGun.Character.Spd.dy    = 0;
                                    }
                                    
                                    break;
                                //----------------------------------------障害物ありなので移動はできない
                                case MAZE_MAP_CHAR_WALL:
                                case MAZE_MAP_CHAR_IWA_00:
                                case MAZE_MAP_CHAR_IWA_01:
                                case MAZE_MAP_CHAR_BAR_00:
                                case MAZE_MAP_CHAR_BAR_01:
                                case MAZE_MAP_CHAR_ENEMY:
                                default:
                                    
                                    //----移動不可、アニメはセット
                                    MGameMgr.GunGun.AnmBase                 = GunGunDirectAnmBase[dir];
                                    MGameMgr.GunGun.Character.Anm.Data.no   = GunGunGameSpriteTable[MGameMgr.GunGun.AnmBase + MGameMgr.GunGun.Character.Anm.Index].No;
                                    
                                    //----念のためクリア
                                    MGameMgr.GunGun.Character.MoveCount = 0;
                                    MGameMgr.GunGun.KeyDirect           = DIR_NOTHING;
                                    MGameMgr.GunGun.Character.Spd.dx    = 0;
                                    MGameMgr.GunGun.Character.Spd.dy    = 0;
                                    
                                    break;
                            }
                            
                        }else
                        {//----方向キー入力なし
                            //----念のためクリア
                            MGameMgr.GunGun.Character.MoveCount = 0;
                            MGameMgr.GunGun.KeyDirect           = DIR_NOTHING;
                            MGameMgr.GunGun.Character.Spd.dx    = 0;
                            MGameMgr.GunGun.Character.Spd.dy    = 0;
                        }
                    }else
                    {//----捕まった：
                        GameMgr.WaitFlag = ON;          // iwasawa Correction (2003/4/27)
                        //----ステータス変更：捕まる
                        MGameMgr.GunGun.Character.Status = GUNGUN_CAUGHT;
                        
                        //----捕まるアニメセット
                        MGameMgr.GunGun.AnmBase                 = GunGunCoughtAnmBase[MGameMgr.Kuma.MoveDirect];
                        MGameMgr.GunGun.Character.Anm.Data.no   = GunGunGameSpriteTable[MGameMgr.GunGun.AnmBase + MGameMgr.GunGun.Character.Anm.Index].No;
                        
                        //----残機数を減らす：ゲームオーバーフラグはステ-タス：捕まるにてチェック
                        if(--MGameMgr.Zanki<=0){
                            MGameMgr.Zanki=0;
                        }
                        
                        //----クマのステータスを変更：捕まえたへ
                        MGameMgr.Kuma.Character.Status  = KUMA_CATCH;
                        
                        //----タイマークリア
                        MGameMgr.GunGun.Timer                   = 0;
                        
                        //----柵タスク削除
                        pTask=SearchTask(TASK_NO_GAME_BAR);
                        if(pTask!=NULL){
                            pTask->mode = TASK_MODE_EXIT;
                        }
                        
                        //----スタータスク削除
                        pTask=SearchTask(TASK_NO_GAME_STAR);
                        if(pTask!=NULL){
                            pTask->mode = TASK_MODE_EXIT;
                        }
                    }
                    
                    break;
                //--------------------------------移動
                case GUNGUN_WALK:
                    MGameMgr.GunGun.Character.Pos.x += MGameMgr.GunGun.Character.Spd.dx*MGameMgr.GunGun.Character.Spd.sx;
                    MGameMgr.GunGun.Character.Pos.y += MGameMgr.GunGun.Character.Spd.dy*MGameMgr.GunGun.Character.Spd.sy;
                    
                    
//                  //----捕まり判定
//                  if( !CheckCought(MGameMgr.GunGun.Px,MGameMgr.GunGun.Py,MGameMgr.Kuma.Px,MGameMgr.Kuma.Py) )
//                  {//捕まっていない
//                      
//                  }else
//                  {//捕まった
//                      //----ステータス変更：捕まる
//                      MGameMgr.GunGun.Character.Status = GUNGUN_CAUGHT;
//                      
//                      //----捕まるアニメセット
//                      MGameMgr.GunGun.AnmBase                 = GunGunCoughtAnmBase[MGameMgr.Kuma.MoveDirect];
//                      MGameMgr.GunGun.Character.Anm.Data.no   = GunGunGameSpriteTable[MGameMgr.GunGun.AnmBase + MGameMgr.GunGun.Character.Anm.Index].No;
//                      
//                      //----残機数を減らす：ゲームオーバーフラグはステ-タス：捕まるにてチェック
//                      if(--MGameMgr.Zanki<=0){
//                          MGameMgr.Zanki=0;
//                      }
//                      
//                      //----クマのステータスを変更：捕まえたへ
//                      MGameMgr.Kuma.Character.Status  = KUMA_CATCH;
//                      
//                      //----タイマークリア
//                      MGameMgr.GunGun.Timer           = 0;
//                      
//                      //----柵タスク削除
//                      pTask=SearchTask(TASK_NO_GAME_BAR);
//                      if(pTask!=NULL){
//                          pTask->mode = TASK_MODE_EXIT;
//                      }
//                      
//                      //----スタータスク削除
//                      pTask=SearchTask(TASK_NO_GAME_STAR);
//                      if(pTask!=NULL){
//                          pTask->mode = TASK_MODE_EXIT;
//                      }
//                  }
                    
                    //----移動終了
                    if(--MGameMgr.GunGun.Character.MoveCount <= 0)
                    {
                        //----ステータス変更：キー待ちへ
                        MGameMgr.GunGun.Character.Status = GUNGUN_WAIT;
                        
                        //----マップ位置移動（完全に移動が終了してからマップ上の位置を移動）
                        switch(MGameMgr.GunGun.KeyDirect)
                        {
                            case DIR_UP:
                                if(--MGameMgr.GunGun.Py < 1){
                                    MGameMgr.GunGun.Py=1;
                                }
                                break;
                            case DIR_DOWN:
                                if(++MGameMgr.GunGun.Py >= MAZE_GAME_SQUARE_H_NUM+1){
                                    MGameMgr.GunGun.Py=MAZE_GAME_SQUARE_H_NUM-1+1;
                                }
                                break;
                            case DIR_LEFT:
                                if(--MGameMgr.GunGun.Px < 1){
                                    MGameMgr.GunGun.Px=1;
                                }
                                break;
                            case DIR_RIGHT:
                                if(++MGameMgr.GunGun.Px>=MAZE_GAME_SQUARE_W_NUM+1){
                                    MGameMgr.GunGun.Px=MAZE_GAME_SQUARE_W_NUM-1+1;
                                }
                                break;
                            default:
                        }
                        
                        //優先順位変更
                        MGameMgr.GunGun.Character.Pos.z = PRIORITY_MAZE_GAME_GUNGUN - MGameMgr.GunGun.Py;
                        
                        //----星があるのかチェック
                        if( CheckStarPos(MGameMgr.GunGun.Px,MGameMgr.GunGun.Py) )
                        {
                            //----星タスク削除
                            pTask=SearchTask(TASK_NO_GAME_STAR);
                            if(pTask!=NULL){
                                pTask->mode = TASK_MODE_EXIT;
                            }
                            
                            //----ハチタスク生成
                            Task.func       = BeeTask;
                            Task.priority   = TASK_NO_GAME_BEE;
                            Task.attribute  = ATTR_USER;
                            Task.status     = TASK_NEW_ENTRY;
                            Task.id         = TASK_NO_GAME_BEE;
                            Task.wait_time  = 0;
                            Task.buf        = NULL;
                            Task.name       = "BeeTask";
                            Task.mode       = TASK_MODE_INIT;
                            Task.user[0]    = MGameMgr.GunGun.Px;
                            Task.user[1]    = MGameMgr.GunGun.Py;
                            CreateTask(&Task);
                        }
                        
                        //----移動方向クリア
                        MGameMgr.GunGun.KeyDirect       = DIR_NOTHING;
                    }
                    
                    break;
                //--------------------------------答え取得移動
                case GUNGUN_GET_ANSWER_WALK:
                    
                    MGameMgr.GunGun.Character.Pos.x += MGameMgr.GunGun.Character.Spd.dx*MGameMgr.GunGun.Character.Spd.sx;
                    MGameMgr.GunGun.Character.Pos.y += MGameMgr.GunGun.Character.Spd.dy*MGameMgr.GunGun.Character.Spd.sy;
                    
                    //----移動終了まで待ち
                    if(--MGameMgr.GunGun.Character.MoveCount <= 0)
                    {
                        //[♪]ピロン
                        ssPlaySe(MAZU_SE_10);
                        
                        //[♪]
                        dsPlayXa(XA_FILE_MAZU03,7);
                        MGameMgr.GunGun.XaWaitTimer = GET_DA_STATUS_WAIT_TIME;
                        MGameMgr.GunGun.XaFlag      = 1;
                        
                        //----ステータス変更：クリアへ
                        MGameMgr.GunGun.Character.Status = GUNGUN_CLEAR;
                        
                        //----マップ位置移動（完全に移動が終了してからマップ上の位置を移動）
                        switch(MGameMgr.GunGun.KeyDirect)
                        {
                            case DIR_UP:
                                if(--MGameMgr.GunGun.Py < 1){
                                    MGameMgr.GunGun.Py=1;
                                }
                                break;
                            case DIR_DOWN:
                                if(++MGameMgr.GunGun.Py >= MAZE_GAME_SQUARE_H_NUM+1){
                                    MGameMgr.GunGun.Py=MAZE_GAME_SQUARE_H_NUM-1+1;
                                }
                                break;
                            case DIR_LEFT:
                                if(--MGameMgr.GunGun.Px < 1){
                                    MGameMgr.GunGun.Px=1;
                                }
                                break;
                            case DIR_RIGHT:
                                if(++MGameMgr.GunGun.Px>=MAZE_GAME_SQUARE_W_NUM+1){
                                    MGameMgr.GunGun.Px=MAZE_GAME_SQUARE_W_NUM-1+1;
                                }
                                break;
                            default:
                        }
                        
                        //----移動方向クリア：上の処理で移動が完了後行います
                        MGameMgr.GunGun.KeyDirect   = DIR_NOTHING;

                        //----マップ上の答えをクリア：上の処理で移動が完了後行います
                        ClearAnswer(MGameMgr.GunGun.Px,MGameMgr.GunGun.Py);
                        
                        //----クリアアニメをセット
                        MGameMgr.GunGun.AnmBase                 = GUNGUN_ANM_BASE_CLEAR;
                        MGameMgr.GunGun.Character.Anm.Data.no   = GunGunGameSpriteTable[MGameMgr.GunGun.AnmBase + MGameMgr.GunGun.Character.Anm.Index].No;
                        
                        //----タイマークリア
                        MGameMgr.GunGun.Timer=0;

                        //----クイズタスクのメインの中のモードを変更
                        MGameMgr.Question.Mode          = QUESTION_OK;
                        MGameMgr.Question.AnswerFlag    = 1;

                        //----クマのステータスを変更：クリア
                        MGameMgr.Kuma.Character.Status  = KUMA_CLEAR;

                        //----柵タスク削除
                        pTask=SearchTask(TASK_NO_GAME_BAR);
                        if(pTask!=NULL){
                            pTask->mode = TASK_MODE_EXIT;
                        }

                        //----星タスク削除
                        pTask=SearchTask(TASK_NO_GAME_STAR);
                        if(pTask!=NULL){
                            pTask->mode = TASK_MODE_EXIT;
                        }
                    }

                    break;
                //--------------------------------正解
                case GUNGUN_CORRECT_ANSWER:
                    
                    
                    
                    
                    break;
                //--------------------------------クリア
                case GUNGUN_CLEAR:
                    
                    if(--MGameMgr.GunGun.XaWaitTimer<=0){
                        if(dSoundStatus == DslStatStandby){
                            //XA再生終了
                            
                            //----ステータス変更：消えるへ
                            MGameMgr.GunGun.Character.Status = GUNGUN_DISAPPEAR;
                            
                            //----煙アニメをセット
                            MGameMgr.GunGun.AnmBase                     = GUNGUN_ANM_BASE_SMOKE;
                            MGameMgr.GunGun.Character.Anm.Index         = 0;
                            MGameMgr.GunGun.Character.Anm.Data.no       = GunGunGameSpriteTable[MGameMgr.GunGun.AnmBase + MGameMgr.GunGun.Character.Anm.Index].No;
                            MGameMgr.GunGun.Character.Anm.Data.wt       = 0;
                            
                            //----タイマークリア
                            MGameMgr.GunGun.Timer                   = 0;
                            
                            //----クマのステータスを変更：消えるへ
                            MGameMgr.Kuma.Character.Status = KUMA_DISAPPEAR;
                            
                            //----クマのアニメ設定
                            MGameMgr.Kuma.AnmBase                   = KUMA_ANM_BASE_SMOKE;
                            MGameMgr.Kuma.Character.Anm.Index       = 0;
                            MGameMgr.Kuma.Character.Anm.Data.no     = KumaGameSpriteTable[MGameMgr.Kuma.AnmBase + MGameMgr.Kuma.Character.Anm.Index].No;
                            MGameMgr.Kuma.Character.Anm.Data.wt     = 0;
                            
                            //[♪]ドン
                            ssPlaySe(MAZU_SE_07);
                        }
                    }
                    
                    break;
                //--------------------------------消える
                case GUNGUN_DISAPPEAR:
                    
                    if(++MGameMgr.GunGun.Timer>GUNGUN_GAME_DISAPPEAR_WAIT_TIME)
                    {
                        if(MGameMgr.CheckClearFlag)
                        {//----クリア
                            //----ステータス変更：イベント待ちへ
                            MGameMgr.GunGun.Character.Status = GUNGUN_EVENT_WAIT;
                            
                            //----クリアフラグセット
                            MGameMgr.ClearFlag  = 1;
                            
                            //----レベルアップ
                            if(++MGameMgr.PlayLevel>MAZE_GAME_MAX_LEVEL_NUM-1)
                            {
                                MGameMgr.PlayLevel=MAZE_GAME_MAX_LEVEL_NUM-1;
                                
                                //オールクリアフラグセット
                                MGameMgr.AllClearFlag   = 1;
                            }
                            
                            //
                            if(MGameMgr.PlayLevel>MGameMgr.Level)
                            {//前回のレベルより高い場合は書き換える
                                MGameMgr.Level=MGameMgr.PlayLevel;
                            }
                            
                        }else
                        {//----次へ
                            //----グングンタスク初期化
                            ip_task->mode = TASK_MODE_INIT;
                            
                            //----タイマークリア
                            MGameMgr.GunGun.Timer   = 0;
                            
                            //----クマタスク初期化
                            pTask       = SearchTask(TASK_NO_GAME_KUMA);
                            pTask->mode = TASK_MODE_INIT;
                            
                            //----クイズタスクのメインの中のモードを変更
                            MGameMgr.Question.Mode  = QUESTION_NEXT_UP;
                        }
                    }
                    break;
                //--------------------------------イベント待ち
                case GUNGUN_EVENT_WAIT:
                    break;
                //--------------------------------捕まる
                case GUNGUN_CAUGHT:
                    //----一定時間捕まった絵で待つ
                    if(++MGameMgr.GunGun.Timer>GUNGUN_GAME_CATCH_WAIT_TIME)
                    {
                        //----グングンタスク初期化
                        ip_task->mode = TASK_MODE_INIT;
                        
                        //----残機数がゼロの場合はゲームオーバー
                        if(MGameMgr.Zanki==0)
                        {
                            MGameMgr.GameOverFlag = 1;
                        }else
                        {
                            //----クマタスク初期化
                            pTask       = SearchTask(TASK_NO_GAME_KUMA);
                            pTask->mode = TASK_MODE_INIT;
                            
                            //[♪]ドン
                            ssPlaySe(MAZU_SE_07);
                            
                            //----クイズタスクのメインの中のモードを変更
                            MGameMgr.Question.Mode  = QUESTION_NEXT_NONE;
                        }
                    }
                    
                    if(MGameMgr.GunGun.Timer==140){
                        //[♪]ありゃー
                        ssPlaySe(MAZU_SE_01);
                    }
                    
                    break;
                //--------------------------------星を踏む
                case GUNGUN_STAR_STEP:
                    break;
                default:
            }
            
            //----アニメ切り替え
            if(++MGameMgr.GunGun.Character.Anm.Data.wt > GUNGUN_GAME_ANM_WAIT_TIME)
            {
                MGameMgr.GunGun.Character.Anm.Data.wt   = 0;
                MGameMgr.GunGun.Character.Anm.Index ^=1;
                MGameMgr.GunGun.Character.Anm.Data.no   = GunGunGameSpriteTable[MGameMgr.GunGun.AnmBase + MGameMgr.GunGun.Character.Anm.Index].No;
            }
            
            //----描画
            SpData.No       = MGameMgr.GunGun.Character.Anm.Data.no;
            SpData.PosX     = MGameMgr.GunGun.Character.Pos.x + MGameMgr.GunGun.Character.OPos.x + GunGunGameSpriteTable[MGameMgr.GunGun.AnmBase + MGameMgr.GunGun.Character.Anm.Index].Ofx;
            SpData.PosY     = MGameMgr.GunGun.Character.Pos.y + MGameMgr.GunGun.Character.OPos.y + GunGunGameSpriteTable[MGameMgr.GunGun.AnmBase + MGameMgr.GunGun.Character.Anm.Index].Ofy;
            SpData.PosZ     = MGameMgr.GunGun.Character.Pos.z + MGameMgr.GunGun.Character.OPos.z;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );
            
            break;
        //----------------------------------------------------------------タスク終了
        case TASK_MODE_EXIT:
            
            
            //----自分を削除
            ExitTask(ip_task->id);
            break;
        default:
    }
    
    return TRUE;
}


//-----------------------------------------------------------------------------
//  関数名  :GunGunZankiTask
//
//  work    :グングン残機タスク
//  in      :TASK* ip_task  タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int GunGunZankiTask(TASK* ip_task)
{
    static SPRITE_DATA SpData;
    int i;


    switch(ip_task->mode)
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //----MODE NEXT
            ip_task->mode = TASK_MODE_MAIN;
            
            break;
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:
            
            for(i=0;i<MGameMgr.Zanki;i++){
                SpData.No       = MAZE_CHAR_GAME_GUNGUN_MARK;
                SpData.PosX     = GUNGUN_MARK_POS_X+GUNGUN_MARK_KANKAKU_X*2 - GUNGUN_MARK_KANKAKU_X*i;
                SpData.PosY     = GUNGUN_MARK_POS_Y;
                SpData.PosZ     = PRIORITY_MAZE_GAME_GUNGUN_MARK;
                SpData.ScaleX   = SCALE10;
                SpData.ScaleY   = SCALE10;
                SpData.Rotate   = ROTATE000;
                SpData.Reverse  = NOREVERS;
                DrawSprite( &SpData );
            }
            
            break;
        //----------------------------------------------------------------タスク終了
        case TASK_MODE_EXIT:
            
            //----自分を削除
            ExitTask(ip_task->id);
            break;
        default:
    }
}


//-----------------------------------------------------------------------------
//  関数名  :KumaTask
//
//  work    :クマタスク
//  in      :TASK* ip_task  タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int KumaTask(TASK* ip_task)
{
    static int KumaDirectAnmBase[]={
        KUMA_ANM_BASE_UP,
        KUMA_ANM_BASE_DOWN,
        KUMA_ANM_BASE_LEFT,
        KUMA_ANM_BASE_RIGHT,
    };

    static int KumaMoveCountTable[]={
        MAZE_GAME_SQUARE_H,
        MAZE_GAME_SQUARE_H,
        MAZE_GAME_SQUARE_W,
        MAZE_GAME_SQUARE_W,
    };

    static SPRITE_DATA SpData;
    TASK Task;
    TASK *pTask;
    int i,j,kmvdir,kmvflag,rval;


//  FntPrint("\n\n\n\n");
//  FntPrint("VINDEX=[%2d]\n",MGameMgr.VisitIndex);
//  FntPrint("KUMAPOS=[%2d][%2d]\n", MGameMgr.Kuma.Px,MGameMgr.Kuma.Py);
//
//  FntPrint("\n\n\n\n\n\n\n\n");
//  for(i=0;i<MAZE_GAME_SQUARE_H_NUM+2;i++){
//      for(j=0;j<MAZE_GAME_SQUARE_W_NUM+2;j++){
//          FntPrint("%2d",MGameMgr.WorkMap.Data[i][j]);
//      }
//      FntPrint("\n");
//  }



#ifdef __DEBUG_MAZE__
    FntPrint("(x,y)=(%2d,%2d)\n",wSx,wSy);
    if(MGameMgr.Kuma.ThinkMode==THINK_MODE_SEARCH){
        DrawSearchRoad(MGameMgr.VisitIndex);
    }
#endif

    switch(ip_task->mode)
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //----MODE NEXT
            ip_task->mode = TASK_MODE_MAIN;
            
            //----クマ初期化
            MGameMgr.Kuma.Character.Status      = KUMA_APPEAR;              //継続プレイの場合は"???"に設定する
            MGameMgr.Kuma.Character.Anm.Data.no = KumaGameSpriteTable[KUMA_ANM_BASE_SMOKE].No;
            MGameMgr.Kuma.Character.Anm.Data.wt = 0;
            MGameMgr.Kuma.Character.Anm.Index   = 0;
            MGameMgr.Kuma.Character.Pos.x       = MAZE_GAME_MAP_LEFT_X + KUMA_INIT_MAP_OFFSET_X + (KUMA_INIT_PX) * MAZE_GAME_SQUARE_W;
            MGameMgr.Kuma.Character.Pos.y       = MAZE_GAME_MAP_LEFT_Y + KUMA_INIT_MAP_OFFSET_Y + (KUMA_INIT_PY) * MAZE_GAME_SQUARE_H;
            MGameMgr.Kuma.Character.Pos.z       = PRIORITY_MAZE_GAME_KUMA;
            MGameMgr.Kuma.Character.OPos.x      = KUMA_ANM_OFSET_X;
            MGameMgr.Kuma.Character.OPos.y      = KUMA_ANM_OFSET_Y;
            MGameMgr.Kuma.Character.OPos.z      = 0;
            MGameMgr.Kuma.Character.Spd.dx      = 0;
            MGameMgr.Kuma.Character.Spd.dy      = 0;
            MGameMgr.Kuma.Character.Spd.sx      = 1;
            MGameMgr.Kuma.Character.Spd.sy      = 1;
            MGameMgr.Kuma.Character.MoveCount   = 0;
            MGameMgr.Kuma.ThinkMode             = THINK_MODE_RANDOM;
            MGameMgr.Kuma.LastThinkMode         = THINK_MODE_RANDOM;
            MGameMgr.Kuma.Flag                  = 1;
            MGameMgr.Kuma.BarFlag               = 0;
            MGameMgr.Kuma.StarFlag              = 0;
            MGameMgr.Kuma.AnmBase               = KUMA_ANM_BASE_SMOKE;      //継続プレイの場合はアニメセットを変更する
            MGameMgr.Kuma.Timer                 = 0;
            MGameMgr.Kuma.Px                    = KUMA_INIT_PX;
            MGameMgr.Kuma.Py                    = KUMA_INIT_PY;
            MGameMgr.Kuma.MoveDirect            = DIR_NOTHING;
            
            break;
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:
            
        //  FntPrint("KUMA-PXPY=(%2d,%2d)\n",   MGameMgr.Kuma.Px,MGameMgr.Kuma.Py);
            
            switch(MGameMgr.Kuma.Character.Status)
            {
                //--------------------------------出現
                case KUMA_APPEAR:
                    if(++MGameMgr.Kuma.Timer>KUMA_APPEAR_TIME)
                    {
                        //----ステータス変更：出現後待ちへ
                        MGameMgr.Kuma.Character.Status = KUMA_APPEAR_WAIT;
                        
                        //----アニメ設定
                        MGameMgr.Kuma.AnmBase               = KUMA_ANM_BASE_DOWN;
                        MGameMgr.Kuma.Character.Anm.Data.no = KumaGameSpriteTable[MGameMgr.Kuma.AnmBase + MGameMgr.Kuma.Character.Anm.Index].No;
                        
                        //---タイマークリア
                        MGameMgr.Kuma.Timer = 0;
                    }
                    
                    break;
                //--------------------------------出現後待ち
                case KUMA_APPEAR_WAIT:
                    //クイズタスクでXA再生が終了するのを待ちます
                    
                    break;
                //--------------------------------待ち（何もしなしで待つ、動けない場合などの為）
                case KUMA_WAIT:
                    //----レベルにより待ち時間を調整
                    if(++MGameMgr.Kuma.Timer>KumaWaitTimeTable[MGameMgr.PlayLevel])
                    {
                        //★ただいまテスト中ランダム移動へ、まずは基本動作を作成する。
                        
                        //----ステータス変更：考るへ
                        MGameMgr.Kuma.Character.Status = KUMA_THINK;
                        
                        //----思考モード
                        //----前回の思考モード保存
                        MGameMgr.Kuma.LastThinkMode = MGameMgr.Kuma.ThinkMode;
                        if(  rand()%100 < KumaThinkModeProbabilityTable[MGameMgr.PlayLevel] )
                        {//----探索
                            MGameMgr.Kuma.ThinkMode = THINK_MODE_SEARCH;
                        }else
                        {//----ランダム
                            MGameMgr.Kuma.ThinkMode = THINK_MODE_RANDOM;
                        }
                        
                        //----タイマークリア
                        MGameMgr.Kuma.Timer=0;
                    }
                    
                    break;
                //--------------------------------考る
                case KUMA_THINK:
                    kmvdir=0;
                    if(MGameMgr.Kuma.ThinkMode==THINK_MODE_RANDOM)
                    {
                        kmvflag = GetKumaRandomMoveDirect(&kmvdir);
                    }else{
                        kmvflag = SearchGunGun(&kmvdir);
                    }

//                  kmvflag = GetKumaRandomMoveDirect(&kmvdir);

                    //----ランダムで移動
                    if( kmvflag )
                    {//----移動可能
                        //----ステータス変更：ランダム移動へ
                        MGameMgr.Kuma.Character.Status = KUMA_WALK;
                        
                        //----アニメ設定
                        MGameMgr.Kuma.AnmBase               = KumaDirectAnmBase[kmvdir];
                        MGameMgr.Kuma.Character.Anm.Data.no = KumaGameSpriteTable[MGameMgr.Kuma.AnmBase + MGameMgr.Kuma.Character.Anm.Index].No;
                        
                        //----移動データセット
                        MGameMgr.Kuma.Character.Spd.dx      = DirectRoadTable[kmvdir].Px;
                        MGameMgr.Kuma.Character.Spd.dy      = DirectRoadTable[kmvdir].Py;
                        MGameMgr.Kuma.Character.MoveCount   = KumaMoveCountTable[kmvdir];
                        MGameMgr.Kuma.MoveDirect            = kmvdir;
                        
                        //----タイマークリア
                        MGameMgr.Kuma.Timer = 0;
                        
                        //----柵生成:ランダムで生成、必ずマップ上の位置は移動前のものを取得、下の処理の上で行う
                        if( (rand()%100) < BAR_BIRTH_PROBABILITY )
                        {
                        //  if( !CheckGunGunPos(MGameMgr.Kuma.Px,MGameMgr.Kuma.Py) )
                            if( !CheckGunGunPosArea(MGameMgr.Kuma.Px,MGameMgr.Kuma.Py) )
                            {//そのエリアにグングンがいなければ柵を生成する
                                //柵は１つ以上作成しない
                                if(MGameMgr.Kuma.BarFlag==0)
                                {
                                    //----タスク生成
                                    Task.func       = BarTask;
                                    Task.priority   = TASK_NO_GAME_BAR;
                                    Task.attribute  = ATTR_USER;
                                    Task.status     = TASK_NEW_ENTRY;
                                    Task.id         = TASK_NO_GAME_BAR;
                                    Task.wait_time  = 0;
                                    Task.buf        = NULL;
                                    Task.name       = "BarTask";
                                    Task.mode       = TASK_MODE_INIT;
                                    Task.user[0]    = MGameMgr.Kuma.Px;
                                    Task.user[1]    = MGameMgr.Kuma.Py;
                                    CreateTask(&Task);
                                }
                            }
                        }
                        
                        //----星生成
                        if( (rand()%100) < STAR_BIRTH_PROBABILITY )
                        {
                            //----ハチタスクが存在する場合は生成しない
                            pTask=SearchTask(TASK_NO_GAME_BEE);
                            if(pTask==NULL)
                            {
                                rval = rand()%35;
                                if( !CheckGunGunPos(StarPosTable[rval].Px,StarPosTable[rval].Py) )
                                {//その位置にグングンがいなければ星を生成する
                                    //星は１つ以上作成しない
                                    if(MGameMgr.Kuma.StarFlag==0)
                                    {
                                        //星タスクが存在する場合は生成しない
                                        pTask=SearchTask(TASK_NO_GAME_STAR);
                                        if(pTask==NULL){
                                            //----タスク生成
                                            Task.func       = StarTask;
                                            Task.priority   = TASK_NO_GAME_STAR;
                                            Task.attribute  = ATTR_USER;
                                            Task.status     = TASK_NEW_ENTRY;
                                            Task.id         = TASK_NO_GAME_STAR;
                                            Task.wait_time  = 0;
                                            Task.buf        = NULL;
                                            Task.name       = "StarTask";
                                            Task.mode       = TASK_MODE_INIT;
                                            Task.user[0]    = StarPosTable[rval].Px;
                                            Task.user[1]    = StarPosTable[rval].Py;
                                            CreateTask(&Task);
                                        }
                                    }
                                }
                            }
                        }
                        
                        //----マップ位置移動移動する前にマップ上の位置を移動）
                        switch(MGameMgr.Kuma.MoveDirect)
                        {
                            case DIR_UP:
                                if(--MGameMgr.Kuma.Py < 1){
                                    MGameMgr.Kuma.Py = 1;
                                }
                                break;
                            case DIR_DOWN:
                                if(++MGameMgr.Kuma.Py >= MAZE_GAME_SQUARE_H_NUM+1){
                                    MGameMgr.Kuma.Py = MAZE_GAME_SQUARE_H_NUM-1+1;
                                }
                                break;
                            case DIR_LEFT:
                                if(--MGameMgr.Kuma.Px < 1){
                                    MGameMgr.Kuma.Px = 1;
                                }
                                break;
                            case DIR_RIGHT:
                                if(++MGameMgr.Kuma.Px >= MAZE_GAME_SQUARE_W_NUM+1){
                                    MGameMgr.Kuma.Px = MAZE_GAME_SQUARE_W_NUM-1+1;
                                }
                                break;
                            default:
                        }
                        
                    }else
                    {//----移動不可能
                        //----ステータス変更：待ちへ
                        MGameMgr.Kuma.Character.Status = KUMA_WAIT;
                        
                        //----移動データクリア
                        MGameMgr.Kuma.Character.Spd.dx      = 0;
                        MGameMgr.Kuma.Character.Spd.dy      = 0;
                        MGameMgr.Kuma.Character.MoveCount   = 0;
                        MGameMgr.Kuma.MoveDirect            = DIR_NOTHING;
                        
                        //----タイマークリア
                        MGameMgr.Kuma.Timer = 0;
                    }
                    
                    break;
                //--------------------------------移動
                case KUMA_WALK:
                    MGameMgr.Kuma.Character.Pos.x   += MGameMgr.Kuma.Character.Spd.dx * MGameMgr.Kuma.Character.Spd.sx;
                    MGameMgr.Kuma.Character.Pos.y   += MGameMgr.Kuma.Character.Spd.dy * MGameMgr.Kuma.Character.Spd.sy;
                    
                    if(--MGameMgr.Kuma.Character.MoveCount <= 0)
                    {//----移動終了
                        //----ステータス変更：待ちへ
                        MGameMgr.Kuma.Character.Status = KUMA_WAIT;
                        
                        //----タイマークリア
                        MGameMgr.Kuma.Timer = 0;
                        
                        //----移動方向クリア
                        MGameMgr.Kuma.MoveDirect        = DIR_NOTHING;
                        
                        //優先順位変更
                        MGameMgr.Kuma.Character.Pos.z   = PRIORITY_MAZE_GAME_KUMA - MGameMgr.Kuma.Py;
                    }
                    
                    break;
                //--------------------------------捕まえた
                case KUMA_CATCH:
                    //----表示オフ
                    MGameMgr.Kuma.Flag              = 0;
                    
                    //----ステータス変更：捕また待ちへ
                    MGameMgr.Kuma.Character.Status = KUMA_CATCH_WAIT;
                    
                    //[♪]つーかまえた
                    ssPlaySe(MAZU_SE_02);
                    break;
                //--------------------------------捕また待ち
                case KUMA_CATCH_WAIT:
                    //----グングンがこちらのステータスを変更するまで何もしないで待ち
                    
                    break;
                //--------------------------------蜂に刺さされて暴れる
                case KUMA_BEE_BITE_OUCH:
                    if(++MGameMgr.Kuma.Timer>KUMA_BITE_OUCH_WAIT_TIME)
                    {
                        //----ステータス変更：待ちへ
                        MGameMgr.Kuma.Character.Status  = KUMA_WAIT;

                        //----位置補正
                        MGameMgr.Kuma.Character.Pos.x   = MAZE_GAME_MAP_LEFT_X + KUMA_INIT_MAP_OFFSET_X + (MGameMgr.Kuma.Px) * MAZE_GAME_SQUARE_W;
                        MGameMgr.Kuma.Character.Pos.y   = MAZE_GAME_MAP_LEFT_Y + KUMA_INIT_MAP_OFFSET_Y + (MGameMgr.Kuma.Py) * MAZE_GAME_SQUARE_H;
                        
                        //----アニメ設定
                        MGameMgr.Kuma.AnmBase               = KumaDirectAnmBase[1];
                        MGameMgr.Kuma.Character.Anm.Data.no = KumaGameSpriteTable[MGameMgr.Kuma.AnmBase + MGameMgr.Kuma.Character.Anm.Index].No;

                        //----タイマークリア
                        MGameMgr.Kuma.Timer = 0;
                    }
                    

                    break;
                //--------------------------------クリア
                case KUMA_CLEAR:
                    //----グングンがこちらのステータスを変更するまで何もしないで待ち
                    
                    break;
                //--------------------------------消える
                case KUMA_DISAPPEAR:
                    
                    break;
                default:
            }

            //アニメ切り替え
            if(++MGameMgr.Kuma.Character.Anm.Data.wt > KUMA_GAME_ANM_WAIT_TIME)
            {
                MGameMgr.Kuma.Character.Anm.Data.wt = 0;
                MGameMgr.Kuma.Character.Anm.Index ^=1;
                MGameMgr.Kuma.Character.Anm.Data.no = KumaGameSpriteTable[MGameMgr.Kuma.AnmBase + MGameMgr.Kuma.Character.Anm.Index].No;
            }

            if(MGameMgr.Kuma.Flag){
                //描画
                SpData.No       = MGameMgr.Kuma.Character.Anm.Data.no;
                SpData.PosX     = MGameMgr.Kuma.Character.Pos.x + MGameMgr.Kuma.Character.OPos.x + KumaGameSpriteTable[MGameMgr.Kuma.AnmBase + MGameMgr.Kuma.Character.Anm.Index].Ofx;
                SpData.PosY     = MGameMgr.Kuma.Character.Pos.y + MGameMgr.Kuma.Character.OPos.y + KumaGameSpriteTable[MGameMgr.Kuma.AnmBase + MGameMgr.Kuma.Character.Anm.Index].Ofy;
                SpData.PosZ     = MGameMgr.Kuma.Character.Pos.z + MGameMgr.Kuma.Character.OPos.z;
                SpData.ScaleX   = SCALE10;
                SpData.ScaleY   = SCALE10;
                SpData.Rotate   = ROTATE000;
                SpData.Reverse  = NOREVERS;
                DrawSprite( &SpData );
            }

            break;
        //----------------------------------------------------------------タスク終了
        case TASK_MODE_EXIT:
            
            
            
            //----自分を削除
            ExitTask(ip_task->id);
            break;
        default:
    }

    return TRUE;
}


//-----------------------------------------------------------------------------
//  関数名  :BeeTask
//
//  work    :ハチタスク
//  in      :タスクポインタ　TASK* ip_task
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int BeeTask(TASK* ip_task)
{
    static MAZE_SPRITE_DATA BeeSpriteTable[]=
    {
        {   MAZE_CHAR_GAME_BEE_LEFT,    0,  0   },
        {   MAZE_CHAR_GAME_BEE_RIGHT,   0,  0   },
    };

    SPRITE_DATA SpData;
    int sx,sy,wx,wy;;


    switch(ip_task->mode)
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //----TASK MODE NEXT MAIN 
            ip_task->mode = TASK_MODE_MAIN;
            
            //----初期化
            MGameMgr.Bee.Px                     = ip_task->user[0];
            MGameMgr.Bee.Py                     = ip_task->user[1];
            MGameMgr.Bee.Character.Status       = 0;
            MGameMgr.Bee.Character.Anm.Data.no  = 0;
            MGameMgr.Bee.Character.Anm.Data.wt  = 0;
            MGameMgr.Bee.Character.Anm.Index    = 0;
            MGameMgr.Bee.Character.Pos.x        = MAZE_GAME_MAP_LEFT_X + (MGameMgr.Bee.Px)*MAZE_GAME_SQUARE_W +BEE_ANM_OFSET_X;
            MGameMgr.Bee.Character.Pos.y        = MAZE_GAME_MAP_LEFT_Y + (MGameMgr.Bee.Py)*MAZE_GAME_SQUARE_H +BEE_ANM_OFSET_Y;
            MGameMgr.Bee.Character.Pos.z        = PRIORITY_MAZE_GAME_BEE;
            MGameMgr.Bee.Character.OPos.x       = BEE_ANM_OFSET_X;
            MGameMgr.Bee.Character.OPos.y       = BEE_ANM_OFSET_Y;
            MGameMgr.Bee.Character.OPos.z       = 0;
            MGameMgr.Bee.Character.Spd.dx       = 0;
            MGameMgr.Bee.Character.Spd.dy       = 0;
            MGameMgr.Bee.Character.Spd.sx       = BEE_SPEED_X;
            MGameMgr.Bee.Character.Spd.sy       = BEE_SPEED_Y;
            MGameMgr.Bee.Timer                  = 0;
            
            //----移動方向セット
            sx  = MGameMgr.Kuma.Px - MGameMgr.Bee.Px;
            sy  = MGameMgr.Kuma.Py - MGameMgr.Bee.Py;
            
            if(sx>0){//右
                sx=1;
                MGameMgr.Bee.Character.Anm.Data.no  = BeeSpriteTable[1].No;
            }else
            if(sx<0){//左
                MGameMgr.Bee.Character.Anm.Data.no  = BeeSpriteTable[0].No;
                sx=-1;
            }else{
                MGameMgr.Bee.Character.Anm.Data.no  = BeeSpriteTable[0].No;
                sx=0;
            }

            if(sy>0){//下
                sy=1;
            }else
            if(sy<0){//上
                sy=-1;
            }else{
                sy=0;
            }

            MGameMgr.Bee.Character.Spd.dx       = sx;
            MGameMgr.Bee.Character.Spd.dy       = sy;
            
            break;
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:

            //----念の為
            if(++MGameMgr.Bee.Timer>300){
                //----ハチタスク終了
                ip_task->mode=TASK_MODE_EXIT;
            }

            if(!(MGameMgr.Bee.Timer%20)){
                //[♪]ビー
                ssPlaySe(MAZU_SE_04);
            }

            //----移動
            wx  = MGameMgr.Kuma.Character.Pos.x - MGameMgr.Bee.Character.Pos.x;
            wy  = MGameMgr.Kuma.Character.Pos.y - MGameMgr.Bee.Character.Pos.y;

            if(wx>=0){//右
                MGameMgr.Bee.Character.Spd.dx = 1;
            }else
            if(wx<0){//左
                MGameMgr.Bee.Character.Spd.dx = -1;
            }

            if(wy>=0){//下
                MGameMgr.Bee.Character.Spd.dy = 1;
            }else
            if(wy<0){//上
                MGameMgr.Bee.Character.Spd.dy = -1;
            }

            if( ABS(wx) > BEE_NOMOVE_AREA ){
                MGameMgr.Bee.Character.Pos.x += MGameMgr.Bee.Character.Spd.sx * MGameMgr.Bee.Character.Spd.dx;
            }
            if( ABS(wy) > BEE_NOMOVE_AREA ){
                MGameMgr.Bee.Character.Pos.y += MGameMgr.Bee.Character.Spd.sy * MGameMgr.Bee.Character.Spd.dy;
            }

            //----ヒット
            if( ABS(wx) < BEE_ATTACK_AREA){
                if( ABS(wy) < BEE_ATTACK_AREA )
                {
                    //----ハチタスク終了
                    ip_task->mode=TASK_MODE_EXIT;
                    
                    //----クマステータス変更：はち刺され
                    MGameMgr.Kuma.Character.Status  = KUMA_BEE_BITE_OUCH;
                    
                    //----アニメ設定
                    MGameMgr.Kuma.AnmBase               = 27;
                    MGameMgr.Kuma.Character.Anm.Data.no = KumaGameSpriteTable[MGameMgr.Kuma.AnmBase + MGameMgr.Kuma.Character.Anm.Index].No;
                    
                    //[♪]やった
                    ssPlaySe(MAZU_SE_00);
                }
            }
            
            //----描画
            SpData.No       = MGameMgr.Bee.Character.Anm.Data.no;
            SpData.PosX     = MGameMgr.Bee.Character.Pos.x + MGameMgr.Bee.Character.OPos.x;
            SpData.PosY     = MGameMgr.Bee.Character.Pos.y + MGameMgr.Bee.Character.OPos.y;
            SpData.PosZ     = MGameMgr.Bee.Character.Pos.z;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );
            
            break;
        //----------------------------------------------------------------タスク終了
        case TASK_MODE_EXIT:
            
            
            //----自分を削除
            ExitTask(ip_task->id);
            break;
        default:
    }

    return TRUE;
}


//-----------------------------------------------------------------------------
//  関数名  :StarTask
//
//  work    :★タスク
//  in      :タスクポインタ　TASK* ip_task
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int StarTask(TASK* ip_task)
{
    SPRITE_DATA SpData;


    switch(ip_task->mode)
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //----MODE NEXT
            ip_task->mode = TASK_MODE_MAIN;

            //----星生成フラグオン
            MGameMgr.Kuma.StarFlag=1;

            //----星変数初期化
            MGameMgr.Star.Status    = STAR_APPEAR;
            MGameMgr.Star.MapNo     = MAZE_MAP_CHAR_STAR;
            MGameMgr.Star.Px        = ip_task->user[0];
            MGameMgr.Star.Py        = ip_task->user[1];
            MGameMgr.Star.Timer     = STAR_EXISTANCE_BASE_TIME + rand()%STAR_EXISTANCE_RANDOM_MAX_TIME; //タイマー

            //----マップへセット
            SetStar(MGameMgr.Star.MapNo,MGameMgr.Star.Px,MGameMgr.Star.Py);

            break;
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:
            if(--MGameMgr.Star.Timer<=0){
                //----タスクモードを変更：終了へ
                ip_task->mode = TASK_MODE_EXIT;
            }
            break;
        //----------------------------------------------------------------タスク終了
        case TASK_MODE_EXIT:
            
            //----星フラグオフ
            MGameMgr.Kuma.StarFlag  = 0;
            
            //----マップ上からクリア
            ClearStar(MGameMgr.Star.Px, MGameMgr.Star.Py);
            
            //----自分を削除
            ExitTask(ip_task->id);
            break;
        default:
    }
    return TRUE;
}


//-----------------------------------------------------------------------------
//  関数名  :BarTask
//
//  work    :柵管理タスク
//  in      :TASK* ip_task  タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int BarTask(TASK* ip_task)
{
    static int BarTable[]=
    {
        MAZE_MAP_CHAR_BAR_00,
        MAZE_MAP_CHAR_BAR_01,
    };

    SPRITE_DATA SpData;


    switch(ip_task->mode)
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //----MODE NEXT
            ip_task->mode = TASK_MODE_MAIN;

            //----柵生成フラグオン
            MGameMgr.Kuma.BarFlag=1;

            //----初期化
            MGameMgr.Bar.Status = BAR_APPEAR;                   //モード
            MGameMgr.Bar.MapNo  = BarTable[rand()%2];           //マップ番号
            MGameMgr.Bar.Px     = ip_task->user[0];             //マップ上の位置Ｘ
            MGameMgr.Bar.Py     = ip_task->user[1];             //マップ上の位置Ｙ
            MGameMgr.Bar.Timer  = BAR_EXISTANCE_BASE_TIME + rand()%BAR_EXISTANCE_RANDOM_MAX_TIME;   //タイマー

            //----マップへセット
            SetBar(MGameMgr.Bar.MapNo, MGameMgr.Bar.Px, MGameMgr.Bar.Py);

            break;
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:
//          FntPrint("BarExistance=[%3d]\n",MGameMgr.Bar.Timer);
//          FntPrint("Bar.Px=[%2d]\n",MGameMgr.Bar.Px);
//          FntPrint("Bar.Py=[%2d]\n",MGameMgr.Bar.Py);

            switch(MGameMgr.Bar.Status)
            {
                //----------------------出現
                case BAR_APPEAR:
                    
                    //----タイマーで消える
                    if(--MGameMgr.Bar.Timer <= 0)
                    {//----削除
                        //----柵モード：消える
                        MGameMgr.Bar.Status = BAR_DISAPPEAR;
                    }
                    
                    break;
                //----------------------消える
                case BAR_DISAPPEAR:
                    //----タスクモードを変更：終了へ
                    ip_task->mode = TASK_MODE_EXIT;
                    
                    break;
                default:
            }

            break;
        //----------------------------------------------------------------タスク終了
        case TASK_MODE_EXIT:
            //----柵フラグオフ
            MGameMgr.Kuma.BarFlag=0;

            //----マップ上からクリア
            ClearBar(MGameMgr.Bar.Px, MGameMgr.Bar.Py);

            //----自分を削除
            ExitTask(ip_task->id);
            break;
        default:
    }
}


//-----------------------------------------------------------------------------
//  関数名  :QuestionTask
//
//  work    :質問タスク
//  in      :TASK* ip_task  タスクポインタ
//  out     :TRUE
//  note    :レベル毎に再起動
//-----------------------------------------------------------------------------
static int QuestionTask(TASK* ip_task)
{
    static int  QIndex;
    static int  QPosIndex;

    MAZE_GAME_QUESTION_NUM_DATA TextNum;
    TASK Task;
    int i,Ans,Type,QAns;


    switch(ip_task->mode)
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //----MODE NEXT
            ip_task->mode = TASK_MODE_MAIN;
            
            //----質問データ初期化
            MGameMgr.Question.Mode          = QUESTION_FLASH;
            MGameMgr.Question.Index         = 0;
            MGameMgr.Question.Timer         = 0;
            MGameMgr.Question.FlashFlag     = 0;
            MGameMgr.Question.AnswerFlag    = 0;
            MGameMgr.Question.FlashCount    = 0;
            MGameMgr.Question.WaitTimer     = QUESTION_START_PLAY_WAIT_TIME;
            
            for(i=0;i<MAX_QUESTION_NUM;i++){
                MGameMgr.Question.Data[i].Flag              = 0;
                MGameMgr.Question.Data[i].QuestionNum.num1  = 0;
                MGameMgr.Question.Data[i].QuestionNum.num2  = 0;
                MGameMgr.Question.Data[i].QuestionNum.num3  = 0;
            }
            
            //----問題生成
            QIndex      = rand() % QUESTION_LEVEL_BASE;     //問題(0～10)
            QPosIndex   = rand() % QUESTION_POS_BASE;       //位置(0～10)
            
            for(i=0;i<MAX_QUESTION_NUM;i++)
            {
                //----答えと問題タイプ設定で問題設定
                Ans     = QuestionDataTable[ QUESTION_LEVEL_BASE * MGameMgr.PlayLevel + QIndex ].Data[i];
                Type    = QuestionTypeTable[MGameMgr.PlayLevel];
                if(Ans==-1){
                    continue;
                }else{
                    //CreateQuestion(Type,Ans,&TextNum);
                    CreateQuestion2(Type,Ans,&TextNum);
                }
                
                //----問題登録
                MGameMgr.Question.Data[i].Flag              = 0;
                MGameMgr.Question.Data[i].QuestionNum.num1  = TextNum.num1;
                MGameMgr.Question.Data[i].QuestionNum.num2  = TextNum.num2;
                MGameMgr.Question.Data[i].QuestionNum.num3  = TextNum.num3;
                
//              //----タイプにより答えが変わる
//              if( QuestionTypeTable[MGameMgr.PlayLevel]==MAZE_GAME_QUESTION_TYPE_ADDITION ){
//                  QAns = TextNum.num3;        //足算の答え
//              }else{
//                  QAns = TextNum.num2;        //引算の答え
//              }


                QAns    = TextNum.num3;
                SetAnswer(  QAns,
                            AnswerPosTable[ AnswerPosIndexTable[QUESTION_LEVEL_BASE+QPosIndex].Data[i] ].Px,
                            AnswerPosTable[ AnswerPosIndexTable[QUESTION_LEVEL_BASE+QPosIndex].Data[i] ].Py);
                
                //----答えを登録
                MGameMgr.Answer[i] = QAns;
            }

            //[♪]ピロピロリーン
            ssPlaySe(MAZU_SE_06);

            break;
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:
            
//          if(JstPad & PADL1){
//              if(++QPosIndex > QUESTION_POS_BASE-1){
//                  QPosIndex=0;
//              }
//          }
            
//          if(JstPad & PADRright){
//              ip_task->mode=TASK_MODE_INIT;
//          }

            switch(MGameMgr.Question.Mode)
            {
                //--------------------------------フラッシュ
                case QUESTION_FLASH:
                    //----１問正解毎にフラッシュ
                    if(++MGameMgr.Question.Timer>QUESTION_FLASH_WAIT_TIME){
                        MGameMgr.Question.Timer     = 0;
                        MGameMgr.Question.FlashFlag ^=1;
                        
                        if(MGameMgr.Question.FlashFlag){
                            if(MGameMgr.Question.FlashCount!=0){
                                //[♪]ピロ
                                ssPlaySe(MAZU_SE_09);
                            }
                            
                            if(++MGameMgr.Question.FlashCount>=4)
                            {//３回音が鳴り終えたら問題フラッシュ終了
                                MGameMgr.Question.Mode          = QUESTION_PLAY_XA;
                                MGameMgr.Question.FlashFlag     = 1;
                                MGameMgr.Question.WaitTimer     = QUESTION_START_PLAY_WAIT_TIME;
                            }
                        }
                    }
                    
                    break;
                //--------------------------------XA再生開始
                case QUESTION_PLAY_XA:
                    if(--MGameMgr.Question.WaitTimer<=0)
                    {//SEがなり終わってから６０イント待ってから問題のXAを再生
                        Task.func           = PlayQuestionTask;
                        Task.priority       = TASK_NO_GAME_PLAY_QUESTION;
                        Task.attribute      = ATTR_USER;
                        Task.status         = TASK_NEW_ENTRY;
                        Task.id             = TASK_NO_GAME_PLAY_QUESTION;
                        Task.wait_time      = 0;
                        Task.buf            = NULL;
                        Task.name           = "PlayQuestionTask";
                        Task.mode           = TASK_MODE_INIT;
                        Task.user[0]        = QuestionTypeTable[MGameMgr.PlayLevel];                            //Type
                        Task.user[1]        = MGameMgr.Question.Data[MGameMgr.Question.Index].QuestionNum.num1; //Num1
                        Task.user[2]        = MGameMgr.Question.Data[MGameMgr.Question.Index].QuestionNum.num2; //Num2
                        CreateTask(&Task);

                        //ステータス変更：XA再生待ち　へ
                        MGameMgr.Question.Mode          = QUESTION_PLAY_XA_WAIT;
                        MGameMgr.Question.WaitTimer     = 10;
                    }
                    break;
                //--------------------------------XA再生待ち
                case QUESTION_PLAY_XA_WAIT:
                    if(--MGameMgr.Question.WaitTimer<=0){
                        if(!MGameMgr.Question.PlayXa.Flag)
                        {//再生終了待ち
                            GameMgr.WaitFlag = OFF;         // iwasawa Correction (2003/4/27)
                            //----ステータス変更：キー待ちへ
                            MGameMgr.GunGun.Character.Status    = GUNGUN_WAIT;
                            //----ステータス変更：待ちへ
                            MGameMgr.Kuma.Character.Status      = KUMA_WAIT;
                            
                            //ステータス変更：選択へ
                            MGameMgr.Question.Mode              = QUESTION_SELECT;
                            
                            //[♪]カーン
                            ssPlaySe(MAZU_SE_08);
                            
                            //[♪]BGM
                            ssPlayBgm(MAZU_BGM_00);
                            
                            //ポーズタスクウェイクアップ
                            WakeupTask(TASK_NO_GAME_PAUSE);
                        }
                    }
                    break;
                //--------------------------------答えを探している間
                case QUESTION_SELECT:
                    break;
                //--------------------------------答え取得
                case QUESTION_OK:
                    break;
                //--------------------------------次の問題へ
                case QUESTION_NEXT_UP:
                    //----次の問題の表示用データをセット
                    if(++MGameMgr.Question.Index>QuestionNumTable[MGameMgr.PlayLevel]-1)
                    {
                        MGameMgr.Question.Index = QuestionNumTable[MGameMgr.PlayLevel]-1;
                    }else{
                        //[♪]ピロピロリーン
                        ssPlaySe(MAZU_SE_06);
                    }
                    
                    //----表示用データ初期化(Indexはそのまま)
                    MGameMgr.Question.Mode          = QUESTION_FLASH;
                    MGameMgr.Question.AnswerFlag    = 0;
                    MGameMgr.Question.Timer         = 0;
                    MGameMgr.Question.FlashFlag     ^= 1;
                    MGameMgr.Question.FlashCount    = 0;
                    
                    //[♪]BGM
                    ssStopBgm(MAZU_BGM_00);
                    
                    //ポーズタスクスリープ
                    SleepTask(TASK_NO_GAME_PAUSE);
                    
                    break;
                //--------------------------------次の問題へ
                case QUESTION_NEXT_NONE:
                    //[♪]ピロピロリーン
                    ssPlaySe(MAZU_SE_06);
                    
                    //----表示用データ初期化(Indexはそのまま)
                    MGameMgr.Question.Mode          = QUESTION_FLASH;
                    MGameMgr.Question.AnswerFlag    = 0;
                    MGameMgr.Question.Timer         = 0;
                    MGameMgr.Question.FlashFlag     ^= 1;
                    MGameMgr.Question.FlashCount    = 0;
                    
                    //[♪]BGM
                    ssStopBgm(MAZU_BGM_00);

                    //ポーズタスクスリープ
                    SleepTask(TASK_NO_GAME_PAUSE);
                default:
            }
            
            //----問題表示
            DrawQuestion(   MGameMgr.Question.Index,
                            QUESTION_BASE_POS_X,
                            QUESTION_BASE_POS_Y,
                            PRIORITY_MAZE_GAME_QUESTION,
                            MGameMgr.Question.FlashFlag,
                            MGameMgr.Question.AnswerFlag);
            
            //----
//          FntPrint("PLAYLEVEL=%2d\n", MGameMgr.PlayLevel);
//          FntPrint("MAX_QNUM_=%2d\n", QuestionNumTable[MGameMgr.PlayLevel]);
//          FntPrint("QIndex___=%2d\n", QIndex);
//          for(i=0;i<MAX_QUESTION_NUM;i++)
//          {
//              FntPrint("[%2d]_%d-%d-%d-%d\n",
//                          i,
//                          MGameMgr.Question.Data[i].Flag,
//                          MGameMgr.Question.Data[i].QuestionNum.num1,
//                          MGameMgr.Question.Data[i].QuestionNum.num2,
//                          MGameMgr.Question.Data[i].QuestionNum.num3);
//          }
            
            break;
        //----------------------------------------------------------------タスク終了
        case TASK_MODE_EXIT:
            
            //----自分を削除
            ExitTask(ip_task->id);
            break;  
    }
    return TRUE;
}





//-----------------------------------------------------------------------------
//  関数名  :PlayQuestionTask
//
//  work    :問題再生
//  in      :TASK* ip_task  タスクポインタ
//  out     :TRUE
//  note    :？と？はいくつ？　ゲームスタート
//          :？は？といくつ？　ゲームスタート
//-----------------------------------------------------------------------------
enum{
    PLAY_STR_TO,
    PLAY_STR_HA,
    PLAY_STR_IKUTSU,
    PLAY_STR_GAME_START,
};

static int PlayQuestionTask(TASK* ip_task)
{

    static XA_DATA NumXaTable[]=
    {
        {   XA_FILE_YOMI01, 0   },  //  ”０”
        {   XA_FILE_YOMI01, 1   },  //  ”１”
        {   XA_FILE_YOMI01, 2   },  //  ”２”
        {   XA_FILE_YOMI01, 3   },  //  ”３”
        {   XA_FILE_YOMI01, 4   },  //  ”４”
        {   XA_FILE_YOMI01, 5   },  //  ”５”
        {   XA_FILE_YOMI01, 6   },  //  ”６”
        {   XA_FILE_YOMI01, 7   },  //  ”７”
        {   XA_FILE_YOMI01, 8   },  //  ”８”
        {   XA_FILE_YOMI01, 9   },  //  ”９”
        {   XA_FILE_YOMI01, 10  },  //  ”１０”
    };

    static XA_DATA StrXaTable[]=
    {
        {   XA_FILE_MAZU01, 0   },  //　”と”
        {   XA_FILE_MAZU01, 5   },  //  ”は”
        {   XA_FILE_MAZU01, 8   },  //  ”いくつ？”
        {   XA_FILE_MAZU01, 7   },  //  ”ゲームスタート”
    };


    TASK* pTask;

    switch( ip_task->mode )
    {
        //---------------------------------------------------------------------
        case TASK_MODE_INIT:
            //next MAIN
            ip_task->mode       = TASK_MODE_MAIN;

            //init
            MGameMgr.Question.PlayXa.Flag       = 1; 
            MGameMgr.Question.PlayXa.Type       = ip_task->user[0];
            MGameMgr.Question.PlayXa.Num1       = ip_task->user[1];
            MGameMgr.Question.PlayXa.Num2       = ip_task->user[2];
            MGameMgr.Question.PlayXa.Mode       = 0;
            MGameMgr.Question.PlayXa.WaitFlag   = 0;
            MGameMgr.Question.PlayXa.WaitTimer  = GET_DA_STATUS_WAIT_TIME*3;

            break;
        //---------------------------------------------------------------------
        case TASK_MODE_MAIN:
            switch(MGameMgr.Question.PlayXa.Mode)
            {
                //----------------１盤面数字
                case 0:
                    
                    if(!MGameMgr.Question.PlayXa.WaitFlag){
                        MGameMgr.Question.PlayXa.WaitFlag=1;
                        //[♪]１番目の数字
                        dsPlayXa(   NumXaTable[MGameMgr.Question.PlayXa.Num1].FileNo,
                                    NumXaTable[MGameMgr.Question.PlayXa.Num1].ChannelNo);
                    }else{
                        if(--MGameMgr.Question.PlayXa.WaitTimer<=0){
                            if(dSoundStatus == DslStatStandby){
                                //再生終了していたら次へ
                                MGameMgr.Question.PlayXa.Mode       = 1;
                                MGameMgr.Question.PlayXa.WaitFlag   = 0;
                                MGameMgr.Question.PlayXa.WaitTimer  = GET_DA_STATUS_WAIT_TIME*3;
                            }
                        }
                    }
                    break;
                //----------------”と”or”は”
                case 1:
                    if(!MGameMgr.Question.PlayXa.WaitFlag){
                        MGameMgr.Question.PlayXa.WaitFlag=1;
                        
                        if(MGameMgr.Question.PlayXa.Type==MAZE_GAME_QUESTION_TYPE_ADDITION){
                            //[♪]”と”
                            dsPlayXa(   StrXaTable[PLAY_STR_TO].FileNo,
                                        StrXaTable[PLAY_STR_TO].ChannelNo);
                        }else{
                            //[♪]”は”
                            dsPlayXa(   StrXaTable[PLAY_STR_HA].FileNo,
                                        StrXaTable[PLAY_STR_HA].ChannelNo);
                        }
                    }else{
                        if(--MGameMgr.Question.PlayXa.WaitTimer<=0){
                            if(dSoundStatus == DslStatStandby){
                                //再生終了していたら次へ
                                MGameMgr.Question.PlayXa.Mode       = 2;
                                MGameMgr.Question.PlayXa.WaitFlag   = 0;
                                MGameMgr.Question.PlayXa.WaitTimer  = GET_DA_STATUS_WAIT_TIME*3;
                            }
                        }
                    }
                    break;
                //----------------２盤面数字
                case 2:
                    if(!MGameMgr.Question.PlayXa.WaitFlag){
                        MGameMgr.Question.PlayXa.WaitFlag=1;
                        //[♪]２番目の数字
                        dsPlayXa(   NumXaTable[MGameMgr.Question.PlayXa.Num2].FileNo,
                                    NumXaTable[MGameMgr.Question.PlayXa.Num2].ChannelNo);
                    }else{
                        if(--MGameMgr.Question.PlayXa.WaitTimer<=0){
                            if(dSoundStatus == DslStatStandby){
                                //再生終了していたら次へ
                                MGameMgr.Question.PlayXa.Mode       = 3;
                                MGameMgr.Question.PlayXa.WaitFlag   = 0;
                                MGameMgr.Question.PlayXa.WaitTimer  = GET_DA_STATUS_WAIT_TIME*3;
                            }
                        }
                    }
                    break;
                //----------------”と”or”は”
                case 3:
                    if(!MGameMgr.Question.PlayXa.WaitFlag){
                        MGameMgr.Question.PlayXa.WaitFlag=1;
                        
                        if(MGameMgr.Question.PlayXa.Type==MAZE_GAME_QUESTION_TYPE_ADDITION){
                            //[♪]”は”
                            dsPlayXa(   StrXaTable[PLAY_STR_HA].FileNo,
                                        StrXaTable[PLAY_STR_HA].ChannelNo);
                        }else{
                            //[♪]”と”
                            dsPlayXa(   StrXaTable[PLAY_STR_TO].FileNo,
                                        StrXaTable[PLAY_STR_TO].ChannelNo);
                        }
                    }else{
                        if(--MGameMgr.Question.PlayXa.WaitTimer<=0){
                            if(dSoundStatus == DslStatStandby){
                                //再生終了していたら次へ
                                MGameMgr.Question.PlayXa.Mode       = 4;
                                MGameMgr.Question.PlayXa.WaitFlag   = 0;
                                MGameMgr.Question.PlayXa.WaitTimer  = GET_DA_STATUS_WAIT_TIME*3;
                            }
                        }
                    }
                    break;
                //----------------”いくつ？”
                case 4:
                    if(!MGameMgr.Question.PlayXa.WaitFlag){
                        MGameMgr.Question.PlayXa.WaitFlag=1;
                        //[♪]”いくつ？”
                        dsPlayXa(   StrXaTable[PLAY_STR_IKUTSU].FileNo,
                                    StrXaTable[PLAY_STR_IKUTSU].ChannelNo);
                    }else{
                        if(--MGameMgr.Question.PlayXa.WaitTimer<=0){
                            if(dSoundStatus == DslStatStandby){
                                //再生終了していたら次へ
                                MGameMgr.Question.PlayXa.Mode       = 5;
                                MGameMgr.Question.PlayXa.WaitFlag   = 0;
                                MGameMgr.Question.PlayXa.WaitTimer  = GET_DA_STATUS_WAIT_TIME*3;
                            }
                        }
                    }
                    break;
                //----------------”ゲームスタート”
                case 5:
                    if(!MGameMgr.Question.PlayXa.WaitFlag){
                        MGameMgr.Question.PlayXa.WaitFlag=1;
                        //[♪]”ゲームスタート”
                        dsPlayXa(   StrXaTable[PLAY_STR_GAME_START].FileNo,
                                    StrXaTable[PLAY_STR_GAME_START].ChannelNo);
                    }else{
                        if(--MGameMgr.Question.PlayXa.WaitTimer<=0){
                            if(dSoundStatus == DslStatStandby){
                                //再生終了していたら次へ
                                MGameMgr.Question.PlayXa.Mode       = 6;
                                MGameMgr.Question.PlayXa.WaitFlag   = 0;
                                MGameMgr.Question.PlayXa.WaitTimer  = GET_DA_STATUS_WAIT_TIME*3;
                            }
                        }
                    }
                    break;
                //----------------終了
                case 6:
                    ip_task->mode = TASK_MODE_EXIT;
                    break;
                default:
            }
            break;
        //---------------------------------------------------------------------
        case TASK_MODE_EXIT:
            //off
            MGameMgr.Question.PlayXa.Flag       = 0; 
            
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
//  work    :ゲーム背景タスク
//  in      :TASK* ip_task  タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int GameBgTask(TASK* ip_task)
{
    SPRITE_DATA SpData;
    int i,j,mno;

    static int BlockSpriteNoTable[]={
        MAZE_CHAR_GAME_IWA_00,
        MAZE_CHAR_GAME_IWA_01,
    };

    static int AnswerNumSpriteTable[]={
        MAZE_CHAR_GAME_ANSWER_NUM_00,
        MAZE_CHAR_GAME_ANSWER_NUM_01,
        MAZE_CHAR_GAME_ANSWER_NUM_02,
        MAZE_CHAR_GAME_ANSWER_NUM_03,
        MAZE_CHAR_GAME_ANSWER_NUM_04,
        MAZE_CHAR_GAME_ANSWER_NUM_05,
        MAZE_CHAR_GAME_ANSWER_NUM_06,
        MAZE_CHAR_GAME_ANSWER_NUM_07,
        MAZE_CHAR_GAME_ANSWER_NUM_08,
        MAZE_CHAR_GAME_ANSWER_NUM_09,
        MAZE_CHAR_GAME_ANSWER_NUM_10,
    };

    static int BarSpriteNoTable[]={
        MAZE_CHAR_GAME_SAKU_00,
        MAZE_CHAR_GAME_SAKU_01,
    };


    switch(ip_task->mode)
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //----MODE NEXT
            ip_task->mode = TASK_MODE_MAIN;

            break;
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:
            mno     = 0;
            for(i=1;i<MAZE_GAME_SQUARE_W_NUM+1;i++)
            {
                for(j=1;j<MAZE_GAME_SQUARE_H_NUM+1;j++)
                {
                    switch(MGameMgr.Map.Data[j][i])
                    {
                        case MAZE_MAP_CHAR_WALL:    //----何もない
                            break;
                        case MAZE_MAP_CHAR_IWA_00:  //----岩
                        case MAZE_MAP_CHAR_IWA_01:  //----岩
                            if(MGameMgr.Map.Data[j][i]==MAZE_MAP_CHAR_IWA_00){
                                mno = 0;
                            }else{
                                mno = 1;
                            }
                            
                            //----岩を描画する
                            SpData.No       = BlockSpriteNoTable[mno];
                            SpData.PosX     = MAZE_GAME_MAP_LEFT_X + (i-1)*MAZE_GAME_SQUARE_W;
                            SpData.PosY     = MAZE_GAME_MAP_LEFT_Y + (j-1)*MAZE_GAME_SQUARE_H;
                            SpData.PosZ     = PRIORITY_MAZE_GAME_IWA;
                            SpData.ScaleX   = SCALE10;
                            SpData.ScaleY   = SCALE10;
                            SpData.Rotate   = ROTATE000;
                            SpData.Reverse  = NOREVERS;
                            DrawSprite( &SpData );
                            
                            break;
                        case MAZE_MAP_CHAR_NUM_00:  //----数字０
                        case MAZE_MAP_CHAR_NUM_01:  //----数字１
                        case MAZE_MAP_CHAR_NUM_02:  //----数字２
                        case MAZE_MAP_CHAR_NUM_03:  //----数字３
                        case MAZE_MAP_CHAR_NUM_04:  //----数字４
                        case MAZE_MAP_CHAR_NUM_05:  //----数字５
                        case MAZE_MAP_CHAR_NUM_06:  //----数字６
                        case MAZE_MAP_CHAR_NUM_07:  //----数字７
                        case MAZE_MAP_CHAR_NUM_08:  //----数字８
                        case MAZE_MAP_CHAR_NUM_09:  //----数字９
                        case MAZE_MAP_CHAR_NUM_10:  //----数字１０
                            //----答えとなる数字を描画
                            SpData.No       = AnswerNumSpriteTable[MGameMgr.Map.Data[j][i]];
                            SpData.PosX     = MAZE_GAME_MAP_LEFT_X + (i-1)*MAZE_GAME_SQUARE_W + 3;
                            SpData.PosY     = MAZE_GAME_MAP_LEFT_Y + (j-1)*MAZE_GAME_SQUARE_H - 1;
                            SpData.PosZ     = PRIORITY_MAZE_GAME_ANSWER_NUM;
                            SpData.ScaleX   = SCALE10;
                            SpData.ScaleY   = SCALE10;
                            SpData.Rotate   = ROTATE000;
                            SpData.Reverse  = NOREVERS;
                            DrawSprite( &SpData );
                            
                            break;
                        case MAZE_MAP_CHAR_STAR:
                            //----星
                            SpData.No       = MAZE_CHAR_GAME_BIG_STAR;
                            SpData.PosX     = MAZE_GAME_MAP_LEFT_X + (i-1)*MAZE_GAME_SQUARE_W+2;
                            SpData.PosY     = MAZE_GAME_MAP_LEFT_Y + (j-1)*MAZE_GAME_SQUARE_H;
                            SpData.PosZ     = PRIORITY_MAZE_GAME_STAR;
                            SpData.ScaleX   = SCALE10;
                            SpData.ScaleY   = SCALE10;
                            SpData.Rotate   = ROTATE000;
                            SpData.Reverse  = NOREVERS;
                            DrawSprite( &SpData );
                            break;
                        case MAZE_MAP_CHAR_BAR_00:
                        case MAZE_MAP_CHAR_BAR_01:
                            if(MGameMgr.Map.Data[j][i]==MAZE_MAP_CHAR_BAR_00){
                                mno = 0;
                            }else{
                                mno = 1;
                            }
                            
                            //----柵
                            SpData.No       = BarSpriteNoTable[mno];
                            SpData.PosX     = MAZE_GAME_MAP_LEFT_X + (i-1)*MAZE_GAME_SQUARE_W + 2;
                            SpData.PosY     = MAZE_GAME_MAP_LEFT_Y + (j-1)*MAZE_GAME_SQUARE_H - 3;
                            SpData.PosZ     = PRIORITY_MAZE_GAME_SAKU;
                            SpData.ScaleX   = SCALE10;
                            SpData.ScaleY   = SCALE10;
                            SpData.Rotate   = ROTATE000;
                            SpData.Reverse  = NOREVERS;
                            DrawSprite( &SpData );
                            
                            break;
                        default:
                    }
                }
            }
            
            
            //背景左
            SpData.No       = MAZE_CHAR_GAME_BG_00;
            SpData.PosX     = 0;
            SpData.PosY     = 0;
            SpData.PosZ     = PRIORITY_MAZE_GAME_BG;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );

            //背景左
            SpData.No       = MAZE_CHAR_GAME_BG_01;
            SpData.PosX     = 256;
            SpData.PosY     = 0;
            SpData.PosZ     = PRIORITY_MAZE_GAME_BG;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );

            break;
        //----------------------------------------------------------------タスク終了
        case TASK_MODE_EXIT:
            
            
            
            
            //----自分を削除
            ExitTask(ip_task->id);
            break;  
        default:
    }

    return TRUE;
}




//-----------------------------------------------------------------------------
//  関数名  :SelectLevelTask
//
//  work    :セレクトレベルタスク
//  in      :TASK* ip_task  タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int SelectLevelTask(TASK* ip_task)
{
    static int LevelNumTable[]={
        MAZE_CHAR_GAME_SELECT_LEVEL_NUM_1,  //19,
        MAZE_CHAR_GAME_SELECT_LEVEL_NUM_2,  //20,
        MAZE_CHAR_GAME_SELECT_LEVEL_NUM_3,  //21,
        MAZE_CHAR_GAME_SELECT_LEVEL_NUM_4,  //22,
        MAZE_CHAR_GAME_SELECT_LEVEL_NUM_5,  //23,
    };

    static MAZE_SPRITE_DATA GakudaninSpriteTable[]=
    {
        {   MAZE_CHAR_GAME_DANTYOU_00,              0,      -6  },  //団長00アニメ
        {   MAZE_CHAR_GAME_DANTYOU_01,              0,      -6  },  //団長01アニメ
        {   MAZE_CHAR_GAME_DANIN_FUUSEN_BLUE_00,    0,      0   },  //楽団員A00アニメ(青風船時)
        {   MAZE_CHAR_GAME_DANIN_FUUSEN_BLUE_01,    0,      0   },  //楽団員A01アニメ(青風船時)
        {   MAZE_CHAR_GAME_DANIN_HATA_02,           0,      0   },  //楽団員C00アニメ
        {   MAZE_CHAR_GAME_DANIN_HATA_03,           0,      0   },  //楽団員C01アニメ
        {   MAZE_CHAR_GAME_DANIN_HATA_00,           0,      0   },  //楽団員B00アニメ
        {   MAZE_CHAR_GAME_DANIN_HATA_01,           0,      0   },  //楽団員B01アニメ
        {   MAZE_CHAR_GAME_DANIN_FUUSEN_ORANGE_00,  0,      0   },  //楽団員A00アニメ(橙風船時)
        {   MAZE_CHAR_GAME_DANIN_FUUSEN_ORANGE_01,  0,      0   },  //楽団員A01アニメ(橙風船時)
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

            //----texture read sram -> vram
            if((file_read(MazeGameTextureFile[0].fn,LoadAddress)) == -1)
            {//read error
                return FALSE;
            }

            //----texture init
            TexInit( MAZE_GAME_TIM_NUM, &MazeGameTextureImage[MAZE_GAME_TIM_POS] );
            TimImgData = MazeGameTextureImage;

            //----ゲーム用スプライト開放
            ReleaseSprite();

            //----ゲーム用スプライト登録
            EntrySprite( MazeGameSpriteData );

            //----プレイレベルクリア
            MGameMgr.PlayLevel  = 0;

            //----継続フラグOFF
            MGameMgr.ContinueFlag   = 0;

            //フェードイン
            GameMgr.FadeFlag    = FadeIn;

            //----レベルセレクトワーク初期化
            MGameMgr.SelectLevel.Mode               = MAZE_GAME_SELECT_LEVEL_MODE_00;
            MGameMgr.SelectLevel.Timer              = 0;
            MGameMgr.SelectLevel.BlockNo            = 0;
            MGameMgr.SelectLevel.BlockWt            = 0;
            MGameMgr.SelectLevel.KeteiWt            = 0;
            MGameMgr.SelectLevel.KeteiFlushIndex    = 0;
            MGameMgr.SelectLevel.KeteiFlushWt       = 0;
            MGameMgr.SelectLevel.AnmIndex           = 0;
            MGameMgr.SelectLevel.AnmNo              = GakudaninSpriteTable[0].No;
            MGameMgr.SelectLevel.AnmWt              = 0;
            MGameMgr.SelectLevel.AnmBase            = 0;
            MGameMgr.SelectLevel.PosX               = MAZE_GAME_SELECT_LEVEL_GAKUDANIN_INIT_X;
            MGameMgr.SelectLevel.PosY               = MAZE_GAME_SELECT_LEVEL_GAKUDANIN_INIT_Y;
            MGameMgr.SelectLevel.WaitFlag           = 0;

            //[♪]パンパカパーん
            dsPlayXa(XA_FILE_ZIRI10,5);

            break;
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:
            //----選択可能レベルをプレートのアニメで表現する
            switch(MGameMgr.SelectLevel.Mode)
            {
                //----------------------------------選択可能なレベルまで明るく(楽団員現る)
                case MAZE_GAME_SELECT_LEVEL_MODE_00:
                    ++MGameMgr.SelectLevel.Timer;
                    if(MGameMgr.SelectLevel.Timer > MAZE_GAME_SELECT_LEVEL_MODE_00_TIME){
                        MGameMgr.SelectLevel.Mode = MAZE_GAME_SELECT_LEVEL_MODE_01;
                        //スクリプト
                        MGameMgr.Script.Flag= 1;
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
                    
                    for(i=0;i<MGameMgr.Level+1;i++){//横
                        for(j=0;j<5;j++){//縦
                            if(j>i) continue;
                            //レベルセレクトプレート
                            SpData.No       = MAZE_CHAR_GAME_SELECT_LEVEL_PLATE_LIGHT;
                            SpData.PosX     = 101 + 25*i - 2;
                            SpData.PosY     = 40 + 95 - 10*j + 3;
                            SpData.PosZ     = PRIORITY_MAZE_EVENT_BG-2;
                            SpData.ScaleX   = SCALE10;
                            SpData.ScaleY   = SCALE10;
                            SpData.Rotate   = ROTATE000;
                            SpData.Reverse  = NOREVERS;
                            DrawSprite( &SpData );
                        }
                    }
                    
                    //----楽団員移動
                    MGameMgr.SelectLevel.PosX -= MAZE_GAME_SELECT_LEVEL_GAKUDANIN_SPEED_X; 
                    if(MGameMgr.SelectLevel.PosX<MAZE_GAME_SELECT_LEVEL_GAKUDANIN_STOP_X)
                    {
                        MGameMgr.SelectLevel.PosX = MAZE_GAME_SELECT_LEVEL_GAKUDANIN_STOP_X;
                    }
                    
                    break;
                //----------------------------------下から上へ明るく
                case MAZE_GAME_SELECT_LEVEL_MODE_01:
                    SsinScriptFlag = MGameMgr.Script.Flag;          // iwasawa Correction (2003/4/27)
                    if(!MGameMgr.Script.Flag){
                        //----操作
                        if(JstPad &  PADLright)
                        {
                            //[♪] レバー音
                            ssPlaySe(BUTONSE_LEVER);
                            if(++MGameMgr.PlayLevel>MGameMgr.Level){
                                MGameMgr.PlayLevel=0;
                            }
                        }else
                        if(JstPad &  PADLleft){
                            //[♪] レバー音
                            ssPlaySe(BUTONSE_LEVER);
                            if(--MGameMgr.PlayLevel<0){
                                MGameMgr.PlayLevel=MGameMgr.Level;
                            }
                        }else{
                            
                        }
                        
                        //----決定
                        if(JstPad &  PADRright)
                        {//next EXIT
                            //[♪]決定
                            ssPlaySe(BUTONSE_MARU);
                            
                            MGameMgr.SelectLevel.Mode = MAZE_GAME_SELECT_LEVEL_MODE_02;
                        }
                    }
                    
                    //----描画
                    if( ++MGameMgr.SelectLevel.BlockWt > MAZE_GAME_SELECT_LEVEL_FLUSH_ANM_TIME)
                    {//
                        MGameMgr.SelectLevel.BlockWt=0;
                    //  if(++MGameMgr.SelectLevel.BlockNo > MAZE_GAME_MAX_LEVEL_NUM-1)
                        if(++MGameMgr.SelectLevel.BlockNo > MAZE_GAME_MAX_LEVEL_NUM)
                        {
                            MGameMgr.SelectLevel.BlockNo=0;
                        }
                    }
                    
                    for(i=0;i<MGameMgr.Level+1;i++){//横
                        for(j=0;j<5;j++){//縦
                            if(j>i) continue;
                            if(MGameMgr.SelectLevel.BlockNo <= j) continue;
                            
                            //レベルセレクトプレート
                            SpData.No       = MAZE_CHAR_GAME_SELECT_LEVEL_PLATE_LIGHT;
                            SpData.PosX     = 101 + 25*i - 2;
                            SpData.PosY     = 40 + 95 - 10*j + 3;
                            SpData.PosZ     = PRIORITY_MAZE_EVENT_BG-3;
                            SpData.ScaleX   = SCALE10;
                            SpData.ScaleY   = SCALE10;
                            SpData.Rotate   = ROTATE000;
                            SpData.Reverse  = NOREVERS;
                            DrawSprite( &SpData );
                        }
                    }
                    break;
                //----------------------------------選んだレベルのみフラッシュ
                case MAZE_GAME_SELECT_LEVEL_MODE_02:
                    
                    if(!MGameMgr.SelectLevel.WaitFlag){
                        if(++MGameMgr.SelectLevel.KeteiWt > MAZE_GAME_SELECT_LEVEL_KETEI_WAIT_TIME){
                            //フラッシュ後抜ける
                            MGameMgr.SelectLevel.WaitFlag=1;
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
                    
                    if( ++MGameMgr.SelectLevel.KeteiFlushWt > MAZE_GAME_SELECT_LEVEL_KETEI_FLUSH_TIME ){
                        MGameMgr.SelectLevel.KeteiFlushWt = 0;
                        MGameMgr.SelectLevel.KeteiFlushIndex^=1;
                    }
                    
                    if(MGameMgr.SelectLevel.KeteiFlushIndex){
                        for(i=0;i<5;i++){//縦
                            if(MGameMgr.PlayLevel>=i){
                                //レベルセレクトプレート
                                SpData.No       = MAZE_CHAR_GAME_SELECT_LEVEL_PLATE_LIGHT;
                                SpData.PosX     = 101 + 25*MGameMgr.PlayLevel - 2;
                                SpData.PosY     = 40 + 95 - 10*i + 3;
                                SpData.PosZ     = PRIORITY_MAZE_EVENT_BG-2;
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
            if(++MGameMgr.SelectLevel.AnmWt > MAZE_GAME_SELECT_LEVEL_GAKUDANIN_ANM_WAIT_TIME){
                MGameMgr.SelectLevel.AnmWt      = 0;
                MGameMgr.SelectLevel.AnmIndex   ^=1;
            }
            
            for(i=0;i<5;i++)
            {
                MGameMgr.SelectLevel.AnmBase    = i*2;
                MGameMgr.SelectLevel.AnmNo      = GakudaninSpriteTable[MGameMgr.SelectLevel.AnmBase + MGameMgr.SelectLevel.AnmIndex].No;
                
                SpData.No                       = MGameMgr.SelectLevel.AnmNo;
                SpData.PosX                     = MGameMgr.SelectLevel.PosX + i*40 + GakudaninSpriteTable[MGameMgr.SelectLevel.AnmBase + MGameMgr.SelectLevel.AnmIndex].Ofx;
                SpData.PosY                     = MGameMgr.SelectLevel.PosY + GakudaninSpriteTable[MGameMgr.SelectLevel.AnmBase + MGameMgr.SelectLevel.AnmIndex].Ofy;
                SpData.PosZ                     = PRIORITY_MAZE_EVENT_BG - 4;
                SpData.ScaleX                   = SCALE10;
                SpData.ScaleY                   = SCALE10;
                SpData.Rotate                   = ROTATE000;
                SpData.Reverse                  = NOREVERS;
                DrawSprite( &SpData );
            }

            //----レベルセレクトプレートワク
            SpData.No       = 16;
            SpData.PosX     = 100 + 25 * MGameMgr.PlayLevel - 2;
            SpData.PosY     = 40 + 80 - 10 * MGameMgr.PlayLevel + 3;
            SpData.PosZ     = PRIORITY_MAZE_EVENT_BG - 3;
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
                SpData.PosZ     = PRIORITY_MAZE_EVENT_BG-4;
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
                    SpData.No       = MAZE_CHAR_GAME_SELECT_LEVEL_PLATE_DARK;
                    SpData.PosX     = 101 + 25*i - 2;
                    SpData.PosY     = 40 + 95 - 10*j + 3;
                    SpData.PosZ     = PRIORITY_MAZE_EVENT_BG-1;
                    SpData.ScaleX   = SCALE10;
                    SpData.ScaleY   = SCALE10;
                    SpData.Rotate   = ROTATE000;
                    SpData.Reverse  = NOREVERS;
                    DrawSprite( &SpData );
                }
            }

            //----レベルセレクト背景左
            SpData.No       = MAZE_CHAR_GAME_SELECT_LEVEL_BG_00;
            SpData.PosX     = 0;
            SpData.PosY     = 0;
            SpData.PosZ     = PRIORITY_MAZE_EVENT_BG;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );
            
            //----レベルセレクト背景右
            SpData.No       = MAZE_CHAR_GAME_SELECT_LEVEL_BG_01;
            SpData.PosX     = 256;
            SpData.PosY     = 0;
            SpData.PosZ     = PRIORITY_MAZE_EVENT_BG;
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

            MGameMgr.Script.Flag    = 1;
            MGameMgr.Script.Index   = 0;
            MGameMgr.Script.Line    = ip_task->user[0];
            MGameMgr.Script.Base    = ip_task->user[1];
            MGameMgr.Script.Num     = ip_task->user[2];
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
                        switch(MGameMgr.Script.Line)
                        {
                            case SCRIPT_LINE_1:
                                MenuMessageSet10(&MazeScript[MGameMgr.Script.Base + MGameMgr.Script.Index]);
                                break;
                            case SCRIPT_LINE_2:
                                MenuMessageSet20(&MazeScript[MGameMgr.Script.Base + MGameMgr.Script.Index]);
                                break;
                            case SCRIPT_LINE_3:
                                MenuMessageSet30(&MazeScript[MGameMgr.Script.Base + MGameMgr.Script.Index]);
                                break;
                            default:
                        }
                        
                        if(++MGameMgr.Script.Index >= MGameMgr.Script.Num){
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
            
            MGameMgr.Script.Flag    = 0;
            
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
            MGameMgr.ExitFlag   = 1;
            
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
//  work    :ポーズ監視タスク
//  in      :TASK* ip_task  タスクポインタ
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
                    SleepTask(TASK_NO_GAME_GUNGUN);
                    SleepTask(TASK_NO_GAME_KUMA);
                    SleepTask(TASK_NO_GAME_QUESTION);
                    SleepTask(TASK_NO_GAME_GUNGUN_ZANKI);
                    SleepTask(TASK_NO_GAME_BAR);
                    SleepTask(TASK_NO_GAME_STAR);
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
                    WakeupTask(TASK_NO_GAME_GUNGUN);
                    WakeupTask(TASK_NO_GAME_KUMA);
                    WakeupTask(TASK_NO_GAME_QUESTION);
                    WakeupTask(TASK_NO_GAME_GUNGUN_ZANKI);
                    WakeupTask(TASK_NO_GAME_BAR);
                    WakeupTask(TASK_NO_GAME_STAR);
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
//  関数名  :FalseEventBakuTask
//
//  work    :失敗イベントタスク-1
//  in      :TASK *ip_task  タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int FalseEventBakuTask(TASK *ip_task)
{
    TASK Task;

    switch(ip_task->mode)
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //next main
            ip_task->mode = TASK_MODE_MAIN;
            
            //----texture read sram -> vram
            if((file_read(MazeEventTextureFile[0].fn,LoadAddress)) == -1)
            {//read error
                return FALSE;
            }
            
            //----texture init
            TexInit( MAZE_EVENT_TIM_NUM, &MazeEventTextureImage[MAZE_EVENT_TIM_POS] );
            TimImgData = MazeEventTextureImage;
            
            //----開放
            ReleaseSprite();
            
            //----ゲーム用スプライト登録
            EntrySprite( MazeEventSpriteData );
            
            //----イベントデータ初期化
            MGameMgr.Event.EndFlag              = 0;        //終了フラグ
            MGameMgr.Event.Timer                = 0;        //タイマー
            MGameMgr.Event.GunGunTimer          = 0;        //グングンタイマー
            MGameMgr.Event.GunGunAnmNo          = 0;        //グングンアニメ番号
            MGameMgr.Event.GunGunAnmIndex       = 0;        //グングンアニメインデックス
            MGameMgr.Event.GunGunAnmWaitTime    = 0;        //グングンアニメウェイトタイム
            MGameMgr.Event.GunGunPosX           = 90;       //グングン位置Ｘ
            MGameMgr.Event.GunGunPosY           = 60;       //グングン位置Ｙ
            MGameMgr.Event.GunGunStopFlag       = 0;        //停止フラグ 
            MGameMgr.Event.GunGunAngle          = 0;        //角度
            MGameMgr.Event.GunGunWorkX          = 0;        //ワーク
            MGameMgr.Event.KumaTimer            = 0;        //クマタイマー
            MGameMgr.Event.KumaAnmNo            = 0;        //クマアニメ番号
            MGameMgr.Event.KumaAnmIndex         = 0;        //クマアニメインデックス
            MGameMgr.Event.KumaAnmWaitTime      = 0;        //クマアニメウェイトタイム
            MGameMgr.Event.KumaPosX             = 184;      //クマ位置Ｘ
            MGameMgr.Event.KumaPosY             = 40;       //クマ位置Ｙ
            MGameMgr.Event.KumaMoveDirX         = 0;        //クマ移動方向Ｘ
            MGameMgr.Event.KumaStopFlag         = 0;        //停止フラグ 
            MGameMgr.Event.BakuhatsuTimer       = 0;        //爆発タイマー
            MGameMgr.Event.BakuhatsuAnmIndex    = 0;        //爆発アニメインデックス
            MGameMgr.Event.BakuhatsuAnmWaitTime = 0;        //爆発アニメウェイトタイム
            MGameMgr.Event.BakuhatsuDrawFlag    = 1;        //爆発アニメ表示フラグ
            
            //----終了処理メニュー
            MGameMgr.SelectContinue.Val         = 0;
            MGameMgr.SelectContinue.Type        = SELECT_RETRY_H;
            MGameMgr.SelectContinue.No          = 0;
            MGameMgr.SelectContinue.Wt          = 0;
            MGameMgr.SelectContinue.FadeFlag    = 0;

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
            Task.user[1]        = FALSE_DEMO_1_SCRIPT_BASE;
            Task.user[2]        = FALSE_DEMO_1_SCRIPT_NUM;
            CreateTask(&Task);

            //[♪]ボン
            ssPlaySe(MAZU_SE_03);


#ifdef __DEBUG_MAZE__
            //フェードイン
            GameMgr.FadeFlag    = FadeIn;
#endif

            break;
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:
            
            //----クリアイベント終了チェック遺
            if(!MGameMgr.Script.Flag){//----クリアイベント終了チェック
                if(++MGameMgr.Event.Timer > MAZE_GAME_FALSE_EVENT_BAKU_END_TIME){
                    MGameMgr.Event.EndFlag=1;
                }
            }

            //----グングンとクマと背景の処理
            EventBakuhatsu();
            EventGunGun(MAZE_EVENT_FALSE_BAKU);
            EventKuma(MAZE_EVENT_FALSE_BAKU);
            MazeEventBg();

            if(MGameMgr.Event.EndFlag)
            {
                if(SelectContinue(!MGameMgr.SelectContinue.FadeFlag))
                {//●ボタンが押された
                    if(!MGameMgr.SelectContinue.FadeFlag)
                    {//フェード中
                        if((MGameMgr.SelectContinue.Val==0) && (MGameMgr.SelectContinue.Type==SELECT_RETRY_H))
                        {//もう一度プレイしますか？　はい
                            MGameMgr.SelectContinue.FadeFlag    = 1;
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
                        if( (MGameMgr.SelectContinue.Val==1) && (MGameMgr.SelectContinue.Type==SELECT_RETRY_H))
                        {//もう一度プレイしますか？　いいえ
                            MGameMgr.SelectContinue.Type    =SELECT_END_H;
                            MGameMgr.SelectContinue.Val     = 0;
                        }else
                        if((MGameMgr.SelectContinue.Type==SELECT_END_H) && (MGameMgr.SelectContinue.Val==0))
                        {//やめますか？　はい
                            MGameMgr.SelectContinue.FadeFlag    = 1;
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
                        if((MGameMgr.SelectContinue.Type==SELECT_END_H) && (MGameMgr.SelectContinue.Val==1))
                        {//やめますか？　いいえ
                            MGameMgr.SelectContinue.Type    = SELECT_RETRY_H;
                            MGameMgr.SelectContinue.Val     = 0;
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
            //----登録スプライト開放
            ReleaseSprite();

            //--------------------ここは２択
            //  (1)セレクトレベルへ
            //  (2)メインメニュー
            if((MGameMgr.SelectContinue.Val==0) && (MGameMgr.SelectContinue.Type==SELECT_RETRY_H))
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
                MGameMgr.ExitFlag=1;
            }
            
            //自分を削除
            ExitTask(ip_task->id);
            break;
        default:
    }

    return TRUE;
}


//-----------------------------------------------------------------------------
//  関数名  :FalseEventGutsTask
//
//  work    :失敗イベントタスク-2
//  in      :TASK *ip_task  タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int FalseEventGutsTask(TASK *ip_task)
{
    TASK Task;

    switch(ip_task->mode)
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //next main
            ip_task->mode = TASK_MODE_MAIN;
            
            //----texture read sram -> vram
            if((file_read(MazeEventTextureFile[0].fn,LoadAddress)) == -1)
            {//read error
                return FALSE;
            }
            
            //----texture init
            TexInit( MAZE_EVENT_TIM_NUM, &MazeEventTextureImage[MAZE_EVENT_TIM_POS] );
            TimImgData = MazeEventTextureImage;
            
            //----開放
            ReleaseSprite();
            
            //----ゲーム用スプライト登録
            EntrySprite( MazeEventSpriteData );
            
            //----イベントデータ初期化
            MGameMgr.Event.EndFlag              = 0;        //終了フラグ
            MGameMgr.Event.Timer                = 0;        //タイマー
            MGameMgr.Event.GunGunTimer          = 0;        //グングンタイマー
            MGameMgr.Event.GunGunAnmNo          = 0;        //グングンアニメ番号
            MGameMgr.Event.GunGunAnmIndex       = 0;        //グングンアニメインデックス
            MGameMgr.Event.GunGunAnmWaitTime    = 0;        //グングンアニメウェイトタイム
            MGameMgr.Event.GunGunPosX           = 186;      //グングン位置Ｘ
            MGameMgr.Event.GunGunPosY           = 40;       //グングン位置Ｙ
            MGameMgr.Event.GunGunStopFlag       = 0;        //停止フラグ 
            MGameMgr.Event.KumaTimer            = 0;        //クマタイマー
            MGameMgr.Event.KumaAnmNo            = 0;        //クマアニメ番号
            MGameMgr.Event.KumaAnmIndex         = 0;        //クマアニメインデックス
            MGameMgr.Event.KumaAnmWaitTime      = 0;        //クマアニメウェイトタイム
            MGameMgr.Event.KumaPosX             = 0;        //クマ位置Ｘ
            MGameMgr.Event.KumaPosY             = 0;        //クマ位置Ｙ
            MGameMgr.Event.KumaMoveDirX         = 0;        //クマ移動方向Ｘ
            MGameMgr.Event.KumaStopFlag         = 0;        //停止フラグ 
            MGameMgr.Event.BakuhatsuTimer       = 0;        //爆発タイマー
            MGameMgr.Event.BakuhatsuAnmIndex    = 0;        //爆発アニメインデックス
            MGameMgr.Event.BakuhatsuAnmWaitTime = 0;        //爆発アニメウェイトタイム
            MGameMgr.Event.BakuhatsuDrawFlag    = 0;        //爆発アニメ表示フラグ
            
            //----終了処理メニュー
            MGameMgr.SelectContinue.Val         = 0;
            MGameMgr.SelectContinue.Type        = SELECT_RETRY_H;
            MGameMgr.SelectContinue.No          = 0;
            MGameMgr.SelectContinue.Wt          = 0;
            MGameMgr.SelectContinue.FadeFlag    = 0;

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
            Task.user[1]        = FALSE_DEMO_2_SCRIPT_BASE;
            Task.user[2]        = FALSE_DEMO_2_SCRIPT_NUM;
            CreateTask(&Task);

#ifdef __DEBUG_MAZE__
            //フェードイン
            GameMgr.FadeFlag    = FadeIn;
#endif

            break;
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:
            //----クリアイベント終了チェック遺
            if(!MGameMgr.Script.Flag){//----クリアイベント終了チェック
                if(++MGameMgr.Event.Timer > MAZE_GAME_FALSE_EVENT_GUTS_END_TIME){
                    MGameMgr.Event.EndFlag=1;
                }
            }
            
            //----グングンとクマと背景の処理
            EventGunGun(MAZE_EVENT_FALSE_GUTS);
            EventKuma(MAZE_EVENT_FALSE_GUTS);
            MazeEventBg();
            
            if(MGameMgr.Event.EndFlag)
            {
                if(SelectContinue(!MGameMgr.SelectContinue.FadeFlag))
                {//●ボタンが押された
                    if(!MGameMgr.SelectContinue.FadeFlag)
                    {//フェード中
                        if((MGameMgr.SelectContinue.Val==0) && (MGameMgr.SelectContinue.Type==SELECT_RETRY_H))
                        {//もう一度プレイしますか？　はい
                            MGameMgr.SelectContinue.FadeFlag    = 1;
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
                        if( (MGameMgr.SelectContinue.Val==1) && (MGameMgr.SelectContinue.Type==SELECT_RETRY_H))
                        {//もう一度プレイしますか？　いいえ
                            MGameMgr.SelectContinue.Type    =SELECT_END_H;
                            MGameMgr.SelectContinue.Val     = 0;
                        }else
                        if((MGameMgr.SelectContinue.Type==SELECT_END_H) && (MGameMgr.SelectContinue.Val==0))
                        {//やめますか？　はい
                            MGameMgr.SelectContinue.FadeFlag    = 1;
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
                        if((MGameMgr.SelectContinue.Type==SELECT_END_H) && (MGameMgr.SelectContinue.Val==1))
                        {//やめますか？　いいえ
                            MGameMgr.SelectContinue.Type    = SELECT_RETRY_H;
                            MGameMgr.SelectContinue.Val     = 0;
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
            //----登録スプライト開放
            ReleaseSprite();

            //--------------------ここは２択
            //  (1)セレクトレベルへ
            //  (2)メインメニュー
            if((MGameMgr.SelectContinue.Val==0) && (MGameMgr.SelectContinue.Type==SELECT_RETRY_H))
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
                MGameMgr.ExitFlag=1;
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
//  in      :TASK *ip_task  タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int ClearEventTask(TASK *ip_task)
{
    TASK Task;
    SPRITE_DATA SpData;


    switch(ip_task->mode)
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //next main
            ip_task->mode = TASK_MODE_MAIN;

            //----texture read sram -> vram
            if((file_read(MazeEventTextureFile[0].fn,LoadAddress)) == -1)
            {//read error
                return FALSE;
            }

            //----texture init
            TexInit( MAZE_EVENT_TIM_NUM, &MazeEventTextureImage[MAZE_EVENT_TIM_POS] );
            TimImgData = MazeEventTextureImage;

            //----開放
            ReleaseSprite();

            //----ゲーム用スプライト登録
            EntrySprite( MazeEventSpriteData );

            //----イベントデータ初期化
            MGameMgr.Event.EndFlag              = 0;        //終了フラグ
            MGameMgr.Event.Timer                = 0;        //タイマー
            MGameMgr.Event.GunGunTimer          = 0;        //グングンタイマー
            MGameMgr.Event.GunGunAnmNo          = 0;        //グングンアニメ番号
            MGameMgr.Event.GunGunAnmIndex       = 0;        //グングンアニメインデックス
            MGameMgr.Event.GunGunAnmWaitTime    = 0;        //グングンアニメウェイトタイム
            MGameMgr.Event.GunGunPosX           = 114;      //グングン位置Ｘ
            MGameMgr.Event.GunGunPosY           = 87;       //グングン位置Ｙ
            MGameMgr.Event.GunGunStopFlag       = 0;        //停止フラグ 
            MGameMgr.Event.KumaTimer            = 0;        //クマタイマー
            MGameMgr.Event.KumaAnmNo            = 0;        //クマアニメ番号
            MGameMgr.Event.KumaAnmIndex         = 0;        //クマアニメインデックス
            MGameMgr.Event.KumaAnmWaitTime      = 0;        //クマアニメウェイトタイム
            MGameMgr.Event.KumaPosX             = 360;      //クマ位置Ｘ
            MGameMgr.Event.KumaPosY             = 34;       //クマ位置Ｙ
            MGameMgr.Event.KumaMoveDirX         = -1;       //クマ移動方向Ｘ
            MGameMgr.Event.KumaStopFlag         = 0;        //停止フラグ 

            //----終了処理メニュー
            MGameMgr.SelectContinue.Val         = 0;
            MGameMgr.SelectContinue.Type        = SELECT_RETRY_H;
            MGameMgr.SelectContinue.No          = 0;
            MGameMgr.SelectContinue.Wt          = 0;
            MGameMgr.SelectContinue.FadeFlag    = 0;

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

#ifdef __DEBUG_MAZE__
            //フェードイン
            GameMgr.FadeFlag    = FadeIn;
#endif

            break;
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:

            if(!MGameMgr.Script.Flag){//----クリアイベント終了チェック
                if(++MGameMgr.Event.Timer > MAZE_GAME_CLEAR_EVENT_END_TIME){
                    MGameMgr.Event.EndFlag=1;
                }
            }

            //----グングンとクマと背景の処理
            EventGunGun(MAZE_EVENT_CLEAR);
            EventKuma(MAZE_EVENT_CLEAR);
            MazeEventBg();
            
            //----もう一度プレイしますか？
            if(MGameMgr.Event.EndFlag)
            {
                if(SelectContinue(!MGameMgr.SelectContinue.FadeFlag))
                {//●ボタンが押された
                    if(!MGameMgr.SelectContinue.FadeFlag)
                    {//フェード中
                        if((MGameMgr.SelectContinue.Val==0) && (MGameMgr.SelectContinue.Type==SELECT_RETRY_H))
                        {//もう一度プレイしますか？　はい
                            MGameMgr.SelectContinue.FadeFlag    = 1;
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
                        if( (MGameMgr.SelectContinue.Val==1) && (MGameMgr.SelectContinue.Type==SELECT_RETRY_H))
                        {//もう一度プレイしますか？　いいえ
                            MGameMgr.SelectContinue.Type    =SELECT_END_H;
                            MGameMgr.SelectContinue.Val     = 0;
                        }else
                        if((MGameMgr.SelectContinue.Type==SELECT_END_H) && (MGameMgr.SelectContinue.Val==0))
                        {//やめますか？　はい
                            MGameMgr.SelectContinue.FadeFlag    = 1;
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
                        if((MGameMgr.SelectContinue.Type==SELECT_END_H) && (MGameMgr.SelectContinue.Val==1))
                        {//やめますか？　いいえ
                            MGameMgr.SelectContinue.Type    = SELECT_RETRY_H;
                            MGameMgr.SelectContinue.Val     = 0;
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
            //----登録スプライト開放
            ReleaseSprite();
            
            //--------------------ここは２択
            //  (1)セレクトレベルへ
            //  (2)メインメニュー
            if((MGameMgr.SelectContinue.Val==0) && (MGameMgr.SelectContinue.Type==SELECT_RETRY_H))
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
                MGameMgr.ExitFlag=1;
            }
            
            //----自分を削除
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
//  in      :TASK *ip_task  タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int AllClearEventTask(TASK *ip_task)
{
    TASK Task;
    SPRITE_DATA SpData;


    switch(ip_task->mode)
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //next main
            ip_task->mode = TASK_MODE_MAIN;

            //----texture read sram -> vram
            if((file_read(MazeEventTextureFile[0].fn,LoadAddress)) == -1)
            {//read error
                return FALSE;
            }

            //----texture init
            TexInit( MAZE_EVENT_TIM_NUM, &MazeEventTextureImage[MAZE_EVENT_TIM_POS] );
            TimImgData = MazeEventTextureImage;

            //----開放
            ReleaseSprite();

            //----ゲーム用スプライト登録
            EntrySprite( MazeEventSpriteData );

            //----イベントデータ初期化
            MGameMgr.Event.EndFlag              = 0;        //終了フラグ
            MGameMgr.Event.Timer                = 0;        //タイマー
            MGameMgr.Event.GunGunTimer          = 0;        //グングンタイマー
            MGameMgr.Event.GunGunAnmNo          = 0;        //グングンアニメ番号
            MGameMgr.Event.GunGunAnmIndex       = 0;        //グングンアニメインデックス
            MGameMgr.Event.GunGunAnmWaitTime    = 0;        //グングンアニメウェイトタイム
            MGameMgr.Event.GunGunPosX           = 114;      //グングン位置Ｘ
            MGameMgr.Event.GunGunPosY           = 87;       //グングン位置Ｙ
            MGameMgr.Event.GunGunStopFlag       = 0;        //停止フラグ 
            MGameMgr.Event.KumaTimer            = 0;        //クマタイマー
            MGameMgr.Event.KumaAnmNo            = 0;        //クマアニメ番号
            MGameMgr.Event.KumaAnmIndex         = 0;        //クマアニメインデックス
            MGameMgr.Event.KumaAnmWaitTime      = 0;        //クマアニメウェイトタイム
            MGameMgr.Event.KumaPosX             = 360;      //クマ位置Ｘ
            MGameMgr.Event.KumaPosY             = 34;       //クマ位置Ｙ
            MGameMgr.Event.KumaMoveDirX         = -1;       //クマ移動方向Ｘ
            MGameMgr.Event.KumaStopFlag         = 0;        //停止フラグ 

            //----終了処理メニュー
            MGameMgr.SelectContinue.Val         = 0;
            MGameMgr.SelectContinue.Type        = SELECT_RETRY_H;
            MGameMgr.SelectContinue.No          = 0;
            MGameMgr.SelectContinue.Wt          = 0;
            MGameMgr.SelectContinue.FadeFlag    = 0;

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

#ifdef __DEBUG_MAZE__
            //フェードイン
            GameMgr.FadeFlag    = FadeIn;
#endif

            break;
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:
            
            //----クリアイベント終了チェック遺
            if(!MGameMgr.Script.Flag){//----クリアイベント終了チェック
                if(++MGameMgr.Event.Timer > MAZE_GAME_ALL_CLEAR_EVENT_END_TIME){
                    MGameMgr.Event.EndFlag=1;
                }
            }
            
            if(MGameMgr.Event.Timer == 10)
            {//
                dsPlayXa(XA_FILE_MAZU03,8);
            }
            
            //----グングンとクマと背景の処理
            EventGunGun(MAZE_EVENT_CLEAR);
            EventKuma(MAZE_EVENT_CLEAR);
            MazeEventBg();
            
            //----もう一度プレイしますか？
            if(MGameMgr.Event.EndFlag)
            {
                if(SelectContinue(!MGameMgr.SelectContinue.FadeFlag))
                {//●ボタンが押された
                    if(!MGameMgr.SelectContinue.FadeFlag)
                    {//フェード中
                        if((MGameMgr.SelectContinue.Val==0) && (MGameMgr.SelectContinue.Type==SELECT_RETRY_H))
                        {//もう一度プレイしますか？　はい
                            MGameMgr.SelectContinue.FadeFlag    = 1;
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
                        if( (MGameMgr.SelectContinue.Val==1) && (MGameMgr.SelectContinue.Type==SELECT_RETRY_H))
                        {//もう一度プレイしますか？　いいえ
                            MGameMgr.SelectContinue.Type    =SELECT_END_H;
                            MGameMgr.SelectContinue.Val     = 0;
                        }else
                        if((MGameMgr.SelectContinue.Type==SELECT_END_H) && (MGameMgr.SelectContinue.Val==0))
                        {//やめますか？　はい
                            MGameMgr.SelectContinue.FadeFlag    = 1;
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
                        if((MGameMgr.SelectContinue.Type==SELECT_END_H) && (MGameMgr.SelectContinue.Val==1))
                        {//やめますか？　いいえ
                            MGameMgr.SelectContinue.Type    = SELECT_RETRY_H;
                            MGameMgr.SelectContinue.Val     = 0;
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
            //----登録スプライト開放
            ReleaseSprite();
            
            //--------------------ここは２択
            //  (1)セレクトレベルへ
            //  (2)メインメニュー
            if((MGameMgr.SelectContinue.Val==0) && (MGameMgr.SelectContinue.Type==SELECT_RETRY_H))
            {
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
                MGameMgr.ExitFlag=1;
            }

            //----自分を削除
            ExitTask(ip_task->id);
            break;
        default:
    }

    return TRUE;
}


//-----------------------------------------------------------------------------
//  関数名  :InitGameMap
//
//  work    :ゲームマップ初期化
//  in      :なし
//  out     :なし
//  note    :なし
//-----------------------------------------------------------------------------
static void InitGameMap(void)
{
    memcpy( MGameMgr.Map.Data,
            InitMapData,
            (MAZE_GAME_SQUARE_W_NUM+2)*(MAZE_GAME_SQUARE_H_NUM+2) );
}


//-----------------------------------------------------------------------------
//  関数名  :CopyGameMapToWorkMap
//
//  work    :ワーク用のマップをコピー
//  in      :なし
//  out     :なし
//  note    :なし
//-----------------------------------------------------------------------------
static void CopyGameMapToWorkMap(void)
{
    memcpy( MGameMgr.WorkMap.Data,
            MGameMgr.Map.Data,
            (MAZE_GAME_SQUARE_W_NUM+2)*(MAZE_GAME_SQUARE_H_NUM+2) );
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
    if(NewPad & PADLup){
        *ip_dir=DIR_UP;
        return TRUE;
    }else
    if(NewPad & PADLdown){
        *ip_dir=DIR_DOWN;
        return TRUE;
    }
    else
    if(NewPad & PADLleft){
        *ip_dir=DIR_LEFT;
        return TRUE;
    }
    else
    if(NewPad & PADLright){
        *ip_dir=DIR_RIGHT;
        return TRUE;
    }else{
        *ip_dir=DIR_NOTHING;
        return FALSE;
    }
}


//-----------------------------------------------------------------------------
//  関数名  :CheckCharacterMaze
//
//  work    :キャラクターチェック
//  in      :int    i_x     マップ上の位置X
//  in      :int    i_y     マップ上の位置Y
//          :int    i_dir   方向データ
//  out     :引数方向のキャラクター情報
//  note    :なし
//-----------------------------------------------------------------------------
static int CheckCharacterMaze(int i_x,int i_y,int i_dir)
{
    int ofx,ofy;

    //検索方向よりオフセット選択
    switch(i_dir)
    {
        case DIR_UP:
            ofx=0;
            ofy=-1;
            break;
        case DIR_DOWN:
            ofx=0;
            ofy=1;
            break;
        case DIR_LEFT:
            ofx=-1;
            ofy=0;
            break;
        case DIR_RIGHT:
            ofx=1;
            ofy=0;
            break;
        default:
            ofx=0;
            ofy=0;
            break;
    }

    //----クマの配置を別処理でチェック
    if( CheckKumaPos(i_x + ofx ,i_y + ofy) )
    {
        return MAZE_MAP_CHAR_ENEMY;
    }

    //----調べる
    switch( MGameMgr.Map.Data[i_y + ofy][i_x + ofx] )
    {
        case MAZE_MAP_CHAR_WALL:
            return MAZE_MAP_CHAR_WALL;
            break;
        case MAZE_MAP_CHAR_IWA_00:
            return MAZE_MAP_CHAR_IWA_00;
            break;
        case MAZE_MAP_CHAR_IWA_01:
            return MAZE_MAP_CHAR_IWA_01;
            break;
        case MAZE_MAP_CHAR_NONE:
            return MAZE_MAP_CHAR_NONE;
            break;
        case MAZE_MAP_CHAR_NUM_00:
            return MAZE_MAP_CHAR_NUM_00;
        case MAZE_MAP_CHAR_NUM_01:
            return MAZE_MAP_CHAR_NUM_01;
            break;
        case MAZE_MAP_CHAR_NUM_02:
            return MAZE_MAP_CHAR_NUM_02;
            break;
        case MAZE_MAP_CHAR_NUM_03:
            return MAZE_MAP_CHAR_NUM_03;
            break;
        case MAZE_MAP_CHAR_NUM_04:
            return MAZE_MAP_CHAR_NUM_04;
            break;
        case MAZE_MAP_CHAR_NUM_05:
            return MAZE_MAP_CHAR_NUM_05;
            break;
        case MAZE_MAP_CHAR_NUM_06:
            return MAZE_MAP_CHAR_NUM_06;
            break;
        case MAZE_MAP_CHAR_NUM_07:
            return MAZE_MAP_CHAR_NUM_07;
            break;
        case MAZE_MAP_CHAR_NUM_08:
            return MAZE_MAP_CHAR_NUM_08;
            break;
        case MAZE_MAP_CHAR_NUM_09:
            return MAZE_MAP_CHAR_NUM_09;
            break;
        case MAZE_MAP_CHAR_NUM_10:
            return MAZE_MAP_CHAR_NUM_10;
            break;
        case MAZE_MAP_CHAR_STAR:
            return MAZE_MAP_CHAR_STAR;
            break;
        case MAZE_MAP_CHAR_BAR_00:
            return MAZE_MAP_CHAR_BAR_00;
            break;
        case MAZE_MAP_CHAR_BAR_01:
            return MAZE_MAP_CHAR_BAR_01;
            break;
        case MAZE_MAP_CHAR_ENEMY:
            return MAZE_MAP_CHAR_ENEMY;
            break;
        default:
            return MAZE_MAP_CHAR_WALL;
            break;
    }
}


//-----------------------------------------------------------------------------
//  関数名  :CheckAnswer
//
//  work    :答えを調べる
//  in      :int i_dir  方向
//  out     :TRUE
//          :FALSE
//  note    :なし
//-----------------------------------------------------------------------------
static int CheckAnswer(int i_dir)
{
    int ofx,ofy;

    //----検索方向よりオフセット選択
    switch(i_dir)
    {
        case DIR_UP:
            ofx=0;
            ofy=-1;
            break;
        case DIR_DOWN:
            ofx=0;
            ofy=1;
            break;
        case DIR_LEFT:
            ofx=-1;
            ofy=0;
            break;
        case DIR_RIGHT:
            ofx=1;
            ofy=0;
            break;
        default:
            ofx=0;
            ofy=0;
            break;
    }

    //----調べる
    if( MGameMgr.Map.Data[MGameMgr.GunGun.Py+ofy][MGameMgr.GunGun.Px+ofx]==MGameMgr.Answer[MGameMgr.QuestionIndex] )
    {//正解
        return TRUE;
    }
    //不正解
    return FALSE;
}

//-----------------------------------------------------------------------------
//  関数名  :ClearAnswer
//
//  work    :答えをクリア
//  in      :int i_x
//          :int i_y
//  out     :なし
//  note    :なし
//-----------------------------------------------------------------------------
static void ClearAnswer(int i_x,int i_y)
{
    //答えをマップ上からクリア
    MGameMgr.Map.Data[i_y][i_x] = MAZE_MAP_CHAR_NONE;
}


//-----------------------------------------------------------------------------
//  関数名  :SetAnswer
//
//  work    :答えをセット
//  in      :int i_val
//          :int i_x
//          :int i_y
//  out     :なし
//  note    :なし
//-----------------------------------------------------------------------------
static void SetAnswer(int i_val, int i_x,int i_y)
{
    if( MGameMgr.Map.Data[i_y][i_x]==MAZE_MAP_CHAR_NONE )
    {
        //答えをマップ上へセット
        MGameMgr.Map.Data[i_y][i_x] = i_val;
    }
}


//-----------------------------------------------------------------------------
//  関数名  :SetBar
//
//  work    :柵をセット
//  in      :int i_val
//          :int i_x
//          :int i_y
//  out     :なし
//  note    :なし
//-----------------------------------------------------------------------------
static void SetBar(int i_val, int i_x,int i_y)
{
    if( MGameMgr.Map.Data[i_y][i_x]==MAZE_MAP_CHAR_NONE )
    {
        //柵をマップ上へセット
        MGameMgr.Map.Data[i_y][i_x] = i_val;
    }
}


//-----------------------------------------------------------------------------
//  関数名  :SetStar
//
//  work    :柵をセット
//  in      :int i_val
//          :int i_x
//          :int i_y
//  out     :なし
//  note    :なし
//-----------------------------------------------------------------------------
static void SetStar(int i_val, int i_x,int i_y)
{
    if( MGameMgr.Map.Data[i_y][i_x]==MAZE_MAP_CHAR_NONE )
    {
        //星をマップ上へセット
        MGameMgr.Map.Data[i_y][i_x] = i_val;
    }
}



//-----------------------------------------------------------------------------
//  関数名  :ClearBar
//
//  work    :柵をクリア
//  in      :int i_x
//          :int i_y
//  out     :なし
//  note    :なし
//-----------------------------------------------------------------------------
static void ClearBar(int i_x,int i_y)
{
    if( (MGameMgr.Map.Data[i_y][i_x]==MAZE_MAP_CHAR_BAR_00) || (MGameMgr.Map.Data[i_y][i_x]==MAZE_MAP_CHAR_BAR_01) )
    {
        //柵をマップ上からクリア
        MGameMgr.Map.Data[i_y][i_x]=MAZE_MAP_CHAR_NONE;
    }
}


//-----------------------------------------------------------------------------
//  関数名  :ClearStar
//
//  work    :星をクリア
//  in      :int i_x
//  in      :int i_y
//  out     :なし
//  note    :なし
//-----------------------------------------------------------------------------
static void ClearStar(int i_x,int i_y)
{
    if( (MGameMgr.Map.Data[i_y][i_x]==MAZE_MAP_CHAR_STAR) )
    {
        //星をマップ上からクリア
        MGameMgr.Map.Data[i_y][i_x]=MAZE_MAP_CHAR_NONE;
    }
}



//-----------------------------------------------------------------------------
//  関数名  :CheckCought
//
//  work    :捕まり判定(グングン側で行う)
//  in      :int i_x1
//          :int i_y1
//          :int i_x2
//          :int i_y2
//  out     :TRUE   捕まった
//          :FALSE  捕まっていない
//  note    :なし
//-----------------------------------------------------------------------------
static int CheckCought(int i_x1,int i_y1,int i_x2,int i_y2)
{
    
    if( (i_x1==i_x2) &&  (i_y1==i_y2) ){
        return TRUE;
    }else{
        return FALSE;
    }
}


//-----------------------------------------------------------------------------
//  関数名  :CheckGunGunPos
//
//  work    :グングンのマップ上の位置をチェック
//  in      :int i_x
//          :int i_y
//  out     :TRUE   グングンがいる
//          :FALSE  グングンはいない
//  note    :なし
//-----------------------------------------------------------------------------
static int CheckGunGunPos(int i_x,int i_y)
{
    if( MGameMgr.GunGun.Px==i_x ){
        if( MGameMgr.GunGun.Py==i_y ){
            return TRUE;
        }
    }
    return FALSE;
}


//-----------------------------------------------------------------------------
//  関数名  :CheckGunGunPosArea
//
//  work    :グングンのマップ上位置から周り８方向かどうかをチェック
//  in      :int    i_x     検索位置X
//          :int    i_y     検索位置Y
//  out     :TRUE   グングンがいる
//          :FALSE  グングンはいない
//  note    :なし
//-----------------------------------------------------------------------------
static int CheckGunGunPosArea(int i_x,int i_y)
{
    //----------------
    //  ■■■
    //  ■※■
    //  ■■■
    //  左上から０～７
    //----------------
    static POS2D AreaPosTable[]=
    {
        //  X   Y
        {   -1, -1  },
        {   0,  -1  },
        {   1,  -1  },
        {   -1, 0   },
        {   1,  0   },
        {   -1, 1   },
        {   0,  1   },
        {   1,  1   },
    };
    int i;

    for(i=0;i<8;i++){
        if( MGameMgr.GunGun.Px == (i_x+AreaPosTable[i].x) ){
            if( MGameMgr.GunGun.Py == (i_x+AreaPosTable[i].y) ){
                return TRUE;
            }
        }
    }
    return FALSE;
}


//-----------------------------------------------------------------------------
//  関数名  :CheckKumaPos
//
//  work    :クマのマップ上の位置をチェック
//  in      :int i_x
//          :int i_y
//  out     :TRUE   クマがいる
//          :FALSE  クマはいない
//  note    :なし
//-----------------------------------------------------------------------------
static int CheckKumaPos(int i_x,int i_y)
{
    if( MGameMgr.Kuma.Px==i_x ){
        if( MGameMgr.Kuma.Py==i_y ){
            return TRUE;
        }
    }
    return FALSE;
}


//-----------------------------------------------------------------------------
//  関数名  :CheckStarPos
//
//  work    :星がマップ上の位置にあるかをチェック
//  in      :int i_x
//          :int i_y
//  out     :TRUE   星あり
//          :FALSE  星なし
//  note    :なし
//-----------------------------------------------------------------------------
static int CheckStarPos(int i_x,int i_y)
{
    if( MGameMgr.Map.Data[i_y][i_x]==MAZE_MAP_CHAR_STAR )
    {
        return TRUE;
    }
    return FALSE;
}



//-----------------------------------------------------------------------------
//  関数名  :GetKumaRandomMoveDirect
//
//  work    :ランダムで移動する方向データを取得(上下左右１ブロックのみ)
//  in      :int* ip_dir        移動方向
//          :                   DIR_UP          上
//          :                   DIR_DOWN        下
//          :                   DIR_LEFT        左
//          :                   DIR_RIGHT       右
//          :                   DIR_NOTHING     なし
//  out     :TRUE   移動可能
//          :FALSE  移動不可能
//  note    :なし
//-----------------------------------------------------------------------------
static int GetKumaRandomMoveDirect(int* ip_dir)
{

    int cnt;
    int chkmove[4];
    int sel[4];


    cnt = 0;
    chkmove[DIR_UP] = chkmove[DIR_DOWN] = chkmove[DIR_LEFT] = chkmove[DIR_RIGHT] = 0;
    sel[0]=sel[1]=sel[2]=sel[3]=0;

    //----自分の周りを確認
    if( CheckCharacterMaze(MGameMgr.Kuma.Px, MGameMgr.Kuma.Py, DIR_UP)==MAZE_MAP_CHAR_NONE ){
        chkmove[DIR_UP] = 1;
    }

    if( CheckCharacterMaze(MGameMgr.Kuma.Px, MGameMgr.Kuma.Py, DIR_DOWN)==MAZE_MAP_CHAR_NONE ){
        chkmove[DIR_DOWN] = 1;
    }

    if( CheckCharacterMaze(MGameMgr.Kuma.Px, MGameMgr.Kuma.Py, DIR_LEFT)==MAZE_MAP_CHAR_NONE ){
        chkmove[DIR_LEFT] = 1;
    }

    if( CheckCharacterMaze(MGameMgr.Kuma.Px, MGameMgr.Kuma.Py, DIR_RIGHT)==MAZE_MAP_CHAR_NONE ){
        chkmove[DIR_RIGHT] = 1;
    }

    //----移動可能な方向を取得
    if(chkmove[DIR_UP]){
        sel[cnt]=DIR_UP;
        cnt++;
        rand();
    }

    if(chkmove[DIR_DOWN]){
        sel[cnt]=DIR_DOWN;
        cnt++;
        rand();
    }

    if(chkmove[DIR_LEFT]){
        sel[cnt]=DIR_LEFT;
        cnt++;
        rand();
    }

    if(chkmove[DIR_RIGHT]){
        sel[cnt]=DIR_RIGHT;
        cnt++;
        rand();
    }

    //----選択できる中からランダムで方向を返す
    if(cnt==0)
    {
        *ip_dir = DIR_NOTHING;
        return FALSE;
    }else
    {
        *ip_dir = sel[rand()%cnt];
        return TRUE;
    }
}


//  //-----------------------------------------------------------------------------
//  //  関数名  :CreateQuestion
//  //
//  //  work    :問題生成
//  //  in      :i_type     MAZE_GAME_QUESTION_TYPE_ADDITION        足算
//  //          :           MAZE_GAME_QUESTION_TYPE_SUBTRACTION     引算
//  //          :i_num      答え(１～１０)
//  //          :*ip_qtnum  値を取得する変数へのポインタ
//  //  out     :int    TRUE
//  //          :       FALSE
//  //  note    :なし
//  //-----------------------------------------------------------------------------
//  static int CreateQuestion(int i_type,int i_num, MAZE_GAME_QUESTION_NUM_DATA* ip_qtnum)
//  {
//      int work1,work2;
//
//      if(i_num>10)    return FALSE;
//      if(i_num<1)     return FALSE;
//
//      work1 = work2 = 0;
//      switch(i_type)
//      {
//          case MAZE_GAME_QUESTION_TYPE_ADDITION:  //足算
//              if(i_num==0) return FALSE;
//              work1           = rand() % i_num;
//              work2           = i_num - work1;
//              
//              //work1 + work2 = i_num
//              ip_qtnum->num1  = work1;
//              ip_qtnum->num2  = work2;
//              ip_qtnum->num3  = i_num;
//              
//              break;
//          case MAZE_GAME_QUESTION_TYPE_SUBTRACTION:   //引算
//              work1           = 11 - i_num;
//              if(work1==0) return FALSE;
//              work1           = rand() % work1;
//              work2           = work1 + i_num;
//              
//              //work2 - work1 = i_num
//              ip_qtnum->num1  = work2;
//              ip_qtnum->num2  = work1;
//              ip_qtnum->num3  = i_num;
//              
//              break;
//          default:
//              return FALSE;
//      }
//
//      return TRUE;
//  }
//

//-----------------------------------------------------------------------------
//  関数名  :CreateQuestion2
//
//  work    :問題生成
//  in      :i_type     MAZE_GAME_QUESTION_TYPE_ADDITION        足算
//          :           MAZE_GAME_QUESTION_TYPE_SUBTRACTION     引算
//          :i_num      答え(１～１０)
//          :*ip_qtnum  値を取得する変数へのポインタ
//  out     :int    TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int CreateQuestion2(int i_type,int i_num, MAZE_GAME_QUESTION_NUM_DATA* ip_qtnum)
{
    int randindex,numindex;


    if(i_num>11)    return FALSE;
    if(i_num<0)     return FALSE;

    switch(i_type)
    {
        case MAZE_GAME_QUESTION_TYPE_ADDITION:  //足算
            
            switch(MGameMgr.PlayLevel)
            {
                //LEVEL-1
                case 0:
                    // 1- 6
                    numindex        = i_num - 1;
                    randindex       = rand() % MazeQuestionGetTable_Level_1[numindex].Num;
                    ip_qtnum->num1  = MazeQuestionGetTable_Level_1[numindex].Data[randindex].Val[0];
                    ip_qtnum->num2  = MazeQuestionGetTable_Level_1[numindex].Data[randindex].Val[1];
                    ip_qtnum->num3  = i_num;
                    break;
                //LEVEL-2
                case 1:
                    //7-10
                    numindex        = i_num - 7;
                    randindex       = rand() % MazeQuestionGetTable_Level_2[numindex].Num;
                    ip_qtnum->num1  = MazeQuestionGetTable_Level_2[numindex].Data[randindex].Val[0];
                    ip_qtnum->num2  = MazeQuestionGetTable_Level_2[numindex].Data[randindex].Val[1];
                    ip_qtnum->num3  = i_num;
                    break;
                default:
            }
            
            break;
        case MAZE_GAME_QUESTION_TYPE_SUBTRACTION:   //引算
            
            switch(MGameMgr.PlayLevel)
            {
                case 2:
                    // i_num:0-5
                    numindex        = i_num;
                    randindex       = rand() % MazeQuestionGetTable_Level_3[numindex].Num;
                    ip_qtnum->num1  = MazeQuestionGetTable_Level_3[numindex].Data[randindex].Val[0];
                    ip_qtnum->num2  = MazeQuestionGetTable_Level_3[numindex].Data[randindex].Val[1];
                    ip_qtnum->num3  = i_num;
                    break;
                case 3:
                    // 1-10
                    numindex        = i_num - 1;
                    randindex       = rand() % MazeQuestionGetTable_Level_4[numindex].Num;
                    ip_qtnum->num1  = MazeQuestionGetTable_Level_4[numindex].Data[randindex].Val[0];
                    ip_qtnum->num2  = MazeQuestionGetTable_Level_4[numindex].Data[randindex].Val[1];
                    ip_qtnum->num3  = i_num;
                    break;
                case 4:
                    // 0-10
                    numindex        = i_num;
                    randindex       = rand() % MazeQuestionGetTable_Level_5[numindex].Num;
                    ip_qtnum->num1  = MazeQuestionGetTable_Level_5[numindex].Data[randindex].Val[0];
                    ip_qtnum->num2  = MazeQuestionGetTable_Level_5[numindex].Data[randindex].Val[1];
                    ip_qtnum->num3  = i_num;
                    break;
                default:
            }
            
            break;
        default:
            return FALSE;
    }

    return TRUE;
}


//-----------------------------------------------------------------------------
//  関数名  :DrawQuestion
//
//  work    :問題表示
//  in      :int i_index
//          :int i_x
//          :int i_y
//          :int i_z
//          :int i_flash
//          :int i_ansflag
//  out     :なし
//  note    :足算   ２と３は？
//          :引算   ９は３と？
//-----------------------------------------------------------------------------
static void DrawQuestion(int i_index,int i_x,int i_y,int i_z,int i_flash,int i_ansflag )
{
    static int QNumTable[]={
        MAZE_CHAR_GAME_QUESTION_NUM_00,     //出題の数字”０”
        MAZE_CHAR_GAME_QUESTION_NUM_01,     //出題の数字”１”
        MAZE_CHAR_GAME_QUESTION_NUM_02,     //出題の数字”２”
        MAZE_CHAR_GAME_QUESTION_NUM_03,     //出題の数字”３”
        MAZE_CHAR_GAME_QUESTION_NUM_04,     //出題の数字”４”
        MAZE_CHAR_GAME_QUESTION_NUM_05,     //出題の数字”５”
        MAZE_CHAR_GAME_QUESTION_NUM_06,     //出題の数字”６”
        MAZE_CHAR_GAME_QUESTION_NUM_07,     //出題の数字”７”
        MAZE_CHAR_GAME_QUESTION_NUM_08,     //出題の数字”８”
        MAZE_CHAR_GAME_QUESTION_NUM_09,     //出題の数字”９”
        MAZE_CHAR_GAME_QUESTION_NUM_10,     //出題の数字”１０”
    };

    static int QStrTable1[]={
        MAZE_CHAR_GAME_QUESTION_STR_TO,     //出題の”と”  足算
        MAZE_CHAR_GAME_QUESTION_STR_HA,     //出題の”は”  引算
    };

    static int QStrTable2[]={
        MAZE_CHAR_GAME_QUESTION_STR_HA,     //出題の”は”  引算
        MAZE_CHAR_GAME_QUESTION_STR_TO,     //出題の”と”  足算
    };

    SPRITE_DATA SpData;


    //----
    if(i_index < 0 ){
        i_index = 0;
    }else if( i_index > QuestionNumTable[MGameMgr.PlayLevel]-1 ){
        i_index = QuestionNumTable[MGameMgr.PlayLevel]-1;
    }else{
    
    }

    //----描画　数字
    if(i_flash){
        //----描画　数字
        SpData.No       = QNumTable[ MGameMgr.Question.Data[i_index].QuestionNum.num1 ];    //インデックス番号
        SpData.PosX     = i_x + QUESTION_NUM1_POS_X;    //X位置
        SpData.PosY     = i_y + QUESTION_NUM1_POS_Y;    //Y位置
        SpData.PosZ     = i_z;                          //優先順位
        SpData.ScaleX   = SCALE10;                      //スケールX
        SpData.ScaleY   = SCALE10;                      //スケールY
        SpData.Rotate   = ROTATE000;                    //回転角
        SpData.Reverse  = NOREVERS;                     //反転コード
        DrawSprite( &SpData );                          //スプライト描画
    }

    //----描画　”は”または”と”
    SpData.No       = QStrTable1[QuestionTypeTable[MGameMgr.PlayLevel]];                //インデックス番号
    SpData.PosX     = i_x + QUESTION_STR1_POS_X;    //X位置
    SpData.PosY     = i_y + QUESTION_STR1_POS_Y;    //Y位置
    SpData.PosZ     = i_z;                          //優先順位
    SpData.ScaleX   = SCALE10;                      //スケールX
    SpData.ScaleY   = SCALE10;                      //スケールY
    SpData.Rotate   = ROTATE000;                    //回転角
    SpData.Reverse  = NOREVERS;                     //反転コード
    DrawSprite( &SpData );                          //スプライト描画

    //----フラッシュ用
    if(i_flash){
        //----描画　数字
//      if( QuestionTypeTable[MGameMgr.PlayLevel]==MAZE_GAME_QUESTION_TYPE_ADDITION ){
//          SpData.No       = QNumTable[MGameMgr.Question.Data[i_index].QuestionNum.num2];  //インデックス番号
//      }else{
//          SpData.No       = QNumTable[MGameMgr.Question.Data[i_index].QuestionNum.num3];  //インデックス番号
//      }


        SpData.No       = QNumTable[MGameMgr.Question.Data[i_index].QuestionNum.num2];  //インデックス番号
        SpData.PosX     = i_x + QUESTION_NUM2_POS_X;    //X位置
        SpData.PosY     = i_y + QUESTION_NUM2_POS_Y;    //Y位置
        SpData.PosZ     = i_z;                          //優先順位
        SpData.ScaleX   = SCALE10;                      //スケールX
        SpData.ScaleY   = SCALE10;                      //スケールY
        SpData.Rotate   = ROTATE000;                    //回転角
        SpData.Reverse  = NOREVERS;                     //反転コード
        DrawSprite( &SpData );                          //スプライト描画
    }

    //----描画　”は”または”と”
    SpData.No       = QStrTable2[QuestionTypeTable[MGameMgr.PlayLevel]];                //インデックス番号
    SpData.PosX     = i_x + QUESTION_STR2_POS_X;    //X位置
    SpData.PosY     = i_y + QUESTION_STR2_POS_Y;    //Y位置
    SpData.PosZ     = i_z;                          //優先順位
    SpData.ScaleX   = SCALE10;                      //スケールX
    SpData.ScaleY   = SCALE10;                      //スケールY
    SpData.Rotate   = ROTATE000;                    //回転角
    SpData.Reverse  = NOREVERS;                     //反転コード
    DrawSprite( &SpData );                          //スプライト描画

    //----描画　数字
//  if( QuestionTypeTable[MGameMgr.PlayLevel]==MAZE_GAME_QUESTION_TYPE_ADDITION ){
//      SpData.No       = QNumTable[MGameMgr.Question.Data[i_index].QuestionNum.num3];  //インデックス番号
//  }else{
//      SpData.No       = QNumTable[MGameMgr.Question.Data[i_index].QuestionNum.num2];  //インデックス番号
//  }

    SpData.No       = QNumTable[MGameMgr.Question.Data[i_index].QuestionNum.num3];  //インデックス番号

    //----フラッシュ用
    if(i_flash){
        //----フラグで答えの表示を管理
        if(!i_ansflag){
            SpData.No       = MAZE_CHAR_GAME_QUESTION_MARK_H;           //インデックス番号
        }
    
        SpData.PosX     = i_x + QUESTION_NUM3_POS_X;    //X位置
        SpData.PosY     = i_y + QUESTION_NUM3_POS_Y;    //Y位置
        SpData.PosZ     = i_z;                          //優先順位
        SpData.ScaleX   = SCALE10;                      //スケールX
        SpData.ScaleY   = SCALE10;                      //スケールY
        SpData.Rotate   = ROTATE000;                    //回転角
        SpData.Reverse  = NOREVERS;                     //反転コード
        DrawSprite( &SpData );                          //スプライト描画
    }
}


//-----------------------------------------------------------------------------
//  関数名  :EventGunGun
//
//  work    :イベント処理でのグングン
//  in      :int i_etype
//  out     :なし
//  note    :なし
//-----------------------------------------------------------------------------
static void EventGunGun(int i_etype)
{

    static MAZE_SPRITE_DATA ClearGunGunAnmTable[]=
    {
        {   MAZE_CHAR_EVENT_GUNGUN_BANZAI_ARM_YOKO_LEFT,    89,     141 },  //LEFT
        {   MAZE_CHAR_EVENT_GUNGUN_BANZAI_ARM_UE_LEFT,      94,     119 },
        {   MAZE_CHAR_EVENT_GUNGUN_BANZAI_ARM_YOKO_RIGHT,   195,    138 },  //RIGHT
        {   MAZE_CHAR_EVENT_GUNGUN_BANZAI_ARM_UE_RIGHT,     188,    117 },
        {   MAZE_CHAR_EVENT_GUNGUN_BANZAI_MOUTH,            138,    127 },  //MOUTH
        {   -1,                                             0,      0   },
    };

    static MAZE_SPRITE_DATA FalseBakuGunGunAnmTable[]=
    {
        {   MAZE_CHAR_EVENT_GUNGUN_BOROBORO_00,     -12,    0   },
        {   MAZE_CHAR_EVENT_GUNGUN_BOROBORO_01,     0,      -14 },
    };

    static MAZE_SPRITE_DATA FalseGutsGunGunAnmTable[]=
    {
        {   MAZE_CHAR_EVENT_GUNGUN_ZITANDA_00,  0,  0   },
        {   MAZE_CHAR_EVENT_GUNGUN_ZITANDA_01,  0,  0   },
    };

    SPRITE_DATA SpData;
    double dwx=0;


    switch(i_etype)
    {
        //----------------------------------------クリア：グングンバンザイ：停止は手を上げ、口を閉じる
        case MAZE_EVENT_CLEAR:
            
            //----アニメ停止
            if(++MGameMgr.Event.GunGunTimer>=MAZE_GAME_CLEAR_EVENT_ANM_STOP_TIME)
            {
                MGameMgr.Event.GunGunTimer=MAZE_GAME_CLEAR_EVENT_ANM_STOP_TIME;
            }else{
                //----アニメ切り替え
                if(++MGameMgr.Event.GunGunAnmWaitTime > MAZE_GAME_EVENT_ANM_WAIT_TIME)
                {
                    MGameMgr.Event.GunGunAnmWaitTime = 0;
                    MGameMgr.Event.GunGunAnmIndex^=1;
                }
            }

            //----グングン左手
            SpData.No       = ClearGunGunAnmTable[0+MGameMgr.Event.GunGunAnmIndex].No;  //インデックス番号
            SpData.PosX     = ClearGunGunAnmTable[0+MGameMgr.Event.GunGunAnmIndex].Ofx; //X位置
            SpData.PosY     = ClearGunGunAnmTable[0+MGameMgr.Event.GunGunAnmIndex].Ofy; //Y位置
            SpData.PosZ     = PRIORITY_MAZE_EVENT_BG-10;        //優先順位
            SpData.ScaleX   = SCALE10;                          //スケールX
            SpData.ScaleY   = SCALE10;                          //スケールY
            SpData.Rotate   = ROTATE000;                        //回転角
            SpData.Reverse  = NOREVERS;                         //反転コード
            DrawSprite( &SpData );                              //スプライト描画

            //----グングン右手
            SpData.No       = ClearGunGunAnmTable[2+MGameMgr.Event.GunGunAnmIndex].No;  //インデックス番号
            SpData.PosX     = ClearGunGunAnmTable[2+MGameMgr.Event.GunGunAnmIndex].Ofx; //X位置
            SpData.PosY     = ClearGunGunAnmTable[2+MGameMgr.Event.GunGunAnmIndex].Ofy; //Y位置
            SpData.PosZ     = PRIORITY_MAZE_EVENT_BG-10;        //優先順位
            SpData.ScaleX   = SCALE10;                          //スケールX
            SpData.ScaleY   = SCALE10;                          //スケールY
            SpData.Rotate   = ROTATE000;                        //回転角
            SpData.Reverse  = NOREVERS;                         //反転コード
            DrawSprite( &SpData );                              //スプライト描画

            //----グングン口
            if(MGameMgr.Event.GunGunAnmIndex==0){
                SpData.No       = ClearGunGunAnmTable[4+MGameMgr.Event.GunGunAnmIndex].No;  //インデックス番号
                SpData.PosX     = ClearGunGunAnmTable[4+MGameMgr.Event.GunGunAnmIndex].Ofx; //X位置
                SpData.PosY     = ClearGunGunAnmTable[4+MGameMgr.Event.GunGunAnmIndex].Ofy; //Y位置
                SpData.PosZ     = PRIORITY_MAZE_EVENT_BG-10;        //優先順位
                SpData.ScaleX   = SCALE10;                          //スケールX
                SpData.ScaleY   = SCALE10;                          //スケールY
                SpData.Rotate   = ROTATE000;                        //回転角
                SpData.Reverse  = NOREVERS;                         //反転コード
                DrawSprite( &SpData );                              //スプライト描画
            }

            //----グングン体
            SpData.No       = MAZE_CHAR_EVENT_GUNGUN_BANZAI_BODY;   //インデックス番号
            SpData.PosX     = MGameMgr.Event.GunGunPosX;            //X位置
            SpData.PosY     = MGameMgr.Event.GunGunPosY;            //Y位置
            SpData.PosZ     = PRIORITY_MAZE_EVENT_BG-10;            //優先順位
            SpData.ScaleX   = SCALE10;                              //スケールX
            SpData.ScaleY   = SCALE10;                              //スケールY
            SpData.Rotate   = ROTATE000;                            //回転角
            SpData.Reverse  = NOREVERS;                             //反転コード
            DrawSprite( &SpData );                                  //スプライト描画
            
            break;
        //----------------------------------------失敗０：爆発
        case MAZE_EVENT_FALSE_BAKU:
            
            if(++MGameMgr.Event.GunGunTimer>MAZE_GAME_EVENT_BAKUHATSAU_WAIT_TIME)
            {
                //----Y
                MGameMgr.Event.GunGunAnmIndex   = 1;
                MGameMgr.Event.GunGunPosY       += 1;
                if(MGameMgr.Event.GunGunPosY>340){
                    MGameMgr.Event.GunGunPosY=340;
                }
                
                //---角度
                MGameMgr.Event.GunGunAngle += 4;
                if(MGameMgr.Event.GunGunAngle >= 360){
                    MGameMgr.Event.GunGunAngle = 0;
                }
                
                //----X
                MGameMgr.Event.GunGunWorkX      = (double)(MGameMgr.Event.GunGunPosX + 5 * sin( DEG2RAD(MGameMgr.Event.GunGunAngle) ));
                MGameMgr.Event.GunGunPosX       = (int)MGameMgr.Event.GunGunWorkX;
            }

            //----グングン体
            SpData.No       = FalseBakuGunGunAnmTable[MGameMgr.Event.GunGunAnmIndex].No;                                //インデックス番号
            SpData.PosX     = MGameMgr.Event.GunGunPosX + FalseBakuGunGunAnmTable[MGameMgr.Event.GunGunAnmIndex].Ofx;   //X位置
            SpData.PosY     = MGameMgr.Event.GunGunPosY + FalseBakuGunGunAnmTable[MGameMgr.Event.GunGunAnmIndex].Ofy;   //Y位置
            SpData.PosZ     = PRIORITY_MAZE_EVENT_BG-10;            //優先順位
            SpData.ScaleX   = SCALE10;                              //スケールX
            SpData.ScaleY   = SCALE10;                              //スケールY
            SpData.Rotate   = ROTATE000;                            //回転角
            SpData.Reverse  = NOREVERS;                             //反転コード
            DrawSprite( &SpData );                                  //スプライト描画
            
            break;
        //----------------------------------------失敗１：クマガッツポーズ
        case MAZE_EVENT_FALSE_GUTS:
            
//          if(++MGameMgr.Event.GunGunTimer>=MAZE_GAME_EVENT_GUTS_GUNGUN_ANM_STOP_TIME)
//          {
//              MGameMgr.Event.GunGunTimer=MAZE_GAME_EVENT_GUTS_GUNGUN_ANM_STOP_TIME;
//          }else
//          {
                if(++MGameMgr.Event.GunGunAnmWaitTime > MAZE_GAME_EVENT_ANM_WAIT_TIME)
                {
                    MGameMgr.Event.GunGunAnmWaitTime = 0;
                    MGameMgr.Event.GunGunAnmIndex^=1;
                }
//          }
            
            //----グングン体
            SpData.No       = FalseGutsGunGunAnmTable[MGameMgr.Event.GunGunAnmIndex].No;                                //インデックス番号
            SpData.PosX     = MGameMgr.Event.GunGunPosX + FalseGutsGunGunAnmTable[MGameMgr.Event.GunGunAnmIndex].Ofx;   //X位置
            SpData.PosY     = MGameMgr.Event.GunGunPosY + FalseGutsGunGunAnmTable[MGameMgr.Event.GunGunAnmIndex].Ofy;   //Y位置
            SpData.PosZ     = PRIORITY_MAZE_EVENT_BG-10;        //優先順位
            SpData.ScaleX   = SCALE10;                          //スケールX
            SpData.ScaleY   = SCALE10;                          //スケールY
            SpData.Rotate   = ROTATE000;                        //回転角
            SpData.Reverse  = NOREVERS;                         //反転コード
            DrawSprite( &SpData );                              //スプライト描画
            
            //----影
            SpData.No       = MAZE_CHAR_EVENT_SHADOW_SMALL;     //番号
            SpData.PosX     = MGameMgr.Event.GunGunPosX + 1;    //X位置
            SpData.PosY     = MGameMgr.Event.GunGunPosY + 48;   //Y位置
            SpData.PosZ     = PRIORITY_MAZE_EVENT_BG-6;         //優先順位
            SpData.ScaleX   = SCALE10;                          //スケールX
            SpData.ScaleY   = SCALE10;                          //スケールY
            SpData.Rotate   = ROTATE000;                        //回転角
            SpData.Reverse  = NOREVERS;                         //反転コード
            DrawSprite( &SpData );                              //スプライト描画
            
            break;
        default:
    }
}


//-----------------------------------------------------------------------------
//  関数名  :EventKuma
//
//  work    :イベント処理でのクマ
//  in      :int i_etype
//  out     :なし
//  note    :なし
//-----------------------------------------------------------------------------
static void EventKuma(int i_etype)
{
    static MAZE_SPRITE_DATA ClearKumaAnmTableble[]=
    {
        {   MAZE_CHAR_EVENT_KUMA_PARTS_13,  0,  0   },      //走る左A
        {   MAZE_CHAR_EVENT_KUMA_PARTS_14,  0,  0   },      //走る左B
        {   MAZE_CHAR_EVENT_KUMA_PARTS_15,  0,  0   },      //走る右A
        {   MAZE_CHAR_EVENT_KUMA_PARTS_16,  0,  0   },      //走る右B
    };

    static MAZE_SPRITE_DATA BakuhatsuKumaAnmTable[]=
    {
        {   MAZE_CHAR_EVENT_KUMA_BANZAI_00,     0,  0   },
        {   MAZE_CHAR_EVENT_KUMA_BANZAI_01,     0,  0   },
        {   MAZE_CHAR_EVENT_KUMA_BANZAI_02,     0,  0   },
    };

    static MAZE_SPRITE_DATA GutsKumaAnmTable[]=
    {
        {   MAZE_CHAR_EVENT_KUMA_GUTS_00_ARM_LEFT,      95,     118 },
        {   MAZE_CHAR_EVENT_KUMA_GUTS_01_ARM_LEFT,      94,     103 },
        {   MAZE_CHAR_EVENT_KUMA_GUTS_00_ARM_RIGHT,     196,    118 },
        {   MAZE_CHAR_EVENT_KUMA_GUTS_01_ARM_RIGHT,     193,    103 },
    };

    SPRITE_DATA SpData;


    switch(i_etype)
    {
        //----------------------------------------クリア：グングンバンザイ
        case MAZE_EVENT_CLEAR:
            
            if(++MGameMgr.Event.KumaAnmWaitTime > MAZE_GAME_EVENT_ANM_WAIT_TIME/4){
                MGameMgr.Event.KumaAnmWaitTime  = 0;
                MGameMgr.Event.KumaAnmIndex     ^= 1;
                MGameMgr.Event.KumaAnmNo        = ClearKumaAnmTableble[MGameMgr.Event.KumaMoveDirX+1+MGameMgr.Event.KumaAnmIndex].No;
            }
            
            //----移動
            MGameMgr.Event.KumaPosX += 2*MGameMgr.Event.KumaMoveDirX;
            MGameMgr.Event.KumaMoveDirX;        //クマ移動方向Ｘ
            
            if( (MGameMgr.Event.KumaPosX < -30) || (MGameMgr.Event.KumaPosX > 360) ){
                MGameMgr.Event.KumaMoveDirX *= -1;
            }
            
            //MGameMgr.Event.KumaStopFlag;      //停止フラグ 
            
            //----クマ
            SpData.No       = ClearKumaAnmTableble[MGameMgr.Event.KumaMoveDirX+1+MGameMgr.Event.KumaAnmIndex].No;   //インデックス番号
            SpData.PosX     = MGameMgr.Event.KumaPosX;          //X位置
            SpData.PosY     = MGameMgr.Event.KumaPosY;          //Y位置
            SpData.PosZ     = PRIORITY_MAZE_EVENT_BG-3;         //優先順位
            SpData.ScaleX   = SCALE10;                          //スケールX
            SpData.ScaleY   = SCALE10;                          //スケールY
            SpData.Rotate   = ROTATE000;                        //回転角
            SpData.Reverse  = NOREVERS;                         //反転コード
            DrawSprite( &SpData );                              //スプライト描画
            
            break;
        //----------------------------------------失敗０：爆発
        case MAZE_EVENT_FALSE_BAKU:
            
            if(++MGameMgr.Event.KumaTimer>=MAZE_GAME_EVENT_BAKUHATSAU_KUMA_ANM_STOP_TIME)
            {
                MGameMgr.Event.KumaTimer = MAZE_GAME_EVENT_BAKUHATSAU_KUMA_ANM_STOP_TIME;
            }else{
                if(++MGameMgr.Event.KumaAnmWaitTime > MAZE_GAME_EVENT_ANM_WAIT_TIME){
                    MGameMgr.Event.KumaAnmWaitTime  = 0;
                    MGameMgr.Event.KumaAnmIndex     ^= 1;
                    MGameMgr.Event.KumaAnmNo        = BakuhatsuKumaAnmTable[MGameMgr.Event.KumaAnmIndex+1].No;
                }
            }
            
            //----クマ
            SpData.No       = BakuhatsuKumaAnmTable[MGameMgr.Event.KumaAnmIndex].No;    //番号
            SpData.PosX     = MGameMgr.Event.KumaPosX;          //X位置
            SpData.PosY     = MGameMgr.Event.KumaPosY;          //Y位置
            SpData.PosZ     = PRIORITY_MAZE_EVENT_BG-7;         //優先順位
            SpData.ScaleX   = SCALE10;                          //スケールX
            SpData.ScaleY   = SCALE10;                          //スケールY
            SpData.Rotate   = ROTATE000;                        //回転角
            SpData.Reverse  = NOREVERS;                         //反転コード
            DrawSprite( &SpData );                              //スプライト描画
            
            //----影
            SpData.No       = MAZE_CHAR_EVENT_SHADOW_SMALL;     //番号
            SpData.PosX     = MGameMgr.Event.KumaPosX + 4;      //X位置
            SpData.PosY     = MGameMgr.Event.KumaPosY + 45;     //Y位置
            SpData.PosZ     = PRIORITY_MAZE_EVENT_BG-6;         //優先順位
            SpData.ScaleX   = SCALE10;                          //スケールX
            SpData.ScaleY   = SCALE10;                          //スケールY
            SpData.Rotate   = ROTATE000;                        //回転角
            SpData.Reverse  = NOREVERS;                         //反転コード
            DrawSprite( &SpData );                              //スプライト描画
            
            
            break;
        //----------------------------------------失敗１：クマガッツポーズ
        case MAZE_EVENT_FALSE_GUTS:
            if(++MGameMgr.Event.KumaTimer >= MAZE_GAME_EVENT_GUTS_KUMA_ANM_STOP_TIME)
            {
                MGameMgr.Event.KumaTimer = MAZE_GAME_EVENT_GUTS_KUMA_ANM_STOP_TIME;
            }else
            {
                if(++MGameMgr.Event.KumaAnmWaitTime > MAZE_GAME_EVENT_ANM_WAIT_TIME){
                    MGameMgr.Event.KumaAnmWaitTime  = 0;
                    MGameMgr.Event.KumaAnmIndex     ^= 1;
                    MGameMgr.Event.KumaAnmNo        = GutsKumaAnmTable[MGameMgr.Event.KumaAnmIndex].No;
                }
            }

            //----クマ口
            if(MGameMgr.Event.KumaAnmIndex){
                SpData.No       = MAZE_CHAR_EVENT_KUMA_ENTRY_MOUSE; //番号
                SpData.PosX     = 142;                              //X位置
                SpData.PosY     = 130;                              //Y位置
                SpData.PosZ     = PRIORITY_MAZE_EVENT_BG-8;         //優先順位
                SpData.ScaleX   = SCALE10;                          //スケールX
                SpData.ScaleY   = SCALE10;                          //スケールY
                SpData.Rotate   = ROTATE000;                        //回転角
                SpData.Reverse  = NOREVERS;                         //反転コード
                DrawSprite( &SpData );                              //スプライト描画
            }

            //----クマ頭
            SpData.No       = MAZE_CHAR_EVENT_KUMA_HEAD_00;     //番号
            SpData.PosX     = 121;                              //X位置
            SpData.PosY     = 79;                               //Y位置
            SpData.PosZ     = PRIORITY_MAZE_EVENT_BG-7;         //優先順位
            SpData.ScaleX   = SCALE10;                          //スケールX
            SpData.ScaleY   = SCALE10;                          //スケールY
            SpData.Rotate   = ROTATE000;                        //回転角
            SpData.Reverse  = NOREVERS;                         //反転コード
            DrawSprite( &SpData );                              //スプライト描画

            //----腕左
            SpData.No       = GutsKumaAnmTable[MGameMgr.Event.KumaAnmIndex + 0].No;     //番号
            SpData.PosX     = GutsKumaAnmTable[MGameMgr.Event.KumaAnmIndex + 0].Ofx;    //X位置
            SpData.PosY     = GutsKumaAnmTable[MGameMgr.Event.KumaAnmIndex + 0].Ofy;    //Y位置
            SpData.PosZ     = PRIORITY_MAZE_EVENT_BG-7;         //優先順位
            SpData.ScaleX   = SCALE10;                          //スケールX
            SpData.ScaleY   = SCALE10;                          //スケールY
            SpData.Rotate   = ROTATE000;                        //回転角
            SpData.Reverse  = NOREVERS;                         //反転コード
            DrawSprite( &SpData );                              //スプライト描画

            //----腕右
            SpData.No       = GutsKumaAnmTable[MGameMgr.Event.KumaAnmIndex + 2].No;     //番号
            SpData.PosX     = GutsKumaAnmTable[MGameMgr.Event.KumaAnmIndex + 2].Ofx;    //X位置
            SpData.PosY     = GutsKumaAnmTable[MGameMgr.Event.KumaAnmIndex + 2].Ofy;    //Y位置
            SpData.PosZ     = PRIORITY_MAZE_EVENT_BG-7;         //優先順位
            SpData.ScaleX   = SCALE10;                          //スケールX
            SpData.ScaleY   = SCALE10;                          //スケールY
            SpData.Rotate   = ROTATE000;                        //回転角
            SpData.Reverse  = NOREVERS;                         //反転コード
            DrawSprite( &SpData );                              //スプライト描画

            //----クマ体
            SpData.No       = MAZE_CHAR_EVENT_KUMA_BODY;        //番号
            SpData.PosX     = 113;                              //X位置
            SpData.PosY     = 140;                              //Y位置
            SpData.PosZ     = PRIORITY_MAZE_EVENT_BG-7;         //優先順位
            SpData.ScaleX   = SCALE10;                          //スケールX
            SpData.ScaleY   = SCALE10;                          //スケールY
            SpData.Rotate   = ROTATE000;                        //回転角
            SpData.Reverse  = NOREVERS;                         //反転コード
            DrawSprite( &SpData );                              //スプライト描画
            
            break;
        default:
    }
}


//-----------------------------------------------------------------------------
//  関数名  :MazeEventBg
//
//  work    :イベント時の背景
//  in      :なし
//  out     :なし
//  note    :なし
//-----------------------------------------------------------------------------
static void MazeEventBg(void)
{
    SPRITE_DATA SpData;

    //----背景
    SpData.No       = MAZE_CHAR_EVENT_BG_02;    //インデックス番号
    SpData.PosX     = 0;                        //X位置
    SpData.PosY     = 47;                       //Y位置
    SpData.PosZ     = PRIORITY_MAZE_EVENT_BG-5; //優先順位
    SpData.ScaleX   = SCALE10;                  //スケールX
    SpData.ScaleY   = SCALE10;                  //スケールY
    SpData.Rotate   = ROTATE000;                //回転角
    SpData.Reverse  = NOREVERS;                 //反転コード
    DrawSprite( &SpData );                      //スプライト描画

    SpData.No       = MAZE_CHAR_EVENT_BG_03;    //インデックス番号
    SpData.PosX     = 256;                      //X位置
    SpData.PosY     = 47;                       //Y位置
    SpData.PosZ     = PRIORITY_MAZE_EVENT_BG-5; //優先順位
    SpData.ScaleX   = SCALE10;                  //スケールX
    SpData.ScaleY   = SCALE10;                  //スケールY
    SpData.Rotate   = ROTATE000;                //回転角
    SpData.Reverse  = NOREVERS;                 //反転コード
    DrawSprite( &SpData );                      //スプライト描画

    //----背景
    SpData.No       = MAZE_CHAR_EVENT_BG_00;    //インデックス番号
    SpData.PosX     = 0;                        //X位置
    SpData.PosY     = 0;                        //Y位置
    SpData.PosZ     = PRIORITY_MAZE_EVENT_BG;   //優先順位
    SpData.ScaleX   = SCALE10;                  //スケールX
    SpData.ScaleY   = SCALE10;                  //スケールY
    SpData.Rotate   = ROTATE000;                //回転角
    SpData.Reverse  = NOREVERS;                 //反転コード
    DrawSprite( &SpData );                      //スプライト描画

    SpData.No       = MAZE_CHAR_EVENT_BG_01;    //インデックス番号
    SpData.PosX     = 256;                      //X位置
    SpData.PosY     = 0;                        //Y位置
    SpData.PosZ     = PRIORITY_MAZE_EVENT_BG;   //優先順位
    SpData.ScaleX   = SCALE10;                  //スケールX
    SpData.ScaleY   = SCALE10;                  //スケールY
    SpData.Rotate   = ROTATE000;                //回転角
    SpData.Reverse  = NOREVERS;                 //反転コード
    DrawSprite( &SpData );                      //スプライト描画
}


//-----------------------------------------------------------------------------
//  関数名  :EventBakuhatsu
//
//  work    :イベント爆発
//  in      :なし
//  out     :なし
//  note    :なし
//-----------------------------------------------------------------------------
static void EventBakuhatsu(void)
{

    static MAZE_SPRITE_DATA BakuhatsuAnmTable[]=
    {
        {   MAZE_CHAR_EVENT_BAKU_SMALL,     108,    78  },
        {   MAZE_CHAR_EVENT_BAKU_BIG_00,    6,      21  },
        {   MAZE_CHAR_EVENT_BAKU_BIG_00,    6,      21  },
        {   MAZE_CHAR_EVENT_BAKU_BIG_00,    6,      21  },
        {   MAZE_CHAR_EVENT_BAKU_BIG_00,    6,      21  },
        {   MAZE_CHAR_EVENT_BAKU_BIG_00,    6,      21  },
        {   MAZE_CHAR_EVENT_BAKU_BIG_00,    6,      21  },
        {   MAZE_CHAR_EVENT_BAKU_BIG_00,    6,      21  },
        {   MAZE_CHAR_EVENT_BAKU_BIG_00,    6,      21  },
        {   MAZE_CHAR_EVENT_BAKU_BIG_00,    6,      21  },
        {   MAZE_CHAR_EVENT_BAKU_BIG_00,    6,      21  },
        {   MAZE_CHAR_EVENT_BAKU_BIG_00,    6,      21  },
        {   MAZE_CHAR_EVENT_BAKU_BIG_00,    6,      21  },
        {   MAZE_CHAR_EVENT_BAKU_BIG_00,    6,      21  },
        {   MAZE_CHAR_EVENT_BAKU_BIG_00,    6,      21  },
    };

    SPRITE_DATA SpData;

    if(MGameMgr.Event.BakuhatsuDrawFlag==1)
    {
        if(++MGameMgr.Event.BakuhatsuAnmWaitTime > MAZE_GAME_EVENT_BAKUHATSAU_ANM_WAIT_TIME)
        {
            MGameMgr.Event.BakuhatsuAnmWaitTime=0;
            MGameMgr.Event.BakuhatsuAnmIndex++;
            if(MGameMgr.Event.BakuhatsuAnmIndex>4){
                MGameMgr.Event.BakuhatsuAnmIndex=4;
                MGameMgr.Event.BakuhatsuDrawFlag=0;
            }
        }
        
        //----爆発
        SpData.No       = BakuhatsuAnmTable[MGameMgr.Event.BakuhatsuAnmIndex].No;   //インデックス番号
        SpData.PosX     = BakuhatsuAnmTable[MGameMgr.Event.BakuhatsuAnmIndex].Ofx;  //X位置
        SpData.PosY     = BakuhatsuAnmTable[MGameMgr.Event.BakuhatsuAnmIndex].Ofy;  //Y位置
        SpData.PosZ     = PRIORITY_MAZE_EVENT_BG-12;                //優先順位
        SpData.ScaleX   = SCALE10;                                  //スケールX
        SpData.ScaleY   = SCALE10;                                  //スケールY
        SpData.Rotate   = ROTATE000;                                //回転角
        SpData.Reverse  = NOREVERS;                                 //反転コード
        DrawSprite( &SpData );                                      //スプライト描画

        if( (MGameMgr.Event.BakuhatsuAnmIndex>=1) && (MGameMgr.Event.BakuhatsuAnmIndex<=14) )
        {
            SpData.No       = MAZE_CHAR_EVENT_BAKU_BIG_01;  //インデックス番号
            SpData.PosX     = 262;                          //X位置
            SpData.PosY     = 21;                           //Y位置
            SpData.PosZ     = PRIORITY_MAZE_EVENT_BG-12;    //優先順位
            SpData.ScaleX   = SCALE10;                      //スケールX
            SpData.ScaleY   = SCALE10;                      //スケールY
            SpData.Rotate   = ROTATE000;                    //回転角
            SpData.Reverse  = NOREVERS;                     //反転コード
            DrawSprite( &SpData );                          //スプライト描画
        }
    }
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
        MAZE_CHAR_EVENT_SELECT_CONTINUE_BUPE_00,
        MAZE_CHAR_EVENT_SELECT_CONTINUE_BUPE_01,
    };

    static int MaruBatuTable[]={
        MAZE_CHAR_EVENT_SELECT_CONTINUE_YES_LIGHT,  MAZE_CHAR_EVENT_SELECT_CONTINUE_NO_DARK,
        MAZE_CHAR_EVENT_SELECT_CONTINUE_YES_DARK,   MAZE_CHAR_EVENT_SELECT_CONTINUE_NO_LIGHT,
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
            MGameMgr.SelectContinue.Val^=1;
            //[♪] レバー音
            ssPlaySe(BUTONSE_LEVER);
        }
    }


    //はい・いいえ
    SpData.No       = MaruBatuTable[MGameMgr.SelectContinue.Val*2];     //インデックス番号
    SpData.PosX     = 68+72;                                            //X位置
    SpData.PosY     = 73+57;                                            //Y位置
    SpData.PosZ     = PRIORITY_MAZE_EVENT_MENU-2;                           //優先順位
    SpData.ScaleX   = SCALE10;                                          //スケールX
    SpData.ScaleY   = SCALE10;                                          //スケールY
    SpData.Rotate   = ROTATE000;                                        //回転角
    SpData.Reverse  = NOREVERS;                                         //反転コード
    DrawSprite( &SpData );                                              //スプライト描画

    SpData.No       = MaruBatuTable[MGameMgr.SelectContinue.Val*2+1];   //インデックス番号
    SpData.PosX     = 68+126;                                           //X位置
    SpData.PosY     = 73+57;                                            //Y位置
    SpData.PosZ     = PRIORITY_MAZE_EVENT_MENU-2;                           //優先順位
    SpData.ScaleX   = SCALE10;                                          //スケールX
    SpData.ScaleY   = SCALE10;                                          //スケールY
    SpData.Rotate   = ROTATE000;                                        //回転角
    SpData.Reverse  = NOREVERS;                                         //反転コード
    DrawSprite( &SpData );                                              //スプライト描画

    //プレート文字
    switch(MGameMgr.SelectContinue.Type)
    {
        case SELECT_RETRY_H:
            SpData.No       = MAZE_CHAR_EVENT_SELECT_CONTINUE_RETRY_H;  //インデックス番号
            SpData.PosX     = 68+20;                                    //X位置
            SpData.PosY     = 73+20;                                    //Y位置
            SpData.PosZ     = PRIORITY_MAZE_EVENT_MENU-2;                   //優先順位
            SpData.ScaleX   = SCALE10;                                  //スケールX
            SpData.ScaleY   = SCALE10;                                  //スケールY
            SpData.Rotate   = ROTATE000;                                //回転角
            SpData.Reverse  = NOREVERS;                                 //反転コード
            DrawSprite( &SpData );                                      //スプライト描画
            break;
        case SELECT_END_H:
            SpData.No       = MAZE_CHAR_EVENT_SELECT_CONTINUE_END_H;    //インデックス番号
            SpData.PosX     = 68+20;                                    //X位置
            SpData.PosY     = 73+20;                                    //Y位置
            SpData.PosZ     = PRIORITY_MAZE_EVENT_MENU-2;                   //優先順位
            SpData.ScaleX   = SCALE10;                                  //スケールX
            SpData.ScaleY   = SCALE10;                                  //スケールY
            SpData.Rotate   = ROTATE000;                                //回転角
            SpData.Reverse  = NOREVERS;                                 //反転コード
            DrawSprite( &SpData );                                      //スプライト描画
            break;
        case SELECT_CONTINUE_H:
            SpData.No       = MAZE_CHAR_EVENT_SELECT_CONTINUE_CONTINUE_H;//インデックス番号
            SpData.PosX     = 68+20;                                    //X位置
            SpData.PosY     = 73+20;                                    //Y位置
            SpData.PosZ     = PRIORITY_MAZE_EVENT_MENU-2;                   //優先順位
            SpData.ScaleX   = SCALE10;                                  //スケールX
            SpData.ScaleY   = SCALE10;                                  //スケールY
            SpData.Rotate   = ROTATE000;                                //回転角
            SpData.Reverse  = NOREVERS;                                 //反転コード
            DrawSprite( &SpData );                                      //スプライト描画
            break;
        default:
    }

    //ブーぺ
    if(++MGameMgr.SelectContinue.Wt>SELECT_LEVEL_PUPE_ANM_TIME){
        MGameMgr.SelectContinue.No^=1;
        MGameMgr.SelectContinue.Wt=0;
    }
    SpData.No       = BupeAnmTable[MGameMgr.SelectContinue.No]; //インデックス番号
    SpData.PosX     = 68+12;                                    //X位置
    SpData.PosY     = 73+34;                                    //Y位置
    SpData.PosZ     = PRIORITY_MAZE_EVENT_MENU-10;                  //優先順位
    SpData.ScaleX   = SCALE10;                                  //スケールX
    SpData.ScaleY   = SCALE10;                                  //スケールY
    SpData.Rotate   = ROTATE000;                                //回転角
    SpData.Reverse  = NOREVERS;                                 //反転コード
    DrawSprite( &SpData );                                      //スプライト描画

    //プレート
    SpData.No       = MAZE_CHAR_EVENT_SELECT_CONTINUE_PLATE;    //インデックス番号
    SpData.PosX     = 68;                                       //X位置
    SpData.PosY     = 73;                                       //Y位置
    SpData.PosZ     = PRIORITY_MAZE_EVENT_MENU;                     //優先順位
    SpData.ScaleX   = SCALE10;                                  //スケールX
    SpData.ScaleY   = SCALE10;                                  //スケールY
    SpData.Rotate   = ROTATE000;                                //回転角
    SpData.Reverse  = NOREVERS;                                 //反転コード
    DrawSprite( &SpData );                                      //スプライト描画

    //えらぶ
    SpData.No       = MAZE_CHAR_EVENT_SELECT_CONTINUE_ERABU;    //インデックス番号
    SpData.PosX     = (320-130)/2;                              //X位置
    SpData.PosY     = 206;                                      //Y位置
    SpData.PosZ     = PRIORITY_MAZE_EVENT_MENU-1;                   //優先順位
    SpData.ScaleX   = SCALE10;                                  //スケールX
    SpData.ScaleY   = SCALE10;                                  //スケールY
    SpData.Rotate   = ROTATE000;                                //回転角
    SpData.Reverse  = NOREVERS;                                 //反転コード
    DrawSprite( &SpData );                                      //スプライト描画

    //けってい
    SpData.No       = MAZE_CHAR_EVENT_SELECT_CONTINUE_KETEI;    //インデックス番号
    SpData.PosX     = (320-130)/2+78;                           //X位置
    SpData.PosY     = 206;                                      //Y位置
    SpData.PosZ     = PRIORITY_MAZE_EVENT_MENU-1;                   //優先順位
    SpData.ScaleX   = SCALE10;                                  //スケールX
    SpData.ScaleY   = SCALE10;                                  //スケールY
    SpData.Rotate   = ROTATE000;                                //回転角
    SpData.Reverse  = NOREVERS;                                 //反転コード
    DrawSprite( &SpData );                                      //スプライト描画

    return o_ret;
}


//-----------------------------------------------------------------------------
//  関数名  :GetDirectKumaToGunGun
//
//  work    :クマからみたグングンの方向
//  in      :なし
//  out     :方向
//  note    :なし
//-----------------------------------------------------------------------------
static int GetDirectKumaToGunGun(void)
{
    int dx,dy;

    dx = MGameMgr.GunGun.Px - MGameMgr.Kuma.Px;
    dy = MGameMgr.GunGun.Py - MGameMgr.Kuma.Py;

    if(dx>0)
    {//----右
        return DIR_RIGHT;
    }else
    if(dx<0)
    {//----左
        return DIR_LEFT;
    }else
    {//----上下
        if(dy>=0)
        {//----下
            return DIR_DOWN;
        }else
        {//----上
            return DIR_UP;
        }
    }
}


//-----------------------------------------------------------------------------
//  関数名  :SearchGunGun
//
//  work    :クマがグングンをサーチ
//  in      :int*       ip_dir
//  out     :TRUE       道発見
//          :FALSE      道見つからず
//  note    :なし
//-----------------------------------------------------------------------------
static int SearchGunGun(int* ip_dir)
{
#ifndef __DEBUG_MAZE__
    int wSx,wSy;
#endif
    int dir;


    if(MGameMgr.Kuma.LastThinkMode==THINK_MODE_SEARCH)
    {//----前回の思考モードが探索の場合は前回のデータを続けて使用する
        
        //---前回のデータより移動方向を取得、出現物よりこのタスクが優先が高いのでチェックはしない
        wSx = MGameMgr.VisitRoad[MGameMgr.VisitIndex].Px - MGameMgr.Kuma.Px;
        wSy = MGameMgr.VisitRoad[MGameMgr.VisitIndex].Py - MGameMgr.Kuma.Py;
        --MGameMgr.VisitIndex;

        
        if(MGameMgr.VisitIndex<=1)
        {//----再探索
            //----初期化
            MGameMgr.VisitSuccess   = 0;
            MGameMgr.VisitIndex     = 0;
            memset( MGameMgr.WorkMap.Data,  0,  (MAZE_GAME_SQUARE_H_NUM+2)*(MAZE_GAME_SQUARE_W_NUM+2));
            
            //----マップをコピー
            CopyGameMapToWorkMap();
            
            //----探索
            dir=GetDirectKumaToGunGun();
            switch(dir){
                case DIR_UP:
                    VisitUp(MGameMgr.Kuma.Px,MGameMgr.Kuma.Py);
                    break;
                case DIR_DOWN:
                    VisitDown(MGameMgr.Kuma.Px,MGameMgr.Kuma.Py);
                    break;
                case DIR_LEFT:
                    VisitLeft(MGameMgr.Kuma.Px,MGameMgr.Kuma.Py);
                    break;
                case DIR_RIGHT:
                    VisitRight(MGameMgr.Kuma.Px,MGameMgr.Kuma.Py);
                    break;
                default:
            }
            
            if(MGameMgr.VisitSuccess)
            {//----探索成功
                //---next pos
                MGameMgr.VisitIndex-=2;
                wSx = MGameMgr.VisitRoad[MGameMgr.VisitIndex].Px - MGameMgr.Kuma.Px;
                wSy = MGameMgr.VisitRoad[MGameMgr.VisitIndex].Py - MGameMgr.Kuma.Py;
                
                if(wSx>0){
                    *ip_dir=DIR_RIGHT;
                }else
                if(wSx<0){
                    *ip_dir=DIR_LEFT;
                }else{
                    if(wSy>0){
                        *ip_dir=DIR_DOWN;
                    }else
                    if(wSy<0){
                        *ip_dir=DIR_UP;
                    }else{
                        *ip_dir=DIR_NOTHING;
                        return FALSE;
                    }
                }
                
                return TRUE;
            }else
            {//----探索失敗
                //----
                *ip_dir=DIR_NOTHING;
                return FALSE;
            }
        }else{
            if(wSx>0){
                *ip_dir=DIR_RIGHT;
            }else
            if(wSx<0){
                *ip_dir=DIR_LEFT;
            }else{
                if(wSy>0){
                    *ip_dir=DIR_DOWN;
                }else
                if(wSy<0){
                    *ip_dir=DIR_UP;
                }else{
                    *ip_dir=DIR_NOTHING;
                    return FALSE;
                }
            }
        }
    }else
    {
        //----初期化
        MGameMgr.VisitSuccess   = 0;
        MGameMgr.VisitIndex     = 0;
        memset( MGameMgr.WorkMap.Data,  0,  (MAZE_GAME_SQUARE_H_NUM+2)*(MAZE_GAME_SQUARE_W_NUM+2));
        
        //----マップをコピー
        CopyGameMapToWorkMap();
        
        //----探索
        dir=GetDirectKumaToGunGun();
        switch(dir){
            case DIR_UP:
                VisitUp(MGameMgr.Kuma.Px,MGameMgr.Kuma.Py);
                break;
            case DIR_DOWN:
                VisitDown(MGameMgr.Kuma.Px,MGameMgr.Kuma.Py);
                break;
            case DIR_LEFT:
                VisitLeft(MGameMgr.Kuma.Px,MGameMgr.Kuma.Py);
                break;
            case DIR_RIGHT:
                VisitRight(MGameMgr.Kuma.Px,MGameMgr.Kuma.Py);
                break;
            default:
        }
        
        if(MGameMgr.VisitSuccess)
        {//----探索成功
            //---next pos
            MGameMgr.VisitIndex-=2;
            wSx = MGameMgr.VisitRoad[MGameMgr.VisitIndex].Px - MGameMgr.Kuma.Px;
            wSy = MGameMgr.VisitRoad[MGameMgr.VisitIndex].Py - MGameMgr.Kuma.Py;
            
            if(wSx>0){
                *ip_dir=DIR_RIGHT;
            }else
        if(wSx<0){
                *ip_dir=DIR_LEFT;
            }else{
                if(wSy>0){
                    *ip_dir=DIR_DOWN;
                }else
                if(wSy<0){
                    *ip_dir=DIR_UP;
                }else{
                    *ip_dir=DIR_NOTHING;
                    return FALSE;
                }
            }
            
            return TRUE;
        }else
        {//----探索失敗
            //----
            *ip_dir=DIR_NOTHING;
            return FALSE;
        }
    }
}


//-----------------------------------------------------------------------------
//  関数名  :VisitUp
//
//  work    :探索
//  in      :位置Ｘ
//          :位置Ｙ
//  out     :なし
//  note    :なし
//-----------------------------------------------------------------------------
static void VisitUp(int x,int y)
{
    //----通過地点に0を置く
    MGameMgr.WorkMap.Data[y][x] = 0;

    if( (x==MGameMgr.GunGun.Px) && (y==MGameMgr.GunGun.Py) )
    {//----ゴールに到達
        MGameMgr.VisitSuccess = 1;
    }

    //----ゴールに到達していない場合の処理
    if(!MGameMgr.VisitSuccess && (MGameMgr.WorkMap.Data[y-1][x  ]==MAZE_MAP_CHAR_NONE)) VisitUp(x,   y-1 ); //上が開いている場合
    if(!MGameMgr.VisitSuccess && (MGameMgr.WorkMap.Data[y  ][x+1]==MAZE_MAP_CHAR_NONE)) VisitUp(x+1, y   ); //右が開いている場合
    if(!MGameMgr.VisitSuccess && (MGameMgr.WorkMap.Data[y+1][x  ]==MAZE_MAP_CHAR_NONE)) VisitUp(x,   y+1 ); //下が開いている場合
    if(!MGameMgr.VisitSuccess && (MGameMgr.WorkMap.Data[y  ][x-1]==MAZE_MAP_CHAR_NONE)) VisitUp(x-1, y   ); //左が開いている場合

    if(MGameMgr.VisitSuccess)
    {//----戻り
        MGameMgr.VisitRoad[MGameMgr.VisitIndex].Px = x;
        MGameMgr.VisitRoad[MGameMgr.VisitIndex].Py = y;
        MGameMgr.VisitIndex++;
    } 
}


//-----------------------------------------------------------------------------
//  関数名  :VisitDown
//
//  work    :探索
//  in      :位置Ｘ
//          :位置Ｙ
//  out     :なし
//  note    :なし
//-----------------------------------------------------------------------------
static void VisitDown(int x,int y)
{
    //----通過地点に0を置く
    MGameMgr.WorkMap.Data[y][x] = 0;

    if( (x==MGameMgr.GunGun.Px) && (y==MGameMgr.GunGun.Py) )
    {//----ゴールに到達
        MGameMgr.VisitSuccess = 1;
    }

    //----ゴールに到達していない場合の処理
    if(!MGameMgr.VisitSuccess && (MGameMgr.WorkMap.Data[y+1][x  ]==MAZE_MAP_CHAR_NONE)) VisitDown(x,   y+1 );   //下が開いている場合
    if(!MGameMgr.VisitSuccess && (MGameMgr.WorkMap.Data[y  ][x-1]==MAZE_MAP_CHAR_NONE)) VisitDown(x-1, y   );   //左が開いている場合
    if(!MGameMgr.VisitSuccess && (MGameMgr.WorkMap.Data[y-1][x  ]==MAZE_MAP_CHAR_NONE)) VisitDown(x,   y-1 );   //上が開いている場合
    if(!MGameMgr.VisitSuccess && (MGameMgr.WorkMap.Data[y  ][x+1]==MAZE_MAP_CHAR_NONE)) VisitDown(x+1, y   );   //右が開いている場合

    if(MGameMgr.VisitSuccess)
    {//----戻り
        MGameMgr.VisitRoad[MGameMgr.VisitIndex].Px = x;
        MGameMgr.VisitRoad[MGameMgr.VisitIndex].Py = y;
        MGameMgr.VisitIndex++;
    } 
}


//-----------------------------------------------------------------------------
//  関数名  :VisitLeft
//
//  work    :探索
//  in      :位置Ｘ
//          :位置Ｙ
//  out     :なし
//  note    :なし
//-----------------------------------------------------------------------------
static void VisitLeft(int x,int y)
{
    //----通過地点に0を置く
    MGameMgr.WorkMap.Data[y][x] = 0;

    if( (x==MGameMgr.GunGun.Px) && (y==MGameMgr.GunGun.Py) )
    {//----ゴールに到達
        MGameMgr.VisitSuccess = 1;
    }

    //----ゴールに到達していない場合の処理
    if(!MGameMgr.VisitSuccess && (MGameMgr.WorkMap.Data[y-1][x  ]==MAZE_MAP_CHAR_NONE)) VisitLeft(x,   y-1 );   //上が開いている場合
    if(!MGameMgr.VisitSuccess && (MGameMgr.WorkMap.Data[y  ][x-1]==MAZE_MAP_CHAR_NONE)) VisitLeft(x-1, y   );   //左が開いている場合
    if(!MGameMgr.VisitSuccess && (MGameMgr.WorkMap.Data[y  ][x+1]==MAZE_MAP_CHAR_NONE)) VisitLeft(x+1, y   );   //右が開いている場合
    if(!MGameMgr.VisitSuccess && (MGameMgr.WorkMap.Data[y+1][x  ]==MAZE_MAP_CHAR_NONE)) VisitLeft(x,   y+1 );   //下が開いている場合

    if(MGameMgr.VisitSuccess)
    {//----戻り
        MGameMgr.VisitRoad[MGameMgr.VisitIndex].Px = x;
        MGameMgr.VisitRoad[MGameMgr.VisitIndex].Py = y;
        MGameMgr.VisitIndex++;
    } 
}


//-----------------------------------------------------------------------------
//  関数名  :VisitRight
//
//  work    :探索
//  in      :位置Ｘ
//          :位置Ｙ
//  out     :なし
//  note    :なし
//-----------------------------------------------------------------------------
static void VisitRight(int x,int y)
{
    //----通過地点に0を置く
    MGameMgr.WorkMap.Data[y][x] = 0;

    if( (x==MGameMgr.GunGun.Px) && (y==MGameMgr.GunGun.Py) )
    {//----ゴールに到達
        MGameMgr.VisitSuccess = 1;
    }

    //----ゴールに到達していない場合の処理
    if(!MGameMgr.VisitSuccess && (MGameMgr.WorkMap.Data[y  ][x+1]==MAZE_MAP_CHAR_NONE)) VisitRight(x+1, y   );  //右が開いている場合
    if(!MGameMgr.VisitSuccess && (MGameMgr.WorkMap.Data[y+1][x  ]==MAZE_MAP_CHAR_NONE)) VisitRight(x,   y+1 );  //下が開いている場合
    if(!MGameMgr.VisitSuccess && (MGameMgr.WorkMap.Data[y  ][x-1]==MAZE_MAP_CHAR_NONE)) VisitRight(x-1, y   );  //左が開いている場合
    if(!MGameMgr.VisitSuccess && (MGameMgr.WorkMap.Data[y-1][x  ]==MAZE_MAP_CHAR_NONE)) VisitRight(x,   y-1 );  //上が開いている場合

    if(MGameMgr.VisitSuccess)
    {//----戻り
        MGameMgr.VisitRoad[MGameMgr.VisitIndex].Px = x;
        MGameMgr.VisitRoad[MGameMgr.VisitIndex].Py = y;
        MGameMgr.VisitIndex++;
    } 
}



//-----------------------------------------------------------------------------
//  関数名  :DrawSearchRoad
//
//  work    :探索結果を表示
//  in      :int i_num                          表示数
//  out     :なし
//  note    :なし
//-----------------------------------------------------------------------------
static void DrawSearchRoad(int i_num)
{
    SPRITE_DATA SpData;
    int i;

    for(i=0;i<i_num;i++)
    {
        //----描画
        SpData.No       = MAZE_CHAR_GAME_GUNGUN_MARK;   //インデックス番号
        SpData.PosX     = MAZE_GAME_MAP_LEFT_X + (MGameMgr.VisitRoad[i].Px-1)*MAZE_GAME_SQUARE_W + 4;   //X位置
        SpData.PosY     = MAZE_GAME_MAP_LEFT_Y + (MGameMgr.VisitRoad[i].Py-1)*MAZE_GAME_SQUARE_H + 2;   //Y位置
        SpData.PosZ     = 10;                           //優先順位
        SpData.ScaleX   = SCALE10;                      //スケールX
        SpData.ScaleY   = SCALE10;                      //スケールY
        SpData.Rotate   = ROTATE000;                    //回転角
        SpData.Reverse  = NOREVERS;                     //反転コード
        DrawSprite( &SpData );                          //スプライト描画
        
//      FntPrint("VROAD=[%2d][%2d-%2d]\n",i,MGameMgr.VisitRoad[i].Px,MGameMgr.VisitRoad[i].Py);
    }
}



#ifdef __DEBUG_MAZE__

//-----------------------------------------------------------------------------
//  関数名  :DebugGameSpriteTask
//
//  work    :ゲームスプライトデバッグ
//  in      :TASK*      タスクポインタ
//  out     :TRUE
//          :FALSE
//  note    :なし
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
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //----MODE NEXT
            ip_task->mode = TASK_MODE_MAIN;

            //----texture read sram -> vram
            if((file_read(MazeGameTextureFile[0].fn,LoadAddress)) == -1)
            {//read error
                return FALSE;
            }

            //----texture init
            TexInit( MAZE_GAME_TIM_NUM, &MazeGameTextureImage[MAZE_GAME_TIM_POS] );
            TimImgData = MazeGameTextureImage;

            //----開放
            ReleaseSprite();

            //----ゲーム用スプライト登録
            EntrySprite( MazeGameSpriteData );

            //----初期化
            SpIndex     = 0;
            SpEntryNum  = GetEntrySpriteNum();
            Counter     = 0;
            FlushFlag   = 0;

            //フェードイン
            GameMgr.FadeFlag    = FadeIn;
            
            break;
        //----------------------------------------------------------------タスクメイン
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

            //----描画
            SpData.No       = SpIndex;                                          //インデックス番号
            SpData.PosX     = (320 - MazeGameSpriteData[SpIndex].Width)  / 2;   //X位置
            SpData.PosY     = (240 - MazeGameSpriteData[SpIndex].Height) / 2;   //Y位置
            SpData.PosZ     = 10;                                               //優先順位
            SpData.ScaleX   = SCALE10;                                          //スケールX
            SpData.ScaleY   = SCALE10;                                          //スケールY
            SpData.Rotate   = ROTATE000;                                        //回転角
            SpData.Reverse  = NOREVERS;                                         //反転コード
            DrawSprite( &SpData );                                              //スプライト描画

            //----テクスチャ情報
            FntPrint("-Maze GameSprite Check-\n");
            FntPrint("SNO=%d/%d\n", SpIndex,SpEntryNum-1 );
            FntPrint("OfX=%d\n",    MazeGameSpriteData[SpIndex].OffSetX );      //TIMの中のスプライト左上開始X位置
            FntPrint("OfY=%d\n",    MazeGameSpriteData[SpIndex].OffSetY );      //TIMの中のスプライト左上開始Y位置
            FntPrint("W__=%d\n",    MazeGameSpriteData[SpIndex].Width   );      //TIMの中のテクスチャの幅
            FntPrint("H__=%d\n",    MazeGameSpriteData[SpIndex].Height  );      //TIMの中のテクスチャの高さ
            FntPrint("PNO=%d\n",    MazeGameSpriteData[SpIndex].PaletteNo );    //TIMの中のテクスチャパレット番号
            FntPrint("CNT=%d\n",    ++Counter );

            break;
        //----------------------------------------------------------------タスク終了
        case TASK_MODE_EXIT:
            //----開放
            ReleaseSprite();
            
            //----自分を削除
            ExitTask(ip_task->id);
            break;
        default:
            break;
    }
}


//-----------------------------------------------------------------------------
//  関数名  :DebugEventSpriteTask
//
//  work    :イベントスプライトデバッグ
//  in      :TASK*      タスクポインタ
//  out     :TRUE
//          :FALSE
//  note    :なし
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
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            //----MODE NEXT
            ip_task->mode = TASK_MODE_MAIN;

            //----texture read sram -> vram
            if((file_read(MazeEventTextureFile[0].fn,LoadAddress)) == -1)
            {//read error
                return FALSE;
            }

            //----texture init
            TexInit( MAZE_EVENT_TIM_NUM, &MazeEventTextureImage[MAZE_EVENT_TIM_POS] );
            TimImgData = MazeEventTextureImage;

            //----開放
            ReleaseSprite();

            //----ゲーム用スプライト登録
            EntrySprite( MazeEventSpriteData );

            //----初期化
            SpIndex     = 0;
            SpEntryNum  = GetEntrySpriteNum();
            Counter     = 0;
            FlushFlag   = 0;

            //フェードイン
            GameMgr.FadeFlag    = FadeIn;

            break;
        //----------------------------------------------------------------タスクメイン
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

            //----描画
            SpData.No       = SpIndex;                                          //インデックス番号
            SpData.PosX     = (320 - MazeEventSpriteData[SpIndex].Width)  / 2;  //X位置
            SpData.PosY     = (240 - MazeEventSpriteData[SpIndex].Height) / 2;  //Y位置
            SpData.PosZ     = 10;                                               //優先順位
            SpData.ScaleX   = SCALE10;                                          //スケールX
            SpData.ScaleY   = SCALE10;                                          //スケールY
            SpData.Rotate   = ROTATE000;                                        //回転角
            SpData.Reverse  = NOREVERS;                                         //反転コード
            DrawSprite( &SpData );                                              //スプライト描画

            //----テクスチャ情報
            FntPrint("-Maze EventSprite Check-\n");
            FntPrint("SNO=%d/%d\n", SpIndex,SpEntryNum-1 );
            FntPrint("OfX=%d\n",    MazeEventSpriteData[SpIndex].OffSetX );     //TIMの中のスプライト左上開始X位置
            FntPrint("OfY=%d\n",    MazeEventSpriteData[SpIndex].OffSetY );     //TIMの中のスプライト左上開始Y位置
            FntPrint("W__=%d\n",    MazeEventSpriteData[SpIndex].Width   );     //TIMの中のテクスチャの幅
            FntPrint("H__=%d\n",    MazeEventSpriteData[SpIndex].Height  );     //TIMの中のテクスチャの高さ
            FntPrint("PNO=%d\n",    MazeEventSpriteData[SpIndex].PaletteNo );   //TIMの中のテクスチャパレット番号
            FntPrint("CNT=%d\n",    ++Counter );

            break;
        //----------------------------------------------------------------タスク終了
        case TASK_MODE_EXIT:
            //----開放
            ReleaseSprite();
            
            //----自分を削除
            ExitTask(ip_task->id);
            break;
        default:
            break;
    }
}

#endif

//-----------------------------------------------------------------------------
// end of MAZE.C
//-----------------------------------------------------------------------------