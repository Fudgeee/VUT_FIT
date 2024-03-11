#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "esp_log.h"
#include "esp_err.h"
#include "freertos/task.h"
#include "sdkconfig.h"
#include "font8x8_basic.h"
#include "ssd1306.h"
#include "freertos/FreeRTOS.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

static esp_adc_cal_characteristics_t *adc_chars;
static const adc_channel_t channel = ADC_CHANNEL_0;
static const adc_bits_width_t width = ADC_WIDTH_BIT_12;
static const adc_atten_t atten = ADC_ATTEN_DB_11;
static const adc_unit_t unit = ADC_UNIT_1;

void i2c_master_init(){ // init esp pins
	i2c_config_t i2c_config = {
		.mode = I2C_MODE_MASTER,
		.sda_io_num = GPIO_NUM_21,
		.scl_io_num = GPIO_NUM_22,
		.sda_pullup_en = GPIO_PULLUP_ENABLE,
		.scl_pullup_en = GPIO_PULLUP_ENABLE,
		.master.clk_speed = 1000000
	};
	i2c_param_config(I2C_NUM_0, &i2c_config);
	i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0);
}

void ssd1306_init(){ // init display
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (OLED_I2C_ADDRESS << 1) | I2C_MASTER_WRITE, true);
	i2c_master_write_byte(cmd, OLED_CONTROL_BYTE_CMD_STREAM, true);
	i2c_master_write_byte(cmd, OLED_CMD_SET_CHARGE_PUMP, true);
	i2c_master_write_byte(cmd, 0x14, true);
	i2c_master_write_byte(cmd, OLED_CMD_SET_SEGMENT_REMAP, true);
	i2c_master_write_byte(cmd, OLED_CMD_SET_COM_SCAN_MODE, true);
	i2c_master_write_byte(cmd, OLED_CMD_DISPLAY_ON, true);
	i2c_master_stop(cmd);
	esp_err_t espRc = i2c_master_cmd_begin(I2C_NUM_0, cmd, 10/portTICK_PERIOD_MS);
	i2c_cmd_link_delete(cmd);
}

void task_display_text(char *arg_text) {
	char *text = arg_text;
	uint8_t text_length = strlen(text);
	i2c_cmd_handle_t cmd;
	uint8_t cur_page = 0;
	cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (OLED_I2C_ADDRESS << 1) | I2C_MASTER_WRITE, true);
	i2c_master_write_byte(cmd, OLED_CONTROL_BYTE_CMD_STREAM, true);
	i2c_master_write_byte(cmd, 0x00, true);
	i2c_master_write_byte(cmd, 0x10, true);
	i2c_master_write_byte(cmd, 0xB0 | cur_page, true);
	i2c_master_stop(cmd);
	i2c_master_cmd_begin(I2C_NUM_0, cmd, 10/portTICK_PERIOD_MS);
	i2c_cmd_link_delete(cmd);
	for (uint8_t i = 0; i < text_length; i++) {
		if (text[i] != '\n') {
			cmd = i2c_cmd_link_create();
			i2c_master_start(cmd);
			i2c_master_write_byte(cmd, (OLED_I2C_ADDRESS << 1) | I2C_MASTER_WRITE, true);
			i2c_master_write_byte(cmd, OLED_CONTROL_BYTE_DATA_STREAM, true);
			i2c_master_write(cmd, ASCII[(uint8_t)text[i]], 8, true);
			i2c_master_stop(cmd);
			i2c_master_cmd_begin(I2C_NUM_0, cmd, 10/portTICK_PERIOD_MS);
			i2c_cmd_link_delete(cmd);
		}
		else {
			cmd = i2c_cmd_link_create();
			i2c_master_start(cmd);
			i2c_master_write_byte(cmd, (OLED_I2C_ADDRESS << 1) | I2C_MASTER_WRITE, true);
			i2c_master_write_byte(cmd, OLED_CONTROL_BYTE_CMD_STREAM, true);
			i2c_master_write_byte(cmd, 0x00, true);
			i2c_master_write_byte(cmd, 0x10, true);
			i2c_master_write_byte(cmd, 0xB0 | ++cur_page, true);
			i2c_master_stop(cmd);
			i2c_master_cmd_begin(I2C_NUM_0, cmd, 10/portTICK_PERIOD_MS);
			i2c_cmd_link_delete(cmd);
		} 
	}
	vTaskDelete(NULL);
}

void app_main(){
	i2c_master_init(); // init esp pins
	ssd1306_init(); // init display
    adc1_config_width(width);
    adc1_config_channel_atten(channel, atten);
    adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_value_t val_type = esp_adc_cal_characterize(unit, atten, width, 1100, adc_chars);
	char bpm_vypis[200];
	bool heartbeat = true;
	int bpm_counter = 0; // number of heartbeats per 3 seconds
	int counter = 0; // 50ms * 60 = 3 seconds
	int bpm = 0;
	int prev_bpm = 0; // previous bpm
	int prev_prev_bpm = 0;
	int prev_prev_prev_bpm = 0;
	int prev_prev_prev_prev_bpm = 0;

    while (1) {
        uint32_t adc_reading = 0;
        //Multisampling
        for (int i = 0; i < 256; i++) { // number of samples = 256
            adc_reading += adc1_get_raw((adc1_channel_t)channel);
        }
        adc_reading /= 256; // normalizing sample
        // Convert adc_reading to voltage [mV]
        uint32_t voltage = esp_adc_cal_raw_to_voltage(adc_reading, adc_chars);
		if(voltage >= 2595 && heartbeat == true){
			bpm_counter++;
			heartbeat = false;
		}
		else if(voltage <= 2565 && heartbeat == false){
			heartbeat = true;
		}
		counter++; // 50ms * 60 = 3 seconds
		if(counter > 60){ 
			counter = 0;
		}
		if(counter == 0){ // counting bpm every 3 seconds so need to multiply by 20 to get hearthbeats per 1 minute and averaging with 4 previous values and actual
			if(prev_bpm != 0 && prev_prev_bpm != 0 && prev_prev_prev_bpm != 0 && prev_prev_prev_prev_bpm != 0){
				bpm = ((bpm_counter * 20) + prev_bpm + prev_prev_bpm + prev_prev_prev_bpm + prev_prev_prev_prev_bpm) / 5;
			}
			else if(prev_bpm != 0 && prev_prev_bpm != 0 && prev_prev_prev_bpm != 0){
				bpm = ((bpm_counter * 20) + prev_bpm + prev_prev_bpm + prev_prev_prev_bpm) / 4;
			}
			else if(prev_bpm != 0 && prev_prev_bpm != 0){  
				bpm = ((bpm_counter * 20) + prev_bpm + prev_prev_bpm) / 3;
			}
			else if(prev_bpm != 0){
				bpm = ((bpm_counter * 20) + prev_bpm) / 2;
			}
			else{
				bpm = bpm_counter * 20;
			} 
			sprintf(bpm_vypis,"                \n                \n      BPM:      \n                \n                \n       %d       \n                \n                ",bpm);
			xTaskCreate(&task_display_text, "task_display_text",  2048, bpm_vypis, 6, NULL); // output on display       			
			prev_prev_prev_prev_bpm = prev_prev_prev_bpm;
			prev_prev_prev_bpm = prev_prev_bpm;
			prev_prev_bpm = prev_bpm;
			prev_bpm = bpm;
			bpm = 0;
			bpm_counter = 0;
		}
		vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}