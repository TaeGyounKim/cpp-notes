// "조건문과 비교" 글의 시각화: switch 문의 흐름과 fallthrough.

const shipping = { id: 'shipping', name: 'shipping', type: 'Shipping', addr: '0x100', value: 'Overnight' };
const fee = (value) => ({ id: 'fee', name: 'fee', type: 'int', addr: '0x104', value });

export default {
	code: `enum class Shipping { Standard, Express, Overnight };

int main()
{
    Shipping shipping{ Shipping::Overnight };
    int fee{ 3000 };
    switch (shipping) {
        using enum Shipping;
        case Overnight:
            fee += 5000;
            [[fallthrough]];
        case Express:
            fee += 2000;
            break;
        case Standard:
            break;
    }
}`,
	steps: [
		{
			line: 5,
			note: '배송 방법은 Overnight',
			stack: [shipping],
		},
		{
			line: 6,
			note: '기본 배송비 3000',
			stack: [shipping, fee('3000')],
		},
		{
			line: 7,
			note: 'shipping의 값과 같은 case를 찾아 그 자리로 곧장 건너뜀',
			stack: [shipping, fee('3000')],
		},
		{
			line: 9,
			note: '값이 Overnight이므로 이 case부터 실행을 시작',
			stack: [shipping, fee('3000')],
		},
		{
			line: 10,
			note: '3000 + 5000 = 8000',
			stack: [shipping, fee('8000')],
		},
		{
			line: 11,
			note: 'break가 없으므로 멈추지 않음. [[fallthrough]]는 일부러 이어 간다는 표시일 뿐 실행되는 동작은 없음',
			stack: [shipping, fee('8000')],
		},
		{
			line: 13,
			note: 'case Express: 줄은 들어오는 입구일 뿐 실행을 막지 않음. 그대로 이어서 8000 + 2000 = 10000',
			stack: [shipping, fee('10000')],
		},
		{
			line: 14,
			note: 'break를 만나 switch 문을 빠져나감. case Standard 쪽은 실행되지 않음',
			stack: [shipping, fee('10000')],
		},
		{
			line: 18,
			note: 'switch 문 다음으로 이어짐. 최종 배송비는 10000',
			stack: [shipping, fee('10000')],
		},
	],
};
