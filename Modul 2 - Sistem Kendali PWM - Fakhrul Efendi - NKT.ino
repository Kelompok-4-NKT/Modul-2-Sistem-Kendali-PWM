/************************************************/

// Modul Praktikum 2 - Sistem Kendali PWM
// Nama Tim			: NKT
// Nama Anggota 1	: Fakhrul Efendi
// Nama Anggota 2	: Iqbal Syaifullah A.
// Versi Program	: 1.5

/************************************************/
//Deklarasi variabel sensor
int sensor1 = A0;
int sensor2 = A1;
int sensor3 = A2;
int sensor4 = A3;
int sensor5 = A4;
int sensor6 = A5;
int baca_sensor[6];

//Variabel motor
int pinEnable1 = 4;//Harus diset HIGH apabila akan diaktifkan
int pinEnable2 = 2;//Harus diset HIGH apabila akan diaktifkan
//Motor Kiri
int motor_kiri1 = 5;//Input motor driver 1 L293D
int motor_kiri2 = 6;//Input motor driver 2 L293D
//Motor Kanan
int motor_kanan1 = 3;//Input motor driver 3 L293D
int motor_kanan2 = 11;//Input motor driver 4 L293D

//Variabel Bantuan
int x;

//Variabel Bantuan menyimpan memory a.k.a Error Detection Memory
//int LastError = 0;
void setup(){
  //Pinmode input sensor
  pinMode(sensor1, INPUT);//Set pin A0 sebagai input
  pinMode(sensor2, INPUT);//Set pin A1 sebagai input
  pinMode(sensor3, INPUT);//Set pin A2 sebagai input
  pinMode(sensor4, INPUT);//Set pin A3 sebagai input
  pinMode(sensor5, INPUT);//Set pin A4 sebagai input
  pinMode(sensor6, INPUT);//Set pin A5 sebagai input
  //Pinmode output motor
  pinMode(pinEnable1, OUTPUT);//Set pin 4 sebagai output
  pinMode(pinEnable2, OUTPUT);//Set pin 2 sebagai output
  pinMode(motor_kiri1, OUTPUT);//Set pin 5 sebagai output
  pinMode(motor_kiri2, OUTPUT);//Set pin 6 sebagai output
  pinMode(motor_kanan1, OUTPUT);//Set pin 3 sebagai output
  pinMode(motor_kanan2, OUTPUT);//Set pin 11 sebagai output
  //Inisialisasi komunikasi serial
  Serial.begin(9600);//Baud Rate standar 9600
  }

  void readsensor(){//Fungsi untuk membaca sensor kemudian menyimpan pada array
    baca_sensor[0] = analogRead(sensor1);
    baca_sensor[1] = analogRead(sensor2);
    baca_sensor[2] = analogRead(sensor3);
    baca_sensor[3] = analogRead(sensor4);
    baca_sensor[4] = analogRead(sensor5);
    baca_sensor[5] = analogRead(sensor6);
    
    //Menampilkan data sensor ke Serial Monitor
    for (x=0; x<=5; x++){
      Serial.println(baca_sensor[x]);
      Serial.print("Nilai sensor [x] : ");
      //Serial.print(LastError);
    }
  }
  void loop(){
    //Nilai terendah photodiode = 33 (Paling Gelap)
    //Nilai tertinggi photodiode = 689 (Paling Terang)
    readsensor();
    //Sensor 1 dan 2 mendeteksi gelap, sisanya terang : Duty cycle 0% motor kiri, 50% motor kanan
    if (baca_sensor[0] < 34 && baca_sensor[1] < 34 && 
        baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
        baca_sensor[4] > 34 && baca_sensor[5] > 34 ){
      digitalWrite(pinEnable1, HIGH);
      //analogWrit(pin, value 0-255)
      analogWrite(motor_kiri1, 0);
      analogWrite(motor_kiri2, 0);
      
      digitalWrite(pinEnable2, HIGH);
      analogWrite(motor_kanan1, 127);
      analogWrite(motor_kanan2, 0);
    }
    //Sensor 2 dan 3 mendeteksi gelap, sisanya terang : Duty cycle 20% motor kiri, 50% motor kanan
    if (baca_sensor[0] > 34 && baca_sensor[1] < 34 && 
        baca_sensor[2] < 34 && baca_sensor[3] > 34 && 
        baca_sensor[4] > 34 && baca_sensor[5] > 34 ){
      digitalWrite(pinEnable1, HIGH);
      analogWrite(motor_kiri1, 0.2*255);
      analogWrite(motor_kiri2, 0);
      
      digitalWrite(pinEnable2, HIGH);
      analogWrite(motor_kanan1, 127);
      analogWrite(motor_kanan2, 0);
    }
    //Sensor 3 dan 4 mendeteksi gelap, sisanya terang : Duty cycle 60% pada kedua motor (kedua motor aktif)
    if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
        baca_sensor[2] < 34 && baca_sensor[3] < 34 && 
        baca_sensor[4] > 34 && baca_sensor[5] > 34 ){
      digitalWrite(pinEnable1, HIGH);
      analogWrite(motor_kiri1, 0.6*255);
      analogWrite(motor_kiri2, 0);
      
      digitalWrite(pinEnable2, HIGH);
      analogWrite(motor_kanan1, 0.6*255);
      analogWrite(motor_kanan2, 0);
    }
    //Sensor 4 dan 5 mendeteksi gelap, sisanya terang : Duty cycle 50% motor kiri, 20% motor kanan
    if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
        baca_sensor[2] > 34 && baca_sensor[3] < 34 && 
        baca_sensor[4] < 34 && baca_sensor[5] > 34 ){
      digitalWrite(pinEnable1, HIGH);
      analogWrite(motor_kiri1, 0.5*255);
      analogWrite(motor_kiri2, 0);
      
      digitalWrite(pinEnable2, HIGH);
      analogWrite(motor_kanan1, 0.2*255);
      analogWrite(motor_kanan2, 0);
    }
    //Sensor 5 dan 6 mendeteksi gelap, sisanya terang : Duty cycle 50% Motor kiri, 0% motor kanan
    if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
        baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
        baca_sensor[4] < 34 && baca_sensor[5] < 34 ){
      digitalWrite(pinEnable1, HIGH);
      analogWrite(motor_kiri1, 255/2);
      analogWrite(motor_kiri2, 0);
      
      digitalWrite(pinEnable2, HIGH);
      analogWrite(motor_kanan1, 0);
      analogWrite(motor_kanan2, 0);
    }
    //Semua sensor mendeteksi terang : Duty cycle kedua motor 0% (semua motor mati)
    if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
        baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
        baca_sensor[4] > 34 && baca_sensor[5] > 34 ){
      digitalWrite(pinEnable1, HIGH);
      analogWrite(motor_kiri1, 0);
      analogWrite(motor_kiri2, 0);
      
      digitalWrite(pinEnable2, HIGH);
      analogWrite(motor_kanan1, 0);
      analogWrite(motor_kanan2, 0);
    }
	/*  
    //Studi Kasus 2 : Error Condition -> 1 sensor terbaca
    //Sensor 1 dan 2 mendeteksi gelap, sisanya terang : Duty cycle 0% motor kiri, 50% motor kanan
    if (baca_sensor[0] < 34 && baca_sensor[1] > 34 && 
        baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
        baca_sensor[4] > 34 && baca_sensor[5] > 34 ){
		LastError = 1; //Kondisi sensor 1 saja yang membaca gelap
    //Jalankan fungsi motor terakhir
      digitalWrite(pinEnable1, HIGH);
      //analogWrit(pin, value 0-255)
      analogWrite(motor_kiri1, 0);
      analogWrite(motor_kiri2, 0);
      
      digitalWrite(pinEnable2, HIGH);
      analogWrite(motor_kanan1, 127);
      analogWrite(motor_kanan2, 0);
    }
    //Sensor 2 dan 3 mendeteksi gelap, sisanya terang : Duty cycle 20% motor kiri, 50% motor kanan
    if (baca_sensor[0] > 34 && baca_sensor[1] < 34 && 
        baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
        baca_sensor[4] > 34 && baca_sensor[5] > 34 ){
		LastError = 2; //Kondisi sensor 2 saja yang membaca gelap
    //Jalankan fungsi motor terakhir
      digitalWrite(pinEnable1, HIGH);
      analogWrite(motor_kiri1, 0.2*255);
      analogWrite(motor_kiri2, 0);
      
      digitalWrite(pinEnable2, HIGH);
      analogWrite(motor_kanan1, 127);
      analogWrite(motor_kanan2, 0);
 	}
    //Sensor 3 dan 4 mendeteksi gelap, sisanya terang : Duty cycle 60% pada kedua motor (kedua motor aktif)
    if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
        baca_sensor[2] < 34 && baca_sensor[3] > 34 && 
        baca_sensor[4] > 34 && baca_sensor[5] > 34 ){
		LastError = 3; //Kondisi sensor 3 saja yang membaca gelap
    //Jalankan fungsi motor terakhir
      digitalWrite(pinEnable1, HIGH);
      analogWrite(motor_kiri1, 0.6*255);
      analogWrite(motor_kiri2, 0);
      
      digitalWrite(pinEnable2, HIGH);
      analogWrite(motor_kanan1, 0.6*255);
      analogWrite(motor_kanan2, 0);
    }
    //Sensor 4 dan 5 mendeteksi gelap, sisanya terang : Duty cycle 50% motor kiri, 20% motor kanan
    if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
        baca_sensor[2] > 34 && baca_sensor[3] < 34 && 
        baca_sensor[4] > 34 && baca_sensor[5] > 34 ){
      	LastError = 4;//Kondisi sensor 4 saja yang membaca gelap
      digitalWrite(pinEnable1, HIGH);
      analogWrite(motor_kiri1, 0.5*255);
      analogWrite(motor_kiri2, 0);
      
      digitalWrite(pinEnable2, HIGH);
      analogWrite(motor_kanan1, 0.2*255);
      analogWrite(motor_kanan2, 0);
    }
    //Sensor 5 dan 6 mendeteksi gelap, sisanya terang : Duty cycle 50% Motor kiri, 0% motor kanan
    if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
        baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
        baca_sensor[4] < 34 && baca_sensor[5] > 34 ){
      	LastError = 5;//Kondisi sensor 4 saja yang membaca gelap
      digitalWrite(pinEnable1, HIGH);
      analogWrite(motor_kiri1, 0.5*255);
      analogWrite(motor_kiri2, 0);
      
      digitalWrite(pinEnable2, HIGH);
      analogWrite(motor_kanan1, 0);
      analogWrite(motor_kanan2, 0);
    }
    //Semua sensor mendeteksi terang : Duty cycle kedua motor 0% (semua motor mati)
    if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
        baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
        baca_sensor[4] > 34 && baca_sensor[5] < 34 ){
      	LastError = 5;//Kondisi sensor 5 saja yang membaca gelap
      digitalWrite(pinEnable1, HIGH);
      analogWrite(motor_kiri1, 0);
      analogWrite(motor_kiri2, 0);
      
      digitalWrite(pinEnable2, HIGH);
      analogWrite(motor_kanan1, 0);
      analogWrite(motor_kanan2, 0);
    }
    //Semua sensor mendeteksi terang : Duty cycle kedua motor 0% (semua motor mati)
    if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
        baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
        baca_sensor[4] > 34 && baca_sensor[5] > 34 ){
      	LastError = 6;//Kondisi semua sensor tidak membaca gelap
      digitalWrite(pinEnable1, HIGH);
      analogWrite(motor_kiri1, 0);
      analogWrite(motor_kiri2, 0);
      
      digitalWrite(pinEnable2, HIGH);
      analogWrite(motor_kanan1, 0);
      analogWrite(motor_kanan2, 0);
    }*/
  }