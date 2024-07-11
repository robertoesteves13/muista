#pragma once

#include <QObject>

class WordProficiency {
  public:
    enum Value : uint8_t { New, Learning, Familiar, Master };

    WordProficiency() = default;
    constexpr WordProficiency(Value aFruit) : m_value(aFruit) {}

    constexpr operator Value() const { return m_value; }
    explicit operator bool() const = delete;

    quint32 weight() {
        switch (this->m_value) {
        case WordProficiency::New:
            return 0;
        case WordProficiency::Learning:
            return 1;
        case WordProficiency::Familiar:
            return 3;
        case WordProficiency::Master:
            return 5;
        }
    }

    WordProficiency upgrade() {
        switch (this->m_value) {
        case WordProficiency::New:
            return WordProficiency::Learning;
        case WordProficiency::Learning:
            return WordProficiency::Familiar;
        case WordProficiency::Familiar:
            return WordProficiency::Master;
        case WordProficiency::Master:
            return WordProficiency::Master;
        }
    }

  private:
    Value m_value;
};

