#include <print>

// ---- 외부 라이브러리라고 가정: 정의만 볼 수 있고 구현은 바꿀 수 없다 ----
// 강수량을 인치 단위로만 다룬다. 내일 강수량 예측도 해 준다.
class RainGauge
{
public:
    virtual ~RainGauge() = default;
    virtual void setTodayInches(double inches) { m_today = inches; }
    virtual double tomorrowInches() const { return m_today * 0.8 + 0.05; }
    virtual double chanceOfRain() const { return m_today > 0.3 ? 0.7 : 0.2; }
    virtual void showReport() const   // 출력 모양이 마음에 들지 않는다.
    {
        std::println("RESULT {:.2f} IN / P={:.2f}", tomorrowInches(),
                     chanceOfRain());
    }

private:
    double m_today{ 0.0 };
};
// ---- 라이브러리 끝 ----

class MetricRainGauge : public RainGauge
{
public:
    // 기능 더하기: 밀리미터로 쓰는 인터페이스. 기반 클래스 기능을 감싼다.
    virtual void setTodayMillimeters(double mm)
    {
        setTodayInches(toInches(mm));        // 변환 후 기반 클래스에 맡김
    }
    virtual double tomorrowMillimeters() const
    {
        return toMillimeters(tomorrowInches());
    }

    // 기능 바꾸기: 보고서 모양을 재정의
    void showReport() const override
    {
        std::println("내일 강수량 {:.1f}mm ({:.2f}in)", tomorrowMillimeters(),
                     tomorrowInches());
        std::println("비 올 확률 {:.0f}%", chanceOfRain() * 100);
        if (chanceOfRain() > 0.5) {
            std::println("우산을 챙기세요!");
        }
    }

private:
    static double toInches(double mm) { return mm / 25.4; }
    static double toMillimeters(double inches) { return inches * 25.4; }
};

int main()
{
    MetricRainGauge gauge;
    gauge.setTodayMillimeters(12.7);   // 0.5인치

    const RainGauge& asBase{ gauge };
    asBase.showReport();               // 재정의한 판이 불린다.
}
