֧�ֻ��ͣ�MT5507/MS918/MS828/MS628/G9

1.��libtsplayer.so�����/system/lib/Ŀ¼�£�
2.��kdmServer��kdmStart.sh�����/system/bin/Ŀ¼�£�
3.��kdmStart.sh���뿪����������޸�init.rc�ļ���(���ļ����׷����������)��
#permissions for kdmServer
    chmod 0755 /system/bin/kdmStart.sh
    chmod 0755 /system/bin/kdmServer

#deamon kdmServer
service kdmStart /system/bin/kdmStart.sh
    user root
    class main
    oneshot


�������飺
    ͨ������ִ�У�ps | grep kdm����ܿ���/data/kdmServer�����򿪻������ɹ���������������ļ���λ�ú�Ȩ�ޣ��Լ����������