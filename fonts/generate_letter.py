#!/usr/bin/env python3
import os
import sys
import font_parser

PRINT_CHAR = 'X'

SOURCE_START = '''#pragma once

#ifdef __cplusplus
extern "C" {
#endif
'''
SOURCE_END = '''
#ifdef __cplusplus
}
#endif
'''
ARR_TYPE = 'uint16_t'
LEN_TYPE = 'uint16_t'
CONST_NAME = 'letterXY'


def parse_matrix(lines: list[str]) -> list[tuple[int, int]]:
    res = []
    for y in range(len(lines)):
        for x in range(len(lines[y])):
            if lines[y][x:x + 1] == PRINT_CHAR:
                res.append((x, y))

    return res


def generate_arr_source(letter: str,
                        points: list[tuple[int, int]],
                        chunk_len: int = 5) -> list[str]:
    res = []

    res.append(f'const {ARR_TYPE} {CONST_NAME}_{letter}[] = {{')

    point_chunks = [
        points[i:i + chunk_len] for i in range(0, len(points), chunk_len)
    ]
    for chunk in point_chunks:
        line = '\t'.join([f'{point[0]}, {point[1]}' for point in chunk])
        res.append(f'    {line}')

    res.append('};')
    res.append(f'const {LEN_TYPE} {CONST_NAME}_{letter}_len = {len(points)};')

    return res


def generate_source(glyphs: dict[str, list[tuple[int, int]]]) -> list[str]:
    res = SOURCE_START.split('\n')
    res.append('')

    for key in glyphs:
        res.extend(generate_arr_source(key, glyphs[key]))
        res.append('')

    res.append('')
    res.extend(SOURCE_END.split('\n'))
    return res


def read_folder(path: str) -> dict[str, list[tuple[int, int]]]:
    files = []
    for item in os.scandir(path):
        if item.is_file():
            files.append(item.path)

    res = {}
    for item in files:
        with open(item, 'r') as f:
            points = parse_matrix(f.readlines())
            res[os.path.basename(item).split('.')[0]] = points

    return res


if __name__ == '__main__':
    img = font_parser.render_font(sys.argv[1])
    glyphs = font_parser.get_glyph_pixels(img)

    # glyphs = read_folder(sys.argv[1])

    with open('../main/font.h', 'w') as res:
        res.write('\n'.join(generate_source(glyphs)))
