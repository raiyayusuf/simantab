# NIRWANA - Neural Integrated River Warning and Automation

![KoSSMI 2026](https://img.shields.io/badge/KoSSMI-2026-blue)
![Level 4](https://img.shields.io/badge/Level-Ibnu%20Haitham-brightgreen)
![C++](https://img.shields.io/badge/Language-C%2B%2B-orange)
![ESP32](https://img.shields.io/badge/Hardware-ESP32-red)
![Blynk](https://img.shields.io/badge/IoT-Blynk-purple)
![Telegram](https://img.shields.io/badge/Notif-Telegram-blue)

## 📌 Deskripsi Proyek

**NIRWANA (Neural Integrated River Warning and Automation)** adalah sistem berbasis IoT yang dirancang untuk memantau kondisi air secara **real-time** dan memberikan **peringatan dini terhadap potensi banjir**. Sistem ini mengintegrasikan sensor level air, debit air, dan kondisi cuaca untuk menganalisis situasi secara otomatis, kemudian merespons melalui notifikasi **Telegram**, kontrol **Blynk**, serta kontrol perangkat seperti valve dan indikator peringatan.

Seluruh logika sistem berjalan pada **ESP32** secara mandiri tanpa database eksternal, memastikan respon cepat dan real-time. NIRWANA bertujuan meningkatkan kesiapsiagaan dan meminimalkan risiko dampak banjir secara cepat dan akurat.

Proyek ini dikembangkan untuk mengikuti **Kompetisi Sains Siswa Muslim Indonesia (KoSSMI) 2026** pada **Level 4 (Ibnu Haitham)** dengan tema **"Solusi Inovatif Smart City, SDGs, dan Penanggulangan Bencana"**.

## 👥 Tim Pengembang

| Peran | Nama | Institusi |
|-------|------|-----------|
| **Ketua Tim** | Abiyu Zada Abinaya | SMA N 9 Yogyakarta |
| **Anggota** | Aria Agung Jati | SMA N 9 Yogyakarta |
| **Coach** | Raiya Yusuf Priatmojo | GSE - Global Solusi Edukasi |
| **Coach** | Yudha | GSE - Global Solusi Edukasi |

## 🏆 Latar Belakang Lomba

KoSSMI 2026 Level 4 (Ibnu Haitham) menantang peserta untuk merancang dan membangun solusi inovatif yang mendukung:
- **Pengembangan Smart City**
- **Pencapaian Sustainable Development Goals (SDGs)**
- **Upaya Penanggulangan Bencana**

NIRWANA menjawab tantangan tersebut dengan fokus pada **penanggulangan bencana banjir** melalui sistem monitoring dan peringatan dini berbasis IoT, sekaligus berkontribusi pada **SDG 11 (Sustainable Cities and Communities)** dan **SDG 13 (Climate Action)** .

## 🛠️ Tech Stack

- **Microcontroller**: ESP32 (utama)
- **Sensors**: 
  - Ultrasonic HC-SR04 (ketinggian air)
  - Water Flow YF-S201 (debit air)
  - Raindrop Sensor (curah hujan)
- **Actuators**: 
  - Servo SG90 (pintu air darurat)
  - Solenoid Valve 12V (aktif LOW)
  - LED 5mm (hijau, kuning, merah)
- **Display**: OLED 128x64 I2C (SSD1306)
- **Connectivity**: WiFi (ESP32 built-in)
- **IoT Platform**: Blynk (dashboard & kontrol)
- **Notification**: Telegram Bot API
- **Language**: C++ (Arduino Framework)
- **IDE**: Arduino IDE
- **Libraries**: 
  - Blynk
  - UniversalTelegramBot
  - ArduinoJson
  - ESP32Servo
  - Adafruit GFX & SSD1306

## ✨ Fitur Utama

- **Monitoring Real-time**: Mengukur ketinggian air (ultrasonic), debit air (water flow), dan curah hujan (raindrop)
- **Display OLED 128x64**: Menampilkan data sensor secara langsung (ketinggian air, debit, curah hujan, status sistem)
- **Peringatan Dini via Telegram**: Bot Telegram otomatis mengirim notifikasi ke grup/pribadi saat kondisi kritis
- **Dashboard Blynk**: Monitoring dan kontrol dari smartphone (on/off valve, reset indikator)
- **Kontrol Otomatis**: Servo dan solenoid valve merespons kondisi darurat secara mandiri
- **Indikator Lokal**: LED peringatan (hijau/kuning/merah) sebagai alarm visual di lokasi
- **100% ESP32**: Semua logika terpusat di ESP32, tanpa database eksternal untuk respon lebih cepat

## ⚙️ Cara Kerja Sistem

1. **Sensor Ultrasonik** mengukur ketinggian air sungai secara berkala (range 0-5cm, dikonversi jadi level air).
2. **Water Flow Sensor** menghitung debit aliran air via interrupt (pulse counter).
3. **Raindrop Sensor** mendeteksi intensitas curah hujan (analog >3500 = Cerah, <3500 = Hujan).
4. Semua data sensor ditampilkan secara real-time pada **OLED Display**:
   - Baris 1: Ketinggian Air (cm)
   - Baris 2: Status (Normal/Siaga/Bahaya)
   - Baris 3: Debit Air (L/min)
   - Baris 4: Kondisi Cuaca
   - Progress bar visual di bagian bawah
5. Data diproses oleh **ESP32** dengan logika threshold:
   - **Level Normal** (air < 1.5cm): LED hijau menyala, servo posisi aman (tertutup), solenoid OFF
   - **Level Siaga** (air 1.5-2.3cm): LED kuning menyala, notifikasi Telegram dikirim
   - **Level Bahaya** (air ≥ 2.3cm): 
     - LED merah menyala
     - Servo bergerak ke posisi darurat (menutup agar tidak ada penduduk yang mendekati area sungai)
     - Solenoid ON (LOW) untuk membuka valve
     - Notifikasi Telegram darurat dikirim
     - Status "BAHAYA" di OLED
6. Pengguna dapat memantau data real-time dan mengontrol valve manual melalui **Blynk App** (Virtual Pins V0-V3).
7. Semua notifikasi dikirim via **Telegram Bot** ke nomor/grup yang terdaftar.
8. Sistem bekerja mandiri dengan loop pembaruan setiap 400ms dan update Telegram berkala setiap 60 detik.
