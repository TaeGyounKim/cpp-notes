#include <cstdio>

// C++11판: std::println(C++23) 대신 std::printf
class RainGauge   // 외부 라이브러리라고 가정
{
public:
    virtual ~RainGauge() {}
    virtual void setTodayInches(double inches) { m_today = inches; }
    virtual double tomorrowInches() const { return m_today * 0.8 + 0.05; }
    virtual double chanceOfRain() const { return m_today > 0.3 ? 0.7 : 0.2; }
    virtual void showReport() const
    {
        std::printf("RESULT %.2f IN / P=%.2f\n", tomorrowInches(),
                    chanceOfRain());
    }

private:
    double m_today = 0.0;
};

class MetricRainGauge : public RainGauge
{
public:
    virtual void setTodayMillimeters(double mm) { setTodayInches(mm / 25.4); }
    virtual double tomorrowMillimeters() const
    {
        return tomorrowInches() * 25.4;
    }
    void showReport() const override
    {
        std::printf("내일 강수량 %.1fmm, 비 올 확률 %.0f%%\n",
                    tomorrowMillimeters(), chanceOfRain() * 100);
    }
};

int main()
{
    MetricRainGauge gauge;
    gauge.setTodayMillimeters(12.7);
    const RainGauge& asBase = gauge;
    asBase.showReport();
}
