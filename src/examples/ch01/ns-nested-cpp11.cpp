#include <iostream>

// C++11 ~ C++14: 네임스페이스 블록을 하나씩 겹쳐 쓴다.
namespace studio {
    namespace audio {
        namespace effects {
            void echo()
            {
                std::cout << "메아리 효과" << '\n';
            }
        }
    }
}

// 네임스페이스 별칭은 C++11에서도 쓸 수 있다.
namespace fx = studio::audio::effects;

int main()
{
    studio::audio::effects::echo();
    fx::echo();
}
