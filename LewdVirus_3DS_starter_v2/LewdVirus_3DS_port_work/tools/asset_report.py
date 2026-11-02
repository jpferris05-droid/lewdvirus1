#!/usr/bin/env python3
"""Inventory recovered RPG Maker assets; optionally make 3DS-sized previews.

Requires Pillow: python -m pip install Pillow
Examples:
  python asset_report.py /path/to/LewdVirus_recovered_project
  python asset_report.py /path/to/project --previews /path/to/previews --limit 100
"""
from pathlib import Path
from collections import Counter
import argparse, json

p = argparse.ArgumentParser()
p.add_argument('project', type=Path)
p.add_argument('--previews', type=Path)
p.add_argument('--limit', type=int, default=0)
a = p.parse_args()
root = a.project
for folder in ('Data', 'Graphics', 'Audio', 'Scripts', 'PluginScripts'):
    base = root / folder
    files = [x for x in base.rglob('*') if x.is_file()] if base.exists() else []
    exts = Counter(x.suffix.lower() or '[none]' for x in files)
    print(f'{folder}: {len(files)} files, {sum(x.stat().st_size for x in files)/1024/1024:.1f} MiB')
    print('  ' + ', '.join(f'{k}={v}' for k,v in exts.most_common()))

if a.previews:
    try:
        from PIL import Image
    except ImportError:
        raise SystemExit('Pillow is required: python -m pip install Pillow')
    srcs = sorted((root/'Graphics').rglob('*.png'))
    if a.limit:
        srcs = srcs[:a.limit]
    a.previews.mkdir(parents=True, exist_ok=True)
    manifest = []
    for src in srcs:
        rel = src.relative_to(root/'Graphics')
        out = a.previews / rel
        out.parent.mkdir(parents=True, exist_ok=True)
        with Image.open(src) as im:
            original = im.size
            im.thumbnail((320, 240), Image.Resampling.LANCZOS)
            im.save(out, optimize=True)
        manifest.append({'source': str(rel), 'preview': str(out.relative_to(a.previews)),
                         'original_size': original})
    (a.previews/'manifest.json').write_text(json.dumps(manifest, indent=2))
    print(f'Wrote {len(manifest)} resized PNG previews to {a.previews}')
