# Linear-Algebra
線形代数学をプログラミングを通して学ぶリポジトリ

- ところでポインタっていつ使うの？
  - 「コンパイル時にサイズが決まらないデータ」や「巨大すぎてコピーしたくないデータ」を扱うときに使う．

## 第1回: 複素ベクトル構造体の設計とメモリ管理
### ComplexVectorの実装
1. 構造体`ComplexVector`を定義
  1. ベクトルの次元数`size`(int)
  2. データ列へのポインタ`data`(`double complex*`)
    - `<complex.h>`の`double complex`型を使用．
2. 関数`ComplexVector* create_vector(int size)`の作成
  1. 指定`size`のベクトルを作成
  2. 構造体自体の`malloc`, メンバ`data`の`malloc`のどちらも必要
  3. 確保した領域は0で初期化
  4. 確保失敗時のNULLチェック
3. 関数`void free_vector(ComplexVector *v)`の作成
  1. 使い終わったベクトルを解放する
  2. `create`と逆の手順で解放->メモリリークを防ぐ
  3. `data`の解放が先？`v`の解放が先？
4. 関数`void set_element(ComplexVector *v, int index, double complex value)`の作成
  1. ベクトル`v`の`index`番目に`value`をセット
  2. 範囲外アクセスのチェック->該当するなら`exit(1)`
5. 関数`double complex get_element(const ComplexVector *v, int index)`の作成
  1. 値の取得．範囲チェックする．
  2. なぜ引数に`const`?
