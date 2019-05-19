/*MIT License
Copyright (c) 2018 imliubo
Github  https://github.com/imliubo
Website https://www.makingfun.xyz
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"

/************************
 *   STATIC VARIABLES   *
 ************************/
os_timer_t blue_led_timer;
os_timer_t key_read_timer;

/************************
 *   STATIC FUNCTIONS   *
 ************************/

/**
 * LED��ʱ��ת������1s״̬��תһ��
 */
static void ICACHE_FLASH_ATTR
blue_led_timer_toggle(void){
	os_timer_disarm(&blue_led_timer);//ȡ����ʱ��
	uint32 status = GPIO_INPUT_GET(GPIO_ID_PIN(2));//��ȡ���ƹܽ�״̬
	GPIO_OUTPUT_SET(GPIO_ID_PIN(2),!status);//ȡ��ʵ�����ƹܽŵ�ƽ��ת���Ӷ�ʵ���������
	os_timer_arm(&blue_led_timer, 1000, true);//ʹ�ܶ�ʱ��
}

/**
 * ������ʱ״̬��ȡ������10ms��ȡһ�ΰ���״̬
 */
static void ICACHE_FLASH_ATTR
key_read_value(void){
	os_timer_disarm(&key_read_timer);//ȡ����ʱ��
	if(GPIO_INPUT_GET(GPIO_ID_PIN(14)) == 0x00){//����������£��͵�ƽ
		os_delay_us(20000);//��ʱ20ms����
		if(GPIO_INPUT_GET(GPIO_ID_PIN(14)) == 0x00){//�ٴ��ж�״̬����ֹ��
			uint32 status = GPIO_INPUT_GET(GPIO_ID_PIN(4));//��ȡ��ǰ�ܽ�״̬
			GPIO_OUTPUT_SET(GPIO_ID_PIN(4),!status);//ȡ��ʵ�ֹܽŵ�ƽ��ת
			while(GPIO_INPUT_GET(GPIO_ID_PIN(14)));//�ȴ������ɿ�
		}
	}
	os_timer_arm(&key_read_timer, 10, true);//ʹ�ܶ�ʱ��
}

/**
 *�����жϷ��������ߵ�ƽ����
 */
static void ICACHE_FLASH_ATTR
key_intr_handler(void){
	uint32 gpio_status = GPIO_REG_READ(GPIO_STATUS_ADDRESS);//��ȡGPIO�Ĵ���״̬����ȡ�ж���Ϣ
	uint8 level = 0;
	GPIO_REG_WRITE(GPIO_STATUS_ADDRESS,gpio_status);//����ж���Ϣ
	if(gpio_status & (BIT(15))){//�ж��Ƿ���gpio15
		if(GPIO_INPUT_GET(15)){//����Ǹߵ�ƽ
			GPIO_OUTPUT_SET(GPIO_ID_PIN(5),0);//Ϩ����
			GPIO_OUTPUT_SET(GPIO_ID_PIN(12),1);//Ϩ��Ƶ�
			GPIO_OUTPUT_SET(GPIO_ID_PIN(4),0);//Ϩ���̵�
			GPIO_OUTPUT_SET(GPIO_ID_PIN(2),0);//Ϩ������
			os_timer_disarm(&key_read_timer);//ȡ��������ʱ��
			os_timer_disarm(&blue_led_timer);//ȡ�����ƶ�ʱ��ת��ʱ��
		}else{//����ǵ͵�ƽ
			//��������
		}
	}else{//�������gpio15
		//��������
	}
}

/************************
 *   GLOBAL FUNCTIONS   *
 ************************/
void ICACHE_FLASH_ATTR
gpio_test(void){

	gpio_init();//��ʼ��GPIO

	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO5_U,FUNC_GPIO5);//���
	GPIO_OUTPUT_SET(GPIO_ID_PIN(5),1);//�ߵ�ƽ����������

	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U,FUNC_GPIO12);//�Ƶ�
	GPIO_OUTPUT_SET(GPIO_ID_PIN(12),0);//�͵�ƽ����������

	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U,FUNC_GPIO2);//����
	os_timer_disarm(&blue_led_timer);
	os_timer_setfn(&blue_led_timer, (os_timer_func_t *) blue_led_timer_toggle,NULL);//��ʱ�ص�����
	os_timer_arm(&blue_led_timer, 1000, true);//����ʱ��Ϊ1s

	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO4_U,FUNC_GPIO4);//�̵ƣ�������������ת
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTMS_U,FUNC_GPIO14);//����
	GPIO_DIS_OUTPUT(GPIO_ID_PIN(14));//��������Ϊ����ģʽ
	PIN_PULLUP_EN(PERIPHS_IO_MUX_MTMS_U);//��������ʹ��
	os_timer_disarm(&key_read_timer);
	os_timer_setfn(&key_read_timer, (os_timer_func_t *) key_read_value,NULL);//��ʱ�ص�����
	os_timer_arm(&key_read_timer, 10, true);//����ʱ��Ϊ10ms

	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDO_U,FUNC_GPIO15);//�жϰ���
	GPIO_DIS_OUTPUT(GPIO_ID_PIN(15));//����Ϊ����ģʽ
	PIN_PULLUP_DIS(PERIPHS_IO_MUX_MTDO_U);//����ʹ��
	ETS_GPIO_INTR_DISABLE();//��ֹ����GPIO�ж�
	ETS_GPIO_INTR_ATTACH((void *)key_intr_handler,NULL);//ע��GPIO�жϴ�����
	gpio_pin_intr_state_set(GPIO_ID_PIN(15),GPIO_PIN_INTR_HILEVEL);//���øߵ�ƽ�����ж�
	ETS_GPIO_INTR_ENABLE();//ʹ������GPIO�ж�

}


