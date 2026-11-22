#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Field
{
public:
    virtual ~Field() {}
    virtual void set(const std::string& text) = 0;
    virtual std::string text() const = 0;
};

// std::optional(C++17) 대신 "값이 있는가" 플래그를 따로 둔다.
class TextField : public Field
{
public:
    void set(const std::string& text) override
    {
        m_value = text;
        m_hasValue = true;
    }
    std::string text() const override { return m_hasValue ? m_value : ""; }

private:
    std::string m_value;
    bool m_hasValue = false;
};

int main()
{
    std::vector<std::unique_ptr<Field>> form;
    // std::make_unique(C++14) 대신 new를 unique_ptr에 넘긴다.
    form.push_back(std::unique_ptr<Field>(new TextField()));
    form.push_back(std::unique_ptr<Field>(new TextField()));
    form[0]->set("부엌");
    for (const auto& field : form) {
        std::cout << '[' << field->text() << "]\n";
    }
}
