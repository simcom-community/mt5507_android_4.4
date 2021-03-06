/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2006
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE. 
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/

/*******************************************************************************
 *
 * Filename:
 * ---------
 * gapattdb.c
 *
 * Project:
 * --------
 *   MAUI
 *
 * Description:
 * ------------
 * GAP ATT record database
 *
 * Author:
 * -------
 * Autumn Li(mtk01174)
 *
 *==============================================================================
 *             HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!! 
 *------------------------------------------------------------------------------
 * $Log$
 *
 * 11 21 2012 dlight.ting
 * [ALPS00399218] [Bluetooth] Check in BT proximity pairing problem
 * .
 * 
 * 10 16 2012 dlight.ting
 * [ALPS00367405] [SW.MT6577_PLATFORM]BT4.0 LE PXP patch
 * .
 * 
 * 10 15 2012 dlight.ting
 * [ALPS00367405] [SW.MT6577_PLATFORM]BT4.0 LE PXP patch
 * .
 *
 * 10 31 2011 dlight.ting
 * NULL
 * .
 *
 * 08 01 2011 autumn.li
 * [ALPS00064244] [BT] [BLE] ATT/GATT revision
 * ATT/GATT revision
 *
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!! 
 *==============================================================================
 *******************************************************************************/
#include "attdb.h"
#include "attdef.h"
#include "attdbmain.h"

#if defined(__BT_4_0_PRIVACY__) && defined(__BT_LE_STANDALONE__)
extern U8 BtbmAttHandlePrivacy(U8 type, BtRemoteDevice *link, U16 handle, U16 *len, U8 **raw);
extern U8 BtbmAttHandleReconnectAddress(U8 type, BtRemoteDevice *link, U16 handle, U16 *len, U8 **raw);
#endif
extern U8 BtbmAttHandleDeviceName(U8 type, BtRemoteDevice *link, U16 handle, U16 *len, U8 **raw);
extern U8 BtbmAttHandleAppearance(U8 type, BtRemoteDevice *link, U16 handle, U16 *len, U8 **raw);

const U8 attGapRecord[] = 
{
    ATT_HANDLE16(ATT_HANDLE_PRIMARY_SERVICE_GAP, BT_UUID_GATT_TYPE_PRIMARY_SERVICE, BT_ATT_CONST_VARIABLE, 0x02),
        ATT_PERMINSIONS(ATT_PERMISSIONS_READ_ONLY, ATT_SECURITY_READ_NOT_REQUIRED, 0x00, ATT_SECURITY_WRITE_NOT_REQUIRED, 0x00), 
        ATT_SETUUID16(BT_UUID_GATT_SERVICE_GAP),
        
#if defined(__BT_4_0_PRIVACY__) && defined(__BT_LE_STANDALONE__)
    ATT_HANDLE16(ATT_HANDLE_GAP_CHARACTERISTIC_PERIPHERAL_PRIVACY, BT_UUID_GATT_TYPE_CHARACTERISTIC, BT_ATT_CONST_VARIABLE, 0x05), 
        ATT_PERMINSIONS(ATT_PERMISSIONS_READ_ONLY, ATT_SECURITY_READ_NOT_REQUIRED, 0, ATT_SECURITY_WRITE_NOT_REQUIRED, 0), 
  #ifdef __BT_4_0_ENABLE_SET_PRIVACY__
        ATT_SETCHARACTERISTIC(GATT_CHAR_PROP_READ | GATT_CHAR_PROP_WRITE_WO_RESPONSE | GATT_CHAR_PROP_WRITE, ATT_HANDLE_GAP_CHARACTERISTIC_PERIPHERAL_PRIVACY_VALUE, BT_UUID_GATT_CHAR_TYPE_PERIPHERAL_PRIVACY_FLAG),
  #else
        ATT_SETCHARACTERISTIC(GATT_CHAR_PROP_READ, ATT_HANDLE_GAP_CHARACTERISTIC_PERIPHERAL_PRIVACY_VALUE, BT_UUID_GATT_CHAR_TYPE_PERIPHERAL_PRIVACY_FLAG),
  #endif
        
    ATT_HANDLE16(ATT_HANDLE_GAP_CHARACTERISTIC_PERIPHERAL_PRIVACY_VALUE, BT_UUID_GATT_CHAR_TYPE_PERIPHERAL_PRIVACY_FLAG, BT_ATT_FIX_VARIABLE_IN_UPPER_AP, 0x01), 
        ATT_PERMINSIONS(ATT_PERMISSIONS_GATT_DEFINED, ATT_SECURITY_READ_NOT_REQUIRED, 0, ATT_SECURITY_WRITE_NOT_REQUIRED, 0), 

  #ifdef __BT_4_0_PRIVACY_RECON_ADDR__
    ATT_HANDLE16(ATT_HANDLE_GAP_CHARACTERISTIC_RECONNECT_ADDRESS, BT_UUID_GATT_TYPE_CHARACTERISTIC, BT_ATT_CONST_VARIABLE, 0x05), 
        ATT_PERMINSIONS(ATT_PERMISSIONS_READ_ONLY, ATT_SECURITY_READ_NOT_REQUIRED, 0, ATT_SECURITY_WRITE_NOT_REQUIRED, 0), 
        ATT_SETCHARACTERISTIC(GATT_CHAR_PROP_READ | GATT_CHAR_PROP_WRITE_WO_RESPONSE | GATT_CHAR_PROP_WRITE, ATT_HANDLE_GAP_CHARACTERISTIC_RECONNECT_ADDRESS_VALUE, BT_UUID_GATT_CHAR_TYPE_RECONNECTION_ADDRESS),
        
    ATT_HANDLE16(ATT_HANDLE_GAP_CHARACTERISTIC_RECONNECT_ADDRESS_VALUE, BT_UUID_GATT_CHAR_TYPE_RECONNECTION_ADDRESS, BT_ATT_FIX_VARIABLE_IN_UPPER_AP, 0x06), 
        ATT_PERMINSIONS(ATT_PERMISSIONS_GATT_DEFINED, ATT_SECURITY_READ_NOT_REQUIRED, 0, ATT_SECURITY_WRITE_NOT_REQUIRED, 0), 
  #endif
#endif

    /* Handle =   0x0002, Type16 = Primary service, Value = GAP Service*/
    ATT_HANDLE16(ATT_HANDLE_GAP_CHARACTERISTIC_DEVICE_NAME, BT_UUID_GATT_TYPE_CHARACTERISTIC, BT_ATT_CONST_VARIABLE, 0x05), 
        ATT_PERMINSIONS(ATT_PERMISSIONS_READ_ONLY, ATT_SECURITY_READ_NOT_REQUIRED, 0, ATT_SECURITY_WRITE_NOT_REQUIRED, 0), 
        ATT_SETCHARACTERISTIC(GATT_CHAR_PROP_READ, ATT_HANDLE_GAP_CHARACTERISTIC_DEVICE_NAME_VALUE, BT_UUID_GATT_CHAR_TYPE_DEVICE_NAME),
        
    ATT_HANDLE16(ATT_HANDLE_GAP_CHARACTERISTIC_DEVICE_NAME_VALUE, BT_UUID_GATT_CHAR_TYPE_DEVICE_NAME, BT_ATT_FIX_VARIABLE_IN_UPPER_AP, 0x05), 
        ATT_PERMINSIONS(ATT_PERMISSIONS_GATT_DEFINED, ATT_SECURITY_READ_NOT_REQUIRED, 0, ATT_SECURITY_WRITE_NOT_REQUIRED, 0),  

    ATT_HANDLE16(ATT_HANDLE_GAP_CHARACTERISTIC_APPEARANCE, BT_UUID_GATT_TYPE_CHARACTERISTIC, BT_ATT_CONST_VARIABLE, 0x05), 
        ATT_PERMINSIONS(ATT_PERMISSIONS_READ_ONLY, ATT_SECURITY_READ_NOT_REQUIRED, 0, ATT_SECURITY_WRITE_NOT_REQUIRED, 0),   
        ATT_SETCHARACTERISTIC(GATT_CHAR_PROP_READ, ATT_HANDLE_GAP_CHARACTERISTIC_APPEARANCE_VALUE, BT_UUID_GATT_CHAR_TYPE_APPEARANCE),
        
    ATT_HANDLE16(ATT_HANDLE_GAP_CHARACTERISTIC_APPEARANCE_VALUE, BT_UUID_GATT_CHAR_TYPE_APPEARANCE, BT_ATT_FIX_VARIABLE_IN_UPPER_AP, 0x02), 
        ATT_PERMINSIONS(ATT_PERMISSIONS_GATT_DEFINED, ATT_SECURITY_READ_NOT_REQUIRED, 0, ATT_SECURITY_WRITE_NOT_REQUIRED, 0),   
};

/*********************
Function Definitions 
**********************/

/*****************************************************************************
 * FUNCTION
 *  GapAttDB_Registration
 * DESCRIPTION
 *  
 * PARAMETERS
 *  void
 * RETURNS
 *  
 *****************************************************************************/
U8 GapAttDB_Registration(void)
{
    BtStatus status;

    status = ATTDB_AddRecord(attGapRecord, sizeof(attGapRecord));
#if defined(__BT_4_0_PRIVACY__) && defined(__BT_LE_STANDALONE__)
    ATTDB_AddRecordCB(ATT_HANDLE_GAP_CHARACTERISTIC_PERIPHERAL_PRIVACY_VALUE, BtbmAttHandlePrivacy);
  #ifdef __BT_4_0_PRIVACY_RECON_ADDR__
    ATTDB_AddRecordCB(ATT_HANDLE_GAP_CHARACTERISTIC_RECONNECT_ADDRESS_VALUE, BtbmAttHandleReconnectAddress);
  #endif
#endif
    ATTDB_AddRecordCB(ATT_HANDLE_GAP_CHARACTERISTIC_DEVICE_NAME_VALUE, BtbmAttHandleDeviceName);
    ATTDB_AddRecordCB(ATT_HANDLE_GAP_CHARACTERISTIC_APPEARANCE_VALUE, BtbmAttHandleAppearance);
    ATTDB_AddGroupRecord(ATT_HANDLE_PRIMARY_SERVICE_GAP, 
                         ATT_HANDLE_PRIMARY_SERVICE_GAP_END, 
                         BT_UUID_GATT_TYPE_PRIMARY_SERVICE);
     return (U8)status;
}


