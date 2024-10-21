#ifndef kiy_core_h
#define kiy_core_h

#include <stdio.h>

#define KIY_CORE_API_VER "V2.1.0.2"

//***********************************TYPE*********************************************

typedef unsigned long    CRV;
typedef void*            CHANDLE;
typedef CHANDLE*         PCHANDLE;


const unsigned long CPIN_MAX_RETRY_TIMES			= 15;
const unsigned long CPIN_MIN_LENGTH					= 6;
const unsigned long CPIN_MAX_LENGTH					= 15;
const unsigned long CTRANSMIT_MAX_PACKAGE			= 128;
const unsigned long CTRANSMIT_MAX_BUFFER_SIZE		= 136;

//***********************************KIY ERROR CODE*********************************************

CRV const CRV_SUCCESS					= 0x00000000;

CRV const CRV_BASE						= 0xE0100000;
CRV const CRV_FAILED					= (CRV_BASE | 0x01);
CRV const CRV_OPEN_DEVICE_ERROR			= (CRV_BASE | 0x02);
CRV const CRV_INVALID_COMMAND			= (CRV_BASE | 0x03);
CRV const CRV_KIY_NOT_INITIALIZED		= (CRV_BASE | 0x04);
CRV const CRV_PARAMETER_ERROR			= (CRV_BASE | 0x05);
CRV const CRV_DEVICE_TYPE_ERROR			= (CRV_BASE | 0x06);
CRV const CRV_NOT_PAIR					= (CRV_BASE | 0x07);

CRV const CRV_PIN_ERROR					= (CRV_BASE | 0x63c0);
CRV const CRV_EEPROM_ERROR				= (CRV_BASE | 0x6581);
CRV const CRV_LEN_ERROR					= (CRV_BASE | 0x6700);
CRV const CRV_FILE_TYPE_ERROR			= (CRV_BASE | 0x6981);
CRV const CRV_AC_ERROR					= (CRV_BASE | 0x6982);
CRV const CRV_PIN_LOCK					= (CRV_BASE | 0x6983);
CRV const CRV_DATA_ERROR				= (CRV_BASE | 0x6A80);
CRV const CRV_NOT_SUPPORT_FUNCTION		= (CRV_BASE | 0x6A81);
CRV const CRV_NOT_FIND_FILE_ERROR		= (CRV_BASE | 0x6A82);
CRV const CRV_NOT_ENOUGH_ROOM			= (CRV_BASE | 0x6A84);
CRV const CRV_P1P2_ERROR				= (CRV_BASE | 0x6A86);
CRV const CRV_OFFSET_ERROR				= (CRV_BASE | 0x6B00);
CRV const CRV_FILE_LEN_ERROR			= (CRV_BASE | 0x6C00);

//***********************************METHOD*********************************************

#define EXPORTED __declspec(dllexport)

#ifdef __cplusplus
extern "C" {
#endif

/**
* @brief 接口库初始化
*/
EXPORTED void core_initializer();

/**
* @brief 接口库反初始化
*/
EXPORTED void core_finalizer();

/**
* @brief 查找设备

* @param[out] pPath 设备路径列表，以;分割
* @param[in out] pulPathLen 设备路径列表长度值

* @return 错误码
*/
EXPORTED CRV core_finddevice(char* pPath,
							 unsigned long* pulPathLen);

/**
* @brief 获取KIY版本号

* @param[in] pkeyPath 设备路径
* @param[out] pVersion KIY版本号，4字节

* @return 错误码
*/
EXPORTED CRV core_getversion(char* pkeyPath,
							 unsigned char* pVersion);

/**
* @brief 获取设备ID，每个设备具有唯一ID值

* @param[in] pkeyPath 设备路径
* @param[in] bHash 设备ID是否Hash
* @param[out] pDeviceId 设备ID
* @param[in out] pulPathLen 设备ID长度值，设备ID长度：16，设备ID Hash长度：32

* @return 错误码
*/
EXPORTED CRV core_getdeviceid(char* pkeyPath,
							  bool bHash,
							  unsigned char* pDeviceId,
							  unsigned long* pulDeviceIdLen);

/**
* @brief 获取类型

* @param[in] pkeyPath 设备路径
* @param[out] pType Key类型，1字节，0x01：A-Key，0xFF：R-Key

* @return 错误码
*/
EXPORTED CRV core_gettype(char* pkeyPath,
						  unsigned char* pType);

/**
* @brief 获取HID值，每套设备具有相同HID值

* @param[in] pkeyPath 设备路径
* @param[out] pHID HID
* @param[in out] pulHIDLen HID长度值，长度32

* @return 错误码
*/
EXPORTED CRV core_gethid(char* pkeyPath,
						 unsigned char* pHID,
						 unsigned long* pulHIDLen);

/**
* @brief 获取名称

* @param[in] pkeyPath 设备路径
* @param[out] szName 名称
* @param[in out] pulNameLen 返回名称长度，最大32

* @return 错误码
*/
EXPORTED CRV core_getname(char* pkeyPath,
						  unsigned char* szName,
						  unsigned long* pulNameLen);

/**
* @brief 设置名称

* @param[in] pkeyPath 设备路径
* @param[in] szName 名称
* @param[in] ulNameLen 名称长度，最大32

* @return 错误码
*/
EXPORTED CRV core_setname(char* pkeyPath,
						  unsigned char* szName,
						  unsigned long ulNameLen);

/**
* @brief 根密钥是否初始化

* @param[in] pkeyPath 设备路径
* @param[out] pbIsDevInit 是否初始化

* @return 错误码
*/
EXPORTED CRV core_isdevinit(char* pkeyPath,
							bool* pbIsDevInit);

/**
* @brief 初始化设备根密钥

* @param[in] pkeyPath 设备路径

* @return 错误码
*/
EXPORTED CRV core_initdev(char* pkeyPath);

/**
* @brief 登录

* @param[in] pkeyPath 设备路径
* @param[in] pPIN PIN码
* @param[in] ulPINLen PIN码长度，6-15
* @param[out] pulRRTimes PIN码剩余重试次数

* @return 错误码
*/
EXPORTED CRV core_login(char* pkeyPath,
						unsigned char* pPIN,
						unsigned long  ulPINLen,
						unsigned long* pulRRTimes);

/**
* @brief 登出

* @param[in] pkeyPath 设备路径

* @return 错误码
*/
EXPORTED CRV core_logout(char* pkeyPath);

/**
* @brief 修改PIN码

* @param[in] pkeyPath 设备路径
* @param[in] pOldPIN PIN码
* @param[in] ulOldPINLen PIN码长度，6-15
* @param[out] pulRRTimes PIN码剩余重试次数
* @param[in] pNewPIN 新PIN码
* @param[in] ulNewPINLen 新PIN码长度，6-15

* @return 错误码
*/
EXPORTED CRV core_changepin(char* pkeyPath,
							unsigned char* pOldPIN,
							unsigned long  ulOldPINLen,
							unsigned long* pulRRTimes,
							unsigned char* pNewPIN,
							unsigned long  ulNewPINLen);
/**
* @brief Ecdsa secp256k1私钥签名

* @param[in] pkeyPath 设备路径
* @param[in] pAddress 秘钥路径
* @param[in] ulAddressLen 秘钥路径长度，1-10
* @param[in] pHash Hash值
* @param[in] ulHashLen Hash值长度，32
* @param[out] pSigned 签名值
* @param[in out] pulSignedLen 签名值长度，65

* @return 错误码
*/
EXPORTED CRV core_sign_ecdsa_secp256k1(char* pkeyPath,
									   int* pAddress,
									   unsigned long ulAddressLen,
									   unsigned char* pHash,
									   unsigned long ulHashLen,
									   unsigned char* pSigned,
									   unsigned long* pulSignedLen);

/**
* @brief Ecdsa secp256k1公钥验签

* @param[in] pkeyPath 设备路径
* @param[in] pAddress 秘钥路径
* @param[in] ulAddressLen 秘钥路径长度，1-10
* @param[in] pHash Hash值
* @param[in] ulHashLen Hash值长度，32
* @param[in] pSigned 签名值
* @param[in] ulSignedLen 签名值长度，65
* @param[out] pbResult 验签结果

* @return 错误码
*/
EXPORTED CRV core_verify_ecdsa_secp256k1(char* pkeyPath,
										 int* pAddress,
										 unsigned long ulAddressLen,
										 unsigned char* pHash,
										 unsigned long ulHashLen,
										 unsigned char* pSigned,
										 unsigned long ulSignedLen,
										 bool* pbResult);

/**
* @brief Ecdsa secp256k1获取公钥

* @param[in] pkeyPath 设备路径
* @param[in] uchType 类型，0：65字节公钥，1：33字节公钥
* @param[in] pAddress 秘钥路径
* @param[in] ulAddressLen 秘钥路径长度，1-10
* @param[out] pPubKey 公钥值
* @param[in out] pulPubKeyLen 公钥值长度

* @return 错误码
*/
EXPORTED CRV core_getpubkey_ecdsa_secp256k1(char* pkeyPath,
											unsigned char uchType,
											int* pAddress,
											unsigned long ulAddressLen,
											unsigned char* pPubKey,
											unsigned long* pulPubKeyLen);

/**
* @brief 同步

* @param[in] psrcKeyPath 源Key设备路径
* @param[in] pdestKeyPath 目标Key设备路径

* @return 错误码
*/
EXPORTED CRV core_sync(char* psrcKeyPath,
					   char* pdestKeyPath);

/**
* @brief 重载PIN码

* @param[in] psrcKeyPath 源Key设备路径
* @param[in] pdestKeyPath 目标Key设备路径
* @param[in] pNewPIN 新PIN码
* @param[in] ulNewPINLen 新PIN码长度，6-15

* @return 错误码
*/
EXPORTED CRV core_reloadpin(char* psrcKeyPath,
						    char* pdestKeyPath,
						    unsigned char* pNewPIN,
						    unsigned long  ulNewPINLen);

/**
* @brief ED25519私钥签名

* @param[in] pkeyPath 设备路径
* @param[in] pAddress 秘钥路径
* @param[in] ulAddressLen 秘钥路径长度，1-10
* @param[in] pMsg 待签名数据
* @param[in] ulMsgLen 待签名数据长度，1-4096
* @param[in] uchHashType 摘要算法类型，SHA512:0xF7
* @param[out] pSigned 签名值
* @param[in out] pulSignedLen 签名值长度，64

* @return 错误码
*/
EXPORTED CRV core_sign_ed25519(char* pkeyPath,
							   int* pAddress,
							   unsigned long ulAddressLen,
							   unsigned char* pMsg,
							   unsigned long ulMsgLen,
							   unsigned char uchHashType,
							   unsigned char* pSigned,
							   unsigned long* pulSignedLen);

/**
* @brief ED25519公钥验签

* @param[in] pkeyPath 设备路径
* @param[in] pAddress 秘钥路径
* @param[in] ulAddressLen 秘钥路径长度，1-10
* @param[in] pMsg 待签名数据
* @param[in] ulMsgLen 待签名数据长度，1-4096
* @param[in] uchHashType 摘要算法类型，SHA512:0xF7
* @param[in] pSigned 签名值
* @param[in] ulSignedLen 签名值长度，64
* @param[out] pbResult 验签结果

* @return 错误码
*/
EXPORTED CRV core_verify_ed25519(char* pkeyPath,
								 int* pAddress,
								 unsigned long ulAddressLen,
								 unsigned char* pMsg,
								 unsigned long ulMsgLen,
								 unsigned char uchHashType,
								 unsigned char* pSigned,
								 unsigned long ulSignedLen,
								 bool* pbResult);

/**
* @brief ED25519获取公钥

* @param[in] pkeyPath 设备路径
* @param[in] pAddress 秘钥路径
* @param[in] ulAddressLen 秘钥路径长度，1-10
* @param[in] uchHashType 摘要算法类型，SHA512:0xF7
* @param[out] pPubKey 公钥值
* @param[in out] pulPubKeyLen 公钥值长度，33

* @return 错误码
*/
EXPORTED CRV core_getpubkey_ed25519(char* pkeyPath,
									int* pAddress,
									unsigned long ulAddressLen,
									unsigned char uchHashType,
									unsigned char* pPubKey,
									unsigned long* pulPubKeyLen);

#ifdef __cplusplus
}
#endif // __cplusplus


#endif /* kiy_core_h */
