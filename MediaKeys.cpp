#include <HID.h>
#include "MediaKeys.h"

//
// see https://www.stefanjones.ca/blog/arduino-leonardo-remote-multimedia-keys/
//

static const uint8_t _hidReportDescriptor[] PROGMEM = {
  0x05, 0x0c,                    // Usage Page (Consumer Devices)
  0x09, 0x01,                    // Usage (Consumer Control)
  0xa1, 0x01,                    // Collection (Application)
  0x85, 0x04,                    // REPORT_ID (4)
  0x15, 0x00,                    // Logical Minimum (0)
  0x25, 0x01,                    // Logical Maximum (1)
  0x09, 0xe9,                    // Usage (Volume Up)
  0x09, 0xea,                    // Usage (Volume Down)
  0x75, 0x01,                    // Report Size (1)
  0x95, 0x02,                    // Report Count (2)
  0x81, 0x06,                    // Input (Data, Variable, Relative)

  0x09, 0xe2,                    // Usage (Mute)
  0x95, 0x01,                    // Report Count (1)
  0x81, 0x06,                    // Input (Data, Variable, Relative)

  0x09, 0xcd,                    // Usage (Play/Pause)
  0x95, 0x01,                    // Report Count (1)
  0x81, 0x06,                    // Input (Data, Variable, Relative)

  0x09, 0xb1,                    // Usage (Pause)
  0x95, 0x01,                    // Report Count (1)
  0x81, 0x06,                    // Input (Data, Variable, Relative)

  0x09, 0xb7,                    // Usage (Stop)
  0x95, 0x01,                    // Report Count (1)
  0x81, 0x06,                    // Input (Data, Variable, Relative)

  0x09, 0xb5,                    // Usage (Next)
  0x95, 0x01,                    // Report Count (1)
  0x81, 0x06,                    // Input (Data, Variable, Relative)

  0x09, 0xb6,                    // Usage (Previous)
  0x95, 0x01,                    // Report Count (1)
  0x81, 0x06,                    // Input (Data, Variable, Relative)

  0x09, 0xb3,                    // Usage (Fast Forward)
  0x95, 0x01,                    // Report Count (1)
  0x81, 0x06,                    // Input (Data, Variable, Relative)

  0x09, 0xb4,                    // Usage (Rewind)
  0x95, 0x01,                    // Report Count (1)
  0x81, 0x06,                    // Input (Data, Variable, Relative)

  0x95, 0x06,                    // Report Count (6) Number of bits remaining in byte
  0x81, 0x07,                    // Input (Constant, Variable, Relative) 

  0xc0                           // End Collection
};

const u8 noKeyHeld = 255;

MediaKeys_::MediaKeys_() {
  keyHeld = noKeyHeld;

  static HIDSubDescriptor node(_hidReportDescriptor, sizeof(_hidReportDescriptor));
  HID().AppendDescriptor(&node);
}

void mediaKeys_doPress(u16 w) {
  u8 m[2];
  m[0] = (u8)(w & 0xFF);
  m[1] = (u8)(w >> 8);
  HID().SendReport(4, m, 2);
}

void MediaKeys_::press(u8 mk) {
  release(mk);
  mediaKeys_doPress(1 << mk);
  keyHeld = mk;
}

void MediaKeys_::release(u8 mk) {
  if (keyHeld != mk) {
    return;
  }
  mediaKeys_doPress(0);
  keyHeld = noKeyHeld;
}

// global instance
MediaKeys_ MediaKeys;
