// "virtual의 실제" 글의 시각화: 객체마다 vtable 포인터가 있고, 가상 함수 호출은 그것을 따라간다.
// 주소와 배치는 설명을 위해 단순하게 그렸다. 실제 배치는 컴파일러마다 다를 수 있다.

const plain = (extra) => ({ id: 'p', name: 'plain의 vptr', type: 'Sensor', addr: '0x100', ...extra });
const kitchen = (extra) => ({ id: 'k', name: 'kitchen의 vptr', type: 'Thermometer', addr: '0x0e0', ...extra });
// 칸 이름에 그 칸이 가리키는 함수를, 타입 자리에 어느 vtable의 몇 번 칸인지 적는다. Thermo는 Thermometer를 줄인 것
const entry = (id, table, fn) => ({ id, name: fn, type: `${table} vtable[${id[1]}]`, addr: id.startsWith('s') ? '0x7a0' : '0x7c0' });

const sensorTable = [entry('s0', 'Sensor', 'Sensor::describe'), entry('s1', 'Sensor', 'Sensor::calibrate')];
const thermoTable = [entry('t0', 'Thermo', 'Thermo::describe'), entry('t1', 'Thermo', 'Sensor::calibrate')];

export default {
	regions: { stack: '객체', heap: '클래스별 vtable' },
	code: `Sensor plain;
Thermometer kitchen;
const Sensor& ref{ kitchen };
ref.describe();
ref.calibrate(0.5);
ref.kind();`,
	steps: [
		{
			line: 1,
			note: 'Sensor 객체는 맨 앞에 숨은 vtable 포인터(vptr)를 가짐. Sensor의 vtable에는 가상 함수 describe와 calibrate의 구현 주소가 들어 있음',
			stack: [plain({ pointsTo: 's0' })],
			heap: sensorTable,
		},
		{
			line: 2,
			note: 'Thermometer 객체의 vptr은 Thermometer의 vtable을 가리킴. describe 칸은 재정의한 Thermometer판, calibrate 칸은 재정의하지 않았으므로 Sensor판 그대로',
			stack: [plain({ pointsTo: 's0' }), kitchen({ pointsTo: 't0' })],
			heap: [...sensorTable, ...thermoTable],
		},
		{
			line: 3,
			note: 'ref는 kitchen의 별명일 뿐. 컴파일러가 보는 타입은 Sensor지만, 가리키는 객체의 vptr은 여전히 Thermometer의 vtable',
			stack: [plain({ pointsTo: 's0' }), kitchen({ pointsTo: 't0', aliases: ['ref'] })],
			heap: [...sensorTable, ...thermoTable],
		},
		{
			line: 4,
			note: 'ref.describe(): 실행 중에 객체의 vptr을 따라가 0번 칸을 읽음. 그곳에 있는 Thermometer::describe가 불림(동적 바인딩)',
			stack: [plain({ pointsTo: 's0' }), kitchen({ pointsTo: 't0', aliases: ['ref'] })],
			heap: [...sensorTable, entry('t0', 'Thermo', '▶ Thermo::describe'), thermoTable[1]],
		},
		{
			line: 5,
			note: 'ref.calibrate(): 같은 방식으로 1번 칸을 읽음. Thermometer가 재정의하지 않았으므로 Sensor::calibrate가 불림',
			stack: [plain({ pointsTo: 's0' }), kitchen({ pointsTo: 't0', aliases: ['ref'] })],
			heap: [...sensorTable, thermoTable[0], entry('t1', 'Thermo', '▶ Sensor::calibrate')],
		},
		{
			line: 6,
			note: 'ref.kind(): kind는 가상 함수가 아니라 vtable에 칸이 없음. 컴파일할 때 ref의 타입(Sensor)만 보고 Sensor::kind를 부르도록 정해 둠(정적 바인딩)',
			stack: [plain({ pointsTo: 's0' }), kitchen({ pointsTo: 't0', aliases: ['ref'] })],
			heap: [...sensorTable, ...thermoTable],
		},
	],
};
