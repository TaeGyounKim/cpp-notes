#include <print>
#include <string>

namespace todo
{
    const int DefaultPriority{ 3 };
    const int DefaultPriorityStep{ 1 };

    class Task
    {
    public:
        Task(const std::string& title);

        // 인수를 생략하면 DefaultPriorityStep이 쓰인다. (기본 인수)
        void raisePriority(int amount = DefaultPriorityStep);
        void lowerPriority(int amount = DefaultPriorityStep);
        void complete();   // 끝냄으로 표시
        void reopen();     // 다시 남은 일로 되돌림
        void display() const;

        void setTitle(const std::string& title);
        const std::string& getTitle() const;

        void setId(int id);
        int getId() const;

        void setPriority(int priority);
        int getPriority() const;

        bool isDone() const;

    private:
        std::string m_title;
        int m_id{ -1 };
        int m_priority{ DefaultPriority };
        bool m_done{ false };
    };

    Task::Task(const std::string& title)
        : m_title{ title }
    {
    }

    // 기본 인수는 선언에만 적는다. 정의에는 다시 적지 않는다.
    void Task::raisePriority(int amount)
    {
        setPriority(getPriority() + amount);
    }

    void Task::lowerPriority(int amount)
    {
        setPriority(getPriority() - amount);
    }

    void Task::complete() { m_done = true; }
    void Task::reopen() { m_done = false; }

    void Task::display() const
    {
        std::println("[{}] {} (우선순위 {}) {}", getId(), getTitle(),
                     getPriority(), isDone() ? "끝냄" : "남음");
    }

    void Task::setTitle(const std::string& title) { m_title = title; }
    const std::string& Task::getTitle() const { return m_title; }

    void Task::setId(int id) { m_id = id; }
    int Task::getId() const { return m_id; }

    void Task::setPriority(int priority) { m_priority = priority; }
    int Task::getPriority() const { return m_priority; }

    bool Task::isDone() const { return m_done; }
}

// Task 클래스만 따로 시험해 본다.
int main()
{
    todo::Task task{ "report" };
    task.display();

    task.setTitle("monthly-report");
    task.setId(71);
    task.raisePriority();    // 기본 인수: 1만큼 올린다.
    task.raisePriority(5);   // 5만큼 올린다.
    task.lowerPriority(2);
    task.complete();
    task.display();
}
