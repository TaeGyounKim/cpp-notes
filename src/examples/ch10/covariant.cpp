#include <print>

// 평행한 두 계층: 기록 장치와, 그 장치가 쓰는 저장 매체
class Storage
{
public:
    virtual ~Storage() = default;
    virtual void printType() const = 0;
};

class SdCard : public Storage
{
public:
    void printType() const override { std::println("  SD 카드"); }
    virtual void format() { std::println("  SD 카드 포맷"); }
};

class CloudDrive : public Storage
{
public:
    void printType() const override { std::println("  클라우드"); }
    virtual void sync() { std::println("  클라우드 동기화"); }
};

class Recorder
{
public:
    virtual ~Recorder() = default;
    virtual Storage& readyStorage() = 0;
};

class Dashcam : public Recorder
{
public:
    // 공변 반환 타입: Storage& 대신 더 구체적인 SdCard&를 돌려준다.
    SdCard& readyStorage() override
    {
        m_card.format();
        return m_card;
    }

private:
    SdCard m_card;
};

class Doorbell : public Recorder
{
public:
    CloudDrive& readyStorage() override
    {
        m_drive.sync();
        return m_drive;
    }

private:
    CloudDrive m_drive;
};

int main()
{
    Dashcam cam;
    cam.readyStorage().format();   // SdCard&를 받으므로 format()을 바로 부름

    Doorbell bell;
    Recorder& any{ bell };
    any.readyStorage().printType();   // Recorder로 보면 Storage&
}
