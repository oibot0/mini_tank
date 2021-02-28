/**********************************Copyright (c)**********************************
**                       鐗堟潈鎵�鏈� (C), 2015-2020, 娑傞甫绉戞妧
**
**                             http://www.tuya.com
**
*********************************************************************************/
/**
 * @file    mcu_api.c
 * @author  娑傞甫缁煎悎鍗忚寮�鍙戠粍
 * @version v2.5.6
 * @date    2020.12.16
 * @brief   鐢ㄦ埛闇�瑕佷富鍔ㄨ皟鐢ㄧ殑鍑芥暟閮藉湪璇ユ枃浠跺唴
 */

/****************************** 鍏嶈矗澹版槑 锛侊紒锛� *******************************
鐢变簬MCU绫诲瀷鍜岀紪璇戠幆澧冨绉嶅鏍凤紝鎵�浠ユ浠ｇ爜浠呬緵鍙傝�冿紝鐢ㄦ埛璇疯嚜琛屾妸鎺ф渶缁堜唬鐮佽川閲忥紝
娑傞甫涓嶅MCU鍔熻兘缁撴灉璐熻矗銆�
******************************************************************************/

#define MCU_API_GLOBAL

#include "wifi.h"

/**
 * @brief  hex杞琤cd
 * @param[in] {Value_H} 楂樺瓧鑺�
 * @param[in] {Value_L} 浣庡瓧鑺�
 * @return 杞崲瀹屾垚鍚庢暟鎹�
 */
unsigned char hex_to_bcd(unsigned char Value_H,unsigned char Value_L)
{
    unsigned char bcd_value;
    
    if((Value_H >= '0') && (Value_H <= '9'))
        Value_H -= '0';
    else if((Value_H >= 'A') && (Value_H <= 'F'))
        Value_H = Value_H - 'A' + 10;
    else if((Value_H >= 'a') && (Value_H <= 'f'))
        Value_H = Value_H - 'a' + 10;
     
    bcd_value = Value_H & 0x0f;
    
    bcd_value <<= 4;
    if((Value_L >= '0') && (Value_L <= '9'))
        Value_L -= '0';
    else if((Value_L >= 'A') && (Value_L <= 'F'))
        Value_L = Value_L - 'a' + 10;
    else if((Value_L >= 'a') && (Value_L <= 'f'))
        Value_L = Value_L - 'a' + 10;
    
    bcd_value |= Value_L & 0x0f;

    return bcd_value;
}

/**
 * @brief  姹傚瓧绗︿覆闀垮害
 * @param[in] {str} 瀛楃涓插湴鍧�
 * @return 鏁版嵁闀垮害
 */
unsigned long my_strlen(unsigned char *str)  
{
    unsigned long len = 0;
    if(str == NULL) { 
        return 0;
    }
    
    for(len = 0; *str ++ != '\0'; ) {
        len ++;
    }
    
    return len;
}

/**
 * @brief  鎶妔rc鎵�鎸囧唴瀛樺尯鍩熺殑鍓峜ount涓瓧鑺傝缃垚瀛楃c
 * @param[out] {src} 寰呰缃殑鍐呭瓨棣栧湴鍧�
 * @param[in] {ch} 璁剧疆鐨勫瓧绗�
 * @param[in] {count} 璁剧疆鐨勫唴瀛橀暱搴�
 * @return 寰呰缃殑鍐呭瓨棣栧湴鍧�
 */
void *my_memset(void *src,unsigned char ch,unsigned short count)
{
    unsigned char *tmp = (unsigned char *)src;
    
    if(src == NULL) {
        return NULL;
    }
    
    while(count --) {
        *tmp ++ = ch;
    }
    
    return src;
}

/**
 * @brief  鍐呭瓨鎷疯礉
 * @param[out] {dest} 鐩爣鍦板潃
 * @param[in] {src} 婧愬湴鍧�
 * @param[in] {count} 鎷疯礉鏁版嵁涓暟
 * @return 鏁版嵁澶勭悊瀹屽悗鐨勬簮鍦板潃
 */
void *my_memcpy(void *dest, const void *src, unsigned short count)  
{  
    unsigned char *pdest = (unsigned char *)dest;  
    const unsigned char *psrc  = (const unsigned char *)src;  
    unsigned short i;
    
    if(dest == NULL || src == NULL) { 
        return NULL;
    }
    
    if((pdest <= psrc) || (pdest > psrc + count)) {  
        for(i = 0; i < count; i ++) {  
            pdest[i] = psrc[i];  
        }  
    }else {
        for(i = count; i > 0; i --) {  
            pdest[i - 1] = psrc[i - 1];  
        }  
    }  
    
    return dest;  
}

/**
 * @brief  瀛楃涓叉嫹璐�
 * @param[in] {dest} 鐩爣鍦板潃
 * @param[in] {src} 婧愬湴鍧�
 * @return 鏁版嵁澶勭悊瀹屽悗鐨勬簮鍦板潃
 */
char *my_strcpy(char *dest, const char *src)  
{
    if((NULL == dest) || (NULL == src)) {
        return NULL;
    }
    
    char *p = dest;
    while(*src!='\0') {
        *dest++ = *src++;
    }
    *dest = '\0';
    return p;
}

/**
 * @brief  瀛楃涓叉瘮杈�
 * @param[in] {s1} 瀛楃涓� 1
 * @param[in] {s2} 瀛楃涓� 2
 * @return 澶у皬姣旇緝鍊�
 * -         0:s1=s2
 * -         <0:s1<s2
 * -         >0:s1>s2
 */
int my_strcmp(char *s1 , char *s2)
{
    while( *s1 && *s2 && *s1 == *s2 ) {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

/**
 * @brief  灏唅nt绫诲瀷鎷嗗垎鍥涗釜瀛楄妭
 * @param[in] {number} 4瀛楄妭鍘熸暟鎹�
 * @param[out] {value} 澶勭悊瀹屾垚鍚�4瀛楄妭鏁版嵁
 * @return Null
 */
void int_to_byte(unsigned long number,unsigned char value[4])
{
    value[0] = number >> 24;
    value[1] = number >> 16;
    value[2] = number >> 8;
    value[3] = number & 0xff;
}

/**
 * @brief  灏�4瀛楄妭鍚堝苟涓�1涓�32bit鍙橀噺
 * @param[in] {value} 4瀛楄妭鏁扮粍
 * @return 鍚堝苟瀹屾垚鍚庣殑32bit鍙橀噺
 */
unsigned long byte_to_int(const unsigned char value[4])
{
    unsigned long nubmer = 0;

    nubmer = (unsigned long)value[0];
    nubmer <<= 8;
    nubmer |= (unsigned long)value[1];
    nubmer <<= 8;
    nubmer |= (unsigned long)value[2];
    nubmer <<= 8;
    nubmer |= (unsigned long)value[3];
    
    return nubmer;
}

/**
 * @brief  raw鍨媎p鏁版嵁涓婁紶
 * @param[in] {dpid} dpid鍙�
 * @param[in] {value} 褰撳墠dp鍊兼寚閽�
 * @param[in] {len} 鏁版嵁闀垮害
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_raw_update(unsigned char dpid,const unsigned char value[],unsigned short len)
{
    unsigned short send_len = 0;
    
    if(stop_update_flag == ENABLE)
        return SUCCESS;
    //
    send_len = set_wifi_uart_byte(send_len,dpid);
    send_len = set_wifi_uart_byte(send_len,DP_TYPE_RAW);
    //
    send_len = set_wifi_uart_byte(send_len,len / 0x100);
    send_len = set_wifi_uart_byte(send_len,len % 0x100);
    //
    send_len = set_wifi_uart_buffer(send_len,(unsigned char *)value,len);
    
    wifi_uart_write_frame(STATE_UPLOAD_CMD,MCU_TX_VER,send_len);
    
    return SUCCESS;
}

/**
 * @brief  bool鍨媎p鏁版嵁涓婁紶
 * @param[in] {dpid} dpid鍙�
 * @param[in] {value} 褰撳墠dp鍊�
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_bool_update(unsigned char dpid,unsigned char value)
{
    unsigned short send_len = 0;
    
    if(stop_update_flag == ENABLE)
        return SUCCESS;
    
    send_len = set_wifi_uart_byte(send_len,dpid);
    send_len = set_wifi_uart_byte(send_len,DP_TYPE_BOOL);
    //
    send_len = set_wifi_uart_byte(send_len,0);
    send_len = set_wifi_uart_byte(send_len,1);
    //
    if(value == FALSE) {
        send_len = set_wifi_uart_byte(send_len,FALSE);
    }else {
        send_len = set_wifi_uart_byte(send_len,1);
    }
    
    wifi_uart_write_frame(STATE_UPLOAD_CMD, MCU_TX_VER, send_len);
    
    return SUCCESS;
}

/**
 * @brief  value鍨媎p鏁版嵁涓婁紶
 * @param[in] {dpid} dpid鍙�
 * @param[in] {value} 褰撳墠dp鍊�
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_value_update(unsigned char dpid,unsigned long value)
{
    unsigned short send_len = 0;
    
    if(stop_update_flag == ENABLE)
        return SUCCESS;
    
    send_len = set_wifi_uart_byte(send_len,dpid);
    send_len = set_wifi_uart_byte(send_len,DP_TYPE_VALUE);
    //
    send_len = set_wifi_uart_byte(send_len,0);
    send_len = set_wifi_uart_byte(send_len,4);
    //
    send_len = set_wifi_uart_byte(send_len,value >> 24);
    send_len = set_wifi_uart_byte(send_len,value >> 16);
    send_len = set_wifi_uart_byte(send_len,value >> 8);
    send_len = set_wifi_uart_byte(send_len,value & 0xff);
    
    wifi_uart_write_frame(STATE_UPLOAD_CMD,MCU_TX_VER,send_len);
    
    return SUCCESS;
}

/**
 * @brief  string鍨媎p鏁版嵁涓婁紶
 * @param[in] {dpid} dpid鍙�
 * @param[in] {value} 褰撳墠dp鍊兼寚閽�
 * @param[in] {len} 鏁版嵁闀垮害
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_string_update(unsigned char dpid,const unsigned char value[],unsigned short len)
{
    unsigned short send_len = 0;
    
    if(stop_update_flag == ENABLE)
        return SUCCESS;
    //
    send_len = set_wifi_uart_byte(send_len,dpid);
    send_len = set_wifi_uart_byte(send_len,DP_TYPE_STRING);
    //
    send_len = set_wifi_uart_byte(send_len,len / 0x100);
    send_len = set_wifi_uart_byte(send_len,len % 0x100);
    //
    send_len = set_wifi_uart_buffer(send_len,(unsigned char *)value,len);
    
    wifi_uart_write_frame(STATE_UPLOAD_CMD,MCU_TX_VER,send_len);
    
    return SUCCESS;
}

/**
 * @brief  enum鍨媎p鏁版嵁涓婁紶
 * @param[in] {dpid} dpid鍙�
 * @param[in] {value} 褰撳墠dp鍊�
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_enum_update(unsigned char dpid,unsigned char value)
{
    unsigned short send_len = 0;
    
    if(stop_update_flag == ENABLE)
        return SUCCESS;
    
    send_len = set_wifi_uart_byte(send_len,dpid);
    send_len = set_wifi_uart_byte(send_len,DP_TYPE_ENUM);
    //
    send_len = set_wifi_uart_byte(send_len,0);
    send_len = set_wifi_uart_byte(send_len,1);
    //
    send_len = set_wifi_uart_byte(send_len,value);
    
    wifi_uart_write_frame(STATE_UPLOAD_CMD,MCU_TX_VER,send_len);
    
    return SUCCESS;
}

/**
 * @brief  fault鍨媎p鏁版嵁涓婁紶
 * @param[in] {dpid} dpid鍙�
 * @param[in] {value} 褰撳墠dp鍊�
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_fault_update(unsigned char dpid,unsigned long value)
{
    unsigned short send_len = 0;
     
    if(stop_update_flag == ENABLE)
        return SUCCESS;
    
    send_len = set_wifi_uart_byte(send_len,dpid);
    send_len = set_wifi_uart_byte(send_len,DP_TYPE_BITMAP);
    //
    send_len = set_wifi_uart_byte(send_len,0);
    
    if((value | 0xff) == 0xff) {
        send_len = set_wifi_uart_byte(send_len,1);
        send_len = set_wifi_uart_byte(send_len,value);
    }else if((value | 0xffff) == 0xffff) {
        send_len = set_wifi_uart_byte(send_len,2);
        send_len = set_wifi_uart_byte(send_len,value >> 8);
        send_len = set_wifi_uart_byte(send_len,value & 0xff);
    }else {
        send_len = set_wifi_uart_byte(send_len,4);
        send_len = set_wifi_uart_byte(send_len,value >> 24);
        send_len = set_wifi_uart_byte(send_len,value >> 16);
        send_len = set_wifi_uart_byte(send_len,value >> 8);
        send_len = set_wifi_uart_byte(send_len,value & 0xff);
    }    
    
    wifi_uart_write_frame(STATE_UPLOAD_CMD, MCU_TX_VER, send_len);

    return SUCCESS;
}

#ifdef MCU_DP_UPLOAD_SYN
/**
 * @brief  raw鍨媎p鏁版嵁鍚屾涓婁紶
 * @param[in] {dpid} dpid鍙�
 * @param[in] {value} 褰撳墠dp鍊兼寚閽�
 * @param[in] {len} 鏁版嵁闀垮害
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_raw_update_syn(unsigned char dpid,const unsigned char value[],unsigned short len)
{
    unsigned short send_len = 0;
    
    if(stop_update_flag == ENABLE)
        return SUCCESS;
    //
    send_len = set_wifi_uart_byte(send_len,dpid);
    send_len = set_wifi_uart_byte(send_len,DP_TYPE_RAW);
    //
    send_len = set_wifi_uart_byte(send_len,len / 0x100);
    send_len = set_wifi_uart_byte(send_len,len % 0x100);
    //
    send_len = set_wifi_uart_buffer(send_len,(unsigned char *)value,len);
    
    wifi_uart_write_frame(STATE_UPLOAD_SYN_CMD,MCU_TX_VER,send_len);
    
    return SUCCESS;
}

/**
 * @brief  bool鍨媎p鏁版嵁鍚屾涓婁紶
 * @param[in] {dpid} dpid鍙�
 * @param[in] {value} 褰撳墠dp鍊兼寚閽�
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_bool_update_syn(unsigned char dpid,unsigned char value)
{
    unsigned short send_len = 0;
    
    if(stop_update_flag == ENABLE)
        return SUCCESS;
    
    send_len = set_wifi_uart_byte(send_len,dpid);
    send_len = set_wifi_uart_byte(send_len,DP_TYPE_BOOL);
    //
    send_len = set_wifi_uart_byte(send_len,0);
    send_len = set_wifi_uart_byte(send_len,1);
    //
    if(value == FALSE) {
        send_len = set_wifi_uart_byte(send_len,FALSE);
    }else {
        send_len = set_wifi_uart_byte(send_len,1);
    }
    
    wifi_uart_write_frame(STATE_UPLOAD_SYN_CMD, MCU_TX_VER, send_len);
    
    return SUCCESS;
}

/**
 * @brief  value鍨媎p鏁版嵁鍚屾涓婁紶
 * @param[in] {dpid} dpid鍙�
 * @param[in] {value} 褰撳墠dp鍊兼寚閽�
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_value_update_syn(unsigned char dpid,unsigned long value)
{
    unsigned short send_len = 0;
    
    if(stop_update_flag == ENABLE)
        return SUCCESS;
    
    send_len = set_wifi_uart_byte(send_len,dpid);
    send_len = set_wifi_uart_byte(send_len,DP_TYPE_VALUE);
    //
    send_len = set_wifi_uart_byte(send_len,0);
    send_len = set_wifi_uart_byte(send_len,4);
    //
    send_len = set_wifi_uart_byte(send_len,value >> 24);
    send_len = set_wifi_uart_byte(send_len,value >> 16);
    send_len = set_wifi_uart_byte(send_len,value >> 8);
    send_len = set_wifi_uart_byte(send_len,value & 0xff);
    
    wifi_uart_write_frame(STATE_UPLOAD_SYN_CMD, MCU_TX_VER, send_len);
    
    return SUCCESS;
}

/**
 * @brief  string鍨媎p鏁版嵁鍚屾涓婁紶
 * @param[in] {dpid} dpid鍙�
 * @param[in] {value} 褰撳墠dp鍊兼寚閽�
 * @param[in] {len} 鏁版嵁闀垮害
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_string_update_syn(unsigned char dpid,const unsigned char value[],unsigned short len)
{
    unsigned short send_len = 0;
    
    if(stop_update_flag == ENABLE)
        return SUCCESS;
    //
    send_len = set_wifi_uart_byte(send_len,dpid);
    send_len = set_wifi_uart_byte(send_len,DP_TYPE_STRING);
    //
    send_len = set_wifi_uart_byte(send_len,len / 0x100);
    send_len = set_wifi_uart_byte(send_len,len % 0x100);
    //
    send_len = set_wifi_uart_buffer(send_len,(unsigned char *)value,len);
    
    wifi_uart_write_frame(STATE_UPLOAD_SYN_CMD,MCU_TX_VER,send_len);
    
    return SUCCESS;
}

/**
 * @brief  enum鍨媎p鏁版嵁鍚屾涓婁紶
 * @param[in] {dpid} dpid鍙�
 * @param[in] {value} 褰撳墠dp鍊兼寚閽�
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_enum_update_syn(unsigned char dpid,unsigned char value)
{
    unsigned short send_len = 0;
    
    if(stop_update_flag == ENABLE)
        return SUCCESS;
    
    send_len = set_wifi_uart_byte(send_len,dpid);
    send_len = set_wifi_uart_byte(send_len,DP_TYPE_ENUM);
    //
    send_len = set_wifi_uart_byte(send_len,0);
    send_len = set_wifi_uart_byte(send_len,1);
    
    send_len = set_wifi_uart_byte(send_len,value);
    
    wifi_uart_write_frame(STATE_UPLOAD_SYN_CMD,MCU_TX_VER,send_len);
    
    return SUCCESS;
}

/**
 * @brief  fault鍨媎p鏁版嵁鍚屾涓婁紶
 * @param[in] {dpid} dpid鍙�
 * @param[in] {value} 褰撳墠dp鍊兼寚閽�
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_fault_update_syn(unsigned char dpid,unsigned long value)
{
    unsigned short send_len = 0;
     
    if(stop_update_flag == ENABLE)
        return SUCCESS;
    
    send_len = set_wifi_uart_byte(send_len,dpid);
    send_len = set_wifi_uart_byte(send_len,DP_TYPE_BITMAP);
    //
    send_len = set_wifi_uart_byte(send_len,0);
    
    if((value | 0xff) == 0xff) {
        send_len = set_wifi_uart_byte(send_len,1);
        send_len = set_wifi_uart_byte(send_len,value);
    }else if((value | 0xffff) == 0xffff) {
        send_len = set_wifi_uart_byte(send_len,2);
        send_len = set_wifi_uart_byte(send_len,value >> 8);
        send_len = set_wifi_uart_byte(send_len,value & 0xff);
    }else {
        send_len = set_wifi_uart_byte(send_len,4);
        send_len = set_wifi_uart_byte(send_len,value >> 24);
        send_len = set_wifi_uart_byte(send_len,value >> 16);
        send_len = set_wifi_uart_byte(send_len,value >> 8);
        send_len = set_wifi_uart_byte(send_len,value & 0xff);
    }    
    
    wifi_uart_write_frame(STATE_UPLOAD_SYN_CMD,MCU_TX_VER,send_len);

    return SUCCESS;
}
#endif

/**
 * @brief  mcu鑾峰彇bool鍨嬩笅鍙慸p鍊�
 * @param[in] {value} dp鏁版嵁缂撳啿鍖哄湴鍧�
 * @param[in] {len} dp鏁版嵁闀垮害
 * @return 褰撳墠dp鍊�
 * @note   Null
 */
unsigned char mcu_get_dp_download_bool(const unsigned char value[],unsigned short len)
{
    return(value[0]);
}

/**
 * @brief  mcu鑾峰彇enum鍨嬩笅鍙慸p鍊�
 * @param[in] {value} dp鏁版嵁缂撳啿鍖哄湴鍧�
 * @param[in] {len} dp鏁版嵁闀垮害
 * @return 褰撳墠dp鍊�
 * @note   Null
 */
unsigned char mcu_get_dp_download_enum(const unsigned char value[],unsigned short len)
{
    return(value[0]);
}

/**
 * @brief  mcu鑾峰彇value鍨嬩笅鍙慸p鍊�
 * @param[in] {value} dp鏁版嵁缂撳啿鍖哄湴鍧�
 * @param[in] {len} dp鏁版嵁闀垮害
 * @return 褰撳墠dp鍊�
 * @note   Null
 */
unsigned long mcu_get_dp_download_value(const unsigned char value[],unsigned short len)
{
    return(byte_to_int(value));
}

/**
 * @brief  涓插彛鎺ユ敹鏁版嵁鏆傚瓨澶勭悊
 * @param[in] {value} 涓插彛鏀跺埌鐨�1瀛楄妭鏁版嵁
 * @return Null
 * @note   鍦∕CU涓插彛澶勭悊鍑芥暟涓皟鐢ㄨ鍑芥暟,骞跺皢鎺ユ敹鍒扮殑鏁版嵁浣滀负鍙傛暟浼犲叆
 */
void uart_receive_input(unsigned char value)
{
   // #error "璇峰湪涓插彛鎺ユ敹涓柇涓皟鐢╱art_receive_input(value),涓插彛鏁版嵁鐢盡CU_SDK澶勭悊,鐢ㄦ埛璇峰嬁鍐嶅彟琛屽鐞�,瀹屾垚鍚庡垹闄よ琛�"
    
    if(1 == rx_buf_out - rx_buf_in) {
        //涓插彛鎺ユ敹缂撳瓨宸叉弧
    }else if((rx_buf_in > rx_buf_out) && ((rx_buf_in - rx_buf_out) >= sizeof(wifi_uart_rx_buf))) {
        //涓插彛鎺ユ敹缂撳瓨宸叉弧
    }else {
        //涓插彛鎺ユ敹缂撳瓨鏈弧
        if(rx_buf_in >= (unsigned char *)(wifi_uart_rx_buf + sizeof(wifi_uart_rx_buf))) {
            rx_buf_in = (unsigned char *)(wifi_uart_rx_buf);
        }
        
        *rx_buf_in ++ = value;
    }
}

/**
 * @brief  涓插彛鎺ユ敹澶氫釜瀛楄妭鏁版嵁鏆傚瓨澶勭悊
 * @param[in] {value} 涓插彛瑕佹帴鏀剁殑鏁版嵁鐨勬簮鍦板潃
 * @param[in] {data_len} 涓插彛瑕佹帴鏀剁殑鏁版嵁鐨勬暟鎹暱搴�
 * @return Null
 * @note   濡傞渶瑕佹敮鎸佷竴娆″瀛楄妭缂撳瓨锛屽彲璋冪敤璇ュ嚱鏁�
 */
void uart_receive_buff_input(unsigned char value[], unsigned short data_len)
{
  //  #error "璇峰湪闇�瑕佷竴娆＄紦瀛樺涓瓧鑺備覆鍙ｆ暟鎹璋冪敤姝ゅ嚱鏁�,涓插彛鏁版嵁鐢盡CU_SDK澶勭悊,鐢ㄦ埛璇峰嬁鍐嶅彟琛屽鐞�,瀹屾垚鍚庡垹闄よ琛�"
    
    unsigned short i = 0;
    for(i = 0; i < data_len; i++) {
        uart_receive_input(value[i]);
    }
}

/**
 * @brief  wifi涓插彛鏁版嵁澶勭悊鏈嶅姟
 * @param  Null
 * @return Null
 * @note   鍦∕CU涓诲嚱鏁皐hile寰幆涓皟鐢ㄨ鍑芥暟
 */
void wifi_uart_service(void)
{
   // #error "璇风洿鎺ュ湪main鍑芥暟鐨剋hile(1){}涓坊鍔爓ifi_uart_service(),璋冪敤璇ュ嚱鏁颁笉瑕佸姞浠讳綍鏉′欢鍒ゆ柇,瀹屾垚鍚庡垹闄よ琛�"
    static unsigned short rx_in = 0;
    unsigned short offset = 0;
    unsigned short rx_value_len = 0;
    
    while((rx_in < sizeof(wifi_data_process_buf)) && with_data_rxbuff() > 0) {
        wifi_data_process_buf[rx_in ++] = take_byte_rxbuff();
    }
    
    if(rx_in < PROTOCOL_HEAD)
        return;
    
    while((rx_in - offset) >= PROTOCOL_HEAD) {
        if(wifi_data_process_buf[offset + HEAD_FIRST] != FRAME_FIRST) {
            offset ++;
            continue;
        }
        
        if(wifi_data_process_buf[offset + HEAD_SECOND] != FRAME_SECOND) {
            offset ++;
            continue;
        }  
        
        if(wifi_data_process_buf[offset + PROTOCOL_VERSION] != MCU_RX_VER) {
            offset += 2;
            continue;
        }      
        
        rx_value_len = wifi_data_process_buf[offset + LENGTH_HIGH] * 0x100;
        rx_value_len += (wifi_data_process_buf[offset + LENGTH_LOW] + PROTOCOL_HEAD);
        if(rx_value_len > sizeof(wifi_data_process_buf) + PROTOCOL_HEAD) {
            offset += 3;
            continue;
        }
        
        if((rx_in - offset) < rx_value_len) {
            break;
        }
        
        //鏁版嵁鎺ユ敹瀹屾垚
        if(get_check_sum((unsigned char *)wifi_data_process_buf + offset,rx_value_len - 1) != wifi_data_process_buf[offset + rx_value_len - 1]) {
            //鏍￠獙鍑洪敊
            //printf("crc error (crc:0x%X  but data:0x%X)\r\n",get_check_sum((unsigned char *)wifi_data_process_buf + offset,rx_value_len - 1),wifi_data_process_buf[offset + rx_value_len - 1]);
            offset += 3;
            continue;
        }
        
        data_handle(offset);
        offset += rx_value_len;
    }//end while

    rx_in -= offset;
    if(rx_in > 0) {
        my_memcpy((char *)wifi_data_process_buf, (const char *)wifi_data_process_buf + offset, rx_in);
    }
}

/**
 * @brief  鍗忚涓插彛鍒濆鍖栧嚱鏁�
 * @param  Null
 * @return Null
 * @note   鍦∕CU鍒濆鍖栦唬鐮佷腑璋冪敤璇ュ嚱鏁�
 */
void wifi_protocol_init(void)
{
  //  #error " 璇峰湪main鍑芥暟涓坊鍔爓ifi_protocol_init()瀹屾垚wifi鍗忚鍒濆鍖�,骞跺垹闄よ琛�"
    rx_buf_in = (unsigned char *)wifi_uart_rx_buf;
    rx_buf_out = (unsigned char *)wifi_uart_rx_buf;
    
    stop_update_flag = DISABLE;
    
#ifndef WIFI_CONTROL_SELF_MODE
    wifi_work_state = WIFI_SATE_UNKNOW;
#endif
}



#ifndef WIFI_CONTROL_SELF_MODE
/**
 * @brief  MCU鑾峰彇澶嶄綅wifi鎴愬姛鏍囧織
 * @param  Null
 * @return 澶嶄綅鏍囧織
 * -           0(RESET_WIFI_ERROR):澶辫触
 * -           1(RESET_WIFI_SUCCESS):鎴愬姛
 * @note   1:MCU涓诲姩璋冪敤mcu_reset_wifi()鍚庤皟鐢ㄨ鍑芥暟鑾峰彇澶嶄綅鐘舵��
 *         2:濡傛灉涓烘ā鍧楄嚜澶勭悊妯″紡,MCU鏃犻』璋冪敤璇ュ嚱鏁�
 */
unsigned char mcu_get_reset_wifi_flag(void)
{
    return reset_wifi_flag;
}

/**
 * @brief  MCU涓诲姩閲嶇疆wifi宸ヤ綔妯″紡
 * @param  Null
 * @return Null
 * @note   1:MCU涓诲姩璋冪敤,閫氳繃mcu_get_reset_wifi_flag()鍑芥暟鑾峰彇閲嶇疆wifi鏄惁鎴愬姛
 *         2:濡傛灉涓烘ā鍧楄嚜澶勭悊妯″紡,MCU鏃犻』璋冪敤璇ュ嚱鏁�
 */
void mcu_reset_wifi(void)
{
    reset_wifi_flag = RESET_WIFI_ERROR;
    
    wifi_uart_write_frame(WIFI_RESET_CMD, MCU_TX_VER, 0);
}

/**
 * @brief  鑾峰彇璁剧疆wifi鐘舵�佹垚鍔熸爣蹇�
 * @param  Null
 * @return wifimode flag
 * -           0(SET_WIFICONFIG_ERROR):澶辫触
 * -           1(SET_WIFICONFIG_SUCCESS):鎴愬姛
 * @note   1:MCU涓诲姩璋冪敤mcu_set_wifi_mode()鍚庤皟鐢ㄨ鍑芥暟鑾峰彇澶嶄綅鐘舵��
 *         2:濡傛灉涓烘ā鍧楄嚜澶勭悊妯″紡,MCU鏃犻』璋冪敤璇ュ嚱鏁�
 */
unsigned char mcu_get_wifimode_flag(void)
{
    return set_wifimode_flag;
}

/**
 * @brief  MCU璁剧疆wifi宸ヤ綔妯″紡
 * @param[in] {mode} 杩涘叆鐨勬ā寮�
 * @ref        0(SMART_CONFIG):杩涘叆smartconfig妯″紡
 * @ref        1(AP_CONFIG):杩涘叆AP妯″紡
 * @return Null
 * @note   1:MCU涓诲姩璋冪敤
 *         2:鎴愬姛鍚�,鍙垽鏂璼et_wifi_config_state鏄惁涓篢RUE;TRUE琛ㄧず涓鸿缃畐ifi宸ヤ綔妯″紡鎴愬姛
 *         3:濡傛灉涓烘ā鍧楄嚜澶勭悊妯″紡,MCU鏃犻』璋冪敤璇ュ嚱鏁�
 */
void mcu_set_wifi_mode(unsigned char mode)
{
    unsigned char length = 0;
    
    set_wifimode_flag = SET_WIFICONFIG_ERROR;
    
    length = set_wifi_uart_byte(length, mode);
    
    wifi_uart_write_frame(WIFI_MODE_CMD, MCU_TX_VER, length);
}

/**
 * @brief  MCU涓诲姩鑾峰彇褰撳墠wifi宸ヤ綔鐘舵��
 * @param  Null
 * @return wifi work state
 * -          SMART_CONFIG_STATE: smartconfig閰嶇疆鐘舵��
 * -          AP_STATE: AP閰嶇疆鐘舵��
 * -          WIFI_NOT_CONNECTED: WIFI閰嶇疆鎴愬姛浣嗘湭杩炰笂璺敱鍣�
 * -          WIFI_CONNECTED: WIFI閰嶇疆鎴愬姛涓旇繛涓婅矾鐢卞櫒
 * -          WIFI_CONN_CLOUD: WIFI宸茬粡杩炴帴涓婁簯鏈嶅姟鍣�
 * -          WIFI_LOW_POWER: WIFI澶勪簬浣庡姛鑰楁ā寮�
 * -          SMART_AND_AP_STATE: WIFI smartconfig&AP 妯″紡
 * @note   濡傛灉涓烘ā鍧楄嚜澶勭悊妯″紡,MCU鏃犻』璋冪敤璇ュ嚱鏁�
 */
unsigned char mcu_get_wifi_work_state(void)
{
    return wifi_work_state;
}
#endif

#ifdef SUPPORT_GREEN_TIME
/**
 * @brief  MCU鑾峰彇鏍兼灄鏃堕棿
 * @param  Null
 * @return Null
 * @note   MCU闇�瑕佽嚜琛岃皟鐢ㄨ鍔熻兘
 */
void mcu_get_green_time(void)
{
    wifi_uart_write_frame(GET_ONLINE_TIME_CMD, MCU_TX_VER, 0);
}
#endif

#ifdef SUPPORT_MCU_RTC_CHECK
/**
 * @brief  MCU鑾峰彇绯荤粺鏃堕棿,鐢ㄤ簬鏍″鏈湴鏃堕挓
 * @param  Null
 * @return Null
 * @note   MCU涓诲姩璋冪敤瀹屾垚鍚庡湪mcu_write_rtctime鍑芥暟鍐呮牎瀵箁tc鏃堕挓
 */
void mcu_get_system_time(void)
{
    wifi_uart_write_frame(GET_LOCAL_TIME_CMD, MCU_TX_VER, 0);
}
#endif

#ifdef WIFI_TEST_ENABLE
/**
 * @brief  mcu鍙戣捣wifi鍔熻兘娴嬭瘯
 * @param  Null
 * @return Null
 * @note   MCU闇�瑕佽嚜琛岃皟鐢ㄨ鍔熻兘
 */
void mcu_start_wifitest(void)
{
    wifi_uart_write_frame(WIFI_TEST_CMD, MCU_TX_VER, 0);
}
#endif

#ifdef WIFI_HEARTSTOP_ENABLE
/**
 * @brief  閫氱煡WIFI妯＄粍鍏抽棴蹇冭烦
 * @param  Null
 * @return Null
 * @note   MCU闇�瑕佽嚜琛岃皟鐢ㄨ鍔熻兘
 */
void wifi_heart_stop(void)
{
    wifi_uart_write_frame(HEAT_BEAT_STOP, MCU_TX_VER, 0);
}
#endif

#ifdef GET_WIFI_STATUS_ENABLE
/**
 * @brief  鑾峰彇褰撳墠wifi鑱旂綉鐘舵��
 * @param  Null
 * @return Null
 * @note   MCU闇�瑕佽嚜琛岃皟鐢ㄨ鍔熻兘
 */
void mcu_get_wifi_connect_status(void)
{
    wifi_uart_write_frame(GET_WIFI_STATUS_CMD, MCU_TX_VER, 0);
}
#endif

#ifdef WIFI_STREAM_ENABLE
/**
 * @brief  娴佹湇鍔″彂閫�
 * @param[in] {id} ID鍙�
 * @param[in] {buffer} 鍙戦�佸寘鐨勫湴鍧�
 * @param[in] {buf_len} 鍙戦�佸寘闀垮害
 * @return 娴佹湇鍔′紶杈撶粨鏋�
 * -           0(ERROR): 澶辫触
 * -           1(SUCCESS): 鎴愬姛
 * @note   MCU闇�瑕佽嚜琛屽疄鐜拌鍔熻兘
 */
unsigned char stream_trans_send(unsigned int id, unsigned char *buffer, unsigned long buf_len)
{
    unsigned long map_offset = 0;
    unsigned int pack_num = 0;
    unsigned int rest_length = 0;

    if(stop_update_flag == ENABLE)
        return ERROR;

    pack_num = buf_len / STREM_PACK_LEN;
    rest_length = buf_len - pack_num * STREM_PACK_LEN;
    if (rest_length > 0) {
        pack_num++;
    }

    int this_len = STREM_PACK_LEN;
    for (int cnt = 0; cnt < pack_num; cnt++,map_offset += this_len) {
        if (cnt == pack_num - 1 && rest_length > 0) {
            this_len = rest_length;
        }else {
            this_len = STREM_PACK_LEN;
        }

        if(ERROR == stream_trans(id, map_offset, buffer + map_offset, this_len)) {
            //mcu姝ｅ湪鍗囩骇涓紝涓嶅彲浠ヨ繘琛屾祦鏈嶅姟浼犺緭
            //printf("is upgrade\n");
            return ERROR;
        }
        
        #error "璇锋牴鎹彁绀猴紝鑷瀹屽杽娴佹湇鍔″彂閫佷唬鐮侊紝瀹屾垚鍚庤鍒犻櫎璇ヨ"
        /*  濡傛灉MCU鍙互浣跨敤澶氳繘绋嬫垨澶氱嚎绋嬶紝鍙互灏嗘鍑芥暟鏀惧湪涓�涓崟鐙殑杩涚▼鎴栫嚎绋嬮噷鎵ц锛屽苟鎵撳紑涓嬮潰鎵�绀虹殑浠ｇ爜  */
        /*
        while(0xff == stream_status); //绛夊緟妯″潡鍥炲
        
        if(0x00 != stream_status) {
            //澶辫触  鍙湪 stream_trans_send_result 鍑芥暟涓煡鐪嬮敊璇爜
            return ERROR;
        }
        */
        
        /*  濡傛灉MCU涓嶆敮鎸佸杩涚▼鎴栧绾跨▼锛屼娇鐢ㄦ鍑芥暟鏃舵瘡娆″彧鍙戜竴鍖咃紙鏁版嵁闀垮害涓嶅ぇ浜嶴TREM_PACK_LEN锛夛紝
        鍙戦�佸畬涔嬪悗鍦� stream_trans_send_result 鍑芥暟涓鐞嗘ā鍧楄繑鍥炵殑缁撴灉锛屽彂閫佹垚鍔熸椂鍐嶆璋冪敤姝ゅ嚱鏁板彂閫佷笅涓�鍖咃紝娉ㄦ剰鍖呭亸绉昏澧炲姞  */
    }
    
    return SUCCESS;
}

/**
 * @brief  澶氬湴鍥炬祦鏈嶅姟鍙戦��
 * @param[in] {id} 鍦板浘娴佹湇鍔′細璇滻D
 * @param[in] {sub_id} 瀛愬湴鍥綢D
 * @param[in] {sub_id_pro_mode} 瀛愬湴鍥綢D鏁版嵁澶勭悊鏂瑰紡
 * @ref       0x00: 缁х画绱姞
 * @ref       0x01: 娓呴櫎涓婁紶鐨勬暟鎹�
 * @param[in] {buffer} 鏁版嵁鍖呭彂閫佺殑鍦板潃
 * @param[in] {buf_len} 鏁版嵁鍖呭彂閫佺殑闀垮害
 * @return 娴佹湇鍔′紶杈撶粨鏋�
 * -           0(ERROR): 澶辫触
 * -           1(SUCCESS): 鎴愬姛
 * @note   MCU闇�瑕佽嚜琛屽疄鐜拌鍔熻兘
 */
unsigned char maps_stream_trans_send(unsigned int id, unsigned char sub_id, unsigned char sub_id_pro_mode, unsigned char *buffer, unsigned long buf_len)
{
    unsigned long map_offset = 0;
    unsigned int pack_num = 0;
    unsigned int rest_length = 0;
    unsigned char pro_ver = 0; //鍦板浘鏈嶅姟鍗忚鐗堟湰 榛樿涓�0

    if(stop_update_flag == ENABLE)
        return SUCCESS;

    pack_num = buf_len / STREM_PACK_LEN;
    rest_length = buf_len - pack_num * STREM_PACK_LEN;
    if (rest_length > 0) {
        pack_num++;
    }

    int this_len = STREM_PACK_LEN;
    for (int cnt = 0; cnt < pack_num; cnt++,map_offset += this_len) {
        if (cnt == pack_num - 1 && rest_length > 0) {
            this_len = rest_length;
        }else {
            this_len = STREM_PACK_LEN;
        }

        if(ERROR == maps_stream_trans(pro_ver, id, sub_id, sub_id_pro_mode, map_offset, buffer + map_offset, this_len)) {
            //mcu姝ｅ湪鍗囩骇涓紝涓嶅彲浠ヨ繘琛屾祦鏈嶅姟浼犺緭
            //printf("is upgrade\n");
            return ERROR;
        }
        
        #error "璇锋牴鎹彁绀猴紝鑷瀹屽杽娴佹湇鍔″彂閫佷唬鐮侊紝瀹屾垚鍚庤鍒犻櫎璇ヨ"
        /*  濡傛灉MCU鍙互浣跨敤澶氳繘绋嬫垨澶氱嚎绋嬶紝鍙互灏嗘鍑芥暟鏀惧湪涓�涓崟鐙殑杩涚▼鎴栫嚎绋嬮噷鎵ц锛屽苟鎵撳紑涓嬮潰鎵�绀虹殑浠ｇ爜  */
        /*
        while(0xff == maps_stream_status); //绛夊緟妯″潡鍥炲
        
        if(0x00 != maps_stream_status) {
            //澶辫触  鍙湪 maps_stream_trans_send_result 鍑芥暟涓煡鐪嬮敊璇爜
            return ERROR;
        }
        */
        
        /*  濡傛灉MCU涓嶆敮鎸佸杩涚▼鎴栧绾跨▼锛屼娇鐢ㄦ鍑芥暟鏃舵瘡娆″彧鍙戜竴鍖咃紙鏁版嵁闀垮害涓嶅ぇ浜嶴TREM_PACK_LEN锛夛紝
        鍙戦�佸畬涔嬪悗鍦� maps_stream_trans_send_result 鍑芥暟涓鐞嗘ā鍧楄繑鍥炵殑缁撴灉锛屽彂閫佹垚鍔熸椂鍐嶆璋冪敤姝ゅ嚱鏁板彂閫佷笅涓�鍖咃紝娉ㄦ剰鍖呭亸绉昏澧炲姞  */
    }
    
    return SUCCESS;
}
#endif

#ifdef WIFI_CONNECT_TEST_ENABLE
/**
 * @brief  mcu鍙戣捣wifi鍔熻兘娴嬭瘯(杩炴帴鎸囧畾璺敱)
 * @param[in] {ssid_buf} 瀛樻斁璺敱鍣ㄥ悕绉板瓧绗︿覆鏁版嵁鐨勫湴鍧�(ssid闀垮害鏈�澶ф敮鎸�32涓瓧鑺�)
 * @param[in] {passwd_buffer} 瀛樻斁璺敱鍣ㄥ悕绉板瓧绗︿覆鏁版嵁鐨勫湴鍧�(passwd闀垮害鏈�澶ф敮鎸�64涓瓧鑺�)
 * @return Null
 * @note   MCU闇�瑕佽嚜琛岃皟鐢ㄨ鍔熻兘
 */
void mcu_start_connect_wifitest(unsigned char *ssid_buf,unsigned char *passwd_buffer)
{
    unsigned short send_len = 0;

    if( my_strlen(ssid_buf) > 32 || my_strlen(passwd_buffer) > 64) {
        //printf("ssid_buf or passwd_buffer is too long!");
        return;
    }
    
    send_len = set_wifi_uart_buffer(send_len, "{\"ssid\":\"", my_strlen("{\"ssid\":\""));
    send_len = set_wifi_uart_buffer(send_len,ssid_buf,my_strlen(ssid_buf));
    send_len = set_wifi_uart_buffer(send_len, "\",\"password\":\"", my_strlen("\",\"password\":\""));
    send_len = set_wifi_uart_buffer(send_len,passwd_buffer,my_strlen(passwd_buffer));
    send_len = set_wifi_uart_buffer(send_len, "\"}", my_strlen("\"}"));

    wifi_uart_write_frame(WIFI_CONNECT_TEST_CMD, MCU_TX_VER, send_len);
}
#endif

#ifdef GET_MODULE_MAC_ENABLE
/**
 * @brief  鑾峰彇妯″潡MAC
 * @param  Null
 * @return Null
 * @note   MCU闇�瑕佽嚜琛岃皟鐢ㄨ鍔熻兘
 */
void mcu_get_module_mac(void)
{
    wifi_uart_write_frame(GET_MAC_CMD, MCU_TX_VER, 0);
}
#endif

#ifdef IR_TX_RX_TEST_ENABLE
/**
 * @brief  mcu鍙戣捣绾㈠杩涘叆鏀跺彂浜ф祴
 * @param  Null
 * @return Null
 * @note   MCU闇�瑕佽嚜琛岃皟鐢ㄨ鍔熻兘
 */
void mcu_start_ir_test(void)
{
    wifi_uart_write_frame(IR_TX_RX_TEST_CMD, MCU_TX_VER, 0);
}
#endif

#ifdef MODULE_EXPANDING_SERVICE_ENABLE
/**
 * @brief  鎵撳紑妯″潡鏃堕棿鏈嶅姟閫氱煡
 * @param[in] {time_type} 鏃堕棿绫诲瀷
 * @ref       0x00: 鏍兼灄鏃堕棿
 * @ref       0x01: 鏈湴鏃堕棿
 * @return Null
 * @note   MCU闇�瑕佽嚜琛岃皟鐢ㄨ鍔熻兘
 */
void open_module_time_serve(unsigned char time_type)
{
    unsigned short send_len = 0;
    send_len = set_wifi_uart_byte(send_len, 0x01);
    send_len = set_wifi_uart_byte(send_len, time_type);
    wifi_uart_write_frame(MODULE_EXTEND_FUN_CMD, MCU_TX_VER, send_len);
}

/**
 * @brief  涓诲姩璇锋眰澶╂皵鏈嶅姟鏁版嵁
 * @param  Null
 * @return Null
 * @note   MCU闇�瑕佽嚜琛岃皟鐢ㄨ鍔熻兘
 */
void request_weather_serve(void)
{
    unsigned short send_len = 0;
    send_len = set_wifi_uart_byte(send_len, 0x03);
    wifi_uart_write_frame(MODULE_EXTEND_FUN_CMD, MCU_TX_VER, send_len);
}

/**
 * @brief  鎵撳紑妯″潡閲嶇疆鐘舵�侀�氱煡
 * @param  Null
 * @return Null
 * @note   MCU闇�瑕佽嚜琛岃皟鐢ㄨ鍔熻兘
 */
void open_module_reset_state_serve(void)
{
    unsigned short send_len = 0;
    send_len = set_wifi_uart_byte(send_len, 0x04);
    wifi_uart_write_frame(MODULE_EXTEND_FUN_CMD, MCU_TX_VER, send_len);
}
#endif

#ifdef BLE_RELATED_FUNCTION_ENABLE
/**
 * @brief  mcu鍙戣捣钃濈墮鍔熻兘鎬ф祴璇曪紙鎵弿鎸囧畾钃濈墮淇℃爣锛�
 * @param  Null
 * @return Null
 * @note   MCU闇�瑕佽嚜琛岃皟鐢ㄨ鍔熻兘
 */
void mcu_start_BLE_test(void)
{
    unsigned short send_len = 0;
    send_len = set_wifi_uart_byte(send_len, 0x01);
    wifi_uart_write_frame(BLE_TEST_CMD, MCU_TX_VER, send_len);
}
#endif

#ifdef VOICE_MODULE_PROTOCOL_ENABLE
/**
 * @brief  鑾峰彇璇煶鐘舵�佺爜
 * @param  Null
 * @return Null
 * @note   MCU闇�瑕佽嚜琛岃皟鐢ㄨ鍔熻兘
 */
void get_voice_state(void)
{
    wifi_uart_write_frame(GET_VOICE_STATE_CMD, MCU_TX_VER, 0);
}

/**
 * @brief  MIC闈欓煶璁剧疆
 * @param[in] {set_val} 闈欓煶璁剧疆鍊�
 * @ref       0x00: mic寮�鍚�
 * @ref       0x01: mic闈欓煶
 * @ref       0xA0: 鏌ヨ闈欓煶鐘舵��
 * @return Null
 * @note   MCU闇�瑕佽嚜琛岃皟鐢ㄨ鍔熻兘
 */
void set_voice_MIC_silence(unsigned char set_val)
{
    unsigned short send_len = 0;
    send_len = set_wifi_uart_byte(send_len, set_val);
    wifi_uart_write_frame(MIC_SILENCE_CMD, MCU_TX_VER, send_len);
}

/**
 * @brief  speaker闊抽噺璁剧疆
 * @param[in] {set_val} 闊抽噺璁剧疆鍊�
 * @ref       0~10: 闊抽噺鑼冨洿
 * @ref       0xA0: 鏌ヨ闊抽噺鍊�
 * @return Null
 * @note   MCU闇�瑕佽嚜琛岃皟鐢ㄨ鍔熻兘
 */
void set_speaker_voice(unsigned char set_val)
{
    unsigned short send_len = 0;
    send_len = set_wifi_uart_byte(send_len, set_val);
    wifi_uart_write_frame(SET_SPEAKER_VOLUME_CMD, MCU_TX_VER, send_len);
}

/**
 * @brief  闊抽浜ф祴
 * @param[in] {set_val} 闊抽浜ф祴鍊�
 * @ref       0x00: 鍏抽棴闊抽浜ф祴
 * @ref       0x01: mic1闊抽鐜矾娴嬭瘯
 * @ref       0x02: mic2闊抽鐜矾娴嬭瘯
 * @ref       0xA0: 鏌ヨ褰撳墠浜ф祴鐘舵��
 * @return Null
 * @note   MCU闇�瑕佽嚜琛岃皟鐢ㄨ鍔熻兘
 */
void voice_test(unsigned char test_val)
{
    unsigned short send_len = 0;
    send_len = set_wifi_uart_byte(send_len, test_val);
    wifi_uart_write_frame(VOICE_TEST_CMD, MCU_TX_VER, send_len);
}

/**
 * @brief  鍞ら啋浜ф祴
 * @param  Null
 * @return Null
 * @note   MCU闇�瑕佽嚜琛岃皟鐢ㄨ鍔熻兘
 */
void voice_awaken_test(void)
{
    wifi_uart_write_frame(VOICE_AWAKEN_TEST_CMD, MCU_TX_VER, 0);
}

/**
 * @brief  璇煶妯＄粍MCU鍔熻兘璁剧疆
 * @param[in] {play} 鎾斁/鏆傚仠鍔熻兘 1(鎾斁) / 0(鏆傚仠)
 * @param[in] {bt_play} 钃濈墮寮�鍏冲姛鑳� 1(寮�) / 0(鍏�)
 * @return Null
 * @note   MCU闇�瑕佽嚜琛岃皟鐢ㄨ鍔熻兘
 */
void voice_mcu_fun_set(unsigned char play, unsigned char bt_play)
{
    unsigned short send_len = 0;
    unsigned char str[50];
    
    //MCU璁剧疆鏆備粎鏀寔鈥濇挱鏀�/鏆傚仠鈥� 鈥濊摑鐗欏紑鍏斥��
    
    sprintf((char*)str,"{\"play\":%s,\"bt_play\":%s}", play?"true":"false", bt_play?"true":"false");
    
    send_len = set_wifi_uart_byte(send_len, 0x00);
    send_len = set_wifi_uart_buffer(send_len, str, my_strlen(str));
    wifi_uart_write_frame(VOICE_EXTEND_FUN_CMD, MCU_TX_VER, send_len);
}
#endif


