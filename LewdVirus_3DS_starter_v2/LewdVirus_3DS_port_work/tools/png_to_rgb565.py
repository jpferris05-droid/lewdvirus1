#!/usr/bin/env python3
"""Convert a PNG to raw little-endian RGB565 for the 3DS framebuffer prototype."""
import argparse
from pathlib import Path
from PIL import Image
ap=argparse.ArgumentParser(); ap.add_argument("input",type=Path); ap.add_argument("output",type=Path); ap.add_argument("--width",type=int,default=320); ap.add_argument("--height",type=int,default=240); a=ap.parse_args()
im=Image.open(a.input).convert("RGB")
if (im.width,im.height)!=(a.width,a.height): im=im.resize((a.width,a.height),Image.Resampling.LANCZOS)
out=bytearray()
for r,g,b in im.getdata():
 p=((r>>3)<<11)|((g>>2)<<5)|(b>>3); out.extend((p&255,p>>8))
a.output.parent.mkdir(parents=True,exist_ok=True); a.output.write_bytes(out); print(f"Wrote {a.output}: {im.width}x{im.height}, {len(out)} bytes")
