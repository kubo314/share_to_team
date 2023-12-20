#include "D_Main.h"
#include "D_I2C.h"
#include "D_SIO.h"
#include "D_EIO.h"

void user_main(void) {
    int current_sensor_values[9];

    int plus = 90;
    int minus = 100;
    int straight = 75;
    
    int shikii = 300;

    while (TRUE) {
        //配列にすべて代入してループの中でセンサーの値が変わるのを防ぐ
        //gAD[CN2] と gAD[1]は同じ
        for (int i = 4; i < 9; i++) {
            current_sensor_values[i] = gAD[i];
        }

        //前のセンサーで判定
        if (current_sensor_values[CN7] >= shikii && current_sensor_values[CN9] <= shikii) {
            motor(minus, plus);
        } else if (current_sensor_values[CN7] <= shikii && current_sensor_values[CN9] >= shikii) {
            motor(plus, minus);
        } else {
            motor(straight, straight);
        }

        //後ろのセンサーで判定
        //後ろのセンサーは補助なのでまっすぐ進む処理は入れない
        if (current_sensor_values[CN5] >= shikii && current_sensor_values[CN6] <= shikii) {
            motor(minus, plus);
        } else if (current_sensor_values[CN5] <= shikii && current_sensor_values[CN6] >= shikii) {
            motor(plus, minus);
        }
    }
}