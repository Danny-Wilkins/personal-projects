import sys
for i in sys.argv[1].lower(): print(chr((ord(i) + int(sys.argv[2]) - 97) % 26 + 97), end='') if i.isalpha() else print(i, end='')