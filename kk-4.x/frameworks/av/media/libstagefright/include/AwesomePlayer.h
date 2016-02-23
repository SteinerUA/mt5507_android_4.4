/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef AWESOME_PLAYER_H_

#define AWESOME_PLAYER_H_

#include "HTTPBase.h"
#include "TimedEventQueue.h"

#include <media/MediaPlayerInterface.h>
#include <media/stagefright/DataSource.h>
#include <media/stagefright/OMXClient.h>
#include <media/stagefright/TimeSource.h>
#include <media/stagefright/MetaData.h>
#include <utils/threads.h>
#include <drm/DrmManagerClient.h>

#ifndef ANDROID_DEFAULT_CODE
#include <media/stagefright/MetaData.h>
#endif

namespace android {

struct AudioPlayer;
struct DataSource;
struct MediaBuffer;
struct MediaExtractor;
struct MediaSource;
struct NuCachedSource2;
struct IGraphicBufferProducer;

class DrmManagerClinet;
class DecryptHandle;

class TimedTextDriver;
struct WVMExtractor;

#ifndef ANDROID_DEFAULT_CODE 
struct ALooper;
struct MetaData;
#endif
struct AwesomeRenderer : public RefBase {
    AwesomeRenderer() {}

    virtual void render(MediaBuffer *buffer) = 0;

private:
    AwesomeRenderer(const AwesomeRenderer &);
    AwesomeRenderer &operator=(const AwesomeRenderer &);
};

#ifdef CC_SUPPORT_TV_STAGEFRIGHT
#define  TV_LOG_LEVEL_DISABLE 0
#define  TV_LOG_LEVEL_AV_SYNC 1
#define  TV_LOG_LEVEL_RENDER 2
#define  TV_LOG_LEVEL_FLOW 3

#if 0
#define  SOURCE_TYPE_NORMAL 0 //Normal
#define  SOURCE_TYPE_CTS 1 
#define  SOURCE_TYPE_GTS 2 
#define  SOURCE_TYPE_LETV 3 
#endif
#endif
struct AwesomePlayer {
    AwesomePlayer();
    ~AwesomePlayer();

    void setListener(const wp<MediaPlayerBase> &listener);
    void setUID(uid_t uid);

    status_t setDataSource(
            const char *uri,
            const KeyedVector<String8, String8> *headers = NULL);

    status_t setDataSource(int fd, int64_t offset, int64_t length);

    status_t setDataSource(const sp<IStreamSource> &source);

    void reset();

    status_t prepare();
    status_t prepare_l();
    status_t prepareAsync();
    status_t prepareAsync_l();

    status_t play();
    
    status_t pause();

    bool isPlaying() const;

    status_t setSurfaceTexture(const sp<IGraphicBufferProducer> &bufferProducer);
    void setAudioSink(const sp<MediaPlayerBase::AudioSink> &audioSink);
    status_t setLooping(bool shouldLoop);

    status_t getDuration(int64_t *durationUs);
    status_t getPosition(int64_t *positionUs);

    status_t setParameter(int key, const Parcel &request);
    status_t getParameter(int key, Parcel *reply);
    status_t invoke(const Parcel &request, Parcel *reply);
    status_t setCacheStatCollectFreq(const Parcel &request);

    status_t seekTo(int64_t timeUs);

    // This is a mask of MediaExtractor::Flags.
    uint32_t flags() const;

    void postAudioEOS(int64_t delayUs = 0ll);
    void postAudioSeekComplete();
    void postAudioTearDown();
    status_t dump(int fd, const Vector<String16> &args) const;
#if defined (CC_SUPPORT_TV_STAGEFRIGHT) && !defined(ANDROID_DEFAULT_CODE)
    void postDurationUpdateEvent(int64_t duration);
    void postDurationUpdateEvent_l(int64_t duration);    
    bool isNotifyDuration();
    sp<MetaData> getMetaData() const;
#endif

#ifdef CC_SUPPORT_TV_STAGEFRIGHT
    //0: Disbale DTV LOG, 1:Enable AV SYNC LOG. 2: Enable Flow Log.
    int getLogLevel();
#endif


private:
    friend struct AwesomeEvent;
    friend struct PreviewPlayer;

    enum {
        PLAYING             = 0x01,
        LOOPING             = 0x02,
        FIRST_FRAME         = 0x04,
        PREPARING           = 0x08,
        PREPARED            = 0x10,
        AT_EOS              = 0x20,
        PREPARE_CANCELLED   = 0x40,
        CACHE_UNDERRUN      = 0x80,
        AUDIO_AT_EOS        = 0x0100,
        VIDEO_AT_EOS        = 0x0200,
        AUTO_LOOPING        = 0x0400,

        // We are basically done preparing but are currently buffering
        // sufficient data to begin playback and finish the preparation phase
        // for good.
        PREPARING_CONNECTED = 0x0800,

        // We're triggering a single video event to display the first frame
        // after the seekpoint.
        SEEK_PREVIEW        = 0x1000,

        AUDIO_RUNNING       = 0x2000,
        AUDIOPLAYER_STARTED = 0x4000,

        INCOGNITO           = 0x8000,

        TEXT_RUNNING        = 0x10000,
        TEXTPLAYER_INITIALIZED  = 0x20000,

        SLOW_DECODER_HACK   = 0x40000,
#ifndef ANDROID_DEFAULT_CODE
        PGDL_NONINTERLEAVE = 0x01000000,    
        PAUSING          = 0x02000000,
        EOS_HANDLING     = 0x04000000,
        CACHE_MISSING    = 0x80000000,
#endif
    };
 #ifndef ANDROID_DEFAULT_CODE
    enum{
        FINAL_OK=0,
        FINAL_HAS_UNSUPPORT_VIDEO=1,
        FINAL_HAS_UNSUPPORT_AUDIO=2,
        FINAL_UNKNOW=0xFF,
    };

     uint32_t  mFinalStopFlag;
 #endif

    mutable Mutex mLock;
    Mutex mMiscStateLock;
    mutable Mutex mStatsLock;
    Mutex mAudioLock;

    OMXClient mClient;
    TimedEventQueue mQueue;
    bool mQueueStarted;
    wp<MediaPlayerBase> mListener;
    bool mUIDValid;
    uid_t mUID;

    sp<ANativeWindow> mNativeWindow;
    sp<MediaPlayerBase::AudioSink> mAudioSink;

    SystemTimeSource mSystemTimeSource;
    TimeSource *mTimeSource;

    String8 mUri;
    KeyedVector<String8, String8> mUriHeaders;

    sp<DataSource> mFileSource;

    sp<MediaSource> mVideoTrack;
    sp<MediaSource> mVideoSource;
    sp<AwesomeRenderer> mVideoRenderer;
    bool mVideoRenderingStarted;
    bool mVideoRendererIsPreview;
    int32_t mMediaRenderingStartGeneration;
    int32_t mStartGeneration;

    ssize_t mActiveAudioTrackIndex;
    sp<MediaSource> mAudioTrack;
    sp<MediaSource> mOmxSource;
    sp<MediaSource> mAudioSource;
    AudioPlayer *mAudioPlayer;
    int64_t mDurationUs;

    int32_t mDisplayWidth;
    int32_t mDisplayHeight;
    int32_t mVideoScalingMode;

    uint32_t mFlags;
    uint32_t mExtractorFlags;
    uint32_t mSinceLastDropped;

    int64_t mTimeSourceDeltaUs;
    int64_t mVideoTimeUs;
	bool mVideoSourceFlag;

    enum SeekType {
        NO_SEEK,
        SEEK,
        SEEK_VIDEO_ONLY
    };
    SeekType mSeeking;

    bool mSeekNotificationSent;
    int64_t mSeekTimeUs;

    int64_t mBitrate;  // total bitrate of the file (in bps) or -1 if unknown.

    bool mWatchForAudioSeekComplete;
    bool mWatchForAudioEOS;

    sp<TimedEventQueue::Event> mVideoEvent;
    bool mVideoEventPending;
    sp<TimedEventQueue::Event> mStreamDoneEvent;
    bool mStreamDoneEventPending;
    sp<TimedEventQueue::Event> mBufferingEvent;
    bool mBufferingEventPending;
    sp<TimedEventQueue::Event> mCheckAudioStatusEvent;
    bool mAudioStatusEventPending;
    sp<TimedEventQueue::Event> mVideoLagEvent;
    bool mVideoLagEventPending;
    sp<TimedEventQueue::Event> mAudioTearDownEvent;
    bool mAudioTearDownEventPending;
    sp<TimedEventQueue::Event> mAsyncPrepareEvent;
#ifndef ANDROID_DEFAULT_CODE
    sp<TimedEventQueue::Event> mDurationUpdateEvent;
    bool mDurationUpdateEventPending;
#endif
#ifdef CC_SUPPORT_TV_STAGEFRIGHT
     //0: Disbale DTV LOG, 1:Enable AV SYNC LOG. 2: Enable Flow Log.
     int  mDebugLogLevel;
     bool mSWVideoDecoder;
     bool mSWAudioDecoder;
     int  mDebugDisableAudio;
     int  mDebugDisableAVsync;
#endif

    Condition mPreparedCondition;
    bool mIsAsyncPrepare;
    status_t mPrepareResult;
    status_t mStreamDoneStatus;

    void postVideoEvent_l(int64_t delayUs = -1);
    void postBufferingEvent_l();
    void postStreamDoneEvent_l(status_t status);
    void postCheckAudioStatusEvent(int64_t delayUs);
    void postVideoLagEvent_l();
    void postAudioTearDownEvent(int64_t delayUs);

    status_t play_l();

    MediaBuffer *mVideoBuffer;

    sp<HTTPBase> mConnectingDataSource;
    sp<NuCachedSource2> mCachedSource;

    DrmManagerClient *mDrmManagerClient;
    sp<DecryptHandle> mDecryptHandle;

    int64_t mLastVideoTimeUs;
    TimedTextDriver *mTextDriver;

    sp<WVMExtractor> mWVMExtractor;
    sp<MediaExtractor> mExtractor;

    status_t setDataSource_l(
            const char *uri,
            const KeyedVector<String8, String8> *headers = NULL);

    status_t setDataSource_l(const sp<DataSource> &dataSource);
    status_t setDataSource_l(const sp<MediaExtractor> &extractor);
    void reset_l();
    status_t seekTo_l(int64_t timeUs);
    status_t pause_l(bool at_eos = false);
    void initRenderer_l();
    void notifyVideoSize_l();
    void seekAudioIfNecessary_l(int64_t time=-1);

    void cancelPlayerEvents(bool keepNotifications = false);

    void setAudioSource(sp<MediaSource> source);
    status_t initAudioDecoder();


    void setVideoSource(sp<MediaSource> source);
    status_t initVideoDecoder(uint32_t flags = 0);

    void addTextSource_l(size_t trackIndex, const sp<MediaSource>& source);

    void onStreamDone();
#ifndef ANDROID_DEFAULT_CODE
    void OnDurationUpdate();
#endif
    void notifyListener_l(int msg, int ext1 = 0, int ext2 = 0);

    void onVideoEvent();
    void onBufferingUpdate();
    void onCheckAudioStatus();
    void onPrepareAsyncEvent();
    void abortPrepare(status_t err);
    void finishAsyncPrepare_l();
    void onVideoLagUpdate();
    void onAudioTearDownEvent();

    void beginPrepareAsync_l();

    bool getCachedDuration_l(int64_t *durationUs, bool *eos);

    status_t finishSetDataSource_l();

    static bool ContinuePreparation(void *cookie);

    bool getBitrate(int64_t *bitrate);

    void finishSeekIfNecessary(int64_t videoTimeUs);
    void ensureCacheIsFetching_l();

    void notifyIfMediaStarted_l();
    void createAudioPlayer_l();
    status_t startAudioPlayer_l(bool sendErrorNotification = true);

    void shutdownVideoDecoder_l();
    status_t setNativeWindow_l(const sp<ANativeWindow> &native);

    bool isStreamingHTTP() const;
    void sendCacheStats();
    void checkDrmStatus(const sp<DataSource>& dataSource);

    enum FlagMode {
        SET,
        CLEAR,
        ASSIGN
    };
    void modifyFlags(unsigned value, FlagMode mode);

    struct TrackStat {
        String8 mMIME;
        String8 mDecoderName;
    };

    // protected by mStatsLock
    struct Stats {
        int mFd;
        String8 mURI;
        int64_t mBitrate;

        // FIXME:
        // These two indices are just 0 or 1 for now
        // They are not representing the actual track
        // indices in the stream.
        ssize_t mAudioTrackIndex;
        ssize_t mVideoTrackIndex;

        int64_t mNumVideoFramesDecoded;
        int64_t mNumVideoFramesDropped;
        int32_t mVideoWidth;
        int32_t mVideoHeight;
        uint32_t mFlags;
        Vector<TrackStat> mTracks;
    } mStats;

    bool    mOffloadAudio;
    bool    mAudioTearDown;
    bool    mAudioTearDownWasPlaying;
    int64_t mAudioTearDownPosition;

    status_t setVideoScalingMode(int32_t mode);
    status_t setVideoScalingMode_l(int32_t mode);
    status_t getTrackInfo(Parcel* reply) const;

    status_t selectAudioTrack_l(const sp<MediaSource>& source, size_t trackIndex);

    // when select is true, the given track is selected.
    // otherwise, the given track is unselected.
    status_t selectTrack(size_t trackIndex, bool select);

    size_t countTracks() const;

    AwesomePlayer(const AwesomePlayer &);
    AwesomePlayer &operator=(const AwesomePlayer &);
#if defined (CC_SUPPORT_TV_STAGEFRIGHT) && !defined(ANDROID_DEFAULT_CODE)
    int64_t mAVSyncThreshold;
    uint32_t  mLateMargin;
    bool mPrerollEnable;
    int64_t mLastPositionUs;
    int64_t mLastAudioSeekUs;
    uint32_t mSourceType;
#endif 
};

}  // namespace android

#endif  // AWESOME_PLAYER_H_
