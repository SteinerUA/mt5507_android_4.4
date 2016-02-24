package com.tcl.deviceinfo;

import java.lang.Exception;
import android.os.SystemProperties;
import com.tcl.factory.FactoryManager;
import java.util.ArrayList;
import java.util.List;
import android.util.Log;

// Begin added by TCL lulin, mail: lulin@tcl.com
import com.tcl.tvmanager.TvManager;
import com.tcl.utility.property.Property;
import android.content.Context;
// End of TCL

/**
 *  DeviceInfo������ڱ�׼������ƽ̨��ص����ݡ��������������£� 
 *	<br>&Oslash;&nbsp; ���𴴽�/data/devinfo.txt�ļ���������DeviceID������汾�š�ClientType��DeviceID��CRCУ����
 *	<br>&Oslash;&nbsp; ʵ��DeviceID��˫���ݣ�������DeviceID����У��
 *	<br>&Oslash;&nbsp; Ϊ�û��ṩƽ̨��ص����ݲ�ͨ��ProjectID��������Щ���ݣ�ʵ��һ��������ݶ��ProjectID��Ŀ��
 *	<br>&Oslash;&nbsp; ƽ̨���ݽ���˫���ݣ�Ϊ��ȷ��ƽ̨���ݵİ�ȫ�ԣ������ݽ���˫���ݡ�ϵͳ����ʱ�����ݽ���У�飬�������У��ʧ�ܣ���ӱ����лָ�
 *	<br>&Oslash;&nbsp; ΪӦ���ṩ������صĽӿڡ�Ӧ��Ҫ���ȡ�������ݣ�����ֱ�ӵ��ù����˵��ӿڣ���ͨ��DeviceInfo����Ľӿ�����ȡ����ȷ�����ݵİ�ȫ��
 */
public class TDeviceInfo {
	private static final String TAG = "TCL_DeviceInfo";
	private static final boolean LOGI = true;
	private static TDeviceInfo mDeviceInfo;
	private static FactoryManager mFactoryManager;

	static {
		System.loadLibrary("deviceinfo_jni");
	}

    /**
     * ��ȡDeviceInfo��ʵ������
     * @param ��
     * @return ����һ��DeviceInfo�Ķ���
     */
	public static TDeviceInfo getInstance() {
		if(mDeviceInfo == null) {
			mDeviceInfo = new TDeviceInfo();
		}
		return mDeviceInfo;
	}

    /**
     * ��ȡ�豸��Ӳ���汾 
     * @param ��
     * @return ����Ӳ���汾��
     */
	public String getHardwareVersion() {
		String mRet = "";
		try {
			mRet = SystemProperties.get("ro.hardware.version_id");
		} catch (Exception e){
			e.printStackTrace();
		}
		return mRet;
	}

    /**
     * ��ȡϵͳ������汾 
     * @param ��
     * @return ����ϵͳ����汾��
     */
	public String getSoftwareVersion() {
		String mRet = "";
		try {
			mRet = SystemProperties.get("ro.software.version_id");
		} catch (Exception e){
			e.printStackTrace();
		}
		return mRet;
	}

    /**
     * ��ȡClientType��������getClientType()�������� 
     * @param  ��
     * @return ���ص�ǰƽ̨ClientType
     */
	 @Deprecated
	public String getDeviceModel() {
		return getClientType(getProjectID());
	}

    /**
     * ��ȡDeviceID 
     * @param  ��
     * @return ���ص�ǰƽ̨DeviceID
     */
	public String getDeviceID() {
		String mRet = "";
		try {
			mRet = mFactoryManager.doGetDeviceID();
		} catch (Exception e) {
			e.printStackTrace();
		}
		if(LOGI) Log.i(TAG, "getDeviceID:" + mRet);
		return mRet;
	}

    /**
     * ���ڻָ�������������ƽ̨���ݣ��ָ�������״̬ 
	 * �÷������ݲ�ͬƽ̨��Ҫ����ʵ��
     * @param  ��
     * @return ��
     */
	public void cleanE2promInfo() {
		try {
			mFactoryManager.doCleanChannelList();
			mFactoryManager.doResetUserSettings();
		} catch (Exception e){
			e.printStackTrace();
		}
	}

    /**
     * ��ȡProjectID 
     * @param  ��
     * @return ���ص�ǰƽ̨��ProjectID��Ĭ��ֵΪ��0
     */
	public int getProjectID() {
		int mRet = 0;
		try {
			mRet = mFactoryManager.doGetAttribute(FactoryManager.FACTORY_ATTR_PROJ_ID);
		} catch (Exception e){
			e.printStackTrace();
		}
		return mRet;
	}

    /**
     * ��ȡClientType 
     * @param int prjid����ǰƽ̨��ProjectID 
     * @return ���ص�ǰƽ̨ClientType
     */
	public String getClientType(int prjid) {
		String mRet = "";
		try {
			mRet = native_devinfo_getClientType(prjid);
		} catch (Exception e){
			e.printStackTrace();
		}
		return mRet;
	}

    /**
     * ��ȡƽ̨�Ļ������� 
     * @param int prjid����ǰƽ̨��ProjectID
     * @return ����ƽ̨�Ļ�������
     */
	public String getModelName(int prjid) {
		String mRet = "";
		try {
			mRet = native_devinfo_getModelName(prjid);
		} catch (Exception e){
			e.printStackTrace();
		}
		return mRet;
	}

    /**
     * ��ȡ�������� 
     * @param int prjid����ǰƽ̨��ProjectID
     * @return ���ص���ʹ�õ���������
     */
	public String getPanelName(int prjid) {
		String mRet = "";
		try {
			mRet = native_devinfo_getPanelName(prjid);
		} catch (Exception e){
			e.printStackTrace();
		}
		return mRet;
	}

    /**
     * ��ȡ��������
     * @param int prjid����ǰƽ̨��ProjectID
     * @return �����������ͣ�4K2K���أ�1�� 2K1K���أ�0
     */
	public int getPanelType(int prjid) {
		int mRet = -1;
		try {
			mRet = native_devinfo_getPanelType(prjid);
		} catch (Exception e){
			e.printStackTrace();
		}
		return mRet;
	}

    /**
     * ��ȡ��Դ������
     * @param int prjid����ǰƽ̨��ProjectID
     * @return ���ص�Դ������
     */
	public String getPSUName(int prjid) {
		String mRet = "";
		try {
			mRet = native_devinfo_getPSUName(prjid);
		} catch (Exception e){
			e.printStackTrace();
		}
		return mRet;
	}

    /**
     * ��ȡң����������
     * @param int prjid����ǰƽ̨��ProjectID
     * @return ����ң����������
     */
	public String getRCUName(int prjid) {
		String mRet = "";
		try {
			mRet = native_devinfo_getRCUName(prjid);
		} catch (Exception e){
			e.printStackTrace();
		}
		return mRet;
	}

    /**
     * �жϵ�ǰƽ̨֧��֧��3D����
     * @param int prjid����ǰƽ̨��ProjectID
     * @return ֧�ַ��أ�1�� ���򷵻أ�0
     */
	public int get3DStatus(int prjid) {
		int mRet = -1;
		try {
			mRet = native_devinfo_get3DStatus(prjid);
		} catch (Exception e){
			e.printStackTrace();
		}
		return mRet;
	}

    /**
     * ��ȡ��ʹ�õ�3D�۾�����
     * @param int prjid����ǰƽ̨��ProjectID
     * @return �����۾����أ�1�� ƫ���۾����أ�0
     */
	public int get3DGlassesType(int prjid) {
		int mRet = -1;
		try {
			mRet = native_devinfo_get3DGlassesType(prjid);
		} catch (Exception e){
			e.printStackTrace();
		}
		return mRet;
	}

    /**
     * �ж�֧��֧��Wifi����
     * @param int prjid����ǰƽ̨��ProjectID
     * @return ֧�ַ��أ�1�����򷵻أ�0
     */
	public int getWifiStatus(int prjid) {
		int mRet = -1;
		try {
			mRet = native_devinfo_getWifiStatus(prjid);
		} catch (Exception e){
			e.printStackTrace();
		}
		return mRet;
	}

    /**
     * ��ȡWifi����
     * @param int prjid����ǰƽ̨��ProjectID
     * @return ����Wifi��1������Wifi���أ�0
     */
	public int getWifiType(int prjid) {
		int mRet = -1;
		try {
			mRet = native_devinfo_getWifiType(prjid);
		} catch (Exception e){
			e.printStackTrace();
		}
		return mRet;
	}

    /**
     * �жϵ�ǰƽ̨�Ƿ�֧���˶���������
     * @param int prjid����ǰƽ̨��ProjectID
     * @return ֧�ַ��أ�1����֧�ַ��أ�0
     */
	public int getMemc(int prjid) {
		int mRet = -1;
		try {
			mRet = native_devinfo_getMemc(prjid);
		} catch (Exception e){
			e.printStackTrace();
		}
		return mRet;
	}

    /**
     * �жϹ���Dģʽ�Ƿ��
     * @param ��
     * @return �򿪷��أ�<code>true</code>�����򷵻أ�<code>false</code>
     */
	public boolean getFactoryDModeStatus() {
		boolean mRet = false;
		try {
			mRet = (mFactoryManager.doGetAttribute(FactoryManager.FACTORY_ATTR_D_MODE) == 1)?true:false;
		} catch (Exception e){
			e.printStackTrace();
		}
		return mRet;
	}

    /**
     * �жϹ���Pģʽ�Ƿ��
     * @param ��
     * @return �򿪷��أ�<code>true</code>�����򷵻أ�<code>false</code>
     */
	public boolean getFactoryPModeStatus() {
		boolean mRet = false;
		try {
			mRet = (mFactoryManager.doGetAttribute(FactoryManager.FACTORY_ATTR_P_MODE) == 1)?true:false;
		} catch (Exception e){
			e.printStackTrace();
		}
		return mRet;
	}

    /**
     * �жϹ���Wģʽ�Ƿ��
     * @param ��
     * @return �򿪷��أ�<code>true</code>�����򷵻أ�<code>false</code>
     */
	public boolean getFactoryWModeStatus() {
		boolean mRet = false;
		try {
			mRet = (mFactoryManager.doGetAttribute(FactoryManager.FACTORY_ATTR_WARM_UP_MODE) == 1)?true:false;
		} catch (Exception e){
			e.printStackTrace();
		}
		return mRet;
	}

    /**
     * ��ȡ��Ʒע����
     * @param ��
     * @return ���ز�Ʒע����
     */
	public String getRegistrationCode() {
		String mRet = "";
		try {
			mRet = mFactoryManager.doGetRegisterCode();
		} catch (Exception e) {
			e.printStackTrace();
		}
		if(LOGI) Log.i(TAG, "getRegistrationCode:" + mRet);
		return mRet;
	}

	/**
     * ��ȡTV��������
     * @param ��
     * @return ����TV�������ƣ�Ĭ��ֵΪ��TCL Multimedia<br>
     * TV���������ԡ�TCL+�ӹ�˾���ơ���������
     */
	public String getTVCompany() {
		String mRet = "TCL Multimedia";
		try {
			mRet = SystemProperties.get("ro.build.company");
		} catch (Exception e){
			e.printStackTrace();
		}
		return mRet;
	}

    /**
     * ��ȡProjectID��Ŀ�б�
	 * <br>ͨ��ProjectID��Ŀ�б����֪���ж��ٸ�ProjectID�Լ�ProjiectIDֵ�Ƕ���
     * @param ��
     * @return ���أ�List<Integer>���͵�ProjectID��Ŀ�б�
     */
	public List<Integer> getProjectList() {
		List<Integer> mRet = new ArrayList<Integer>();
		int mTemp[] = native_devinfo_getProjectList();
		for(int i=0;i<mTemp.length;i++){
			mRet.add(mTemp[i]);
		} 
		return mRet;
	}

    /**
     * ����ProjectID
     * @param ��Ҫ���õ�ProjectIDֵ
     * @return ��
     */
	public void setProjectID(int projectID) {
		try {
			mFactoryManager.doSetAttribute(FactoryManager.FACTORY_ATTR_PROJ_ID, projectID);
		} catch (Exception e){
			e.printStackTrace();
		}
	}

    /**
     * ��ȡMAC��ַ
     * @param ��
     * @return ����MAC��ַ
     */
	public String getMACAddress() {
		String mRet = "";
		try {
			mRet = mFactoryManager.doGetMacAddress();
		} catch (Exception e) {
			e.printStackTrace();
		}
		if(LOGI) Log.i(TAG, "getMACAddress:" + mRet);
		return mRet;
	}
	
	/**
     * ��ȡ��������
     * @param ��
     * @return ���س�������
     */
	public String getCityName() {
		String mRet = "";
		try {
			mRet = Utils.getCityName();
		} catch (Exception e) {
			e.printStackTrace();
		}
		if(LOGI) Log.i(TAG, "getCityName:" + mRet);
		return mRet;
	}
	
	/**
     * ���ó�������
     * @param ��������
     * @return ��
     */
	public void setCityName(String mCityName) {
		try {
			Utils.setCityName(mCityName);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}


	/*
        .. SN .....
     * @param .
     * @return String  
     add by lulin mail lul@tcl.com
   */
	public String getSn() {
		String mRet = "";
		try {
			mRet = mFactoryManager.doGetSnCode();
		} catch (Exception e) {
			e.printStackTrace();
		}
		if(LOGI) Log.i(TAG, "getSncode:" + mRet);
		return mRet;
	}
 
		/*
        .. UUID 
     * @param .
     * @return String  
     add by lulin mail lul@tcl.com
   */
       public String getDeviceUUID(Context context) {
            TvManager tvm = TvManager.getInstance(context);
            Property tvmProp = tvm.getProperty();

            String mRet = tvmProp.get("persist.app.auth.UUID","");

            if(LOGI) Log.i(TAG, "get UUID:" + mRet);
            return mRet;
        }
     
     /*
        .. UUID 
     * @param .
     * @return String  
     add by lulin mail lul@tcl.com
   */
        public void setDeviceUUID(Context context, String uuid) {
            TvManager tvm = TvManager.getInstance(context);
            Property tvmProp = tvm.getProperty();

            tvmProp.set("persist.app.auth.UUID", uuid);
   
            if(LOGI) Log.e(TAG, "set UUID");
           
        }
        // End of TCL
	private TDeviceInfo() {
		try {
			mFactoryManager = FactoryManager.getInstance(null);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	/*
	 *init generate devinfo.txt 
	 *@hide
	 */
	public void init(){
		try {
			//check device info database
			native_devinfo_checkDatabase();
			//create file "/data/devinfo.txt"
			Utils.createDeviceInfoFile();
		} catch (Exception e){
			e.printStackTrace();
		}
	}

	private static native void native_devinfo_checkDatabase();
	private static native String native_devinfo_getClientType(int projectID);
	private static native String native_devinfo_getModelName(int projectID);
	private static native String native_devinfo_getPanelName(int projectID);
	private static native int native_devinfo_getPanelType(int projectID);
	private static native String native_devinfo_getPSUName(int projectID);
	private static native String native_devinfo_getRCUName(int projectID);
	private static native int native_devinfo_get3DStatus(int projectID);
	private static native int native_devinfo_get3DGlassesType(int projectID);
	private static native int native_devinfo_getWifiStatus(int projectID);
	private static native int native_devinfo_getWifiType(int projectID);
	private static native int native_devinfo_getMemc(int projectID);
	private static native int[] native_devinfo_getProjectList();

}
