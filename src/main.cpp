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
    man.initSmartServoBus(2, (gpio_num_t)4); // nastaveni poctu serv na roboruce 
    rkSetup(cfg);

    fmt::print("{}'s roboruka '{}' started!\n", cfg.owner, cfg.name);
    fmt::print("Battery at {}%, {}mV\n", rkBatteryPercent(), rkBatteryVoltageMv());

    // rkArmSetServo(3, 60); // parkovaci pozice 
    int k = 0; 
    int IDservo = 1;

    while(true) {     
   
        
        // zacatek nastavovani serv ****************************************************************************************
        if (rkButtonIsPressed(1)) {
            k += 10;
            rkArmSetServo(IDservo, k);
        }
        if (rkButtonIsPressed(2)) { 
            k-=10;
            rkArmSetServo(IDservo, k);      
        }
        if (rkButtonIsPressed(3)) {
            k += 1;
            rkArmSetServo(IDservo, k);
        }
       
        fmt::print("vision: {}, position: {}\n", k, rkArmGetServo(IDservo) ); //konec nastavovani serv *****************
        
        
        vTaskDelay(pdMS_TO_TICKS(500));  
    }
}


