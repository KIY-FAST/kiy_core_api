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
* @brief �ӿڿ��ʼ��
*/
EXPORTED void core_initializer();

/**
* @brief �ӿڿⷴ��ʼ��
*/
EXPORTED void core_finalizer();

/**
* @brief �����豸

* @param[out] pPath �豸·���б���;�ָ�
* @param[in out] pulPathLen �豸·���б���ֵ

* @return ������
*/
EXPORTED CRV core_finddevice(char* pPath,
							 unsigned long* pulPathLen);

/**
* @brief ��ȡKIY�汾��

* @param[in] pkeyPath �豸·��
* @param[out] pVersion KIY�汾�ţ�4�ֽ�

* @return ������
*/
EXPORTED CRV core_getversion(char* pkeyPath,
							 unsigned char* pVersion);

/**
* @brief ��ȡ�豸ID��ÿ���豸����ΨһIDֵ

* @param[in] pkeyPath �豸·��
* @param[in] bHash �豸ID�Ƿ�Hash
* @param[out] pDeviceId �豸ID
* @param[in out] pulPathLen �豸ID����ֵ���豸ID���ȣ�16���豸ID Hash���ȣ�32

* @return ������
*/
EXPORTED CRV core_getdeviceid(char* pkeyPath,
							  bool bHash,
							  unsigned char* pDeviceId,
							  unsigned long* pulDeviceIdLen);

/**
* @brief ��ȡ����

* @param[in] pkeyPath �豸·��
* @param[out] pType Key���ͣ�1�ֽڣ�0x01��A-Key��0xFF��R-Key

* @return ������
*/
EXPORTED CRV core_gettype(char* pkeyPath,
						  unsigned char* pType);

/**
* @brief ��ȡHIDֵ��ÿ���豸������ͬHIDֵ

* @param[in] pkeyPath �豸·��
* @param[out] pHID HID
* @param[in out] pulHIDLen HID����ֵ������32

* @return ������
*/
EXPORTED CRV core_gethid(char* pkeyPath,
						 unsigned char* pHID,
						 unsigned long* pulHIDLen);

/**
* @brief ��ȡ����

* @param[in] pkeyPath �豸·��
* @param[out] szName ����
* @param[in out] pulNameLen �������Ƴ��ȣ����32

* @return ������
*/
EXPORTED CRV core_getname(char* pkeyPath,
						  unsigned char* szName,
						  unsigned long* pulNameLen);

/**
* @brief ��������

* @param[in] pkeyPath �豸·��
* @param[in] szName ����
* @param[in] ulNameLen ���Ƴ��ȣ����32

* @return ������
*/
EXPORTED CRV core_setname(char* pkeyPath,
						  unsigned char* szName,
						  unsigned long ulNameLen);

/**
* @brief ����Կ�Ƿ��ʼ��

* @param[in] pkeyPath �豸·��
* @param[out] pbIsDevInit �Ƿ��ʼ��

* @return ������
*/
EXPORTED CRV core_isdevinit(char* pkeyPath,
							bool* pbIsDevInit);

/**
* @brief ��ʼ���豸����Կ

* @param[in] pkeyPath �豸·��

* @return ������
*/
EXPORTED CRV core_initdev(char* pkeyPath);

/**
* @brief ��¼

* @param[in] pkeyPath �豸·��
* @param[in] pPIN PIN��
* @param[in] ulPINLen PIN�볤�ȣ�6-15
* @param[out] pulRRTimes PIN��ʣ�����Դ���

* @return ������
*/
EXPORTED CRV core_login(char* pkeyPath,
						unsigned char* pPIN,
						unsigned long  ulPINLen,
						unsigned long* pulRRTimes);

/**
* @brief �ǳ�

* @param[in] pkeyPath �豸·��

* @return ������
*/
EXPORTED CRV core_logout(char* pkeyPath);

/**
* @brief �޸�PIN��

* @param[in] pkeyPath �豸·��
* @param[in] pOldPIN PIN��
* @param[in] ulOldPINLen PIN�볤�ȣ�6-15
* @param[out] pulRRTimes PIN��ʣ�����Դ���
* @param[in] pNewPIN ��PIN��
* @param[in] ulNewPINLen ��PIN�볤�ȣ�6-15

* @return ������
*/
EXPORTED CRV core_changepin(char* pkeyPath,
							unsigned char* pOldPIN,
							unsigned long  ulOldPINLen,
							unsigned long* pulRRTimes,
							unsigned char* pNewPIN,
							unsigned long  ulNewPINLen);
/**
* @brief Ecdsa secp256k1˽Կǩ��

* @param[in] pkeyPath �豸·��
* @param[in] pAddress ��Կ·��
* @param[in] ulAddressLen ��Կ·�����ȣ�1-10
* @param[in] pHash Hashֵ
* @param[in] ulHashLen Hashֵ���ȣ�32
* @param[out] pSigned ǩ��ֵ
* @param[in out] pulSignedLen ǩ��ֵ���ȣ�65

* @return ������
*/
EXPORTED CRV core_sign_ecdsa_secp256k1(char* pkeyPath,
									   int* pAddress,
									   unsigned long ulAddressLen,
									   unsigned char* pHash,
									   unsigned long ulHashLen,
									   unsigned char* pSigned,
									   unsigned long* pulSignedLen);

/**
* @brief Ecdsa secp256k1��Կ��ǩ

* @param[in] pkeyPath �豸·��
* @param[in] pAddress ��Կ·��
* @param[in] ulAddressLen ��Կ·�����ȣ�1-10
* @param[in] pHash Hashֵ
* @param[in] ulHashLen Hashֵ���ȣ�32
* @param[in] pSigned ǩ��ֵ
* @param[in] ulSignedLen ǩ��ֵ���ȣ�65
* @param[out] pbResult ��ǩ���

* @return ������
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
* @brief Ecdsa secp256k1��ȡ��Կ

* @param[in] pkeyPath �豸·��
* @param[in] uchType ���ͣ�0��65�ֽڹ�Կ��1��33�ֽڹ�Կ
* @param[in] pAddress ��Կ·��
* @param[in] ulAddressLen ��Կ·�����ȣ�1-10
* @param[out] pPubKey ��Կֵ
* @param[in out] pulPubKeyLen ��Կֵ����

* @return ������
*/
EXPORTED CRV core_getpubkey_ecdsa_secp256k1(char* pkeyPath,
											unsigned char uchType,
											int* pAddress,
											unsigned long ulAddressLen,
											unsigned char* pPubKey,
											unsigned long* pulPubKeyLen);

/**
* @brief ͬ��

* @param[in] psrcKeyPath ԴKey�豸·��
* @param[in] pdestKeyPath Ŀ��Key�豸·��

* @return ������
*/
EXPORTED CRV core_sync(char* psrcKeyPath,
					   char* pdestKeyPath);

/**
* @brief ����PIN��

* @param[in] psrcKeyPath ԴKey�豸·��
* @param[in] pdestKeyPath Ŀ��Key�豸·��
* @param[in] pNewPIN ��PIN��
* @param[in] ulNewPINLen ��PIN�볤�ȣ�6-15

* @return ������
*/
EXPORTED CRV core_reloadpin(char* psrcKeyPath,
						    char* pdestKeyPath,
						    unsigned char* pNewPIN,
						    unsigned long  ulNewPINLen);

/**
* @brief ED25519˽Կǩ��

* @param[in] pkeyPath �豸·��
* @param[in] pAddress ��Կ·��
* @param[in] ulAddressLen ��Կ·�����ȣ�1-10
* @param[in] pMsg ��ǩ������
* @param[in] ulMsgLen ��ǩ�����ݳ��ȣ�1-4096
* @param[in] uchHashType ժҪ�㷨���ͣ�SHA512:0xF7
* @param[out] pSigned ǩ��ֵ
* @param[in out] pulSignedLen ǩ��ֵ���ȣ�64

* @return ������
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
* @brief ED25519��Կ��ǩ

* @param[in] pkeyPath �豸·��
* @param[in] pAddress ��Կ·��
* @param[in] ulAddressLen ��Կ·�����ȣ�1-10
* @param[in] pMsg ��ǩ������
* @param[in] ulMsgLen ��ǩ�����ݳ��ȣ�1-4096
* @param[in] uchHashType ժҪ�㷨���ͣ�SHA512:0xF7
* @param[in] pSigned ǩ��ֵ
* @param[in] ulSignedLen ǩ��ֵ���ȣ�64
* @param[out] pbResult ��ǩ���

* @return ������
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
* @brief ED25519��ȡ��Կ

* @param[in] pkeyPath �豸·��
* @param[in] pAddress ��Կ·��
* @param[in] ulAddressLen ��Կ·�����ȣ�1-10
* @param[in] uchHashType ժҪ�㷨���ͣ�SHA512:0xF7
* @param[out] pPubKey ��Կֵ
* @param[in out] pulPubKeyLen ��Կֵ���ȣ�33

* @return ������
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
