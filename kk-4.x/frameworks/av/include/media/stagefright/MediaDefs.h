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

#ifndef MEDIA_DEFS_H_

#define MEDIA_DEFS_H_

namespace android {

extern const char *MEDIA_MIMETYPE_IMAGE_JPEG;
#ifndef ANDROID_DEFAULT_CODE
extern const char *MEDIA_MIMETYPE_VIDEO_VPX;
#endif //ANDROID_DEFAULT_CODE
extern const char *MEDIA_MIMETYPE_VIDEO_VP8;
extern const char *MEDIA_MIMETYPE_VIDEO_VP9;

extern const char *MEDIA_MIMETYPE_VIDEO_AVC;
extern const char *MEDIA_MIMETYPE_VIDEO_MPEG4;
extern const char *MEDIA_MIMETYPE_VIDEO_H263;
extern const char *MEDIA_MIMETYPE_VIDEO_MPEG2;

#if defined (CC_SUPPORT_TV_STAGEFRIGHT)
extern const char *MEDIA_MIMETYPE_VIDEO_MPEG1;
extern const char *MEDIA_MIMETYPE_VIDEO_VP6;
extern const char *MEDIA_MIMETYPE_VIDEO_MJPEG;
extern const char *MEDIA_MIMETYPE_VIDEO_AVS;
#endif

extern const char *MEDIA_MIMETYPE_VIDEO_RAW;
//extern const char *MEDIA_MIMETYPE_VIDEO_SORENSON_SPARK;

extern const char *MEDIA_MIMETYPE_VIDEO_DIVX;
extern const char *MEDIA_MIMETYPE_VIDEO_DIVX3;
extern const char *MEDIA_MIMETYPE_VIDEO_XVID;
extern const char *MEDIA_MIMETYPE_AUDIO_AMR_NB;
extern const char *MEDIA_MIMETYPE_AUDIO_AMR_WB;
extern const char *MEDIA_MIMETYPE_AUDIO_MPEG;           // layer III
extern const char *MEDIA_MIMETYPE_AUDIO_MPEG_LAYER_I;
extern const char *MEDIA_MIMETYPE_AUDIO_MPEG_LAYER_II;
extern const char *MEDIA_MIMETYPE_AUDIO_AAC;
extern const char *MEDIA_MIMETYPE_AUDIO_QCELP;
extern const char *MEDIA_MIMETYPE_AUDIO_VORBIS;
extern const char *MEDIA_MIMETYPE_AUDIO_G711_ALAW;
extern const char *MEDIA_MIMETYPE_AUDIO_G711_MLAW;
extern const char *MEDIA_MIMETYPE_AUDIO_RAW;
extern const char *MEDIA_MIMETYPE_AUDIO_FLAC;
extern const char *MEDIA_MIMETYPE_AUDIO_AAC_ADTS;
extern const char *MEDIA_MIMETYPE_AUDIO_MSGSM;
#if defined (CC_SUPPORT_TV_STAGEFRIGHT)
extern const char *MEDIA_MIMETYPE_AUDIO_ADPCM_MS;
extern const char *MEDIA_MIMETYPE_AUDIO_ADPCM_IMA;
#endif

extern const char *MEDIA_MIMETYPE_CONTAINER_MPEG4;
extern const char *MEDIA_MIMETYPE_CONTAINER_WAV;
extern const char *MEDIA_MIMETYPE_CONTAINER_OGG;
extern const char *MEDIA_MIMETYPE_CONTAINER_MATROSKA;
extern const char *MEDIA_MIMETYPE_CONTAINER_MPEG2TS;
extern const char *MEDIA_MIMETYPE_CONTAINER_AVI;
extern const char *MEDIA_MIMETYPE_CONTAINER_MPEG2PS;

extern const char *MEDIA_MIMETYPE_CONTAINER_WVM;

extern const char *MEDIA_MIMETYPE_TEXT_3GPP;
extern const char *MEDIA_MIMETYPE_TEXT_SUBRIP;

#if defined (CC_SUPPORT_TV_STAGEFRIGHT) && !defined(ANDROID_DEFAULT_CODE)
extern const char *MEDIA_MIMETYPE_APPLICATION_SDP;

#ifdef MTK_VIDEO_HEVC_SUPPORT
extern const char *MEDIA_MIMETYPE_VIDEO_HEVC;
#endif

#ifdef MTK_RMVB_PLAYBACK_SUPPORT
extern const char *MEDIA_MIMETYPE_CONTAINER_RM;
#endif

extern const char *MEDIA_MIMETYPE_VIDEO_REAL_VIDEO;
extern const char *MEDIA_MIMETYPE_AUDIO_REAL_AUDIO;

#ifdef MTK_VIDEO_HEVC_SUPPORT
extern const char *MEDIA_MIMETYPE_VIDEO_HEVC;
#endif

#ifdef MTK_ASF_PLAYBACK_SUPPORT
extern const char *MEDIA_MIMETYPE_CONTAINER_ASF;
#endif

extern const char *MEDIA_MIMETYPE_VIDEO_MJPEG;
extern const char *MEDIA_MIMETYPE_AUDIO_WMA;
extern const char *MEDIA_MIMETYPE_AUDIO_WMAPRO;
extern const char *MEDIA_MIMETYPE_VIDEO_WMV;

extern const char *MEDIA_MIMETYPE_VIDEO_DIVX;
extern const char *MEDIA_MIMETYPE_VIDEO_DIVX3;
extern const char *MEDIA_MIMETYPE_VIDEO_XVID;

#ifndef ANDROID_DEFAULT_WCP_CODE
extern const char *MEDIA_MIMETYPE_AUDIO_WMAPRO;
#endif

#ifdef MTK_FLV_PLAYBACK_SUPPORT
extern const char *MEDIA_MIMETYPE_CONTAINER_FLV;
extern const char *MEDIA_MIMETYPE_VIDEO_FLV;
extern const char *MEDIA_MIMETYPE_AUDIO_FLV;
#endif//#ifdef MTK_FLV_PLAYBACK_SUPPORT

#ifdef MTK_AUDIO_APE_SUPPORT
extern const char *MEDIA_MIMETYPE_AUDIO_APE;
#endif

#ifdef MTK_OGM_PLAYBACK_SUPPORT
extern const char *MEDIA_MIMETYPE_CONTAINER_OGM; 
#endif 


#if defined(MTK_AUDIO_ADPCM_SUPPORT) || defined(HAVE_ADPCMENCODE_FEATURE)
extern const char *MEDIA_MIMETYPE_AUDIO_MS_ADPCM;
extern const char *MEDIA_MIMETYPE_AUDIO_DVI_IMA_ADPCM;
#endif

#ifdef MTK_AIV_SUPPORT
extern const char *MEDIA_MIMETYPE_CONTAINER_AIV;
#endif

#if 1 //defined (CC_SUPPORT_TV_STAGEFRIGHT)
extern const char *MEDIA_MIMETYPE_AUDIO_EC3;
extern const char *MEDIA_MIMETYPE_AUDIO_AC3;
extern const char *MEDIA_MIMETYPE_AUDIO_DTS;
#endif

#endif // #ifndef ANDROID_DEFAULT_CODE

}  // namespace android

#endif  // MEDIA_DEFS_H_
