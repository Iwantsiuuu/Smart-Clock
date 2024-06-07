#include "write_rtc_task.h"
#include "main_ble.h"

void notify_task(){

	cy_rslt_t rslt;
	char buffer[STRING_BUFFER_SIZE];
	//	char buffer_text[40];
	struct tm date_time;
	wiced_result_t wiced_result = WICED_BT_ERROR;

	while(1){

		if(set_rtc){

			rslt = cyhal_rtc_read(&rtc_obj, &date_time);
			if (CY_RSLT_SUCCESS == rslt)
			{
				strftime(buffer, sizeof(buffer), "%c", &date_time);
				printf("\r%s\n", buffer);
			}
		}

		//Send Notify to AIROC
		if(connection_id != 0){
			if(app_psoc_string_client_char_config[0] & GATT_CLIENT_CONFIG_NOTIFICATION){
				//				sprintf(buffer_text,"\r%s\n", buffer);
				wiced_bt_gatt_server_send_notification( connection_id, HDLC_PSOC_STRING_VALUE, strlen(buffer), (uint8_t *)buffer, NULL);
				memset(buffer, '\0', sizeof(buffer));
			}
		}
		vTaskDelay(pdMS_TO_TICKS(10));
	}
}
