# arduino-dino

---

# arduino環境

---

# 腳位

+ 5V
+ GND
+ D1~D13
+ A1~A7

---

# 輸出

`pinMode(腳位,OUTPUT);`
`digitalWrite(腳位,電位);`

---

# 輸入

`pinMode(腳位,INPUT);`
`digitalRead(腳位);`

---

# 按鈕、上拉電阻

`pinMode(腳位,INPUT_PULLUP);`

---

# 變數

+ 布林 boolean
+ 字元 char
+ 數字 
  + 整數 byte,int,long
  + 小數 float,double

---

|變數名稱|範圍                  |
|-------|----------------------|
|boolean|0,1                   |
|char   |-128~127              |
|byte   |0~255                 |
|int    |-32768~32767          |
|long   |-2147483648~2147483647|
|float  |+/-3.4E+38            |
|double |+/-3.4E+38            |

---


# 陣列

> 未來還有很多變數，那就用陣列吧

---

# I<sup>2</sup>C

---

# OLED螢幕

---

# 遊戲流程圖

```c
void setup{
}
void loop{
}
```
