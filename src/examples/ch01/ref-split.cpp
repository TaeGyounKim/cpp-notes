#include <print>
#include <vector>

// 방법 1: 결과를 참조 매개변수로 내보낸다. (출력 매개변수)
void splitScores(const std::vector<int>& scores,
                 std::vector<int>& passed, std::vector<int>& failed)
{
    for (int score : scores) {
        if (score >= 60) {
            passed.push_back(score);
        } else {
            failed.push_back(score);
        }
    }
}

// 방법 2: 결과를 구조체에 담아 값으로 돌려준다. (권장)
struct SplitResult
{
    std::vector<int> passed;
    std::vector<int> failed;
};

SplitResult splitScores(const std::vector<int>& scores)
{
    SplitResult result;
    for (int score : scores) {
        if (score >= 60) {
            result.passed.push_back(score);
        } else {
            result.failed.push_back(score);
        }
    }
    return result;
}

int main()
{
    std::vector<int> scores{ 90, 45, 72, 58, 60 };

    std::vector<int> passed;
    std::vector<int> failed;
    splitScores(scores, passed, failed);
    std::println("{} {}", passed, failed);

    SplitResult result{ splitScores(scores) };
    std::println("{} {}", result.passed, result.failed);
}
