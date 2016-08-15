# http://stackoverflow.com/a/14637692/1234408
import sys
from PIL import Image


def floodfill(img, seed, color):
    im = img.load()
    work = [seed]
    start_color = im[seed]
    while work:
        x, y = work.pop()
        im[x, y] = color
        for dx, dy in ((-1,0), (1,0), (0,-1), (0,1)):
            nx, ny = x + dx, y + dy
            if im[nx, ny] == start_color:
                work.append((nx, ny))


USA_MAP = Image.open(sys.argv[1]).convert('1')
POINT_STATE = {'AL': (420, 260), 'AZ': (110, 240), 'AR': (350, 250)}

painted_map = USA_MAP.convert('L')
data = {'AL': 10.5, 'AZ': 23.4, 'AR': 15.0}
# Normalize data based on the minimum weight being 0+eps and maximum 30.
for k, v in data.items():
    v = v/30.
    color = int(round(255 * v))
    floodfill(painted_map, POINT_STATE[k], 255 - color)

painted_map.save(sys.argv[2])
