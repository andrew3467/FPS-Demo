//
// Created by Andrew Graser on 4/25/2024.
//

#ifndef FPS_DEMO_EVENT_H
#define FPS_DEMO_EVENT_H

#endif //FPS_DEMO_EVENT_H


namespace Engine {
    enum class EventType {
        WINDOW_CLOSE, WINDOW_RESIZE,
        KEY_PRESS, KEY_RELEASE, KEY_REPEAT,
        CURSOR_MOVE, SCROLL
    };

    class Event {
    public:
        Event(EventType type) : mType(type) {}
        virtual ~Event() = default;

        EventType GetType() {return mType;}

    private:
        EventType mType;
    };

    class EventHandler {
    public:
        void Dispatch(const Event *event) {

        }
    };
}