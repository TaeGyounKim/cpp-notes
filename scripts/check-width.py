# 예제 코드에서 화면 폭(한글은 두 칸)이 넓어 편집기에 가로 스크롤이 생길 줄을 찾는다.
# 사용법: python scripts/check-width.py <파일.cpp ...>
import sys, io, unicodedata
LIMIT = 80
bad = 0
for path in sys.argv[1:]:
    for n, line in enumerate(io.open(path, encoding='utf-8'), 1):
        w = sum(2 if unicodedata.east_asian_width(c) in 'WF' else 1 for c in line.rstrip('\n'))
        if w > LIMIT:
            bad += 1
            print(f'{path}:{n}: {w}칸')
print('넘치는 줄 없음' if not bad else f'{bad}줄이 {LIMIT}칸을 넘음')
