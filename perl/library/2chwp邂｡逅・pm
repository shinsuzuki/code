#-------------------------------------------------------------------------------
# nichanwp_manager.pm
#-------------------------------------------------------------------------------

#!/opt/local/bin/perl

#必須です
use strict;
use warnings;
use threads;
use threads::shared;
use File::Basename;
use File::Copy;
use File::Path;
use File::Spec;
use Time::HiRes;
use Readonly;
use Encode;

#文字コード
use utf8;
binmode STDIN, ":utf8";
binmode STDOUT, ":utf8";

require 'mylib.pm';
require 'nichanlib.pm';
require 'wplib.pm';

#-------------------------------------------------------------------------------
#  機能  
#      :2chのスレッドをwordpressへ登録する処理を管理する
#  入力
#      :カテゴリリンクファイル
#      :記事リンクディレクトリ
#      :記事内容ディレクトリ
#      :記事内容変換ディレクトリ
#      :記事内容カラー変換ディレクトリ
#      :対象とする記事数
#      :
#-------------------------------------------------------------------------------
#  ■アップロード処理                                                                                                                                             
#                                                                                                                                                          
#  取得したファイルから、管理用ファイルを作成。                                                                                                                  
#  
#  管理ID[カテゴリ_スレID]、スレッド名、ポストID、バイト数、ファイルパス、更新フラグ、スレッド数、データ落ちフラグ
#  
#  ファイルから、管理ID、スレッド名、行数を取得、管理用ファイルにデータの有無をチェック。                                                                                
#  管理用ファイルにデータがある場合は、バイト数が大きければ、バイト数数=最新のバイト数、更新フラグ=1、として更新する。 バイト数が小さければ更新しない（更新フラグが立っている場合は更新する）。            
#  管理用ファイルにデータがない場合は、管理ID（カテゴリ_スレID）、スレッド名、ポストID=-1、バイト数=最新のバイト数、更新フラグ=1を登録する。 とする。                                    
#                                                                                                                                                          
#  新規登録／更新処理
#  ポストIDと更新フラグを見て、新規登録／更新処理を行う。
#                                                                                                                                                          
#  新規登録／更新が成功した場合、ポストIDを更新、更新フラグ=0とする。
#  新規登録／更新が失敗した場合、ポストID=-1、更新フラグ=1とする。 
#  
#  
#  ＊スレッドは2００以上のものを対象とする。
#  ＊スレッドのファイル毎回ダウンロードする。それが前回より行数が少ない場合はエラーだが、行数チェックによりアップされない。
#  ＊例外処理未実装
#  ＊データがない場合の処理未実装
#-------------------------------------------------------------------------------

#データファイルインデックス
Readonly my $DATA_INDEX_TITLE => 0;                    #記事タイトル
Readonly my $DATA_INDEX_COMMENT_COUNT => 1;            #コメント数
Readonly my $DATA_INDEX_CONTENTS => 2;             #記事内容


#管理データインデックス
Readonly my $MGR_INDEX_ID => 0;                        #管理ID[カテゴリ_スレID]
Readonly my $MGR_INDEX_THREAD_NAME => 1;           #スレッド名
Readonly my $MGR_INDEX_POST_ID => 2;               #ポストID
Readonly my $MGR_INDEX_FILE_PATH => 3;             #ファイルパス
Readonly my $MGR_INDEX_UPDATE_FLAG => 4;           #更新フラグ (未設定:-1, 設定:1)
Readonly my $MGR_INDEX_COMMENT_COUNT => 5;         #コメントカウント
Readonly my $MGR_INDEX_DATA_FROP_FLAG => 6;            #データ落ちフラグ

#管理ファイル
Readonly my $WP_MNG_FILE => "wp_mgr.txt";            
Readonly my $WP_MNG_FILE_BACK_DIR => "wp_mgr_back";          




#---------------------------------------- param
my($input_category_file, $thread_link_dir, $thread_contents_dir, $thread_contents_convert_dir, $thread_contents_convert_color_dir, $target_comment_count, $wait_time, $wait_time_for_wp, $filter_file) = @ARGV;


#フィルター単語を読み込む
my @filter_datas = mylib::read_file($filter_file, "utf8");


#
if(!mylib::check_exist_dir($WP_MNG_FILE_BACK_DIR)){
    mkdir($WP_MNG_FILE_BACK_DIR);
}else{
    if(mylib::check_exist_file($WP_MNG_FILE)){
        
        my ($sec, $min, $hour, $mday, $mon, $year, $wday, $yday, $isdst) = localtime(time);
        my $date = sprintf("%04d%02d%02d_%02d%02d%02d", $year + 1900, $mon + 1, $mday, $hour, $min, $sec);
        my $back_file_name = $date."_".$WP_MNG_FILE;
        $back_file_name = mylib::combine_path($WP_MNG_FILE_BACK_DIR, $back_file_name);
        File::Copy::copy($WP_MNG_FILE, $back_file_name);
    }
}


#thread_linkd_dirが無い場合は作成
if(!mylib::check_exist_dir($thread_link_dir)){
    mkdir($thread_link_dir);
}else{
    mylib::remove_dir_force($thread_link_dir);
    mkdir($thread_link_dir);
}

#$thread_contents_dirが無い場合は作成
if(!mylib::check_exist_dir($thread_contents_dir)){
    mkdir($thread_contents_dir);
}else{
    mylib::remove_dir_force($thread_contents_dir);
    mkdir($thread_contents_dir);
}

#$thread_contents_convert_dirが無い場合は作成
if(!mylib::check_exist_dir($thread_contents_convert_dir)){
    mkdir($thread_contents_convert_dir);
}else{
    mylib::remove_dir_force($thread_contents_convert_dir);
    mkdir($thread_contents_convert_dir);
}

#$thread_contents_convert_color_dirが無い場合は作成
if(!mylib::check_exist_dir($thread_contents_convert_color_dir)){
    mkdir($thread_contents_convert_color_dir);
}else{
    mylib::remove_dir_force($thread_contents_convert_color_dir);
    mkdir($thread_contents_convert_color_dir);
}



#wordpress 基本情報
my $user = 'admin';
my $password = 'xxxxxxxxxxxxxxxxx';
my $endpoint = 'http://xxxxxxxx.sakura.ne.jp/wordpress/xmlrpc.php';
my $blogid = 1;




#---------------------------------------- カテゴリリンクの一覧を読み込み
print("================================================================================\n");
print("|  カテゴリリンクの一覧を読み込み:$input_category_file\n");
print("================================================================================\n");
my @tmp_category_lines = mylib::read_file($input_category_file, "utf8");
my @category_lines = ();

foreach(@tmp_category_lines){
    if($_ =~ /^#/){
        #これは対象外
    }else{
        push(@category_lines, $_);
    }
}

print(join("\n",@category_lines));


#---------------------------------------- 管理ファイルがある場合、スレッド名、スレッドカウントを取得
print("================================================================================\n");
print("|  管理ファイルがある場合、スレッド名、スレッドカウントを取得\n");
print("================================================================================\n");
my %wp_thread_comment_count_hash = (); #キーはスレッド名
my %wp_id_comment_count_hash = ();     #キーはID

if(mylib::check_exist_file($WP_MNG_FILE)){
    my @mngwp_lines = mylib::read_file($WP_MNG_FILE, 'utf8');
    
    foreach (@mngwp_lines){
        if($_ ne ""){
            my @datas = split(/\t/, $_);
            my $id = $datas[$MGR_INDEX_ID];
            #print("$id\n");
            my $tn = $datas[$MGR_INDEX_THREAD_NAME];
            #print("$tn\n");
            my $comment_count = $datas[$MGR_INDEX_COMMENT_COUNT];
            #print("$comment_count\n");
            $wp_thread_comment_count_hash{$tn} = $comment_count;
            $wp_id_comment_count_hash{$id} = $comment_count;
        }
    }
}


#---------------------------------------- カテゴリ毎に記事一覧のリンクを取得、ファイルに保存する、この一覧をダウンロードします
print("================================================================================\n");
print("|  カテゴリ毎に記事一覧のリンクを取得、ファイルに保存する　(フィルタリング後、この一覧をダウンロードに使用)\n");
print("================================================================================\n");
foreach my $cl (@category_lines){
    if($cl ne "" ){
        my @div_tab = split(/\t/, $cl);
        my @div_slash = split('/', $div_tab[0]);
        my $category = $div_slash[-1];
        my $url = $div_tab[0]."subback.html";
        my $save_file_path = mylib::combine_path($thread_link_dir, $category.".txt");
        nichanlib::get_2ch_thread_link_for_category($url, \%wp_thread_comment_count_hash, $target_comment_count,'tmp_get_2ch_thread_link_for_category.txt', $save_file_path, \@filter_datas);
        print($url." => ".$save_file_path."\n");
        sleep($wait_time);
    }   
}


#---------------------------------------- 記事一覧リンク毎に記事内容を取得、ファイルに保存
print("================================================================================\n");
print("|  記事一覧リンク毎に記事内容を取得、ファイルに保存\n");
print("================================================================================\n");
my @link_files = mylib::get_files_top_dir($thread_link_dir, '*.txt');

foreach my $lf (@link_files){
    my @div_slash = split(/\//, $lf);
    my @div_dot = split(/\./, $div_slash[1]);
    my $hozon_dir = mylib::combine_path($thread_contents_dir, $div_dot[0]);

    #print("<$lf>\n");
    #print("<$thread_contents_dir>\n");
    #print("<$div_dot[0]>\n");
    #print("[$hozon_dir]\n");
    #next;

    #カテゴリ毎にディレクトリを作成
    if(!mylib::check_exist_dir($hozon_dir)){
        eval{
            mkpath( $hozon_dir );
        };
        
        if( $@ ){
            die "$hozon_dir を作成できません。$@";
        }
    }
    
    #記事リンクの内容をファイルに保存
    nichanlib::get_2ch_thread_contents($lf, $hozon_dir, $wait_time);
}


#---------------------------------------- 必要のないリンクをテキストへ変換
print("================================================================================\n");
print("|  記事内容の必要のないリンクをテキストへ変換\n");
print("================================================================================\n");
nichanlib::convert_entry_text_from_thread_contents($thread_contents_dir, $thread_contents_convert_dir);


#---------------------------------------- 記事内容にコメントにカラーを設定、これをアップします
print("================================================================================\n");
print("|  記事内容にコメントにカラーを設定\n");
print("================================================================================\n");
nichanlib::convert_entry_text_from_thread_contents_color($thread_contents_convert_dir, $thread_contents_convert_color_dir);



#---------------------------------------- wordpress有効チェック
print("================================================================================\n");
print("|  wordpress有効チェック\n");
print("================================================================================\n");
my $result_ui = wplib::get_user_info($user, $password, $endpoint);

#取得できない場合は、メンテナンス状態と見なし、終了します
if(!defined($result_ui)){
    print("==> wordpressが有効ではないので終了します\n");
    exit();   
}


#---------------------------------------- ファイルリストを抽出
print("================================================================================\n");
print("|  ファイルリストを抽出\n");
print("================================================================================\n");
my @upload_kouho_files = mylib::get_files_all_dir($thread_contents_convert_color_dir ,"*.txt");


#---------------------------------------- wp管理用ファイルを読み込み
print("================================================================================\n");
print("|  wp管理用ファイルを読み込み\n");
print("================================================================================\n");
my %mng_hash = ();

if(mylib::check_exist_file($WP_MNG_FILE)){
    my @mngwp_lines = mylib::read_file($WP_MNG_FILE, 'utf8');
    
    foreach (@mngwp_lines){
        if($_ ne ""){
            my @datas = split(/\t/, $_);
            my $id = $datas[$MGR_INDEX_ID];
            my $data = join("\t", @datas);
            print("$id\n");
            $mng_hash{$id} = $data;
            #print($data."\n");
        }
    }
}


#---------------------------------------- 取得したファイルとをwp管理データを比較
print("================================================================================\n");
print("|  取得したファイルとをwp管理データを比較、更新ファイルを作成\n");
print("================================================================================\n");
my %tmp_entry_data_hash = ();
foreach my $upk_file (@upload_kouho_files){
    
    my @suffix_list = qw /.txt/;
    my ($category_id, $path, $suffix) = fileparse($upk_file, @suffix_list);
    my @tmp_lines = mylib::read_file($upk_file,'utf8');

    if(exists($mng_hash{$category_id})){
        #更新:そのまま、更新処理の２択
        my $data = $mng_hash{$category_id};
        my @datas = split("\t", $data);
        $datas[$MGR_INDEX_UPDATE_FLAG] = -1;
        $datas[$MGR_INDEX_COMMENT_COUNT] = $tmp_lines[$DATA_INDEX_COMMENT_COUNT];
        my $entry = join("\t", @datas);;
        $tmp_entry_data_hash{$category_id} = $entry;
        
    }else{
        #新規とデータ落ちの場合
        my $title = $tmp_lines[$DATA_INDEX_TITLE];
        my $comment_count = $tmp_lines[$DATA_INDEX_COMMENT_COUNT];
        
        # 管理ID[カテゴリ_スレID]、スレッド名、 ポストID、ファイルパス、 更新フラグ、 コメント数、 データ落ちフラグ
        print("$upk_file\n");
        my $entry = "$category_id\t${title}\t-1\t${upk_file}\t-1\t${comment_count}\t0";
        $tmp_entry_data_hash{$category_id} = $entry;
    }
}

#管理ファイルのデータをコピー
#print("**********\n");
my %entry_data_hash = %mng_hash;

foreach my $key (keys(%tmp_entry_data_hash)){
    if(exists($entry_data_hash{$key})){
        #更新
        #print("更新:".$key."\n");
        $entry_data_hash{$key} = $tmp_entry_data_hash{$key};
    }else{
        #追加
        #print("追加:".$key."\n");
        $entry_data_hash{$key} = $tmp_entry_data_hash{$key};
    }
}

my @entry_datas = values(%entry_data_hash);

my @sorted_entry_datas = sort{
    my @datas_a = split("\t",$a);
    my @datas_b = split("\t",$b);
    $datas_a[4] <=> $datas_b[4]; } @entry_datas;

mylib::write_file($WP_MNG_FILE, \@sorted_entry_datas, 'utf8');


#---------------------------------------- wp管理データにより、wpの新規登録/更新処理を行う
print("================================================================================\n");
print("|  wp管理データにより、wpの新規登録/更新処理\n");
print("================================================================================\n");
my %mngwp_hash = ();
my @mngwp_lines = mylib::read_file($WP_MNG_FILE, 'utf8');

#管理データ読み込み、ハッシュへ
foreach (@mngwp_lines){
    my @datas = split(/\t/, $_);
    my $id = $datas[0];
    $mngwp_hash{$id} = join("\t", @datas);
}

#新規登録/更新登録
foreach my $key (keys(%mngwp_hash)){
    my $wait_flag = 1;
    print($key."\n");
    my $line = $mngwp_hash{$key};
    my @datas = split(/\t/,$line);
    
    my $post_id = $datas[$MGR_INDEX_POST_ID];
    $post_id += 0;
    
    my $entry_flag = $datas[$MGR_INDEX_UPDATE_FLAG];
    $entry_flag += 0;
    
    my $file = $datas[$MGR_INDEX_FILE_PATH];
    
    #更新対象の場合
    if($entry_flag == -1){
        if($post_id == -1){
            print(" => new_entry => $file\n");
            my %entry_hash = create_entry_data($file);
            my $categories_ref = $entry_hash{"entry_categories_ref"}; #カテゴリ
            my $keyword = $entry_hash{"keyword"};                     #キーワード
            my $title = $entry_hash{"title"};                         #タイトル
            $title = encode('utf-8', $title );
            my $text_body = $entry_hash{"text_body"};                 #内容_body
            $text_body = encode('utf-8', $text_body);
            my $text_more = $entry_hash{"text_more"};                 #内容_more
            $text_more = encode('utf-8', $text_more); 
            my $excerpt = "";                                           #概要
            
            #新規登録
            my $result =undef;
            
            while(1){
                my $checked = 0;

                eval{
                    $result = wplib::entry_thread($user, $password, $endpoint, $blogid, $title, $text_body, $text_more, $excerpt, $keyword, $categories_ref);
                };
                
                if($@){
                    $checked = 1;
                }else{
                    last;
                }
                
                if($checked == 1){
                    print("========================================> false sleep 600(sec)\n");
                    sleep(600)
                }
            }
            
            
            #結果
            if(!defined($result)){
                #エラー
                print(" => new_entry_false\n");
                my $tmp_mngwp = $mngwp_hash{$key};
                my @tmp_mngwp_datas = split("\t", $tmp_mngwp);
                #$tmp_mngwp_datas[$MGR_INDEX_POST_ID] = -1;                #ポストIDは -1 のまま
                #$tmp_mngwp_datas[$MGR_INDEX_UPDATE_FLAG] = -1;            #更新フラグは -1 のまま
                $tmp_mngwp_datas[$DATA_INDEX_COMMENT_COUNT] = -1;       #コメント数は -1 を設定
                $tmp_mngwp = join('\t', @tmp_mngwp_datas);
                $mngwp_hash{$key} = $tmp_mngwp;
            }else{
                #成功
                my $new_post_id = $result;
                print(" => new_entry_success => postid:$new_post_id\n");
                my $tmp_mngwp = $mngwp_hash{$key};
                my @tmp_mngwp_datas = split("\t", $tmp_mngwp);
                $tmp_mngwp_datas[$MGR_INDEX_POST_ID] = $new_post_id;  #ポストIDを設定
                $tmp_mngwp_datas[$MGR_INDEX_UPDATE_FLAG] = 1;           #更新フラグ1を設定
                $tmp_mngwp = join("\t", @tmp_mngwp_datas);
                $mngwp_hash{$key} = $tmp_mngwp;
            }
        }else{
            #update
            print(" => update_entry => $file\n");
            my %entry_hash = create_entry_data($file);
            my $categories_ref = $entry_hash{"entry_categories_ref"}; #カテゴリ
            my $keyword = $entry_hash{"keyword"};                     #キーワード
            my $title = $entry_hash{"title"};                         #タイトル
            $title = encode('utf-8', $title);
            my $text_body = $entry_hash{"text_body"};                 #内容_body
            $text_body = encode('utf-8', $text_body);
            my $text_more = $entry_hash{"text_more"};                 #内容_more
            $text_more = encode('utf-8', $text_more);
            my $excerpt = "";                                           #概要
            
            #更新登録
            my $result_update = undef;
            while(1){
                my $checked = 0;
                eval{
                    $result_update = wplib::update_thread($user, $password, $endpoint, $post_id, $title, $text_body, $text_more, $excerpt, $keyword, $categories_ref); 
                };
                
                if($@){
                    $checked = 1;
                }else{
                    last;
                }
                
                if($checked == 1){
                    print("========================================> false sleep 600(sec)\n");
                    sleep(600)
                }
            }
            
            #結果
            if(!defined($result_update )){
                #エラー
                print(" => update_entry_false\n");
                my $tmp_mngwp = $mngwp_hash{$key};
                my @tmp_mngwp_datas = split("\t", $tmp_mngwp);
                $tmp_mngwp_datas[$MGR_INDEX_UPDATE_FLAG] = -1;          #更新フラグはエラーのため -1 を設定
                $tmp_mngwp_datas[$DATA_INDEX_COMMENT_COUNT] = -1;       #コメント数は -1 を設定
                $tmp_mngwp = join('\t', @tmp_mngwp_datas);
                $mngwp_hash{$key} = $tmp_mngwp;

            }else{
                #成功
                print(" => update_entry_success\n");
                my $tmp_mngwp = $mngwp_hash{$key};
                my @tmp_mngwp_datas = split(/\t/, $tmp_mngwp);
                $tmp_mngwp_datas[$MGR_INDEX_UPDATE_FLAG] = 1;           #更新フラグは 1 を設定
                $tmp_mngwp = join("\t", @tmp_mngwp_datas);
                $mngwp_hash{$key} = $tmp_mngwp;
            }
        }
    }else{
        $wait_flag = 0;
        print(" => no work\n");    
    }
    
    if($wait_flag == 1){
        sleep($wait_time_for_wp);
    }
}


#wpへの新規登録/更新登録の結果をファイルに保存
print("================================================================================\n");
print("|  wpへの新規登録/更新登録の結果をファイルに保存\n");
print("================================================================================\n");
my @output_mngwp_datas = ();
foreach my $key (keys(%mngwp_hash)){
    my $line = $mngwp_hash{$key};
    #print("$line\n");
    push(@output_mngwp_datas, $line);
}

mylib::write_file($WP_MNG_FILE, \@output_mngwp_datas, 'utf8');

exit();







#-------------------------------------------------------------------------------
#  job
#      :ｔ登録する記事ファイル
#  in
#      :登録ファイル
#  out
#      :登録情報のハッシュ
#-------------------------------------------------------------------------------
sub create_entry_data{
    my($file) = @_;

    my %tmp_hash = ();
    my @lines = mylib::read_file($file, "utf8");
    
    #カテゴリ
    my @suffix_list = qw /.txt/;
    my ($filename, $path, $suffix) = fileparse($file, @suffix_list);
    my @div_undes_datas = split(/_/, $filename);
    my $category = $div_undes_datas[0];
    my @entry_categories = ();
    push(@entry_categories, $category);
    $tmp_hash{"entry_categories_ref"} = \@entry_categories;
    
    #キーワード
    $tmp_hash{"keyword"} = $category;
    
    
    #タイトル
    my $entry_title = $lines[$DATA_INDEX_TITLE];
    $entry_title = delete_thread_count($entry_title);
    $tmp_hash{"title"} = $entry_title;
    
    #内容
    my $contents = $lines[$DATA_INDEX_CONTENTS];
    my %div_contents_hash = div_enrty_data($contents);
    $tmp_hash{"text_body"} = $div_contents_hash{"text_body"};
    $tmp_hash{"text_more"} = $div_contents_hash{"text_more"};

    return %tmp_hash;
}


#-------------------------------------------------------------------------------
#  job
#      :記事内容テキストを分割します
#  in
#      :記事内容テキスト
#  out
#      :分割した記事テキストハッシュ
#-------------------------------------------------------------------------------
sub div_enrty_data{
    my($text) = @_;
    my %tmp_hash = ();
    #my $check_str = '</dt>';
    my $check_str = '<dt>8';
    
    my $pos_index = index($text, $check_str);
    #$pos_index += length($check_str);
    my $text_body = substr($text, 0, $pos_index);
    
    my $len = length($text);
    $len -= $pos_index;
    my $text_more = substr($text, $pos_index, $len);

    #print("$pos_index\n");
    #print("$text_body\n");
    #print("$text_more\n");
    
    $tmp_hash{"text_body"} = $text_body;
    $tmp_hash{"text_more"} = $text_more;
    
    return %tmp_hash;
}


#-------------------------------------------------------------------------------
#  job
#      :記事のタイトルから記事数を削除します
#  in
#      :記事タイトル
#  out
#      :記事のタイトルから記事数を削除したテキスト
#-------------------------------------------------------------------------------
sub delete_thread_count{
    my ($title) = @_;
    
    my  $title_only = $title;
    $title_only =~ s/\s\(\d+\)$//;
    
    return $title_only;
}