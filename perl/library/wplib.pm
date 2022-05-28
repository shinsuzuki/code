#-------------------------------------------------------------------------------
# wplib.pm
#-------------------------------------------------------------------------------
package wplib;

#必須です
use strict;
use warnings;
use Encode;
use Encode qw(encode_utf8);
use File::Basename;
use File::Path;
use File::Spec;
use XMLRPC::Lite;

#文字コード
use utf8;
binmode STDIN, ":utf8";
binmode STDOUT, ":utf8";

#モジュール
require "mylib.pm";

#-------------------------------------------------------------------------------
# job  
#      :スレッドを新規登録する（新規からカテゴリは登録できない）
# in   
#      :ユーザー名
#      :パスワード
#      :エンドポイント
#      :ブログID
#      :タイトル
#      :ブログ記事本文
#      :ログ記事本文の「続き」部分
#      :ブログ記事の概要
#      :ブログ記事のキーワード
# out  
#      :postid
# memo
#      :パラメータ例）
#          my @categories =();
#          push(@categories, encode('utf-8' ,'国語'));
#          これをパラメータとして使用する ➡ \@categories
#
#      :結果取得例）
#      :my $result = entry_thread(...);
#      :if(!defined($result)){
#      :   #エラー
#      :}else{
#      :   #成功,postidを買えす
#      :   $result;
#      :}
#-------------------------------------------------------------------------------
sub entry_thread{
    my($username, $password, $endpoint, $blogid, $entry_title, $entry_body, $entry_more, $entry_excerpt, $entry_keyword, $categories_ref) = @_;

    my $result = XMLRPC::Lite
        -> proxy($endpoint)
        -> call('metaWeblog.newPost', $blogid, $username, $password,
            {
                #-- ブログ記事タイトル
                'title' => $entry_title,
                #-- ブログ記事本文
                'description' => $entry_body,
                #-- コメントを受け付けるかどうか(1でコメント受付)
                'mt_allow_comments' => 1,
                #-- トラックバックを受け付けるかどうか(1でトラックバック受付)
                'mt_allow_pings' => 1,
                #-- ブログ記事本文の「続き」部分
                'mt_text_more' => $entry_more,
                #-- ブログ記事の概要
                'mt_excerpt' => $entry_excerpt,
                #-- ブログ記事のキーワード
                'mt_keywords' => $entry_keyword,
                #-- カテゴリ
                'categories' => $categories_ref,
            },
            1
        )
        -> result;
        
    return $result;    
}


#-------------------------------------------------------------------------------
# job
#      :スレッドを更新登録する
# in   
#      :ユーザー名
#      :パスワード
#      :エンドポイント
#      :ポストID
#      :タイトル
#      :ブログ記事本文
#      :ログ記事本文の「続き」部分
#      :ブログ記事の概要
#      :ブログ記事のキーワード
#      :カテゴリ配列への参照
# out
#      :更新登録結果
# memo
#      :（例）
#          my @categories =();
#          push(@categories, encode('utf-8' ,'国語'));
#          これをパラメータとして使用する ➡ \@categories
#-------------------------------------------------------------------------------
sub update_thread{
    my($username, $password, $endpoint, $postid, $entry_title, $entry_body, $entry_more, $entry_excerpt, $entry_keyword, $categories_ref) = @_;
    
    my $result = XMLRPC::Lite
        -> proxy($endpoint)
        -> call('metaWeblog.editPost', $postid, $username, $password,
            {
                #-- ブログ記事タイトル
                'title' => $entry_title,
                #-- ブログ記事本文
                'description' => $entry_body,
                #-- コメントを受け付けるかどうか(1でコメント受付)
                'mt_allow_comments' => 1,
                #-- トラックバックを受け付けるかどうか(1でトラックバック受付)
                'mt_allow_pings' => 1,
                #-- ブログ記事本文の「続き」部分
                'mt_text_more' => $entry_more,
                #-- ブログ記事の概要
                'mt_excerpt' => $entry_excerpt,
                #-- ブログ記事のキーワード
                'mt_keywords' => $entry_keyword,
                #-- カテゴリ
                'categories' => $categories_ref,
            },
            1
        )
        -> result;

    return $result;
}


#-------------------------------------------------------------------------------
# job
#      :ブログ情報を取得します
# in
#      :ユーザー名
#      :パスワード
#      :エンドポイント
# out
#      :ブログ情報取得結果
#-------------------------------------------------------------------------------
sub get_blog_info{
    my($username, $password, $endpoint) = @_;
    
    my $rpc = XMLRPC::Lite->new();
    $rpc->proxy($endpoint);
    
    my $res = $rpc->call("blogger.getUsersBlogs",
                XMLRPC::Data->type('string', ''),
                XMLRPC::Data->type('string', $username),
                XMLRPC::Data->type('string', $password),
                );

    return $rpc;
    
}


#-------------------------------------------------------------------------------
# job
#      :ユーザー情報を取得します
# in
#      :ユーザー名
#      :パスワード
#      :エンドポイント
# out
#      :ブログ情報取得結果
#-------------------------------------------------------------------------------
sub get_user_info{
    my($username, $password, $endpoint) = @_;
    
    my $rpc = XMLRPC::Lite->new();
    $rpc->proxy($endpoint);
    
    my $res = $rpc->call("blogger.getUserInfo",
        "",
        $username,
        $password,
    )->result;

    return $res;
}

#-------------------------------------------------------------------------------
return 1;