<?php
class CSV_UPDATE_MODULE{
 public static $csv;
 public static $path;
 public static $records;
 public static $csvfilename;
 public static $checkpath;
 public static $template;
 public static $create_file_dir;
 function __construct($uri = ''){}
   public static function set_csv_filename($csv_filename){
     self::$checkpath = dirname(__FILE__).'/' . $csv_filename . '.csv';
     if(file_exists(self::$checkpath)){
       self::$path = self::$checkpath;
     }else{
       echo 'CSVがセットされていません';
     }
   }
   //CSVファイルを強制的に読み込む
 public static function force_load_csv(){
   ini_set('auto_detect_line_endings',true);
   self::$csv = new SplFileObject(self::$path);
   self::$csv->setFlags(SplFileObject::READ_CSV);
   foreach (self::$csv as $key => $line) {

     if($key == 0){
       mb_convert_variables('UTF-8','SJIS',$line);
       $item = $line;
     }
     foreach( $line as $l => $str ){
       if($key > 0){
         mb_convert_variables('UTF-8','SJIS',$str);
         self::$records[$key][$item[$l]] = $str;
       }else{
         self::$records[$key][$l] = $str;
       };
     }
   }
 }
 //レコードを強制的に返す
 public static function force_get_all(){
  return self::$records;
 }

 //更新時のテンプレート用HTMLをセット
 public static function set_template_html($template_path){
   if(file_exists($template_path)){
     self::$template = file_get_contents($template_path,true);
   }else{
     echo 'テンプレートが存在しません。';
   }
 }
 //更新時のテンプレート用HTMLをセット
 public static function echo_template_html(){
   if(self::$template):
   echo self::$template;
    else:
   echo 'テンプレートが設定されておりません';
   endif;
 }
 //テンプレートから強制的に複数のHTMLを作成する
 /*
CSVの項目は
html と　path を入れなければならない
| str1 | str2 | str3 | html(出力ファイル名) | path（出力パス）|
 */
 public static function force_create_html(){
   $item_name = array();
   $temp_files = array();
   foreach (self::$records as $key => $item) {
     $tmp_file = self::$template;
     foreach($item as $line_key => $line_item){
       //CSVのフィールドを登録
       if($key == 0){
         $item_name[$line_key] = $line_item;
       }else{
         $tmp_file = preg_replace('/\$\{'.$line_key.'\}/',$line_item,$tmp_file);
       }

     }

     if($key != 0){
       $put_files = array();
       $put_files['html'] = $tmp_file;
       $put_files['path'] = $item['path'];
       $temp_files[] = $put_files;
     }
   }

   foreach($temp_files as $putfile){
     if(!file_exists(dirname(__FILE__).'/' .$putfile['path'])){
       $dirpath_tmp = explode('/',$putfile['path']);
       array_pop($dirpath_tmp);
       $dirpath = implode('/',$dirpath_tmp);
       if(!file_exists(dirname(__FILE__).'/' .$dirpath)){
        mkdir(dirname(__FILE__).'/' .$dirpath);
       }
     }
     file_put_contents(dirname(__FILE__).'/' .$putfile['path'],$putfile['html']);
   }
 }

 //テンプレートから強制的に一つのHTMLに結合する
/*
| ${str1} | ${str1} | ${str1} |
*/

 public static function force_create_listHtml(){
   $item_name = array();
   $temp_files = array();
   $tmp_output_file = '';
   foreach (self::$records as $key => $item) {
     $tmp_file = self::$template;
     foreach($item as $line_key => $line_item){
       //CSVのフィールドを登録
       if($key == 0){
         $item_name[$line_key] = $line_item;
       }else{
         $tmp_file = preg_replace('/\$\{'.$line_key.'\}/',$line_item,$tmp_file);
       }
     }
     if($key != 0){
       $put_files = array();
       $put_files['html'] = $tmp_file;
       $put_files['path'] = $item['path'];
       $temp_files[] = $put_files;
     }
   }

   foreach($temp_files as $putfile){
     if(!file_exists(dirname(__FILE__) . '/output')){
       mkdir(dirname(__FILE__).'/output');
     }
     $tmp_output_file .= $putfile['html'];
   }
   file_put_contents(dirname(__FILE__).'/output/' .'list.html',$tmp_output_file);
 }

 //テンプレート内の文字列をCSVで一気に置換える
 //replace.htmlを読み込んで、
 //1列目の文字を2列目の文字に置換える
 //replace/replaced.htmlに結果を出力
 //フィールドは不要
 public static function replace_html(){
   $tmp_file = self::$template;
   $count = 0;//CSV列カウンター　2列目までのみ使う
   foreach (self::$records as $key => $item) {
     $count = 0;
     foreach($item as $line_key => $line_item){
         if($count <= 1):
           //1列目を置き換え前の文字とする
           if($count == 0){
             $rep_target = $line_item;
           }else{
             //2列目の文字に置換える
             $tmp_file = preg_replace('#'. $rep_target .'#',$line_item,$tmp_file);
           }
         endif;
       $count ++;
     }
   }

   if(!file_exists(dirname(__FILE__) . '/replace')){
     mkdir(dirname(__FILE__).'/replace');
   }
   file_put_contents(dirname(__FILE__).'/replace/' .'replaced.html',$tmp_file);
 }
 //テスト表示
 public static function test_echo($str){
   echo 'include ' . $str . " ok\n";
 }
}
?>
