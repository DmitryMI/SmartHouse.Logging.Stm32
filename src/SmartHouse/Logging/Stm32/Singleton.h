#pragma once

template <typename T, typename CONTEXT>
class Singleton
{
public:
    // Very fast inlined operator accessors
    T* operator->() { return m_Instance; }
    const T* operator->() const { return m_Instance; }
    T& operator*() { return *m_Instance; }
    const T& operator*() const { return *m_Instance; }

protected:
    Singleton()
    {
        static bool static_init = []()->bool {
            m_Instance = new T;
            return true;
            }();
    }

    Singleton(int)
    {
        static bool static_init = []()->bool {
            m_Instance = CONTEXT::init();
            return true;
            }();
    }

private:
    static T* m_Instance;
};

template <typename T, typename CONTEXT>
T* Singleton<T, CONTEXT>::m_Instance;