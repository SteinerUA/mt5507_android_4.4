����TS��:
������0x47��ͷ��188�ֽڵ�TS��
CTsPlayer����:
class ITsPlayer{
public:
	ITsPlayer(){}
	virtual ~ITsPlayer(){}
public:
	//ȡ�ò���ģʽ
	virtual int  GetPlayMode()=0;
	//��ʾ����
	virtual int  SetVideoWindow(int x,int y,int width,int height)=0;
	//16λɫ����Ҫ����colorkey��͸����Ƶ��
	virtual int  SetColorKey(int enable,int key565)=0;
	//x��ʾ��Ƶ
	virtual int  VideoShow(void)=0;
	//������Ƶ
	virtual int  VideoHide(void)=0;
	//��ʼ����Ƶ����
	virtual void InitVideo(PVIDEO_PARA_T pVideoPara)=0;
	//��ʼ����Ƶ����
	virtual void InitAudio(PAUDIO_PARA_T pAudioPara)=0;
	//��ʼ����
	virtual bool StartPlay()=0;
	//��ts��д��
	virtual int WriteData(unsigned char* pBuffer, unsigned int nSize)=0;
	//��ͣ
	virtual bool Pause()=0;
	//��������
	virtual bool Resume()=0;
	//�������
	virtual bool Fast()=0;
	//ֹͣ�������
	virtual bool StopFast()=0;
	//ֹͣ
	virtual bool Stop()=0;
    //��λ
    virtual bool Seek()=0;
    //�趨����
	//�趨����
	virtual bool SetVolume(int volume)=0;
	//��ȡ����
	virtual int GetVolume()=0;
	//�趨��Ƶ��ʾ����
	virtual bool SetRatio(int nRatio)=0;
	//��ȡ��ǰ����
	virtual int GetAudioBalance()=0;
	//��������
	virtual bool SetAudioBalance(int nAudioBalance)=0;
	//��ȡ��Ƶ�ֱ���
	virtual void GetVideoPixels(int& width, int& height)=0;
	//�Ƿ���������죬�����Ӳ�����죬�뷵��false
	virtual bool IsSoftFit()=0;
	//����EPG��С������̶�640*530��������1280*720���ڸ���ƽ̨����Щҳ�滹��640*530������ʱ�������ֱַ������л�������Ҫ�������ݲ�ͬ�ֱ�������������
	virtual void SetEPGSize(int w, int h);
};

ʵ��CTsPlayer��:

typedef struct{
	unsigned short	pid;//pid
	int				nVideoWidth;//��Ƶ���
	int				nVideoHeight;//��Ƶ�߶�
	int				nFrameRate;//֡��
	vformat_t		vFmt;//��Ƶ��ʽ IPTV��ΪVFORMAT_H264,��vformat.h
	unsigned long	cFmt;//�����ʽ IPTV��ΪCODEC_TAG_H264
}VIDEO_PARA_T, *PVIDEO_PARA_T;
typedef struct{
	unsigned short	pid;//pid
	int				nChannels;//������
	int				nSampleRate;//������
	aformat_t		aFmt;//��Ƶ��ʽ IPTV��ΪAFORMAT_MPEG,��aformat.h
	int				nExtraSize;
	unsigned char*	pExtraData;	
}AUDIO_PARA_T, *PAUDIO_PARA_T;


���о��巽������:(��ֱ�ӿ�TsPlayer.cpp)
	//ȡ�ò���ģʽ��������ֱ�ӷ���1
	int  GetPlayMode();
	//��ʾ����
	int  SetVideoWindow(int x,int y,int width,int height);
	//����colorkey��͸����Ƶ��32λ���ã�����-1
	int  SetColorKey(int enable,int key565);
	//��ʾ��Ƶ
	int  VideoShow(void);
	//������Ƶ
	int  VideoHide(void);
	//��ʼ����Ƶ����
	void InitVideo(PVIDEO_PARA_T pVideoPara);
	//��ʼ����Ƶ����
	void InitAudio(PAUDIO_PARA_T pAudioPara);
	//��ʼ����
	bool StartPlay();
	//��ts��д��
	int WriteData(unsigned char* pBuffer, unsigned int nSize);
	//��ͣ
	bool Pause();
	//��������
	bool Resume();
	//�������,����Fast���յ���TS��ֻ����Ƶû����Ƶ,����Ҫ����ͬ��,�յ�һ֡��ʾһ֡
	bool Fast();
	//ֹͣ�������,֮���յ���TS��Ϊ�������ŵ�,����Ƶ����,��Ҫ����ͬ��
	bool StopFast();
	//ֹͣ
	bool Stop();
	//��λ,��Ҫ����ͬ������Ƶ
	bool Seek();
	//�趨����,������Ϊ��ǰӰƬ������,������ϵͳ����(0~100)
	bool SetVolume(int volume);
	//��ȡ����,������Ϊ��ǰӰƬ������,������ϵͳ����(0~100)
	int GetVolume();
	//�趨��Ƶ��ʾ����,Ԥ���ݲ���ʵ��
	bool SetRatio(int nRatio);
	//��ȡ��ǰ����
	int GetAudioBalance();
	//��������
	bool SetAudioBalance(int nAudioBalance);
	//��ȡ��Ƶϵͳ��ʾ�ֱ��ʣ����ǵ�ǰӰƬ�ķֱ���
	void GetVideoPixels(int& width, int& height);
	//�Ƿ���������죬�����Ӳ�����죬�뷵��false
	virtual bool IsSoftFit()=0;
	//����EPG��С������̶�640*530��������1280*720���ڸ���ƽ̨����Щҳ�滹��640*530������ʱ�������ֱַ������л�������Ҫ�������ݲ�ͬ�ֱ�������������
	virtual void SetEPGSize(int w, int h);

��ʼ����ʱ,����˳��:
InitVideo
InitAudio
SetVideoWindow
SetColorKey
VideoShow
StartPlay

�¼�һ������
ITsPlayer* GetTsPlayer();
��cpp��
ITsPlayer* GetTsPlayer()
{
	return new CTsPlayer();
}
