#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <new>
#include <optional>
#include <print>
#include <stdexcept>
#include <string>

// ---------- C 라이브러리라고 가정한 부분 ----------
// extern "C": 이름을 C 방식으로(맹글링 없이) 내보내고 C 호출 규약을 쓴다.
// 실제로는 이 선언이 C 헤더에, 정의는 C로 컴파일된 라이브러리에 있다.
extern "C" {
struct kv_store {
    char keys[8][32];
    char values[8][32];
    int count;
};

kv_store* kv_open(void)
{
    kv_store* s = static_cast<kv_store*>(std::calloc(1, sizeof(kv_store)));
    return s;
}
void kv_close(kv_store* s) { std::free(s); }

int kv_put(kv_store* s, const char* key, const char* value)   // 0 성공
{
    if (s->count >= 8 || std::strlen(key) >= 32 || std::strlen(value) >= 32) {
        return -1;
    }
    std::strcpy(s->keys[s->count], key);
    std::strcpy(s->values[s->count], value);
    ++s->count;
    return 0;
}

const char* kv_get(const kv_store* s, const char* key)   // 없으면 NULL
{
    for (int i = 0; i < s->count; ++i) {
        if (std::strcmp(s->keys[i], key) == 0) { return s->values[i]; }
    }
    return nullptr;
}
}

// ---------- 객체 지향 래퍼(퍼사드): C 핸들과 오류 코드를 숨긴다 ----------
class Store final {
public:
    Store() : m_handle{ kv_open(), kv_close }   // RAII: 소멸하면 kv_close
    {
        if (!m_handle) { throw std::bad_alloc{}; }
    }
    void put(const std::string& key, const std::string& value)
    {
        if (kv_put(m_handle.get(), key.c_str(), value.c_str()) != 0) {
            throw std::length_error{ "저장 실패: " + key };
        }
    }
    std::optional<std::string> get(const std::string& key) const
    {
        const char* v{ kv_get(m_handle.get(), key.c_str()) };
        if (!v) { return std::nullopt; }
        return std::string{ v };
    }

private:
    std::unique_ptr<kv_store, decltype(&kv_close)> m_handle;
};

// ---------- 스크립트가 부르는 프로그램처럼: 표준 입력과 종료 코드 ----------
// 입력 줄: "set 키 값" 또는 "get 키". 실패하면 0이 아닌 값으로 끝낸다.
int main()
{
    Store store;
    std::string cmd, key, value;
    int status{ 0 };
    while (std::cin >> cmd >> key) {
        if (cmd == "set" && std::cin >> value) {
            store.put(key, value);
        } else if (cmd == "get") {
            if (auto v{ store.get(key) }) {
                std::println("{}={}", key, *v);
            } else {
                std::println(stderr, "없는 키: {}", key);   // 오류는 stderr로
                status = 2;
            }
        }
    }
    return status;   // 부른 쪽(스크립트)이 이 값으로 성공 여부를 판단
}
