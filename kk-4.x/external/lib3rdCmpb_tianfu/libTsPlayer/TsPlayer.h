#ifndef _TSPLAYER_H_
#define _TSPLAYER_H_
#include <stdio.h>
#include <stdlib.h>
extern "C" {
#include "vformat.h"
#include "aformat.h"
}

#include <pthread.h>
#include <semaphore.h>
#include "IMtkPb_Ctrl.h"
#include "IMtkPb_Ctrl_DTV.h"

//#define ENABLE_VIDEO_HIDE_SHOW  (0)    /*��video show & hide ��ʵ�ʵĶ���*/
#define ENABLE_PRINT_DEBUG_LOG  (1)    /*��ʾdebug log ��Ϣ*/
#define ENABLE_WAIT_CHANGE_AV   (1)    /*1 -- �ȴ�changeVideo & changeAudio ��ɵ�ʱ����������*/
#define ENABLE_LOCAL_TEST       (0)    /*1 -- ���뱾�ز��Եİ汾0 -- ����ʵ��ʹ�õİ汾*/

#define ENABLE_KEEP_LAST_FRAME  (1)    /*��̨�������һ֡*/
#define ENABLE_DO_NOT_BLOCK_WRITE_DATA   (1)   /*1 -- ������WriteData()�������ã�ֱ�ӷ���ʧ��  0 -- ����*/


#if ENABLE_PRINT_DEBUG_LOG
#define ENABLE_SHOW_EXEC_TIME   (1)    /*��ӡTsPlyer �к���ִ�е�ʱ��㣬���ʱ��*/
#else
#define ENABLE_SHOW_EXEC_TIME   (0)
#endif


#define TRICKMODE_NONE       0x00
#define TRICKMODE_I          0x01
#define TRICKMODE_FFFB       0x02


typedef struct
{
    unsigned short	pid;//pid
    int				nVideoWidth;//��Ƶ���
    int				nVideoHeight;//��Ƶ�߶�
    int				nFrameRate;//֡��
    vformat_t		vFmt;//��Ƶ��ʽ
    unsigned long	cFmt;//�����ʽ
} VIDEO_PARA_T, *PVIDEO_PARA_T;
typedef struct
{
    unsigned short	pid;//pid
    int				nChannels;//������
    int				nSampleRate;//������
    aformat_t		aFmt;//��Ƶ��ʽ
    int				nExtraSize;
    unsigned char*	pExtraData;
} AUDIO_PARA_T, *PAUDIO_PARA_T;

class CTsPlayer;

class ITsPlayer
{
public:
    ITsPlayer() {}
    virtual ~ITsPlayer() {}
public:
    //ȡ�ò���ģʽ
    virtual int  GetPlayMode() = 0;
    //��ʾ����
    virtual int  SetVideoWindow(int x, int y, int width, int height) = 0;
    //16λɫ����Ҫ����colorkey��͸����Ƶ��
    virtual int  SetColorKey(int enable, int key565) = 0;
    //x��ʾ��Ƶ
    virtual int  VideoShow(void) = 0;
    //������Ƶ
    virtual int  VideoHide(void) = 0;
    //��ʼ����Ƶ����
    virtual int InitVideo(PVIDEO_PARA_T pVideoPara) = 0;
    //��ʼ����Ƶ����
    virtual int InitAudio(PAUDIO_PARA_T pAudioPara) = 0;
    //��ʼ����
    virtual bool StartPlay() = 0;
    //��ts��д��
    virtual int WriteData(unsigned char* pBuffer, unsigned int nSize) = 0;
    //��ͣ
    virtual bool Pause() = 0;
    //��������
    virtual bool Resume() = 0;
    //�������
    virtual bool Fast() = 0;
    //ֹͣ�������
    virtual bool StopFast() = 0;
    //ֹͣ
    virtual bool Stop() = 0;

    virtual bool StopExt() = 0;
    //��λ
    virtual bool Seek() = 0;
    //�趨����
    //�趨����
    virtual bool SetVolume(int volume) = 0;
    //��ȡ����
    virtual int GetVolume() = 0;
    //�趨��Ƶ��ʾ����
    virtual bool SetRatio(int nRatio) = 0;
    //��ȡ��ǰ����
    virtual int GetAudioBalance() = 0;
    //��������
    virtual bool SetAudioBalance(int nAudioBalance) = 0;
    //��ȡ��Ƶ�ֱ���
    virtual void GetVideoPixels(int& width, int& height) = 0;
    virtual bool IsSoftFit() = 0;
    virtual void SetEPGSize(int w, int h) = 0;
    
//////////////////////for tianfu

uint32_t ui4CmpbHandle;   //cmpb handle

virtual void  enable_keep_last_frame( bool istrue) = 0; /// ENABLE_KEEP_LAST_FRAME = 1;


    virtual int   GetTSInfo(void* pBuf, uint32_t nLen, IMTK_PB_CTRL_TS_SINGLE_PAT_INFO_T*  ptTSInfo) = 0;
    virtual int   GetCurrentPTS(uint64_t* video_pts, uint64_t* audio_pts) = 0;

};



class CTsPlayer : public ITsPlayer
{
public:
    CTsPlayer();
    virtual ~CTsPlayer();
public:
    //ȡ�ò���ģʽ
    virtual int  GetPlayMode();
    //��ʾ����
    virtual int  SetVideoWindow(int x, int y, int width, int height);
    //16λɫ����Ҫ����colorkey��͸����Ƶ��
    virtual int  SetColorKey(int enable, int key565);
    //x��ʾ��Ƶ
    virtual int  VideoShow(void);
    //������Ƶ
    virtual int  VideoHide(void);
    //��ʼ����Ƶ����
    virtual int InitVideo(PVIDEO_PARA_T pVideoPara);
    //��ʼ����Ƶ����
    virtual int InitAudio(PAUDIO_PARA_T pAudioPara);
    //��ʼ����
    virtual bool StartPlay();
    //��ts��д��
    virtual int WriteData(unsigned char* pBuffer, unsigned int nSize);
    //��ͣ
    virtual bool Pause();
    //��������
    virtual bool Resume();
    //�������
    virtual bool Fast();
    //ֹͣ�������
    virtual bool StopFast();
    //ֹͣ
    virtual bool Stop();

    virtual bool StopExt();
    //��λ
    virtual bool Seek();
    //�趨����
    //�趨����
    virtual bool SetVolume(int volume);
    //��ȡ����
    virtual int GetVolume();
    //�趨��Ƶ��ʾ����
    virtual bool SetRatio(int nRatio);
    //��ȡ��ǰ����
    virtual int GetAudioBalance();
    //��������
    virtual bool SetAudioBalance(int nAudioBalance);
    //��ȡ��Ƶ�ֱ���
    virtual void GetVideoPixels(int& width, int& height);
    virtual bool IsSoftFit();
    virtual void SetEPGSize(int w, int h);
    
    /////////////////////////for tianfu
    
    virtual void  enable_keep_last_frame( bool istrue); /// ENABLE_KEEP_LAST_FRAME = 1;
    virtual int   GetTSInfo(void* pBuf, uint32_t nLen, IMTK_PB_CTRL_TS_SINGLE_PAT_INFO_T*  ptTSInfo);
    virtual int   GetCurrentPTS(uint64_t* video_pts, uint64_t* audio_pts);


    //thread for execute player command
    static void* playerCmdProcess(void* arg);
    //cmpb callback
    static IMTK_PB_CB_ERROR_CODE_T cmpbPlayCallback(IMTK_PB_CTRL_EVENT_T eEventType, void* pvTag,  uint32_t u4Data);

#if ENABLE_SHOW_EXEC_TIME
    //get current time: ms  (relatively)
    static long  getTimeMs(void);
#endif




///////////////////////////////

private:
    IMTK_PB_CTRL_FRAME_RATE_T frameRateConvert(int i4_frame_rate);
    IMTK_PB_CTRL_AUD_SAMPLE_RATE_T sampleRateConvert(int sample_rate);

private:
    
    int i4CmpbLastRet;       // 0--no error  1--init error  2--setmediainfo error  3--play/resume error  4--pause error  5--setspeed error  6--stop error
    IMTK_PB_CTRL_SET_MEDIA_INFO_T   tLastMediaInfo;   // media info last play info
    IMTK_PB_CTRL_SET_MEDIA_INFO_T   tCurtMediaInfo;   // media info this time play info
    IMTK_PB_CTRL_AUD_INFO_T tAudInfo;                 // audio info  for changeAudio
    IMTK_PB_CTRL_VID_INFO_T tVidInfo;                 // video info  for changeVideo

    uint32_t ui4RectX;        //video show area: x
    uint32_t ui4RectY;        //video show area: y
    uint32_t ui4RectW;        //video show area: width
    uint32_t ui4RectH;        //video show area: height
    
    

    uint32_t ui4WriteDataTimes; /* show times of sending data*/
    uint32_t ui4FirstPlayFlag;  /*just for the first time play*/
    uint32_t ui4SpeedUpdateFlag;  /*����SPEED_UPDATE ��IMtk_Pb_Ctrl_SetSpeed ����Ҫ���ʱ�������*/

    int i4AudioBalance;//1:��������2:��������3:˫����

#if ENABLE_DO_NOT_BLOCK_WRITE_DATA
    uint32_t ui4FlagNotSend;    /* 0 -- can  send data   1 -- can not send data������Ӱ���ܱ�֤writeData ��play/stop/pause�ȶ�����ͬ����ʱ����Ҫ���*/
    uint32_t ui4SendFailTimes;  /* δ�ɹ��������ݵĴ���*/
#endif

#if ENABLE_WAIT_CHANGE_AV
    uint32_t ui4FlagWaitAv;           // 3--can send data  1--video 2--audio
#endif

    uint32_t ui4FlagPlayDone;

    uint32_t ui4FlagDummyPlay;       // 0 -- call start play  1 -- dummy play  (because of  function CTsPlayer::Stop() will  be called twice by Suing in one play )
    IMTK_PB_CTRL_SPEED_T ePlaySpeed; // current play speed, for CTsPlayer::Fast() & CTsPlayer::StopFast()

    int i4MsgQueHandle;          // msg queue handle which used to send command to thread for member function of CTsPlayer
    pthread_t   pidCmdProcess;   // pid of thread which receive command and excute command(play/stop/setmediainfo)

    /*ʹ���첽ִ�еķ�ʽ��������ٶȣ��첽ִ�еĶ�����������һ���߳������У�
      �����ϲ����CTsPlayer::Stop() ��ʱ�����cmpb ��IMtkPb_Ctrl_Stop(), IMtkPb_Ctrl_SetMediaInfo(), IMtkPb_Ctrl_Play()��
      �������ϲ����CTsPlayer::StartPlay()��ʱ�����ж�mediaInfo ��Ϣ�Ƿ��иı䣬����иı䣬
      �����changeAudio & changeVideo ������(��Ϊ�Ϻ���������media info���ٸı䣬���Կ����ṩ���ٶ�)
       */
};

ITsPlayer* GetTsPlayer();

#if ENABLE_LOCAL_TEST
ITsPlayer* GetTsPlayerForTest(char* srcType);
#endif

#endif
