#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace todo
{
    const int FirstTaskId{ 1000 };   // 자릿수 구분자(1'000)는 C++14부터

    class Task
    {
    public:
        Task(const std::string& title)
            : m_title{ title }
        {
        }

        void complete() { m_done = true; }
        void setId(int id) { m_id = id; }
        int getId() const { return m_id; }
        const std::string& getTitle() const { return m_title; }
        bool isDone() const { return m_done; }

        void display() const
        {
            std::cout << '[' << getId() << "] " << getTitle() << ' '
                      << (isDone() ? "done" : "pending") << '\n';
        }

    private:
        std::string m_title;
        int m_id{ -1 };
        bool m_done{ false };
    };

    class TaskList
    {
    public:
        Task& addTask(const std::string& title)
        {
            Task task{ title };
            task.setId(m_nextId++);
            m_tasks.push_back(task);
            return m_tasks.back();
        }

        Task& getTask(int id)
        {
            for (auto& task : m_tasks) {
                if (task.getId() == id) {
                    return task;
                }
            }
            throw std::logic_error{ "no such task" };
        }

        void displayAll() const
        {
            for (const auto& task : m_tasks) {
                task.display();
            }
        }

    private:
        std::vector<Task> m_tasks;
        int m_nextId{ FirstTaskId };
    };
}

int main()
{
    todo::TaskList list;
    list.addTask("report");
    list.addTask("email");
    list.getTask(1000).complete();
    list.displayAll();

    try {
        list.getTask(9999).complete();
    } catch (const std::logic_error& exception) {
        std::cout << "error: " << exception.what() << '\n';
    }
}
