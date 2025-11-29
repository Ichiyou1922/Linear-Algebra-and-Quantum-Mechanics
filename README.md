# Linear-Algebra
線形代数学をプログラミングを通して学ぶリポジトリ

- ところでポインタっていつ使うの？
  - 「コンパイル時にサイズが決まらないデータ」や「巨大すぎてコピーしたくないデータ」を扱うときに使う．

## 第1回: 複素ベクトル構造体の設計とメモリ管理
### ComplexVectorの実装
1. 構造体`ComplexVector`を定義
  - ベクトルの次元数`size`(int)
  - データ列へのポインタ`data`(`double complex*`)
    - `<complex.h>`の`double complex`型を使用．
2. 関数`ComplexVector* create_vector(int size)`の作成
  - 指定`size`のベクトルを作成
  - 構造体自体の`malloc`, メンバ`data`の`malloc`のどちらも必要
  - 確保した領域は0で初期化
  - 確保失敗時のNULLチェック
3. 関数`void free_vector(ComplexVector *v)`の作成
  - 使い終わったベクトルを解放する
  - `create`と逆の手順で解放->メモリリークを防ぐ
  - `data`の解放が先？`v`の解放が先？
4. 関数`void set_element(ComplexVector *v, int index, double complex value)`の作成
  - ベクトル`v`の`index`番目に`value`をセット
  - 範囲外アクセスのチェック->該当するなら`exit(1)`
5. 関数`double complex get_element(const ComplexVector *v, int index)`の作成
  - 値の取得．範囲チェックする．
  - なぜ引数に`const`?
