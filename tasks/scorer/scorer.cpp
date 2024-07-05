#include <iostream>
#include <algorithm>
#include "scorer.h"
bool Comparator(const Event*& x, const Event*& y) {
    return x->time < y->time;
}
ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    std::vector<const Event*> events_pointers;
    for (const Event& event : events) {
        events_pointers.push_back(&event);
    }
    std::sort(events_pointers.begin(), events_pointers.end(), Comparator);
    ScoreTable table;
    for (const Event* event : events_pointers) {
        if (event->time > score_time) {
            break;
        }
        if (event->event_type == EventType::CheckSuccess) {
            table[event->student_name].insert(event->task_name);
        } else if (event->event_type == EventType::CheckFailed) {
            table[event->student_name].erase(event->task_name);
            if (table[event->student_name].empty()) {
                table.erase(event->student_name);
            }
        } else if (event->event_type == EventType::MergeRequestClosed) {
            table[event->student_name].insert(event->task_name);
        } else {
            table[event->student_name].erase(event->task_name);
            if (table[event->student_name].empty()) {
                table.erase(event->student_name);
            }
        }
    }
    return table;  // test
}
