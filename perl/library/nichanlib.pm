#-------------------------------------------------------------------------------
# nichanlib.pm
#-------------------------------------------------------------------------------
package nichanlib;

#必須です
use strict;
use warnings;
use File::Basename;
use File::Path;
use File::Spec;
use XMLRPC::Lite;
use Encode;
use Encode qw/ decode encode_utf8 /;
use LWP::UserAgent;
use HTML::TreeBuilder;



#文字コード
use utf8;
binmode STDIN, ":utf8";
binmode STDOUT, ":utf8";

#モジュール
require "mylib.pm";


#-------------------------------------------------------------------------------
# job  
#      :2cからカテゴリリンク情報を取得、ファイルに保存します
# in   
#      :取得メニューリンク
#      :作業用メニューリンクページ
#      :結果カテゴリリンクページ保存ファイル
# out  
#      :無し
# exp
#      :nichlib::get_2ch_bbs_menu('http://menu.2ch.net/bbsmenu.html', 'tmp_2ch_bbsmenu.html', '2ch_bbsmenu_link.tsv');
#-------------------------------------------------------------------------------
sub get_2ch_bbs_menu{
    
    #---------------------------------------- param
    my($menu_url, $tmp_2ch_bbs_menu_html_file, $save_2ch_bbs_menu_link_file) = @_;
    print("取得メニューリンク:$menu_url\n");
    print("作業用メニューリンクページ:$tmp_2ch_bbs_menu_html_file\n");
    print("結果カテゴリリンクページ保存ファイル:$save_2ch_bbs_menu_link_file\n");
    
    #---------------------------------------- get page
    print(" => get page\n");
    my $ua = LWP::UserAgent->new;
    $ua->agent('Mozilla/5.0 (Windows NT 5.1) AppleWebKit/535.1 (KHTML, like Gecko) Chrome/14.0.835.187 Safari/535.1');
    my $res = $ua->get($menu_url);
    $ua->parse_head(0);
    my $content = decode ( 'shiftjis', $res->content );
    my @content_array = ();
    push(@content_array, $content);
    
    #print(" -> save tmp file\n");
    &mylib::write_file($tmp_2ch_bbs_menu_html_file, \@content_array, 'utf8');
    
    
    #---------------------------------------- get link
    print(" => get link\n");
    my $tree = new HTML::TreeBuilder;
    $tree->parse_file($tmp_2ch_bbs_menu_html_file);
    $tree->eof(); 
     
    my @list = ();
    for my $a ( $tree->look_down("href", qr{http://} ) ) {
        my $line = join("\t", $a->attr_get_i('href'), decode( 'utf-8', $a->as_text));
        #print $line."\n";
        push(@list, $line);
    }
    
    $tree = $tree->delete;
    
    
    #---------------------------------------- save link
    print(" => save file\n");
    &mylib::write_file($save_2ch_bbs_menu_link_file, \@list, "utf8");
}


#-------------------------------------------------------------------------------
# job  
#      :2chのカテゴリのリンク情報から、記事一覧のリンクを取得
# in   
#      :入力：カテゴリURL
#      :入力：コメント数ハッシュのリファレンス
#      :入力：対象スレッド数
#      :出力：作業用ファイル
#      :出力：スレッドURL保存ファイル
#      :フィルタ文字ファイル
# out  
#      :無し
# exp
#      :nichlib::get_2ch_thread_link_for_category('http://yuzuru.2ch.net/comicnews/subback.html', \%thread_count_hash_ref, 300,'tmp_category.html', 'thread_url_file.tsv');
#-------------------------------------------------------------------------------
sub get_2ch_thread_link_for_category{

    #---------------------------------------- param
    my($menu_url, $comment_count_hash_ref, $target_thread_count, $tmp_category_file, $thread_url_file, $filter_word_datas_ref) = @_;
    print("カテゴリURL:$menu_url\n");
    print("コメント数ハッシュのリファレンス:$comment_count_hash_ref\n");
    print("作業用ファイル:$tmp_category_file\n");
    print("スレッドURL保存ファイル:$thread_url_file\n");
    
    #---------------------------------------- param
    print(" => get page\n");
    my $ua = LWP::UserAgent->new;
    $ua->agent('Mozilla/5.0 (Windows NT 5.1) AppleWebKit/535.1 (KHTML, like Gecko) Chrome/14.0.835.187 Safari/535.1');
    my $res = $ua->get($menu_url);
    $ua->parse_head(0);
    my $content= decode ( 'shiftjis' , $res->content );
    my @content_array = ();
    push(@content_array, $content);
    &mylib::write_file($tmp_category_file, \@content_array, 'utf8');
    
    #---------------------------------------- 記事ページ解析
    print(" => get thread\n");
    my $tree = new HTML::TreeBuilder;
    $tree->parse_file($tmp_category_file);
    $tree->eof();
         
    #base
    my $base_url = "";
    foreach my $tag ($tree->find("base")) {
        $base_url = $tag->attr('href');
        print ($base_url."\n");
        last;
    }
    
    #タイトルとリンクは全て同じフォーマットでは無い、タイトルはページから取得するのでここで必要ない、リンクのみを抽出する。
    my @list = ();
    for my $a ( $tree->look_down("href", qr{^\d} ) ) {
        my $tmp_url = $base_url.decode('utf-8', $a->attr_get_i('href'));
        $tmp_url =~ s/\/l50//go;
        
        #取得定義数以上、または前回より大きい場合はリンクとする
        my $tmp_title = decode('utf-8', $a->as_text);
        my $count = 0;
        
        if($tmp_title =~ /\((\d+)\)$/){
            $count = $1;
        }
        
        #対象とするスレッド数 以上の場合
        if($count >= $target_thread_count){
            
            #k下記の文字列が含まれている場合は対象とする
            #print($tmp_title."\n");
            #print($filter_str."\n");
            
            my @filter_str_datas = @{$filter_word_datas_ref};
            my $check_fds_flag = 0;
            
            foreach my $fsd(@filter_str_datas){
                
                if($fsd ne ""){
                    my $result = index($tmp_title, $fsd);
                    #print("$result\n");
                    if($result == -1){
                        next; #次をチェック
                    }else{
                        $check_fds_flag = 1;
                     last:    #チェックループを抜ける
                    }
                }
            }
            
            #文字列が対象に含まれていない場合は次をチェック
            if($check_fds_flag == 0){
                next;
            }
            
#          if($filter_str ne "none"){
#              my $result = index($tmp_title, $filter_str);
#              #print("$result\n");
#              if($result == -1){
#                  next;
#              }
#          }

            #前後のいらないものを削除
            $tmp_title =~ s/^\d{1,4}: //;
            $tmp_title =~ s/ \((\d+)\)$//;
            
            #前回よりスレッド数 より大きい場合hはチェック、そうでない場合は登録する
            my $before_count=0;
            #print("==========================>> ".$tmp_title."\n");
            if(exists($comment_count_hash_ref->{$tmp_title})){
                #print("==========================>> あるよ => ".$tmp_title."\n");
                
                $before_count = $comment_count_hash_ref->{$tmp_title};
                $before_count += 0;
                
                #更新登録
                if($count > $before_count){
                    my $tmp_text_url = join("\t", $tmp_url, $tmp_title, $count);
                    push(@list, $tmp_text_url);
                }
            }else{
                #print("==========================>> ないよ => ".$tmp_title."\n");
                
                #新規登録
                my $tmp_text_url = join("\t", $tmp_url, $tmp_title, $count);
                push(@list, $tmp_text_url);
            }
        }
    }
       
    $tree = $tree->delete;
    
    #--------------------------------- save link
    print(" => save file\n");
    &mylib::write_file($thread_url_file, \@list, "utf8");
}


#-------------------------------------------------------------------------------
# job  
#      :2c記事一覧のリンクから内容を取得します
# in   
#      :スレッドURLTSVファイル
#      :スレッド出力ディレクトリ
#      :処理待ち時間
# out  
#      :無し
# exp
#      :nichnlib::get_2ch_thread_contents('thread_url_file.tsv' './txt', 3);
#-------------------------------------------------------------------------------
sub get_2ch_thread_contents{
    
    #--------------------------------- param
    my($thread_url_file, $output_dir, $wait_time) = @_;
    print("スレッドURLファイル:$thread_url_file\n");
    print("出力ディレクトリ:$output_dir\n");
    print("処理待ち時間:$wait_time\n");
    
    #--------------------------------- 出力ディレクトリ作成
    if(!(-d $output_dir)){
        mkdir($output_dir);
    }
    
    #--------------------------------- ファイルからスレッドのリンクを抽出
    my @web_datas = ();
    my %thread_count_hash = ();
    print(" => read url file\n");
    my @list = &mylib::read_file($thread_url_file, "utf8");
    
    foreach my $l (@list){
        
        if($l eq ""){
            next;
        }
        
        #url
        my @datas = split(/\t/, $l);
        my $url = $datas[0];
        push(@web_datas, $url);
        
        #thread count
        my $title = $datas[1];
        my $count = $datas[2];;
        print("$title => $count\n");
        $thread_count_hash{$url} = $count;
    }
    
    #--------------------------------- スレッド取得
    foreach my $wd (@web_datas){
        
        print(" => get page:web data:$wd\n");
        my @data_array = ();
        my @split_address = split(/\//, $wd);
        #my $tmp_html_file_name = $split_address[-1].".html";
        my $tmp_html_file_name = "_tmp.html";
    
        my $url = $wd;
        my $ua = LWP::UserAgent->new;
        $ua->agent('Mozilla/5.0 (Windows NT 5.1) AppleWebKit/535.1 (KHTML, like Gecko) Chrome/14.0.835.187 Safari/535.1');
        my $res = $ua->get($url);
        
        if($res->is_success){
        
            $ua->parse_head(0);
            my $content = $res->decoded_content;
                
            #--------------------------------- 記事ページ解析
            print(" => get thread content\n");
            my $tree = new HTML::TreeBuilder;
            $tree->parse($content);
            $tree->eof();
                 
            #--------------------------------- タイトル
            my $title = "";
            foreach my $tag ($tree->find("h1")) {
                $title = $tag->as_text;
                print("タイトル：".$title."\n");
                push(@data_array, $title);
            }
            
            #--------------------------------- コメント数
            my $comment_count = $thread_count_hash{$wd};
            $comment_count += 0;
            push(@data_array, $comment_count);
                
            #---------------------------------　記事を抽出（as_HTMLだと文字化けするが、as_XMLだときちんととれる）
            for my $a ( $tree->look_down("class", "thread" ) ) { 
                my $line = $a->as_XML;
                push(@data_array, $line);
            }
        
            #--------------------------------- 保存
            print(" => save file\n");
            my $file_name = $split_address[-2]."_".$split_address[-1].".txt";
            my $save_file = File::Spec->catfile($output_dir, $file_name);
            
            &mylib::write_file($save_file, \@data_array, "utf8");
            $tree = $tree->delete;
            
            sleep($wait_time);
        }else{
            #エラー
            print("get error:$url\n");
        }
    }
}


#-------------------------------------------------------------------------------
# job  
#      :2cから取得したスレッド内容の不要な部分を変換します
# in   
#      :スレッドページフォルダ
#      :スレッドページ編集結果フォルダ
# out  
#      :無し
# exp
#      :nichlib::convert_entry_text_from_thread_contents('$input_dir' '$output_dir');
#-------------------------------------------------------------------------------
sub convert_entry_text_from_thread_contents{
    
    #--------------------------------- param
    my($input_dir, $output_dir) = @_;
    print("スレッドページディレクトリ:$input_dir\n");
    print("スレッドページ編集結果ディレクトリ:$output_dir\n");
    
    #--------------------------------- 
    print(" => get files\n");
    my @files = mylib::get_files_all_dir($input_dir, "*.txt");

    print(" => convert files\n");
    foreach my $file (@files){
        print(" => $file\n");
        
        my@lines = mylib::read_file($file, 'utf8');
        my @output_lines = ();
        my $title = "";
        my $comment_count = 0;
        my $result = "";
        
        #スレッド内リンクを文字へ、メールリンクを文字へ変換
        for(my $i=0; $i <= $#lines ; $i++){
            
            #1行目はタイトル
            if($i == 0){
                $title = $lines[$i];
                next;
            }
            
            #2行目はコメント数
            if($i == 1){
                $comment_count = $lines[$i];
                next;
            }
            
            $result = $lines[$i];
            $result =~ s/(<a href=\"\.\.\/test\/read\.cgi.+?\">)(.+?)(<\/a>)/$2/g;
            #$result =~ s/(<a href=\"mailto:sage\">)(.+?)(<\/a>)/<font color=green>$2<\/font>/g;
            
            $result =~ s/(<a href=\"mailto:.*?\">).+?(<\/a>)/<font color=\"green\">名無しさん<\/font>/g;
            $result =~ s/(<font color=\"green\">).+?(<\/font>)/<font color=\"green\">名無しさん<\/font>/g;
            
                        
            #3行しかないので抜ける
            last;
        }
        
        push(@output_lines, $title);
        push(@output_lines, $comment_count);
        push(@output_lines, $result);

        #print($title."\n");
        #print($result."\n");
        
        my ($filename, $path, $suffix) = fileparse($file);
        my @tmp_paths = split(/\//, $path);
        my @tmp_paths_2 = @tmp_paths[1..$#tmp_paths];
        $path = join("/", @tmp_paths_2);
        my $tmp_dir = mylib::combine_path($output_dir, $path);
        #print("  => ".$tmp_dir."\n");
        
        if(!mylib::check_exist_dir($tmp_dir)){
            mylib::make_dir_force($tmp_dir);
        }
        
        my $fn = mylib::combine_path($tmp_dir, $filename);
        mylib::write_file($fn, \@output_lines, 'utf8');
    }
}


#-------------------------------------------------------------------------------
# job  
#      :2cから取得したスレッド内容に返信コメントに色を設定します
# in   
#      :スレッドページディレクトリ
#      :スレッドページ編集結果（色付け）ディレクトリ
# out  
#      :無し
# exp
#      :nichlib::convert_entry_text_from_thread_contents('$input_dir' '$output_dir');
#-------------------------------------------------------------------------------
sub convert_entry_text_from_thread_contents_color{

    #--------------------------------- param
    my($input_dir, $output_dir) = @_;
    print("スレッドページディレクトリ:$input_dir\n");
    print("スレッドページ編集結果（色付け）ディレクトリ:$output_dir\n");
    
    #--------------------------------- 
    print(" => get files\n");
    my @files = mylib::get_files_all_dir($input_dir, "*.txt");

    print(" => convert files\n");
    foreach my $file (@files){
        print(" => $file\n");
        
        my@lines = mylib::read_file($file, 'utf8');
        my $file_title = $lines[0];
        my $file_comment_count = $lines[1];
        my $contents = $lines[2];
        
        my $dl_header = "<dl class=\"thread\">";
        my $dl_footer = "</dl>";
        my $start_index = 0;
        my @output_datas = ();
        my $comment_count = 1;
        my %comment_hash = ();

        while(1){
            my $check_start_index = index($contents, "<dt>", $start_index);

            if($check_start_index == -1){
                last;
            }
        
            my $check_end_index =  index ($contents, "</dd>", $check_start_index);
            $check_end_index += 5;
            my $comment = substr($contents, $check_start_index, $check_end_index - $check_start_index );
            $comment_hash{$comment_count} = $comment;
        
            #my $check_cotain_start_index = index($comment, "<dd>", 0);
            #$check_cotain_start_index += 4;
            #my $check_cotain_end_index = index($comment, "</dd>", 0);
            #$comment_contain_hash{$comment_count} = substr($comment, $check_cotain_start_index, $check_cotain_end_index - $check_cotain_start_index);
            $comment_count++;
            $start_index = $check_end_index;
        }
        
        
        #@output_datas
        print(" => check コメントリンク\n");
        my %add_comment_hash = ();
        foreach my $key (sort(keys(%comment_hash))){
            my $comment = $comment_hash{$key};
        
            if($comment =~ /<dd>&gt;&gt;(\d+)/){
                if($comment =~ s/<dd>/<dd class="ret1">/){
                    $comment_hash{$key} = $comment ;
                    #print("$comment\n");
                }
            }
        }

        my @sort_keys = sort {$a <=> $b} keys(%comment_hash);


        push(@output_datas, $dl_header);
        foreach my $key (@sort_keys){
            push(@output_datas, $comment_hash{$key});
        }
        push(@output_datas, $dl_footer);
        my $output_datas_join = join("",@output_datas);
        #print("$output_datas_join\n");
        

        my @output_lines = ();
        push(@output_lines, $file_title);
        push(@output_lines, $file_comment_count);
        push(@output_lines, $output_datas_join);
        
        #保存
        my ($filename, $path, $suffix) = fileparse($file);
        my @tmp_paths = split(/\//, $path);
        my @tmp_paths_2 = @tmp_paths[1..$#tmp_paths];
        $path = join("/", @tmp_paths_2);
        my $tmp_dir = mylib::combine_path($output_dir, $path);
        #print("  => ".$tmp_dir."\n");
        
        if(!mylib::check_exist_dir($tmp_dir)){
            mylib::make_dir_force($tmp_dir);
        }
        
        my $fn = mylib::combine_path($tmp_dir, $filename);
        mylib::write_file($fn, \@output_lines, 'utf8');
    }
}

#-------------------------------------------------------------------------------
return 1;