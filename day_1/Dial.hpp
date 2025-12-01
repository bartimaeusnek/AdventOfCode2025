// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include <memory>
#include <cstdint>

template <typename T>
class DialNode {
public:
    explicit DialNode(T value) : m_value(value) {}
    T m_value;
    std::shared_ptr<DialNode> m_next;
    std::weak_ptr<DialNode> m_prev;
};

template <typename T>
class Dial {
public:
    explicit Dial(const uint32_t maximum, T starting_point) : m_clicks(0) {
        if (maximum == 0) return;

        auto start = std::make_shared<DialNode<T>>(0);
        auto last = start;

        for (uint32_t i = 1; i < maximum; ++i) {
            auto node = std::make_shared<DialNode<T>>(i);
            last->m_next = node;
            node->m_prev = last;
            last = node;
        }

        last->m_next = start;
        start->m_prev = last;

        m_current = start;
        while (Current() != starting_point) {
            m_current = m_current->m_next;
        }
    }

    [[nodiscard]] T MoveLeft(const uint32_t by) {
        for (uint32_t i = 0; i < by; ++i) {
            m_current = m_current->m_prev.lock();
            if (!Current()) ++m_clicks;
        }
        return m_current->m_value;
    }
    [[nodiscard]] T MoveRight(const uint32_t by) {
        for (uint32_t i = 0; i < by; ++i) {
            m_current = m_current->m_next;
            if (!Current()) ++m_clicks;
        }
        return m_current->m_value;
    }

    [[nodiscard]] T Current() const {
        return m_current->m_value;
    }

    [[nodiscard]] uint32_t get_clicks() const {
        return m_clicks;
    }

private:
    std::shared_ptr<DialNode<T>> m_current;
    uint32_t m_clicks;
};