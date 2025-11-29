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

### norm_squaredの実装
- ベクトルのノルムの二乗を返す関数
```math
|v|^2 = \sum_{i+0}^{N-1}|v_{i}|^2= \sum_{i+0}^{N-1} (v_{i} \cdot v_{i}*)
```
### 内積(Inner Product)の実装
- 二つのベクトル間の内積は以下で表される．
```math
\langle \phi|\psi \rangle = \sum_{j=0}^{N-1}\phi_{j}*\psi_{j}
```
- 左側のブラベクトル $\langle \phi|$ の要素が共役複素数になる．
  - 順序を逆にすると複素共役になる．
```math
\langle \psi|\phi \rangle = \langle \phi|\psi \rangle *
```
- 内積を計算する関数を追加する．

## 第2回: 演算子の実装(行列構造体)

