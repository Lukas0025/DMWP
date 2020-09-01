/**
 *  _____  __  ____          _______  
 * |  __ \|  \/  \ \        / /  __ \ 
 * | |  | | \  / |\ \  /\  / /| |__) |
 * | |  | | |\/| | \ \/  \/ / |  ___/ 
 * | |__| | |  | |  \  /\  /  | |     
 * |_____/|_|  |_|   \/  \/   |_|
 * 
 * Model spark
 * Hour recurrent prediction model for temperature using temp sensor only
 * 
 * @param uint8_t cur. month    0 - 11
 * @param uint8_t cur. hour     0 - 23
 * @param float   avg temp for last houre
 * 
 * 
 * @version 1.0.0
 * @author Lukáš Plevač <lukasplevac@gmail.com>
 * @date 1.8.2020
 */

#include <stdint.h>
#include <math.h>

extern "C" {
    #include "../lib/Tinn.h"
}

class spark {
    public:
        spark() {
            this->model = xtbuild(135, 150, 100);
        }

        float predict(uint8_t month, uint8_t hour, float temp) {
                        
            float in[135];
            this->in_encode(temp, month, hour, in);

            return this->temp_decode(xtpredict(this->model, in));
        }

        float fit_by_list(uint8_t months[], uint8_t hours[], float temps [], float targets[], unsigned len, float rate) {

            float loss = 0;

            for (unsigned i = 0; i < len; i++) {
                loss += this->fit(months[i], hours[i], temps[i], targets[i], rate);
            }

            return loss / len;

        }

        float fit(uint8_t month, uint8_t hour, float temp, float target, float rate) {
            
            float in[135];
            this->in_encode(temp, month, hour, in);

            float tg[100];
            this->temp_encode(target, tg);

            return xttrain(this->model, in, tg, rate);
        }

    private:
        Tinn model;

        void temp_encode(float temp, float *out) {
            //fill array with zeros
            for (uint8_t i = 0; i < 100; i++) {
                out[i] = 0;
            }

            temp = round(temp) + 49;

            out[(int)temp] = 1;

        }

        void in_encode(float temp, uint8_t month, uint8_t hour, float *out) {
            this->temp_encode(temp, out);

            //encode mouth
            for (uint16_t i = 100; i < 111; i++) {
                out[i] = 0;
            }

            out[100 + month] = 1;

            //hour encode
            for (uint16_t i = 111; i < 135; i++) {
                out[i] = 0;
            }

            out[111 + hour] = 1;

        }

        float temp_decode(float *enc) {
            //find max value
            int maxI = 0;
            for (uint8_t i = 1; i < 100; i++) {
                if (enc[maxI] < enc[i]) {
                    maxI = i;
                }
            }

            return maxI - 49;
        }
};