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
#include "modules/tcpServerClient.h"

/*********************
 *      INCLUDES
 *********************/
#include "modules/AP_Web_SmartConfig_Airkiss_test.h"
#include "Utils/cJSON.h"
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/************************
 *   STATIC VARIABLES   *
 ************************/

/**********************
 *      MACROS
 **********************/


/****************************
 *   TCP CLIENT FUNCTIONS   *
 ****************************/

/**********************************
 *  TCP CLIENT STATIC PROTOTYPES  *
 **********************************/
static void tcp_client_sent_cb(void *arg);
static void tcp_client_recv_cb(void *arg,char *pdata,unsigned short length);
static void tcp_client_recon_cb(void *arg,sint8 error);
static void tcp_client_discon_cb(void *arg);
static void tcp_client_connect_cb(void *arg);

/**********************************
 *   TCP CLIENT STATIC VARIABLES  *
 **********************************/

/**********************************
 *   TCP CLIENT STATIC FUNCTIONS  *
 **********************************/

/**
 * TCP Client���ݷ��ͻص�����
 */
static void ICACHE_FLASH_ATTR
tcp_client_sent_cb(void *arg){
	os_printf("tcp client send data successful\r\n");
}

/**
 * TCP Client���ݽ��ջص��������������⴦���յ�Server����������
 */
static void ICACHE_FLASH_ATTR
tcp_client_recv_cb(void *arg,char *pdata,unsigned short len){
	os_printf("tcp client receive tcp server data\r\n");
	os_printf("length: %d \r\ndata: %s\r\n",len,pdata);

	//TO DO

	/**
	 *process the receive data
	 */

}

/**
 * TCP Client�����ص������������ڴ˺������������Ӵ���
 */
static void ICACHE_FLASH_ATTR
tcp_client_recon_cb(void *arg,sint8 error){
	os_printf("tcp client connect tcp server error %d\r\n",error);
}

/**
 * TCP Client�Ͽ����ӻص�����
 */
static void ICACHE_FLASH_ATTR
tcp_client_discon_cb(void *arg){
	os_printf("tcp client disconnect tcp server successful\r\n");
}

/**
 * TCP Client���ӳɹ��ص�����
 */
static void ICACHE_FLASH_ATTR
tcp_client_connect_cb(void *arg){
	struct espconn *pespconn = arg;

	os_printf("tcp client connect tcp server successful\r\n");
	espconn_regist_recvcb(pespconn,tcp_client_recv_cb);//ע��������ݻص�����
	espconn_regist_sentcb(pespconn,tcp_client_sent_cb);//ע�����ݷ�����ɻص�����
	espconn_regist_disconcb(pespconn,tcp_client_discon_cb);//ע��Ͽ����ӻص�����

}

/**********************************
 *   TCP CLIENT GLOBAL FUNCTIONS  *
 **********************************/
/**
 * TCP Client��ʱ�������ݻص�����
 */
sint8 ICACHE_FLASH_ATTR
tcp_client_send_data(struct espconn *espconn,uint8 *pdata,uint16 length){
    if (espconn == NULL) {
    	return ESPCONN_ARG;
    }
    espconn_send(espconn,pdata,length);
}

/**
 * TCP Client��ʼ������
 * @remote_ip    Ҫ���ӵ�TCP Server IP��ַ
 * @local_ip     ESP8266 IP��ַ
 * @remote_port  Ҫ���ӵ�TCP Server�˿ں�
 */
void ICACHE_FLASH_ATTR
tcp_client_init(struct espconn *espconn,uint8 *remote_ip,struct ip_addr *local_ip, int remote_port){

	uint32 server_ip = ipaddr_addr(remote_ip);

	os_printf("tcp client connect to tcp server\r\n");
	espconn->proto.tcp = (esp_tcp *)os_zalloc(sizeof(esp_tcp));
	espconn->type = ESPCONN_TCP;

	os_memcpy(espconn->proto.tcp->remote_ip,&server_ip,4);//����Ҫ���ӵ�Server IP��ַ
	espconn->proto.tcp->remote_port = remote_port;//����Ҫ���ӵ�Server �˿ں�
	os_memcpy(espconn->proto.tcp->local_ip,local_ip,4);//���ñ���IP��ַ
	espconn->proto.tcp->local_port = espconn_port();//���ñ��ض˿ں�

	espconn_regist_connectcb(espconn,tcp_client_connect_cb);//ע�����ӳɹ��ص�����
	espconn_regist_reconcb(espconn,tcp_client_recon_cb);//ע������������ӻص�����

	espconn_connect(espconn);//Client����Server
}



/****************************
 *   TCP SERVER FUNCTIONS   *
 ****************************/
/**********************************
 *  TCP SERVER STATIC PROTOTYPES  *
 **********************************/
static void tcp_server_sent_cb(void *arg);
static void tcp_server_recv_cb(void *arg,char *pdata,unsigned short length);
static void tcp_server_recon_cb(void *arg,sint8 error);
static void tcp_server_discon_cb(void *arg);
static void tcp_server_listen_cb(void *arg);

/**********************************
 *   TCP SERVER STATIC VARIABLES  *
 **********************************/


/**********************************
 *   TCP server STATIC FUNCTIONS  *
 **********************************/

/**
 * TCP Server���ݷ��ͻص�����
 */
static void ICACHE_FLASH_ATTR
tcp_server_sent_cb(void *arg){
	os_printf("tcp server send data successful\r\n");

}

/**
 * TCP Server���ݽ��ջص��������������⴦���յ�Client����������
 */
static void ICACHE_FLASH_ATTR
tcp_server_recv_cb(void *arg,char *pdata,unsigned short len){
	os_printf("tcp server receive tcp client data\r\n");
	os_printf("length: %d \r\ndata: %s\r\n",len,pdata);

	//TO DO

	/**
	 *process the receive data
	 */
	AP_recv_data_process(pdata);
}

/**
 * TCP Server�����ص������������ڴ˺������������Ӵ���
 */
static void ICACHE_FLASH_ATTR
tcp_server_recon_cb(void *arg,sint8 error){
	os_printf("tcp server connect tcp client error %d\r\n",error);
}

/**
 * TCP Server�Ͽ����ӻص�����
 */
static void ICACHE_FLASH_ATTR
tcp_server_discon_cb(void *arg){
	os_printf("tcp server disconnect tcp client successful\r\n");
}

/**
 * TCP Server����Client���ӻص�����
 */
static void ICACHE_FLASH_ATTR
tcp_server_listen_cb(void *arg){
	struct espconn *pespconn = arg;

	os_printf("tcp server have tcp client connect\r\n");
	espconn_regist_recvcb(pespconn,tcp_server_recv_cb);//ע���յ����ݻص�����
	espconn_regist_sentcb(pespconn,tcp_server_sent_cb);//ע�ᷢ�������ݻص�����
	espconn_regist_disconcb(pespconn,tcp_server_discon_cb);//ע��Ͽ����ӻص�����

}

/**********************************
 *   TCP CLIENT GLOBAL FUNCTIONS  *
 **********************************/

/**
 * TCP Server��ʱ�������ݻص�����
 */
sint8 ICACHE_FLASH_ATTR
tcp_server_send_data(struct espconn *espconn,uint8 *pdata,uint16 length){
    if (espconn == NULL) {
    	return ESPCONN_ARG;
    }

	espconn_send(espconn,pdata,length);
}

/**
 * TCP Server��ʼ������
 * @local_port ���ؼ����˿ںţ���Client���ӵĶ˿ں�һ��
 */
void ICACHE_FLASH_ATTR
tcp_server_init(struct espconn *espconn,uint16 local_port){

	os_printf("tcp server waiting tcp client connect!\r\n");
	espconn->proto.tcp = (esp_tcp *)os_zalloc(sizeof(esp_tcp));
	espconn->type = ESPCONN_TCP;

	espconn->proto.tcp->local_port = local_port;//���ñ��ؼ����Ķ˿ںţ��ȴ�Client����

	espconn_regist_connectcb(espconn,tcp_server_listen_cb);//ע��Server�����ص�����
	espconn_regist_reconcb(espconn,tcp_server_recon_cb);//ע������������ӻص�����

	espconn_accept(espconn);//����Server,��ʼ����
	espconn_regist_time(espconn,360,0);//��ʱ�Ͽ�����ʱ��
}
