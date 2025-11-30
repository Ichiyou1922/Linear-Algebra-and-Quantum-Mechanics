# Linear-Algebra
線形代数学と量子力学をプログラミングを通して学ぶリポジトリ

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
- 時間発展の主役は行列
- 量子力学において演算子 $\hat A$ は行列として表現され，状態ベクトル $|\psi \rangle$ に作用して新しい状態を作り出す．
```math
|\psi ` \rangle = \hat A|\psi \rangle
```
### プログラミングでの実装
- 行列は二次元のデータだが，メモリは一次元．`data[low][col]`という方法もあるが，キャッシュ効率が悪く，大規模計算に向いてない．
- 一次元配列へのマッピング(Row-Major-Order).
  - $M\times N$ 行列の(i, j)成分は一次元配列上のインデックスKに以下のように対応させる．
```math
k = i \times (列数) + j
```
- 行列ライブラリを実装する->ComplexMatrix

## 第3回: 時間発展とルンゲクッタ法
- 時間概念を導入し，シュレーディンガー方程式による時間発展をシミュレーションする．
### シュレーディンガー方程式
1. ニュートン力学では，未来は $F=m \ddot r$ によって確定するが，ミクロな世界では確定した未来はない．あるのは確率．
2. 状態をベクトルで表す．
  - 量子力学では，「ここにこれくらい，あそこにあれくらいの確率で...」という情報の全てを状態ベクトル $|\psi \rangle$ に詰め込む．
  - 2準位系: 状態が二つしかないもの．電子のスピン(上か下か)など．
```math
上向き: |↑ \rangle = \begin{pmatrix} 1 \\ 0 \end{pmatrix}
```
```math
下向き: |↓ \rangle = \begin{pmatrix} 0 \\ 1 \end{pmatrix}
```
  - 量子力学には中間が存在する->この状態をを複素数を含むベクトルで表す．
```math
|\psi \rangle = \begin{pmatrix} 0.6 \\ 0.8i \end{pmatrix}
```
  - 第0成分 $c_{0}$ を上向きである**確率振幅**, 第1成分 $c_{1}$ を下向きである**確率振幅**と呼ぶ．
  - 観測したときの確率Pは，複素数の絶対値の2乗になる->ポルンの規則
```math
P(↑)=|c_{0}|^2, P(↓)=|c_{1}|^2
```
3. シュレーディンガー方程式
- 状態 $|\psi \rangle$ が決まった時，この状態はどのように変化するか？->シュレーディンガー方程式はこれを表す．
```math
-i\hbar \frac{d}{dt}|\psi (t)\rangle = \hat H |\psi (t) \rangle
```
  - 左辺は状態ベクトル $|\psi \rangle$ の速度(時間変化率)を表す．
    - 虚数単位iのおかげで確率は減衰せずに振動する．
  - 右辺はその瞬間の変化の方向(速度)を表す．
    - $\hat H$ はハミルトニアン．系の全エネルギーを表す行列．
    - 現在の状態 $|\psi \rangle$ に行列 $\hat H$ を書けることでその瞬間の速度を求める．

- ニュートン: 力 $F$ が変化を作る $\leftrightarrow$ シュレディンガー: エネルギー $\hat H$ が状態の変化を作る

- シュレディンガー方程式の言っていることはルンゲクッタ法のプロセスに似ている．
  - 現在の速度を使って，少し先の未来の状態を予測する．

- 線形演算関数`add_vector`を作って，行列同士の足し算やスカラー倍を可能にする．

### ルンゲクッタ法でラビ振動を再現
- ラビ振動->量子ビットに電磁波を当てると，状態が0->1->0...と周期的に反転する現象．
1. ハミルトニアンH`main関数内`:
```math
H = \frac{\Omega}{2}\sigma_{x} = \begin{pmatrix} 0 & 0.5 \\ 0.5 & 0 \end{pmatrix} (ただし\Omega = 1.0)
```
2. 初期状態 $\psi_{0}$ は上向き
```math
|\psi (0) \rangle = \begin{pmatrix} 1 \\ 0 \end{pmatrix}
```
3. `dt=0.01`, `ステップ数=1000`->t=0~t=10

## 第5回: 離調(Detuning)とエネルギーギャップ
- ラビ振動は共鳴と呼ばれる特殊な状態だった．
- 現実の量子コンピュータ制御では，制御パルスの周波数がわずかにずれることが頻繁にある->離調(Detuning, $\Delta$ )という．
- ハミルトニアンに成分を追加する．
```math
H = \frac{1}{2} \begin{pmatrix} -\Delta & \Omega \\ \Omega & -\Delta \end{pmatrix}
```

