#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct TimePoint {
    int d, m, y;
    
    int asDays() const {
        return y * 372 + m * 31 + d;
    }
};

struct LifeEvent {
    int dayCount;
    bool begins;
    
    bool operator<(const LifeEvent& other) const { 
        if (dayCount == other.dayCount) { // Если события произошли в один день
            return !begins && other.begins; // Сначала обрабатываем окончания периодов
        }
        return dayCount < other.dayCount; // Иначе сортируем по дате
    }
};

int main() {
    int peopleCount;
    cin >> peopleCount;
    
    vector<LifeEvent> timeline;
    
    for (int i = 0; i < peopleCount; ++i) {
        TimePoint born, died;
        cin >> born.d >> born.m >> born.y;
        cin >> died.d >> died.m >> died.y;
        
        TimePoint adultAge = born;
        adultAge.y += 18;
        
        // успел ли человек достичь 18 до смерти?
        if (adultAge.asDays() > died.asDays()) {
            continue;
        }
        
        TimePoint elderlyAge = born;
        elderlyAge.y += 80;
        
        TimePoint periodEnd = (elderlyAge.asDays() > died.asDays()) ? died : elderlyAge;
        
        timeline.push_back({adultAge.asDays(), true});
        timeline.push_back({periodEnd.asDays(), false});
    }
    
    sort(timeline.begin(), timeline.end());
    
    int activePeople = 0;
    int maxTogether = 0;
    
    for (const LifeEvent& moment : timeline) {
        if (moment.begins) {
            activePeople++;
            if (activePeople > maxTogether) {
                maxTogether = activePeople;
            }
        } else {
            activePeople--;
        }
    }
    
    cout << maxTogether << endl;
    
    return 0;
}