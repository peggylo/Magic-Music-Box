// 魔法音樂盒 - 播放音階
// 使用無源蜂鳴器 + 超音波感測器

// 定義蜂鳴器接腳
const int buzzerPin = 8;

// 定義超音波感測器接腳
const int trigPin = 9;
const int echoPin = 10;

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
  Serial.begin(9600);  // 啟動序列埠
  Serial.println("=== 魔法音樂盒啟動 ===");
  Serial.println("感應範圍：5-25 公分");
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
    Serial.println("✓ 手進入範圍！播放音樂！");
    
    // 播放完整音樂
    playMusic();
    
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

// 播放完整音樂的函式
void playMusic() {
  // 第一句：Do Re Mi Fa So So So
  playNote(NOTE_C);  // Do
  playNote(NOTE_D);  // Re
  playNote(NOTE_E);  // Mi
  playNote(NOTE_F);  // Fa
  playNote(NOTE_G);  // So
  playNote(NOTE_G);  // So
  playNote(NOTE_G);  // So
  
  delay(200);  // 兩句之間的停頓
  
  // 第二句：So Fa Mi Re Do Do Do
  playNote(NOTE_G);  // So
  playNote(NOTE_F);  // Fa
  playNote(NOTE_E);  // Mi
  playNote(NOTE_D);  // Re
  playNote(NOTE_C);  // Do
  playNote(NOTE_C);  // Do
  playNote(NOTE_C);  // Do
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

