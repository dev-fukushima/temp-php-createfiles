<?php include_once dirname(__FILE__).'/' .'class.csv_update_module.inc';
ini_set('display_errors', "On");
CSV_UPDATE_MODULE::set_csv_filename('create');
CSV_UPDATE_MODULE::force_load_csv();
CSV_UPDATE_MODULE::set_template_html(dirname(__FILE__).'/' .'template.html');
CSV_UPDATE_MODULE::force_create_html();

?>
<!DOCTYPE html>
<html lang="ja">
  <head>
    <meta charset="utf-8">
    <title>ファイルを量産するときに使うモジュール</title>
  </head>
  <body>
    <h1>モジュールクラスを利用してファイルを量産する</h1>
    <p>
      このファイルにCSV_UPDATE_MODULEクラスを読み込んでブラウザで表示させた瞬間、
      CSVに記載されている情報をもとに、テンプレートを使ってファイルを量産します。
    </p>
    <table>
      <tr>
        <th>path</th>
      </tr>
      <tr>
        <td>
          出力先ファイルパス。
        </td>
      </tr>
    </table>
    <p>
      CSVのpath フィールドに記載されているclass.csv_update_module.incからのファイルパスにHTMLファイルを出力します。
    </p>
  </body>
</html>
