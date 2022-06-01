#include <Arduino.h> // from Roboruka
#include "RBControl.hpp" // for encoders 
#include "roboruka.h"
using namespace rb;

void setup() {
    rkConfig cfg;
    cfg.motor_enable_failsafe = false;
    cfg.rbcontroller_app_enable = true;
    cfg.motor_max_power_pct = 100;
    cfg.motor_polarity_switch_left = true;
    cfg.motor_polarity_switch_right = true;
    auto &man = Manager::get();
    //man.initSmartServoBus(2, (gpio_num_t)cfg.pins.arm_servos); // nastaveni poctu serv na roboruce 
    man.initSmartServoBus(2, (gpio_num_t)4); // nastaveni poctu serv na roboruce, datovy pin 
    rkSetup(cfg);

    fmt::print("{}'s roboruka '{}' started!\n", cfg.owner, cfg.name);
    fmt::print("Battery at {}%, {}mV\n", rkBatteryPercent(), rkBatteryVoltageMv());

    rkMotorsSetPower(50, 50);
    man.motor(MotorId::M1).drive(-500*110/100, 50);	// right motor 
    man.motor(MotorId::M2).drive(-500, 50);	// left motor
    delay(100);
    //man.motor(MotorId::M1).drive(0, 0);	// nezastavi, dokud nedojede minuly drive  
    //man.motor(MotorId::M2).drive(0, 0);
    rkMotorsSetPower(0, 0); // zastavi ihned, i kdyz probiha drive  	
    int32_t enR = man.motor(MotorId::M1).enc()->value();  // reading encoder
    int32_t enL = man.motor(MotorId::M2).enc()->value();
    fmt::print("enc: {},  {}\n",  enL, enR);


    // rkArmSetServo(3, 60); // parkovaci pozice 
    int k = 80; 
    int IDservo0 = 0;
    int IDservo1 = 1;

    while(true) {     
   
        
        // zacatek nastavovani serv ****************************************************************************************
        if (rkButtonIsPressed(1, true)) {
            k += 10;
            rkArmSetServo(IDservo0, k);
            rkArmSetServo(IDservo1, k);
        }
        if (rkButtonIsPressed(2, true)) { 
            k-=10;
            rkArmSetServo(IDservo0, k);
            rkArmSetServo(IDservo1, k);      
        }
        if (rkButtonIsPressed(3, true)) {
            k += 1;
            rkArmSetServo(IDservo0, k);
            rkArmSetServo(IDservo1, k);
        }
    




        //printf("vision: %i, position: %3.2f, %3.2f  \n", k, rkArmGetServo(IDservo0), rkArmGetServo(IDservo1) ); //konec nastavovani serv *****************
        printf("vision: %i, position: \n", k);
        delay(500);
        //vTaskDelay(pdMS_TO_TICKS(500));  
    }
}



