//-----------------------------------------------------------------------------
// AIR.C
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  include
//-----------------------------------------------------------------------------
#include "COMMON.H"
#include "KAZU.H"
#include "SPMGR.H"
#include "TASKMGR.H"
#include "AIR.H"
#include "SPCONT.H"
#include "SOUND.H"
//-----------------------------------------------------------------------------
//  define
//-----------------------------------------------------------------------------
//----debug sw「デバッグ時はコメントを外してください」
//  #define __DEBUG_AIR__
//  #define __DEBUG_ALL_QUESTION_AIR__


//----------------------------------------
//テクスチャー枚数と位置
#define AIR_GAME_TIM_POS                0+4
#define AIR_GAME_TIM_NUM                9
#define AIR_EVENT_TIM_POS               0+4
#define AIR_EVENT_TIM_NUM               24


//----------------------------------------------------------------------------- TIM位置
//---- ゲーム部
#define TIM_POS_AIR_GAME_BG_00              0+4     //背景１
#define TIM_POS_AIR_GAME_BG_01              1+4     //背景２
#define TIM_POS_AIR_GAME_GUN_00             2+4     //部品１
#define TIM_POS_AIR_GAME_GUN_01             3+4     //部品２
#define TIM_POS_AIR_GAME_GUN_02             4+4     //部品３
#define TIM_POS_AIR_GAME_ITEM               5+4     //アイテム
#define TIM_POS_AIR_GAME_OPANEL             6+4     //お願いパネル
#define TIM_POS_AIR_GAME_QUESTION           7+4     //問題と部品
#define TIM_POS_AIR_GAME_NEEDLE             8+4     //針


//---- イベント部
#define TIM_POS_AIR_EVENT_FONT              0       //選択処理テクスチャ
#define TIM_POS_AIR_EVENT_YORNO             1       //選択処理テクスチャ
#define TIM_POS_AIR_EVENT_EBG_00            0+4
#define TIM_POS_AIR_EVENT_EBG_01            1+4
#define TIM_POS_AIR_EVENT_EBG_02            2+4
#define TIM_POS_AIR_EVENT_EBG_03            3+4
#define TIM_POS_AIR_EVENT_EBG_04            4+4
#define TIM_POS_AIR_EVENT_EBG_05            5+4
#define TIM_POS_AIR_EVENT_EBG_06            6+4
#define TIM_POS_AIR_EVENT_EBG_07            7+4
#define TIM_POS_AIR_EVENT_EBG_08            8+4
#define TIM_POS_AIR_EVENT_EBG_09            9+4
#define TIM_POS_AIR_EVENT_EBG_10            10+4
#define TIM_POS_AIR_EVENT_EBG_11            11+4
#define TIM_POS_AIR_EVENT_EBG_12            12+4
#define TIM_POS_AIR_EVENT_EBG_13            13+4
#define TIM_POS_AIR_EVENT_EBG_14            14+4
#define TIM_POS_AIR_EVENT_EBG_15            15+4
#define TIM_POS_AIR_EVENT_ECHARA1           16+4
#define TIM_POS_AIR_EVENT_ECHARA2           17+4
#define TIM_POS_AIR_EVENT_ECHARA3           18+4
#define TIM_POS_AIR_EVENT_ECHARA4           19+4
#define TIM_POS_AIR_EVENT_ECHARA5           20+4
#define TIM_POS_AIR_EVENT_ECHARA6           21+4
#define TIM_POS_AIR_EVENT_ECHARA7           22+4
#define TIM_POS_AIR_EVENT_ECHARA8           23+4

//----------------------------------------------------------------------------- 
// ■キャラ番号
//----------------------------------------------------------------------------- 
//---- ゲーム部

//----------------------------------------------------------------------------- BG_00.TIM / 部品１
#define AIR_CHAR_GAME_BG_00                         0                   //背景１
//----------------------------------------------------------------------------- BG_01.TIM / 部品２
#define AIR_CHAR_GAME_BG_01                         1                   //背景2 
//----------------------------------------------------------------------------- GUN_00.TIM / 部品１
#define AIR_CHAR_GUNGUN_00                          2                   //標準横A
#define AIR_CHAR_GUNGUN_01                          3                   //標準横B
#define AIR_CHAR_GUNGUN_02                          4                   //正解A
#define AIR_CHAR_GUNGUN_03                          5                   //正解B
#define AIR_CHAR_GUNGUN_04                          6                   //ぐにゃぐにゃA
#define AIR_CHAR_GUNGUN_05                          7                   //ぐにゃぐにゃB
#define AIR_CHAR_GUNGUN_06                          8                   //下降
#define AIR_CHAR_GUNGUN_07                          9                   //上昇
#define AIR_CHAR_GUNGUN_08                          10                  //グングン飛行機・横（失敗）
#define AIR_CHAR_KUMA_00                            11                  //クマ  縦
#define AIR_CHAR_KUMA_01                            12                  //クマ  横
//----------------------------------------------------------------------------- GUN_01.TIM / 部品２
#define AIR_CHAR_MOUNTAIN_00                        13                  //背景の山
#define AIR_CHAR_MOUNTAIN_01                        14                  //上の画像に繋げて下さい
#define AIR_CHAR_FUUSEN_00                          15                  //風船１
#define AIR_CHAR_FUUSEN_01                          16                  //風船２
#define AIR_CHAR_FUUSEN_02                          17                  //風船３
#define AIR_CHAR_HAND_PA                            18                  //手・パー
#define AIR_CHAR_HAND_GU                            19                  //手・グー
#define AIR_CHAR_ARM                                20                  //伸びる手の棒
#define AIR_CHAR_CLOUD_LARGE                        21                  //雲・大
#define AIR_CHAR_CLOUD_MIDDLE                       22                  //雲・中
#define AIR_CHAR_CLOUD_SMALL                        23                  //雲・小
#define AIR_CHAR_SMOKE_LARGE                        24                  //煙・大
#define AIR_CHAR_SMOKE_MIDDLE                       25                  //煙・中
#define AIR_CHAR_SMOKE_SMALL                        26                  //煙・小
#define AIR_CHAR_QUESTION_PLATE_LEFT                27                  //問題プレート・左
#define AIR_CHAR_QUESTION_PLATE_CENTER              28                  //問題プレート・中央
#define AIR_CHAR_QUESTION_PLATE_RIGHT               29                  //問題プレート・右 
#define AIR_CHAR_MARU                               30                  //まる
#define AIR_CHAR_BATSU                              31                  //ばつ
#define AIR_CHAR_FUKURO                             32                  //フクロ
#define AIR_CHAR_ONNPU                              33                  //音符
#define AIR_CHAR_ASE                                34                  //汗
#define AIR_CHAR_CROW_00                            35                  //からすA
#define AIR_CHAR_CROW_01                            36                  //からすB
#define AIR_CHAR_CROW_02                            37                  //からすC
//----------------------------------------------------------------------------- GUN_02.TIM / 部品３
#define AIR_CHAR_LEVEL_SELECT_PLATE                 38                  //レベルプレート

//選択カーソル
#define AIR_CHAR_LEVEL_SELECT_CURSOR                39


#define AIR_CHAR_LEVEL_SELECT_BLOCK                 40                  //点滅ブロック
#define AIR_CHAR_LEVEL_SELECT_01                    41                  //セレクト１
#define AIR_CHAR_LEVEL_SELECT_02                    42                  //セレクト２
#define AIR_CHAR_LEVEL_SELECT_03                    43                  //セレクト３
#define AIR_CHAR_LEVEL_SELECT_04                    44                  //セレクト４
#define AIR_CHAR_LEVEL_SELECT_05                    45                  //セレクト５
#define AIR_CHAR_THUBDER_LARGE                      46                  //雷・大
#define AIR_CHAR_THUBDER_SMALL                      47                  //雷・小
#define AIR_CHAR_CRUSH_00                           48                  //激突A
#define AIR_CHAR_CRUSH_01                           49                  //激突B
//----------------------------------------------------------------------------- ITEM.TIM / アイテム
#define AIR_CHAR_ITEM_GUITAR                        50                  //ギター
#define AIR_CHAR_ITEM_DOLL                          51                  //人形  
#define AIR_CHAR_ITEM_JEWELRY                       52                  //宝石  
#define AIR_CHAR_ITEM_TRUMPET                       53                  //らっぱ
#define AIR_CHAR_ITEM_RIBBON                        54                  //リボン
#define AIR_CHAR_ITEM_RING                          55                  //指輪  
#define AIR_CHAR_ITEM_CROWN                         56                  //王冠  
#define AIR_CHAR_ITEM_JAR                           57                  //つぼ  
#define AIR_CHAR_ITEM_TRAIN                         58                  //汽車  
#define AIR_CHAR_ITEM_POSTCARD                      59                  //葉書  
#define AIR_CHAR_DUST_TSHIRT                        60                  //ボロTシャツ
#define AIR_CHAR_DUST_MIRROR                        61                  //ボロ手鏡
#define AIR_CHAR_DUST_KAN                           62                  //空き缶
#define AIR_CHAR_DUST_YAKAN                         63                  //ボロやかん
#define AIR_CHAR_DUST_APPLE                         64                  //ボロりんご
#define AIR_CHAR_DUST_SHOES                         65                  //ボロ靴
//----------------------------------------------------------------------------- OPANEL.TIM / お願いパネル
#define AIR_CHAR_HELP_PANEL                         66                  //助けてパネル      96,61
//---------------------------------------------------------------------------- QUESTION.TIM / 問題と部品
#define AIR_CHAR_QUESTION_TEXT_00                   67                  //はりはどこをさしていますか？
#define AIR_CHAR_QUESTION_TEXT_01                   68                  //いくつになりますか？  (60,30      数字の場所・前 / 88,29      数字の場所・後 )
#define AIR_CHAR_QUESTION_TEXT_02                   69                  //いくつですか？    (50,37      数字の場所・前/ 80,37       数字の場所・後)
#define AIR_CHAR_QUESTION_TEXT_03                   70                  //どちらがおおいですか？
#define AIR_CHAR_QUESTION_TEXT_04                   71                  //□にはいるかずはなんですか？
#define AIR_CHAR_QUESTION_TEXT_05                   72                  //＿じ＿＿なんぷん～？      
#define AIR_CHAR_PANEL_BLUE_BIG                     73                  //大・青
#define AIR_CHAR_PANEL_PINK_BIG                     74                  //大・ピンク
#define AIR_CHAR_PANEL_BLUE_SMALL                   75                  //小・青
#define AIR_CHAR_PANEL_PINK_SMALL                   76                  //小・ピンク
#define AIR_CHAR_WAKU_RED                           77                  //出題赤枠
#define AIR_CHAR_QA_NO_00                           78                  //0　出題、解答用数字
#define AIR_CHAR_QA_NO_01                           79                  //1　出題、解答用数字
#define AIR_CHAR_QA_NO_02                           80                  //2　出題、解答用数字
#define AIR_CHAR_QA_NO_03                           81                  //3　出題、解答用数字
#define AIR_CHAR_QA_NO_04                           82                  //4　出題、解答用数字
#define AIR_CHAR_QA_NO_05                           83                  //5　出題、解答用数字
#define AIR_CHAR_QA_NO_06                           84                  //6　出題、解答用数字
#define AIR_CHAR_QA_NO_07                           85                  //7　出題、解答用数字
#define AIR_CHAR_QA_NO_08                           86                  //8　出題、解答用数字
#define AIR_CHAR_QA_NO_09                           87                  //9　出題、解答用数字
#define AIR_CHAR_COUNTER_NO_01                      88                  //1　カウンター用数字
#define AIR_CHAR_COUNTER_NO_02                      89                  //2　カウンター用数字
#define AIR_CHAR_COUNTER_NO_03                      90                  //3　カウンター用数字
#define AIR_CHAR_COUNTER_NO_04                      91                  //4　カウンター用数字
#define AIR_CHAR_COUNTER_NO_05                      92                  //5　カウンター用数字
#define AIR_CHAR_COUNTER_NO_06                      93                  //6　カウンター用数字
#define AIR_CHAR_COUNTER_NO_07                      94                  //7　カウンター用数字
#define AIR_CHAR_COUNTER_NO_08                      95                  //8　カウンター用数字
#define AIR_CHAR_COUNTER_NO_09                      96                  //9　カウンター用数字
#define AIR_CHAR_COUNTER_NO_00                      97                  //0　カウンター用数字
#define AIR_CHAR_QNO_01                             98                  //1　ウィンドウ用問題数の数字
#define AIR_CHAR_QNO_02                             99                  //2　ウィンドウ用問題数の数字
#define AIR_CHAR_QNO_03                             100                 //3　ウィンドウ用問題数の数字
#define AIR_CHAR_QNO_04                             101                 //4　ウィンドウ用問題数の数字
#define AIR_CHAR_QNO_05                             102                 //5　ウィンドウ用問題数の数字
#define AIR_CHAR_QNO_06                             103                 //6　ウィンドウ用問題数の数字
#define AIR_CHAR_QNO_07                             104                 //7　ウィンドウ用問題数の数字
#define AIR_CHAR_QNO_08                             105                 //8　ウィンドウ用問題数の数字
#define AIR_CHAR_QNO_09                             106                 //9　ウィンドウ用問題数の数字
#define AIR_CHAR_QNO_10                             107                 //10　ウィンドウ用問題数の数字
#define AIR_CHAR_QUESTION_NO_01                     108                 //1　問題・数字の順番用
#define AIR_CHAR_QUESTION_NO_02                     109                 //2　問題・数字の順番用
#define AIR_CHAR_QUESTION_NO_03                     110                 //3　問題・数字の順番用
#define AIR_CHAR_QUESTION_NO_04                     111                 //4　問題・数字の順番用
#define AIR_CHAR_QUESTION_NO_05                     112                 //5　問題・数字の順番用
#define AIR_CHAR_QUESTION_NO_06                     113                 //6　問題・数字の順番用
#define AIR_CHAR_QUESTION_NO_07                     114                 //7　問題・数字の順番用
#define AIR_CHAR_QUESTION_NO_08                     115                 //8　問題・数字の順番用
#define AIR_CHAR_QUESTION_NO_09                     116                 //9　問題・数字の順番用
#define AIR_CHAR_QUESTION_NO_00                     117                 //0　問題・数字の順番用
#define AIR_CHAR_ONAZI_STR                          118                 //おなじ
#define AIR_CHAR_CLOCK_PANEL                        119                 //時計版
#define AIR_CHAR_CLOCK_TANSIN                       120                 //短針
#define AIR_CHAR_CLOCK_TYOUSIN                      121                 //長針
#define AIR_CHAR_BALL_ORANGE                        122                 //ボール・オレンジ
#define AIR_CHAR_MIKAN                              123                 //みかん
#define AIR_CHAR_BALL_RED                           124                 //ボール・赤
#define AIR_CHAR_APPLE                              125                 //りんご
//----------------------------------------------------------------------------- 緊急追加
#define AIR_CHAR_ARM_WPIXEL_01                      126                 //アーム1ドット
#define AIR_CHAR_ARM_WPIXEL_02                      127                 //アーム2ドット
#define AIR_CHAR_ARM_WPIXEL_03                      128                 //アーム3ドット
#define AIR_CHAR_ARM_WPIXEL_04                      129                 //アーム4ドット
#define AIR_CHAR_ARM_WPIXEL_05                      130                 //アーム5ドット
#define AIR_CHAR_ARM_WPIXEL_06                      131                 //アーム6ドット
#define AIR_CHAR_ARM_WPIXEL_07                      132                 //アーム7ドット
#define AIR_CHAR_ARM_WPIXEL_08                      133                 //アーム8ドット
#define AIR_CHAR_ARM_WPIXEL_09                      134                 //アーム9ドット
#define AIR_CHAR_ARM_WPIXEL_10                      135                 //アーム10ドット
//----------------------------------------------------------------------------- 緊急追加
#define AIR_CHAR_NEEDLE_SHORT_00                    136                 //短針00
#define AIR_CHAR_NEEDLE_SHORT_01                    137                 //短針01
#define AIR_CHAR_NEEDLE_SHORT_02                    138                 //短針02
#define AIR_CHAR_NEEDLE_SHORT_03                    139                 //短針03
#define AIR_CHAR_NEEDLE_SHORT_04                    140                 //短針04
#define AIR_CHAR_NEEDLE_SHORT_05                    141                 //短針05
#define AIR_CHAR_NEEDLE_SHORT_06                    142                 //短針06
#define AIR_CHAR_NEEDLE_SHORT_07                    143                 //短針07
#define AIR_CHAR_NEEDLE_SHORT_08                    144                 //短針08
#define AIR_CHAR_NEEDLE_SHORT_09                    145                 //短針09
#define AIR_CHAR_NEEDLE_SHORT_10                    146                 //短針10
#define AIR_CHAR_NEEDLE_SHORT_11                    147                 //短針11
#define AIR_CHAR_NEEDLE_SHORT_12                    148                 //短針12
#define AIR_CHAR_NEEDLE_SHORT_13                    149                 //短針13
#define AIR_CHAR_NEEDLE_SHORT_14                    150                 //短針14
#define AIR_CHAR_NEEDLE_SHORT_15                    151                 //短針15
#define AIR_CHAR_NEEDLE_SHORT_16                    152                 //短針16
#define AIR_CHAR_NEEDLE_SHORT_17                    153                 //短針17
#define AIR_CHAR_NEEDLE_SHORT_18                    154                 //短針18
#define AIR_CHAR_NEEDLE_SHORT_19                    155                 //短針19
#define AIR_CHAR_NEEDLE_SHORT_20                    156                 //短針20
#define AIR_CHAR_NEEDLE_SHORT_21                    157                 //短針21
#define AIR_CHAR_NEEDLE_SHORT_22                    158                 //短針22
#define AIR_CHAR_NEEDLE_SHORT_23                    159                 //短針23
#define AIR_CHAR_NEEDLE_SHORT_24                    160                 //短針24
#define AIR_CHAR_NEEDLE_SHORT_25                    161                 //短針25
#define AIR_CHAR_NEEDLE_SHORT_26                    162                 //短針26
#define AIR_CHAR_NEEDLE_SHORT_27                    163                 //短針27
#define AIR_CHAR_NEEDLE_SHORT_28                    164                 //短針28
#define AIR_CHAR_NEEDLE_SHORT_29                    165                 //短針29
#define AIR_CHAR_NEEDLE_SHORT_30                    166                 //短針30
#define AIR_CHAR_NEEDLE_SHORT_31                    167                 //短針31
#define AIR_CHAR_NEEDLE_SHORT_32                    168                 //短針32
#define AIR_CHAR_NEEDLE_SHORT_33                    169                 //短針33
#define AIR_CHAR_NEEDLE_SHORT_34                    170                 //短針34
#define AIR_CHAR_NEEDLE_SHORT_35                    171                 //短針35
#define AIR_CHAR_NEEDLE_SHORT_36                    172                 //短針36
#define AIR_CHAR_NEEDLE_SHORT_37                    173                 //短針37
#define AIR_CHAR_NEEDLE_SHORT_38                    174                 //短針38
#define AIR_CHAR_NEEDLE_SHORT_39                    175                 //短針39
#define AIR_CHAR_NEEDLE_SHORT_40                    176                 //短針40
#define AIR_CHAR_NEEDLE_SHORT_41                    177                 //短針41
#define AIR_CHAR_NEEDLE_SHORT_42                    178                 //短針42
#define AIR_CHAR_NEEDLE_SHORT_43                    179                 //短針43
#define AIR_CHAR_NEEDLE_SHORT_44                    180                 //短針44
#define AIR_CHAR_NEEDLE_SHORT_45                    181                 //短針45
#define AIR_CHAR_NEEDLE_SHORT_46                    182                 //短針46
#define AIR_CHAR_NEEDLE_SHORT_47                    183                 //短針47
#define AIR_CHAR_NEEDLE_LONG_00                     184                 //長針00
#define AIR_CHAR_NEEDLE_LONG_01                     185                 //長針01
#define AIR_CHAR_NEEDLE_LONG_02                     186                 //長針02
#define AIR_CHAR_NEEDLE_LONG_03                     187                 //長針03
#define AIR_CHAR_NEEDLE_LONG_04                     188                 //長針04
#define AIR_CHAR_NEEDLE_LONG_05                     189                 //長針05
#define AIR_CHAR_NEEDLE_LONG_06                     190                 //長針06
#define AIR_CHAR_NEEDLE_LONG_07                     191                 //長針07
#define AIR_CHAR_NEEDLE_LONG_08                     192                 //長針08
#define AIR_CHAR_NEEDLE_LONG_09                     193                 //長針09
#define AIR_CHAR_NEEDLE_LONG_10                     194                 //長針10
#define AIR_CHAR_NEEDLE_LONG_11                     195                 //長針11



//---- イベント部
//----------------------------------------------------------------------------- EBG_00.TIM  
#define AIR_CHAR_EVENT_BG_00                        0                   //
//----------------------------------------------------------------------------- EBG_01.TIM  
#define AIR_CHAR_EVENT_BG_01                        1                   //
//----------------------------------------------------------------------------- EBG_02.TIM  
#define AIR_CHAR_EVENT_BG_02                        2                   //
//----------------------------------------------------------------------------- EBG_03.TIM  
#define AIR_CHAR_EVENT_BG_03                        3                   //
//----------------------------------------------------------------------------- EBG_04.TIM  
#define AIR_CHAR_EVENT_BG_04                        4                   //
//----------------------------------------------------------------------------- EBG_05.TIM  
#define AIR_CHAR_EVENT_BG_05                        5                   //
//----------------------------------------------------------------------------- EBG_06.TIM  
#define AIR_CHAR_EVENT_BG_06                        6                   //
//----------------------------------------------------------------------------- EBG_07.TIM  
#define AIR_CHAR_EVENT_BG_07                        7                   //
//----------------------------------------------------------------------------- EBG_08.TIM  
#define AIR_CHAR_EVENT_BG_08                        8                   //
//----------------------------------------------------------------------------- EBG_09.TIM  
#define AIR_CHAR_EVENT_BG_09                        9                   //
//----------------------------------------------------------------------------- EBG_10.TIM  
#define AIR_CHAR_EVENT_BG_10                        10                  //
//----------------------------------------------------------------------------- EBG_11.TIM  
#define AIR_CHAR_EVENT_BG_11                        11                  //
//----------------------------------------------------------------------------- EBG_12.TIM  
#define AIR_CHAR_EVENT_BG_12                        12                  //
//----------------------------------------------------------------------------- EBG_13.TIM  
#define AIR_CHAR_EVENT_BG_13                        13                  //
//----------------------------------------------------------------------------- EBG_14.TIM  
#define AIR_CHAR_EVENT_BG_14                        14                  //
//----------------------------------------------------------------------------- EBG_15.TIM  
#define AIR_CHAR_EVENT_BG_15                        15                  //
//----------------------------------------------------------------------------- ECHARA1.TIM 
#define AIR_CHAR_EVENT_GUNGUN_00                    16                  //左手上げ
#define AIR_CHAR_EVENT_USAGI_00                     17                  //うさぎ
#define AIR_CHAR_EVENT_USAGI_01                     18                  //うさぎ
#define AIR_CHAR_EVENT_NEZUMI_00                    19                  //ねずみ
#define AIR_CHAR_EVENT_NEZUMI_01                    20                  //ねずみ
//----------------------------------------------------------------------------- ECHARA2.TIM 
#define AIR_CHAR_EVENT_GUNGUN_01                    21                  //照れ
#define AIR_CHAR_EVENT_GUNGUN_MOUSE_00              22                  //正面口
#define AIR_CHAR_EVENT_GUNGUN_MOUSE_01              23                  //正面口閉じ
#define AIR_CHAR_EVENT_GUNGUN_MOUSE_02              24                  //斜め口
#define AIR_CHAR_EVENT_GUNGUN_MOUSE_03              25                  //斜め口閉じ
#define AIR_CHAR_EVENT_KAYORINU_00                  26                  //カヨリーヌ
#define AIR_CHAR_EVENT_KAYORINU_01                  27                  //カヨリーヌ
//----------------------------------------------------------------------------- ECHARA3.TIM 
#define AIR_CHAR_EVENT_GUNGUN_02                    28                  //腕組み
#define AIR_CHAR_EVENT_RISU_00                      29                  //リス
#define AIR_CHAR_EVENT_RISU_01                      30                  //リス
//----------------------------------------------------------------------------- ECHARA4.TIM 
#define AIR_CHAR_EVENT_GUNGUN_03                    31                  //腕組み
//----------------------------------------------------------------------------- ECHARA5.TIM 
#define AIR_CHAR_EVENT_GUNGUN_04                    32                  //にっこり
//----------------------------------------------------------------------------- ECHARA6.TIM 
#define AIR_CHAR_EVENT_GUNGUN_05                    33                  //左手ガッツ
//----------------------------------------------------------------------------- ECHARA7.TIM 
#define AIR_CHAR_EVENT_FOX_00                       34                  //きつね
#define AIR_CHAR_EVENT_FOX_01                       35                  //きつね
//----------------------------------------------------------------------------- ECHARA8.TIM 
#define AIR_CHAR_EVENT_BUTA_00                      36                  //ぶた
#define AIR_CHAR_EVENT_BUTA_01                      37                  //ぶた
//----------------------------------------------------------------------------- システムテクスチャ
#define AIR_CHAR_EVENT_SELECT_CONTINUE_PLATE        38                  //プレート
#define AIR_CHAR_EVENT_SELECT_CONTINUE_YES_DARK     39                  //非選択・はい
#define AIR_CHAR_EVENT_SELECT_CONTINUE_NO_DARK      40                  //非選択・いいえ
#define AIR_CHAR_EVENT_SELECT_CONTINUE_YES_LIGHT    41                  //選択・はい
#define AIR_CHAR_EVENT_SELECT_CONTINUE_NO_LIGHT     42                  //選択・いいえ
#define AIR_CHAR_EVENT_SELECT_CONTINUE_BUPE_00      43                  //プーぺ１
#define AIR_CHAR_EVENT_SELECT_CONTINUE_BUPE_01      44                  //プーぺ２
#define AIR_CHAR_EVENT_SELECT_CONTINUE_RETRY_H      45                  //もういちど
#define AIR_CHAR_EVENT_SELECT_CONTINUE_END_H        46                  //おわり
#define AIR_CHAR_EVENT_SELECT_CONTINUE_CONTINUE_H   47                  //つづけ
#define AIR_CHAR_EVENT_SELECT_CONTINUE_CURSOR       48                  //指カーソル
#define AIR_CHAR_EVENT_SELECT_CONTINUE_ERABU        49                  //えらぶ
#define AIR_CHAR_EVENT_SELECT_CONTINUE_KETEI        50                  //けってい
#define AIR_CHAR_EVENT_SELECT_CONTINUE_MENU         51                  //めにゅー

//----------------------------------------------------------------------------- 
// ■エフェクト番号
//----------------------------------------------------------------------------- 
#define AIR_EFFECT_MARU                             0   //まる
#define AIR_EFFECT_BATSU                            2   //ばつ
#define AIR_EFFECT_FUKURO                           4   //フクロ
#define AIR_EFFECT_ONNPU                            6   //音符
#define AIR_EFFECT_ASE                              8   //汗
#define AIR_EFFECT_ITEM_GUITAR                      10  //ギター
#define AIR_EFFECT_ITEM_DOLL                        12  //人形
#define AIR_EFFECT_ITEM_JEWELRY                     14  //宝石
#define AIR_EFFECT_ITEM_TRUMPET                     16  //らっぱ
#define AIR_EFFECT_ITEM_RIBBON                      18  //リボン
#define AIR_EFFECT_ITEM_RING                        20  //指輪
#define AIR_EFFECT_ITEM_CROWN                       22  //王冠
#define AIR_EFFECT_ITEM_JAR                         24  //つぼ
#define AIR_EFFECT_ITEM_TRAIN                       26  //汽車
#define AIR_EFFECT_ITEM_POSTCARD                    28  //葉書
#define AIR_EFFECT_DUST_TSHIRT                      30  //ボロTシャツ
#define AIR_EFFECT_DUST_MIRROR                      32  //ボロ手鏡
#define AIR_EFFECT_DUST_KAN                         34  //空き缶
#define AIR_EFFECT_DUST_YAKAN                       36  //ボロやかん
#define AIR_EFFECT_DUST_APPLE                       38  //ボロりんご
#define AIR_EFFECT_DUST_SHOES                       40  //ボロ靴
#define AIR_EFFECT_HELP_PANEL                       42  //助けてパネル
#define AIR_EFFECT_CRUSH                            44  //激突A
#define AIR_EFFECT_SMOKE                            51  //煙


//---- イベント部






//-----------------------------------------------------------------------------
//  typdef
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  class
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  extern
//-----------------------------------------------------------------------------
extern u_long   pad;
extern u_long   NewPad; 
extern u_long   OldPad; 
extern u_long   JstPad; 
extern u_long   WorkPad;

//game
extern u_long   BG_00_image[];
extern u_long   BG_00_clut[];
extern u_long   BG_01_image[];
extern u_long   BG_01_clut[];
extern u_long   GUN_00_image[];
extern u_long   GUN_00_clut[];
extern u_long   GUN_01_image[];
extern u_long   GUN_01_clut[];
extern u_long   GUN_02_image[];
extern u_long   GUN_02_clut[];
extern u_long   ITEM_image[];
extern u_long   ITEM_clut[];
extern u_long   OPANEL_image[];
extern u_long   OPANEL_clut[];
extern u_long   QUESTION_image[];
extern u_long   QUESTION_clut[];

//event
extern u_long   EBG_00_image[];
extern u_long   EBG_00_clut[];
extern u_long   EBG_01_image[];
extern u_long   EBG_01_clut[];
extern u_long   EBG_02_image[];
extern u_long   EBG_02_clut[];
extern u_long   EBG_03_image[];
extern u_long   EBG_03_clut[];
extern u_long   EBG_04_image[];
extern u_long   EBG_04_clut[];
extern u_long   EBG_05_image[];
extern u_long   EBG_05_clut[];
extern u_long   EBG_06_image[];
extern u_long   EBG_06_clut[];
extern u_long   EBG_07_image[];
extern u_long   EBG_07_clut[];
extern u_long   EBG_08_image[];
extern u_long   EBG_08_clut[];
extern u_long   EBG_09_image[];
extern u_long   EBG_09_clut[];
extern u_long   EBG_10_image[];
extern u_long   EBG_10_clut[];
extern u_long   EBG_11_image[];
extern u_long   EBG_11_clut[];
extern u_long   EBG_12_image[];
extern u_long   EBG_12_clut[];
extern u_long   EBG_13_image[];
extern u_long   EBG_13_clut[];
extern u_long   EBG_14_image[];
extern u_long   EBG_14_clut[];
extern u_long   EBG_15_image[];
extern u_long   EBG_15_clut[];
extern u_long   ECHARA1_image[];
extern u_long   ECHARA1_clut[];
extern u_long   ECHARA2_image[];
extern u_long   ECHARA2_clut[];
extern u_long   ECHARA3_image[];
extern u_long   ECHARA3_clut[];
extern u_long   ECHARA4_image[];
extern u_long   ECHARA4_clut[];
extern u_long   ECHARA5_image[];
extern u_long   ECHARA5_clut[];
extern u_long   ECHARA6_image[];
extern u_long   ECHARA6_clut[];
extern u_long   ECHARA7_image[];
extern u_long   ECHARA7_clut[];
extern u_long   ECHARA8_image[];
extern u_long   ECHARA8_clut[];
extern u_long   NEEDLE_image[];
extern u_long   NEEDLE_clut[];

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
//-------------------------------------------------------------------------------- ロードファイル名
static TIMD AirGameTextureFile[] = {
    //  デモタイトル名、    BINファイル名
    {   "RCUBE3",           "\\TIM\\AIRGD.B;1"},
};

static TIMD AirEventTextureFile[] = {
    //  デモタイトル名、    BINファイル名
    {   "RCUBE2",           "\\TIM\\AIRED.B;1"},
};


//-------------------------------------------------------------------------------- テクスチャデータ
static GsIMAGE AirGameTextureImage[]=
{
    //                  tpos        size        image               pos         size        clut
    {   TIM_COLOR_16,   384,0,      64,256,     font_image,         16,480,     16,6,       font_clut       },
    {   TIM_COLOR_16,   448,0,      64,256,     YorN_image,         0,480,      16,16,      YorN_clut       },
    {   TIM_COLOR_16,   512,0,      64,256,     help_00_image,      0,496,      16,2,       help_00_clut    },
    {   TIM_COLOR_16,   320,0,      64,256,     MMENU_image,        16,489,     16,7,       MMENU_clut      },
    {   TIM_COLOR_16,   512, 256,   64, 256,    BG_00_image,         0,500,     16,1,       BG_00_clut      },      //背景１
    {   TIM_COLOR_16,   768, 256,   16, 256,    BG_01_image,         0,499,     16,1,       BG_01_clut      },      //背景２
    {   TIM_COLOR_16,   448, 256,   64, 256,    GUN_00_image,       32,480,     16,16,      GUN_00_clut     },      //部品１
    {   TIM_COLOR_16,   320, 256,   64, 256,    GUN_01_image,       64,480,     16,16,      GUN_01_clut     },      //部品２
    {   TIM_COLOR_16,   640, 256,   64, 256,    GUN_02_image,       96,480,     16,16,      GUN_02_clut     },      //部品３
    {   TIM_COLOR_16,   576, 256,   64, 256,    ITEM_image,         48,480,     16,16,      ITEM_clut       },      //アイテム
    {   TIM_COLOR_256,  704, 256,   64, 128,    OPANEL_image,        0,498,     256,1,      OPANEL_clut     },      //お願いパネル
    {   TIM_COLOR_16,   384, 256,   64, 256,    QUESTION_image,     80,480,     16,16,      QUESTION_clut   },      //問題と部品
    {   TIM_COLOR_16,   832, 256,   64, 256,    NEEDLE_image,       128,480,    16,1,       NEEDLE_clut     },      //針
    
};


static GsIMAGE AirEventTextureImage[]=
{
    //  type            tpos        size        image               pos         size        clut
    {   TIM_COLOR_16,   384,0,      64,256,     font_image,         16,480,     16,6,       font_clut       },
    {   TIM_COLOR_16,   448,0,      64,256,     YorN_image,         0,480,      16,16,      YorN_clut       },
    {   TIM_COLOR_16,   512,0,      64,256,     help_00_image,      0,496,      16,2,       help_00_clut    },
    {   TIM_COLOR_16,   320,0,      64,256,     MMENU_image,        16,489,     16,7,       MMENU_clut      },
    {   TIM_COLOR_16,   704,256,    64,256,     EBG_00_image,       144,481,    16, 1,      EBG_00_clut     },
    {   TIM_COLOR_16,   898,256,    16,256,     EBG_01_image,       144,480,    16, 1,      EBG_01_clut     },
    {   TIM_COLOR_16,   832,256,    64,256,     EBG_02_image,       128,490,    16, 1,      EBG_02_clut     },
    {   TIM_COLOR_16,   930,256,    16,256,     EBG_03_image,       128,482,    16, 1,      EBG_03_clut     },
    {   TIM_COLOR_16,   320,256,    64,256,     EBG_04_image,       128,495,    16, 1,      EBG_04_clut     },
    {   TIM_COLOR_16,   914,256,    16,256,     EBG_05_image,       128,483,    16, 1,      EBG_05_clut     },
    {   TIM_COLOR_16,   384,256,    64,256,     EBG_06_image,       128,493,    16, 1,      EBG_06_clut     },
    {   TIM_COLOR_16,   999,  0,    16,256,     EBG_07_image,       128,484,    16, 1,      EBG_07_clut     },
    {   TIM_COLOR_16,   448,256,    64,256,     EBG_08_image,       128,491,    16, 1,      EBG_08_clut     },
    {   TIM_COLOR_16,   864,  0,    16,256,     EBG_09_image,       128,485,    16, 1,      EBG_09_clut     },
    {   TIM_COLOR_16,   512,256,    64,256,     EBG_10_image,       128,492,    16, 1,      EBG_10_clut     },
    {   TIM_COLOR_16,   880,  0,    16,256,     EBG_11_image,       128,486,    16, 1,      EBG_11_clut     },
    {   TIM_COLOR_16,   640,256,    64,256,     EBG_12_image,       128,489,    16, 1,      EBG_12_clut     },
    {   TIM_COLOR_16,   744,  0,    16,256,     EBG_13_image,       128,494,    16, 1,      EBG_13_clut     },
    {   TIM_COLOR_16,   576,256,    64,256,     EBG_14_image,       128,487,    16, 1,      EBG_14_clut     },
    {   TIM_COLOR_16,   930,  0,    16,256,     EBG_15_image,       128,488,    16, 1,      EBG_15_clut     },
    {   TIM_COLOR_16,   576,  0,    59,256,     ECHARA1_image,       32,480,    16,16,      ECHARA1_clut    },
    {   TIM_COLOR_16,   768,256,    64,256,     ECHARA2_image,       48,480,    16,16,      ECHARA2_clut    },
    {   TIM_COLOR_16,   704,  0,    40,256,     ECHARA3_image,       64,480,    16,16,      ECHARA3_clut    },
    {   TIM_COLOR_16,   960,  0,    39,256,     ECHARA4_image,       80,480,    16,16,      ECHARA4_clut    },
    {   TIM_COLOR_16,   640,  0,    56,256,     ECHARA5_image,       96,480,    16,16,      ECHARA5_clut    },
    {   TIM_COLOR_16,   768,  0,    50,256,     ECHARA6_image,      112,480,    16,16,      ECHARA6_clut    },
    {   TIM_COLOR_16,   833,  0,    31,236,     ECHARA7_image,      128,480,    16, 1,      ECHARA7_clut    },
    {   TIM_COLOR_16,   896,  0,    34,216,     ECHARA8_image,      128,481,    16, 1,      ECHARA8_clut    },
};


//-------------------------------------------------------------------------------- スプライト登録データ
//ゲーム部登録データ
static ENTRY_SPRITE_DATA AirGameSpriteData[] =
{
    //  TexNo                       TimLX   TimLY   Height  Width   PalNo
    //-------------------------------------------------------------------------     --[BG_00.TIM]
    {   TIM_POS_AIR_GAME_BG_00,     0,      0,      240,    256,    0       },          //背景１        
    //---------------------------------------------------------------------         --[BG_01.TIM]
    {   TIM_POS_AIR_GAME_BG_01,     256,    0,      240,    64,     0       },          //背景2         
    //---------------------------------------------------------------------         --[GUN_00.TIM]
    {   TIM_POS_AIR_GAME_GUN_00,    0,      0,      44,     62,     0       },          //標準横A
    {   TIM_POS_AIR_GAME_GUN_00,    62,     0,      44,     62,     0       },          //標準横B
    {   TIM_POS_AIR_GAME_GUN_00,    124,    0,      44,     62,     0       },          //正解A
    {   TIM_POS_AIR_GAME_GUN_00,    0,      44,     44,     62,     0       },          //正解B
    {   TIM_POS_AIR_GAME_GUN_00,    62,     44,     44,     62,     0       },          //ぐにゃぐにゃA
    {   TIM_POS_AIR_GAME_GUN_00,    124,    44,     44,     62,     0       },          //ぐにゃぐにゃB
    {   TIM_POS_AIR_GAME_GUN_00,    0,      88,     44,     62,     0       },          //下降
    {   TIM_POS_AIR_GAME_GUN_00,    62,     88,     44,     62,     0       },          //上昇
    {   TIM_POS_AIR_GAME_GUN_00,    124,    88,     44,     62,     0       },          //グングン飛行機・横
    {   TIM_POS_AIR_GAME_GUN_00,    0,      132,    41,     54,     1       },          //プロペラ　縦
    {   TIM_POS_AIR_GAME_GUN_00,    54,     132,    41,     54,     1       },          //プロペラ　横
    //---------------------------------------------------------------------         --[GUN_01.TIM]
    {   TIM_POS_AIR_GAME_GUN_01,    0,      0,      57,     252,    0       },          //背景の山                  0,183
    {   TIM_POS_AIR_GAME_GUN_01,    0,      57,     57,     76,     0       },          //上の画像に繋げて下さい。    252,183   
    {   TIM_POS_AIR_GAME_GUN_01,    76,     57,     41,     36,     1       },          //風船１
    {   TIM_POS_AIR_GAME_GUN_01,    112,    57,     41,     36,     1       },          //風船２
    {   TIM_POS_AIR_GAME_GUN_01,    148,    57,     41,     36,     1       },          //風船３
    {   TIM_POS_AIR_GAME_GUN_01,    76,     98,     26,     36,     2       },          //手・パー
    {   TIM_POS_AIR_GAME_GUN_01,    112,    98,     27,     26,     2       },          //手・グー
    {   TIM_POS_AIR_GAME_GUN_01,    138,    98,     26,     16,     3       },          //伸びる手の棒　グングンマシンに合わせて表示させてください。
    {   TIM_POS_AIR_GAME_GUN_01,    184,    57,     34,     58,     4       },          //雲・大
    {   TIM_POS_AIR_GAME_GUN_01,    184,    90,     30,     48,     4       },          //雲・中
    {   TIM_POS_AIR_GAME_GUN_01,    184,    120,    22,     34,     4       },          //雲・小
    {   TIM_POS_AIR_GAME_GUN_01,    112,    128,    18,     22,     5       },          //煙・大
    {   TIM_POS_AIR_GAME_GUN_01,    134,    128,    18,     22,     5       },          //煙・中
    {   TIM_POS_AIR_GAME_GUN_01,    156,    128,    18,     22,     5       },          //煙・小
    {   TIM_POS_AIR_GAME_GUN_01,      0,    128,    68,     16,     6       },          //問題プレート・左          16,0    
    {   TIM_POS_AIR_GAME_GUN_01,    16,     128,    68,     8,      6       },          //問題プレート・中央（×23)   32,0から
    {   TIM_POS_AIR_GAME_GUN_01,    24,     128,    68,     88,     6       },          //問題プレート・右            216,0 
    {   TIM_POS_AIR_GAME_GUN_01,    112,    146,    26,     30,     7       },          //まる  15,13
    {   TIM_POS_AIR_GAME_GUN_01,    142,    146,    26,     30,     7       },          //ばつ  15,13
    {   TIM_POS_AIR_GAME_GUN_01,    0,      196,    40,     64,     8       },          //フクロ
    {   TIM_POS_AIR_GAME_GUN_01,    64,     196,    32,     32,     8       },          //音符  14,14
    {   TIM_POS_AIR_GAME_GUN_01,    96,     196,    32,     32,     8       },          //汗    14,14
    {   TIM_POS_AIR_GAME_GUN_01,    128,    196,    46,     52,     9       },          //からすA
    {   TIM_POS_AIR_GAME_GUN_01,    176,    143,    46,     52,     9       },          //からすB
    {   TIM_POS_AIR_GAME_GUN_01,    180,    196,    46,     52,     9       },          //からすC
    //---------------------------------------------------------------------         --[GUN_02.TIM]
    {   TIM_POS_AIR_GAME_GUN_02,    0,      0,      97,     142,    0       },          //レベルプレート
    {   TIM_POS_AIR_GAME_GUN_02,    96,     104,    14,     20,     4       },          //選択カーソル
    {   TIM_POS_AIR_GAME_GUN_02,    96,     118,    9,      18,     4       },          //点滅ブロック
    {   TIM_POS_AIR_GAME_GUN_02,    96,     128,    10,     8,      3       },          //１
    {   TIM_POS_AIR_GAME_GUN_02,    104,    128,    10,     8,      3       },          //２
    {   TIM_POS_AIR_GAME_GUN_02,    112,    128,    10,     8,      3       },          //３
    {   TIM_POS_AIR_GAME_GUN_02,    120,    128,    10,     8,      3       },          //４
    {   TIM_POS_AIR_GAME_GUN_02,    128,    128,    10,     8,      3       },          //５
    {   TIM_POS_AIR_GAME_GUN_02,    0,      184,    42,     78,     5       },          //雷・大
    {   TIM_POS_AIR_GAME_GUN_02,    78,     184,    42,     46,     5       },          //雷・小
    {   TIM_POS_AIR_GAME_GUN_02,    124,    184,    59,     46,     5       },          //激突A
    {   TIM_POS_AIR_GAME_GUN_02,    170,    184,    59,     46,     5       },          //激突B
    //---------------------------------------------------------------------         --[ITEM.TIM]
    {   TIM_POS_AIR_GAME_ITEM,      0,      0,      43,     64,     0       },          //ギター        30,18
    {   TIM_POS_AIR_GAME_ITEM,      64,     0,      43,     64,     1       },          //人形          12,18
    {   TIM_POS_AIR_GAME_ITEM,      128,    0,      43,     64,     2       },          //宝石          20,18
    {   TIM_POS_AIR_GAME_ITEM,      192,    0,      43,     64,     3       },          //らっぱ        26,18
    {   TIM_POS_AIR_GAME_ITEM,      0,      43,     43,     64,     4       },          //リボン        18,18
    {   TIM_POS_AIR_GAME_ITEM,      64,     43,     43,     64,     5       },          //指輪          12,18
    {   TIM_POS_AIR_GAME_ITEM,      128,    43,     43,     64,     6       },          //王冠          20,18
    {   TIM_POS_AIR_GAME_ITEM,      192,    43,     43,     64,     7       },          //つぼ          14,18
    {   TIM_POS_AIR_GAME_ITEM,      0,      86,     43,     64,     8       },          //汽車          26,18
    {   TIM_POS_AIR_GAME_ITEM,      64,     86,     43,     64,     9       },          //葉書          16,18
    {   TIM_POS_AIR_GAME_ITEM,      128,    86,     43,     64,     10      },          //ボロTシャツ   20,16
    {   TIM_POS_AIR_GAME_ITEM,      192,    86,     43,     64,     11      },          //ボロ手鏡      18,16
    {   TIM_POS_AIR_GAME_ITEM,      0,      129,    43,     64,     12      },          //空き缶        18,16
    {   TIM_POS_AIR_GAME_ITEM,      64,     129,    43,     64,     13      },          //ボロやかん    24,16
    {   TIM_POS_AIR_GAME_ITEM,      128,    129,    43,     64,     14      },          //ボロりんご    10,16
    {   TIM_POS_AIR_GAME_ITEM,      192,    129,    43,     64,     15      },          //ボロ靴        16,16
    //---------------------------------------------------------------------         --[OPANEL.TIM]
    {   TIM_POS_AIR_GAME_OPANEL,    0,      0,      109,    128,    0       },          //おねがい
    //---------------------------------------------------------------------         --[QUESTION.TIM]
    {   TIM_POS_AIR_GAME_QUESTION,  0,      0,      25,     150,    0       },          //はりはどこをさしていますか？
    {   TIM_POS_AIR_GAME_QUESTION,  0,      25,     26,     112,    0       },          //いくつになりますか？  (60,30      数字の場所・前 / 88,29      数字の場所・後 )
    {   TIM_POS_AIR_GAME_QUESTION,  0,      51,     11,     138,    0       },          //いくつですか？    (50,37      数字の場所・前/ 80,37       数字の場所・後)
    {   TIM_POS_AIR_GAME_QUESTION,  0,      62,     10,     134,    0       },          //どちらがおおいですか？
    {   TIM_POS_AIR_GAME_QUESTION,  0,      72,     31,     178,    0       },          //はいるかずはなんですか？
    {   TIM_POS_AIR_GAME_QUESTION,  56,     189,    25,     176,    0       },          //＿じ＿＿なんぷん～？      (42,29)
    {   TIM_POS_AIR_GAME_QUESTION,  0,      123,    23,     74,     1       },          //大・青
    {   TIM_POS_AIR_GAME_QUESTION,  74,     123,    23,     74,     1       },          //大・ピンク
    {   TIM_POS_AIR_GAME_QUESTION,  148,    123,    20,     24,     1       },          //小・青
    {   TIM_POS_AIR_GAME_QUESTION,  172,    123,    20,     24,     1       },          //小・ピンク
    {   TIM_POS_AIR_GAME_QUESTION,  178,    85,     18,     22,     0       },          //出題赤枠
    {   TIM_POS_AIR_GAME_QUESTION,  0,      103,    10,     10,     0       },          //0　出題、解答用数字
    {   TIM_POS_AIR_GAME_QUESTION,  10,     103,    10,     10,     0       },          //1　出題、解答用数字
    {   TIM_POS_AIR_GAME_QUESTION,  20,     103,    10,     10,     0       },          //2　出題、解答用数字
    {   TIM_POS_AIR_GAME_QUESTION,  30,     103,    10,     10,     0       },          //3　出題、解答用数字
    {   TIM_POS_AIR_GAME_QUESTION,  40,     103,    10,     10,     0       },          //4　出題、解答用数字
    {   TIM_POS_AIR_GAME_QUESTION,  50,     103,    10,     10,     0       },          //5　出題、解答用数字
    {   TIM_POS_AIR_GAME_QUESTION,  60,     103,    10,     10,     0       },          //6　出題、解答用数字
    {   TIM_POS_AIR_GAME_QUESTION,  70,     103,    10,     10,     0       },          //7　出題、解答用数字
    {   TIM_POS_AIR_GAME_QUESTION,  80,     103,    10,     10,     0       },          //8　出題、解答用数字
    {   TIM_POS_AIR_GAME_QUESTION,  90,     103,    10,     10,     0       },          //9　出題、解答用数字
    {   TIM_POS_AIR_GAME_QUESTION,  0,      146,    14,     8,      2       },          //1　カウンター用数字
    {   TIM_POS_AIR_GAME_QUESTION,  8,      146,    14,     8,      2       },          //2　カウンター用数字
    {   TIM_POS_AIR_GAME_QUESTION,  16,     146,    14,     8,      2       },          //3　カウンター用数字
    {   TIM_POS_AIR_GAME_QUESTION,  24,     146,    14,     8,      2       },          //4　カウンター用数字
    {   TIM_POS_AIR_GAME_QUESTION,  32,     146,    14,     8,      2       },          //5　カウンター用数字
    {   TIM_POS_AIR_GAME_QUESTION,  40,     146,    14,     8,      2       },          //6　カウンター用数字
    {   TIM_POS_AIR_GAME_QUESTION,  48,     146,    14,     8,      2       },          //7　カウンター用数字
    {   TIM_POS_AIR_GAME_QUESTION,  56,     146,    14,     8,      2       },          //8　カウンター用数字
    {   TIM_POS_AIR_GAME_QUESTION,  64,     146,    14,     8,      2       },          //9　カウンター用数字
    {   TIM_POS_AIR_GAME_QUESTION,  72,     146,    14,     8,      2       },          //0　カウンター用数字
    {   TIM_POS_AIR_GAME_QUESTION,  0,      160,    12,     12,     3       },          //1　ウィンドウ用問題数の数字
    {   TIM_POS_AIR_GAME_QUESTION,  12,     160,    12,     12,     3       },          //2　ウィンドウ用問題数の数字
    {   TIM_POS_AIR_GAME_QUESTION,  24,     160,    12,     12,     3       },          //3　ウィンドウ用問題数の数字
    {   TIM_POS_AIR_GAME_QUESTION,  36,     160,    12,     12,     3       },          //4　ウィンドウ用問題数の数字
    {   TIM_POS_AIR_GAME_QUESTION,  48,     160,    12,     12,     3       },          //5　ウィンドウ用問題数の数字
    {   TIM_POS_AIR_GAME_QUESTION,  60,     160,    12,     12,     3       },          //6　ウィンドウ用問題数の数字
    {   TIM_POS_AIR_GAME_QUESTION,  72,     160,    12,     12,     3       },          //7　ウィンドウ用問題数の数字
    {   TIM_POS_AIR_GAME_QUESTION,  84,     160,    12,     12,     3       },          //8　ウィンドウ用問題数の数字
    {   TIM_POS_AIR_GAME_QUESTION,  96,     160,    12,     12,     3       },          //9　ウィンドウ用問題数の数字
    {   TIM_POS_AIR_GAME_QUESTION,  108,    160,    12,     12,     3       },          //10　ウィンドウ用問題数の数字
    {   TIM_POS_AIR_GAME_QUESTION,  0,      172,    16,     10,     4       },          //1　問題・数字の順番用
    {   TIM_POS_AIR_GAME_QUESTION,  10,     172,    16,     10,     4       },          //2　問題・数字の順番用
    {   TIM_POS_AIR_GAME_QUESTION,  20,     172,    16,     10,     4       },          //3　問題・数字の順番用
    {   TIM_POS_AIR_GAME_QUESTION,  30,     172,    16,     10,     4       },          //4　問題・数字の順番用
    {   TIM_POS_AIR_GAME_QUESTION,  40,     172,    16,     10,     4       },          //5　問題・数字の順番用
    {   TIM_POS_AIR_GAME_QUESTION,  50,     172,    16,     10,     4       },          //6　問題・数字の順番用
    {   TIM_POS_AIR_GAME_QUESTION,  60,     172,    16,     10,     4       },          //7　問題・数字の順番用
    {   TIM_POS_AIR_GAME_QUESTION,  70,     172,    16,     10,     4       },          //8　問題・数字の順番用
    {   TIM_POS_AIR_GAME_QUESTION,  80,     172,    16,     10,     4       },          //9　問題・数字の順番用
    {   TIM_POS_AIR_GAME_QUESTION,  90,     172,    16,     10,     4       },          //0　問題・数字の順番用
    {   TIM_POS_AIR_GAME_QUESTION,  0,      113,    10,     32,     0       },          //おなじ
    {   TIM_POS_AIR_GAME_QUESTION,  0,      189,    34,     36,     7       },          //時計版
    {   TIM_POS_AIR_GAME_QUESTION,  0,      224,    26,     26,     7       },          //短針
    {   TIM_POS_AIR_GAME_QUESTION,  26,     224,    28,     28,     7       },          //長針
    {   TIM_POS_AIR_GAME_QUESTION,  36,     189,    8,      10,     5       },          //ボール・オレンジ
    {   TIM_POS_AIR_GAME_QUESTION,  36,     197,    8,      10,     5       },          //みかん
    {   TIM_POS_AIR_GAME_QUESTION,  46,     189,    8,      10,     6       },          //ボール・赤
    {   TIM_POS_AIR_GAME_QUESTION,  46,     197,    8,      10,     6       },          //りんご
    //---------------------------------------------------------------------         --[緊急追加]
    {   TIM_POS_AIR_GAME_GUN_01,    138,    98,     26,     1,      3       },          //伸びる手の棒　グングンマシンに合わせて表示させてください。
    {   TIM_POS_AIR_GAME_GUN_01,    138,    98,     26,     2,      3       },          //伸びる手の棒　グングンマシンに合わせて表示させてください。
    {   TIM_POS_AIR_GAME_GUN_01,    138,    98,     26,     3,      3       },          //伸びる手の棒　グングンマシンに合わせて表示させてください。
    {   TIM_POS_AIR_GAME_GUN_01,    138,    98,     26,     4,      3       },          //伸びる手の棒　グングンマシンに合わせて表示させてください。
    {   TIM_POS_AIR_GAME_GUN_01,    138,    98,     26,     5,      3       },          //伸びる手の棒　グングンマシンに合わせて表示させてください。
    {   TIM_POS_AIR_GAME_GUN_01,    138,    98,     26,     6,      3       },          //伸びる手の棒　グングンマシンに合わせて表示させてください。
    {   TIM_POS_AIR_GAME_GUN_01,    138,    98,     26,     7,      3       },          //伸びる手の棒　グングンマシンに合わせて表示させてください。
    {   TIM_POS_AIR_GAME_GUN_01,    138,    98,     26,     8,      3       },          //伸びる手の棒　グングンマシンに合わせて表示させてください。
    {   TIM_POS_AIR_GAME_GUN_01,    138,    98,     26,     9,      3       },          //伸びる手の棒　グングンマシンに合わせて表示させてください。
    {   TIM_POS_AIR_GAME_GUN_01,    138,    98,     26,     10,     3       },          //伸びる手の棒　グングンマシンに合わせて表示させてください。
    //---------------------------------------------------------------------         --[緊急追加]
    {   TIM_POS_AIR_GAME_NEEDLE,    22*0,   22*0,   22,     22,     0       },          //短針00
    {   TIM_POS_AIR_GAME_NEEDLE,    22*1,   22*0,   22,     22,     0       },          //短針01
    {   TIM_POS_AIR_GAME_NEEDLE,    22*2,   22*0,   22,     22,     0       },          //短針02
    {   TIM_POS_AIR_GAME_NEEDLE,    22*3,   22*0,   22,     22,     0       },          //短針03
    {   TIM_POS_AIR_GAME_NEEDLE,    22*4,   22*0,   22,     22,     0       },          //短針04
    {   TIM_POS_AIR_GAME_NEEDLE,    22*5,   22*0,   22,     22,     0       },          //短針05
    {   TIM_POS_AIR_GAME_NEEDLE,    22*6,   22*0,   22,     22,     0       },          //短針06
    {   TIM_POS_AIR_GAME_NEEDLE,    22*7,   22*0,   22,     22,     0       },          //短針07
    {   TIM_POS_AIR_GAME_NEEDLE,    22*8,   22*0,   22,     22,     0       },          //短針08
    {   TIM_POS_AIR_GAME_NEEDLE,    22*9,   22*0,   22,     22,     0       },          //短針09
    {   TIM_POS_AIR_GAME_NEEDLE,    22*10,  22*0,   22,     22,     0       },          //短針10
    {   TIM_POS_AIR_GAME_NEEDLE,    22*0,   22*1,   22,     22,     0       },          //短針11
    {   TIM_POS_AIR_GAME_NEEDLE,    22*1,   22*1,   22,     22,     0       },          //短針12
    {   TIM_POS_AIR_GAME_NEEDLE,    22*2,   22*1,   22,     22,     0       },          //短針13
    {   TIM_POS_AIR_GAME_NEEDLE,    22*3,   22*1,   22,     22,     0       },          //短針14
    {   TIM_POS_AIR_GAME_NEEDLE,    22*4,   22*1,   22,     22,     0       },          //短針15
    {   TIM_POS_AIR_GAME_NEEDLE,    22*5,   22*1,   22,     22,     0       },          //短針16
    {   TIM_POS_AIR_GAME_NEEDLE,    22*6,   22*1,   22,     22,     0       },          //短針17
    {   TIM_POS_AIR_GAME_NEEDLE,    22*7,   22*1,   22,     22,     0       },          //短針18
    {   TIM_POS_AIR_GAME_NEEDLE,    22*8,   22*1,   22,     22,     0       },          //短針19
    {   TIM_POS_AIR_GAME_NEEDLE,    22*9,   22*1,   22,     22,     0       },          //短針20
    {   TIM_POS_AIR_GAME_NEEDLE,    22*10,  22*1,   22,     22,     0       },          //短針21
    {   TIM_POS_AIR_GAME_NEEDLE,    22*0,   22*2,   22,     22,     0       },          //短針22
    {   TIM_POS_AIR_GAME_NEEDLE,    22*1,   22*2,   22,     22,     0       },          //短針23
    {   TIM_POS_AIR_GAME_NEEDLE,    22*2,   22*2,   22,     22,     0       },          //短針24
    {   TIM_POS_AIR_GAME_NEEDLE,    22*3,   22*2,   22,     22,     0       },          //短針25
    {   TIM_POS_AIR_GAME_NEEDLE,    22*4,   22*2,   22,     22,     0       },          //短針26
    {   TIM_POS_AIR_GAME_NEEDLE,    22*5,   22*2,   22,     22,     0       },          //短針27
    {   TIM_POS_AIR_GAME_NEEDLE,    22*6,   22*2,   22,     22,     0       },          //短針28
    {   TIM_POS_AIR_GAME_NEEDLE,    22*7,   22*2,   22,     22,     0       },          //短針29
    {   TIM_POS_AIR_GAME_NEEDLE,    22*8,   22*2,   22,     22,     0       },          //短針30
    {   TIM_POS_AIR_GAME_NEEDLE,    22*9,   22*2,   22,     22,     0       },          //短針31
    {   TIM_POS_AIR_GAME_NEEDLE,    22*10,  22*2,   22,     22,     0       },          //短針32
    {   TIM_POS_AIR_GAME_NEEDLE,    22*0,   22*3,   22,     22,     0       },          //短針33
    {   TIM_POS_AIR_GAME_NEEDLE,    22*1,   22*3,   22,     22,     0       },          //短針34
    {   TIM_POS_AIR_GAME_NEEDLE,    22*2,   22*3,   22,     22,     0       },          //短針35
    {   TIM_POS_AIR_GAME_NEEDLE,    22*3,   22*3,   22,     22,     0       },          //短針36
    {   TIM_POS_AIR_GAME_NEEDLE,    22*4,   22*3,   22,     22,     0       },          //短針37
    {   TIM_POS_AIR_GAME_NEEDLE,    22*5,   22*3,   22,     22,     0       },          //短針38
    {   TIM_POS_AIR_GAME_NEEDLE,    22*6,   22*3,   22,     22,     0       },          //短針39
    {   TIM_POS_AIR_GAME_NEEDLE,    22*7,   22*3,   22,     22,     0       },          //短針40
    {   TIM_POS_AIR_GAME_NEEDLE,    22*8,   22*3,   22,     22,     0       },          //短針41
    {   TIM_POS_AIR_GAME_NEEDLE,    22*9,   22*3,   22,     22,     0       },          //短針42
    {   TIM_POS_AIR_GAME_NEEDLE,    22*10,  22*3,   22,     22,     0       },          //短針43
    {   TIM_POS_AIR_GAME_NEEDLE,    22*0,   22*4,   22,     22,     0       },          //短針44
    {   TIM_POS_AIR_GAME_NEEDLE,    22*1,   22*4,   22,     22,     0       },          //短針45
    {   TIM_POS_AIR_GAME_NEEDLE,    22*2,   22*4,   22,     22,     0       },          //短針46
    {   TIM_POS_AIR_GAME_NEEDLE,    22*3,   22*4,   22,     22,     0       },          //短針47
    {   TIM_POS_AIR_GAME_NEEDLE,    0,      120,    30,     30,     0       },          //長針00
    {   TIM_POS_AIR_GAME_NEEDLE,    30,     120,    30,     30,     0       },          //長針01
    {   TIM_POS_AIR_GAME_NEEDLE,    60,     120,    30,     30,     0       },          //長針02
    {   TIM_POS_AIR_GAME_NEEDLE,    90,     120,    30,     30,     0       },          //長針03
    {   TIM_POS_AIR_GAME_NEEDLE,    120,    120,    30,     30,     0       },          //長針04
    {   TIM_POS_AIR_GAME_NEEDLE,    150,    120,    30,     30,     0       },          //長針05
    {   TIM_POS_AIR_GAME_NEEDLE,    0,      150,    30,     30,     0       },          //長針06
    {   TIM_POS_AIR_GAME_NEEDLE,    30,     150,    30,     30,     0       },          //長針07
    {   TIM_POS_AIR_GAME_NEEDLE,    60,     150,    30,     30,     0       },          //長針08
    {   TIM_POS_AIR_GAME_NEEDLE,    90,     150,    30,     30,     0       },          //長針09
    {   TIM_POS_AIR_GAME_NEEDLE,    120,    150,    30,     30,     0       },          //長針10
    {   TIM_POS_AIR_GAME_NEEDLE,    150,    150,    30,     30,     0       },          //長針11
    //---------------------------------------------------------------------
    {   ENTRY_SPRITE_DATA_END,0,0,0,0,0 }   // データエンド
};


//イベント部登録データ
static ENTRY_SPRITE_DATA AirEventSpriteData[] =
{
    //  TexNo                       TimLX   TimLY   Height  Width   PalNo
    //-------------------------------------------------------------------------     --[EBG_00.TIM]
    {   TIM_POS_AIR_EVENT_EBG_00,   0,      0,      240,    256,    0       },          
    //-------------------------------------------------------------------------     --[EBG_01.TIM]
    {   TIM_POS_AIR_EVENT_EBG_01,   0,      0,      240,    64,     0       },          
    //-------------------------------------------------------------------------     --[EBG_02.TIM]
    {   TIM_POS_AIR_EVENT_EBG_02,   0,      0,      240,    256,    0       },          
    //-------------------------------------------------------------------------     --[EBG_03.TIM]
    {   TIM_POS_AIR_EVENT_EBG_03,   0,      0,      240,    64,     0       },          
    //-------------------------------------------------------------------------     --[EBG_04.TIM]
    {   TIM_POS_AIR_EVENT_EBG_04,   0,      0,      240,    256,    0       },          
    //-------------------------------------------------------------------------     --[EBG_05.TIM]
    {   TIM_POS_AIR_EVENT_EBG_05,   0,      0,      240,    64,     0       },          
    //-------------------------------------------------------------------------     --[EBG_06.TIM]
    {   TIM_POS_AIR_EVENT_EBG_06,   0,      0,      240,    256,    0       },          
    //-------------------------------------------------------------------------     --[EBG_07.TIM]
    {   TIM_POS_AIR_EVENT_EBG_07,   0,      0,      240,    64,     0       },          
    //-------------------------------------------------------------------------     --[EBG_08.TIM]
    {   TIM_POS_AIR_EVENT_EBG_08,   0,      0,      240,    256,    0       },          
    //-------------------------------------------------------------------------     --[EBG_09.TIM]
    {   TIM_POS_AIR_EVENT_EBG_09,   0,      0,      240,    64,     0       },          
    //-------------------------------------------------------------------------     --[EBG_10.TIM]
    {   TIM_POS_AIR_EVENT_EBG_10,   0,      0,      240,    256,    0       },          
    //-------------------------------------------------------------------------     --[EBG_11.TIM]
    {   TIM_POS_AIR_EVENT_EBG_11,   0,      0,      240,    64,     0       },          
    //-------------------------------------------------------------------------     --[EBG_12.TIM]
    {   TIM_POS_AIR_EVENT_EBG_12,   0,      0,      240,    256,    0       },          
    //-------------------------------------------------------------------------     --[EBG_13.TIM]
    {   TIM_POS_AIR_EVENT_EBG_13,   0,      0,      240,    64,     0       },          
    //-------------------------------------------------------------------------     --[EBG_14.TIM]
    {   TIM_POS_AIR_EVENT_EBG_14,   0,      0,      240,    256,    0       },          
    //-------------------------------------------------------------------------     --[EBG_15.TIM]
    {   TIM_POS_AIR_EVENT_EBG_15,   0,      0,      240,    64,     0       },          
    //-------------------------------------------------------------------------     --[ECHARA1.TIM]
    {   TIM_POS_AIR_EVENT_ECHARA1,  0,      0,      153,    162,    0       },          
    {   TIM_POS_AIR_EVENT_ECHARA1,  162,    0,      89,     72,     1       },          
    {   TIM_POS_AIR_EVENT_ECHARA1,  162,    89,     89,     72,     1       },          
    {   TIM_POS_AIR_EVENT_ECHARA1,  0,      153,    85,     80,     2       },          
    {   TIM_POS_AIR_EVENT_ECHARA1,  80,     153,    85,     80,     2       },          
    //-------------------------------------------------------------------------     --[ECHARA2.TIM]
    {   TIM_POS_AIR_EVENT_ECHARA2,  0,      0,      153,    162,    0       },          
    {   TIM_POS_AIR_EVENT_ECHARA2,  162,    0,      26,     67,     0       },          
    {   TIM_POS_AIR_EVENT_ECHARA2,  162,    26,     26,     67,     0       },          
    {   TIM_POS_AIR_EVENT_ECHARA2,  162,    56,     39,     84,     0       },          
    {   TIM_POS_AIR_EVENT_ECHARA2,  162,    95,     39,     84,     0       },          
    {   TIM_POS_AIR_EVENT_ECHARA2,  0,      153,    93,     110,    1       },          
    {   TIM_POS_AIR_EVENT_ECHARA2,  110,    153,    93,     110,    1       },          
    //-------------------------------------------------------------------------     --[ECHARA3.TIM]
    {   TIM_POS_AIR_EVENT_ECHARA3,  0,      0,      165,    156,    0       },          
    {   TIM_POS_AIR_EVENT_ECHARA3,  0,      165,    78,     78,     1       },          
    {   TIM_POS_AIR_EVENT_ECHARA3,  80,     165,    78,     78,     1       },          
    //-------------------------------------------------------------------------     --[ECHARA4.TIM]
    {   TIM_POS_AIR_EVENT_ECHARA4,  0,      0,      173,    156,    0       },          
    //-------------------------------------------------------------------------     --[ECHARA5.TIM]
    {   TIM_POS_AIR_EVENT_ECHARA5,  0,      0,      162,    220,    0       },          
    //-------------------------------------------------------------------------     --[ECHARA6.TIM]
    {   TIM_POS_AIR_EVENT_ECHARA6,  0,      0,      188,    200,    0       },          
    //-------------------------------------------------------------------------     --[ECHARA7.TIM]
    {   TIM_POS_AIR_EVENT_ECHARA7,  0,      0,      118,    122,    0       },          
    {   TIM_POS_AIR_EVENT_ECHARA7,  0,      118,    118,    122,    0       },          
    //-------------------------------------------------------------------------     --[ECHARA8.TIM]
    {   TIM_POS_AIR_EVENT_ECHARA8,  0,      0,      108,    134,    0       },          
    {   TIM_POS_AIR_EVENT_ECHARA8,  0,      108,    108,    134,    0       },          
    //---------------------------------------------------------------------------[YorNo.TIM]
    {   TIM_POS_AIR_EVENT_YORNO,    0,      0,      115,    186,    0       },      //プレート
    {   TIM_POS_AIR_EVENT_YORNO,    0,      115,    40,     38,     1       },      //非選択・はい 74,57
    {   TIM_POS_AIR_EVENT_YORNO,    38,     115,    40,     44,     1       },      //非選択・いいえ 126,57
    {   TIM_POS_AIR_EVENT_YORNO,    82,     115,    40,     44,     2       },      //選択・はい 72,57
    {   TIM_POS_AIR_EVENT_YORNO,    126,    115,    40,     44,     2       },      //選択・いいえ 126,57
    {   TIM_POS_AIR_EVENT_YORNO,    186,    0,      69,     58,     3       },      //プーぺ１
    {   TIM_POS_AIR_EVENT_YORNO,    186,    69,     69,     58,     3       },      //プーぺ２
    {   TIM_POS_AIR_EVENT_YORNO,    0,      155,    14,     148,    4       },      //もういちど
    {   TIM_POS_AIR_EVENT_YORNO,    0,      170,    14,     148,    4       },      //おわり
    {   TIM_POS_AIR_EVENT_YORNO,    20,     20,     14,     148,    4       },      //つづけ
    //---------------------------------------------------------------------------[font.TIM]
    {   TIM_POS_AIR_EVENT_FONT,     24,     200,    24,     26,     2       },      //指カーソル
    {   TIM_POS_AIR_EVENT_FONT,     0,      232,    15,     52,     4       },      //えらぶ
    {   TIM_POS_AIR_EVENT_FONT,     52,     232,    15,     52,     4       },      //けってい
    {   TIM_POS_AIR_EVENT_FONT,     104,    232,    15,     52,     4       },      //めにゅー
    //---------------------------------------------------------------------------
    {   ENTRY_SPRITE_DATA_END,0,0,0,0,0 }   // データエンド
};


//-------------------------------------------------------------------------------- 
//カウンター数字テーブル
static int TimerNoTable[]=
{
    AIR_CHAR_COUNTER_NO_00,             //0　カウンター用数字
    AIR_CHAR_COUNTER_NO_01,             //1　カウンター用数字
    AIR_CHAR_COUNTER_NO_02,             //2　カウンター用数字
    AIR_CHAR_COUNTER_NO_03,             //3　カウンター用数字
    AIR_CHAR_COUNTER_NO_04,             //4　カウンター用数字
    AIR_CHAR_COUNTER_NO_05,             //5　カウンター用数字
    AIR_CHAR_COUNTER_NO_06,             //6　カウンター用数字
    AIR_CHAR_COUNTER_NO_07,             //7　カウンター用数字
    AIR_CHAR_COUNTER_NO_08,             //8　カウンター用数字
    AIR_CHAR_COUNTER_NO_09,             //9　カウンター用数字
};

//問題出題用数字
static int QuestionTextNoSmallTable[]=
{
    AIR_CHAR_QA_NO_00,                  //0　出題、解答用数字
    AIR_CHAR_QA_NO_01,                  //1　出題、解答用数字
    AIR_CHAR_QA_NO_02,                  //2　出題、解答用数字
    AIR_CHAR_QA_NO_03,                  //3　出題、解答用数字
    AIR_CHAR_QA_NO_04,                  //4　出題、解答用数字
    AIR_CHAR_QA_NO_05,                  //5　出題、解答用数字
    AIR_CHAR_QA_NO_06,                  //6　出題、解答用数字
    AIR_CHAR_QA_NO_07,                  //7　出題、解答用数字
    AIR_CHAR_QA_NO_08,                  //8　出題、解答用数字
    AIR_CHAR_QA_NO_09,                  //9　出題、解答用数字
};

//問題用数字
static int QuestionTextNoLargeTable[]=
{
    AIR_CHAR_QUESTION_NO_00,            //0　問題・数字の順番用
    AIR_CHAR_QUESTION_NO_01,            //1　問題・数字の順番用
    AIR_CHAR_QUESTION_NO_02,            //2　問題・数字の順番用
    AIR_CHAR_QUESTION_NO_03,            //3　問題・数字の順番用
    AIR_CHAR_QUESTION_NO_04,            //4　問題・数字の順番用
    AIR_CHAR_QUESTION_NO_05,            //5　問題・数字の順番用
    AIR_CHAR_QUESTION_NO_06,            //6　問題・数字の順番用
    AIR_CHAR_QUESTION_NO_07,            //7　問題・数字の順番用
    AIR_CHAR_QUESTION_NO_08,            //8　問題・数字の順番用
    AIR_CHAR_QUESTION_NO_09,            //9　問題・数字の順番用
};


//-------- ゲーム管理
static AIR_GAME AGameMgr;


#define NORMAL_EFFECT_DRAW_TIME     1
#define CRUSH_SMOKE_TIME            16
#define GUNGUN_FEELING_MARK_TIME    90
#define SMOKE_TIME                  8

//--------エフェクトデータテーブル
static EFFECT_ENTRY_DATA EffectEntryTable[]=
{
    {   AIR_CHAR_MARU           ,GUNGUN_FEELING_MARK_TIME   ,15,    13  },          //まる
    {   ANM_STOP                ,0                          ,0,     0   },          //----------
    {   AIR_CHAR_BATSU          ,GUNGUN_FEELING_MARK_TIME   ,15,    13  },          //ばつ
    {   ANM_STOP                ,0                          ,0,     0   },          //----------
    {   AIR_CHAR_FUKURO         ,NORMAL_EFFECT_DRAW_TIME    ,0,     0   },          //フクロ
    {   ANM_STOP                ,0                          ,0,     0   },          //----------
    {   AIR_CHAR_ONNPU          ,GUNGUN_FEELING_MARK_TIME   ,14,    14  },          //音符
    {   ANM_STOP                ,0                          ,0,     0   },          //----------
    {   AIR_CHAR_ASE            ,GUNGUN_FEELING_MARK_TIME   ,14,    14  },          //汗
    {   ANM_STOP                ,0                          ,0,     0   },          //----------
    {   AIR_CHAR_ITEM_GUITAR    ,NORMAL_EFFECT_DRAW_TIME    ,30,    18  },          //ギター
    {   ANM_STOP                ,0                          ,0,     0   },          //----------
    {   AIR_CHAR_ITEM_DOLL      ,NORMAL_EFFECT_DRAW_TIME    ,12,    18  },          //人形  
    {   ANM_STOP                ,0                          ,0,     0   },          //----------
    {   AIR_CHAR_ITEM_JEWELRY   ,NORMAL_EFFECT_DRAW_TIME    ,20,    18  },          //宝石  
    {   ANM_STOP                ,0                          ,0,     0   },          //----------
    {   AIR_CHAR_ITEM_TRUMPET   ,NORMAL_EFFECT_DRAW_TIME    ,26,    18  },          //らっぱ
    {   ANM_STOP                ,0                          ,0,     0   },          //----------
    {   AIR_CHAR_ITEM_RIBBON    ,NORMAL_EFFECT_DRAW_TIME    ,18,    18  },          //リボン
    {   ANM_STOP                ,0                          ,0,     0   },          //----------
    {   AIR_CHAR_ITEM_RING      ,NORMAL_EFFECT_DRAW_TIME    ,12,    18  },          //指輪  
    {   ANM_STOP                ,0                          ,0,     0   },          //----------
    {   AIR_CHAR_ITEM_CROWN     ,NORMAL_EFFECT_DRAW_TIME    ,20,    18  },          //王冠  
    {   ANM_STOP                ,0                          ,0,     0   },          //----------
    {   AIR_CHAR_ITEM_JAR       ,NORMAL_EFFECT_DRAW_TIME    ,14,    18  },          //つぼ  
    {   ANM_STOP                ,0                          ,0,     0   },          //----------
    {   AIR_CHAR_ITEM_TRAIN     ,NORMAL_EFFECT_DRAW_TIME    ,26,    18  },          //汽車  
    {   ANM_STOP                ,0                          ,0,     0   },          //----------
    {   AIR_CHAR_ITEM_POSTCARD  ,NORMAL_EFFECT_DRAW_TIME    ,16,    18  },          //葉書  
    {   ANM_STOP                ,0                          ,0,     0   },          //----------
    {   AIR_CHAR_DUST_TSHIRT    ,NORMAL_EFFECT_DRAW_TIME    ,26,    16  },          //ボロTシャツ
    {   ANM_STOP                ,0                          ,0,     0   },          //----------
    {   AIR_CHAR_DUST_MIRROR    ,NORMAL_EFFECT_DRAW_TIME    ,18,    16  },          //ボロ手鏡
    {   ANM_STOP                ,0                          ,0,     0   },          //----------
    {   AIR_CHAR_DUST_KAN       ,NORMAL_EFFECT_DRAW_TIME    ,18,    16  },          //空き缶
    {   ANM_STOP                ,0                          ,0,     0   },          //----------
    {   AIR_CHAR_DUST_YAKAN     ,NORMAL_EFFECT_DRAW_TIME    ,24,    16  },          //ボロやかん
    {   ANM_STOP                ,0                          ,0,     0   },          //----------
    {   AIR_CHAR_DUST_APPLE     ,NORMAL_EFFECT_DRAW_TIME    ,10,    16  },          //ボロりんご
    {   ANM_STOP                ,0                          ,0,     0   },          //----------
    {   AIR_CHAR_DUST_SHOES     ,NORMAL_EFFECT_DRAW_TIME    ,16,    16  },          //ボロ靴
    {   ANM_STOP                ,0                          ,0,     0   },          //----------
    {   AIR_CHAR_HELP_PANEL     ,NORMAL_EFFECT_DRAW_TIME    ,128,   128 },          //助けてパネル
    {   ANM_STOP                ,0                          ,0,     0   },          //----------
    {   AIR_CHAR_CRUSH_00       ,CRUSH_SMOKE_TIME           ,28,    22  },          //激突A
    {   AIR_CHAR_CRUSH_01       ,CRUSH_SMOKE_TIME           ,28,    22  },          //激突B
    {   AIR_CHAR_CRUSH_00       ,CRUSH_SMOKE_TIME           ,28,    22  },          //激突A
    {   AIR_CHAR_CRUSH_01       ,CRUSH_SMOKE_TIME           ,28,    22  },          //激突B
    {   AIR_CHAR_CRUSH_00       ,CRUSH_SMOKE_TIME           ,28,    22  },          //激突A
    {   AIR_CHAR_CRUSH_01       ,CRUSH_SMOKE_TIME           ,28,    22  },          //激突B
    {   ANM_STOP                ,0                          ,0,     0   },          //----------
    {   AIR_CHAR_SMOKE_SMALL    ,SMOKE_TIME                 ,11,    6   },          //煙小
    {   AIR_CHAR_SMOKE_MIDDLE   ,SMOKE_TIME                 ,10,    7-4 },          //煙中
    {   AIR_CHAR_SMOKE_LARGE    ,SMOKE_TIME                 ,11,    9-7 },          //煙大
    {   ANM_STOP                ,0                          ,0,     0   },          //----------
};


//--------カラススプライトテーブル
static int CrowSpriteTable[]={
    AIR_CHAR_CROW_00,   //CROW_ANM_BASE_SUPRISE
    AIR_CHAR_CROW_00,
    AIR_CHAR_CROW_01,   //CROW_ANM_BASE_FLY
    AIR_CHAR_CROW_02,
};


//--------基本ラインY座標
static int LinePosYTbl[]=
{
    BASE_ALINE_01_Y,
    BASE_ALINE_02_Y,
    BASE_ALINE_03_Y
};


//--------基本ライン
static int LineTbl[]=
{
    BASE_ALINE_01,
    BASE_ALINE_02,
    BASE_ALINE_03
};


//-------- 取得アイテムテーブル
static CATCH_DATA GetItemTable[]=
{
    {   AIR_EFFECT_ITEM_GUITAR,     22,       0 },
    {   AIR_EFFECT_ITEM_DOLL,       10,     -16 },
    {   AIR_EFFECT_ITEM_JEWELRY,    18,       4 },
    {   AIR_EFFECT_ITEM_TRUMPET,     4,      -2 },
    {   AIR_EFFECT_ITEM_RIBBON,      4,      -5 },
    {   AIR_EFFECT_ITEM_RING,        8,     -14 },
    {   AIR_EFFECT_ITEM_CROWN,      10,      -4 },
    {   AIR_EFFECT_ITEM_JAR,        12,     -12 },
    {   AIR_EFFECT_ITEM_TRAIN,      16,       0 },
    {   AIR_EFFECT_ITEM_POSTCARD,   10,     -12 },
};


//-------- 取得ゴミテーブル
static CATCH_DATA GetDustTable[]=
{
    {   AIR_EFFECT_DUST_TSHIRT,     10,     0   },
    {   AIR_EFFECT_DUST_MIRROR,     13,     -14 },
    {   AIR_EFFECT_DUST_KAN,        10,     -8  },
    {   AIR_EFFECT_DUST_YAKAN,      12,      2  },
    {   AIR_EFFECT_DUST_APPLE,       8,     -8  },
    {   AIR_EFFECT_DUST_SHOES,      16,     -8  },
};


//-------- 敵復活待ち時間
static int EnemyDeathWaitTable[]={
    ENEMY_DEATH_WAIT_TIMER_1,   //LEVEL-1
    ENEMY_DEATH_WAIT_TIMER_2,   //LEVEL-2
    ENEMY_DEATH_WAIT_TIMER_3,   //LEVEL-3
};


//-------- 取得アイテムテーブル
//static int GetItemTable[]=
//{
//  AIR_EFFECT_ITEM_GUITAR,
//  AIR_EFFECT_ITEM_DOLL,
//  AIR_EFFECT_ITEM_JEWELRY,
//  AIR_EFFECT_ITEM_TRUMPET,
//  AIR_EFFECT_ITEM_RIBBON,
//  AIR_EFFECT_ITEM_RING,
//  AIR_EFFECT_ITEM_CROWN,
//  AIR_EFFECT_ITEM_JAR,
//  AIR_EFFECT_ITEM_TRAIN,
//  AIR_EFFECT_ITEM_POSTCARD,
//};
//
//
//-------- 取得ゴミテーブル
//static int GetDustTable[]=
//{
//  AIR_EFFECT_DUST_TSHIRT,
//  AIR_EFFECT_DUST_MIRROR,
//  AIR_EFFECT_DUST_KAN,
//  AIR_EFFECT_DUST_YAKAN,
//  AIR_EFFECT_DUST_APPLE,
//  AIR_EFFECT_DUST_SHOES,
//};


//-------- 問題データ
//----問題データ＆選択肢／質問種類０
static QUESTION_TEXT_00_DATA QuestionText00_Data[]=
{
    //  種類                問題文の数値            選択する答え
    //----[ LEVEL-1 ]----------------------------------------------------------------------------------------------------------------
    {   QUESTION_TEXT_00,    1,  2, -1,  4,  5,     6,  0,0,     3, 1,0,     9, 0,0 },  //[ 0]      [ 1 -  2 - ■ -  4 -  5]
    {   QUESTION_TEXT_00,    2,  3,  4,  5, -1,     7,  0,0,     6, 1,0,     8, 0,0 },  //[ 1]      [ 2 -  3 -  4 -  5 - ■]
    {   QUESTION_TEXT_00,    3, -1,  5,  6,  7,     4,  1,0,     8, 0,0,     9, 0,0 },  //[ 2]      [ 3 - ■ -  5 -  6 -  7]
    {   QUESTION_TEXT_00,    4,  5,  6,  -1, 8,     2,  0,0,     9, 0,0,     7, 1,0 },  //[ 3]      [ 4 -  5 -  6 - ■ -  8]
    {   QUESTION_TEXT_00,    5,  6,  7, -1,  9,     1,  0,0,     3, 0,0,     8, 1,0 },  //[ 4]      [ 5 -  6 -  7 - ■ -  9]
    {   QUESTION_TEXT_00,    6,  7,  8,  9, -1,     12, 0,0,    11, 0,0,     10,1,0 },  //[ 5]      [ 6 -  7 -  8 -  9 - ■]
    {   QUESTION_TEXT_00,    7,  8,  9, -1, 11,     12, 0,0,    10, 1,0,     13,0,0 },  //[ 6]      [ 7 -  8 -  9 - ■ - 11]
    {   QUESTION_TEXT_00,    9, 10, -1, 12, 13,     14, 0,0,    11, 1,0,     16,0,0 },  //[ 7]      [ 9 - 10 - ■ - 12 - 13]
    {   QUESTION_TEXT_00,   10, -1, 12, 13, 14,     11, 1,0,    15, 0,0,     17,0,0 },  //[ 8]      [10 - ■ - 12 - 13 - 14]
    {   QUESTION_TEXT_00,   11, 12, 13, -1, 15,     18, 0,0,    14, 1,0,     16,0,0 },  //[ 9]      [11 - 12 - 13 - ■ - 15]
    {   QUESTION_TEXT_00,   -1, 13, 14, 15, 16,     19, 0,0,    11, 0,0,     12,1,0 },  //[10]      [■ - 13 - 14 - 15 - 16]
    {   QUESTION_TEXT_00,   13, 14, -1, 16, 17,     15, 1,0,    12, 0,0,     11,0,0 },  //[11]      [13 - 14 - ■ - 16 - 17]
    {   QUESTION_TEXT_00,   14, -1, 16, 17, 18,     12, 0,0,    15, 1,0,     19,0,0 },  //[12]      [14 - ■ - 16 - 17 - 18]
    {   QUESTION_TEXT_00,   15, 16, 17, -1, 19,     18, 1,0,    14, 0,0,     12,0,0 },  //[13]      [15 - 16 - 17 - ■ - 19]
    //----[ LEVEL-2 ]----------------------------------------------------------------------------------------------------------------
    {   QUESTION_TEXT_00,   -1,  4,  6,  8, 10,     8,  0,0,    7,  0,0,     2, 1,0 },  //[14]      [■ -  4 -  6 -  8 - 10]
    {   QUESTION_TEXT_00,    4,  6,  8, -1, 12,     10, 1,0,    14, 0,0,    16, 0,0 },  //[15]      [ 4 -  6 -  8 - ■ - 12]
    {   QUESTION_TEXT_00,    6,  8, -1, 12, 14,     16, 0,0,    10, 1,0,    18, 0,0 },  //[16]      [ 6 -  8 - ■ - 12 - 14]
    {   QUESTION_TEXT_00,    8, -1, 12, 14, 16,     18, 0,0,    15, 0,0,    10, 1,0 },  //[17]      [ 8 - ■ - 12 - 14 - 16]
    {   QUESTION_TEXT_00,    9, -1, 13, 15, 17,     11, 1,0,    10, 0,0,    19, 0,0 },  //[18]      [ 9 - ■ - 13 - 15 - 17]
    {   QUESTION_TEXT_00,   10, 12, 14, 16, -1,     18, 1,0,    11, 0,0,    13, 0,0 },  //[19]      [10 - 12 - 14 - 16 - ■]
    {   QUESTION_TEXT_00,   22, -1, 24, 25, 26,     21, 0,0,    23, 1,0,    29, 0,0 },  //[20]      [22 - ■ - 24 - 25 - 26]
    {   QUESTION_TEXT_00,   -1, 28, 29, 30, 31,     27, 1,0,    25, 0,0,    29, 0,0 },  //[21]      [■ - 28 - 29 - 30 - 31]
    {   QUESTION_TEXT_00,   31, 32, 33, -1, 35,     38, 0,0,    30, 0,0,    34, 1,0 },  //[22]      [31 - 32 - 33 - ■ - 35]
    {   QUESTION_TEXT_00,   34, -1, 36, 37, 38,     33, 0,0,    39, 0,0,    35, 1,0 },  //[23]      [34 - ■ - 36 - 37 - 38]
    {   QUESTION_TEXT_00,   44, 45, -1, 47, 48,     41, 0,0,    46, 1,0,    49, 0,0 },  //[24]      [44 - 45 - ■ - 47 - 48]
    {   QUESTION_TEXT_00,   59, 60, 61, -1, 63,     65, 0,0,    67, 0,0,    62, 1,0 },  //[25]      [59 - 60 - 61 - ■ - 63]
    {   QUESTION_TEXT_00,   64, -1, 66, 67, 68,     65, 1,0,    69, 0,0,    63, 0,0 },  //[26]      [64 - ■ - 66 - 67 - 68]
    {   QUESTION_TEXT_00,   72, 73, 74, -1, 76,     71, 0,0,    75, 1,0,    79, 0,0 },  //[27]      [72 - 73 - 74 - ■ - 76]
    {   QUESTION_TEXT_00,   77, 78, -1, 80, 81,     79, 1,0,    76, 0,0,    72, 0,0 },  //[28]      [77 - 78 - ■ - 80 - 81]
    {   QUESTION_TEXT_00,   89, -1, 91, 92, 93,     90, 1,0,    98, 0,0,    94, 0,0 },  //[29]      [89 - ■ - 91 - 92 - 93]
    //----[ LEVEL-3 ]----------------------------------------------------------------------------------------------------------------
    {   QUESTION_TEXT_00,   10, 20, 30, -1, 50,     60, 0,0,    40, 1,0,    80, 0,0 },  //[30]      [10 - 20 - 30 - ■ - 50]
    {   QUESTION_TEXT_00,   20, -1, 40, 50, 60,     30, 1,0,    70, 0,0,    80, 0,0 },  //[31]      [20 - ■ - 40 - 50 - 60]
    {   QUESTION_TEXT_00,   30, 40, 50, 60, -1,     10, 0,0,    20, 0,0,    70, 1,0 },  //[32]      [30 - 40 - 50 - 60 - ■]
    {   QUESTION_TEXT_00,   -1, 50, 60, 70, 80,     30, 0,0,    40, 1,0,    90, 0,0 },  //[33]      [■ - 50 - 60 - 70 - 80]
    {   QUESTION_TEXT_00,   50, 60, 70, -1, 90,     20, 0,0,    80, 1,0,    30, 0,0 },  //[34]      [50 - 60 - 70 - ■ - 90]
    {   QUESTION_TEXT_00,   21, 23, 25, 27, -1,     29, 1,0,    22, 0,0,    24, 0,0 },  //[35]      [21 - 23 - 25 - 27 - ■]
    {   QUESTION_TEXT_00,   25, -1, 29, 31, 33,     27, 1,0,    23, 0,0,    26, 0,0 },  //[36]      [25 - ■ - 29 - 31 - 33]
    {   QUESTION_TEXT_00,   33, 35, 37, -1, 41,     39, 1,0,    32, 0,0,    36, 0,0 },  //[37]      [33 - 35 - 37 - ■ - 41]
    {   QUESTION_TEXT_00,   39, 41, -1, 45, 47,     49, 0,0,    43, 1,0,    42, 0,0 },  //[38]      [39 - 41 - ■ - 45 - 47]
    {   QUESTION_TEXT_00,   43, -1, 47, 49, 51,     46, 0,0,    41, 0,0,    45, 1,0 },  //[39]      [43 - ■ - 47 - 49 - 51]
    {   QUESTION_TEXT_00,   55, 57, 59, 61, -1,     66, 0,0,    63, 1,0,    69, 0,0 },  //[40]      [55 - 57 - 59 - 61 - ■]
    {   QUESTION_TEXT_00,   69, 71, 73, 75, -1,     77, 1,0,    78, 0,0,    79, 0,0 },  //[41]      [69 - 71 - 73 - 75 - ■]
    {   QUESTION_TEXT_00,   73, -1, 77, 79, 81,     71, 0,0,    75, 1,0,    76, 0,0 },  //[42]      [73 - ■ - 77 - 79 - 81]
    {   QUESTION_TEXT_00,   81, 83, 85, -1, 89,     87, 1,0,    86, 0,0,    82, 0,0 },  //[43]      [81 - 83 - 85 - ■ - 89]
    {   QUESTION_TEXT_00,   89, 91, -1, 95, 97,     99, 0,0,    93, 1,0,    94, 0,0 },  //[44]      [89 - 91 - ■ - 95 - 97]
    {   QUESTION_TEXT_00,   24, -1, 28, 30, 32,     26, 1,0,    22, 0,0,    27, 0,0 },  //[45]      [24 - ■ - 28 - 30 - 32]
    {   QUESTION_TEXT_00,   28, 30, -1, 34, 36,     33, 0,0,    32, 1,0,    35, 0,0 },  //[46]      [28 - 30 - ■ - 34 - 36]
    {   QUESTION_TEXT_00,   34, 36, 38, -1, 42,     46, 0,0,    40, 1,0,    48, 0,0 },  //[47]      [34 - 36 - 38 - ■ - 42]
    {   QUESTION_TEXT_00,   -1, 40, 42, 44, 46,     38, 1,0,    36, 0,0,    34, 0,0 },  //[48]      [■ - 40 - 42 - 44 - 46]
    {   QUESTION_TEXT_00,   -1, 44, 46, 48, 50,     40, 0,0,    41, 0,0,    42, 1,0 },  //[49]      [■ - 44 - 46 - 48 - 50]
    {   QUESTION_TEXT_00,   54, 56, 58, -1, 62,     66, 0,0,    60, 1,0,    64, 0,0 },  //[50]      [54 - 56 - 58 - ■ - 62]
    {   QUESTION_TEXT_00,   -1, 68, 70, 72, 74,     66, 1,0,    62, 0,0,    64, 0,0 },  //[51]      [■ - 68 - 70 - 72 - 74]
    {   QUESTION_TEXT_00,   68, 70, 72, 74, -1,     76, 1,0,    78, 0,0,    75, 0,0 },  //[52]      [68 - 70 - 72 - 74 - ■]
    {   QUESTION_TEXT_00,   88, -1, 92, 94, 96,     90, 1,0,    98, 0,0,    95, 0,0 },  //[53]      [88 - ■ - 92 - 94 - 96]
    {   QUESTION_TEXT_00,   90, 92, 94, -1, 98,     95, 0,0,    96, 1,0,    97, 0,0 },  //[54]      [90 - 92 - 94 - ■ - 98]
};


//問題データ＆選択肢／質問種類１
static QUESTION_TEXT_01_DATA QuestionText01_Data[]=
{
    //  種類                問題文の数値    選択する答え
    //----[ LEVEL-1 ]--------------------------------------------------------------------------------------------------------
    {   QUESTION_TEXT_01,   0,  1,          1,1,0,  2,0,0,  3,0,0   },  //[ 0]      [0] と [1] で いくつになりますか？
    {   QUESTION_TEXT_01,   0,  2,          1,0,0,  2,1,0,  3,0,0   },  //[ 1]      [0] と [2] で いくつになりますか？
    {   QUESTION_TEXT_01,   0,  3,          2,0,0,  3,1,0,  4,0,0   },  //[ 2]      [0] と [3] で いくつになりますか？
    {   QUESTION_TEXT_01,   0,  4,          4,1,0,  5,0,0,  6,0,0   },  //[ 3]      [0] と [4] で いくつになりますか？
    {   QUESTION_TEXT_01,   0,  5,          3,0,0,  4,0,0,  5,1,0   },  //[ 4]      [0] と [5] で いくつになりますか？
    {   QUESTION_TEXT_01,   1,  0,          1,1,0,  2,0,0,  3,0,0   },  //[ 5]      [1] と [0] で いくつになりますか？
    {   QUESTION_TEXT_01,   1,  1,          1,0,0,  2,1,0,  3,0,0   },  //[ 6]      [1] と [1] で いくつになりますか？
    {   QUESTION_TEXT_01,   1,  2,          1,0,0,  2,0,0,  3,1,0   },  //[ 7]      [1] と [2] で いくつになりますか？
    {   QUESTION_TEXT_01,   1,  3,          4,1,0,  5,0,0,  6,0,0   },  //[ 8]      [1] と [3] で いくつになりますか？
    {   QUESTION_TEXT_01,   1,  4,          4,0,0,  5,1,0,  6,0,0   },  //[ 9]      [1] と [4] で いくつになりますか？
    {   QUESTION_TEXT_01,   1,  5,          4,0,0,  5,0,0,  6,1,0   },  //[10]      [1] と [5] で いくつになりますか？
    {   QUESTION_TEXT_01,   2,  0,          1,0,0,  2,1,0,  3,0,0   },  //[11]      [2] と [0] で いくつになりますか？
    {   QUESTION_TEXT_01,   2,  1,          1,0,0,  2,0,0,  3,1,0   },  //[12]      [2] と [1] で いくつになりますか？
    {   QUESTION_TEXT_01,   2,  2,          4,1,0,  5,0,0,  6,0,0   },  //[13]      [2] と [2] で いくつになりますか？
    {   QUESTION_TEXT_01,   2,  3,          4,0,0,  5,1,0,  6,0,0   },  //[14]      [2] と [3] で いくつになりますか？
    {   QUESTION_TEXT_01,   2,  4,          4,0,0,  5,0,0,  6,1,0   },  //[15]      [2] と [4] で いくつになりますか？
    {   QUESTION_TEXT_01,   3,  0,          3,1,0,  4,0,0,  5,0,0   },  //[16]      [3] と [0] で いくつになりますか？
    {   QUESTION_TEXT_01,   3,  1,          3,0,0,  4,1,0,  5,0,0   },  //[17]      [3] と [1] で いくつになりますか？
    {   QUESTION_TEXT_01,   3,  2,          3,0,0,  4,0,0,  5,1,0   },  //[18]      [3] と [2] で いくつになりますか？
    {   QUESTION_TEXT_01,   3,  3,          6,1,0,  7,0,0,  8,0,0   },  //[19]      [3] と [3] で いくつになりますか？
    {   QUESTION_TEXT_01,   4,  0,          2,0,0,  3,0,0,  4,1,0   },  //[20]      [4] と [0] で いくつになりますか？
    {   QUESTION_TEXT_01,   4,  1,          5,1,0,  6,0,0,  7,0,0   },  //[21]      [4] と [1] で いくつになりますか？
    {   QUESTION_TEXT_01,   4,  2,          5,0,0,  6,1,0,  7,0,0   },  //[22]      [4] と [2] で いくつになりますか？
    {   QUESTION_TEXT_01,   5,  0,          5,1,0,  6,0,0,  7,0,0   },  //[23]      [5] と [0] で いくつになりますか？
    {   QUESTION_TEXT_01,   5,  1,          4,0,0,  5,0,0,  6,1,0   },  //[24]      [5] と [1] で いくつになりますか？
    //----[ LEVEL-2 ]--------------------------------------------------------------------------------------------------------
    {   QUESTION_TEXT_01,   0,  6,          6,1,0,  7,0,0,  8,0,0   },  //[25]      [0] と [6] で いくつになりますか？
    {   QUESTION_TEXT_01,   0,  7,          6,0,0,  7,1,0,  8,0,0   },  //[26]      [0] と [7] で いくつになりますか？
    {   QUESTION_TEXT_01,   0,  8,          6,0,0,  7,0,0,  8,1,0   },  //[27]      [0] と [8] で いくつになりますか？
    {   QUESTION_TEXT_01,   0,  9,          7,0,0,  8,0,0,  9,1,0   },  //[28]      [0] と [9] で いくつになりますか？
    {   QUESTION_TEXT_01,   0,  10,         9,0,0,  10,1,0, 11,0,0  },  //[29]      [0] と [10] で いくつになりますか？
    {   QUESTION_TEXT_01,   1,  6,          7,1,0,  8,0,0,  9,0,0   },  //[30]      [1] と [6] で いくつになりますか？
    {   QUESTION_TEXT_01,   1,  7,          7,0,0,  8,1,0,  9,0,0   },  //[31]      [1] と [7] で いくつになりますか？
    {   QUESTION_TEXT_01,   1,  8,          7,0,0,  8,0,0,  9,1,0   },  //[32]      [1] と [8] で いくつになりますか？
    {   QUESTION_TEXT_01,   1,  9,          8,0,0,  9,0,0,  10,1,0  },  //[33]      [1] と [9] で いくつになりますか？
    {   QUESTION_TEXT_01,   2,  5,          7,1,0,  8,0,0,  9,0,0   },  //[34]      [2] と [5] で いくつになりますか？
    {   QUESTION_TEXT_01,   2,  6,          7,0,0,  8,1,0,  9,0,0   },  //[35]      [2] と [6] で いくつになりますか？
    {   QUESTION_TEXT_01,   2,  7,          9,1,0,  10,0,0, 11,0,0  },  //[36]      [2] と [7] で いくつになりますか？
    {   QUESTION_TEXT_01,   2,  8,          9,0,0,  10,1,0, 11,0,0  },  //[37]      [2] と [8] で いくつになりますか？
    {   QUESTION_TEXT_01,   3,  4,          6,0,0,  7,1,0,  8,0,0   },  //[38]      [3] と [4] で いくつになりますか？
    {   QUESTION_TEXT_01,   3,  5,          7,0,0,  8,1,0,  9,0,0   },  //[39]      [3] と [5] で いくつになりますか？
    {   QUESTION_TEXT_01,   3,  6,          9,1,0,  10,0,0, 11,0,0  },  //[40]      [3] と [6] で いくつになりますか？
    {   QUESTION_TEXT_01,   3,  7,          10,1,0, 11,0,0, 12,0,0  },  //[41]      [3] と [7] で いくつになりますか？
    {   QUESTION_TEXT_01,   4,  3,          5,0,0,  6,0,0,  7,1,0   },  //[42]      [4] と [3] で いくつになりますか？
    {   QUESTION_TEXT_01,   4,  4,          8,1,0,  9,0,0,  10,0,0  },  //[43]      [4] と [4] で いくつになりますか？
    {   QUESTION_TEXT_01,   4,  5,          8,0,0,  9,1,0,  10,0,0  },  //[44]      [4] と [5] で いくつになりますか？
    {   QUESTION_TEXT_01,   4,  6,          9,0,0,  10,1,0, 11,0,0  },  //[45]      [4] と [6] で いくつになりますか？
    {   QUESTION_TEXT_01,   5,  2,          6,0,0,  7,1,0,  8,0,0   },  //[46]      [5] と [2] で いくつになりますか？
    {   QUESTION_TEXT_01,   5,  3,          8,1,0,  9,0,0,  10,0,0  },  //[47]      [5] と [3] で いくつになりますか？
    {   QUESTION_TEXT_01,   5,  4,          7,0,0,  8,0,0,  9,1,0   },  //[48]      [5] と [4] で いくつになりますか？
    {   QUESTION_TEXT_01,   5,  5,          9,0,0,  10,1,0, 11,0,0  },  //[49]      [5] と [5] で いくつになりますか？
    {   QUESTION_TEXT_01,   6,  0,          6,1,0,  7,0,0,  8,0,0   },  //[50]      [6] と [0] で いくつになりますか？
    {   QUESTION_TEXT_01,   6,  1,          5,0,0,  6,0,0,  7,1,0   },  //[51]      [6] と [1] で いくつになりますか？
    {   QUESTION_TEXT_01,   6,  2,          7,0,0,  8,1,0,  9,0,0   },  //[52]      [6] と [2] で いくつになりますか？
    {   QUESTION_TEXT_01,   6,  3,          9,1,0,  10,0,0, 11,0,0  },  //[53]      [6] と [3] で いくつになりますか？
    {   QUESTION_TEXT_01,   6,  4,          9,0,0,  10,1,0, 11,0,0  },  //[54]      [6] と [4] で いくつになりますか？
    {   QUESTION_TEXT_01,   7,  0,          6,0,0,  7,1,0,  8,0,0   },  //[55]      [7] と [0] で いくつになりますか？
    {   QUESTION_TEXT_01,   7,  1,          7,0,0,  8,1,0,  9,0,0   },  //[56]      [7] と [1] で いくつになりますか？
    {   QUESTION_TEXT_01,   7,  2,          7,0,0,  8,0,0,  9,1,0   },  //[57]      [7] と [2] で いくつになりますか？
    {   QUESTION_TEXT_01,   7,  3,          9,0,0,  10,1,0, 11,0,0  },  //[58]      [7] と [3] で いくつになりますか？
    {   QUESTION_TEXT_01,   8,  0,          8,1,0,  9,0,0,  10,0,0  },  //[59]      [8] と [0] で いくつになりますか？
    {   QUESTION_TEXT_01,   8,  1,          8,0,0,  9,1,0,  10,0,0  },  //[60]      [8] と [1] で いくつになりますか？
    {   QUESTION_TEXT_01,   8,  2,          9,0,0,  10,1,0, 11,0,0  },  //[61]      [8] と [2] で いくつになりますか？
    {   QUESTION_TEXT_01,   9,  0,          8,0,0,  9,1,0,  10,0,0  },  //[62]      [9] と [0] で いくつになりますか？
    {   QUESTION_TEXT_01,   9,  1,          10,1,0, 11,0,0, 12,0,0  },  //[63]      [9] と [1] で いくつになりますか？
    {   QUESTION_TEXT_01,   10, 0,          10,1,0, 11,0,0, 12,0,0  },  //[64]      [10] と [0] で いくつになりますか？
};


//問題データ＆選択肢／質問種類２
static QUESTION_TEXT_02_DATA QuestionText02_Data[]=
{
    //  種類                問題文の数値    選択する答え
    //----[ LEVEL-2 ]--------------------------------------------------------------------------------------------------------
    {   QUESTION_TEXT_02,   1,  0,          1,1,0,  2,0,0,  3,0,0   },      //[0]       [1] は [0] と いくつですか？
    {   QUESTION_TEXT_02,   2,  0,          0,0,0,  1,0,0,  2,1,0   },      //[1]       [2] は [0] と いくつですか？
    {   QUESTION_TEXT_02,   3,  0,          1,0,0,  2,0,0,  3,1,0   },      //[2]       [3] は [0] と いくつですか？
    {   QUESTION_TEXT_02,   4,  0,          4,1,0,  5,0,0,  6,0,0   },      //[3]       [4] は [0] と いくつですか？
    {   QUESTION_TEXT_02,   5,  0,          3,0,0,  4,0,0,  5,1,0   },      //[4]       [5] は [0] と いくつですか？
    {   QUESTION_TEXT_02,   1,  1,          0,1,0,  2,0,0,  3,0,0   },      //[5]       [1] は [1] と いくつですか？
    {   QUESTION_TEXT_02,   2,  1,          1,1,0,  2,0,0,  3,0,0   },      //[6]       [2] は [1] と いくつですか？
    {   QUESTION_TEXT_02,   3,  1,          2,1,0,  3,0,0,  4,0,0   },      //[7]       [3] は [1] と いくつですか？
    {   QUESTION_TEXT_02,   4,  1,          2,0,0,  3,1,0,  4,0,0   },      //[8]       [4] は [1] と いくつですか？
    {   QUESTION_TEXT_02,   5,  1,          4,1,0,  5,0,0,  6,0,0   },      //[9]       [5] は [1] と いくつですか？
    {   QUESTION_TEXT_02,   6,  1,          4,0,0,  5,1,0,  6,0,0   },      //[10]      [6] は [1] と いくつですか？
    {   QUESTION_TEXT_02,   2,  2,          0,1,0,  1,0,0,  2,0,0   },      //[11]      [2] は [2] と いくつですか？
    {   QUESTION_TEXT_02,   3,  2,          0,0,0,  1,1,0,  2,0,0   },      //[12]      [3] は [2] と いくつですか？
    {   QUESTION_TEXT_02,   4,  2,          0,0,0,  1,0,0,  2,1,0   },      //[13]      [4] は [2] と いくつですか？
    {   QUESTION_TEXT_02,   5,  2,          2,0,0,  3,1,0,  4,0,0   },      //[14]      [5] は [2] と いくつですか？
    {   QUESTION_TEXT_02,   6,  2,          2,0,0,  3,0,0,  4,1,0   },      //[15]      [6] は [2] と いくつですか？
    {   QUESTION_TEXT_02,   7,  2,          5,1,0,  6,0,0,  7,0,0   },      //[16]      [7] は [2] と いくつですか？
    {   QUESTION_TEXT_02,   3,  3,          0,1,0,  1,0,0,  2,0,0   },      //[17]      [3] は [3] と いくつですか？
    {   QUESTION_TEXT_02,   4,  3,          1,1,0,  2,0,0,  3,0,0   },      //[18]      [4] は [3] と いくつですか？
    {   QUESTION_TEXT_02,   5,  3,          2,1,0,  3,0,0,  4,0,0   },      //[19]      [5] は [3] と いくつですか？
    {   QUESTION_TEXT_02,   6,  3,          3,1,0,  4,0,0,  5,0,0   },      //[20]      [6] は [3] と いくつですか？
    {   QUESTION_TEXT_02,   7,  3,          3,0,0,  4,1,0,  5,0,0   },      //[21]      [7] は [3] と いくつですか？
    {   QUESTION_TEXT_02,   8,  3,          5,1,0,  6,0,0,  7,0,0   },      //[22]      [8] は [3] と いくつですか？
    {   QUESTION_TEXT_02,   4,  4,          0,1,0,  1,0,0,  2,0,0   },      //[23]      [4] は [4] と いくつですか？
    {   QUESTION_TEXT_02,   5,  4,          1,1,0,  2,0,0,  3,0,0   },      //[24]      [5] は [4] と いくつですか？
    {   QUESTION_TEXT_02,   6,  4,          1,0,0,  2,1,0,  3,0,0   },      //[25]      [6] は [4] と いくつですか？
    {   QUESTION_TEXT_02,   7,  4,          1,0,0,  2,0,0,  3,1,0   },      //[26]      [7] は [4] と いくつですか？
    {   QUESTION_TEXT_02,   8,  4,          3,0,0,  4,1,0,  5,0,0   },      //[27]      [8] は [4] と いくつですか？
    {   QUESTION_TEXT_02,   9,  4,          4,0,0,  5,1,0,  6,0,0   },      //[28]      [9] は [4] と いくつですか？
    {   QUESTION_TEXT_02,   5,  5,          0,1,0,  1,0,0,  2,0,0   },      //[29]      [5] は [5] と いくつですか？
    {   QUESTION_TEXT_02,   6,  5,          0,0,0,  1,1,0,  2,0,0   },      //[30]      [6] は [5] と いくつですか？
    {   QUESTION_TEXT_02,   7,  5,          2,1,0,  3,0,0,  4,0,0   },      //[31]      [7] は [5] と いくつですか？
    {   QUESTION_TEXT_02,   8,  5,          1,0,0,  2,0,0,  3,1,0   },      //[32]      [8] は [5] と いくつですか？
    {   QUESTION_TEXT_02,   9,  5,          2,0,0,  3,0,0,  4,1,0   },      //[33]      [9] は [5] と いくつですか？
    {   QUESTION_TEXT_02,   10, 5,          4,0,0,  5,1,0,  6,0,0   },      //[34]      [10] は [5] と いくつですか？
    //----[ LEVEL-3 ]--------------------------------------------------------------------------------------------------------
    {   QUESTION_TEXT_02,   6,  0,          6,1,0,  7,0,0,  8,0,0   },      //[35]      [6] は [0] と いくつですか？        
    {   QUESTION_TEXT_02,   7,  0,          6,0,0,  7,1,0,  8,0,0   },      //[36]      [7] は [0] と いくつですか？
    {   QUESTION_TEXT_02,   8,  0,          8,1,0,  9,0,0,  10,0,0  },      //[37]      [8] は [0] と いくつですか？
    {   QUESTION_TEXT_02,   9,  0,          8,0,0,  9,1,0,  10,0,0  },      //[38]      [9] は [0] と いくつですか？
    {   QUESTION_TEXT_02,   10, 0,          10,1,0, 11,0,0, 12,0,0  },      //[39]      [10] は [0] と いくつですか？
    {   QUESTION_TEXT_02,   7,  1,          4,0,0,  5,0,0,  6,1,0   },      //[40]      [7] は [1] と いくつですか？
    {   QUESTION_TEXT_02,   8,  1,          6,0,0,  7,1,0,  8,0,0   },      //[41]      [8] は [1] と いくつですか？
    {   QUESTION_TEXT_02,   9,  1,          7,0,0,  8,1,0,  9,0,0   },      //[42]      [9] は [1] と いくつですか？
    {   QUESTION_TEXT_02,   10, 1,          8,0,0,  9,1,0,  10,0,0  },      //[43]      [10] は [1] と いくつですか？
    {   QUESTION_TEXT_02,   8,  2,          4,0,0,  5,0,0,  6,1,0   },      //[44]      [8] は [2] と いくつですか？
    {   QUESTION_TEXT_02,   9,  2,          5,0,0,  6,0,0,  7,1,0   },      //[45]      [9] は [2] と いくつですか？
    {   QUESTION_TEXT_02,   10, 2,          7,0,0,  8,1,0,  9,0,0   },      //[46]      [10] は [2] と いくつですか？
    {   QUESTION_TEXT_02,   9,  3,          6,1,0,  7,0,0,  8,0,0   },      //[47]      [9] は [3] と いくつですか？
    {   QUESTION_TEXT_02,   10, 3,          6,0,0,  7,1,0,  8,0,0   },      //[48]      [10] は [3] と いくつですか？
    {   QUESTION_TEXT_02,   10, 4,          6,1,0,  7,0,0,  8,0,0   },      //[49]      [10] は [4] と いくつですか？
    {   QUESTION_TEXT_02,   6,  6,          0,1,0,  1,0,0,  2,0,0   },      //[50]      [6] は [6] と いくつですか？
    {   QUESTION_TEXT_02,   7,  6,          0,0,0,  1,1,0,  2,0,0   },      //[51]      [7] は [6] と いくつですか？
    {   QUESTION_TEXT_02,   8,  6,          2,1,0,  3,0,0,  4,0,0   },      //[52]      [8] は [6] と いくつですか？
    {   QUESTION_TEXT_02,   9,  6,          3,1,0,  4,0,0,  5,0,0   },      //[53]      [9] は [6] と いくつですか？
    {   QUESTION_TEXT_02,   10, 6,          3,0,0,  4,1,0,  5,0,0   },      //[54]      [10] は [6] と いくつですか？
    {   QUESTION_TEXT_02,   7,  7,          0,1,0,  1,0,0,  2,0,0   },      //[55]      [7] は [7] と いくつですか？
    {   QUESTION_TEXT_02,   8,  7,          0,0,0,  1,1,0,  2,0,0   },      //[56]      [8] は [7] と いくつですか？
    {   QUESTION_TEXT_02,   9,  7,          1,0,0,  2,1,0,  3,0,0   },      //[57]      [9] は [7] と いくつですか？
    {   QUESTION_TEXT_02,   10, 7,          3,1,0,  4,0,0,  5,0,0   },      //[58]      [10] は [7] と いくつですか？
    {   QUESTION_TEXT_02,   8,  8,          0,1,0,  1,0,0,  2,0,0   },      //[59]      [8] は [8] と いくつですか？
    {   QUESTION_TEXT_02,   9,  8,          1,1,0,  2,0,0,  3,0,0   },      //[60]      [9] は [8] と いくつですか？
    {   QUESTION_TEXT_02,   10, 8,          1,0,0,  2,1,0,  3,0,0   },      //[61]      [10] は [8] と いくつですか？
    {   QUESTION_TEXT_02,   9,  9,          0,1,0,  1,0,0,  2,0,0   },      //[62]      [9] は [9] と いくつですか？
    {   QUESTION_TEXT_02,   10, 9,          1,1,0,  2,0,0,  3,0,0   },      //[63]      [10] は [9] と いくつですか？
    {   QUESTION_TEXT_02,   10, 10,         0,1,0,  1,0,0,  2,0,0   },      //[64]      [10] は [10] と いくつですか？
};


//問題データ＆選択肢／質問種類３
static QUESTION_TEXT_03_DATA QuestionText03_Data[]=
{
    //  種類                問題文の数値    選択する答え
    //----[ LEVEL-1 ]--------------------------------------------------------------------------------------------------------------------------------------------------------
    {   QUESTION_TEXT_03,   12,             CLOCK_00_00,1,0,    CLOCK_11_00,0,0,    CLOCK_01_00,0,0 },      //[ 0]      [12] 時のとき時計のはりはどこをさしていますか？
    {   QUESTION_TEXT_03,    1,             CLOCK_00_05,0,0,    CLOCK_01_00,1,0,    CLOCK_02_00,0,0 },      //[ 1]      [ 1] 時のとき時計のはりはどこをさしていますか？
    {   QUESTION_TEXT_03,    2,             CLOCK_00_10,0,0,    CLOCK_01_00,0,0,    CLOCK_02_00,1,0 },      //[ 2]      [ 2] 時のとき時計のはりはどこをさしていますか？
    {   QUESTION_TEXT_03,    3,             CLOCK_03_00,1,0,    CLOCK_00_15,0,0,    CLOCK_04_00,0,0 },      //[ 3]      [ 3] 時のとき時計のはりはどこをさしていますか？
    {   QUESTION_TEXT_03,    4,             CLOCK_00_20,0,0,    CLOCK_04_00,1,0,    CLOCK_05_00,0,0 },      //[ 4]      [ 4] 時のとき時計のはりはどこをさしていますか？
    {   QUESTION_TEXT_03,    5,             CLOCK_00_25,0,0,    CLOCK_06_00,0,0,    CLOCK_05_00,1,0 },      //[ 5]      [ 5] 時のとき時計のはりはどこをさしていますか？
    {   QUESTION_TEXT_03,    6,             CLOCK_06_00,1,0,    CLOCK_07_00,0,0,    CLOCK_00_30,0,0 },      //[ 6]      [ 6] 時のとき時計のはりはどこをさしていますか？
    {   QUESTION_TEXT_03,    7,             CLOCK_08_00,0,0,    CLOCK_07_00,1,0,    CLOCK_00_35,0,0 },      //[ 7]      [ 7] 時のとき時計のはりはどこをさしていますか？
    {   QUESTION_TEXT_03,    8,             CLOCK_07_00,0,0,    CLOCK_00_40,0,0,    CLOCK_08_00,1,0 },      //[ 8]      [ 8] 時のとき時計のはりはどこをさしていますか？
    {   QUESTION_TEXT_03,    9,             CLOCK_09_00,1,0,    CLOCK_08_00,0,0,    CLOCK_00_45,0,0 },      //[ 9]      [ 9] 時のとき時計のはりはどこをさしていますか？
    {   QUESTION_TEXT_03,   10,             CLOCK_09_00,0,0,    CLOCK_10_00,1,0,    CLOCK_00_50,0,0 },      //[10]      [10] 時のとき時計のはりはどこをさしていますか？
    {   QUESTION_TEXT_03,   11,             CLOCK_10_00,0,0,    CLOCK_00_55,0,0,    CLOCK_11_00,1,0 },      //[11]      [11] 時のとき時計のはりはどこをさしていますか？
    {   QUESTION_TEXT_03,   12,             CLOCK_11_00,0,0,    CLOCK_01_00,0,0,    CLOCK_00_00,1,0 },      //[12]      [12] 時のとき時計のはりはどこをさしていますか？
    {   QUESTION_TEXT_03,    1,             CLOCK_01_00,1,0,    CLOCK_00_00,0,0,    CLOCK_00_05,0,0 },      //[13]      [ 1] 時のとき時計のはりはどこをさしていますか？
    {   QUESTION_TEXT_03,    2,             CLOCK_03_00,0,0,    CLOCK_02_00,1,0,    CLOCK_00_10,0,0 },      //[14]      [ 2] 時のとき時計のはりはどこをさしていますか？
    {   QUESTION_TEXT_03,    3,             CLOCK_00_15,0,0,    CLOCK_04_00,0,0,    CLOCK_03_00,1,0 },      //[15]      [ 3] 時のとき時計のはりはどこをさしていますか？
    {   QUESTION_TEXT_03,    4,             CLOCK_04_00,1,0,    CLOCK_05_00,0,0,    CLOCK_00_20,0,0 },      //[16]      [ 4] 時のとき時計のはりはどこをさしていますか？
    {   QUESTION_TEXT_03,    5,             CLOCK_00_25,0,0,    CLOCK_05_00,1,0,    CLOCK_04_00,0,0 },      //[17]      [ 5] 時のとき時計のはりはどこをさしていますか？
    {   QUESTION_TEXT_03,    6,             CLOCK_07_00,0,0,    CLOCK_00_30,0,0,    CLOCK_06_00,1,0 },      //[18]      [ 6] 時のとき時計のはりはどこをさしていますか？
    {   QUESTION_TEXT_03,    7,             CLOCK_07_00,1,0,    CLOCK_00_35,0,0,    CLOCK_08_00,0,0 },      //[19]      [ 7] 時のとき時計のはりはどこをさしていますか？
    {   QUESTION_TEXT_03,    8,             CLOCK_00_40,0,0,    CLOCK_08_00,1,0,    CLOCK_09_00,0,0 },      //[20]      [ 8] 時のとき時計のはりはどこをさしていますか？
    {   QUESTION_TEXT_03,    9,             CLOCK_10_00,0,0,    CLOCK_00_45,0,0,    CLOCK_09_00,1,0 },      //[21]      [ 9] 時のとき時計のはりはどこをさしていますか？
    {   QUESTION_TEXT_03,   10,             CLOCK_10_00,1,0,    CLOCK_09_00,0,0,    CLOCK_00_50,0,0 },      //[22]      [10] 時のとき時計のはりはどこをさしていますか？
    {   QUESTION_TEXT_03,   11,             CLOCK_00_55,0,0,    CLOCK_11_00,1,0,    CLOCK_10_00,0,0 },      //[23]      [11] 時のとき時計のはりはどこをさしていますか？
};  


//問題データ＆選択肢／質問種類４
static QUESTION_TEXT_04_DATA QuestionText04_Data[]=
{
    //  種類                問題文の数値    選択する答え
    //----[ LEVEL-2 ]--------------------------------------------------------------------------------------------------------------------------------------------------------
    {   QUESTION_TEXT_04,   12, 30,         CLOCK_00_30,1,0,    CLOCK_01_30,0,0,    CLOCK_06_00,0,0 },      //[ 0]      [12:30] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,    1, 30,         CLOCK_06_05,0,0,    CLOCK_01_30,1,0,    CLOCK_02_30,0,0 },      //[ 1]      [ 1:30] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,    2, 30,         CLOCK_01_30,0,0,    CLOCK_06_10,0,0,    CLOCK_02_30,1,0 },      //[ 2]      [ 2:30] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,    3, 30,         CLOCK_03_30,1,0,    CLOCK_04_30,0,0,    CLOCK_06_15,0,0 },      //[ 3]      [ 3:30] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,    4, 30,         CLOCK_06_20,0,0,    CLOCK_04_30,1,0,    CLOCK_05_30,0,0 },      //[ 4]      [ 4:30] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,    5, 30,         CLOCK_06_30,0,0,    CLOCK_06_25,0,0,    CLOCK_05_30,1,0 },      //[ 5]      [ 5:30] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,    6, 30,         CLOCK_06_30,1,0,    CLOCK_07_30,0,0,    CLOCK_05_30,0,0 },      //[ 6]      [ 6:30] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,    7, 30,         CLOCK_06_30,0,0,    CLOCK_07_30,1,0,    CLOCK_06_35,0,0 },      //[ 7]      [ 7:30] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,    8, 30,         CLOCK_07_30,0,0,    CLOCK_06_40,0,0,    CLOCK_08_30,1,0 },      //[ 8]      [ 8:30] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,    9, 30,         CLOCK_09_30,1,0,    CLOCK_06_45,0,0,    CLOCK_10_30,0,0 },      //[ 9]      [ 9:30] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,   10, 30,         CLOCK_06_50,0,0,    CLOCK_10_30,1,0,    CLOCK_11_30,0,0 },      //[10]      [10:30] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,   11, 30,         CLOCK_10_30,0,0,    CLOCK_06_55,0,0,    CLOCK_11_30,1,0 },      //[11]      [11:30] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,   12, 30,         CLOCK_06_00,0,0,    CLOCK_01_30,0,0,    CLOCK_00_30,1,0 },      //[12]      [12:30] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,    1, 30,         CLOCK_01_30,1,0,    CLOCK_02_30,0,0,    CLOCK_06_05,0,0 },      //[13]      [ 1:30] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,    2, 30,         CLOCK_06_10,0,0,    CLOCK_02_30,1,0,    CLOCK_03_30,0,0 },      //[14]      [ 2:30] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,    3, 30,         CLOCK_04_30,0,0,    CLOCK_06_15,0,0,    CLOCK_03_30,1,0 },      //[15]      [ 3:30] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,    4, 30,         CLOCK_04_30,1,0,    CLOCK_05_30,0,0,    CLOCK_06_20,0,0 },      //[16]      [ 4:30] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,    5, 30,         CLOCK_04_30,0,0,    CLOCK_05_30,1,0,    CLOCK_06_25,0,0 },      //[17]      [ 5:30] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,    6, 30,         CLOCK_07_30,0,0,    CLOCK_05_30,0,0,    CLOCK_06_30,1,0 },      //[18]      [ 6:30] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,    7, 30,         CLOCK_07_30,1,0,    CLOCK_06_35,0,0,    CLOCK_08_30,0,0 },      //[19]      [ 7:30] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,    8, 30,         CLOCK_06_40,0,0,    CLOCK_08_30,1,0,    CLOCK_09_30,0,0 },      //[20]      [ 8:30] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,    9, 30,         CLOCK_10_30,0,0,    CLOCK_06_45,0,0,    CLOCK_09_30,1,0 },      //[21]      [ 9:30] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,   10, 30,         CLOCK_10_30,1,0,    CLOCK_11_30,0,0,    CLOCK_06_50,0,0 },      //[22]      [10:30] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,   11, 30,         CLOCK_00_30,0,0,    CLOCK_11_30,1,0,    CLOCK_06_55,0,0 },      //[23]      [11:30] の とき時計の針はどこをさしていますか？
    //----[ LEVEL-3 ]--------------------------------------------------------------------------------------------------------------------------------------------------------
    {   QUESTION_TEXT_04,   12, 15,         CLOCK_00_15,1,0,    CLOCK_03_00,0,0,    CLOCK_11_15,0,0 },      //[24]      [12:15] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,    1, 15,         CLOCK_02_15,0,0,    CLOCK_01_15,1,0,    CLOCK_03_05,0,0 },      //[25]      [ 1:15] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,    2, 15,         CLOCK_01_15,0,0,    CLOCK_03_10,0,0,    CLOCK_02_15,1,0 },      //[26]      [ 2:15] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,    3, 15,         CLOCK_03_15,1,0,    CLOCK_04_15,0,0,    CLOCK_02_15,0,0 },      //[27]      [ 3:15] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,    4, 15,         CLOCK_03_20,0,0,    CLOCK_04_15,1,0,    CLOCK_03_15,0,0 },      //[28]      [ 4:15] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,    5, 15,         CLOCK_03_25,0,0,    CLOCK_06_15,0,0,    CLOCK_05_15,1,0 },      //[29]      [ 5:15] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,    6, 15,         CLOCK_06_15,1,0,    CLOCK_07_15,0,0,    CLOCK_03_30,0,0 },      //[30]      [ 6:15] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,    7, 15,         CLOCK_03_35,0,0,    CLOCK_07_15,1,0,    CLOCK_08_15,0,0 },      //[31]      [ 7:15] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,    8, 15,         CLOCK_09_15,0,0,    CLOCK_03_40,0,0,    CLOCK_08_15,1,0 },      //[32]      [ 8:15] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,    9, 15,         CLOCK_09_15,1,0,    CLOCK_10_15,0,0,    CLOCK_03_45,0,0 },      //[33]      [ 9:15] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,   10, 15,         CLOCK_03_50,0,0,    CLOCK_10_15,1,0,    CLOCK_09_15,0,0 },      //[34]      [10:15] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,   11, 15,         CLOCK_03_55,0,0,    CLOCK_10_15,0,0,    CLOCK_11_15,1,0 },      //[35]      [11:15] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,   12, 45,         CLOCK_09_00,0,0,    CLOCK_01_45,0,0,    CLOCK_00_45,1,0 },      //[36]      [12:45] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,    1, 45,         CLOCK_01_45,1,0,    CLOCK_02_45,0,0,    CLOCK_09_05,0,0 },      //[37]      [ 1:45] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,    2, 45,         CLOCK_03_45,0,0,    CLOCK_02_45,1,0,    CLOCK_09_10,0,0 },      //[38]      [ 2:45] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,    3, 45,         CLOCK_09_15,0,0,    CLOCK_04_45,0,0,    CLOCK_03_45,1,0 },      //[39]      [ 3:45] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,    4, 45,         CLOCK_04_45,1,0,    CLOCK_05_45,0,0,    CLOCK_09_20,0,0 },      //[40]      [ 4:45] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,    5, 45,         CLOCK_06_45,0,0,    CLOCK_05_45,1,0,    CLOCK_08_25,0,0 },      //[41]      [ 5:45] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,    6, 45,         CLOCK_08_30,0,0,    CLOCK_07_45,0,0,    CLOCK_06_45,1,0 },      //[42]      [ 6:45] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,    7, 45,         CLOCK_07_45,1,0,    CLOCK_06_45,0,0,    CLOCK_08_35,0,0 },      //[43]      [ 7:45] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,    8, 45,         CLOCK_09_45,0,0,    CLOCK_08_45,1,0,    CLOCK_08_40,0,0 },      //[44]      [ 8:45] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,    9, 45,         CLOCK_08_45,0,0,    CLOCK_10_45,0,0,    CLOCK_09_45,1,0 },      //[45]      [ 9:45] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,   10, 45,         CLOCK_10_45,1,0,    CLOCK_09_45,0,0,    CLOCK_08_50,0,0 },      //[46]      [10:45] の とき時計の針はどこをさしていますか？
    {   QUESTION_TEXT_04,   11, 45,         CLOCK_00_45,0,0,    CLOCK_11_45,1,0,    CLOCK_08_55,0,0 },      //[47]      [11:45] の とき時計の針はどこをさしていますか？
};

//問題データ＆選択肢／質問種類５
static QUESTION_TEXT_05_DATA QuestionText05_Data[]=
{
    //  種類                問題文の数値    選択する答え
    //----[ LEVEL-1 ]--------------------------------------------------------------------------------------------------------
    {   QUESTION_TEXT_05,   1,  1,           1,0,0,     -1,1,0,      1,0,1  },  //[ 0]      [ 1]-[ 1] どちらが多いですか？
    {   QUESTION_TEXT_05,   1,  2,           1,0,0,     -1,0,0,      2,1,1  },  //[ 1]      [ 1]-[ 2] どちらが多いですか？
    {   QUESTION_TEXT_05,   2,  2,           2,0,0,     -1,1,0,      2,0,1  },  //[ 2]      [ 2]-[ 2] どちらが多いですか？
    {   QUESTION_TEXT_05,   2,  3,           2,0,0,     -1,0,0,      3,1,1  },  //[ 3]      [ 2]-[ 3] どちらが多いですか？
    {   QUESTION_TEXT_05,   3,  3,           3,0,0,     -1,1,0,      3,0,1  },  //[ 4]      [ 3]-[ 3] どちらが多いですか？
    {   QUESTION_TEXT_05,   3,  4,           3,0,0,     -1,0,0,      4,1,1  },  //[ 5]      [ 3]-[ 4] どちらが多いですか？
    {   QUESTION_TEXT_05,   4,  4,           4,0,0,     -1,1,0,      4,0,1  },  //[ 6]      [ 4]-[ 4] どちらが多いですか？
    {   QUESTION_TEXT_05,   4,  5,           4,0,0,     -1,0,0,      5,1,1  },  //[ 7]      [ 4]-[ 5] どちらが多いですか？
    {   QUESTION_TEXT_05,   5,  5,           5,0,0,     -1,1,0,      5,0,1  },  //[ 8]      [ 5]-[ 5] どちらが多いですか？
    {   QUESTION_TEXT_05,   5,  6,           5,0,0,     -1,0,0,      6,1,1  },  //[ 9]      [ 5]-[ 6] どちらが多いですか？
    {   QUESTION_TEXT_05,   6,  6,           6,0,0,     -1,1,0,      6,0,1  },  //[10]      [ 6]-[ 6] どちらが多いですか？
    {   QUESTION_TEXT_05,   6,  7,           6,0,0,     -1,0,0,      7,1,1  },  //[11]      [ 6]-[ 7] どちらが多いですか？
    {   QUESTION_TEXT_05,   7,  7,           7,0,0,     -1,1,0,      7,0,1  },  //[12]      [ 7]-[ 7] どちらが多いですか？
    {   QUESTION_TEXT_05,   7,  8,           7,0,0,     -1,0,0,      8,1,1  },  //[13]      [ 7]-[ 8] どちらが多いですか？
    {   QUESTION_TEXT_05,   8,  8,           8,0,0,     -1,1,0,      8,0,1  },  //[14]      [ 8]-[ 8] どちらが多いですか？
    {   QUESTION_TEXT_05,   8,  9,           8,0,0,     -1,0,0,      9,1,1  },  //[15]      [ 8]-[ 9] どちらが多いですか？
    {   QUESTION_TEXT_05,   9,  9,           9,0,0,     -1,1,0,      9,0,1  },  //[16]      [ 9]-[ 9] どちらが多いですか？
    {   QUESTION_TEXT_05,   9,  10,          9,0,0,     -1,0,0,     10,1,1  },  //[17]      [ 9]-[10] どちらが多いですか？
    {   QUESTION_TEXT_05,   10, 10,         10,0,0,     -1,1,0,     10,0,1  },  //[18]      [10]-[10] どちらが多いですか？
};


//問題データ＆選択肢／質問種類６
static QUESTION_TEXT_06_DATA QuestionText06_Data[]=
{
    //  種類                問題文の数値    選択する答え
    //----[ LEVEL-3 ]--------------------------------------------------------------------------------------------------------
    {   QUESTION_TEXT_06,   10, 11,         10,0,0,     -1,0,0,     11,1,1  },  //[ 0]      [10]-[11] どちらが多いですか？
    {   QUESTION_TEXT_06,   11, 11,         11,0,0,     -1,1,0,     11,0,1  },  //[ 1]      [11]-[11] どちらが多いですか？
    {   QUESTION_TEXT_06,   11, 12,         11,0,0,     -1,0,0,     12,1,1  },  //[ 2]      [11]-[12] どちらが多いですか？
    {   QUESTION_TEXT_06,   12, 12,         12,0,0,     -1,1,0,     12,0,1  },  //[ 3]      [12]-[12] どちらが多いですか？
    {   QUESTION_TEXT_06,   12, 13,         12,0,0,     -1,0,0,     13,1,1  },  //[ 4]      [12]-[13] どちらが多いですか？
    {   QUESTION_TEXT_06,   13, 13,         13,0,0,     -1,1,0,     13,0,1  },  //[ 5]      [13]-[13] どちらが多いですか？
    {   QUESTION_TEXT_06,   13, 14,         13,0,0,     -1,0,0,     14,1,1  },  //[ 6]      [13]-[14] どちらが多いですか？
    {   QUESTION_TEXT_06,   14, 14,         14,0,0,     -1,1,0,     14,0,1  },  //[ 7]      [14]-[14] どちらが多いですか？
    {   QUESTION_TEXT_06,   14, 15,         14,0,0,     -1,0,0,     15,1,1  },  //[ 8]      [14]-[15] どちらが多いですか？
    {   QUESTION_TEXT_06,   15, 15,         15,0,0,     -1,1,0,     15,0,1  },  //[ 9]      [15]-[15] どちらが多いですか？
    {   QUESTION_TEXT_06,   15, 16,         15,0,0,     -1,0,0,     16,1,1  },  //[10]      [15]-[16] どちらが多いですか？
    {   QUESTION_TEXT_06,   16, 16,         16,0,0,     -1,1,0,     16,0,1  },  //[11]      [16]-[16] どちらが多いですか？
    {   QUESTION_TEXT_06,   16, 17,         16,0,0,     -1,0,0,     17,1,1  },  //[12]      [16]-[17] どちらが多いですか？
    {   QUESTION_TEXT_06,   17, 17,         17,0,0,     -1,1,0,     17,0,1  },  //[13]      [17]-[17] どちらが多いですか？
    {   QUESTION_TEXT_06,   17, 18,         17,0,0,     -1,0,0,     18,1,1  },  //[14]      [17]-[18] どちらが多いですか？
    {   QUESTION_TEXT_06,   18, 18,         18,0,0,     -1,1,0,     18,0,1  },  //[15]      [18]-[18] どちらが多いですか？
    {   QUESTION_TEXT_06,   18, 19,         18,0,0,     -1,0,0,     19,1,1  },  //[16]      [18]-[19] どちらが多いですか？
    {   QUESTION_TEXT_06,   19, 19,         19,0,0,     -1,1,0,     19,0,1  },  //[17]      [19]-[19] どちらが多いですか？
    {   QUESTION_TEXT_06,   19, 20,         19,0,0,     -1,0,0,     20,1,1  },  //[18]      [19]-[20] どちらが多いですか？
    {   QUESTION_TEXT_06,   20, 20,         20,0,0,     -1,1,0,     20,0,1  },  //[19]      [20]-[20] どちらが多いですか？
};


//-------- クイズデータ
//  LEVEL-1
//      QUESTION_TEXT_00_DATA   00-13   /   □に入るのはなんですか？
//      QUESTION_TEXT_01_DATA   00-24   /   １と３でいくつになりますか？
//      QUESTION_TEXT_03_DATA   00-23   /   １じのときとけいのはりはどこをさしていますか？
//      QUESTION_TEXT_05_DATA   00-18   /   どちらがおおいですか？　(くだもの比べ)
//  
//  LEVEL-2
//      QUESTION_TEXT_00_DATA   14-29   /   □に入るのはなんですか？
//      QUESTION_TEXT_01_DATA   25-64   /   １と３でいくつになりますか？
//      QUESTION_TEXT_02_DATA   00-34   /   ２は１といくつですか？
//      QUESTION_TEXT_04_DATA   00-23   /   １じ３０ぷんのときとけいのはりはどこをさしていますか？
//  
//  LEVEL-3
//      QUESTION_TEXT_00_DATA   30-54   /   □に入るのはなんですか？
//      QUESTION_TEXT_02_DATA   35-64   /   ２は１といくつですか？
//      QUESTION_TEXT_04_DATA   24-47   /   １じ１５ぷんのときとけいのはりはどこをさしていますか？
//      QUESTION_TEXT_06_DATA   00-19   /   どちらがおおいですか？　(パネルの数字比べ)


//--------サイズ
#define QUESTION_TEXT_00_NUM    GET_ARRAY_SIZE (QuestionText00_Data)
#define QUESTION_TEXT_01_NUM    GET_ARRAY_SIZE (QuestionText01_Data)
#define QUESTION_TEXT_02_NUM    GET_ARRAY_SIZE (QuestionText02_Data)
#define QUESTION_TEXT_03_NUM    GET_ARRAY_SIZE (QuestionText03_Data)
#define QUESTION_TEXT_04_NUM    GET_ARRAY_SIZE (QuestionText04_Data)
#define QUESTION_TEXT_05_NUM    GET_ARRAY_SIZE (QuestionText05_Data)
#define QUESTION_TEXT_06_NUM    GET_ARRAY_SIZE (QuestionText06_Data)


//--------問題数
#ifdef __DEBUG_ALL_QUESTION_AIR__
    //デバッグ
    #define MAX_QUESTION_CLEAR_NUM          10
    #define MAX_QUESTION_NUM                300

#else
    //ゲーム本番
    #define MAX_QUESTION_CLEAR_NUM          10
    #define MAX_QUESTION_NUM                10
#endif



#ifdef __DEBUG_ALL_QUESTION_AIR__
//---------------------------------- 質問全体デバッグ用

static QUESTION_TOP_DATA QuestionTopData[1][1][MAX_QUESTION_NUM]=
{
    {//LEVEL-1
        {//--Num_0
            {   QUESTION_TEXT_00,   0   },  //TEXT-00
            {   QUESTION_TEXT_00,   1   },
            {   QUESTION_TEXT_00,   2   },
            {   QUESTION_TEXT_00,   3   },
            {   QUESTION_TEXT_00,   4   },
            {   QUESTION_TEXT_00,   5   },
            {   QUESTION_TEXT_00,   6   },
            {   QUESTION_TEXT_00,   7   },
            {   QUESTION_TEXT_00,   8   },
            {   QUESTION_TEXT_00,   9   },
            {   QUESTION_TEXT_00,   10  },
            {   QUESTION_TEXT_00,   11  },
            {   QUESTION_TEXT_00,   12  },
            {   QUESTION_TEXT_00,   13  },
            {   QUESTION_TEXT_00,   14  },
            {   QUESTION_TEXT_00,   15  },
            {   QUESTION_TEXT_00,   16  },
            {   QUESTION_TEXT_00,   17  },
            {   QUESTION_TEXT_00,   18  },
            {   QUESTION_TEXT_00,   19  },
            {   QUESTION_TEXT_00,   20  },
            {   QUESTION_TEXT_00,   21  },
            {   QUESTION_TEXT_00,   22  },
            {   QUESTION_TEXT_00,   23  },
            {   QUESTION_TEXT_00,   24  },
            {   QUESTION_TEXT_00,   25  },
            {   QUESTION_TEXT_00,   26  },
            {   QUESTION_TEXT_00,   27  },
            {   QUESTION_TEXT_00,   28  },
            {   QUESTION_TEXT_00,   29  },
            {   QUESTION_TEXT_00,   30  },
            {   QUESTION_TEXT_00,   31  },
            {   QUESTION_TEXT_00,   32  },
            {   QUESTION_TEXT_00,   33  },
            {   QUESTION_TEXT_00,   34  },
            {   QUESTION_TEXT_00,   35  },
            {   QUESTION_TEXT_00,   36  },
            {   QUESTION_TEXT_00,   37  },
            {   QUESTION_TEXT_00,   38  },
            {   QUESTION_TEXT_00,   39  },
            {   QUESTION_TEXT_00,   40  },
            {   QUESTION_TEXT_00,   41  },
            {   QUESTION_TEXT_00,   42  },
            {   QUESTION_TEXT_00,   43  },
            {   QUESTION_TEXT_00,   44  },
            {   QUESTION_TEXT_00,   45  },
            {   QUESTION_TEXT_00,   46  },
            {   QUESTION_TEXT_00,   47  },
            {   QUESTION_TEXT_00,   48  },
            {   QUESTION_TEXT_00,   49  },
            {   QUESTION_TEXT_00,   50  },
            {   QUESTION_TEXT_00,   51  },
            {   QUESTION_TEXT_00,   52  },
            {   QUESTION_TEXT_00,   53  },
            {   QUESTION_TEXT_00,   54  },
            {   QUESTION_TEXT_01,   0   },  //TEXT-01
            {   QUESTION_TEXT_01,   1   },
            {   QUESTION_TEXT_01,   2   },
            {   QUESTION_TEXT_01,   3   },
            {   QUESTION_TEXT_01,   4   },
            {   QUESTION_TEXT_01,   5   },
            {   QUESTION_TEXT_01,   6   },
            {   QUESTION_TEXT_01,   7   },
            {   QUESTION_TEXT_01,   8   },
            {   QUESTION_TEXT_01,   9   },
            {   QUESTION_TEXT_01,   10  },
            {   QUESTION_TEXT_01,   11  },
            {   QUESTION_TEXT_01,   12  },
            {   QUESTION_TEXT_01,   13  },
            {   QUESTION_TEXT_01,   14  },
            {   QUESTION_TEXT_01,   15  },
            {   QUESTION_TEXT_01,   16  },
            {   QUESTION_TEXT_01,   17  },
            {   QUESTION_TEXT_01,   18  },
            {   QUESTION_TEXT_01,   19  },
            {   QUESTION_TEXT_01,   20  },
            {   QUESTION_TEXT_01,   21  },
            {   QUESTION_TEXT_01,   22  },
            {   QUESTION_TEXT_01,   23  },
            {   QUESTION_TEXT_01,   24  },
            {   QUESTION_TEXT_01,   25  },
            {   QUESTION_TEXT_01,   26  },
            {   QUESTION_TEXT_01,   27  },
            {   QUESTION_TEXT_01,   28  },
            {   QUESTION_TEXT_01,   29  },
            {   QUESTION_TEXT_01,   30  },
            {   QUESTION_TEXT_01,   31  },
            {   QUESTION_TEXT_01,   32  },
            {   QUESTION_TEXT_01,   33  },
            {   QUESTION_TEXT_01,   34  },
            {   QUESTION_TEXT_01,   35  },
            {   QUESTION_TEXT_01,   36  },
            {   QUESTION_TEXT_01,   37  },
            {   QUESTION_TEXT_01,   38  },
            {   QUESTION_TEXT_01,   39  },
            {   QUESTION_TEXT_01,   40  },
            {   QUESTION_TEXT_01,   41  },
            {   QUESTION_TEXT_01,   42  },
            {   QUESTION_TEXT_01,   43  },
            {   QUESTION_TEXT_01,   44  },
            {   QUESTION_TEXT_01,   45  },
            {   QUESTION_TEXT_01,   46  },
            {   QUESTION_TEXT_01,   47  },
            {   QUESTION_TEXT_01,   48  },
            {   QUESTION_TEXT_01,   49  },
            {   QUESTION_TEXT_01,   50  },
            {   QUESTION_TEXT_01,   51  },
            {   QUESTION_TEXT_01,   52  },
            {   QUESTION_TEXT_01,   53  },
            {   QUESTION_TEXT_01,   54  },
            {   QUESTION_TEXT_01,   55  },
            {   QUESTION_TEXT_01,   56  },
            {   QUESTION_TEXT_01,   57  },
            {   QUESTION_TEXT_01,   58  },
            {   QUESTION_TEXT_01,   59  },
            {   QUESTION_TEXT_01,   60  },
            {   QUESTION_TEXT_01,   61  },
            {   QUESTION_TEXT_01,   62  },
            {   QUESTION_TEXT_01,   63  },
            {   QUESTION_TEXT_01,   64  },
            {   QUESTION_TEXT_02,   0   },  //TEXT-02
            {   QUESTION_TEXT_02,   1   },
            {   QUESTION_TEXT_02,   2   },
            {   QUESTION_TEXT_02,   3   },
            {   QUESTION_TEXT_02,   4   },
            {   QUESTION_TEXT_02,   5   },
            {   QUESTION_TEXT_02,   6   },
            {   QUESTION_TEXT_02,   7   },
            {   QUESTION_TEXT_02,   8   },
            {   QUESTION_TEXT_02,   9   },
            {   QUESTION_TEXT_02,   10  },
            {   QUESTION_TEXT_02,   11  },
            {   QUESTION_TEXT_02,   12  },
            {   QUESTION_TEXT_02,   13  },
            {   QUESTION_TEXT_02,   14  },
            {   QUESTION_TEXT_02,   15  },
            {   QUESTION_TEXT_02,   16  },
            {   QUESTION_TEXT_02,   17  },
            {   QUESTION_TEXT_02,   18  },
            {   QUESTION_TEXT_02,   19  },
            {   QUESTION_TEXT_02,   20  },
            {   QUESTION_TEXT_02,   21  },
            {   QUESTION_TEXT_02,   22  },
            {   QUESTION_TEXT_02,   23  },
            {   QUESTION_TEXT_02,   24  },
            {   QUESTION_TEXT_02,   25  },
            {   QUESTION_TEXT_02,   26  },
            {   QUESTION_TEXT_02,   27  },
            {   QUESTION_TEXT_02,   28  },
            {   QUESTION_TEXT_02,   29  },
            {   QUESTION_TEXT_02,   30  },
            {   QUESTION_TEXT_02,   31  },
            {   QUESTION_TEXT_02,   32  },
            {   QUESTION_TEXT_02,   33  },
            {   QUESTION_TEXT_02,   34  },
            {   QUESTION_TEXT_02,   35  },
            {   QUESTION_TEXT_02,   36  },
            {   QUESTION_TEXT_02,   37  },
            {   QUESTION_TEXT_02,   38  },
            {   QUESTION_TEXT_02,   39  },
            {   QUESTION_TEXT_02,   40  },
            {   QUESTION_TEXT_02,   41  },
            {   QUESTION_TEXT_02,   42  },
            {   QUESTION_TEXT_02,   43  },
            {   QUESTION_TEXT_02,   44  },
            {   QUESTION_TEXT_02,   45  },
            {   QUESTION_TEXT_02,   46  },
            {   QUESTION_TEXT_02,   47  },
            {   QUESTION_TEXT_02,   48  },
            {   QUESTION_TEXT_02,   49  },
            {   QUESTION_TEXT_02,   50  },
            {   QUESTION_TEXT_02,   51  },
            {   QUESTION_TEXT_02,   52  },
            {   QUESTION_TEXT_02,   53  },
            {   QUESTION_TEXT_02,   54  },
            {   QUESTION_TEXT_02,   55  },
            {   QUESTION_TEXT_02,   56  },
            {   QUESTION_TEXT_02,   57  },
            {   QUESTION_TEXT_02,   58  },
            {   QUESTION_TEXT_02,   59  },
            {   QUESTION_TEXT_02,   60  },
            {   QUESTION_TEXT_02,   61  },
            {   QUESTION_TEXT_02,   62  },
            {   QUESTION_TEXT_02,   63  },
            {   QUESTION_TEXT_02,   64  },
            {   QUESTION_TEXT_03,   0   },//TEXT-03
            {   QUESTION_TEXT_03,   1   },
            {   QUESTION_TEXT_03,   2   },
            {   QUESTION_TEXT_03,   3   },
            {   QUESTION_TEXT_03,   4   },
            {   QUESTION_TEXT_03,   5   },
            {   QUESTION_TEXT_03,   6   },
            {   QUESTION_TEXT_03,   7   },
            {   QUESTION_TEXT_03,   8   },
            {   QUESTION_TEXT_03,   9   },
            {   QUESTION_TEXT_03,   10  },
            {   QUESTION_TEXT_03,   11  },
            {   QUESTION_TEXT_03,   12  },
            {   QUESTION_TEXT_03,   13  },
            {   QUESTION_TEXT_03,   14  },
            {   QUESTION_TEXT_03,   15  },
            {   QUESTION_TEXT_03,   16  },
            {   QUESTION_TEXT_03,   17  },
            {   QUESTION_TEXT_03,   18  },
            {   QUESTION_TEXT_03,   19  },
            {   QUESTION_TEXT_03,   20  },
            {   QUESTION_TEXT_03,   21  },
            {   QUESTION_TEXT_03,   22  },
            {   QUESTION_TEXT_03,   23  },
            {   QUESTION_TEXT_04,   0   },  //TEXT-04
            {   QUESTION_TEXT_04,   1   },
            {   QUESTION_TEXT_04,   2   },
            {   QUESTION_TEXT_04,   3   },
            {   QUESTION_TEXT_04,   4   },
            {   QUESTION_TEXT_04,   5   },
            {   QUESTION_TEXT_04,   6   },
            {   QUESTION_TEXT_04,   7   },
            {   QUESTION_TEXT_04,   8   },
            {   QUESTION_TEXT_04,   9   },
            {   QUESTION_TEXT_04,   10  },
            {   QUESTION_TEXT_04,   11  },
            {   QUESTION_TEXT_04,   12  },
            {   QUESTION_TEXT_04,   13  },
            {   QUESTION_TEXT_04,   14  },
            {   QUESTION_TEXT_04,   15  },
            {   QUESTION_TEXT_04,   16  },
            {   QUESTION_TEXT_04,   17  },
            {   QUESTION_TEXT_04,   18  },
            {   QUESTION_TEXT_04,   19  },
            {   QUESTION_TEXT_04,   20  },
            {   QUESTION_TEXT_04,   21  },
            {   QUESTION_TEXT_04,   22  },
            {   QUESTION_TEXT_04,   23  },
            {   QUESTION_TEXT_04,   24  },
            {   QUESTION_TEXT_04,   25  },
            {   QUESTION_TEXT_04,   26  },
            {   QUESTION_TEXT_04,   27  },
            {   QUESTION_TEXT_04,   28  },
            {   QUESTION_TEXT_04,   29  },
            {   QUESTION_TEXT_04,   30  },
            {   QUESTION_TEXT_04,   31  },
            {   QUESTION_TEXT_04,   32  },
            {   QUESTION_TEXT_04,   33  },
            {   QUESTION_TEXT_04,   34  },
            {   QUESTION_TEXT_04,   35  },
            {   QUESTION_TEXT_04,   36  },
            {   QUESTION_TEXT_04,   37  },
            {   QUESTION_TEXT_04,   38  },
            {   QUESTION_TEXT_04,   39  },
            {   QUESTION_TEXT_04,   40  },
            {   QUESTION_TEXT_04,   41  },
            {   QUESTION_TEXT_04,   42  },
            {   QUESTION_TEXT_04,   43  },
            {   QUESTION_TEXT_04,   44  },
            {   QUESTION_TEXT_04,   45  },
            {   QUESTION_TEXT_04,   46  },
            {   QUESTION_TEXT_04,   47  },
            {   QUESTION_TEXT_05,   0   },  // TEXT-05
            {   QUESTION_TEXT_05,   1   },
            {   QUESTION_TEXT_05,   2   },
            {   QUESTION_TEXT_05,   3   },
            {   QUESTION_TEXT_05,   4   },
            {   QUESTION_TEXT_05,   5   },
            {   QUESTION_TEXT_05,   6   },
            {   QUESTION_TEXT_05,   7   },
            {   QUESTION_TEXT_05,   8   },
            {   QUESTION_TEXT_05,   9   },
            {   QUESTION_TEXT_05,   10  },
            {   QUESTION_TEXT_05,   11  },
            {   QUESTION_TEXT_05,   12  },
            {   QUESTION_TEXT_05,   13  },
            {   QUESTION_TEXT_05,   14  },
            {   QUESTION_TEXT_05,   15  },
            {   QUESTION_TEXT_05,   16  },
            {   QUESTION_TEXT_05,   17  },
            {   QUESTION_TEXT_05,   18  },
            {   QUESTION_TEXT_06,   0   },  //TEXT-06
            {   QUESTION_TEXT_06,   1   },
            {   QUESTION_TEXT_06,   2   },
            {   QUESTION_TEXT_06,   3   },
            {   QUESTION_TEXT_06,   4   },
            {   QUESTION_TEXT_06,   5   },
            {   QUESTION_TEXT_06,   6   },
            {   QUESTION_TEXT_06,   7   },
            {   QUESTION_TEXT_06,   8   },
            {   QUESTION_TEXT_06,   9   },
            {   QUESTION_TEXT_06,   10  },
            {   QUESTION_TEXT_06,   11  },
            {   QUESTION_TEXT_06,   12  },
            {   QUESTION_TEXT_06,   13  },
            {   QUESTION_TEXT_06,   14  },
            {   QUESTION_TEXT_06,   15  },
            {   QUESTION_TEXT_06,   16  },
            {   QUESTION_TEXT_06,   17  },
            {   QUESTION_TEXT_06,   18  },
            {   QUESTION_TEXT_06,   19  },
            {   QUESTION_TEXT_00,   0   },
            {   QUESTION_TEXT_00,   0   },
            {   QUESTION_TEXT_00,   0   },
            {   QUESTION_TEXT_00,   0   },
        },
    },
};


#else


//----------------------------------ゲーム本番用
//各レベル１０題
static QUESTION_TOP_DATA QuestionTopData[AIR_GAME_MAX_LEVEL_NUM][AIR_GAME_MAX_KIND_NUM][10]=
{
    {//----level1
        {//Num-1
            {   QUESTION_TEXT_00,   0   },
            {   QUESTION_TEXT_01,   2   },
            {   QUESTION_TEXT_00,   2   },
            {   QUESTION_TEXT_05,   0   },
            {   QUESTION_TEXT_01,   0   },
            {   QUESTION_TEXT_03,   0   },
            {   QUESTION_TEXT_00,   1   },
            {   QUESTION_TEXT_01,   1   },
            {   QUESTION_TEXT_03,   1   },
            {   QUESTION_TEXT_05,   1   },
        },
        {//Num-2
            {   QUESTION_TEXT_00,   3   },
            {   QUESTION_TEXT_05,   3   },
            {   QUESTION_TEXT_00,   4   },
            {   QUESTION_TEXT_01,   3   },
            {   QUESTION_TEXT_05,   2   },
            {   QUESTION_TEXT_03,   2   },
            {   QUESTION_TEXT_01,   4   },
            {   QUESTION_TEXT_03,   3   },
            {   QUESTION_TEXT_00,   5   },
            {   QUESTION_TEXT_01,   5   },
        },
        {//Num-3
            {   QUESTION_TEXT_00,   7   },
            {   QUESTION_TEXT_03,   4   },
            {   QUESTION_TEXT_00,   6   },
            {   QUESTION_TEXT_05,   5   },
            {   QUESTION_TEXT_01,   7   },
            {   QUESTION_TEXT_00,   8   },
            {   QUESTION_TEXT_01,   6   },
            {   QUESTION_TEXT_05,   4   },
            {   QUESTION_TEXT_01,   8   },
            {   QUESTION_TEXT_03,   5   },
        },
        {//Num-4
            {   QUESTION_TEXT_00,   9   },
            {   QUESTION_TEXT_05,   7   },
            {   QUESTION_TEXT_00,   11  },
            {   QUESTION_TEXT_01,   9   },
            {   QUESTION_TEXT_03,   7   },
            {   QUESTION_TEXT_01,   11  },
            {   QUESTION_TEXT_03,   6   },
            {   QUESTION_TEXT_00,   10  },
            {   QUESTION_TEXT_05,   6   },
            {   QUESTION_TEXT_01,   10  },
        },
        {//Num-5
            {   QUESTION_TEXT_00,   12  },
            {   QUESTION_TEXT_03,   8   },
            {   QUESTION_TEXT_01,   12  },
            {   QUESTION_TEXT_00,   13  },
            {   QUESTION_TEXT_05,   8   },
            {   QUESTION_TEXT_00,   0   },
            {   QUESTION_TEXT_01,   14  },
            {   QUESTION_TEXT_03,   9   },
            {   QUESTION_TEXT_05,   9   },
            {   QUESTION_TEXT_01,   13  },
        },
        {//Num-6
            {   QUESTION_TEXT_00,   1   },
            {   QUESTION_TEXT_03,   11  },
            {   QUESTION_TEXT_05,   10  },
            {   QUESTION_TEXT_01,   15  },
            {   QUESTION_TEXT_00,   2   },
            {   QUESTION_TEXT_01,   16  },
            {   QUESTION_TEXT_00,   3   },
            {   QUESTION_TEXT_01,   17  },
            {   QUESTION_TEXT_03,   10  },
            {   QUESTION_TEXT_05,   11  },
        },
        {//Num-7
            {   QUESTION_TEXT_00,   4   },
            {   QUESTION_TEXT_01,   19  },
            {   QUESTION_TEXT_00,   6   },
            {   QUESTION_TEXT_01,   18  },
            {   QUESTION_TEXT_05,   13  },
            {   QUESTION_TEXT_01,   20  },
            {   QUESTION_TEXT_03,   12  },
            {   QUESTION_TEXT_00,   5   },
            {   QUESTION_TEXT_03,   13  },
            {   QUESTION_TEXT_05,   12  },
        },
        {//Num-8
            {   QUESTION_TEXT_00,   7   },
            {   QUESTION_TEXT_05,   15  },
            {   QUESTION_TEXT_00,   8   },
            {   QUESTION_TEXT_01,   22  },
            {   QUESTION_TEXT_00,   9   },
            {   QUESTION_TEXT_01,   21  },
            {   QUESTION_TEXT_03,   15  },
            {   QUESTION_TEXT_01,   23  },
            {   QUESTION_TEXT_03,   14  },
            {   QUESTION_TEXT_05,   14  },
        },
        {//Num-9
            {   QUESTION_TEXT_00,   10  },
            {   QUESTION_TEXT_03,   16  },
            {   QUESTION_TEXT_00,   12  },
            {   QUESTION_TEXT_01,   24  },
            {   QUESTION_TEXT_00,   11  },
            {   QUESTION_TEXT_05,   16  },
            {   QUESTION_TEXT_01,   0   },
            {   QUESTION_TEXT_03,   17  },
            {   QUESTION_TEXT_05,   17  },
            {   QUESTION_TEXT_01,   1   },
        },
        {//Num-10
            {   QUESTION_TEXT_00,   13  },
            {   QUESTION_TEXT_01,   2   },
            {   QUESTION_TEXT_00,   0   },
            {   QUESTION_TEXT_05,   0   },
            {   QUESTION_TEXT_00,   1   },
            {   QUESTION_TEXT_05,   18  },
            {   QUESTION_TEXT_01,   4   },
            {   QUESTION_TEXT_03,   18  },
            {   QUESTION_TEXT_01,   3   },
            {   QUESTION_TEXT_03,   19  },
        },
    },
    {//----level2
        {//Num-1
            {   QUESTION_TEXT_00,   14  },
            {   QUESTION_TEXT_01,   25  },
            {   QUESTION_TEXT_04,   1   },
            {   QUESTION_TEXT_02,   1   },
            {   QUESTION_TEXT_00,   15  },
            {   QUESTION_TEXT_01,   26  },
            {   QUESTION_TEXT_02,   0   },
            {   QUESTION_TEXT_01,   27  },
            {   QUESTION_TEXT_04,   0   },
            {   QUESTION_TEXT_00,   16  },
        },
        {//Num-2
            {   QUESTION_TEXT_00,   17  },
            {   QUESTION_TEXT_02,   3   },
            {   QUESTION_TEXT_00,   19  },
            {   QUESTION_TEXT_01,   29  },
            {   QUESTION_TEXT_04,   3   },
            {   QUESTION_TEXT_01,   30  },
            {   QUESTION_TEXT_04,   2   },
            {   QUESTION_TEXT_02,   2   },
            {   QUESTION_TEXT_00,   18  },
            {   QUESTION_TEXT_01,   28  },
        },
        {//Num-3
            {   QUESTION_TEXT_00,   20  },
            {   QUESTION_TEXT_04,   5   },
            {   QUESTION_TEXT_01,   33  },
            {   QUESTION_TEXT_00,   22  },
            {   QUESTION_TEXT_01,   31  },
            {   QUESTION_TEXT_02,   4   },
            {   QUESTION_TEXT_01,   32  },
            {   QUESTION_TEXT_04,   4   },
            {   QUESTION_TEXT_00,   21  },
            {   QUESTION_TEXT_02,   5   },
        },
        {//Num-4
            {   QUESTION_TEXT_00,   23  },
            {   QUESTION_TEXT_02,   6   },
            {   QUESTION_TEXT_04,   6   },
            {   QUESTION_TEXT_00,   24  },
            {   QUESTION_TEXT_01,   34  },
            {   QUESTION_TEXT_02,   7   },
            {   QUESTION_TEXT_01,   36  },
            {   QUESTION_TEXT_00,   25  },
            {   QUESTION_TEXT_01,   35  },
            {   QUESTION_TEXT_04,   7   },
        },
        {//Num-5
            {   QUESTION_TEXT_00,   26  },
            {   QUESTION_TEXT_01,   37  },
            {   QUESTION_TEXT_04,   9   },
            {   QUESTION_TEXT_00,   27  },
            {   QUESTION_TEXT_01,   39  },
            {   QUESTION_TEXT_00,   28  },
            {   QUESTION_TEXT_02,   8   },
            {   QUESTION_TEXT_04,   8   },
            {   QUESTION_TEXT_02,   9   },
            {   QUESTION_TEXT_01,   38  },
        },
        {//Num-6
            {   QUESTION_TEXT_00,   29  },
            {   QUESTION_TEXT_02,   10  },
            {   QUESTION_TEXT_00,   15  },
            {   QUESTION_TEXT_01,   40  },
            {   QUESTION_TEXT_00,   14  },
            {   QUESTION_TEXT_04,   10  },
            {   QUESTION_TEXT_01,   41  },
            {   QUESTION_TEXT_04,   11  },
            {   QUESTION_TEXT_01,   42  },
            {   QUESTION_TEXT_02,   11  },
        },
        {//Num-7
            {   QUESTION_TEXT_01,   43  },
            {   QUESTION_TEXT_02,   12  },
            {   QUESTION_TEXT_01,   45  },
            {   QUESTION_TEXT_00,   16  },
            {   QUESTION_TEXT_04,   13  },
            {   QUESTION_TEXT_00,   17  },
            {   QUESTION_TEXT_04,   12  },
            {   QUESTION_TEXT_00,   18  },
            {   QUESTION_TEXT_01,   44  },
            {   QUESTION_TEXT_02,   13  },
        },
        {//Num-8
            {   QUESTION_TEXT_00,   21  },
            {   QUESTION_TEXT_04,   14  },
            {   QUESTION_TEXT_00,   20  },
            {   QUESTION_TEXT_01,   48  },
            {   QUESTION_TEXT_02,   15  },
            {   QUESTION_TEXT_01,   46  },
            {   QUESTION_TEXT_00,   19  },
            {   QUESTION_TEXT_01,   47  },
            {   QUESTION_TEXT_02,   14  },
            {   QUESTION_TEXT_04,   15  },
        },
        {//Num-9
            {   QUESTION_TEXT_00,   22  },
            {   QUESTION_TEXT_01,   49  },
            {   QUESTION_TEXT_00,   23  },
            {   QUESTION_TEXT_02,   17  },
            {   QUESTION_TEXT_01,   50  },
            {   QUESTION_TEXT_04,   16  },
            {   QUESTION_TEXT_00,   24  },
            {   QUESTION_TEXT_01,   51  },
            {   QUESTION_TEXT_02,   16  },
            {   QUESTION_TEXT_04,   17  },
        },
        {//Num-10
            {   QUESTION_TEXT_00,   25  },
            {   QUESTION_TEXT_02,   19  },
            {   QUESTION_TEXT_04,   18  },
            {   QUESTION_TEXT_00,   27  },
            {   QUESTION_TEXT_01,   52  },
            {   QUESTION_TEXT_00,   26  },
            {   QUESTION_TEXT_01,   53  },
            {   QUESTION_TEXT_02,   18  },
            {   QUESTION_TEXT_01,   54  },
            {   QUESTION_TEXT_04,   19  },
        },
    },
    {//----level3
        {//Num-1
            {   QUESTION_TEXT_00,   30  },
            {   QUESTION_TEXT_02,   35  },
            {   QUESTION_TEXT_04,   25  },
            {   QUESTION_TEXT_00,   31  },
            {   QUESTION_TEXT_02,   36  },
            {   QUESTION_TEXT_06,   0   },
            {   QUESTION_TEXT_00,   32  },
            {   QUESTION_TEXT_02,   37  },
            {   QUESTION_TEXT_04,   24  },
            {   QUESTION_TEXT_06,   1   },
        },
        {//Num-2
            {   QUESTION_TEXT_00,   34  },
            {   QUESTION_TEXT_02,   38  },
            {   QUESTION_TEXT_00,   35  },
            {   QUESTION_TEXT_06,   2   },
            {   QUESTION_TEXT_02,   39  },
            {   QUESTION_TEXT_04,   26  },
            {   QUESTION_TEXT_02,   40  },
            {   QUESTION_TEXT_00,   33  },
            {   QUESTION_TEXT_04,   27  },
            {   QUESTION_TEXT_06,   3   },
        },
        {//Num-3
            {   QUESTION_TEXT_00,   36  },
            {   QUESTION_TEXT_02,   41  },
            {   QUESTION_TEXT_06,   4   },
            {   QUESTION_TEXT_00,   37  },
            {   QUESTION_TEXT_02,   43  },
            {   QUESTION_TEXT_06,   5   },
            {   QUESTION_TEXT_02,   42  },
            {   QUESTION_TEXT_04,   28  },
            {   QUESTION_TEXT_00,   38  },
            {   QUESTION_TEXT_04,   29  },
        },
        {//Num-4
            {   QUESTION_TEXT_00,   39  },
            {   QUESTION_TEXT_04,   31  },
            {   QUESTION_TEXT_00,   41  },
            {   QUESTION_TEXT_02,   44  },
            {   QUESTION_TEXT_06,   6   },
            {   QUESTION_TEXT_00,   40  },
            {   QUESTION_TEXT_02,   46  },
            {   QUESTION_TEXT_04,   30  },
            {   QUESTION_TEXT_02,   45  },
            {   QUESTION_TEXT_06,   7   },
        },
        {//Num-5
            {   QUESTION_TEXT_00,   42  },
            {   QUESTION_TEXT_02,   47  },
            {   QUESTION_TEXT_06,   8   },
            {   QUESTION_TEXT_02,   49  },
            {   QUESTION_TEXT_00,   43  },
            {   QUESTION_TEXT_02,   48  },
            {   QUESTION_TEXT_04,   32  },
            {   QUESTION_TEXT_00,   44  },
            {   QUESTION_TEXT_06,   9   },
            {   QUESTION_TEXT_04,   33  },
        },
        {//Num-6
            {   QUESTION_TEXT_00,   45  },
            {   QUESTION_TEXT_06,   11  },
            {   QUESTION_TEXT_04,   35  },
            {   QUESTION_TEXT_00,   47  },
            {   QUESTION_TEXT_02,   50  },
            {   QUESTION_TEXT_00,   46  },
            {   QUESTION_TEXT_02,   51  },
            {   QUESTION_TEXT_04,   34  },
            {   QUESTION_TEXT_06,   10  },
            {   QUESTION_TEXT_02,   52  },
        },
        {//Num-7
            {   QUESTION_TEXT_00,   48  },
            {   QUESTION_TEXT_06,   12  },
            {   QUESTION_TEXT_00,   50  },
            {   QUESTION_TEXT_02,   54  },
            {   QUESTION_TEXT_00,   49  },
            {   QUESTION_TEXT_02,   55  },
            {   QUESTION_TEXT_04,   36  },
            {   QUESTION_TEXT_02,   53  },
            {   QUESTION_TEXT_04,   37  },
            {   QUESTION_TEXT_06,   13  },
        },
        {//Num-8
            {   QUESTION_TEXT_00,   51  },
            {   QUESTION_TEXT_06,   14  },
            {   QUESTION_TEXT_00,   53  },
            {   QUESTION_TEXT_02,   57  },
            {   QUESTION_TEXT_00,   52  },
            {   QUESTION_TEXT_04,   39  },
            {   QUESTION_TEXT_02,   58  },
            {   QUESTION_TEXT_06,   15  },
            {   QUESTION_TEXT_02,   56  },
            {   QUESTION_TEXT_04,   38  },
        },
        {//Num-9
            {   QUESTION_TEXT_00,   54  },
            {   QUESTION_TEXT_06,   17  },
            {   QUESTION_TEXT_00,   31  },
            {   QUESTION_TEXT_02,   59  },
            {   QUESTION_TEXT_00,   30  },
            {   QUESTION_TEXT_02,   60  },
            {   QUESTION_TEXT_02,   61  },
            {   QUESTION_TEXT_04,   40  },
            {   QUESTION_TEXT_06,   16  },
            {   QUESTION_TEXT_04,   41  },
        },
        {//Num-10
            {   QUESTION_TEXT_00,   32  },
            {   QUESTION_TEXT_06,   19  },
            {   QUESTION_TEXT_02,   64  },
            {   QUESTION_TEXT_00,   34  },
            {   QUESTION_TEXT_06,   18  },
            {   QUESTION_TEXT_02,   62  },
            {   QUESTION_TEXT_02,   63  },
            {   QUESTION_TEXT_04,   42  },
            {   QUESTION_TEXT_00,   33  },
            {   QUESTION_TEXT_04,   43  },
        },
    },
};

#endif

//----------------------------------------------------------------問題XAデータ
//----TEXT01
static XA_DATA QuestionText01_XA_Data[]=
{
    {   XA_FILE_AIR04,  0   },  //[ 0]      [0] と [1] で いくつになりますか？
    {   XA_FILE_AIR04,  1   },  //[ 1]      [0] と [2] で いくつになりますか？
    {   XA_FILE_AIR04,  2   },  //[ 2]      [0] と [3] で いくつになりますか？
    {   XA_FILE_AIR04,  3   },  //[ 3]      [0] と [4] で いくつになりますか？
    {   XA_FILE_AIR04,  4   },  //[ 4]      [0] と [5] で いくつになりますか？
    {   XA_FILE_AIR04,  5   },  //[ 5]      [1] と [0] で いくつになりますか？
    {   XA_FILE_AIR04,  6   },  //[ 6]      [1] と [1] で いくつになりますか？
    {   XA_FILE_AIR04,  7   },  //[ 7]      [1] と [2] で いくつになりますか？
    {   XA_FILE_AIR04,  8   },  //[ 8]      [1] と [3] で いくつになりますか？
    {   XA_FILE_AIR04,  9   },  //[ 9]      [1] と [4] で いくつになりますか？
    {   XA_FILE_AIR04,  10  },  //[10]      [1] と [5] で いくつになりますか？
    {   XA_FILE_AIR04,  11  },  //[11]      [2] と [0] で いくつになりますか？
    {   XA_FILE_AIR04,  12  },  //[12]      [2] と [1] で いくつになりますか？
    {   XA_FILE_AIR04,  13  },  //[13]      [2] と [2] で いくつになりますか？
    {   XA_FILE_AIR04,  14  },  //[14]      [2] と [3] で いくつになりますか？
    {   XA_FILE_AIR04,  15  },  //[15]      [2] と [4] で いくつになりますか？
    {   XA_FILE_AIR05,  0   },  //[16]      [3] と [0] で いくつになりますか？
    {   XA_FILE_AIR05,  1   },  //[17]      [3] と [1] で いくつになりますか？
    {   XA_FILE_AIR05,  2   },  //[18]      [3] と [2] で いくつになりますか？
    {   XA_FILE_AIR05,  3   },  //[19]      [3] と [3] で いくつになりますか？
    {   XA_FILE_AIR05,  4   },  //[20]      [4] と [0] で いくつになりますか？
    {   XA_FILE_AIR05,  5   },  //[21]      [4] と [1] で いくつになりますか？
    {   XA_FILE_AIR05,  6   },  //[22]      [4] と [2] で いくつになりますか？
    {   XA_FILE_AIR05,  7   },  //[23]      [5] と [0] で いくつになりますか？
    {   XA_FILE_AIR05,  8   },  //[24]      [5] と [1] で いくつになりますか？
    {   XA_FILE_AIR06,  0   },  //[25]      [0] と [6] で いくつになりますか？
    {   XA_FILE_AIR06,  1   },  //[26]      [0] と [7] で いくつになりますか？
    {   XA_FILE_AIR06,  2   },  //[27]      [0] と [8] で いくつになりますか？
    {   XA_FILE_AIR06,  3   },  //[28]      [0] と [9] で いくつになりますか？
    {   XA_FILE_AIR06,  4   },  //[29]      [0] と [10] で いくつになりますか？
    {   XA_FILE_AIR06,  5   },  //[30]      [1] と [6] で いくつになりますか？
    {   XA_FILE_AIR06,  6   },  //[31]      [1] と [7] で いくつになりますか？
    {   XA_FILE_AIR06,  7   },  //[32]      [1] と [8] で いくつになりますか？
    {   XA_FILE_AIR06,  8   },  //[33]      [1] と [9] で いくつになりますか？
    {   XA_FILE_AIR06,  9   },  //[34]      [2] と [5] で いくつになりますか？
    {   XA_FILE_AIR06,  10  },  //[35]      [2] と [6] で いくつになりますか？
    {   XA_FILE_AIR06,  11  },  //[36]      [2] と [7] で いくつになりますか？
    {   XA_FILE_AIR06,  12  },  //[37]      [2] と [8] で いくつになりますか？
    {   XA_FILE_AIR06,  13  },  //[38]      [3] と [4] で いくつになりますか？
    {   XA_FILE_AIR06,  14  },  //[39]      [3] と [5] で いくつになりますか？
    {   XA_FILE_AIR06,  15  },  //[40]      [3] と [6] で いくつになりますか？
    {   XA_FILE_AIR07,  0   },  //[41]      [3] と [7] で いくつになりますか？
    {   XA_FILE_AIR07,  1   },  //[42]      [4] と [3] で いくつになりますか？
    {   XA_FILE_AIR07,  2   },  //[43]      [4] と [4] で いくつになりますか？
    {   XA_FILE_AIR07,  3   },  //[44]      [4] と [5] で いくつになりますか？
    {   XA_FILE_AIR07,  4   },  //[45]      [4] と [6] で いくつになりますか？
    {   XA_FILE_AIR07,  5   },  //[46]      [5] と [2] で いくつになりますか？
    {   XA_FILE_AIR07,  6   },  //[47]      [5] と [3] で いくつになりますか？
    {   XA_FILE_AIR07,  7   },  //[48]      [5] と [4] で いくつになりますか？
    {   XA_FILE_AIR07,  8   },  //[49]      [5] と [5] で いくつになりますか？
    {   XA_FILE_AIR07,  9   },  //[50]      [6] と [0] で いくつになりますか？
    {   XA_FILE_AIR07,  10  },  //[51]      [6] と [1] で いくつになりますか？
    {   XA_FILE_AIR07,  11  },  //[52]      [6] と [2] で いくつになりますか？
    {   XA_FILE_AIR07,  12  },  //[53]      [6] と [3] で いくつになりますか？
    {   XA_FILE_AIR07,  13  },  //[54]      [6] と [4] で いくつになりますか？
    {   XA_FILE_AIR07,  14  },  //[55]      [7] と [0] で いくつになりますか？
    {   XA_FILE_AIR07,  15  },  //[56]      [7] と [1] で いくつになりますか？
    {   XA_FILE_AIR08,  0   },  //[57]      [7] と [2] で いくつになりますか？
    {   XA_FILE_AIR08,  1   },  //[58]      [7] と [3] で いくつになりますか？
    {   XA_FILE_AIR08,  2   },  //[59]      [8] と [0] で いくつになりますか？
    {   XA_FILE_AIR08,  3   },  //[60]      [8] と [1] で いくつになりますか？
    {   XA_FILE_AIR08,  4   },  //[61]      [8] と [2] で いくつになりますか？
    {   XA_FILE_AIR08,  5   },  //[62]      [9] と [0] で いくつになりますか？
    {   XA_FILE_AIR08,  6   },  //[63]      [9] と [1] で いくつになりますか？
    {   XA_FILE_AIR08,  7   },  //[64]      [10] と [0] で いくつになりますか？
};


//----TEXT02
static XA_DATA QuestionText02_XA_Data[]=
{
    {   XA_FILE_AIR09,  0   },  //[0]       [1] は [0] と いくつですか？
    {   XA_FILE_AIR09,  1   },  //[1]       [2] は [0] と いくつですか？
    {   XA_FILE_AIR09,  2   },  //[2]       [3] は [0] と いくつですか？
    {   XA_FILE_AIR09,  3   },  //[3]       [4] は [0] と いくつですか？
    {   XA_FILE_AIR09,  4   },  //[4]       [5] は [0] と いくつですか？
    {   XA_FILE_AIR09,  5   },  //[5]       [1] は [1] と いくつですか？
    {   XA_FILE_AIR09,  6   },  //[6]       [2] は [1] と いくつですか？
    {   XA_FILE_AIR09,  7   },  //[7]       [3] は [1] と いくつですか？
    {   XA_FILE_AIR09,  8   },  //[8]       [4] は [1] と いくつですか？
    {   XA_FILE_AIR09,  9   },  //[9]       [5] は [1] と いくつですか？
    {   XA_FILE_AIR09,  10  },  //[10]      [6] は [1] と いくつですか？
    {   XA_FILE_AIR09,  11  },  //[11]      [2] は [2] と いくつですか？
    {   XA_FILE_AIR09,  12  },  //[12]      [3] は [2] と いくつですか？
    {   XA_FILE_AIR09,  13  },  //[13]      [4] は [2] と いくつですか？
    {   XA_FILE_AIR09,  14  },  //[14]      [5] は [2] と いくつですか？
    {   XA_FILE_AIR09,  15  },  //[15]      [6] は [2] と いくつですか？
    {   XA_FILE_AIR10,  0   },  //[16]      [7] は [2] と いくつですか？
    {   XA_FILE_AIR10,  1   },  //[17]      [3] は [3] と いくつですか？
    {   XA_FILE_AIR10,  2   },  //[18]      [4] は [3] と いくつですか？
    {   XA_FILE_AIR10,  3   },  //[19]      [5] は [3] と いくつですか？
    {   XA_FILE_AIR10,  4   },  //[20]      [6] は [3] と いくつですか？
    {   XA_FILE_AIR10,  5   },  //[21]      [7] は [3] と いくつですか？
    {   XA_FILE_AIR10,  6   },  //[22]      [8] は [3] と いくつですか？
    {   XA_FILE_AIR10,  7   },  //[23]      [4] は [4] と いくつですか？
    {   XA_FILE_AIR10,  8   },  //[24]      [5] は [4] と いくつですか？
    {   XA_FILE_AIR10,  9   },  //[25]      [6] は [4] と いくつですか？
    {   XA_FILE_AIR10,  10  },  //[26]      [7] は [4] と いくつですか？
    {   XA_FILE_AIR10,  11  },  //[27]      [8] は [4] と いくつですか？
    {   XA_FILE_AIR10,  12  },  //[28]      [9] は [4] と いくつですか？
    {   XA_FILE_AIR10,  13  },  //[29]      [5] は [5] と いくつですか？
    {   XA_FILE_AIR10,  14  },  //[30]      [6] は [5] と いくつですか？
    {   XA_FILE_AIR10,  15  },  //[31]      [7] は [5] と いくつですか？
    {   XA_FILE_AIR11,  0   },  //[32]      [8] は [5] と いくつですか？
    {   XA_FILE_AIR11,  1   },  //[33]      [9] は [5] と いくつですか？
    {   XA_FILE_AIR11,  2   },  //[34]      [10] は [5] と いくつですか？
    {   XA_FILE_AIR12,  0   },  //[35]      [6] は [0] と いくつですか？
    {   XA_FILE_AIR12,  1   },  //[36]      [7] は [0] と いくつですか？
    {   XA_FILE_AIR12,  2   },  //[37]      [8] は [0] と いくつですか？
    {   XA_FILE_AIR12,  3   },  //[38]      [9] は [0] と いくつですか？
    {   XA_FILE_AIR12,  4   },  //[39]      [10] は [0] と いくつですか？
    {   XA_FILE_AIR12,  5   },  //[40]      [7] は [1] と いくつですか？
    {   XA_FILE_AIR12,  6   },  //[41]      [8] は [1] と いくつですか？
    {   XA_FILE_AIR12,  7   },  //[42]      [9] は [1] と いくつですか？
    {   XA_FILE_AIR12,  8   },  //[43]      [10] は [1] と いくつですか？
    {   XA_FILE_AIR12,  9   },  //[44]      [8] は [2] と いくつですか？
    {   XA_FILE_AIR12,  10  },  //[45]      [9] は [2] と いくつですか？
    {   XA_FILE_AIR12,  11  },  //[46]      [10] は [2] と いくつですか？
    {   XA_FILE_AIR12,  12  },  //[47]      [9] は [3] と いくつですか？
    {   XA_FILE_AIR12,  13  },  //[48]      [10] は [3] と いくつですか？
    {   XA_FILE_AIR12,  14  },  //[49]      [10] は [4] と いくつですか？
    {   XA_FILE_AIR12,  15  },  //[50]      [6] は [6] と いくつですか？
    {   XA_FILE_AIR13,  0   },  //[51]      [7] は [6] と いくつですか？
    {   XA_FILE_AIR13,  1   },  //[52]      [8] は [6] と いくつですか？
    {   XA_FILE_AIR13,  2   },  //[53]      [9] は [6] と いくつですか？
    {   XA_FILE_AIR13,  3   },  //[54]      [10] は [6] と いくつですか？
    {   XA_FILE_AIR13,  4   },  //[55]      [7] は [7] と いくつですか？
    {   XA_FILE_AIR13,  5   },  //[56]      [8] は [7] と いくつですか？
    {   XA_FILE_AIR13,  6   },  //[57]      [9] は [7] と いくつですか？
    {   XA_FILE_AIR13,  7   },  //[58]      [10] は [7] と いくつですか？
    {   XA_FILE_AIR13,  8   },  //[59]      [8] は [8] と いくつですか？
    {   XA_FILE_AIR13,  9   },  //[60]      [9] は [8] と いくつですか？
    {   XA_FILE_AIR13,  10  },  //[61]      [10] は [8] と いくつですか？
    {   XA_FILE_AIR13,  11  },  //[62]      [9] は [9] と いくつですか？
    {   XA_FILE_AIR13,  12  },  //[63]      [10] は [9] と いくつですか？
    {   XA_FILE_AIR13,  13  },  //[64]      [10] は [10] と いくつですか？
};


//----TEXT03
static XA_DATA QuestionText03_XA_Data[]=
{
    {   XA_FILE_AIR14,  11  },  //[ 0]      [12] 時のとき時計のはりはどこをさしていますか？
    {   XA_FILE_AIR14,  0   },  //[ 1]      [ 1] 時のとき時計のはりはどこをさしていますか？
    {   XA_FILE_AIR14,  1   },  //[ 2]      [ 2] 時のとき時計のはりはどこをさしていますか？
    {   XA_FILE_AIR14,  2   },  //[ 3]      [ 3] 時のとき時計のはりはどこをさしていますか？
    {   XA_FILE_AIR14,  3   },  //[ 4]      [ 4] 時のとき時計のはりはどこをさしていますか？
    {   XA_FILE_AIR14,  4   },  //[ 5]      [ 5] 時のとき時計のはりはどこをさしていますか？
    {   XA_FILE_AIR14,  5   },  //[ 6]      [ 6] 時のとき時計のはりはどこをさしていますか？
    {   XA_FILE_AIR14,  6   },  //[ 7]      [ 7] 時のとき時計のはりはどこをさしていますか？
    {   XA_FILE_AIR14,  7   },  //[ 8]      [ 8] 時のとき時計のはりはどこをさしていますか？
    {   XA_FILE_AIR14,  8   },  //[ 9]      [ 9] 時のとき時計のはりはどこをさしていますか？
    {   XA_FILE_AIR14,  9   },  //[10]      [10] 時のとき時計のはりはどこをさしていますか？
    {   XA_FILE_AIR14,  10  },  //[11]      [11] 時のとき時計のはりはどこをさしていますか？
    {   XA_FILE_AIR14,  11  },  //[12]      [12] 時のとき時計のはりはどこをさしていますか？
    {   XA_FILE_AIR14,  0   },  //[13]      [ 1] 時のとき時計のはりはどこをさしていますか？
    {   XA_FILE_AIR14,  1   },  //[14]      [ 2] 時のとき時計のはりはどこをさしていますか？
    {   XA_FILE_AIR14,  2   },  //[15]      [ 3] 時のとき時計のはりはどこをさしていますか？
    {   XA_FILE_AIR14,  3   },  //[16]      [ 4] 時のとき時計のはりはどこをさしていますか？
    {   XA_FILE_AIR14,  4   },  //[17]      [ 5] 時のとき時計のはりはどこをさしていますか？
    {   XA_FILE_AIR14,  5   },  //[18]      [ 6] 時のとき時計のはりはどこをさしていますか？
    {   XA_FILE_AIR14,  6   },  //[19]      [ 7] 時のとき時計のはりはどこをさしていますか？
    {   XA_FILE_AIR14,  7   },  //[20]      [ 8] 時のとき時計のはりはどこをさしていますか？
    {   XA_FILE_AIR14,  8   },  //[21]      [ 9] 時のとき時計のはりはどこをさしていますか？
    {   XA_FILE_AIR14,  9   },  //[22]      [10] 時のとき時計のはりはどこをさしていますか？
    {   XA_FILE_AIR14,  10  },  //[23]      [11] 時のとき時計のはりはどこをさしていますか？
};


//----TEXT04
static XA_DATA QuestionText04_XA_Data[]=
{
    {   XA_FILE_AIR15,  11  },  //[ 0]      [12:30] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR15,  0   },  //[ 1]      [ 1:30] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR15,  1   },  //[ 2]      [ 2:30] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR15,  2   },  //[ 3]      [ 3:30] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR15,  3   },  //[ 4]      [ 4:30] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR15,  4   },  //[ 5]      [ 5:30] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR15,  5   },  //[ 6]      [ 6:30] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR15,  6   },  //[ 7]      [ 7:30] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR15,  7   },  //[ 8]      [ 8:30] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR15,  8   },  //[ 9]      [ 9:30] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR15,  9   },  //[10]      [10:30] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR15,  10  },  //[11]      [11:30] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR15,  11  },  //[12]      [12:30] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR15,  0   },  //[13]      [ 1:30] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR15,  1   },  //[14]      [ 2:30] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR15,  2   },  //[15]      [ 3:30] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR15,  3   },  //[16]      [ 4:30] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR15,  4   },  //[17]      [ 5:30] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR15,  5   },  //[18]      [ 6:30] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR15,  6   },  //[19]      [ 7:30] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR15,  7   },  //[20]      [ 8:30] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR15,  8   },  //[21]      [ 9:30] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR15,  9   },  //[22]      [10:30] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR15,  10  },  //[23]      [11:30] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR16,  11  },  //[24]      [12:15] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR16,  0   },  //[25]      [ 1:15] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR16,  1   },  //[26]      [ 2:15] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR16,  2   },  //[27]      [ 3:15] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR16,  3   },  //[28]      [ 4:15] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR16,  4   },  //[29]      [ 5:15] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR16,  5   },  //[30]      [ 6:15] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR16,  6   },  //[31]      [ 7:15] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR16,  7   },  //[32]      [ 8:15] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR16,  8   },  //[33]      [ 9:15] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR16,  9   },  //[34]      [10:15] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR16,  10  },  //[35]      [11:15] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR17,  11  },  //[36]      [12:45] の とき時計の針はどこをさしていますか？         <X>
    {   XA_FILE_AIR17,  0   },  //[37]      [ 1:45] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR17,  1   },  //[38]      [ 2:45] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR17,  2   },  //[39]      [ 3:45] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR17,  3   },  //[40]      [ 4:45] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR17,  4   },  //[41]      [ 5:45] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR17,  5   },  //[42]      [ 6:45] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR17,  6   },  //[43]      [ 7:45] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR17,  7   },  //[44]      [ 8:45] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR17,  8   },  //[45]      [ 9:45] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR17,  9   },  //[46]      [10:45] の とき時計の針はどこをさしていますか？
    {   XA_FILE_AIR17,  10  },  //[47]      [11:45] の とき時計の針はどこをさしていますか？
};


//----------------------------------------------------------------スクリプト
//----ゲーム開始時
#define START_SCRIPT_BASE                       0
#define START_SCRIPT_NUM                        1

//----レベルセレクト
#define SELECT_LEVEL_SCRIPT_BASE                1
#define SELECT_LEVEL_SCRIPT_NUM                 1

//----初プレイデモ開始時
#define INIT_PLAY_DEMO_SCRIPT_BASE              2
#define INIT_PLAY_DEMO_SCRIPT_NUM               3

//----クリアデモ
#define CLEAR_DEMO_SCRIPT_BASE                  5
#define CLEAR_DEMO_SCRIPT_NUM                   1

//----オールクリアデモ１
#define ALL_CLEAR_DEMO_1_SCRIPT_BASE            6
#define ALL_CLEAR_DEMO_1_SCRIPT_NUM             2

//----オールクリアデモ２
#define ALL_CLEAR_DEMO_2_SCRIPT_BASE            8
#define ALL_CLEAR_DEMO_2_SCRIPT_NUM             1

//----失敗１
#define FALSE_DEMO_1_SCRIPT_BASE                9
#define FALSE_DEMO_1_SCRIPT_NUM                 1

//----失敗２
#define FALSE_DEMO_2_SCRIPT_BASE                10
#define FALSE_DEMO_2_SCRIPT_NUM                 1

//----タイムオーバーだ｡
#define TIMEOVER_SCRIPT_BASE                    11
#define TIMEOVER_SCRIPT_NUM                     1


//----スクリプト本体
static SCRIP_DATA AirScript[]=
{
    //----------------------------------------ゲーム開始時
    {//グングン　ひこうき。
        0,
        NamePlateMinna,
        XA_FILE_AIR03,
        1,
        "初音時０６グングン　ひこうき。待９０終"
    },
    //----------------------------------------レベルセレクト
    {//こんどは　どの　レベルで　あそぶ？　改ひかっている　ぶぶんを　えらんでね。
        0,
        NamePlateMinna,
        XA_FILE_AIR00,
        10,
        "初音時０６ひかっている　ぶぶんを　えらんでね。待２４０終"
    },
    //----------------------------------------開始デモ
    {//いたずら　カラスさん　に　改みんなのたからものを　改とられちゃった。
        0,
        NamePlateMinna,
        XA_FILE_AIR00,
        0,
        "初音時０６いたずらカラスさんに　改みんなの　たからものを　改とられちゃった。待１２０終"
    },
    {//どの　カラスさんが　たからもの　改もっているのかな。
        0,
        NamePlateMinna,
        XA_FILE_AIR00,
        1,
        "初音時０６どの　カラスさんが　たからものを　改もっているのかな。待１２０終"
    },
    {//うえに　でてくる　もんだい　の　改こたえが　かいてある　ふくろをもった　改カラスさん　が　あやしいぞ。
        0,
        NamePlateMinna,
        XA_FILE_AIR00,
        2,
        "初音時０６うえに　でてくる　もんだいの　改こたえが　かいてある　ふくろを　改もった　カラスさんが　あやしいぞ！待５２０終"
    },
    //----------------------------------------クリア
    {//つぎも　がんばるぞ。
        0,
        NamePlateMinna,
        XA_FILE_AIR02,
        7,
        "初音時０６つぎも　がんばるぞ。待１２０終"
    },
    //----------------------------------------オールクリア１
    {//きみの　おかげで　たからもの　がもどったよ。
        0,
        NamePlateMinna,
        XA_FILE_AIR02,
        8,
        "初音時０６きみの　おかげで　たからものが　改もどったよ。待２４０終"
    },
    {//どうもありがとう。
        0,
        NamePlateMinna,
        XA_FILE_AIR02,
        9,
        "初音時０６どうも　ありがとう。待２４０終"
    },
    //----------------------------------------オールクリア２
    {//なんだかてれるね。
        0,
        NamePlateMinna,
        XA_FILE_AIR02,
        10,
        "初音時０６なんだか　てれるね。待１２０終"
    },
    //----------------------------------------失敗１
    {//ざんねん　にげられてしまった。
        0,
        NamePlateMinna,
        XA_FILE_AIR02,
        5,
        "初音時０６ざんねん　にげられてしまった。待１２０終"
    },
    //----------------------------------------失敗２
    {//つぎはがんばろうよ。
        0,
        NamePlateMinna,
        XA_FILE_AIR02,
        6,
        "初音時０６つぎはがんばろうよ。待１２０終"
    },
    //----------------------------------------タイムオーバーだ｡
    {//タイムオーバーだ｡
        0,
        NamePlateMinna,
        XA_FILE_AIR01,
        5,
        "初音時０６タイムオーバーだ｡待９０終"
    },
};


//-----------------------------------------------------------------------------
// codes 
//-----------------------------------------------------------------------------
#ifdef __DEBUG_AIR__
static int DebugDrawClockTask(TASK* ip_task)
{
    static int x,y,z,time;


    static char* ClockStTable[]={
        "CLOCK_00_00",
        "CLOCK_00_05",
        "CLOCK_00_10",
        "CLOCK_00_15",
        "CLOCK_00_20",
        "CLOCK_00_25",
        "CLOCK_00_30",
        "CLOCK_00_35",
        "CLOCK_00_40",
        "CLOCK_00_45",
        "CLOCK_00_50",
        "CLOCK_00_55",
        "CLOCK_01_00",
        "CLOCK_01_05",
        "CLOCK_01_10",
        "CLOCK_01_15",
        "CLOCK_01_20",
        "CLOCK_01_25",
        "CLOCK_01_30",
        "CLOCK_01_35",
        "CLOCK_01_40",
        "CLOCK_01_45",
        "CLOCK_01_50",
        "CLOCK_01_55",
        "CLOCK_02_00",
        "CLOCK_02_05",
        "CLOCK_02_10",
        "CLOCK_02_15",
        "CLOCK_02_20",
        "CLOCK_02_25",
        "CLOCK_02_30",
        "CLOCK_02_35",
        "CLOCK_02_40",
        "CLOCK_02_45",
        "CLOCK_02_50",
        "CLOCK_02_55",
        "CLOCK_03_00",
        "CLOCK_03_05",
        "CLOCK_03_10",
        "CLOCK_03_15",
        "CLOCK_03_20",
        "CLOCK_03_25",
        "CLOCK_03_30",
        "CLOCK_03_35",
        "CLOCK_03_40",
        "CLOCK_03_45",
        "CLOCK_03_50",
        "CLOCK_03_55",
        "CLOCK_04_00",
        "CLOCK_04_05",
        "CLOCK_04_10",
        "CLOCK_04_15",
        "CLOCK_04_20",
        "CLOCK_04_25",
        "CLOCK_04_30",
        "CLOCK_04_35",
        "CLOCK_04_40",
        "CLOCK_04_45",
        "CLOCK_04_50",
        "CLOCK_04_55",
        "CLOCK_05_00",
        "CLOCK_05_05",
        "CLOCK_05_10",
        "CLOCK_05_15",
        "CLOCK_05_20",
        "CLOCK_05_25",
        "CLOCK_05_30",
        "CLOCK_05_35",
        "CLOCK_05_40",
        "CLOCK_05_45",
        "CLOCK_05_50",
        "CLOCK_05_55",
        "CLOCK_06_00",
        "CLOCK_06_05",
        "CLOCK_06_10",
        "CLOCK_06_15",
        "CLOCK_06_20",
        "CLOCK_06_25",
        "CLOCK_06_30",
        "CLOCK_06_35",
        "CLOCK_06_40",
        "CLOCK_06_45",
        "CLOCK_06_50",
        "CLOCK_06_55",
        "CLOCK_07_00",
        "CLOCK_07_05",
        "CLOCK_07_10",
        "CLOCK_07_15",
        "CLOCK_07_20",
        "CLOCK_07_25",
        "CLOCK_07_30",
        "CLOCK_07_35",
        "CLOCK_07_40",
        "CLOCK_07_45",
        "CLOCK_07_50",
        "CLOCK_07_55",
        "CLOCK_08_00",
        "CLOCK_08_05",
        "CLOCK_08_10",
        "CLOCK_08_15",
        "CLOCK_08_20",
        "CLOCK_08_25",
        "CLOCK_08_30",
        "CLOCK_08_35",
        "CLOCK_08_40",
        "CLOCK_08_45",
        "CLOCK_08_50",
        "CLOCK_08_55",
        "CLOCK_09_00",
        "CLOCK_09_05",
        "CLOCK_09_10",
        "CLOCK_09_15",
        "CLOCK_09_20",
        "CLOCK_09_25",
        "CLOCK_09_30",
        "CLOCK_09_35",
        "CLOCK_09_40",
        "CLOCK_09_45",
        "CLOCK_09_50",
        "CLOCK_09_55",
        "CLOCK_10_00",
        "CLOCK_10_05",
        "CLOCK_10_10",
        "CLOCK_10_15",
        "CLOCK_10_20",
        "CLOCK_10_25",
        "CLOCK_10_30",
        "CLOCK_10_35",
        "CLOCK_10_40",
        "CLOCK_10_45",
        "CLOCK_10_50",
        "CLOCK_10_55",
        "CLOCK_11_00",
        "CLOCK_11_05",
        "CLOCK_11_10",
        "CLOCK_11_15",
        "CLOCK_11_20",
        "CLOCK_11_25",
        "CLOCK_11_30",
        "CLOCK_11_35",
        "CLOCK_11_40",
        "CLOCK_11_45",
        "CLOCK_11_50",
        "CLOCK_11_55",
    };

    switch( ip_task->mode )
    {
        //---------------------------------------------------------------------init
        case TASK_MODE_INIT:
            //next main
            ip_task->mode = TASK_MODE_MAIN;
            
            //----texture read sram -> vram
            if((file_read(AirGameTextureFile[0].fn,LoadAddress)) == -1)
            {//read error
                return FALSE;
            }

            //----texture init
            TexInit( AIR_GAME_TIM_NUM, &AirGameTextureImage[AIR_GAME_TIM_POS] );
            TimImgData = AirGameTextureImage;

            //----ゲーム用スプライト登録
            EntrySprite( AirGameSpriteData );

            //init
            time = 0;
            x=100;
            y=100;
            z=100;

            // フェードInします
            GameMgr.FadeFlag = FadeIn;

            break;
        //---------------------------------------------------------------------main
        case TASK_MODE_MAIN:
            
            if(JstPad & PADLup){
                if(--time<0)    time=143;
            }else
            if(JstPad & PADLdown){
                if(++time>=144) time=0;
            }else{
                
            }

            FntPrint("[%s]-[%3d]",ClockStTable[time],time);
            DrawClock(time,x,y,z);
            break;
        //---------------------------------------------------------------------exit
        case TASK_MODE_EXIT:
            
            
            break;
        default:
    }
}
#endif



//-----------------------------------------------------------------------------
//  関数名 :Air
//
//  work   :グングン飛行機
//  in     :GAMEMGR*    ゲームマネージャへのポインタ
//  out    :TRUE        成功
//  note   :なし
//-----------------------------------------------------------------------------
int Air(GAMEMGR * ip_GameMgr)
{
    SPRITE_DATA SpData;
    TASK Task;
    static int counter=0;


    switch( ip_GameMgr->SubMode )
    {
        case INIT:
            //----スプライトマネージャ初期化
            InitSprite();

            //----タスクマネージャ初期化
            InitTaskMgr();

            //----ランダム設定
            srand(ip_GameMgr->Timer);

            //----岩澤担当部分：初期化
            SfileRead2(AIR_SOUNDFILE);
            HelpInit();
            GameMgr.WaitFlag    = ON;

            //---- ゲーム管理情報初期化
            AGameMgr.PlayLevel          = 0;                                //プレイレベル
            AGameMgr.Level              = ip_GameMgr->Level[GAME_AIRP];     //ゲームレベル
            AGameMgr.Timer              = TIMER_NUM;                        //ゲーム時間
            AGameMgr.TimerDiv           = TIMER_NUM_DIV;                    //ゲーム時間
            AGameMgr.SelectLevelFlag    = 1;                                //セレクトレベルフラグ
            AGameMgr.TimeUpSignal       = 0;                                //時間切れシグナル
            AGameMgr.TimeUpFlag         = 0;                                //時間切れフラグ
            AGameMgr.ClearFlag          = 0;                                //クリアフラグ
            AGameMgr.ClearTimer         = 0;                                //クリアタイマー
            AGameMgr.ClearEnd           = 0;                                //クリア終了
            AGameMgr.AllClearFlag       = 0;                                //オールクリアフラグ
            AGameMgr.ExitFlag           = 0;                                //終了フラグ

            //継続プレイフラグクリア
            AGameMgr.Air.ContinueFlag   = 0;


#ifdef __DEBUG_AIR__

            if( NewPad & PADL1 && NewPad & PADR1)
            {//----時計デバッグ
                Task.func       = DebugDrawClockTask;
                Task.priority   = TASK_NO_DEBUG;
                Task.attribute  = ATTR_USER;
                Task.status     = TASK_NEW_ENTRY;
                Task.id         = TASK_NO_DEBUG;
                Task.wait_time  = 0;
                Task.buf        = NULL;
                Task.name       = "DebugDrawClockTask";
                Task.mode       = TASK_MODE_INIT;
                CreateTask(&Task);
            }else
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
            }
#else
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
#endif

            //----メインモード
            ip_GameMgr->SubMode = MAIN;
            
            break;
        case MAIN:
            //-----------------------------------------ゲームメインループ▼
            FntPrint("");           //呼んでおかないとダメ

#ifdef __DEBUG_AIR__
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("Script-Flag:[%d]",AGameMgr.Script.Flag);
#endif

            ExecuteTask();          //タスクマネージャ実行
            TransSprite();          //スプライト転送
            SpraitControl();
            
            //終了チェック
            if(AGameMgr.ExitFlag)   ip_GameMgr->SubMode = EXIT;
            //-----------------------------------------------------------▲
            break;
        case EXIT:
            //ゲームレベル
            ip_GameMgr->Level[GAME_AIRP]    = AGameMgr.Level;

            //----岩澤担当部分：終了
            SpraitCharClr();
            SpraitControl();
            GameMgr.WaitFlag = ON;
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
//
//  work   :ゲームマネージャタスク
//  in     :TASK*   タスクポインタ
//  out    :TRUE
//  note   :なし
//-----------------------------------------------------------------------------
static int GameControllTask(TASK* ip_task)
{
    SPRITE_DATA SpData;
    TASK Task;
    ANSWER Answer;
    int i;


    switch( ip_task->mode )
    {
        //---------------------------------------------------------------------初期化
        case TASK_MODE_INIT:
            //next main
            ip_task->mode = TASK_MODE_MAIN;

            //----texture read sram -> vram
            if((file_read(AirGameTextureFile[0].fn,LoadAddress)) == -1)
            {//read error
                return FALSE;
            }

            //----texture init
            TexInit( AIR_GAME_TIM_NUM, &AirGameTextureImage[AIR_GAME_TIM_POS] );
            TimImgData = AirGameTextureImage;

            //----ゲーム用スプライト登録
            EntrySprite( AirGameSpriteData );

            //---- ゲーム管理情報初期化
            AGameMgr.TimeUpSignal       = 0;                                    //時間切れシグナル
            AGameMgr.TimeUpFlag         = 0;                                    //時間切れフラグ
            AGameMgr.ClearFlag          = 0;                                    //レベルクリアフラグ
            AGameMgr.ClearTimer         = 0;                                    //クリアタイマー
            AGameMgr.ClearEnd           = 0;                                    //
            AGameMgr.AllClearFlag       = 0;                                    //オールクリアフラグ
        //  AGameMgr.PlayLevel          = 0;                                    //
        //  AGameMgr.Level              = 0;                                    //現在のゲームレベル

#ifdef __DEBUG_ALL_QUESTION_AIR__
            AGameMgr.Question.Num       = 0;
#else
            AGameMgr.Question.Num       = rand() % AIR_GAME_MAX_KIND_NUM;       //何番目
#endif
            AGameMgr.Question.Index     = 0;                                    //インデックス
            AGameMgr.Question.ClearNum  = 0;                                    //クリア数
            AGameMgr.Question.TextFlag  = 0;                                    //

            //[♪]BGM
            ssPlayBgm(AIR_BGM_00);

            // フェードInします
            GameMgr.FadeFlag = FadeIn;

            //---- 背景タスク
            Task.func       = BgTask;
            Task.priority   = TASK_NO_GAME_BG;
            Task.attribute  = ATTR_USER;
            Task.status     = TASK_NEW_ENTRY;
            Task.id         = TASK_NO_GAME_BG;
            Task.wait_time  = 0;
            Task.buf        = NULL;
            Task.name       = "BgTask";
            Task.mode       = TASK_MODE_INIT;
            CreateTask(&Task);

            //----飛行機タスク
            Task.func       = AirTask;
            Task.priority   = TASK_NO_GAME_AIR;
            Task.attribute  = ATTR_USER;
            Task.status     = TASK_NEW_ENTRY;
            Task.id         = TASK_NO_GAME_AIR;
            Task.wait_time  = 0;
            Task.buf        = NULL;
            Task.name       = "AirTask";
            Task.mode       = TASK_MODE_INIT;
            CreateTask(&Task);

            //----クイズタスク
            Task.func       = QuizTask;
            Task.priority   = TASK_NO_GAME_QUIZ;
            Task.attribute  = ATTR_USER;
            Task.status     = TASK_NEW_ENTRY;
            Task.id         = TASK_NO_GAME_QUIZ;
            Task.wait_time  = 0;
            Task.buf        = NULL;
            Task.name       = "QuizTask";
            Task.mode       = TASK_MODE_INIT;
            CreateTask(&Task);

            //----おじゃまキャラタスク
            Task.func       = EnemyTask;
            Task.priority   = TASK_NO_GAME_ENEMY;
            Task.attribute  = ATTR_USER;
            Task.status     = TASK_NEW_ENTRY;
            Task.id         = TASK_NO_GAME_ENEMY;
            Task.wait_time  = 0;
            Task.buf        = NULL;
            Task.name       = "EnemyTask";
            Task.mode       = TASK_MODE_INIT;
            CreateTask(&Task);

            //----カラスタスク
            Task.func       = CrowTask;
            Task.priority   = TASK_NO_GAME_CROW;
            Task.attribute  = ATTR_USER;
            Task.status     = TASK_NEW_ENTRY;
            Task.id         = TASK_NO_GAME_CROW;
            Task.wait_time  = 0;
            Task.buf        = NULL;
            Task.name       = "CrowTask";
            Task.mode       = TASK_MODE_INIT;
            CreateTask(&Task);

            //----エフェクトタスク
            Task.func       = EffectTask;
            Task.priority   = TASK_NO_GAME_EFFECT;
            Task.attribute  = ATTR_USER;
            Task.status     = TASK_NEW_ENTRY;
            Task.id         = TASK_NO_GAME_EFFECT;
            Task.wait_time  = 0;
            Task.buf        = NULL;
            Task.name       = "EffectTask";
            Task.mode       = TASK_MODE_INIT;
            CreateTask(&Task);

#ifndef __DEBUG_ALL_QUESTION_AIR__
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
#endif

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
                
            //----スリープタスク
        //  SleepTask(TASK_NO_GAME_AIR);
        //  SleepTask(TASK_NO_GAME_QUIZ);
            SleepTask(TASK_NO_GAME_CROW);
            SleepTask(TASK_NO_GAME_ENEMY);
            SleepTask(TASK_NO_GAME_EFFECT);
            SleepTask(TASK_NO_GAME_TIMER);
            SleepTask(TASK_NO_GAME_PAUSE);

            break;
        //---------------------------------------------------------------------メイン
        case TASK_MODE_MAIN:

#ifdef __DEBUG_AIR__
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("LEVEL=%d/PLAY_LEVEL=%d\n",AGameMgr.Level,AGameMgr.PlayLevel);
            FntPrint("QINDEX=%d\n",AGameMgr.Question.Index);
            FntPrint("QNUM=%d\n",AGameMgr.Question.Num);

            FntPrint("ANS=");
            for(i=0;i<3;i++)
            {
                GetAnswerData(  QuestionTopData[AGameMgr.PlayLevel][AGameMgr.Question.Num][AGameMgr.Question.Index].Kind,
                                QuestionTopData[AGameMgr.PlayLevel][AGameMgr.Question.Num][AGameMgr.Question.Index].No,
                                i,&Answer);

                FntPrint("%d",  Answer.Flag);
            }
#endif

#ifdef __DEBUG_ALL_QUESTION_AIR__
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("\n");
            FntPrint("LEVEL=%d/PLAY_LEVEL=%d\n",AGameMgr.Level,AGameMgr.PlayLevel);
            FntPrint("QINDEX=%d\n",AGameMgr.Question.Index);
            FntPrint("QNUM=%d\n",AGameMgr.Question.Num);

            FntPrint("ANS=");
            for(i=0;i<3;i++)
            {
                GetAnswerData(  QuestionTopData[AGameMgr.PlayLevel][AGameMgr.Question.Num][AGameMgr.Question.Index].Kind,
                                QuestionTopData[AGameMgr.PlayLevel][AGameMgr.Question.Num][AGameMgr.Question.Index].No,
                                i,&Answer);

                FntPrint("%d",  Answer.Flag);
            }
            FntPrint("\n");
#endif

            //クリア後飛行機画面外へ、タイムアップ
            if( AGameMgr.ClearEnd || AGameMgr.TimeUpFlag )  ip_task->mode = TASK_MODE_EXIT;
            break;
        //---------------------------------------------------------------------終了
        case TASK_MODE_EXIT:
            //----ゲームタスク終了
            RemoveTask(TASK_NO_GAME_BG);
            RemoveTask(TASK_NO_GAME_AIR);
            RemoveTask(TASK_NO_GAME_QUIZ);
            RemoveTask(TASK_NO_GAME_CROW);
            RemoveTask(TASK_NO_GAME_ENEMY);
            RemoveTask(TASK_NO_GAME_EFFECT);
            RemoveTask(TASK_NO_GAME_TIMER);
            RemoveTask(TASK_NO_GAME_PAUSE);

        //  RemoveTask(TASK_NO_GAME_SCRIPT);

            //スクリプトタスク終了
            ChangeTaskMode(TASK_NO_GAME_SCRIPT,TASK_MODE_EXIT);


            //----登録スプライト開放
            ReleaseSprite();

            //[♪]BGM
            ssStopBgm(AIR_BGM_00);

            //ガイド破棄
            SpraitCharClr();

            //----イベントタスク    
            if(AGameMgr.AllClearFlag)
            {//レベル３クリア
                Task.func       = AllClearEventTask;
                Task.priority   = TASK_NO_GAME_EVENT;
                Task.attribute  = ATTR_USER;
                Task.status     = TASK_NEW_ENTRY;
                Task.id         = TASK_NO_GAME_EVENT;
                Task.wait_time  = 0;
                Task.buf        = NULL;
                Task.name       = "AllClearEventTask";
                Task.mode       = TASK_MODE_INIT;
                CreateTask(&Task);
            }else
            if(AGameMgr.ClearFlag)
            {//レベル１．２クリア
                Task.func       = ClearEventTask;
                Task.priority   = TASK_NO_GAME_EVENT;
                Task.attribute  = ATTR_USER;
                Task.status     = TASK_NEW_ENTRY;
                Task.id         = TASK_NO_GAME_EVENT;
                Task.wait_time  = 0;
                Task.buf        = NULL;
                Task.name       = "ClearEventTask";
                Task.mode       = TASK_MODE_INIT;
                CreateTask(&Task);
            }else if(AGameMgr.TimeUpFlag)
            {//タイムアップ
                Task.func       = FalseEventTask;
                Task.priority   = TASK_NO_GAME_EVENT;
                Task.attribute  = ATTR_USER;
                Task.status     = TASK_NEW_ENTRY;
                Task.id         = TASK_NO_GAME_EVENT;
                Task.wait_time  = 0;
                Task.buf        = NULL;
                Task.name       = "FalseEventTask";
                Task.mode       = TASK_MODE_INIT;
                CreateTask(&Task);
            }else
            {
                
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
    static int SelectNumTable[]={
        AIR_CHAR_LEVEL_SELECT_01,
        AIR_CHAR_LEVEL_SELECT_02,
        AIR_CHAR_LEVEL_SELECT_03
    };

    SPRITE_DATA SpData;
    TASK Task;
    int i,j;


    switch(ip_task->mode)
    {
        //----------------------------------------------------------------タスク初期化
        case TASK_MODE_INIT:
            SpraitCharSet(&GaidoLevelSpControl00[0], NULL);     // iwasawa Correction (2003/4/27)
            //next MAIN
            ip_task->mode       = TASK_MODE_MAIN;

            //----プレイレベルクリア
            AGameMgr.PlayLevel      = 0;

            //----継続プレイフラグOFF
            AGameMgr.Air.ContinueFlag   = 0;

            //----レベルセレクトワーク初期化
            AGameMgr.SelectLevel.Mode               = AIR_GAME_SELECT_LEVEL_MODE_01;
            AGameMgr.SelectLevel.Timer              = 0;
            AGameMgr.SelectLevel.BlockNo            = 0;
            AGameMgr.SelectLevel.BlockWt            = 0;
            AGameMgr.SelectLevel.KeteiWt            = 0;
            AGameMgr.SelectLevel.KeteiFlushIndex    = 0;
            AGameMgr.SelectLevel.KeteiFlushWt       = 0;
            AGameMgr.SelectLevel.AnmIndex           = 0;
            AGameMgr.SelectLevel.AnmNo              = 0;
            AGameMgr.SelectLevel.AnmWt              = 0;
            AGameMgr.SelectLevel.AnmBase            = 0;
            AGameMgr.SelectLevel.PosX               = 0;
            AGameMgr.SelectLevel.PosY               = 0;
            AGameMgr.SelectLevel.WaitFlag           = 0;

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
            Task.user[1]        = SELECT_LEVEL_SCRIPT_BASE;
            Task.user[2]        = SELECT_LEVEL_SCRIPT_NUM;
            CreateTask(&Task);

            break;
        //----------------------------------------------------------------タスクメイン
        case TASK_MODE_MAIN:
            SsinScriptFlag = AGameMgr.Script.Flag;          // iwasawa Correction (2003/4/27)
            //----選択可能レベルをプレートのアニメで表現する
            switch(AGameMgr.SelectLevel.Mode)
            {
                //----------------------------------選択可能なレベルまで明るく(楽団員現る)
                case AIR_GAME_SELECT_LEVEL_MODE_00:
                    
                    
                    break;
                //----------------------------------下から上へ明るく
                case AIR_GAME_SELECT_LEVEL_MODE_01:
                    if(!AGameMgr.Script.Flag){
                        //----操作
                        if(JstPad &  PADLright)
                        {
                            //[♪] レバー音
                            ssPlaySe(BUTONSE_LEVER);
                            if(++AGameMgr.PlayLevel>AGameMgr.Level){
                                AGameMgr.PlayLevel=0;
                            }
                        }else
                        if(JstPad &  PADLleft){
                            //[♪] レバー音
                            ssPlaySe(BUTONSE_LEVER);
                            if(--AGameMgr.PlayLevel<0){
                                AGameMgr.PlayLevel=AGameMgr.Level;
                            }
                        }else{
                            
                        }
                        
                        //----決定
                        if(JstPad &  PADRright)
                        {//next EXIT
                            AGameMgr.SelectLevel.Mode = AIR_GAME_SELECT_LEVEL_MODE_02;
                            
                            //[♪]決定
                            ssPlaySe(BUTONSE_MARU);
                            
                            //スクリプトタスク終了
                            ChangeTaskMode(TASK_NO_GAME_SCRIPT,TASK_MODE_EXIT);
                        }
                    }
                    
                    //----描画
                    if( ++AGameMgr.SelectLevel.BlockWt > AIR_GAME_SELECT_LEVEL_FLUSH_ANM_TIME)
                    {//
                        AGameMgr.SelectLevel.BlockWt=0;
                        if(++AGameMgr.SelectLevel.BlockNo > AIR_GAME_MAX_LEVEL_NUM)
                        {
                            AGameMgr.SelectLevel.BlockNo=0;
                        }
                    }

                    for(i=0;i<AGameMgr.Level+1;i++){//横
                        for(j=0;j<3;j++){//縦
                            if(j>i) continue;
                            if(AGameMgr.SelectLevel.BlockNo <= j) continue;
                            
                            //レベルセレクトプレート
                            SpData.No       = AIR_CHAR_LEVEL_SELECT_BLOCK;
                            SpData.PosX     = LEVEL_SELECT_BLOCK_POSX + LEVEL_SELECT_BLOCK_KKX * i;
                            SpData.PosY     = LEVEL_SELECT_BLOCK_POSY - LEVEL_SELECT_BLOCK_KKY * j;
                            SpData.PosZ     = PRIORITY_EFFECT-2;
                            SpData.ScaleX   = SCALE10;
                            SpData.ScaleY   = SCALE10;
                            SpData.Rotate   = ROTATE000;
                            SpData.Reverse  = NOREVERS;
                            DrawSprite( &SpData );
                        }
                    }
                    break;
                //----------------------------------選んだレベルのみフラッシュ
                case AIR_GAME_SELECT_LEVEL_MODE_02:
                    
                    if(!AGameMgr.SelectLevel.WaitFlag){
                        if(++AGameMgr.SelectLevel.KeteiWt > AIR_GAME_SELECT_LEVEL_KETEI_WAIT_TIME)
                        {//フラッシュ後抜ける
                            ip_task->mode = TASK_MODE_EXIT;
                        }
                    }
                    
                    if( ++AGameMgr.SelectLevel.KeteiFlushWt > AIR_GAME_SELECT_LEVEL_KETEI_FLUSH_TIME ){
                        AGameMgr.SelectLevel.KeteiFlushWt = 0;
                        AGameMgr.SelectLevel.KeteiFlushIndex^=1;
                    }
                    
                    if(AGameMgr.SelectLevel.KeteiFlushIndex){
                        for(i=0;i<3;i++){//縦
                            if(AGameMgr.PlayLevel>=i){
                                //レベルセレクトプレート
                                SpData.No       = AIR_CHAR_LEVEL_SELECT_BLOCK;
                                SpData.PosX     = LEVEL_SELECT_BLOCK_POSX + LEVEL_SELECT_BLOCK_KKX * AGameMgr.PlayLevel;
                                SpData.PosY     = LEVEL_SELECT_BLOCK_POSY - LEVEL_SELECT_BLOCK_KKY * i;
                                SpData.PosZ     = PRIORITY_EFFECT-2;
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

            //選択カーソル
            SpData.No       = AIR_CHAR_LEVEL_SELECT_CURSOR;
            SpData.PosX     = LEVEL_SELECT_BLOCK_POSX + AGameMgr.PlayLevel * LEVEL_SELECT_BLOCK_KKX - 1;
            SpData.PosY     = LEVEL_SELECT_NUM_POSY - 5 - LEVEL_SELECT_BLOCK_KKY * AGameMgr.PlayLevel;
            SpData.PosZ     = PRIORITY_EFFECT-2;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );

            //----レベル数字
            for(i=0;i<AGameMgr.Level+1;i++){
                SpData.No       = SelectNumTable[i];
                SpData.PosX     = LEVEL_SELECT_NUM_POSX + LEVEL_SELECT_BLOCK_KKX * i;
                SpData.PosY     = LEVEL_SELECT_NUM_POSY - LEVEL_SELECT_BLOCK_KKY * i;
                SpData.PosZ     = PRIORITY_EFFECT-2;
                SpData.ScaleX   = SCALE10;
                SpData.ScaleY   = SCALE10;
                SpData.Rotate   = ROTATE000;
                SpData.Reverse  = NOREVERS;
                DrawSprite( &SpData );
            }

            //レベルプレート
            SpData.No       = AIR_CHAR_LEVEL_SELECT_PLATE;
            SpData.PosX     = LEVEL_SELECT_PLATE_POSX;
            SpData.PosY     = LEVEL_SELECT_PLATE_POSY;
            SpData.PosZ     = PRIORITY_EFFECT;
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


            //----お願いタスク
            Task.func       = WishTask;
            Task.priority   = TASK_NO_GAME_WISH;
            Task.attribute  = ATTR_USER;
            Task.status     = TASK_NEW_ENTRY;
            Task.id         = TASK_NO_GAME_WISH;
            Task.wait_time  = 0;
            Task.buf        = NULL;
            Task.name       = "WishTask";
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
//  関数名 :WishTask
//
//  work   :お願いタスク
//  in     :TASK*   タスクポインタ
//  out    :TRUE
//  note   :なし
//-----------------------------------------------------------------------------
static int WishTask(TASK* ip_task)
{
    SPRITE_DATA SpData;
    TASK Task;


    switch( ip_task->mode )
    {
        //----------------------------------------------------------------init
        case TASK_MODE_INIT:
            //next MAIN
            ip_task->mode = TASK_MODE_MAIN;
            
            //init - flag / wait
            ip_task->user[0]    = GET_DA_STATUS_WAIT_TIME*4;

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
            Task.user[0]        = SCRIPT_LINE_3;
            Task.user[1]        = INIT_PLAY_DEMO_SCRIPT_BASE;
            Task.user[2]        = INIT_PLAY_DEMO_SCRIPT_NUM;
            CreateTask(&Task);

            break;
        //----------------------------------------------------------------main
        case TASK_MODE_MAIN:
            if(!AGameMgr.Script.Flag){
                if( --ip_task->user[0]<=0){
                    if(dSoundStatus == DslStatStandby){
                        ip_task->mode = TASK_MODE_EXIT;
                    }
                }
            }

            //お願いパネル
            SpData.No       = AIR_CHAR_HELP_PANEL;
            SpData.PosX     = (320-128)/2;
            SpData.PosY     = (240-128)/2+16;
            SpData.PosZ     = PRIORITY_EFFECT;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );
            
            break;
        //----------------------------------------------------------------exit
        case TASK_MODE_EXIT:
            //スクリプトOFF
            MetuseijiFlag=OFF;

            if(AGameMgr.SelectLevelFlag)
            {//セレクトレベルタスクが起動した後にこのタスクが起動しているため
                
                //タスクウェイクアップ
            //  WakeupTask(TASK_NO_GAME_AIR);
            //  WakeupTask(TASK_NO_GAME_QUIZ);
                WakeupTask(TASK_NO_GAME_CROW);
                WakeupTask(TASK_NO_GAME_ENEMY);
                WakeupTask(TASK_NO_GAME_EFFECT);
                WakeupTask(TASK_NO_GAME_TIMER);
                WakeupTask(TASK_NO_GAME_PAUSE);
                
                //クリア
            //  AGameMgr.SelectLevelFlag = 0;
            }
            
            //飛行機制御ON
            AGameMgr.Air.ControllFlag = 1;
            
            //問題表示ON
            AGameMgr.Question.TextFlag = 1;

            //ガイドセット
            GaidoInit();

            //自分を削除
            ExitTask(ip_task->id);
            break;
        default:
    }
}


//-----------------------------------------------------------------------------
//  関数名 :TimerTask
//
//  work   :タイマータスク
//  in     :TASK*   タスクポインタ
//  out    :TRUE
//  note   :なし
//-----------------------------------------------------------------------------
static int TimerTask(TASK* ip_task)
{
    SPRITE_DATA SpData;
    TASK Task;
    int i;

    switch( ip_task->mode )
    {
        //----------------------------------------------------------------初期化
        case TASK_MODE_INIT:
            //next MAIN
            ip_task->mode = TASK_MODE_MAIN;
            
            //init
            AGameMgr.Timer      = TIMER_NUM;
            AGameMgr.TimerDiv   = TIMER_NUM_DIV;

            ip_task->user[0]    = 0;    //mode
            ip_task->user[1]    = 0;    //timer
            
            break;
        //----------------------------------------------------------------メイン
        case TASK_MODE_MAIN:
            
            switch(ip_task->user[0])
            {
                case 0:
                    if(--AGameMgr.TimerDiv < 0){
                        //再セット
                        AGameMgr.TimerDiv=TIMER_NUM_DIV;
                        
                        if(--AGameMgr.Timer<=0)
                        {//
                            GameMgr.WaitFlag = ON;          // iwasawa Correction (2003/4/27)
                            //タイムアップシグナルON
                            AGameMgr.TimeUpSignal=1;
                            
                            //change mode
                            ip_task->user[0]    = 1;
                            
                            //[♪]ピッピー
                            dsPlayXa(XA_FILE_AIR21,0);
                            ip_task->user[1] = GET_DA_STATUS_WAIT_TIME*3;
                            
                            //ポーズタスク削除
                            RemoveTask(TASK_NO_GAME_PAUSE);
                        }
                    }
                    break;
                case 1:
                    if(--ip_task->user[1]<=0){
                        if(dSoundStatus == DslStatStandby){
                            //change mode
                            ip_task->user[0] = 2;
                            ip_task->user[1] = GET_DA_STATUS_WAIT_TIME*3;
                            
                            //[♪]タイムオーバーだ
                            dsPlayXa(XA_FILE_AIR01,5);
                        }
                    }
                    break;
                case 2:
                    if(--ip_task->user[1]<=0){
                        if(dSoundStatus == DslStatStandby){
                            ip_task->mode=TASK_MODE_EXIT;
//                          //change mode
//                          ip_task->user[0] = 3;
//                          
//                          Task.func           = EventFadeOutTask;
//                          Task.priority       = TASK_NO_GAME_FADE;
//                          Task.attribute      = ATTR_USER;
//                          Task.status         = TASK_NEW_ENTRY;
//                          Task.id             = TASK_NO_GAME_FADE;
//                          Task.wait_time      = 0;
//                          Task.buf            = NULL;
//                          Task.name           = "EventFadeOutTask";
//                          Task.mode           = TASK_MODE_INIT;
//                          Task.user[0]        = ip_task->id;
//                          CreateTask(&Task);
                        }
                    }
                    break;
//              case 3:
//                  
//                  break;
                default:
            }

            //描画
            DrawNo(AGameMgr.Timer,TIMER_STR_WIDE,TimerNoTable,TIMER_POS_X,TIMER_POS_Y,PRIORITY_QUIZ_TIME_COUNTER);

            break;
        //----------------------------------------------------------------終了
        case TASK_MODE_EXIT:
            //タイムアップフラグセット
            AGameMgr.TimeUpFlag = 1;
            
            //自分を削除
            ExitTask(ip_task->id);
            
            break;
        default:
    }
    return TRUE;
}




//-----------------------------------------------------------------------------
//  関数名 :PauseTask
//
//  work   :ポーズ監視タスク
//  in     :TASK*   タスクポインタ
//  out    :TRUE
//  note   :なし
//-----------------------------------------------------------------------------
static int PauseTask(TASK* ip_task)
{
    SPRITE_DATA SpData;
    TASK Task;
    int ret;

    switch( ip_task->mode )
    {
        //----------------------------------------------------------------初期化
        case TASK_MODE_INIT:
            //next MAIN
            ip_task->mode       = TASK_MODE_MAIN;
            
            //Flag
            ip_task->user[0]    = 0;

            //メニューフラグチェック
            GameMgr.WaitFlag    = OFF;

            break;
        //----------------------------------------------------------------メイン
        case TASK_MODE_MAIN:
            if( !ip_task->user[0] )
            {//メニューオープン待ち
                ret = MainMenuCheck10();
                
                if(ret==ON)
                {//スタートボタン押される
                    //停止コントロールフラグセット
                    ip_task->user[0] = 1;
                    
                    //タスクスリープ
                    SleepTask( TASK_NO_GAME_TIMER );        //タイマー
                    SleepTask( TASK_NO_GAME_AIR );          //飛行機タスク
                    SleepTask( TASK_NO_GAME_CROW );         //カラスタスク
                    SleepTask( TASK_NO_GAME_ENEMY );        //敵タスク
                    SleepTask( TASK_NO_GAME_QUIZ );         //クイズタスク
                    SleepTask( TASK_NO_GAME_EFFECT );       //エフェクトタスク
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
                    WakeupTask( TASK_NO_GAME_TIMER );       //タイマー
                    WakeupTask( TASK_NO_GAME_AIR );         //飛行機タスク
                    WakeupTask( TASK_NO_GAME_CROW );        //カラスタスク
                    WakeupTask( TASK_NO_GAME_ENEMY );       //敵タスク
                    WakeupTask( TASK_NO_GAME_QUIZ );        //クイズタスク
                    WakeupTask( TASK_NO_GAME_EFFECT );      //エフェクトタスク
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
        //----------------------------------------------------------------終了
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
//  関数名 :AirTask
//
//  work   :飛行機タスク
//  in     :TASK*   タスクポインタ
//  out    :TRUE
//  note   :なし
//-----------------------------------------------------------------------------
static int AirTask(TASK* ip_task)
{
    static int WaitAnmTable[]   = { AIR_CHAR_GUNGUN_00, AIR_CHAR_GUNGUN_01  };  //通常
    static int TrueAnmTable[]   = { AIR_CHAR_GUNGUN_02, AIR_CHAR_GUNGUN_03  };  //正解
    static int FalseAnmTable[]  = { AIR_CHAR_GUNGUN_08, AIR_CHAR_GUNGUN_08  };  //正解
    static int DamageAnmTable[] = { AIR_CHAR_GUNGUN_04, AIR_CHAR_GUNGUN_05  };  //衝突

    static int ShotSeTable[]    = { AIR_SE_00,AIR_SE_01,AIR_SE_02   };
    static int TrueSoundTable[] = { AIR_SE_05,AIR_SE_06,AIR_SE_07   };
    static int FalseSoundTable[]= { AIR_SE_10,AIR_SE_11,AIR_SE_12   };

    SPRITE_DATA SpData;
    TASK Task;
    int i,eindex,qresult;
    int randval;
    int shotsound,truesound,falsesound;


    switch( ip_task->mode )
    {
        //----------------------------------------------------------------初期化
        case TASK_MODE_INIT:
            //mode change
            ip_task->mode = TASK_MODE_MAIN;

            //飛行機
            AGameMgr.Air.Body.MoveCount     = 0;
            AGameMgr.Air.Body.Status        = AIR_APPEAR;
            AGameMgr.Air.Body.OPos.x        = AIR_OFFSET_X;
            AGameMgr.Air.Body.OPos.y        = AIR_OFFSET_Y;
            AGameMgr.Air.Body.OPos.z        = AIR_OFFSET_Z;
            AGameMgr.Air.Body.Pos.x         = AIR_POS_INIT_X;
            AGameMgr.Air.Body.Pos.y         = AIR_POS_LINE_02_INIT_Y;
            AGameMgr.Air.Body.Pos.z         = PRIORITY_AIR;
            AGameMgr.Air.Body.Anm.Data.no   = AIR_CHAR_GUNGUN_00;
            AGameMgr.Air.Body.Anm.Data.wt   = 0;
            AGameMgr.Air.Body.Anm.Index     = 0;
            AGameMgr.Air.Body.Spd.wx        = 0;
            AGameMgr.Air.Body.Spd.wy        = 0;
            AGameMgr.Air.Body.Spd.dx        = 0;
            AGameMgr.Air.Body.Spd.dy        = 0;
            AGameMgr.Air.Body.Spd.sx        = 0;
            AGameMgr.Air.Body.Spd.sy        = AIR_MOVE_SPEED_Y;
            AGameMgr.Air.Line               = BASE_ALINE_02;
            AGameMgr.Air.Time               = 0;
            AGameMgr.Air.ItemIndex          = 0;
            AGameMgr.Air.ItemNo             = 0;
            AGameMgr.Air.DustNo             = 0;
            AGameMgr.Air.ItemOPx            = 0;
            AGameMgr.Air.ItemOPy            = 0;
            AGameMgr.Air.DustOPx            = 0;
            AGameMgr.Air.DustOPy            = 0;
            
            //継続プレイの場合はコントロール可能


            if(AGameMgr.Air.ContinueFlag)
            {
                AGameMgr.Air.ControllFlag=1;
            }else
            {
                AGameMgr.Air.ControllFlag=0;
            }

            //ハンド
            AGameMgr.Air.Hand.MoveCount     = 0;
            AGameMgr.Air.Hand.Status        = HAND_NONE;
            AGameMgr.Air.Hand.OPos.x        = AIR_HAND_OFFSET_X;
            AGameMgr.Air.Hand.OPos.y        = AIR_HAND_OFFSET_Y;
            AGameMgr.Air.Hand.OPos.z        = AIR_HAND_OFFSET_Z;
            AGameMgr.Air.Hand.Pos.x         = 0;
            AGameMgr.Air.Hand.Pos.y         = 0;
            AGameMgr.Air.Hand.Pos.z         = PRIORITY_AIR_HAND;
            AGameMgr.Air.Hand.Anm.Data.no   = AIR_CHAR_HAND_PA;
            AGameMgr.Air.Hand.Anm.Data.wt   = 0;
            AGameMgr.Air.Hand.Anm.Index     = 0;
            AGameMgr.Air.Hand.Spd.wx        = 0;
            AGameMgr.Air.Hand.Spd.wy        = 0;
            AGameMgr.Air.Hand.Spd.dx        = 0;
            AGameMgr.Air.Hand.Spd.dy        = 0;
            AGameMgr.Air.Hand.Spd.sx        = AIR_HAND_MOVE_SPEED_X;
            AGameMgr.Air.Hand.Spd.sy        = 0;

            break;
            
        //----------------------------------------------------------------メイン
        case TASK_MODE_MAIN:
            switch( AGameMgr.Air.Body.Status )
            {
                //------------------------------出現
                case AIR_APPEAR:
                    
                    //キー待ちへ
                    AGameMgr.Air.Body.Status = AIR_WAIT;
                    
                    break;
                //------------------------------キー待ち
                case AIR_WAIT:
                    //移動カウントクリア
                    AGameMgr.Air.Body.MoveCount = 0;
                    
                    //キー待ちのときのみ衝突チェック
                    if( CheckHitAirToEnemy() )
                    {//衝突
                        //ステータスを衝突へ
                        AGameMgr.Air.Body.Status = AIR_DAMAGE;
                        
                        //アニメ時間
                        AGameMgr.Air.Time = AIR_DAMAGE_TIMER;
                        
                        //アニメ衝突へ
                        AGameMgr.Air.Body.Anm.Data.no = DamageAnmTable[0];
                        
                        //アニメコントロール
                        AGameMgr.Air.Body.Anm.Index     = 0;
                        AGameMgr.Air.Body.Anm.Data.wt   = AIR_DAMAGE_ANM_CHANGE_TIME;
                        
                        //相手に連絡 / 飛行機にぶつかった後
                        AGameMgr.Enemy.Body.Status  = ENEMY_MOVE_CRASH;
                        AGameMgr.Enemy.Flag         = 0;
                        
                        //煙エフェクト
                        CreateEffect(AIR_EFFECT_CRUSH,AGameMgr.Air.Body.Pos.x + AIR_SMOKE_OFFSET_X, AGameMgr.Air.Body.Pos.y + AIR_SMOKE_OFFSET_Y,PRIORITY_EFFECT_2);
                        
                        //[♪]衝突音
                        ssPlaySe(AIR_SE_04);
                        //[♪]衝突音
                        ssPlaySe(AIR_SE_17);
                        
                    }else
                    {//順調
                        if( --AGameMgr.Air.Body.Anm.Data.wt < 0 )
                        {//
                            AGameMgr.Air.Body.Anm.Index ^= 1;                           //インデックス
                            AGameMgr.Air.Body.Anm.Data.wt = AIR_DAMAGE_ANM_CHANGE_TIME; //タイマー
                        }
                        
                        //アニメ
                        AGameMgr.Air.Body.Anm.Data.no = WaitAnmTable[AGameMgr.Air.Body.Anm.Index];
                        
                        //ゲームクリア後
                        if(!AGameMgr.ClearFlag)
                        {
                            if(AGameMgr.Air.ControllFlag)
                            {//出現時は操作不可
                                if( JstPad &  PADRright )
                                {//●ボタンチェック
                                    
                                    //アームが伸びる
                                    //ステータスキャッチング行きへ
                                    AGameMgr.Air.Body.Status    = AIR_CATCH_GOING;
                                    
                                    //ハンドセット
                                    AGameMgr.Air.Hand.Anm.Data.no   = AIR_CHAR_HAND_PA;
                                    AGameMgr.Air.Hand.Status        = HAND_CATCH_GOING;
                                    AGameMgr.Air.Hand.Pos.x         = AGameMgr.Air.Body.Pos.x + AIR_HAND_POS_OFFSET_X;
                                    AGameMgr.Air.Hand.Pos.y         = AGameMgr.Air.Body.Pos.y + AIR_HAND_POS_OFFSET_Y;
                                    AGameMgr.Air.Hand.MoveCount     = 0;
                                    
                                    //[♪]掛け声
                                    shotsound = rand() % 3;
                                    ssPlaySe( ShotSeTable[shotsound] );
                                    
                                    //[♪]マジックハンド
                                    ssPlaySe(AIR_SE_15);
                                
                                }else
                                if( JstPad & PADLup )
                                {//↑チェック
                                    if(AGameMgr.Air.Line != BASE_ALINE_01)
                                    {//一番上のラインにいない場合は上昇OK
                                        //ステ－タス上昇へ
                                        AGameMgr.Air.Body.Status = AIR_MOVE_UP;
                                        
                                        //アニメパターン上昇へ
                                        AGameMgr.Air.Body.Anm.Data.no = AIR_CHAR_GUNGUN_07;
                                        
                                        //[♪]旋回音
                                        ssPlaySe(AIR_SE_13);
                                    }
                                }else
                                if( JstPad & PADLdown )
                                {//↓チェック
                                    if(AGameMgr.Air.Line != BASE_ALINE_03)
                                    {//一番下のラインにいなければ下降OK
                                        //ステ－タス下降へ
                                        AGameMgr.Air.Body.Status = AIR_MOVE_DOWN;
                                        
                                        //アニメパターン下降へ
                                        AGameMgr.Air.Body.Anm.Data.no = AIR_CHAR_GUNGUN_06;
                                        
                                        //[♪]旋回音
                                        ssPlaySe(AIR_SE_13);
                                    }
                                }else
                                {//
                                    
                                }
                            }
                        }
                    }
                    
                    break;
                //------------------------------上昇
                case AIR_MOVE_UP:
                    if( ++AGameMgr.Air.Body.MoveCount < AIR_MOVE_COUNT_Y )
                    {//移動中
                        AGameMgr.Air.Body.Pos.y -= AGameMgr.Air.Body.Spd.sy;
                    }else
                    {//ライン移動終了
                        //ステータスをキー待ちへ
                        AGameMgr.Air.Body.Status = AIR_WAIT;
                        
                        //現在のラインへ
                        if(--AGameMgr.Air.Line < BASE_ALINE_01 ) AGameMgr.Air.Line = BASE_ALINE_01;
                        
                        //Y座標再セット
                        AGameMgr.Air.Body.Pos.y = LinePosYTbl[AGameMgr.Air.Line];
                        
                        //アニメパターン通常へ
                        AGameMgr.Air.Body.Anm.Data.no = AIR_CHAR_GUNGUN_00;
                    }
                    
                    break;
                //------------------------------下降
                case AIR_MOVE_DOWN:
                    if( ++AGameMgr.Air.Body.MoveCount < AIR_MOVE_COUNT_Y )
                    {//移動中
                        AGameMgr.Air.Body.Pos.y += AGameMgr.Air.Body.Spd.sy;
                    }else
                    {//ライン移動終了
                        //ステータスをキー待ちへ
                        AGameMgr.Air.Body.Status = AIR_WAIT;
                        
                        //現在のラインへ
                        if(++AGameMgr.Air.Line > BASE_ALINE_03 ) AGameMgr.Air.Line = BASE_ALINE_03;
                        
                        //Y座標再セット
                        AGameMgr.Air.Body.Pos.y = LinePosYTbl[AGameMgr.Air.Line];
                        
                        //アニメパターン通常へ
                        AGameMgr.Air.Body.Anm.Data.no = AIR_CHAR_GUNGUN_00;
                    }
                    
                    break;
                //------------------------------キャッチング行き
                case AIR_CATCH_GOING:
                    
                    if( --AGameMgr.Air.Body.Anm.Data.wt < 0 )
                    {//
                        AGameMgr.Air.Body.Anm.Index ^= 1;                           //インデックス
                        AGameMgr.Air.Body.Anm.Data.wt = AIR_DAMAGE_ANM_CHANGE_TIME; //タイマー
                    }
                    //アニメ
                    AGameMgr.Air.Body.Anm.Data.no = WaitAnmTable[AGameMgr.Air.Body.Anm.Index];
                    
                    
                    if( CheckHitHandToPanel(&eindex,&qresult) )
                    {//答えパネル衝突
                        //[♪]キャッチ音
                        ssPlaySe(AIR_SE_19);
                        
                        if(qresult)
                        {//正解
                            //ステータスを正解へ
                            AGameMgr.Air.Body.Status = AIR_QUIZ_OK;
                            
                            //手のステータスをリターンへ
                            AGameMgr.Air.Hand.Status        = HAND_CATCH_RETURN;
                            
                            //パーからグーへ
                            AGameMgr.Air.Hand.Anm.Data.no   = AIR_CHAR_HAND_GU;
                            
                            //取得したアイテム
                            AGameMgr.Air.ItemNo             = GetItemTable[AGameMgr.Air.ItemIndex].EffectNo;
                            AGameMgr.Air.ItemOPx            = GetItemTable[AGameMgr.Air.ItemIndex].OPx;
                            AGameMgr.Air.ItemOPy            = GetItemTable[AGameMgr.Air.ItemIndex].OPy;
                            if(++AGameMgr.Air.ItemIndex>MAX_ITEM_NUM-1) AGameMgr.Air.ItemIndex = MAX_ITEM_NUM-1;
                            
                            //正解マーク
                            CreateEffect(AIR_EFFECT_MARU,   AGameMgr.Air.Body.Pos.x + RESULT_MARK_OFFSET_X,   AGameMgr.Air.Body.Pos.y + RESULT_MARK_OFFSET_Y,   PRIORITY_EFFECT_2);
                            CreateEffect(AIR_EFFECT_ONNPU,  AGameMgr.Air.Body.Pos.x + FEELING_MARK_OFFSET_X,  AGameMgr.Air.Body.Pos.y + FEELING_MARK_OFFSET_Y,  PRIORITY_EFFECT_2);
                            
                            //アイテムを取得した時はここ
                            AGameMgr.Enemy.Body.Status  = ENEMY_DEATH_WAIT;
                            //位置補正
                            AGameMgr.Enemy.Body.Pos.x   = EVEMY_BIRTH_POS_X;
                            //タイマーセット
                            AGameMgr.Enemy.Time = EnemyDeathWaitTable[AGameMgr.PlayLevel];
                            
                            //tタイマーが０以下のの場合は処理しない
                            if(AGameMgr.Timer>0)
                            {
                                //正解数
                                if(++AGameMgr.Question.ClearNum >= MAX_QUESTION_CLEAR_NUM)
                                {
                                    GameMgr.WaitFlag = ON;          // iwasawa Correction (2003/4/27)
                                    AGameMgr.Question.ClearNum = MAX_QUESTION_CLEAR_NUM;
                                
#ifndef __DEBUG_ALL_QUESTION_AIR__
                                    //タイマータスク削除（終了チェック削除）
                                    RemoveTask(TASK_NO_GAME_TIMER);
                                    RemoveTask(TASK_NO_GAME_PAUSE);
                                    
                                    //クリアフラグセット
                                    AGameMgr.ClearFlag=1;
                                    
                                    //[♪]ヒャッホー
                                    dsPlayXa(XA_FILE_AIR02,4);
#endif
                                }
                            }

                            //----カラス情報変更
                            for(i=0;i<MAX_CROW_NUM;i++)
                            {
                                
                                //----カラス情報変更
                                AGameMgr.Crow[i].Flag               = 0;                        //カラス存在フラグオフ
                                AGameMgr.Crow[i].Body.Status        = CROW_SURPRISE;            //ステータス変更    答えを奪われ驚きへ
                                AGameMgr.Crow[i].Panel.Anm.Data.wt  = CROW_FUKURO_FLUSH_TIME;   //フラッシュタイムセット
                                AGameMgr.Crow[i].Time               = CROW_SURPRISE_WAIT_TIME;  //驚きアクション時間
                                
                                //驚きの時の絵を正解とそれ以外の場合は変更する
                                if(i==eindex){
                                //  AGameMgr.Crow[i].Body.Anm.Data.no   = AIR_CHAR_CROW_00; //驚き
                                //  AGameMgr.Crow[i].Body.Anm.Index     = 0;
                                //  AGameMgr.Crow[i].Body.Anm.Data.wt   = 0;
                                    AGameMgr.Crow[i].AnmBase            = CROW_ANM_BASE_SUPRISE;
                                    
                                    AGameMgr.Crow[i].CheckPanel         = 1;
                                }else{
                                //  AGameMgr.Crow[i].Body.Anm.Data.no   = AIR_CHAR_CROW_01; //通常
                                //  AGameMgr.Crow[i].Body.Anm.Index     = 0;
                                //  AGameMgr.Crow[i].Body.Anm.Data.wt   = 0;
                                    AGameMgr.Crow[i].AnmBase            = CROW_ANM_BASE_FLY;
                                }
                            }

                            //[♪]正解効果音
                            ssPlaySe(AIR_SE_16);
                            
                            //[♪]正解
                            truesound = rand() % 3;
                            ssPlaySe(TrueSoundTable[truesound]);
                            
                            //[♪]カラス悲鳴
                            ssPlaySe(AIR_SE_08);
                            
                        }else
                        {//不正解
                            //ステータスを不正解へ
                            AGameMgr.Air.Body.Status = AIR_QUIZ_NG;
                            
                            //手のステータスをリターンへ
                            AGameMgr.Air.Hand.Status    = HAND_CATCH_RETURN;
                            
                            //パーからグーへ
                            AGameMgr.Air.Hand.Anm.Data.no   = AIR_CHAR_HAND_GU;
                            
                            //取得したゴミ
                            randval                         = rand() % MAX_DUST_NUM;
                            AGameMgr.Air.DustNo             = GetDustTable[randval].EffectNo;
                            AGameMgr.Air.DustOPx            = GetDustTable[randval].OPx;
                            AGameMgr.Air.DustOPy            = GetDustTable[randval].OPy;
                            
                            //失敗マーク
                            CreateEffect(AIR_EFFECT_BATSU,  AGameMgr.Air.Body.Pos.x + RESULT_MARK_OFFSET_X,   AGameMgr.Air.Body.Pos.y + RESULT_MARK_OFFSET_Y    ,PRIORITY_EFFECT_2);
                            CreateEffect(AIR_EFFECT_ASE,    AGameMgr.Air.Body.Pos.x + FEELING_MARK_OFFSET_X,  AGameMgr.Air.Body.Pos.y + FEELING_MARK_OFFSET_Y   ,PRIORITY_EFFECT_2);
                            
                            //アイテムをした時はここ
                            AGameMgr.Enemy.Body.Status  = ENEMY_DEATH_WAIT;
                            //位置補正
                            AGameMgr.Enemy.Body.Pos.x   = EVEMY_BIRTH_POS_X;
                            //タイマーセット
                            AGameMgr.Enemy.Time = EnemyDeathWaitTable[AGameMgr.PlayLevel];
                            
                            //----カラス情報変更
                            AGameMgr.Crow[eindex].Flag              = 0;                        //カラス存在フラグオフ
                            AGameMgr.Crow[eindex].Body.Status       = CROW_SURPRISE;            //ステータス変更    答えを奪われ驚きへ
                            AGameMgr.Crow[eindex].Panel.Anm.Data.wt = CROW_FUKURO_FLUSH_TIME;   //フラッシュタイムセット
                            AGameMgr.Crow[eindex].Time              = CROW_SURPRISE_WAIT_TIME;  //驚きアクション時間
                        //  AGameMgr.Crow[eindex].Body.Anm.Data.no  = AIR_CHAR_CROW_00;         //
                        
                            AGameMgr.Crow[eindex].Body.Anm.Index    = 0;
                            AGameMgr.Crow[eindex].Body.Anm.Data.wt  = 0;
                            AGameMgr.Crow[eindex].AnmBase           = CROW_ANM_BASE_SUPRISE;
                            
                            AGameMgr.Crow[eindex].CheckPanel    = 1;
                            
                            //[♪]不正解
                            falsesound = rand() % 3;
                            ssPlaySe(FalseSoundTable[falsesound]);
                            
                            //[♪]カラス悲鳴
                            ssPlaySe(AIR_SE_08);
                        }
                    }
                    else if( CheckHitHandToEnemy() )
                    {//敵と衝突
                        //[♪]はじかれ音
                        ssPlaySe(AIR_SE_14);

                        //キャッチング戻りへ
                        AGameMgr.Air.Body.Status = AIR_CATCH_RETURN;
                        
                        //手のステータスをリターンへ
                        AGameMgr.Air.Hand.Status    = HAND_CATCH_RETURN;
                    }else if( JstPad &  PADRright )
                    {//自分で戻す
                        //[♪]はじかれ音
                        ssPlaySe(AIR_SE_14);

                        //キャッチング戻りへ
                        AGameMgr.Air.Body.Status = AIR_CATCH_RETURN;
                        
                        //手のステータスをリターンへ
                        AGameMgr.Air.Hand.Status    = HAND_CATCH_RETURN;
                    }else
                    {//
                        if( ++AGameMgr.Air.Hand.MoveCount < AIR_HAND_MOVE_COUNT_X ){
                            AGameMgr.Air.Hand.Pos.x += AGameMgr.Air.Hand.Spd.sx;
                        }else{
                            //キャッチング戻りへ
                            AGameMgr.Air.Body.Status = AIR_CATCH_RETURN;
                            
                            //手のステータスをリターンへ
                            AGameMgr.Air.Hand.Status    = HAND_CATCH_RETURN;
                        }
                    }
                    
                    break;
                //------------------------------キャッチング戻り
                case AIR_CATCH_RETURN:
                    if( --AGameMgr.Air.Body.Anm.Data.wt < 0 )
                    {//
                        AGameMgr.Air.Body.Anm.Index ^= 1;                           //インデックス
                        AGameMgr.Air.Body.Anm.Data.wt = AIR_DAMAGE_ANM_CHANGE_TIME; //タイマー
                    }
                    //アニメ
                    AGameMgr.Air.Body.Anm.Data.no = WaitAnmTable[AGameMgr.Air.Body.Anm.Index];

                    //戻り処理
                    if( --AGameMgr.Air.Hand.MoveCount > 0 ){
                        AGameMgr.Air.Hand.Pos.x -= AGameMgr.Air.Hand.Spd.sx;
                    }else{
                        //ハンド再設定
                        AGameMgr.Air.Hand.Pos.x     = AGameMgr.Air.Body.Pos.x + AIR_HAND_POS_OFFSET_X;
                        AGameMgr.Air.Hand.MoveCount=0;
                        //待ちへ
                        AGameMgr.Air.Body.Status = AIR_WAIT;
                    }
                    break;
                //------------------------------敵にぶつかる
                case AIR_DAMAGE:
                    if( --AGameMgr.Air.Time < 0)
                    {
                        //ステータスをキー待ちへ
                        AGameMgr.Air.Body.Status = AIR_WAIT;
                        
                        //アニメパターン通常へ
                        AGameMgr.Air.Body.Anm.Data.no = WaitAnmTable[0];
                    }else
                    {
                        if( --AGameMgr.Air.Body.Anm.Data.wt < 0)
                        {//
                            AGameMgr.Air.Body.Anm.Index ^= 1;                           //インデックス
                            AGameMgr.Air.Body.Anm.Data.wt = AIR_DAMAGE_ANM_CHANGE_TIME; //タイマー
                        }
                    }

                    //アニメ
                    AGameMgr.Air.Body.Anm.Data.no = DamageAnmTable[AGameMgr.Air.Body.Anm.Index];
                    
                    break;
                //------------------------------クイズ正解
                case AIR_QUIZ_OK:
                    if( --AGameMgr.Air.Body.Anm.Data.wt < 0 )
                    {//
                        AGameMgr.Air.Body.Anm.Index ^= 1;                           //インデックス
                        AGameMgr.Air.Body.Anm.Data.wt = AIR_TRUE_ANM_CHANGE_TIME;   //タイマー
                    }
                    //アニメ
                    AGameMgr.Air.Body.Anm.Data.no = TrueAnmTable[AGameMgr.Air.Body.Anm.Index];

                    //戻り処理
                    if( --AGameMgr.Air.Hand.MoveCount > 0 ){
                        AGameMgr.Air.Hand.Pos.x -= AGameMgr.Air.Hand.Spd.sx;
                    }else{
                        //ハンド再設定
                        AGameMgr.Air.Hand.Pos.x     = AGameMgr.Air.Body.Pos.x + AIR_HAND_POS_OFFSET_X;
                        AGameMgr.Air.Hand.MoveCount=0;
                        //待ちへ
                        AGameMgr.Air.Body.Status = AIR_WAIT;
                    }

                    break;
                //------------------------------クイズ不正解
                case AIR_QUIZ_NG:
                    if( --AGameMgr.Air.Body.Anm.Data.wt < 0 )
                    {//
                        AGameMgr.Air.Body.Anm.Index ^= 1;                           //インデックス
                        AGameMgr.Air.Body.Anm.Data.wt = AIR_FALSE_ANM_CHANGE_TIME;  //タイマー
                    }
                    //アニメ
                    AGameMgr.Air.Body.Anm.Data.no = FalseAnmTable[AGameMgr.Air.Body.Anm.Index];
                    
                    //戻り処理
                    if( --AGameMgr.Air.Hand.MoveCount > 0 ){
                        AGameMgr.Air.Hand.Pos.x -= AGameMgr.Air.Hand.Spd.sx;
                    }else{
                        //ハンド再設定
                        AGameMgr.Air.Hand.Pos.x     = AGameMgr.Air.Body.Pos.x + AIR_HAND_POS_OFFSET_X;
                        AGameMgr.Air.Hand.MoveCount=0;
                        //待ちへ
                        AGameMgr.Air.Body.Status = AIR_WAIT;
                    }
                    break;
                //------------------------------クリア
                case AIR_CLEAR:
                    if( --AGameMgr.Air.Body.Anm.Data.wt < 0 )
                    {//
                        AGameMgr.Air.Body.Anm.Index ^= 1;                           //インデックス
                        AGameMgr.Air.Body.Anm.Data.wt = AIR_TRUE_ANM_CHANGE_TIME;   //タイマー
                    }
                    //アニメ
                    AGameMgr.Air.Body.Anm.Data.no = WaitAnmTable[AGameMgr.Air.Body.Anm.Index];

                    AGameMgr.ClearTimer++;
                    if((AGameMgr.ClearTimer%15)==0)
                    {
                        CreateEffect(AIR_EFFECT_SMOKE,AGameMgr.Air.Body.Pos.x - 25, AGameMgr.Air.Body.Pos.y+8,PRIORITY_EFFECT_2);
                    }
                    
                    AGameMgr.Air.Body.Pos.x += 2;
                    if(AGameMgr.Air.Body.Pos.x>400)
                    {
                        AGameMgr.ClearEnd   = 1;
//                      Task.func           = EventFadeOutTask;
//                      Task.priority       = TASK_NO_GAME_FADE;
//                      Task.attribute      = ATTR_USER;
//                      Task.status         = TASK_NEW_ENTRY;
//                      Task.id             = TASK_NO_GAME_FADE;
//                      Task.wait_time      = 0;
//                      Task.buf            = NULL;
//                      Task.name           = "EventFadeOutTask";
//                      Task.mode           = TASK_MODE_INIT;
//                      Task.user[0]        = ip_task->id;
//                      CreateTask(&Task);
                    }
                    
                    break;
                //------------------------------タイムアップ
                case AIR_TIMEUP:
                    
                    break;
                default:
            }

            //--------------- 描画　アーム＆手
            if( AGameMgr.Air.Body.Status==AIR_CATCH_GOING               ||
                        AGameMgr.Air.Body.Status==AIR_CATCH_RETURN      ||
                            AGameMgr.Air.Body.Status==AIR_QUIZ_OK       ||
                                AGameMgr.Air.Body.Status==AIR_QUIZ_NG){
                
                //手
                SpData.No       = AGameMgr.Air.Hand.Anm.Data.no;
                SpData.PosX     = AGameMgr.Air.Hand.Pos.x - AGameMgr.Air.Hand.OPos.x;
                SpData.PosY     = AGameMgr.Air.Hand.Pos.y - AGameMgr.Air.Hand.OPos.y;
                SpData.PosZ     = PRIORITY_AIR_HAND;
                SpData.ScaleX   = SCALE10;
                SpData.ScaleY   = SCALE10;
                SpData.Rotate   = ROTATE000;
                SpData.Reverse  = NOREVERS;
                DrawSprite( &SpData );

                //伸びる腕
                DrawArm( AGameMgr.Air.Hand.MoveCount*AIR_HAND_MOVE_SPEED_X+AIR_ARM_LENGTH_OFFSET_X, AGameMgr.Air.Body.Pos.x+AIR_ARM_OFFSET_X, AGameMgr.Air.Body.Pos.y+AIR_ARM_OFFSET_Y );

                //アイテム
                if( AGameMgr.Air.Body.Status==AIR_QUIZ_OK )
                {//アイテム表示
                    CreateEffect(AGameMgr.Air.ItemNo, AGameMgr. Air.Hand.Pos.x + AGameMgr.Air.ItemOPx, AGameMgr.Air.Hand.Pos.y+AGameMgr.Air.ItemOPy,PRIORITY_EFFECT);
                }else if( AGameMgr.Air.Body.Status==AIR_QUIZ_NG )
                {//ゴミ表示
                    CreateEffect(AGameMgr.Air.DustNo, AGameMgr.Air.Hand.Pos.x + AGameMgr.Air.DustOPx, AGameMgr.Air.Hand.Pos.y + AGameMgr.Air.DustOPy,PRIORITY_EFFECT);
                }else
                {//表示しない
                    
                }
            }
            //--------------- 描画　飛行機本体
            SpData.No       = AGameMgr.Air.Body.Anm.Data.no;
            SpData.PosX     = AGameMgr.Air.Body.Pos.x - AGameMgr.Air.Body.OPos.x;
            
            //位置補正
            if(AGameMgr.Air.Body.Anm.Data.no==AIR_CHAR_GUNGUN_08)   SpData.PosY     = AGameMgr.Air.Body.Pos.y - AGameMgr.Air.Body.OPos.y + 2;
            else                                                    SpData.PosY     = AGameMgr.Air.Body.Pos.y - AGameMgr.Air.Body.OPos.y;

            SpData.PosZ     = AGameMgr.Air.Body.Pos.z;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );
            
            break;

        //----------------------------------------------------------------終了
        case TASK_MODE_EXIT:
            
        //  //クリアフラグセット
        //  AGameMgr.ClearEnd=1;
            
            break;
        default:
    }
}


//-----------------------------------------------------------------------------
//  関数名 :BgTask
//
//  work   :背景タスク
//  in     :TASK*   タスクポインタ
//  out    :TRUE
//  note   :なし
//-----------------------------------------------------------------------------
static int BgTask(TASK* ip_task)
{
    int i,addx;
    SPRITE_DATA SpData;

    static int MountainPtnTbl[MOUNTAIN_NUM]={
        0,1,0,1,0,1,0,1,0,1,    //10
    };

    static int MountainSizeW[]={
        MOUNTAIN_01_SIZE_W-1,
        MOUNTAIN_00_SIZE_W,
    };


    switch( ip_task->mode )
    {
        case TASK_MODE_INIT:
            //change mode
            ip_task->mode = TASK_MODE_MAIN;

            ip_task->user[BG_TASK_COUNTER]              = 0;
            ip_task->user[BG_TASK_MOUNTASIN_BASE_X]     = MOUNTASIN_INIT_X;
            ip_task->user[BG_TASK_CLOUD_LARGE_POS_X]    = COLUD_LARGE_INIT_X;
            ip_task->user[BG_TASK_CLOUD_MIDDLE_POS_X]   = COLUD_MIDDLE_INIT_X;
            ip_task->user[BG_TASK_CLOUD_SMALL_POS_X]    = COLUD_SMALL_INIT_X;
            
            break;
        case TASK_MODE_MAIN:
            ip_task->user[BG_TASK_COUNTER]++;

            //--------------- 山
            addx    = 0;
            for(i=0;i<MOUNTAIN_NUM;i++)
            {
                addx += MountainSizeW[ MountainPtnTbl[i] ];
                
                //山
                SpData.No       = AIR_CHAR_MOUNTAIN_00 + MountainPtnTbl[i];
                SpData.PosX     = ip_task->user[BG_TASK_MOUNTASIN_BASE_X] + addx;

                if( SpData.PosX > -320 && SpData.PosX < 340 ){
                    SpData.PosY     = MOUNTAIN_POS_Y;
                    SpData.PosZ     = PRIORITY_MOUNTAIN;
                    SpData.ScaleX   = SCALE10;
                    SpData.ScaleY   = SCALE10;
                    SpData.Rotate   = ROTATE000;
                    SpData.Reverse  = NOREVERS;
                    DrawSprite( &SpData );
                }
            }

            if(ip_task->user[BG_TASK_MOUNTASIN_BASE_X] <= MOUNTASIN_INIT_X - 327 )
            {//loop
                ip_task->user[BG_TASK_MOUNTASIN_BASE_X] = MOUNTASIN_INIT_X;
            }

            //scroll
            if( (ip_task->user[BG_TASK_COUNTER] % DIV_MOUNTAIN_SPD_X) == 0 ){
                ip_task->user[BG_TASK_MOUNTASIN_BASE_X] -= MOUNTAIN_SPD_X;
            }

            //--------------- 雲（大）
            SpData.No       = AIR_CHAR_CLOUD_LARGE;
            SpData.PosX     = ip_task->user[BG_TASK_CLOUD_LARGE_POS_X];
            SpData.PosY     = CLOUD_LARGE_POS_Y;
            SpData.PosZ     = PRIORITY_CLOUD_LARGE;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );

            if( (ip_task->user[BG_TASK_COUNTER] % DIV_CLOUD_LARGE_SPD_X)==0 ){
                ip_task->user[BG_TASK_CLOUD_LARGE_POS_X] -= CLOUD_LARGE_SPD_X;
            }
            
            if( ip_task->user[BG_TASK_CLOUD_LARGE_POS_X] < COLUD_LARGE_OUT_X){
                ip_task->user[BG_TASK_CLOUD_LARGE_POS_X] = COLUD_LARGE_INIT_X;
            } 

            //--------------- 雲（中）
            SpData.No       = AIR_CHAR_CLOUD_MIDDLE;
            SpData.PosX     = ip_task->user[BG_TASK_CLOUD_MIDDLE_POS_X];
            SpData.PosY     = CLOUD_MIDDLE_POS_Y;
            SpData.PosZ     = PRIORITY_CLOUD_MIDDLE;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );

            if( (ip_task->user[BG_TASK_COUNTER] % DIV_CLOUD_MIDDLE_SPD_X)==0 ){
                ip_task->user[BG_TASK_CLOUD_MIDDLE_POS_X] -= CLOUD_MIDDLE_SPD_X;
            }

            if( ip_task->user[BG_TASK_CLOUD_MIDDLE_POS_X] < COLUD_MIDDLE_OUT_X){
                ip_task->user[BG_TASK_CLOUD_MIDDLE_POS_X] = COLUD_MIDDLE_INIT_X;
            }

            //--------------- 雲（小）
            SpData.No       = AIR_CHAR_CLOUD_SMALL;
            SpData.PosX     = ip_task->user[BG_TASK_CLOUD_SMALL_POS_X];
            SpData.PosY     = CLOUD_SMALL_POS_Y;
            SpData.PosZ     = PRIORITY_CLOUD_SMALL;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );

            if( (ip_task->user[BG_TASK_COUNTER] % DIV_CLOUD_SMALL_SPD_X)==0 ){
                ip_task->user[BG_TASK_CLOUD_SMALL_POS_X] -= CLOUD_SMALL_SPD_X;
            }

            if( ip_task->user[BG_TASK_CLOUD_SMALL_POS_X] < COLUD_SMALL_OUT_X){
                ip_task->user[BG_TASK_CLOUD_SMALL_POS_X] = COLUD_SMALL_INIT_X;
            }

            //背景青空左
            SpData.No       = AIR_CHAR_GAME_BG_00;
            SpData.PosX     = 0;
            SpData.PosY     = 0;
            SpData.PosZ     = PRIORITY_BG;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );

            //背景青空右
            SpData.No       = AIR_CHAR_GAME_BG_01;
            SpData.PosX     = 256;
            SpData.PosY     = 0;
            SpData.PosZ     = PRIORITY_BG;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );

            break;
        case TASK_MODE_EXIT:
            break;
        default:
    }

    return TRUE;
}


//-----------------------------------------------------------------------------
//  関数名 :QuizTask
//
//  work   :クイズタスク
//  in     :TASK*   タスクポインタ
//  out    :TRUE
//  note   :なし
//-----------------------------------------------------------------------------
static int QuizTask( TASK* ip_task )
{
    static int lnum=0;
    static int qindex=0;
    
    int i;
    SPRITE_DATA SpData;
    TASK Task;


    switch( ip_task->mode )
    {
        case TASK_MODE_INIT:
            //----next mode
            ip_task->mode = TASK_MODE_MAIN;
            
            break;
        case TASK_MODE_MAIN:
            //--------------------------------▼
            //大きい方の数字
//          DrawNo(lnum,QUESTION_TEXT_WIDE_LARGE,QuestionTextNoLargeTable,20,180,PRIORITY_EFFECT_2);

            //小さい方の数字
//          DrawNo(lnum,QUESTION_TEXT_WIDE_SMALL,QuestionTextNoSmallTable,20,200,PRIORITY_EFFECT_2);

            //ボール描画
//          DrawBall(BALL_COLOR_RED,    10,240,110,PRIORITY_QUIZ_TEXT_FRUIT);
//          DrawBall(BALL_COLOR_ORANGE, 10,240,140,PRIORITY_QUIZ_TEXT_FRUIT);

            //フルーツ描画
//          DrawFruits(FRUITS_APPLE,    10,240,170,PRIORITY_QUIZ_TEXT_FRUIT);
//          DrawFruits(FRUITS_MIKAN,    10,240,200,PRIORITY_QUIZ_TEXT_FRUIT);

            //パネル付番号描画
//          DrawNoPanel(PANEL_COLOR_BLUE, 12,290,180,PRIORITY_QUIZ_TEXT_PANEL);
//          DrawNoPanel(PANEL_COLOR_PINK, 20,290,210,PRIORITY_QUIZ_TEXT_PANEL);

//          //番号
//          DrawNoLarge( 9,290, 80,PRIORITY_QUIZ_TEXT_NUM);
//          DrawNoLarge(13,290,100,PRIORITY_QUIZ_TEXT_NUM);
//          DrawNoLarge(23,290,120,PRIORITY_QUIZ_TEXT_NUM);
//          DrawNoLarge(33,290,140,PRIORITY_QUIZ_TEXT_NUM);
//          DrawNoLarge(43,290,160,PRIORITY_QUIZ_TEXT_NUM);

            //--------------------------------▲
//          if( JstPad & PADL1 ){
//              if(++qindex>44){
//                  qindex=0;
//              }
//          }

            //--------問題描画
            if(AGameMgr.Question.TextFlag)
            {
                DrawQuestionText(   QuestionTopData[AGameMgr.PlayLevel][AGameMgr.Question.Num][AGameMgr.Question.Index].Kind,
                                    QuestionTopData[AGameMgr.PlayLevel][AGameMgr.Question.Num][AGameMgr.Question.Index].No  );
            }

            //--------正解数描画
            DrawCorrectAnswerNo(AGameMgr.Question.ClearNum, 218, 29);

            //--------クイズパネル描画
            //--クイズパネル左
            SpData.No       = AIR_CHAR_QUESTION_PLATE_LEFT;
            SpData.PosX     = 16;
            SpData.PosY     = 0;
            SpData.PosZ     = PRIORITY_QUIZ_PANEL;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );
            
            //--クイズパネル真中
            for(i=0;i<23;i++)
            {
                SpData.No       = AIR_CHAR_QUESTION_PLATE_CENTER;
                SpData.PosX     = 32 + i*8;
                SpData.PosY     = 0;
                SpData.PosZ     = PRIORITY_QUIZ_PANEL;
                SpData.ScaleX   = SCALE10;
                SpData.ScaleY   = SCALE10;
                SpData.Rotate   = ROTATE000;
                SpData.Reverse  = NOREVERS;
                DrawSprite( &SpData );
            }

            //--クイズパネル右
            SpData.No       = AIR_CHAR_QUESTION_PLATE_RIGHT;
            SpData.PosX     = 216;
            SpData.PosY     = 0;
            SpData.PosZ     = PRIORITY_QUIZ_PANEL;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );

            break;
        case TASK_MODE_EXIT:
            break;
        default:
    }

    return TRUE;
}


//-----------------------------------------------------------------------------
//  関数名 :CrowTask
//
//  work   :カラスタスク
//  in     :タスクポインタ
//  out    :TRUE
//  note   :なし
//-----------------------------------------------------------------------------
static int CrowTask(TASK* ip_task)
{
    int i;
    SPRITE_DATA SpData;
    ANSWER Answer;
    int Xaflag;


    switch(ip_task->mode)
    {
        //--------------------------------------------------------------------初期化
        case TASK_MODE_INIT:
            //change mode
            ip_task->mode = TASK_MODE_MAIN;

            for(i=0;i<MAX_CROW_NUM;i++)
            {//初期化
                AGameMgr.Crow[i].Body.MoveCount             = 0;
                AGameMgr.Crow[i].Body.Status                = CROW_BIRTH;
                AGameMgr.Crow[i].Body.OPos.x                = 26;
                AGameMgr.Crow[i].Body.OPos.y                = 23;
                AGameMgr.Crow[i].Body.OPos.z                = 0;
                AGameMgr.Crow[i].Body.Pos.x                 = CROW_BIRTH_POS_X;
                AGameMgr.Crow[i].Body.Pos.y                 = LinePosYTbl[i];
                AGameMgr.Crow[i].Body.Pos.z                 = PRIORITY_CROW;
                AGameMgr.Crow[i].Body.Anm.Data.no           = AIR_CHAR_CROW_01;
                AGameMgr.Crow[i].Body.Anm.Data.wt           = 0;
                AGameMgr.Crow[i].Body.Anm.Index             = 0;
                AGameMgr.Crow[i].Body.Spd.wx                = 0;
                AGameMgr.Crow[i].Body.Spd.wy                = 0;
                AGameMgr.Crow[i].Body.Spd.dx                = 0;
                AGameMgr.Crow[i].Body.Spd.dy                = 0;
                AGameMgr.Crow[i].Body.Spd.sx                = CROW_SPEED_X;
                AGameMgr.Crow[i].Body.Spd.sy                = 0;

                //----問題セット
                GetAnswerData(  QuestionTopData[AGameMgr.PlayLevel][AGameMgr.Question.Num][AGameMgr.Question.Index].Kind,
                                QuestionTopData[AGameMgr.PlayLevel][AGameMgr.Question.Num][AGameMgr.Question.Index].No,
                                i,&Answer);
                
                AGameMgr.Crow[i].Ans.QuestionData.Kind      = Answer.QuestionData.Kind;
                AGameMgr.Crow[i].Ans.QuestionData.No        = Answer.QuestionData.No;
                AGameMgr.Crow[i].Ans.Flag                   = Answer.Flag;
                AGameMgr.Crow[i].Ans.QuestionData.Attr      = Answer.QuestionData.Attr;
                //----
                AGameMgr.Crow[i].AnmBase            = CROW_ANM_BASE_FLY;
                AGameMgr.Crow[i].Flag               = 0;
                AGameMgr.Crow[i].Line               = LineTbl[i];
                AGameMgr.Crow[i].Time               = 0;
                
                AGameMgr.Crow[i].Panel.MoveCount    = 0;
                AGameMgr.Crow[i].Panel.Status       = CROW_BIRTH;
                AGameMgr.Crow[i].Panel.OPos.x       = 20;
                AGameMgr.Crow[i].Panel.OPos.y       = 34;
                AGameMgr.Crow[i].Panel.OPos.z       = 0;
                AGameMgr.Crow[i].Panel.Pos.x        = 0;
                AGameMgr.Crow[i].Panel.Pos.y        = LinePosYTbl[i];
                AGameMgr.Crow[i].Panel.Pos.z        = PRIORITY_CROW_PANEL;
                AGameMgr.Crow[i].Panel.Anm.Data.no  = AIR_CHAR_FUKURO;
                AGameMgr.Crow[i].Panel.Anm.Data.wt  = 0;
                AGameMgr.Crow[i].Panel.Anm.Index    = 1;
                AGameMgr.Crow[i].Panel.Spd.wx       = 0;
                AGameMgr.Crow[i].Panel.Spd.wy       = 0;
                AGameMgr.Crow[i].Panel.Spd.dx       = 0;
                AGameMgr.Crow[i].Panel.Spd.dy       = 0;
                AGameMgr.Crow[i].Panel.Spd.sx       = CROW_FUKURO_SPEED_X;
                AGameMgr.Crow[i].Panel.Spd.sy       = 0;
                AGameMgr.Crow[i].CheckPanel         = 0;
            }

            //[♪]出題音
            ssPlaySe(AIR_SE_18);

            //[♪]問題音声

            PlayQuestion(   QuestionTopData[AGameMgr.PlayLevel][AGameMgr.Question.Num][AGameMgr.Question.Index].Kind,
                            QuestionTopData[AGameMgr.PlayLevel][AGameMgr.Question.Num][AGameMgr.Question.Index].No);

            break;
        //--------------------------------------------------------------------メイン
        case TASK_MODE_MAIN:
            Xaflag = 0;
            //----
            for(i=0;i<MAX_CROW_NUM;i++)
            {
                //------------------------------カラス
                switch(AGameMgr.Crow[i].Body.Status)
                {
                    //--------------------セット
                    case CROW_BIRTH:
                        //ステータスを出現へ
                        AGameMgr.Crow[i].Body.Status=CROW_APPEAR;
                        
                        //存在フラグON
                        AGameMgr.Crow[i].Flag               = 1;
                        
                        //問題セットなど
                        
                        
                        break;
                    //--------------------出現（左から）
                    case CROW_APPEAR:
                        //移動
                        AGameMgr.Crow[i].Body.Pos.x-=AGameMgr.Crow[i].Body.Spd.sx;
                        if(AGameMgr.Crow[i].Body.Pos.x < CROW_WAIT_POS_X)
                        {
                            //停止位置
                            AGameMgr.Crow[i].Body.Pos.x=CROW_WAIT_POS_X;
                            
                            //ステータス変更
                            AGameMgr.Crow[i].Body.Status=CROW_WAIT;
                        }
                        
                        break;
                    //--------------------答えぶら下げ待ち
                    case CROW_WAIT:
                        
                        
                        
                        break;
                    //--------------------答えを奪われ驚き
                    case CROW_SURPRISE:
                        if(--AGameMgr.Crow[i].Time < 0 )
                        {
                            if(AGameMgr.Crow[i].Ans.Flag)
                            {//正解なら "CROW_OK_RETURN"
                                //ステータス変更    戻る（右へ）
                                AGameMgr.Crow[i].Body.Status        = CROW_OK_RETURN;
                            //  AGameMgr.Crow[i].Body.Anm.Data.no   = AIR_CHAR_CROW_01;
                            //  AGameMgr.Crow[i].Body.Anm.Index     = 0;
                            //  AGameMgr.Crow[i].Body.Anm.Data.wt   = 0;
                                AGameMgr.Crow[i].AnmBase            = CROW_ANM_BASE_FLY;
                                
                            }else
                            {//不正解なら "CROW_RETURN"
                                //ステータス変更    戻る（右へ）
                                AGameMgr.Crow[i].Body.Status        = CROW_RETURN;
                            //  AGameMgr.Crow[i].Body.Anm.Data.no   = AIR_CHAR_CROW_01;
                            //  AGameMgr.Crow[i].Body.Anm.Index     = 0;
                            //  AGameMgr.Crow[i].Body.Anm.Data.wt   = 0;
                                AGameMgr.Crow[i].AnmBase            = CROW_ANM_BASE_FLY;
                                
                            }
                            
                            //フラッシュ終了
                            AGameMgr.Crow[i].Panel.Anm.Index=1;
                        }
                        
                        
                        break;
                    //--------------------戻る（右へ）
                    case CROW_OK_RETURN:
                    case CROW_RETURN:
                        AGameMgr.Crow[i].Body.Pos.x+=AGameMgr.Crow[i].Body.Spd.sx;
                        if(AGameMgr.Crow[i].Body.Pos.x > CROW_BIRTH_POS_X)
                        {
                            //出現位置にて停止
                            AGameMgr.Crow[i].Body.Pos.x=CROW_BIRTH_POS_X;
                            
                            //ステータス変更    画面外待ちへ
                            AGameMgr.Crow[i].Body.Status=CROW_DEATH_WAIT;
                            
                            if(AGameMgr.Crow[i].Ans.Flag==1)
                            {//正解が画面外にいたら次の問題へ
                                
                                //タイムアップの場合は
                                if(AGameMgr.TimeUpSignal){
                                    AGameMgr.Crow[i].Body.Status=CROW_TIMEUP;
                                }else{
                                    //change mode
                                    ip_task->mode = TASK_MODE_INIT;
                                }
                                
                                //ここで次の問題へインデックス＋＋
                                if(++AGameMgr.Question.Index>MAX_QUESTION_NUM-1)
                                {
                                    //クリアチェック
                                    if(AGameMgr.ClearFlag)
                                    {
                                        //ステータス変更
                                        AGameMgr.Air.Body.Status = AIR_CLEAR;
                                        
                                        //レベルアップ
                                        if(++AGameMgr.PlayLevel>AIR_GAME_MAX_LEVEL_NUM-1){
                                            AGameMgr.PlayLevel=AIR_GAME_MAX_LEVEL_NUM-1;
                                            
                                            //オールクリアフラグセット
                                            AGameMgr.AllClearFlag   = 1;
                                        }
                                        
                                        //
                                        if(AGameMgr.PlayLevel>AGameMgr.Level)
                                        {//前回のレベルより高い場合は書き換える
                                            AGameMgr.Level=AGameMgr.PlayLevel;
                                        }
                                        
                                        //タスク削除
                                        RemoveTask(TASK_NO_GAME_ENEMY);     //敵タスク
                                        RemoveTask(TASK_NO_GAME_QUIZ );     //クイズタスク
                                        
                                        //自分を削除
                                        ExitTask(ip_task->id);              //カラスタスク
                                    }
                                    AGameMgr.Question.Index = MAX_QUESTION_NUM-1;
                                }
                            }
                            
                            //ここでもう一度存在フラグをOFFにする（すでにプレイヤーのタスクでOFFにしてある）
                            AGameMgr.Crow[i].Flag=0;
                            
                        }
                        break;
                    //--------------------画面外待ち
                    case CROW_DEATH_WAIT:
                        // 待っている
                        
                        break;
                    //--------------------画面外
                    case CROW_DEATH:
                        //ステータス変更    セット
                        AGameMgr.Crow[i].Body.Status=CROW_BIRTH;
                        break;
                    //--------------------タイムアップ
                    case CROW_TIMEUP:
                        
                        break;
                    default:
                }
                
                //------------------------------パネル描画
                if(AGameMgr.Crow[i].Body.Status==CROW_APPEAR ||                                 //出現
                            AGameMgr.Crow[i].Body.Status==CROW_WAIT ||                          //待ち
                                    AGameMgr.Crow[i].Body.Status==CROW_SURPRISE ||              //驚き
                                            AGameMgr.Crow[i].Body.Status==CROW_OK_RETURN ||     //正解
                                                AGameMgr.Crow[i].Body.Status==CROW_RETURN ||    //不正解
                                                    AGameMgr.Crow[i].Body.Status==CROW_TIMEUP ) //タイムアップ
                {//
                    if(AGameMgr.Crow[i].Body.Status==CROW_SURPRISE)
                    {//驚いているとき
                        if(AGameMgr.Crow[i].Body.Anm.Data.no==AIR_CHAR_CROW_00)
                        {//正解はフラッシュ
                            if(--AGameMgr.Crow[i].Panel.Anm.Data.wt<0)
                            {//フラッシュコントロール
                                AGameMgr.Crow[i].Panel.Anm.Index^=1;
                                AGameMgr.Crow[i].Panel.Anm.Data.wt=CROW_FUKURO_FLUSH_TIME;
                            }
                        }
                    }
                    
                    if(AGameMgr.Crow[i].Panel.Anm.Index)
                    {//
                        if( !((AGameMgr.Crow[i].Body.Status==CROW_OK_RETURN || AGameMgr.Crow[i].Body.Status==CROW_RETURN) && AGameMgr.Crow[i].CheckPanel ) )
                        {
                            //カラスの位置からのオフセット
                            AGameMgr.Crow[i].Panel.Pos.x = AGameMgr.Crow[i].Body.Pos.x;
                            AGameMgr.Crow[i].Panel.Pos.x += CROW_FUKURO_OFFSET_X;
                            AGameMgr.Crow[i].Panel.Pos.y = AGameMgr.Crow[i].Body.Pos.y;
                            AGameMgr.Crow[i].Panel.Pos.y += CROW_FUKURO_OFFSET_Y;
                            
                            SpData.No       = AGameMgr.Crow[i].Panel.Anm.Data.no;
                            SpData.PosX     = AGameMgr.Crow[i].Panel.Pos.x - AGameMgr.Crow[i].Panel.OPos.x;
                            SpData.PosY     = AGameMgr.Crow[i].Panel.Pos.y - AGameMgr.Crow[i].Panel.OPos.y;
                            SpData.PosZ     = AGameMgr.Crow[i].Panel.Pos.z;
                            SpData.ScaleX   = SCALE10;
                            SpData.ScaleY   = SCALE10;
                            SpData.Rotate   = ROTATE000;
                            SpData.Reverse  = NOREVERS;
                            DrawSprite( &SpData );
                        }
                    }
                }
                
                //------------------------------答え描画
                if(AGameMgr.Crow[i].Body.Status==CROW_APPEAR ||                                 //出現
                            AGameMgr.Crow[i].Body.Status==CROW_WAIT ||                          //待ち
                                    AGameMgr.Crow[i].Body.Status==CROW_SURPRISE ||              //驚き
                                            AGameMgr.Crow[i].Body.Status==CROW_RETURN ||        //不正解
                                                AGameMgr.Crow[i].Body.Status==CROW_TIMEUP )     //タイムアップ
                {
                    //正解は表示しない
                    if( !AGameMgr.Crow[i].CheckPanel )
                    {
                        //種類とインデック番号で表示
                        DrawSelectAnswer(   &(AGameMgr.Crow[i].Ans.QuestionData),
                                            AGameMgr.Crow[i].Body.Pos.x-52,
                                            AGameMgr.Crow[i].Body.Pos.y+2,
                                            PRIORITY_ANSWER_PANEL );
                    }
                }
                
                //------------------------------カラスアニメ
                if(++AGameMgr.Crow[i].Body.Anm.Data.wt>CROW_ANM_WAIT_TIME){
                    AGameMgr.Crow[i].Body.Anm.Data.wt   = 0;
                    AGameMgr.Crow[i].Body.Anm.Index     ^=1;
                }

                //----スプライトセット
                AGameMgr.Crow[i].Body.Anm.Data.no = CrowSpriteTable[ AGameMgr.Crow[i].AnmBase + AGameMgr.Crow[i].Body.Anm.Index];

                //------------------------------カラス描画
                SpData.No       = AGameMgr.Crow[i].Body.Anm.Data.no;
                SpData.PosX     = AGameMgr.Crow[i].Body.Pos.x - AGameMgr.Crow[i].Body.OPos.x;
                SpData.PosY     = AGameMgr.Crow[i].Body.Pos.y - AGameMgr.Crow[i].Body.OPos.y;
                SpData.PosZ     = AGameMgr.Crow[i].Body.Pos.z;
                SpData.ScaleX   = SCALE10;
                SpData.ScaleY   = SCALE10;
                SpData.Rotate   = ROTATE000;
                SpData.Reverse  = NOREVERS;
                DrawSprite( &SpData );
            }
            
            break;
        //--------------------------------------------------------------------終了
        case TASK_MODE_EXIT:
            break;
        default:
    }

    return TRUE;
}


//-----------------------------------------------------------------------------
//  関数名 :EnemyTask
//
//  work   :おじゃまキャラタスク
//  in     :タスクポインタ
//  out    :TRUE
//  note   :なし
//-----------------------------------------------------------------------------
static int EnemyTask(TASK* ip_task)
{
    static int EnemyType[]={
        ENEMY_TYPE_FUUSEN,
        ENEMY_TYPE_CLOUD,
        ENEMY_TYPE_AIRR,
    };

    static ENEMY_ANM_DATA EnemyAnmData[MAX_ENEMY_NUM][4] =
    {
        {//風船
            { AIR_CHAR_FUUSEN_00,       24,     18,     20,     0   },
            { AIR_CHAR_FUUSEN_01,       24,     18,     20,     0   },
            { AIR_CHAR_FUUSEN_02,       24,     18,     20,     0   },
            { ANM_REPEAT,               0,      0,      0,      0   },
        },
        {//雲
            { AIR_CHAR_THUBDER_LARGE,   24,     39,     21,     0   },
            { AIR_CHAR_THUBDER_SMALL,   24,     23,     21,     0   },
            { ANM_REPEAT,               0,      0,      0,      0   },
            { 0,0,0,0,0},
        },
        {//飛行機
            { AIR_CHAR_KUMA_00,         24,     27,     20,     0   },
            { AIR_CHAR_KUMA_01,         24,     27,     20,     0   },
            { ANM_REPEAT,               0,      0,      0,      0   },
            { 0,0,0,0,0},
        },
    };

    static int EnemySpeedWaitTable[]={
        ENEMY_SPD_X_WAIT_1, //LEVEL-1
        ENEMY_SPD_X_WAIT_0, //LEVEL-2
        ENEMY_SPD_X_WAIT_0, //LEVEL-3
    };

    static int EnemySpeedTable[]={
        ENEMY_SPD_X_1,      //LEVEL-1
        ENEMY_SPD_X_1,      //LEVEL-2
        ENEMY_SPD_X_1,      //LEVEL-3
    };


    SPRITE_DATA SpData;
    int eno,lno,i;


    switch( ip_task->mode )
    {
        case TASK_MODE_INIT:
            //change mode
            ip_task->mode = TASK_MODE_MAIN;
            
            //INIT
            AGameMgr.Enemy.Body.MoveCount   = 0;
            AGameMgr.Enemy.Body.Status      = ENEMY_BIRTH;
            AGameMgr.Enemy.Body.OPos.x      = 0;
            AGameMgr.Enemy.Body.OPos.y      = 0;
            AGameMgr.Enemy.Body.OPos.z      = 0;
            AGameMgr.Enemy.Body.Pos.x       = 0;
            AGameMgr.Enemy.Body.Pos.y       = 0;
            AGameMgr.Enemy.Body.Pos.z       = 0;
            AGameMgr.Enemy.Body.Anm.Data.no = 0;
            AGameMgr.Enemy.Body.Anm.Data.wt = 0;
            AGameMgr.Enemy.Body.Anm.Index   = 0;
            AGameMgr.Enemy.Body.Spd.wx      = 0;
            AGameMgr.Enemy.Body.Spd.wy      = 0;
            AGameMgr.Enemy.Body.Spd.dx      = 0;
            AGameMgr.Enemy.Body.Spd.dy      = 0;
            AGameMgr.Enemy.Body.Spd.sx      = 0;
            AGameMgr.Enemy.Body.Spd.sy      = 0;
            AGameMgr.Enemy.Line             = 0;
            AGameMgr.Enemy.Type             = 0;
            AGameMgr.Enemy.Time             = 0;
            AGameMgr.Enemy.Flag             = 0;
            AGameMgr.Enemy.SpeedWaitCounter = 0;
            
            break;
        case TASK_MODE_MAIN:
            switch( AGameMgr.Enemy.Body.Status )
            {
                case ENEMY_BIRTH:       //生成
                    
                    eno = rand() % MAX_ENEMY_NUM;
                    lno = rand() % MAX_LINE_NUM;
                    //敵生成
                    AGameMgr.Enemy.Flag             = 1;
                    AGameMgr.Enemy.Line             = lno;
                    AGameMgr.Enemy.Type             = EnemyType[eno];
                    AGameMgr.Enemy.Time             = 0;
                    AGameMgr.Enemy.SpeedWaitCounter = EnemySpeedWaitTable[AGameMgr.PlayLevel];
                    AGameMgr.Enemy.Body.MoveCount   = 0;
                    //AGameMgr.Enemy.Body.Status        = ENEMY_BIRTH;
                    AGameMgr.Enemy.Body.OPos.x      = EnemyAnmData[AGameMgr.Enemy.Type][0].OPos.x;
                    AGameMgr.Enemy.Body.OPos.y      = EnemyAnmData[AGameMgr.Enemy.Type][0].OPos.y;
                    AGameMgr.Enemy.Body.OPos.z      = 0;
                    AGameMgr.Enemy.Body.Pos.x       = EVEMY_BIRTH_POS_X;
                    AGameMgr.Enemy.Body.Pos.y       = LinePosYTbl[AGameMgr.Enemy.Line];
                    AGameMgr.Enemy.Body.Pos.z       = PRIORITY_ENEMY;
                    AGameMgr.Enemy.Body.Anm.Data.no = EnemyAnmData[AGameMgr.Enemy.Type][0].AnmData.no;
                    AGameMgr.Enemy.Body.Anm.Data.wt = EnemyAnmData[AGameMgr.Enemy.Type][0].AnmData.wt;
                    AGameMgr.Enemy.Body.Anm.Index   = 0;
                    AGameMgr.Enemy.Body.Spd.wx      = 0;
                    AGameMgr.Enemy.Body.Spd.wy      = 0;
                    AGameMgr.Enemy.Body.Spd.dx      = 0;
                    AGameMgr.Enemy.Body.Spd.dy      = 0;
                    AGameMgr.Enemy.Body.Spd.sx      = EnemySpeedTable[AGameMgr.PlayLevel];
                    AGameMgr.Enemy.Body.Spd.sy      = 0;
                    
                    //ステ-タスを移動へ
                    AGameMgr.Enemy.Body.Status      = ENEMY_MOVE_WAIT;
                    break;
                case ENEMY_MOVE_WAIT:
                    for(i=0;i<3;i++)
                    {//カラスの状態をチェック
                        if(AGameMgr.Crow[i].Ans.Flag==1)
                        {//正解を持っているカラスが↓
                            if(AGameMgr.Crow[i].Body.Status==CROW_WAIT)
                            {//待ち状態の場合は発進
                                AGameMgr.Enemy.Body.Status = ENEMY_MOVE;
                            }
                        }
                    }
                    break;
                case ENEMY_MOVE:        //移動
                    if( --AGameMgr.Enemy.Body.Anm.Data.wt < 0 )
                    {
                        if( EnemyAnmData[AGameMgr.Enemy.Type][AGameMgr.Enemy.Body.Anm.Index + 1].AnmData.no == ANM_REPEAT )
                        {//次のパターンがANM_REPEATなら繰り返し
                            AGameMgr.Enemy.Body.Anm.Index = 0;
                        }else
                        {//次のパターンへ
                            AGameMgr.Enemy.Body.Anm.Index++;
                        }
                        
                        //オフセット補正
                        AGameMgr.Enemy.Body.Anm.Data.wt = EnemyAnmData[AGameMgr.Enemy.Type][AGameMgr.Enemy.Body.Anm.Index].AnmData.wt;
                        AGameMgr.Enemy.Body.OPos.x      = EnemyAnmData[AGameMgr.Enemy.Type][AGameMgr.Enemy.Body.Anm.Index].OPos.x;
                        AGameMgr.Enemy.Body.OPos.y      = EnemyAnmData[AGameMgr.Enemy.Type][AGameMgr.Enemy.Body.Anm.Index].OPos.y;
                    }
                    
                    //パターンセット
                    AGameMgr.Enemy.Body.Anm.Data.no = EnemyAnmData[AGameMgr.Enemy.Type][AGameMgr.Enemy.Body.Anm.Index].AnmData.no;
                    
                    //画面外位置
                    if(--AGameMgr.Enemy.SpeedWaitCounter < 0)
                    {
                        AGameMgr.Enemy.SpeedWaitCounter = EnemySpeedWaitTable[AGameMgr.PlayLevel];
                        AGameMgr.Enemy.Body.Pos.x -= EnemySpeedTable[AGameMgr.PlayLevel];

                    //  AGameMgr.Enemy.SpeedWaitCounter = ENEMY_SPD_X_WAIT_0;
                    //  AGameMgr.Enemy.Body.Pos.x -= ENEMY_SPD_X;
                    }
                    
                    if(AGameMgr.Enemy.Body.Pos.x < EVEMY_DEATH_POS_X )
                    {
                        //ステ-タスを削除待ちへ
                        AGameMgr.Enemy.Body.Status = ENEMY_DEATH_WAIT;
                        //位置補正
                        AGameMgr.Enemy.Body.Pos.x   = EVEMY_BIRTH_POS_X;
                        //タイマーセット
                        AGameMgr.Enemy.Time = EnemyDeathWaitTable[AGameMgr.PlayLevel];
                    }
                    
                    break;
                case ENEMY_MOVE_CRASH:  //飛行機にぶつかった後
                    AGameMgr.Enemy.Body.Pos.y += ENEMY_CRUSH_SPD_Y;
                    if( AGameMgr.Enemy.Body.Pos.y > ENEMY_OUT_Y ){
                        //ステータスを削除待ちへ
                        AGameMgr.Enemy.Body.Status = ENEMY_DEATH_WAIT;
                        //位置補正
                        AGameMgr.Enemy.Body.Pos.x   = EVEMY_BIRTH_POS_X;
                        //タイマーセット
                        AGameMgr.Enemy.Time = EnemyDeathWaitTable[AGameMgr.PlayLevel];
                    }
                    
                    break;
                case ENEMY_DEATH_WAIT:  //削除待ち
                    if( --AGameMgr.Enemy.Time < 0 ){
                        //ステータスを削除へ
                        AGameMgr.Enemy.Body.Status = ENEMY_DEATH;
                    }
                    
                    break;
                case ENEMY_DEATH:       //画面外または正解した場合
                    //敵削除
                    
                    //test
                    AGameMgr.Enemy.Body.Status = ENEMY_BIRTH;
                case ENEMY_TIMEUP:  //タイムアップ
                    
                    break;
                default:
            }
            
            //描画
            SpData.No       = AGameMgr.Enemy.Body.Anm.Data.no;
            SpData.PosX     = AGameMgr.Enemy.Body.Pos.x - AGameMgr.Enemy.Body.OPos.x;
            SpData.PosY     = AGameMgr.Enemy.Body.Pos.y - AGameMgr.Enemy.Body.OPos.y;
            SpData.PosZ     = AGameMgr.Enemy.Body.Pos.z;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );
            break;
        case TASK_MODE_EXIT:
            break;
        default:
    }

    return TRUE;
}


//-----------------------------------------------------------------------------
//  関数名 :EffectTask
//
//  work   :効果タスク
//  in     :TASK*       タスクポインタ
//  out    :
//  note   :なし
//-----------------------------------------------------------------------------
static int EffectTask(TASK* ip_task)
{
    SPRITE_DATA SpData;
    int i;


    switch( ip_task->mode )
    {
        case TASK_MODE_INIT:
            //change mode
            ip_task->mode = TASK_MODE_MAIN;

            for(i=0;i<MAX_EFFECT_NUM;i++){
                AGameMgr.Effect.Data[i].Flag    = 0;        //フラグ
                AGameMgr.Effect.Data[i].No      = 0;        //種類番号
                AGameMgr.Effect.Data[i].Index   = 0;        //管理番号
                AGameMgr.Effect.Data[i].Time    = 0;        //時間
                AGameMgr.Effect.Data[i].Px      = 0;        //位置X
                AGameMgr.Effect.Data[i].Py      = 0;        //位置Y
                AGameMgr.Effect.Data[i].Pz      = 0;        //位置Z
            }

            break;
        case TASK_MODE_MAIN:
            for(i=0;i<MAX_EFFECT_NUM;i++){
                if( AGameMgr.Effect.Data[i].Flag )
                {//登録してあれば描画
                    if( --AGameMgr.Effect.Data[i].Time <= 0 )
                    {//次のパターン
                        if( EffectEntryTable[ AGameMgr.Effect.Data[i].No + 1 ].No == ANM_STOP )
                        {//アニメ削除
                            AGameMgr.Effect.Data[i].Flag = 0;
                        }else if( EffectEntryTable[ AGameMgr.Effect.Data[i].No + 1 ].No == ANM_WAIT )
                        {//そのまま標示（タイム値再設定）
                            AGameMgr.Effect.Data[i].Time = EffectEntryTable[ AGameMgr.Effect.Data[i].No ].Time;
                        }else
                        {//次のパターンセット
                            AGameMgr.Effect.Data[i].No++;                                                           //管理番号
                            AGameMgr.Effect.Data[i].Index   = EffectEntryTable[AGameMgr.Effect.Data[i].No].No;      //インデックス
                            AGameMgr.Effect.Data[i].Time    = EffectEntryTable[AGameMgr.Effect.Data[i].No].Time;    //時間
                            AGameMgr.Effect.Data[i].OPx     = EffectEntryTable[AGameMgr.Effect.Data[i].No].OPx;     //位置X
                            AGameMgr.Effect.Data[i].OPy     = EffectEntryTable[AGameMgr.Effect.Data[i].No].OPy;     //位置Y
                        }
                    }else
                    {//今のパターン継続
                        
                    }
                    
                    //描画
                    SpData.No       = AGameMgr.Effect.Data[i].Index;
                    SpData.PosX     = AGameMgr.Effect.Data[i].Px - AGameMgr.Effect.Data[i].OPx;
                    SpData.PosY     = AGameMgr.Effect.Data[i].Py - AGameMgr.Effect.Data[i].OPx;
                    SpData.PosZ     = AGameMgr.Effect.Data[i].Pz;
                    SpData.ScaleX   = SCALE10;
                    SpData.ScaleY   = SCALE10;
                    SpData.Rotate   = ROTATE000;
                    SpData.Reverse  = NOREVERS;
                    DrawSprite( &SpData );
                }
            }
        case TASK_MODE_EXIT:
            break;
        default:
    }


    return TRUE;
}


//-----------------------------------------------------------------------------
//  関数名 :CreateEffect
//
//  work   :エフェクト登録
//  in     :int i_no,
//          int i_x,
//          int i_y
//          int i_z
//  out    :インデックス値（－１なら登録失敗）
//  note   :なし
//-----------------------------------------------------------------------------
static int CreateEffect(int i_no,int i_x,int i_y,int i_z)
{
    
    int i,index;

    for(i=0;i<MAX_EFFECT_NUM;i++){
        if( !AGameMgr.Effect.Data[i].Flag ){//空きなら取得
            index=i;
            
            //登録
            AGameMgr.Effect.Data[i].Flag    = 1;                            //フラグ
            AGameMgr.Effect.Data[i].No      = i_no;                         //種類番号
            AGameMgr.Effect.Data[i].Index   = EffectEntryTable[i_no].No;    //描画インデックス
            AGameMgr.Effect.Data[i].Time    = EffectEntryTable[i_no].Time;  //時間
            AGameMgr.Effect.Data[i].Px      = i_x;                          //位置X
            AGameMgr.Effect.Data[i].Py      = i_y;                          //位置Y
            AGameMgr.Effect.Data[i].Pz      = i_z;                          //位置Z
            AGameMgr.Effect.Data[i].OPx     = EffectEntryTable[i_no].OPx;   //位置X
            AGameMgr.Effect.Data[i].OPy     = EffectEntryTable[i_no].OPy;   //位置Y
            
            return index;
        }
    }

    return -1;
}



//-----------------------------------------------------------------------------
//  関数名 :CheckHitAirToEnemy
//
//  work   :オジャマキャラとの衝突チェック
//  in     :なし
//  out    :TRUE    衝突した
//          FALSE   衝突していない
//  note   :なし
//-----------------------------------------------------------------------------
static int CheckHitAirToEnemy(void)
{
    if(AGameMgr.Enemy.Flag){
        if( AGameMgr.Air.Line == AGameMgr.Enemy.Line )
        {//同じラインの場合チェック
            
            if( ABS(AGameMgr.Enemy.Body.Pos.x - AGameMgr.Air.Body.Pos.x)  < ENEMY_HIT_DISTANCE )
            {//HIT
                //存在フラグOFF
                AGameMgr.Enemy.Flag = 0;
                return TRUE;
            }
        }
    }
    return FALSE;
}


//-----------------------------------------------------------------------------
//  関数名 :CheckHitHandToEnemy
//
//  work   :手とオジャマキャラの書とツチェック
//  in     :なし
//  out    :TRUE    衝突した
//          FALSE   衝突していない
//  note   :なし
//-----------------------------------------------------------------------------
static int CheckHitHandToEnemy(void)
{
    if(AGameMgr.Enemy.Flag){
        if( AGameMgr.Air.Line == AGameMgr.Enemy.Line )
        {//同じラインの場合チェック
            if( ABS(AGameMgr.Enemy.Body.Pos.x - AGameMgr.Air.Hand.Pos.x)  < HIT_DISTANCE_HAND_TO_ENEMY )
            {//HIT
                return TRUE;
            }
        }
    }
    return FALSE;
}


//-----------------------------------------------------------------------------
//  関数名 :CheckHitHandToPanel
//
//  work   :手と答えパネルの衝突チェック
//  in     :インデックス
//          答えの結果
//  out    :TRUE
//          FALSE
//  note   :なし
//-----------------------------------------------------------------------------
static int CheckHitHandToPanel(int* ip_index,int* ip_result)
{
    int i;

    for(i=0;i<MAX_ENEMY_NUM;i++)
    {
        if(AGameMgr.Crow[i].Flag)
        {//存在していればチェック
            if( AGameMgr.Air.Line == AGameMgr.Crow[i].Line )
            {//同じラインの場合チェック
                if( ABS(AGameMgr.Crow[i].Panel.Pos.x - AGameMgr.Air.Hand.Pos.x)  < HIT_DISTANCE_HAND_TO_PANEL )
                {//HIT
                    *ip_result  = AGameMgr.Crow[i].Ans.Flag;    //答えの結果
                    *ip_index   = i;
                    return TRUE;
                }
            }
        }
    }
    *ip_index=-1;
    return FALSE;
}


//-----------------------------------------------------------------------------
//  関数名  :DrawNo
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
static void DrawNo(int i_num,int i_wsize,int *ip_numtbl,int i_x,int i_y,int i_z)
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
//  関数名 :DrawArm
//  機能   :アーム描画
//  注意   :なし
//-----------------------------------------------------------------------------
static void DrawArm(int i_length,int i_x,int i_y)
{
    SPRITE_DATA SpData;
    int lengtharr[2];
    int i,bx,by;
    static int ArmTbl[]={
        0,                          //0
        AIR_CHAR_ARM_WPIXEL_01,     //1
        AIR_CHAR_ARM_WPIXEL_02,     //2
        AIR_CHAR_ARM_WPIXEL_03,     //3
        AIR_CHAR_ARM_WPIXEL_04,     //4
        AIR_CHAR_ARM_WPIXEL_05,     //5
        AIR_CHAR_ARM_WPIXEL_06,     //6
        AIR_CHAR_ARM_WPIXEL_07,     //7
        AIR_CHAR_ARM_WPIXEL_08,     //8
        AIR_CHAR_ARM_WPIXEL_09,     //9
        AIR_CHAR_ARM_WPIXEL_10,     //10
    };

    if(i_length<0) i_length=0;

    lengtharr[0] = i_length/10;
    lengtharr[1] = (i_length-lengtharr[0]*10);

    bx=i_x;
    by=i_y;
    //10桁
    for(i=0;i<lengtharr[0];i++)
    {
        //描画
        SpData.No       = ArmTbl[10];
        SpData.PosX     = bx;
        SpData.PosY     = by;
        SpData.PosZ     = PRIORITY_AIR_ARM;
        SpData.ScaleX   = SCALE10;
        SpData.ScaleY   = SCALE10;
        SpData.Rotate   = ROTATE000;
        SpData.Reverse  = NOREVERS;
        DrawSprite( &SpData );

        //w-ize
        bx+=10; 
    }

    //1桁
    //描画
    if( lengtharr[1] )
    {
        SpData.No       = ArmTbl[ lengtharr[1]  ];
        SpData.PosX     = bx;
        SpData.PosY     = by;
        SpData.PosZ     = PRIORITY_AIR_ARM;
        SpData.ScaleX   = SCALE10;
        SpData.ScaleY   = SCALE10;
        SpData.Rotate   = ROTATE000;
        SpData.Reverse  = NOREVERS;
        DrawSprite( &SpData );
    }
}




//-----------------------------------------------------------------------------
//  関数名 :DrawCorrectAnswerNo
//
//  work    :正解した問題数分パネルを表示
//  in      :int i_num  正解数(1～10)
//          :int i_x    位置X
//          :int i_y    位置Y
//  out     :
//  note    :なし
//-----------------------------------------------------------------------------
static void DrawCorrectAnswerNo(int i_num,int i_x,int i_y)
{
    SPRITE_DATA SpData;
    int i,j;

    static int CorrectAnswerNoTable[]={
        AIR_CHAR_QNO_01,
        AIR_CHAR_QNO_02,
        AIR_CHAR_QNO_03,
        AIR_CHAR_QNO_04,
        AIR_CHAR_QNO_05,
        AIR_CHAR_QNO_06,
        AIR_CHAR_QNO_07,
        AIR_CHAR_QNO_08,
        AIR_CHAR_QNO_09,
        AIR_CHAR_QNO_10,
    };


    for(i=0;i<3;i++){
        for(j=0;j<4;j++){
            if( (i*4+j) < i_num )
            {//
                SpData.No       = CorrectAnswerNoTable[i*4 + j];
                SpData.PosX     = i_x + j*12;
                SpData.PosY     = i_y + i*12;
                SpData.PosZ     = 49;
                SpData.ScaleX   = SCALE10;
                SpData.ScaleY   = SCALE10;
                SpData.Rotate   = ROTATE000;
                SpData.Reverse  = NOREVERS;
                DrawSprite( &SpData );
            }
        }
    }
}


//-----------------------------------------------------------------------------
//  関数名 :DrawClock
//
//  work   :時計描画
//  in     :int i_time      時間インデックス
//         :int i_x         位置X
//         :int i_y         位置Y
//  out    :なし
//  note   :なし
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
        {   AIR_CHAR_NEEDLE_LONG_00,    AIR_CHAR_NEEDLE_SHORT_00    },      //CLOCK_00_00
        {   AIR_CHAR_NEEDLE_LONG_01,    AIR_CHAR_NEEDLE_SHORT_00    },      //CLOCK_00_05
        {   AIR_CHAR_NEEDLE_LONG_02,    AIR_CHAR_NEEDLE_SHORT_00    },      //CLOCK_00_10
        {   AIR_CHAR_NEEDLE_LONG_03,    AIR_CHAR_NEEDLE_SHORT_01    },      //CLOCK_00_15
        {   AIR_CHAR_NEEDLE_LONG_04,    AIR_CHAR_NEEDLE_SHORT_01    },      //CLOCK_00_20
        {   AIR_CHAR_NEEDLE_LONG_05,    AIR_CHAR_NEEDLE_SHORT_01    },      //CLOCK_00_25
        {   AIR_CHAR_NEEDLE_LONG_06,    AIR_CHAR_NEEDLE_SHORT_02    },      //CLOCK_00_30
        {   AIR_CHAR_NEEDLE_LONG_07,    AIR_CHAR_NEEDLE_SHORT_02    },      //CLOCK_00_35
        {   AIR_CHAR_NEEDLE_LONG_08,    AIR_CHAR_NEEDLE_SHORT_02    },      //CLOCK_00_40
        {   AIR_CHAR_NEEDLE_LONG_09,    AIR_CHAR_NEEDLE_SHORT_03    },      //CLOCK_00_45
        {   AIR_CHAR_NEEDLE_LONG_10,    AIR_CHAR_NEEDLE_SHORT_03    },      //CLOCK_00_50
        {   AIR_CHAR_NEEDLE_LONG_11,    AIR_CHAR_NEEDLE_SHORT_03    },      //CLOCK_00_55
        {   AIR_CHAR_NEEDLE_LONG_00,    AIR_CHAR_NEEDLE_SHORT_04    },      //CLOCK_01_00
        {   AIR_CHAR_NEEDLE_LONG_01,    AIR_CHAR_NEEDLE_SHORT_04    },      //CLOCK_01_05
        {   AIR_CHAR_NEEDLE_LONG_02,    AIR_CHAR_NEEDLE_SHORT_04    },      //CLOCK_01_10
        {   AIR_CHAR_NEEDLE_LONG_03,    AIR_CHAR_NEEDLE_SHORT_05    },      //CLOCK_01_15
        {   AIR_CHAR_NEEDLE_LONG_04,    AIR_CHAR_NEEDLE_SHORT_05    },      //CLOCK_01_20
        {   AIR_CHAR_NEEDLE_LONG_05,    AIR_CHAR_NEEDLE_SHORT_05    },      //CLOCK_01_25
        {   AIR_CHAR_NEEDLE_LONG_06,    AIR_CHAR_NEEDLE_SHORT_06    },      //CLOCK_01_30
        {   AIR_CHAR_NEEDLE_LONG_07,    AIR_CHAR_NEEDLE_SHORT_06    },      //CLOCK_01_35
        {   AIR_CHAR_NEEDLE_LONG_08,    AIR_CHAR_NEEDLE_SHORT_06    },      //CLOCK_01_40
        {   AIR_CHAR_NEEDLE_LONG_09,    AIR_CHAR_NEEDLE_SHORT_07    },      //CLOCK_01_45
        {   AIR_CHAR_NEEDLE_LONG_10,    AIR_CHAR_NEEDLE_SHORT_07    },      //CLOCK_01_50
        {   AIR_CHAR_NEEDLE_LONG_11,    AIR_CHAR_NEEDLE_SHORT_07    },      //CLOCK_01_55
        {   AIR_CHAR_NEEDLE_LONG_00,    AIR_CHAR_NEEDLE_SHORT_08    },      //CLOCK_02_00
        {   AIR_CHAR_NEEDLE_LONG_01,    AIR_CHAR_NEEDLE_SHORT_08    },      //CLOCK_02_05
        {   AIR_CHAR_NEEDLE_LONG_02,    AIR_CHAR_NEEDLE_SHORT_08    },      //CLOCK_02_10
        {   AIR_CHAR_NEEDLE_LONG_03,    AIR_CHAR_NEEDLE_SHORT_09    },      //CLOCK_02_15
        {   AIR_CHAR_NEEDLE_LONG_04,    AIR_CHAR_NEEDLE_SHORT_09    },      //CLOCK_02_20
        {   AIR_CHAR_NEEDLE_LONG_05,    AIR_CHAR_NEEDLE_SHORT_09    },      //CLOCK_02_25
        {   AIR_CHAR_NEEDLE_LONG_06,    AIR_CHAR_NEEDLE_SHORT_10    },      //CLOCK_02_30
        {   AIR_CHAR_NEEDLE_LONG_07,    AIR_CHAR_NEEDLE_SHORT_10    },      //CLOCK_02_35
        {   AIR_CHAR_NEEDLE_LONG_08,    AIR_CHAR_NEEDLE_SHORT_10    },      //CLOCK_02_40
        {   AIR_CHAR_NEEDLE_LONG_09,    AIR_CHAR_NEEDLE_SHORT_11    },      //CLOCK_02_45
        {   AIR_CHAR_NEEDLE_LONG_10,    AIR_CHAR_NEEDLE_SHORT_11    },      //CLOCK_02_50
        {   AIR_CHAR_NEEDLE_LONG_11,    AIR_CHAR_NEEDLE_SHORT_11    },      //CLOCK_02_55
        {   AIR_CHAR_NEEDLE_LONG_00,    AIR_CHAR_NEEDLE_SHORT_12    },      //CLOCK_03_00
        {   AIR_CHAR_NEEDLE_LONG_01,    AIR_CHAR_NEEDLE_SHORT_12    },      //CLOCK_03_05
        {   AIR_CHAR_NEEDLE_LONG_02,    AIR_CHAR_NEEDLE_SHORT_12    },      //CLOCK_03_10
        {   AIR_CHAR_NEEDLE_LONG_03,    AIR_CHAR_NEEDLE_SHORT_13    },      //CLOCK_03_15
        {   AIR_CHAR_NEEDLE_LONG_04,    AIR_CHAR_NEEDLE_SHORT_13    },      //CLOCK_03_20
        {   AIR_CHAR_NEEDLE_LONG_05,    AIR_CHAR_NEEDLE_SHORT_13    },      //CLOCK_03_25
        {   AIR_CHAR_NEEDLE_LONG_06,    AIR_CHAR_NEEDLE_SHORT_14    },      //CLOCK_03_30
        {   AIR_CHAR_NEEDLE_LONG_07,    AIR_CHAR_NEEDLE_SHORT_14    },      //CLOCK_03_35
        {   AIR_CHAR_NEEDLE_LONG_08,    AIR_CHAR_NEEDLE_SHORT_14    },      //CLOCK_03_40
        {   AIR_CHAR_NEEDLE_LONG_09,    AIR_CHAR_NEEDLE_SHORT_15    },      //CLOCK_03_45
        {   AIR_CHAR_NEEDLE_LONG_10,    AIR_CHAR_NEEDLE_SHORT_15    },      //CLOCK_03_50
        {   AIR_CHAR_NEEDLE_LONG_11,    AIR_CHAR_NEEDLE_SHORT_15    },      //CLOCK_03_55
        {   AIR_CHAR_NEEDLE_LONG_00,    AIR_CHAR_NEEDLE_SHORT_16    },      //CLOCK_04_00
        {   AIR_CHAR_NEEDLE_LONG_01,    AIR_CHAR_NEEDLE_SHORT_16    },      //CLOCK_04_05
        {   AIR_CHAR_NEEDLE_LONG_02,    AIR_CHAR_NEEDLE_SHORT_16    },      //CLOCK_04_10
        {   AIR_CHAR_NEEDLE_LONG_03,    AIR_CHAR_NEEDLE_SHORT_17    },      //CLOCK_04_15
        {   AIR_CHAR_NEEDLE_LONG_04,    AIR_CHAR_NEEDLE_SHORT_17    },      //CLOCK_04_20
        {   AIR_CHAR_NEEDLE_LONG_05,    AIR_CHAR_NEEDLE_SHORT_17    },      //CLOCK_04_25
        {   AIR_CHAR_NEEDLE_LONG_06,    AIR_CHAR_NEEDLE_SHORT_18    },      //CLOCK_04_30
        {   AIR_CHAR_NEEDLE_LONG_07,    AIR_CHAR_NEEDLE_SHORT_18    },      //CLOCK_04_35
        {   AIR_CHAR_NEEDLE_LONG_08,    AIR_CHAR_NEEDLE_SHORT_18    },      //CLOCK_04_40
        {   AIR_CHAR_NEEDLE_LONG_09,    AIR_CHAR_NEEDLE_SHORT_19    },      //CLOCK_04_45
        {   AIR_CHAR_NEEDLE_LONG_10,    AIR_CHAR_NEEDLE_SHORT_19    },      //CLOCK_04_50
        {   AIR_CHAR_NEEDLE_LONG_11,    AIR_CHAR_NEEDLE_SHORT_19    },      //CLOCK_04_55
        {   AIR_CHAR_NEEDLE_LONG_00,    AIR_CHAR_NEEDLE_SHORT_20    },      //CLOCK_05_00
        {   AIR_CHAR_NEEDLE_LONG_01,    AIR_CHAR_NEEDLE_SHORT_20    },      //CLOCK_05_05
        {   AIR_CHAR_NEEDLE_LONG_02,    AIR_CHAR_NEEDLE_SHORT_20    },      //CLOCK_05_10
        {   AIR_CHAR_NEEDLE_LONG_03,    AIR_CHAR_NEEDLE_SHORT_21    },      //CLOCK_05_15
        {   AIR_CHAR_NEEDLE_LONG_04,    AIR_CHAR_NEEDLE_SHORT_21    },      //CLOCK_05_20
        {   AIR_CHAR_NEEDLE_LONG_05,    AIR_CHAR_NEEDLE_SHORT_21    },      //CLOCK_05_25
        {   AIR_CHAR_NEEDLE_LONG_06,    AIR_CHAR_NEEDLE_SHORT_22    },      //CLOCK_05_30
        {   AIR_CHAR_NEEDLE_LONG_07,    AIR_CHAR_NEEDLE_SHORT_22    },      //CLOCK_05_35
        {   AIR_CHAR_NEEDLE_LONG_08,    AIR_CHAR_NEEDLE_SHORT_22    },      //CLOCK_05_40
        {   AIR_CHAR_NEEDLE_LONG_09,    AIR_CHAR_NEEDLE_SHORT_23    },      //CLOCK_05_45
        {   AIR_CHAR_NEEDLE_LONG_10,    AIR_CHAR_NEEDLE_SHORT_23    },      //CLOCK_05_50
        {   AIR_CHAR_NEEDLE_LONG_11,    AIR_CHAR_NEEDLE_SHORT_23    },      //CLOCK_05_55
        {   AIR_CHAR_NEEDLE_LONG_00,    AIR_CHAR_NEEDLE_SHORT_24    },      //CLOCK_06_00
        {   AIR_CHAR_NEEDLE_LONG_01,    AIR_CHAR_NEEDLE_SHORT_24    },      //CLOCK_06_05
        {   AIR_CHAR_NEEDLE_LONG_02,    AIR_CHAR_NEEDLE_SHORT_24    },      //CLOCK_06_10
        {   AIR_CHAR_NEEDLE_LONG_03,    AIR_CHAR_NEEDLE_SHORT_25    },      //CLOCK_06_15
        {   AIR_CHAR_NEEDLE_LONG_04,    AIR_CHAR_NEEDLE_SHORT_25    },      //CLOCK_06_20
        {   AIR_CHAR_NEEDLE_LONG_05,    AIR_CHAR_NEEDLE_SHORT_25    },      //CLOCK_06_25
        {   AIR_CHAR_NEEDLE_LONG_06,    AIR_CHAR_NEEDLE_SHORT_26    },      //CLOCK_06_30
        {   AIR_CHAR_NEEDLE_LONG_07,    AIR_CHAR_NEEDLE_SHORT_26    },      //CLOCK_06_35
        {   AIR_CHAR_NEEDLE_LONG_08,    AIR_CHAR_NEEDLE_SHORT_26    },      //CLOCK_06_40
        {   AIR_CHAR_NEEDLE_LONG_09,    AIR_CHAR_NEEDLE_SHORT_27    },      //CLOCK_06_45
        {   AIR_CHAR_NEEDLE_LONG_10,    AIR_CHAR_NEEDLE_SHORT_27    },      //CLOCK_06_50
        {   AIR_CHAR_NEEDLE_LONG_11,    AIR_CHAR_NEEDLE_SHORT_27    },      //CLOCK_06_55
        {   AIR_CHAR_NEEDLE_LONG_00,    AIR_CHAR_NEEDLE_SHORT_28    },      //CLOCK_07_00
        {   AIR_CHAR_NEEDLE_LONG_01,    AIR_CHAR_NEEDLE_SHORT_28    },      //CLOCK_07_05
        {   AIR_CHAR_NEEDLE_LONG_02,    AIR_CHAR_NEEDLE_SHORT_28    },      //CLOCK_07_10
        {   AIR_CHAR_NEEDLE_LONG_03,    AIR_CHAR_NEEDLE_SHORT_29    },      //CLOCK_07_15
        {   AIR_CHAR_NEEDLE_LONG_04,    AIR_CHAR_NEEDLE_SHORT_29    },      //CLOCK_07_20
        {   AIR_CHAR_NEEDLE_LONG_05,    AIR_CHAR_NEEDLE_SHORT_29    },      //CLOCK_07_25
        {   AIR_CHAR_NEEDLE_LONG_06,    AIR_CHAR_NEEDLE_SHORT_30    },      //CLOCK_07_30
        {   AIR_CHAR_NEEDLE_LONG_07,    AIR_CHAR_NEEDLE_SHORT_30    },      //CLOCK_07_35
        {   AIR_CHAR_NEEDLE_LONG_08,    AIR_CHAR_NEEDLE_SHORT_30    },      //CLOCK_07_40
        {   AIR_CHAR_NEEDLE_LONG_09,    AIR_CHAR_NEEDLE_SHORT_31    },      //CLOCK_07_45
        {   AIR_CHAR_NEEDLE_LONG_10,    AIR_CHAR_NEEDLE_SHORT_31    },      //CLOCK_07_50
        {   AIR_CHAR_NEEDLE_LONG_11,    AIR_CHAR_NEEDLE_SHORT_31    },      //CLOCK_07_55
        {   AIR_CHAR_NEEDLE_LONG_00,    AIR_CHAR_NEEDLE_SHORT_32    },      //CLOCK_08_00
        {   AIR_CHAR_NEEDLE_LONG_01,    AIR_CHAR_NEEDLE_SHORT_32    },      //CLOCK_08_05
        {   AIR_CHAR_NEEDLE_LONG_02,    AIR_CHAR_NEEDLE_SHORT_32    },      //CLOCK_08_10
        {   AIR_CHAR_NEEDLE_LONG_03,    AIR_CHAR_NEEDLE_SHORT_33    },      //CLOCK_08_15
        {   AIR_CHAR_NEEDLE_LONG_04,    AIR_CHAR_NEEDLE_SHORT_33    },      //CLOCK_08_20
        {   AIR_CHAR_NEEDLE_LONG_05,    AIR_CHAR_NEEDLE_SHORT_33    },      //CLOCK_08_25
        {   AIR_CHAR_NEEDLE_LONG_06,    AIR_CHAR_NEEDLE_SHORT_34    },      //CLOCK_08_30
        {   AIR_CHAR_NEEDLE_LONG_07,    AIR_CHAR_NEEDLE_SHORT_34    },      //CLOCK_08_35
        {   AIR_CHAR_NEEDLE_LONG_08,    AIR_CHAR_NEEDLE_SHORT_34    },      //CLOCK_08_40
        {   AIR_CHAR_NEEDLE_LONG_09,    AIR_CHAR_NEEDLE_SHORT_35    },      //CLOCK_08_45
        {   AIR_CHAR_NEEDLE_LONG_10,    AIR_CHAR_NEEDLE_SHORT_35    },      //CLOCK_08_50
        {   AIR_CHAR_NEEDLE_LONG_11,    AIR_CHAR_NEEDLE_SHORT_35    },      //CLOCK_08_55
        {   AIR_CHAR_NEEDLE_LONG_00,    AIR_CHAR_NEEDLE_SHORT_36    },      //CLOCK_09_00
        {   AIR_CHAR_NEEDLE_LONG_01,    AIR_CHAR_NEEDLE_SHORT_36    },      //CLOCK_09_05
        {   AIR_CHAR_NEEDLE_LONG_02,    AIR_CHAR_NEEDLE_SHORT_36    },      //CLOCK_09_10
        {   AIR_CHAR_NEEDLE_LONG_03,    AIR_CHAR_NEEDLE_SHORT_37    },      //CLOCK_09_15
        {   AIR_CHAR_NEEDLE_LONG_04,    AIR_CHAR_NEEDLE_SHORT_37    },      //CLOCK_09_20
        {   AIR_CHAR_NEEDLE_LONG_05,    AIR_CHAR_NEEDLE_SHORT_37    },      //CLOCK_09_25
        {   AIR_CHAR_NEEDLE_LONG_06,    AIR_CHAR_NEEDLE_SHORT_38    },      //CLOCK_09_30
        {   AIR_CHAR_NEEDLE_LONG_07,    AIR_CHAR_NEEDLE_SHORT_38    },      //CLOCK_09_35
        {   AIR_CHAR_NEEDLE_LONG_08,    AIR_CHAR_NEEDLE_SHORT_38    },      //CLOCK_09_40
        {   AIR_CHAR_NEEDLE_LONG_09,    AIR_CHAR_NEEDLE_SHORT_39    },      //CLOCK_09_45
        {   AIR_CHAR_NEEDLE_LONG_10,    AIR_CHAR_NEEDLE_SHORT_39    },      //CLOCK_09_50
        {   AIR_CHAR_NEEDLE_LONG_11,    AIR_CHAR_NEEDLE_SHORT_39    },      //CLOCK_09_55
        {   AIR_CHAR_NEEDLE_LONG_00,    AIR_CHAR_NEEDLE_SHORT_40    },      //CLOCK_10_00
        {   AIR_CHAR_NEEDLE_LONG_01,    AIR_CHAR_NEEDLE_SHORT_40    },      //CLOCK_10_05
        {   AIR_CHAR_NEEDLE_LONG_02,    AIR_CHAR_NEEDLE_SHORT_40    },      //CLOCK_10_10
        {   AIR_CHAR_NEEDLE_LONG_03,    AIR_CHAR_NEEDLE_SHORT_41    },      //CLOCK_10_15
        {   AIR_CHAR_NEEDLE_LONG_04,    AIR_CHAR_NEEDLE_SHORT_41    },      //CLOCK_10_20
        {   AIR_CHAR_NEEDLE_LONG_05,    AIR_CHAR_NEEDLE_SHORT_41    },      //CLOCK_10_25
        {   AIR_CHAR_NEEDLE_LONG_06,    AIR_CHAR_NEEDLE_SHORT_42    },      //CLOCK_10_30
        {   AIR_CHAR_NEEDLE_LONG_07,    AIR_CHAR_NEEDLE_SHORT_42    },      //CLOCK_10_35
        {   AIR_CHAR_NEEDLE_LONG_08,    AIR_CHAR_NEEDLE_SHORT_42    },      //CLOCK_10_40
        {   AIR_CHAR_NEEDLE_LONG_09,    AIR_CHAR_NEEDLE_SHORT_43    },      //CLOCK_10_45
        {   AIR_CHAR_NEEDLE_LONG_10,    AIR_CHAR_NEEDLE_SHORT_43    },      //CLOCK_10_50
        {   AIR_CHAR_NEEDLE_LONG_11,    AIR_CHAR_NEEDLE_SHORT_43    },      //CLOCK_10_55
        {   AIR_CHAR_NEEDLE_LONG_00,    AIR_CHAR_NEEDLE_SHORT_44    },      //CLOCK_11_00
        {   AIR_CHAR_NEEDLE_LONG_01,    AIR_CHAR_NEEDLE_SHORT_44    },      //CLOCK_11_05
        {   AIR_CHAR_NEEDLE_LONG_02,    AIR_CHAR_NEEDLE_SHORT_44    },      //CLOCK_11_10
        {   AIR_CHAR_NEEDLE_LONG_03,    AIR_CHAR_NEEDLE_SHORT_45    },      //CLOCK_11_15
        {   AIR_CHAR_NEEDLE_LONG_04,    AIR_CHAR_NEEDLE_SHORT_45    },      //CLOCK_11_20
        {   AIR_CHAR_NEEDLE_LONG_05,    AIR_CHAR_NEEDLE_SHORT_45    },      //CLOCK_11_25
        {   AIR_CHAR_NEEDLE_LONG_06,    AIR_CHAR_NEEDLE_SHORT_46    },      //CLOCK_11_30
        {   AIR_CHAR_NEEDLE_LONG_07,    AIR_CHAR_NEEDLE_SHORT_46    },      //CLOCK_11_35
        {   AIR_CHAR_NEEDLE_LONG_08,    AIR_CHAR_NEEDLE_SHORT_46    },      //CLOCK_11_40
        {   AIR_CHAR_NEEDLE_LONG_09,    AIR_CHAR_NEEDLE_SHORT_47    },      //CLOCK_11_45
        {   AIR_CHAR_NEEDLE_LONG_10,    AIR_CHAR_NEEDLE_SHORT_47    },      //CLOCK_11_50
        {   AIR_CHAR_NEEDLE_LONG_11,    AIR_CHAR_NEEDLE_SHORT_47    },      //CLOCK_11_55
    };

    SpData.No       = AIR_CHAR_CLOCK_PANEL;
    SpData.PosX     = i_x - 17;
    SpData.PosY     = i_y - 16;
    SpData.PosZ     = i_z;
    SpData.ScaleX   = SCALE10;
    SpData.ScaleY   = SCALE10;
    SpData.Rotate   = ROTATE000;
    SpData.Reverse  = NOREVERS;
    DrawSprite( &SpData );

    SpData.No       = ClockAngleTable[i_time].tansin;
    SpData.PosX     = i_x - 17 + 7;
    SpData.PosY     = i_y - 16 + 6;
    SpData.PosZ     = i_z-2;
    SpData.ScaleX   = SCALE10;
    SpData.ScaleY   = SCALE10;
    SpData.Rotate   = ROTATE000;
    SpData.Reverse  = NOREVERS;
    DrawSprite( &SpData );

    SpData.No       = ClockAngleTable[i_time].tyousin;
    SpData.PosX     = i_x - 17 + 3;
    SpData.PosY     = i_y - 16 + 2;
    SpData.PosZ     = i_z-1;
    SpData.ScaleX   = SCALE10;
    SpData.ScaleY   = SCALE10;
    SpData.Rotate   = ROTATE000;
    SpData.Reverse  = NOREVERS;
    DrawSprite( &SpData );
}


//-----------------------------------------------------------------------------
//  関数名 :DrawBall
//
//  work    :ボール描画
//  in      :int i_kind
//          :int i_num
//          :int i_x
//          :int i_y
//          :int i_z
//  out     :なし
//  note    :なし
//-----------------------------------------------------------------------------
static void DrawBall(int i_color ,int i_num,int i_x,int i_y,int i_z)
{
    SPRITE_DATA SpData;
    int i,j;

    static int BallColorTable[]={
        AIR_CHAR_BALL_RED,
        AIR_CHAR_BALL_ORANGE
    };

    static int BallPanelTable[]={
        AIR_CHAR_PANEL_BLUE_BIG,
        AIR_CHAR_PANEL_PINK_BIG
    };


    //ボール描画
    for(i=0;i<2;i++){
        for(j=0;j<5;j++){
            if( (i*5+j) < i_num )
            {//
                SpData.No       = BallColorTable[i_color];
                SpData.PosX     = i_x - 37 + 22 + j*10;
                SpData.PosY     = i_y - 12 +  3 + i*10;
                SpData.PosZ     = i_z-1;
                SpData.ScaleX   = SCALE10;
                SpData.ScaleY   = SCALE10;
                SpData.Rotate   = ROTATE000;
                SpData.Reverse  = NOREVERS;
                DrawSprite( &SpData );
            }
        }
    }

    //数字描画(小さい数字)
    DrawNo( i_num,
                QUESTION_TEXT_WIDE_SMALL,
                QuestionTextNoSmallTable,
                i_x - 37 - 6,
                i_y - 12 + 7,
                i_z-1);

    //パネル
    SpData.No       = BallPanelTable[i_color];
    SpData.PosX     = i_x - 37;
    SpData.PosY     = i_y - 12;
    SpData.PosZ     = i_z;
    SpData.ScaleX   = SCALE10;
    SpData.ScaleY   = SCALE10;
    SpData.Rotate   = ROTATE000;
    SpData.Reverse  = NOREVERS;
    DrawSprite( &SpData );

}


//-----------------------------------------------------------------------------
//  関数名 :DrawFruits
//
//  work    :果物描画
//  in      :int i_kind
//          int i_num,
//          int i_x,
//          int i_y
//          int i_z
//  out     :なし
//  note    :なし
//-----------------------------------------------------------------------------
static void DrawFruits(int i_kind ,int i_num,int i_x,int i_y,int i_z)
{
    SPRITE_DATA SpData;
    int i,j;

    static int FruitsTable[]={
        AIR_CHAR_APPLE,
        AIR_CHAR_MIKAN
    };

    static int FruitsPanelTable[]={
        AIR_CHAR_PANEL_BLUE_BIG,
        AIR_CHAR_PANEL_PINK_BIG
    };

    //果物
    for(i=0;i<2;i++){
        for(j=0;j<5;j++){
            if( (i*5+j) < i_num )
            {//
                SpData.No       = FruitsTable[i_kind];
                SpData.PosX     = i_x - 37 + 24 + j*9;
                SpData.PosY     = i_y - 12 +  3 + i*9;
                SpData.PosZ     = i_z-1;
                SpData.ScaleX   = SCALE10;
                SpData.ScaleY   = SCALE10;
                SpData.Rotate   = ROTATE000;
                SpData.Reverse  = NOREVERS;
                DrawSprite( &SpData );
            }
        }
    }

    //数字描画(小さい数字)
    DrawNo( i_num,
            QUESTION_TEXT_WIDE_SMALL,
            QuestionTextNoSmallTable,
            i_x - 37 - 6,
            i_y - 12 + 7,
            i_z-1);

    //パネル
    SpData.No       = FruitsPanelTable[i_kind];
    SpData.PosX     = i_x - 37;
    SpData.PosY     = i_y - 12;
    SpData.PosZ     = i_z;
    SpData.ScaleX   = SCALE10;
    SpData.ScaleY   = SCALE10;
    SpData.Rotate   = ROTATE000;
    SpData.Reverse  = NOREVERS;
    DrawSprite( &SpData );

}


//-----------------------------------------------------------------------------
//  関数名 :DrawNoPanel
//
//  work   :パネルの数字描画
//  in     :int i_color
//          int i_num
//          int i_x
//          int i_y
//          int i_z
//  out    :
//  note   :なし
//-----------------------------------------------------------------------------
static void DrawNoPanel(int i_color ,int i_num,int i_x,int i_y,int i_z)
{
    SPRITE_DATA SpData;

    static int NoPanelTable[]={
        AIR_CHAR_PANEL_BLUE_SMALL,                  //小・青
        AIR_CHAR_PANEL_PINK_SMALL,                  //小・ピンク
    };


    //大きい方の数字
    DrawNo( i_num,
                QUESTION_TEXT_WIDE_LARGE,
                QuestionTextNoLargeTable,
                i_x - 12 - 8,
                i_y - 10 + 2,
                i_z-1);

    //パネル
    SpData.No       = NoPanelTable[i_color];
    SpData.PosX     = i_x - 12;
    SpData.PosY     = i_y - 10;
    SpData.PosZ     = i_z;
    SpData.ScaleX   = SCALE10;
    SpData.ScaleY   = SCALE10;
    SpData.Rotate   = ROTATE000;
    SpData.Reverse  = NOREVERS;
    DrawSprite( &SpData );
}


//-----------------------------------------------------------------------------
//  関数名 :DrawNoLarge
//
//  work   :数字描画
//  in     :int i_num
//         :int i_x
//         :int i_y
//         :int i_z
//  out    :なし
//  note   :なし
//-----------------------------------------------------------------------------
static void DrawNoLarge(int i_num,int i_x,int i_y,int i_z)
{
    //大きい方の数字
    DrawNo( i_num,
                QUESTION_TEXT_WIDE_LARGE,
                QuestionTextNoLargeTable,
                i_x - 10,
                i_y - 8,
                i_z);
}


//-----------------------------------------------------------------------------
//  関数名  :DrawNoSmall
//
//  work    :数字描画
//  in      :int i_nu
//          :int i_x
//          :int i_y
//          :int i_z
//  out     :なし
//  note    :なし
//-----------------------------------------------------------------------------
static void DrawNoSmall(int i_num,int i_x,int i_y,int i_z)
{
    //小さい方の数字
    DrawNo( i_num,
            QUESTION_TEXT_WIDE_SMALL,
            QuestionTextNoSmallTable,
            i_x - 5,
            i_y - 5,
            i_z);
}

//-----------------------------------------------------------------------------
//  関数名  :DrawSelectAnswer
//
//  work    :選択する答えを描画
//  in      :QUESTION_DATA *ip_q
//          :int i_x        
//          :int i_y        
//          :int i_z        
//  out     :なし
//  note    :なし
//-----------------------------------------------------------------------------
static void DrawSelectAnswer(QUESTION_DATA *ip_q,int i_x,int i_y,int i_z)
{
    int i,chkindex;
    SPRITE_DATA SpData;

    switch(ip_q->Kind)
    {
        case QUESTION_TEXT_00:      //□に入るのはなんですか？
            if( ip_q->No < 10 ) DrawNoLarge(ip_q->No,i_x-5,i_y,i_z);    //一桁
            else                DrawNoLarge(ip_q->No,i_x,  i_y,i_z);    //二桁
            break;
        case QUESTION_TEXT_01:      //１と３でいくつになりますか
            if( ip_q->No < 10 ) DrawNoLarge(ip_q->No,i_x-5, i_y,i_z);   //一桁
            else                DrawNoLarge(ip_q->No,i_x,   i_y,i_z);   //二桁
            
            break;
        case QUESTION_TEXT_02:      //２は１といくつですか？
            if( ip_q->No < 10 ) DrawNoLarge(ip_q->No,i_x-5, i_y,i_z);   //一桁
            else                DrawNoLarge(ip_q->No,i_x,   i_y,i_z);   //二桁
            break;
        case QUESTION_TEXT_03:      //１じのときとけいのはりはどこをさしていますか？
            DrawClock(ip_q->No,i_x+8,i_y+1,i_z);
            break;
        case QUESTION_TEXT_04:      //１じ３０ぷんのときとけいのはりはどこをさしていますか？
            DrawClock(ip_q->No,i_x+8,i_y+1,i_z);
            break;
        case QUESTION_TEXT_05:      //どちらがおおいですか？　(くだもの比べ)
            if(ip_q->No!=-1)
            {//果物
                if(ip_q->Attr==0){
                    DrawFruits(FRUITS_APPLE,ip_q->No,i_x,i_y,i_z);
                }else{
                    DrawFruits(FRUITS_MIKAN,ip_q->No,i_x,i_y,i_z);
                }
            }else
            {//”おなじ”
                SpData.No       = AIR_CHAR_ONAZI_STR;
                SpData.PosX     = i_x - 16 + 8;
                SpData.PosY     = i_y -  5 - 0;
                SpData.PosZ     = i_z;
                SpData.ScaleX   = SCALE10;
                SpData.ScaleY   = SCALE10;
                SpData.Rotate   = ROTATE000;
                SpData.Reverse  = NOREVERS;
                DrawSprite( &SpData );
            }
            break;
        case QUESTION_TEXT_06:      //どちらがおおいですか？　(パネルの数字比べ)
            if(ip_q->No!=-1)
            {//パネル
                if(ip_q->Attr==0){
                    DrawNoPanel(PANEL_COLOR_BLUE,ip_q->No,i_x+9,i_y,i_z);
                }else{
                    DrawNoPanel(PANEL_COLOR_PINK,ip_q->No,i_x+9,i_y,i_z);
                }
            }else
            {//”おなじ”
                SpData.No       = AIR_CHAR_ONAZI_STR;
                SpData.PosX     = i_x - 16 + 8;
                SpData.PosY     = i_y -  5 - 0;
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
//  関数名  :DrawQuestionText_00
//
//  work    :”□にはいるかずはなんですか？”描画
//  in      :int *ip_numtable   問題にでる数字テーブルへのポインタ
//          :int i_x            位置X
//          :int i_y            位置Y
//          :int i_z            位置Z
//  out     :なし
//  note    :－１のところが問題になります
//          :左上中心
//-----------------------------------------------------------------------------
static void DrawQuestionText_00(int *ip_numtable,int i_x,int i_y,int i_z)
{
    SPRITE_DATA SpData;
    int i,wno;

    //数字
    for(i=0;i<5;i++)
    {
        if(ip_numtable[i]!=-1)
        {
        //  DrawNoLarge(ip_numtable[i],i_x+11+i*36,i_y+22,i_z-2);
            
            if(ip_numtable[i]<10)   DrawNoSmall(ip_numtable[i], i_x+11+i*36 - 6 ,i_y+22,i_z-2); //一桁
            else                    DrawNoSmall(ip_numtable[i], i_x+11+i*36 - 2 ,i_y+22,i_z-2); //二桁
            
        }else{
            wno=i;
        }
    }

    //赤い枠
    SpData.No       = AIR_CHAR_WAKU_RED;
    SpData.PosX     = i_x + 9 + wno * 36;
    SpData.PosY     = i_y + 13;
    SpData.PosZ     = i_z-1;
    SpData.ScaleX   = SCALE10;
    SpData.ScaleY   = SCALE10;
    SpData.Rotate   = ROTATE000;
    SpData.Reverse  = NOREVERS;
    DrawSprite( &SpData );

    //問題文
    SpData.No       = AIR_CHAR_QUESTION_TEXT_04;
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
//  関数名  :DrawQuestionText_01
//
//  work    :”＿と＿でいくつになりますか？”描画
//  in      :int *ip_numtable   問題にでる数字テーブルへのポインタ
//          :int i_x            位置X
//          :int i_y            位置Y
//          :int i_z            位置Z
//  out     :なし
//  note    :左上中心
//          :数字はかならず一桁
//-----------------------------------------------------------------------------
static void DrawQuestionText_01(int *ip_numtable,int i_x,int i_y,int i_z)
{
    SPRITE_DATA SpData;
    int i;

    //問題数字
    for(i=0;i<2;i++)
    {
        DrawNoSmall(ip_numtable[i],i_x-8 + i*36 ,i_y+5,i_z-1);
    }

    //問題文
    SpData.No       = AIR_CHAR_QUESTION_TEXT_01;
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
//  関数名  :DrawQuestionText_02
//
//  work    :”＿は＿といくつですか？”描画
//  in      :int *ip_numtable   問題にでる数字テーブルへのポインタ
//          :int i_x            位置X
//          :int i_y            位置Y
//          :int i_z            位置Z
//  out     :なし
//  note    :左上中心
//          :数字はかならず一桁
//-----------------------------------------------------------------------------
static void DrawQuestionText_02(int *ip_numtable,int i_x,int i_y,int i_z)
{
    SPRITE_DATA SpData;
    int i;

    //問題数字
    for(i=0;i<2;i++)
    {
        DrawNoSmall(ip_numtable[i],i_x-8 + i*36 ,i_y+5,i_z-1);
    }
    
    //問題文
    SpData.No       = AIR_CHAR_QUESTION_TEXT_02;
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
//  関数名  :DrawQuestionText_03
//
//  work    :”＿じのときとけいのはりはどこをさしていますか？”描画
//  in      :int i_num      時間
//          :int i_x        位置X
//          :int i_y        位置Y
//          :int i_z        位置Z
//  out     :なし
//  note    :左上中心
//-----------------------------------------------------------------------------
static void DrawQuestionText_03(int i_num,int i_x,int i_y,int i_z)
{
    SPRITE_DATA SpData;

    //数字
    DrawNoSmall(i_num,i_x-8 ,i_y+5,i_z-1);

    //問題文
    SpData.No       = AIR_CHAR_QUESTION_TEXT_00;
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
//  関数名  :DrawQuestionText_04
//
//  work    :”＿じ＿＿ぷんのときとけいのはりはどこをさしていますか？”描画
//  in      :int ip_numtable
//          :int i_x
//          :int i_y
//          :int i_z
//  out     :なし
//  note    :左上中心
//-----------------------------------------------------------------------------
static void DrawQuestionText_04(int *ip_numtable,int i_x,int i_y,int i_z)
{
    SPRITE_DATA SpData;
    int i;

    //数字描画
    for(i=0;i<2;i++)
    {
        DrawNoSmall(ip_numtable[i],i_x + i*34 ,i_y+5,i_z-1);
    }

    //問題文
    SpData.No       = AIR_CHAR_QUESTION_TEXT_05;
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
//  関数名  :DrawQuestionText_05
//
//  work    :”どちらがおおいですか？”描画　(くだもの比べ)
//  in      :int *ip_numtable
//          :int i_x
//          :int i_y
//          :int i_z
//  out     :なし
//  note    :左上中心
//          :りんご。オレンジの順番
//-----------------------------------------------------------------------------
static void DrawQuestionText_05(int *ip_numtable,int i_x,int i_y,int i_z)
{
    static int FruitsKindTable[]={
        FRUITS_APPLE,
        FRUITS_MIKAN,
    };

    SPRITE_DATA SpData;
    int i;


    //果物
    for(i=0;i<2;i++)
    {
        DrawFruits(FruitsKindTable[i],ip_numtable[i],i_x+40+i * 90,i_y+26,i_z-1);
    }

    //問題文
    SpData.No       = AIR_CHAR_QUESTION_TEXT_03;
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
//  関数名  :DrawQuestionText_06
//
//  work    :”どちらがおおいですか？”描画　(パネル比べ)
//  in      :int i_num
//          :int i_x
//          :int i_y
//          :int i_z
//  out     :なし
//  note    :左上中心
//          :
//-----------------------------------------------------------------------------
static void DrawQuestionText_06(int *ip_numtable,int i_x,int i_y,int i_z)
{
    static int ColorTable[]={
        PANEL_COLOR_BLUE,
        PANEL_COLOR_PINK,
    };
    SPRITE_DATA SpData;
    int i;


    //パネル
    for(i=0;i<2;i++)
    {
        DrawNoPanel(ColorTable[i],ip_numtable[i],i_x + 70 + i * 40,i_y+26,i_z-1);
    }

    //問題文
    SpData.No       = AIR_CHAR_QUESTION_TEXT_03;
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
//  関数名  :DrawQuestionText
//
//  work    :問題文描画
//  in      :int i_kind     種類
//          :int i_no       番号
//  out     :
//  note    :なし
//-----------------------------------------------------------------------------
static void DrawQuestionText(int i_kind,int i_no)
{
    switch(i_kind)
    {
        
        case QUESTION_TEXT_00:      //”□に入るのはなんですか？”
            if(i_no>QUESTION_TEXT_00_NUM-1) i_no=QUESTION_TEXT_00_NUM-1;
            
             DrawQuestionText_00(   QuestionText00_Data[i_no].ProblemVal.Data,
                                    QUESTION_TEXT_00_POSX,
                                    QUESTION_TEXT_00_POSY,
                                    PRIORITY_QUIZ_TEXT);
            break;
        case QUESTION_TEXT_01:      //”＿と＿でいくつになりますか？”
            if(i_no>QUESTION_TEXT_01_NUM-1) i_no=QUESTION_TEXT_01_NUM-1;
            
             DrawQuestionText_01(   QuestionText01_Data[i_no].ProblemVal.Data,
                                    QUESTION_TEXT_01_POSX,
                                    QUESTION_TEXT_01_POSY,
                                    PRIORITY_QUIZ_TEXT);
            break;
        case QUESTION_TEXT_02:      //”＿は＿といくつですか？”
            if(i_no>QUESTION_TEXT_02_NUM-1) i_no=QUESTION_TEXT_02_NUM-1;
            
             DrawQuestionText_02(   QuestionText02_Data[i_no].ProblemVal.Data,
                                    QUESTION_TEXT_02_POSX,
                                    QUESTION_TEXT_02_POSY,
                                    PRIORITY_QUIZ_TEXT);
            break;
        case QUESTION_TEXT_03:      //”＿じのときとけいのはりはどこをさしていますか？”
            if(i_no>QUESTION_TEXT_03_NUM-1) i_no=QUESTION_TEXT_03_NUM-1;
            
             DrawQuestionText_03(   QuestionText03_Data[i_no].ProblemVal.Data[0],
                                    QUESTION_TEXT_03_POSX,
                                    QUESTION_TEXT_03_POSY,
                                    PRIORITY_QUIZ_TEXT);
            break;
        case QUESTION_TEXT_04:      //”＿じ＿ぷんのときとけいのはりはどこをさしていますか？”
            if(i_no>QUESTION_TEXT_04_NUM-1) i_no=QUESTION_TEXT_04_NUM-1;
            
             DrawQuestionText_04(   QuestionText04_Data[i_no].ProblemVal.Data,
                                    QUESTION_TEXT_04_POSX,
                                    QUESTION_TEXT_04_POSY,
                                    PRIORITY_QUIZ_TEXT);
            break;
        case QUESTION_TEXT_05:      //”どちらが大きいですか？（果物）”
            if(i_no>QUESTION_TEXT_05_NUM-1) i_no=QUESTION_TEXT_05_NUM-1;
            
             DrawQuestionText_05(   QuestionText05_Data[i_no].ProblemVal.Data,
                                    QUESTION_TEXT_05_POSX,
                                    QUESTION_TEXT_05_POSY,
                                    PRIORITY_QUIZ_TEXT);
            break;
        case QUESTION_TEXT_06:      //”どちらが大きいですか？（パネルの数字）”
            if(i_no>QUESTION_TEXT_06_NUM-1) i_no=QUESTION_TEXT_06_NUM-1;
            
             DrawQuestionText_06(   QuestionText06_Data[i_no].ProblemVal.Data,
                                    QUESTION_TEXT_06_POSX,
                                    QUESTION_TEXT_06_POSY,
                                    PRIORITY_QUIZ_TEXT);
            break;
        default:
    }
}



//-----------------------------------------------------------------------------
//  関数名  :GetAnswerData
//
//  work    :種類とインデックス情報から答えデータを取得
//  in      :int i_kind
//          :int i_index
//          :int i_num 
//          :ANSWER * ip_ans
//  out     :TRUE   成功
//          :FALSE  失敗
//  note    :なし
//-----------------------------------------------------------------------------
static int GetAnswerData(int i_kind,int i_index, int i_num ,ANSWER * ip_ans)
{
    switch(i_kind)
    {
        case QUESTION_TEXT_00:      //”□に入るのはなんですか？”
            if(i_index>QUESTION_TEXT_00_NUM-1)  return FALSE;
            
            ip_ans->QuestionData.Kind   = QuestionText00_Data[i_index].Kind;
            ip_ans->QuestionData.No     = QuestionText00_Data[i_index].AnswerVal.Data[i_num].Val;
            ip_ans->Flag                = QuestionText00_Data[i_index].AnswerVal.Data[i_num].Flag;
            ip_ans->QuestionData.Attr   = QuestionText00_Data[i_index].AnswerVal.Data[i_num].Attr;
            
            break;
        case QUESTION_TEXT_01:      //”＿と＿でいくつになりますか？”
            if(i_index>QUESTION_TEXT_01_NUM-1)  return FALSE;
            
            ip_ans->QuestionData.Kind   = QuestionText01_Data[i_index].Kind;
            ip_ans->QuestionData.No     = QuestionText01_Data[i_index].AnswerVal.Data[i_num].Val;
            ip_ans->Flag                = QuestionText01_Data[i_index].AnswerVal.Data[i_num].Flag;
            ip_ans->QuestionData.Attr   = QuestionText01_Data[i_index].AnswerVal.Data[i_num].Attr;
            break;
        case QUESTION_TEXT_02:      //”＿は＿といくつですか？”
            if(i_index>QUESTION_TEXT_02_NUM-1)  return FALSE;
            
            ip_ans->QuestionData.Kind   = QuestionText02_Data[i_index].Kind;
            ip_ans->QuestionData.No     = QuestionText02_Data[i_index].AnswerVal.Data[i_num].Val;
            ip_ans->Flag                = QuestionText02_Data[i_index].AnswerVal.Data[i_num].Flag;
            ip_ans->QuestionData.Attr   = QuestionText02_Data[i_index].AnswerVal.Data[i_num].Attr;
            break;
        case QUESTION_TEXT_03:      //”＿じのときとけいのはりはどこをさしていますか？”
            if(i_index>QUESTION_TEXT_03_NUM-1)  return FALSE;
            
            ip_ans->QuestionData.Kind   = QuestionText03_Data[i_index].Kind;
            ip_ans->QuestionData.No     = QuestionText03_Data[i_index].AnswerVal.Data[i_num].Val;
            ip_ans->Flag                = QuestionText03_Data[i_index].AnswerVal.Data[i_num].Flag;
            ip_ans->QuestionData.Attr   = QuestionText03_Data[i_index].AnswerVal.Data[i_num].Attr;
            break;
        case QUESTION_TEXT_04:      //”＿じ＿ぷんのときとけいのはりはどこをさしていますか？”
            if(i_index>QUESTION_TEXT_04_NUM-1)  return FALSE;
            
            ip_ans->QuestionData.Kind   = QuestionText04_Data[i_index].Kind;
            ip_ans->QuestionData.No     = QuestionText04_Data[i_index].AnswerVal.Data[i_num].Val;
            ip_ans->Flag                = QuestionText04_Data[i_index].AnswerVal.Data[i_num].Flag;
            ip_ans->QuestionData.Attr   = QuestionText04_Data[i_index].AnswerVal.Data[i_num].Attr;
            break;
        case QUESTION_TEXT_05:      //”どちらが大きいですか？（果物）”
            if(i_index>QUESTION_TEXT_05_NUM-1)  return FALSE;
            
            ip_ans->QuestionData.Kind   = QuestionText05_Data[i_index].Kind;
            ip_ans->QuestionData.No     = QuestionText05_Data[i_index].AnswerVal.Data[i_num].Val;
            ip_ans->Flag                = QuestionText05_Data[i_index].AnswerVal.Data[i_num].Flag;
            ip_ans->QuestionData.Attr   = QuestionText05_Data[i_index].AnswerVal.Data[i_num].Attr;
            break;
        case QUESTION_TEXT_06:      //”どちらが大きいですか？（パネルの数字）”
            if(i_index>QUESTION_TEXT_06_NUM-1)  return FALSE;
            
            ip_ans->QuestionData.Kind   = QuestionText06_Data[i_index].Kind;
            ip_ans->QuestionData.No     = QuestionText06_Data[i_index].AnswerVal.Data[i_num].Val;
            ip_ans->Flag                = QuestionText06_Data[i_index].AnswerVal.Data[i_num].Flag;
            ip_ans->QuestionData.Attr   = QuestionText06_Data[i_index].AnswerVal.Data[i_num].Attr;
            break;
        default:
            return FALSE;
    }
    
    return TRUE;
}




//-----------------------------------------------------------------------------
//  関数名  :問題を再生
//
//  work    :PlayQuestion
//  in      :int i_kind     種類
//          :int i_index    インデックス
//  out     :TRUE
//          :FALSE
//  note    :なし
//-----------------------------------------------------------------------------
static void PlayQuestion(int i_kind,int i_index)
{
    switch(i_kind)
    {
        case QUESTION_TEXT_00:
            dsPlayXa(XA_FILE_AIR19,0);
            break;
        case QUESTION_TEXT_01:
            dsPlayXa(   QuestionText01_XA_Data[i_index].FileNo,
                        QuestionText01_XA_Data[i_index].ChannelNo);
            break;
        case QUESTION_TEXT_02:
            dsPlayXa(   QuestionText02_XA_Data[i_index].FileNo,
                        QuestionText02_XA_Data[i_index].ChannelNo);
            break;
        case QUESTION_TEXT_03:
            dsPlayXa(   QuestionText03_XA_Data[i_index].FileNo,
                        QuestionText03_XA_Data[i_index].ChannelNo);
            break;
        case QUESTION_TEXT_04:
            dsPlayXa(   QuestionText04_XA_Data[i_index].FileNo,
                        QuestionText04_XA_Data[i_index].ChannelNo);
            break;
        case QUESTION_TEXT_05:
            dsPlayXa(XA_FILE_AIR18,0);
            break;
        case QUESTION_TEXT_06:
            dsPlayXa(XA_FILE_AIR18,0);
            break;
        default:
    }
}




//-----------------------------------------------------------------------------
//  関数名  :EventGunGun
//
//  work    :イベントグングン処理
//  in      :int i_type
//  out     :
//  note    :なし
//-----------------------------------------------------------------------------
static void EventGunGun(int i_type)
{
    static EVENT_CHAR GunGun[]={
        {   AIR_CHAR_EVENT_GUNGUN_04,   48,     54 + 16 + 16    },
        {   AIR_CHAR_EVENT_GUNGUN_05,   58+3,   35 + 10 + 16    },
        {   AIR_CHAR_EVENT_GUNGUN_00,   86+1,   63 + 16 + 16    },
        {   AIR_CHAR_EVENT_GUNGUN_01,   86,     63 + 16 + 16    },
        {   AIR_CHAR_EVENT_GUNGUN_02,   86,     58 + 18 + 16    },
        {   AIR_CHAR_EVENT_GUNGUN_03,   86,     58 + 18 + 16    },
    };

    static EVENT_CHAR GunGunMouse[]={
        {   AIR_CHAR_EVENT_GUNGUN_MOUSE_00,     130,    131+ 16 + 16    },  //正面口        オールクリア照れ
        {   AIR_CHAR_EVENT_GUNGUN_MOUSE_01,     130,    131+ 16 + 16    },  //正面口閉じ    オールクリア照れ
        {   AIR_CHAR_EVENT_GUNGUN_MOUSE_02,     116,    111+  8 + 16    },  //斜め口        ガッツポーズ
        {   AIR_CHAR_EVENT_GUNGUN_MOUSE_03,     116,    111+  9 + 16    },  //斜め口閉じ    ガッツポーズ
    };
    static int TereAnmTable[]={2,3};

    SPRITE_DATA SpData;
    TASK Task;


    switch(i_type)
    {
        case EVENT_CLEAR:
            ++AGameMgr.Event.GunTimer;
            if(!AGameMgr.Event.WaitFlag){
                if(AGameMgr.Event.GunTimer>EVENT_CLEAR_GUN_WAIT_TIME)
                {
                    AGameMgr.Event.GunTimer         = EVENT_CLEAR_GUN_WAIT_TIME;
                    AGameMgr.Event.GunNo            = 1;
                    AGameMgr.Event.WaitFlag         = 1;
                }
            }

            
            //体
            SpData.No       = GunGun[AGameMgr.Event.GunNo].No;
            SpData.PosX     = GunGun[AGameMgr.Event.GunNo].PosX;
            SpData.PosY     = GunGun[AGameMgr.Event.GunNo].PosY;
            SpData.PosZ     = PRIORITY_EVENT_CHAR;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );

            if(--AGameMgr.Event.GunXaWaitTimer<=0){
                if(dSoundStatus == DslStatStandby){
                    AGameMgr.Event.GunXaFlag=0;
                }
            }

            //口
            if(AGameMgr.Event.GunNo==1)
            {//ガッツポーズの時の口のアニメ
                if(!AGameMgr.Event.GunXaFlag){
                    AGameMgr.Event.GunMouseWt   = 0;
                    AGameMgr.Event.GunMouseNo   = 1;
                }else{
                    if(++AGameMgr.Event.GunMouseWt>EVENT_GUN_GUTS_MOUSE_PAT_TIME){
                        AGameMgr.Event.GunMouseWt   = 0;
                        AGameMgr.Event.GunMouseNo   ^=1;
                    }
                }
                
                SpData.No       = GunGunMouse[AGameMgr.Event.GunMouseNo+2].No;
                SpData.PosX     = GunGunMouse[AGameMgr.Event.GunMouseNo+2].PosX;
                SpData.PosY     = GunGunMouse[AGameMgr.Event.GunMouseNo+2].PosY;
                SpData.PosZ     = PRIORITY_EVENT_CHAR-1;
                SpData.ScaleX   = SCALE10;
                SpData.ScaleY   = SCALE10;
                SpData.Rotate   = ROTATE000;
                SpData.Reverse  = NOREVERS;
                DrawSprite( &SpData );
            }
            
            break;
        case EVENT_FALSE:
            ++AGameMgr.Event.GunTimer;

            if(!AGameMgr.Event.WaitFlag){
                if(AGameMgr.Event.GunTimer > EVENT_FALSE_PAT_00_TIME){
                    if(!AGameMgr.Script.Flag){
                        AGameMgr.Event.GunNo            = 1;
                        AGameMgr.Event.WaitFlag         = 1;
                        AGameMgr.Event.GunXaFlag        = 1;
                        AGameMgr.Event.GunXaWaitTimer   = GET_DA_STATUS_WAIT_TIME*3;
                        
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
                    }
                }
            }

            //体
            SpData.No       = GunGun[AGameMgr.Event.GunNo].No;
            SpData.PosX     = GunGun[AGameMgr.Event.GunNo].PosX;
            SpData.PosY     = GunGun[AGameMgr.Event.GunNo].PosY;
            SpData.PosZ     = PRIORITY_EVENT_CHAR;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );
            
            
            if(--AGameMgr.Event.GunXaWaitTimer<=0){
                if(dSoundStatus == DslStatStandby){
                    AGameMgr.Event.GunXaFlag=0;
                }
            }

            //口
            if(AGameMgr.Event.GunNo==1)
            {//ガッツポーズの時の口のアニメ
                if(!AGameMgr.Event.GunXaFlag){
                    AGameMgr.Event.GunMouseWt   = 0;
                    AGameMgr.Event.GunMouseNo   = 1;
                }else{
                    if(++AGameMgr.Event.GunMouseWt>EVENT_GUN_GUTS_MOUSE_PAT_TIME){
                        AGameMgr.Event.GunMouseWt   = 0;
                        AGameMgr.Event.GunMouseNo   ^=1;
                    }
                }
                
                SpData.No       = GunGunMouse[AGameMgr.Event.GunMouseNo+2].No;
                SpData.PosX     = GunGunMouse[AGameMgr.Event.GunMouseNo+2].PosX;
                SpData.PosY     = GunGunMouse[AGameMgr.Event.GunMouseNo+2].PosY;
                SpData.PosZ     = PRIORITY_EVENT_CHAR-1;
                SpData.ScaleX   = SCALE10;
                SpData.ScaleY   = SCALE10;
                SpData.Rotate   = ROTATE000;
                SpData.Reverse  = NOREVERS;
                DrawSprite( &SpData );
            }
            
            break;
        case EVENT_ALLCLEAR:
            switch(AGameMgr.Event.GunMode)
            {
                case EVENT_ALLCLEAR_GUN_MODE_GUTS:
                    ++AGameMgr.Event.GunTimer;
                    if(!AGameMgr.Event.GunFlag)
                    {
                        if(AGameMgr.Event.GunTimer>EVENT_ALL_CLEAR_PAT_00_TIME)
                        {//ガッツポーズセット
                            AGameMgr.Event.GunNo    = 1;
                            AGameMgr.Event.GunFlag  = 1;
                        }
                    }
                    
                    if(AGameMgr.Event.GunNo==1)
                    {//ガッツポーズ時の口アニメ
                        if(++AGameMgr.Event.GunMouseWt>EVENT_GUN_GUTS_MOUSE_PAT_TIME){
                            AGameMgr.Event.GunMouseWt   = 0;
                            AGameMgr.Event.GunMouseNo   ^=1;
                        }
                        
                        SpData.No       = GunGunMouse[AGameMgr.Event.GunMouseNo+2].No;
                        SpData.PosX     = GunGunMouse[AGameMgr.Event.GunMouseNo+2].PosX;
                        SpData.PosY     = GunGunMouse[AGameMgr.Event.GunMouseNo+2].PosY;
                        SpData.PosZ     = PRIORITY_EVENT_CHAR-1;
                        SpData.ScaleX   = SCALE10;
                        SpData.ScaleY   = SCALE10;
                        SpData.Rotate   = ROTATE000;
                        SpData.Reverse  = NOREVERS;
                        DrawSprite( &SpData );
                    }

                    if(!AGameMgr.Script.Flag){
                        if(--AGameMgr.Event.GunXaWaitTimer<=0){
                            if(dSoundStatus == DslStatStandby){
                                //ガッツポーズ終了、テレモードへ
                                AGameMgr.Event.GunXaFlag        = 1;
                                AGameMgr.Event.GunXaWaitTimer   = GET_DA_STATUS_WAIT_TIME*3;

                                AGameMgr.Event.GunMode  = EVENT_ALLCLEAR_GUN_MODE_TERE;
                                AGameMgr.Event.GunNo    = 2;
                                AGameMgr.Event.GunWt    = EVENT_ALL_CLEAR_PAT_02_TIME;
                                
                                //口アニメワーククリア
                                AGameMgr.Event.GunMouseWt   = 0;
                                AGameMgr.Event.GunMouseNo   = 0;
                                
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
                                Task.user[1]        = ALL_CLEAR_DEMO_2_SCRIPT_BASE;
                                Task.user[2]        = ALL_CLEAR_DEMO_2_SCRIPT_NUM;
                                CreateTask(&Task);
                            }
                        }
                    }


                    break;
                case EVENT_ALLCLEAR_GUN_MODE_TERE:

                    if(AGameMgr.Event.WaitFlag){
                        if(--AGameMgr.Event.GunXaWaitTimer<=0){
                            if(dSoundStatus == DslStatStandby){
                                AGameMgr.Event.WaitFlag     = 1;
                                AGameMgr.Event.GunMouseWt   = 0;
                                AGameMgr.Event.GunMouseNo   ^=1;
                            }
                        }
                    }

                    //体アニメ
                    if(--AGameMgr.Event.GunWt<0)
                    {
                        AGameMgr.Event.GunWt    = EVENT_ALL_CLEAR_PAT_02_TIME;
                        AGameMgr.Event.GunIndex ^= 1;
                        AGameMgr.Event.GunNo    = TereAnmTable[AGameMgr.Event.GunIndex];
                    }
                    
                    if(!AGameMgr.Event.WaitFlag){
                        //口アニメ
                        if(++AGameMgr.Event.GunMouseWt>EVENT_GUN_TERE_MOUSE_PAT_TIME){
                            AGameMgr.Event.GunMouseWt   = 0;
                            AGameMgr.Event.GunMouseNo   ^=1;
                        }
                    }
                    
                    if(AGameMgr.Event.GunMouseNo){
                        SpData.No       = GunGunMouse[AGameMgr.Event.GunMouseNo].No;
                        SpData.PosX     = GunGunMouse[AGameMgr.Event.GunMouseNo].PosX;
                        SpData.PosY     = GunGunMouse[AGameMgr.Event.GunMouseNo].PosY;
                        SpData.PosZ     = PRIORITY_EVENT_CHAR-1;
                        SpData.ScaleX   = SCALE10;
                        SpData.ScaleY   = SCALE10;
                        SpData.Rotate   = ROTATE000;
                        SpData.Reverse  = NOREVERS;
                        DrawSprite( &SpData );
                    }
                    break;
                default:
            }
            
            //体
            SpData.No       = GunGun[AGameMgr.Event.GunNo].No;
            SpData.PosX     = GunGun[AGameMgr.Event.GunNo].PosX;
            SpData.PosY     = GunGun[AGameMgr.Event.GunNo].PosY;
            SpData.PosZ     = PRIORITY_EVENT_CHAR;
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
//  関数名  :EventBg
//
//  work    :イベント背景処理
//  in      :int i_type
//  out     :なし
//  note    :なし
//-----------------------------------------------------------------------------
static void EventBg(int i_type)
{
    static int ClearEventBgTable[]={
        AIR_CHAR_EVENT_BG_12,AIR_CHAR_EVENT_BG_13,
        AIR_CHAR_EVENT_BG_14,AIR_CHAR_EVENT_BG_15,
        AIR_CHAR_EVENT_BG_10,AIR_CHAR_EVENT_BG_11,
    };

    static int FalseEventBgTable[]={
        AIR_CHAR_EVENT_BG_04,AIR_CHAR_EVENT_BG_05,
        AIR_CHAR_EVENT_BG_06,AIR_CHAR_EVENT_BG_07,
        AIR_CHAR_EVENT_BG_08,AIR_CHAR_EVENT_BG_09,
    };

    static EVENT_CHAR SpectatorTable[]={
        {   AIR_CHAR_EVENT_BUTA_00,         166,    2   + 20},  //ぶた
        {   AIR_CHAR_EVENT_BUTA_01,         166,    2   + 20},  //ぶた
        {   AIR_CHAR_EVENT_FOX_00,          22,     2   + 20},  //きつね
        {   AIR_CHAR_EVENT_FOX_01,          22,     2   + 20},  //きつね
        {   AIR_CHAR_EVENT_USAGI_00,        238,    60  + 36},  //うさぎ
        {   AIR_CHAR_EVENT_USAGI_01,        238,    60  + 36},  //うさぎ
        {   AIR_CHAR_EVENT_KAYORINU_00,     12,     67  + 20},  //カヨリーヌ
        {   AIR_CHAR_EVENT_KAYORINU_01,     12,     67  + 20},  //カヨリーヌ
        {   AIR_CHAR_EVENT_NEZUMI_00,       10,     133 + 20},  //ねずみ
        {   AIR_CHAR_EVENT_NEZUMI_01,       10,     133 + 20},  //ねずみ
        {   AIR_CHAR_EVENT_RISU_00,         238,    123 + 36},  //リス
        {   AIR_CHAR_EVENT_RISU_01,         238,    123 + 36},  //リス
    };

    SPRITE_DATA SpData;
    int i;


    switch(i_type)
    {
        case EVENT_CLEAR:
            if(++AGameMgr.Event.BgWt>EVENT_BG_ANM_WAIT_TIME)
            {
                AGameMgr.Event.BgWt = 0;
                if(++AGameMgr.Event.BgNo>2)
                {
                    AGameMgr.Event.BgNo=0;
                }
            }
            
            //背景描画
            SpData.No       = ClearEventBgTable[AGameMgr.Event.BgNo*2];
            SpData.PosX     = 0;
            SpData.PosY     = 0;
            SpData.PosZ     = PRIORITY_EVENT_BG;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );
            
            SpData.No       = ClearEventBgTable[AGameMgr.Event.BgNo*2+1];
            SpData.PosX     = 256;
            SpData.PosY     = 0;
            SpData.PosZ     = PRIORITY_EVENT_BG;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );
            
            break;
        case EVENT_FALSE:
            if(++AGameMgr.Event.BgTimer>EVENT_BG_FALSE_MODE_CHANGE_TIME)
            {
                AGameMgr.Event.BgTimer=EVENT_BG_FALSE_MODE_CHANGE_TIME;
                AGameMgr.Event.BgMode=1;
            }
            
            if(AGameMgr.Event.BgMode==0)
            {// 残念
                //背景描画
                SpData.No       = AIR_CHAR_EVENT_BG_00;
                SpData.PosX     = 0;
                SpData.PosY     = 0;
                SpData.PosZ     = PRIORITY_EVENT_BG;
                SpData.ScaleX   = SCALE10;
                SpData.ScaleY   = SCALE10;
                SpData.Rotate   = ROTATE000;
                SpData.Reverse  = NOREVERS;
                DrawSprite( &SpData );
                
                SpData.No       = AIR_CHAR_EVENT_BG_01;
                SpData.PosX     = 256;
                SpData.PosY     = 0;
                SpData.PosZ     = PRIORITY_EVENT_BG;
                SpData.ScaleX   = SCALE10;
                SpData.ScaleY   = SCALE10;
                SpData.Rotate   = ROTATE000;
                SpData.Reverse  = NOREVERS;
                DrawSprite( &SpData );
            }else
            {//がんばるぞ
                if(++AGameMgr.Event.BgWt>EVENT_BG_ANM_WAIT_TIME)
                {
                    AGameMgr.Event.BgWt = 0;
                    if(++AGameMgr.Event.BgNo>2)
                    {
                        AGameMgr.Event.BgNo=0;
                    }
                }
                
                //背景描画
                SpData.No       = FalseEventBgTable[AGameMgr.Event.BgNo*2];
                SpData.PosX     = 0;
                SpData.PosY     = 0;
                SpData.PosZ     = PRIORITY_EVENT_BG;
                SpData.ScaleX   = SCALE10;
                SpData.ScaleY   = SCALE10;
                SpData.Rotate   = ROTATE000;
                SpData.Reverse  = NOREVERS;
                DrawSprite( &SpData );
                
                SpData.No       = FalseEventBgTable[AGameMgr.Event.BgNo*2+1];
                SpData.PosX     = 256;
                SpData.PosY     = 0;
                SpData.PosZ     = PRIORITY_EVENT_BG;
                SpData.ScaleX   = SCALE10;
                SpData.ScaleY   = SCALE10;
                SpData.Rotate   = ROTATE000;
                SpData.Reverse  = NOREVERS;
                DrawSprite( &SpData );
            }
            
            break;
        case EVENT_ALLCLEAR:
            if(++AGameMgr.Event.BgWt>EVENT_BG_FALSE_ANM_WAIT_TIME)
            {
                AGameMgr.Event.BgWt = 0;
                AGameMgr.Event.SpectatorNo  ^= 1;
            }
            
            for(i=0;i<6;i++){
                    SpData.No       = SpectatorTable[i*2+AGameMgr.Event.SpectatorNo].No;
                    SpData.PosX     = SpectatorTable[i*2+AGameMgr.Event.SpectatorNo].PosX;
                    SpData.PosY     = SpectatorTable[i*2+AGameMgr.Event.SpectatorNo].PosY;
                    SpData.PosZ     = PRIORITY_EVENT_BG - i*10;
                    SpData.ScaleX   = SCALE10;
                    SpData.ScaleY   = SCALE10;
                    SpData.Rotate   = ROTATE000;
                    SpData.Reverse  = NOREVERS;
                    DrawSprite( &SpData );
            }

            for(i=0;i<6;i++){
                    SpData.No       = SpectatorTable[i*2+AGameMgr.Event.SpectatorNo].No;
                    SpData.PosX     = SpectatorTable[i*2+AGameMgr.Event.SpectatorNo].PosX;
                    SpData.PosY     = SpectatorTable[i*2+AGameMgr.Event.SpectatorNo].PosY;
                    SpData.PosZ     = PRIORITY_EVENT_BG - i*10;
                    SpData.ScaleX   = SCALE10;
                    SpData.ScaleY   = SCALE10;
                    SpData.Rotate   = ROTATE000;
                    SpData.Reverse  = NOREVERS;
                    DrawSprite( &SpData );
            }

            
            //背景描画
            SpData.No       = AIR_CHAR_EVENT_BG_02;
            SpData.PosX     = 0;
            SpData.PosY     = 0;
            SpData.PosZ     = PRIORITY_EVENT_BG;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );
            
            SpData.No       = AIR_CHAR_EVENT_BG_03;
            SpData.PosX     = 256;
            SpData.PosY     = 0;
            SpData.PosZ     = PRIORITY_EVENT_BG;
            SpData.ScaleX   = SCALE10;
            SpData.ScaleY   = SCALE10;
            SpData.Rotate   = ROTATE000;
            SpData.Reverse  = NOREVERS;
            DrawSprite( &SpData );
            
            break;
        default:
    }
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
//                  AGameMgr.Script.Flag    = 1;
//                  AGameMgr.Script.Index   = 0;
//                  AGameMgr.Script.Line    = ip_task->user[0];
//                  AGameMgr.Script.Base    = ip_task->user[1];
//                  AGameMgr.Script.Num     = ip_task->user[2];
//                  
//                  break;
//              //---------------------------------------------------------------------
//              case TASK_MODE_MAIN:
//                  
//                  if(MetuseijiFlag==OFF)
//                  {
//                      switch(AGameMgr.Script.Line)
//                      {
//                          case SCRIPT_LINE_1:
//                              MenuMessageSet10(&AirScript[AGameMgr.Script.Base + AGameMgr.Script.Index]);
//                              break;
//                          case SCRIPT_LINE_2:
//                              MenuMessageSet20(&AirScript[AGameMgr.Script.Base + AGameMgr.Script.Index]);
//                              break;
//                          case SCRIPT_LINE_3:
//                              MenuMessageSet30(&AirScript[AGameMgr.Script.Base + AGameMgr.Script.Index]);
//                              break;
//                          default:
//                      }
//                      
//                      if(++AGameMgr.Script.Index >= AGameMgr.Script.Num)
//                      {
//                          ip_task->mode = TASK_MODE_EXIT;
//                      }
//                  }
//                  break;
//              //---------------------------------------------------------------------
//              case TASK_MODE_EXIT:
//                  AGameMgr.Script.Flag    = 0;
//                  
//                  //自分を削除
//                  ExitTask(ip_task->id);
//                  break;
//
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

            AGameMgr.Script.Flag    = 1;
            AGameMgr.Script.Index   = 0;
            AGameMgr.Script.Line    = ip_task->user[0];
            AGameMgr.Script.Base    = ip_task->user[1];
            AGameMgr.Script.Num     = ip_task->user[2];
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
                        switch(AGameMgr.Script.Line)
                        {
                            case SCRIPT_LINE_1:
                                MenuMessageSet10(&AirScript[AGameMgr.Script.Base + AGameMgr.Script.Index]);
                                break;
                            case SCRIPT_LINE_2:
                                MenuMessageSet20(&AirScript[AGameMgr.Script.Base + AGameMgr.Script.Index]);
                                break;
                            case SCRIPT_LINE_3:
                                MenuMessageSet30(&AirScript[AGameMgr.Script.Base + AGameMgr.Script.Index]);
                                break;
                            default:
                        }
                        
                        if(++AGameMgr.Script.Index >= AGameMgr.Script.Num){
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
            
            AGameMgr.Script.Flag    = 0;
            
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
            AGameMgr.ExitFlag   = 1;
            
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
//  in      :TASK*      タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int AllClearEventTask(TASK* ip_task)
{
    SPRITE_DATA SpData;
    TASK Task;

    switch(ip_task->mode)
    {
        //---------------------------------------------------------------------初期化
        case TASK_MODE_INIT:
            //----next mode
            ip_task->mode = TASK_MODE_MAIN;
            
            //----texture read cd -> sram -> vram
            if((file_read(AirEventTextureFile[0].fn,LoadAddress)) == -1)
            {//read error
                return FALSE;
            }
            
            //----texture init
            TexInit( AIR_EVENT_TIM_NUM, &AirEventTextureImage[AIR_EVENT_TIM_POS] );
            TimImgData = AirEventTextureImage;
            
            //----ゲーム用スプライト登録
            EntrySprite( AirEventSpriteData );
            
            //----イベント
            AGameMgr.Event.BgNo         = 0;
            AGameMgr.Event.BgWt         = 0;
            AGameMgr.Event.BgTimer      = 0;
            AGameMgr.Event.BgMode       = 0;
            AGameMgr.Event.GunMouseNo   = 0;
            AGameMgr.Event.GunMouseWt   = 0;
            AGameMgr.Event.GunMouseIndex= 0;
            AGameMgr.Event.GunNo        = 0;
            AGameMgr.Event.GunWt        = 0;
            AGameMgr.Event.GunTimer     = 0;
            AGameMgr.Event.GunMode      = EVENT_ALLCLEAR_GUN_MODE_GUTS;
            AGameMgr.Event.SpectatorNo  = 0;
            AGameMgr.Event.GunFlag      = 0;
            AGameMgr.Event.GunIndex     = 0;
            AGameMgr.Event.GunXaFlag        = 0;
            AGameMgr.Event.GunXaWaitTimer   = 0;
            AGameMgr.Event.Timer        = 0;
            AGameMgr.Event.EndFlag      = 0;
            AGameMgr.Event.WaitFlag     = 0;
            
            //終了処理メニュー
            AGameMgr.SelectContinue.Val         = 0;
            AGameMgr.SelectContinue.Type        = SELECT_RETRY_H;
            AGameMgr.SelectContinue.No          = 0;
            AGameMgr.SelectContinue.Wt          = 0;
            AGameMgr.SelectContinue.FadeFlag    = 0;

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
            Task.user[1]        = ALL_CLEAR_DEMO_1_SCRIPT_BASE;
            Task.user[2]        = ALL_CLEAR_DEMO_1_SCRIPT_NUM;
            CreateTask(&Task);

            AGameMgr.Event.GunXaFlag        = 1;
            AGameMgr.Event.GunXaWaitTimer   = GET_DA_STATUS_WAIT_TIME*3;

#ifdef  __DEBUG_AIR__
            // フェードInします
            GameMgr.FadeFlag = FadeIn;
#endif

            break;
        //---------------------------------------------------------------------メイン
        case TASK_MODE_MAIN:
            ++AGameMgr.Event.Timer;
            if(AGameMgr.Event.Timer>ALL_CLEAR_EVENT_TIME){
                AGameMgr.Event.EndFlag=1;
            }

            EventGunGun(EVENT_ALLCLEAR);        //グングン
            EventBg(EVENT_ALLCLEAR);            //背景処理

            //イベント終了後この処理を起動
            if(AGameMgr.Event.EndFlag)
            {
                if(SelectContinue(!AGameMgr.SelectContinue.FadeFlag))
                {//●ボタンが押された
                    if(!AGameMgr.SelectContinue.FadeFlag)
                    {//フェード中
                        if((AGameMgr.SelectContinue.Val==0) && (AGameMgr.SelectContinue.Type==SELECT_RETRY_H))
                        {//もう一度プレイしますか？　はい
                            AGameMgr.SelectContinue.FadeFlag    = 1;
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
                        if( (AGameMgr.SelectContinue.Val==1) && (AGameMgr.SelectContinue.Type==SELECT_RETRY_H))
                        {//もう一度プレイしますか？　いいえ
                            AGameMgr.SelectContinue.Type    =SELECT_END_H;
                            AGameMgr.SelectContinue.Val     = 0;
                        }else
                        if((AGameMgr.SelectContinue.Type==SELECT_END_H) && (AGameMgr.SelectContinue.Val==0))
                        {//やめますか？　はい
                            AGameMgr.SelectContinue.FadeFlag    = 1;
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
                        if((AGameMgr.SelectContinue.Type==SELECT_END_H) && (AGameMgr.SelectContinue.Val==1))
                        {//やめますか？　いいえ
                            AGameMgr.SelectContinue.Type    = SELECT_RETRY_H;
                            AGameMgr.SelectContinue.Val     = 0;
                        }else
                        {
                            
                        }
                    }else
                    {
                        
                    }
                }
            }
            
            
            break;
        //---------------------------------------------------------------------終了
        case TASK_MODE_EXIT:
            //----登録スプライト開放
            ReleaseSprite();
            
            //----2択：もう一度プレイする／やめる
            if((AGameMgr.SelectContinue.Val==0) && (AGameMgr.SelectContinue.Type==SELECT_RETRY_H))
            {//もう一度プレイする
                //継続プレイフラグをクリアする
                AGameMgr.Air.ContinueFlag   = 0;
                
                //コントロールフラグクリア
                AGameMgr.Air.ControllFlag   = 0;
                
                //セレクトレベルフラグセット
                AGameMgr.SelectLevelFlag    = 1;
                
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
            }else
            {//やめる
                //コントロールフラグクリア
                AGameMgr.Air.ControllFlag   = 0;
                
                //ゲーム終了
                AGameMgr.ExitFlag           = 1;
            }
            
            //自分を削除
            ExitTask(ip_task->id);
            break;
    }
}


//-----------------------------------------------------------------------------
//  関数名  :ClearEventTask
//
//  work    :ノーマルクリアイベントタスク
//  in      :TASK*      タスクポインタ
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int ClearEventTask(TASK* ip_task)
{
    SPRITE_DATA SpData;
    TASK Task;

    switch(ip_task->mode)
    {
        //----------------------------------------------------------------初期化
        case TASK_MODE_INIT:
            //----next mode
            ip_task->mode = TASK_MODE_MAIN;
            
            //----texture read cd -> sram -> vram
            if((file_read(AirEventTextureFile[0].fn,LoadAddress)) == -1)
            {//read error
                return FALSE;
            }
            
            //----texture init
            TexInit( AIR_EVENT_TIM_NUM, &AirEventTextureImage[AIR_EVENT_TIM_POS] );
            TimImgData = AirEventTextureImage;
            
            //----ゲーム用スプライト登録
            EntrySprite( AirEventSpriteData );
            
            //----イベント
            AGameMgr.Event.BgNo         = 0;
            AGameMgr.Event.BgWt         = 0;
            AGameMgr.Event.BgTimer      = 0;
            AGameMgr.Event.BgMode       = 0;
            AGameMgr.Event.GunMouseNo   = 0;
            AGameMgr.Event.GunMouseWt   = 0;
            AGameMgr.Event.GunMouseIndex= 0;
            AGameMgr.Event.GunNo        = 0;
            AGameMgr.Event.GunWt        = 0;
            AGameMgr.Event.GunTimer     = 0;
            AGameMgr.Event.GunMode      = 0;
            AGameMgr.Event.GunFlag      = 0;
            AGameMgr.Event.GunIndex     = 0;
            AGameMgr.Event.GunXaFlag        = 0;
            AGameMgr.Event.GunXaWaitTimer   = 0;
            AGameMgr.Event.SpectatorNo  = 0;
            AGameMgr.Event.Timer        = 0;
            AGameMgr.Event.EndFlag      = 0;
            AGameMgr.Event.WaitFlag     = 0;


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

            AGameMgr.Event.GunXaFlag        = 1;
            AGameMgr.Event.GunXaWaitTimer   = GET_DA_STATUS_WAIT_TIME*3;

            //終了処理メニュー
            AGameMgr.SelectContinue.Val         = 0;
            AGameMgr.SelectContinue.Type        = SELECT_RETRY_H;
            AGameMgr.SelectContinue.No          = 0;
            AGameMgr.SelectContinue.Wt          = 0;
            AGameMgr.SelectContinue.FadeFlag    = 0;

#ifdef  __DEBUG_AIR__
            // フェードInします
            GameMgr.FadeFlag = FadeIn;
#endif
            break;
        //----------------------------------------------------------------メイン
        case TASK_MODE_MAIN:
            ++AGameMgr.Event.Timer;
            if(AGameMgr.Event.Timer>CLEAR_EVENT_TIME){
                AGameMgr.Event.EndFlag=1;
            }

            EventGunGun(EVENT_CLEAR);   //グングン
            EventBg(EVENT_CLEAR);       //背景処理


            //イベント終了後この処理を起動
            if(AGameMgr.Event.EndFlag)
            {
                if(SelectContinue(!AGameMgr.SelectContinue.FadeFlag))
                {//●ボタンが押された
                    if(!AGameMgr.SelectContinue.FadeFlag)
                    {//フェード中
                        if((AGameMgr.SelectContinue.Val==0) && (AGameMgr.SelectContinue.Type==SELECT_RETRY_H))
                        {//もう一度プレイしますか？　はい
                            AGameMgr.SelectContinue.FadeFlag    = 1;
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
                        if( (AGameMgr.SelectContinue.Val==1) && (AGameMgr.SelectContinue.Type==SELECT_RETRY_H))
                        {//もう一度プレイしますか？　いいえ
                            AGameMgr.SelectContinue.Type    =SELECT_END_H;
                            AGameMgr.SelectContinue.Val     = 0;
                        }else
                        if((AGameMgr.SelectContinue.Type==SELECT_END_H) && (AGameMgr.SelectContinue.Val==0))
                        {//やめますか？　はい
                            AGameMgr.SelectContinue.FadeFlag    = 1;
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
                        if((AGameMgr.SelectContinue.Type==SELECT_END_H) && (AGameMgr.SelectContinue.Val==1))
                        {//やめますか？　いいえ
                            AGameMgr.SelectContinue.Type    = SELECT_RETRY_H;
                            AGameMgr.SelectContinue.Val     = 0;
                        }else
                        {
                            
                        }
                    }else
                    {
                        
                    }
                }
            }
            
            break;
        //----------------------------------------------------------------終了
        case TASK_MODE_EXIT:

            //----登録スプライト開放
            ReleaseSprite();
            
            //----2択：もう一度プレイする／やめる
            if((AGameMgr.SelectContinue.Val==0) && (AGameMgr.SelectContinue.Type==SELECT_RETRY_H))
            {//もう一度プレイする
                //継続プレイフラグをクリアする
                AGameMgr.Air.ContinueFlag   = 0;
                
                //コントロールフラグクリア
                AGameMgr.Air.ControllFlag   = 0;
                
                //セレクトレベルフラグセット
                AGameMgr.SelectLevelFlag    = 1;
                
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
            }else
            {//やめる
                //コントロールフラグクリア
                AGameMgr.Air.ControllFlag   = 0;
                
                //ゲーム終了
                AGameMgr.ExitFlag           = 1;
            }
            
            //自分を削除
            ExitTask(ip_task->id);
            break;
    }
}


//-----------------------------------------------------------------------------
//  関数名  :FalseEventTask
//
//  work    :時間切れイベント
//  in      :TASK* ip_task
//  out     :TRUE
//  note    :なし
//-----------------------------------------------------------------------------
static int FalseEventTask(TASK* ip_task)
{
    SPRITE_DATA SpData;
    TASK Task;


    switch(ip_task->mode)
    {
        //----------------------------------------------------------------初期化
        case TASK_MODE_INIT:
            //----next mode
            ip_task->mode = TASK_MODE_MAIN;
            
            //----texture read cd -> sram -> vram
            if((file_read(AirEventTextureFile[0].fn,LoadAddress)) == -1)
            {//read error
                return FALSE;
            }
            
            //----texture init
            TexInit( AIR_EVENT_TIM_NUM, &AirEventTextureImage[AIR_EVENT_TIM_POS] );
            TimImgData = AirEventTextureImage;
            
            //----ゲーム用スプライト登録
            EntrySprite( AirEventSpriteData );
            
            //----イベント
            AGameMgr.Event.BgNo         = 0;
            AGameMgr.Event.BgWt         = 0;
            AGameMgr.Event.BgTimer      = 0;
            AGameMgr.Event.BgMode       = 0;
            AGameMgr.Event.GunMouseNo   = 0;
            AGameMgr.Event.GunMouseWt   = 0;
            AGameMgr.Event.GunMouseIndex= 0;
            AGameMgr.Event.GunNo        = 5;
            AGameMgr.Event.GunWt        = 0;
            AGameMgr.Event.GunTimer     = 0;
            AGameMgr.Event.GunMode      = 0;
            AGameMgr.Event.GunFlag      = 0;
            AGameMgr.Event.GunIndex     = 0;
            AGameMgr.Event.GunXaFlag        = 0;
            AGameMgr.Event.GunXaWaitTimer   = 0;
            AGameMgr.Event.SpectatorNo  = 0;
            AGameMgr.Event.Timer        = 0;
            AGameMgr.Event.EndFlag      = 0;
            AGameMgr.Event.WaitFlag     = 0;

            //終了処理メニュー
            AGameMgr.SelectContinue.Val         = 0;
            AGameMgr.SelectContinue.Type        = SELECT_RETRY_H;
            AGameMgr.SelectContinue.No          = 0;
            AGameMgr.SelectContinue.Wt          = 0;
            AGameMgr.SelectContinue.FadeFlag    = 0;

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

#ifdef  __DEBUG_AIR__
            // フェードInします
            GameMgr.FadeFlag = FadeIn;
#endif
            break;
        //----------------------------------------------------------------メイン
        case TASK_MODE_MAIN:
            ++AGameMgr.Event.Timer;
            if(AGameMgr.Event.Timer>FALSE_EVENT_TIME){
                AGameMgr.Event.EndFlag=1;
            }

            EventGunGun(EVENT_FALSE);       //グングン
            EventBg(EVENT_FALSE);           //背景処理

            //イベント終了後この処理を起動
            if(AGameMgr.Event.EndFlag)
            {
                if(SelectContinue(!AGameMgr.SelectContinue.FadeFlag))
                {//●ボタンが押された
                    if(!AGameMgr.SelectContinue.FadeFlag)
                    {//フェード中
                        if((AGameMgr.SelectContinue.Val==0) && (AGameMgr.SelectContinue.Type==SELECT_RETRY_H))
                        {//もう一度プレイしますか？　はい
                            AGameMgr.SelectContinue.FadeFlag    = 1;
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
                        if( (AGameMgr.SelectContinue.Val==1) && (AGameMgr.SelectContinue.Type==SELECT_RETRY_H))
                        {//もう一度プレイしますか？　いいえ
                            AGameMgr.SelectContinue.Type    =SELECT_END_H;
                            AGameMgr.SelectContinue.Val     = 0;
                        }else
                        if((AGameMgr.SelectContinue.Type==SELECT_END_H) && (AGameMgr.SelectContinue.Val==0))
                        {//やめますか？　はい
                            AGameMgr.SelectContinue.FadeFlag    = 1;
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
                        if((AGameMgr.SelectContinue.Type==SELECT_END_H) && (AGameMgr.SelectContinue.Val==1))
                        {//やめますか？　いいえ
                            AGameMgr.SelectContinue.Type    = SELECT_RETRY_H;
                            AGameMgr.SelectContinue.Val     = 0;
                        }else
                        {
                            
                        }
                    }else
                    {
                        
                    }
                }
            }
            
            
            break;
        //----------------------------------------------------------------終了
        case TASK_MODE_EXIT:
            //----登録スプライト開放
            ReleaseSprite();
            
            //----2択：もう一度プレイする／やめる
            if((AGameMgr.SelectContinue.Val==0) && (AGameMgr.SelectContinue.Type==SELECT_RETRY_H))
            {//もう一度プレイする
                //継続プレイフラグをクリアする
                AGameMgr.Air.ContinueFlag   = 0;
                
                //コントロールフラグクリア
                AGameMgr.Air.ControllFlag   = 0;
                
                //セレクトレベルフラグセット
                AGameMgr.SelectLevelFlag    = 1;
                
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
            }else
            {//やめる
                //コントロールフラグクリア
                AGameMgr.Air.ControllFlag   = 0;
                
                //ゲーム終了
                AGameMgr.ExitFlag           = 1;
            }
            
            //自分を削除
            ExitTask(ip_task->id);
            break;
    }
}

//-----------------------------------------------------------------------------
//  関数名 :SelectContinue
//  機能   :クリアイベント後の選択
//  注意   :なし
//-----------------------------------------------------------------------------
static int SelectContinue(int i_flag)
{
    static int BupeAnmTable[] ={
        AIR_CHAR_EVENT_SELECT_CONTINUE_BUPE_00,
        AIR_CHAR_EVENT_SELECT_CONTINUE_BUPE_01,
    };

    static int MaruBatuTable[]={
        AIR_CHAR_EVENT_SELECT_CONTINUE_YES_LIGHT,   AIR_CHAR_EVENT_SELECT_CONTINUE_NO_DARK,
        AIR_CHAR_EVENT_SELECT_CONTINUE_YES_DARK,    AIR_CHAR_EVENT_SELECT_CONTINUE_NO_LIGHT,
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
            AGameMgr.SelectContinue.Val^=1;
            //[♪] レバー音
            ssPlaySe(BUTONSE_LEVER);
        }
    }


    //はい・いいえ
    SpData.No       = MaruBatuTable[AGameMgr.SelectContinue.Val*2];     //インデックス番号
    SpData.PosX     = 68+72;                                            //X位置
    SpData.PosY     = 73+57;                                            //Y位置
    SpData.PosZ     = PRIORITY_AIR_GAME_EVENT_MENU-2;                   //優先順位
    SpData.ScaleX   = SCALE10;                                          //スケールX
    SpData.ScaleY   = SCALE10;                                          //スケールY
    SpData.Rotate   = ROTATE000;                                        //回転角
    SpData.Reverse  = NOREVERS;                                         //反転コード
    DrawSprite( &SpData );                                              //スプライト描画

    SpData.No       = MaruBatuTable[AGameMgr.SelectContinue.Val*2+1];   //インデックス番号
    SpData.PosX     = 68+126;                                           //X位置
    SpData.PosY     = 73+57;                                            //Y位置
    SpData.PosZ     = PRIORITY_AIR_GAME_EVENT_MENU-2;                   //優先順位
    SpData.ScaleX   = SCALE10;                                          //スケールX
    SpData.ScaleY   = SCALE10;                                          //スケールY
    SpData.Rotate   = ROTATE000;                                        //回転角
    SpData.Reverse  = NOREVERS;                                         //反転コード
    DrawSprite( &SpData );                                              //スプライト描画

    //プレート文字
    switch(AGameMgr.SelectContinue.Type)
    {
        case SELECT_RETRY_H:
            SpData.No       = AIR_CHAR_EVENT_SELECT_CONTINUE_RETRY_H;   //インデックス番号
            SpData.PosX     = 68+20;                                    //X位置
            SpData.PosY     = 73+20;                                    //Y位置
            SpData.PosZ     = PRIORITY_AIR_GAME_EVENT_MENU-2;           //優先順位
            SpData.ScaleX   = SCALE10;                                  //スケールX
            SpData.ScaleY   = SCALE10;                                  //スケールY
            SpData.Rotate   = ROTATE000;                                //回転角
            SpData.Reverse  = NOREVERS;                                 //反転コード
            DrawSprite( &SpData );                                      //スプライト描画
            break;
        case SELECT_END_H:
            SpData.No       = AIR_CHAR_EVENT_SELECT_CONTINUE_END_H; //インデックス番号
            SpData.PosX     = 68+20;                                    //X位置
            SpData.PosY     = 73+20;                                    //Y位置
            SpData.PosZ     = PRIORITY_AIR_GAME_EVENT_MENU-2;           //優先順位
            SpData.ScaleX   = SCALE10;                                  //スケールX
            SpData.ScaleY   = SCALE10;                                  //スケールY
            SpData.Rotate   = ROTATE000;                                //回転角
            SpData.Reverse  = NOREVERS;                                 //反転コード
            DrawSprite( &SpData );                                      //スプライト描画
            break;
        case SELECT_CONTINUE_H:
            SpData.No       = AIR_CHAR_EVENT_SELECT_CONTINUE_CONTINUE_H;//インデックス番号
            SpData.PosX     = 68+20;                                    //X位置
            SpData.PosY     = 73+20;                                    //Y位置
            SpData.PosZ     = PRIORITY_AIR_GAME_EVENT_MENU-2;           //優先順位
            SpData.ScaleX   = SCALE10;                                  //スケールX
            SpData.ScaleY   = SCALE10;                                  //スケールY
            SpData.Rotate   = ROTATE000;                                //回転角
            SpData.Reverse  = NOREVERS;                                 //反転コード
            DrawSprite( &SpData );                                      //スプライト描画
            break;
        default:
    }

    //ブーぺ
    if(++AGameMgr.SelectContinue.Wt > SELECT_LEVEL_PUPE_ANM_TIME){
        AGameMgr.SelectContinue.No^=1;
        AGameMgr.SelectContinue.Wt=0;
    }
    SpData.No       = BupeAnmTable[AGameMgr.SelectContinue.No]; //インデックス番号
    SpData.PosX     = 68+12;                                    //X位置
    SpData.PosY     = 73+34;                                    //Y位置
    SpData.PosZ     = PRIORITY_AIR_GAME_EVENT_MENU-10;          //優先順位
    SpData.ScaleX   = SCALE10;                                  //スケールX
    SpData.ScaleY   = SCALE10;                                  //スケールY
    SpData.Rotate   = ROTATE000;                                //回転角
    SpData.Reverse  = NOREVERS;                                 //反転コード
    DrawSprite( &SpData );                                      //スプライト描画

    //プレート
    SpData.No       = AIR_CHAR_EVENT_SELECT_CONTINUE_PLATE; //インデックス番号
    SpData.PosX     = 68;                                       //X位置
    SpData.PosY     = 73;                                       //Y位置
    SpData.PosZ     = PRIORITY_AIR_GAME_EVENT_MENU;             //優先順位
    SpData.ScaleX   = SCALE10;                                  //スケールX
    SpData.ScaleY   = SCALE10;                                  //スケールY
    SpData.Rotate   = ROTATE000;                                //回転角
    SpData.Reverse  = NOREVERS;                                 //反転コード
    DrawSprite( &SpData );                                      //スプライト描画

    //えらぶ
    SpData.No       = AIR_CHAR_EVENT_SELECT_CONTINUE_ERABU;     //インデックス番号
    SpData.PosX     = (320-130)/2;                              //X位置
    SpData.PosY     = 206;                                      //Y位置
    SpData.PosZ     = PRIORITY_AIR_GAME_EVENT_MENU;             //優先順位
    SpData.ScaleX   = SCALE10;                                  //スケールX
    SpData.ScaleY   = SCALE10;                                  //スケールY
    SpData.Rotate   = ROTATE000;                                //回転角
    SpData.Reverse  = NOREVERS;                                 //反転コード
    DrawSprite( &SpData );                                      //スプライト描画

    //けってい
    SpData.No       = AIR_CHAR_EVENT_SELECT_CONTINUE_KETEI;     //インデックス番号
    SpData.PosX     = (320-130)/2+78;                           //X位置
    SpData.PosY     = 206;                                      //Y位置
    SpData.PosZ     = PRIORITY_AIR_GAME_EVENT_MENU;             //優先順位
    SpData.ScaleX   = SCALE10;                                  //スケールX
    SpData.ScaleY   = SCALE10;                                  //スケールY
    SpData.Rotate   = ROTATE000;                                //回転角
    SpData.Reverse  = NOREVERS;                                 //反転コード
    DrawSprite( &SpData );                                      //スプライト描画

    return o_ret;
}




#ifdef __DEBUG_AIR__
//-----------------------------------------------------------------------------
//  関数名 :DebugGameSpriteTask
//
//  work   :スプライトタスク
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
        //----------------------------------------------------------------初期化
        case TASK_MODE_INIT:
            //----
            ip_task->mode = TASK_MODE_MAIN;

            //----texture read sram -> vram
            if((file_read(AirGameTextureFile[0].fn,LoadAddress)) == -1)
            {//read error
                return FALSE;
            }

            //----texture init
            TexInit( AIR_GAME_TIM_NUM, &AirGameTextureImage[AIR_GAME_TIM_POS] );
            TimImgData = AirGameTextureImage;

            //----ゲーム用スプライト登録
            EntrySprite( AirGameSpriteData );

            //----
            SpIndex     = 0;
            SpEntryNum  = GetEntrySpriteNum();
            Counter     = 0;

            // フェードInします
            GameMgr.FadeFlag = FadeIn;

            break;
        //----------------------------------------------------------------メイン
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
            SpData.PosX     = (320 - AirGameSpriteData[SpIndex].Width)  / 2;        //X位置
            SpData.PosY     = (240 - AirGameSpriteData[SpIndex].Height) / 2;        //Y位置
            SpData.PosZ     = 10;                                               //優先順位
            SpData.ScaleX   = SCALE10;                                          //スケールX
            SpData.ScaleY   = SCALE10;                                          //スケールY
            SpData.Rotate   = ROTATE000;                                        //回転角
            SpData.Reverse  = NOREVERS;                                         //反転コード
            DrawSprite( &SpData );                                              //スプライト描画

            //info
            FntPrint("SNO=%d/%d\n", SpIndex,SpEntryNum-1 );
            FntPrint("OfX=%d\n",    AirGameSpriteData[SpIndex].OffSetX );       //TIMの中のスプライト左上開始X位置
            FntPrint("OfY=%d\n",    AirGameSpriteData[SpIndex].OffSetY );       //TIMの中のスプライト左上開始Y位置
            FntPrint("W__=%d\n",    AirGameSpriteData[SpIndex].Width   );       //TIMの中のテクスチャの幅
            FntPrint("H__=%d\n",    AirGameSpriteData[SpIndex].Height  );       //TIMの中のテクスチャの高さ
            FntPrint("PNO=%d\n",    AirGameSpriteData[SpIndex].PaletteNo );     //TIMの中のテクスチャパレット番号
            FntPrint("CNT=%d\n",    ++Counter );

            break;
        //----------------------------------------------------------------終了
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
static int DebugEventSpriteTask(TASK* ip_task)
{
    static int SpIndex;
    static int SpEntryNum;
    static int Counter;
    static int FlushFlag;

    SPRITE_DATA SpData;


    switch(ip_task->mode)
    {
        //----------------------------------------------------------------初期化
        case TASK_MODE_INIT:
            //----
            ip_task->mode = TASK_MODE_MAIN;

            //----texture read sram -> vram
            if((file_read(AirEventTextureFile[0].fn,LoadAddress)) == -1)
            {//read error
                return FALSE;
            }

            //----texture init
            TexInit( AIR_EVENT_TIM_NUM, &AirEventTextureImage[AIR_EVENT_TIM_POS] );
            TimImgData = AirEventTextureImage;

            //----ゲーム用スプライト登録
            EntrySprite( AirEventSpriteData );

            //----
            SpIndex     = 0;
            SpEntryNum  = GetEntrySpriteNum();
            Counter     = 0;

            // フェードInします
            GameMgr.FadeFlag = FadeIn;

            break;
        //----------------------------------------------------------------メイン
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
            SpData.PosX     = (320 - AirEventSpriteData[SpIndex].Width)  / 2;       //X位置
            SpData.PosY     = (240 - AirEventSpriteData[SpIndex].Height) / 2;       //Y位置
            SpData.PosZ     = 10;                                               //優先順位
            SpData.ScaleX   = SCALE10;                                          //スケールX
            SpData.ScaleY   = SCALE10;                                          //スケールY
            SpData.Rotate   = ROTATE000;                                        //回転角
            SpData.Reverse  = NOREVERS;                                         //反転コード
            DrawSprite( &SpData );                                              //スプライト描画

            //info
            FntPrint("SNO=%d/%d\n", SpIndex,SpEntryNum-1 );
            FntPrint("OfX=%d\n",    AirEventSpriteData[SpIndex].OffSetX );      //TIMの中のスプライト左上開始X位置
            FntPrint("OfY=%d\n",    AirEventSpriteData[SpIndex].OffSetY );      //TIMの中のスプライト左上開始Y位置
            FntPrint("W__=%d\n",    AirEventSpriteData[SpIndex].Width   );      //TIMの中のテクスチャの幅
            FntPrint("H__=%d\n",    AirEventSpriteData[SpIndex].Height  );      //TIMの中のテクスチャの高さ
            FntPrint("PNO=%d\n",    AirEventSpriteData[SpIndex].PaletteNo );        //TIMの中のテクスチャパレット番号
            FntPrint("CNT=%d\n",    ++Counter );

            break;
        //----------------------------------------------------------------終了
        case TASK_MODE_EXIT:
            break;
        default:
            break;
    }
}

#endif

//-----------------------------------------------------------------------------
// end of AIR.C
//-----------------------------------------------------------------------------
omoisan 4年前