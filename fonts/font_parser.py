#!/usr/bin/env python3
import sys
from PIL import Image, ImageFont, ImageDraw

GLYPHS = [
    'ABCDEFGHIJKLMNOPQRTUVWXYZ',
    'abcdefghijklmnopqrstuvwxyz',
    '0123456789',
]
GLYPH_HEIGHT = 16
GLYPH_WIDTH = 8
GLYPH_V_SPACING = 0
GLYPH_H_SPACING = 0


def get_glyph_index(glyph: str) -> tuple[int, int] | None:
    if len(glyph) != 1:
        raise ValueError(glyph)

    for y in range(len(GLYPHS)):
        res = GLYPHS[y].find(glyph)
        if res > 0:
            return (res, y)

    return None


def get_glyph_box(glyph: str) -> tuple[int, int, int, int] | None:
    coords = get_glyph_index(glyph)
    if coords is None:
        return None
    x, y = coords
    x0 = GLYPH_H_SPACING + x * (GLYPH_WIDTH + GLYPH_H_SPACING)
    y0 = GLYPH_V_SPACING + y * (GLYPH_HEIGHT + GLYPH_V_SPACING)
    x1 = x0 + GLYPH_WIDTH
    y1 = y0 + GLYPH_HEIGHT

    return (x0, y0, x1, y1)


def get_glyphs_boxes() -> dict[str, tuple[int, int, int, int]]:
    res = {}
    for line in GLYPHS:
        for glyph in line:
            res[glyph] = get_glyph_box(glyph)

    return res


def get_glyph_pixels(img: Image.Image) -> dict[str, list[tuple[int, int]]]:
    glyph_boxes = get_glyphs_boxes()

    res = {}
    for glyph in glyph_boxes:
        glyph_img = img.crop(glyph_boxes[glyph])
        pixels = []
        for x in range(GLYPH_WIDTH):
            for y in range(GLYPH_HEIGHT):
                if glyph_img.getpixel((x, y)) > 0:
                    pixels.append((x, y))

        res[glyph] = pixels

    return res


def render_font(path: str,
                width: int = 800,
                height: int = 600,
                font_size: int = 16) -> Image.Image:
    img = Image.new('1', (width, height))
    draw = ImageDraw.Draw(img)

    font = ImageFont.truetype(sys.argv[1], size=font_size)

    for y in range(len(GLYPHS)):
        for x in range(len(GLYPHS[y])):
            glyph = GLYPHS[y][x]
            glyph_x = GLYPH_H_SPACING + x * (GLYPH_WIDTH + GLYPH_H_SPACING)
            glyph_y = GLYPH_V_SPACING + y * (GLYPH_HEIGHT + GLYPH_V_SPACING)
            draw.text((glyph_x, glyph_y), glyph, font=font, fill=1)

    lines_len = [len(line) for line in GLYPHS]
    img_width = GLYPH_H_SPACING + max(lines_len) * (GLYPH_WIDTH +
                                                    GLYPH_H_SPACING)
    img_height = GLYPH_V_SPACING + len(GLYPHS) * (GLYPH_HEIGHT +
                                                  GLYPH_V_SPACING)
    return img.crop((0, 0, img_width, img_height))


if __name__ == '__main__':
    img = render_font(sys.argv[1])

    print(get_glyph_pixels(img)['A'])
    img.save('font.png')
