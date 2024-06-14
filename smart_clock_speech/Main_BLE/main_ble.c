#include "main_ble.h"

volatile int uxTopUsedPriority;

cyhal_pwm_t PWM_obj;
TimerHandle_t timer_led_blink;

bool set_rtc = false;

uint8_t led_blink_count;
uint16_t connection_id = 0;

bool flag_bt_actived = false;

void app_bt_timeout_led_blink(TimerHandle_t timer_handle)
{
	static wiced_bool_t led_on = WICED_TRUE;
	printf("Num at void timout : %d\r\n", led_blink_count);
	if (led_on)
	{
		cyhal_gpio_write(CYBSP_USER_LED, CYBSP_LED_STATE_OFF);
		if (--led_blink_count)
		{
			led_on = WICED_FALSE;
			xTimerStart(timer_led_blink, 0);
		}
	}
	else
	{
		led_on = WICED_TRUE;
		cyhal_gpio_write(CYBSP_USER_LED , CYBSP_LED_STATE_ON);
		xTimerStart(timer_led_blink, 0);
	}
}

void app_bt_led_blink(uint16_t num_of_blinks)
{
	if (num_of_blinks)
	{
		printf("Num at void blink : %d\r\n", num_of_blinks);
		led_blink_count = num_of_blinks;
		cyhal_gpio_write(CYBSP_USER_LED , CYBSP_LED_STATE_ON);
		xTimerStart(timer_led_blink, 0);
	}
}

/*******************************************************************************
 * Function Name: wiced_bt_dev_status_t app_bt_management_callback(
 * 					wiced_bt_management_evt_t event,
 * 					wiced_bt_management_evt_data_t *p_event_data )
 ********************************************************************************/
wiced_result_t app_bt_management_callback( wiced_bt_management_evt_t event, wiced_bt_management_evt_data_t *p_event_data )
{
	/* Start in error state so that any unimplemented states will return error */
	wiced_result_t result = WICED_BT_ERROR;
	wiced_bt_device_address_t bda = {0};

	printf("Bluetooth Management Event: 0x%x %s\r\n", event, get_bt_event_name(event));

	switch( event )
	{
	case BTM_ENABLED_EVT:								// Bluetooth Controller and Host Stack Enabled
//		if(flag_bt_actived == true){
			if( WICED_BT_SUCCESS == p_event_data->enabled.status )
			{
				printf( "Bluetooth Enabled\n\r" );

				/* Set the local BDA from the value in the configurator and print it */
				wiced_bt_set_local_bdaddr((uint8_t *)cy_bt_device_address, BLE_ADDR_PUBLIC);
				wiced_bt_dev_read_local_addr( bda );
				printf( "Local Bluetooth Device Address: ");
				print_bd_address(bda);

				/* Set advertisement packet and begin advertising */
				wiced_bt_ble_set_raw_advertisement_data(CY_BT_ADV_PACKET_DATA_SIZE, cy_bt_adv_packet_data);

				/* Register GATT callback and initialize database*/
				wiced_bt_gatt_register( app_bt_gatt_event_callback );
				wiced_bt_gatt_db_init( gatt_database, gatt_database_len, NULL );

				/* Disable pairing */
				wiced_bt_set_pairable_mode( WICED_FALSE, WICED_FALSE );

				result = WICED_BT_SUCCESS;
			}
			else
			{
				printf( "Failed to initialize Bluetooth controller and stack\n\r" );
			}
//		}
		break;

	case BTM_PAIRING_IO_CAPABILITIES_BLE_REQUEST_EVT: 		// IO capabilities request
		result = WICED_BT_SUCCESS;
		break;

	case BTM_PAIRING_COMPLETE_EVT: 							// Pairing Complete event
		result = WICED_BT_SUCCESS;
		break;

	case BTM_ENCRYPTION_STATUS_EVT: 						// Encryption Status Event
		result = WICED_BT_SUCCESS;
		break;

	case BTM_SECURITY_REQUEST_EVT: 							// Security access
		result = WICED_BT_SUCCESS;
		break;

	case BTM_PAIRED_DEVICE_LINK_KEYS_UPDATE_EVT: 			// Save link keys with app
		result = WICED_BT_SUCCESS;
		break;

	case BTM_PAIRED_DEVICE_LINK_KEYS_REQUEST_EVT: 			// Retrieve saved link keys
		/* This must return WICED_BT_ERROR if bonding information is not stored in EEPROM */
		result = WICED_BT_ERROR;
		break;

	case BTM_LOCAL_IDENTITY_KEYS_UPDATE_EVT: 				// Save keys to NVRAM
		result = WICED_BT_SUCCESS;
		break;

	case  BTM_LOCAL_IDENTITY_KEYS_REQUEST_EVT: 				// Read keys from NVRAM
		/* This should return WICED_BT_SUCCESS if not using privacy. If RPA is enabled but keys are not
               stored in EEPROM, this must return WICED_BT_ERROR so that the stack will generate new privacy keys */
		result = WICED_BT_ERROR;
		break;

	case BTM_BLE_SCAN_STATE_CHANGED_EVT: 					// Scan State Change
		result = WICED_BT_SUCCESS;
		break;

	case BTM_BLE_ADVERT_STATE_CHANGED_EVT:					// Advertising State Change
		printf("Advertisement State Change: %s\n\r", get_bt_advert_mode_name(p_event_data->ble_advert_state_changed));
		result = WICED_BT_SUCCESS;
		if (p_event_data->ble_advert_state_changed == BTM_BLE_ADVERT_OFF){
			if(connection_id == 0){
				cyhal_pwm_set_duty_cycle(&PWM_obj, 100, 2);
			}
			else { //connected
				cyhal_pwm_set_duty_cycle(&PWM_obj, 0, 2);
			}
		}
		else{
			cyhal_pwm_set_duty_cycle(&PWM_obj, 50, 2);
		}
		break;

	default:
		break;
	}

	return result;
}

/*******************************************************************************
 * Function Name: wiced_bt_gatt_status_t app_bt_gatt_event_callback(
 * 					wiced_bt_gatt_evt_t event,
 * 					wiced_bt_gatt_event_data_t *p_data )
 ********************************************************************************/
static wiced_bt_gatt_status_t app_bt_gatt_event_callback( wiced_bt_gatt_evt_t event, wiced_bt_gatt_event_data_t *p_event_data )
{
	/* Start in error state so that any unimplemented states will return error */
	wiced_bt_gatt_status_t status = WICED_BT_GATT_ERROR;

	/* Call the appropriate callback function based on the GATT event type, and pass the relevant event
	 * parameters to the callback function */
	switch (event)
	{
	case GATT_CONNECTION_STATUS_EVT:
		status = app_bt_connect_event_handler(&p_event_data->connection_status);
		break;

	case GATT_ATTRIBUTE_REQUEST_EVT:
		status = app_bt_server_event_handler(p_event_data);
		break;

	case GATT_GET_RESPONSE_BUFFER_EVT: /* GATT buffer request, typically sized to max of bearer mtu - 1 */
		p_event_data->buffer_request.buffer.p_app_rsp_buffer = app_bt_alloc_buffer(p_event_data->buffer_request.len_requested);
		p_event_data->buffer_request.buffer.p_app_ctxt = (void *)app_bt_free_buffer;
		status = WICED_BT_GATT_SUCCESS;
		break;

	case GATT_APP_BUFFER_TRANSMITTED_EVT: /* GATT buffer transmitted event,  check \ref wiced_bt_gatt_buffer_transmitted_t*/
	{
		pfn_free_buffer_t pfn_free = (pfn_free_buffer_t)p_event_data->buffer_xmitted.p_app_ctxt;

		/* If the buffer is dynamic, the context will point to a function to free it. */
		if (pfn_free)
		{
			pfn_free(p_event_data->buffer_xmitted.p_app_data);
		}
		status = WICED_BT_GATT_SUCCESS;
	}
	break;

	default:
		printf( "Unhandled GATT Event: 0x%x (%d)\n\r", event, event );
		status = WICED_BT_GATT_SUCCESS;
		break;
	}
	return status;
}

/*******************************************************************************
 * Function Name: app_bt_connect_event_handler
 *
 * Handles GATT connection status changes.
 *
 * Param:	p_conn_status  Pointer to data that has connection details
 * Return:	wiced_bt_gatt_status_t
 * See possible status codes in wiced_bt_gatt_status_e in wiced_bt_gatt.h
 *******************************************************************************/
static wiced_bt_gatt_status_t app_bt_connect_event_handler(wiced_bt_gatt_connection_status_t *p_conn_status)
{
	wiced_bt_gatt_status_t status = WICED_BT_GATT_ERROR;

	if (NULL != p_conn_status)
	{
		if (p_conn_status->connected)
		{
			printf("GATT_CONNECTION_STATUS_EVT: Connect BDA ");
			print_bd_address(p_conn_status->bd_addr);
			printf("Connection ID %d\n\r", p_conn_status->conn_id );
			connection_id = p_conn_status->conn_id;
			/* Handle the connection */
//			flag_bt_actived = false;
		}
		else
		{
			printf("Disconnected : BDA " );
			print_bd_address(p_conn_status->bd_addr);
			printf("Connection ID '%d', Reason '%s'\n\r", p_conn_status->conn_id, get_bt_gatt_disconn_reason_name(p_conn_status->reason) );
			connection_id = 0;
			set_rtc = false;

//			flag_bt_actived = true;
			/* Handle the disconnection */

			/* Restart the advertisements */
			//			wiced_bt_start_advertisements( BTM_BLE_ADVERT_UNDIRECTED_HIGH, 0, NULL );
		}

		status = WICED_BT_GATT_SUCCESS;
	}

	return status;
}

/*******************************************************************************
 * Function Name: app_bt_server_event_handler
 *
 * Invoked when GATT_ATTRIBUTE_REQUEST_EVT occurs in GATT Event callback.
 *
 * Param:	p_data   				Pointer to BLE GATT request data
 * Return:	wiced_bt_gatt_status_t  BLE GATT status
 *******************************************************************************/
static wiced_bt_gatt_status_t app_bt_server_event_handler(wiced_bt_gatt_event_data_t *p_data)
{
	wiced_bt_gatt_status_t status = WICED_BT_GATT_ERROR;
	wiced_bt_gatt_attribute_request_t   *p_att_req = &p_data->attribute_request;

	switch (p_att_req->opcode)
	{

	case GATT_REQ_READ: /* Attribute read notification (attribute value internally read from GATT database) */
	case GATT_REQ_READ_BLOB:
		status = app_bt_gatt_req_read_handler(p_att_req->conn_id, p_att_req->opcode,
				&p_att_req->data.read_req, p_att_req->len_requested);
		break;

	case GATT_REQ_READ_BY_TYPE:
		status = app_bt_gatt_req_read_by_type_handler(p_att_req->conn_id, p_att_req->opcode,
				&p_att_req->data.read_by_type, p_att_req->len_requested);
		break;

	case GATT_REQ_READ_MULTI:
	case GATT_REQ_READ_MULTI_VAR_LENGTH:
		status = app_bt_gatt_req_read_multi_handler(p_att_req->conn_id, p_att_req->opcode,
				&p_att_req->data.read_multiple_req, p_att_req->len_requested);
		break;

	case GATT_REQ_WRITE:
	case GATT_CMD_WRITE:
	case GATT_CMD_SIGNED_WRITE:
		status = app_bt_write_handler(p_data);
		if ((p_att_req->opcode == GATT_REQ_WRITE) && (status == WICED_BT_GATT_SUCCESS))
		{
			wiced_bt_gatt_write_req_t *p_write_request = &p_att_req->data.write_req;
			wiced_bt_gatt_server_send_write_rsp(p_att_req->conn_id, p_att_req->opcode, p_write_request->handle);
		}
		break;

	case GATT_REQ_PREPARE_WRITE:
		status = WICED_BT_GATT_SUCCESS;
		break;

	case GATT_REQ_EXECUTE_WRITE:
		wiced_bt_gatt_server_send_execute_write_rsp(p_att_req->conn_id, p_att_req->opcode);
		status = WICED_BT_GATT_SUCCESS;
		break;

	case GATT_REQ_MTU:
		/* Application calls wiced_bt_gatt_server_send_mtu_rsp() with the desired mtu */
		status = wiced_bt_gatt_server_send_mtu_rsp(p_att_req->conn_id,
				p_att_req->data.remote_mtu,
				wiced_bt_cfg_settings.p_ble_cfg->ble_max_rx_pdu_size);
		break;

	case GATT_HANDLE_VALUE_CONF: /* Value confirmation */
		break;

	case GATT_HANDLE_VALUE_NOTIF:
		break;

	default:
		printf( "Unhandled GATT Server Event: 0x%x (%d)\n\r", p_att_req->opcode, p_att_req->opcode );
		break;
	}

	return status;
}

/*******************************************************************************
 * Function Name: app_bt_write_handler
 *
 * Invoked when GATTS_REQ_TYPE_WRITE is received from the
 * client device. Handles "Write Requests" received from Client device.
 *
 * Param:	p_write_req   			Pointer to BLE GATT write request
 * Return:	wiced_bt_gatt_status_t  BLE GATT status
 *******************************************************************************/
static wiced_bt_gatt_status_t app_bt_write_handler(wiced_bt_gatt_event_data_t *p_data)
{
	wiced_bt_gatt_write_req_t *p_write_req = &p_data->attribute_request.data.write_req;;

	wiced_bt_gatt_status_t status = WICED_BT_GATT_INVALID_HANDLE;

	for (int i = 0; i < app_gatt_db_ext_attr_tbl_size; i++)
	{

		/* Check for a matching handle entry */
		if (app_gatt_db_ext_attr_tbl[i].handle == p_write_req->handle)
		{
			//			printf("len value %d \r\n", p_write_req->val_len);
			for (int a = 0; a < p_write_req->val_len; a++){
				//				printf("Pval %d \r\n",p_write_req->p_val[a]);
			}
			//             memset(app_gatt_db_ext_attr_tbl[i].p_write_req->p_val, 0x00, app_gatt_db_ext_attr_tbl[i].max_len);

			/* Detected a matching handle in the external lookup table */
			if (app_gatt_db_ext_attr_tbl[i].max_len >= p_write_req->val_len)
			{
				/* Value fits within the supplied buffer; copy over the value */
				app_gatt_db_ext_attr_tbl[i].cur_len = p_write_req->val_len;
				memset(app_gatt_db_ext_attr_tbl[i].p_data, 0x00, app_gatt_db_ext_attr_tbl[i].max_len);
				memcpy(app_gatt_db_ext_attr_tbl[i].p_data, p_write_req->p_val, app_gatt_db_ext_attr_tbl[i].cur_len);

				if (memcmp(app_gatt_db_ext_attr_tbl[i].p_data, p_write_req->p_val, app_gatt_db_ext_attr_tbl[i].cur_len) == 0)
				{
					status = WICED_BT_GATT_SUCCESS;
				}

				switch ( p_write_req->handle )
				{
				// Add action when specified handle is written
				case HDLC_PSOC_LED_VALUE:
					uint16_t data;
					if (p_write_req->val_len == 1)data = app_psoc_led[0];
					else if (p_write_req->val_len == 2)data = app_psoc_led[0] << 8 | app_psoc_led[1];//Kalau memakai AIROC lsb first
					//                 		else if (p_write_req->val_len == 2)data = app_psoc_led[1] << 8 | app_psoc_led[0];//Kalau memakai LightBlue msb first
					app_bt_led_blink(data);
					printf("%d\r\n",data);
					break;

				case HDLC_PSOC_STRING_VALUE:

					char *ptr = app_psoc_string;
					printf("Data string = %s\r\n",ptr);

					//					char data_test[] = {'1','2',' ','3','0',' ','4','0',' ','2','5',' ','3','0',' ','2','0','2','4','\0'};
					int set_rtc_data[6];
					//					char* token = strtok(app_psoc_string, " ");
					char* token = strtok(app_psoc_string, " ");

					while (token != NULL){
						set_rtc = false;
						for(uint8_t i = 0; i < 6; i++){
							set_rtc_data[i] = atoi(token);
							printf("Data set rtc %d : %d\r\n",i, set_rtc_data[i]);
							token = strtok(NULL, " ");
							vTaskDelay(10);
						}
					}
					if(token == NULL){

						RTC_Setup.hour = (uint8_t)set_rtc_data[0];
						RTC_Setup.min = (uint8_t)set_rtc_data[1];
						RTC_Setup.sec =	(uint8_t)set_rtc_data[2];
						RTC_Setup.mday = (uint8_t)set_rtc_data[3];
						RTC_Setup.month = (uint8_t)set_rtc_data[4];
						RTC_Setup.Year = (uint16_t)set_rtc_data[5];
						set_new_time();
						set_rtc = true;
					}

					break;
				}
			}
			else
			{
				/* Value to write will not fit within the table */
				status = WICED_BT_GATT_INVALID_ATTR_LEN;
				printf("Invalid attribute length during GATT write\n");
			}
			break;
		}
	}
	if (WICED_BT_GATT_SUCCESS != status)
	{
		printf("GATT write failed: %d\n\r", status);
	}

	return status;
}

/*******************************************************************************
 * Function Name: app_bt_gatt_req_read_handler
 *
 * This Function handles GATT read and read blob events
 *
 * Params: 	conn_id       			Connection ID
 * 			opcode        			BLE GATT request type opcode
 * 			p_read_req    			Pointer to read request containing the handle to read
 * 			len_requested 			Length of data requested
 * Return: 	wiced_bt_gatt_status_t  BLE GATT status
 *******************************************************************************/
static wiced_bt_gatt_status_t app_bt_gatt_req_read_handler(uint16_t conn_id, wiced_bt_gatt_opcode_t opcode,
		wiced_bt_gatt_read_t *p_read_req, uint16_t len_requested)
{
	gatt_db_lookup_table_t *puAttribute;
	uint16_t attr_len_to_copy, to_send;
	uint8_t *from;

	if ((puAttribute = app_bt_find_by_handle(p_read_req->handle)) == NULL)
	{
		wiced_bt_gatt_server_send_error_rsp(conn_id, opcode, p_read_req->handle, WICED_BT_GATT_INVALID_HANDLE);
		return WICED_BT_GATT_INVALID_HANDLE;
	}

	attr_len_to_copy = puAttribute->cur_len;

	if (p_read_req->offset >= puAttribute->cur_len)
	{
		wiced_bt_gatt_server_send_error_rsp(conn_id, opcode, p_read_req->handle, WICED_BT_GATT_INVALID_OFFSET);
		return WICED_BT_GATT_INVALID_OFFSET;
	}

	switch ( p_read_req->handle )
	{
	// Add action when specified handle is read
	case HDLC_PSOC_LED_VALUE:
		printf( "LED is %s\r\n", app_psoc_led[0] ? "ON" : "OFF" );
		break;
	}

	to_send = MIN(len_requested, attr_len_to_copy - p_read_req->offset);
	from = puAttribute->p_data + p_read_req->offset;
	return wiced_bt_gatt_server_send_read_handle_rsp(conn_id, opcode, to_send, from, NULL); /* No need for context, as buff not allocated */
}

/*******************************************************************************
 * Function Name: app_bt_gatt_req_read_by_type_handler
 *
 * Process read-by-type request from peer device
 *
 * Params:	conn_id       			Connection ID
 * 			opcode        			BLE GATT request type opcode
 * 			p_read_req    			Pointer to read request containing the handle to read
 * 			len_requested 			Length of data requested
 * Return:	wiced_bt_gatt_status_t	BLE GATT status
 *******************************************************************************/
static wiced_bt_gatt_status_t app_bt_gatt_req_read_by_type_handler(uint16_t conn_id, wiced_bt_gatt_opcode_t opcode,
		wiced_bt_gatt_read_by_type_t *p_read_req, uint16_t len_requested)
{
	gatt_db_lookup_table_t *puAttribute;
	uint16_t attr_handle = p_read_req->s_handle;
	uint8_t *p_rsp = app_bt_alloc_buffer(len_requested);
	uint8_t pair_len = 0;
	int used = 0;

	if (p_rsp == NULL)
	{
		wiced_bt_gatt_server_send_error_rsp(conn_id, opcode, attr_handle, WICED_BT_GATT_INSUF_RESOURCE);
		return WICED_BT_GATT_INSUF_RESOURCE;
	}

	/* Read by type returns all attributes of the specified type, between the start and end handles */
	while (WICED_TRUE)
	{
		attr_handle = wiced_bt_gatt_find_handle_by_type(attr_handle, p_read_req->e_handle, &p_read_req->uuid);

		if (attr_handle == 0)
			break;

		if ((puAttribute = app_bt_find_by_handle(attr_handle)) == NULL)
		{
			wiced_bt_gatt_server_send_error_rsp(conn_id, opcode, p_read_req->s_handle, WICED_BT_GATT_ERR_UNLIKELY);
			app_bt_free_buffer(p_rsp);
			return WICED_BT_GATT_INVALID_HANDLE;
		}

		{
			int filled = wiced_bt_gatt_put_read_by_type_rsp_in_stream(p_rsp + used, len_requested - used, &pair_len,
					attr_handle, puAttribute->cur_len, puAttribute->p_data);
			if (filled == 0)
			{
				break;
			}
			used += filled;
		}

		/* Increment starting handle for next search to one past current */
		attr_handle++;
	}

	if (used == 0)
	{
		wiced_bt_gatt_server_send_error_rsp(conn_id, opcode, p_read_req->s_handle, WICED_BT_GATT_INVALID_HANDLE);
		app_bt_free_buffer(p_rsp);
		return WICED_BT_GATT_INVALID_HANDLE;
	}

	switch ( p_read_req->s_handle )
	{
	// Add action when specified handle is read
	case HDLC_PSOC_LED_VALUE:
		printf( "LED is %s\r\n", app_psoc_led[0] ? "ON" : "OFF" );
		break;
	}

	/* Send the response */
	wiced_bt_gatt_server_send_read_by_type_rsp(conn_id, opcode, pair_len, used, p_rsp, (void *)app_bt_free_buffer);

	return WICED_BT_GATT_SUCCESS;
}

/*******************************************************************************
 * Function Name: app_bt_gatt_req_read_multi_handler
 *
 * Process write read multi request from peer device
 *
 * Params:	conn_id       			Connection ID
 * 			opcode        			BLE GATT request type opcode
 * 			p_read_req    			Pointer to read request containing the handle to read
 * 			len_requested 			Length of data requested
 * Return:	wiced_bt_gatt_status_t  BLE GATT status
 *******************************************************************************/
static wiced_bt_gatt_status_t app_bt_gatt_req_read_multi_handler(uint16_t conn_id, wiced_bt_gatt_opcode_t opcode,
		wiced_bt_gatt_read_multiple_req_t *p_read_req, uint16_t len_requested)
{
	gatt_db_lookup_table_t *puAttribute;
	uint8_t *p_rsp = app_bt_alloc_buffer(len_requested);
	int used = 0;
	int xx;
	uint16_t handle = wiced_bt_gatt_get_handle_from_stream(p_read_req->p_handle_stream, 0);

	if (p_rsp == NULL)
	{
		wiced_bt_gatt_server_send_error_rsp(conn_id, opcode, handle, WICED_BT_GATT_INSUF_RESOURCE);
		return WICED_BT_GATT_INVALID_HANDLE;
	}

	/* Read by type returns all attributes of the specified type, between the start and end handles */
	for (xx = 0; xx < p_read_req->num_handles; xx++)
	{
		handle = wiced_bt_gatt_get_handle_from_stream(p_read_req->p_handle_stream, xx);
		if ((puAttribute = app_bt_find_by_handle(handle)) == NULL)
		{
			wiced_bt_gatt_server_send_error_rsp(conn_id, opcode, *p_read_req->p_handle_stream, WICED_BT_GATT_ERR_UNLIKELY);
			app_bt_free_buffer(p_rsp);
			return WICED_BT_GATT_ERR_UNLIKELY;
		}

		{
			int filled = wiced_bt_gatt_put_read_multi_rsp_in_stream(opcode, p_rsp + used, len_requested - used,
					puAttribute->handle, puAttribute->cur_len, puAttribute->p_data);
			if (!filled)
			{
				break;
			}
			used += filled;
		}
	}

	if (used == 0)
	{
		wiced_bt_gatt_server_send_error_rsp(conn_id, opcode, *p_read_req->p_handle_stream, WICED_BT_GATT_INVALID_HANDLE);
		return WICED_BT_GATT_INVALID_HANDLE;
	}

	switch ( *p_read_req->p_handle_stream )
	{
	// Add action when specified handle is read
	case HDLC_PSOC_LED_VALUE:
		printf( "LED is %s\r\n", app_psoc_led[0] ? "ON" : "OFF" );
		break;
	}

	/* Send the response */
	wiced_bt_gatt_server_send_read_multiple_rsp(conn_id, opcode, used, p_rsp, (void *)app_bt_free_buffer);

	return WICED_BT_GATT_SUCCESS;
}


/*******************************************************************************
 * Function Name: app_bt_find_by_handle
 *
 * Finds attribute location by handle
 *
 * Param:  handle    				handle to look up
 * Return: gatt_db_lookup_table_t   	pointer to location containing handle data
 ********************************************************************************/
static gatt_db_lookup_table_t *app_bt_find_by_handle(uint16_t handle)
{
	int i;
	for (i = 0; i < app_gatt_db_ext_attr_tbl_size; i++)
	{
		if (app_gatt_db_ext_attr_tbl[i].handle == handle)
		{
			return (&app_gatt_db_ext_attr_tbl[i]);
		}
	}
	return NULL;
}


/*******************************************************************************
 * Function Name: app_bt_alloc_buffer
 *
 * This Function allocates the buffer of requested length
 *
 * Param:  len			Length of buffer
 * Return: uint8_t*      Pointer to allocated buffer
 ********************************************************************************/
static uint8_t *app_bt_alloc_buffer(uint16_t len)
{
	uint8_t *p = (uint8_t *)malloc(len);
	return p;
}

/*******************************************************************************
 * Function Name: app_bt_free_buffer
 *
 * This Function frees the buffer requested
 *
 * Param:  p_data		Pointer to buffer to be freed
 ********************************************************************************/
static void app_bt_free_buffer(uint8_t *p_data)
{
	if (p_data != NULL)
	{
		free(p_data);
	}
}
