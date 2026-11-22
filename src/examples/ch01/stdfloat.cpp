#include <print>
#include <stdfloat>

int main()
{
    std::float16_t half{ 0.1f16 };
    std::float32_t single{ 0.1f32 };
    std::float64_t dbl{ 0.1f64 };

    // sizeof(변수)는 그 변수가 차지하는 바이트 수
    std::println("float16_t: {}바이트, 0.1 = {}", sizeof(half), half);
    std::println("float32_t: {}바이트, 0.1 = {}", sizeof(single), single);
    std::println("float64_t: {}바이트, 0.1 = {}", sizeof(dbl), dbl);

    // 같은 0.1을 더 긴 자릿수로 찍으면 정밀도 차이가 보인다.
    std::println("{:.20f}", half);
    std::println("{:.20f}", single);
    std::println("{:.20f}", dbl);
}
