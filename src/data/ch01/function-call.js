// "함수와 어트리뷰트" 글의 시각화: 함수를 호출하면 인수가 매개변수로 복사된다.

const count = { id: 'count', name: 'count', type: 'main · int', addr: '0x100', value: '3' };
const total = (value) => ({ id: 'total', name: 'total', type: 'main · int', addr: '0x104', value });
const pPrice = { id: 'pPrice', name: 'price', type: 'getTotal · int', addr: '0x0e0', value: '4500' };
const pCount = { id: 'pCount', name: 'count', type: 'getTotal · int', addr: '0x0e4', value: '3' };

export default {
	code: `int getTotal(int price, int count)
{
    return price * count;
}

int main()
{
    int count{ 3 };
    int total{ getTotal(4500, count) };
}`,
	steps: [
		{
			line: 8,
			note: 'main의 변수 count에 3이 들어감',
			stack: [count],
		},
		{
			line: 9,
			note: 'total을 초기화하려면 먼저 getTotal(4500, count)의 값이 필요함. 함수를 호출함',
			stack: [count, total('???')],
		},
		{
			line: 1,
			note: '매개변수 칸이 새로 생기고 인수의 값이 복사됨. price에는 4500, count에는 main의 count 값 3. 이름이 같아도 main의 count와는 다른 칸',
			stack: [count, total('???'), pPrice, pCount],
		},
		{
			line: 3,
			note: '4500 * 3 = 13500을 계산해 호출한 곳으로 돌려줌',
			stack: [count, total('???'), pPrice, pCount],
		},
		{
			line: 9,
			note: '함수가 끝나면 매개변수 칸은 사라짐. 돌려받은 13500이 total에 들어감',
			stack: [count, total('13500')],
		},
	],
};
