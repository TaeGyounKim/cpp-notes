// "형변환, 부동소수점, 연산자" 글의 시각화: 연산자와 형변환으로 평균 구하기.

const total = (value) => ({ id: 'total', name: 'total', type: 'int', addr: '0x100', value });
const count = (value) => ({ id: 'count', name: 'count', type: 'int', addr: '0x104', value });
const rough = (value) => ({ id: 'rough', name: 'rough', type: 'int', addr: '0x108', value });
const exact = (value) => ({ id: 'exact', name: 'exact', type: 'double', addr: '0x110', value });

export default {
	code: `int main()
{
    int total{ 0 };
    int count{ 0 };
    total += 85;
    count++;
    total += 90;
    count++;
    int rough{ total / count };
    double exact{
        static_cast<double>(total) / count };
}`,
	steps: [
		{
			line: 3,
			note: '점수의 합을 담을 칸. 0으로 시작',
			stack: [total('0')],
		},
		{
			line: 4,
			note: '점수의 개수를 담을 칸. 0으로 시작',
			stack: [total('0'), count('0')],
		},
		{
			line: 5,
			note: 'total += 85는 total = total + 85와 같음. 0 + 85 = 85',
			stack: [total('85'), count('0')],
		},
		{
			line: 6,
			note: 'count++는 count를 1 올림',
			stack: [total('85'), count('1')],
		},
		{
			line: 7,
			note: '85 + 90 = 175',
			stack: [total('175'), count('1')],
		},
		{
			line: 8,
			note: 'count가 2가 됨',
			stack: [total('175'), count('2')],
		},
		{
			line: 9,
			note: 'int를 int로 나누면 결과도 int. 175 / 2는 87.5가 아니라 87. 소수 부분은 버려짐',
			stack: [total('175'), count('2'), rough('87')],
		},
		{
			line: 11,
			note: 'total을 double로 바꾼 값 175.0으로 나눔. count도 double로 자동 변환되어 175.0 / 2.0 = 87.5. total 자체는 int 175 그대로',
			stack: [total('175'), count('2'), rough('87'), exact('87.5')],
		},
	],
};
