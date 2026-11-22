#include <algorithm>
#include <filesystem>
#include <format>
#include <fstream>
#include <print>
#include <string>
#include <utility>
#include <vector>

namespace fs = std::filesystem;

int main()
{
    // 경로 조작: 실제 파일이 없어도 된다.
    fs::path p{ "/data/sensors/room.csv" };
    std::println("부모 {}, 파일 {}, 줄기 {}, 확장자 {}",
                 p.parent_path().string(), p.filename().string(),
                 p.stem().string(), p.extension().string());

    fs::path dir{ "/data" };
    dir /= "logs";                 // 구분자를 넣어 덧붙임
    fs::path name{ "day" };
    name += "01.txt";              // 구분자 없이 이어 붙임
    std::println("{} / {}", dir.string(), (dir / name).string());

    for (const auto& part : p) { std::print("[{}]", part.string()); }
    std::println("");

    // 실제 파일 시스템: 임시 폴더 아래에 디렉터리와 파일을 만든다.
    fs::path root{ fs::temp_directory_path() / "fs-demo" };
    fs::remove_all(root);                          // 이전 실행 흔적 지우기
    fs::create_directories(root / "a" / "b");
    std::ofstream{ root / "top.txt" } << "12345";
    std::ofstream{ root / "a" / "b" / "deep.txt" } << "abc";

    fs::directory_entry entry{ root / "top.txt" };
    if (entry.exists() && entry.is_regular_file()) {
        std::println("top.txt {}바이트", entry.file_size());
    }

    // 재귀 순회. 순서는 정해져 있지 않으므로 상대 경로로 정렬해 보인다.
    std::vector<std::pair<std::string, std::string>> rows;
    for (fs::recursive_directory_iterator it{ root }, end; it != end; ++it) {
        std::string rel{ fs::relative(it->path(), root).generic_string() };
        std::string spacer(it.depth() * 2, ' ');
        if (it->is_regular_file()) {
            rows.emplace_back(rel, std::format("{}파일 {} ({}바이트)", spacer,
                                               rel, it->file_size()));
        } else if (it->is_directory()) {
            rows.emplace_back(rel, std::format("{}폴더 {}", spacer, rel));
        }
    }
    std::ranges::sort(rows);
    for (const auto& row : rows) { std::println("{}", row.second); }

    std::println("삭제한 항목 {}개", fs::remove_all(root));
}
