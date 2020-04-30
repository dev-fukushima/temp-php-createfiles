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
 //テンプレートから強制的にHTMLを作成する
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
       mkdir(dirname(__FILE__).'/' .$dirpath);
     }
     file_put_contents(dirname(__FILE__).'/' .$putfile['path'],$putfile['html']);
   }
 }
}
?>
