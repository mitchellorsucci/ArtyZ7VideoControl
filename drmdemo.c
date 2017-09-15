#include "resChange.h"

int main() {

    struct drm_mode_modeinfo test_mode = {DRM_MODE("1600x900", DRM_MODE_TYPE_DRIVER, 108000, 1600, 1624, \
    1704, 1800, 0, 900, 901, 904, 1000, 0, \
    DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC)};
    drm_cntrl * test;
    test = drmControlInit("/dev/dri/card0", test_mode);

    uint32_t currentSize = test->create_dumb[test->current_fb]->size;

    uint8_t * mem = (uint8_t *)test->fbMem[0];
    for(int i = 0; i < currentSize; i++) {
        if(i % 4 == 0) {
            *(mem + i) = i % 255;
        } else if (i % 2 == 0) {
            *(mem + i) = i % 127;
        }else {
            *(mem + i) = 0x00;
        }
    }

    uint8_t * mem2 = (uint8_t *)test->fbMem[1];
    for(int i = 0; i < currentSize; i++) {
        if(i % 3 == 0) {
            *(mem2 + i) = 0xFF;
        } else {
            *(mem2 + i) = 0x00;
        }
    }

    char c;
    while(1) {
        c = fgetc(stdin);
        if(c == 'b') {
            // swapFB(test, 2, 0);
            // swapFB(test, 0, 1);
            mapFBtoCRTC(test, 1);
        } else if (c == 'a') {
            // swapFB(test, 1, 0);
            // swapFB(test, 0, 2);
            mapFBtoCRTC(test, 0);
        } else if( c == 'x') {
            break;
        }
    }

    drmControlClose(test);
    return SUCCESS;
}