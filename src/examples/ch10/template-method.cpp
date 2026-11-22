#include <print>

class BatteryEstimator
{
public:
    virtual ~BatteryEstimator() = default;

    // 템플릿 메서드: 계산의 뼈대. 가상 함수가 아니다.
    int hoursLeft() const { return m_percent * hoursPerPercent() / 10; }
    void setPercent(int percent) { m_percent = percent; }

private:
    int m_percent{ 0 };
    // 파생 클래스가 바꿀 부분. private이어도 재정의할 수 있다.
    virtual int hoursPerPercent() const { return 2; }
};

class LowPowerEstimator : public BatteryEstimator
{
private:
    int hoursPerPercent() const override { return 5; }
};

int main()
{
    BatteryEstimator normal;
    normal.setPercent(50);
    LowPowerEstimator saver;
    saver.setPercent(50);
    std::println("일반: {}시간, 절전: {}시간", normal.hoursLeft(),
                 saver.hoursLeft());
}
