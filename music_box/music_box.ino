// 魔法音樂盒 - 播放音階
// 使用無源蜂鳴器 + 超音波感測器

// 定義蜂鳴器接腳
const int buzzerPin = 8;

// 定義超音波感測器接腳
const int trigPin = 9;
const int echoPin = 10;

// 定義 RGB LED 接腳（共陽極）
const int ledV = 7;   // LED 電源（用數位腳位代替 5V）
const int ledR = 11;
const int ledG = 12;
const int ledB = 13;

// 定義感應距離（公分）
const int minDistance = 5;   // 最近距離
const int maxDistance = 25;  // 最遠距離（約兩個拳頭）

// 狀態變數：記錄上一次是否在範圍內
bool wasInRange = false;

// 定義音符頻率 (Hz)
const int NOTE_C = 262;  // Do
const int NOTE_D = 294;  // Re
const int NOTE_E = 330;  // Mi
const int NOTE_F = 349;  // Fa
const int NOTE_G = 392;  // So

// 定義音符時長 (毫秒)
const int noteDuration = 300;  
const int pauseDuration = 30;  
const int toneVolume = 30;  // 調整音量：實際發聲時間百分比 (1-100)

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledV, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  
  // 設定 LED 電源腳位為 HIGH（當作 5V 使用）
  digitalWrite(ledV, HIGH);
  
  // 初始化 LED（共陽極，全部設為 HIGH = 關閉）
  digitalWrite(ledR, HIGH);
  digitalWrite(ledG, HIGH);
  digitalWrite(ledB, HIGH);
  
  Serial.begin(9600);  // 啟動序列埠
  Serial.println("=== 魔法音樂盒啟動 ===");
  Serial.println("感應範圍：5-25 公分");
  randomSeed(analogRead(0));  // 初始化隨機數種子
  delay(1000);  // 等待 1 秒後開始
}

void loop() {
  // 讀取距離
  long distance = getDistance();
  
  // 顯示偵測到的距離
  Serial.print("偵測距離: ");
  Serial.print(distance);
  Serial.print(" 公分 - ");
  
  // 判斷目前是否在範圍內
  bool isInRange = (distance >= minDistance && distance <= maxDistance);
  
  // 只有從「範圍外」進入「範圍內」時才播放音樂
  if (isInRange && !wasInRange) {
    // 隨機選擇播放哪一首（0 或 1）
    int songChoice = random(2);
    
    Serial.print("✓ 手進入範圍！播放音樂 ");
    Serial.print(songChoice + 1);
    Serial.println(" 號");
    
    // 根據隨機結果播放對應的音樂
    if (songChoice == 0) {
      playMusic1();
    } else {
      playMusic2();
    }
    
    // 更新狀態
    wasInRange = true;
    
  } else if (isInRange && wasInRange) {
    Serial.println("✓ 在範圍內（已播放過，等待離開）");
    delay(100);
    
  } else if (!isInRange && wasInRange) {
    Serial.println("✗ 離開範圍（可再次觸發）");
    wasInRange = false;
    delay(100);
    
  } else {
    Serial.println("✗ 超出範圍");
    delay(100);
  }
}

// 播放第一首音樂的函式：Do Re Mi Fa So So So, So Fa Mi Re Do Do Do
void playMusic1() {
  // 第一句：Do Re Mi Fa So So So（顏色漸變）
  setLedColor(255, 0, 0);     // 紅色
  playNote(NOTE_C);  // Do
  
  setLedColor(255, 100, 0);   // 橘色
  playNote(NOTE_D);  // Re
  
  setLedColor(255, 255, 0);   // 黃色
  playNote(NOTE_E);  // Mi
  
  setLedColor(0, 255, 0);     // 綠色
  playNote(NOTE_F);  // Fa
  
  setLedColor(0, 255, 255);   // 青色
  playNote(NOTE_G);  // So
  
  setLedColor(0, 100, 255);   // 藍色
  playNote(NOTE_G);  // So
  
  setLedColor(150, 0, 255);   // 紫色
  playNote(NOTE_G);  // So
  
  delay(200);  // 兩句之間的停頓
  
  // 第二句：So Fa Mi Re Do Do Do（反向漸變）
  setLedColor(150, 0, 255);   // 紫色
  playNote(NOTE_G);  // So
  
  setLedColor(0, 100, 255);   // 藍色
  playNote(NOTE_F);  // Fa
  
  setLedColor(0, 255, 255);   // 青色
  playNote(NOTE_E);  // Mi
  
  setLedColor(0, 255, 0);     // 綠色
  playNote(NOTE_D);  // Re
  
  setLedColor(255, 255, 0);   // 黃色
  playNote(NOTE_C);  // Do
  
  setLedColor(255, 100, 0);   // 橘色
  playNote(NOTE_C);  // Do
  
  setLedColor(255, 0, 0);     // 紅色
  playNote(NOTE_C);  // Do
  
  setLedColor(0, 0, 0);  // 關閉 LED
}

// 播放第二首音樂的函式：Sol Mi Sol Mi, Do Re Mi Sol Mi
void playMusic2() {
  // 第一句：Sol Mi Sol Mi（顏色變化）
  setLedColor(0, 255, 0);     // 綠色
  playNote(NOTE_G);  // Sol
  
  setLedColor(0, 255, 255);   // 青色
  playNote(NOTE_E);  // Mi
  
  setLedColor(0, 255, 0);     // 綠色
  playNote(NOTE_G);  // Sol
  
  setLedColor(0, 255, 255);   // 青色
  playNote(NOTE_E);  // Mi
  
  delay(200);  // 兩句之間的停頓
  
  // 第二句：Do Re Mi Sol Mi（顏色漸變）
  setLedColor(255, 0, 0);     // 紅色
  playNote(NOTE_C);  // Do
  
  setLedColor(255, 255, 0);   // 黃色
  playNote(NOTE_D);  // Re
  
  setLedColor(0, 255, 0);     // 綠色
  playNote(NOTE_E);  // Mi
  
  setLedColor(0, 255, 255);   // 青色
  playNote(NOTE_G);  // Sol
  
  setLedColor(0, 100, 255);   // 藍色
  playNote(NOTE_E);  // Mi
  
  setLedColor(0, 0, 0);  // 關閉 LED
}

// 播放單一音符的函式（較小音量版本）
void playNote(int frequency) {
  int actualToneDuration = (noteDuration * toneVolume) / 100;
  tone(buzzerPin, frequency, actualToneDuration);
  delay(noteDuration + pauseDuration);
}

// 讀取超音波感測器距離的函式
long getDistance() {
  // 發送超音波脈衝
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // 讀取回波時間
  long duration = pulseIn(echoPin, HIGH, 30000);  // 30ms timeout
  
  // 計算距離（公分）
  // 音速 = 340 m/s，來回距離除以 2
  long distance = duration * 0.034 / 2;
  
  // 如果讀取失敗或超出範圍，回傳 999
  if (distance == 0 || distance > 400) {
    return 999;
  }
  
  return distance;
}

// 設定 RGB LED 顏色的函式（共陽極）
void setLedColor(int red, int green, int blue) {
  // 共陽極：LOW=亮，HIGH=暗
  // 所以要反轉數值
  analogWrite(ledR, 255 - red);
  analogWrite(ledG, 255 - green);
  analogWrite(ledB, 255 - blue);
}

