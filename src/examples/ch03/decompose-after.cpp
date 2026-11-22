#include <print>
#include <string>
#include <vector>

struct Student
{
    std::string name;
    std::vector<int> scores;
};

// 점수가 없으면 0.0을 돌려준다.
double calculateAverage(const std::vector<int>& scores)
{
    if (scores.empty()) {
        return 0.0;
    }
    int sum{ 0 };
    for (int score : scores) {
        sum += score;
    }
    return static_cast<double>(sum) / scores.size();
}

char toGrade(double average)
{
    if (average >= 90.0) { return 'A'; }
    if (average >= 80.0) { return 'B'; }
    if (average >= 70.0) { return 'C'; }
    return 'F';
}

void printStudent(const Student& student)
{
    const double average{ calculateAverage(student.scores) };
    std::println("{:<6} {:>5.1f} {}", student.name, average,
                 toGrade(average));
}

// students는 비어 있지 않아야 한다.
const Student& findBestStudent(const std::vector<Student>& students)
{
    const Student* best{ &students.front() };
    for (const auto& student : students) {
        if (calculateAverage(student.scores)
            > calculateAverage(best->scores)) {
            best = &student;
        }
    }
    return *best;
}

// 읽으면 하는 일의 순서가 그대로 보인다.
void report(const std::vector<Student>& students)
{
    for (const auto& student : students) {
        printStudent(student);
    }
    const Student& best{ findBestStudent(students) };
    std::println("최고 평균: {} ({:.1f})", best.name,
                 calculateAverage(best.scores));
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
