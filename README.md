# temp-php-createfiles
phpを使ってファイルを量産するときに使います。  
  
このファイルにCSV_UPDATE_MODULEクラスを読み込んでブラウザで表示させた瞬間、  
CSVに記載されている情報をもとに、テンプレートを使ってファイルを量産します。  
  
## 使い方
1. index.phpを用意
1. class.csv_update_module.inc を読み込む
1. CSV_UPDATE_MODULEクラスの変数を設定し関数を実行
   1. set_csv_filename　読込むCSVのファイル名
   1. force_load_csv CSVの読込実行
   1. set_template_html テンプレートファイルの設定
   1. force_create_html ファイル量産実行
   
|テンプレート内の置換え対象フィールド名| path |
|:---:|:---:|
|置換えるテンプレート内の${フィールド名}文字列| 出力先ファイルパス |   
   
1. CSVのpath フィールドに記載されているclass.csv_update_module.incからのファイルパスにファイルを出力します。
1. フィールド名の文字列を置換えます
