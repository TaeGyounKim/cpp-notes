#include <print>

// 세밀하지만 많은 인터페이스: 하고 싶은 일 하나에 여러 단계가 필요하다.
class Image
{
public:
    void adjustBrightness(int amount) { std::println("밝기 {:+}", amount); }
    void adjustContrast(int amount) { std::println("대비 {:+}", amount); }
    void sharpen(double radius) { std::println("선명하게 {}", radius); }
    void reduceNoise(int level) { std::println("잡티 제거 {}", level); }
    void crop(int top, int left, int bottom, int right)
    {
        std::println("자르기 {} {} {} {}", top, left, bottom, right);
    }
};

// 퍼사드: 자주 하는 일을 쉬운 인터페이스 하나로 감싼다.
// 세밀한 조절이 필요한 사람은 여전히 Image를 직접 쓸 수 있다.
class QuickEdit
{
public:
    explicit QuickEdit(Image& image) : m_image{ image } {}

    void autoEnhance()
    {
        m_image.reduceNoise(2);
        m_image.adjustBrightness(10);
        m_image.adjustContrast(5);
        m_image.sharpen(1.5);
    }

private:
    Image& m_image;
};

int main()
{
    Image photo;
    QuickEdit edit{ photo };
    edit.autoEnhance();          // 흔한 경우는 쉽게
    photo.crop(0, 0, 600, 800);  // 드문 경우도 가능하게
}
