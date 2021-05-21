/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "project.h"
#include "utilities.h"
#include "gps_ctrl.h"
#include "data.h"

#include <stdio.h>
#include <string.h>


#define SIZE_GPS       (80u)
#define CHEKSUM_MARKER  '*'
#define CARR_RETURN     '\r'
#define LINE_FEED       '\n'
#define COMA            ','
#define MSG_START       '$'

/* The following constants are based on the NMEA manual found here:
    http://geostar-navi.com/files/docs/geos5/GeoS_NMEA_protocol_v4_0_eng.pdf
    page = 8
*/
#define UTF_SIZE               (9u)  
#define LATITUDE_SIZE          (7u)
#define LATITUDE_N_S_SIZE      (1u)
#define LONGITUDE_SIZE         (8u)
#define LONGITUDE_SIZE_E_W     (1u)

#define UTF_WORD_POS           (9u)  
#define LATITUDE_WORD_POS      (7u)
#define LATITUDE_N_S_WORD_POS  (1u)
#define LONGITUDE_WORD_POS     (8u)
#define LONGITUDE_E_W_WORD_POS (1u)

// Number of words after GPGGA. Each word is counted after each comma
#define NUM_WORDS              (15u)  


static uint8 gps_array[SIZE_GPS];
static uint8 gps_index = 0u;

static uint8 msg_ok = FALSE;


CY_ISR(gps_handler){
    
    if(!msg_ok)
    {
        gps_array[gps_index] = UART_GPS_RXDATA_REG;  // Reads incoming data on each interrupt
        
        /* If both end characters are read, reset the array and send the ok flag */
        if((gps_array[gps_index] == LINE_FEED) && (gps_array[gps_index - 1u] == CARR_RETURN))
        {
            msg_ok = TRUE;
        }
                
        if(gps_array[gps_index] == MSG_START)
        {
            gps_array[0] = MSG_START;
            gps_index = 0;
        }
        else
            gps_index++;            
    }
    
    gps_isr_ClearPending();
}


/* Initialize all ISRs here */
void gps_setup(void)
{
    gps_isr_Start();
    gps_isr_StartEx(gps_handler);
}


/* Process the incoming GPS data for location information. The data will then be transmitted 
   onto the GUI for further processing. The data may also be transmitted onto the Jetson Nano
   or even processed locally. 
    
    Note: GPS data is processed accoerding to NMEA standard version 4.0. All characters are ASCII characters */
void gps_process(void)
{
    if(!msg_ok)
        return;
                
    /* in orer to gather information on location, the GPS needs to gather the message that starts 
       with GPGGA. Index starts at 1 since the '$' character is first (0) */
    if((gps_array[0] == 'G' && gps_array[1] == 'N' && gps_array[2] == 'G' && 
       gps_array[3] == 'G' && gps_array[4] == 'A'))
    { 
        /* Start at 6 to avoid the coma character */
        for(uint i = 0; i < gps_index; i++)
        {                   
            /* Count each comma */
            //tx_data.gngga_msg[i] = gps_array[i];
            return;
        }
    }
    else
    {
        msg_ok = FALSE;
        return;
    }
    
    
    /* Reset message flag and fill 'gps_array' with zeroes */
    memset(gps_array, 0, sizeof(gps_array));
    msg_ok = FALSE;
}

/* [] END OF FILE */
