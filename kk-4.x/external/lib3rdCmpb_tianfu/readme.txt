file:
	��Ŀ¼����3rd appʹ�õ�cmpb��װ���Լ���Ӧ�Ĳ��Գ���

history:
Version       Date        Author    Modification
-------    ----------    -------    ------------
1.0        2012-3-24      mawei.ma    Create



------------------------------------------------

contents:

hios_player������ ����Ӧ���̳Ǻͽ�����Ϸʹ��
         ��
         ��������test dir: test_hios_player


libTsPlayer������ �Ϻ�����IPTV����Ӱapkʹ��
         ��
         ��������test dir: test_libTsPlayer


local_test ������  ���Գ����Ŀ¼��Ĭ�������Ŀ¼�µĲ��Գ����ڱ�������branch��ʱ�򲻻ᱻ���롿
           ������  ��Ҫ�򿪸�Ŀ¼�µ�Android.mk�еĿ���


build manual:

1. build current branch
   eg:  cd vm_linux/project_x/sys_build/hisense_android/mt5396_cn_android && make -L ODB=true

2. �л���android����Ŀ¼
   eg: cd ../../../../../vm_linux/android/froyo-2.2

3. source �����Ӧ��buildָ��
   eg: source build/envsetup.sh


4. build:  mmm  <dir>
    ��
    �������� build so:  eg:  mmm external/lib3rdCmpb/libTsPlayer
    ��
    �������� build test elf: mmm external/lib3rdCmpb/local_test/test_libTsPlayer
   

