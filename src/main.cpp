/*************************************************
 * Author : Zhenjiang.Zhang
 * Email : zjzhang@126.com
 * Date : 2022-07-05
 * Description : libwebrtc example
 * License : MIT license.
 **************************************************/
#include <stdio.h>
#include <condition_variable>
#include <ctime>
#include <iostream>
#include <mutex>
#include <thread>  // std::thread
#include <unistd.h>
#include "libwebrtc.h"
#include "rtc_audio_device.h"
#include "rtc_desktop_capturer.h"
#include "rtc_desktop_device.h"
#include "rtc_media_stream.h"
#include "rtc_media_track.h"
#include "rtc_mediaconstraints.h"
#include "rtc_peerconnection.h"
#include "rtc_peerconnection_factory.h"
#include "rtc_types.h"
#include "rtc_video_device.h"
#include "rtc_video_frame.h"
#include "rtc_video_renderer.h"
using namespace libwebrtc;

int main() {	
  RTCConfiguration config_;
  LibWebRTC::Initialize();
  config_.sdp_semantics = SdpSemantics::kUnifiedPlan;
  config_.tcp_candidate_policy =
      TcpCandidatePolicy::kTcpCandidatePolicyDisabled;
  config_.bundle_policy = BundlePolicy::kBundlePolicyMaxBundle;

  // 初始化PC工厂
  scoped_refptr<RTCPeerConnectionFactory> pcFactory =
      LibWebRTC::CreateRTCPeerConnectionFactory();
  pcFactory->Initialize();
  // 枚举视频设备
  auto video_device_ = pcFactory->GetVideoDevice();
  int cnum = video_device_->NumberOfDevices();
  printf(" Number Of Video Devices %d \r\n", cnum);
  char deviceNameUTF8[255];
  char deviceUniqueIdUTF8[255];
  for (int i = 0; i < cnum; i++) {
    video_device_->GetDeviceName(i, deviceNameUTF8, 254, deviceUniqueIdUTF8,
                                 254);
    printf("\t Name Of Video Devices [%s] [%s]\r\n", deviceNameUTF8,
           deviceUniqueIdUTF8);
  }

  // 枚举音频设备
  auto audio_device_ = pcFactory->GetAudioDevice();
  int rnum = audio_device_->RecordingDevices();
  int pnum = audio_device_->PlayoutDevices();
  printf(" Number Of Audio Recording Devices %d \r\n", rnum);
  char name[RTCAudioDevice::kAdmMaxDeviceNameSize];
  char guid[RTCAudioDevice::kAdmMaxGuidSize];
  for (int i = 0; i < rnum; i++) {
    audio_device_->RecordingDeviceName(i, name, guid);
    printf("\t Name Of Audio Recording Devices [%d] [%s] [%s] \r\n", i, name,
           guid);
  }
  printf(" Number Of Audio Playout Devices %d \r\n", pnum);
  for (int i = 0; i < pnum; i++) {
    audio_device_->PlayoutDeviceName(i, name, guid);
    printf("\t Name Of Audio Playout Devices [%d] [%s] [%s] \r\n", i, name,
           guid);
  }

  pcFactory->Terminate();
}
