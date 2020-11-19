#pragma once
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#ifndef MAPVK_VK_TO_VSC
#define MAPVK_VK_TO_VSC 0
#endif
#ifndef MAPVK_VSC_TO_VK
#define MAPVK_VSC_TO_VK 1
#endif
#ifndef MAPVK_VK_TO_CHAR
#define MAPVK_VK_TO_CHAR 2
#endif
#ifndef MAPVK_VSC_TO_VK_EX
#define MAPVK_VSC_TO_VK_EX 3
#endif
#ifndef VK_XBUTTON1
#define VK_XBUTTON1 0x05
#endif
#ifndef VK_XBUTTON2
#define VK_XBUTTON2 0x06
#endif
#ifndef VK_VOLUME_MUTE
#define VK_VOLUME_MUTE 0xAD
#endif
#ifndef VK_VOLUME_DOWN
#define VK_VOLUME_DOWN 0xAE
#endif
#ifndef VK_VOLUME_UP
#define VK_VOLUME_UP 0xAF
#endif
#ifndef VK_MEDIA_NEXT_TRACK
#define VK_MEDIA_NEXT_TRACK 0xB0
#endif
#ifndef VK_MEDIA_PREV_TRACK
#define VK_MEDIA_PREV_TRACK 0xB1
#endif
#ifndef VK_MEDIA_STOP
#define VK_MEDIA_STOP 0xB2
#endif
#ifndef VK_MEDIA_PLAY_PAUSE
#define VK_MEDIA_PLAY_PAUSE 0xB3
#endif
#ifndef VK_LAUNCH_MAIL
#define VK_LAUNCH_MAIL 0xB4
#endif
#ifndef VK_LAUNCH_MEDIA_SELECT
#define VK_LAUNCH_MEDIA_SELECT 0xB5
#endif
#ifndef VK_LAUNCH_APP1
#define VK_LAUNCH_APP1 0xB6
#endif
#ifndef VK_LAUNCH_APP2
#define VK_LAUNCH_APP2 0xB7
#endif
#ifndef WM_POINTERDOWN
#define WM_POINTERDOWN 0x0246
#endif
#ifndef WM_POINTERUP
#define WM_POINTERUP 0x0247
#endif
#ifndef WM_POINTERUPDATE
#define WM_POINTERUPDATE 0x0245
#endif
#ifndef GET_POINTERID_WPARAM
#define GET_POINTERID_WPARAM(wparam) (wparam & 0xFFFF)
#endif
#ifndef IS_POINTER_PRIMARY_WPARAM
#define IS_POINTER_PRIMARY_WPARAM(wparam) (wparam & 0x20000000)
#endif
// #ifndef POINTER_INFO
// typedef struct tagPOINTER_INFO {
//   POINTER_INPUT_TYPE         pointerType;
//   UINT32                     pointerId;
//   UINT32                     frameId;
//   POINTER_FLAGS              pointerFlags;
//   HANDLE                     sourceDevice;
//   HWND                       hwndTarget;
//   POINT                      ptPixelLocation;
//   POINT                      ptHimetricLocation;
//   POINT                      ptPixelLocationRaw;
//   POINT                      ptHimetricLocationRaw;
//   DWORD                      dwTime;
//   UINT32                     historyCount;
//   INT32                      InputData;
//   DWORD                      dwKeyStates;
//   UINT64                     PerformanceCount;
//   POINTER_BUTTON_CHANGE_TYPE ButtonChangeType;
// } POINTER_INFO;
// #endif
// #ifndef POINTER_TOUCH_INFO
// typedef ULONG TOUCH_FLAGS;
// typedef ULONG TOUCH_MASK;
// typedef struct tagPOINTER_TOUCH_INFO {
//   POINTER_INFO pointerInfo;
//   TOUCH_FLAGS  touchFlags;
//   TOUCH_MASK   touchMask;
//   RECT         rcContact;
//   RECT         rcContactRaw;
//   UINT32       orientation;
//   UINT32       pressure;
// } POINTER_TOUCH_INFO;
// #endif