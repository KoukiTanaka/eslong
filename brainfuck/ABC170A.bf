入力回数カウンタ0
入力値1
デクリメント用カウンタ2

[-]+++++
[>,>,[-]<   //入力 空白等を飛ばす
   >++++++++++++++++ 16回次のfor文を繰り返す
   [ 
     <--- 入力値を3減らす
     >- カウンタのデクリメント
   ]
   < 入力値を参照
   >+ //次の場所をif文の条件として利用
   <
   [
     >[-] if文の条件式を偽に
     <[-] 入力値を消去
   ]
   >
   [
       [-]
       < //入力値に移動
       < 現在のカウンタ回数を確認

       //現在のfor文回数を2個先のポインタへコピー start
       [
           >>+ 
           >+ 
           <<<-
       ]
       >>>
       [
           <<<+
           >>>-
       ]
       //現在のfor文回数を2個先のポインタへコピー end
       +++++
       <
       [
           >-
           <-
       ]
       >
       [
           >+
           <-
       ]
       <
       [-]入力値を消去
   ]
   <
   <-
]
[-]
++++++++++++++++
[
    >>>>+++
    <<<<-
]
>>>>+.