# プログラミング言語

- c

# 開発環境

## 起動処理

```
make してから ./main
```

```
make clean で余計なファイル消せる
```

# TIPS

### 命名規則

グローバル変数はパスカルケース

```
Head,PowDiみたいなの
```

ローカル変数はキャメルケース

```
lastBoardNumsみたいなの
```

関数はスネークケース

```
find_next_boardsみたいなの
```

### 注意点

- 変数のスコープはできるだけ小さくする。
- 関数の機能は最小限に抑える。複数の機能を持たせない。
- 全てを関数化すると機能を辿るのが煩わしくなるため、いい感じにする。
- stone_count で再帰関数つかった
