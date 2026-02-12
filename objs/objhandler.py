import sys
import re

vertices = []
triangles = []
while (line := sys.stdin.readline()):
    if re.match(r"^#", line):
        continue

    # geometric faces
    elif re.match(r"^f",line):
        face = line.rstrip().split(' ')[1:]

        triangle_v = []
        for point in face:
            triangle_v.append(int(point.split('/',1)[0]))

        for i in range(len(triangle_v) - 2):
            triangles.append([triangle_v[0],triangle_v[1 + i],triangle_v[2+i]])
    # vertices
    elif re.match(r"^v",line):
        vertices.append(line.strip().split(' ')[1:])

v = len(vertices)
for triangle in triangles:
    for index in triangle:
        if index < 0:
            index += v
        else:
            index -= 1
        # write vertices to stdout
        print(" ".join(vertices[index]),end=" ")
    print()

