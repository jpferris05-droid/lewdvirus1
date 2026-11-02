#include "port_blit.h"
bool port_blit_rgb565_top(const uint16_t *pixels, unsigned width, unsigned height) {
 if (!pixels || width != 320 || height != 240) return false;
 u8 *fb = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL); if (!fb) return false;
 /* libctru BGR8 framebuffer is column-major with a 240-pixel stride. */
 for (unsigned x=0;x<400;x++) for(unsigned y=0;y<240;y++){ unsigned o=(x*240+y)*3; fb[o]=fb[o+1]=fb[o+2]=0; }
 for(unsigned x=0;x<320;x++) for(unsigned y=0;y<240;y++){
  uint16_t p=pixels[y*320+x]; unsigned r=((p>>11)&31)*255/31, g=((p>>5)&63)*255/63, b=(p&31)*255/31;
  unsigned o=((x+40)*240+y)*3; fb[o]=(u8)b; fb[o+1]=(u8)g; fb[o+2]=(u8)r;
 }
 GSPGPU_FlushDataCache(fb,400*240*3); return true;
}
