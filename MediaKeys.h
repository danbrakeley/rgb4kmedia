#ifndef _MEDIA_KEYS_H_
#define _MEDIA_KEYS_H_

const u8 MK_VOL_UP = 0;
const u8 MK_VOL_DOWN = 1;
const u8 MK_MUTE = 2;
const u8 MK_PLAYPAUSE = 3;
const u8 MK_PAUSE = 4;
const u8 MK_STOP = 5;
const u8 MK_NEXT = 6;
const u8 MK_PREV = 7;
const u8 MK_FAST_FORWARD = 8;
const u8 MK_REWIND = 9;

class MediaKeys_ {
public:
  MediaKeys_();

  void press(u8 mk);
  void release(u8 mk);

private:
  u8 keyHeld;
};

extern MediaKeys_ MediaKeys;

#endif
