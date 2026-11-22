#include <array>
#include <cstddef>
#include <mdspan>
#include <print>
#include <span>
#include <vector>

// 읽기만 하므로 span<const int>. vector, array, C 배열 모두 받는다.
int total(std::span<const int> values)
{
    int sum{ 0 };
    for (int v : values) { sum += v; }
    return sum;
}

// 원소를 고치는 함수는 span<int>. 원본이 바뀐다.
void scale(std::span<int> values, int factor)
{
    for (int& v : values) { v *= factor; }
}

// 2차원 뷰를 행과 열로 출력한다.
void printGrid(const auto& grid)
{
    using Index = decltype(grid.extent(0));     // mdspan의 index_type
    for (Index r{ 0 }; r < grid.extent(0); ++r) {
        for (Index c{ 0 }; c < grid.extent(1); ++c) {
            std::print("{:>3}", grid[r, c]);       // C++23 다차원 첨자
        }
        std::println("");
    }
}

int main()
{
    std::vector v{ 11, 22, 33, 44, 55, 66 };
    std::array<int, 5> arr{ 5, 4, 3, 2, 1 };
    int carr[]{ 9, 8, 7 };
    std::println("합 {} {} {}", total(v), total(arr), total(carr));

    std::span all{ v };                             // 포인터와 길이뿐
    std::println("subspan(2, 3) {} first(2) {} last(2) {}", all.subspan(2, 3),
                 all.first(2), all.last(2));
    std::println("가운데 셋의 합 {}", total({ v.data() + 2, 3 }));

    scale(all.first(2), 10);                        // 앞 둘만 10배
    std::println("원본 {}", v);

    // mdspan: 연속된 8개를 2행 4열로 본다.
    std::vector cells{ 1, 2, 3, 4, 5, 6, 7, 8 };
    std::mdspan rows{ cells.data(), 2, 4 };         // 기본: 행 우선
    printGrid(rows);
    std::println("크기 {}, 행을 하나 넘을 때 건너뛰는 원소 {}", rows.size(),
                 rows.stride(0));

    // 열 우선 배치, 컴파일 시간에 정한 크기
    std::mdspan<int, std::extents<int, 2, 4>, std::layout_left> cols{
        cells.data() };
    printGrid(cols);

    // 첫 차원은 고정, 둘째는 실행 시간에
    std::mdspan<int, std::extents<int, 2, std::dynamic_extent>> mixed{
        cells.data(), 4 };
    mixed[1, 3] = 80;                               // 원본이 바뀐다.
    std::println("cells {}", cells);
}
