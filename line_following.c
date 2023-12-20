#include "D_Main.h"
#include "D_I2C.h"
#include "D_SIO.h"
#include "D_EIO.h"

void user_main(void) {
    int current_sensor_values[9];

    int plus = 90;
    int minus = -100;
    int straight = 75;
    
    int shikii = 300;

    int i;

    while (TRUE) {
        //配列にすべて代入してループの中でセンサーの値が変わるのを防ぐ
        //gAD[CN2] と gAD[1]は同じ
        for (i = 2; i < 9; i++) {
            current_sensor_values[i] = gAD[i];
        }
        
        //T字路
        //行き
        if (current_sensor_values[CN7] <= shikii || current_sensor_values[CN5] <= shikii) {
            if (current_sensor_values[CN8] <= shikii) {
                motor(minus, plus);
                wait_ms(300);
                continue;
            }
        }
        //帰り
        if (current_sensor_values[CN7] <= shikii || current_sensor_values[CN5] <= shikii) {
            if (current_sensor_values[CN9] <= shikii || current_sensor_values[CN6] <= shikii) {
                motor(plus, minus);
                wait_ms(300);
                continue;
            }
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
        //後ろのセンサーは補助なので直進の処理は入れない
        if (current_sensor_values[CN5] >= shikii && current_sensor_values[CN6] <= shikii) {
            motor(minus, plus);
        } else if (current_sensor_values[CN5] <= shikii && current_sensor_values[CN6] >= shikii) {
            motor(plus, minus);
        }

        //タワーでUターン
        //CN3, CN4が他の値と干渉している?ためコメントアウト
        /*
        if (current_sensor_values[CN3] >= shikii || current_sensor_values[CN4] >= shikii) {
            motor(0, 0);
            wait_ms(100);
            motor(-75, -75);
            wait_ms(400);
            motor(100, -100);
            wait_ms(600);
        }
        */
    }
}