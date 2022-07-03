# TODO
from cs50 import get_float
from math import floor
while 1:
    money = get_float("Change owed: ")
    if money >=0:
        break
cnt = 0

if money / 0.25 >= 1:
    cnt += floor(money / 0.25)
    money = round(money % 0.25, 2)

if money / 0.1 >= 1:
    cnt += floor(money / 0.1)
    money = round(money % 0.1, 2)

if money / 0.05 >= 1:
    cnt += floor(money / 0.05)
    money = round(money % 0.05, 2)

if money / 0.01 >= 1:
    cnt += floor(money / 0.01)
    money = round(money % 0.01, 2)

print(cnt)