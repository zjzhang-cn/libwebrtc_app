###Linux
```bash
gn gen out/x64/release --args="target_os=\"linux\" target_cpu=\"x64\" rtc_use_dummy_audio_file_devices=false is_component_build=false is_clang=true is_debug=false rtc_use_h264=true ffmpeg_branding=\"Chrome\" rtc_include_tests=false rtc_build_examples=false libwebrtc_desktop_capture=false"
ninja -C out/x64/release libwebrtc_app

```
###andorid
```bash
gn gen out/arm/linux --args="target_os=\"linux\" target_cpu=\"arm\" rtc_use_dummy_audio_file_devices=false is_component_build=false is_clang=true is_debug=false rtc_use_h264=true ffmpeg_branding=\"Chrome\" rtc_include_tests=false rtc_build_examples=false libwebrtc_desktop_capture=false"
ninja -C out/arm/linux  libwebrtc_app
```

```patch
diff --git a/BUILD.gn b/BUILD.gn
index e60d7dd0bd..b9b6acab8b 100644
--- a/BUILD.gn
+++ b/BUILD.gn
@@ -29,7 +29,7 @@ if (!build_with_chromium) {
   # 'ninja default' and then 'ninja all', the second build should do no work.
   group("default") {
     testonly = true
-    deps = [ ":webrtc" ]
+    deps = [ ":webrtc","//libwebrtc", "//libwebrtc_app"]
     if (rtc_build_examples) {
       deps += [ "examples" ]
     }