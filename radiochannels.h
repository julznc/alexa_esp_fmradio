#ifndef __RADIOCHANNELS_H__
#define __RADIOCHANNELS_H__

#include <stdint.h>

// non-standard channel numbers!
#define STATEVALUE_TO_CHANNEL(val)      ((((uint8_t)val * 2) -2 ) / 5)

// predefined radio stations in Metro Manila PH
static uint16_t FM_STATIONS[] =
{
    8750,  //  1 - 87.5 FM1
    8790,  //  2 - Radyo Katipunan 87.9
    8830,  //  3 - Jam 88.3
    8910,  //  4 - Wave 89.1
    8990,  //  5 - Magic 89.9
    9030,  //  6 - 90.3 Radyo Bandera News FM
    9070,  //  7 - 90.7 Love Radio
    9150,  //  8 - 91.5 Win Radio
    9230,  //  9 - Radyo5 92.3 News FM
    9310,  // 10 - Monster RX 93.1
    9390,  // 11 - 93.9 iFM
    9470,  // 12 - Mellow 947
    9550,  // 13 - Pinas FM 95.5
    9630,  // 14 - 96.3 Easy Rock
    9710,  // 15 - Barangay LS 97.1
    9790,  // 16 - 979 Home Radio
    9830,  // 17 - 98.3 Radyo Kontra Droga
    9840,  // 18 - 98.4 CSFM
    9870,  // 19 - 98.7 DZFE The Master's Touch
    9950,  // 20 - 99.5 Play FM
    9990,  // 21 - Radio Manila 99.9
    10030, // 22 - 100.3 RJFM
    10110, // 23 - 101.1 Yes The Best
    10150, // 24 - The Anchor 101.5
    10190, // 25 - MOR 101.9 For Life!
    10270, // 26 - 102.7 Star FM
    10350, // 27 - 103.5 K-Lite
    10430, // 28 - 104.3 FM2
    10510, // 29 - 105.1 Crossover
    10590, // 30 - Lite FM 105.9
    10670, // 31 - 106.7 Energy FM
    10710, // 32 - 107.1 Radyo Kontra Weeaboo
    10750, // 33 - Wish 107.5
};

#define MAX_FM_CHANNEL          (sizeof(FM_STATIONS) / sizeof(FM_STATIONS[0]))
#define DEFAULT_FM_CHANNEL      (7)

#endif // __RADIOCHANNELS_H__
