#include <iostream>
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

// ---- 사용자 인터페이스 ----
int showMenu();
void doAdd(todo::TaskList& list);
void doComplete(todo::TaskList& list);
void doRaise(todo::TaskList& list);

int main()
{
    todo::TaskList list;
    bool done{ false };

    while (!done) {
        int selection{ showMenu() };
        switch (selection) {
            case 0:
                done = true;
                break;
            case 1:
                doAdd(list);
                break;
            case 2:
                doComplete(list);
                break;
            case 3:
                doRaise(list);
                break;
            case 4:
                list.displayAll();
                break;
            case 5:
                list.displayPending();
                break;
            case 6:
                list.displayDone();
                break;
            default:
                std::println(std::cerr, "없는 메뉴입니다.");
                break;
        }
    }
    std::println("종료합니다.");
}

int showMenu()
{
    std::println("");
    std::println("1) 추가  2) 끝냄  3) 우선순위 올리기");
    std::println("4) 전체  5) 남은 일  6) 끝낸 일  0) 종료");
    std::print("메뉴 > ");

    int selection{};
    std::cin >> selection;
    std::println("{}", selection);
    return selection;
}

void doAdd(todo::TaskList& list)
{
    std::print("제목? ");
    std::string title;
    std::cin >> title;

    auto& task{ list.addTask(title) };
    std::println("{} -> {}번으로 추가함", title, task.getId());
}

void doComplete(todo::TaskList& list)
{
    std::print("번호? ");
    int id{};
    std::cin >> id;
    std::println("{}", id);

    try {
        auto& task{ list.getTask(id) };
        task.complete();
        std::println("{}번을 끝냄으로 표시함", id);
    } catch (const std::logic_error& exception) {
        std::println(std::cerr, "{}번 처리 실패: {}", id, exception.what());
    }
}

void doRaise(todo::TaskList& list)
{
    std::print("번호? ");
    int id{};
    std::cin >> id;
    std::println("{}", id);

    std::print("얼마나? ");
    int amount{};
    std::cin >> amount;
    std::println("{}", amount);

    try {
        auto& task{ list.getTask(id) };
        task.raisePriority(amount);
        std::println("{}번의 우선순위: {}", id, task.getPriority());
    } catch (const std::logic_error& exception) {
        std::println(std::cerr, "{}번 처리 실패: {}", id, exception.what());
    }
}
