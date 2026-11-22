#include <print>
#include <string>
#include <vector>

struct Student
{
    std::string name;
    std::vector<int> scores;
};

// 한 함수가 모든 일을 한다: 평균 계산, 등급 판정, 최고 점수 찾기, 출력
void report(const std::vector<Student>& students)
{
    double bestAverage{ 0.0 };
    std::string bestName;
    for (const auto& student : students) {
        double average{ 0.0 };
        if (!student.scores.empty()) {
            int sum{ 0 };
            for (int score : student.scores) {
                sum += score;
            }
            average = static_cast<double>(sum) / student.scores.size();
        }
        char grade{ 'F' };
        if (average >= 90.0) {
            grade = 'A';
        } else if (average >= 80.0) {
            grade = 'B';
        } else if (average >= 70.0) {
            grade = 'C';
        }
        std::println("{:<6} {:>5.1f} {}", student.name, average, grade);
        if (average > bestAverage) {
            bestAverage = average;
            bestName = student.name;
        }
    }
    std::println("최고 평균: {} ({:.1f})", bestName, bestAverage);
}

int main()
{
    std::vector<Student> students{
        { "Kim", { 95, 88, 92 } },
        { "Lee", { 72, 65, 80 } },
        { "Park", {} },
    };
    report(students);
}
