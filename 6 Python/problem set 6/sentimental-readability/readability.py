# TODO
from cs50 import get_string

def get_avg_alpha(s):
    result = 0

    for c in s:
        if c >= 'a' and c <= 'z':
            result += 1
        elif c >= 'A' and c <= 'Z':
            result += 1
    return result / len(s.split()) * 100

def get_avg_sen(s):
    sen_cnt = 0

    for c in s:
        if c == "!" or c == "." or c == "?":
            sen_cnt += 1

    return sen_cnt / len(s.split()) * 100

s = get_string("Text: ")

grade = 0.0588 * get_avg_alpha(s) - 0.296 * get_avg_sen(s) - 15.8

if grade < 1:
    print("Before Grade 1")
elif grade >= 16:
    print("Grade 16+")
else:
    print("Grade", round(grade))