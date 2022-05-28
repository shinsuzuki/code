#-------------------------------------------------------------------------------
# mylib.pm
#-------------------------------------------------------------------------------
package mylib;


#-------------------------------------------------------------------------------
#【注意】
# 配列の引き渡しはリファレンスで行う
#-------------------------------------------------------------------------------
use utf8;
use Config::Simple;
use Data::UUID;
use Encode;
use File::Basename;
use File::Compare;
use File::Copy;
use File::Find::Rule;
use File::Path;
use File::Spec;
use File::Remove;
use List::Util;
use Sys::Hostname;
use Term::ANSIColor;
use Time::HiRes;
use Time::Piece;


################################################################################
# job
#      :インクルードディレクトリを表示
# in
#      :無し
# out
#      :無し
# exp
#      :mylib::print_include_dir();
###############################################################################
sub print_include_dir{
    print("#include dir:\n"); 
    foreach(&get_include_dir()){
        print($_."\n");    
    }
}


################################################################################
# job
#      :インクルードディレクトリを表示
# in
#      :無し
# out
#      :インクルードディレクトリ
# exp
#      :mylib::get_include_dir();
###############################################################################
sub get_include_dir{
    return @INC;
}


################################################################################
# job
#      :perlバージョンをを表示
# in
#      :無し
# out
#      :無し
# exp
#      :mylib::print_perl_version();
###############################################################################
sub print_perl_version{
    print("#perl verion:".&get_perl_version()."\n");    
}


################################################################################
# job
#      :perlバージョンを取得
# in
#      :無し
# out
#      :perlバージョン
# exp
#      :mylib::get_perl_version();
###############################################################################
sub get_perl_version{
    return $]; 
}


################################################################################
# job
#      :pidを表示
# in
#      :無し
# out
#      :無し
# exp
#      :mylib::print_pid();
###############################################################################
sub print_process_id{
    print("#pid:".&get_process_id()."\n");
}


################################################################################
# job
#      :script fileを表示
# in
#      :無し
# out
#      :無し
# exp
#      :mylib::print_script_file();
###############################################################################
sub print_script_file{
    print("#script file:".&get_script_file()."\n");
}


################################################################################
# job
#      :script file名を取得
# in
#      :無し
# out
#      :script_file名
# exp
#      :mylib::get_script_file();
###############################################################################
sub get_script_file{
    return $0;
}


################################################################################
# job
#      :perlのパスを表示
# in
#      :無し
# out
#      :無し
# exp
#      :mylib::print_perl_path();
###############################################################################
sub print_perl_path{
    my $cmd_str = 'which perl';
    my $result_qx = qx/$cmd_str/;
    print("#perl path:".$result_qx);
}

################################################################################
# job
#      :perlの環境情報を表示
# in
#      :無し
# out
#      :無し
# exp
#      :mylib::print_perl_info();
###############################################################################
sub print_perl_info{

    &print_perl_path();
    &print_perl_version();
    &print_include_dir();
    &print_script_file();
    &print_pid();
}


################################################################################
# job
#      :OS名を取得
# in
#      :なし
# out
#      :OS名
# exp
#      :my $os = mylib::get_os_name();
################################################################################
sub get_os_name{
    return $^O;    
}


################################################################################
# job
#      :プロセスIDを取得
# in
#      :なし
# out
#      :プロセスID
# exp
#      :my $os = mylib::get_process_id();
################################################################################
sub get_process_id{
    return $$;
}


################################################################################
# job
#      :ホスト名を取得
# in
#      :なし
# out
#      :ホスト名
# exp
#      :my $os = mylib::get_hostname();
################################################################################
sub get_hostname{
    return hostname();
}


################################################################################
# job
#      :ホスト名を取得
# in
#      :なし
# out
#      :ホスト名
# exp
#      :my $os = mylib::get_loginname();
################################################################################
sub get_loginname{
    return getlogin();
}


#-------------------------------------------------------------------------------
# job
#       :ファイル読み込み
# in
#      :読み込むファイル 
#      :エンコード文字列 (utf8,encoding(euc-jp),encoding(cp932))
# out
#      :行配列
# ex
#      :my @list = mylib::read_file("file.txt", "utf8");
#      :my @list = mylib::read_file("file.txt", "encoding(euc-jp)");
#      :my @list = mylib::read_file("file.txt", "encoding(cp932)");
#-------------------------------------------------------------------------------
sub read_file{
    my($file, $enc) = @_;
    
    if (!open(FH, "<:$enc", $file)){
        die("error :$!");
    }
    
    my @ret_list = ();
    
    #動かないときがあるので下記に修正
    #my @list = <FH>;
    #foreach my $data_line (@list){
    #  chomp($data_line);
    #  push(@ret_list, $data_line);
    #}
    
    while(<FH>){
        #print $_;
        my $line = $_;
        chomp($line);
        push(@ret_list, $line);
    }
    
    close(FH);

    return @ret_list;
}

#-------------------------------------------------------------------------------
# job
#       :ファイル 書き込み
# in
#      :保存するファイル
#      :配列のリファレンス
#      :エンコード文字列　(utf8,encoding(euc-jp),encoding(cp932))
# out
#      :なし
# ex
#      :mylib::write_file("wr_utf8.txt", \@list, "utf8");
#      :mylib::write_file("wr_euc.txt", \@list, "encoding(euc-jp)");
#      :mylib::write_file("wr_sjis.txt", \@list, "encoding(cp932)");
#-------------------------------------------------------------------------------
sub write_file{
    
    my ($file, $list_ref, $enc) = @_;

    if (!open(WFH, ">:$enc", "$file")){
        die("error :$!");
    }

    foreach my $line (@{$list_ref}){
        print WFH "$line\n"
    }

    close(WFH);
}


#-------------------------------------------------------------------------------
# job
#       :ファイル一覧を取得（再帰）
# in
#      :ディレクトリ
#      :対象ファイル種別 (*.ext)
# out
#      :ファイル一覧の配列
# ex
#      ::my @files = mylib::get_files_all_dir('./', '*.pl');
#-------------------------------------------------------------------------------
sub get_files_all_dir{
    
    my ($dir, $ext) = @_;
    
    my $rule = File::Find::Rule->new;
    $rule->file;
    $rule->name($ext);
    my @files  = $rule->in($dir);
    
    return @files;
}


#-------------------------------------------------------------------------------
# job
#       :ファイル一覧を取得
# in
#      :ディレクトリ
#       :対象ファイル種別 (*.ext)
# out
#      :file_list
# exp
#      :my @files = mylib::get_files_top_dir('.', '*.txt');
#-------------------------------------------------------------------------------
sub get_files_top_dir{

    my ($dir, $file) = @_;

    my $search = File::Spec->catfile( $dir, $file);

    return glob($search);
}


#-------------------------------------------------------------------------------
# job
#       :ディレクトリ直下のファイルを結合したファイルを作成
# in
#      :対象ディレクトリ
#       :対象ファイル種別 (*.ext)
# out
#      :結合したファイル
# exp
#      :my @files = mylib::create_cat_file_for_dir('.', '*.txt',"test_cat.txt", "utf8");
#-------------------------------------------------------------------------------
sub create_cat_file_for_dir{

    my ($dir, $file, $out_file, $enc) = @_;

    if (!open(WFH, ">:$enc", "$out_file")){
        die("error :$!");
    }

    my @files = &get_files_top_dir($dir, $file);
    foreach my $file (@files){
        my @lines = &read_file($file, "utf8");
        foreach my $line (@lines){
            print WFH "$line\n"
        }
    }
    
    close(WFH);
}


#-------------------------------------------------------------------------------
# job
#       :配列のユニーク処理
# in
#      :配列のリファレンス
# out
#      :ユニーク配列
# exp
#       :my @l = (1,2,3,1,2);
#      :my @ul = mylib::uniq_for_array(\@l);
#-------------------------------------------------------------------------------
sub uniq_for_array{

    my ($list_ref) = @_;

    my %seen = (); 
    my @uniqs = grep { ! $seen{$_} ++ } @{$list_ref};

    return @uniqs;
}


#-------------------------------------------------------------------------------
# job
#       :ファイル行のユニーク処理
# in
#      :入力ファイル
# out
#      :結果ファイル
# exp
#      :mylib::uniq_for_file("test.txt", "test_uniq.txt");
#-------------------------------------------------------------------------------
sub uniq_for_file{
    
    my ($in_file, $uniq_file) = @ARGV;
    
    if (!open(FH, "<:utf8", $in_file)){
        die("error :$!");
    }

    my $count = 0;    
    my %uniq_hash = ();
    
    while(my $line = <FH>){
        $count++;
        print("$count"."\r");
        chomp($line);
        
        if(!exists($uniq_hash{$line})){
            $uniq_hash{$line} = 1;
        }
    }
    close(FH);
    
    my @out_list = keys(%uniq_hash);

    #同パッケージ内の関数を呼ぶときは&をつけます
    &write_file($uniq_file, \@out_list,"utf8");
    
}


#-------------------------------------------------------------------------------
# job
#       :配列に登録されているデータ数を取得
# in
#      :配列のリファレンス
# out
#      :配列に登録されているデータ数
# exp
#       :my @arr = (1,2,3);
#       :print(mylib::get_array_count(\@arr));
#-------------------------------------------------------------------------------
sub get_array_count{
    
    my ($array_ref) = @_;
    return $#{$array_ref} + 1;
}

#-------------------------------------------------------------------------------
# job
#       :配列にの最大インデックスを取得
# in
#      :配列のリファレンス
# out
#      :配列にの最大インデックス
# exp
#       :my @arr = (1,2,3);
#       :print(mylib::get_array_max_index(\@arr));
#-------------------------------------------------------------------------------
sub get_array_max_index{
    
    my ($array_ref) = @_;
    return $#{$array_ref};
}


#-------------------------------------------------------------------------------
# job
#       :ハッシュに登録されているデータ数を取得
# in
#      :ハッシュのリファレンス
# out
#      :ハッシュに登録されているデータ数
# exp
#       :my %h = ();
#        $h{"a"} = 1;
#        $h{"b"} = 2;
#        print(mylib::get_hash_count(\%h));
#-------------------------------------------------------------------------------
sub get_hash_count{
    
    my ($hash_ref) = @_;
    
    my $count = keys( %{$hash_ref} );
    
    return $count;
}


#-------------------------------------------------------------------------------
# job
#       :ハッシュに登録されているデータ数を取得
# in
#      :ハッシュのリファレンス
# out
#      :ハッシュに登録されているデータ数
# exp
#       :my %h = ();
#        $h{"a"} = 1;
#        $h{"b"} = 2;
#        print(mylib::get_hash_count(\%h));
#-------------------------------------------------------------------------------
sub get_hash_keys{
    
    my ($hash_ref) = @_;
    
    return sort(keys( %{$hash_ref}));
}

#-------------------------------------------------------------------------------
# job
#       :ハッシュに登録されているデータ数を取得
# in
#      :ハッシュのリファレンス
# out
#      :ハッシュに登録されているデータ数
# exp
#       :my %h = ();
#        $h{"a"} = 1;
#        $h{"b"} = 2;
#        print(mylib::get_hash_values(\%h));
#-------------------------------------------------------------------------------
sub get_hash_values{
    
    my ($hash_ref) = @_;
    
    return sort(values(%{$hash_ref}));
}


#-------------------------------------------------------------------------------
# job
#       :現在時刻を取得
# in
#      :無し
# out
#      :現在時刻文字列
# exp
#       :my $str = mylib::get_time_now(); #2011/08/25 16:32:48
#-------------------------------------------------------------------------------
sub get_time_now{

    my $t = Time::Piece::localtime();
    my $time_str = sprintf("%04d/%02d/%02d %02d:%02d:%02d",$t->year,$t->mon,$t->mday,$t->hour,$t->minute,$t->sec);
    
    return $time_str;
}


################################################################################
# job
#      :ハッシュを作成
# in
#      :単語リストのリファレンス
# out
#      :ハッシュ
# exp
#      :my @l  = ("1","2","3");
#      :my %h = mylib::create_hash_from_word_list(\@l);
###############################################################################
sub create_hash_from_word_list{
    
    my($array_ref) = @_;

    print("create_hash_from_word_list\n");

    for my $index (0..$#{$array_ref}){
        my $word = ${$array_ref}[$index];
        print($word);
        
        if($word ne ""){
            $word_hash{$word} = 1;
        }
    }
    
    return %word_hash;
}


################################################################################
# job
#      :ハッシュをキーと値を表示
# in
#      :ハッシュのリファレンス
# out
#      :無し
# exp
#      :my @l  = ("1","2","3");
#      :my %h = mylib::create_hash_from_word_list(\@l);
#      :mylib::print_hash(\%h);
###############################################################################
sub print_hash{

    my($hash_ref) = @_;
    
    while( ($name, $value) = each %{$hash_ref} ){
        print ("key:[$name]\tvalue:[$value]\n");
    }
}


################################################################################
# job
#      :分割対象とする配列を分割、そのリファレンス配列を返す
# in
#      :分割対象とする配列のリファレンス
#      :分割グループ数
# out
#      :配列を分割した配列のリファレンス配列
# exp
#      :分割
#      :my @datas = (0,1,2,3,4,5,6,7,8,9,10);
#      :my @div_datas = mylib::div_array_data(\@datas, 3);
#      :
#      :#参照
#      :for(my $i = 0; $i <= $#div_datas; $i++){
#      :   print("top:$i\n");
#      :   my $data_ref = $div_datas[$i];
#      :   my $array_data_index = $#{$data_ref};
#      :           
#      :   for(my $j = 0; $j <= $array_data_index; $j++){
#      :       print("  child:".$data_ref->[$j]."\n");
#      :   }
#      :}
#
###############################################################################
sub div_array_data{
    
    my($array_ref, $div_array_count) = @_;
    
    my $max_array_index = $#{$array_ref};
    my $max_array_length =  $max_array_index + 1;
    
    #print("max_array_index:$max_array_index\n");
    #print("max_array_length:$max_array_length\n");
    
    ##データ分割
    my $div_count = int($max_array_length / $div_array_count) + 1;
    
    
    my @div_data_matome_array = ();
    my @tmp_data_array = ();
    my $out_count = 0;
    
    for(my $i = 0; $i <= $max_array_index; $i++){
        $out_count++;
        push(@tmp_data_array, $array_ref->[$i]);
        
        if($out_count >= $div_count){
            my @tmps = @tmp_data_array;
            push(@div_data_matome_array, \@tmps);
            #print("data - $i\n");
            @tmp_data_array = ();
            $out_count = 0;
        }
    }
    
    if($#tmp_data_array > 0){
        my @tmps = @tmp_data_array;
        push(@div_data_matome_array, \@tmps);
    }
    
    return @div_data_matome_array;
}


################################################################################
# job
#      :テキストにcabochaを実行する
# in
#      :テキストファイル
# out
#      :cabocha結果ファイル
# exp
#      :mylib::txt_to_caboca_for_file("test.txt", "test.cba");
###############################################################################
sub txt_to_caboca_for_file{

    my($input_file, $output_file) = @_;
    
    my $command = "cabocha -f1 $input_file > $output_file";
    
    eval{ 
        my $ret = system $command;
    };
    
    if ($@) {
        print("cabocha処理例外発生：$input_file\n");
    }
}


################################################################################
# job
#      :ディレクトリ内のテキストにcabochaを実行する
# in
#      :入力テキストディレクトリ
#      :ファイルの拡張子
# out
#      :出力Cabochaディレクトリ
# exp
#      :mylib::txt_to_caboca_for_dir("./txt", "*.txt", "./cba");
###############################################################################
sub txt_to_caboca_for_dir{
    
    my($input_dir, $ext, $output_dir) = @_;

    #出力ディレクトリ作成
    if(-d $output_dir){
        rmtree($output_dir);
    }
    mkdir($output_dir);    
    
    #対象ファイル読み込み
    my @files = &get_files_all_dir($input_dir, $ext);
    my $progress=0;
    
    for(my $i=0;$i <= $#files ;$i++){
        #print($files[$i]."\n");
        $progress = (($i+1) * 100) / ($#files + 1);
        print sprintf(" %3.0f", $progress) . "% \r";
        
        #ファイル処理
        #print($files[$i]."\n");
        my $file_name = "$files[$i]" . ".cba";
        $file_name = basename($file_name);
        my $output_file = File::Spec->catfile($output_dir, $file_name);
        
        my $command = "cabocha -f1 $files[$i] > $output_file";
        
        eval{ 
            my $ret = system $command;
        };
        
        if ($@) {
            print("cabocha処理例外発生：$files[$i]\n");
        }
    }
}


################################################################################
# job
#      :GUIDによるファイル名を作成
# in
#      :ファイルの拡張子
# out
#      :GUIDのファイル名
# exp
#      :mylib::create_guid_file_name(".txt");
#      :（例）0DCBFC3E-FA2D-11E0-8C54-E9B9A237EDC3.txt
###############################################################################
sub create_guid_file_name{

    my($ext) = @_;
    
    my $file_name = Data::UUID->new->create_str.$ext;
    return $file_name;
}


################################################################################
# job
#      :GUIDによるファイル名を作成(接頭辞を設定します)
# in
#      :プレフィックス文字
#      :ファイルの拡張子
# out
#      :GUIDのファイル名
# exp
#      :mylib::create_guid_file_name_add_prefix("type_",".txt");
#      :（例）type_962039C4-FA2D-11E0-A6CF-F8B9A237EDC3.txt
###############################################################################
sub create_guid_file_name_add_prefix{

    my($prefix, $ext) = @_;
    
    my $file_name = $prefix.Data::UUID->new->create_str.$ext;
    return $file_name;
}


################################################################################
# job
#      :処理時間計測開始（処理時間計測終了とペアで使用）
# in
#      :なし
# out
#      :開始時間
# exp
#      :my $start_time = mylib::stop_watch_start();
#      :my $time = mylib::stop_watch_stop($start_time);
###############################################################################
sub stop_watch_start{
    return Time::HiRes::time;
}


################################################################################
# job
#      :処理時間計測終了（処理時間計測開始とペアで使用）
# in
#      :開始時間
# out
#      :開始から終了までの時間（秒）
# exp
#      :my $start_time = mylib::stop_watch_start();
#      :my $time = mylib::stop_watch_stop($start_time);
###############################################################################
sub stop_watch_stop{
    my ($start_time) = @_;
    return Time::HiRes::time - $start_time;
}


################################################################################
# job
#      :処理時間計測終了、表示
# in
#      :開始時間
# out
#      :なし
# exp
#      :my $start_time = mylib::stop_watch_start();
#      :mylib::stop_watch_stop_and_print($start_time);
###############################################################################
sub stop_watch_stop_and_print{
    my ($start_time) = @_;
    printf("time:"."%0.3f(s)\n",Time::HiRes::time - $start_time); 
}


################################################################################
# job
#      :ディレクトリの作成（深いフォルダを作成）
# in
#      :ディレクトリ
# out
#      :なし
# exp
#      :mylib::make_dir_depth("./test1/test2/test3");
###############################################################################
sub make_dir_force{
    my ($tmp_dir) = @_;
    
    eval {
        if (-d $tmp_dir) {
            rmtree($tmp_dir);
        }
        
        mkpath [$tmp_dir] or die $!;
    };
    
    if ($@) {
      die $@;
    }   
}


################################################################################
# job
#      :ディレクトリの削除（存在する場合でも削除）
# in
#      :ディレクトリ
# out
#      :なし
# exp
#      :mylib::remove_dir_force("test");
###############################################################################
sub remove_dir_force{
    
    my ($tmp_dir) = @_;
    
    if ((tmp_dir ne '.') and (tmp_dir ne '..')) {
        if (-d $tmp_dir) {
            rmtree($tmp_dir);
        }       
    }
}


################################################################################
# job
#      :システムコマンド実行、結果を返す
# in
#      :システムコマンド文字列
# out
#      :実行結果
# exp
#      :my $reslt = mylib::system_command("ls -la");
###############################################################################
sub system_command{
    my ($cmd) = @_;
    
    my $result_qx = "";
    
    if($cmd ne ""){
        $result_qx = qx/$cmd/;
    }
    
    $result_qx =  decode('UTF-8', $result_qx);
    
    return $result_qx;
}


################################################################################
# job
#      :ファイルをコピー
# in
#      :コピー元ファイル
#      :コピー先ファイル
# out
#      :なし
# exp
#      :my $reslt = mylib::copy_file("a.txt", "b.txt");    ファイルをコピー    
#      :my $reslt = mylib::copy_file("a.txt", "./test");   ディレクトリへコピー
###############################################################################
sub copy_file{
    my ($src_file, $dest_file) = @_;
    
    File::Copy::copy($src_file, $dest_file) or die $!;
}

################################################################################
# job
#      :ファイルを移動
# in
#      :移動元ファイル
#      :移動先ファイル
# out
#      :なし
# exp
#      :my $reslt = mylib::move_file("a.txt", "b.txt");    ファイルを移動
#      :my $reslt = mylib::move_file("a.txt", "./test");   フォルダへコピー
###############################################################################
sub move_file{
    my ($src, $dest) = @_;
    
    File::Copy::move($src, $dest) or die $!;
}


################################################################################
# job
#      :配列からデータを検索
# in
#      :対象とする配列のリファレンス
#      :探すデータ文字列
# out
#      :検索結果配列
# exp1
#      :my @datas = (12,22,13,44);
#      :my $reslt = mylib::search_for_array(\@datas, "^1");
# exp2
#      :my @datas = ("apple","ace","big","cute");
#      :my @results = mylib::search_for_array(\@datas, "^a");
###############################################################################
sub search_for_array{
    my ($data_array_ref, $search_str) = @_;
    
    my @results = grep(/$search_str/, @{$data_array_ref});
    return @results;
}

################################################################################
# job
#      :splitｓ処理
# in
#      :分割文字列
#      :対象文字列
# out
#      :分割結果配列
# exp
#      :my @datas = mylib::split_simple(",", "a,s,b,d");
###############################################################################
sub split_simple{
    my ($div_string, $str) = @_;
    
    return split(/$div_string/, $str);
}


################################################################################
# job
#      :ハッシュをマージ
# in
#      :ハッシュ1のリファレンス
#      :ハッシュ2のリファレンス
# out
#      :マージしたハッシュ
# exp
#      :my %hash1 = ("a" => 1, "b" => 2);
#      :my %hash2 = ("c" => 3, "d" => 4);
#      :my %hash3 = mylib::merge_hash(\%hash1, \%hash2);
###############################################################################
sub merge_hash{
    my ($hash_1_ref, $hash_2_ref) = @_;
    
    my %hash_merge = (%{$hash_1_ref}, %{$hash_2_ref});
    return %hash_merge;
}


################################################################################
# job
#      :ファイルの存在チェック
# in
#      :チェックするファイル
# out
#      :結果
# exp
#      :if(mylib::check_exist_file("test.txt")){
#      :   print("ファイルが存在します");
#      :} else {
#      :   print("ファイルが存在しません");
#      :}
###############################################################################
sub check_exist_file{
    my ($file) = @_;
    
    my $result = 0;
    if(-f $file){
        $result = 1;
    }
    
    return $result;
}


################################################################################
# job
#      :ディレクトリの存在チェック
# in
#      :チェックするディレクトリ
# out
#      :結果
# exp
#      :if(mylib::check_exist_dir("./data")){
#      :   print("ディレクトリが存在します");
#      :} else {
#      :   print("ディレクトリが存在しません");
#      :}
###############################################################################
sub check_exist_dir{
    my ($dir) = @_;
    
    my $result = 0;
    if(-d $dir){
        $result = 1;
    }
    
    return $result;
}


################################################################################
# job
#      :ファイルの削除
# in
#      :対象とするファイル
# out
#      :なし
# exp
#      :mylib::delete_file("test.txt");
################################################################################
sub delete_file{
    my ($file) = @_;
    
    unlink $file or die $!; 
}
 

################################################################################
# job
#      :ワイルドカードを使ったファイルの削除
# in
#      :対象とするワイルドカード
# out
#      :なし
# exp
#      :mylib::delete_file_by_wildcard("*.data");
################################################################################
sub delete_file_by_wildcard{
    my ($wild_card) = @_;
    
    File::Remove::remove $wild_card;
}


################################################################################
# job
#      :ファイルパスパース
# in
#      :対象とするファイルパス
# out
#      :パース結果(dir, name)
# exp
#      :my %tmp = mylib::parse_file_path("./data1/data2/test.txt");
#      :print($tmp{"dir"}."\n");
#      :print($tmp{"name"}."\n");
################################################################################
sub parse_file_path{
    my($file_path) = @_;
        
    my ($name, $dir, $ext) = fileparse($file_path);
    my %tmp_hash = ();
    $tmp_hash{"dir"} = $dir; 
    $tmp_hash{"name"} = $name;
    #$tmp_hash{"ext"} = $ext; 
    
    return %tmp_hash; 
}


################################################################################
# job
#      :フルパスを取得
# in
#      :対象とするファイルパス
# out
#      :フルパス
# exp
#      :my $fullpath = mylib::get_full_path("./data1/data2/test.txt");
#      :print($fullpath."\n");
################################################################################
sub get_full_path{
    my($file_path) = @_;
    
    return File::Spec->rel2abs($file_path);
}


#動かない？　保留
################################################################################
# job
#      :設定ファイルを読み込む
# in
#      :設定ファイル
# out
#      :設定オブジェクト
# exp
#      :my $cfg = mylib::read_config_file("app.ini");
#      :print(cfg->param("pass")."\n");
################################################################################
#sub read_config_file(){
#  my($config_file_path) = @_;
#  
#  my $cfgObj = new Config::Simple;
#  $cfgObj->read($config_file_path);
#  my $cfg = $cfgObj->vars();
#
#  return $cfg;
#}


################################################################################
# job
#      :ファイルを比較
# in
#      :ファイル1
#      :ファイル2
# out
#      :比較結果
# exp
#      :my $cfg = mylib::read_config_file("app.ini");
#      :print(cfg->param("pass")."\n");
################################################################################
sub compare_file{
    my($file1, $file2) = @_;

    if (File::Compare::compare($file1, $file2) == 0) {
        return 1;
    } else {
        return 0;
    }
}


################################################################################
# job
#      :正規表現:マッチ（option:gi）
# in
#      :チェック対象文字列
#      :チェックパターン文字列
# out
#      :結果
# exp
#      :my $check_str = "あいうえお";
#      :if(mylib::regex_match_simple($check_str,"^あい")){
#      :   print("match\n");
#      :}else{
#      :   print("no match\n");
#      :}
################################################################################
sub regex_match_simple{
    my ($check_str, $regex_str) = @_;
    
    if ($check_str =~ m/$regex_str/gi) {
        return 1;
    }
    return 0;    
}


################################################################################
# job
#      :正規表現:置換（option:gi）
# in
#      :チェック対象文字列
#      :チェックパターン文字列
#      :置換文字列
# out
#      :置換結果文字列
# exp
#      :my $check_str = "abc,def,gshi,abc";
#      :my $str = mylib::regex_replace_simple($check_str,"abc", "xyz");
################################################################################
sub regex_replace_simple{
    my ($check_str, $regex_str, $rep_str) = @_;
    
    my $str = $check_str;
    $str =~ s/$regex_str/$rep_str/gi;
    return $str;
}


################################################################################
# job
#      :配列の最大値を取得（数値対応）
# in
#      :対象とする配列
# out
#      :最大値
# exp
#      :my $check_str = mylib::get_max_for_array(@data);
################################################################################
sub get_max_for_array{
    my($array_ref) = @_;
    my @array_data =  @{$array_ref};
    return List::Util::max(@array_data);   
}


################################################################################
# job
#      :配列の最小値を取得（数値対応）
# in
#      :対象とする配列
# out
#      :最小値
# exp
#      :my $check_str = mylib::get_min_for_array(@data);
################################################################################
sub get_min_for_array{
    my($array_ref) = @_;
    my @array_data =  @{$array_ref};
    return List::Util::min(@array_data);   
}


################################################################################
# job
#      :配列の合計値を取得（数値対応）
# in
#      :対象とする配列
# out
#      :合計値
# exp
#      :my $check_str = mylib::get_sum_for_array(@data);
################################################################################
sub get_sum_for_array{
    my($array_ref) = @_;
    my @array_data =  @{$array_ref};
    return List::Util::sum(@array_data);
}


################################################################################
# job
#      :パスを結合する
# in
#      :ディレクトリパス
#      :ファイル名
# out
#      :結合したパス
# exp
#      :my $path = mylib::combine_path("./data1/data2", "test.txt");
################################################################################
sub combine_path{
    my($dir, $file) = @_;
    
    my $cpath = File::Spec->catfile($dir, $file);
    return $cpath;
}


################################################################################
# job
#      :文字コードをUTF-8へ変換
# in
#      :対象とする文字列
# out
#      :utf-8に変換した文字列
# exp
#      :my $result = mylib::enc_utf8($str);
################################################################################
sub enc_utf8{
    my($str) = @_;
    
    return Encode::encode('utf-8', $str);
}

sub dec_utf8{
    my($str) = @_;
    
    return Encode::decode('utf-8', $str);
}



################################################################################
# job
#      :色づけ表示
# in
#      :色指定 ("black","red","green","yellow","blue","magenta","cyan","white")
#      :文字列
# out
#      :なし
# exp
#      :my $result = mylib::enc_utf8($str);
################################################################################
sub print_color{
    my($color, $str) = @_;

    print color($color), $str, color("reset");
}


#-------------------------------------------------------------------------------
return 1;