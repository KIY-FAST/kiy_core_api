package com.example.keydemo_jar;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.AppCompatEditText;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.text.method.ScrollingMovementMethod;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import com.example.hidsdk.hidkpi.CKIYFactory;
import com.example.hidsdk.utils.ByteUtil;
import com.example.hidsdk.utils.ThreadPoolManager;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    //    private int[] address = new int[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    private int[] address = new int[]{1, 2, 3, 4, 5};
    private byte[] hash = new byte[]{(byte) 0x01, (byte) 0x01, (byte) 0x01, (byte) 0x01, (byte) 0x01,
            (byte) 0x02, (byte) 0x02, (byte) 0x02, (byte) 0x02, (byte) 0x02,
            (byte) 0x03, (byte) 0x03, (byte) 0x03, (byte) 0x03, (byte) 0x03,
            (byte) 0x04, (byte) 0x04, (byte) 0x04, (byte) 0x04, (byte) 0x04,
            (byte) 0x05, (byte) 0x05, (byte) 0x05, (byte) 0x05, (byte) 0x05,
            (byte) 0x06, (byte) 0x06, (byte) 0x06, (byte) 0x06, (byte) 0x06,
            (byte) 0x07, (byte) 0x07};
    private byte[] sig;
    private TextView infoTv;
    private AppCompatEditText devPath1, devPath2;
    private AppCompatEditText name;
    private AppCompatEditText pinEt, oldPinEt, newPinEt;
    private AppCompatEditText getPubKey_address, getPubKey_type;
    private AppCompatEditText verify_sign, verify_hash, verify_address;
    private AppCompatEditText sign_hash, sign_address;
    private AppCompatEditText getPubKey_ED25519_address;
    private AppCompatEditText verify_ed25519_sign, verify_ed25519_msg, verify_ed25519_address;
    private AppCompatEditText sign_ed25519_msg, sign_ed25519_address;
    private AppCompatEditText export_root_key, import_root_key, reload_pin_newPin;

    private Handler mHandler = new Handler() {
        public void handleMessage(Message msg) {
            switch (msg.what) {
                case 100:
                    infoTv.append(String.valueOf(msg.obj) + "\n");
                    tvShowBottom();
                    break;
                case 200:
                    infoTv.setText("");
                    tvShowTop();
                    break;
            }
        }

        ;
    };


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        CKIYFactory.getKIYInstance().init(this);
        devPath1 = findViewById(R.id.devPath1);
        devPath2 = findViewById(R.id.devPath2);
        name = findViewById(R.id.name);
        pinEt = findViewById(R.id.pin);
        oldPinEt = findViewById(R.id.oldPin);
        newPinEt = findViewById(R.id.newPin);
        getPubKey_address = findViewById(R.id.getPubKey_address);
        getPubKey_type = findViewById(R.id.getPubKey_type);
        verify_sign = findViewById(R.id.verify_sign);
        verify_hash = findViewById(R.id.verify_hash);
        verify_address = findViewById(R.id.verify_address);
        sign_hash = findViewById(R.id.sign_hash);
        sign_address = findViewById(R.id.sign_address);
        getPubKey_ED25519_address = findViewById(R.id.getPubKey_ED25519_address);
        verify_ed25519_sign = findViewById(R.id.verify_ed25519_sign);
        verify_ed25519_msg = findViewById(R.id.verify_ed25519_msg);
        verify_ed25519_address = findViewById(R.id.verify_ed25519_address);
        sign_ed25519_msg = findViewById(R.id.sign_ed25519_msg);
        sign_ed25519_address = findViewById(R.id.sign_ed25519_address);
        export_root_key = findViewById(R.id.export_root_key);
        import_root_key = findViewById(R.id.import_root_key);
        reload_pin_newPin = findViewById(R.id.reload_pin_newPin);

        infoTv = findViewById(R.id.info);
        infoTv.setMovementMethod(ScrollingMovementMethod.getInstance());
        findViewById(R.id.findDevBtn).setOnClickListener(this);
        findViewById(R.id.getDeviceIDHashBtn).setOnClickListener(this);
        findViewById(R.id.getVersionBtn).setOnClickListener(this);
        findViewById(R.id.getDeviceIDBtn).setOnClickListener(this);
        findViewById(R.id.getDeviceTypeBtn).setOnClickListener(this);
        findViewById(R.id.getHIDBtn).setOnClickListener(this);
        findViewById(R.id.isDevInitBtn).setOnClickListener(this);
        findViewById(R.id.getNameBtn).setOnClickListener(this);
        findViewById(R.id.setNameBtn).setOnClickListener(this);
        findViewById(R.id.initDevBtn).setOnClickListener(this);
        findViewById(R.id.loginBtn).setOnClickListener(this);
        findViewById(R.id.logoutBtn).setOnClickListener(this);
        findViewById(R.id.changePINBtn).setOnClickListener(this);
        findViewById(R.id.signBtn).setOnClickListener(this);
        findViewById(R.id.verifyBtn).setOnClickListener(this);
        findViewById(R.id.getPubKeyBtn).setOnClickListener(this);
        findViewById(R.id.signED25519Btn).setOnClickListener(this);
        findViewById(R.id.verifyED25519Btn).setOnClickListener(this);
        findViewById(R.id.getPubKeyED25519Btn).setOnClickListener(this);

        findViewById(R.id.getRandomBtn).setOnClickListener(this);
        findViewById(R.id.exportRootKeyBtn).setOnClickListener(this);
        findViewById(R.id.importRootKeyBtn).setOnClickListener(this);
        findViewById(R.id.copyBtn).setOnClickListener(this);
        findViewById(R.id.reloadPINBtn).setOnClickListener(this);
        infoTv.setTextIsSelectable(true);

        findViewById(R.id.clearBtn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Message message = Message.obtain();
                message.what = 200;
                mHandler.sendMessage(message);
            }
        });
        Log.e("WCL>>>","111: "+ ByteUtil.bytesToHexString(hash));
    }

    @Override
    public void onClick(View v) {
        ThreadPoolManager.getInstance().executeRunable(new Runnable() {
            @Override
            public void run() {
                String msg = "";
                try {
                    switch (v.getId()) {
                        case R.id.findDevBtn:
                            String dev = CKIYFactory.getKIYInstance().findDev();
                            msg = "查找设备：" + dev;
                            if (!dev.isEmpty())
                            {
                                if (dev.contains(";"))
                                {
                                    String[] devArray = dev.trim().split(";");
                                    MainActivity.this.runOnUiThread(new Runnable() {
                                        public void run() {
                                            devPath1.setText(devArray[1]);
                                            devPath2.setText(devArray[0]);
                                        }
                                    });
                                }
                                else
                                {
                                    MainActivity.this.runOnUiThread(new Runnable() {
                                        public void run() {
                                            devPath1.setText(dev);
                                        }
                                    });
                                }
                            }
                            break;
                        case R.id.getVersionBtn:
                            msg = "获取KIY版本号：" + ByteUtil.bytesToHexString(CKIYFactory.getKIYInstance().getVersion(devPath1.getText().toString().trim()));
                            break;
                        case R.id.getDeviceIDBtn:
                            msg = "获取设备ID：" + ByteUtil.bytesToHexString(CKIYFactory.getKIYInstance().getDeviceID(devPath1.getText().toString().trim(), 0));
                            break;
                        case R.id.getDeviceIDHashBtn:
                            msg = "获取设备ID Hash：" + ByteUtil.bytesToHexString(CKIYFactory.getKIYInstance().getDeviceID(devPath1.getText().toString().trim(),1));
                            break;
                        case R.id.getHIDBtn:
                            msg = "获取HID：" + ByteUtil.bytesToHexString(CKIYFactory.getKIYInstance().getHID(devPath1.getText().toString().trim()));
                            break;
                        case R.id.getDeviceTypeBtn:
                            msg = "获取设备类型：" + ByteUtil.bytesToHexString(new byte[]{CKIYFactory.getKIYInstance().getDeviceType(devPath1.getText().toString().trim())});
                            break;
                        case R.id.getNameBtn:
                            msg = "获取名称：" + CKIYFactory.getKIYInstance().getName(devPath1.getText().toString().trim());
                            break;
                        case R.id.setNameBtn:
                            msg = "设置名称：" + CKIYFactory.getKIYInstance().setName(devPath1.getText().toString().trim(), name.getText().toString().trim());
                            break;
                        case R.id.isDevInitBtn:
                            msg = "BTC根秘钥是否初始化：" + CKIYFactory.getKIYInstance().isDevInit(devPath1.getText().toString().trim());
                            break;
                        case R.id.initDevBtn:
                            msg = "初始化BTC根秘钥：" + CKIYFactory.getKIYInstance().initDev(devPath1.getText().toString().trim());
                            break;
                        case R.id.loginBtn:
                            int loginState = CKIYFactory.getKIYInstance().login(devPath1.getText().toString().trim(), pinEt.getText().toString().trim());
                            msg = "登录设备：" + (loginState == 0 ? true : false + ",剩余次数：" + ByteUtil.bytesToHexString(ByteUtil.intToBytes2(loginState)).substring(3));
                            break;
                        case R.id.logoutBtn:
                            msg = "登出设备：" + CKIYFactory.getKIYInstance().logout(devPath1.getText().toString().trim());
                            break;
                        case R.id.changePINBtn:
                            int changePinState = CKIYFactory.getKIYInstance().changePIN(devPath1.getText().toString().trim(), oldPinEt.getText().toString().trim(), newPinEt.getText().toString().trim());
                            msg = "修改KIY PIN码：" + (changePinState == 0 ? true : false + ",剩余次数：" + ByteUtil.bytesToHexString(ByteUtil.intToBytes2(changePinState)).substring(3));
                            break;
                        case R.id.signBtn:
                            String[] sign_address_str = sign_address.getText().toString().trim().split(" ");
                            byte[] sign_hash_byte = ByteUtil.hexStringToByte(sign_hash.getText().toString().trim());
                            sig = CKIYFactory.getKIYInstance().sign_ecdsa_secp256k1(devPath1.getText().toString().trim(), StringToInt(sign_address_str), sign_hash_byte);
                            msg = "私钥签名：" + ByteUtil.bytesToHexString(sig);
                            break;
                        case R.id.verifyBtn:
                            byte[] verify_sign_byte = ByteUtil.hexStringToByte(verify_sign.getText().toString().trim());
                            byte[] verify_hash_byte = ByteUtil.hexStringToByte(verify_hash.getText().toString().trim());
                            String[] verify_address_str = verify_address.getText().toString().trim().split(" ");
                            msg = "公钥验证：" + CKIYFactory.getKIYInstance().verify_ecdsa_secp256k1(devPath1.getText().toString().trim(), StringToInt(verify_address_str), verify_hash_byte, verify_sign_byte);
                            break;
                        case R.id.getPubKeyBtn:
                            String[] getPubKey_address_str = getPubKey_address.getText().toString().trim().split(" ");
                            int getPubKey_type_int = Integer.parseInt(getPubKey_type.getText().toString().trim());
                            msg = "获取公钥：" + ByteUtil.bytesToHexString(CKIYFactory.getKIYInstance().getPubKey_ecdsa_secp256k1(devPath1.getText().toString().trim(), getPubKey_type_int, StringToInt(getPubKey_address_str)));
                            break;
                        case R.id.signED25519Btn:
                            String[] sign_ed25519_address_str = sign_ed25519_address.getText().toString().trim().split(" ");
                            byte[] sign_ed25519_msg_byte = sign_ed25519_msg.getText().toString().getBytes();
                            sig = CKIYFactory.getKIYInstance().sign_ed25519(devPath1.getText().toString().trim(), StringToIntED25519(sign_ed25519_address_str), sign_ed25519_msg_byte, (byte)0xF7);
                            msg = "ED25519私钥签名：" + ByteUtil.bytesToHexString(sig);
                            break;
                        case R.id.verifyED25519Btn:
                            byte[] verify_ed25519_sign_byte = ByteUtil.hexStringToByte(verify_ed25519_sign.getText().toString().trim());
                            byte[] verify_ed25519_msg_byte = verify_ed25519_msg.getText().toString().getBytes();
                            String[] verify_ed25519_address_str = verify_ed25519_address.getText().toString().trim().split(" ");
                            msg = "ED25519公钥验证：" + CKIYFactory.getKIYInstance().verify_ed25519(devPath1.getText().toString().trim(), StringToIntED25519(verify_ed25519_address_str), verify_ed25519_msg_byte, verify_ed25519_sign_byte, (byte)0xF7);
                            break;
                        case R.id.getPubKeyED25519Btn:
                            String[] getPubKey_ed25519_address_str = getPubKey_ED25519_address.getText().toString().trim().split(" ");
                            msg = "ED25519获取公钥：" + ByteUtil.bytesToHexString(CKIYFactory.getKIYInstance().getPubKey_ed25519(devPath1.getText().toString().trim(), StringToIntED25519(getPubKey_ed25519_address_str), (byte)0xF7));
                            break;
                        case R.id.copyBtn:
                            boolean copyRet = CKIYFactory.getKIYInstance().sync(devPath1.getText().toString().trim(), devPath2.getText().toString().trim());
                            msg = "拷贝：" + copyRet;
                            break;
                        case R.id.reloadPINBtn:
                            boolean reloadPINRet = CKIYFactory.getKIYInstance().reloadPIN(devPath1.getText().toString().trim(), devPath2.getText().toString().trim(), reload_pin_newPin.getText().toString().trim());
                            msg = "重载PIN码：" + reloadPINRet;
                            break;
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                    msg = "异常：" + e.getMessage();
                }
                sendMessage(msg);
            }
        });
    }

    public void sendMessage(String msg) {
        Message message = Message.obtain();
        message.what = 100;
        message.obj = msg;
        mHandler.sendMessage(message);
    }

    public void tvShowBottom() {
        int offset = infoTv.getLineCount() * infoTv.getLineHeight();
        if (offset > infoTv.getHeight()) {
            infoTv.scrollTo(0, offset - infoTv.getHeight());
        }
    }

    public void tvShowTop() {
        infoTv.scrollTo(0, 0);
    }


    public int[] StringToInt(String[] arrs) throws Exception {
        try {
            int[] ints = new int[arrs.length];
            for (int i = 0; i < arrs.length; i++) {
                ints[i] = Integer.parseInt(arrs[i]);
            }
            return ints;
        } catch (Exception e) {
            e.printStackTrace();
            throw new Exception(e.getMessage());
        }
    }

    public int[] StringToIntED25519(String[] arrs) throws Exception {
        try {
            int[] ints = new int[arrs.length];
            for (int i = 0; i < arrs.length; i++) {
                ints[i] = Integer.parseInt(arrs[i]);
                ints[i] = ints[i] | ((byte)0x80 << 24);
            }
            return ints;
        } catch (Exception e) {
            e.printStackTrace();
            throw new Exception(e.getMessage());
        }
    }
}