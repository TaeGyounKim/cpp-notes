#include <print>
#include <stdexcept>
#include <string>
#include <vector>

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

    const int FirstTaskId{ 1'000 };

    class TaskList
    {
    public:
        // 새 할 일을 추가하고, 추가된 할 일의 참조를 돌려준다.
        Task& addTask(const std::string& title);

        // 번호 또는 제목으로 찾는다. 없으면 예외를 던진다.
        Task& getTask(int id);
        Task& getTask(const std::string& title);

        void displayAll() const;
        void displayPending() const;
        void displayDone() const;

    private:
        std::vector<Task> m_tasks;
        int m_nextId{ FirstTaskId };
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

    Task& TaskList::addTask(const std::string& title)
    {
        Task task{ title };
        task.setId(m_nextId++);   // 번호를 쓰고 난 뒤 1 올린다.
        m_tasks.push_back(task);
        return m_tasks.back();    // back(): 마지막 원소의 참조
    }

    Task& TaskList::getTask(int id)
    {
        for (auto& task : m_tasks) {   // auto&: 복사본이 아니라 원소 자체
            if (task.getId() == id) {
                return task;
            }
        }
        throw std::logic_error{ "그런 번호의 할 일이 없습니다." };
    }

    Task& TaskList::getTask(const std::string& title)
    {
        for (auto& task : m_tasks) {
            if (task.getTitle() == title) {
                return task;
            }
        }
        throw std::logic_error{ "그런 제목의 할 일이 없습니다." };
    }

    void TaskList::displayAll() const
    {
        for (const auto& task : m_tasks) {
            task.display();
        }
    }

    void TaskList::displayPending() const
    {
        for (const auto& task : m_tasks) {
            if (!task.isDone()) {
                task.display();
            }
        }
    }

    void TaskList::displayDone() const
    {
        for (const auto& task : m_tasks) {
            if (task.isDone()) {
                task.display();
            }
        }
    }
}

// TaskList 클래스를 시험해 본다.
int main()
{
    todo::TaskList list;

    todo::Task& first{ list.addTask("report") };
    first.complete();

    todo::Task& second{ list.addTask("email") };
    second.raisePriority(2);

    list.addTask("cleanup");

    std::println("== 전체 ==");
    list.displayAll();

    std::println("== 남은 일 ==");
    list.displayPending();

    std::println("== 끝낸 일 ==");
    list.displayDone();

    try {
        list.getTask(9999).complete();
    } catch (const std::logic_error& exception) {
        std::println("찾지 못함: {}", exception.what());
    }
}
