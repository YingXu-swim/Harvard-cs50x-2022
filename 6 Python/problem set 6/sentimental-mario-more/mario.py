# TODO
from cs50 import get_int

while 1:
    h = get_int("Height: ")
    if h > 0 and h < 9:
        break

for i in range(h):
    # left
    print(" " * (h-i-1) + "#" * (i + 1), end=" " * 2)
    # right
    print("#" * (i + 1))