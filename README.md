# 魔法音樂盒 Magic Music Box 🎵

Arduino 音樂盒專案，使用超音波感測器控制蜂鳴器播放音樂。

## 功能 Features

- 🎶 播放音階 (Play Scale)：Do Re Mi Fa So So So, So Fa Mi Re Do Do Do
- 👋 手勢控制 (Gesture Control)：手靠近時觸發播放
- 📊 即時監控 (Real-time Monitor)：序列埠顯示偵測距離

## 硬體 Hardware

- Arduino Uno
- 無源蜂鳴器模組 (Passive Buzzer Module)：三線 S/V/G
- 超音波感測器 (Ultrasonic Sensor)：HC-SR04

## 接線 Wiring

**蜂鳴器 Buzzer**
- S → Pin 8
- V → 5V
- G → GND

**超音波感測器 Ultrasonic**
- VCC → 5V
- Trig → Pin 9
- Echo → Pin 10
- GND → GND

## 使用 Usage

1. 連接硬體
2. 上傳程式到 Arduino
3. 手放在感測器前方 5-25 公分
4. 自動播放音樂

## 上傳程式 Upload

```bash
cd music_box
arduino-cli compile --fqbn arduino:avr:uno .
arduino-cli upload -p /dev/cu.usbserial-1120 --fqbn arduino:avr:uno .
```

## 參數調整 Settings

- `noteDuration`：音符長度 (Note Duration)
- `toneVolume`：音量 (Volume, 1-100)
- `minDistance` / `maxDistance`：感應距離 (Detection Range)
