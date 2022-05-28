//-----------------------------------------------------------------------------
// TASKMGR.H
//-----------------------------------------------------------------------------
#ifndef __TASKMGR_H__
#define __TASKMGR_H__
//-----------------------------------------------------------------------------
//  include
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  define
//-----------------------------------------------------------------------------
//----------------------------------------ﾀｽｸ登録最大数
#define MAX_TASK_NUM 64

//----------------------------------------ﾀｽｸ属性
enum
{
    ATTR_FREE = 0, //ﾌﾘｰ：初期化用
    ATTR_SYSTEM,   //ｼｽﾃﾑ
    ATTR_USER,     //ﾕｰｻﾞｰ
};

//----------------------------------------ﾀｽｸﾓｰﾄﾞ
enum
{
    TASK_MODE_INIT = 0, //初期化処理
    TASK_MODE_MAIN,     //ﾒｲﾝ処理
    TASK_MODE_EXIT,     //終了処理
};

//----------------------------------------ﾀｽｸ状態
enum
{
    TASK_FREE = 0,   //ﾌﾘｰ：初期化用
    TASK_RUN,        //実行中
    TASK_READY,      //実行待ち
    TASK_WAIT,       //待ち
    TASK_KILL,       //削除
    TASK_NEW_ENTRY,  //新規に登録
    TASK_KILL_ENTRY, //自分自身を削除する
};

//---------------------------------------- ﾀｽｸ優先
#define PRIO_FREE 0
#define PRIO_FIRST 1
#define PRIO_LAST 10000

//ｼｽﾃﾑﾀｽｸで[0-999]、[9001-10000]を予約する
//ﾕｰｻﾞｰﾀｽｸは、[1000-9000]の間の値を優先順位として指定して下さい
#define PRIO_USER_FIRST PRIO_FIRST + 999
#define PRIO_USER_LAST PRIO_LAST - 999

//---------------------------------------- ﾀｽｸID
#define ID_FREE 0
#define ID_FIRST 1
#define ID_LAST 10000

//---------------------------------------- ﾀｽｸｳｪｲﾄﾀｲﾑ
#define WTIME_ZERO 0

//ｼｽﾃﾑﾀｽｸで[1-999]、[9001-10000]を予約する
//ﾕｰｻﾞｰﾀｽｸは、[1000-9000]の間の値をIDとして指定して下さい
#define ID_USER_FIRST ID_FIRST + 999
#define ID_USER_LAST ID_LAST - 999

//----------------------------------------  ﾀｽｸﾕｰｻﾞｰﾜｰｸｻｲｽﾞ
#define USER_WORK_SIZE 32

//-----------------------------------------------------------------------------
//  typdef
//-----------------------------------------------------------------------------
//---------------------------------------- TASK構造体
typedef struct _TASK
{
    int (*func)(struct _TASK *); //実行する関数ｱﾄﾞﾚｽ
    struct _TASK *prev;          //事前に実行されたﾀｽｸのｱﾄﾞﾚｽ
    struct _TASK *next;          //次に実行予定のﾀｽｸのｱﾄﾞﾚｽ
    int mode;                    //ﾀｽｸﾓｰﾄﾞ
    int attribute;               //ﾀｽｸの属性
    int status;                  //ﾀｽｸの状態
    int id;                      //ﾀｽｸ認識のＩＤ
    int priority;                //ﾀｽｸのの優先順番号
    int wait_time;               //ｳｪｲﾄﾀｲﾑ（起動待ち）
    void *buf;                   //使用するﾒﾓﾘへのｱﾄﾞﾚｽ（拡張ﾃﾞｰﾀ）
    int user[USER_WORK_SIZE];    //ﾕｰｻﾞｰﾜｰｸ
    char *name;                  //ﾀｽｸﾈｰﾑ
} TASK;

//-----------------------------------------------------------------------------
//  prototype & extern
//-----------------------------------------------------------------------------
//---------------------------------------- Local Funcs
static int _CheckTaskEmpty(void);
static int _CheckTaskFull(void);
static TASK *_AllocFreeTask(void);
static void _InsertFreeTask(TASK *);
static TASK *_InsertTask(TASK *);
static void _DeleteTask(TASK *);

//---------------------------------------- Global Funcs
extern void InitTaskMgr(void);
extern TASK *CreateTask(TASK *);
extern TASK *RemoveTask(int);
extern int ExitTask(int);
extern int ChangeTaskMode(int, int);
extern TASK *SearchTask(int);
extern int WakeupTask(int);
extern int SleepTask(int);
extern int ExecuteTask(void);

//-----------------------------------------------------------------------------
// end of TASKMGR.H
//-----------------------------------------------------------------------------
#endif