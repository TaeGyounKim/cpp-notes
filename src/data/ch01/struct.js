// "열거형과 구조체" 글의 시각화: 구조체 변수는 필드 여러 칸의 묶음.

const grade = (value) => ({ id: 'grade', name: 'item.grade', type: 'char', addr: '0x100', value });
const id = (value) => ({ id: 'id', name: 'item.id', type: 'int', addr: '0x104', value });
const price = (value) => ({ id: 'price', name: 'item.price', type: 'int', addr: '0x108', value });
const copyGrade = { id: 'copyGrade', name: 'copy.grade', type: 'char', addr: '0x10c', value: "'A'" };
const copyId = { id: 'copyId', name: 'copy.id', type: 'int', addr: '0x110', value: '1024' };
const copyPrice = (value) => ({ id: 'copyPrice', name: 'copy.price', type: 'int', addr: '0x114', value });

export default {
	code: `struct Product
{
    char grade;
    int id;
    int price;
};

int main()
{
    Product item;
    item.grade = 'A';
    item.id = 1024;
    item.price = 4500;
    Product copy{ item };
    copy.price = 5000;
}`,
	steps: [
		{
			line: 10,
			note: '변수 하나를 만들었지만 칸은 세 개가 생김. 초기화하지 않았으므로 세 칸 모두 알 수 없는 값',
			stack: [grade('???'), id('???'), price('???')],
		},
		{
			line: 11,
			note: 'item의 grade 칸에 문자 A를 넣음. 점(.) 뒤에 필드 이름을 적어 칸을 고름',
			stack: [grade("'A'"), id('???'), price('???')],
		},
		{
			line: 12,
			note: 'item의 id 칸에 1024를 넣음',
			stack: [grade("'A'"), id('1024'), price('???')],
		},
		{
			line: 13,
			note: 'item의 price 칸에 4500을 넣음. 이제 세 칸이 모두 채워짐',
			stack: [grade("'A'"), id('1024'), price('4500')],
		},
		{
			line: 14,
			note: 'item으로 copy를 초기화. 세 칸이 새로 생기고 item의 값이 칸마다 복사됨',
			stack: [grade("'A'"), id('1024'), price('4500'), copyGrade, copyId, copyPrice('4500')],
		},
		{
			line: 15,
			note: 'copy의 price만 바뀜. item과 copy는 서로 다른 칸이므로 item.price는 4500 그대로',
			stack: [grade("'A'"), id('1024'), price('4500'), copyGrade, copyId, copyPrice('5000')],
		},
	],
};
