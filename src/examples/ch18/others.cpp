#include <bitset>
#include <cstddef>
#include <iterator>
#include <map>
#include <print>
#include <stdexcept>
#include <string>
#include <vector>

// 집의 방마다 켜 둔 기능을 비트로 기록한다. 비트 번호가 기능 번호다.
class SmartHome
{
public:
    static constexpr std::size_t Features{ 8 };
    using Flags = std::bitset<Features>;

    void addPreset(const std::string& name, const std::string& bits)
    {
        m_presets.emplace(name, Flags{ bits });   // "0" "1" 문자열로 만듦
    }

    void addRoom(const std::string& room, const std::string& preset)
    {
        auto it{ m_presets.find(preset) };
        if (it == m_presets.end()) { throw std::out_of_range{ "없는 프리셋" }; }
        if (!m_rooms.emplace(room, it->second).second) {
            throw std::invalid_argument{ "이미 있는 방" };
        }
    }

    void enable(const std::string& room, std::size_t feature)
    {
        m_rooms.at(room).set(feature);
    }

    void applyPreset(const std::string& room, const std::string& preset)
    {
        m_rooms.at(room) |= m_presets.at(preset);   // 비트 OR로 합침
    }

    const Flags& features(const std::string& room) const
    {
        return m_rooms.at(room);
    }

private:
    std::map<std::string, Flags> m_presets;
    std::map<std::string, Flags> m_rooms;
};

int main()
{
    // C 배열도 포인터가 반복자이므로 컨테이너처럼 쓸 수 있다.
    int raw[]{ 3, 1, 4, 1, 5 };
    std::vector<int> v;
    v.insert(v.end(), std::cbegin(raw), std::cend(raw));
    v.append_range(raw);                        // C++23
    std::println("{}", v);

    // string도 순차 컨테이너다.
    std::string word;
    word.push_back('h');
    word.insert(word.end(), 'i');
    for (auto it{ word.crbegin() }; it != word.crend(); ++it) {
        std::print("{}", *it);                // 거꾸로
    }
    std::println(" (크기 {}, 용량 {})", word.size(), word.capacity());

    // bitset 기초
    std::bitset<10> bits;                       // 모두 0
    bits.set(3).set(6);
    bits[8] = true;                             // 대리 객체에 대입
    bits[9] = bits[3];
    bits.flip(0);
    std::println("{} / 3번 켜짐? {} / 켜진 비트 {}개", bits.to_string(),
                 bits.test(3), bits.count());

    std::bitset<10> a{ "0011001100" };
    std::bitset<10> b{ "0000111100" };
    auto both{ a & b };
    std::println("a & b  {}", both.to_string());
    both <<= 4;
    std::println("<<= 4  {}", both.to_string());

    SmartHome home;
    home.addPreset("기본", "00000011");        // 0번, 1번 기능
    home.addPreset("보안", "11000000");        // 6번, 7번 기능
    home.addRoom("거실", "기본");
    home.enable("거실", 4);
    home.applyPreset("거실", "보안");
    std::println("거실 {}", home.features("거실").to_string());
    try {
        home.addRoom("거실", "기본");
    } catch (const std::invalid_argument& e) {
        std::println("{}", e.what());
    }
}
